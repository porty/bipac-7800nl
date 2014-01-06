#ifndef __FAP4KE_TASK_H_INCLUDED__
#define __FAP4KE_TASK_H_INCLUDED__

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
 * File Name  : fap4ke_task.h
 *
 * Description: This file contains the Task Manager Definitions.
 *
 *******************************************************************************
 */


/*******************************************************************
 * Public API
 *******************************************************************/

#include "fap_task.h"

#define FAP4KE_TASK_INIT(_task, _taskHandler, _arg)     \
    do {                                                \
        (_task)->handler = (_taskHandler);              \
        (_task)->arg = (_arg);                          \
        (_task)->name = #_taskHandler;                  \
        (_task)->refCount = 0;                          \
    } while(0)

void fap4keTsk_init(void);

void fap4keTsk_loop(void);

/* IMPORTANT: tasks may only be scheduled in interrupt context! */
fapRet fap4keTsk_schedule(fap4keTsk_taskPriority_t taskPriority,
                          fap4keTsk_task_t *task);

/*******************************************************************
 * Private
 *******************************************************************/

typedef struct {
    Dll_t list;
    uint32 count;
} fap4keTsk_workQueue_t;

typedef struct {
    fap4keTsk_workQueue_t workQueue[FAP4KE_TASK_PRIORITY_MAX];
    volatile int32 count;
} fap4keTsk_scheduler_t;

#endif  /* defined(__FAP4KE_TASK_H_INCLUDED__) */
