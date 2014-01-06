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
 * File Name  : bcmPktDmaEthDqm.c
 *
 * Description: This file contains the Packet DMA Implementation for the
 *              Forward Assit Processor (FAP) Dynamic Queues for use by the
 *              Ethernet Controller.
 *
 *******************************************************************************
 */

#if defined(CONFIG_BCM96362)

#include <linux/string.h>
#include <bcm_intr.h>
#include "bcm_log.h"
#include "fap4ke_local.h"
#include "bcmPktDma.h"
#include "bcmPktDmaHooks.h"
#include "fap.h"
#include "fap_task.h"
#include "fap_dqm.h"
#include "fap_dqmHost.h"
#include "fap4ke_dqm.h"
#include "fap4ke_msg.h"
#include "fap4ke_irq.h"
#include "fap4ke_memory.h"

int	bcmPktDma_EthInitRxChan_Dqm( uint32 channel,
                                 uint32 bufDescrs,
                                 BcmPktDma_LocalEthRxDma *pEthRxDma)
{
    xmit2FapMsg_t fapMsg;

    fapMsg.drvInit.cmd     = FAPMSG_CMD_INIT_RX;
    fapMsg.drvInit.channel = channel;
    fapMsg.drvInit.drv     = FAPMSG_DRV_ENET;
    fapMsg.drvInit.numBds =  bufDescrs;

#if defined(RX_BDS_IN_PSM) || defined(RX_BDS_IN_QSM)
    /* The 4ke translates rxBds into a local address. Send as Host-based. */
    fapMsg.drvInit.Bds = (uint32)pEthRxDma->rxBds;
#else
    fapMsg.drvInit.Bds = (uint32)(VIRT_TO_PHY(pEthRxDma->rxBds)|0x80000000);
#endif

    /* Dma Ctrl registers require bit 29 to be set as well to read properly */
    fapMsg.drvInit.Dma = (uint32)(VIRT_TO_PHY(pEthRxDma->rxDma)|0xA0000000);

    bcmPktDma_xmit2Fap(FAP_MSG_DRV_ENET_INIT, &fapMsg);
    
    return 1;

}

int	bcmPktDma_EthInitTxChan_Dqm( uint32 channel,
                                 uint32 bufDescrs,
                                 BcmPktDma_LocalEthTxDma *pEthTxDma)
{
    xmit2FapMsg_t fapMsg;

    fapMsg.drvInit.cmd     = FAPMSG_CMD_INIT_TX;
    fapMsg.drvInit.channel = channel;
    fapMsg.drvInit.drv     = FAPMSG_DRV_ENET;
    fapMsg.drvInit.numBds =  bufDescrs;

#if defined(TX_BDS_IN_PSM)
    /* The 4ke translates txBds into a local address. Send as Host-based. */
    fapMsg.drvInit.Bds = (uint32)pEthTxDma->txBds;
#else
    fapMsg.drvInit.Bds = (uint32)(VIRT_TO_PHY(pEthTxDma->txBds)|0x80000000);
#endif

    /* Dma Ctrl registers require bit 29 to be set as well to read properly */
    fapMsg.drvInit.Dma = (uint32)(VIRT_TO_PHY(pEthTxDma->txDma)|0xA0000000);

    bcmPktDma_xmit2Fap(FAP_MSG_DRV_ENET_INIT, &fapMsg);

    return 1;

}

/* --------------------------------------------------------------------------
    Name: bcmPktDma_EthSelectRxIrq
 Purpose: Return IRQ number to be used for bcmPkt Rx on a specific channel
   Notes: Interrupt ID returned is 0. 
          Handling of INTERRUPT_ID_FAP is installed in fapDriver instead
-------------------------------------------------------------------------- */
int	bcmPktDma_EthSelectRxIrq_Dqm(int channel)
{
    return(0); 
}

/* --------------------------------------------------------------------------
    Name: bcmPktDma_EthClrRxIrq
 Purpose: Clear the Rx interrupt for a specific channel
-------------------------------------------------------------------------- */
void	bcmPktDma_EthClrRxIrq_Dqm(int channel)
{
    // BCM_LOG_INFO(BCM_LOG_ID_FAP, "channel: %d\n", channel);

    uint32 qbit = 1 << (DQM_FAP2HOST_ETH0_RX_Q + channel);
    
    dqmClearNotEmptyIrqStsHost(qbit);
    dqmEnableNotEmptyIrqMskHost(qbit);
}

/* --------------------------------------------------------------------------
    Name: bcmPktDma_EthRecvAvailable
 Purpose: Return 1 if a packet is available, 0 otherwise
-------------------------------------------------------------------------- */
int bcmPktDma_EthRecvAvailable_Dqm(int channel) 
{
    // BCM_LOG_INFO(BCM_LOG_ID_FAP, "channel: %d", channel);

    return (dqmRecvAvailableHost(DQM_FAP2HOST_ETH0_RX_Q + channel));
}
 
