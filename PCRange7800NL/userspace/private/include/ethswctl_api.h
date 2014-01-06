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

#ifndef _ETHSWCTL_API_H_
#define _ETHSWCTL_API_H_

#include <bcmnet.h>
#include <bcm/bcmswapitypes.h>
#include <bcm/bcmswapistat.h>

#ifdef ETHSWCTL_DEBUG
#define DBG( body ) do { body } while(0);
#else
//#define DBG( body ) do { body } while(0);
#define DBG( body )
#endif

/* define used to identify communication with external chip configured as SPI slave device */
#define BCM_EXT_6829 0x80

/****************************************************************************/
/* Enable Hardware Switching                                                */
/* Returns: 0 on success; a negative value on failure                       */
/****************************************************************************/
int ethswctl_enable_switching(void);

/****************************************************************************/
/* Disable Hardware Switching                                               */
/* Returns: 0 on success; a negative value on failure                       */
/****************************************************************************/
int ethswctl_disable_switching(void);

/****************************************************************************/
/* Get Hardware Switching Enable/Disable Status                             */
/* Returns status(0=Disable;1=Enable) on success; negative value on failure */
/****************************************************************************/
int ethswctl_get_switching_status(void);

/****************************************************************************/
/* dumps the registers of a given page                                      */
/* Returns: 0 on success; a negative value on failure                       */
/****************************************************************************/
int ethswctl_pagedump(int page);

/****************************************************************************/
/* dumps the mib counters of a given port                                   */
/* type = 0 to dump a subset of MIB counters. type = 1 to dump all counters */
/* Returns: 0 on success; a negative value on failure                       */
/****************************************************************************/
int ethswctl_mibdump(int port, int type);


/****************************************************************************/
/*  Switch Control API for Buffer Management                                                                   */
/****************************************************************************/

/*
 * Function:
 *  bcm_switch_control_set
 * Description:
 *  Set Flow Control Drop/Pause Control mechanisms of the switch.
 *  unit - RoboSwitch PCI device unit number (driver internal).
 *    type - The desired configuration parameter to modify.
 *    arg - The value with which to set the parameter.
 * Returns:
 *    BCM_E_xxxx
 */
int bcm_switch_control_set(int unit, bcm_switch_control_t type, int arg);


/*
 * Function:
 *  bcm_switch_control_get
 * Description:
 *  Get Flow Control Drop/Pause Control mechanisms of the switch.
 * Parameters:
 *  unit - RoboSwitch PCI device unit number (driver internal).
 *    type - The desired configuration parameter to retrieve.
 *    arg - Pointer to where the retrieved value will be written.
 * Returns:
 *    BCM_E_xxxx
 */
int bcm_switch_control_get(int unit, bcm_switch_control_t type, int *arg);


/*
 * Function:
 *  bcm_switch_control_priority_set
 * Description:
 *  Set switch parameters on a per-priority (cos) basis.
 * Parameters:
 *  unit - Device unit number
 *  priority - The priority to affect
 *  type - The desired configuration parameter to modify
 *  arg - The value with which to set the parameter
 * Returns:
 *  BCM_E_xxx
 */
int bcm_switch_control_priority_set(int unit, bcm_cos_t priority,
                bcm_switch_control_t type, int arg);


/*
 * Function:
 *  bcm_switch_control_priority_get
 * Description:
 *  Get switch parameters on a per-priority (cos) basis.
 * Parameters:
 *  unit - Device unit number
 *  priority - The priority to affect
 *  type - The desired configuration parameter to retrieve
 *  arg - Pointer to where the retrieved value will be written
 * Returns:
 *  BCM_E_xxx
 */
int bcm_switch_control_priority_get(int unit, bcm_cos_t priority,
                bcm_switch_control_t type, int *arg);



/****************************************************************************/
/* Port Configuration API: For Configuring Egress Tag Replacement Registers */
/****************************************************************************/

/* Set the replacement VLAN tag */
int bcm_port_replace_tag_set(int unit, bcm_port_t port, unsigned int vlan_tag);

/* Retrieve the replacement VLAN tag */
int bcm_port_replace_tag_get(int unit, bcm_port_t port, unsigned int *vlan_tag);

