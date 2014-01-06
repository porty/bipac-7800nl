/************************************************************
 *
 * Copyright (c) 2009 Broadcom Corporation
 * All Rights Reserved
 *
<:license-private
 *
 ************************************************************/

#ifndef __FAPDQM_H_INCLUDED__ 
#define __FAPDQM_H_INCLUDED__


/******************************************************************************
* File Name  : fap_dqm.h                                                      *
*                                                                             *
* Description: This is the main header file of the DQM implementation for     * 
*              the FAP MIPS core.                                             *
******************************************************************************/

#include    "bcmtypes.h"
#include    "fap_hw.h"

/* Queue Definitions */
#define DQM_MAX_QUEUE                   32
#define DQM_MAX_HANDLER                 8

typedef struct {
    uint32 pBuf;
    uint32 dmaWord0;
    uint32 na1;
    uint32 na2;
} __attribute__((packed)) fapDqm_XtmRx_t;

#define DQM_FAP2HOST_XTM0_RX_Q         0
    #define DQM_FAP2HOST_XTM_RX_Q_SIZE     2
    #define DQM_FAP2HOST_XTM0_RX_DEPTH     128
    #define DQM_FAP2HOST_XTM1_RX_DEPTH      16
    #define DQM_IUDMA_XTM_RX_BUDGET        100
       
#define DQM_FAP2HOST_XTM1_RX_Q         1
#define DQM_FAP2HOST_XTM2_RX_Q         2
#define DQM_FAP2HOST_XTM3_RX_Q         3

typedef struct {
    uint8   *pBuf;           // 32  word0
    uint16   source  : 8;    // 8   word1
    uint8    channel;        // 8   word1
    uint16   len;            // 16  word1
    uint32   key;            // 32  word2
    uint16   dmaStatus;      // 16  word3
    uint16   param1;         // 16  word3
} __attribute__((packed)) fapDqm_XtmTx_t;

#define DQM_HOST2FAP_XTM_XMIT_Q        4
    #define DQM_HOST2FAP_XTM_XMIT_Q_SIZE       4
    #define DQM_HOST2FAP_XTM_XMIT_DEPTH        128
    #define DQM_HOST2FAP_XTM_XMIT_BUDGET       80
       
#define DQM_HOST2FAP_XTM_FREE_RXBUF_Q  5
    #define DQM_HOST2FAP_XTM_FREE_RXBUF_Q_SIZE 2
    #define DQM_HOST2FAP_XTM_FREE_RXBUF_DEPTH  128
    #define DQM_HOST2FAP_XTM_FREE_RXBUF_BUDGET 32
       
#define DQM_FAP2HOST_XTM_FREE_TXBUF_Q  6
    #define DQM_FAP2HOST_XTM_FREE_TXBUF_Q_SIZE 1
    #define DQM_FAP2HOST_XTM_FREE_TXBUF_DEPTH  128
    #define DQM_FAP2HOST_XTM_FREE_TXBUF_BUDGET 32
       
typedef struct {
    uint32 pBuf;
    uint32 dmaWord0;
    uint32 na1;
    uint32 na2;
} __attribute__((packed)) fapDqm_EthRx_t;

#define DQM_FAP2HOST_ETH0_RX_Q         7
    #define DQM_FAP2HOST_ETH_RX_Q_SIZE     2
    #define DQM_FAP2HOST_ETH0_RX_DEPTH     128
    #define DQM_FAP2HOST_ETH1_RX_DEPTH      16
    #define DQM_IUDMA_ETH_RX_BUDGET        100
       
#define DQM_FAP2HOST_ETH1_RX_Q         8
#define DQM_FAP2HOST_ETH2_RX_Q         9
#define DQM_FAP2HOST_ETH3_RX_Q         10

