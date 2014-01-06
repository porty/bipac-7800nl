/****************************************************************************
 *
 * SoftDslG993p2.h 
 *
 *
 * Description:
 *	This file contains definitions for G993p2 configuration
 *
 * $Revision: 1.65 $
 *
 * $Id: SoftDslG993p2.h,v 1.65 2009/07/02 22:48:53 rwdu Exp $
 *
 * $Log: SoftDslG993p2.h,v $
 * Revision 1.79  2009/10/30 22:42:55  jinlu
 * PR32848-a move vdsl-only bitmap in cfgFlags
 *
 * Revision 1.78  2009/10/23 22:22:24  linyin
 * PR33360: Add LD6301 line driver ID
 *
 * Revision 1.77  2009/10/23 21:00:08  rwdu
 * SRA dynamic framing support (xmt path).
 *
 * Revision 1.76  2009/10/22 02:48:20  rwdu
 * integrate Rcv dynamic framing calculation into SRA.
 *
 * Revision 1.75  2009/09/28 22:32:57  rgreenf
 * PR33224: move driver bit to cfgFlags
 *
 * Revision 1.74  2009/09/15 17:35:12  nino
 * Fix a comment.
 *
 * Revision 1.73  2009/09/15 04:32:03  mding
 * add D_sweep flag to control sweep direction
 *
 * Revision 1.72  2009/09/02 23:53:34  jinlu
 * PR32329 add support of D change in SRA
 *
 * Revision 1.71  2009/08/27 21:58:13  nino
 * Add phaseError and VCOAdjInfo fields to ntrCnt structure. Add ntrCfgStruct and related constants.
 *
 * Revision 1.70  2009/07/31 23:49:05  mding
 * add DS Dynamic D control variables
 *
 * Revision 1.69  2009/07/31 03:26:36  mding
 * record old L when L changes with Dynamic D
 *
 * Revision 1.68  2009/07/30 01:49:31  mding
 * add US Dynamic D variables
 *
 * Revision 1.67  2009/07/23 00:26:42  mding
 * add N to rxBigi for Dynamic D control
 *
 * Revision 1.66  2009/07/16 02:59:53  ilyas
 * Follow VDSL cfgFlags TPS_TC configuration
 *
 * Revision 1.65  2009/07/02 22:48:53  rwdu
 * max US tone should be target specific.
 *
 * Revision 1.64  2009/06/30 21:52:35  ovandewi
 * PR33016: Annex J board Id
 *
 * Revision 1.63  2009/06/25 15:09:57  ovandewi
 * PR32873: ANNEXJ front end family
 *
 * Revision 1.62  2009/03/13 21:12:48  ilyas
 * Added NTR control and counters report
 *
 * Revision 1.61  2009/02/25 19:24:20  linyin
 * PR32516: Fix xmt gain overflow from E14 side
 *
 * Revision 1.60  2009/02/18 06:28:14  ilyas
 * Added API function to retrieve local capabilies
 *
 * Revision 1.59  2009/02/05 01:45:59  cnpeng
 * Check in TX filters for time domain US0 in EU-36 to EU-64
 *
 * Revision 1.58  2009/01/29 22:11:45  rgreenf
 * PR32505: merge Ikanos driver bit control from AvC011_branch
 *
 * Revision 1.57  2009/01/20 19:54:52  rgreenf
 * PR32432: implement tone/bitrate clamping mechanism
 *
 * Revision 1.56  2009/01/09 18:37:33  jinlu
 * PR32042 add high crest test signal
 *
 * Revision 1.55  2008/11/17 19:08:57  ilyas
 * Added AdeId definition for 6302 frontend designs
 *
 * Revision 1.54  2008/10/24 22:44:13  yongbing
 * PR32195 Provide a driver configuration bit to control ADSL/VDSL toggling in G994
 *
 * Revision 1.53  2008/10/17 23:20:26  jinlu
 * PR32201 update xmt sync gain after bs
 *
 * Revision 1.52  2008/08/27 13:56:58  ovandewi
 * PR31845: macros to recognize POTS/ISDN HW
 *
 * Revision 1.51  2008/08/22 00:47:55  rgreenf
 * src/Adsl/Main/SoftDsl.h
 *
 * Revision 1.50  2008/08/16 01:06:10  ilyas
 * Get rid of special test target. Create common test configuration structure
 *
 * Revision 1.49  2008/08/14 20:52:57  rwdu
 * replace afe reset workaround with afe reset for B1 chips.
 *
 * Revision 1.48  2008/08/13 22:59:29  ilyas
 * Added macros to access afeInfo data
 *
 * Revision 1.47  2008/07/31 22:42:36  rgreenf
 * add status reports for annex and profile
 *
 * Revision 1.46  2008/07/24 20:18:48  ilyas
 * Added AFE frontend definitions to distinguish between 1556 multimode vs. VDSL board
 *
 * Revision 1.45  2008/07/22 23:28:01  ilyas
 * Changed AfeID definitions
 *
 * Revision 1.44  2008/07/11 22:39:59  ilyas
 * Added initial afeInfo initialization
 *
 * Revision 1.43  2008/07/11 18:50:09  rgreenf
 * add detail to afe descriptor structure
 *
 * Revision 1.42  2008/07/09 20:45:17  ilyas
 * Started framework for configurable AFE info
 *
 * Revision 1.41  2008/06/15 00:57:48  ovandewi
 * Name 6368/G993p2 cfg flags
 *
 * Revision 1.40  2008/05/20 19:34:53  jinlu
 * PR31608 enabls ds bs
 *
 * Revision 1.39  2008/05/13 22:21:57  jinlu
 * PR31781 add support to control rateAdaptationFlags from CPE GUI; init xmt/rcv ring buffer with Lmax
 *
 * Revision 1.38  2008/05/13 17:11:41  jinlu
 * PR31781-f enable ds sra for vdsl; add separate control for bs & sra; adapt tone selection with sra direction
 *
 * Revision 1.37  2008/05/09 22:03:40  jinlu
 * PR31781 enable us sra for vdsl
 *
 * Revision 1.36  2008/05/08 19:16:27  jinlu
 * PR31781 partial check-in for vdsl sra; not enabled yet
 *
 * Revision 1.35  2008/04/02 23:22:53  jinlu
 * PR31702 add compensation for AFE TF boost and 0.5dB boost for VCOPE compatibility
 *
 * Revision 1.34  2008/03/28 17:32:33  rgreenf
 * add band plan phase status
 *
 * Revision 1.33  2008/03/11 21:10:58  ilyas
 * Support nitro for 6368 B0, still disabled for now
 *
 * Revision 1.32  2008/02/25 19:31:08  jinlu
 * PR31266 implement ACTATP updating during showtime; PR31441 remove maxPower calculation in showtime
 *
 * Revision 1.31  2008/02/22 21:43:55  mding
 * define ldmode bit in cfgflags
 *
 * Revision 1.30  2008/02/22 09:57:20  jboxho
 * PhyR compilation flag fix
 *
 * Revision 1.29  2008/02/20 23:24:57  ovandewi
 * add field for fext eq upbo
 *
 * Revision 1.28  2008/01/02 19:05:18  jinlu
 * PR31373 add bitswap virtual noise support; disable showtime sync detection during active ds bs; minor improvements of tone selection for ds bs during gain adjustment
 *
 * Revision 1.27  2007/12/04 00:50:05  jinlu
 * PR31381: fix dual latency support for US bitswap; PR31346: remove false US bitswap request rejection
 *
 * Revision 1.26  2007/11/27 20:09:01  jinlu
 * Add support of RX bitswap control commands
 *
 * Revision 1.25  2007/11/19 22:03:02  nino
 * 6348 code modifications to support integration with 6368 low-level code.
 *
 * Revision 1.24  2007/11/15 14:47:40  ovandewi
 * PR31078: add US0 shaping
 *
 * Revision 1.23  2007/11/14 19:33:34  jinlu
 * add sync dump search of best margin tones for polarity check; add feq coeffs ccump before updating with new bi/gi; pipeline qproc dumps based on tx/rx alignment
 *
 * Revision 1.22  2007/11/09 23:52:21  ovandewi
 * further move component out of driver ctrl
 *
 * Revision 1.21  2007/11/09 21:59:27  tonytran
 * PR31302 - Allow PHY to accept configuration from driver
 *
 * Revision 1.20  2007/11/08 22:48:41  jinlu
 * Rx bitswap full algorithm implementation; Add dual latency support; Add NSIF driven restriction control; Add DslDiag controlled rx bitswap enabling/disabling; Add test generator for IOP
 *
 * Revision 1.19  2007/11/06 21:43:37  yongbing
 * PR31149: Get connectionSetup structure pointer directly from SoftDsl.c file
 *
 * Revision 1.18  2007/11/01 22:21:41  ovandewi
 * allow 32 RFI bands
 *
 * Revision 1.17  2007/09/26 21:12:52  jinlu
 * Fix QPROC lockup issue in test shortVdsl5Band9983BandsActiveFast; add more rx bitswap functions
 *
 * Revision 1.16  2007/09/19 19:35:33  jinlu
 * Move bitswap varibles to SlowVar; Implement RejectRequest(); Add Rx bitswap related data stucture/functions
 *
 * Revision 1.15  2007/09/18 22:35:19  dadityan
 * #defines for BandPlan Statuses
 *
 * Revision 1.14  2007/09/12 19:02:37  jinlu
 * Initial implementation of US bitswap
 *
 * Revision 1.13  2007/09/04 07:21:14  tonytran
 * PR31097: 1_28_rc8
 *
 * Revision 1.12  2007/08/24 00:35:05  rgreenf
 * add latency path id
 *
 * Revision 1.11  2007/08/23 20:56:42  rgreenf
 * add extra framer parameter reporting
 *
 * Revision 1.10  2007/08/20 21:34:04  rgreenf
 * added training phase 6368 status reporting - ongoing
 *
 * Revision 1.9  2007/08/20 16:34:19  rgreenf
 * added training phase 6368 status reporting - ongoing
 *
 * Revision 1.8  2007/08/18 00:30:41  jboxho
 * PhyR implementation on 6368 - first step
 *
 * Revision 1.7  2007/08/11 00:44:55  ovandewi
 * PR31078: rework G993p2 common data pump capability struct
 *
 * Revision 1.6  2007/08/10 21:48:38  tonytran
 * Undo previous checked-in
 *
 * Revision 1.5  2007/08/10 16:16:01  tonytran
 * *** empty log message ***
 *
 * Revision 1.4  2007/08/05 19:00:53  ilyas
 * Added overhead message support to VDSL build and status definition for DBPrint
 *
 * Revision 1.3  2007/06/08 06:30:52  ilyas
 * Added API to get negotiated G.994 parameters
 *
 * Revision 1.2  2007/06/02 17:52:24  ilyas
 * Created firmware target for 6368, ongoing work
 *
 * Revision 1.1  2007/06/01 00:39:05  ilyas
 * Moved G993p2 definitions to a separate file for E14 code
 *
 *
 *****************************************************************************/

