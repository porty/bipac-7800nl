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
#ifndef BCM_PLOAM_API_H
#define BCM_PLOAM_API_H

#include "bcm_gpon_api_common.h"

/**
 * PLOAM Driver user API
 **/

/*Parameter Tags indicating whether the parameter is an input, output, or input/output argument*/
#ifndef IN
#define IN
#endif /*IN*/

#ifndef OUT
#define OUT
#endif /*OUT*/

#ifndef INOUT
#define INOUT
#endif /*INOUT*/

/*Device names*/
#define BCM_PLOAM_DEVICE_NAME     "bcm_ploam"
#define BCM_PLOAM_USR_DEVICE_NAME "bcm_user_ploam"

#if defined(CONFIG_BCM_GPON_FPGA)
#define BCM_PLOAM_NUM_DATA_TCONTS 2
#define BCM_PLOAM_NUM_DATA_GEM_PORTS 4
#else /*!FPGA:*/
#define BCM_PLOAM_NUM_DATA_TCONTS 32
#define BCM_PLOAM_NUM_DATA_GEM_PORTS 32
#endif /*CONFIG_GPON_FPGA*/

/**
 * Ploam Driver ioctl command IDs
 **/
#define BCM_PLOAM_IOC_INIT                       10  /*Return codes: 0*/
#define BCM_PLOAM_IOC_GET_EVENT_STATUS           11  /*Return codes: 0*/
#define BCM_PLOAM_IOC_MASK_EVENT                 12  /*Return codes: 0*/
#define BCM_PLOAM_IOC_GET_ALARM_STATUS           13  /*Return codes: 0*/
#define BCM_PLOAM_IOC_MASK_ALARM                 14  /*Return codes: 0*/
#define BCM_PLOAM_IOC_SET_SF_SD_THRESHOLD        15  /*Return codes: 0, EINVAL_PLOAM_ARG*/
#define BCM_PLOAM_IOC_GET_SF_SD_THRESHOLD        16  /*Return codes: 0*/
#define BCM_PLOAM_IOC_REGISTER_MSG               17  /*Return codes: 0, EINVAL_PLOAM_DUPLICATE*/
#define BCM_PLOAM_IOC_UNREGISTER_MSG             18  /*Return codes: 0, EINVAL*/
#define BCM_PLOAM_IOC_START                      19  /*Return codes: 0, EINVAL_PLOAM_STATE, EINVAL_INIT_OPER_STATE*/
#define BCM_PLOAM_IOC_STOP                       20  /*Return codes: 0, EINVAL*/
#define BCM_PLOAM_IOC_GET_STATE                  21  /*Return codes: 0*/
#define BCM_PLOAM_IOC_GET_MESSAGE_COUNTERS       22  /*Return codes: 0*/
#define BCM_PLOAM_IOC_GET_GTC_COUNTERS           23  /*Return codes: 0*/
#define BCM_PLOAM_IOC_GET_GEM_PORT_COUNTERS      24  /*Return codes: 0, EINVAL_PLOAM_GEM_PORT*/
/*Return codes: 0, EINVAL_PLOAM_ARG, EINVAL_PLOAM_GEM_PORT, EINVAL_PLOAM_DUPLICATE, EINVAL_PLOAM_NOENT*/
#define BCM_PLOAM_IOC_CFG_GEM_PORT               25
/*Return codes: 0, EINVAL_PLOAM_GEM_PORT, EINVAL_PLOAM_STATE, EINVAL_PLOAM_ARG*/
#define BCM_PLOAM_IOC_CFG_GEM_PORT_QOS           26
#define BCM_PLOAM_IOC_DECFG_GEM_PORT             27 /*Return codes: 0, EINVAL_PLOAM_GEM_PORT, EINVAL_PLOAM_ARG*/
#define BCM_PLOAM_IOC_ENABLE_GEM_PORT            28 /*Return codes: 0, EINVAL_PLOAM_GEM_PORT, EINVAL_PLOAM_ARG*/
#define BCM_PLOAM_IOC_GET_GEM_PORT_CFG           29 /*Return codes: 0, EINVAL_PLOAM_GEM_PORT, EINVAL_PLOAM_ARG*/
#define BCM_PLOAM_IOC_GET_ALLOC_IDS              31 /*Return codes: 0*/
#define BCM_PLOAM_IOC_GET_OMCI_PORT_INFO         32 /*Return codes: 0*/
#define BCM_PLOAM_IOC_SET_1ST_SN_PREAMBLE        33 /*Return codes: EINVAL_PLOAM_STATE*/
#define BCM_PLOAM_IOC_GET_GTC_PARAMS             34 /*Return codes: 0*/
#define BCM_PLOAM_IOC_GET_ONU_ID                 35 /*Return codes: 0, ENODATA*/
#define BCM_PLOAM_IOC_GET_FEC_MODE               36 /*Return codes: 0*/
#define BCM_PLOAM_IOC_GET_ENCRYPTION_KEY         37 /*Return codes: 0, ENODATA, EINVAL_PLOAM_STATE*/
#define BCM_PLOAM_IOC_SET_SERIAL_PASSWD          38 /*Return codes: 0*/
#define BCM_PLOAM_IOC_GET_SERIAL_PASSWD          39 /*Return codes: 0*/
#define BCM_PLOAM_IOC_GET_DRIVER_VERSION         40 /*Return codes: 0*/
#define BCM_PLOAM_IOC_CFG_GEM_PORT_GTCDS         41 /*Return codes: EINVAL_PLOAM_GEM_PORT, EINVAL_PLOAM_ARG, EINVAL_PLOAM_STATE*/
#define BCM_PLOAM_IOC_GTCDS_CFG                  42 /*Return codes: 0*/
#define BCM_PLOAM_IOC_MCAST_FILTER_ENTRY         43 /*Return codes: EINVAL_PLOAM_ARG, EINVAL_PLOAM_NOENT*/
#define BCM_PLOAM_IOC_GTCUS_CFG                  44 /*Return codes: EINVAL_PLOAM_ARG, EINVAL_PLOAM_STATE*/
#define BCM_PLOAM_IOC_GET_REGISTERED_MSGS        45 /*Return codes: 0*/
#define BCM_PLOAM_IOC_GEN_PRBS                   46 /*Return codes: EINVAL_PLOAM_ARG*/
#define BCM_OPTICS_IOC_IF_CFG                    47 /*Return codes: 0*/
#define BCM_OPTICS_IOC_GET_IF_CFG                48 /*Return codes: 0*/
#define BCM_AE_IOC_MODE                          49 /*Return codes: EINVAL_PLOAM_STATE*/
#define BCM_AE_IOC_STATUS                        50 /*Return codes: EINVAL_PLOAM_STATE*/
#define BCM_PLOAM_IOC_SET_TO1_TO2                51 /*Return codes: EINVAL_PLOAM_ARG*/
#define BCM_PLOAM_IOC_GET_TO1_TO2                52 /*Return codes: 0*/
#define BCM_PLOAM_IOC_SET_ALARM_SOAK_TIME        53 /*Return codes: EINVAL_PLOAM_NOENT*/
#define BCM_PLOAM_IOC_GET_ALARM_SOAK_TIME        54 /*Return codes: EINVAL_PLOAM_NOENT*/

