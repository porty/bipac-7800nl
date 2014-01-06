#ifndef __FAP4KE_MAILBOX_H_INCLUDED__
#define __FAP4KE_MAILBOX_H_INCLUDED__

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
 * File Name  : fap4ke_MailBox.h
 *
 * Description: This file contains global definitions and API of the 6362 FAP
 *              Message FIFOs.
 *
 *******************************************************************************
 */

#include <stdarg.h>

#define FAP_MAILBOX_PRINTBUF_SIZE 2048 /* bytes */

typedef enum {
    FAP_MAILBOX_MSGID_SUCCESS,
    FAP_MAILBOX_MSGID_ERROR,
    FAP_MAILBOX_MSGID_PRINT,
    FAP_MAILBOX_MSGID_LOG_ASSERT,
    FAP_MAILBOX_MSGID_LOG_ERROR,
    FAP_MAILBOX_MSGID_LOG_NOTICE,
    FAP_MAILBOX_MSGID_LOG_INFO,
    FAP_MAILBOX_MSGID_LOG_DEBUG,
    FAP_MAILBOX_MSGID_KEEPALIVE,
    FAP_MAILBOX_MSGID_WORD_HI,
    FAP_MAILBOX_MSGID_WORD_LO,
    FAP_MAILBOX_MSGID_MAX
} fapMailBox_msgId_t;

typedef union {
    struct {
        uint32 msgId : 16;
        uint32 data  : 16;
    } __attribute__((packed));
    uint32 u32;
} fapMailBox_msg_t;


/*******************************************************************
 * FAP API
 *******************************************************************/

extern char fapMailBox_printBuffer[FAP_MAILBOX_PRINTBUF_SIZE];

/* #define fapMailBox_4kePrint(_msgId, fmt, arg...)                        \ */
/*     do {                                                                \ */
/*         uint32 _flags;                                                  \ */
/*         fapMailBox_msg_t _msg;                                          \ */
/*         FAP4KE_LOCK(_flags);                                            \ */
/*         fap4ke_snprintf(fapMailBox_printBuffer, FAP_MAILBOX_PRINTBUF_SIZE, \ */
/*                         fmt, ##arg);                                    \ */
/*         _msg.msgId = (_msgId);                                          \ */
/*         _msg.data = ++fapMailBox_4kePrintCount;                         \ */
/*         fapToHost_xmitAndWaitForAck(_msg);                              \ */
/*         FAP4KE_UNLOCK(_flags);                                          \ */
/*     } while(0) */

void fapMailBox_4kePrint(fapMailBox_msgId_t msgId, const char *templat, ...);
void fapMailBox_4kePrintk(const char *templat, ...);
void fapMailBox_4keSendKeepAlive(void);
void fapMailBox_4keSendWord(uint32 val32);
void fapMailBox_4keInit(void);

#endif  /* defined(__FAP4KE_MAILBOX_H_INCLUDED__) */
