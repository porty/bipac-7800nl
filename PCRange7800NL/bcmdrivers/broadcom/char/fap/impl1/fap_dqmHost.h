/************************************************************
 *
 * Copyright (c) 2009 Broadcom Corporation
 * All Rights Reserved
 *
<:license-private
 *
 ************************************************************/

#ifndef __FAPDQMHOST_H_INCLUDED__ 
#define __FAPDQMHOST_H_INCLUDED__

#include <linux/interrupt.h>

/******************************************************************************
* File Name  : fap_dqmHost.h                                                  *
*                                                                             *
* Description: This is a support header file for the FAP on the host side.    *
******************************************************************************/

#define DQM_MAX_HANDLER_HOST 8

/* queue handler structure */
typedef struct {
   uint32                mask;
   bool                  enable;
   bool                  runInIsr;
   struct tasklet_struct task;
} fapHostDqm_handlerInfo_t;

/*
 * fapHost_dqm_t: DQM variables
 */ 
typedef struct{
    /* Queue Handlers */
    uint32 handlerCount;
    fapHostDqm_handlerInfo_t handlerInfo[DQM_MAX_HANDLER_HOST];
} fapHost_dqm_t;

/* register access */
#define dqmWriteFifoDataWordHost(__index, __wordNo, __data) *((unsigned int *)(((unsigned int)&hostDqmQDataReg->q[__index])+(__wordNo*4))) = __data
#define dqmReadFifoDataWordHost(__index, __wordNo) *((unsigned int *)(((unsigned int)&hostDqmQDataReg->q[__index])+(__wordNo*4)))
#define dqmReadNotEmptyIrqMskHost() FAP_HOST_REG_RD(hostDqmReg->mips_not_empty_irq_msk)
#define dqmReadNotEmptyIrqStsHost() FAP_HOST_REG_RD(hostDqmReg->not_empty_irq_sts)
#define dqmReadNotEmptyStsHost()    FAP_HOST_REG_RD(hostDqmReg->not_empty_sts)
#define dqmReadLowWtmkIrqMskHost()  FAP_HOST_REG_RD(hostDqmReg->mips_low_wtmk_irq_msk)
#define dqmReadLowWtmkIrqStsHost()  FAP_HOST_REG_RD(hostDqmReg->low_wtmk_irq_sts)
#define dqmClearNotEmptyIrqStsHost(__qb) FAP_HOST_REG_WR(hostDqmReg->not_empty_irq_sts, __qb)
#define dqmClearLowWtmkIrqStsHost(__qb)  FAP_HOST_REG_WR(hostDqmReg->low_wtmk_irq_sts, __qb)
#define dqmEnableNotEmptyIrqMskHost(__qb) FAP_HOST_REG_WR(hostDqmReg->mips_not_empty_irq_msk, dqmReadNotEmptyIrqMskHost() | __qb)
#define dqmEnableLowWtmkIrqMskHost(__qb) FAP_HOST_REG_WR(hostDqmReg->mips_low_wtmk_irq_msk, dqmReadLowWtmkIrqMskHost() | __qb)
#define dqmRecvAvailableHost(__q) dqmReadNotEmptyStsHost() & (1 << (__q))
#define dqmXmitAvailableHost(__q) FAP_HOST_REG_RD(hostDqmQCntrlReg->q[__q].sts)

typedef void(* fapTasklet_handler_t)(unsigned long arg);
extern fapTasklet_handler_t g_pXtmDqmHandler;

/* global host side DQM structure in DDR from fap_dqm.c */
extern fapHost_dqm_t hostDqm;
#define g_hostDqmHandlerInfo  (hostDqm.handlerInfo)
#define g_hostDqmHandlerCount (hostDqm.handlerCount)

/* prototypes */
int dqmHandlerRegisterHost(uint32 mask, fapTasklet_handler_t handler,
                           unsigned long arg, bool runInIsr);
void dqmIrqHandlerHost(void);

/******************************************************************************
* Function: dqmXmitMsgHost                                                    *
*                                                                             *
* Description: send a DQM token - host side                                   *
******************************************************************************/
static inline void dqmXmitMsgHost(uint32 queue, 
                    uint32 tokenSize, 
                    DQMQueueDataReg_S *t)
{
    volatile uint32 *wp = (volatile uint32 *)(&hostDqmQDataReg->q[queue].word0);
    uint32 *rp = (uint32 *)(t);
    int i;

    for(i=0; i<tokenSize; ++i)
    {
        *wp++ = *rp++;
    }
}

/******************************************************************************
* Function: dqmRecvMsgHost                                                    *
*                                                                             *
* Description: get a DQM token - host side                                    *
******************************************************************************/
static inline void dqmRecvMsgHost(uint32 queue, 
                    uint32 tokenSize, 
                    DQMQueueDataReg_S *t)
{
    uint32 *wp = (uint32 *)(t);
    volatile uint32 *rp = (volatile uint32 *)(&hostDqmQDataReg->q[queue].word0);
    int i;

    for(i=0; i<tokenSize; ++i)
    {
        *wp++ = *rp++;
    }
}

/******************************************************************************
* Function: _dqmHandlerEnableHost                                             *
*                                                                             *
* Description: enables or disables a host side DQM handler                    *
*              called by dqmHandlerEnableHost and dqmHandlerDisableHost       *
******************************************************************************/ 
static inline int _dqmHandlerEnableHost(uint32 mask, bool enable)
{
   int i, ret = 1;

   for (i = 0; i < g_hostDqmHandlerCount; i++)
   {
      if (mask == g_hostDqmHandlerInfo[i].mask)
      {
          g_hostDqmHandlerInfo[i].enable = enable;
          ret = 0;
      }
   }

   return ret;
}

#define dqmHandlerEnableHost(_mask)  _dqmHandlerEnableHost(_mask, TRUE)
#define dqmHandlerDisableHost(_mask) _dqmHandlerEnableHost(_mask, FALSE)

#endif /* __FAPDQMHOST_H_INCLUDED__ */
