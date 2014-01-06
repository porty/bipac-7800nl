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
 * File Name  : bcmPktDmaXtmDqm.c
 *
 * Description: This file contains the Packet DMA Implementation for the
 *              Forward Assist Processor (FAP) Dynamic Queues for use by the
 *              XTM Controller.
 *
 *******************************************************************************
 */

#ifndef CONFIG_BCM96816

#include <bcm_intr.h>
#if (defined(CONFIG_BCM_FAP) || defined(CONFIG_BCM_FAP_MODULE))
#include "bcm_log.h"
#include "fap4ke_local.h"
#endif
#include "bcmPktDma.h"
#include "bcmPktDmaHooks.h"

#if (defined(CONFIG_BCM_FAP) || defined(CONFIG_BCM_FAP_MODULE))
#include "fap_task.h"
#include "fap_dqm.h"
#include "fap4ke_dqm.h"
#include "fap_dqmHost.h"
#include "fap4ke_msg.h"
#include "fap4ke_irq.h"

/* Globals initialized in the XTM Driver */
fapTasklet_handler_t g_pXtmDqmHandler;
#endif

/* --------------------------------------------------------------------------
    Name: bcmPktDma_XtmSelectRxIrq
 Purpose: Return IRQ number to be used for bcmPkt Rx on a specific channel
   Notes: Interrupt ID returned is 0. 
          Handling of INTERRUPT_ID_FAP is installed in fapDriver instead
-------------------------------------------------------------------------- */
int	bcmPktDma_XtmSelectRxIrq_Dqm(int channel)
{
    return 0;
}

/* --------------------------------------------------------------------------
    Name: bcmPktDma_XtmClrRxIrq
 Purpose: Clear the Rx interrupt for a specific channel
-------------------------------------------------------------------------- */
void    bcmPktDma_XtmClrRxIrq_Dqm(int channel)
{
    uint32 qbit = 1 << (DQM_FAP2HOST_XTM0_RX_Q + channel);
 
    //printk("\nbcmPktDma_XtmClrRxIrq_Dqm\n");
   
    dqmClearNotEmptyIrqStsHost(qbit);
    dqmEnableNotEmptyIrqMskHost(qbit);
}

/* --------------------------------------------------------------------------
    Name: bcmPktDma_XtmRecvAvailable
 Purpose: Return 1 if a packet is available, 0 otherwise
-------------------------------------------------------------------------- */
int bcmPktDma_XtmRecvAvailable_Dqm(int channel) 
{
    return (dqmRecvAvailableHost(DQM_FAP2HOST_XTM0_RX_Q + channel)); 
}

/* --------------------------------------------------------------------------
    Name: bcmPktDma_XtmRecv
 Purpose: Receive a packet on a channel
   Notes: In DQM msg, word0 = pBuf; word1 = dmaDesc.word0
-------------------------------------------------------------------------- */
uint32 bcmPktDma_XtmRecv_Dqm(int channel, unsigned char **pBuf, int * pLen)
{
    uint32            dqm = DQM_FAP2HOST_XTM0_RX_Q + channel;
    fapDqm_XtmRx_t    rx;
    DmaDesc           dmaDesc;

    // BCM_LOG_INFO(BCM_LOG_ID_FAP, "channel: %d", channel);

    dmaDesc.word0 = 0;
    
    if (dqmRecvAvailableHost(dqm))
    {
        dqmRecvMsgHost(dqm, DQM_FAP2HOST_XTM_RX_Q_SIZE, 
                                      (DQMQueueDataReg_S *) &rx);

        *pBuf         = (unsigned char *) rx.pBuf;
        dmaDesc.word0 = rx.dmaWord0;
        *pLen         = dmaDesc.length;

        //printk("XtmRecv_Dqm pbuf: 0x%08lX len: %d dmaDesc.word0: 0x%08lX\n",
        //          (long unsigned int)*pBuf, *pLen, dmaDesc.word0);   
    }
    else
    {
        *pBuf   = (unsigned char *) NULL;
        *pLen   = 0;
        dmaDesc.status = DMA_OWN;
    }
    
    return dmaDesc.word0;
}

