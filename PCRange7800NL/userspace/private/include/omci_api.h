/***********************************************************************
 *
 *  Copyright (c) 2007  Broadcom Corporation
 *  All Rights Reserved
 *
# 
# 
# This program is the proprietary software of Broadcom Corporation and/or its 
# licensors, and may only be used, duplicated, modified or distributed pursuant 
# to the terms and conditions of a separate, written license agreement executed 
# between you and Broadcom (an "Authorized License").  Except as set forth in 
# an Authorized License, Broadcom grants no license (express or implied), right 
# to use, or waiver of any kind with respect to the Software, and Broadcom 
# expressly reserves all rights in and to the Software and all intellectual 
# property rights therein.  IF YOU HAVE NO AUTHORIZED LICENSE, THEN YOU HAVE 
# NO RIGHT TO USE THIS SOFTWARE IN ANY WAY, AND SHOULD IMMEDIATELY NOTIFY 
# BROADCOM AND DISCONTINUE ALL USE OF THE SOFTWARE. 
# 
# Except as expressly set forth in the Authorized License, 
# 
# 1. This program, including its structure, sequence and organization, 
#    constitutes the valuable trade secrets of Broadcom, and you shall use 
#    all reasonable efforts to protect the confidentiality thereof, and to 
#    use this information only in connection with your use of Broadcom 
#    integrated circuit products. 
# 
# 2. TO THE MAXIMUM EXTENT PERMITTED BY LAW, THE SOFTWARE IS PROVIDED "AS IS" 
#    AND WITH ALL FAULTS AND BROADCOM MAKES NO PROMISES, REPRESENTATIONS OR 
#    WARRANTIES, EITHER EXPRESS, IMPLIED, STATUTORY, OR OTHERWISE, WITH 
#    RESPECT TO THE SOFTWARE.  BROADCOM SPECIFICALLY DISCLAIMS ANY AND 
#    ALL IMPLIED WARRANTIES OF TITLE, MERCHANTABILITY, NONINFRINGEMENT, 
#    FITNESS FOR A PARTICULAR PURPOSE, LACK OF VIRUSES, ACCURACY OR 
#    COMPLETENESS, QUIET ENJOYMENT, QUIET POSSESSION OR CORRESPONDENCE 
#    TO DESCRIPTION. YOU ASSUME THE ENTIRE RISK ARISING OUT OF USE OR 
#    PERFORMANCE OF THE SOFTWARE. 
# 
# 3. TO THE MAXIMUM EXTENT PERMITTED BY LAW, IN NO EVENT SHALL BROADCOM OR 
#    ITS LICENSORS BE LIABLE FOR (i) CONSEQUENTIAL, INCIDENTAL, SPECIAL, 
#    INDIRECT, OR EXEMPLARY DAMAGES WHATSOEVER ARISING OUT OF OR IN ANY 
#    WAY RELATING TO YOUR USE OF OR INABILITY TO USE THE SOFTWARE EVEN 
#    IF BROADCOM HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES; 
#    OR (ii) ANY AMOUNT IN EXCESS OF THE AMOUNT ACTUALLY PAID FOR THE 
#    SOFTWARE ITSELF OR U.S. $1, WHICHEVER IS GREATER. THESE LIMITATIONS 
#    SHALL APPLY NOTWITHSTANDING ANY FAILURE OF ESSENTIAL PURPOSE OF ANY 
#    LIMITED REMEDY. 
#
 *
 ************************************************************************/

#ifndef _GPON_OMCI_API_H_
#define _GPON_OMCI_API_H_

#include "os_defs.h"


/*
 * Macros
 */
#if defined(OMCI_API_CMS)

#include "cms.h"
#include "cms_log.h"

#define ERROR(...)  cmsLog_error(__VA_ARGS__)
#define NOTICE(...) cmsLog_notice(__VA_ARGS__)
#define DEBUG(...)  cmsLog_debug(__VA_ARGS__)

#else

