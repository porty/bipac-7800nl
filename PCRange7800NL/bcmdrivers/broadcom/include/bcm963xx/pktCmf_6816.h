#ifndef __PKT_CMF_6816_H_INCLUDED__
#define __PKT_CMF_6816_H_INCLUDED__

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
 *******************************************************************************
 */

#include "bcm_log.h"
#include "pktHdr.h"     /* Common definitions and utilities */

/*----- Defines -----*/

#define PKTCMF_VERSION              "0.1"
#define PKTCMF_VER_STR              "v" PKTCMF_VERSION " " __DATE__ " " __TIME__
#define PKTCMF_MODNAME              "Broadcom Packet CMF 6816"

/* include bcm_map.h to use CMF_IS_6816Bx() */
#define CMF_IS_6816B0()             ((PERF->RevID  & 0xFF) == 0xB0)
#define CMF_IS_6816B1()             ((PERF->RevID  & 0xFF) == 0xB1)
#define CMF_IS_6816BX()             ( CMF_IS_6816B0() || CMF_IS_6816B1() )

#define PKTCMF_NAME                 "pktcmf"

#define PKTCMF_ERROR                (-1)
#define PKTCMF_SUCCESS              0

/* Packet CMF Character Device */
#define PKTCMFDRV_MAJOR             232
#define PKTCMFDRV_NAME              PKTCMF_NAME
#define PKTCMFDRV_DEVICE_NAME       "/dev/" PKTCMFDRV_NAME

/* Packet CMF Control Utility Executable */
#define PKTCMF_CTL_UTILITY_PATH     "/bin/cmfctl"

/* Packet CMF Proc FS Directory Path */
#define PKTCMF_PROC_FS_DIR_PATH     PKTCMF_NAME

/* Conditional Compilation */
// #define CC_LAB_CMF_FFE_BYPASS_MODE

/* Configuration of default action on MISS: "Drop" or "Send to MIPS" */
#define CMF_MISS_CFG_DROP   0
#define CMF_MISS_CFG_MIPS   1
#define CMF_MISS_CFG_PASS   2
#define CMF_MISS_DEFAULT    CMF_MISS_CFG_DROP

/* Menuconfig: BRCM_DRIVER_PKTFLOW_DEBUG selection will cause -DPKTDBG C Flags*/
#ifdef PKTDBG
#define CC_PKTCMF_DEBUG
#define CC_PKTCMF_ASSERT
#endif

#if defined( __KERNEL__ )
#include "bcm_OS_Deps.h"
#define KERNEL_LOCK(level)          local_irq_save(level)
#define KERNEL_UNLOCK(level)        local_irq_restore(level)
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

/* Redefined from unexported header: ./broadcom/net/enet/impl2/bcmenet.h */
#define BRCM_TAG_ETH_TYPE           0x8874  /* BRCM_TYPE */
#define BRCM_TAG_LENGTH             6

#define PKTCMF_ALL_ENTRIES          (-1)

/*
 *------------------------------------------------------------------------------
 * Single CMF RAM space shared by all CMF instances on the 6816
 * Flow cache uses a 16bit CMF Tuple for identifying a Flow accelerated in
 * hardware. As there is only a single CMF engine shared by all ports, the
 * entire 16bit value of the tuple is used to represent the matched FlowINFO
 * RAM element index.
 *
 * Macros shared by FlowCache for NATed configurations of CMF.
 *------------------------------------------------------------------------------
 */
