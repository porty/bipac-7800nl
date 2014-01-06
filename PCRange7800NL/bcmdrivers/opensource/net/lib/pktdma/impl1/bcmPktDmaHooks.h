#ifndef __PKTDMA_HOOKS_H_INCLUDED__
#define __PKTDMA_HOOKS_H_INCLUDED__

/*
<:copyright-broadcom

 Copyright (c) 2009 Broadcom Corporation
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
 * File Name  : bcmPktDmaHooks.h
 *
 * Description: This file contains the Packet DMA Host Hook macros and definitions.
 *              It may be included in Kernel space only.
 *
 *******************************************************************************
 */

#include "fap4ke_msg.h"
#include "fap_hw.h"

/* Hook for: fapDrv_Xmit2Fap */
#define bcmPktDma_xmit2Fap(_msgType, _pMsg)                             \
    ({                                                                  \
        int __ret;                                                      \
        if(bcmPktDma_hostHooks_g.xmit2Fap != NULL)                      \
            __ret = bcmPktDma_hostHooks_g.xmit2Fap(_msgType, _pMsg);    \
        else                                                            \
            __ret = FAP_ERROR;                                          \
        __ret;                                                          \
    })

/* Hook for: dqmXmitMsgHost */
#define bcmPktDma_dqmXmitMsgHost(_queue, _tokenSize, _t)                \
    ({                                                                  \
        if(bcmPktDma_hostHooks_g.dqmXmitMsgHost != NULL)                \
          bcmPktDma_hostHooks_g.dqmXmitMsgHost(_queue, _tokenSize, _t); \
    })

/* Hook for: dqmRecvMsgHost */
#define bcmPktDma_dqmRecvMsgHost(_queue, _tokenSize, _t)                \
    ({                                                                  \
        if(bcmPktDma_hostHooks_g.dqmRecvMsgHost != NULL)                \
          bcmPktDma_hostHooks_g.dqmRecvMsgHost(_queue, _tokenSize, _t); \
    })

/* Hooks for: dqmHandlerEnableHost, dqmHandlerDisableHost */
#define __bcmPktDma_dqmHandlerEnableHost(_mask, _enable)                \
    ({                                                                  \
        int __ret;                                                      \
        if(bcmPktDma_hostHooks_g.dqmEnableHost != NULL)                 \
            __ret = bcmPktDma_hostHooks_g.dqmEnableHost(_mask, _enable); \
        else                                                            \
            __ret = FAP_ERROR;                                          \
        __ret;                                                          \
    })
#define bcmPktDma_dqmHandlerEnableHost(_mask)  __bcmPktDma_dqmHandlerEnableHost(_mask, TRUE)
#define bcmPktDma_dqmHandlerDisableHost(_mask) __bcmPktDma_dqmHandlerEnableHost(_mask, FALSE)

/* FAP Driver Hooks */
typedef struct {
    int  (* xmit2Fap)(fapMsgGroups_t msgType, xmit2FapMsg_t *pMsg);
    void (* dqmXmitMsgHost)(uint32 queue, uint32 tokenSize, DQMQueueDataReg_S *t);
    void (* dqmRecvMsgHost)(uint32 queue, uint32 tokenSize, DQMQueueDataReg_S *t);
    int  (* dqmEnableHost)(uint32 mask, bool enable);
} bcmPktDma_hostHooks_t;

extern bcmPktDma_hostHooks_t bcmPktDma_hostHooks_g;

int bcmPktDma_bind(bcmPktDma_hostHooks_t *hooks);
void bcmPktDma_unbind(void);

#endif  /* defined(__PKTDMA_HOOKS_H_INCLUDED__) */
