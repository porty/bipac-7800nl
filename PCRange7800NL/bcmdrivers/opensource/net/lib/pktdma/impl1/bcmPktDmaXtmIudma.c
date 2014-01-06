/*
<:copyright-broadcom

 Copyright (c) 2007 Broadcom Corporation
 All Rights Reserved
 No portions of this material may be reproduced in any form without the
 written permission of:
          Broadcom Corporation
          5300 California Avenue
          Irvine, California 92617
 All information contained in this document is Broadcom Corporation
 company private, proprietary, and trade secret.

:>
*/
/*
 *******************************************************************************
 * File Name  : bcmPktDmaXtmIudma.c
 *
 * Description: This file contains the Packet DMA Implementation for the iuDMA
 *              channels of the XTM Controller.
 * Note       : This bcmPktDma code is tied to impl1 of the Xtm Driver 
 *
 *******************************************************************************
 */

#ifndef CONFIG_BCM96816

#if !(defined(CONFIG_BCM_FAP) || defined(CONFIG_BCM_FAP_MODULE))
#include <bcm_intr.h>
#endif

#if defined(CONFIG_BCM_FAP) || defined(CONFIG_BCM_FAP_MODULE)
#include "bcm_log.h"
#include "fap4ke_local.h"
#include "fap_task.h"
#include "fap_dqm.h"
#endif

#include "bcmPktDma.h"

/* fap4ke_local redfines memset to the 4ke lib one - not what we want */
#if defined memset
#undef memset
#endif

#if !defined(CONFIG_BCM_FAP) && !defined(CONFIG_BCM_FAP_MODULE)
/* Define in DDR */
BcmPktDma_LocalXtmRxDma *g_pXtmRxDma[MAX_RECEIVE_QUEUES];
BcmPktDma_LocalXtmTxDma *g_pXtmTxDma[MAX_TRANSMIT_QUEUES];
#endif

/* Binding with XTMRT */
PBCMXTMRT_GLOBAL_INFO g_pXtmGlobalInfo = (PBCMXTMRT_GLOBAL_INFO)NULL; 


int bcmPktDma_XtmInitRxChan_Iudma(uint32 channel,
                                  uint32 bufDescrs,
                                  BcmPktDma_LocalXtmRxDma *pXtmRxDma)
{
    g_pXtmRxDma[channel] = (BcmPktDma_LocalXtmRxDma *)pXtmRxDma;
    g_pXtmRxDma[channel]->numRxBds = bufDescrs;
    g_pXtmRxDma[channel]->rxAssignedBds = 0;
    g_pXtmRxDma[channel]->rxHeadIndex = 0;
    g_pXtmRxDma[channel]->rxTailIndex = 0;
    g_pXtmRxDma[channel]->xtmrxchannel_isr_enable = 1;
    
    g_pXtmRxDma[channel]->rxBds = (volatile DmaDesc *)(pXtmRxDma->rxBds);
    g_pXtmRxDma[channel]->rxDma = (volatile DmaChannelCfg *)(pXtmRxDma->rxDma);
       
    return 1;

}

int bcmPktDma_XtmInitTxChan_Iudma(uint32 channel,
                                  uint32 bufDescrs,
                                  BcmPktDma_LocalXtmTxDma *pXtmTxDma)
{
    //printk("bcmPktDma_XtmInitTxChan_Iudma ch: %ld bufs: %ld txdma: %p\n", 
    //        channel, bufDescrs, pXtmTxDma);

    g_pXtmTxDma[channel] = (BcmPktDma_LocalXtmTxDma *)pXtmTxDma;
    
    g_pXtmTxDma[channel]->txFreeBds = bufDescrs;
    g_pXtmTxDma[channel]->txHeadIndex = 0;
    g_pXtmTxDma[channel]->txTailIndex = 0;
    g_pXtmTxDma[channel]->txEnabled = 1;

    g_pXtmTxDma[channel]->txBds = (volatile DmaDesc *)pXtmTxDma->txBds;
    g_pXtmTxDma[channel]->txDma = (volatile DmaChannelCfg *)pXtmTxDma->txDma;
    g_pXtmTxDma[channel]->pKeyPtr = pXtmTxDma->pKeyPtr;
    
    return 1;
}

