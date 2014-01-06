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
 * File Name  : bcmPktDmaEthIudma.c
 *
 * Description: This file contains the Packet DMA Implementation for the iuDMA
 *              channels of the Ethernet Controller.
 * Note       : This bcmPktDma code is tied to impl3 of the Eth Driver
 *
 *******************************************************************************
 */

#include <bcm_intr.h>
#if defined(CONFIG_BCM96362)
#include "bcm_log.h"
#include "fap4ke_local.h"
#endif
#include "bcmPktDma.h"

#if defined(CONFIG_BCM96362)
#include "fap_task.h"
#include "fap_dqm.h"
#include "fap4ke_memory.h"
#endif

/* Uncomment this define to turn on error checking and logging in the bcmPktDma driver */
//#define ENABLE_BCMPKTDMA_IUDMA_ERROR_CHECKING

/* fap4ke_local redfines memset to the 4ke lib one - not what we want */
#if defined memset
#undef memset
#endif

#if !(defined(CONFIG_BCM_FAP) || defined(CONFIG_BCM_FAP_MODULE))
/* Define in DDR */
BcmPktDma_LocalEthRxDma *g_pEthRxDma[NUM_RXDMA_CHANNELS];
BcmPktDma_LocalEthTxDma *g_pEthTxDma[NUM_TXDMA_CHANNELS];
#endif

/* Globals initialized in the Enet Driver */
BcmEnet_devctrl *   g_pEnetDevCtrl    = (BcmEnet_devctrl *) NULL;   /* Binding with Switch ENET */
/* Create an interface to set this */
int *               g_pEnetrxchannel_isr_enable = (int *)NULL;


int bcmPktDma_EthInitRxChan_Iudma( uint32 channel,
                                     uint32 bufDescrs,
                                     BcmPktDma_LocalEthRxDma *pEthRxDma)
{
    g_pEthRxDma[channel] = (BcmPktDma_LocalEthRxDma *)pEthRxDma;
    g_pEthRxDma[channel]->numRxBds = bufDescrs;
    g_pEthRxDma[channel]->rxAssignedBds = 0;
    g_pEthRxDma[channel]->rxHeadIndex = 0;
    g_pEthRxDma[channel]->rxTailIndex = 0;
    g_pEthRxDma[channel]->enetrxchannel_isr_enable = 1;  /* Must be worked out */

    /* Copy over pointers from passed in structure */
    g_pEthRxDma[channel]->rxBds = (volatile DmaDesc *)(pEthRxDma->rxBds);
    g_pEthRxDma[channel]->rxDma = (volatile DmaChannelCfg *)(pEthRxDma->rxDma);

    return 1;

}

int bcmPktDma_EthInitTxChan_Iudma( uint32 channel,
                                     uint32 bufDescrs,
                                     BcmPktDma_LocalEthTxDma *pEthTxDma)
{
    g_pEthTxDma[channel] = (BcmPktDma_LocalEthTxDma *)pEthTxDma;

    g_pEthTxDma[channel]->txFreeBds = bufDescrs;
    g_pEthTxDma[channel]->txHeadIndex = 0;
    g_pEthTxDma[channel]->txTailIndex = 0;
    g_pEthTxDma[channel]->txEnabled = 1;

    /* Copy over pointers from Eth Driver */
    g_pEthTxDma[channel]->txBds = pEthTxDma->txBds;
    g_pEthTxDma[channel]->txDma = (volatile DmaChannelCfg *)pEthTxDma->txDma;
    g_pEthTxDma[channel]->pKeyPtr = pEthTxDma->pKeyPtr;

    return 1;

}

/* --------------------------------------------------------------------------
    Name: bcmPktDma_EthSelectRxIrq
 Purpose: Return IRQ number to be used for bcmPkt Rx on a specific channel
-------------------------------------------------------------------------- */
int bcmPktDma_EthSelectRxIrq_Iudma(int channel)
{
    switch (channel)
    {
         case 0: return INTERRUPT_ID_ENETSW_RX_DMA_0; break;
         case 1: return INTERRUPT_ID_ENETSW_RX_DMA_1; break;
         case 2: return INTERRUPT_ID_ENETSW_RX_DMA_2; break;
         case 3: return INTERRUPT_ID_ENETSW_RX_DMA_3; break;
         default: return INTERRUPT_ID_ENETSW_RX_DMA_0; break;
    }
}

/* --------------------------------------------------------------------------
    Name: bcmPktDma_EthRecv
 Purpose: Receive a packet on a specific channel,
          returning the associated DMA flag
-------------------------------------------------------------------------- */
uint32 bcmPktDma_EthRecv_Iudma(int channel, unsigned char **pBuf, int * pLen)
{
    BcmPktDma_LocalEthRxDma * rxdma;
    DmaDesc         dmaDesc;

    FAP4KE_IUDMA_PMON_DECLARE();
    FAP4KE_IUDMA_PMON_BEGIN(FAP4KE_PMON_ID_IUDMA_RECV);

    dmaDesc.word0 = 0;
    rxdma = g_pEthRxDma[channel];
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

    FAP4KE_IUDMA_PMON_END(FAP4KE_PMON_ID_IUDMA_RECV);

    return dmaDesc.word0;

}