/*Ploam Driver Event IDs*/
#define BCM_PLOAM_EVENT_ONU_STATE_CHANGE       (1<<0)
#define BCM_PLOAM_EVENT_ALARM                  (1<<1)
#define BCM_PLOAM_EVENT_OMCI_PORT_ID           (1<<2)
#define BCM_PLOAM_EVENT_USER_PLOAM_RX_OVERFLOW (1<<3)
#define BCM_PLOAM_EVENT_USER_PLOAM_TX_OVERFLOW (1<<4)

/*Type of ioctl argument pointer for commands BCM_PLOAM_IOC_GET_EVENT_STATUS*/
typedef struct {
  UINT32 eventBitmap; /*Bitwise OR of BCM_PLOAM_EVENT_* flags*/
  UINT32 eventMask; /*Bitwise OR of BCM_PLOAM_EVENT_* flags*/

} BCM_Ploam_EventStatusInfo ;

/*Type of ioctl argument pointer for commands BCM_PLOAM_IOC_MASK_EVENT*/
typedef struct {
  UINT32 eventMask; /*Bitwise OR of BCM_PLOAM_EVENT_* flags*/

} BCM_Ploam_EventMaskInfo ;

/*Ploam Driver Alarms*/
#define BCM_PLOAM_ALARM_ID_APC_FAIL  (1<<0)
#define BCM_PLOAM_ALARM_ID_LOS       (1<<1)
#define BCM_PLOAM_ALARM_ID_LOL       (1<<2)
#define BCM_PLOAM_ALARM_ID_LOF       (1<<3)
#define BCM_PLOAM_ALARM_ID_LCDG      (1<<4)
#define BCM_PLOAM_ALARM_ID_SF        (1<<5)
#define BCM_PLOAM_ALARM_ID_SD        (1<<6)
#define BCM_PLOAM_ALARM_ID_SUF       (1<<7)
#define BCM_PLOAM_ALARM_ID_MEM       (1<<8)
#define BCM_PLOAM_ALARM_ID_DACT      (1<<9)
#define BCM_PLOAM_ALARM_ID_DIS      (1<<10)
#define BCM_PLOAM_ALARM_ID_PEE      (1<<11)

#define BCM_PLOAM_NUM_ALARMS 12

/*Type of ioctl argument pointer for command BCM_PLOAM_IOC_GET_ALARM_STATUS*/
typedef struct {
  OUT UINT32 alarmStatusBitmap; /* Bitwise OR of BCM_PLOAM_ALARM_ID_* flags*/
  OUT UINT32 alarmEventBitmap;  /* Bitwise OR of BCM_PLOAM_ALARM_ID_* flags*/
  OUT UINT32 alarmMaskBitmap;   /* Bitwise OR of BCM_PLOAM_ALARM_ID_* flags*/

} BCM_Ploam_AlarmStatusInfo ;

