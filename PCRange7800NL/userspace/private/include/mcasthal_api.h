#ifndef _MCAST_HAL_API_H_
#define _MCAST_HAL_API_H_
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

/*******************************************************************************
 * File Name  : mcasthal_api.h
 *
 * Description: This file contains mcast IGMP snooping API proto types for HAL
 *
 ******************************************************************************/
#include <sys/socket.h>
#include <netinet/in.h>
#include <linux/if.h>

typedef struct mcast_hal_snoop_entry 
{
   char                      br_name[IFNAMSIZ]; /* bridge interface name */
   int                       port_no;      /* port number of bridge interface */
   struct                    in_addr grp;  /* mcast group address */
   struct                    in_addr src;  /* mcast source address */
   struct                    in_addr rep;  /* mcast receiver/client address */
   int                       filter_mode;  /* filter mode: MCAST_EXCLUDE or 
                                                       MCAST_INCLUDE from in.h */
} MCAST_HAL_SNOOP_ENTRY_t;

/******************************************************************************
 *
 * Function: mcastHal_addFlow 
 *                                                                             
 * Description: API to add a igmp snooping flow in the HAL/hardware 
 *
 * INPUT  -  *snp_entry MCAST_HAL_SNOOP_ENTRY_t entry
 *
 * Returns -1 on error 0 on success
 *
 ******************************************************************************/
int mcastHal_addFlow(MCAST_HAL_SNOOP_ENTRY_t *snp_entry);

 
/******************************************************************************
 *
 * Function: mcastHal_deleleFlow
 *                                                                             
 * Description: API to remove a igmp snooping flow in the HAL/hardware 
 *
 * INPUT  -  *snp_entry MCAST_HAL_SNOOP_ENTRY_t entry
 *
 * Returns -1 on error 0 on success
 ******************************************************************************/
int mcastHal_deleleFlow(MCAST_HAL_SNOOP_ENTRY_t *snp_entry);


#endif /* _MCAST_HAL_API_H_*/
