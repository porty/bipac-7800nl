#ifndef __FCACHE_H_INCLUDED__
#define __FCACHE_H_INCLUDED__

/*
 *
 * Patent pending Flow Cache algorithm and implementation.
 *

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
 * File Name : fcache.h
 * Description of Flow Cache is CONFIDENTIAL and available ONLY in fcache.c .
 *
 *  Version 0.1: Prototype
 *  Version 1.0: BCM963xx
 *  Version 1.1: Multicast
 *  Version 1.2: L4 protocol, L1
 *  Version 2.0: FKB based
 *  Version 2.1: IPv6 Support
 *
 *******************************************************************************
 */
#define PKTFLOW_VERSION             "v2.1"

#define PKTFLOW_VER_STR             PKTFLOW_VERSION " " __DATE__ " " __TIME__
#define PKTFLOW_MODNAME             "Broadcom Packet Flow Cache "
#define PKTFLOW_NAME                "fcache"
#define FCACHE_PROCFS_DIR_PATH      PKTFLOW_NAME    /* dir: /procfs/fcache    */

/* Flow Cache Character Device */
#define FCACHE_DRV_MAJOR             242
#define FCACHE_DRV_NAME              PKTFLOW_NAME
#define FCACHE_DRV_DEVICE_NAME       "/dev/" FCACHE_DRV_NAME

/*
 * Conditional Compilation for Debug Support: global and per layer override
 * - Commenting out CC_FCACHE_DEBUG will disable debug for all layers.
 * - Selectively disable per subsystem by commenting out its define.
 * - Debug levels listed in pktDbg.h
 */
#ifdef PKTDBG
#define CC_FCACHE_DEBUG
#endif

/* LAB ONLY: Design development */
#ifdef PKTDBG
#define CC_CONFIG_FCACHE_COLOR          /* Color highlighted debugging     */
#define CC_CONFIG_FCACHE_DBGLVL     0   /* DBG_BASIC Level                 */
#define CC_CONFIG_FCACHE_DRV_DBGLVL 0   /* DBG_BASIC Level Basic           */
#define CC_CONFIG_FCACHE_STATS          /* Statistics design engineering   */
#endif

/* Functional interface return status */
#define FCACHE_ERROR                (-1)    /* Functional interface error     */
#define FCACHE_SUCCESS              0       /* Functional interface success   */

#define FCACHE_CHECK                1       /* Boolean enforcing key audits   */