/*Type of ioctl argument pointer for command BCM_PLOAM_IOC_MASK_ALARM*/
typedef struct {
  IN UINT32 alarmMaskBitmap; /* Bitwise OR of BCM_PLOAM_ALARM_ID_* flags */

} BCM_Ploam_MaskAlarmInfo ;

/*Type of ioctl argument pointer for commands BCM_PLOAM_IOC_SET_SF_SD_THRESHOLD
 *and BCM_PLOAM_IOC_GET_SF_SD_THRESHOLD*/
typedef struct {
  INOUT UINT8 sf_exp; /*Range: [3..8]*/
  INOUT UINT8 sd_exp; /*Range: [sf_exp+1..9]*/

} BCM_Ploam_SFSDthresholdInfo ;

#define BCM_PLOAM_DIRECTION_US 0
#define BCM_PLOAM_DIRECTION_DS 1

#define BCM_PLOAM_NUM_PLOAM_PAYLOAD_BYTES 10

/*Type of object returned when reading from "bcm_user_ploam" device file */
typedef struct {
  UINT16 seqNum;
  UINT8 direction; /*BCM_PLOAM_DIRECTION_US or BCM_PLOAM_DIRECTION_DS*/
  UINT8 onu_id;
  UINT8 msg_id;
  UINT8 payload[BCM_PLOAM_NUM_PLOAM_PAYLOAD_BYTES];
  UINT8 crc;

} BCM_Ploam_Msg;

/*Legacy:*/
typedef BCM_Ploam_Msg BCM_Ploam_msg;


/*Type of ioctl argument pointer for command BCM_PLOAM_IOC_REGISTER_MSG*/
typedef struct {
  IN UBOOL8 registerAll;
  IN UINT8 direction; /*BCM_PLOAM_DIRECTION_US or BCM_PLOAM_DIRECTION_DS*/
  IN UINT8 msgId;

} BCM_Ploam_RegisterMsgInfo;

/*Type of ioctl argument pointer for command BCM_PLOAM_IOC_UNREGISTER_MSG*/
typedef struct {
  IN UBOOL8 unregisterAll;
  IN UINT8 direction; /*BCM_PLOAM_DIRECTION_US or BCM_PLOAM_DIRECTION_DS*/
  IN UINT8 msgId;

} BCM_Ploam_UnregisterMsgInfo ;

/*Type of ioctl argument pointer for BCM_PLOAM_IOC_GET_REGISTERED_MSGS*/
typedef struct {
  OUT UINT32 usMsgMap[8];
  OUT UINT32 dsMsgMap[8];

} BCM_Ploam_RegisteredMsgsInfo;

/*ONU Administrative states*/
typedef enum {
  BCM_PLOAM_ASTATE_OFF=0,
  BCM_PLOAM_ASTATE_ON

} BCM_Ploam_AdminState;

/*ONU Operational states*/
typedef enum {
  BCM_PLOAM_OSTATE_INITIAL_O1=1,
  BCM_PLOAM_OSTATE_STANDBY_O2,
  BCM_PLOAM_OSTATE_SERIAL_NUMBER_O3,
  BCM_PLOAM_OSTATE_RANGING_O4,
  BCM_PLOAM_OSTATE_OPERATION_O5,
  BCM_PLOAM_OSTATE_POPUP_O6,
  BCM_PLOAM_OSTATE_EMERGENCY_STOP_O7,
  BCM_PLOAM_OSTATE_DEACTIVATED_O8

} BCM_Ploam_OperState;

/*Type of ioctl argument pointer for command BCM_PLOAM_IOC_START*/
typedef struct {
  IN UINT8 initOperState; /*BCM_PLOAM_OSTATE_INITIAL_O1 or BCM_PLOAM_OSTATE_EMERGENCY_STOP_O7*/

} BCM_Ploam_StartInfo;

/*Type of ioctl argument pointer for command BCM_PLOAM_IOC_STOP*/
typedef struct {
  IN UBOOL8 sendDyingGasp;

} BCM_Ploam_StopInfo;

/*Type of ioctl argument pointer for command BCM_PLOAM_IOC_GET_STATE*/
typedef struct {
  OUT UINT8 adminState; /*BCM_PLOAM_ASTATE_ON or BCM_PLOAM_ASTATE_OFF*/
  OUT UINT8 operState;  /*BCM_PLOAM_OSTATE_* */

} BCM_Ploam_StateInfo;

/*Legacy:*/
typedef BCM_Ploam_StateInfo BCM_Ploam_stateInfo;


/*Type of ioctl argument pointer for command BCM_PLOAM_IOC_GET_MESSAGE_COUNTERS*/
typedef struct {
  IN UINT32 reset;
  OUT UINT32 crcErrors;
  OUT UINT32 rxPloamsTotal;
  OUT UINT32 rxPloamsUcast;
  OUT UINT32 rxPloamsBcast;
  OUT UINT32 rxPloamsDiscarded;
  OUT UINT32 rxPloamsNonStd;
  OUT UINT32 txPloams;
  OUT UINT32 txPloamsNonStd;

} BCM_Ploam_MessageCounters;

