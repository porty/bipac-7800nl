#ifndef __FAP4KE_PACKET_H_INCLUDED__
#define __FAP4KE_PACKET_H_INCLUDED__

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
 * File Name  : fap4ke_packet.h
 *
 * Description: This file contains ...
 *
 *******************************************************************************
 */

//#define CC_FAP4KE_PKT_FFE

//#define CC_FAP4KE_PKT_TEST

//#define CC_FAP4KE_PKT_HW_ICSUM

#if defined(CONFIG_BLOG_IPV6)
#define CC_FAP4KE_PKT_IPV6_SUPPORT
#endif

/* IPv4 Dot Decimal Notation formating */
#define IP4DDN   " <%03u.%03u.%03u.%03u>"
#define IP4PDDN  " <%03u.%03u.%03u.%03u:%05u>"
#define IP4(ip) ((uint8_t*)&ip)[0], ((uint8_t*)&ip)[1], ((uint8_t*)&ip)[2], ((uint8_t*)&ip)[3]

#define IP6HEX  "<%04x:%04x:%04x:%04x:%04x:%04x:%04x:%04x>"
#define IP6PHEX "<%04x:%04x:%04x:%04x:%04x:%04x:%04x:%04x:%u>"
#define IP6(ip) ((uint16_t*)&ip)[0], ((uint16_t*)&ip)[1],   \
                ((uint16_t*)&ip)[2], ((uint16_t*)&ip)[3],   \
                ((uint16_t*)&ip)[4], ((uint16_t*)&ip)[5],   \
                ((uint16_t*)&ip)[6], ((uint16_t*)&ip)[7]

#define ETH_ALEN           6
#define BRCM_TAG_LENGTH    6
#define ETHERTYPE_LENGTH   2
#define IPOA_HLEN          8

#define FAP4KE_PKT_MAX_FLOWS             100
#define FAP4KE_PKT_HASH_TABLE_SIZE       32  /* 256 MAX! */
#define FAP4KE_PKT_HASH_TABLE_ENTRY_MAX  FAP4KE_PKT_MAX_FLOWS

#define FAP4KE_PKT_MAX_HEADERS           4

#if defined(CC_FAP4KE_PKT_IPV6_SUPPORT)
/* Maximum header size:
 * 14 (ETH) + 6 (BRCM Tag) + 8 (2 VLANs) +
 * 8 (PPPoE) + 40 (IPv6) + 20 (IPv4) + 
 * 20 (TCP/UDP) = 116 bytes
 */
#define FAP4KE_PKT_HEADER_SIZE           116
#define FAP4KE_PKT_CMD_LIST_SIZE         168   /* max 156 expected */
#else
/* Maximum header size:
 * 14 (ETH) + 6 (BRCM Tag) + 8 (2 VLANs) +
 * 8 (PPPoE) + 20 (IPv4) + 20 (TCP/UDP) = 76 bytes
 */
#define FAP4KE_PKT_HEADER_SIZE           76
#define FAP4KE_PKT_CMD_LIST_SIZE         96
#endif

#define FAP4KE_PKT_CSUM_CMD_LIST_SIZE    20

typedef enum {
    FAP4KE_PKT_LOOKUP_MISS,
    FAP4KE_PKT_LOOKUP_HIT,
    FAP4KE_PKT_LOOKUP_BUSY,
    FAP4KE_PKT_LOOKUP_MAX
} fap4kePkt_lookup_t;

typedef enum {
    FAP4KE_PKT_PHY_ENET=0,
    FAP4KE_PKT_PHY_XTM,
    FAP4KE_PKT_PHY_MAX
} fap4kePkt_phy_t;

typedef struct {
    uint8  macDa[ETH_ALEN];
    uint8  macSa[ETH_ALEN];
    uint16 etherType;
} __attribute__((packed)) fap4kePkt_ethHeader_t;

typedef struct {
    uint32 brcmTag;
    uint16 etherType;
} __attribute__((packed)) fap4kePkt_bcmHeader_t;

typedef struct {
    uint16 tci;
    uint16 etherType;
} __attribute__((packed)) fap4kePkt_vlanHeader_t;

typedef uint16 fap4kePkt_pppType_t;