/* --------------------------------------------------------------------------
    Name: bcmPktDma_XtmSelectRxIrq
 Purpose: Return IRQ number to be used for bcmPkt Rx on a specific channel
-------------------------------------------------------------------------- */
int	bcmPktDma_XtmSelectRxIrq_Iudma(int channel)
{
    return (SAR_RX_INT_ID_BASE + channel);
}

/* --------------------------------------------------------------------------
    Name: bcmPktDma_XtmRecv
 Purpose: Receive a packet on a specific channel, 
          returning the associated DMA desc
-------------------------------------------------------------------------- */
uint32 bcmPktDma_XtmRecv_Iudma(int channel, unsigned char **pBuf, int * pLen)
{
    BcmPktDma_LocalXtmRxDma *rxdma;
    DmaDesc                  dmaDesc;

    FAP4KE_IUDMA_PMON_DECLARE();
    FAP4KE_IUDMA_PMON_BEGIN(FAP4KE_PMON_ID_IUDMA_RECV);

    dmaDesc.word0 = 0;
    rxdma = g_pXtmRxDma[channel];

    if (rxdma->rxAssignedBds != 0)
    {
        /* Get the status from Rx BD */
        dmaDesc.word0 = rxdma->rxBds[rxdma->rxHeadIndex].word0;

        /* If no more rx packets, we are done for this channel */
        if ((dmaDesc.status & DMA_OWN) == 0)
        {
            *pBuf = (unsigned char *)
                   (phys_to_virt(rxdma->rxBds[rxdma->rxHeadIndex].address));
            *pLen = (int) dmaDesc.length;

            /* Wrap around the rxHeadIndex */
            if (++rxdma->rxHeadIndex == rxdma->numRxBds) 
            {
                rxdma->rxHeadIndex = 0;
            }
            rxdma->rxAssignedBds--;
        }
    } 
    else   /* out of buffers! */
       return (uint32)0xFFFF; 

    //printk("XtmRecv_Iudma end ch: %d head: %d tail: %d assigned: %d\n", channel, rxdma->rxHeadIndex, rxdma->rxTailIndex, rxdma->rxAssignedBds);

    FAP4KE_IUDMA_PMON_END(FAP4KE_PMON_ID_IUDMA_RECV);

    return dmaDesc.word0;
}

/* --------------------------------------------------------------------------
    Name: bcmPktDma_XtmXmitAvailable
 Purpose: Determine if there are free resources for the xmit
   Notes: channel in XTM mode refers to a specific TXQINFO struct of a 
          specific XTM Context
-------------------------------------------------------------------------- */
int bcmPktDma_XtmXmitAvailable_Iudma(int channel) 
{
    BcmPktDma_LocalXtmTxDma *txdma;
    
    txdma = g_pXtmTxDma[channel];
    if (txdma->txFreeBds != 0)  return 1;
    
    return 0;
}

/* --------------------------------------------------------------------------
    Name: bcmPktDma_XtmTxEnable_Iudma
 Purpose: Coordinate with FAP for tx enable
  Return: 1 on success; 0 otherwise
-------------------------------------------------------------------------- */
int bcmPktDma_XtmTxEnable_Iudma( int channel )
{
    BcmPktDma_LocalXtmTxDma *txdma;

    //printk("bcmPktDma_XtmTxEnable_Iudma ch: %d\n", channel);

    txdma = g_pXtmTxDma[channel];
    txdma->txEnabled = 1;
    return 1;
}