#ifndef	SoftDslG993p2Header
#define	SoftDslG993p2Header

/* Caution: Do not change anything in this structure definition, including associated constant */
/* This structure definition is used only by the driver and any change impose incompatibility issue in driver */
/* The structure following this structure (g993p2PhyDataPumpCapabilities) can be changed in PHY application */

#define NbandsSupport 5 /* FIXME - This is not the right place for the define - move to correct place */
#define 	MAX_XMT_NBANDS	5
#define 	MAX_RCV_NBANDS	5
#define     MAX_RFI_NBANDS  32

#define   VDSL2_ANNEX_A 0x2
#define   VDSL2_ANNEX_B 0x1
#define   VDSL2_ANNEX_C 0x3
#define		PROFILE8a 		0x1
#define		PROFILE8b 		0x2
#define		PROFILE8c 		0x4
#define		PROFILE8d 		0x8
#define		PROFILE12a 		0x10
#define		PROFILE12b 		0x20
#define		PROFILE17a 		0x40
#define		PROFILE30a 		0x80
#define		NegBandPlan 		0x02
#define		PhyBandPlan 		0x01
#define   DiscoveryPhase  0x00
#define   MedleyPhase     0x01


/*cfgFlags bit defines*/
#define         CfgFlagsLdMode          0x1
#define         CfgFlagsFextEqualized   0x2
#define         CfgFlagsRawEthernetDS   0x4
#define         CfgFlagsNoPtmCrcCalc    0x8
#define         CfgFlagsNoG994AVdslToggle   0x10
#define         CfgFlagsAlignAfterPeriodics 0x20
#define         CfgFlagsVdslNoPtmSupport	0x40
#define         CfgFlagsVdslNoAtmSupport	0x80
#define         CfgFlagsVdslIfxPeriodic	  0x100 /* Enable Ifx Periodic start shift offset */
#define         CfgFlagsDynamicDFeatureDisable  0x00000200
#define         CfgFlagsDynamicFFeatureDisable  0x00000400
#define         CfgFlagsSOSFeatureDisable       0x00000800