#if 0
/* This has been replaced with bcmPktDma_EthFreeXmitBufGet */
/* --------------------------------------------------------------------------
    Name: bcmPktDma_EthFreeXmitBuf
 Purpose: Free a single TX buffer
-------------------------------------------------------------------------- */
void bcmPktDma_EthFreeXmitBuf_Iudma(int channel, int index)
{
    BcmPktDma_LocalEthTxDma *   txdma;
    uint32                 key;

    txdma = g_pEthTxDma[channel];
    key = txdma->pKeyPtr[index];

    BCM_ENET_TX_DEBUG("Reclaim index=%d, key=%x, source=%d\n", index, key, bufSource );

#if defined(CONFIG_BCM96362)
     /* Send the nbuff to the Host MIPs to be freed. For chip 6362 */
     if(key != 0)
     {
         DQMQueueDataReg_S msg;

         msg.word0 = (uint32) channel;
         msg.word1 = (uint32) key;
         (void) dqmXmitMsg4ke(DQM_FAP2HOST_ETH_FREE_TXBUF_Q,
                              DQM_FAP2HOST_ETH_FREE_TXBUF_Q_SIZE, &msg);
         txdma->pKeyPtr[index] = 0;
     }
#endif

/* Push this one level higher
        case FAP_ETH_RX:
            bcmPktDma_EthFreeRecvBuf_Iudma( channel, nbuff_get_data(pNBuff));
            break;

#ifndef CONFIG_BCM96816
        case FAP_XTM_RX:
            bcmPktDma_XtmFreeRecvBuf_Iudma(channel, nbuff_get_data(pNBuff));
            break;
#endif
*/
}
#endif

/* --------------------------------------------------------------------------
    Name: bcmPktDma_EthXmitAvailable
 Purpose: Determine if there are free resources for the xmit
-------------------------------------------------------------------------- */
int bcmPktDma_EthXmitAvailable_Iudma(int channel)
{
    BcmPktDma_LocalEthTxDma *txdma;

    txdma = g_pEthTxDma[channel];
    if (txdma->txFreeBds != 0)  return 1;

    return 0;
}

/* --------------------------------------------------------------------------
    Name: bcmPktDma_EthTxEnable_Iudma
 Purpose: Coordinate with FAP for tx enable
  Return: 1 on success; 0 otherwise
-------------------------------------------------------------------------- */
int bcmPktDma_EthTxEnable_Iudma( int channel )
{
    BcmPktDma_LocalEthTxDma *  txdma;

    txdma = g_pEthTxDma[channel];
    txdma->txEnabled = 1;
    return 1;
}

/* --------------------------------------------------------------------------
    Name: bcmPktDma_EthTxDisable_Iudma
 Purpose: Coordinate with FAP for tx disable
  Return: 1 on success; 0 otherwise
-------------------------------------------------------------------------- */
int bcmPktDma_EthTxDisable_Iudma( int channel )
{
    BcmPktDma_LocalEthTxDma *  txdma;

    txdma = g_pEthTxDma[channel];
    txdma->txEnabled = 0;
    txdma->txDma->cfg = 0;

    return 1;
}

/* --------------------------------------------------------------------------
    Name: bcmPktDma_EthRxEnable
 Purpose: Enable rx interrupts for the given channel.
  Return: 1 on success; 0 otherwise
-------------------------------------------------------------------------- */

int bcmPktDma_EthRxEnable_Iudma( int channel )
{
    BcmPktDma_LocalEthRxDma * rxdma;

    rxdma = g_pEthRxDma[channel];

    rxdma->rxDma->cfg |= DMA_ENABLE;

    rxdma->rxEnabled = 1;

    return 1;
}

/* --------------------------------------------------------------------------
    Name: bcmPktDma_EthRxReEnable_Iudma
 Purpose: Enable rx ints on Host side only; Same as bcmPktDma_EthRxReEnable
  Return: 1 on success; 0 otherwise
-------------------------------------------------------------------------- */

int bcmPktDma_EthRxReEnable_Iudma( int channel )
{
    return( bcmPktDma_EthRxEnable_Iudma(channel) );
}

/* --------------------------------------------------------------------------
    Name: bcmPktDma_EthRxDisable
 Purpose: Disable rx interrupts for the given channel
  Return: 1 on success; 0 otherwise
-------------------------------------------------------------------------- */

