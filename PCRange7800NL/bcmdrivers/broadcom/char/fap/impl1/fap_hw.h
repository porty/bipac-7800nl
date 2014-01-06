#ifndef __FAP_HW_H_INCLUDED__
#define __FAP_HW_H_INCLUDED__

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

/*
 *******************************************************************************
 * File Name  : fap_hw.h
 *
 * Description: This file contains ...
 *
 *******************************************************************************
 */

#include "bcmtypes.h"

// Comment out and rebuild all FAP files to get a log of every register access
//#define FAP_DEBUG_MODE
#define USE_SMISBUS

#if defined(FAP_DEBUG_MODE)
// Use these macros to access registers from code running on the host
#define FAP_HOST_REG_RD(_reg) fapHostAddrRead((&(_reg)), #_reg)
#define FAP_HOST_REG_WR(_reg, _val32) fapHostAddrWrite(&(_reg), (_val32), #_reg)
// Use these macros to access registers from code running on the 4ke
// Note that printing register access from 4ke is currently not possible
// since the prints would use the mailbox, which require register accesses...
#define FAP_4KE_REG_RD(_reg) FAP_ADDR_RD(&(_reg))
#define FAP_4KE_REG_WR(_reg, _val32) FAP_ADDR_WR(&(_reg), _val32)
#else
// Use these macros to access registers from code running on the host
#define FAP_HOST_REG_RD(_reg) FAP_ADDR_RD(&(_reg))
#define FAP_HOST_REG_WR(_reg, _val32) FAP_ADDR_WR(&(_reg), _val32)
// Use these macros to access registers from code running on the 4ke
#define FAP_4KE_REG_RD(_reg) FAP_ADDR_RD(&(_reg))
#define FAP_4KE_REG_WR(_reg, _val32) FAP_ADDR_WR(&(_reg), _val32)
#endif

#define hwPrint(fmt, arg...)    printk(fmt, ##arg)
// Use these macros to print registers from code running in the Host
#define FAP_PRINT_REG(grp, reg) hwPrint("  %-20s  0x%08x\n", #reg, (unsigned int)grp->reg)
#define FAP_PRINT_REG_ELEM(grp, reg) hwPrint("  %-20s  0x%08x\n", #reg, (unsigned int)grp.reg)

// Internal use only
#define FAP_ADDR_RD(_addr) *((volatile uint32 *)(_addr))
#define FAP_ADDR_WR(_addr, _val32) *((volatile uint32 *)(_addr)) = (_val32)

// FAP Address Offsets
#define CTRL_REG_BLOCK_OFFSET 0x0000 
#define OG_MSG_OFFSET         0x0100 
#define IN_MSG_OFFSET         0x0200 
#define DMA_OFFSET            0x0300
#define TKN_INTF_OFFSET       0x0400
#define PERF_MEAS_OFFSET      0x0600
#define MSG_ID_OFFSET         0x0700
#define DQM_OFFSET            0x0800
#define DQMQCNTRL_OFFSET      0x0a00
#define DQMQDATA_OFFSET       0x0c00
#define DQMQMIB_OFFSET        0x1000
#define QSM_OFFSET            0x3000
#define DPE_BASIC_OFFSET      0x3F000

#define mPhysToNonCacheVirtAddr(x)   ((x&0x1fffffff)|0xa0000000)
#define mPhysToCacheVirtAddr(x)      ((x&0x1fffffff)|0x80000000)
#define mVirtToPhysAddr(x)           (x&0x1fffffff)
#define mCacheToNonCacheVirtAddr(x)  ( ((uint32)(x) & 0x1fffffff) | 0xa0000000 )

/* SMI Bus Control Register */
#define MIPS_SMISB_CTRL 0xFF400030
#define mips_smisb_ctrl ((volatile uint32 *)(MIPS_SMISB_CTRL))

// Host Base Addresses
#ifdef CONFIG_BCM96362
  #ifdef USE_SMISBUS
#define PHYS_FAP_BASE             0x14001000 /* 6362 using SMISBUS */
  #else
#define PHYS_FAP_BASE             0x11001000 /* 6362 using UBUS    */
  #endif
#else
#define PHYS_FAP_BASE             0x14401000 /* 3380 */
#endif



#define NON_CACHE_VIRT_FAP_BASE   mPhysToNonCacheVirtAddr(PHYS_FAP_BASE)

// Registers for Host Access
#define hostRegCntrl         ((volatile CoprocCtlRegs_S *)(NON_CACHE_VIRT_FAP_BASE + CTRL_REG_BLOCK_OFFSET))
#define hostOgMsgReg         ((volatile OGMsgFifoRegs_S *)(NON_CACHE_VIRT_FAP_BASE + OG_MSG_OFFSET))
#define hostInMsgReg         ((volatile INMsgFifoRegs_S *)(NON_CACHE_VIRT_FAP_BASE + IN_MSG_OFFSET))
#define hostDmaReg           ((volatile DMARegs_S *)(NON_CACHE_VIRT_FAP_BASE + DMA_OFFSET))
#define hostTknIntfReg       ((volatile TknIntfRegs_S *)(NON_CACHE_VIRT_FAP_BASE + TKN_INTF_OFFSET))
#define hostPerfMeasReg      ((volatile PMRegs_S *)(NON_CACHE_VIRT_FAP_BASE + PERF_MEAS_OFFSET))
#define hostMsgIdReg         ((volatile MsgIdRegs_S *)(NON_CACHE_VIRT_FAP_BASE + MSG_ID_OFFSET))
#define hostDqmReg           ((volatile DQMCtlRegs_S *)(NON_CACHE_VIRT_FAP_BASE + DQM_OFFSET))
#define hostDqmQCntrlReg     ((volatile DQMQCntrlRegs_S *)(NON_CACHE_VIRT_FAP_BASE + DQMQCNTRL_OFFSET))
#define hostDqmQDataReg      ((volatile DQMQDataRegs_S *)(NON_CACHE_VIRT_FAP_BASE + DQMQDATA_OFFSET))
#define hostDqmQMibReg       ((volatile DQMQMibRegs_S *)(NON_CACHE_VIRT_FAP_BASE + DQMQMIB_OFFSET))
#define hostDpeBasicReg      ((volatile DpeBasicRegs_S *)(NON_CACHE_VIRT_FAP_BASE + DPE_BASIC_OFFSET))