/* --------------------------------------------------------------------------
    Name: bcmPktDma_XtmFreeRecvBuf
 Purpose: Free a single RX buffer
   Notes: In DQM msg, word0 = channel; word1 = pBuf
-------------------------------------------------------------------------- */
void bcmPktDma_XtmFreeRecvBuf_Dqm(int channel, unsigned char * pBuf)
{   
    DQMQueueDataReg_S msg;

    while(!dqmXmitAvailableHost(DQM_HOST2FAP_XTM_FREE_RXBUF_Q));

    msg.word0 = (uint32) channel;
    msg.word1 = (uint32) pBuf;
    (void) bcmPktDma_dqmXmitMsgHost(DQM_HOST2FAP_XTM_FREE_RXBUF_Q, 
                                    DQM_HOST2FAP_XTM_FREE_RXBUF_Q_SIZE, &msg);
}

/* --------------------------------------------------------------------------
    Name: bcmPktDma_XtmFreeXmitBufGet_Dqm
 Purpose: Free all possible TX buffers once transmission is done
   Notes: Params pTxSource and pTxAddr not used in DQM implementation
-------------------------------------------------------------------------- */
BOOL bcmPktDma_XtmFreeXmitBufGet_Dqm(int channel, uint32 *pKey, int *pTxSource, uint32 *pTxAddr)
{
    BOOL ret = FALSE;
    DQMQueueDataReg_S msg;

    //BCM_LOG_DEBUG(BCM_LOG_ID_FAP, "channel: %d", channel);

    /* Reclaim transmitted buffers for any queue */
    if (dqmRecvAvailableHost(DQM_FAP2HOST_XTM_FREE_TXBUF_Q))
    {
        /* Channel and index for bcmPktDma_EthFreeXmitBuf don't matter */
        /* Just take skb ptrs off the DQM queue til done */
        dqmRecvMsgHost(DQM_FAP2HOST_XTM_FREE_TXBUF_Q, 
                          DQM_FAP2HOST_XTM_FREE_TXBUF_Q_SIZE, &msg);
         
         *pKey     = (uint32) msg.word0;
         ret = TRUE;
    }
    
    return ret;
}

/* --------------------------------------------------------------------------
    Name: bcmPktDma_XtmXmitAvailable
 Purpose: Determine if there are free resources for the xmit
-------------------------------------------------------------------------- */
int bcmPktDma_XtmXmitAvailable_Dqm(int channel) 
{
    return (dqmXmitAvailableHost(DQM_HOST2FAP_XTM_XMIT_Q));
}

/* --------------------------------------------------------------------------
    Name: bcmPktDma_XtmXmit
 Purpose: Xmit an skb
          param1, param2, param3 N/A
          In DQM msg, word0 = skb; word1 = channel & len 
  Return: 1 on success; 0 otherwise
-------------------------------------------------------------------------- */
int bcmPktDma_XtmXmit_Dqm(int channel, uint8 *pBuf, uint16 len, int bufSource,
                          uint16 dmaStatus, uint32 key,int param1)
{
    fapDqm_XtmTx_t tx;

    //printk("bcmPktDma_XtmXmit_Dqm ch: %d pBuf: %lx len: %d key: %lx dma: %x\n",
    //                channel, (uint32)pBuf, len, key, dmaStatus);

    // BCM_LOG_INFO(BCM_LOG_ID_FAP, "channel %d", channel);

    /* If there is space in the ETH_XMIT_Q, send the xmit request to the FAP */
    if (dqmXmitAvailableHost(DQM_HOST2FAP_XTM_XMIT_Q))
    {
        tx.pBuf = pBuf;
        tx.source = bufSource;
        tx.channel = channel;
        tx.len = len;
        tx.key = key;
        tx.dmaStatus = dmaStatus;
        tx.param1 = param1;
 
        bcmPktDma_dqmXmitMsgHost(DQM_HOST2FAP_XTM_XMIT_Q, 
                                 DQM_HOST2FAP_XTM_XMIT_Q_SIZE, 
                                (DQMQueueDataReg_S *) &tx);

        return 1;
    }

/*     else  */
/*         BCM_LOG_ERROR(BCM_LOG_ID_FAP,  */
/*                   "bcmPktDma_EthXmit_Dqm to ETH_XMIT_Q FAILED! (drop)\n"); */
    
    return 0;
}

