#ifndef __PKT_CMF_6368_H_INCLUDED__
#define __PKT_CMF_6368_H_INCLUDED__

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
 * File Name  : pktCmf.h
 *
 * Description: This file contains the specification of some common definitions
 *      and interfaces to other modules. This file may be included by both
 *      Kernel and userapp (C only).
 *
 * FIXME: Conditional Compilation directive cleanup for production.
 *
 *******************************************************************************
 */

#include "pktHdr.h"     /* Common definitions and utilities */

/*----- Conditional Compilation Directives -----*/

/* Conditional Compilation of color encodings: Windows hyperterm has issues? */
#ifdef PKTDBG
#define CC_PKTCMF_COLOR_PRINT
#endif

/*
 * Conditional Compilation for Debug Support: global and per layer override
 * - Commenting out CC_PKTCMF_DEBUG will disable debug for all layers.
 * - Selectively disable per subsystem by commenting out its define.
 * - Debug levels listed in pktDbg.h
 */
#ifdef PKTDBG
#define CC_PKTCMF_DEBUG
#endif

#define CC_PKTCMF_HW_DEBUG_LVL      0 /* DBG_BASIC Level Basic              */
#define CC_PKTCMF_HAL_DEBUG_LVL     0 /* DBG_BASIC Level Basic              */
#define CC_PKTCMF_FWD_DEBUG_LVL     0 /* DBG_BASIC Level Basic              */
#define CC_PKTCMF_DRV_DEBUG_LVL     0 /* DBG_BASIC Level Basic              */
#define CC_PKTCMF_PROTO_DEBUG_LVL   0 /* DBG_BASIC Level Basic              */
#define CC_PKTCMF_CONFIG_DEBUG_LVL  0 /* DBG_EXTIF Level External Interface */
#define CC_PKTCMF_UTIL_DEBUG_LVL    0 /* DBG_BASIC Level Basic              */

/*
 * Conditional Compilation for Assert Support: global and per layer override
 * - Commenting out CC_PKTCMF_ASSERT will disable assert for all layers.
 */
#ifdef PKTDBG
#define CC_PKTCMF_ASSERT
#endif

#define CC_PKTCMF_HW_ASSERT
#define CC_PKTCMF_HAL_ASSERT
#define CC_PKTCMF_FWD_ASSERT
#define CC_PKTCMF_DRV_ASSERT
#define CC_PKTCMF_PROTO_ASSERT
#define CC_PKTCMF_CONFIG_ASSERT
#define CC_PKTCMF_UTIL_ASSERT

/* LAB ONLY: Conditional Compilation to enable static configuration */
// xtmrt is presently statically configured, dependency: bcmxtmrt_request()
// #define CC_PKTCMF_STATIC_CONFIG_ENABLED

/* LAB ONLY: Conditional Compilation to enable proc filesystem displays */
#define CC_PKTCMF_PROC_FS_SUPPORT

/* LAB ONLY: Conditional Compilation to enable CMF Table Dumps */
#ifdef PKTDBG
#define CC_PKTCMF_HW_DUMP_SUPPORT
#define CC_PKTCMF_TABLE_DUMP
#endif

/* LAB ONLY: Conditional Compilation to enable IP flow statistics reporting */
#define CC_PKTCMF_FLOW_STATS

/* CAUTION:  PBuf statistics counters may be read and cleared by XTM */
#define CC_PKTCMF_PBUF_STATS


/* LAB ONLY: Conditional Compilation of Packet CMF Manual Initialization */
// #define CC_PKTCMF_MANUAL_INITIALIZATION

/* LAB ONLY: Conditional Compilation to override SwPktBusCTL config in XTM */
// #define CC_PKTCMF_SWITCHPKTBUS_OVERRIDE


/*----- Defines -----*/

#define PKTCMF_VERSION              "0.1"
#define PKTCMF_VER_STR              "v" PKTCMF_VERSION " " __DATE__ " " __TIME__
#define PKTCMF_MODNAME              "Broadcom Packet CMF (Experimental)"

#define PKTCMF_NAME                 "pktcmf"

#define PKTCMF_ERROR                (-1)
#define PKTCMF_SUCCESS              0

#define PKTCMF_LEARN_DISABLE        0
#define PKTCMF_LEARN_ENABLE         1
#define PKTCMF_LEARN_FLUSH          2