#define FAP_HOST_PSM_BASE    0xB1010000

/* Place Enet Rx Bds at upper end of 16KB QSM. 400 BDs * 2W per BD * 2 ch * 4bytes per word */
#define pHostQsm             ((volatile uint8 *)(NON_CACHE_VIRT_FAP_BASE + QSM_OFFSET))
#define pHostRxEnetBds       ((volatile uint8 *)(NON_CACHE_VIRT_FAP_BASE + QSM_OFFSET + 16*1024 - (400*2*2*4)))

// 4ke FAP Base Address
#define _4KE_BASE    0xe0001000

// Registers for 4ke Access
#define _4keRegCntrl          ((volatile CoprocCtlRegs_S *)(_4KE_BASE + CTRL_REG_BLOCK_OFFSET))
#define _4keOgMsgReg          ((volatile OGMsgFifoRegs_S *)(_4KE_BASE + OG_MSG_OFFSET))
#define _4keInMsgReg          ((volatile INMsgFifoRegs_S *)(_4KE_BASE + IN_MSG_OFFSET))
#define _4keDmaReg            ((volatile DMARegs_S *)(_4KE_BASE + DMA_OFFSET))
#define _4keTknIntfReg        ((volatile TknIntfRegs_S *)(_4KE_BASE + TKN_INTF_OFFSET))
#define _4kePerfMeasReg       ((volatile PMRegs_S *)(_4KE_BASE + PERF_MEAS_OFFSET))
#define _4keMsgIdReg          ((volatile MsgIdRegs_S *)(_4KE_BASE + MSG_ID_OFFSET))
#define _4keDqmReg            ((volatile DQMCtlRegs_S *)(_4KE_BASE + DQM_OFFSET))
#define _4keDqmQCntrlReg      ((volatile DQMQCntrlRegs_S *)(_4KE_BASE + DQMQCNTRL_OFFSET))
#define _4keDqmQDataReg       ((volatile DQMQDataRegs_S *)(_4KE_BASE + DQMQDATA_OFFSET))
#define _4keDqmQMibReg        ((volatile DQMQMibRegs_S *)(_4KE_BASE + DQMQMIB_OFFSET))
#define _4keSharedMemPtr      ((volatile uint32 *)(_4KE_BASE + SHARED_MEM_OFFSET))
#define _4keDpeBasicReg       ((volatile DpeBasicRegs_S *)(_4KE_BASE + DPE_BASIC_OFFSET))
#define _4keMiscIrqReg        ((volatile MiscIrqRegs_S *)(0xB000182C))
#define _4keIntChipIrqStatus  ((volatile ChipIrqStatusRegs_S *)(0xB0000028))

// FAP DQM Registers
#define FAP_QSM_BASE                                   0xE0004000

// FAP PSM Registers
#define FAP_PSM_BASE                                   0xE0010000
#define FAP_PSM_SIZE                                   32768 /* bytes */
#define FAP_PSM_SIZE_32                                (FAP_PSM_SIZE / 4) /* words */

// FAP DPE Memory Base Addresses
#define FAP_DPE_NUG_MEM_BASE                           0xE0050000 
#define FAP_DPE_PKT_MEM_BASE                           0xE0051000 
#define FAP_DPE_INST_MEM_BASE                          0xE0052000 

#define CONVERT_PSM_HOST2FAP(x)                        (((uint32)x & 0xFFFF) | FAP_PSM_BASE)

#define CONVERT_QSM_HOST2FAP(x)                        (((uint32)x - (uint32)pHostQsm) | FAP_QSM_BASE)

