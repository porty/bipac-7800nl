/***********************************************************************
 *
 *  Copyright (c) 2006-2007  Broadcom Corporation
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

#ifndef __CMS_QOS_H
#define __CMS_QOS_H

/*!\file cms_qos.h
 * \brief Header file for the QoS portion of the CMS Data Abstration Layer API.
 *   This is in the cms_dal library.  Also includes some QoS definitions.
 */



/********************** Include Files ***************************************/
#include "cms_core.h"

/********************** Global Types ****************************************/


#define QOS_LEVELS               8
#define ETH_QOS_LEVELS           4
#define WLAN_QOS_LEVELS          8

#define MAX_QOS_LEVELS           8

#ifdef BRCM_WLAN
#define WIRELESS_PREDEFINE_QUEUE 8
#else
#define WIRELESS_PREDEFINE_QUEUE 0
#endif

#if defined(CHIP_6368) || defined(CHIP_6362) || defined(CHIP_6328)
#define MAX_ATM_TRANSMIT_QUEUES  16
#else
#define MAX_ATM_TRANSMIT_QUEUES  8
#endif
#define MAX_PTM_TRANSMIT_QUEUES  8

//#define MAX_QOS_QUEUE_ENTRY   (MAX_ATM_TRANSMIT_QUEUES + WIRELESS_PREDEFINE_QUEUE)  //max QoS Queue entries.
#define QOS_CLS_MAX_ENTRY     32    //max QoS Classification rules

#define WIRELESS_QUEUE_INTF      "wireless"

#define QOS_CRITERION_UNUSED        -1
#define QOS_RESULT_NO_CHANGE        -1
#define QOS_RESULT_AUTO_MARK        -2


#define DHCP_VENDOR_CLASS_OPTION    60
#define DHCP_USER_CLASS_OPTION      77


//#define DSCP_NONE                 -1
#define DSCP_AUTO                 -2
#define DSCP_DEFAULT              0x00
#define DSCP_AF13                 0x38
#define DSCP_AF12                 0x30
#define DSCP_AF11                 0x28
#define DSCP_CS1                  0x20
#define DSCP_AF23                 0x58
#define DSCP_AF22                 0x50
#define DSCP_AF21                 0x48
#define DSCP_CS2                  0x40
#define DSCP_AF33                 0x78
#define DSCP_AF32                 0x70
#define DSCP_AF31                 0x68
#define DSCP_CS3                  0x60
#define DSCP_AF43                 0x98
#define DSCP_AF42                 0x90
#define DSCP_AF41                 0x88
#define DSCP_CS4                  0x80
#define DSCP_EF                   0xB8
#define DSCP_CS5                  0xA0
#define DSCP_CS6                  0xC0
#define DSCP_CS7                  0xE0
#define DSCP_MASK                 0xFC


#define MAX_SEND_SIZE 256

typedef struct optionmsgbuf
{
   SINT32   mtype;
   char     mtext[MAX_SEND_SIZE];
} QosDhcpOptionMsgBuf;


/** This function adds a QoS classification object instance.
 *
 * @param clsObj     (IN) pointer to the QoS classification object to be added.
 * @return CmsRet         enum.
 */
CmsRet dalQos_classAdd(const QMgmtClassificationObject *clsObj);

/** This function deletes the QoS classification object instance.
 *
 * @param iidStack   (IN) instance id stack of the classification object.
 * @param clsObj     (IN) pointer to the QoS classification object to be deleted.
 * @return CmsRet         enum.
 */
CmsRet dalQos_classDelete(const InstanceIdStack *iidStack, const QMgmtClassificationObject *clsObj);

/** This function adds a QoS queue object instance.
 *
 * @param queueObj   (IN) pointer to the QoS queue object to be added.
 * @return CmsRet         enum.
 */
CmsRet dalQos_queueAdd(const QMgmtQueueObject *queueObj);

/** This function deletes the QoS queue object instance.
 *
 * @param iidStack   (IN) instance id stack of the queue object.
 * @param queueObj   (IN) pointer to the QoS queue object to be deleted.
 * @return CmsRet         enum.
 */
CmsRet dalQos_queueDelete(const InstanceIdStack *iidStack, const QMgmtQueueObject *queueObj);

/** This function adds a QoS queue object instance.
 *
 * @param queueObj   (IN) pointer to the QoS queue object to be added.
 * @return CmsRet         enum.
 */
CmsRet dalQos_defaultQueueAdd(char *intf, char *schedulerAlg, UINT32 weight, UINT32 precedence);

/** This function returns an unused queue ID for the layer2 interface.
 *
 * @param l2Ifname (IN)  layer2 interface name for the queue.
 * @param qId      (OUT) unused queue ID
 * @return CmsRet         enum.
 */
CmsRet dalQos_getAvailableQueueId(const char *l2Ifname, UINT32 *qId);

/** This function returns an unused class key.
 *
 * @param clsKey      (OUT) unused class key
 * @return CmsRet         enum.
 */
CmsRet dalQos_getAvailableClsKey(UINT32 *clsKey);

/** This function enables/disables the default queues associated with the wireless interface.
 * This function will acquire the cms lock before accessing mdm, and release it before return.
 *
 * @param ifname   (IN) wireless interface name.
 * @param enabled  (IN) boolean to enable or disable the default queues.
 * @return CmsRet       enum.
 */
CmsRet rutQos_setDefaultWlQueuesLock(char *ifname, UBOOL8 enabled);

#endif   /* __CMS_QOS_H */
