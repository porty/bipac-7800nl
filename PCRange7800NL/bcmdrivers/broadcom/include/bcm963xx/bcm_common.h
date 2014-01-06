/*
<:copyright-broadcom 
 
 Copyright (c) 2004 Broadcom Corporation 
 All Rights Reserved 
 No portions of this material may be reproduced in any form without the 
 written permission of: 
          Broadcom Corporation 
          16215 Alton Parkway 
          Irvine, California 92619 
 All information contained in this document is Broadcom Corporation 
 company private, proprietary, and trade secret. 
 
:>
*/

#ifndef __BCM_COMMON_H
#define __BCM_COMMON_H

#if defined(CONFIG_BCM96328)
#include <6328_common.h>
#endif
#if defined(CONFIG_BCM96368)
#include <6368_common.h>
#endif
#if defined(CONFIG_BCM96816)
#include <6816_common.h>
#endif
#if defined(CONFIG_BCM96362)
#include <6362_common.h>
#endif

#define __save_and_cli  save_and_cli
#define __restore_flags restore_flags

#endif

