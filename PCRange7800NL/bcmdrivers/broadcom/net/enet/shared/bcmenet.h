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
#ifndef _BCMENET_H_
#define _BCMENET_H_

#include <linux/skbuff.h>
#include <linux/if_ether.h>
#include <linux/if_vlan.h>
#include <bcm_map.h>
#include <linux/spinlock.h>
#include <linux/interrupt.h>
#include <linux/netdevice.h>
#include <linux/etherdevice.h>
#include "boardparms.h"
#include "bcm_log.h"
#include <bcmnet.h>
#include <bcm/bcmswapitypes.h>
#include <linux/version.h>

/*---------------------------------------------------------------------*/
/* specify number of BDs and buffers to use                            */
/*---------------------------------------------------------------------*/
/* In order for ATM shaping to work correctly,
 * the number of receive BDS/buffers = # tx queues * # buffers per tx queue
 * (80 ENET buffers = 8 tx queues * 10 buffers per tx queue)
 */
#define ENET_CACHE_SMARTFLUSH
// bill #define ENET_MAX_MTU_SIZE       (1528 + 4)    /* Body(1500) + EH_SIZE(14) + VLANTAG(4) + BRCMTAG(6) + FCS(4) */
#define ENET_MAX_MTU_SIZE       (2076 + 4)    /* Body(2048) + EH_SIZE(14) + VLANTAG(4) + BRCMTAG(6) + FCS(4) */
#define ENET_MIN_MTU_SIZE       60            /* Without FCS */

#define DMA_MAX_BURST_LENGTH    8       /* in 64 bit words */
#define RX_BONDING_EXTRA        0
#define RX_ENET_FKB_INPLACE     sizeof(FkBuff_t)
#define RX_ENET_SKB_HEADROOM    176
#define SKB_ALIGNED_SIZE        ((sizeof(struct sk_buff) + 0x0f) & ~0x0f)
#define RX_BUF_LEN              ((ENET_MAX_MTU_SIZE + 63) & ~63)
#define RX_BUF_SIZE             (SKB_DATA_ALIGN(RX_ENET_FKB_INPLACE  + \
                                                RX_ENET_SKB_HEADROOM + \
                                                RX_BONDING_EXTRA     + \
                                                RX_BUF_LEN           + \
                                                sizeof(struct skb_shared_info)))

/* misc. configuration */
#define DMA_FC_THRESH_LO        5
#define DMA_FC_THRESH_HI        (NR_RX_BDS_MIN / 2)
/* IEEE 802.3 Ethernet constant */
#define ETH_CRC_LEN             4
#define ETH_MULTICAST_BIT       0x01

#define CACHE_TO_NONCACHE(x)    KSEG1ADDR(x)
#define NONCACHE_TO_CACHE(x)    KSEG0ADDR(x)

#define ERROR(x)        printk x
#ifndef ASSERT
#define ASSERT(x)       if (x); else ERROR(("assert: "__FILE__" line %d\n", __LINE__)); 
#endif

#if defined(DUMP_TRACE)
#define TRACE(x)        printk x
#else
#define TRACE(x)
#endif

#define NUM_PORTS                   1

typedef struct extsw_info_s {
    unsigned int switch_id;
    int brcm_tag_type;
    int accessType;
    int page;
    int spi_ss;
    int spi_cid;
} extsw_info_t;

typedef struct emac_pm_addr_t {
    BOOL                valid;          /* 1 indicates the corresponding address is valid */
    unsigned int        ref;            /* reference count */
    unsigned char       dAddr[ETH_ALEN];/* perfect match register's destination address */
    char                unused[2];      /* pad */
} emac_pm_addr_t;                    
#define MAX_PMADDR          4           /* # of perfect match address */
/*
 * device context
 */ 

typedef struct {
    unsigned char da[6];
    unsigned char sa[6];
    uint16 brcm_type;
    uint32 brcm_tag;
    uint16 encap_proto;
} __attribute__((packed)) BcmEnet_hdr;
typedef struct {
    unsigned char da[6];
    unsigned char sa[6];
    uint16 brcm_type;
    uint16 brcm_tag;
    uint16 encap_proto;
} __attribute__((packed)) BcmEnet_hdr2;

#if defined(VLAN_TAG_FFF_STRIP)
#define VLAN_TYPE           0x8100
typedef struct {
    unsigned char da[6];
    unsigned char sa[6];
    uint16 brcm_type;
    uint32 brcm_tag;
    uint16 vlan_proto;
    uint16 vlan_TCI;
    uint16 encap_proto;
} __attribute__((packed)) BcmVlan_ethhdr;
typedef struct {
    unsigned char da[6];
    unsigned char sa[6];
    uint16 brcm_type;
    uint16 brcm_tag;
    uint16 vlan_proto;
    uint16 vlan_TCI;
    uint16 encap_proto;
} __attribute__((packed)) BcmVlan_ethhdr2;
#endif

