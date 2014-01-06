/***********************************************************
 *
 * Copyright (c) 2009 Broadcom Corporation
 * All Rights Reserved
 *
<:license-private
 *
 ************************************************************/

#ifndef __FAP4KE_INIT_H_INCLUDED__
#define __FAP4KE_INIT_H_INCLUDED__

/*
 *******************************************************************************
 * File Name  : fap4ke_init.h
 *
 * Description: This file contains ...
 *
 *******************************************************************************
 */

//#define CC_FAP_6362A0

#define FAP_INIT_4KE_STACK_SIZE 1024

#if defined(CC_FAP_6362A0)
#define DSPRAM_SIZE          (1<<12)
#define DSPRAM_BASE          0x00002000
#else
#define DSPRAM_SIZE          (1<<13)
#define DSPRAM_BASE          0x00004000
#endif

#define DSPRAM_VBASE         (DSPRAM_BASE | 0x80000000)

#define FAP_INIT_DSPRAM_STACK_POINTER_LOC ( DSPRAM_VBASE + FAP_INIT_4KE_STACK_SIZE )

#endif  /* defined(__FAP4KE_INIT_H_INCLUDED__) */