int bcmPktDma_EthRxDisable_Iudma( int channel )
{
    BcmPktDma_LocalEthRxDma * rxdma;
    int                       i;

    rxdma = g_pEthRxDma[channel];
    rxdma->rxEnabled = 0;

    rxdma->rxDma->cfg &= ~DMA_ENABLE;
    for(i = 0; rxdma->rxDma->cfg & DMA_ENABLE; i++)
    {
        rxdma->rxDma->cfg &= ~DMA_ENABLE;

        if (i >= 100)
            break;
#if !(defined(CONFIG_BCM_FAP) || defined(CONFIG_BCM_FAP_MODULE))
        /* The delay only works when called from Linux */
        udelay(20);
#endif
    }

  return 1;
}


#if (defined(CONFIG_BCM96816) && defined(DBL_DESC))
DmaDesc16 * bcmPktDma_EthAllocTxBds(int numBds)
{
    void * p;
    /* Tx Descriptors are allocated in DDR */
    if ((p = kmalloc(numBds*sizeof(DmaDesc16), GFP_KERNEL))!=0) {
        memset(p, 0, numBds*sizeof(DmaDesc16));
        cache_flush_len(p, numBds*sizeof(DmaDesc16));
    }
    return( (DmaDesc16 *)(CACHE_TO_NONCACHE(p)) );   /* tx bd ring */
}
#else
DmaDesc * bcmPktDma_EthAllocTxBds(int numBds)
{
    void * p;

#if defined(TX_BDS_IN_PSM) && (defined(CONFIG_BCM_FAP) || defined(CONFIG_BCM_FAP_MODULE))
{
    unsigned int bdStartAddr;

    /* Tx Descriptors are in PSM. Use Host-side addressing here. */
    bdStartAddr = (unsigned int)pHostPsm->global.enetTxBds;
    bdStartAddr = (bdStartAddr + 7) & 0xFFFFFFF8;   /* force to 8 byte aligned */
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
#endif

DmaDesc * bcmPktDma_EthAllocRxBds(int channel, int numBds)
{
    void * p;

#if defined(RX_BDS_IN_PSM) && (defined(CONFIG_BCM_FAP) || defined(CONFIG_BCM_FAP_MODULE))
{
    unsigned int bdStartAddr;

    /* Rx Descriptors are in PSM. Use Host-side addressing here. */
    bdStartAddr = (unsigned int)pHostPsm->global.enetRxBds;
    bdStartAddr = (bdStartAddr + 7) & 0xFFFFFFF8;   /* force to 8 byte aligned */
    bdStartAddr += (channel * numBds * sizeof(DmaDesc));
    p = (void *)bdStartAddr;
    memset(p, 0, numBds*sizeof(DmaDesc));
    return((DmaDesc *)p);   /* rx bd ring */
}
#elif defined(RX_BDS_IN_QSM) && (defined(CONFIG_BCM_FAP) || defined(CONFIG_BCM_FAP_MODULE))
{
    unsigned int bdStartAddr;

    /* Rx Descriptors are in QSM. Use Host-side addressing here. */
    bdStartAddr = (unsigned int)pHostRxEnetBds;   /* already 8 byte aligned */
    bdStartAddr += (channel * numBds * sizeof(DmaDesc));
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


EXPORT_SYMBOL(g_pEnetDevCtrl);
//EXPORT_SYMBOL(g_pEnetrxchannel_isr_enable);

EXPORT_SYMBOL(bcmPktDma_EthInitRxChan_Iudma);
EXPORT_SYMBOL(bcmPktDma_EthInitTxChan_Iudma);
EXPORT_SYMBOL(bcmPktDma_EthSelectRxIrq_Iudma);
EXPORT_SYMBOL(bcmPktDma_EthRecv_Iudma);
EXPORT_SYMBOL(bcmPktDma_EthXmitAvailable_Iudma);
EXPORT_SYMBOL(bcmPktDma_EthXmit_Iudma);
EXPORT_SYMBOL(bcmPktDma_EthTxEnable_Iudma);
EXPORT_SYMBOL(bcmPktDma_EthTxDisable_Iudma);
EXPORT_SYMBOL(bcmPktDma_EthRxEnable_Iudma);
EXPORT_SYMBOL(bcmPktDma_EthRxReEnable_Iudma);
EXPORT_SYMBOL(bcmPktDma_EthRxDisable_Iudma);
EXPORT_SYMBOL(bcmPktDma_EthAllocTxBds);
EXPORT_SYMBOL(bcmPktDma_EthAllocRxBds);

#if !(defined(CONFIG_BCM_FAP) || defined(CONFIG_BCM_FAP_MODULE))
EXPORT_SYMBOL(g_pEthRxDma);
EXPORT_SYMBOL(g_pEthTxDma);
#endif

#if 0
/* This has been replaced with bcmPktDma_EthFreeXmitBufGet */
EXPORT_SYMBOL(bcmPktDma_EthFreeXmitBuf_Iudma);
#endif
