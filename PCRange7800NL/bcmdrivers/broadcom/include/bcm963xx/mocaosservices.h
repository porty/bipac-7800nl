/*
<:copyright-broadcom 
 
 Copyright (c) 2002 Broadcom Corporation 
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
//**************************************************************************
// File Name  : BcmMoCAApi.h
//
// Description: This file contains the definitions, structures and function
//              prototypes for the Broadcom Multimedia over Coaxial
//              Alliance (MoCA) Application Program Interface (API).
//
// Updates    : 01/2/2008 Created.
//**************************************************************************

#if !defined(_MoCAOSSERVICES_H_)
#define _MoCAOSSERVICES_H_

//**************************************************************************
// Constant Definitions
//**************************************************************************
#define RTN_SUCCESS                 0
#define RTN_ERROR                   1
#define USE_CURRENT_THREAD_PRIORITY 0

//**************************************************************************
// Type Definitions
//**************************************************************************
typedef void (*FN_GENERIC) (void *);
typedef struct MoCAOsFuncs
{
    FN_GENERIC pfnAlloc;
    FN_GENERIC pfnFree;
    FN_GENERIC pfnDelay;
    FN_GENERIC pfnCreateSem;
    FN_GENERIC pfnRequestSem;
    FN_GENERIC pfnReleaseSem;
    FN_GENERIC pfnDeleteSem;
    FN_GENERIC pfnDisableInts;
    FN_GENERIC pfnEnableInts;
    FN_GENERIC pfnInvalidateCache;
    FN_GENERIC pfnFlushCache;
    FN_GENERIC pfnGetTopMemAddr;
    FN_GENERIC pfnBlinkLed;
    FN_GENERIC pfnGetSystemTick;
    FN_GENERIC pfnStartTimer;
    FN_GENERIC pfnPrintf;
} MoCA_OS_FUNCS, *PMoCA_OS_FUNCS;

//**************************************************************************
// Function Prototypes
//**************************************************************************

UINT32   MoCAOsInitialize( PMoCA_OS_FUNCS pFuncs );
char*    MoCAOsAlloc( UINT32 ulSize );
void     MoCAOsFree( char *pBuf );
UINT32   MoCAOsCreateThread( char *pszName, void *pFnEntry, UINT32 ulFnParm,
    UINT32 ulPriority, UINT32 ulStackSize, UINT32 *pulThreadId );
UINT32   MoCAOsCreateSem( UINT32 ulInitialState );
UINT32   MoCAOsRequestSem( UINT32 ulSem, UINT32 ulTimeoutMs );
void     MoCAOsReleaseSem( UINT32 ulSem );
UINT32   MoCAOsRequestSemCli( UINT32 ulSem, UINT32 ulTimeout );
void     MoCAOsReleaseSemSti( UINT32 ulSem );
void     MoCAOsDeleteSem( UINT32 ulSem );
UINT32   MoCAOsDisableInts( void );
void     MoCAOsEnableInts( UINT32 ulLevel );
void     MoCAOsDelay( UINT32 ulTimeoutMs );
UINT32   MoCAOsTickGet( void );
UINT32   MoCAOsTickCheck( UINT32 ulWaitTime, UINT32 ulMsToWait );
void     MoCAOsInvalidateCache( void *pBuf, UINT32 ulLength );
void     MoCAOsFlushCache( void *pBuf, UINT32 ulLength );
char*    MoCAOsTopMemAddr( void );
void     MoCAOsBlinkLed( void );
UINT32   MoCAOsInitDeferredHandler( void *pFnEntry, UINT32 ulFnParm,
    UINT32 ulTimeout );
void     MoCAOsScheduleDeferred( UINT32 ulHandle );
void     MoCAOsUninitDeferredHandler( UINT32 ulHandle );
UINT32   MoCAOsStartTimer( void *pFnEntry, UINT32 ulFnParm, UINT32 ulTimeout );
void     MoCAOsPrintf( char *, ... );

#endif // _MoCAOSSERVICES_H_