typedef struct
	{
	 unsigned char 		selectedProfile ; 
	 short 				maxAggTxPwrDsQ4DB, maxAggTxPwrUsQ4DB ;  
	 unsigned char 		sprtUs0Reqd ; 
	 unsigned int 		minDataRate ; 
	 short 				profileDsMaxTone , profileUsMaxTone ; 
	 unsigned int 		maxDelay ; 
	 unsigned short		maxD ; 
	} g993p2ProfileContent; 

struct g993p2CommonDataPumpCapabilities
	{
	unsigned short	verId;
	unsigned short	size;

	unsigned long		profileSel;		/* bitMap bit 0 -7 profileselect for 8a,8b,8c,8d,12a,12b,17a,30a respectively */
	unsigned long		maskUS0;
	unsigned long		cfgFlags;

	unsigned long		maskEU;		/* 0->32, 1->36, 2->40, 3->44, 4->48, 5->52, 6->56, 7->60, 8->64 */
	unsigned long		maskADLU;		/* 0->32, 1->36, 2->40, 3->44, 4->48, 5->52, 6->56, 7->60, 8->64 */
	};

#ifdef BCM6368_SRC
typedef struct
	{
	struct g993p2CommonDataPumpCapabilities;
	} g993p2DataPumpCapabilities;