// FAP Control Registers
typedef struct CoprocCtlRegs_S
{
  uint32    irq_4ke_mask;    // 00
  uint32    irq_4ke_status;  // 04
            #define IRQ_FAP_4KE_TIMER                           (1 << 0)
            #define IRQ_FAP_4KE_OUT_FIFO                        (1 << 1)
            #define IRQ_FAP_4KE_IN_FIFO                         (1 << 2)
            #define IRQ_FAP_4KE_DQM                             (1 << 3)
            #define IRQ_FAP_4KE_MBOX_IN                         (1 << 4)
            #define IRQ_FAP_4KE_MBOX_OUT                        (1 << 5)
            #define IRQ_FAP_4KE_GENERAL_PURPOSE_INPUT           (1 << 6)
            #define IRQ_FAP_4KE_ERROR_EB2UBUS_TIMEOUT           (1 << 7)
            #define IRQ_FAP_4KE_ERROR_UB_SLAVE_TIMEOUT          (1 << 8)
            #define IRQ_FAP_4KE_ERROR_UB_SLAVE                  (1 << 9)
            #define IRQ_FAP_4KE_ERROR_UB_MASTER                 (1 << 10)
            #define IRQ_FAP_4KE_ERROR_EB_DQM_OVERFLOW           (1 << 11)
            #define IRQ_FAP_4KE_ERROR_UB_DQM_OVERFLOW           (1 << 12)
            #define IRQ_FAP_4KE_ERROR_DMA0_RX_FIFO_NOT_EMPTY    (1 << 13)
            #define IRQ_FAP_4KE_ERROR_DMA0_TX_FIFO_NOT_EMPTY    (1 << 14)
            #define IRQ_FAP_4KE_ERROR_DMA1_RX_FIFO_NOT_EMPTY    (1 << 15)
            #define IRQ_FAP_4KE_ERROR_DMA1_TX_FIFO_NOT_EMPTY    (1 << 16)
            #define IRQ_FAP_4KE_TIMER_0                         (1 << 17)
            #define IRQ_FAP_4KE_TIMER_1                         (1 << 18)
            #define IRQ_FAP_4KE_TIMER_2                         (1 << 19)

  uint32    irq_mips_mask;   // 08
  uint32    irq_mips_status; // 0C
            #define IRQ_FAP_HOST_TIMER                           (1 << 0)
            #define IRQ_FAP_HOST_DQM                             (1 << 3)
            #define IRQ_FAP_HOST_MBOX_IN                         (1 << 4)
            #define IRQ_FAP_HOST_MBOX_OUT                        (1 << 5)
            #define IRQ_FAP_HOST_GENERAL_PURPOSE_INPUT           (1 << 6)
            #define IRQ_FAP_HOST_ERROR_EB2UBUS_TIMEOUT           (1 << 7)
            #define IRQ_FAP_HOST_ERROR_UB_SLAVE_TIMEOUT          (1 << 8)
            #define IRQ_FAP_HOST_ERROR_UB_SLAVE                  (1 << 9)
            #define IRQ_FAP_HOST_ERROR_UB_MASTER                 (1 << 10)
            #define IRQ_FAP_HOST_ERROR_EB_DQM_OVERFLOW           (1 << 11)
            #define IRQ_FAP_HOST_ERROR_UB_DQM_OVERFLOW           (1 << 12)
            #define IRQ_FAP_HOST_ERROR_DMA0_RX_FIFO_NOT_EMPTY    (1 << 13)
            #define IRQ_FAP_HOST_ERROR_DMA0_TX_FIFO_NOT_EMPTY    (1 << 14)
            #define IRQ_FAP_HOST_ERROR_DMA1_RX_FIFO_NOT_EMPTY    (1 << 15)
            #define IRQ_FAP_HOST_ERROR_DMA1_TX_FIFO_NOT_EMPTY    (1 << 16)
            #define IRQ_FAP_HOST_TIMER_0                         (1 << 17)
            #define IRQ_FAP_HOST_TIMER_1                         (1 << 18)
            #define IRQ_FAP_HOST_TIMER_2                         (1 << 19)

  uint32    gp_mask;         // 10
  uint32    gp_status;       // 14
            #define IRQ_FAP_GP_TIMER_0                         (1 << 0)
            #define IRQ_FAP_GP_TIMER_1                         (1 << 1)
            #define IRQ_FAP_GP_MBOX_IN                         (1 << 2)
            #define IRQ_FAP_GP_MBOX_OUT                        (1 << 3)
            #define IRQ_FAP_GP_ERROR_EB2UBUS_TIMEOUT           (1 << 4)
            #define IRQ_FAP_GP_ERROR_UB_SLAVE_TIMEOUT          (1 << 5)
            #define IRQ_FAP_GP_ERROR_UB_SLAVE                  (1 << 6)
            #define IRQ_FAP_GP_ERROR_UB_MASTER                 (1 << 7)
            #define IRQ_FAP_GP_ERROR_EB_DQM_OVERFLOW           (1 << 8)
            #define IRQ_FAP_GP_ERROR_UB_DQM_OVERFLOW           (1 << 9)
            #define IRQ_FAP_GP_ERROR_DMA0_RX_FIFO_NOT_EMPTY    (1 << 10)
            #define IRQ_FAP_GP_ERROR_DMA0_TX_FIFO_NOT_EMPTY    (1 << 11)
            #define IRQ_FAP_GP_ERROR_DMA1_RX_FIFO_NOT_EMPTY    (1 << 12)
            #define IRQ_FAP_GP_ERROR_DMA1_TX_FIFO_NOT_EMPTY    (1 << 13)
            #define IRQ_FAP_GP_TIMER_2                         (1 << 14)

  uint32    gp_tmr0_ctl;     // 18
            #define   TIMER_ENABLE                     0x80000000
            #define   TIMER_MODE_REPEAT                0x40000000
            #define   TIMER_COUNT_MASK                 0x3fffffff
  uint32    gp_tmr0_cnt;     // 1C
  uint32    gp_tmr1_ctl;     // 20
  uint32    gp_tmr1_cnt;     // 24
  uint32    host_mbox_in;    // 28
  uint32    host_mbox_out;   // 2C
  uint32    gp_out;          // 30
  uint32    gp_in;           // 34
            #define GP_IN_TAM_IRQ_MASK                 0x80000000
            #define GP_IN_SEGDMA_IRQ_MASK              0x00000002
            #define GP_IN_USPP_BUSY_FLAG               0x00000001
  uint32    gp_in_irq_mask;  // 38
            #define GP_IN_BASE4_IRQ_MASK               0x80000000
            #define GP_IN_BASE4_IRQ_SHIFT              31
  uint32    gp_in_irq_status;// 3C
            #define GP_IN_IRQ_STATUS_MASK              0x0000FFFF
            #define GP_IN_IRQ_STATUS_SHIFT             0
  uint32    dma_control;     // 40
            #define DMA1_RESULT_FIFO_DEPTH_MASK        0x0000F000
            #define DMA1_RESULT_FIFO_DEPTH_SHIFT       12
            #define DMA1_CMD_FIFO_AVAIL_MASK           0x00000F00
            #define DMA1_CMD_FIFO_AVAIL_SHIFT          8
            #define DMA0_RESULT_FIFO_DEPTH_MASK        0x000000F0
            #define DMA0_RESULT_FIFO_DEPTH_SHIFT       4
            #define DMA0_CMD_FIFO_AVAIL_MASK           0x0000000F
            #define DMA0_CMD_FIFO_AVAIL_SHIFT          0
  uint32    dma_status;      // 44
            #define DMA_STS_DMA1_RSLT_FULL_BIT         0x00000080
            #define DMA_STS_DMA1_RSLT_EMPTY_BIT        0x00000040
            #define DMA_STS_DMA1_CMD_FULL_BIT          0x00000020
            #define DMA_STS_DMA1_BUSY                  0x00000010
            #define DMA_STS_DMA1_SHIFT                 4
            #define DMA_STS_DMA0_RSLT_FULL_BIT         0x00000008
            #define DMA_STS_DMA0_RSLT_EMPTY_BIT        0x00000004
            #define DMA_STS_DMA0_CMD_FULL_BIT          0x00000002
            #define DMA_STS_DMA0_BUSY                  0x00000001
  uint32    dma0_3_fifo_status; // 48 
  uint32    dma4_7_fifo_status; // 4C
            #define DMA_FIFO_STS_DMAi_RSLT_DEPTH_MSK   0x000000F0
            #define DMA_FIFO_STS_DMAi_CMD_ROOM_MSK     0x0000000F
            #define DMA_FIFO_STS_DMAi_RSLT_DEPTH_SHIFT 4
  uint32    dma_irq_sts;        // 50
  uint32    dma_4ke_irq_mask;   // 54
  uint32    dma_host_irq_mask;  // 58
  uint32    diag_cntrl;         // 5C
  uint32    diag_hi;            // 60
  uint32    diag_lo;            // 64
  uint32    bad_address;        // 68
  uint32    addr1_mask;         // 6C
  uint32    addr1_base_in;      // 70
  uint32    addr1_base_out;     // 74
  uint32    addr2_mask;         // 78
  uint32    addr2_base_in;      // 7C
  uint32    addr2_base_out;     // 80
  uint32    scratch;            // 84
  uint32    mbist_tm;           // 88
  uint32    soft_resets;        // 8C active high
            #define SOFT_RESET_DMA                    0x00000004
            #define SOFT_RESET_BASE4                  0x00000002
            #define SOFT_RESET_4KE                    0x00000001
  uint32    eb2ubus_timeout;    // 90
            #define EB2UBUS_TIMEOUT_EN                0x80000000 
            #define EB2UBUS_TIMEOUT_MASK              0x0000FFFF
            #define EB2UBUS_TIMEOUT_SHIFT             0
  uint32    m4ke_core_status;   // 94
  uint32    gp_in_irq_sense;    // 98
  uint32    ub_slave_timeout;   // 9C
            #define UB_SLAVE_TIMEOUT_EN               0x80000000 
            #define UB_SLAVE_TIMEOUT_MASK             0x0000FFFF
            #define UB_SLAVE_TIMEOUT_SHIFT            0
  uint32    diag_en;            // A0
  uint32    dev_timeout;        // A4
  uint32    ubus_error_out_mask;// A8
  uint32    diag_capt_stop_mask;// AC
            #define BASE4_ERROR_MASK                  0x80000000 
  uint32    rev_id;             // B0
  uint32    gp_tmr2_ctl;        // B4
  uint32    gp_tmr2_cnt;        // B8


} CoprocCtlRegs_S;