/*Legacy:*/
typedef BCM_Ploam_MessageCounters BCM_Ploam_messageCounters;

/*Type of ioctl argument pointer for command BCM_PLOAM_IOC_GET_GTC_COUNTERS*/
typedef struct {
  IN UINT32 reset;
  OUT UINT32 bipErr;
  OUT UINT32 fecCerr;
  OUT UINT32 fecUerr;
  OUT UINT32 fecCWs;
  OUT UINT32 fecSecs;
  OUT UINT32 hecCerr;
  OUT UINT32 hecUerr;

} BCM_Ploam_GtcCounters;

/*Legacy:*/
typedef BCM_Ploam_GtcCounters BCM_Ploam_gtcCounters;

#define BCM_PLOAM_GEM_PORT_IDX_ALL 0xfffe
#define BCM_PLOAM_GEM_PORT_IDX_UNASSIGNED 0xffff
#define BCM_PLOAM_GEM_PORT_ID_UNASSIGNED 0xffff

/*Type of ioctl argument pointer for command BCM_PLOAM_IOC_GET_GEM_PORT_COUNTERS*/
typedef struct {
  IN UINT32 reset;
 /*Accepted values: [0..BCM_PLOAM_NUM_DATA_GEM_PORTS-1],
  *BCM_PLOAM_GEM_PORT_IDX_ALL and BCM_PLOAM_GEM_PORT_IDX_UNASSIGNED*/
  INOUT UINT16 gemPortIndex;
 /*Accepted values: [0..BCM_PLOAM_MAX_GEM_ID] and
  *BCM_PLOAM_GEM_PORT_ID_UNASSIGNED.*/
  INOUT UINT16 gemPortID;
  OUT UINT32 rxBytes;
  OUT UINT32 txBytes;
  OUT UINT32 rxFragments;
  OUT UINT32 txFragments;
  OUT UINT32 txFrames;
  OUT UINT32 rxFrames;
  OUT UINT32 rxDroppedFrames;
  OUT UINT32 txDroppedFrames;
  OUT UINT32 rxMcastAcceptedFrames;
  OUT UINT32 rxMcastDroppedFrames;

} BCM_Ploam_GemPortCounters;

/*Legacy:*/
typedef BCM_Ploam_GemPortCounters BCM_Ploam_gemPortCounters;

#define BCM_PLOAM_ALLOC_ID_UNASSIGNED 0xffff
#define BCM_PLOAM_MAX_GEM_ID          0x0fff
#define BCM_PLOAM_MAX_ALLOC_ID        0x0fff

/*Type of ioctl argument pointer for command BCM_PLOAM_IOC_CFG_GEM_PORT*/
typedef struct {
 /*Accepted values: [0..BCM_PLOAM_NUM_DATA_GEM_PORTS-1], and BCM_PLOAM_GEM_PORT_IDX_ALLOC
  *to have the driver allocate the port*/
  INOUT UINT16 gemPortIndex;
  IN UINT16 gemPortID; /*Range: [0..BCM_PLOAM_MAX_GEM_ID]*/
 /*Accepted values: [0..BCM_PLOAM_MAX_ALLOC_ID], and BCM_PLOAM_ALLOC_ID_UNASSIGNED
  *for a DS-only GEM Port*/
  IN UINT16 allocID;

} BCM_Ploam_CfgGemPortInfo;

typedef BCM_Ploam_CfgGemPortInfo BCM_Ploam_cfgGemPortInfo;

#define BCM_PLOAM_MAX_PRIORITY 31
#define BCM_PLOAM_MAX_WEIGHT 127

/*Type of ioctl argument pointer for command BCM_PLOAM_IOC_CFG_GEM_PORT_QOS*/
typedef struct {
 /*Accepted values: [0..BCM_PLOAM_NUM_DATA_GEM_PORTS-1],
  *and BCM_PLOAM_GEM_PORT_IDX_UNASSIGNED*/
  INOUT UINT16 gemPortIndex;
 /*Accepted values: [0..BCM_PLOAM_MAX_GEM_ID] and
  *BCM_PLOAM_GEM_PORT_ID_UNASSIGNED.*/
  INOUT UINT16 gemPortID;
  IN UINT8 priority; /*Range: [0..BCM_PLOAM_MAX_PRIORITY]*/
  IN UINT8 weight; /*Range: [0..BCM_PLOAM_MAX_WEIGHT]*/

} BCM_Ploam_CfgGemPortQosInfo;

/*Multicast Filter Mode*/
typedef enum {
  BCM_PLOAM_GTCDS_MCAST_FILTER_OFF=0,
  BCM_PLOAM_GTCDS_MCAST_FILTER_DMAC=1,
  BCM_PLOAM_GTCDS_MCAST_FILTER_DMAC_OVID=2,
  BCM_PLOAM_GTCDS_MCAST_FILTER_DMAC_OVID_IVID=3

} BCM_Ploam_McastFilterMode;

#define BCM_PLOAM_GTCDS_NUM_QUEUES 8