#define ERROR(fmt, arg...) \
    printf("\nomci_api:ERROR <%s,%d>: " fmt "\n", __FUNCTION__, __LINE__, ##arg)

#if defined(OMCI_API_NOTICE)
#define NOTICE(fmt, arg...) \
    printf("omci_api: " fmt "\n", ##arg)
#else
#define NOTICE(fmt, arg...)
#endif

#if defined(OMCI_API_DEBUG)
#define DEBUG(fmt, arg...) \
    printf("omci_api:DEBUG <%s,%d>: " fmt "\n", __FUNCTION__, __LINE__, ##arg)
#else
#define DEBUG(fmt, arg...)
#endif

#endif /* OMCI_API_CMS */

#ifdef GPON_LEGACY_API
#define BCMGPON_FILE "/dev/bcmgpon"
#else
#define BCMGPON_FILE "/dev/bcm_omci"
#endif   // GPON_LEGACY_API

#define OMCI_PACKET_HDR_SIZE     8  /* bytes */
#define OMCI_PACKET_MSG_SIZE     32 /* bytes */
#define OMCI_PACKET_TRAILER_SIZE 8  /* bytes */
#define OMCI_PACKET_SIZE         (OMCI_PACKET_HDR_SIZE + OMCI_PACKET_MSG_SIZE + \
                                  OMCI_PACKET_TRAILER_SIZE)

#define OMCI_PACKET_PRIORITY(p) ((p)->tcId >> 15)
#define OMCI_PACKET_TC_ID(p)    ((p)->tcId & 0x7FFF)
#define OMCI_PACKET_TC_ID_INIT  0x8000
#define OMCI_PACKET_DB(p)       ((p)->msgType & 0x80)
#define OMCI_PACKET_AR(p)       ((p)->msgType & 0x40)
#define OMCI_PACKET_AK(p)       ((p)->msgType & 0x20)
#define OMCI_PACKET_MT(p)       ((p)->msgType & 0x1F)
#define OMCI_PACKET_MT_MAX      32
#define OMCI_PACKET_DEV_ID      0x0A
#define OMCI_CHECK_DEV_ID(p)    ((p)->devId == OMCI_PACKET_DEV_ID)
#define OMCI_PACKET_ME_CLASS(p) (((p)->msgId & 0xFFFF0000) >> 16)
#define OMCI_PACKET_ME_INST(p)  ((p)->msgId & 0xFFFF)

#define OMCI_ME_CLASS_MAX       313 /* Table 18/G.984.4 Amd3 */

#define OMCI_MSG_TYPE_AR(c)       ((c) | 0x40)
#define OMCI_MSG_TYPE_AK(c)       ((c) | 0x20)


/*
 * enumerations
 */
typedef enum {
    OMCI_ACCESS_TYPE_BLOCKING,
    OMCI_ACCESS_TYPE_NONBLOCKING,
    OMCI_ACCESS_TYPE_MAX,
} omciAccessType;

typedef enum {
    OMCI_MSG_TYPE_CREATE = 4,
    OMCI_MSG_TYPE_CREATECOMPLETECONNECTION,
    OMCI_MSG_TYPE_DELETE,
    OMCI_MSG_TYPE_DELETECOMPLETECONNECTION,
    OMCI_MSG_TYPE_SET,
    OMCI_MSG_TYPE_GET,
    OMCI_MSG_TYPE_GETCOMPLETECONNECTION,
    OMCI_MSG_TYPE_GETALLALARMS,
    OMCI_MSG_TYPE_GETALLALARMSNEXT,
    OMCI_MSG_TYPE_MIBUPLOAD,
    OMCI_MSG_TYPE_MIBUPLOADNEXT,
    OMCI_MSG_TYPE_MIBRESET,
    OMCI_MSG_TYPE_ALARM,
    OMCI_MSG_TYPE_ATTRIBUTEVALUECHANGE,
    OMCI_MSG_TYPE_TEST,
    OMCI_MSG_TYPE_STARTSOFTWAREDOWNLOAD,
    OMCI_MSG_TYPE_DOWNLOADSECTION,
    OMCI_MSG_TYPE_ENDSOFTWAREDOWNLOAD,
    OMCI_MSG_TYPE_ACTIVATESOFTWARE,
    OMCI_MSG_TYPE_COMMITSOFTWARE,
    OMCI_MSG_TYPE_SYNCHRONIZETIME,
    OMCI_MSG_TYPE_REBOOT,
    OMCI_MSG_TYPE_GETNEXT,
    OMCI_MSG_TYPE_TESTRESULT,
    OMCI_MSG_TYPE_GETCURRENTDATA
} omciMsgType;

typedef enum {
    OMCI_MSG_RESULT_SUCCESS=0,
    OMCI_MSG_RESULT_PROC_ERROR,
    OMCI_MSG_RESULT_NOT_SUPPORTED,
    OMCI_MSG_RESULT_PARM_ERROR,
    OMCI_MSG_RESULT_UNKNOWN_ME,
    OMCI_MSG_RESULT_UNKNOWN_ME_INST,
    OMCI_MSG_RESULT_DEV_BUSY,
    OMCI_MSG_RESULT_ME_INST_EXISTS
} omciMsgResult;

typedef enum {
    OMCI_PACKET_PRIORITY_LOW=0,
    OMCI_PACKET_PRIORITY_HIGH,
    OMCI_PACKET_PRIORITY_MAX
} omciPacketPriority;


/*
 * structures
 */
struct omciPacket_struct {
    UINT16 tcId;
    UINT8  msgType;
    UINT8  devId;
    UINT32 msgId;
    UINT8  msg[OMCI_PACKET_MSG_SIZE];
    UINT8  trailer[OMCI_PACKET_TRAILER_SIZE];
} __attribute__ ((packed));

typedef struct omciPacket_struct omciPacket;


/*
 * function prototypes
 */
int gpon_omci_api_init(omciAccessType accessType);

void gpon_omci_api_exit(void);

void gpon_omci_api_get_handle(int *pHandle);

int gpon_omci_api_transmit(omciPacket *pPacket, int size);

int gpon_omci_api_receive(omciPacket *pPacket, int size);

#endif /* _GPON_OMCI_API_H_ */
