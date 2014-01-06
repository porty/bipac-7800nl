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

#ifndef _BCM_VLAN_H_
#define _BCM_VLAN_H_

/*
 * Macros, type definitions
 */

/* FIXME: IFNAMSIZ is defined in kernel/linux/include/linux/if.h, but this
   file cannot be included in user space */
#define BCM_VLAN_IFNAMSIZ          16

#define BCM_VLAN_IF_SUFFIX_SIZE    5 /* 4 characters + trailing '\0' */
#define BCM_VLAN_IF_SUFFIX_DEFAULT ".v"

#define BCM_VLAN_TABLE_NAME_SIZE   16

#define BCM_VLAN_MAX_TAGS          4

#define BCM_VLAN_MAX_CMD_ARGS      2

#define BCM_VLAN_MAX_RULE_COMMANDS 16

#define BCM_VLAN_DONT_CARE         ~0

#define BCM_VLAN_DEFAULT_DEV_NAME  "DEFAULT"

typedef enum {
    BCM_VLAN_TABLE_DIR_RX=0,
    BCM_VLAN_TABLE_DIR_TX,
    BCM_VLAN_TABLE_DIR_MAX,
} bcmVlan_ruleTableDirection_t;

typedef enum {
    BCM_VLAN_ACTION_ACCEPT=0,
    BCM_VLAN_ACTION_DROP,
    BCM_VLAN_ACTION_MAX,
} bcmVlan_defaultAction_t;

typedef enum {
    BCM_VLAN_POSITION_BEFORE=0,
    BCM_VLAN_POSITION_AFTER,
    BCM_VLAN_POSITION_APPEND,
    BCM_VLAN_POSITION_MAX,
} bcmVlan_ruleInsertPosition_t;

typedef enum {
    BCM_VLAN_OPCODE_NOP=0,

    BCM_VLAN_OPCODE_POP_TAG,
    BCM_VLAN_OPCODE_PUSH_TAG,

    BCM_VLAN_OPCODE_SET_ETHERTYPE,

    BCM_VLAN_OPCODE_SET_PBITS,
    BCM_VLAN_OPCODE_SET_CFI,
    BCM_VLAN_OPCODE_SET_VID,
    BCM_VLAN_OPCODE_SET_TAG_ETHERTYPE,

    BCM_VLAN_OPCODE_COPY_PBITS,
    BCM_VLAN_OPCODE_COPY_CFI,
    BCM_VLAN_OPCODE_COPY_VID,
    BCM_VLAN_OPCODE_COPY_TAG_ETHERTYPE,

    BCM_VLAN_OPCODE_DSCP2PBITS,

    BCM_VLAN_OPCODE_SET_DSCP,

    BCM_VLAN_OPCODE_DROP_FRAME,

    BCM_VLAN_OPCODE_SET_SKB_PRIO,
    BCM_VLAN_OPCODE_SET_SKB_MARK_PORT,
    BCM_VLAN_OPCODE_SET_SKB_MARK_QUEUE,
    BCM_VLAN_OPCODE_SET_SKB_MARK_FLOWID,

    BCM_VLAN_OPCODE_CONTINUE,

    BCM_VLAN_OPCODE_MAX,
} bcmVlan_cmdOpCode_t;

typedef struct {
    unsigned int tciMask; /* Should NOT be set by user */
    unsigned int tci; /* Should NOT be set by user */
    unsigned int etherType;
    unsigned int pbits;
    unsigned int cfi;
    unsigned int vid;
} bcmVlan_vlanTag_t;

typedef struct {
    unsigned int skbPrio;
    unsigned int skbMarkFlowId;
    unsigned int skbMarkPort;
    unsigned int etherType;
    unsigned int dscp;
    unsigned int vlanDevMacAddr;
    bcmVlan_vlanTag_t vlanTag[BCM_VLAN_MAX_TAGS];
    char txVlanDevName[BCM_VLAN_IFNAMSIZ];
} bcmVlan_tagRuleFilter_t;