/* Packet CMF Character Device */
#define PKTCMFDRV_MAJOR             232
#define PKTCMFDRV_NAME              PKTCMF_NAME
#define PKTCMFDRV_DEVICE_NAME       "/dev/" PKTCMFDRV_NAME

#define DS_MIPS_FWD        /* always use software forwarding for downstream */
#define US_MIPS_FWD_FORCE        /* always use software forwarding for upstream */

/* Packet CMF MIPS Assisted Forwarding Network Device */
#define PKTCMF_SWC_NETDEV_NAME      "swc"
#define PKTCMF_SAR_NETDEV_NAME      "sar"

/* Packet CMF Control Utility Executable */
#define PKTCMF_CTL_UTILITY_PATH     "/bin/cmfctl"

/* Packet CMF Vizualizer Daemon Executable */
#define PKTCMF_VIZ_DAEMON_PATH      "/bin/" PKTCMF_NAME "vizd"
#define PKTCMF_VIZ_IP_ADDR          "192.168.1.100"
#define PKTCMF_VIZ_PORT_NUM         3333

/* Packet CMF Proc FS Directory Path */
#define PKTCMF_PROC_FS_DIR_PATH     PKTCMF_NAME

/* Reserved channel for DSL Diags */
#define DSLDIAGS_CHANNEL            15

/* Upstream flows to CMF_SHADOW_TXCH will be hardware forwarded by SWC CMF */
#define CMF_SHADOW_TXCH             0

/*
 *------------------------------------------------------------------------------
 * For Linux: use local_irq_save/local_irq_restore
 * For VxWorks: use intLock/intUnlock
 *------------------------------------------------------------------------------
 */
#if defined( __KERNEL__ )
#include <asm/system.h>             /* interrupt locking for MIPS */
#define KERNEL_LOCK(level)          local_irq_save(level)
#define KERNEL_UNLOCK(level)        local_irq_restore(level)
#endif

/*
 *------------------------------------------------------------------------------
 * Color encoding for Packet CMF layers. Macro CLRsys defined per CMF layer.
 *------------------------------------------------------------------------------
 */
#if defined(CC_PKTCMF_COLOR_PRINT)
#define PKT_DBG_COLOR_SUPPORTED
#endif

/*
 *------------------------------------------------------------------------------
 * Common debug macros for Packet CMF layers.
 *------------------------------------------------------------------------------
 */
#if defined(CC_PKTCMF_DEBUG)
#define PKT_DBG_SUPPORTED
#endif

#if defined(CC_PKTCMF_ASSERT)
#define PKT_ASSERT_SUPPORTED
#endif

/*
 *------------------------------------------------------------------------------
 * Common defines for Packet CMF layers.
 *------------------------------------------------------------------------------
 */
#define CMF_DECL(x)                 #x, /* for string declaration in C file */
#undef CMF_DECL
#define CMF_DECL(x)                 x,  /* for enum declaration in H file */

/* Offsets and sizes in CMF are specified as half words */
#define CMFUNIT                     (sizeof(uint16_t))

#define CMP1BYTE                    (sizeof(uint8_t))
#define CMP2BYTES                   (sizeof(uint16_t))
#define CMP4BYTES                   (sizeof(uint32_t))

/* Creation of CMF NIBBLE MASK, b0=[0..3] b1=[4..7] b2=[8..11] b3=[12..15] */
#define NBLMSK1BYTE                 0x3
#define NBLMSK3NBLS                 0x7
#define NBLMSK2BYTES                0xF

/*
 *------------------------------------------------------------------------------
 * A CMF Entry is represented by a tuple (Engine+InfoRam MatchIx). Given this
 * tuple, the CMF Engine instance and InfoRam entry can be extracted using
 * the following macros. Any entries in other RAMs of the CMF Engine can also
 * be deduced from the tuple via the HAL layer.
 * 
 * Conversion of a 2byte CMF match index to a CMF instance and match tag index.
 *------------------------------------------------------------------------------
 */

/*
 * The Upstream SAR TxChannel or Downstream SAR RxChannel can be extracted
 * from the MatchTag for an upstream or downstream flow, by applying the
 * CMF_CHANNELMSK to the MatchTag. The lower 4 bits of a match tag are
 * passed through the Switch Packet Bus and serve as channel identification
 * in the upstream.
 */
#if defined(US_MIPS_FWD_FORCE)
#define CMF_CHANNELMSK              0x0
#else
#define CMF_CHANNELMSK              0xF
#endif