typedef struct
	{
	struct g993p2CommonDataPumpCapabilities;

    unsigned char		ADL, dsVirtualNoise, lineProbe, ldMode, shapingUS0, fextEqualizedUpbo;

	short 			bandStartUs[MAX_XMT_NBANDS] ; 
	short 			bandStopUs[MAX_XMT_NBANDS] ; 
	short 			bandStartDs[MAX_RCV_NBANDS] ; 
	short 			bandStopDs[MAX_RCV_NBANDS] ; 
	short 			bandStartRFI[MAX_RFI_NBANDS] ; 
	short 			bandStopRFI[MAX_RFI_NBANDS] ; 

	short			nBandsUs;
	short			nBandsDs;
	short			nBandsRFI;

	unsigned char		IDFTsize;
	unsigned short	initialIDFTsize , fillIFFT;

	unsigned short	ceLen_support ;

	unsigned long		maskA_US0;		/* 0 -> A12b ; 1 -> A17a  ; */
	unsigned long		maskB_US0;		/* 0 -> A12b ; 1 -> A17a  ; */

	unsigned char		nitroOn;
	/* tone and rate clamping control parameters 
	 * Note: rate data is specified per bearer
	 */
	unsigned int maxUsDataRateKbps[2]; 
	unsigned int maxDsDataRateKbps[2];
	unsigned int maxAggrDataRateKbps;  
	unsigned short maxUsTones; 
	unsigned short maxDsTones;
	unsigned short maxAggrTones;  
	unsigned char		US0_lcar;
	unsigned char		US0_hcar;
	} g993p2PhyDataPumpCapabilities;
#else

typedef struct g993p2CommonDataPumpCapabilities g993p2DataPumpCapabilities;
typedef struct g993p2CommonDataPumpCapabilities g993p2PhyDataPumpCapabilities;

#endif

/*
**		AFE descriptor 
*/

#define AFE_DESC_VER_MJ				0
#define AFE_DESC_VER_MN				1

#define AFE_DESC_VERSION(mj,mn)		((mj) << 8)	| (mn)

/* Board AFE ID bitmap definitions */

#define AFE_CHIP_SHIFT				28
#define AFE_CHIP_MASK				(0xF << AFE_CHIP_SHIFT)
#define AFE_CHIP_INT				1
#define AFE_CHIP_6505				2
#define AFE_CHIP_6306				3

#define AFE_CHIP_REV_SHIFT			25
#define AFE_CHIP_REV_MASK			(0x7 << AFE_CHIP_REV_SHIFT)

#define AFE_LD_SHIFT				21
#define AFE_LD_MASK					(0xF << AFE_LD_SHIFT)
#define AFE_LD_ISIL1556				1
#define AFE_LD_6301					2
#define AFE_LD_6302					3

#define AFE_LD_REV_SHIFT			18
#define AFE_LD_REV_MASK				(0x7 << AFE_LD_REV_SHIFT)

#define AFE_FE_ANNEX_SHIFT			15
#define AFE_FE_ANNEX_MASK			(0x7 << AFE_FE_ANNEX_SHIFT)
#define AFE_FE_ANNEXA				1
#define AFE_FE_ANNEXB				2
#define AFE_FE_ANNEXJ               3

#define AFE_FE_REV_SHIFT			8
#define AFE_FE_REV_MASK				(0x7F << AFE_FE_REV_SHIFT)

#define AFE_FE_REV_ISIL_MODE_MASK	0x40
#define AFE_FE_REV_ISIL_MODE_VDSL	0
#define AFE_FE_REV_ISIL_MODE_AVDSL	0x40

#define AFE_FE_REV_ISIL_REV1		1

#define AFE_FE_REV_6302_REV1		1
#define AFE_FE_REV_6302_REV_7_12	1
#define AFE_FE_REV_6302_REV_7_4		2

#define AFE_RESERVED_SHIFT			0
#define AFE_RESERVED_MASK			(0xFF << AFE_RESERVED_SHIFT)



#define MAX_AFE_BANDS                 14

#define TX_POWER_MODES                8
#define RX_POWER_MODES                8
 
