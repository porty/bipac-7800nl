/******************************************************************************
 *
 *  Copyright (c) 2009  Broadcom Corporation
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
/***************************************************************************
 *
 *     Copyright (c) 2008-2009, Broadcom Corporation
 *     All Rights Reserved
 *     Confidential Property of Broadcom Corporation
 *
 *  THIS SOFTWARE MAY ONLY BE USED SUBJECT TO AN EXECUTED SOFTWARE LICENSE
 *  AGREEMENT  BETWEEN THE USER AND BROADCOM.  YOU HAVE NO RIGHT TO USE OR
 *  EXPLOIT THIS MATERIAL EXCEPT SUBJECT TO THE TERMS OF SUCH AN AGREEMENT.
 *
 *  Description: Public interfaces for libmoca
 *
 ************************************************************/

#ifndef _MOCALIB_H_
#define _MOCALIB_H_

#include <stdint.h>
#include <endian.h>
#include <net/if.h>

#ifdef __cplusplus
extern "C" {
#endif

void *moca_open(char *ifname);
void moca_close(void *vctx);
int moca_raw_req(void *vctx, const void *wr, int wr_len,
	void *rd, int max_rd_len);
int moca_event_loop(void *vctx);
void moca_cancel_event_loop(void *vctx);
const char *moca_l2_error_name(uint32_t l2_error);

const char *moca_ie_name(uint16_t ie_type);
unsigned long moca_phy_rate(unsigned long nbas, unsigned long cp);

#define MOCA_TX_BC		0x10
#define MOCA_TX_MAP		0x11

#define MOCA_MAX_NODES                  16
#define MOCA_MAX_PQOS_LIST_FLOW_IDS     32
#define MOCA_MAX_PQOS_ENTRIES           16

#define MOCA_L2_SUCCESS                 0x0
#define MOCA_L2_TRANSACTION_FAILED      0x1
#define MOCA_L2_L2ME_NO_SUPPORT         0x2
#define MOCA_L2_PQOS_INGR_NOT_FOUND     0x4
#define MOCA_L2_PQOS_EGR_NOT_FOUND      0x8
#define MOCA_L2_TRANSACTION_CANT_START  0x10

#define MOCA_PQOS_DECISION_SUCCESS      1

#define MOCA_CONT_TX_NORMAL             0  /* Default */
#define MOCA_CONT_TX_PROBE_I            1
#define MOCA_CONT_RX                    2
#define MOCA_CONT_TX_EXT                3
#define MOCA_CONT_TX_CW                 4
#define MOCA_CONT_TX_TONE               5
#define MOCA_CONT_TX_TONE_SC            6
#define MOCA_CONT_TX_DUAL_TONE_SC       7
#define MOCA_CONT_TX_MODE_DEFAULT       MOCA_CONT_TX_NORMAL

static inline void moca_mac_to_u32(uint32_t *hi, uint32_t *lo,
	const uint8_t *mac)
{
	*hi = (mac[0] << 24) | (mac[1] << 16) | (mac[2] << 8) | (mac[3] << 0);
	*lo = (mac[4] << 24) | (mac[5] << 16);
}

static inline void moca_u32_to_mac(uint8_t *mac, uint32_t hi, uint32_t lo)
{
	mac[0] = (hi >> 24) & 0xff;
	mac[1] = (hi >> 16) & 0xff;
	mac[2] = (hi >>  8) & 0xff;
	mac[3] = (hi >>  0) & 0xff;
	mac[4] = (lo >> 24) & 0xff;
	mac[5] = (lo >> 16) & 0xff;
}

/* GENERATED API BELOW THIS LINE - DO NOT EDIT */

struct moca_init_time {
	uint32_t		nc_mode;
	uint32_t		auto_network_search_en;
	uint32_t		privacy_en;
	uint32_t		tpc_en;
	uint32_t		continuous_power_tx_mode;
	uint32_t		lof;
	int32_t			max_tx_power_beacons;
	uint32_t		freq_mask;
	uint32_t		mac_addr_hi;
	uint32_t		mac_addr_lo;
	uint32_t		mmk_key_hi;
	uint32_t		mmk_key_lo;
	uint32_t		pmk_initial_key_hi;
	uint32_t		pmk_initial_key_lo;
	uint32_t		multicast_mode;
	uint32_t		lab_mode;
	uint32_t		taboo_mask_start;
	uint32_t		taboo_channel_mask;
	int32_t			pad_power;
	uint32_t		preferred_nc;
	int32_t			max_tx_power_packets;
	uint32_t		led_settings;
	uint32_t		moca_loopback_en;
	uint32_t		bo_mode;
	uint32_t		rf_type;
	uint32_t		default_channel;
	uint32_t		assigned_channel;
	uint32_t		mr_non_def_seq_num;
	uint32_t		low_pri_q_num;
	uint32_t		egr_mc_filter_en;
	uint32_t		reserved_init_1;
	uint32_t		reserved_init_2;
	uint32_t		reserved_init_3;
	uint32_t		reserved_init_4;
	uint32_t		reserved_init_5;
} __attribute__((packed,aligned(4)));

struct moca_max_constellation {
	uint32_t		node_id;
	uint32_t		bits_per_carrier;
} __attribute__((packed,aligned(4)));

struct moca_sig_y_done {
	uint32_t		lmo_counter;
	uint32_t		cp;
	uint32_t		cc_offset;
	uint32_t		ac_offset;
	uint32_t		cp_min_ac_delay_offset;
	uint32_t		enableHT;
	uint32_t		cp_overflow;
	uint32_t		reg_pp_cc_maxf_th_scl;
} __attribute__((packed,aligned(4)));

struct moca_priority_allocations {
	uint32_t		reservation_high;
	uint32_t		reservation_med;
	uint32_t		reservation_low;
	uint32_t		limitation_high;
	uint32_t		limitation_med;
	uint32_t		limitation_low;
} __attribute__((packed,aligned(4)));

struct moca_snr_margin_table {
	int8_t			mgntable[12];
} __attribute__((packed,aligned(4)));

struct moca_sapm_table {
	uint8_t			sapmtablelo[112];
	uint8_t			sapmtablehi[112];
} __attribute__((packed,aligned(4)));

struct moca_rlapm_table {
	uint8_t			rlapmtable[68];
} __attribute__((packed,aligned(4)));

struct moca_egr_mc_addr_filter {
	uint32_t		entryid;
	uint32_t		valid;
	uint32_t		addr_hi;
	uint32_t		addr_lo;
} __attribute__((packed,aligned(4)));

struct moca_egr_mc_addr_filter_get {
	uint32_t		entryid;
	uint32_t		valid;
	uint32_t		addr_hi;
	uint32_t		addr_lo;
} __attribute__((packed,aligned(4)));

struct moca_lab_pilots {
	uint8_t			pilots[8];
} __attribute__((packed,aligned(4)));

struct moca_lab_iq_diagram_set {
	uint32_t		nodeid;
	uint32_t		bursttype;
	uint32_t		acmtsymnum;
} __attribute__((packed,aligned(4)));

struct moca_lab_register {
	uint32_t		address;
	uint32_t		value;
} __attribute__((packed,aligned(4)));

struct moca_lab_call_func {
	uint32_t		address;
	uint32_t		param1;
	uint32_t		param2;
} __attribute__((packed,aligned(4)));

struct moca_lab_tpcap {
	uint32_t		enable;
	uint32_t		type;
} __attribute__((packed,aligned(4)));

struct moca_fmr_request {
	uint8_t			hdrFmt;
	uint8_t			entryNodeId;
	uint8_t			entryIndex;
	uint8_t			reserved_0;
	uint16_t		vendorId;
	uint8_t			transType;
	uint8_t			transSubtype;
	uint32_t		wave0Nodemask;
	uint32_t		reserved_1;
	uint8_t			reserved_2;
	uint8_t			msgPriority;
	uint8_t			txnLastWaveNum;
	uint8_t			reserved_3;
	uint32_t		reserved_4;
} __attribute__((packed,aligned(4)));

struct moca_pqos_create_request {
	uint8_t			hdrFmt;
	uint8_t			entryNodeId;
	uint8_t			entryIndex;
	uint8_t			reserved_0;
	uint16_t		vendorId;
	uint8_t			transType;
	uint8_t			transSubtype;
	uint32_t		wave0Nodemask;
	uint32_t		reserved_1;
	uint8_t			reserved_2;
	uint8_t			msgPriority;
	uint8_t			txnLastWaveNum;
	uint8_t			reserved_3;
	uint32_t		flowid_hi;
	uint32_t		flowid_lo;
	uint16_t		tPacketSize;
	uint8_t			reserved_4;
	uint8_t			ingressNodeId;
	uint8_t			reserved_5[3];
	uint8_t			egressNodeId;
	uint32_t		flowTag;
	uint32_t		packetda_hi;
	uint32_t		packetda_lo;
	uint32_t		tPeakDataRate;
	uint32_t		tLeaseTime;
	uint8_t			tBurstSize;
	uint8_t			reserved_6[3];
} __attribute__((packed,aligned(4)));

struct moca_pqos_ingr_add_flow {
	uint32_t		flowid_hi;
	uint32_t		flowid_lo;
	uint32_t		flowtag;
	uint32_t		qtag;
	uint32_t		tpeakdatarate;
	uint32_t		tpacketsize;
	uint32_t		tburstsize;
	uint32_t		tleasetime;
	uint32_t		egressnodeid;
	uint32_t		flowsa_hi;
	uint32_t		flowsa_lo;
	uint32_t		flowda_hi;
	uint32_t		flowda_lo;
	uint32_t		flowvlanpri;
	uint32_t		flowvlanid;
	uint32_t		committedstps;
	uint32_t		committedtxps;
} __attribute__((packed,aligned(4)));

struct moca_pqos_update_request {
	uint8_t			hdrFmt;
	uint8_t			entryNodeId;
	uint8_t			entryIndex;
	uint8_t			reserved_0;
	uint16_t		vendorId;
	uint8_t			transType;
	uint8_t			transSubtype;
	uint32_t		wave0Nodemask;
	uint32_t		reserved_1;
	uint8_t			reserved_2;
	uint8_t			msgPriority;
	uint8_t			txnLastWaveNum;
	uint8_t			reserved_3;
	uint32_t		flowid_hi;
	uint32_t		flowid_lo;
	uint16_t		tPacketSize;
	uint8_t			reserved_4;
	uint8_t			ingressNodeId;
	uint8_t			reserved_5[3];
	uint8_t			egressNodeId;
	uint32_t		flowTag;
	uint32_t		packetda_hi;
	uint32_t		packetda_lo;
	uint32_t		tPeakDataRate;
	uint32_t		tLeaseTime;
	uint8_t			tBurstSize;
	uint8_t			reserved_6[3];
} __attribute__((packed,aligned(4)));

struct moca_pqos_ingr_update {
	uint32_t		flowid_hi;
	uint32_t		flowid_lo;
	uint32_t		flowtag;
	uint32_t		flowda_hi;
	uint32_t		flowda_lo;
	uint32_t		tpeakdatarate;
	uint32_t		tpacketsize;
	uint32_t		tburstsize;
	uint32_t		tleasetime;
	uint32_t		committedstps;
	uint32_t		committedtxps;
} __attribute__((packed,aligned(4)));

struct moca_pqos_delete_request {
	uint8_t			hdrFmt;
	uint8_t			entryNodeId;
	uint8_t			entryIndex;
	uint8_t			reserved_0;
	uint16_t		vendorId;
	uint8_t			transType;
	uint8_t			transSubtype;
	uint32_t		wave0Nodemask;
	uint32_t		reserved_1;
	uint8_t			reserved_2;
	uint8_t			msgPriority;
	uint8_t			txnLastWaveNum;
	uint8_t			reserved_3;
	uint32_t		flowid_hi;
	uint32_t		flowid_lo;
	uint32_t		reserved_4;
} __attribute__((packed,aligned(4)));

struct moca_pqos_ingr_delete {
	uint32_t		flowid_hi;
	uint32_t		flowid_lo;
} __attribute__((packed,aligned(4)));

struct moca_pqos_list_request {
	uint8_t			hdrFmt;
	uint8_t			entryNodeId;
	uint8_t			entryIndex;
	uint8_t			reserved_0;
	uint16_t		vendorId;
	uint8_t			transType;
	uint8_t			transSubtype;
	uint32_t		wave0Nodemask;
	uint32_t		reserved_1;
	uint8_t			reserved_2;
	uint8_t			msgPriority;
	uint8_t			txnLastWaveNum;
	uint8_t			reserved_3;
	uint32_t		flowStartIndex;
	uint8_t			flowMaxReturn;
	uint8_t			reserved_4[3];
} __attribute__((packed,aligned(4)));

struct moca_pqos_query_request {
	uint8_t			hdrFmt;
	uint8_t			entryNodeId;
	uint8_t			entryIndex;
	uint8_t			reserved_0;
	uint16_t		vendorId;
	uint8_t			transType;
	uint8_t			transSubtype;
	uint32_t		wave0Nodemask;
	uint32_t		reserved_1;
	uint8_t			reserved_2;
	uint8_t			msgPriority;
	uint8_t			txnLastWaveNum;
	uint8_t			reserved_3;
	uint32_t		reserved_4;
	uint32_t		flowid_hi;
	uint32_t		flowid_lo;
} __attribute__((packed,aligned(4)));

struct moca_mr_request {
	uint8_t			hdrFmt;
	uint8_t			entryNodeId;
	uint8_t			entryIndex;
	uint8_t			reserved_0;
	uint16_t		vendorId;
	uint8_t			transType;
	uint8_t			transSubtype;
	uint32_t		wave0Nodemask;
	uint32_t		reserved_1;
	uint8_t			reserved_2;
	uint8_t			msgPriority;
	uint8_t			txnLastWaveNum;
	uint8_t			reserved_3;
	uint8_t			resetStatus;
	uint8_t			resetTimer;
	uint16_t		nonDefSeqNum;
} __attribute__((packed,aligned(4)));

struct moca_gen_status {
	uint32_t		vendor_id;
	uint32_t		moca_hw_version;
	uint32_t		moca_sw_version;
	uint32_t		self_moca_version;
	uint32_t		network_moca_version;
	uint32_t		qam_256_support;
	uint32_t		operation_status;
	uint32_t		link_status;
	uint32_t		connected_nodes;
	uint32_t		node_id;
	uint32_t		nc_node_id;
	uint32_t		backup_nc_id;
	uint32_t		rf_channel;
	uint32_t		bw_status;
	uint32_t		nodes_usable_bitmask;
	uint32_t		network_taboo_mask;
	uint32_t		network_taboo_start;
	uint32_t		tx_gcd_power_reduction;
	uint32_t		pqos_egress_numflows;
} __attribute__((packed,aligned(4)));

struct moca_ext_status {
	uint32_t		pmk_even_key_hi;
	uint32_t		pmk_even_key_lo;
	uint32_t		pmk_odd_key_hi;
	uint32_t		pmk_odd_key_lo;
	uint32_t		tek_even_key_hi;
	uint32_t		tek_even_key_lo;
	uint32_t		tek_odd_key_hi;
	uint32_t		tek_odd_key_lo;
} __attribute__((packed,aligned(4)));

struct moca_gen_stats {
	uint32_t		in_uc_packets;
	uint32_t		in_discard_packets_ecl;
	uint32_t		in_discard_packets_mac;
	uint32_t		in_unknown_packets;
	uint32_t		in_mc_packets;
	uint32_t		in_bc_packets;
	uint32_t		in_octets;
	uint32_t		out_uc_packets;
	uint32_t		out_discard_packets;
	uint32_t		out_bc_packets;
	uint32_t		out_octets;
	uint32_t		nc_handoff_counter;
	uint32_t		nc_backup_counter;
	uint32_t		aggr_pkt_stats_tx[10];
	uint32_t		aggr_pkt_stats_rx[10];
	uint32_t		received_data_filtered;
} __attribute__((packed,aligned(4)));

struct moca_ext_stats {
	uint32_t		received_map_packets;
	uint32_t		received_rr_packets;
	uint32_t		received_beacons;
	uint32_t		received_control_packets;
	uint32_t		transmitted_beacons;
	uint32_t		transmitted_maps;
	uint32_t		transmitted_lcs;
	uint32_t		transmitted_rr_packets;
	uint32_t		resync_attempts_to_network;
	uint32_t		gmii_tx_buffer_full_counter;
	uint32_t		moca_rx_buffer_full_counter;
	uint32_t		this_handoff_counter;
	uint32_t		this_backup_counter;
	uint32_t		fc_counter[3];
	uint32_t		transmitted_protocol_ie;
	uint32_t		received_protocol_ie;
	uint32_t		transmitted_time_ie;
	uint32_t		received_time_ie;
} __attribute__((packed,aligned(4)));

struct moca_gen_node_status {
	uint32_t		eui_hi;
	uint32_t		eui_lo;
	int32_t			freq_offset;
	uint32_t		node_tx_backoff;
	uint32_t		protocol_support;
} __attribute__((packed,aligned(4)));

struct moca_tx_profile {
	uint32_t		nbas;
	uint32_t		preamble_type;
	uint32_t		cp;
	uint32_t		tx_power;
	uint32_t		pad;
	uint32_t		bit_loading[32];
	uint32_t		avg_snr;
} __attribute__((packed,aligned(4)));

struct moca_rx_uc_profile {
	uint32_t		nbas;
	uint32_t		preamble_type;
	uint32_t		cp;
	uint32_t		pad;
	uint32_t		rx_gain;
	uint32_t		bit_loading[32];
	uint32_t		avg_snr;
} __attribute__((packed,aligned(4)));

struct moca_rx_bc_profile {
	uint32_t		nbas;
	uint32_t		preamble_type;
	uint32_t		cp;
	uint32_t		pad;
	uint32_t		rx_gain;
	uint32_t		bit_loading[32];
	uint32_t		avg_snr;
} __attribute__((packed,aligned(4)));

struct moca_rx_map_profile {
	uint32_t		nbas;
	uint32_t		preamble_type;
	uint32_t		cp;
	uint32_t		pad;
	uint32_t		rx_gain;
	uint32_t		bit_loading[32];
	uint32_t		avg_snr;
} __attribute__((packed,aligned(4)));

struct moca_node_stats {
	uint32_t		tx_packets;
	uint32_t		rx_packets;
	uint32_t		rx_cw_unerror;
	uint32_t		rx_cw_corrected;
	uint32_t		rx_cw_uncorrected;
	uint32_t		rx_no_sync;
	uint32_t		rx_no_energy;
} __attribute__((packed,aligned(4)));

struct moca_node_stats_ext {
	uint8_t			rx_uc_crc_error;
	uint8_t			rx_uc_timeout_error;
	uint8_t			rx_bc_crc_error;
	uint8_t			rx_bc_timeout_error;
	uint8_t			rx_map_crc_error;
	uint8_t			rx_map_timeout_error;
	uint8_t			rx_beacon_crc_error;
	uint8_t			rx_beacon_timeout_error;
	uint8_t			rx_rr_crc_error;
	uint8_t			rx_rr_timeout_error;
	uint8_t			rx_lc_crc_error;
	uint8_t			rx_lc_timeout_error;
	uint8_t			rx_p1_error;
	uint8_t			rx_p2_error;
	uint8_t			rx_p3_error;
	uint8_t			rx_p1_gcd_error;
} __attribute__((packed,aligned(4)));

struct moca_uc_fwd {
	uint32_t		mac_addr_hi;
	uint32_t		mac_addr_lo;
	uint32_t		moca_dest_node_id;
} __attribute__((packed,aligned(4)));

struct moca_mc_fwd_rd {
	uint32_t		multicast_mac_addr_hi;
	uint32_t		multicast_mac_addr_lo;
	uint32_t		dest_node_id;
} __attribute__((packed,aligned(4)));

struct moca_mc_fwd_wr {
	uint32_t		multicast_mac_addr_hi;
	uint32_t		multicast_mac_addr_lo;
	uint32_t		dest_mac_addr1_hi;
	uint32_t		dest_mac_addr1_lo;
	uint32_t		dest_mac_addr2_hi;
	uint32_t		dest_mac_addr2_lo;
	uint32_t		dest_mac_addr3_hi;
	uint32_t		dest_mac_addr3_lo;
	uint32_t		dest_mac_addr4_hi;
	uint32_t		dest_mac_addr4_lo;
} __attribute__((packed,aligned(4)));

struct moca_src_addr {
	uint32_t		mac_addr_hi;
	uint32_t		mac_addr_lo;
	uint32_t		moca_node_id;
} __attribute__((packed,aligned(4)));

struct moca_drv_info {
	uint32_t		version;
	uint32_t		build_number;
	uint32_t		hw_rev;
	uint32_t		uptime;
	uint32_t		link_uptime;
	uint32_t		core_uptime;
	int8_t			ifname[16];
	int8_t			devname[64];
} __attribute__((packed,aligned(4)));

struct moca_password {
	int8_t			password[32];
} __attribute__((packed,aligned(4)));

struct moca_ext_octet_count {
	uint32_t		in_octets_hi;
	uint32_t		in_octets_lo;
	uint32_t		out_octets_hi;
	uint32_t		out_octets_lo;
} __attribute__((packed,aligned(4)));

struct moca_snr_data {
	uint8_t			data[8192];
} __attribute__((packed,aligned(4)));

struct moca_iq_data {
	uint8_t			data[1024];
} __attribute__((packed,aligned(4)));

struct moca_fw_file {
	uint8_t			fw_file[128];
} __attribute__((packed,aligned(4)));

struct moca_cir_data {
	uint8_t			data[1024];
} __attribute__((packed,aligned(4)));

struct moca_pqos_table {
	uint32_t		flow_id_hi;
	uint32_t		flow_id_lo;
	uint32_t		talker_hi;
	uint32_t		talker_lo;
	uint32_t		lease_time;
	uint32_t		vlan_prio;
	uint32_t		vlan_id;
	uint32_t		egress_node_mask;
	uint32_t		create_time;
} __attribute__((packed,aligned(4)));

struct moca_key_times {
	uint32_t		tekTime;
	uint32_t		tekLastInterval;
	uint32_t		tekEvenOdd;
	uint32_t		pmkTime;
	uint32_t		pmkLastInterval;
	uint32_t		pmkEvenOdd;
} __attribute__((packed,aligned(4)));

struct moca_init_time_options {
	uint32_t		const_tx_mode;
	uint32_t		const_tx_sc1;
	uint32_t		const_tx_sc2;
} __attribute__((packed,aligned(4)));

struct moca_node_stats_ext_acc {
	uint32_t		rx_uc_crc_error;
	uint32_t		rx_uc_timeout_error;
	uint32_t		rx_bc_crc_error;
	uint32_t		rx_bc_timeout_error;
	uint32_t		rx_map_crc_error;
	uint32_t		rx_map_timeout_error;
	uint32_t		rx_beacon_crc_error;
	uint32_t		rx_beacon_timeout_error;
	uint32_t		rx_rr_crc_error;
	uint32_t		rx_rr_timeout_error;
	uint32_t		rx_lc_crc_error;
	uint32_t		rx_lc_timeout_error;
	uint32_t		rx_p1_error;
	uint32_t		rx_p2_error;
	uint32_t		rx_p3_error;
	uint32_t		rx_p1_gcd_error;
} __attribute__((packed,aligned(4)));

struct moca_error_to_mask {
	int32_t			error1;
	int32_t			error2;
	int32_t			error3;
} __attribute__((packed,aligned(4)));

struct moca_lmo_info {
	uint32_t		lmo_node_id;
	uint32_t		lmo_duration_sec;
	uint32_t		is_lmo_success;
} __attribute__((packed,aligned(4)));

struct moca_key_changed {
	uint32_t		tekpmk;
	uint32_t		evenodd;
} __attribute__((packed,aligned(4)));

struct moca_pqos_create_response {
	uint32_t		flowid_hi;
	uint32_t		flowid_lo;
	uint32_t		responsecode;
	uint32_t		decision;
	uint32_t		flowtag;
	uint32_t		ingressnodeid;
	uint32_t		egressnodebitmask;
	uint32_t		flowda_hi;
	uint32_t		flowda_lo;
	uint32_t		maxpeakdatarate;
	uint32_t		tpacketsize;
	uint32_t		maxburstsize;
	uint32_t		tleasetime;
	uint32_t		totalstps;
	uint32_t		totaltxps;
	uint32_t		flowstps;
	uint32_t		flowtxps;
} __attribute__((packed,aligned(4)));

struct moca_pqos_create_complete {
	uint32_t		flowid_hi;
	uint32_t		flowid_lo;
	uint32_t		responsecode;
	uint32_t		decision;
	uint32_t		flowtag;
	uint32_t		ingressnodeid;
	uint32_t		egressnodebitmask;
	uint32_t		flowda_hi;
	uint32_t		flowda_lo;
	uint32_t		maxpeakdatarate;
	uint32_t		tpacketsize;
	uint32_t		maxburstsize;
	uint32_t		tleasetime;
	uint32_t		totalstps;
	uint32_t		totaltxps;
	uint32_t		flowstps;
	uint32_t		flowtxps;
} __attribute__((packed,aligned(4)));

struct moca_pqos_update_response {
	uint32_t		flowid_hi;
	uint32_t		flowid_lo;
	uint32_t		responsecode;
	uint32_t		decision;
	uint32_t		flowtag;
	uint32_t		flowda_hi;
	uint32_t		flowda_lo;
	uint32_t		maxpeakdatarate;
	uint32_t		tpacketsize;
	uint32_t		maxburstsize;
	uint32_t		tleasetime;
	uint32_t		totalstps;
	uint32_t		totaltxps;
	uint32_t		flowstps;
	uint32_t		flowtxps;
} __attribute__((packed,aligned(4)));

struct moca_pqos_update_complete {
	uint32_t		flowid_hi;
	uint32_t		flowid_lo;
	uint32_t		responsecode;
	uint32_t		decision;
	uint32_t		flowtag;
	uint32_t		flowda_hi;
	uint32_t		flowda_lo;
	uint32_t		maxpeakdatarate;
	uint32_t		tpacketsize;
	uint32_t		maxburstsize;
	uint32_t		tleasetime;
	uint32_t		totalstps;
	uint32_t		totaltxps;
	uint32_t		flowstps;
	uint32_t		flowtxps;
} __attribute__((packed,aligned(4)));

struct moca_pqos_delete_response {
	uint32_t		flowid_hi;
	uint32_t		flowid_lo;
	uint32_t		responsecode;
} __attribute__((packed,aligned(4)));

struct moca_pqos_delete_complete {
	uint32_t		flowid_hi;
	uint32_t		flowid_lo;
	uint32_t		responsecode;
} __attribute__((packed,aligned(4)));

struct moca_pqos_list_response {
	uint32_t		responsecode;
	uint32_t		ingressnodeid;
	uint32_t		flowid0_hi;
	uint32_t		flowid0_lo;
	uint32_t		flowid1_hi;
	uint32_t		flowid1_lo;
	uint32_t		flowid2_hi;
	uint32_t		flowid2_lo;
	uint32_t		flowid3_hi;
	uint32_t		flowid3_lo;
	uint32_t		flowid4_hi;
	uint32_t		flowid4_lo;
	uint32_t		flowid5_hi;
	uint32_t		flowid5_lo;
	uint32_t		flowid6_hi;
	uint32_t		flowid6_lo;
	uint32_t		flowid7_hi;
	uint32_t		flowid7_lo;
	uint32_t		flowid8_hi;
	uint32_t		flowid8_lo;
	uint32_t		flowid9_hi;
	uint32_t		flowid9_lo;
	uint32_t		flowid10_hi;
	uint32_t		flowid10_lo;
	uint32_t		flowid11_hi;
	uint32_t		flowid11_lo;
	uint32_t		flowid12_hi;
	uint32_t		flowid12_lo;
	uint32_t		flowid13_hi;
	uint32_t		flowid13_lo;
	uint32_t		flowid14_hi;
	uint32_t		flowid14_lo;
	uint32_t		flowid15_hi;
	uint32_t		flowid15_lo;
	uint32_t		flowid16_hi;
	uint32_t		flowid16_lo;
	uint32_t		flowid17_hi;
	uint32_t		flowid17_lo;
	uint32_t		flowid18_hi;
	uint32_t		flowid18_lo;
	uint32_t		flowid19_hi;
	uint32_t		flowid19_lo;
	uint32_t		flowid20_hi;
	uint32_t		flowid20_lo;
	uint32_t		flowid21_hi;
	uint32_t		flowid21_lo;
	uint32_t		flowid22_hi;
	uint32_t		flowid22_lo;
	uint32_t		flowid23_hi;
	uint32_t		flowid23_lo;
	uint32_t		flowid24_hi;
	uint32_t		flowid24_lo;
	uint32_t		flowid25_hi;
	uint32_t		flowid25_lo;
	uint32_t		flowid26_hi;
	uint32_t		flowid26_lo;
	uint32_t		flowid27_hi;
	uint32_t		flowid27_lo;
	uint32_t		flowid28_hi;
	uint32_t		flowid28_lo;
	uint32_t		flowid29_hi;
	uint32_t		flowid29_lo;
	uint32_t		flowid30_hi;
	uint32_t		flowid30_lo;
	uint32_t		flowid31_hi;
	uint32_t		flowid31_lo;
} __attribute__((packed,aligned(4)));

struct moca_pqos_query_response {
	uint32_t		responsecode;
	uint32_t		leasetimeleft;
	uint32_t		flowid_hi;
	uint32_t		flowid_lo;
	uint16_t		tpacketsize;
	uint8_t			reserved_0;
	uint8_t			ingressnodeid;
	uint8_t			reserved_1[3];
	uint8_t			egressnodeid;
	uint32_t		flowtag;
	uint32_t		packetda_hi;
	uint32_t		packetda_lo;
	uint32_t		tpeakdatarate;
	uint32_t		tleasetime;
	uint8_t			tburstsize;
	uint8_t			reserved_2[3];
} __attribute__((packed,aligned(4)));

struct moca_pqos_maintenance_complete {
	uint32_t		iocovercommit;
	uint32_t		allocatedstps;
	uint32_t		allocatedtxps;
} __attribute__((packed,aligned(4)));

struct moca_fmr_response {
	uint32_t		responsecode;
	uint32_t		responded_node_0;
	uint16_t		fmrinfo_node_0[16];
	uint32_t		responded_node_1;
	uint16_t		fmrinfo_node_1[16];
	uint32_t		responded_node_2;
	uint16_t		fmrinfo_node_2[16];
	uint32_t		responded_node_3;
	uint16_t		fmrinfo_node_3[16];
	uint32_t		responded_node_4;
	uint16_t		fmrinfo_node_4[16];
	uint32_t		responded_node_5;
	uint16_t		fmrinfo_node_5[16];
	uint32_t		responded_node_6;
	uint16_t		fmrinfo_node_6[16];
	uint32_t		responded_node_7;
	uint16_t		fmrinfo_node_7[16];
	uint32_t		responded_node_8;
	uint16_t		fmrinfo_node_8[16];
} __attribute__((packed,aligned(4)));

struct moca_mr_response {
	uint32_t		ResponseCode;
	uint32_t		ResetStatus;
	uint32_t		NonDefSeqNum;
	uint8_t			n00ResetStatus;
	uint8_t			n00RspCode;
	uint8_t			n01ResetStatus;
	uint8_t			n01RspCode;
	uint8_t			n02ResetStatus;
	uint8_t			n02RspCode;
	uint8_t			n03ResetStatus;
	uint8_t			n03RspCode;
	uint8_t			n04ResetStatus;
	uint8_t			n04RspCode;
	uint8_t			n05ResetStatus;
	uint8_t			n05RspCode;
	uint8_t			n06ResetStatus;
	uint8_t			n06RspCode;
	uint8_t			n07ResetStatus;
	uint8_t			n07RspCode;
	uint8_t			n08ResetStatus;
	uint8_t			n08RspCode;
	uint8_t			n09ResetStatus;
	uint8_t			n09RspCode;
	uint8_t			n10ResetStatus;
	uint8_t			n10RspCode;
	uint8_t			n11ResetStatus;
	uint8_t			n11RspCode;
	uint8_t			n12ResetStatus;
	uint8_t			n12RspCode;
	uint8_t			n13ResetStatus;
	uint8_t			n13RspCode;
	uint8_t			n14ResetStatus;
	uint8_t			n14RspCode;
	uint8_t			n15ResetStatus;
	uint8_t			n15RspCode;
} __attribute__((packed,aligned(4)));

struct moca_mr_complete {
	uint32_t		ResponseCode;
	uint32_t		ResetStatus;
	uint32_t		NonDefSeqNum;
	uint8_t			n00ResetStatus;
	uint8_t			n00RspCode;
	uint8_t			n01ResetStatus;
	uint8_t			n01RspCode;
	uint8_t			n02ResetStatus;
	uint8_t			n02RspCode;
	uint8_t			n03ResetStatus;
	uint8_t			n03RspCode;
	uint8_t			n04ResetStatus;
	uint8_t			n04RspCode;
	uint8_t			n05ResetStatus;
	uint8_t			n05RspCode;
	uint8_t			n06ResetStatus;
	uint8_t			n06RspCode;
	uint8_t			n07ResetStatus;
	uint8_t			n07RspCode;
	uint8_t			n08ResetStatus;
	uint8_t			n08RspCode;
	uint8_t			n09ResetStatus;
	uint8_t			n09RspCode;
	uint8_t			n10ResetStatus;
	uint8_t			n10RspCode;
	uint8_t			n11ResetStatus;
	uint8_t			n11RspCode;
	uint8_t			n12ResetStatus;
	uint8_t			n12RspCode;
	uint8_t			n13ResetStatus;
	uint8_t			n13RspCode;
	uint8_t			n14ResetStatus;
	uint8_t			n14RspCode;
	uint8_t			n15ResetStatus;
	uint8_t			n15RspCode;
} __attribute__((packed,aligned(4)));

int moca_get_init_time(void *vctx, struct moca_init_time *out);
int moca_set_init_time(void *vctx, const struct moca_init_time *in);

int moca_get_max_frame_size(void *vctx, uint32_t *bytes);
int moca_set_max_frame_size(void *vctx, uint32_t bytes);

int moca_get_max_transmit_time(void *vctx, uint32_t *usec);
int moca_set_max_transmit_time(void *vctx, uint32_t usec);

int moca_get_min_bw_alarm_threshold(void *vctx, uint32_t *mbps);
int moca_set_min_bw_alarm_threshold(void *vctx, uint32_t mbps);

int moca_set_ooo_lmo(void *vctx, uint32_t node_id);

int moca_get_config_reserved_1(void *vctx, uint32_t *val);
int moca_set_config_reserved_1(void *vctx, uint32_t val);

int moca_get_config_reserved_2(void *vctx, uint32_t *val);
int moca_set_config_reserved_2(void *vctx, uint32_t val);

int moca_get_config_reserved_3(void *vctx, uint32_t *val);
int moca_set_config_reserved_3(void *vctx, uint32_t val);

int moca_get_continuous_ie_rr_insert(void *vctx, uint32_t *bool_val);
int moca_set_continuous_ie_rr_insert(void *vctx, uint32_t bool_val);

int moca_get_continuous_ie_map_insert(void *vctx, uint32_t *bool_val);
int moca_set_continuous_ie_map_insert(void *vctx, uint32_t bool_val);

int moca_get_max_pkt_aggr(void *vctx, uint32_t *pkts);
int moca_set_max_pkt_aggr(void *vctx, uint32_t pkts);

int moca_get_max_constellation(void *vctx, uint32_t node_id, uint32_t *bits_per_carrier);
int moca_set_max_constellation(void *vctx, const struct moca_max_constellation *in);

int moca_set_sig_y_done(void *vctx, const struct moca_sig_y_done *in);

int moca_get_pmk_exchange_interval(void *vctx, uint32_t *msec);
int moca_set_pmk_exchange_interval(void *vctx, uint32_t msec);

int moca_get_tek_exchange_interval(void *vctx, uint32_t *msec);
int moca_set_tek_exchange_interval(void *vctx, uint32_t msec);

int moca_get_priority_allocations(void *vctx, struct moca_priority_allocations *out);
int moca_set_priority_allocations(void *vctx, const struct moca_priority_allocations *in);

int moca_get_snr_margin_table(void *vctx, struct moca_snr_margin_table *out);
int moca_set_snr_margin_table(void *vctx, struct moca_snr_margin_table *out);

int moca_get_nominal_map_cycle(void *vctx, uint32_t *usec);
int moca_set_nominal_map_cycle(void *vctx, uint32_t usec);

int moca_get_max_inc_map_cycle(void *vctx, uint32_t *usec);
int moca_set_max_inc_map_cycle(void *vctx, uint32_t usec);

int moca_get_max_dec_map_cycle(void *vctx, uint32_t *usec);
int moca_set_max_dec_map_cycle(void *vctx, uint32_t usec);

int moca_get_target_phy_rate_qam128(void *vctx, uint32_t *mbps);
int moca_set_target_phy_rate_qam128(void *vctx, uint32_t mbps);

int moca_get_target_phy_rate_qam256(void *vctx, uint32_t *mbps);
int moca_set_target_phy_rate_qam256(void *vctx, uint32_t mbps);

int moca_get_moca_core_trace_enable(void *vctx, uint32_t *bool_val);
int moca_set_moca_core_trace_enable(void *vctx, uint32_t bool_val);

int moca_get_sapm_en(void *vctx, uint32_t *bool_val);
int moca_set_sapm_en(void *vctx, uint32_t bool_val);

int moca_get_arpl_th(void *vctx, int32_t *arpl);
int moca_set_arpl_th(void *vctx, int32_t arpl);

int moca_get_sapm_table(void *vctx, struct moca_sapm_table *out);
int moca_set_sapm_table(void *vctx, struct moca_sapm_table *out);

int moca_get_rlapm_en(void *vctx, uint32_t *bool_val);
int moca_set_rlapm_en(void *vctx, uint32_t bool_val);

int moca_get_rlapm_table(void *vctx, struct moca_rlapm_table *out);
int moca_set_rlapm_table(void *vctx, struct moca_rlapm_table *out);

int moca_set_assigned_channel_set(void *vctx, uint32_t channel);

int moca_get_pss_en(void *vctx, uint32_t *enable);
int moca_set_pss_en(void *vctx, uint32_t enable);

int moca_get_freq_shift(void *vctx, uint32_t *direction);
int moca_set_freq_shift(void *vctx, uint32_t direction);

int moca_set_egr_mc_addr_filter(void *vctx, const struct moca_egr_mc_addr_filter *in);

int moca_get_egr_mc_addr_filter_get(void *vctx, uint32_t entryid, struct moca_egr_mc_addr_filter_get *out);

int moca_get_rx_power_tuning(void *vctx, uint32_t *val);
int moca_set_rx_power_tuning(void *vctx, uint32_t val);

int moca_get_lab_pilots(void *vctx, struct moca_lab_pilots *out);

int moca_set_lab_iq_diagram_set(void *vctx, const struct moca_lab_iq_diagram_set *in);

int moca_set_lab_snr_graph_set(void *vctx, uint32_t node_id);

int moca_get_lab_register(void *vctx, uint32_t address, uint32_t *data);
int moca_set_lab_register(void *vctx, const struct moca_lab_register *in);

int moca_get_lab_call_func(void *vctx, uint32_t *retval);
int moca_set_lab_call_func(void *vctx, const struct moca_lab_call_func *in);

int moca_set_lab_tpcap(void *vctx, const struct moca_lab_tpcap *in);

int moca_set_fmr_request(void *vctx, struct moca_fmr_request *out);

int moca_set_pqos_create_request(void *vctx, struct moca_pqos_create_request *out);

int moca_set_pqos_ingr_add_flow(void *vctx, const struct moca_pqos_ingr_add_flow *in);

int moca_set_pqos_update_request(void *vctx, struct moca_pqos_update_request *out);

int moca_set_pqos_ingr_update(void *vctx, const struct moca_pqos_ingr_update *in);

int moca_set_pqos_delete_request(void *vctx, struct moca_pqos_delete_request *out);

int moca_set_pqos_ingr_delete(void *vctx, const struct moca_pqos_ingr_delete *in);

int moca_set_pqos_list_request(void *vctx, struct moca_pqos_list_request *out);

int moca_set_pqos_query_request(void *vctx, struct moca_pqos_query_request *out);

int moca_set_pqos_maintenance_start(void *vctx);

int moca_set_mr_request(void *vctx, struct moca_mr_request *out);

int moca_get_gen_status(void *vctx, struct moca_gen_status *out);

int moca_get_ext_status(void *vctx, struct moca_ext_status *out);

int moca_get_gen_stats(void *vctx, struct moca_gen_stats *out);

int moca_get_ext_stats(void *vctx, struct moca_ext_stats *out);

int moca_get_gen_node_status(void *vctx, uint32_t idx, struct moca_gen_node_status *out);

int moca_get_tx_profile(void *vctx, uint32_t idx, struct moca_tx_profile *out);

int moca_get_rx_uc_profile(void *vctx, uint32_t idx, struct moca_rx_uc_profile *out);

int moca_get_rx_bc_profile(void *vctx, uint32_t idx, struct moca_rx_bc_profile *out);

int moca_get_rx_map_profile(void *vctx, uint32_t idx, struct moca_rx_map_profile *out);

int moca_get_node_stats(void *vctx, uint32_t idx, struct moca_node_stats *out);

int moca_get_node_stats_ext(void *vctx, uint32_t idx, struct moca_node_stats_ext *out);

int moca_get_uc_fwd(void *vctx, struct moca_uc_fwd *out, int max_out_len);

int moca_get_mc_fwd_rd(void *vctx, struct moca_mc_fwd_rd *out, int max_out_len);

int moca_add_mc_fwd_wr(void *vctx, const struct moca_mc_fwd_wr *entry);
int moca_del_mc_fwd_wr(void *vctx, const struct moca_mc_fwd_wr *entry);

int moca_get_src_addr(void *vctx, struct moca_src_addr *out, int max_out_len);

int moca_set_start(void *vctx);

int moca_set_stop(void *vctx);

int moca_get_drv_info(void *vctx, struct moca_drv_info *out);

int moca_get_password(void *vctx, struct moca_password *out);
int moca_set_password(void *vctx, struct moca_password *out);

int moca_get_ext_octet_count(void *vctx, struct moca_ext_octet_count *out);

int moca_set_reset_stats(void *vctx);

int moca_get_snr_data(void *vctx, struct moca_snr_data *out);

int moca_get_iq_data(void *vctx, struct moca_iq_data *out);

int moca_set_fw_file(void *vctx, struct moca_fw_file *out);

int moca_get_verbose(void *vctx, uint32_t *level);
int moca_set_verbose(void *vctx, uint32_t level);

int moca_get_moca_const_tx_mode(void *vctx, uint32_t *state);

int moca_get_cir_data(void *vctx, uint32_t node, struct moca_cir_data *out);

int moca_set_restore_defaults(void *vctx);

int moca_get_pqos_table(void *vctx, struct moca_pqos_table *out, int max_out_len);
int moca_add_pqos_table(void *vctx, const struct moca_pqos_table *entry);
int moca_del_pqos_table(void *vctx, const struct moca_pqos_table *entry);

int moca_get_key_times(void *vctx, struct moca_key_times *out);

int moca_set_init_time_options(void *vctx, const struct moca_init_time_options *in);
int moca_get_init_time_options(void *vctx, struct moca_init_time_options *out);

int moca_get_node_stats_ext_acc(void *vctx, uint32_t idx, struct moca_node_stats_ext_acc *out);

int moca_set_error_to_mask(void *vctx, const struct moca_error_to_mask *in);
int moca_get_error_to_mask(void *vctx, struct moca_error_to_mask *out);

int moca_set_message(void *vctx, uint32_t id);

void moca_register_power_up_status_cb(void *vctx, void (*callback)(void *userarg, uint32_t status), void *userarg);

void moca_register_link_up_state_cb(void *vctx, void (*callback)(void *userarg, uint32_t status), void *userarg);

void moca_register_admission_status_cb(void *vctx, void (*callback)(void *userarg, uint32_t status), void *userarg);

void moca_register_limited_bw_cb(void *vctx, void (*callback)(void *userarg, uint32_t bw_status), void *userarg);

void moca_register_error_cb(void *vctx, void (*callback)(void *userarg, uint32_t error_id), void *userarg);

void moca_register_lmo_info_cb(void *vctx, void (*callback)(void *userarg, struct moca_lmo_info *out), void *userarg);

void moca_register_key_changed_cb(void *vctx, void (*callback)(void *userarg, struct moca_key_changed *out), void *userarg);

void moca_register_topology_changed_cb(void *vctx, void (*callback)(void *userarg, uint32_t nodemask), void *userarg);

void moca_register_moca_version_changed_cb(void *vctx, void (*callback)(void *userarg, uint32_t active_nodes), void *userarg);

void moca_register_pqos_create_response_cb(void *vctx, void (*callback)(void *userarg, struct moca_pqos_create_response *out), void *userarg);

void moca_register_pqos_create_complete_cb(void *vctx, void (*callback)(void *userarg, struct moca_pqos_create_complete *out), void *userarg);

void moca_register_pqos_update_response_cb(void *vctx, void (*callback)(void *userarg, struct moca_pqos_update_response *out), void *userarg);

void moca_register_pqos_update_complete_cb(void *vctx, void (*callback)(void *userarg, struct moca_pqos_update_complete *out), void *userarg);

void moca_register_pqos_delete_response_cb(void *vctx, void (*callback)(void *userarg, struct moca_pqos_delete_response *out), void *userarg);

void moca_register_pqos_delete_complete_cb(void *vctx, void (*callback)(void *userarg, struct moca_pqos_delete_complete *out), void *userarg);

void moca_register_pqos_list_response_cb(void *vctx, void (*callback)(void *userarg, struct moca_pqos_list_response *out), void *userarg);

void moca_register_pqos_query_response_cb(void *vctx, void (*callback)(void *userarg, struct moca_pqos_query_response *out), void *userarg);

void moca_register_pqos_maintenance_complete_cb(void *vctx, void (*callback)(void *userarg, struct moca_pqos_maintenance_complete *out), void *userarg);

void moca_register_fmr_response_cb(void *vctx, void (*callback)(void *userarg, struct moca_fmr_response *out), void *userarg);

void moca_register_mr_response_cb(void *vctx, void (*callback)(void *userarg, struct moca_mr_response *out), void *userarg);

void moca_register_mr_complete_cb(void *vctx, void (*callback)(void *userarg, struct moca_mr_complete *out), void *userarg);

void moca_register_moca_reset_request_cb(void *vctx, void (*callback)(void *userarg), void *userarg);

void moca_register_lof_cb(void *vctx, void (*callback)(void *userarg, uint32_t lof), void *userarg);

/* GENERATED API ABOVE THIS LINE - DO NOT EDIT */

#ifdef __cplusplus
}
#endif

#endif /* ! _MOCALIB_H_ */
