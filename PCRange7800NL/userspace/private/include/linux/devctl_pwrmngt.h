/***********************************************************************
//
//  Copyright (c) 2008  Broadcom Corporation
//  All Rights Reserved
//  No portions of this material may be reproduced in any form without the
//  written permission of:
//          Broadcom Corporation
//          5300 California Avenue 
//          Irvine, California 92617 
//  All information contained in this document is Broadcom Corporation
//  company private, proprietary, and trade secret.
//
************************************************************************/
#ifndef __DEVCTL_PWRMNGT_H__
#define __DEVCTL_PWRMNGT_H__


/*!\file devctl_pwrmngt.h
 * \brief Header file for the user mode PwrMngt device control library API.
 *  This is in the devCtl library.
 *
 * These API are called by user applications to perform PwrMngt driver operations.
 * These API make Linux ioctl calls to PwrMngt driver. 
 *
 */

#include "cms.h"
#include "bcmpwrmngtcfg.h"

/**Initializes PwrMngt driver
 *
 * This function is called to initialize the PwrMngt driver with init time
 * configuration parameters.
 *
 * @param pInitParms (IN)  A pointer to init buffer.
 * 
 * @return CmsRet enum.
 */
CmsRet PwrMngtCtl_Initialize(PPWRMNGT_CONFIG_PARAMS pInitParms);

/**Uninitializes PwrMngt driver
 *
 * This function is called to uninitialize PwrMngt driver and free resources
 * allocated during initialization.
 *
 * @return CmsRet enum.
 */
CmsRet PwrMngtCtl_Uninitialize(void);

/**Get Config from PwrMngt driver
 *
 * This function is called to initialize the PwrMngt driver with init time
 * configuration parameters.
 *
 * @param pInitParms (IN/OUT)  A pointer to conf buffer.
 * @param pInitParms (IN)  A conf param mask.
 * 
 * @return CmsRet enum.
 */
CmsRet PwrMngtCtl_GetConfig(
    PPWRMNGT_CONFIG_PARAMS pCfgParams, UINT32 configMask);

/**Set Config for PwrMngt driver
 *
 * This function is called to initialize the PwrMngt driver with init time
 * configuration parameters.
 *
 * @param pInitParms (IN/OUT)  A pointer to conf buffer.
 * @param pInitParms (IN)  A conf param mask.
 * 
 * @return CmsRet enum.
 */
CmsRet PwrMngtCtl_SetConfig(
    PPWRMNGT_CONFIG_PARAMS pCfgParams, UINT32 configMask, void *msgHandle);
#endif /* __DEVCTL_PwrMngt_H__ */