#define AFE_TUNING_TX_COMP_ENABLE     0x1
#define AFE_TUNING_RX_COMP_ENABLE     0x2
#define AFE_TUNING_MAX_RX_PWR_ENABLE  0x4
#define AFE_TUNING_MAX_TX_PWR_ENABLE  0x8
 
struct afeDescStruct
  {
  unsigned short	verId;				/* of the structure itself */
  unsigned short	size;               /* size of the structure   */

  unsigned long   chipId;               /* Global chipID  such as 636800A0 */
  unsigned long   boardAfeId;           /* Bitmaped field - copy of the NVRAM AFE ID */

  unsigned long	  afeChidIdConfig0;
  unsigned long   afeChidIdConfig1;     /* bitmap to enable/control specific componion AFE chipset  behaviors */

  unsigned long   afeTuningControl;                /* bitmap to control various compensation, 1 means enable, see AFE_TUNING_XX defs */
  unsigned char   nBandsXmtMax, nBandsRcvMax;

  /* attn tone indeces*/
  unsigned short  txToneIndex[MAX_AFE_BANDS] ; 
  unsigned short  rxToneIndex[MAX_AFE_BANDS] ;
 
  /* attn - 0xffff is zero attenuation */
  unsigned short  txAttn[MAX_AFE_BANDS];
  unsigned short  rxAttn[MAX_AFE_BANDS];

  /* mean passband gains tx and rx - 0x10000 is zero gain */
  unsigned int  meanTxGain;
  unsigned int  meanRxGain;

  /* max Rx Power */
  unsigned short  maxTxPower[TX_POWER_MODES];
  unsigned short  maxRxPower[RX_POWER_MODES];
  }; 

typedef struct afeDescStruct afeDescStruct;

extern void	*SoftDslGetAfeInfo(void *gDslVars);

#ifdef gAfeInfoVars
#define gAfeInfo(x)   gAfeInfoVars
#else
#define gAfeInfo(x)   (*((afeDescStruct *)SoftDslGetAfeInfo(x)))
#endif

#define SoftDslChipId(x)		(gAfeInfo(x).chipId)
#define SoftDslIs6368(x)		((gAfeInfo(x).chipId & 0xFFFF0000) == 0x63680000)
#define SoftDslIs6368Ax(x)		((gAfeInfo(x).chipId & 0xFFFF00F0) == 0x636800A0)
#define SoftDslIs6368Bx(x)		((gAfeInfo(x).chipId & 0xFFFF00F0) == 0x636800B0)
#define SoftDslIs6368A0(x)		( gAfeInfo(x).chipId 			   == 0x636800A0)
#define SoftDslIs6368B0(x)		( gAfeInfo(x).chipId 			   == 0x636800B0)
#define SoftDslIs6368A0B0(x)   ( (gAfeInfo(x).chipId == 0x636800A0) || ( gAfeInfo(x).chipId == 0x636800B0))
#define SoftDslIs6368B1(x)		( gAfeInfo(x).chipId 			   == 0x636800B1)

#define SoftDslAfeId(x)			(gAfeInfo(x).boardAfeId)
#define SoftDslAfeChipId(x)		((gAfeInfo(x).boardAfeId & AFE_CHIP_MASK) >> AFE_CHIP_SHIFT)
#define SoftDslAfeChipIdInt(x)	(SoftDslAfeChipId(x) == AFE_CHIP_INT)
#define SoftDslAfeChipId6505(x)	(SoftDslAfeChipId(x) == AFE_CHIP_6505)
#define SoftDslAfeChipId6306(x)	(SoftDslAfeChipId(x) == AFE_CHIP_6306)

#define SoftDslAfeLD(x)			((gAfeInfo(x).boardAfeId & AFE_LD_MASK) >> AFE_LD_SHIFT)
#define SoftDslAfeLD1556(x)		(SoftDslAfeLD(x) == AFE_LD_ISIL1556)
#define SoftDslAfeLD6301(x)		(SoftDslAfeLD(x) == AFE_LD_6301)
#define SoftDslAfeLD6302(x)		(SoftDslAfeLD(x) == AFE_LD_6302)
#define SoftDslAfeIsOverIsdn(x) (((gAfeInfo(x).boardAfeId & AFE_FE_ANNEX_MASK) >> AFE_FE_ANNEX_SHIFT) == 2)
#define SoftDslAfeIsOverPots(x) (((gAfeInfo(x).boardAfeId & AFE_FE_ANNEX_MASK) >> AFE_FE_ANNEX_SHIFT) == 1)
#define SoftDslAfeIsUs0AnnexJ(x) (((gAfeInfo(x).boardAfeId & AFE_FE_ANNEX_MASK) >> AFE_FE_ANNEX_SHIFT) == 3)
/*
**		Test descriptor 
*/

