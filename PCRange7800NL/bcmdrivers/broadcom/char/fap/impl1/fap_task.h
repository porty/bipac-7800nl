#ifndef __FAP_TASK_H_INCLUDED__
#define __FAP_TASK_H_INCLUDED__

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
 * File Name  : fap_task.h
 *
 * Description: This file contains the constants and structs for FAP 4ke Tasks.
 *
 *******************************************************************************
 */

#include "fap_dll.h"

#ifndef __FAP_H_INCLUDED__
#define FAP_SUCCESS  0
#define FAP_ERROR   -1
#endif

typedef int32 fapRet;

typedef enum {
    FAP4KE_TASK_PRIORITY_HIGH=0,
    FAP4KE_TASK_PRIORITY_LOW,
    FAP4KE_TASK_PRIORITY_MAX
} fap4keTsk_taskPriority_t;

typedef fapRet(* fap4keTsk_handler_t)(uint32 arg);

typedef struct {
    Dll_t node; /* used to maintain linked-lists of tasks */
    fap4keTsk_handler_t handler;
    uint32 arg;
    char *name;
    uint32 refCount;
} fap4keTsk_task_t;

#endif  /* defined(__FAP_TASK_H_INCLUDED__) */