/* Set the replacement TPID */
int bcm_port_replace_tpid_set(int unit, bcm_port_t port, unsigned short tpid);

/* Retrieve the replacement TPID */
int bcm_port_replace_tpid_get(int unit, bcm_port_t port, unsigned short *tpid);

/* Set the replacement TCI (802.1p+CFI+VID) */
int bcm_port_replace_tci_set(int unit, bcm_port_t port, bcm_vlan_t vid);

/* Retrieve the replacement TCI (802.1p+CFI+VID) */
int bcm_port_replace_tci_get(int unit, bcm_port_t port, bcm_vlan_t *vid);

/* Set the replacement VLAN ID */
int bcm_port_replace_vid_set(int unit, bcm_port_t port, bcm_vlan_t vid);

/* Retrieve the replacement VLAN ID */
int bcm_port_replace_vid_get(int unit,  bcm_port_t port, bcm_vlan_t *vid);

/* Set the replacement 802.1p bits */
int bcm_port_replace_8021p_set(int unit, bcm_port_t port, char priority);

/* Retrieve the replacement 802.1p bits */
int bcm_port_replace_8021p_get(int unit, bcm_port_t port, char *priority);

/* Set the replacement CFI bit */
int bcm_port_replace_cfi_set(int unit, bcm_port_t port,	char cfi);

/* Retrieve the replacement CFI bit */
int bcm_port_replace_cfi_get(int unit, bcm_port_t port, char *cfi);

/* Set the egress tag mangling operations for a port */
int bcm_port_tag_mangle_set(int unit,	bcm_port_t port, unsigned short op_map);


/* Get the egress tag mangling operations configured for a port */
int bcm_port_tag_mangle_get(int unit, bcm_port_t port, unsigned short *op_map);

/* Set the match_vid used for egress tag mangling */
int bcm_port_tag_mangle_match_vid_set(int unit, bcm_port_t port,
                                               bcm_vlan_t vid);

/* Retrieve the match_vid used for egress tag mangling */
int bcm_port_tag_mangle_match_vid_get(int unit, bcm_port_t port,
                                               bcm_vlan_t *vid);

/* Set the tag stripping of a port for packets with match_vid */
int bcm_port_tag_strip_set(int unit, bcm_port_t port, char val);

/* Get the tag stripping status of a port for packets with match_vid */
int bcm_port_tag_strip_get(int unit, bcm_port_t port, char *val);

/*
 * Function:
 *  bcm_port_pause_capability_set
 * Description:
 *  Enable/Disable the Tx and Rx Pause
 * Parameters:
 *  val - NONE=0, AUTO=1, BOTH=2, TX=3, RX=4
 * Returns:
 *  BCM_E_xxx
 */
int bcm_port_pause_capability_set(int unit, bcm_port_t port, char val);

/*
 * Function:
 *  bcm_port_pause_capability_get
 * Description:
 * Get Pause Capability
 * Parameters:
 *  val - NONE=0, AUTO=1, BOTH=2, TX=3, RX=4
 * Returns:
 *  BCM_E_xxx
 */
int bcm_port_pause_capability_get(int unit, bcm_port_t port, char *val);

/*
 * Function:
 *  bcm_port_rate_ingress_set
 * Purpose:
 *  Set ingress rate limiting parameters
 * Parameters:
 *  unit - Device number
 *  port - Port number
 *  kbits_sec - Rate in kilobits (1000 bits) per second.
 *            Rate of 0 disables rate limiting.
 *  kbits_burst - Maximum burst size in kilobits (1000 bits).
 * Returns:
 *  BCM_E_XXX
 * Note :
 *  1. Robo Switch support 2 ingress buckets for different packet type.
 *     And the bucket1 contains higher priority if PKT_MSK confilict
 *       with bucket0's PKT_MSK.
 *  2. Robo Switch allowed system basis rate/packet type assignment for
 *     Rate Control. The RATE_TYPE and PKT_MSK will be set once in the
 *       initial routine.
 */
int bcm_port_rate_ingress_set(int unit,
                  bcm_port_t port,
                  unsigned int kbits_sec,
                  unsigned int kbits_burst);