typedef struct {
    uint8   *pBuf;           // 32  word0
    uint16   source  : 8;    // 8   word1
    uint8    channel;        // 8   word1
    uint16   len;            // 16  word1
    uint32   key;            // 32  word2
    uint16   dmaStatus;      // 16  word3
    uint16   param1;         // 16  word3
} __attribute__((packed)) fapDqm_EthTx_t;
       
#define DQM_HOST2FAP_ETH_XMIT_Q        11
    #define DQM_HOST2FAP_ETH_XMIT_Q_SIZE       4
    #define DQM_HOST2FAP_ETH_XMIT_DEPTH        128
    #define DQM_HOST2FAP_ETH_XMIT_BUDGET       80
       
#define DQM_HOST2FAP_ETH_FREE_RXBUF_Q  12
    #define DQM_HOST2FAP_ETH_FREE_RXBUF_Q_SIZE 2
    #define DQM_HOST2FAP_ETH_FREE_RXBUF_DEPTH  128
    #define DQM_HOST2FAP_ETH_FREE_RXBUF_BUDGET 32
       
#define DQM_FAP2HOST_ETH_FREE_TXBUF_Q  13
    #define DQM_FAP2HOST_ETH_FREE_TXBUF_Q_SIZE 1
    #define DQM_FAP2HOST_ETH_FREE_TXBUF_DEPTH  128
    #define DQM_FAP2HOST_ETH_FREE_TXBUF_BUDGET 32
       
#define DQM_HOST2FAP_CMD_Q             14
    #define DQM_HOST2FAP_CMD_Q_SIZE         4
    #define DQM_HOST2FAP_CMD_Q_DEPTH        100
    #define DQM_HOST2FAP_CMD_Q_PING         100
    #define DQM_HOST2FAP_CMD_Q_ACTIVATE       200
    #define DQM_HOST2FAP_CMD_Q_ACTIVATE_OK    201
    #define DQM_HOST2FAP_CMD_Q_DEACTIVATE     202
    #define DQM_HOST2FAP_CMD_Q_DEACTIVATE_OK  203
    #define DQM_HOST2FAP_CMD_Q_PRINT_FLOW     204
    #define DQM_HOST2FAP_CMD_Q_PRINT_FLOW_OK  205
    #define DQM_FAP2HOST_CMD_Q_READY          300
    #define DQM_FAP2HOST_CMD_Q_PKT_TEST       400
    #define DQM_FAP2HOST_CMD_Q_PKT_TEST_OK    401
    #define DQM_HOST2FAP_CMD_Q_DUMP_IUDMA     500
    #define DQM_HOST2FAP_CMD_Q_IRQ_STATS      600

#define DQM_FAP2HOST_CMD_Q             15
    #define DQM_FAP2HOST_CMD_Q_SIZE         4
    #define DQM_FAP2HOST_CMD_Q_DEPTH        4
    #define DQM_FAP2HOST_CMD_Q_PONG         100

#if !defined(CONFIG_BCM_PKTDMA)
#define DQM_HOST2FAP_PACKET_Q          28
    #define DQM_HOST2FAP_PACKET_Q_SIZE     4
    #define DQM_HOST2FAP_PACKET_Q_DEPTH    500

#define DQM_FAP2HOST_PACKET_Q          29
    #define DQM_FAP2HOST_PACKET_Q_SIZE     4
    #define DQM_FAP2HOST_PACKET_Q_DEPTH    500
#endif

#define DQM_HOST2FAP_HOSTIF_Q          30
    #define DQM_HOST2FAP_HOSTIF_Q_SIZE     4
    #define DQM_HOST2FAP_HOSTIF_Q_DEPTH    16
    #define DQM_HOST2FAP_HOSTIF_Q_BUDGET   16

#define DQM_FAP2HOST_HOSTIF_Q          31
    #define DQM_FAP2HOST_HOSTIF_Q_SIZE     4
    #define DQM_FAP2HOST_HOSTIF_Q_DEPTH    16

#endif /* __FAPDQM_H_INCLUDED__ */

