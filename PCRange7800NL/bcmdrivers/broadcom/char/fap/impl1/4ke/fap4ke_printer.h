#ifndef __FAP4KE_PRINTER_H_INCLUDED__
#define __FAP4KE_PRINTER_H_INCLUDED__

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
 * File Name  : fap4ke_printer.h
 *
 * Description: This file contains the implementation of the FAP print support.
 *
 *******************************************************************************
 */

#include "fap4keLib_snprintf.h"

#define CC_FAP4KE_PRINT_DEBUG
#define CC_FAP4KE_PRINT_INFO
#define CC_FAP4KE_PRINT_NOTICE
#define CC_FAP4KE_PRINT_ERROR

#define FAP4KE_COLOR_SUPPORTED

#if defined(FAP4KE_COLOR_SUPPORTED)
#define FAP4KE_COLOR(clr_code)     clr_code
#else
#define FAP4KE_COLOR(clr_code)
#endif

#ifndef _BCM_LOG_SERVICES_
/* White background */
#define CLRr                FAP4KE_COLOR("\e[0;31m")       /* red              */
#define CLRg                FAP4KE_COLOR("\e[0;32m")       /* green            */
#define CLRy                FAP4KE_COLOR("\e[0;33m")       /* yellow           */
#define CLRb                FAP4KE_COLOR("\e[0;34m")       /* blue             */
#define CLRm                FAP4KE_COLOR("\e[0;35m")       /* magenta          */
#define CLRc                FAP4KE_COLOR("\e[0;36m")       /* cyan             */

/* blacK "inverted" background */
#define CLRrk               FAP4KE_COLOR("\e[0;31;40m")    /* red     on blacK */
#define CLRgk               FAP4KE_COLOR("\e[0;32;40m")    /* green   on blacK */
#define CLRyk               FAP4KE_COLOR("\e[0;33;40m")    /* yellow  on blacK */
#define CLRmk               FAP4KE_COLOR("\e[0;35;40m")    /* magenta on blacK */
#define CLRck               FAP4KE_COLOR("\e[0;36;40m")    /* cyan    on blacK */
#define CLRwk               FAP4KE_COLOR("\e[0;37;40m")    /* white   on blacK */

/* Colored background */
#define CLRcb               FAP4KE_COLOR("\e[0;36;44m")    /* cyan    on blue  */
#define CLRyr               FAP4KE_COLOR("\e[0;33;41m")    /* yellow  on red   */
#define CLRym               FAP4KE_COLOR("\e[0;33;45m")    /* yellow  on magen */

/* Generic foreground colors */
#define CLRhigh             CLRm                    /* Highlight color  */
#define CLRbold             CLRcb                   /* Bold      color  */
#define CLRbold2            CLRym                   /* Bold2     color  */
#define CLRerr              CLRyr                   /* Error     color  */
#define CLRnorm             FAP4KE_COLOR("\e[0m")   /* Normal    color  */
#define CLRnl               CLRnorm "\n"            /* Normal + newline */
#endif

#define fap4kePrt_Print(fmt, arg...)                            \
    fapMailBox_4kePrint(FAP_MAILBOX_MSGID_PRINT, fmt, ##arg)

#if defined(CC_FAP4KE_PRINT_DEBUG)
#define fap4kePrt_Debug(fmt, arg...)                                  \
    fapMailBox_4kePrint(FAP_MAILBOX_MSGID_LOG_DEBUG, CLRm "%s: " fmt CLRnorm, __FUNCTION__, ##arg)
#else
#define fap4kePrt_Debug(fmt, arg...)
#endif

#if defined(CC_FAP4KE_PRINT_INFO)
#define fap4kePrt_Info(fmt, arg...)                                   \
    fapMailBox_4kePrint(FAP_MAILBOX_MSGID_LOG_INFO, CLRg "%s: " fmt CLRnorm, __FUNCTION__, ##arg)
#else
#define fap4kePrt_Info(fmt, arg...)
#endif

#if defined(CC_FAP4KE_PRINT_NOTICE)
#define fap4kePrt_Notice(fmt, arg...)                                 \
    fapMailBox_4kePrint(FAP_MAILBOX_MSGID_LOG_NOTICE, CLRb "%s: " fmt CLRnorm, __FUNCTION__, ##arg)
#else
#define fap4kePrt_Notice(fmt, arg...)
#endif

#if defined(CC_FAP4KE_PRINT_ERROR)
#define fap4kePrt_Error(fmt, arg...)                                  \
    fapMailBox_4kePrint(FAP_MAILBOX_MSGID_LOG_ERROR, CLRerr "%s,%d: " fmt CLRnorm, __FUNCTION__, __LINE__, ##arg)
#else
#define fap4kePrt_Error(fmt, arg...)
#endif

#define fap4kePrt_Assert(_condition)                                    \
    do {                                                                \
        if(!(_condition)) {                                             \
            fapMailBox_4kePrint(FAP_MAILBOX_MSGID_LOG_ASSERT, CLRerr "%s,%s,%d: " #_condition CLRnl, \
                                __FILE__, __FUNCTION__, __LINE__);      \
        }                                                               \
    } while(0)

#endif  /* defined(__FAP4KE_PRINTER_H_INCLUDED__) */