/* fc_error: unconditionally compiled */
#define fc_error(fmt, arg...)      \
        print( CLRerr DBGsys "%-10s ERROR: " fmt CLRnl, __FUNCTION__, ##arg )

#undef FCACHE_DECL
#define FCACHE_DECL(x)      x,  /* for enum declaration in H file */

typedef enum
{
    FCACHE_DECL(FCACHE_DBG_DRV_LAYER)
    FCACHE_DECL(FCACHE_DBG_FC_LAYER)
    FCACHE_DECL(FCACHE_DBG_LAYER_MAX)
} FcacheDbgLayer_t;


/*
 *------------------------------------------------------------------------------
 *              Flow Cache character device driver IOCTL enums
 * A character device and the associated userspace utility for design debug.
 *------------------------------------------------------------------------------
 */
typedef enum FcacheIoctl
{
    FCACHE_DECL(FCACHE_IOCTL_STATUS)
    FCACHE_DECL(FCACHE_IOCTL_ENABLE)
    FCACHE_DECL(FCACHE_IOCTL_DISABLE)
    FCACHE_DECL(FCACHE_IOCTL_FLUSH)
    FCACHE_DECL(FCACHE_IOCTL_DEFER)
    FCACHE_DECL(FCACHE_IOCTL_MCAST)
    FCACHE_DECL(FCACHE_IOCTL_MONITOR)
    FCACHE_DECL(FCACHE_IOCTL_TIMER)
    FCACHE_DECL(FCACHE_IOCTL_DEBUG)
    FCACHE_DECL(FCACHE_IOCTL_INVALID)
} FcacheIoctl_t;


#include <pktHdr.h>

#if defined(CONFIG_BCM_PKTFLOW_MODULE) || defined(CONFIG_BCM_PKTFLOW)

#if !defined(CONFIG_BLOG)
#error "Attempting to build Flow cache without BLOG"
#endif

#include <linux/blog.h>

/*
 *------------------------------------------------------------------------------
 * Conditional Compile configuration for Packet Flow Cache
 *------------------------------------------------------------------------------
 */

#if defined(CONFIG_BLOG_IPV6)
#define CC_FCACHE_IPV6_SUPPORT
#endif

//#define CC_CONFIG_FCACHE_BLOG_MANUAL    /* LAB ONLY: Manual blog enabling  */

#define CC_CONFIG_FCACHE_PROCFS         /* Proc filesystem debug dumps     */

#define CC_CONFIG_FCACHE_STACK          /* Patent Pending: sw acceleration */

#if defined(CONFIG_BCM_PKTCMF_MODULE) || defined(CONFIG_BCM_PKTCMF) ||  \
    defined(CONFIG_BCM_FAP_MODULE) || defined(CONFIG_BCM_FAP)
#define CC_FCACHE_PKTCMF                   /* Hardware CMF configured         */
#define CC_CONFIG_FCACHE_DEFER          /* Defer CMF activation on swhit   */
// #define CC_CONFIG_FCACHE_JENKINS_HASH   /* Jenkins 3word hash algorithm    */
#endif

/*
 *------------------------------------------------------------------------------
 * Implementation Constants 
 *------------------------------------------------------------------------------
 */

/* Flow cache static engineering: runtime poll board memory availability ...  */
#define FCACHE_HTABLE_SIZE           64     /* Must not be greater than 255   */
#define FCACHE_MAX_ENTRIES          256     /* Maximum number of entries      */
#if (FCACHE_HTABLE_SIZE > 256)              /* CAUTION: Blog_t uint8_t hash   */
#error "Invalid hash tables size, DO NOT EXCEED 256"
#endif
#if (FCACHE_MAX_ENTRIES > 256)              /* CAUTION: Flow_t uint8_t self   */
#error "Invalid number of flow cache entries, DO NOT EXCEED 256" 
#endif

#define FCACHE_STACK_SIZE           8               /* goto stack size        */
#define FCACHE_JHASH_RAND           0xBABEEBAB      /* Sufficiently random    */

/* Flow cache system periodic timer */
#define FCACHE_REFRESH              ( 1 )           /* Flush timer interval   */
#define FCACHE_REFRESH_INTERVAL     ( FCACHE_REFRESH SECONDS )


/* Refresh based on layer-4 protocol */
#define FCACHE_REFRESH_TCP          60
#define FCACHE_REFRESH_UDP          180
#define FCACHE_REFRESH_TCP_INTERVAL ( FCACHE_REFRESH_TCP SECONDS )
#define FCACHE_REFRESH_UDP_INTERVAL ( FCACHE_REFRESH_UDP SECONDS )

/* Flow cache entry experiencing hw|sw hits has idle quota of FLOW_MAX_QUOTA  */
#define FLOW_MAX_QUOTA              0xFF

/* Reconfigure Hardware CMF if software hits larger than threshold */
#define FCACHE_REACTIVATE           256     /* Lookup threshold to reactivate */
#define FCACHE_MAX_PENALTY          8

/* Flow cache hash table IP-Tuple lookup result */
#define FCACHE_MISS                 0       /* Lookup IPTuple hash table miss */
#define FCACHE_HIT                  1       /* Lookup IPTuple hash table hit  */

/* Hardware CMF invalid connection reference key */
#if defined(CC_FCACHE_PKTCMF)
#define FLOW_HW_INVALID             CMF_TUPLE16_INVALID
#else
#define FLOW_HW_INVALID             0xFFFF  /* Hardware CMF not configured    */
#endif

#define FLOW_NF_INVALID             0x0

#define FLOW_IN_INVALID             0xFF    /* Incarnation 0xFF is invalid    */
#define FLOW_IX_INVALID             0       /* Element at index 0 reserved    */
#define FLOW_NULL                   ((Flow_t*)NULL)

#if defined(CC_FCACHE_PKTCMF)
/*
 *------------------------------------------------------------------------------
 *  Invoked by Packet CMF Protocol layer to clear HW association.
 *  Based on the scope of the request:
 *      System_e scope: Clear hw association for all active flows.
 *      Engine_e scope: Clear hw associations of flows on an engine.
 *      Match_e  scope: Clear a uniquely identified flow.
 *------------------------------------------------------------------------------
 */
typedef enum {
    System_e,       /* System wide active flows */
    Engine_e,       /* Upstream or downstream active flows */
    Match_e         /* Unique active flow of a specified match id */
} FlowScope_t;

typedef int ( *FC_CLEAR_HOOK)(uint32_t key, const FlowScope_t scope);

/*
 *------------------------------------------------------------------------------
 * Flow cache binding to Packet CMF to register CMF upcalls and downcalls
 * Upcalls from Flow cache to CMF: activate, deactivate and refresh functions.
 * Downcalls from CMF to Flow cache: clear hardware associations function.
 *------------------------------------------------------------------------------
 */
extern void fc_bind_cmf(HOOKP activate_fn, HOOK3PARM deactivate_fn,
                        HOOK3PARM refresh_fn, HOOK16 clear_fn,
                        FC_CLEAR_HOOK *fc_clear_fn);
#endif

/*
 *------------------------------------------------------------------------------
 * Defer activation of CMF Hardware. On every fcache_defer number of packets per
 * interval fcache will attempt to activate CMF. The interval is specified by
 * FCACHE_REFRESH_INTERVAL. To avoid a performance impact of repeated activation
 * attempts when CMF tables are depleted, a penalty is applied (factored into
 * fcache_defer. Bursty traffic will have the penalty reduced.
 *------------------------------------------------------------------------------
 */
extern int fcache_defer;
extern int fcacheDefer(int deferral);
extern int fcacheDebug(int debug_level);

/*
 *------------------------------------------------------------------------------
 * Manual enabling and disabling of Flow cache to Blog binding
 *  flag = 0 : disables binding to blog. No more logging.
 *  flag != 0: enables binding to blog via Flow cache receive/transmit.
 *------------------------------------------------------------------------------
 */
extern void fc_bind_blog(int flag);         /* disable[flag=0] enable[flag=1] */

/*
 *------------------------------------------------------------------------------
 * IP Flow learning status [defined by binding with blog]
 *------------------------------------------------------------------------------
 */
extern void fc_status(void);

/*
 *------------------------------------------------------------------------------
 * Flush all learnt entries in flow cache
 *------------------------------------------------------------------------------
 */
extern int  fc_flush(void);

/*
 *------------------------------------------------------------------------------
 * Flow Cache Entry Key:
 * A 32bit key that contains:
 *  - 16bit hardware connection id (encoding of CMF engine and matchIx)
 *  -  8bit incarnation id (avoid latent access)
 *  -  8bit entry id (index of entry in flow cache table)
 *------------------------------------------------------------------------------
 */
typedef struct {
    union {
        struct {
            uint32_t    hw      : 16;   /* uint16_t hardware connection id    */
            uint32_t    incarn  :  8;   /* Allocation instance identification */
            uint32_t    self    :  8;   /* Index into static allocation table */
        } id;
        uint32_t word;
    };
} FlowKey_t;

/*
 *------------------------------------------------------------------------------
 * Flow Cache Table Entry: 2-4 cache lines
 *------------------------------------------------------------------------------
 */
typedef struct flow_t {
    struct dll_t    node;       /* First element implements dll               */
    FlowKey_t       key;        /* Second element implements incarnation      */
    struct flow_t   * chain_p;  /* Single linked list hash table chaining     */

    Blog_t          * blog_p;   /* Buffer log carrying flow context data      */

    uint8_t         idle;       /* Idle quota in seconds before cache flush   */
    union {
        uint8_t         penalty;    /* Number of activates attempted          */
        uint8_t         list_depth; /* depth of jump_list (for multicast only)*/
    };

    uint16_t        swhits;     /* software lookup hits in last interval      */

    uint32_t        cumm_hits;  /* Cummulative sw hit count since creation    */
    uint32_t        cumm_bytes; /* Cummulative byte count since creation      */

    uint32_t        cumm_hw_hits; /* Cummulative sw hit count since creation  */
    uint32_t        cumm_hw_bytes; /* Cummulative byte count since creation   */

#if defined(CC_CONFIG_FCACHE_STACK)
                                /* Command sequence for packet mangling   */
    void            * jump_list[FCACHE_STACK_SIZE];
#endif
} Flow_t;

#else
#define     fc_bind_blog(enable)        NULL_STMT
#endif  /* defined(CONFIG_BCM_PKTFLOW_MODULE) || defined(CONFIG_BCM_PKTFLOW) */

#endif  /* defined(__FCACHE_H_INCLUDED__) */