//Outgoing Message FIFO
typedef struct OGMsgFifoRegs_S
{
  uint32    og_msg_ctl;
  uint32    og_msg_sts;
  uint32    resv[14];
  uint32    og_msg_data;
} OGMsgFifoRegs_S;


//Incoming Message FIFO
typedef struct INMsgFifoRegs_S
{
  uint32    in_msg_ctl;
// Not documented            #define   NUM_MSG_IN_FIFO_MASK            0x001F0000
// Not documented            #define   NUM_MSG_IN_FIFO_OFFSET          16
            #define   NOT_EMPTY_IRQ_STS_MASK          0x00008000
            #define   NOT_EMPTY_IRQ_STS_OFFSET        15
            #define   ERR_IRQ_STS_MASK                0x00004000
            #define   ERR_IRQ_STS_OFFSET              14
            #define   LOW_WTRMRK_IRQ_STS_MASK         0x00002000
            #define   LOW_WTRMRK_IRQ_MSK_OFFSET       13
            #define   MSG_RCVD_IRQ_STS_MASK           0x00001000
            #define   MSG_RCVD_IRQ_MSK_OFFSET         12
            #define   LOW_WATER_MARK_MASK             0x0000003F
            #define   LOW_WATER_MARK_SHIFT            0
            #define   AVAIL_FIFO_SPACE_MASK           0x0000003F
            #define   AVAIL_FIFO_SPACE_OFFSET         0
  uint32    in_msg_sts;
            #define INMSG_NOT_EMPTY_STS_BIT           0x80000000
            #define INMSG_NOT_EMPTY_STS_SHIFT         31
            #define INMSG_ERR_STS_BIT                 0x40000000
            #define INMSG_ERR_STS_SHIFT               30
            #define INMSG_LOW_WATER_STS_BIT           0x20000000
            #define INMSG_LOW_WATER_STS_SHIFT         29
            #define INMSG_MSG_RX_STS_BIT              0x10000000
            #define INMSG_MSG_RX_STS_SHIFT            28
            #define INMSG_RESERVED1_MASK              0x0fc00000
            #define INMSG_RESERVED1_SHIFT             22
            #define INMSG_NUM_MSGS_MASK               0x003F0000
            #define INMSG_NUM_MSGS_SHIFT              16
            #define INMSG_NOT_EMPTY_IRQ_STS_BIT       0x00008000
            #define INMSG_NOT_EMPTY_IRQ_STS_SHIFT     15
            #define INMSG_ERR_IRQ_STS_BIT             0x00004000
            #define INMSG_ERR_IRQ_STS_SHIFT           14
            #define INMSG_LOW_WATER_IRQ_STS_BIT       0x00002000
            #define INMSG_LOW_WATER_IRQ_STS_SHIFT     13
            #define INMSG_MSG_RX_IRQ_STS_BIT          0x00001000
            #define INMSG_MSG_RX_IRQ_STS_SHIFT        12
            #define INMSG_RESERVED2_MASK              0x00000fc0
            #define INMSG_RESERVED2_SHIFT             6
            #define INMSG_AVAIL_FIFO_SPACE_MASK       0x0000003f
            #define INMSG_AVAIL_FIFO_SPACE_SHIFT      0
  uint32    resv[13];
  uint32    in_msg_last;
  uint32    in_msg_data;
} INMsgFifoRegs_S;


