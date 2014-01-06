/***********************************************************
 *
 * Copyright (c) 2009 Broadcom Corporation
 * All Rights Reserved
 *
<:license-private
 *
 ************************************************************/

#ifndef __FAP4KE_IOPDMA_H_INCLUDED__
#define __FAP4KE_IOPDMA_H_INCLUDED__

/*
 *******************************************************************************
 * File Name  : fap4ke_iopDma.h
 *
 * Description: This file contains the public API for the 4KE IOP DMA driver
 *
 *******************************************************************************
 */

// needed for FAP_IOPDMA_ERROR_CHECK
//#include "fap4ke_printer.h"
//#include "fap4ke_mailBox.h"

//#define FAP_IOPDMA_ERROR_CHECK
//#define FAP_IOPDMA_BUILD_LIB

/* IOPDMA channels */
#define IOPDMA_DMA0                          0
#define IOPDMA_DMA1                          1
/* IOPDMA depth */
#define IOPDMA_DMA_DEPTH                     4
/* IOPDMA function returns */
#define IOPDMA_SUCCESS                       FAP_SUCCESS
   /* Returns for iopDma_GetDmaResults */
#define IOPDMA_RESULT_NOT_END_OF_COMMANDS    1
#define IOPDMA_RESULT_FLUSHED                2
#define IOPDMA_RESULT_ABORTED                3
#define IOPDMA_RESULT_IMPROPER_CMDLIST       4
#define IOPDMA_RESULT_DEST_INVALID           5
#define IOPDMA_RESULT_SRC_INVALID            6
#define IOPDMA_RESULT_CMDLIST_PTR_INVALID    7
#define IOPDMA_RESULT_DEST_LEN_INVALID       8
#define IOPDMA_RESULT_SRC_LEN_INVALID        9
#define IOPDMA_RESULT_FIFO_EMPTY             10
   /* Returns for iopDma_StartDmaTransfer */
#define IOPDMA_CMD_FIFO_FULL                 11

/* Returns for iopDma_GetDmaStatus */
#define IOPDMA_STATUS_RESULT_FIFO_FULL       (1<<3)
#define IOPDMA_STATUS_RESULT_FIFO_EMPTY      (1<<2)
#define IOPDMA_STATUS_CMD_FIFO_FULL          (1<<1)
#define IOPDMA_STATUS_BUSY                   (1<<0)

/* Opcodes used internally, but available for use by anyone */ 
#define IOPDMA_EXTCMDLIST_OPCODE_END                  0
#define IOPDMA_EXTCMDLIST_OPCODE_INSERT               1
#define IOPDMA_EXTCMDLIST_OPCODE_REPLACE              2
#define IOPDMA_EXTCMDLIST_OPCODE_DELETE               3
#define IOPDMA_EXTCMDLIST_OPCODE_CHECKSUM1            4
#define IOPDMA_EXTCMDLIST_OPCODE_CHECKSUM2            5
#define IOPDMA_EXTCMDLIST_OPCODE_INSERT_LENGTH        6
#define IOPDMA_EXTCMDLIST_OPCODE_REPLACE_LENGTH       7
#define IOPDMA_EXTCMDLIST_OPCODE_MEMSET               8    

/* Opcodes required to be passed into iopDma_ChecksumCmdListAdd */
#define IOPDMA_HCS_OPCODE_END                      0
#define IOPDMA_HCS_OPCODE_FIRST                    1
#define IOPDMA_HCS_OPCODE_FIRST_WITH_CONST         2
#define IOPDMA_HCS_OPCODE_FIRST_WITH_LEN           3
#define IOPDMA_HCS_OPCODE_CONTINUE                 4
#define IOPDMA_HCS_OPCODE_CONTINUE_WITH_CONST      5
#define IOPDMA_HCS_OPCODE_CONTINUE_WITH_LEN        6
#define IOPDMA_HCS_OPCODE_LAST                     7

#define IOPDMA_LOCAL_ADDR(_addr) ( (uint8 *)(_addr) )
#define IOPDMA_SDRAM_ADDR(_addr) ( (uint8 *)((uint32)(_addr) & ~0x80000000) )

/* Source Buffer structure for use in iopDma_StartDmaTransfer */
typedef struct {
   uint8   *pSourceBuffer;
   uint32   bufferLength;
} fap4keIopDma_SourceBuffer_t;

/* DMA results structure returned by iopDma_GetDmaResults */
typedef struct {
   uint8   *pResultSource;
   uint8   *pResultDestination;
   uint16   HCS0_Value;
   uint16   HCS1_Value;
   uint16   BytesTransferred;
   uint16   Continue;
} fap4keIopDma_DmaResults_t;


/*
 * Inline Functions
*/