/* --------------------------------------------------------------------------
    Name: bcmPktDma_EthRecv
 Purpose: Receive a packet on a specific channel, returning the associated DMA desc
   Notes: In DQM msg, word0 = pBuf; word1 = length; word2 = dmaFlag
-------------------------------------------------------------------------- */
uint32 bcmPktDma_EthRecv_Dqm(int             channel, 
                             unsigned char **pBuf, 
                             int            *pLen)
{
    uint32            dqm = DQM_FAP2HOST_ETH0_RX_Q + channel;
    fapDqm_EthRx_t    rx;
    DmaDesc           dmaDesc;

    // BCM_LOG_INFO(BCM_LOG_ID_FAP, "channel: %d", channel);

    dmaDesc.word0 = 0;
    
    if (dqmRecvAvailableHost(dqm))
    {
        dqmRecvMsgHost(dqm, DQM_FAP2HOST_ETH_RX_Q_SIZE, 
                                      (DQMQueueDataReg_S *) &rx);

        *pBuf         = (unsigned char *) rx.pBuf;
        dmaDesc.word0 = rx.dmaWord0;
        *pLen         = dmaDesc.length;

        //printk("pbuf: 0x%08lX len: %d dmaDesc.word0: 0x%08lX\n",
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
    Name: bcmPktDma_EthFreeRecvBuf
 Purpose: Send a single RX buffer to the FAP to be freed
   Notes: In DQM msg, word0 = channel; word1 = pBuf
-------------------------------------------------------------------------- */
void bcmPktDma_EthFreeRecvBuf_Dqm(int channel, unsigned char * pBuf)
{
    DQMQueueDataReg_S msg;

    // BCM_LOG_INFO(BCM_LOG_ID_FAP, "channel: %d", channel);
    
    /* Wait until there is space in the ETH_FREE_RXBUF_Q,
       then send the free request to the FAP */

    while(!dqmXmitAvailableHost(DQM_HOST2FAP_ETH_FREE_RXBUF_Q));

    msg.word0 = (uint32) channel;
    msg.word1 = (uint32) pBuf;

    dqmXmitMsgHost(DQM_HOST2FAP_ETH_FREE_RXBUF_Q, 
                   DQM_HOST2FAP_ETH_FREE_RXBUF_Q_SIZE, &msg);
}

/* --------------------------------------------------------------------------
    Name: bcmPktDma_EthFreeXmitBufs
 Purpose: Free all possible TX buffers once transmission is done
   Notes: Params pTxSource and pTxAddr not used in DQM implementation
-------------------------------------------------------------------------- */
BOOL bcmPktDma_EthFreeXmitBufGet_Dqm(int channel, uint32 *pKey, int *pTxSource, uint32 *pTxAddr)
{
    BOOL ret = FALSE;
    DQMQueueDataReg_S msg;

    // BCM_LOG_INFO(BCM_LOG_ID_FAP, "channel: %d", channel);

    /* Reclaim transmitted buffers for any queue */
    if (dqmRecvAvailableHost(DQM_FAP2HOST_ETH_FREE_TXBUF_Q))
    {
        /* Channel and index for bcmPktDma_EthFreeXmitBuf don't matter */
        /* Just take skb ptrs off the DQM queue til done */
        dqmRecvMsgHost(DQM_FAP2HOST_ETH_FREE_TXBUF_Q, 
                          DQM_FAP2HOST_ETH_FREE_TXBUF_Q_SIZE, &msg);
         
         *pKey     = (uint32) msg.word0;
         ret = TRUE;
    }
    
    return ret;
}

/* --------------------------------------------------------------------------
    Name: bcmPktDma_EthXmitAvailable
 Purpose: Determine if there are free resources for the xmit
   Notes: Intended to be called on Host MIPs only
-------------------------------------------------------------------------- */
int bcmPktDma_EthXmitAvailable_Dqm(int channel) 
{
    // BCM_LOG_INFO(BCM_LOG_ID_FAP, "chanel %d", channel);

    return (dqmXmitAvailableHost(DQM_HOST2FAP_ETH_XMIT_Q));   
}

/* --------------------------------------------------------------------------
    Name: bcmPktDma_EthXmit
 Purpose: Xmit an skb
   Notes: param1 = gemid; param2 = port_id; param3 = egress_queue
          In DQM msg, word0 = pBuf; word1 = channel & len;  
                      word2 = gemid & port_id; word3 = egress_queue
  Return: 1 on success; 0 otherwise
-------------------------------------------------------------------------- */
int bcmPktDma_EthXmit_Dqm(int channel, uint8 *pBuf, uint16 len, int bufSource, uint16 dmaStatus, uint32 key, int param1)
{
    DQMQueueDataReg_S *msg;
    fapDqm_EthTx_t tx;

    // BCM_LOG_INFO(BCM_LOG_ID_FAP, "channel %d", channel);

    /* If there is space in the ETH_XMIT_Q, send the xmit request to the FAP */
    if (dqmXmitAvailableHost(DQM_HOST2FAP_ETH_XMIT_Q))
    {
        tx.pBuf = pBuf;
        tx.source = bufSource;
        tx.channel = channel;
        tx.len = len;
        tx.key = key;
        tx.dmaStatus = dmaStatus;
        tx.param1 = param1;

        msg = (DQMQueueDataReg_S *) &tx;   
 
        bcmPktDma_dqmXmitMsgHost(DQM_HOST2FAP_ETH_XMIT_Q, 
                                     DQM_HOST2FAP_ETH_XMIT_Q_SIZE, msg);

        return 1;
    }

/*     else  */
/*         BCM_LOG_ERROR(BCM_LOG_ID_FAP,  */
/*                   "bcmPktDma_EthXmit_Dqm to ETH_XMIT_Q FAILED! (drop)\n"); */
    
    return 0;
}

/* --------------------------------------------------------------------------
    Name: bcmPktDma_EthXmit
 Purpose: Xmit an skb without space check. Must be used in conjunction with
          bcmPktDma_EthXmitAvailable_Dqm().
   Notes: param1 = gemid; param2 = port_id; param3 = egress_queue
          In DQM msg, word0 = pBuf; word1 = channel & len;  
                      word2 = gemid & port_id; word3 = egress_queue
  Return: 1 on success; 0 otherwise
-------------------------------------------------------------------------- */
void bcmPktDma_EthXmitNoCheck_Dqm(int channel, uint8 *pBuf, uint16 len, int bufSource,
                                  uint16 dmaStatus, uint32 key, int param1)
{
    fapDqm_EthTx_t tx;

    tx.pBuf = pBuf;
    tx.source = bufSource;
    tx.channel = channel;
    tx.len = len;
    tx.key = key;
    tx.dmaStatus = dmaStatus;
    tx.param1 = param1;

    bcmPktDma_dqmXmitMsgHost(DQM_HOST2FAP_ETH_XMIT_Q, 
                             DQM_HOST2FAP_ETH_XMIT_Q_SIZE, (DQMQueueDataReg_S *)(&tx));
}

/* --------------------------------------------------------------------------
    Name: bcmPktDma_EthTxEnable_Dqm
 Purpose: Coordinate with FAP to enable tx channel 
  Return: 1 on success; 0 otherwise
-------------------------------------------------------------------------- */
int bcmPktDma_EthTxEnable_Dqm( int channel )
{
    xmit2FapMsg_t fapMsg;

    fapMsg.drvCtl.cmd     = FAPMSG_CMD_TX_ENABLE;
    fapMsg.drvCtl.drv     = FAPMSG_DRV_ENET;
    fapMsg.drvCtl.channel = channel;

    return( bcmPktDma_xmit2Fap(FAP_MSG_DRV_CTL, &fapMsg) );
}

/* --------------------------------------------------------------------------
    Name: bcmPktDma_EthTxDisable_Dqm
 Purpose: Coordinate with FAP to disable tx channel
  Return: 1 on success; 0 otherwise
-------------------------------------------------------------------------- */
int bcmPktDma_EthTxDisable_Dqm( int channel )
{
    xmit2FapMsg_t fapMsg;

    fapMsg.drvCtl.cmd     = FAPMSG_CMD_TX_DISABLE;
    fapMsg.drvCtl.drv     = FAPMSG_DRV_ENET;
    fapMsg.drvCtl.channel = channel;

    return( bcmPktDma_xmit2Fap(FAP_MSG_DRV_CTL, &fapMsg) );
}

/* --------------------------------------------------------------------------
    Name: bcmPktDma_EthRxEnable_Dqm
 Purpose: Coordinate with FAP to enable rx 
  Return: 1 on success; 0 otherwise
-------------------------------------------------------------------------- */

int bcmPktDma_EthRxEnable_Dqm( int channel )
{
    xmit2FapMsg_t fapMsg;
    int retVal;

    /* Enable rx pkt processing */
    bcmPktDma_dqmHandlerEnableHost(1 << (DQM_FAP2HOST_ETH0_RX_Q + channel));

    fapMsg.drvCtl.cmd     = FAPMSG_CMD_RX_ENABLE;
    fapMsg.drvCtl.drv     = FAPMSG_DRV_ENET;
    fapMsg.drvCtl.channel = channel;

    retVal = bcmPktDma_xmit2Fap(FAP_MSG_DRV_CTL, &fapMsg);

    /* Execute the DMA enable code on Host side */
    //bcmPktDma_EthRxEnable_Iudma(channel);

    return( retVal );
}

/* --------------------------------------------------------------------------
    Name: bcmPktDma_EthRxReEnable_Dqm
 Purpose: Enable rx ints on Host side only
  Return: 1 on success; 0 otherwise
-------------------------------------------------------------------------- */

int bcmPktDma_EthRxReEnable_Dqm( int channel )
{
    /* Enable rx pkt processing */
    bcmPktDma_dqmHandlerEnableHost(1 << (DQM_FAP2HOST_ETH0_RX_Q + channel));

    return( 1 );
}

/* --------------------------------------------------------------------------
    Name: bcmPktDma_EthRxDisable_Dqm
 Purpose: Coordinate with FAP to disable rx
  Return: 1 on success; 0 otherwise
-------------------------------------------------------------------------- */

int bcmPktDma_EthRxDisable_Dqm( int channel )
{
    xmit2FapMsg_t fapMsg;
    int           retVal;

    /* Disable rx pkt processing */
    //dqmHandlerDisableHost(1 << (DQM_FAP2HOST_ETH0_RX_Q + channel));

    fapMsg.drvCtl.cmd     = FAPMSG_CMD_RX_DISABLE;
    fapMsg.drvCtl.drv     = FAPMSG_DRV_ENET;
    fapMsg.drvCtl.channel = channel;

    retVal = bcmPktDma_xmit2Fap(FAP_MSG_DRV_CTL, &fapMsg);

    /* Execute the DMA enable code on Host side */
    //bcmPktDma_EthRxDisable_Iudma(channel);

    return( retVal );
}

/* This should be moved to bcmenet.c */
void bcm63xx_enet_dqmhandler(unsigned long channel)
{
    // BCM_LOG_INFO(BCM_LOG_ID_FAP, "channel %ld", channel);

#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,30)
    napi_schedule(&g_pEnetDevCtrl->napi);
#else
    netif_rx_schedule(g_pEnetDevCtrl->dev);
#endif
}

#if 0 /* The XMIT Free DQM is polled */
void bcm63xx_enet_xmit_free_handler(unsigned long channel)
{
    uint32   qbit = 1 << DQM_FAP2HOST_ETH_FREE_TXBUF_Q;
    pNBuff_t ptempNBuff;
    uint32   budget = DQM_FAP2HOST_ETH_FREE_TXBUF_BUDGET;
    int      txSource;
    uint32   txAddr;
    uint32   txCount = 0;

    // BCM_LOG_INFO(BCM_LOG_ID_FAP, "channel %ld", channel);

    /* Reclaim transmitted buffers */
    while ( (budget > 0) &&
            (bcmPktDma_EthFreeXmitBufGet(channel,(uint32 *)&ptempNBuff, &txSource, &txAddr) == TRUE))
    {
       budget--;

       pHostPsmGbl->stats.Q13txTotal++;
       txCount++;

       nbuff_free(ptempNBuff);
    }
    
    pHostPsmGbl->stats.Q13txCount = txCount;
    if(txCount > pHostPsmGbl->stats.Q13txHighWm)
    {
        pHostPsmGbl->stats.Q13txHighWm = txCount;
    }

    dqmClearNotEmptyIrqStsHost(qbit);
    dqmEnableNotEmptyIrqMskHost(qbit);
}
#endif

EXPORT_SYMBOL(bcm63xx_enet_dqmhandler);

EXPORT_SYMBOL(bcmPktDma_EthRxReEnable_Dqm);
EXPORT_SYMBOL(bcmPktDma_EthInitRxChan_Dqm);
EXPORT_SYMBOL(bcmPktDma_EthInitTxChan_Dqm);
EXPORT_SYMBOL(bcmPktDma_EthSelectRxIrq_Dqm);
EXPORT_SYMBOL(bcmPktDma_EthClrRxIrq_Dqm);
EXPORT_SYMBOL(bcmPktDma_EthRecvAvailable_Dqm);
EXPORT_SYMBOL(bcmPktDma_EthRecv_Dqm);
EXPORT_SYMBOL(bcmPktDma_EthFreeRecvBuf_Dqm);
EXPORT_SYMBOL(bcmPktDma_EthXmitAvailable_Dqm);
EXPORT_SYMBOL(bcmPktDma_EthXmit_Dqm);
EXPORT_SYMBOL(bcmPktDma_EthXmitNoCheck_Dqm);
EXPORT_SYMBOL(bcmPktDma_EthTxEnable_Dqm);
EXPORT_SYMBOL(bcmPktDma_EthTxDisable_Dqm);
EXPORT_SYMBOL(bcmPktDma_EthRxEnable_Dqm);
EXPORT_SYMBOL(bcmPktDma_EthRxDisable_Dqm); 
EXPORT_SYMBOL(bcmPktDma_EthFreeXmitBufGet_Dqm);    

#endif /* CONFIG_BCM96362 */