/*
 * Function:
 *  bcm_port_rate_ingress_get
 * Purpose:
 *  Get ingress rate limiting parameters
 * Parameters:
 *  unit - Device number
 *  port - Port number
 *  kbits_sec - (OUT) Rate in kilobits (1000 bits) per second, or
 *                  zero if rate limiting is disabled.
 *  kbits_burst - (OUT) Maximum burst size in kilobits (1000 bits).
 * Returns:
 *  BCM_E_XXX
 */
int bcm_port_rate_ingress_get(int unit,
                  bcm_port_t port,
                  unsigned int *kbits_sec,
                  unsigned int *kbits_burst);

/*
 * Function:
 *  bcm_port_rate_egress_set
 * Purpose:
 *  Set egress rate limiting parameters
 * Parameters:
 *  unit - Device number
 *  port - Port number
 *  kbits_sec - Rate in kilobits (1000 bits) per second.
 *          Rate of 0 disables rate limiting.
 *  kbits_burst - Maximum burst size in kilobits (1000 bits).
 * Returns:
 *  BCM_E_XXX
 * Note :
 *  1. Robo Switch support 2 ingress buckets for different packet type.
 *     And the bucket1 contains higher priority if PKT_MSK confilict
 *       with bucket0's PKT_MSK.
 *  2. Robo Switch allowed system basis rate/packet type assignment for
 *     Rate Control. The RATE_TYPE and PKT_MSK will be set once in the
 *       initial routine.
 */
int bcm_port_rate_egress_set(int unit,
                 bcm_port_t port,
                 unsigned int kbits_sec,
                 unsigned int kbits_burst);

/*
 * Function:
 *  bcm_port_rate_egress_get
 * Purpose:
 *  Get egress rate limiting parameters
 * Parameters:
 *  unit - Device number
 *  port - Port number
 *  kbits_sec - (OUT) Rate in kilobits (1000 bits) per second, or
 *              zero if rate limiting is disabled.
 *  kbits_burst - (OUT) Maximum burst size in kilobits (1000 bits).
 * Returns:
 *  BCM_E_XXX
 */
int bcm_port_rate_egress_get(int unit,
                 bcm_port_t port,
                 unsigned int *kbits_sec,
                 unsigned int *kbits_burst);

/* Set the 802.1p bits of port default tag */
int bcm_port_untagged_priority_set(int unit, bcm_port_t port, int priority);

/* Retrieve the 802.1p bits from port default tag */
int bcm_port_untagged_priority_get(int unit, bcm_port_t port, int *priority);

/****************************************************************************/
/*Enet Driver Config/Control API: For Configuring Enet Driver Rx Scheduling */
/****************************************************************************/

/*
 * Function:
 *  bcm_robo_enet_driver_rx_scheduling_set
 * Description:
 *  Select the enet driver rx scheduling mechanism
 * Parameters:
 *  unit - Device unit number
 *  scheduling - scheduling mechanism selection
 * Returns:
 *  BCM_E_xxx
 */
int bcm_enet_driver_rx_scheduling_set(int unit, int scheduling);

/*
 * Function:
 *  bcm_robo_enet_driver_rx_scheduling_get
 * Description:
 *  Get the enet driver rx scheduling mechanism
 * Parameters:
 *  unit - Device unit number
 *  scheduling - scheduling mechanism
 * Returns:
 *  BCM_E_xxx
 */
int bcm_enet_driver_rx_scheduling_get(int unit, int *scheduling);


/*
 * Function:
 *  bcm_robo_enet_driver_wrr_config_set
 * Description:
 *  Configure the WRR parameters
 * Parameters:
 *  unit - Device unit number
 *  max_pkts_per_iter - Max number of packets when the weights will be reloaded.
 *  weights - Pointer to integer array of WRR weights of all 4 channels.
 * Returns:
 *  BCM_E_xxx
 */
int bcm_enet_driver_wrr_weights_set(int unit, int max_pkts_per_iter,
                                                 int *weights);

/*
 * Function:
 *  bcm_robo_enet_driver_wrr_config_get
 * Description:
 *  Retrieve the WRR parameters
 * Parameters:
 *  unit - Device unit number
 *  max_pkts_per_iter - Max number of packets when the weights will be reloaded.
 *  weights - Pointer to integer array of WRR weights of all 4 channels.
 * Returns:
 *  BCM_E_xxx
 */