// DMA Registers
typedef struct mDma_regs_S 
{
  uint32    dma_source;         // 00
  uint32    dma_dest;           // 04
  uint32    dma_cmd_list;       // 08
            #define DMA_CMD_MEMSET                   0x08000000
            #define DMA_CMD_REPLACE_LENGTH           0x07000000
            #define DMA_CMD_INSERT_LENGTH            0x06000000
            #define DMA_CMD_CHECKSUM2                0x05000000
            #define DMA_CMD_CHECKSUM1                0x04000000
            #define DMA_CMD_DELETE                   0x03000000
            #define DMA_CMD_REPLACE                  0x02000000
            #define DMA_CMD_INSERT                   0x01000000
            #define DMA_CMD_OPCODE_MASK              0xFF000000
            #define DMA_CMD_OPCODE_SHIFT             24
            #define DMA_CMD_OFFSET_MASK              0x00FFFF00
            #define DMA_CMD_OFFSET_SHIFT             8
            #define DMA_CMD_LENGTH_MASK              0x000000FF
            #define DMA_CMD_LENGTH_SHIFT             0
  uint32    dma_len_ctl;        // 0c
            #define DMA_CTL_LEN_LENGTH_N_VALUE_MASK  0xFFFC0000
            #define DMA_CTL_LEN_LENGTH_N_VALUE_SHIFT 18
            #define DMA_CTL_LEN_WAIT_BIT             0x00020000 
            #define DMA_CTL_LEN_EXEC_CMD_LIST_BIT    0x00010000 
            #define DMA_CTL_LEN_DEST_ADDR_MASK       0x0000C000 
            #define DMA_CTL_LEN_DEST_IS_TOKEN_MASK   0x0000C000 
            #define DMA_CTL_LEN_DEST_IS_TOKEN_SHIFT  14 
            #define DMA_CTL_LEN_SRC_IS_TOKEN_BIT     0x00002000 
            #define DMA_CTL_LEN_CONTINUE_BIT         0x00001000
            #define DMA_CTL_LEN_LEN_MASK             0x00000FFF
  uint32    dma_rslt_source;    // 10
  uint32    dma_rslt_dest;      // 14
  uint32    dma_rslt_hcs;       // 18
            #define DMA_RSLT_HCS_HCS0_MASK           0x0000FFFF
            #define DMA_RSLT_HCS_HCS0_SHIFT          0
            #define DMA_RSLT_HCS_HCS1_MASK           0xFFFF0000
            #define DMA_RSLT_HCS_HCS1_SHIFT          15
  uint32    dma_rslt_len_stat;  // 1C
            #define DMA_RSLT_ERROR_MASK              0x003FE000
            #define DMA_RSLT_NOT_END_CMDS            0x00200000
            #define DMA_RSLT_FLUSHED                 0x00100000
            #define DMA_RSLT_ABORTED                 0x00080000
            #define DMA_RSLT_ERR_CMD_FMT             0x00040000
            #define DMA_RSLT_ERR_DEST                0x00020000
            #define DMA_RSLT_ERR_SRC                 0x00010000
            #define DMA_RSLT_ERR_CMD_LIST            0x00008000
            #define DMA_RSLT_ERR_DEST_LEN            0x00004000
            #define DMA_RSLT_ERR_SRC_LEN             0x00002000
            #define DMA_RSLT_CONTINUE                0x00001000
            #define DMA_RSLT_DMA_LEN                 0x00000FFF
} mDma_regs_S;


typedef struct DMARegs_S 
{
  mDma_regs_S    dma_ch[2];
} DMARegs_S;


// Token Registers
typedef struct TknIntfRegs_S
{
  uint32    tok_buf_size;    // 00
  uint32    tok_buf_base;    // 04
  uint32    tok_idx2ptr_idx; // 08
  uint32    tok_idx2ptr_ptr; // 0c
} TknIntfRegs_S;

// Performance Measurement Registers on 4ke
typedef struct PMRegs_S
{
  uint32        DCacheHit;      // n/a 
  uint32        DCacheMiss;     // n/a 
  uint32        ICacheHit;      // 08
  uint32        ICacheMiss;     // 0c
  uint32        InstnComplete;  // 10
  uint32        WTBMerge;       // n/a 
  uint32        WTBNoMerge;     // n/a 
} PMRegs_S;

// MessageID Registers
typedef struct MsgIdRegs_S
{
  uint32    msg_id[64];
} MsgIdRegs_S;


// DQM Control Registers
typedef struct DQMCtlRegs_S
{
  uint32        cfg;                        // 00
                #define DQM_CFG_TOT_MEM_SZ_MASK      0xFFFF0000
                #define DQM_CFG_TOT_MEM_SZ_SHIFT     16
                #define DQM_CFG_START_ADDR_MASK      0x0000FFFF
                #define DQM_CFG_START_ADDR_SHIFT     0
  uint32        _4ke_low_wtmk_irq_msk;      // 04
  uint32        mips_low_wtmk_irq_msk;      // 08
  uint32        low_wtmk_irq_sts;           // 0c
  uint32        _4ke_not_empty_irq_msk;     // 10
  uint32        mips_not_empty_irq_msk;     // 14
  uint32        not_empty_irq_sts;          // 18
  uint32        queue_rst;                  // 1c
  uint32        not_empty_sts;              // 20
  uint32        next_avail_mask;            // 24
  uint32        next_avail_queue;           // 28
} DQMCtlRegs_S;


// DQM Queue Control
typedef struct DQMQRegs_S
{
  uint32        size;   // 00
                #define Q_HEAD_PTR_MASK                     0xFFFC0000
                #define Q_HEAD_PTR_SHIFT                    18
                #define Q_TAIL_PTR_MASK                     0x0003FFF0
                #define Q_TAIL_PTR_SHIFT                    4
                #define Q_TOKEN_SIZE_MASK                   0x00000003
                #define Q_TOKEN_SIZE_SHIFT                  0
  uint32        cfgA;   // 04
                #define Q_SIZE_MASK                         0xffff0000
                #define Q_SIZE_SHIFT                        16
                #define Q_START_ADDR_MASK                   0x0000ffff
                #define Q_START_ADDR_SHIFT                  0
  uint32        cfgB;   // 08
                #define Q_NUM_TKNS_MASK                     0x3fff0000
                #define Q_NUM_TKNS_SHIFT                    16
                #define Q_LOW_WATERMARK_MASK                0x00003fff
                #define Q_LOW_WATERMARK_SHIFT               0
  uint32        sts;    // 0c
                #define AVAIL_TOKEN_SPACE_MASK              0x00003FFF
} DQMQRegs_S;

