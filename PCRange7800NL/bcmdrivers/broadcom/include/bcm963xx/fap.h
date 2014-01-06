#ifndef __FAP_H_INCLUDED__
#define __FAP_H_INCLUDED__

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
 * File Name  : fap.h
 *
 * Description: This file contains the specification of some common definitions
 *      and interfaces to other modules. This file may be included by both
 *      Kernel and userapp (C only).
 *
 *******************************************************************************
 */


/*----- Defines -----*/

#define FAP_VERSION              "0.1"
#define FAP_VER_STR              "v" FAP_VERSION " " __DATE__ " " __TIME__
#define FAP_MODNAME              "Broadcom Forwarding Assist Processor (FAP)"

#define FAP_NAME                 "bcmfap"

#ifndef FAP_ERROR
#define FAP_ERROR                (-1)
#endif
#ifndef FAP_SUCCESS
#define FAP_SUCCESS              0
#endif

/* FAP Character Device */
#define FAPDRV_MAJOR             241
#define FAPDRV_NAME              FAP_NAME
#define FAPDRV_DEVICE_NAME       "/dev/" FAPDRV_NAME

/* FAP Control Utility Executable */
#define FAP_CTL_UTILITY_PATH     "/bin/fapctl"

/* FAP Proc FS Directory Path */
#define FAP_PROC_FS_DIR_PATH     FAP_NAME

/* Menuconfig: BRCM_DRIVER_PKTFLOW_DEBUG selection will cause -DPKTDBG C Flags*/
#ifdef PKTDBG
#define CC_FAP_DEBUG
#define CC_FAP_ASSERT
#endif

#if defined( __KERNEL__ )
#include <asm/system.h>             /* interrupt locking for MIPS */
#define KERNEL_LOCK(level)          local_irq_save(level)
#define KERNEL_UNLOCK(level)        local_irq_restore(level)
#endif

/*
 *------------------------------------------------------------------------------
 * Common defines for FAP layers.
 *------------------------------------------------------------------------------
 */
#define FAP_DECL(x)                 #x, /* for string declaration in C file */
#undef FAP_DECL
#define FAP_DECL(x)                 x,  /* for enum declaration in H file */

/*
 *------------------------------------------------------------------------------
 *              Packet CFM character device driver IOCTL enums
 * A character device and the associated userspace utility for design debug.
 * Include fapParser.h for ACTIVATE/DEACTIVATE IOCTLs
 *------------------------------------------------------------------------------
 */
typedef enum {
    FAP_DECL(FAP_IOC_HW)
    FAP_DECL(FAP_IOC_STATUS)
    FAP_DECL(FAP_IOC_RESET)
    FAP_DECL(FAP_IOC_INIT)
    FAP_DECL(FAP_IOC_ENABLE)
    FAP_DECL(FAP_IOC_DISABLE)
    FAP_DECL(FAP_IOC_DEBUG)
    FAP_DECL(FAP_IOC_PRINT)
    FAP_DECL(FAP_IOC_CPU)
    FAP_DECL(FAP_IOC_DMA_DEBUG)
    FAP_DECL(FAP_IOC_MAX)
} fapIoctl_t;

/*
 *------------------------------------------------------------------------------
 * Flow cache uses a 16bit CMF Tuple for identifying a Flow accelerated in
 * hardware. As there is only a single FAP engine shared by all ports, the
 * entire 16bit value of the tuple is used to represent the matched Flow.
 *
 * Macros shared by FlowCache for NATed configurations of FAP.
 *------------------------------------------------------------------------------
 */
typedef enum {
    FAP_DECL(PKTCMF_ENGINE_SWC)
    FAP_DECL(PKTCMF_ENGINE_ALL) /* max number of CMF enum */
} PktCmfEngine_t;

/* Construct a 16bit CMF tuple from the Engine and matched FlowInfo Element. */
#define CMF_TUPLE16(eng,matchIx)    ((__force uint16_t)(matchIx))