/* --------------------------------------------------------------------------
    Name: bcmPktDma_XtmTxEnable_Dqm
 Purpose: Coordinate with FAP to enable tx channel 
  Return: 1 on success; 0 otherwise
-------------------------------------------------------------------------- */
int bcmPktDma_XtmTxEnable_Dqm( int channel )
{
    xmit2FapMsg_t fapMsg;

    //printk("bcmPktDma_XtmTxEnable_Dqm ch: %d\n", channel);

    fapMsg.drvCtl.cmd     = FAPMSG_CMD_TX_ENABLE;
    fapMsg.drvCtl.drv     = FAPMSG_DRV_XTM;
    fapMsg.drvCtl.channel = channel;

    return( bcmPktDma_xmit2Fap(FAP_MSG_DRV_CTL, &fapMsg) );
}

/* --------------------------------------------------------------------------
    Name: bcmPktDma_XtmTxDisable_Dqm
 Purpose: Coordinate with FAP to disable tx channel
  Return: 1 on success; 0 otherwise
-------------------------------------------------------------------------- */
int bcmPktDma_XtmTxDisable_Dqm( int channel )
{
    xmit2FapMsg_t fapMsg;

    //printk("bcmPktDma_XtmTxDisable_Dqm ch: %d\n", channel);

    fapMsg.drvCtl.cmd     = FAPMSG_CMD_TX_DISABLE;
    fapMsg.drvCtl.drv     = FAPMSG_DRV_XTM;
    fapMsg.drvCtl.channel = channel;

    return( bcmPktDma_xmit2Fap(FAP_MSG_DRV_CTL, &fapMsg) );
}

/* --------------------------------------------------------------------------
    Name: bcmPktDma_XtmRxEnable_Dqm
 Purpose: Coordinate with FAP to enable rx 
  Return: 1 on success; 0 otherwise
-------------------------------------------------------------------------- */

int bcmPktDma_XtmRxEnable_Dqm( int channel )
{
    xmit2FapMsg_t fapMsg;
    int retVal;

    //printk("bcmPktDma_XtmRxEnable_Dqm ch: %d\n", channel);

    fapMsg.drvCtl.cmd     = FAPMSG_CMD_RX_ENABLE;
    fapMsg.drvCtl.drv     = FAPMSG_DRV_XTM;
    fapMsg.drvCtl.channel = channel;

    retVal = bcmPktDma_xmit2Fap(FAP_MSG_DRV_CTL, &fapMsg);

    return retVal;
}

/* --------------------------------------------------------------------------
    Name: bcmPktDma_XtmRxDisable_Dqm
 Purpose: Coordinate with FAP to disable rx
  Return: 1 on success; 0 otherwise
-------------------------------------------------------------------------- */

int bcmPktDma_XtmRxDisable_Dqm( int channel )
{
    xmit2FapMsg_t fapMsg;
    int           retVal;

    //printk("bcmPktDma_XtmRxDisable_Dqm ch: %d\n", channel);

    /* Disable rx pkt processing */
    fapMsg.drvCtl.cmd     = FAPMSG_CMD_RX_DISABLE;
    fapMsg.drvCtl.drv     = FAPMSG_DRV_XTM;
    fapMsg.drvCtl.channel = channel;

    retVal = bcmPktDma_xmit2Fap(FAP_MSG_DRV_CTL, &fapMsg);

    return( retVal );
}

int	bcmPktDma_XtmInitRxChan_Dqm( uint32 channel,
                                 uint32 bufDescrs,
                                 BcmPktDma_LocalXtmRxDma *pXtmRxDma)
{
    xmit2FapMsg_t fapMsg;

    fapMsg.drvInit.cmd     = FAPMSG_CMD_INIT_RX;
    fapMsg.drvInit.channel = channel;
    fapMsg.drvInit.drv     = FAPMSG_DRV_XTM;
    fapMsg.drvInit.numBds =  bufDescrs;

#if defined(RX_BDS_IN_PSM) || defined(RX_BDS_IN_QSM)
    /* The 4ke translates rxBds into a local address. Send as Host-based. */
    fapMsg.drvInit.Bds = (uint32)pXtmRxDma->rxBds;
#else
    fapMsg.drvInit.Bds = (uint32)(VIRT_TO_PHY(pXtmRxDma->rxBds)|0x80000000);
#endif

    /* Dma Ctrl registers require bit 29 to be set as well to read properly */
    fapMsg.drvInit.Dma = (uint32)(VIRT_TO_PHY(pXtmRxDma->rxDma)|0xA0000000);

    bcmPktDma_xmit2Fap(FAP_MSG_DRV_XTM_INIT, &fapMsg);
    
    return 1;

}