/*Type of ioctl arguement pointer for command BCM_PLOAM_IOC_CFG_GEM_PORT_GTCDS*/
typedef struct {
 /*Accepted values: [0..BCM_PLOAM_NUM_DATA_GEM_PORTS-1],
  *and BCM_PLOAM_GEM_PORT_IDX_UNASSIGNED*/
  INOUT UINT16 gemPortIndex;
 /*Accepted values: [0..BCM_PLOAM_MAX_GEM_ID] and
  *BCM_PLOAM_GEM_PORT_ID_UNASSIGNED.*/
  INOUT UINT16 gemPortID;
  IN UINT8 queueIdx; /*Range: [0..BCM_PLOAM_GTCDS_NUM_QUEUES[*/
  IN UINT8 mcastFilterMode; /*BCM_Ploam_McastFilterMode*/

} BCM_Ploam_CfgGemPortGtcDsInfo;


/*Type of ioctl argument pointer for command BCM_PLOAM_IOC_DECFG_GEM_PORT*/
typedef struct {
 /*Accepted values: [0..BCM_PLOAM_NUM_DATA_GEM_PORTS-1],
  *BCM_PLOAM_GEM_PORT_IDX_ALL and BCM_PLOAM_GEM_PORT_IDX_UNASSIGNED*/
  INOUT UINT16 gemPortIndex;
 /*Accepted values: [0..BCM_PLOAM_MAX_GEM_ID] and
  *BCM_PLOAM_GEM_PORT_ID_UNASSIGNED.*/
  INOUT UINT16 gemPortID;

} BCM_Ploam_DecfgGemPortInfo;

/*Type of ioctl argument pointer for command BCM_PLOAM_IOC_ENABLE_GEM_PORT*/
typedef struct {
 /*Accepted values: [0..BCM_PLOAM_NUM_DATA_GEM_PORTS-1],
  *and BCM_PLOAM_GEM_PORT_IDX_UNASSIGNED*/
  INOUT UINT16 gemPortIndex;
 /*Accepted values: [0..BCM_PLOAM_MAX_GEM_ID] and
  *BCM_PLOAM_GEM_PORT_ID_UNASSIGNED.*/
  INOUT UINT16 gemPortID;
  IN UBOOL8 enable;

} BCM_Ploam_EnableGemPortInfo;

/*Legacy:*/
typedef BCM_Ploam_EnableGemPortInfo BCM_Ploam_enableGemPortInfo;

/*GEM Port Flags*/
#define BCM_PLOAM_GEM_PORT_FLAGS_PORT_ENABLED (1<<0)
#define BCM_PLOAM_GEM_PORT_FLAGS_PORT_ENCRYPTED (1<<1)
#define BCM_PLOAM_GEM_PORT_FLAGS_PORT_OPERATIONAL (1<<2)

/*Type of ioctl argument pointer for command BCM_PLOAM_IOC_GET_GEM_PORT_CFG*/
typedef struct {
 /*Accepted values: [0..BCM_PLOAM_NUM_DATA_GEM_PORTS-1],
  *and BCM_PLOAM_GEM_PORT_IDX_UNASSIGNED*/
  INOUT UINT16 gemPortIndex;
 /*Accepted values: [0..BCM_PLOAM_MAX_GEM_ID] and
  *BCM_PLOAM_GEM_PORT_ID_UNASSIGNED.*/
  INOUT UINT16 gemPortID;
 /*Accepted values: [0..BCM_PLOAM_MAX_ALLOC_ID], or BCM_PLOAM_ALLOC_ID_UNASSIGNED
  *for a DS-only GEM Port*/
  OUT UINT16 allocID;
  OUT UINT16 flags; /*Bitwise OR of BCM_PLOAM_GEM_PORT_FLAGS_* */
  OUT UINT16 priority;
  OUT UINT16 weight;
  OUT UINT8 dsQueueIdx; /*GTCDS output queue. Range: 0..7*/
  OUT UINT8 mcastFilterMode; /*BCM_Ploam_McastFilterMode*/

} BCM_Ploam_GemPortInfo;

/*Legacy:*/
typedef BCM_Ploam_GemPortInfo BCM_Ploam_gemPortInfo;

/*Type of ioctl argument pointer for command BCM_PLOAM_IOC_GET_ALLOC_IDS*/
typedef struct {
  OUT UINT16 numAllocIDs;
  OUT UINT16 allocIDs[BCM_PLOAM_NUM_DATA_TCONTS];

} BCM_Ploam_AllocIDs;

/*Type of ioctl argument pointer for command BCM_PLOAM_IOC_GET_OMCI_PORT_INFO*/
typedef struct {
  OUT UBOOL8 omciGemPortActivated;
  OUT UBOOL8 encrypted;
  OUT UINT16 omciGemPortID;

} BCM_Ploam_OmciPortInfo;

typedef BCM_Ploam_OmciPortInfo BCM_Ploam_omciPortInfo;