/* Extract the Engine (CMF memory space) from the CMF <Engine,MatchIx> tuple. */
#define GET_CMF_ENGINE(cmfTuple16)  ((__force uint8_t)PKTCMF_ENGINE_SWC)

/* Extract the matched FlowINFO RAM index from the CMF tuple. */
#define GET_CMF_MATCHIX(cmfTuple16) ((__force uint16_t)(cmfTuple16))

/* Special tuple to signify an invalid tuple. */
#define CMF_TUPLE16_INVALID         ((__force uint16_t)(0xFFFF))

#define PKTCMF_MAX_FLOWS            512

typedef enum {
    FAP_PKT_CONTINUE,
    FAP_PKT_DONE,
    FAP_PKT_MAX
} fapAction_t;

//#define CC_FAP_ENET_RX_BLOCKING

typedef void (* FAP_ENET_TX_HOOK)(fapAction_t, uint32_t, uint32_t, int32_t, uint16_t);

extern FAP_ENET_TX_HOOK fapEnet_txHook_g;

void fapTxBind(FAP_ENET_TX_HOOK fapEnet_txHook);

fapAction_t fapReceiveBlocking(uint8_t *packet_p, uint32_t length, uint32_t encap,
                               uint32_t phyHdr, uint32_t *channel, uint32_t *queue,
                               int32_t *txAdjust);
fapAction_t fapReceive(uint8_t *packet_p, uint32_t length, uint32_t encap,
                       uint32_t phyHdr, uint32_t channel);

void fapTxSchedule(void);

//#define CC_FAP_ENET_STATS

#if defined(CC_FAP_ENET_STATS)
void fapEnetStats_contextFull(void);
void fapEnetStats_dqmRxFull(void);
void fapEnetStats_rxPackets(void);
void fapEnetStats_txPackets(uint32_t contextCount);
void fapEnetStats_interrupts(void);
void fapEnetStats_dump(void);
#else
#define fapEnetStats_contextFull()
#define fapEnetStats_dqmRxFull()
#define fapEnetStats_rxPackets()
#define fapEnetStats_txPackets(_contextCount)
#define fapEnetStats_interrupts()
#define fapEnetStats_dump()
#endif

//#define CC_FAP_EVENTS

#if defined(CC_FAP_EVENTS)
#undef FAP_DECL
#define FAP_DECL(x) #x,

#define FAP_EVENT_TYPE_NAME                     \
    {                                           \
        FAP_DECL(RX_BEGIN)            \
        FAP_DECL(RX_END)          \
        FAP_DECL(TX_SCHED)    \
        FAP_DECL(TX_BEGIN)    \
        FAP_DECL(TX_END)      \
    }

typedef enum {
    FAP_EVENT_RX_BEGIN,
    FAP_EVENT_RX_END,
    FAP_EVENT_TX_SCHED,
    FAP_EVENT_TX_BEGIN,
    FAP_EVENT_TX_END,
    FAP_EVENT_MAX
} fapEvent_type_t;

void fapEvent_record(fapEvent_type_t type, uint32_t arg);
void fapEvent_print(void);
uint32_t fapEnet_txQueueUsage(void);
#else
#define fapEvent_record(_type, _arg)
#define fapEvent_print()
#define fapEnet_txQueueUsage() 0
#endif

//#define CC_FAP_ENET_PMON

#if defined(CC_FAP_ENET_PMON)
#define FAP_ENET_PMON_LOG(x)        pmon_log(x)
#define FAP_ENET_PMON_CLR(x)        pmon_clr(x)
#define FAP_ENET_PMON_BGN()         pmon_bgn()
#define FAP_ENET_PMON_END(x)        pmon_end(x)
#define FAP_ENET_PMON_REG(x,y)      pmon_reg(x,y)
#else
#define FAP_ENET_PMON_LOG(x)        
#define FAP_ENET_PMON_CLR(x)        
#define FAP_ENET_PMON_BGN()
#define FAP_ENET_PMON_END(x)        
#define FAP_ENET_PMON_REG(x,y)
#endif

#endif  /* defined(__FAP_H_INCLUDED__) */