typedef struct DQMQCntrlRegs_S
{
  DQMQRegs_S q[32];
} DQMQCntrlRegs_S;


// DQM Queue Data
typedef struct DQMQueueDataReg_S
{
  uint32        word0;   // 00
  uint32        word1;   // 04
  uint32        word2;   // 08
  uint32        word3;   // 0c
} DQMQueueDataReg_S;

typedef struct DQMQDataRegs_S
{
  DQMQueueDataReg_S q[32];
} DQMQDataRegs_S;


// DQM Queue MIB
typedef struct DQMQMibRegs_S 
{
  uint32          MIB_NumFull[32];
  uint32          MIB_NumEmpty[32];
  uint32          MIB_TokensPushed[32];

} DQMQMibRegs_S;

// DPE Basic Control Registers
typedef struct DpeBasicRegs_S
{
  uint32        basic_ffe_cmd_word0;        // 00
                #define DPE_CMD_WORD0_CMD_SHIFT           30
                #define DPE_CMD_WORD0_CMD_MASK            0xC0000000
                #define DPE_CMD_WORD0_PKT_MEM_SLOT_SHIFT  27
                #define DPE_CMD_WORD0_PKT_MEM_SLOT_MASK   0x38000000
                #define DPE_CMD_WORD0_NUG_MEM_SLOT_SHIFT  24
                #define DPE_CMD_WORD0_NUG_MEM_SLOT_MASK   0x07000000
                #define DPE_CMD_WORD0_BUF_LEN_SHIFT       15
                #define DPE_CMD_WORD0_BUF_LEN_MASK        0x00FF8000
                #define DPE_CMD_WORD0_FFE_PC_SHIFT        0
                #define DPE_CMD_WORD0_FFE_PC_MASK         0x00007FFF
  uint32        basic_ffe_cmd_word1;        // 04
                #define DPE_CMD_WORD1_MPEG_CMD_SHIFT      31
                #define DPE_CMD_WORD1_MPEG_CMD_MASK       0x80000000
                #define DPE_CMD_WORD1_DMA_ADDR_SHIFT      0
                #define DPE_CMD_WORD1_DMA_ADDR_MASK       0x0000FFFF
  uint32        basic_ffe_sts_word0;      // 08
                #define DPE_STS_WORD0_FIFO_DEPTH_SHIFT    27
                #define DPE_STS_WORD0_FIFO_DEPTH_MASK     0xF8000000
                #define DPE_STS_WORD0_DMA_XFER_ERR_SHIFT  26
                #define DPE_STS_WORD0_DMA_XFER_ERR_MASK   0x04000000
                #define DPE_STS_WORD0_PKT_MEM_SLOT_SHIFT  23
                #define DPE_STS_WORD0_PKT_MEM_SLOT_MASK   0x03800000
                #define DPE_STS_WORD0_NUG_MEM_SLOT_SHIFT  20
                #define DPE_STS_WORD0_NUG_MEM_SLOT_MASK   0x00700000
                #define DPE_STS_WORD0_FFE_RETURN_VALUE0_SHIFT       0
                #define DPE_STS_WORD0_FFE_RETURN_VALUE0_MASK        0x0000FFFF
  uint32        basic_ffe_sts_word1;      // 0c
                #define DPE_STS_WORD1_FFE_RETURN_VALUE1_SHIFT       0
                #define DPE_STS_WORD1_FFE_RETURN_VALUE1_MASK        0xFFFFFFFF
  uint32        basic_dpe_config;     // 10
                #define DPE_CONFIG_MPEG_MODE_SHIFT                   2
                #define DPE_CONFIG_MPEG_MODE_MASK                    0x00000004
                #define DPE_CONFIG_ENALBE_FFE_COMMAND_SHIFT          1
                #define DPE_CONFIG_ENALBE_FFE_COMMAND_MASK           0x00000002
                #define DPE_CONFIG_FFE_RESET_N_SHIFT                 0
                #define DPE_CONFIG_FFE_RESET_N_MASK                  0x00000001
  uint32        basic_cmd_fifo_1_status;     // 14
                #define DPE_FIFO_STS_FULL_SHIFT                      31
                #define DPE_FIFO_STS_FULL_MASK                       0x80000000
                #define DPE_FIFO_STS_NOT_EMPTY_SHIFT                 30
                #define DPE_FIFO_STS_NOT_EMPTY_MASK                  0x40000000
                #define DPE_FIFO_STS_UNDERRUN_SHIFT                  29
                #define DPE_FIFO_STS_UNDERRUN_MASK                   0x20000000
                #define DPE_FIFO_STS_OVERRUN_SHIFT                   28
                #define DPE_FIFO_STS_OVERRUN_MASK                    0x10000000
                #define DPE_FIFO_STS_WPTR_SHIFT                      16
                #define DPE_FIFO_STS_WPTR_MASK                       0x001F0000
                #define DPE_FIFO_STS_RPTR_SHIFT                      8
                #define DPE_FIFO_STS_RPTR_MASK                       0x00001F00
                #define DPE_FIFO_STS_DEPTH_SHIFT                     0
                #define DPE_FIFO_STS_DEPTH_MASK                      0x0000001F
  uint32        basic_cmd_fifo_2_status;          // 18
  uint32        basic_sts_fifo_1_status;          // 1c
  uint32        basic_sts_fifo_2_status;          // 20
  uint32        basic_dma_fifo_status;            // 24
  uint32        basic_dma_ctrl_fifo_status;       // 28
  uint32        basic_fifo_status;                // 2c
  uint32        basic_fifo_status_mask;           // 30
                #define DPE_CMD_FIFO_1_FULL_MASK                     0x80000000
                #define DPE_CMD_FIFO_1_NOT_EMPTY_MASK                0x40000000
                #define DPE_CMD_FIFO_1_UNDERRUN_MASK                 0x20000000
                #define DPE_CMD_FIFO_1_OVERRUN_MASK                  0x10000000
                #define DPE_CMD_FIFO_2_FULL_MASK                     0x08000000
                #define DPE_CMD_FIFO_2_NOT_EMPTY_MASK                0x04000000
                #define DPE_CMD_FIFO_2_UNDERRUN_MASK                 0x02000000
                #define DPE_CMD_FIFO_2_OVERRUN_MASK                  0x01000000
                #define DPE_STS_FIFO_1_FULL_MASK                     0x00800000
                #define DPE_STS_FIFO_1_NOT_EMPTY_MASK                0x00400000
                #define DPE_STS_FIFO_1_UNDERRUN_MASK                 0x00200000
                #define DPE_STS_FIFO_1_OVERRUN_MASK                  0x0010000
                #define DPE_STS_FIFO_2_FULL_MASK                     0x00080000
                #define DPE_STS_FIFO_2_NOT_EMPTY_MASK                0x00040000
                #define DPE_STS_FIFO_2_UNDERRUN_MASK                 0x00020000
                #define DPE_STS_FIFO_2_OVERRUN_MASK                  0x00010000
                #define DPE_DMA_FIFO_1_FULL_MASK                     0x00008000
                #define DPE_DMA_FIFO_1_NOT_EMPTY_MASK                0x00004000
                #define DPE_DMA_FIFO_1_UNDERRUN_MASK                 0x00002000
                #define DPE_DMA_FIFO_1_OVERRUN_MASK                  0x00001000
                #define DPE_DMA_CTRL_FIFO_2_FULL_MASK                0x00000800
                #define DPE_DMA_CTRL_FIFO_2_NOT_EMPTY_MASK           0x00000400
                #define DPE_DMA_CTRL_FIFO_2_UNDERRUN_MASK            0x00000200
                #define DPE_DMA_CTRL_FIFO_2_OVERRUN_MASK             0x00000100
  uint32        basic_mpeg_fifo_status;     // 34
  uint32        basic_mpeg_status;          // 38
  uint32        basic_mpeg_status_mask;     // 3c
  uint32        basic_mpeg_timestamp;       // 40
  uint32        basic_ffe_status;           // 44
  uint32        basic_ffe_status_mask;      // 48
                #define DPE_FFE_STATUS_UNSUP_CRC_TYPE_MASK           0x00000008
                #define DPE_FFE_STATUS_UNSUP_CRC_POLY_MASK           0x00000004
                #define DPE_FFE_STATUS_HALT_IN_ISR_MASK              0x00000002
                #define DPE_FFE_STATUS_INVALID_OPCODE_MASK           0x00000001
  uint32        basic_dpe_interrupt;        // 4c
                #define DPE_INTERRUPT_FFE_MASK                       0x00000004
                #define DPE_INTERRUPT_MPEG_MASK                      0x00000002
                #define DPE_INTERRUPT_BASIC_MASK                     0x00000001
  uint32        basic_dpe_debug_state_codes;// 50
  uint32        basic_ffe_debug1;           // 54
  uint32        basic_ffe_debug2;           // 58
  uint32        basic_ffe_ctrl1;            // 5c
                #define DPE_BASIC_FFE_CTRL1_INT_DISABLE_MASK         0x00000001
  uint32        basic_ffe_ctrl2;            // 60
  uint32        basic_diag_control;         // 64
  uint32        basic_diag_out;             // 68
  uint32        basic_dpe_revision;         // 6c
  uint32        basic_ffe_revision;         // 70
} DpeBasicRegs_S;


