/*
<:copyright-broadcom

 Copyright (c) 2009 Broadcom Corporation
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
 * File Name  : bcmPktDma.c
 *
 * Description: This file contains the Packet DMA initialization API.
 *
 *******************************************************************************
 */

#include <linux/module.h>

#include "bcmtypes.h"
#include "fap_task.h"
#include "bcmPktDmaHooks.h"

bcmPktDma_hostHooks_t bcmPktDma_hostHooks_g;

static void initHostHooks(void)
{
    memset(&bcmPktDma_hostHooks_g, 0, sizeof(bcmPktDma_hostHooks_t));
}

int bcmPktDma_bind(bcmPktDma_hostHooks_t *hostHooks)
{
    if(hostHooks->xmit2Fap == NULL ||
       hostHooks->dqmXmitMsgHost == NULL ||
       hostHooks->dqmRecvMsgHost == NULL ||
       hostHooks->dqmEnableHost == NULL)
    {
        return FAP_ERROR;
    }

    bcmPktDma_hostHooks_g = *hostHooks;

    printk("%s: FAP Driver binding successfull\n", __FUNCTION__);

    return FAP_SUCCESS;
}

void bcmPktDma_unbind(void)
{
    initHostHooks();
}

int __init bcmPktDma_init(void)
{
    printk("%s: Broadcom Packet DMA Library initialized\n", __FUNCTION__);

    initHostHooks();

    return 0;
}

void __exit bcmPktDma_exit(void)
{
    printk("Broadcom Packet DMA Library exited");
}

module_init(bcmPktDma_init);
module_exit(bcmPktDma_exit);

EXPORT_SYMBOL(bcmPktDma_bind);
EXPORT_SYMBOL(bcmPktDma_unbind);