/*Type of ioctl argument pointer for command BCM_PLOAM_IOC_SET_1ST_SN_PREAMBLE*/
typedef struct {
  IN UBOOL8 enable;
  IN UINT8 preambleLength1;
  IN UINT8 preambleLength2;

} BCM_Ploam_1stSnPreambleInfo;

/*Power Level Modes*/
#define BCM_PLOAM_POWER_LEVEL_NORMAL 0
#define BCM_PLOAM_POWER_LEVEL_MIN_3DB 1
#define BCM_PLOAM_POWER_LEVEL_MIN_6DB 2

#define BCM_PLOAM_NUM_DELIMITER_BYTES 3

/*Type of ioctl argument pointer for command BCM_PLOAM_IOC_GET_GTC_PARAMS*/
typedef struct {
  OUT UINT8 numGuardBits;
  OUT UINT8 numType1PreambleBits;
  OUT UINT8 numType2PreambleBits;
  OUT UINT8 numType3PreambleBits;
  OUT UINT8 type3PreamblePattern;
  OUT UINT8 delimiterData[BCM_PLOAM_NUM_DELIMITER_BYTES];
  OUT UINT8 powerLevel; /*One of BCM_PLOAM_POWER_LEVEL_* */
  OUT UINT32 eqd;

} BCM_Ploam_GtcParamInfo;

/*Legacy:*/
typedef BCM_Ploam_GtcParamInfo BCM_Ploam_gtcParamInfo;

/*Type of ioctl argument pointer for command BCM_PLOAM_IOC_GET_ONU_ID*/
typedef struct {
  OUT UINT8 onuId;

} BCM_Ploam_GetOnuIdInfo;

/*FEC mode bitmap flags:*/
#define BCM_PLOAM_FEC_MODE_FLAG_US_FEC_ON (1<<0)
#define BCM_PLOAM_FEC_MODE_FLAG_DS_FEC_ON (1<<1)

/*Type of ioctl argument pointer for command BCM_PLOAM_IOC_GET_FEC_MODE*/
typedef struct {
  OUT UINT32 fecMode; /*Bitwise OR of BCM_PLOAM_FEC_MODE_FLAG_* */

} BCM_Ploam_GetFecModeInfo;

#define BCM_PLOAM_ENCRYPTION_KEY_SIZE_BYTES 16

/*Type of ioctl argument pointer for command BCM_PLOAM_IOC_GET_ENCRYPTION_KEY*/
typedef struct {
  OUT UINT8 key[BCM_PLOAM_ENCRYPTION_KEY_SIZE_BYTES];

} BCM_Ploam_GetEncryptionKeyInfo;

typedef BCM_Ploam_GetEncryptionKeyInfo BCM_PloamGetEncryptionKeyInfo;

#define BCM_PLOAM_MIN_FRAG_SIZE_MIN 2
#define BCM_PLOAM_MIN_FRAG_SIZE_MAX 255
#define BCM_PLOAM_CELL_GRANT_SIZE_MIN 1
#define BCM_PLOAM_CELL_GRANT_SIZE_MAX 255

/*Type of ioctl argument pointer for command BCM_PLOAM_IOC_GTCUS_CFG*/
typedef struct {
  IN UINT16 minFragSize; /*Range [BCM_PLOAM_MIN_FRAG_SIZE_MIN..BCM_PLOAM_MIN_FRAG_SIZE_MAX]*/
  IN UINT16 cellGrantSize; /*Range [BCM_PLOAM_CELL_GRANT_SIZE_MIN..BCM_PLOAM_CELL_GRANT_SIZE_MAX]*/
  IN UINT16 flags; /*Reserved*/

} BCM_Ploam_GtcUsCfgInfo;

/*GTCDS Flags*/
#define BCM_PLOAM_GTCDS_FLAG_EN_PBIT_QID_MAPPING 1
#define BCM_PLOAM_GTCDS_FLAG_INNER_PBIT_QID_MAPPING 2

/*Enter this TPID to keep current value*/
#define BCM_PLOAM_TPID_KEEP_CURRENT 0xffff

/*Type of ioctl argument pointer for command BCM_PLOAM_IOC_GTCDS_CFG*/
typedef struct {
  IN UINT16 flags; /*Bitwise OR of BCM_PLOAM_GTCDS_FLAG_* */
  IN UINT16 innerVlanTpids[4];
  IN UINT16 outerVlanTpids[4];

} BCM_Ploam_GtcDsCfgInfo;

/*Multicast filter operations*/
typedef enum {
  BCM_PLOAM_MCAST_FILTER_OP_CLR=0,
  BCM_PLOAM_MCAST_FILTER_OP_ADD=1,
  BCM_PLOAM_MCAST_FILTER_OP_CLR_ALL=2,
  BCM_PLOAM_MCAST_FILTER_OP_READ_BEGIN=3,
  BCM_PLOAM_MCAST_FILTER_OP_READ_NEXT=4,

} BCM_Ploam_McastFilterOps;

#define BCM_PLOAM_VID_NOT_USED 0xffff
#define BCM_PLOAM_MAX_NUM_MCAST_FILTER_ENTRIES 512