static inline fapRet iopDma_start(uint32   channel,
                                  uint8   *pDestBuffer, 
                                  uint8   *pSourceBuffer,
                                  uint32   bufferLength,
                                  uint8    *pCommandList,
                                  uint16   pduLength)
{
    uint32 reg32;
    volatile mDma_regs_S *dma_ch_p;

#if defined(FAP_IOPDMA_ERROR_CHECK)
    if ( pSourceBuffer == NULL )
    {
        fap4kePrt_Error("Error: pSourceBuffer is NULL\n");
        return FAP_ERROR;    
    }
    
    if ( channel > 1 )
    {
        fap4kePrt_Error("Error: incorrect channel ID\n");
        return FAP_ERROR;
    }

    if (pDestBuffer == NULL)
    {
        fap4kePrt_Error("Error: pDestBuffer is NULL\n");
        return FAP_ERROR;
    }

    reg32 = FAP_4KE_REG_RD(_4keRegCntrl->dma_status);
    if ( ((channel == 0) && (reg32 & DMA_STS_DMA0_CMD_FULL_BIT)) ||
         ((channel == 1) && (reg32 & DMA_STS_DMA1_CMD_FULL_BIT)) )
    {
        fap4kePrt_Error("DMA Channel %ld is full!\n", channel);
        return IOPDMA_CMD_FIFO_FULL;
    }
#endif

    dma_ch_p = &_4keDmaReg->dma_ch[channel];

    FAP_4KE_REG_WR(dma_ch_p->dma_source, (uint32)(pSourceBuffer));
    FAP_4KE_REG_WR(dma_ch_p->dma_dest, (uint32)(pDestBuffer));

    reg32 = (bufferLength & 0xFFF);

    if (pCommandList != NULL)
    {
        /* Add in the command list every src buffer even though it will only be used on the first source buffer */
        reg32 |= DMA_CTL_LEN_EXEC_CMD_LIST_BIT;

        FAP_4KE_REG_WR(dma_ch_p->dma_cmd_list, (uint32)pCommandList);
    }

    reg32 |= DMA_CTL_LEN_WAIT_BIT;

    if ( pduLength != 0 )
    {
        reg32 |= (pduLength << DMA_CTL_LEN_LENGTH_N_VALUE_SHIFT) & DMA_CTL_LEN_LENGTH_N_VALUE_MASK;
    }

    /* Issue DMA command to block */
    FAP_4KE_REG_WR(dma_ch_p->dma_len_ctl, reg32 );

    return IOPDMA_SUCCESS;
}

static inline fapRet iopDma_finish(uint32 channel)
{
    int dmaRetry = 1000;
    uint32 reg32;
    const uint32 emptyMask = (channel == 0) ? DMA_STS_DMA0_RSLT_EMPTY_BIT :
        DMA_STS_DMA1_RSLT_EMPTY_BIT;

    /************** Wait until DMA Completes ****************/

    do
    {
        reg32 = FAP_4KE_REG_RD(_4keRegCntrl->dma_status) & emptyMask;

    } while(reg32 && --dmaRetry);

    if(dmaRetry == 0)
    {
#if defined(FAP_IOPDMA_ERROR_CHECK)
        fap4kePrt_Error("IOP_DMA timeout!");
#endif
        return FAP_ERROR;
    }

    /************** Retrieve DMA Result ****************/

    reg32 = FAP_4KE_REG_RD(_4keDmaReg->dma_ch[channel].dma_rslt_len_stat);
    
    return (reg32 & DMA_RSLT_ERROR_MASK);
}

/* Public APIs */
extern fapRet iopDma_Init(void);

#if defined(FAP_IOPDMA_BUILD_LIB)
extern fapRet iopDma_StartDmaTransfer( uint32   channel, 
                                       uint8   *pDestBuffer, 
                                       fap4keIopDma_SourceBuffer_t   *pSrcBuffers, 
                                       uint32   numSrcBuffers, 
                                       uint8    *pCommandList,
                                       BOOL     bWait,
                                       uint16   pduLength);
extern fapRet iopDma_StartDmaTransferBlocking(uint32   channel,
                                              uint8   *pDestBuffer, 
                                              uint8   *pSourceBuffer,
                                              uint32   bufferLength,
                                              uint8    *pCommandList,
                                              uint16   pduLength);
extern fapRet iopDma_GetDmaResults ( uint32  channel, 
                                     fap4keIopDma_DmaResults_t *pDmaResults); 
extern fapRet iopDma_GetDmaResultsFast ( uint32  channel, 
                                  fap4keIopDma_DmaResults_t *pDmaResults);
extern fapRet iopDma_GetDmaStatus ( uint32 channel);
extern fapRet iopDma_GetDmaCmdAvailable ( uint32   channel );
extern fapRet iopDma_GetDmaResultFifoDepth ( uint32   channel );
#endif /* FAP_IOPDMA_BUILD_LIB */

/* Functions to build command lists with.  All return length of the bytes written to command list pointer */
extern fapRet iopDma_CmdListAddEndOfCommands( uint8 *pCmdList );
extern fapRet iopDma_CmdListAddInsert( uint8   *pCmdList, 
                                       uint16   offset,
                                       uint8    *pData,
                                       uint8    length );
extern fapRet iopDma_CmdListAddReplace(   uint8   *pCmdList,
                                          uint16   offset,
                                          uint8    *pData,
                                          uint8    length );
extern fapRet iopDma_CmdListAddDelete( uint8   *pCmdList,
                                       uint16   offset,
                                       uint8    length );
extern fapRet iopDma_CmdListAddInsertLength( uint8   *pCmdList,
                                             uint16   offset,
                                             uint16   data);
extern fapRet iopDma_CmdListAddReplaceLength( uint8   *pCmdList,
                                              uint16   offset,
                                              uint16   data);
extern fapRet iopDma_CmdListAddMemset( uint8   *pCmdList,
                                       uint16   offset,
                                       uint8    data,
                                       uint8    length );
extern fapRet iopDma_CmdListAddChecksum1( uint8   *pCmdList,
                                          uint8   *pChecksumCmdList);
extern fapRet iopDma_CmdListAddChecksum2( uint8   *pCmdList,
                                          uint8   *pChecksumCmdList);
extern fapRet iopDma_ChecksumCmdListAdd( uint8   *pChecksumCmdList,
                                         uint8    opcode,
                                         uint16   offset,
                                         uint16   lengthOrConstData);

extern void iopDma_debugDumpRegs( void );
#endif