int bcm_enet_driver_wrr_weights_get(int unit, int *max_pkts_per_iter,
                                                 int *weights);



/* Get enable/disable status of using default queue as egress queue */
int bcm_enet_driver_use_default_txq_status_get(int unit, char *ifname,
                                               int *operation);

/* Set enable/disable status of using default queue as egress queue */
int bcm_enet_driver_use_default_txq_status_set(int unit, char *ifname,
                                               int operation);

/* Get default the egress queue of given interface */
int bcm_enet_driver_default_txq_get(int unit, char *ifname,
                                    bcm_cos_queue_t *cosq);

/* Set default the egress queue of given interface */
int bcm_enet_driver_default_txq_set(int unit, char *ifname,
                                    bcm_cos_queue_t cosq);


/*
 * Function:
 *  bcm_enet_driver_rx_rate_limit_cfg_get
 * Description:
 *  Get enable/disable status of rx rate limiting of given channel
 * Parameters:
 *  unit - Device unit number
 *  channel - iuDMA channel # (rx iuDMA channel from MIPS perspective)
 *  status - rate limiting enable/disable status
 * Returns:
 *  BCM_E_xxx
 */
int bcm_enet_driver_rx_rate_limit_cfg_get(int unit, int channel, int *status);

/*
 * Function:
 *  bcm_enet_driver_rx_rate_limit_cfg_set
 * Description:
 *  Set enable/disable status of rx rate limiting of given channel
 * Parameters:
 *  unit - Device unit number
 *  channel - iuDMA channel # (rx iuDMA channel from MIPS perspective)
 *  status - rate limiting enable/disable status
 * Returns:
 *  BCM_E_xxx
 */
int bcm_enet_driver_rx_rate_limit_cfg_set(int unit, int channel, int status);

/*
 * Function:
 *  bcm_enet_driver_rx_rate_get
 * Description:
 *  Get rx byte rate of a given channel
 * Parameters:
 *  unit - Device unit number
 *  channel - iuDMA channel # (rx iuDMA channel from MIPS perspective)
 *  rate - rx byte rate of the channel in bytes per second
 * Returns:
 *  BCM_E_xxx
 */
int bcm_enet_driver_rx_rate_get(int unit, int channel, int *rate);

/*
 * Function:
 *  bcm_enet_driver_rx_rate_set
 * Description:
 *  Set rx byte rate of a given channel
 * Parameters:
 *  unit - Device unit number
 *  channel - iuDMA channel # (rx iuDMA channel from MIPS perspective)
 *  rate - rx byte rate of the channel in bytes per second
 * Returns:
 *  BCM_E_xxx
 */
int bcm_enet_driver_rx_rate_set(int unit, int channel, int rate);

/*
 * Function:
 *  bcm_enet_driver_rx_pkt_rate_cfg_get
 * Description:
 *  Get enable/disable status of rx pkt rate limiting of given channel
 * Parameters:
 *  unit - Device unit number
 *  channel - iuDMA channel # (rx iuDMA channel from MIPS perspective)
 *  status - rate limiting enable/disable status
 * Returns:
 *  BCM_E_xxx
 */
int bcm_enet_driver_rx_pkt_rate_cfg_get(int unit, int channel, int *status);

/*
 * Function:
 *  bcm_enet_driver_rx_pkt_rate_cfg_set
 * Description:
 *  Set enable/disable status of rx pkt rate limiting of given channel
 * Parameters:
 *  unit - Device unit number
 *  channel - iuDMA channel # (rx iuDMA channel from MIPS perspective)
 *  status - rate limiting enable/disable status
 * Returns:
 *  BCM_E_xxx
 */
int bcm_enet_driver_rx_pkt_rate_cfg_set(int unit, int channel, int status);


/*
 * Function:
 *  bcm_enet_driver_rx_pkt_rate_get
 * Description:
 *  Get rx pkt rate of a given channel
 * Parameters:
 *  unit - Device unit number
 *  channel - iuDMA channel # (rx iuDMA channel from MIPS perspective)
 *  rate - rx packet rate of the channel in packets per second
 * Returns:
 *  BCM_E_xxx
 */