typedef enum {
    CMF_DECL(PKTCMF_ENGINE_SWC)
    CMF_DECL(PKTCMF_ENGINE_ALL) /* max number of CMF enum */
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

/*
 *------------------------------------------------------------------------------
 *              Packet CFM character device driver IOCTL enums
 * A character device and the associated userspace utility for design debug.
 * Include pktCmfParser.h for ACTIVATE/DEACTIVATE IOCTLs
 *------------------------------------------------------------------------------
 */
typedef enum {
    CMF_DECL(PKTCMF_IOC_STATUS)
    CMF_DECL(PKTCMF_IOC_RESET)
    CMF_DECL(PKTCMF_IOC_INIT)
    CMF_DECL(PKTCMF_IOC_ENABLE)
    CMF_DECL(PKTCMF_IOC_DISABLE)
    CMF_DECL(PKTCMF_IOC_LEARN)
    CMF_DECL(PKTCMF_IOC_DEFER)
    CMF_DECL(PKTCMF_IOC_MCAST)
    CMF_DECL(PKTCMF_IOC_NAT)
    CMF_DECL(PKTCMF_IOC_KCALL)
    CMF_DECL(PKTCMF_IOC_UNITTEST)
    CMF_DECL(PKTCMF_IOC_DEBUG)
    CMF_DECL(PKTCMF_IOC_PRINT)
    CMF_DECL(PKTCMF_IOC_HELLOCONFIG)
    CMF_DECL(PKTCMF_IOC_HELLOTRAFFIC)
    CMF_DECL(PKTCMF_IOC_ASPF)
    CMF_DECL(PKTCMF_IOC_PADLEN)
    CMF_DECL(PKTCMF_IOC_SET_GBL)
    CMF_DECL(PKTCMF_IOC_GET_GBL)
    CMF_DECL(PKTCMF_IOC_SET_PORT_DEFAULTS)
    CMF_DECL(PKTCMF_IOC_GET_PORT_DEFAULTS)
    CMF_DECL(PKTCMF_IOC_ACTIVATE_AS_TBL)
    CMF_DECL(PKTCMF_IOC_DEACTIVATE_AS_TBL)
    CMF_DECL(PKTCMF_IOC_ACTIVATE_DP_TBL)
    CMF_DECL(PKTCMF_IOC_DEACTIVATE_DP_TBL)
    CMF_DECL(PKTCMF_IOC_ACTIVATE_EP_TBL)
    CMF_DECL(PKTCMF_IOC_DEACTIVATE_EP_TBL)
    CMF_DECL(PKTCMF_IOC_ACTIVATE_PAC_TBL)
    CMF_DECL(PKTCMF_IOC_DEACTIVATE_PAC_TBL)
    CMF_DECL(PKTCMF_IOC_ACTIVATE_FCB)
    CMF_DECL(PKTCMF_IOC_DEACTIVATE_FCB)
    CMF_DECL(PKTCMF_IOC_FFE_MEM_ACCESS)
    CMF_DECL(PKTCMF_IOC_FFE_CFG_LABEL)
    CMF_DECL(PKTCMF_IOC_FFE_CFG_SNOOP)
    CMF_DECL(PKTCMF_IOC_FFE_CFG_PATCH)
    CMF_DECL(PKTCMF_IOC_CMF_CFG_MISS)
    CMF_DECL(PKTCMF_IOC_LAB_FLOW)
    CMF_DECL(PKTCMF_IOC_FCB_CTRL)
    CMF_DECL(PKTCMF_IOC_GET_FCBHITS)
    CMF_DECL(PKTCMF_IOC_MAX)
} pktCmf_ioctl_t;


typedef enum
{
    CMF_DECL(PKTCMF_HELLO_CMF)  /* Packet CMF Engine                        */
    CMF_DECL(PKTCMF_HELLO_DST)  /* LANPort EMACS, GPON GEM default destQ    */
    CMF_DECL(PKTCMF_HELLO_FLT)  /* Rule Filter Inspection Element Table     */
    CMF_DECL(PKTCMF_HELLO_SIG)  /* Rule Signature Vector TCAM               */
    CMF_DECL(PKTCMF_HELLO_CTX)  /* Context RAM: Sig H|M, Flow H|M, Aspf Hit */
    CMF_DECL(PKTCMF_HELLO_FFE)  /* Flexible Forwarding Engine               */
    CMF_DECL(PKTCMF_HELLO_ASP)  /* Antispoof Vector, TCAM and Logic         */
    CMF_DECL(PKTCMF_HELLO_FLW)  /* Flow Parse Vector TCAM                   */
    CMF_DECL(PKTCMF_HELLO_FIR)  /* Flow Info RAM                            */
    CMF_DECL(PKTCMF_HELLO_NAT)  /* NAT RAM                                  */
    CMF_DECL(PKTCMF_HELLO_HDR)  /* Header info RAM                          */
    CMF_DECL(PKTCMF_HELLO_CMD)  /* Rule Command Set                         */
    CMF_DECL(PKTCMF_HELLO_MOD)  /* Packet Modification Block                */

    CMF_DECL(PKTCMF_HELLO_SWC)  /* Switch VLAN 802.1Q strip/replace TODO    */
    CMF_DECL(PKTCMF_HELLO_GCF)  /* GPON Mcast Coarse Filter TODO            */

    CMF_DECL(PKTCMF_HW_LAYER)
    CMF_DECL(PKTCMF_HW_FLT)
    CMF_DECL(PKTCMF_HW_CAM)
    CMF_DECL(PKTCMF_HW_CTX)
    CMF_DECL(PKTCMF_HW_FIR)
    CMF_DECL(PKTCMF_HW_NAT)
    CMF_DECL(PKTCMF_HW_HDR)
    CMF_DECL(PKTCMF_HW_CMD)
    CMF_DECL(PKTCMF_HW_CAP)
    CMF_DECL(PKTCMF_HW_HITS)
    CMF_DECL(PKTCMF_HW_MISS)
    CMF_DECL(PKTCMF_HW_DROP)

    CMF_DECL(PKTCMF_HWIF_LAYER)
    CMF_DECL(PKTCMF_HWIF_FLT)
    CMF_DECL(PKTCMF_HWIF_SIG)
    CMF_DECL(PKTCMF_HWIF_ASP)
    CMF_DECL(PKTCMF_HWIF_DSC)
    CMF_DECL(PKTCMF_HWIF_CTX)
    CMF_DECL(PKTCMF_HWIF_CMD)
    CMF_DECL(PKTCMF_HWIF_FPV)
    CMF_DECL(PKTCMF_HWIF_FIR)
    CMF_DECL(PKTCMF_HWIF_HDR)
    CMF_DECL(PKTCMF_HWIF_NAT)
    CMF_DECL(PKTCMF_HWIF_FLW)
    CMF_DECL(PKTCMF_HWIF_TPID)
    CMF_DECL(PKTCMF_HWIF_NEQ)
    CMF_DECL(PKTCMF_HWIF_PADLEN)

    CMF_DECL(PKTCMF_HAL_LAYER)
    CMF_DECL(PKTCMF_HAL_FLT)
    CMF_DECL(PKTCMF_HAL_SIG)
    CMF_DECL(PKTCMF_HAL_ASP)
    CMF_DECL(PKTCMF_HAL_DSC)
    CMF_DECL(PKTCMF_HAL_CTX)
    CMF_DECL(PKTCMF_HAL_CMD)
    CMF_DECL(PKTCMF_HAL_FPV)
    CMF_DECL(PKTCMF_HAL_FIR)
    CMF_DECL(PKTCMF_HAL_HDR)
    CMF_DECL(PKTCMF_HAL_NAT)
    CMF_DECL(PKTCMF_HAL_FLW)
    CMF_DECL(PKTCMF_HAL_NEQ)

    CMF_DECL(PKTCMF_PARSER_LAYER)
    CMF_DECL(PKTCMF_PARSER_FCB)
    CMF_DECL(PKTCMF_PARSER_FLW)
    CMF_DECL(PKTCMF_PARSER_ASTBL)
    CMF_DECL(PKTCMF_PARSER_DPTBL)
    CMF_DECL(PKTCMF_PARSER_PACTBL)
    CMF_DECL(PKTCMF_PARSER_EPTBL)

    CMF_DECL(PKTCMF_FFE_LAYER)

    CMF_DECL(PKTCMF_NAT_LAYER)
    CMF_DECL(PKTCMF_LEARN_LAYER)
} pktCmf_layer_t;

typedef uint32_t pktCmfParser_EntityId_t;

/*
 * Interface: Single callback entry point into Packet CMF subsystem
 * from CMF Control utility or other kernel modules.
 */
typedef enum {
    CMF_DECL(PKTCMF_IF_STATUS)
    CMF_DECL(PKTCMF_IF_RESET)
    CMF_DECL(PKTCMF_IF_INIT)
    CMF_DECL(PKTCMF_IF_ENABLE)
    CMF_DECL(PKTCMF_IF_DISABLE)
    CMF_DECL(PKTCMF_IF_PRE_SYSTEMRESET)
    CMF_DECL(PKTCMF_IF_POST_SYSTEMRESET)
    CMF_DECL(PKTCMF_IF_FLUSH)
    CMF_DECL(PKTCMF_IF_DEBUG)
    CMF_DECL(PKTCMF_IF_PRINT)
    CMF_DECL(PKTCMF_IF_UNITTEST)
    CMF_DECL(PKTCMF_IF_CONFIG)
    CMF_DECL(PKTCMF_IF_TRAFFIC)
    CMF_DECL(PKTCMF_IF_SET_ASPF)
    CMF_DECL(PKTCMF_IF_GET_ASPF)
    CMF_DECL(PKTCMF_IF_SET_TPID)
    CMF_DECL(PKTCMF_IF_GET_TPID)
    CMF_DECL(PKTCMF_IF_CMF_CFG_MISS)
    CMF_DECL(PKTCMF_IF_LABFLOW)
    CMF_DECL(PKTCMF_IF_FCBCTRL)
    CMF_DECL(PKTCMF_IF_SET_PADLEN)
    CMF_DECL(PKTCMF_IF_GET_PADLEN)
} pktCmf_if_t;

extern int pktCmf_isEnabled(void);

extern int pktCmfIf( pktCmf_if_t callback, int *parg1, int *parg2 );

#define HELLO_PKT_ERRORED   2
#define HELLO_PKT_FWD2MIPS  0
#define HELLO_PKT_CONSUMED  1
#define HELLO_PKT_DROPPED   2

struct sk_buff;
typedef int (*pktCmfHelloTx)(struct sk_buff * skb_p, int xPort);

#ifdef SUPPORT_HELLO
/*
 * SUPPORT_HELLO conditional compilation: -DSUPPORT_HELLO
 * See: impl2/Makefile  defines CFLAGS += -DSUPPORT_HELLO
 *      cmfctl/Makefile defines CFLAGS += -DSUPPORT_HELLO
 *      bcmenet/impl3/Makefile defines EXTRA_CFLAGS += -DSUPPORT_HELLO
 */
extern int pktCmfHelloRx(struct sk_buff * skb_p, int xPort,
                         pktCmfHelloTx xmitFn);

/* HELLO Callback : Single entry point into HELLO */
extern int pktCmfHelloIf( pktCmf_if_t callback, int *parg1, int *parg2 );
#else
#define pktCmfHelloRx(skb, port, xmitFn) 0
#define pktCmfHelloIf(cb,p1,p2) PKTCMF_SUCCESS
#endif

/* FiltCam Port Capture Configuration: CmfCtl <-> HW */
typedef union {
    struct {
        uint16_t captureFIR     : 1;
        uint16_t captureSIG     : 1;
        uint16_t captureFPV     : 1;
        uint16_t captureASP     : 1;

        uint16_t captureMiss    : 1;
        uint16_t captureHit     : 1;

        uint16_t captureOff     : 1;        /* Disable capture feature */
        uint16_t captureDump    : 1;        /* Dump anything captured */

        uint16_t capturePort    : 8;
    };
    uint16_t u16;
} PortCaptureRequest_t;

/* Lab Flows Configuration: CmfCtl <-> Config : VLAN filters */
typedef enum {
    CMF_DECL(FILT_INV) 
    CMF_DECL(FILT_PBITS)        /* VLAN Outer Tag  3bit pBits */
    CMF_DECL(FILT_VID)          /* VLAN Outer Tag 12bit VLAN ID */
    CMF_DECL(FILT_TCID)         /* VLAN Outer Tag 16bit VLAN TCID */
    CMF_DECL(FILT_ETYPE)        /* Untagged EtherType or Outer VLAN TPID */
    CMF_DECL(FILT_PORT)         /* Ingress Port */
    CMF_DECL(FILT_MAX)
} CmfLabFiltType_t;

/* Description of a single 16bit filter static flow, with forwarding info */
typedef union {
    struct {

        struct {
            uint16_t         filt   :  5;    /* bits 31..27 */
            uint16_t         destQ  :  3;    /* bits 26..24 */
            uint16_t         dest   :  8;    /* bits 23..16 */
        } fwd;

        union {
            struct {
                uint16_t    pbits  :  3;    /* bits 15..13 */
                uint16_t    dei    :  1;    /* bit  12     */
                uint16_t    id     : 12;    /* bits 11..00 */
            } vlan;
            uint16_t        tcid;           /* bits 15..00 */
            uint16_t        etype;          /* bits 15..00 */
            uint16_t        u16;            /* bits 15..00 */
        } value;
    };

    uint32_t u32;

} CmfLabFlow_t;

/*
 *------------------------------------------------------------------------------
 *                  Enet Switch Driver Hooks
 *  Ethernet switch driver will register the appropriate handlers to
 *  manage the Switch ports. CMF will invoke these handlers when CMF is
 *  initialized.
 *------------------------------------------------------------------------------
 */
extern HOOKV pktCmfSaveSwitchPortState;      /* Binding with Switch ENET */
extern HOOKV pktCmfRestoreSwitchPortState;   /* Binding with Switch ENET */
extern HOOKV pktCmfResetSwitch;              /* LAB trigger of reset_switch() */

#endif  /* defined(__PKT_CMF_6816_H_INCLUDED__) */