/* --------------------------------------------------------------------------
    Name: bcmPktDma_XtmTxDisable_Iudma
 Purpose: Coordinate with FAP for tx disable
  Return: 1 on success; 0 otherwise
-------------------------------------------------------------------------- */
int bcmPktDma_XtmTxDisable_Iudma( int channel )
{
    BcmPktDma_LocalXtmTxDma *txdma;
    int j;

    //printk("bcmPktDma_XtmTxDisable_Iudma ch: %d\n", channel);

    txdma = g_pXtmTxDma[channel];
    txdma->txDma->cfg = 0;
    txdma->txEnabled = 0;

#if 1
    /* Changing the link state to LINK_DOWN prevents any more packets
     * from being queued on a transmit DMA channel.  Allow all currenlty
     * queued transmit packets to be transmitted before disabling the DMA.
     */
    for (j = 0; j < 2000 && (txdma->txDma->cfg & DMA_ENABLE) == DMA_ENABLE; j++)
    {
#if !defined(CONFIG_BCM_FAP) && !defined(CONFIG_BCM_FAP_MODULE)
        udelay(500);
#endif
    }

    if ((txdma->txDma->cfg & DMA_ENABLE) == DMA_ENABLE)
    {
        /* This should not happen. */
        printk(KERN_ERR CARDNAME ":**** DMA_PKT_HALT ****\n");
        txdma->txDma->cfg = DMA_PKT_HALT;
#if !defined(CONFIG_BCM_FAP) && !defined(CONFIG_BCM_FAP_MODULE)
        udelay(500);
#endif
        txdma->txDma->cfg = 0;
    }
#endif

    return 1;
}

/* --------------------------------------------------------------------------
    Name: bcmPktDma_XtmRxEnable
    Purpose: Enable rx DMA for the given channel.  
    Return: 1 on success; 0 otherwise
-------------------------------------------------------------------------- */

int bcmPktDma_XtmRxEnable_Iudma( int channel )
{
    BcmPktDma_LocalXtmRxDma *rxdma = g_pXtmRxDma[channel];

    //printk("bcmPktDma_XtmRxEnable_Iudma channel: %d\n", channel);

    rxdma->rxDma->cfg |= DMA_ENABLE;
    rxdma->rxEnabled = 1;

    return 1;
}

/* --------------------------------------------------------------------------
    Name: bcmPktDma_XtmRxDisable
 Purpose: Disable rx interrupts for the given channel
  Return: 1 on success; 0 otherwise
-------------------------------------------------------------------------- */

int bcmPktDma_XtmRxDisable_Iudma( int channel )
{
    BcmPktDma_LocalXtmRxDma  *rxdma;
    int                       i;

    //printk("bcmPktDma_XtmRxDisable_Iudma channel: %d\n", channel);

    rxdma = g_pXtmRxDma[channel];
    rxdma->rxEnabled = 0;

    rxdma->rxDma->cfg &= ~DMA_ENABLE;
    for (i = 0; rxdma->rxDma->cfg & DMA_ENABLE; i++) 
    {
        rxdma->rxDma->cfg &= ~DMA_ENABLE;
    
        if (i >= 100)
        {
            //printk("Failed to disable RX DMA?\n");
            break;
        }

#if !(defined(CONFIG_BCM_FAP) || defined(CONFIG_BCM_FAP_MODULE))
        /* The delay only works when called from Linux */
        udelay(20);
#endif
    }

    return 1;
}