int bcm_enet_driver_rx_pkt_rate_get(int unit, int channel, int *rate);

/*
 * Function:
 *  bcm_enet_driver_rx_pkt_rate_set
 * Description:
 *  Set rx pkt rate of a given channel
 * Parameters:
 *  unit - Device unit number
 *  channel - iuDMA channel # (rx iuDMA channel from MIPS perspective)
 *  rate - rx packet rate of the channel in packets per second
 * Returns:
 *  BCM_E_xxx
 */
int bcm_enet_driver_rx_pkt_rate_set(int unit, int channel, int rate);

/* For testing and debugging */
int bcm_enet_driver_test_config_get(int unit, int type, int param, int *val);
/* For testing and debugging */
int bcm_enet_driver_test_config_set(int unit, int type, int param, int val);

/****************************************************************************/
/*  VLAN API:  For set/get of VLAN Table Entry                              */
/****************************************************************************/

/*
 * Function:
 *  bcm_vlan_port_set
 * Description:
 *  Write the given VLAN table entry to hardware
 * Parameters:
 *  unit - Device unit number
 *  vid -  VLAN ID
 *  fwd_map - Members of the VLAN
 *  untag_map - Untagged members of the VLAN
 * Returns:
 *  BCM_E_xxx
 */
int bcm_vlan_port_set(int unit, int vid, int fwd_map, int untag_map);

/*
 * Function:
 *  bcm_vlan_port_get
 * Description:
 *  Retrieve the forward_map and untag_map of the given VLAN
 * Parameters:
 *  unit - Device unit number
 *  vid -  VLAN ID
 *  fwd_map - Members of the VLAN
 *  untag_map - Untagged members of the VLAN
 * Returns:
 *  BCM_E_xxx
 */
int bcm_vlan_port_get(int unit, int vid, int * fwd_map, int *untag_map);



int bcm_port_pbvlanmap_set(int unit, int port, int fwd_map);
int bcm_port_pbvlanmap_get(int unit, int port, int *fwd_map);


/****************************************************************************/
/*  CoS API:  For CoS configuration                                         */
/****************************************************************************/

/*
 * Function:
 *  bcm_cosq_config_get
 * Description:
 *  Retrieve the Number of CoS queues
 * Parameters:
 *  unit - Device unit number
 *  numq - Number of CoS queues
 * Returns:
 *  BCM_E_xxx
 */
int bcm_cosq_config_get(int unit, int *numq);

/*
 * Function:
 *  bcm_cosq_config_set
 * Description:
 *  Set the number of CoS queues
 * Parameters:
 *  unit - Device unit number
 *  numq - Number of CoS queues. For BCM6816, valid values are 1 and 8.
 * Returns:
 *  BCM_E_xxx
 */
int bcm_cosq_config_set(int unit, int numq);

/*
 * Function:
 *  bcm_cosq_sched_get
 * Description:
 *  Retrieve the scheduling policy and its parameters
 * Parameters:
 *  unit - Device unit number
 *  mode -  Scheduling policy
 *  sp_endq - The queue where SP ends. Valid only when mode is COMBO (SP + WRR)
 *     All queues lower than sp_endq are serviced in WRR and remaining queues
 *     are serviced in SP. Note that SP starts with highest queue.
 *  weights - queue weights for WRR scheduling. Valid only when mode is WRR
 * Returns:
 *  BCM_E_xxx
 */
int bcm_cosq_sched_get(int unit, int *mode, int *sp_endq,
                        int weights[BCM_COS_COUNT]);

/*
 * Function:
 *  bcm_cosq_sched_set
 * Description:
 *  Set the scheduling policy and its parameters
 * Parameters:
 *  unit - Device unit number
 *  mode -  Scheduling policy
 *  sp_endq - The queue where SP ends. Valid only when mode is COMBO (SP + WRR)
 *     All queues lower than sp_endq are serviced in WRR and remaining queues
 *     are serviced in SP. Note that SP starts with highest queue.
 *  weights - queue weights for WRR scheduling. Valid only when mode is WRR
 * Returns:
 *  BCM_E_xxx
 */