#define BRCM_TYPE2          0x888A
#define BRCM_TAG_TYPE2_LEN  4
#define BRCM_TAG2_EGRESS    0x2000

#define MAX_NUM_OF_VPORTS   8
#define MAX_SWITCH_PORTS    8
#define BRCM_TAG_LEN        6
#define BRCM_TYPE           0x8874
#define BRCM_TAG_UNICAST    0x00000000
#define BRCM_TAG_MULTICAST  0x20000000
#define BRCM_TAG_EGRESS     0x40000000
#define BRCM_TAG_INGRESS    0x60000000

#if (defined(CONFIG_BCM96816) && defined(DBL_DESC))
#define MAX_MARK_VALUES   32
#define MAX_GEM_IDS       32
#define MAX_GPON_IFS      40
/* The bits[0:6] of status field in DmaDesc are Rx Gem ID. For now, we are
   using only 5 bits */
#define RX_GEM_ID_MASK    0x1F
#endif

#if defined(CONFIG_BCM96816)
#define MAX_6829_IFS      2
#define BCM6829LINKMASK   0xFF00

#endif

#define NUM_RXDMA_CHANNELS 4
#define NUM_TXDMA_CHANNELS 4

#if defined(CONFIG_BCM_PKTDMA)
//typedef BcmPktDma_EthTxDma BcmEnet_TxDma;
typedef struct BcmPktDma_EthRxDma
{
   int      enetrxchannel_isr_enable;
   volatile DmaChannelCfg *rxDma;
   volatile DmaDesc *rxBds;
   int      rxAssignedBds;
   int      rxHeadIndex;
   int      rxTailIndex;
   int      numRxBds;
   volatile int  rxEnabled;   
} BcmPktDma_EthRxDma;
                        
typedef struct BcmPktDma_EthTxDma
{
    int      txFreeBds; /* # of free transmit bds */
    int      txHeadIndex;
    int      txTailIndex;
    volatile DmaChannelCfg *txDma; /* location of transmit DMA register set */
#if (defined(CONFIG_BCM96816) && defined(DBL_DESC))
    volatile DmaDesc16 *txBds; /* Memory location of tx Dma BD ring */
#else
    volatile DmaDesc *txBds;   /* Memory location of tx Dma BD ring */
#endif
    uint32   *   pKeyPtr;
    int      *   pTxSource;   /* HOST_VIA_LINUX, HOST_VIA_DQM, FAP_XTM_RX, FAP_ETH_RX per BD */
    uint32   *   pTxAddress;  /* Shadow copy of virtual TxBD address to be used in free of tx buffer */
    volatile int txEnabled;
} BcmPktDma_EthTxDma;

typedef struct BcmEnet_RxDma {

    BcmPktDma_EthRxDma pktDmaRxInfo;
    int      rxIrq;   /* rx dma irq */
    struct sk_buff *freeSkbList;

#if defined(RXCHANNEL_PKT_RATE_LIMIT)
    volatile DmaDesc *rxBdsStdBy;
    unsigned char * StdByBuf;
#endif
    unsigned char   *buf_pool[NR_RX_BDS_MAX]; /* rx buffer pool */
    unsigned char skbs[(NR_RX_BDS_MAX * SKB_ALIGNED_SIZE) + 0x10];

} BcmEnet_RxDma;

typedef struct BcmEnet_devctrl {
    struct net_device *dev;             /* ptr to net_device */
    struct net_device *next_dev;        /* next device */
    struct net_device_stats stats;      /* statistics used by the kernel */
    volatile DmaRegs *dmaCtrl;          /* EMAC DMA register base address */
    struct tasklet_struct task;         /* tasklet */
    int             linkState;          /* link status */
    int             wanPort;            /* wan port selection */          
#if defined(CONFIG_BCM96816)
    int             mocaLinkState;      /* holds link state for moca phy */
    int             wanPort6829;        /* wan port selection on 6829 */
#endif
    int             unit;               /* device control index */
    unsigned int    vid;
    uint16          chipId;             /* chip's id */
    uint16          chipRev;            /* step */

    spinlock_t ethlock_tx;
    spinlock_t ethlock_rx;

    emac_pm_addr_t  pmAddr[MAX_PMADDR]; /* perfect match address */
    extsw_info_t  *extSwitch;          /* external switch */
    ETHERNET_MAC_INFO EnetInfo;
    IOCTL_MIB_INFO MibInfo;

#ifdef CONFIG_BCM96816
    /* For gpon virtual interfaces */
    int gem_count;                      /* Number of gem ids */
    int gponifid;   /* Unique ifindex in [0:31] for gpon virtual interface  */
#endif

    int sw_port_id; /* Physical port index of the Ethernet switch  */
    int vport_id;   /* Unique id of virtual eth interface */

    BcmPktDma_EthTxDma *txdma[NUM_TXDMA_CHANNELS];
    BcmEnet_RxDma *rxdma[NUM_RXDMA_CHANNELS];
#if !(defined(CONFIG_BCM_FAP) || defined(CONFIG_BCM_FAP_MODULE))
    uint32   txDmaKeys[NUM_TXDMA_CHANNELS*NR_TX_BDS];
    int      txDmaSources[NUM_TXDMA_CHANNELS*NR_TX_BDS];
    uint32   txDmaAddresses[NUM_TXDMA_CHANNELS*NR_TX_BDS];
#endif

    int default_txq;
    int use_default_txq;
#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,30)
    struct napi_struct napi;
#endif
} BcmEnet_devctrl;