typedef struct MiscIrqRegs_S
{
    uint32 extra2ChipIrqStatus;
           #define IRQ_CHIP_ENETSW_TX_DMA_0     (1 << 0)
           #define IRQ_CHIP_ENETSW_TX_DMA_1     (1 << 1)
           #define IRQ_CHIP_ENETSW_TX_DMA_2     (1 << 2)
           #define IRQ_CHIP_ENETSW_TX_DMA_3     (1 << 3)
           #define IRQ_CHIP_SAR                 (1 << 4)
           #define IRQ_CHIP_RTC                 (1 << 5)
           #define IRQ_CHIP_ENETSW              (1 << 6)

    uint32 reserved1;
    uint32 reserved2;

    uint32 fapIrqMask;       /* 4ke IRQ mask bits for chipIrqStatus */
    uint32 extraFapIrqMask;  /* 4ke IRQ mask bits for extraChipIrqStatus*/
    uint32 extra2FapIrqMask; /* 4ke IRQ mask bits for extra2ChipIrqStatus */
} MiscIrqRegs_S;

typedef struct ChipIrqStatusRegs_S
{
    uint32 extraChipIrqStatus;
           #define IRQ_CHIP_ENETSW_RX_DMA_0     (1 << 0)
           #define IRQ_CHIP_ENETSW_RX_DMA_1     (1 << 1)
           #define IRQ_CHIP_ENETSW_RX_DMA_2     (1 << 2)
           #define IRQ_CHIP_ENETSW_RX_DMA_3     (1 << 3)
           #define IRQ_CHIP_PCM_DMA_0           (1 << 4)
           #define IRQ_CHIP_PCM_DMA_1           (1 << 5)
           #define IRQ_CHIP_DECT_0              (1 << 6)
           #define IRQ_CHIP_DECT_1              (1 << 7)
           #define IRQ_CHIP_EXTERNAL_0          (1 << 8)
           #define IRQ_CHIP_EXTERNAL_1          (1 << 9)
           #define IRQ_CHIP_EXTERNAL_2          (1 << 10)
           #define IRQ_CHIP_EXTERNAL_3          (1 << 11)
           #define IRQ_CHIP_SAR_DMA_0           (1 << 12)
           #define IRQ_CHIP_SAR_DMA_1           (1 << 13)
           #define IRQ_CHIP_SAR_DMA_2           (1 << 14)
           #define IRQ_CHIP_SAR_DMA_3           (1 << 15)
           #define IRQ_CHIP_SAR_DMA_4           (1 << 16)
           #define IRQ_CHIP_SAR_DMA_5           (1 << 17)
           #define IRQ_CHIP_SAR_DMA_6           (1 << 18)
           #define IRQ_CHIP_SAR_DMA_7           (1 << 19)
           #define IRQ_CHIP_SAR_DMA_8           (1 << 20)
           #define IRQ_CHIP_SAR_DMA_9           (1 << 21)
           #define IRQ_CHIP_SAR_DMA_10          (1 << 22)
           #define IRQ_CHIP_SAR_DMA_11          (1 << 23)
           #define IRQ_CHIP_SAR_DMA_12          (1 << 24)
           #define IRQ_CHIP_SAR_DMA_13          (1 << 25)
           #define IRQ_CHIP_SAR_DMA_14          (1 << 26)
           #define IRQ_CHIP_SAR_DMA_15          (1 << 27)
           #define IRQ_CHIP_SAR_DMA_16          (1 << 28)
           #define IRQ_CHIP_SAR_DMA_17          (1 << 29)
           #define IRQ_CHIP_SAR_DMA_18          (1 << 30)
           #define IRQ_CHIP_SAR_DMA_19          (1 << 31)

    uint32 chipIrqStatus;
           #define IRQ_CHIP_TIMER               (1 << 0)
           #define IRQ_CHIP_RING_OSC            (1 << 1)
           #define IRQ_CHIP_LS_SPIM             (1 << 2)
           #define IRQ_CHIP_UART_0              (1 << 3)
           #define IRQ_CHIP_UART_1              (1 << 4)
           #define IRQ_CHIP_HS_SPIM             (1 << 5)
           #define IRQ_CHIP_WLAN_GPIO           (1 << 6)
           #define IRQ_CHIP_WLAN                (1 << 7)
           #define IRQ_CHIP_IPSEC               (1 << 8)
           #define IRQ_CHIP_USBH                (1 << 9)
           #define IRQ_CHIP_USBH20              (1 << 10)
           #define IRQ_CHIP_USBS                (1 << 11)
           #define IRQ_CHIP_NAND_FLASH          (1 << 12)
           #define IRQ_CHIP_PCM                 (1 << 13)
           #define IRQ_CHIP_EPHY                (1 << 14)
           #define IRQ_CHIP_DG                  (1 << 15)
           #define IRQ_CHIP_EPHY_ENERGY_0       (1 << 16)
           #define IRQ_CHIP_EPHY_ENERGY_1       (1 << 17)
           #define IRQ_CHIP_EPHY_ENERGY_2       (1 << 18)
           #define IRQ_CHIP_EPHY_ENERGY_3       (1 << 19)
           #define IRQ_CHIP_USB_CNTL_RX_DMA     (1 << 20)
           #define IRQ_CHIP_USB_CNTL_TX_DMA     (1 << 21)
           #define IRQ_CHIP_USB_BULK_RX_DMA     (1 << 22)
           #define IRQ_CHIP_USB_BULK_TX_DMA     (1 << 23)
           #define IRQ_CHIP_USB_ISO_RX_DMA      (1 << 24)
           #define IRQ_CHIP_USB_ISO_TX_DMA      (1 << 25)
           #define IRQ_CHIP_IPSEC_DMA_0         (1 << 26)
           #define IRQ_CHIP_IPSEC_DMA_1         (1 << 27)
           #define IRQ_CHIP_XDSL                (1 << 28)
           #define IRQ_CHIP_FAP                 (1 << 29)
           #define IRQ_CHIP_PCIE_RC             (1 << 30)
           #define IRQ_CHIP_PCIE_EP             (1 << 31)
} ChipIrqStatusRegs_S;

