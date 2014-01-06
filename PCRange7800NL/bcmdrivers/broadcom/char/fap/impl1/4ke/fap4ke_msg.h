/************************************************************
 *
 * Copyright (c) 2009 Broadcom Corporation
 * All Rights Reserved
 *
<:license-private
 *
 ************************************************************/

#ifndef __FAP4KEMSG_H_INCLUDED__ 
#define __FAP4KEMSG_H_INCLUDED__


/******************************************************************************
* File Name  : fap4ke_msg.h                                                   *
*                                                                             *
* Description: This is the 4ke header file for communication from the         * 
*              Host MIPS FapDrv to the 4ke MIPs HostDrv                       *
******************************************************************************/

typedef enum {
  FAP_MSG_DRV_CTL,
  /* Add other message types here */
  FAP_MSG_DRV_ENET_INIT,
  FAP_MSG_DRV_XTM_INIT,
  FAP_MSG_DRV_XTM_CREATE_DEVICE,
  FAP_MSG_DRV_XTM_LINK_UP
} fapMsgGroups_t;

#define FAPMSG_CMD_RX_ENABLE        0
#define FAPMSG_CMD_RX_DISABLE	    1
#define FAPMSG_CMD_TX_ENABLE	    2
#define FAPMSG_CMD_TX_DISABLE	    3
#define FAPMSG_CMD_INIT_RX          4
#define FAPMSG_CMD_INIT_TX          5

#define FAPMSG_DRV_ENET             0
#define FAPMSG_DRV_XTM              1

typedef struct {
   uint32    cmd;
   uint32    drv;
   int32     channel;
} xmit2FapMsgDriverCtl_t;

typedef struct {
   uint32    cmd;
   uint32    drv;
   int32     channel;
   uint32    Bds;
   uint32    Dma;
   uint32    numBds;
} xmit2FapMsgDriverInit_t;

typedef struct {
   uint32    cmd;
} xmit2FapMsgFlowCfg_t;

typedef struct {
   uint32 devId;
   uint32 encapType;
} xmit2FapMsgXtmCreateDevice_t;

typedef struct {
   uint32 devId;
   uint32 matchId;
} xmit2FapMsgXtmLinkUp_t;

typedef union {

   xmit2FapMsgDriverCtl_t drvCtl;

   xmit2FapMsgFlowCfg_t flowCfg; /* For Phase II */

   /* other message types */
   xmit2FapMsgDriverInit_t drvInit;

   xmit2FapMsgXtmCreateDevice_t xtmCreateDevice;

   xmit2FapMsgXtmLinkUp_t xtmLinkUp;

} xmit2FapMsg_t;

extern int fapDrv_Xmit2Fap( fapMsgGroups_t type, xmit2FapMsg_t *pMsg );

#endif /* __FAP4KEMSG_H_INCLUDED__ */