/* FIXME - Implement range checking */
DmaDesc *bcmPktDma_XtmAllocTxBds(int numBds, int totalBds)
{
    void * p;

    //printk("bcmPktDma_XtmAllocTxBds numBds: %d totalBds: %d\n", numBds, totalBds);

#if defined(TX_BDS_IN_PSM) && (defined(CONFIG_BCM_FAP) || defined(CONFIG_BCM_FAP_MODULE))
{
    unsigned int bdStartAddr;

    /* Tx Descriptors are in PSM. Use Host-side addressing. */
    bdStartAddr = (unsigned int)pHostPsm->global.xtmTxBds;
    bdStartAddr = (bdStartAddr + 7) & 0xFFFFFFF8;   /* force to 8 byte aligned */

    bdStartAddr += ((totalBds - numBds) * sizeof(DmaDesc));
    p = (void *)bdStartAddr;
    memset(p, 0, numBds*sizeof(DmaDesc));
    return((DmaDesc *)p);   /* tx bd ring */
}
#else                                                           
    /* Tx Descriptors are allocated in DDR */
    if ((p = kmalloc(numBds*sizeof(DmaDesc), GFP_KERNEL))) {
        memset(p, 0, numBds*sizeof(DmaDesc));
        cache_flush_len(p, numBds*sizeof(DmaDesc));
    }
    return( (DmaDesc *)(CACHE_TO_NONCACHE(p)) );   /* tx bd ring */
#endif
}

DmaDesc *bcmPktDma_XtmAllocRxBds(int numBds, int totalBds)
{
    void * p;

    //printk("bcmPktDma_XtmAllocRxBds numBds: %d totalBds: %d\n", numBds, totalBds);

#if defined(RX_BDS_IN_PSM) && (defined(CONFIG_BCM_FAP) || defined(CONFIG_BCM_FAP_MODULE))
{
    unsigned int bdStartAddr;

    /* Rx Descriptors are in PSM. Use Host-side addressing. */
    bdStartAddr = (unsigned int)pHostPsm->global.xtmRxBds;
    bdStartAddr = (bdStartAddr + 7) & 0xFFFFFFF8;   /* force to 8 byte aligned */

    bdStartAddr += ((totalBds - numBds) * sizeof(DmaDesc));
    p = (void *)bdStartAddr;
    memset(p, 0, numBds*sizeof(DmaDesc));
    return((DmaDesc *)p);   /* rx bd ring */
}
#else                                                           
    /* Rx Descriptors are allocated in DDR */
    if ((p = kmalloc(numBds*sizeof(DmaDesc), GFP_KERNEL))) {
        memset(p, 0, numBds*sizeof(DmaDesc));
        cache_flush_len(p, numBds*sizeof(DmaDesc));
    }
    return( (DmaDesc *)(CACHE_TO_NONCACHE(p)) );   /* rx bd ring */
#endif
}


EXPORT_SYMBOL(g_pXtmGlobalInfo);

EXPORT_SYMBOL(bcmPktDma_XtmInitRxChan_Iudma);
EXPORT_SYMBOL(bcmPktDma_XtmInitTxChan_Iudma);
EXPORT_SYMBOL(bcmPktDma_XtmSelectRxIrq_Iudma);
EXPORT_SYMBOL(bcmPktDma_XtmClrRxIrq_Iudma);
EXPORT_SYMBOL(bcmPktDma_XtmRecvAvailable_Iudma);
EXPORT_SYMBOL(bcmPktDma_XtmRecv_Iudma);
EXPORT_SYMBOL(bcmPktDma_XtmXmitAvailable_Iudma);
EXPORT_SYMBOL(bcmPktDma_XtmXmit_Iudma);
EXPORT_SYMBOL(bcmPktDma_XtmTxEnable_Iudma);
EXPORT_SYMBOL(bcmPktDma_XtmTxDisable_Iudma);
EXPORT_SYMBOL(bcmPktDma_XtmRxEnable_Iudma);
EXPORT_SYMBOL(bcmPktDma_XtmRxDisable_Iudma);

#if !(defined(CONFIG_BCM_FAP) || defined(CONFIG_BCM_FAP_MODULE))
EXPORT_SYMBOL(g_pXtmRxDma);
EXPORT_SYMBOL(g_pXtmTxDma);
#endif

#endif  /* #ifndef CONFIG_BCM96816 */
