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

#ifndef __DAL_WAN_H__
#define __DAL_WAN_H__


/*!\file dal_wan.h
 * \brief Header file for the WAN portion of the CMS Data Abstration Layer API.
 *  This is in the cms_dal library.
 */


/** add a wan interface.
 *
 * @param webVar (IN) structure containing the necessary info to add
 *                    a wan interface.
 *
 * @return CmsRet enum.
 */
CmsRet dalWan_addInterface(const WEB_NTWK_VAR *webVar);


/** delete a wan interface.
 *
 * @param webVar (IN) structure containing the necessary info to delete
 *                    a wan interface.
 *
 * @return CmsRet enum.
 */
CmsRet dalWan_deleteInterface(const WEB_NTWK_VAR *webVar);


/** edit a wan interface.
 *
 * @param webVar (IN) structure containing the necessary info to edit
 *                    a wan interface.
 *
 * @return CmsRet enum.
 */
CmsRet dalWan_editInterface(const WEB_NTWK_VAR *webVar);


/** This function finds out if the wan layer 2 link is up or for the WanIP/PPPConnObject.
 *
 * @param wanConnOid (IN) oid is either MDMOID_WAN_PPP_CONN or MDMOID_WAN_IP_CONN
 * @param iidStack   (IN) iidStack of the WanIP/PPPConnObject.  This iidStack is
 *                        used to find the ancestor WanLinkCfg object *
 * @return UBOOL8
 */
UBOOL8 dalWan_isWanLayer2LinkUp(MdmObjectId wanConnOid, const InstanceIdStack *iidStack);


/** Get the (layer 2) Wan Ethernet InterfaceConfig object.
 *
 * @param iidStack (OUT) The iidStack of the requested object.
 * @param wanEthIntfObj (OUT) The requested object.
 *
 * @return CmsRet enum.
 */
CmsRet dalWan_getWanEthObject(InstanceIdStack *iidStack,
                              WanEthIntfObject **wanEthIntfObj);


/** Get the (layer 2) Wan Moca InterfaceConfig object.
 *
 * @param iidStack (OUT) The iidStack of the requested object.
 * @param wanMocaIntfObj (OUT) The requested object.
 *
 * @return CmsRet enum.
 */
CmsRet dalWan_getWanMocaObject(InstanceIdStack *iidStack,
                               WanMocaIntfObject **wanMocaIntfObj);


/** Get the WAN L2tpAc InterfaceConfig object.
 *
 * @param iidStack (OUT) The iidStack of the requested object.
 * @param L2tpAcIntfConfigObject (OUT) The requested object.
 *
 * @return CmsRet enum.
 */
CmsRet dalWan_getWanL2tpAcObject(InstanceIdStack *iidStack,
                                 L2tpAcIntfConfigObject **wanL2tpAcIntfObj);

/** Get various adsl flags.
 *
 * @param adslFlags (OUT) contains the various adsl flags.
 *
 * @return CmsRet enum.
 */
CmsRet dalWan_getAdslFlags(UINT32 *adslFlags);


/** Set various adsl flags.
 *
 * @param adslFlags (IN) contains the various adsl flags.
 *
 * @return CmsRet enum.
 */
CmsRet dalWan_setAdslFlags(UINT32 adslFlags);


/** Get current number of used Pvc information.
 *
 * @return number of PVCs currently defined on the modem.
 */
UINT32 dalWan_getNumberOfUsedPvc(void);


/** Call appropriate cmsObj_getNext function to check if all pvc are bridge protocol
 *
 * @return TRUE - all pvcs are bridges,  FALSE =  found the no bridge pvc.
 */
UBOOL8 dalWan_isAllBridgePvcs(void);

/** return string "Bridge" in allBridge if all pvc are bridge for lancfg2.html
 *
 * @param brName (IN) The interface group name (BridgeName in LanDevice object).
 * @param allBridge (OUT) If all PVC's are bridge, then this char buffer
 *                        will be filled with the string "Bridge".
 */
void dalWan_allBridgePrtcl(const char *brName, char *allBridge);


/** check if there exists bridged Wan
 *
 */
UBOOL8 dal_isBridgedWanExisted(void);


/** Return the first non-bridge protocol in the system.
 *  If there are only bridge wan connections in the system, return CMS_WAN_TYPE_BRIDGE.
 *  If there are no wan connections of any type, return CMS_WAN_TYPE_UNDEFINED.
 * 
 * @return a CmsWanConnectionType enum.
 */
CmsWanConnectionType dalWan_getNoBridgeNtwkPrtcl(void);

/** Return true if any WAN interface has firewall enabled.
 * 
 * @return TRUE if any wan interface has firewall enabled.
 */
UBOOL8 dalWan_isAnyFirewallEnabled(void);

