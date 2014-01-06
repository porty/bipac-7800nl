#ifndef __PKT_CMF_H_INCLUDED__
#define __PKT_CMF_H_INCLUDED__

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

#if defined(CONFIG_BCM96368) || defined(CHIP_6368)
#include "pktCmf_6368.h"
#endif

#if defined(CONFIG_BCM96816) || defined(CHIP_6816)
#include "pktCmf_6816.h"
#endif

#if defined(CONFIG_BCM_FAP_MODULE) || defined(CONFIG_BCM_FAP)
#include "fap.h"
#endif

#endif  /* defined(__PKT_CMF_H_INCLUDED__) */