/*Type of ioctl argument pointer for command BCM_IOC_MCAST_FILTER_ENTRY*/
typedef struct {
  IN UINT16 op; /*BCM_Ploam_McastFilterOps*/
  IN UINT16 innerVid; /*Range: [0..4095] or BCM_PLOAM_VID_NOT_USED*/
  IN UINT16 outerVid; /*Range: [0..4095] or BCM_PLOAM_VID_NOT_USED*/
  /*48 Bit Multicast MAC address.
   *The following must be true (DA is the MAC address, bit indexed):
   *(DA[47:23] == 01-00-5E-'0') || (DA[47:32] == 33-33)*/
  IN UINT8 mcastMacAddr[6];

} BCM_Ploam_McastFilterEntry;

#define BCM_PLOAM_SERIAL_NUMBER_SIZE_BYTES 8
#define BCM_PLOAM_PASSWORD_SIZE_BYTES 10

/*Type of ioctl argument pointer for commands BCM_PLOAM_IOC_SET_SERIAL_PASSWD and
 *BCM_PLOAM_IOC_GET_SERIAL_PASSWD*/
typedef struct {
  INOUT UINT8 serialNumber[BCM_PLOAM_SERIAL_NUMBER_SIZE_BYTES];
  INOUT UINT8 password[BCM_PLOAM_PASSWORD_SIZE_BYTES];

} BCM_Ploam_SerialPasswdInfo;

typedef BCM_Ploam_SerialPasswdInfo BCM_Ploam_serialPasswdInfo;

typedef enum {
  BCM_GPON_SERDES_SATA_PRBS7=0,
  BCM_GPON_SERDES_SATA_PRBS15=1,
  BCM_GPON_SERDES_SATA_PRBS23=2,
  BCM_GPON_SERDES_SATA_PRBS31=3,
  BCM_GPON_SERDES_WRAPPER_PSEUDO_RANDOM=4

} BCM_Ploam_PseudoRandomMode;

/*Type of ioctl argument pointer for command BCM_PLOAM_IOC_GEN_PRBS*/
typedef struct {
  IN UINT8 enable;
  IN UINT8 mode; /* BCM_PLOAM_PRBS* */

} BCM_Ploam_GenPrbsInfo;

#define BCM_OPTICS_FLAG_AH_LOS   1
#define BCM_OPTICS_FLAG_AH_BEN   2
#define BCM_OPTICS_FLAG_LVDS_BEN_OE  4
#define BCM_OPTICS_FLAG_LVTTL_BEN_OE 8

/*Type of ioctl argument pointer for command BCM_OPTICS_IOC_IF_CFG and BCM_OPTICS_IOC_GET_IF_CFG*/
typedef struct {
  INOUT UINT8 flags; /*Bitwise OR of BCM_OPTICS_FLAG_* flags*/
  INOUT UINT8 laserTon;
  INOUT UINT8 laserToff;
  INOUT UINT32 txIdlePattern;

} BCM_Optics_IfCfgInfo;

#define BCM_AE_MODE_FLAG_SGMII    1

/*Type of ioctl argument pointer for command BCM_AE_IOC_MODE*/
typedef struct {
  IN UINT8 flags; /*Bitwise OR of BCM_AE_MODE_FLAG_* flags*/

} BCM_AE_ModeInfo;

/*The following BCM_AE_STATUS_* defines are deprecated.
 *Use the BCM_AE_STATUS0_* defines instead.
 */
#define BCM_AE_STATUS_TX_FIFO_ERR_DETECTED (1<<15)
#define BCM_AE_STATUS_RX_FIFO_ERR_DETECTED (1<<14)
#define BCM_AE_STATUS_FALSE_CARRIER_DETECTED (1<<13)
#define BCM_AE_STATUS_CRC_ERR_DETECTED (1<<12)
#define BCM_AE_STATUS_TX_ERR_DETECTED (1<<11)
#define BCM_AE_STATUS_RX_ERR_DETECTED (1<<10)
#define BCM_AE_STATUS_CARRIER_EXTENDED_ERR_DETECTED (1<<9)
#define BCM_AE_STATUS_EARLY_END_EXTENSION_DETECTED (1<<8)
#define BCM_AE_STATUS_LINK_STATUS_CHG (1<<7)
#define BCM_AE_STATUS_PAUSE_RESOLUTION_RXSIDE (1<<6)
#define BCM_AE_STATUS_PAUSE_RESOLUTION_TXSIDE (1<<5)
#define BCM_AE_STATUS_SPEED_STATUS_HI (1<<4)
#define BCM_AE_STATUS_SPEED_STATUS_LO (1<<3)
#define BCM_AE_STATUS_DUPLEX_STATUS (1<<2)
#define BCM_AE_STATUS_LINK_STATUS (1<<1)
#define BCM_AE_STATUS_SGMII_MODE (1<<0)

#define BCM_AE_STATUS_SPEED(flags) (((flags)>>3)&3)
#define BCM_AE_STATUS_SPEED_10MBPS 0
#define BCM_AE_STATUS_SPEED_100MBPS 1
#define BCM_AE_STATUS_SPEED_1000MBPS 2