#define TCFG_MODE_MASK			1
#define TCFG_MODE_NORMAL		0
#define TCFG_MODE_TEST			1

#define TCFG_MODE_RX_MASK		2
#define TCFG_MODE_RX_FBAND		0
#define TCFG_MODE_RX_BBAND		2

#define TCFG_MODE_TX_MASK		4
#define TCFG_MODE_TX_FBAND		0
#define TCFG_MODE_TX_BBAND		4

#define TCFG_TX_QUIET			0
#define TCFG_TX_REVERB			1
#define TCFG_TX_MEDLEY			2
#define TCFG_TX_HIGHCREST		3

#define TCFG_RX_TYPE_MASK		0xF
#define TCFG_RX_TYPE_IDLE		0
#define TCFG_RX_TYPE_AVG		1

#define TCFG_RX_FMT_SHIFT		4
#define TCFG_RX_FMT_MASK		0x30
#define TCFG_RX_FMT_SQ			(0<<TCFG_RX_FMT_SHIFT)
#define TCFG_RX_FMT_XY			(1<<TCFG_RX_FMT_SHIFT)

typedef struct Bpoint Bpoint;
struct Bpoint
{
  unsigned short tone;
  short value;
};

typedef struct Psd993p2 Psd993p2;
struct Psd993p2
{
  unsigned char      maxNbBP;
  unsigned char      n;
  Bpoint bp[32];
};

struct testConfigStruct {
  ushort                mode;         /* bit 0 -> 0 normal mode, 1 test mode
                                       *     1 -> 0 Rx fixed band Rx, 1 broad band
                                       *     2 -> 0 Tx fixed band Tx, 1 broad band 
                                       */
  ushort                txType;       /* 0 = QUIET, 1 = REVERB, 2 = MEDLEY, 3 = HIGH CREST...   */  
  ulong                 rxType;       /* 0..3 meas 0 - none, 1 - avg, 2 - PLN, ...              */  
                                      /* 4..5 0 = nonone, 1 = X^2+Y^2 ,2 = X+iY...              */
  ulong                 duration;     /* INFINIUM or  other non zero is duration in ms          */
  ulong                 avgPeriod;    /* average period in ms.                                  */
  ulong                 logAvgPeriod; /* floor(log2(avgPeriod)) - will be populated by adsl-mech*/
  ulong                 reportPeriod; /* report period in ms; 0 - default == avgPeriod          */
  ushort                numMonTones;  /* number of Rx monitor tones per symbol in a broadband sweep     */
  ushort                txGainDB;     /* additional gain relative to specified PSD mask in fix8_8 format*/
  ulong                 hwControl;    /* TX/RX frontend controls     */
  Psd993p2				      psd;
  uchar                 xmtBufIdx;    /* 0 = bitEnc output, 1 = replay buffer */
  uchar                 measInitReady;
  int                   crestControl;
};
typedef struct testConfigStruct testConfigStruct;

extern testConfigStruct	*SoftDslGetTestConfig(void *gDslVars);

#ifdef gTestCfgVars
#define gTestCfg(x)   gTestCfgVars
#else
#define gTestCfg(x)   (*(SoftDslGetTestConfig(x)))
#endif

#define SoftDslTestCfgMode(x)			(gTestCfg(x).mode)
#define SoftDslTestCfgIsTestMode(x)		(SoftDslTestCfgMode(x) != 0)
#define SoftDslTestCfgIsRxBB(x)			((SoftDslTestCfgMode(x) & TCFG_MODE_RX_MASK) == TCFG_MODE_RX_BBAND)
#define SoftDslTestCfgIsTxBB(x)			((SoftDslTestCfgMode(x) & TCFG_MODE_TX_MASK) == TCFG_MODE_TX_BBAND)

#define SoftDslTestCfgTx(x)				(gTestCfg(x).txType)
#define SoftDslTestCfgTxSignal(x)		(gTestCfg(x).txType)

#define SoftDslTestCfgRx(x)				(gTestCfg(x).rxType)
#define SoftDslTestCfgRxType(x)			(SoftDslTestCfgRx(x) & TCFG_RX_TYPE_MASK)
#define SoftDslTestCfgRxIdle(x)			(SoftDslTestCfgRxType(x) == TCFG_RX_TYPE_IDLE)
#define SoftDslTestCfgRxAvg(x)			(SoftDslTestCfgRxType(x) == TCFG_RX_TYPE_AVG)

#define SoftDslTestCfgRxFmt(x)			(SoftDslTestCfgRx(x) & TCFG_RX_FMT_MASK)
#define SoftDslTestCfgRxFmtSq(x)		(SoftDslTestCfgRxFmt(x) == TCFG_RX_FMT_SQ)
#define SoftDslTestCfgRxFmtXY(x)		(SoftDslTestCfgRxFmt(x) == TCFG_RX_FMT_XY)

