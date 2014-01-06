#ifndef __FAPTMR_H_INCLUDED__
#define __FAPTMR_H_INCLUDED__

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
 * File Name  : fapMips_timers.h
 *
 * Description: This file contains global definitions of the Timers
 *              implementation for the BCM6362 FAP.
 *
 *******************************************************************************
 */

#include "fap4ke_task.h"

/* System timer tick rate */
#define FAPTMR_HZ 10

#define FAPTMR_CLOCK_HZ 166666667   /* changed from 200MHz Feb 24, 2010 */

#define fap4keTmr_jiffies64 ( *((volatile int64 *)(&p4keDspramGbl->timers.jiffies64)) )

#define fap4keTmr_jiffies ( (uint32)(fap4keTmr_jiffies64) )

#define FAP4KE_TIMER_INIT(_timer, _handler, _arg, _taskPriority)        \
    do {                                                                \
        (_timer)->taskPriority = (_taskPriority);                       \
        FAP4KE_TASK_INIT(&(_timer)->task, (_handler), (_arg));          \
    } while(0)

/* The following 4 macros are provided for comparing tick counts that correctly handle
   wraparound in the tick count. The _unknown parameter is typically fap4keTmr_Jiffies,
   and the _known parameter is the value against which you want to compare */

/* if _unknown is after _known, true; otherwise false */
#define fap4keTmr_isTimeAfter(_unknown, _known) ( (int32)(_known) - (int32)(_unknown) < 0 )

/* if _unknown is before _known, true; otherwise false */
#define fap4keTmr_isTimeBefore(_unknown, _known) fap4keTmr_isTimeAfter(_known, _unknown)

/* if _unknown is after than or equal to _known, true; otherwise false */
#define fap4keTmr_isTimeAfter_eq(_unknown, _known) ( (int32)(_unknown) - (int32)(_known) >= 0 )

/* if _unknown is before than or equal to _known, true; otherwise false */
#define fap4keTmr_isTimeBefore_eq(_unknown, _known) fap4keTmr_isTimeAfter_eq(_known, _unknown)

typedef struct {
    Dll_t node;            /* used internally to maintain linked-list of timers */
    uint32 expiration;     /* expiration time, in fap4keTmr_Jiffies */
    fap4keTsk_taskPriority_t taskPriority; /* timer task priority */
    fap4keTsk_task_t task; /* the task in which the timer handler will run */
} fap4keTmr_timer_t;

fapRet fap4keTmr_add(fap4keTmr_timer_t *timer);
void fap4keTmr_Init(void);

#define FAP4KE_PM_CPU_HISTORY_MAX 8

typedef struct {
    uint32 cp0Count;
    uint32 busy;
    uint32 capture;
} fap4keTmr_cpuSample_t;

#define p4keCpuSample ( (&p4keDspramGbl->timers.cpu) )

typedef struct {
    uint32 index;
    uint32 busy[FAP4KE_PM_CPU_HISTORY_MAX];
} fap4keTmr_cpuHistory_t;

#define p4keCpuHistory ( (&p4kePsmGbl->timers.cpu) )

#define pHostCpuHistory ( (&pHostPsmGbl->timers.cpu) )

#endif  /* defined(__FAPTMR_H_INCLUDED__) */