#define BCM_AE_STATUS0_TX_FIFO_ERR_DETECTED (1<<15)
#define BCM_AE_STATUS0_RX_FIFO_ERR_DETECTED (1<<14)
#define BCM_AE_STATUS0_FALSE_CARRIER_DETECTED (1<<13)
#define BCM_AE_STATUS0_CRC_ERR_DETECTED (1<<12)
#define BCM_AE_STATUS0_TX_ERR_DETECTED (1<<11)
#define BCM_AE_STATUS0_RX_ERR_DETECTED (1<<10)
#define BCM_AE_STATUS0_CARRIER_EXTENDED_ERR_DETECTED (1<<9)
#define BCM_AE_STATUS0_EARLY_END_EXTENSION_DETECTED (1<<8)
#define BCM_AE_STATUS0_LINK_STATUS_CHG (1<<7)
#define BCM_AE_STATUS0_PAUSE_RESOLUTION_RXSIDE (1<<6)
#define BCM_AE_STATUS0_PAUSE_RESOLUTION_TXSIDE (1<<5)
#define BCM_AE_STATUS0_SPEED_STATUS_HI (1<<4)
#define BCM_AE_STATUS0_SPEED_STATUS_LO (1<<3)
#define BCM_AE_STATUS0_DUPLEX_STATUS (1<<2)
#define BCM_AE_STATUS0_LINK_STATUS (1<<1)
#define BCM_AE_STATUS0_SGMII_MODE (1<<0)

#define BCM_AE_STATUS0_SPEED(flags) (((flags)>>3)&3)
#define BCM_AE_STATUS0_SPEED_10MBPS 0
#define BCM_AE_STATUS0_SPEED_100MBPS 1
#define BCM_AE_STATUS0_SPEED_1000MBPS 2

#define BCM_AE_STATUS1_SGMII_MODE_CHANGE (1<<15)
#define BCM_AE_STATUS1_CONSISTENCY_MISMATCH (1<<14)
#define BCM_AE_STATUS1_AUTONEG_RESOLUTION_ERR (1<<13)
#define BCM_AE_STATUS1_SGMII_SELECTOR_MISMATCH (1<<12)
#define BCM_AE_STATUS1_SYNC_STATUS_FAIL (1<<11)
#define BCM_AE_STATUS1_SYNC_STATUS_OK (1<<10)
#define BCM_AE_STATUS1_RUDI_C (1<<9)
#define BCM_AE_STATUS1_RUDI_L (1<<8)
#define BCM_AE_STATUS1_RUDI_INVALID (1<<7)
#define BCM_AE_STATUS1_LINK_DOWN_SYNC_LOSS (1<<6)
#define BCM_AE_STATUS1_IDLE_DETECT_STATE (1<<5)
#define BCM_AE_STATUS1_COMPLETE_ACK_STATE (1<<4)
#define BCM_AE_STATUS1_ACK_DETECT_STATE (1<<3)
#define BCM_AE_STATUS1_ABILITY_DETECT_STATE (1<<2)
#define BCM_AE_STATUS1_AN_DISABLE_LINK_OK_STATE (1<<1)
#define BCM_AE_STATUS1_AN_ENABLE_STATE (1<<0)

/*Type of ioctl argument pointer for command BCM_AE_IOC_STATUS*/
typedef struct {
#define BCM_AE_STATUS_NUM_REGS 2
  OUT UINT16 flags[2]; /*Bitwise OR of BCM_AE_STATUS0|1_* flags*/

} BCM_AE_StatusInfo;

#define BCM_PLOAM_MAX_TO1_MS 10000000
#define BCM_PLOAM_MAX_TO2_MS 10000000

/*Type of ioctl argument pointer for command BCM_PLOAM_IOC_SET_TO1_TO2 and
 *BCM_PLOAM_IOC_GET_TO1_TO2*/
typedef struct {
  INOUT UINT32 to1;
  INOUT UINT32 to2;

} BCM_Ploam_TO1TO2Info;

/*Type of ioctl argument pointer for command BCM_PLOAM_IOC_SET_ALARM_SOAK_TIME and
 *BCM_PLOAM_IOC_GET_ALARM_SOAK_TIME*/
typedef struct {
  IN UINT16 alarmId; /*One of BCM_PLOAM_ALARM_ID_* */
  INOUT UINT16 declSoakTime100ms;
  INOUT UINT16 retireSoakTime100ms;

} BCM_Ploam_AlarmSoakTimeInfo;

/* Error Return codes */
#define EINVAL_PLOAM_DUPLICATE           0x102
#define EINVAL_PLOAM_INIT_OPER_STATE     0x103
#define EINVAL_PLOAM_GEM_PORT            0x104
#define EINVAL_PLOAM_GEM_PORT_ENABLED    0x105
#define EINVAL_PLOAM_STATE               0x109
#define EINVAL_PLOAM_ARG                 0x10a
#define EINVAL_PLOAM_NOENT               0x10b

#endif /*BCM_PLOAM_IOC_API_H*/