/*
**		NTR report structure 
*/

struct ntrCntStruct {
    ulong   mipsCntAtDmt;
    ulong   mipsCntAtNtr;
    ulong   lcoCntAtDmt;
    ulong   lcoCntAtNtr;
    ulong   ncoCntAtDmt;
    ulong   ncoCntAtNtr;
    /* 6362 */
#ifdef BCM6362_CHIP
    long    phaseError;       /* 21.11 format */
    long    VCOAdjInfo;
#endif
};
typedef struct ntrCntStruct ntrCntStruct;

/* Define the valid NTR operating modes */
#define NTR_OPER_MODE_6368        (0)
#define NTR_OPER_MODE_INT         (1)
#define NTR_OPER_MODE_EXT_DRIVER  (2)

struct ntrCfgStruct {
    ulong   intModeDivRatio;     /* NTR output freq = 17.664e6/intModeDivRatio */
    ulong   extModePhaseScale;   /* scale factor used to convert external clock ticks to 17.664 MHz clock ticks */
                                 /* extModePhaseScale = 17.664/(external clock freq), 16.16 format */
    ulong   updatePeriod;        /* PLL update period in DMT symbols  */
    long    b0;                  /* loop filter, b0       */              
    long    b1;                  /* loop filter, b1       */
    uchar   operMode;
    uchar   b0_scale;            /* loop filter, b0 scale */
    uchar   b1_scale;            /* loop filter, b1 scale */
    /* The parameters below are for potential future expansion
     * if it is decided to compute the PLL loop filter coefficients
     * on the PHY MIPS instead of the HOST MIPS as is currently
     * being done.
     */
#if 0
    double zeta;              /* damping factor                 */
    double w0;
    double Kvco;              /* VCO gain                       */
    double Kphase;            /* phase detector gain            */
#endif
};
typedef struct ntrCfgStruct ntrCfgStruct;

extern void	*SoftDslGetConnectionSetupPtr(void *gDslVars);

extern void *SoftDslGetSelectedG993p2Caps(void *gDslVars);
extern void *SoftDslGetLocalCaps(void *gDslVars);
#if defined(FIRE_RETRANSMISSION) || defined(FIRE_XMT_6368)
void *SoftDslGetPhyRSpecs(void *gDslVars);
#endif

/*
**
**			G.993 status flags and structures. 
**
**	  Status codes should be defined in SoftDsl.h under
**	  "General status messages (using clearEOC message structure)"
**	  starting from   kDslGeneralMsgStart
**
*/
#ifndef __KERNEL__
typedef struct {
	ulong		ctrl;
	ULONGLONG	arg1;
	ULONGLONG	arg2;
	ulong		lineId;
	ulong		txPh;
	ulong		txSym;
	ulong		rxPh;
	ulong		rxSym;
} e14DbPrintStatus;	
#endif

typedef struct ToneGroup ToneGroup;
struct ToneGroup
{
  unsigned short endTone;
  unsigned short startTone;
};

typedef struct Bp993p2 Bp993p2;
struct Bp993p2
{
  unsigned char  noOfToneGroups;
  unsigned char  reserved;
  ToneGroup toneGroups[32];
};

typedef struct UDenNum16 UDenNum16;
struct UDenNum16
{
  unsigned short num; /*numerator*/
  unsigned short den; /*denominator*/
};
typedef struct FramerDeframerOptions FramerDeframerOptions;
struct FramerDeframerOptions
{
  UDenNum16             S;          /* S== number of PMD symbols over which the FEC data frame spans (=1 for G.dmt fast path, <=1 for ADSL2 fast path) */
  unsigned short        D;          /* interleaving depth: =1 for fast path */
  unsigned short        N;          /* RS codeword size*/
  unsigned short        L;          /* Number of bits per symbol */        
  unsigned short        B;          /* nominal total of each bearer's octets per Mux Data Frame (Slightly redundant)*/
  unsigned short        U;          /* VDSL2: Number of OH sub-frames per OH frame */
  unsigned char         I;          /* VDSL2: Interleaver block length */
  unsigned char         R;          /* RS codeword overhead bytes */
  unsigned char         M;          /* ADSL2 only. Number of Mux frames per FEC Data frame.*/
  unsigned char         T;          /* ADSL2: Number of Mux frames per sync octet*/
                                    /* VDSL2: Number of Mux data frames in an OH sub-frame */
  unsigned char         G;          /* VDSL2: Notional number of OH bytes in an OH sub-frame - actual number of bytes in any sub-frame may 1 be greater than this */
  unsigned char         F;          /* VDSL2: Number of OH frames in an OH superframe */
  unsigned char         codingType; /* codingType associated with this option */
  unsigned char         fireEnabled;/* bitmap flagging fire support for this direction
                                     * and/or for reverse direction */
  unsigned char         fireRxQueue;/* length of the retransmission queue in Rx direection */
  unsigned char         tpsTcOptions; /* result of the pmsTcNegotiation */
  unsigned char         delay;      /* actual delay incurred on this latency path */
  unsigned char         INP;        /* actual INP guaranteed on this latency path */
  unsigned char         B1;
  unsigned char					ovhType;
  unsigned char         path;
  unsigned char					ahifChanId[2];
  unsigned char         tmType[2];
};

