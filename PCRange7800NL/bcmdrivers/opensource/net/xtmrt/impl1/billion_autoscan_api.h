#include "bcmxtmcfg.h"
#include "bcmxtmrt.h"
#include "bcmxtmrtimpl.h"

#define DEFAULTMODE     0
#define AUTOSCANMODE    1
#define AUTOSCANMARK    4096
#define GETMODE 0
#define SETMODE 1
#define BUF_LEN      (2048 - 16 - 64 - (sizeof(struct skb_shared_info)))


void scanpvc_parse_rxpacket( UINT8 * data, UINT32* pbxStatus, PBCMXTMRT_DEV_CONTEXT pDevCtx, UINT32* PotocolType);
void setNet16(UINT8 *address, UINT16 data);
UINT16 getNet16(UINT8 *address);
UINT16 udp_sum_calc(UINT16 len_udp, UINT8 buff[]);
UINT16 calculateIPheaderChecksum(uint8 mode, uint8 *rawPacketPtr);
void fill_the_test_pattern(unsigned char* mac_addr_p);
BCMXTM_STATUS AutoScanTestSend(int PacketType, PBCMXTMRT_DEV_CONTEXT pDevCtx);
UINT32 DoSendAutoScanPkt(PBCMXTMRT_DEV_CONTEXT  pDevCtx , PXTMCFGDRV_AUTOSCAN_PVC pParm );
void GetAndSetMode(int option, UINT32* mode);
UINT32 DoGetAutoScanReport(UINT32* pPotocolType,UINT32* pGlob_PotocolType);