int bcm_cosq_sched_set(int unit, int mode, int sp_endq,
                        int weights[BCM_COS_COUNT]);

/*
 * Function:
 *  bcm_cosq_port_mapping_get
 * Description:
 *  Retrieve the internal priority to CoS queue mapping
 * Parameters:
 *  unit - Device unit number
 *  priority - Internal Priority
 *    port - Port number
 *  cosq - CoS queue
 * Returns:
 *  BCM_E_xxx
 */
int bcm_cosq_port_mapping_get(int unit, bcm_port_t port, bcm_cos_t priority, bcm_cos_queue_t *cosq);

/*
 * Function:
 *  bcm_cosq_port_mapping_set
 * Description:
 *  Set the internal priority to CoS queue mapping
 * Parameters:
 *  unit - Device unit number
 *  priority - Internal Priority
 *    port - Port number
 *  cosq - CoS queue
 * Returns:
 *  BCM_E_xxx
 */
int bcm_cosq_port_mapping_set(int unit, bcm_port_t port, bcm_cos_t priority,
                              bcm_cos_queue_t cosq);


/*
 * Function:
 *  bcm_cosq_rxchannel_mapping_get
 * Description:
 *  Retrieve the CoS queue to Rx iuDMA channel mapping
 * Parameters:
 *  unit - Device unit number
 *  cosq - Egress queue #
 *  channel - iuDMA channel (rx iuDMA channel from MIPS perspective)
 * Returns:
 *  BCM_E_xxx
 */
int bcm_cosq_rxchannel_mapping_get(int unit, bcm_cos_queue_t cosq,
                                   int *channel);

/*
 * Function:
 *  bcm_cosq_rxchannel_mapping_set
 * Description:
 *  Set the CoS queue to Rx iuDMA channel mapping
 * Parameters:
 *  unit - Device unit number
 *  cosq - Egress queue #
 *  channel - iuDMA channel # (rx iuDMA channel from MIPS perspective)
 * Returns:
 *  BCM_E_xxx
 */
int bcm_cosq_rxchannel_mapping_set(int unit, bcm_cos_queue_t cosq, int channel);

/*
 * Function:
 *  bcm_cosq_txchannel_mapping_get
 * Description:
 *  Retrieve the Tx iuDMA channel to egress queue mapping
 * Parameters:
 *  unit - Device unit number
 *  channel - iuDMA channel # (tx iuDMA channel from MIPS perspective)
 *  cosq - Egress queue #
 * Returns:
 *  BCM_E_xxx
 */
int bcm_cosq_txchannel_mapping_get(int unit, int channel, bcm_cos_queue_t *cosq);

/*
 * Function:
 *  bcm_cosq_txchannel_mapping_set
 * Description:
 *  Configure the Tx iuDMA channel to egress queue mapping
 * Parameters:
 *  unit - Device unit number
 *  channel - iuDMA channel # (tx iuDMA channel from MIPS perspective)
 *  cosq - Egress queue #
 * Returns:
 *  BCM_E_xxx
 */
int bcm_cosq_txchannel_mapping_set(int unit, int channel, bcm_cos_queue_t cosq);

/*
 * Function:
 *  bcm_cosq_txchannel_mapping_set
 * Description:
 *  Configure the Tx iuDMA channel to egress queue mapping
 * Parameters:
 *  unit - Device unit number
 *  channel - iuDMA channel # (tx iuDMA channel from MIPS perspective)
 *  cosq - Egress queue #
 * Returns:
 *  BCM_E_xxx
 */
int bcm_cosq_txq_selection_get(int unit, int *method);

/*
 * Function:
 *  bcm_cosq_txchannel_mapping_set
 * Description:
 *  Configure the Tx iuDMA channel to egress queue mapping
 * Parameters:
 *  unit - Device unit number
 *  channel - iuDMA channel # (tx iuDMA channel from MIPS perspective)
 *  cosq - Egress queue #
 * Returns:
 *  BCM_E_xxx
 */
int bcm_cosq_txq_selection_set(int unit, int method);