int	bcmPktDma_XtmInitTxChan_Dqm( uint32 channel,
                                 uint32 bufDescrs,
                                 BcmPktDma_LocalXtmTxDma *pXtmTxDma)
{
    xmit2FapMsg_t fapMsg;

    fapMsg.drvInit.cmd     = FAPMSG_CMD_INIT_TX;
    fapMsg.drvInit.channel = channel;
    fapMsg.drvInit.drv     = FAPMSG_DRV_XTM;
    fapMsg.drvInit.numBds =  bufDescrs;

#if defined(TX_BDS_IN_PSM)
    /* The 4ke translates txBds into a local address. Send as Host-based. */
    fapMsg.drvInit.Bds = (uint32)pXtmTxDma->txBds;
#else
    fapMsg.drvInit.Bds = (uint32)(VIRT_TO_PHY(pXtmTxDma->txBds)|0x80000000);
#endif

    /* Dma Ctrl registers require bit 29 to be set as well to read properly */
    fapMsg.drvInit.Dma = (uint32)(VIRT_TO_PHY(pXtmTxDma->txDma)|0xA0000000);

    bcmPktDma_xmit2Fap(FAP_MSG_DRV_XTM_INIT, &fapMsg);

    return 1;

}

int bcmPktDma_XtmCreateDevice_Dqm(uint32 devId, uint32 encapType)
{
    xmit2FapMsg_t fapMsg;

    fapMsg.xtmCreateDevice.devId = devId;
    fapMsg.xtmCreateDevice.encapType = encapType;

    bcmPktDma_xmit2Fap(FAP_MSG_DRV_XTM_CREATE_DEVICE, &fapMsg);

    return 1;
}

int bcmPktDma_XtmLinkUp_Dqm(uint32 devId, uint32 matchId)
{
    xmit2FapMsg_t fapMsg;

    fapMsg.xtmLinkUp.devId = devId;
    fapMsg.xtmLinkUp.matchId = matchId;

    bcmPktDma_xmit2Fap(FAP_MSG_DRV_XTM_LINK_UP, &fapMsg);

    return 1;
}

void bcm63xx_xtm_dqmhandler(unsigned long channel)
{
    int i;
    PBCMXTMRT_DEV_CONTEXT pDevCtx;

    // BCM_LOG_INFO(BCM_LOG_ID_FAP, "channel %ld", channel);

    for (i = 0; i < MAX_DEV_CTXS; i++)
    {
        if ((pDevCtx = g_pXtmGlobalInfo->pDevCtxs[i]) != NULL &&
             pDevCtx->ulOpenState == XTMRT_DEV_OPENED)
        {
#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,30)
            napi_schedule(&pDevCtx->napi);
#else
            netif_rx_schedule(pDevCtx->pDev);
#endif

            g_pXtmGlobalInfo->ulIntEnableMask |= 1 << channel;
        }
    }
}


EXPORT_SYMBOL(bcm63xx_xtm_dqmhandler);

EXPORT_SYMBOL(bcmPktDma_XtmSelectRxIrq_Dqm);
EXPORT_SYMBOL(bcmPktDma_XtmClrRxIrq_Dqm);
EXPORT_SYMBOL(bcmPktDma_XtmRecvAvailable_Dqm);
EXPORT_SYMBOL(bcmPktDma_XtmRecv_Dqm);
EXPORT_SYMBOL(bcmPktDma_XtmFreeRecvBuf_Dqm);
EXPORT_SYMBOL(bcmPktDma_XtmXmitAvailable_Dqm);
EXPORT_SYMBOL(bcmPktDma_XtmXmit_Dqm);
EXPORT_SYMBOL(bcmPktDma_XtmCreateDevice_Dqm);
EXPORT_SYMBOL(bcmPktDma_XtmLinkUp_Dqm);

#endif   /* #ifndef CONFIG_BCM96816 */

