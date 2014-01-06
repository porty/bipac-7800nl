#ifndef __PKT_FCCTL_API_H_INCLUDED__
#define __PKT_FCCTL_API_H_INCLUDED__

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
/***************************************************************************
 * File Name  : fcctl_api.h
 * Description: APIs for library that controls the Broadcom Flow Cache.
 ***************************************************************************/

#include <fcache.h>

/*
 *------------------------------------------------------------------------------
 * Function Name: fcCtlStatus
 * Description  : Displays flow cache status.
 * Returns      : 0 - success, non-0 - error
 *------------------------------------------------------------------------------
 */
int fcCtlStatus(void);

/*
 *------------------------------------------------------------------------------
 * Function Name: fcCtlEnable
 * Description  : Enables flow cache.
 * Returns      : 0 - success, non-0 - error
 *------------------------------------------------------------------------------
 */
int fcCtlEnable(void);

/*
 *------------------------------------------------------------------------------
 * Function Name: fcCtlDisable
 * Description  : Disables flow cache.
 * Returns      : 0 - success, non-0 - error
 *------------------------------------------------------------------------------
 */
int fcCtlDisable(void);

/*
 *------------------------------------------------------------------------------
 * Function Name: fcCtlFlush
 * Description  : Flushes all flows in flow cache.
 * Returns      : 0 - success, non-0 - error
 *------------------------------------------------------------------------------
 */
int fcCtlFlush(void);


#if defined(PKTCMF_AVAIL)
#define FCACHE_CONFIG_OPT_DEFER     0       /* Set pkt deferral rate value  */
#define FCACHE_CONFIG_OPT_MONITOR   1       /* Monitor idle activates?      */
#endif
#define FCACHE_CONFIG_OPT_MCAST     2       /* Mcast enable/disable         */
#define FCACHE_CONFIG_OPT_TIMER     3       /* Flow Timer values            */
#define FCACHE_CONFIG_OPT_MAX       4       

/*
 *------------------------------------------------------------------------------
 * Function Name: fcCtlConfig
 * Description  : Configures the flow cache parameters.
 * Parameters   :
 *       option : one of the option to be configured.
 *         arg1 : parameter value
 * Returns      : 0 - success, non-0 - error
 *------------------------------------------------------------------------------
 */
int fcCtlConfig(int option, int arg1 );


#if defined(CC_FCACHE_DEBUG)
/*
 *------------------------------------------------------------------------------
 * Function Name: fcCtlDebug
 * Description  : Sets the debug level for the layer in flow cache.
 * Returns      : 0 - success, non-0 - error
 *------------------------------------------------------------------------------
 */
int  fcCtlDebug(int layer, int level);
#endif

#endif  /* defined(__PKT_FCCTL_API_H_INCLUDED__) */