typedef unsigned int bcmVlan_cmdArg_t;

typedef struct {
    bcmVlan_cmdOpCode_t opCode;
    bcmVlan_cmdArg_t arg[BCM_VLAN_MAX_CMD_ARGS];
} bcmVlan_tagRuleCommand_t;

typedef unsigned int bcmVlan_tagRuleIndex_t;

typedef enum {
    BCM_VLAN_MODE_ONT = 0,
    BCM_VLAN_MODE_RG,
    BCM_VLAN_MODE_MAX
} bcmVlan_realDevMode_t;

typedef struct {
    bcmVlan_tagRuleFilter_t filter;
    bcmVlan_tagRuleCommand_t cmd[BCM_VLAN_MAX_RULE_COMMANDS];
    bcmVlan_tagRuleIndex_t id;
    char rxVlanDevName[BCM_VLAN_IFNAMSIZ];
} bcmVlan_tagRule_t;

typedef struct {
    char realDevName[BCM_VLAN_IFNAMSIZ];
    bcmVlan_ruleTableDirection_t tableDir;
    unsigned int nbrOfTags;
} bcmVlan_ruleTableId_t;


/*************************************
 ******       User API           *****
 *************************************/

/* Default values */
#define BCM_VLAN_DEFAULT_TAG_TPID  ETH_P_8021Q
#define BCM_VLAN_DEFAULT_TAG_PBITS 0
#define BCM_VLAN_DEFAULT_TAG_CFI   0
#define BCM_VLAN_DEFAULT_TAG_VID   1 /* IEEE 802.1Q, Table 9-2 */

#define BCM_VLAN_DEFAULT_RX_ACTION BCM_VLAN_ACTION_ACCEPT
#define BCM_VLAN_DEFAULT_TX_ACTION BCM_VLAN_ACTION_ACCEPT

#define BCM_VLAN_MAX_TPID_VALUES 4

/**************************************
 * Macros to get/set command arguments
 * Valid combinations:
 *    TARGET
 *    TARGET + VALUE
 *    TARGET + SOURCE
 *    VALUE  + VALUE2
 **************************************/
#define BCM_VLAN_CMD_GET_TARGET_TAG(_arg)       ( (_arg)[1] )
#define BCM_VLAN_CMD_SET_TARGET_TAG(_arg, _tag) ( (_arg)[1] = (typeof(*(_arg)))(_tag) )

#define BCM_VLAN_CMD_GET_VAL(_arg)              ( (_arg)[0] )
#define BCM_VLAN_CMD_SET_VAL(_arg, _val)        ( (_arg)[0] = (typeof(*(_arg)))(_val) )

#define BCM_VLAN_CMD_GET_SOURCE_TAG(_arg)       ( (_arg)[0] )
#define BCM_VLAN_CMD_SET_SOURCE_TAG(_arg, _tag) ( (_arg)[0] = (typeof(*(_arg)))(_tag) )

#define BCM_VLAN_CMD_GET_VAL2(_arg)             ( (_arg)[1] )
#define BCM_VLAN_CMD_SET_VAL2(_arg, _val)       ( (_arg)[1] = (typeof(*(_arg)))(_val) )

/* Tag Rule Initialization */
static inline void bcmVlan_initTagRule(bcmVlan_tagRule_t *tagRule)
{
    /* initialize filter */
    memset(&tagRule->filter, BCM_VLAN_DONT_CARE, sizeof(bcmVlan_tagRuleFilter_t));

    /* set vlanDevMacAddr flag to 0 */
    tagRule->filter.vlanDevMacAddr = 0; 

    /* initialize transmit VLAN device name filter */
    strcpy(tagRule->filter.txVlanDevName, BCM_VLAN_DEFAULT_DEV_NAME);

    /* initialize commands */
    memset(&tagRule->cmd, BCM_VLAN_OPCODE_NOP, BCM_VLAN_MAX_RULE_COMMANDS * sizeof(bcmVlan_tagRuleCommand_t));

    tagRule->id = BCM_VLAN_DONT_CARE;

    /* initialize receive VLAN device name */
    strcpy(tagRule->rxVlanDevName, BCM_VLAN_DEFAULT_DEV_NAME);
}