typedef struct {
    struct {
        uint8  ver  : 4;
        uint8  type : 4;
    };
    uint8  code;
    uint16 sessionId;
    uint16 length;
    fap4kePkt_pppType_t pppType;
} __attribute__((packed)) fap4kePkt_pppoeHeader_t;

typedef union {
    struct {
        union {
            struct {
                uint8 version:4;
                uint8 ihl:4;
            };
            uint8 version_ihl;
        };
        uint8  tos;
        uint16 totalLength;
        uint16 id;
        uint16 fragOffset;
#define FLAGS_CE     0x8000 /* Flag: "Congestion" */
#define FLAGS_DF     0x4000 /* Flag: "Don't Fragment" */
#define FLAGS_MF     0x2000 /* Flag: "More Fragments" */
#define OFFSET_MASK  0x1FFF /* "Fragment Offset" part */
        uint8  ttl;
        uint8  protocol;
        uint16 csum;
        uint32 ipSa;
        uint32 ipDa;
        /* options... */
    } __attribute__((packed));
    uint32 u32[5];
} fap4kePkt_ipv4Header_t;

#if defined(CC_FAP4KE_PKT_IPV6_SUPPORT)
typedef union {
    uint8  u8[16];
    uint16 u16[8];
    uint32 u32[4];
} fap4kePkt_ipv6Address_t;

typedef union {
    struct {
        uint8 version:4, priority:4;
        uint8 flowLabel[3];
        uint16 payloadLen;
        uint8 nextHeader;
        uint8 hopLimit;
        fap4kePkt_ipv6Address_t ipSa;
        fap4kePkt_ipv6Address_t ipDa;
    } __attribute__((packed));
    uint32 u32[10];
} fap4kePkt_ipv6Header_t;

typedef struct {
    union {
        struct {
            uint8 next_hdr;
            uint8 hdr_len;
            uint16 u16;
        };
        uint32    word0;
    };
    uint32 word1;
} fap4kePkt_ipv6ExtHeader_t;
#endif /* defined(CC_FAP4KE_PKT_IPV6_SUPPORT) */

typedef union {
    fap4kePkt_ipv4Header_t v4;
#if defined(CC_FAP4KE_PKT_IPV6_SUPPORT)
    fap4kePkt_ipv6Header_t v6;
#endif
} fap4kePkt_ipHeader_t;

#define FAP4KE_TCP_RST_SYN_FIN_MASK 0x07

typedef struct {
    uint16 sPort;
    uint16 dPort;
    uint32 seq;        /* word1 */
    uint32 ack_seq;    /* word2 */
    struct {
        uint8 doff : 4;
        uint8 res1 : 4;
    };
    union {
        struct {
            uint8 cwr : 1;
            uint8 ece : 1;
            uint8 urg : 1;
            uint8 ack : 1;
            uint8 psh : 1;
            uint8 rst : 1;
            uint8 syn : 1;
            uint8 fin : 1;
        };
        uint8 flags;
    };
    uint16 window;
    uint16 csum;
    uint16 urg_ptr;
} __attribute__((packed)) fap4kePkt_tcpHeader_t;

typedef struct {
    uint16 sPort;
    uint16 dPort;
    uint16 length;
    uint16 csum;
} __attribute__((packed)) fap4kePkt_udpHeader_t;

typedef union {
    struct {
        uint16 ip;
        uint16 tu;
    };
    uint32 u32;
} __attribute__((packed)) fap4kePkt_icsum_t;

typedef struct {
    union {
#if defined(CC_FAP4KE_PKT_IPV6_SUPPORT)
        struct {
            fap4kePkt_ipv6Address_t ipSa6;
            fap4kePkt_ipv6Address_t ipDa6;
        };
#endif
        struct {
            uint32 ipSa4;
            uint32 ipDa4;
        };
    };
    union {
        struct {
            uint16 sPort;  /* TCP/UDP source port */
            uint16 dPort;  /* TCP/UDP dest port */
        };
        uint32 l4Ports;
    } __attribute__((packed));
    struct {
        uint32 isRouted  : 1;
        uint32 mangleTos : 1;
        uint32 isIPv6    : 1;
        uint32 reserved  : 29;
    } flags;
    fap4kePkt_icsum_t icsum;
} fap4kePkt_ipTuple_t;