/* Construct a 16bit CMF tuple from the Engine and Match index. */
#define CMF_TUPLE16(eng,matchIx)    ((__force uint16_t)(((eng)<<8)\
                                                       |((matchIx)&0xFF)))

/* Extract the Engine (CMF memory space) from the CMF <Engine,MatchIx> tuple. */
#define GET_CMF_ENGINE(cmfTuple16)  ((__force uint8_t)((cmfTuple16>>8) & 0xFF))

/* Extract the MatchIx from the CMF tuple. */
#define GET_CMF_MATCHIX(cmfTuple16) ((__force uint8_t)((cmfTuple16) & 0xFF))

/* Special tuple to signify an invalid tuple. */
#define CMF_TUPLE16_INVALID         CMF_TUPLE16( NULL_IX8, NULL_IX8 )

/* CAUTION: Limited for use between CMF Ctl and CMF Char Device.  */
#define IS_ENGINE(cmfs, eng)        ( (cmfs) &  (1 << eng) )
#define SET_ENGINE(cmfs, eng)       ( (cmfs) |= (1 << eng) )
#define ALL_ENGINE                  ( (1 << PKTCMF_ENGINE_SWC) \
                                    | (1 << PKTCMF_ENGINE_SAR) )

/*
 * SWC VCIDs: [0..8]   6=USB, 7=SAR 8=IMP port to MIPS.
 * SAR VCIDs: [0..16] 16=cell
 */
#define CMF_USB_VCID                6
#define CMF_SAR_VCID                7
#define CMF_MIPS_VCID               8
#define CMF_MAX_VCID                16

/* Redefined from unexported header: ./broadcom/net/enet/impl2/bcmenet.h */
#define BRCM_TAG_ETH_TYPE           0x8874  /* BRCM_TYPE */
#define BRCM_TAG_LENGTH             6
#define BRCM_TAG_ETH_TYPE2          0x888A  /* BRCM_TYPE2 */
#define BRCM_TAG_LENGTH2            4

