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
 * File Name  : pktCmfFfe.h
 *
 * Description: This file contains the specification of some common definitions
 *      and interfaces to other modules. This file may be included by both
 *      Kernel and userapp (C only).
 *
 *******************************************************************************
 */

#ifndef __PKT_CMF_FFE_H_INCLUDED__
#define __PKT_CMF_FFE_H_INCLUDED__

#define FFE_DEFAULT_TPID       0x8100
#define FFE_DEFAULT_PADLEN     0x00

#define FFE_UNSPECIFIED        (~0)

#define FFE_INST_MEM_DEPTH     2048
#define FFE_INST_MEM_SIZE_32   (FFE_INST_MEM_DEPTH * 2)

#define FFE_NUGGET_MEM_DEPTH   256
#define FFE_NUGGET_MEM_SIZE_32 FFE_NUGGET_MEM_DEPTH
#define FFE_NUGGET_MEM_SIZE_8  (FFE_NUGGET_MEM_SIZE_32 * 4)

#define FFE_DP_MEM_SIZE_8      0  /* FIXME */

#define FFE_NEQ_FLT_MAX        4

#define FFE_PATCH_MAX          2

#define DECL_NAME(_x) #_x

#define FFE_PORT_NAME                           \
    { DECL_NAME(FFE_GEPHY0),                                 \
      DECL_NAME(FFE_GEPHY1),                           \
      DECL_NAME(FFE_RGMII0),                           \
      DECL_NAME(FFE_RGMII1),                           \
      DECL_NAME(FFE_SERDES_GMII),                           \
      DECL_NAME(FFE_MOCA),                           \
      DECL_NAME(FFE_USB),                           \
      DECL_NAME(FFE_GPON) }

typedef enum {
    FFE_GEPHY0      = 0,
    FFE_GEPHY1      = 1,
    FFE_RGMII0      = 2,
    FFE_RGMII1      = 3,
    FFE_SERDES_GMII = 4,
    FFE_MOCA        = 5,
    FFE_USB         = 6,
    FFE_GPON        = 7,
    FFE_PORT_MAX    = 8
} ffePort_t;

typedef enum {
    FFE_PMASK_GEPHY0 = (1 << FFE_GEPHY0),
    FFE_PMASK_GEPHY1 = (1 << FFE_GEPHY1),
    FFE_PMASK_RGMII0 = (1 << FFE_RGMII0),
    FFE_PMASK_RGMII1 = (1 << FFE_RGMII1),
    FFE_PMASK_SERDES_GMII = (1 << FFE_SERDES_GMII),
    FFE_PMASK_MOCA = (1 << FFE_MOCA),
    FFE_PMASK_USB = (1 << FFE_USB),
    FFE_PMASK_GPON = (1 << FFE_GPON),
    FFE_PMASK_MAX = (1 << FFE_PORT_MAX)
} ffePortMask_t;

#define FFE_PMASK_ALL (FFE_PMASK_GEPHY0 |       \
                       FFE_PMASK_GEPHY1 |       \
                       FFE_PMASK_RGMII0 |       \
                       FFE_PMASK_RGMII1 |       \
                       FFE_PMASK_SERDES_GMII |  \
                       FFE_PMASK_MOCA |         \
                       FFE_PMASK_USB |          \
                       FFE_PMASK_GPON )

typedef enum {
    FFE_MEM_NUGGET,
    FFE_MEM_DP,
    FFE_MEM_INST,
    FFE_MEM_TYPE_MAX
} ffeMemType_t;

#define FFE_MEM_TYPE \
    { DECL_NAME(NUGGET), \
      DECL_NAME(DP), \
      DECL_NAME(INST) }

typedef enum {
    FFE_ACCESS_READ,
    FFE_ACCESS_WRITE,
    FFE_ACCESS_MAX
} ffeAccessType_t;

typedef enum {
    FFE_DIR_US,
    FFE_DIR_DS,
    FFE_DIR_MAX
} ffeLabelDir_t;

typedef struct {
    uint32_t addr;
    uint32_t inst[2];
} ffeLabelInfo_t;

typedef struct {
    ffeLabelInfo_t byteOffset;
    ffeLabelInfo_t valMask;
} ffeLabelNeqTable_t;

typedef struct {
    ffeLabelDir_t dir;
    uint32_t isr0Start;
    uint32_t entryPt0;
    ffeLabelNeqTable_t neqTable[FFE_NEQ_FLT_MAX];
    ffeLabelInfo_t tpid01;
    ffeLabelInfo_t tpid23;
    ffeLabelInfo_t pbitsTable;
    ffeLabelInfo_t padLen;
} ffeLabelCfg_t;

typedef struct {
    ffeMemType_t memType;
    uint32_t addr;
} ffeSnoopCfgInfo_t;

typedef struct {
    ffeSnoopCfgInfo_t parseVec;
    ffeSnoopCfgInfo_t asp;
    ffeSnoopCfgInfo_t mod;
    ffeSnoopCfgInfo_t pktParams;
} ffeSnoopCfg_t;

typedef struct {
    uint32_t addr;
    uint32_t val[2];
} ffePatchCfgInfo_t;

typedef struct {
    ffePatchCfgInfo_t patch[FFE_PORT_MAX][FFE_PATCH_MAX];
} ffePatchCfg_t;


/********************************************************
 * IOCTL structures
 ********************************************************/

typedef struct {
    ffeAccessType_t accessType;
    ffeMemType_t memType;
    union {
        ffePort_t ffePort;
        ffePortMask_t ffePortMask;
    };
    uint32_t *buf;
    uint32_t addr;
    uint32_t size;
} pktCmfFfe_iocMemAccess_t;

typedef struct {
    ffeLabelCfg_t labelCfg;
} pktCmfFfe_iocLabelCfg_t;

typedef struct {
    ffeSnoopCfg_t snoopCfg;
} pktCmfFfe_iocSnoopCfg_t;

typedef struct {
    ffePatchCfg_t patchCfg;
} pktCmfFfe_iocPatchCfg_t;

#endif /* __PKT_CMF_FFE_H_INCLUDED__ */
