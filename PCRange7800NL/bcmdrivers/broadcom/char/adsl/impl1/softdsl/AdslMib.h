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
/****************************************************************************
 *
 * AdslMib.h 
 *
 * Description:
 *	This file contains the exported functions and definitions for AdslMib
 *
 *
 * Copyright (c) 1993-1998 AltoCom, Inc. All rights reserved.
 * Authors: Ilya Stomakhin
 *
 * $Revision: 1.9 $
 *
 * $Id: AdslMib.h,v 1.9 2004/04/12 23:34:52 ilyas Exp $
 *
 * $Log: AdslMib.h,v $
 * Revision 1.9  2004/04/12 23:34:52  ilyas
 * Merged the latest ADSL driver chnages for ADSL2+
 *
 * Revision 1.8  2004/03/03 20:14:05  ilyas
 * Merged changes for ADSL2+ from ADSL driver
 *
 * Revision 1.7  2003/10/14 00:55:27  ilyas
 * Added UAS, LOSS, SES error seconds counters.
 * Support for 512 tones (AnnexI)
 *
 * Revision 1.6  2003/07/18 19:07:15  ilyas
 * Merged with ADSL driver
 *
 * Revision 1.5  2002/10/31 20:27:13  ilyas
 * Merged with the latest changes for VxWorks/Linux driver
 *
 * Revision 1.4  2002/07/20 00:51:41  ilyas
 * Merged witchanges made for VxWorks/Linux driver.
 *
 * Revision 1.3  2002/01/13 22:25:40  ilyas
 * Added functions to get channels rate
 *
 * Revision 1.2  2002/01/03 06:03:36  ilyas
 * Handle byte moves tha are not multiple of 2
 *
 * Revision 1.1  2001/12/21 22:39:30  ilyas
 * Added support for ADSL MIB data objects (RFC2662)
 *
 *
 *****************************************************************************/

#ifndef	AdslMibHeader
#define	AdslMibHeader

#if defined(_CFE_)
#include "lib_types.h"
#include "lib_string.h"
#include "lib_printf.h"
#endif

#include "AdslMibDef.h"

/* Extended showtime monitor counters */
#define kG992ShowtimeNumOfCellTotal				0	/* number of Tx Cell */
#define kG992ShowtimeNumOfCellData				1	/* number of Tx Data Cells */
#define kG992ShowtimeNumOfBitErrs					2	/* number of Tx Bit Errors */
#define kG992ShowtimeNumOfCellTotalRcved			3	/* number of Rx Cell */
#define kG992ShowtimeNumOfCellDataRcved			4	/* number of Rx Data Cells */
#define kG992ShowtimeNumOfCellDropRcved			5	/* number of Rx Cell Drops */
#define kG992ShowtimeNumOfBitErrsRcved			6	/* number of Rx Bit Errors */

#define kG992ShowtimeNumOfExtendedMonitorCounters	(kG992ShowtimeNumOfBitErrsRcved+1)	/* always last number + 1 */

/* Interface functions */

typedef	int	(SM_DECL *adslMibNotifyHandlerType)	(void *gDslVars, ulong event);

extern Boolean	AdslMibInit(void *gDslVars, dslCommandHandlerType	commandHandler);
extern void		AdslMibTimer(void *gDslVars, long timeMs);
extern void		AdslMibStatusSnooper (void *gDslVars, dslStatusStruct *status);
extern void		AdslMibSetNotifyHandler(void *gDslVars, adslMibNotifyHandlerType notifyHandlerPtr);
extern int		AdslMibGetModulationType(void *gDslVars);
extern Boolean	AdslMibIsAdsl2Mod(void *gDslVars);
extern Boolean	XdslMibIsVdsl2Mod(void *gDslVars);
extern Boolean	XdslMibIsXdsl2Mod(void *gDslVars);
extern int		AdslMibGetActiveChannel(void *gDslVars);
extern int		AdslMibGetGetChannelRate(void *gDslVars, int dir, int channel);
extern Boolean	AdslMibIsLinkActive(void *gDslVars);
extern int		AdslMibPowerState(void *gDslVars);
extern int		AdslMibTrainingState (void *gDslVars);
extern void		AdslMibClearData(void *gDslVars);
extern void		AdslMibClearBertResults(void *gDslVars);
extern void		AdslMibBertStartEx(void *gDslVars, ulong bertSec);
extern void		AdslMibBertStopEx(void *gDslVars);
extern ulong	AdslMibBertContinueEx(void *gDslVars, ulong totalBits, ulong errBits);
extern void		AdslMibSetLPR(void *gDslVars);
extern void		AdslMibSetShowtimeMargin(void *gDslVars, long showtimeMargin);
extern void		AdslMibSetNumTones (void *gDslVars, int numTones);
extern void		AdslMibResetConectionStatCounters(void *gDslVars);
extern void		AdslMibUpdateTxStat(
					void					*gDslVars,
					adslConnectionDataStat	*adslTxData,
					adslPerfCounters		*adslTxPerf,
					atmConnectionDataStat	*atmTxData);

extern void		AdslMibByteMove (int size, void* srcPtr, void* dstPtr);
extern void		AdslMibByteClear(int size, void* dstPtr);
extern int		AdslMibStrCopy(char *srcPtr, char *dstPtr);
extern long		secElapsedInDay;
/* AdslMibGetData dataId codes */

#define	kAdslMibDataAll					0

extern void		*AdslMibGetData (void *gDslVars, int dataId, void *pAdslMibData);

extern int		AdslMibSetObjectValue (
					void	*gDslVars, 
					uchar	*objId, 
					int		objIdLen,
					uchar	*dataBuf,
					ulong	*dataBufLen);
extern int		AdslMibGetObjectValue (
					void	*gDslVars, 
					uchar	*objId, 
					int		objIdLen,
					uchar	*dataBuf,
					ulong	*dataBufLen);

#if defined(CONFIG_BCM96368) || defined(CONFIG_BCM96362) || defined(CONFIG_BCM96328)
extern Boolean XdslMibIs2lpActive(void *gDslVars);
extern Boolean XdslMibIsAtmConnectionType(void *gDslVars);
extern Boolean XdslMibIsPtmConnectionType(void *gDslVars);
#endif

#endif	/* AdslMibHeader */