/** Return true if the WAN interface is vlanmux enabled.
 * 
 * @return TRUE if the wan interface is vlanmux enabled.
 */
UBOOL8 dalWan_isInterfaceVlanEnabled(const char *ifcName);


/* functions defined in dal_wan.c */
UBOOL8 dalWan_getDslLinkCfg(const WEB_NTWK_VAR *webVar, InstanceIdStack *iidStack,
                            WanDslLinkCfgObject **dslLinkCfg);
UBOOL8 dalWan_getIpConn(const WEB_NTWK_VAR *webVar, InstanceIdStack *iidStack,
                        WanIpConnObject **ipConn);
UBOOL8 dalWan_getPppConn(const WEB_NTWK_VAR *webVar, InstanceIdStack *iidStack,
                         WanPppConnObject **pppConn);
UBOOL8 delWan_getAnotherIpConn(SINT32 connIdExcluded, InstanceIdStack *parentIidStack,
                               InstanceIdStack *iidStack, WanIpConnObject **ipConn);
UBOOL8 delWan_getAnotherPppConn(SINT32 connIdExcluded, InstanceIdStack *parentIidStack,
                                InstanceIdStack *iidStack, WanPppConnObject **pppConn);

/** Get the vlanMuxEnable value of a PVC.
 */

/**  Get the wan protocol from IpConn object
 */
SINT32 cmsDal_getWANProtocolFromIpConn(_WanDslLinkCfgObject *dslLinkCfg, _WanIpConnObject *ipConn);

/**  Get the wan protocol from PppConn object
 */
SINT32 cmsDal_getWANProtocolFromPppConn(_WanDslLinkCfgObject *dslLinkCfg);

/** Get protocol in short string format used by httpd
 */
void cmsDal_getWanProtocolName(UINT8 protocol, char *name);

/** Fill webVar from MDM  for edit purpose
  */
CmsRet  dalWan_getWanConInfoForEdit(PWEB_NTWK_VAR webVar) ;
                         
/** Get next ppp device name.  Use the rutWan_fillPppIfName.
 * 
 * @param isPPPoE (IN)  TRUE == PPPoE. FALSE == PPPoA
 * @param pppName (OUT) The next ppp name.
 *
 * @return CmsRet enum.
 */
CmsRet  dalWan_fillPppIfName(UBOOL8 isPPPoE, char *pppName);


/** This function finds out if the WanIPConnObject is a IPoA and it calls rutWl2_isIPoA in
 * rut_wanlayer2.c
 *
 * @param iidStack (IN) iidStack of the WanIPConnObject.  This iidStack is
 *                  used to find the ancestor WanDslLinkCfg object what the linkType is
 *
 * @return UBOOL8 FALSE if it is not ATM or the link or linkeType is EOA (IPoE and Bridge)
 */
UBOOL8 dalWan_isIPoA(const InstanceIdStack *iidStack);


/** This function finds out if the WanPppConnObject is either  PPPoA or PPPoE it calls rutWl2_isPPPoA
 * in rut_wanlayer2.c
 *
 * @param iidStack (IN) iidStack of the WanPppConnObject.  This iidStack is
 *                  used to find the ancestor WanDslLinkCfg object what the linkType is
 *
 * @return UBOOL8 FALSE if it is not ATM or the link or linkeType is EOA (PPPoE)
 */
UBOOL8 dalWan_isPPPoA(const InstanceIdStack *iidStack);

/** This function finds calls rutWl2_isVlanMuxEnabled in 
 * in rut_wanlayer2.c to find out if the vlanMux is enabled  for the WanIP/PPPConnObject
 *
 * @param wanConnOid (IN) oid is either MDMOID_WAN_PPP_CONN or MDMOID_WAN_IP_CONN
 * @param iidStack   (IN) iidStack of the WanIP/PPPConnObject.  This iidStack is
 *                        used to find the ancestor layer 2 object *
 * @return UBOOL8
 */
UBOOL8 dalWan_isVlanMuxEnabled(MdmObjectId wanConnOid, const InstanceIdStack *iidStack);


/** This function finds out if the WanConn object is EoA interface or not. 
 *
 * @param iidStack (IN) iidStack of the WanIp/PppConnObject.  This iidStack is
 *                  used to find the ancestor WanDslLinkCfg object what the linkType is
 *
 * @return UBOOL8 FALSE if it is not ATM or the link or linkeType is EOA 
 */
UBOOL8 dalWan_isEoAInterface(const InstanceIdStack *iidStack);

#ifdef BILLION_WEB // sarah add, 20100311
void dalWan_actIp_PppConnection (char *cL2Ifc, UBOOL8 doStart);
CmsRet dalWan_bnGetWanFromL2Ifc (char *l2Ifc, char *pWanAccessType);
#endif // BILLION_WEB

#endif  /* __DAL_WAN_H__ */