/*
 * Function:
 *  bcm_cosq_priority_method_get
 * Description:
 * Retrieve the method for deciding on frame priority
 * Parameters:
 *  unit - RoboSwitch PCI device unit number (driver internal).
 *  method -
 *  PORT_QOS: Frame priority is based on the priority of port default tag
 *  MAC_QOS: Frame priority is based on the destination MAC address
 *  IEEE8021P_QOS: Frame priority is based on 802.1p field of the frame
 *  DIFFSERV_QOS: Frame priority is based on the diffserv field of the frame
 * Returns:
 *  BCM_E_NONE - Success.
 */
int bcm_cosq_priority_method_get(int unit, int *method);

/*
 * Function:
 *  bcm_cosq_priority_method_set
 * Description:
 *  Set the method for deciding on frame priority
 * Parameters:
 *  unit - RoboSwitch PCI device unit number (driver internal).
 *  method -
 *  PORT_QOS: Frame priority is based on the priority of port default tag
 *  MAC_QOS: Frame priority is based on the destination MAC address
 *  IEEE8021P_QOS: Frame priority is based on 802.1p field of the frame
 *  DIFFSERV_QOS: Frame priority is based on the diffserv field of the frame
 * Returns:
 *  BCM_E_NONE - Success.
 */
int bcm_cosq_priority_method_set(int unit, int method);

/*
 * Function:
 *  bcm_cosq_dscp_priority_mapping_set
 * Description:
 *  Configure DSCP to priority mapping
 * Parameters:
 *  unit - RoboSwitch PCI device unit number (driver internal).
 *  dscp:  6-bit dscp value
 *  priority:  switch priority
 * Returns:
 *  BCM_E_NONE - Success.
 */
int bcm_cosq_dscp_priority_mapping_set(int unit, int dscp, bcm_cos_t priority);

/*
 * Function:
 *  bcm_cosq_dscp_priority_mapping_get
 * Description:
 *  Get DSCP to priority mapping
 * Parameters:
 *  unit - RoboSwitch PCI device unit number (driver internal).
 *  dscp:  6-bit dscp value
 *  priority:  switch priority
 * Returns:
 *  BCM_E_NONE - Success.
 */
int bcm_cosq_dscp_priority_mapping_get(int unit, int dscp, bcm_cos_t *priority);

/*
 * Function:
 *  bcm_port_traffic_control_set
 * Description:
 *  Enable/Disable tx/rx of a switch port
 * Parameters:
 *  unit - RoboSwitch PCI device unit number (driver internal).
 *  port - Port number
 *  ctrl_map: bit0 = rx_disable (1 = disable rx; 0 = enable rx)
 *            bit1 = tx_disable (1 = disable tx; 0 = enable tx)
 * Returns:
 *  BCM_E_NONE - Success.
 */
int bcm_port_traffic_control_set(int unit, bcm_port_t port, int ctrl_map);

/*
 * Function:
 *  bcm_port_traffic_control_get
 * Description:
 *  Get Enable/Disable status of tx/rx of a switch port
 * Parameters:
 *  unit - RoboSwitch PCI device unit number (driver internal).
 *  port - Port number
 *  ctrl_map: bit0 = rx_disable (1 = disable rx; 0 = enable rx)
 *            bit1 = tx_disable (1 = disable tx; 0 = enable tx)
 * Returns:
 *  BCM_E_NONE - Success.
 */
int bcm_port_traffic_control_get(int unit, bcm_port_t port, int *ctrl_map);

/*
 * Function:
 *  bcm_port_loopback_set
 * Description:
 *  Enable/Disable of loopback of USB port or LAN port Phy
 * Parameters:
 *  unit - RoboSwitch PCI device unit number (driver internal).
 *  status:  1 = Enable loopback; 0 = Disable loopback
 * Returns:
 *  BCM_E_NONE - Success.
 */
int bcm_port_loopback_set(int unit, bcm_port_t port, int status);

/*
 * Function:
 *  bcm_port_loopback_get
 * Description:
 *  Get loopback status of USB port or LAN port Phy
 * Parameters:
 *  unit - RoboSwitch PCI device unit number (driver internal).
 *  status:  1 = Enable loopback; 0 = Disable loopback
 * Returns:
 *  BCM_E_NONE - Success.
 */