typedef enum {
  FAP_ALL_REG,
  FAP_CNTRL_REG,
  FAP_OGMSG_REG,
  FAP_INMSG_REG,
  FAP_DMA_REG,
  FAP_TKNINTF_REG,
  FAP_MSGID_REG,
  FAP_DQM_REG,
  FAP_DQMQCNTRL_REG,
  FAP_DQMQDATA_REG,
  FAP_DQMQMIB_REG,
  FAP_DPE_REG
} fapRegGroups_t;

void fapHostHw_PrintRegs(fapRegGroups_t regGroup);

#if defined(BCM_ASSERT_SUPPORTED)
#define FAP_HOST_ASSERT(x)   BCM_ASSERT(x);
#else
#define FAP_HOST_ASSERT(x)
#endif

#ifndef HalDebugPrint
#define HalDebugPrint(zone, fmt, arg...)
#endif

#if defined(BCM_LOG_SUPPORTED)
#define FAP_HOST_LOG(fmt, arg...) BCM_LOG_DEBUG(BCM_LOG_ID_FAP, fmt, ##arg)
#else
#define FAP_HOST_LOG(fmt, arg...) HalDebugPrint(ZONE_INIT, fmt "\n", ##arg)
#endif

#if defined(FAP_DEBUG_MODE)
// Use macros FAP_REG_RD and FAP_REG_WR instead of directly using these
static inline uint32 fapHostAddrRead(volatile uint32 *addr, char *addrName)
{
    uint32 val;

    FAP_HOST_ASSERT(addr != NULL);

    val = FAP_ADDR_RD(addr);

    FAP_HOST_LOG(" [FAP HOST RD @ 0x%08lX] %s = 0x%08lX", (uint32)(addr), addrName, val);

    return val;
}

static inline void fapHostAddrWrite(volatile uint32 *addr, uint32 val, char *addrName)
{
    FAP_HOST_ASSERT(addr != NULL);

    FAP_ADDR_WR(addr, val);

    FAP_HOST_LOG("[FAP HOST WR @ 0x%08lX] %s = 0x%08lX", (uint32)(addr), addrName, val);
}
#endif

#endif  /* defined(__FAP_HW_H_INCLUDED__) */