#else   /* !defined(CONFIG_BCM_PKTDMA) */

typedef struct BcmEnet_TxDma {
    /* transmit variables */
    int      txFreeBds; /* # of free transmit bds */
    int      txHeadIndex;
    int      txTailIndex;
    void    *txNBuff[NR_TX_BDS];   /* list of ntk buffers pending transition */
    volatile DmaChannelCfg *txDma; /* location of transmit DMA register set */
#if (defined(CONFIG_BCM96816) && defined(DBL_DESC))
    volatile DmaDesc16 *txBds; /* Memory location of tx Dma BD ring */
#else
    volatile DmaDesc *txBds;   /* Memory location of tx Dma BD ring */
#endif

    int          txSource[NR_TX_BDS];   /* HOST_VIA_LINUX, HOST_VIA_DQM, FAP_XTM_RX, FAP_ETH_RX */
    volatile int txEnabled;
} BcmEnet_TxDma;

typedef struct BcmEnet_RxDma {
    struct sk_buff *freeSkbList;
    int    rxIrq;   /* rx dma irq */

    /* receive variables */
    int      numRxBds;
    int      rxAssignedBds;             /* # of BDs given to HW */
    int      rxHeadIndex;
    int      rxTailIndex;

    volatile DmaChannelCfg *rxDma;  /* location of receive DMA register set */
    volatile DmaDesc *rxBds;        /* Memory location of rx bd ring */

#if defined(RXCHANNEL_PKT_RATE_LIMIT)
    volatile DmaDesc *rxBdsStdBy;
    unsigned char * StdByBuf;
#endif
    unsigned char   *buf_pool[NR_RX_BDS_MAX]; /* rx buffer pool */
    unsigned char skbs[(NR_RX_BDS_MAX * SKB_ALIGNED_SIZE) + 0x10];

    volatile int  rxEnabled;
} BcmEnet_RxDma;

typedef struct BcmEnet_devctrl {
    struct net_device *dev;             /* ptr to net_device */
    struct net_device *next_dev;        /* next device */
    struct net_device_stats stats;      /* statistics used by the kernel */
    volatile DmaRegs *dmaCtrl;          /* EMAC DMA register base address */
    struct tasklet_struct task;         /* tasklet */
    int             linkState;          /* link status */
    int             wanPort;            /* wan port selection */          
#if defined(CONFIG_BCM96816)
    int             mocaLinkState;      /* holds link state for moca phy */
    int             wanPort6829;        /* wan port selection on 6829 */
#endif
    int             unit;               /* device control index */
    unsigned int    vid;
    uint16          chipId;             /* chip's id */
    uint16          chipRev;            /* step */

    spinlock_t ethlock_tx;
    spinlock_t ethlock_rx;

    emac_pm_addr_t  pmAddr[MAX_PMADDR]; /* perfect match address */
    extsw_info_t    *extSwitch;          /* external switch */
    ETHERNET_MAC_INFO EnetInfo;
    IOCTL_MIB_INFO MibInfo;

#ifdef CONFIG_BCM96816
    /* For gpon virtual interfaces */
    int gem_count;                      /* Number of gem ids */
    int gponifid;   /* Unique ifindex in [0:31] for gpon virtual interface  */
#endif

    int sw_port_id; /* Physical port index of the Ethernet switch  */
    int vport_id;   /* Unique id of virtual eth interface */

    BcmEnet_TxDma *txdma[NUM_TXDMA_CHANNELS];
    BcmEnet_RxDma *rxdma[NUM_RXDMA_CHANNELS];

    int default_txq;
    int use_default_txq;
#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,30)
    struct napi_struct napi;
#endif
} BcmEnet_devctrl;
#endif   /* FAP not included */

#ifndef CARDNAME
#define CARDNAME    "BCM63xx_ENET"
#endif

int bcmenet_add_proc_files(struct net_device *dev);
int bcmenet_del_proc_files(struct net_device *dev);

#ifdef CONFIG_BCM96816
extern void enet_ioctl_notify_moca_link(char * pIfName, int linkState);
#endif

#endif /* _BCMENET_H_ */