/* cmf_error: unconditionally compiled */
#define cmf_error(fmt, arg...)      \
        print( CLRerr DBGsys "%-10s ERROR: " fmt CLRnl, __FUNCTION__, ##arg )

/*
 *------------------------------------------------------------------------------
 * A Packet CMF Engine effectively identifies the memory space of a CMF.
 * 6368 has two CMF memory space corresponding to each CMF engine on the SWC
 * and SAR sides, responsible for "upstream" and "downstream" respectively.
 *------------------------------------------------------------------------------
 */
typedef enum {
    CMF_DECL(PKTCMF_ENGINE_SWC)
    CMF_DECL(PKTCMF_ENGINE_SAR)
    CMF_DECL(PKTCMF_ENGINE_ALL) /* max number of CMF enum */
} PktCmfEngine_t;

/*
 *------------------------------------------------------------------------------
 *
 * Packet CMF Functional Callbacks
 * - Show: Displaying allocated entires in selected CMF(s)
 * - Reset: Selected CMF(s) are placed in Hardware Powerup state.
 * - Init: Selected CMF(s) initial (default) state setting.
 * - Enable: Runtime binding with Linux networking
 * - Disable: Runtime unbinding with Linux networking, flush HAL, HW layers
 *------------------------------------------------------------------------------
 */
typedef enum {
    CMF_DECL(PKTCMF_STATUS)
    CMF_DECL(PKTCMF_RESET)
    CMF_DECL(PKTCMF_INIT)
    CMF_DECL(PKTCMF_ENABLE)
    CMF_DECL(PKTCMF_DISABLE)
    CMF_DECL(PKTCMF_FLUSH)
    CMF_DECL(PKTCMF_PLOG)
    CMF_DECL(PKTCMF_PREQ)
} PktCmfCallback_t;             /* Exported callbacks */

/* Generic call back */
extern int pktCmfCallback(PktCmfEngine_t eng,
                          PktCmfCallback_t callback, int arg);

/* Explicit wrappers to callback */
extern int pktCmfSwcConfig(void);
extern int pktCmfSarConfig(int ulHwFwdTxChannel, unsigned int ulTrafficType);
extern int pktCmfSarAbort(void);

/*
 *------------------------------------------------------------------------------
 *                  Enet Switch Driver Hooks
 *  Ethernet switch driver will register the appropriate handlers to
 *  configure the SAR Port of the Switch. CMF will invoke these handlers when
 *  the SAR runtime driver becomes operational and wishes to use CMF for
 *  downstream hardware accelerated forwarding via the SAR port of the Switch.
 *------------------------------------------------------------------------------
 */
extern HOOKV pktCmfSarPortEnable;   /* Binding with Switch ENET */
extern HOOKV pktCmfSarPortDisable;  /* Binding with Switch ENET */

typedef enum
{
    CMF_DECL(HW_LAYER)
    CMF_DECL(HAL_LAYER)
    CMF_DECL(PROTO_LAYER)
    CMF_DECL(DRV_LAYER)
    CMF_DECL(FWD_LAYER)
    CMF_DECL(UTIL_LAYER)
    CMF_DECL(CONFIG_LAYER)
    CMF_DECL(LEARN_LAYER)
} PktCmfLayer_t;

/*
 *------------------------------------------------------------------------------
 *              Packet CFM character device driver IOCTL enums
 * A character device and the associated userspace utility for design debug.
 *------------------------------------------------------------------------------
 */
typedef enum PktCmfIoctl
{
    CMF_DECL(PKTCMFIOCTL_STATUS)
    CMF_DECL(PKTCMFIOCTL_RESET)
    CMF_DECL(PKTCMFIOCTL_INIT)
    CMF_DECL(PKTCMFIOCTL_ENABLE)
    CMF_DECL(PKTCMFIOCTL_DISABLE)
    CMF_DECL(PKTCMFIOCTL_LEARN)
    CMF_DECL(PKTCMFIOCTL_DEFER)
    CMF_DECL(PKTCMFIOCTL_MCAST)
    CMF_DECL(PKTCMFIOCTL_CONFIG)
    CMF_DECL(PKTCMFIOCTL_UPSTREAM)
    CMF_DECL(PKTCMFIOCTL_DNSTREAM)
    CMF_DECL(PKTCMFIOCTL_DSLDIAGS)
    CMF_DECL(PKTCMFIOCTL_KERNELCALL)
    CMF_DECL(PKTCMFIOCTL_DEBUG)
    CMF_DECL(PKTCMFIOCTL_INVALID)
} PktCmfIoctl_t;

extern int  pktCmfDrvConstruct(void);   /* CMF character device constructor */
extern void pktCmfDrvDestruct(void);    /* CMF character device destructor */

extern int  pktCmfFwdConstruct(void);   /* CMF FWD network device constructor */
extern void pktCmfFwdDestruct(void);    /* CMF FWD network device destructor */

#if defined(CC_PKTCMF_FLOW_STATS)
/*
 *------------------------------------------------------------------------------
 * Statistics maintained in kernel spaced and mmapped to user space.
 *------------------------------------------------------------------------------
 */
#define PKTCMF_MAX_FLOWS            128

typedef struct {
    uint8_t             matchIx;
    uint8_t             mipsIx;
    uint16_t            resvd;
    uint32_t            pktRate;        /* pkt count in last interval */
    uint32_t            pktsCnt;        /* cummulative */
    uint32_t            octetsCnt;      /* cummulative */
    uint32_t            old_ipdaddr;
    uint32_t            old_ipsaddr;
    uint16_t            old_port_dst;
    uint16_t            old_port_src;
} pktCmfFlowStats_t;

typedef struct {
    uint16_t            num_flows[ PKTCMF_ENGINE_ALL ];
    pktCmfFlowStats_t   flowStats[ PKTCMF_ENGINE_ALL][ PKTCMF_MAX_FLOWS ];
} PktCmfStats_t;

extern PktCmfStats_t pktCmfStats_g;

#endif

/* The Port on internal switch connected to ext switch */ 
#define BRCM_EXT_SW_PORT    5  // GMII2_PORT_ID

/* tag Info when an ext switch is used */ 
typedef struct {
    uint8_t  tagEna;    /* external Tag is enabled */
    uint8_t  tagLen;    /* length of external tag */
    uint16_t tagType;   /* Tag Type Rx from or Tx to ext switch */
    uint16_t resvd1;    /* unused */
    uint8_t  resvd0;    /* unused */
    uint8_t  port;      /* The internal port to which ext switch is connected */
} BrcmExtSw_t;

extern BrcmExtSw_t brcmExtSw_g;

#endif  /* defined(__PKT_CMF_6368_H_INCLUDED__) */