int bcm_port_loopback_get(int unit, bcm_port_t port, int *status);

/*
 * Function:
 *  bcm_port_jumbo_control_set
 * Description:
 *  Set jumbo accept/reject control of selected port(s)
 * Parameters:
 *  port - Port number 9(ALL), 8(MIPS), 7(GPON), 6(USB), 5(MOCA), 4(GPON_SERDES), 3(GMII_2), 2(GMII_1), 1(GPHY_1), 0(GPHY_0)
 *  ctrlValPtr - pointer to result
 * Returns:
 *  BCM_E_NONE - Success.
 */
int bcm_port_jumbo_control_set(bcm_port_t port, int* ctrlValPtr); // bill

/*
 * Function:
 *  bcm_port_jumbo_control_get
 * Description:
 *  Get jumbo accept/reject status of selected port(s)
 * Parameters:
 *  port - Port number 9(ALL), 8(MIPS), 7(GPON), 6(USB), 5(MOCA), 4(GPON_SERDES), 3(GMII_2), 2(GMII_1), 1(GPHY_1), 0(GPHY_0)
 *  ctrlValPtr - pointer to result
 * Returns:
 *  BCM_E_NONE - Success.
 */
int bcm_port_jumbo_control_get(bcm_port_t port, int *ctrlValPtr); // bill

int bcm_arl_read(int unit, char *mac, bcm_vlan_t vid, unsigned short *value);
int bcm_arl_write(int unit, char *mac, bcm_vlan_t vid, unsigned short value);
int bcm_arl_dump(int unit);
int bcm_arl_flush(int unit);

/*
 * Function:
 *	bcm_reg_read
 * Description:
 *  Read from a switch register 
 * Parameters:
 *	addr = offset 
 *	len = length of register 
 *	val = value read from register 
 * Returns:
 *	BCM_E_NONE - Success.
 */
int bcm_reg_read(unsigned int addr, char* data, int len);

/*
 * Function:
 *	bcm_reg_write 
 * Description:
 *  Write to a switch register 
 * Parameters:
 *	addr = offset 
 *	len = length of register 
 *	val = value to be written to register 
 * Returns:
 *	BCM_E_NONE - Success.
 */
int bcm_reg_write(unsigned int addr, char *data, int len);

int bcm_spi_read(int spi_id, int chip_id, unsigned int addr, char *data, int len);
int bcm_spi_write(int spi_id, int chip_id, unsigned int addr, char *data, int len); 

int bcm_pseudo_mdio_read(unsigned int addr, char *data, int len);
int bcm_pseudo_mdio_write(unsigned int addr, char *data, int len);

int bcm_get_switch_info(int switch_id, unsigned int *vendor_id,
  unsigned int *dev_id, unsigned int *rev_id, int *bus_type, 
  unsigned int *spi_id, unsigned int *chip_id, unsigned int *pbmp, 
  unsigned int *phypbmp);

int bcm_set_linkstatus(int port, int linkstatus, int speed, int duplex);

/*
 * Function:
 *  bcm_packet_padding_set
 * Description:
 *  Configure enable/disable of packet padding and min length with padding
 * Parameters:
 *  unit - RoboSwitch PCI device unit number (driver internal).
 *  enable - 1 = Enable padding; 0 = Disable padding
 *  length -  min length of the packet after padding. valid only when enable=1
 * Returns:
 *  BCM_E_NONE - Success.
 */
int bcm_packet_padding_set(int unit, int enable, int length);

/*
 * Function:
 *  bcm_packet_padding_get
 * Description:
 *  Get enable/disable of packet padding and min length with padding
 * Parameters:
 *  unit - RoboSwitch PCI device unit number (driver internal).
 *  enable - 1 = padding enabled; 0 = padding disabled
 *  length -  min length of the packet after padding. valid only when enable=1
 * Returns:
 *  BCM_E_NONE - Success.
 */
int bcm_packet_padding_get(int unit, int *enable, int *length);

/****************************************************************************/
/*  Debug API                                                               */
/****************************************************************************/

int bcm_switch_getrxcntrs();
int bcm_switch_resetrxcntrs();


#endif /* _ETHSWCTL_API_H_ */