/* IOCTL commands */
typedef enum {
    BCM_VLAN_IOC_CREATE_VLAN=0,
    BCM_VLAN_IOC_DELETE_VLAN,
    BCM_VLAN_IOC_INSERT_TAG_RULE,
    BCM_VLAN_IOC_REMOVE_TAG_RULE,
    BCM_VLAN_IOC_DUMP_RULE_TABLE,
    BCM_VLAN_IOC_SET_DEFAULT_TAG,
    BCM_VLAN_IOC_SET_DSCP_TO_PBITS,
    BCM_VLAN_IOC_DUMP_DSCP_TO_PBITS,
    BCM_VLAN_IOC_DUMP_LOCAL_STATS,
    BCM_VLAN_IOC_SET_TPID_TABLE,
    BCM_VLAN_IOC_DUMP_TPID_TABLE,
    BCM_VLAN_IOC_SET_IF_SUFFIX,
    BCM_VLAN_IOC_SET_DEFAULT_ACTION,
    BCM_VLAN_IOC_SET_REAL_DEV_MODE,
    BCM_VLAN_IOC_MAX
} bcmVlan_ioctlCmd_t;

typedef struct {
    char realDevName[BCM_VLAN_IFNAMSIZ];
    unsigned int vlanDevId;
    int isRouted;
    int isMulticast;
} bcmVlan_iocCreateVlan_t;

typedef struct {
    char vlanDevName[BCM_VLAN_IFNAMSIZ];
} bcmVlan_iocDeleteVlan_t;

typedef struct {
    bcmVlan_ruleTableId_t ruleTableId;
    bcmVlan_tagRule_t tagRule;
    bcmVlan_ruleInsertPosition_t position;
    bcmVlan_tagRuleIndex_t posTagRuleId;
} bcmVlan_iocInsertTagRule_t;

typedef struct {
    bcmVlan_ruleTableId_t ruleTableId;
    bcmVlan_tagRuleIndex_t tagRuleId;
    bcmVlan_tagRule_t tagRule;
} bcmVlan_iocRemoveTagRule_t;

typedef struct {
    bcmVlan_ruleTableId_t ruleTableId;
} bcmVlan_iocDumpRuleTable_t;

typedef struct {
    bcmVlan_ruleTableId_t ruleTableId;
    UINT16 defaultTpid;
    UINT8 defaultPbits;
    UINT8 defaultCfi;
    UINT16 defaultVid;
} bcmVlan_iocSetDefaultVlanTag_t;

typedef struct {
    char realDevName[BCM_VLAN_IFNAMSIZ];
    UINT8 dscp;
    UINT8 pbits;
} bcmVlan_iocDscpToPbits_t;

typedef struct {
    char vlanDevName[BCM_VLAN_IFNAMSIZ];
} bcmVlan_iocDumpLocalStats_t;

typedef struct {
    char realDevName[BCM_VLAN_IFNAMSIZ];
    unsigned int tpidTable[BCM_VLAN_MAX_TPID_VALUES];
} bcmVlan_iocSetTpidTable_t;

typedef struct {
    char realDevName[BCM_VLAN_IFNAMSIZ];
} bcmVlan_iocDumpTpidTable_t;

typedef struct {
    char suffix[BCM_VLAN_IF_SUFFIX_SIZE];
} bcmVlan_iocSetIfSuffix_t;

typedef struct {
    bcmVlan_ruleTableId_t ruleTableId;
    bcmVlan_defaultAction_t defaultAction;
} bcmVlan_iocSetDefaultAction_t;

typedef struct {
    char realDevName[BCM_VLAN_IFNAMSIZ];
    bcmVlan_realDevMode_t mode;
} bcmVlan_iocSetRealDevMode_t;

#endif /* _BCM_VLAN_H_ */

