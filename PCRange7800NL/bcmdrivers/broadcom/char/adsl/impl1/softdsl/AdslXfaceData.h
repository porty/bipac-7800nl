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
 * AdslXfaceData.h -- ADSL Core interface data structure
 *
 * Description:
 *	To be included both in SoftDsl and BcmAdslCore driver
 *
 *
 * Copyright (c) 2000-2001  Broadcom Corporation
 * All Rights Reserved
 * No portions of this material may be reproduced in any form without the
 * written permission of:
 *          Broadcom Corporation
 *          16215 Alton Parkway
 *          Irvine, California 92619
 * All information contained in this document is Broadcom Corporation
 * company private, proprietary, and trade secret.
 * Authors: Ilya Stomakhin
 *
 * $Revision: 1.14 $
 *
 * $Id: AdslXfaceData.h,v 1.14 2008/10/17 06:41:30 tonytran Exp $
 *
 * $Log: AdslXfaceData.h,v $
 * Revision 1.14  2008/10/17 06:41:30  tonytran
 * Added support for AFE input data logging and playback for 6368 in ADSL mode
 *
 * Revision 1.13  2008/09/03 20:00:29  ilyas
 * Added 6306 support indication (PHY feature) for xDSL driver to know which AfeID to use
 *
 * Revision 1.12  2008/08/14 18:14:05  ilyas
 * Added 30a support indication
 *
 * Revision 1.11  2008/07/22 23:30:16  ilyas
 * Bonding capability indication and saved EPC address
 *
 * Revision 1.10  2007/10/09 20:20:08  ilyas
 * Added PHY configuration command to 6368. VDSL configuration TBD
 *
 * Revision 1.9  2004/02/03 02:57:22  ilyas
 * Added PHY feature settings
 *
 * Revision 1.8  2003/07/18 04:50:21  ilyas
 * Added shared buffer for clEoc messages to avoid copying thru command buffer
 *
 * Revision 1.7  2003/02/25 00:46:32  ilyas
 * Added T1.413 EOC vendor ID
 *
 * Revision 1.6  2003/02/21 23:29:13  ilyas
 * Added OEM vendor ID parameter for T1.413 mode
 *
 * Revision 1.5  2002/09/13 21:17:12  ilyas
 * Added pointers to version and build string to OEM interface structure
 *
 * Revision 1.4  2002/09/07 04:16:29  ilyas
 * Fixed HOST to ADSL MIPS SDRAM address translation for relocatable images
 *
 * Revision 1.3  2002/09/07 01:43:59  ilyas
 * Added support for OEM parameters
 *
 * Revision 1.2  2002/01/22 19:03:10  khp
 * -put sdramBaseAddr at end of Xface struct
 *
 * Revision 1.1  2002/01/15 06:25:08  ilyas
 * Initial implementation of ADSL core firmware
 *
 ****************************************************************************/

#ifndef	AdslXfaceDataHeader
#define AdslXfaceDataHeader

#include "CircBuf.h"

typedef struct _AdslXfaceData {
	stretchBufferStruct sbSta;
	stretchBufferStruct sbCmd;
	unsigned long		gfcTable[15];
	void				*sdramBaseAddr;
} AdslXfaceData;

/* Shared SDRAM configuration data */

#define	kAdslOemVendorIdMaxSize		8
#define	kAdslOemVersionMaxSize		32
#define	kAdslOemSerNumMaxSize		32
#define	kAdslOemNonStdInfoMaxSize	64

typedef struct _AdslOemSharedData {
	unsigned long		g994VendorIdLen;
	unsigned long		g994XmtNonStdInfoLen;
	unsigned long		g994RcvNonStdInfoLen;
	unsigned long		eocVendorIdLen;
	unsigned long		eocVersionLen;
	unsigned long		eocSerNumLen;
	unsigned char		g994VendorId[kAdslOemVendorIdMaxSize];
	unsigned char		eocVendorId[kAdslOemVendorIdMaxSize];
	unsigned char		eocVersion[kAdslOemVersionMaxSize];
	unsigned char		eocSerNum[kAdslOemSerNumMaxSize];
	unsigned char		g994XmtNonStdInfo[kAdslOemNonStdInfoMaxSize];
	unsigned char		g994RcvNonStdInfo[kAdslOemNonStdInfoMaxSize];
	char				*gDslVerionStringPtr;
	char				*gDslBuildDataStringPtr;
	unsigned long		t1413VendorIdLen;
	unsigned char		t1413VendorId[kAdslOemVendorIdMaxSize];
	unsigned long		t1413EocVendorIdLen;
	unsigned char		t1413EocVendorId[kAdslOemVendorIdMaxSize];
	unsigned long		clEocBufLen;
	unsigned char		*clEocBufPtr;
} AdslOemSharedData;

/* feature list */ 

#define	kAdslPhyAnnexA				0
#define	kAdslPhyAnnexB				1
#define	kAdslPhyAnnexC				2
#define	kAdslPhySADSL				3
#define	kAdslPhyAdsl2				4
#define	kAdslPhyAdslG992p3			4
#define	kAdslPhyAdsl2p				5
#define	kAdslPhyAdslG992p5			5
#define	kAdslPhyAnnexI				6
#define	kAdslPhyAdslReAdsl2			7
#define	kAdslPhyG992p2Init			8
#define	kAdslPhyT1P413				9
#define	kAdslPhyVdslG993p2			10
#define	kAdslPhyBonding				11
#define	kAdslPhyVdsl30a				12
#define	kAdslPhy6306				13
#define	kAdslPhyPlayback			14
#define kAdslPhyE14InmAdsl			15

#define	AdslFeatureSupported(fa,f)	((fa)[(f) >> 5] & (1 << ((f) & 0x1F)))
#define	AdslFeatureSet(fa,f)		(fa)[(f) >> 5] |= (1 << ((f) & 0x1F))

#endif /* AdslXfaceDataHeader */