typedef union {
    struct {
        uint8 phy;
        uint8 channel;
        uint8 queue;
        uint8 protocol;
    } __attribute__((packed));
    uint32 u32;
} fap4kePkt_key_t;

/* Defines the key passed on Tx for packets forwarded directly by the FAP */
typedef union {
    struct {
        int16 txAdjust;
        uint16 channel;
    };
    uint32 u32;
} __attribute__((packed)) fap4kePkt_fapTxKey_t;

typedef struct {
    fap4kePkt_key_t source;
    fap4kePkt_key_t dest;
    fap4kePkt_ipTuple_t ipTuple;
    int32 txAdjust;
} fap4kePkt_flowInfo_t;

typedef struct {
    uint32 hits;
    uint32 bytes;
} fap4kePkt_flowStats_t;

typedef struct fap4kePkt_flow {
    struct fap4kePkt_flow *next;

    struct {
        union {
            struct {
                uint8 isActive  : 1;
                uint8 reserved  : 7;
            };
            uint8 u8;
        } flags;
        uint8 hashIx;
        uint16 flowId;
    } __attribute__((packed));

    fap4kePkt_flowInfo_t info;

    fap4kePkt_flowStats_t stats;
} fap4kePkt_flow_t;

/* Special FLOWID signify an invalid flow */
#define FAP4KE_PKT_INVALID_FLOWID   ( (fap4kePkt_flowId_t)(~0) )

typedef uint16 fap4kePkt_flowId_t;

//typedef uint8 fap4kePkt_cmdList_t[FAP4KE_PKT_CMD_LIST_SIZE];

typedef struct {
    uint8 cmdList[FAP4KE_PKT_CMD_LIST_SIZE];
#if defined(CC_FAP4KE_PKT_HW_ICSUM)
    uint8 checksum1[FAP4KE_PKT_CSUM_CMD_LIST_SIZE];
    uint8 checksum2[FAP4KE_PKT_CSUM_CMD_LIST_SIZE];
#endif
    fap4kePkt_flowStats_t stats;
} fap4kePkt_shared_t;

/*
 * Mapped to PSM
 */
typedef struct {
    fap4kePkt_flowInfo_t flowInfoPool[FAP4KE_PKT_MAX_FLOWS];
    fap4kePkt_shared_t shared[FAP4KE_PKT_MAX_FLOWS];
    uint8 headerPool[FAP4KE_PKT_MAX_HEADERS][FAP4KE_PKT_HEADER_SIZE];
} fap4kePkt_tables_t;

#define pktTables4ke p4kePsmGbl->packet.tables

/*
 * Mapped to DSPRAM
 */
typedef struct {
    uint32 flowCount;
    fap4kePkt_flow_t flowPool[FAP4KE_PKT_MAX_FLOWS];
    fap4kePkt_flow_t *hashTable[FAP4KE_PKT_HASH_TABLE_SIZE];
} fap4kePkt_runtime_t;

#define pktRuntime4ke p4keDspramGbl->packet.runtime

#if !defined(CONFIG_BCM_PKTDMA)
typedef struct {
    union {
        struct
        {
            uint8 *packet_p;
            uint16 phy;        /* Rx */
            uint16 headerType; /* Rx */
        } rx;
        struct
        {
            int32 txAdjust;
            uint16 lookup;     /* Tx */
            uint16 queue;      /* Tx */
        } tx;
    };
    uint16 channel;
    uint16 length;
    uint32 count;
} __attribute__((packed)) fap4kePkt_packetInfo_t;
#else
typedef struct {
    uint32 length;
    uint8 *pBuf;
    union {
        struct {
            uint32 portId;
            uint32 dmaFlag;
        } rx;
        struct {
            fap4kePkt_lookup_t lookup;
            fap4kePkt_flow_t *flow_p;
        } tx;
    };
} fap4kePkt_packetInfo_t;
#endif

void fap4kePktTest_runTests(void);

void fap4kePkt_init(void);
fapRet fap4kePkt_activate(fap4kePkt_flowId_t flowId);
fapRet fap4kePkt_deactivate(fap4kePkt_flowId_t flowId);
fapRet fap4kePkt_printFlow(fap4kePkt_flowId_t flowId);

#endif /* __FAP4KE_PACKET_H_INCLUDED__ */