#ifndef ADSL_ONLY
#define MAX_US_TONES1 2816
#else
#define MAX_US_TONES1 64
#endif
typedef struct {
  uint    numTones;
  int     isTrellis;
  int     ftg_wordlength;
  uint    digitalGain;
  short   analogGain;
  short   extraIFFTShift;
  ushort  *txTssiPtr;

  int     DS3boostActive;
  int     init_power_boost;
  uint    mapValXY;
  short   currentPsdVdsl; 

  uint    sraTxLmin;        /* Store for values computed after rate select */
  uint    sraTxLmax;
	uchar	  raModeUs;

  uchar   bI[MAX_US_TONES1];
  ushort  gI[MAX_US_TONES1];
  ushort  syncGain[MAX_US_TONES1];
  ushort  tI[MAX_US_TONES1];
  ushort  txTssi[MAX_US_TONES1];
  ushort  L[2];             /* Number of bits per symbol for each latency */          
  ushort  L_init;           /* Number of bits per symbol for each latency */        
  ushort  L_new;            /* Number of bits per symbol for each latency */        
#ifdef DYNAMIC_D
  ushort  D_new;
  ushort  L_old;
#endif  
#ifdef DYNAMIC_FRAMING
  uchar Tnew;
  uchar Gnew;
  uchar Bnew;
#endif
} TxInit;

typedef struct {
  uint    numTones;
  ushort  nUsed;            /* number of tones with bi >= 0 */
  int     isTrellis;
  int     snrMode;
  ushort  L[2];             /* Number of bits per symbol for each latency */        
  ushort  L_init;           /* Number of bits per symbol for each latency */        
  ushort  L_new;            /* Number of bits per symbol for each latency */        
  ushort  D[2];             /* interleaving depth: =1 for fast path */
  ushort  B[2];             /* nominal total of each bearer's octets per Mux Data Frame (Slightly redundant)*/
  uchar   T[2];             /* ADSL2: Number of Mux frames per sync octet*/
                            /* VDSL2: Number of Mux data frames in an OH sub-frame */
  uchar   G[2];             /* VDSL2: Notional number of OH bytes in an OH sub-frame - actual number of bytes in any sub-frame may 1 be greater than this */
#ifdef DYNAMIC_D
  ushort  N[2];             /* codeword length */
  ushort  L_old;
  char    D_sweep;
#endif
  ushort  D_new;            /* !!! D_new has to be defined unconditionally !!! */
  uchar   pcbRx;
#ifdef DYNAMIC_FRAMING
  uchar  Gnew;
  uchar  Tnew;
  ushort Unew;
  ushort Bnew;
#endif


  uint    sraRxLmin;        /* Store for values computed after rate select */
  uint    sraRxLmax;
	uchar	  raModeDs;
	short		sraUpShiftMarginDs;
	short		sraUpShiftMinTimeDs;
	short		sraDownShiftMarginDs;
	short		sraDownShiftMinTimeDs;

  uchar   maxConstellation; /* max allowed constellation size negotiated */
  uchar   minConstellation; /* min allowed constellation size negotiated */
  short   pilot;            /* pilot tone index (-1 if no pilot is used) */
  short   targetMargin;     /* cached copy of the physical configuration */
  short   targetMaxMargin;  /* cached copy of the physical configuration */
  uint    maxTxPower;       /* maximum transmit power with shaped PSD, equal to
                                 10^((MAXNOMATP-psdRef-10*log10(TONE_SPACING))/10)/groupSize */
  uint    maxPower;         /* maxium transmit power assuming a flat PSD, equal to nUsed, but
                                 expressed in a different format */
  short   refPsd;           /* Reference PSD of the farend tssi */
  short   psdMin;           /* minimum allowed value for the meanGain */
  short   psdMax;           /* maximum allowed value for the meanGain */
  char    *bI;
  short   *gI;
  short   *tI;
  short   *tI_inv;
  ushort  *feTssi;
  short   *maxSnrPtr;
} RxBiGi;

#endif	/* SoftDslG993p2Header */
