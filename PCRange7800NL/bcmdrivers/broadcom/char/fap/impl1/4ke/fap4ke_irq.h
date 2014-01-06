#ifndef __FAPIRQ_H_INCLUDED__
#define __FAPIRQ_H_INCLUDED__

/***********************************************************
 *
 * Copyright (c) 2009 Broadcom Corporation
 * All Rights Reserved
 *
<:license-private
 *
 ************************************************************/

/*
 *******************************************************************************
 * File Name  : fap4ke_irq.h
 *
 * Description: This file contains ...
 *
 *******************************************************************************
 */

#define FAP4KE_IRQ_HANDLERS_MAX 8

#define fap4keIrq_enable(_irqGroup, _irqMask)  _fap4keIrq_enable((_irqGroup), (_irqMask), TRUE)
#define fap4keIrq_disable(_irqGroup, _irqMask) _fap4keIrq_enable((_irqGroup), (_irqMask), FALSE)

typedef fapRet(*fap4keIrq_handler_t)(uint32);

typedef enum {                     /* Usage (see fap_hw.h for register definitions): */
    FAP4KE_IRQ_GROUP_FAP,          /* For interrupts in the irq_4ke_status register */
    FAP4KE_IRQ_GROUP_CHIP_EXTRA2,  /* For interrupts in the extra2ChipIrqStatus register */
    FAP4KE_IRQ_GROUP_CHIP_EXTRA,   /* For interrupts in the extraChipIrqStatus register */
    FAP4KE_IRQ_GROUP_CHIP,         /* For interrupts in the chipIrqStatus register */
    FAP4KE_IRQ_GROUP_MAX
} fap4keIrq_irqGroup_t;

typedef struct
{
    fap4keIrq_handler_t handler;
    uint32 arg;
    fap4keIrq_irqGroup_t irqGroup;
    uint32 irqMask;
    char *name;
    uint32 count;
} fap4keIrq_handlerInfo_t;

#define fap4keIrq_register(_handler, _arg, _irqGroup, _irqMask) \
    __fap4keIrq_register(_handler, _arg, _irqGroup, _irqMask, #_handler)

void fap4keIrq_init(void);

fapRet __fap4keIrq_register(fap4keIrq_handler_t handler, uint32 arg,
                            fap4keIrq_irqGroup_t irqGroup, uint32 irqMask,
                            char *name);

void _fap4keIrq_enable(fap4keIrq_irqGroup_t irqGroup, uint32 irqMask, uint32 enable);

void fap4keIrq_mainHandler(void);

void printIrqStats(void);

#endif  /* defined(__FAPIRQ_H_INCLUDED__) */
