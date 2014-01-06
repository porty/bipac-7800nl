#ifndef __PKT_DBG_H_INCLUDED__
#define __PKT_DBG_H_INCLUDED__

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

#if defined( __KERNEL__ )
#define print               printk
#else
#define print               printf
#endif

/*
 *------------------------------------------------------------------------------
 * Color encodings for console printing:
 *
 * To enable  color coded console printing: #define COLOR(clr_code)  clr_code
 * To disable color coded console printing: #define COLOR(clr_code)
 *
 * You may select a color specific to your subsystem by:
 *  #define CLRsys CLRg
 *
 * Usage:  PKTPRINT(CLRr "format" CLRNL);
 *------------------------------------------------------------------------------
 */

#if !defined(COLOR)

#if defined(PKT_DBG_COLOR_SUPPORTED)
#define COLOR(clr_code)     clr_code
#else
#define COLOR(clr_code)
#endif

/* White background */
#define CLRr                COLOR("\e[0;31m")       /* red              */
#define CLRg                COLOR("\e[0;32m")       /* green            */
#define CLRy                COLOR("\e[0;33m")       /* yellow           */
#define CLRb                COLOR("\e[0;34m")       /* blue             */
#define CLRm                COLOR("\e[0;35m")       /* magenta          */
#define CLRc                COLOR("\e[0;36m")       /* cyan             */

/* blacK "inverted" background */
#define CLRrk               COLOR("\e[0;31;40m")    /* red     on blacK */
#define CLRgk               COLOR("\e[0;32;40m")    /* green   on blacK */
#define CLRyk               COLOR("\e[0;33;40m")    /* yellow  on blacK */
#define CLRmk               COLOR("\e[0;35;40m")    /* magenta on blacK */
#define CLRck               COLOR("\e[0;36;40m")    /* cyan    on blacK */
#define CLRwk               COLOR("\e[0;37;40m")    /* whilte  on blacK */

/* Colored background */
#define CLRcb               COLOR("\e[0;36;44m")    /* cyan    on blue  */
#define CLRyr               COLOR("\e[0;33;41m")    /* yellow  on red   */
#define CLRym               COLOR("\e[0;33;45m")    /* yellow  on magen */

/* Generic foreground colors */
#define CLRhigh             CLRm                    /* Highlight color  */
#define CLRbold             CLRcb                   /* Bold      color  */
#define CLRbold2            CLRym                   /* Bold2     color  */
#define CLRerr              CLRyr                   /* Error     color  */
#define CLRnorm             COLOR("\e[0m")          /* Normal    color  */
#define CLRnl               CLRnorm "\n"            /* Normal + newline */
#endif

/* Each subsystem may define CLRsys */


/*
 *------------------------------------------------------------------------------
 * Macros for generic debug and assert support per subsystem/layer.
 * - declare an int variable per subsystem scope: pktDbgLvl.
 * - define a constant string prefix: DBGsys
 *
 * - define: PKT_DBG_SUPPORTED
 * - define: PKT_ASSERT_SUPPORTED
 *------------------------------------------------------------------------------
 */
#if defined(PKT_DBG_SUPPORTED)
#define DBGCODE(code)       code
#else
#define DBGCODE(code)       NULL_STMT
#endif

/* Suggested debug levels and verbosity */
#define DBG_BASIC           0           /* Independent of pktDbgLvl */
#define DBG_STATE           1           /* Subsystem state change */
#define DBG_EXTIF           2           /* External interface */
#define DBG_INTIF           3           /* Internal interface */
#define DBG_CTLFL           4           /* Algorithm and control flow */
#define DBG_PDATA           5           /* Context, state and data dumps */
#define DBG_BKGRD           6           /* Background timers */

#define DBG(stmts)                                                          \
        DBGCODE( if ( pktDbgLvl ) do { stmts } while(0) )

#define DBGL(lvl, stmts)                                                    \
        DBGCODE( if ( pktDbgLvl >= lvl ) do { stmts } while(0) )

#define dbgl_func(lvl)                                                       \
        DBGCODE( if ( pktDbgLvl >= lvl )                                    \
                     print( CLRsys DBGsys " %-10s:" CLRnl, __FUNCTION__ ) )

#define dbg_print(fmt, arg...)                                              \
        DBGCODE( if ( pktDbgLvl )                                           \
                     print( CLRsys DBGsys fmt CLRnl, ##arg ) )

#define dbgl_print(lvl, fmt, arg...)                                        \
        DBGCODE( if ( pktDbgLvl >= lvl )                                    \
                     print( CLRsys DBGsys " %-10s:" fmt CLRnl,              \
                                          __FUNCTION__, ##arg ) )

#define dbg_error(fmt, arg...)                                              \
        DBGCODE( if ( pktDbgLvl )                                           \
                 print( CLRerr DBGsys " %-10s ERROR: " fmt CLRnl,           \
                                      __FUNCTION__,  ##arg ) )

#define dbg_config(lvl)                                                     \
        DBGCODE( pktDbgLvl = lvl;                                           \
                 print( CLRhigh DBGsys " pktDbgLvl[0x%08x]=%d" CLRnl,       \
                                       (int)&pktDbgLvl, pktDbgLvl ) )



#if defined(PKT_ASSERT_SUPPORTED)
#define ASSERTCODE(code)    code
#else
#define ASSERTCODE(code)    NULL_STMT
#endif

#define dbg_assertv(cond)                                                   \
        ASSERTCODE( if ( !cond )                                            \
                    {                                                       \
                        print( CLRerr DBGsys " %-10s ASSERT: "              \
                               #cond CLRnl, __FUNCTION__ );                 \
                        return;                                             \
                    } )

#define dbg_assertr(cond, rtn)                                              \
        ASSERTCODE( if ( !cond )                                            \
                    {                                                       \
                        print( CLRerr DBGsys " %-10s ASSERT: "              \
                               #cond CLRnl, __FUNCTION__ );                 \
                        return rtn;                                         \
                    } )


#endif  /* defined(__PKT_DBG_H_INCLUDED__) */

