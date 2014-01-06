#include <linux/version.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/interrupt.h>
#include <linux/ioport.h>
#include <linux/version.h>
#include <linux/slab.h>
#include <linux/init.h>
#include <linux/delay.h>
#include <linux/netdevice.h>
#include <linux/etherdevice.h>
#include <linux/skbuff.h>
#include <linux/rtnetlink.h>
#include <linux/ethtool.h>
#include <linux/if_arp.h>
#include <linux/ppp_channel.h>
#include <linux/ppp_defs.h>
#include <linux/if_ppp.h>
#include <linux/atm.h>
#include <linux/atmdev.h>
#include <linux/atmppp.h>
#include <linux/blog.h>
#include <linux/proc_fs.h>
#include <linux/string.h>
#include <bcmtypes.h>
#include <bcm_map_part.h>
#include <bcm_intr.h>
#include <board.h>
#include "bcmnet.h"
#include "bcmxtmcfg.h"
#include "bcmxtmrt.h"
#include <asm/io.h>
#include <asm/uaccess.h>
#include <linux/nbuff.h>
#include "bcmxtmrtimpl.h"
#include "PacketFormat.h"
#include "billion_autoscan_api.h"

extern int bcmxtmrt_xmit(pNBuff_t pNBuff, struct net_device *dev);

#define SCANPVC_DBG 	1
int scanpvc_needip_flag = 0;
int fill_the_test_pattern_done = 0;

void setNet16(UINT8 *address, UINT16 data)
{
    *(UINT8 *) address      = (UINT8)(data >> 8);
    *(UINT8 *)(address + 1) = (UINT8) data;
}

UINT16 getNet16(UINT8 *address)
{
    return (((UINT16)(*(UINT8 *)address)) << 8) | (UINT16)(*(UINT8 *)(address + 1));
}

UINT16 udp_sum_calc(UINT16 len_udp, UINT8 buff[])
{
    UINT8 src_addr[4]={0x0000,0x0000,0x00,0x00};
    UINT8 dest_addr[4]={0xff,0xff,0xff,0xff};
    UINT16 prot_udp=17;
    UINT16 word16;
    UINT32 sum;
    int i;
    sum=0;
    for ( i=0; i<len_udp; i=i+2 ){
             word16 =((buff[i]<<8)&0xFF00)+(buff[i+1]&0xFF);
             sum = sum + (unsigned long)word16;
    }
    for (i=0;i<4;i=i+2){
             word16 =((src_addr[i]<<8)&0xFF00)+(src_addr[i+1]&0xFF);
             sum=sum+word16;
    }
    for (i=0;i<4;i=i+2){
             word16 =((dest_addr[i]<<8)&0xFF00)+(dest_addr[i+1]&0xFF);
             sum=sum+word16;
    }
    sum = sum + prot_udp + len_udp;
    while (sum>>16)
             sum = (sum & 0xFFFF)+(sum >> 16);
    sum = ~sum;
    return ((uint16) sum);
}

UINT16 calculateIPheaderChecksum(uint8 mode, uint8 *rawPacketPtr)
{
    UINT16* hdrPtr = NULL;
    UINT16   length = 0;
    UINT32  checksum = 0;
    if (mode == 1)
    {  /* IP Header checksum */
        hdrPtr = (UINT16 *)&rawPacketPtr[0];
        length = IP_HEADER_HALF_WORDS;
    }
    else if(mode == 2)/* ICMP Header checksum */
    {
        hdrPtr = (UINT16 *)&rawPacketPtr[ICMP_OFFSET_HEADER_START];
        length = SIZE_ICMP_TESTPKT_HALFWORDS;
    }
    for (length, checksum = 0; length != 0; length--, hdrPtr++)
    {
        checksum += (UINT32)getNet16((UINT8 *)hdrPtr);
    }
    /* use the carries to compute the 1's complement sum as per the RFC.    */
    checksum  = (checksum >> 16) + (checksum & 0xFFFF);
    checksum += (checksum >> 16);
    checksum  = (checksum >> 16) + (checksum & 0xFFFF);
    checksum += (checksum >> 16);
    /* return the inverted */
    return (UINT16)~checksum;
}

void fill_the_test_pattern(unsigned char* mac_addr_p)
{
        int j;
        for(j=0;j<MAC_ADDR_SIZE;j++)
        {
             pppoe_2684_llc_pattern[ RFC2684B_LLC_HEADER_LEN + ETH_SRC_MAC_OFFSET + j ]=*mac_addr_p;
             pppoe_2684_vc_pattern[ RFC2684B_VC_HEADER_LEN + ETH_SRC_MAC_OFFSET + j ]=*mac_addr_p;


             dhcpclient_2684_llc_pattern[ RFC2684B_LLC_HEADER_LEN + ETH_SRC_MAC_OFFSET + j ]=*mac_addr_p;
             dhcpclient_2684_llc_pattern[ RFC2684B_LLC_HEADER_LEN + BOOTP_CLI_HWADR_OFFSET + j ]=*mac_addr_p;
             dhcpclient_2684_llc_pattern[ RFC2684B_LLC_HEADER_LEN + BOOTP_CLI_ID_HWADR_OFFSET + j ]=*mac_addr_p;

             dhcpclient_2684_vc_pattern[ RFC2684B_VC_HEADER_LEN + ETH_SRC_MAC_OFFSET + j ]=*mac_addr_p;
             dhcpclient_2684_vc_pattern[ RFC2684B_VC_HEADER_LEN + BOOTP_CLI_HWADR_OFFSET + j ]=*mac_addr_p;
             dhcpclient_2684_vc_pattern[ RFC2684B_VC_HEADER_LEN + BOOTP_CLI_ID_HWADR_OFFSET + j ]=*mac_addr_p;
             mac_addr_p++;

        }
        setNet16(&dhcpclient_2684_llc_pattern[RFC2684B_LLC_HEADER_LEN + ETH_UDP_OFFSET_CHECKSUM], \
        udp_sum_calc( (SIZE_DHCPC_LLC_2684_TESTPKT - RFC2684B_LLC_HEADER_LEN - IP_OFFSET_HEADER_START - IP_HEADER_SIZE), \
        &dhcpclient_2684_llc_pattern[RFC2684B_LLC_HEADER_LEN + IP_OFFSET_HEADER_START + IP_HEADER_SIZE]));

        setNet16(&dhcpclient_2684_vc_pattern[RFC2684B_VC_HEADER_LEN + ETH_UDP_OFFSET_CHECKSUM], \
        udp_sum_calc( (SIZE_DHCPC_VC_2684_TESTPKT - RFC2684B_VC_HEADER_LEN - IP_OFFSET_HEADER_START - IP_HEADER_SIZE), \
        &dhcpclient_2684_vc_pattern[RFC2684B_VC_HEADER_LEN + IP_OFFSET_HEADER_START + IP_HEADER_SIZE]));

        setNet16(&dhcpclient_2684_llc_pattern[RFC2684B_LLC_HEADER_LEN + ETH_IP_OFFSET_CHECKSUM],calculateIPheaderChecksum(1,&dhcpclient_2684_llc_pattern[RFC2684B_LLC_HEADER_LEN + IP_OFFSET_HEADER_START]));


        setNet16(&dhcpclient_2684_vc_pattern[RFC2684B_VC_HEADER_LEN + ETH_IP_OFFSET_CHECKSUM],calculateIPheaderChecksum(1,&dhcpclient_2684_vc_pattern[RFC2684B_VC_HEADER_LEN + IP_OFFSET_HEADER_START]));
        fill_the_test_pattern_done = 1;
}

BCMXTM_STATUS AutoScanTestSend(int PacketType, PBCMXTMRT_DEV_CONTEXT pDevCtx)
{
        BCMXTM_STATUS baStatus = XTMSTS_SUCCESS;
        struct sk_buff* skb_test_p = NULL;
        switch(PacketType)
        {
                case PPPOE_2684_LLC      :
                                         skb_test_p = dev_alloc_skb(BUF_LEN);
                                         if(skb_test_p){
                                            skb_test_p -> len = sizeof(pppoe_2684_llc_pattern);
                                            memcpy(skb_test_p->data ,pppoe_2684_llc_pattern,sizeof(pppoe_2684_llc_pattern));
                                         }
                                         break;

                case PPPOE_2684_VC       :
                                         skb_test_p = dev_alloc_skb(BUF_LEN);
                                         if(skb_test_p){
                                            skb_test_p -> len = sizeof(pppoe_2684_vc_pattern);
                                            memcpy(skb_test_p->data,pppoe_2684_vc_pattern,sizeof(pppoe_2684_vc_pattern));
                                         }
                                         break;

                case PPPOA_LLC           :
                                         skb_test_p = dev_alloc_skb(BUF_LEN);
                                         if(skb_test_p){
                                            skb_test_p -> len = sizeof(pppoa_llc_pattern);
                                            memcpy(skb_test_p->data,pppoa_llc_pattern,sizeof(pppoa_llc_pattern));
                                         }
                                         break;

                case PPPOA_VC            :
                                         skb_test_p = dev_alloc_skb(BUF_LEN);
                                         if(skb_test_p){
                                            skb_test_p -> len = sizeof(pppoa_vc_pattern);
                                            memcpy(skb_test_p->data,pppoa_vc_pattern,sizeof(pppoa_vc_pattern));
                                         }
                                         break;

                case DHCPCCLIENT_2684_LLC:
                                         skb_test_p = dev_alloc_skb(BUF_LEN);
                                         if(skb_test_p){
                                            skb_test_p -> len = sizeof(dhcpclient_2684_llc_pattern);
                                            memcpy(skb_test_p->data,dhcpclient_2684_llc_pattern,sizeof(dhcpclient_2684_llc_pattern));
                                         }
                                         break;

                case DHCPCCLIENT_2684_VC :
                                         skb_test_p = dev_alloc_skb(BUF_LEN);
                                         if(skb_test_p){
                                            skb_test_p -> len = sizeof(dhcpclient_2684_vc_pattern);
                                            memcpy(skb_test_p->data,dhcpclient_2684_vc_pattern,sizeof(dhcpclient_2684_vc_pattern));
                                         }
                                         break;

                default                  :
                                         printk("Error !! PacketType not found\n");
                                         if (skb_test_p != NULL)
                                                nbuff_flushfree(skb_test_p);
                                         return XTMSTS_ERROR;
        }
        skb_test_p->mark |= AUTOSCANMARK;
        bcmxtmrt_xmit( SKBUFF_2_PNBUFF(skb_test_p), pDevCtx->pDev );
        return baStatus;
}

UINT32 DoSendAutoScanPkt(PBCMXTMRT_DEV_CONTEXT  pDevCtx , PXTMCFGDRV_AUTOSCAN_PVC pParm )
{
        BCMXTM_STATUS bxStatus = XTMSTS_ERROR;
        UINT32 repetition;
        UINT32 PacketType;
        UINT32 sent=0;
        if(!fill_the_test_pattern_done)
                fill_the_test_pattern(pDevCtx->pDev->dev_addr);
        repetition = pParm->repetition;
        for (sent = 0; sent < repetition; sent++)
        {
           for(PacketType = 0; PacketType < PACKET_TYPE_MAX; PacketType++)
           {
                if ((bxStatus = AutoScanTestSend(PacketType,pDevCtx)) != XTMSTS_SUCCESS){
                        printk("send autoscan pkt type %d error !\n",PacketType);
                        continue;
                }
           }
        }
	return bxStatus;
}

UINT32 DoGetAutoScanReport(UINT32* pPotocolType,UINT32* pGlob_PotocolType)
{

	memcpy(pPotocolType,pGlob_PotocolType,PACKET_TYPE_MAX*4);
	return XTMSTS_SUCCESS;
}

void GetAndSetMode(int option, UINT32* mode)
{
        static UINT32 CurMode = 0;
        if(option == GETMODE)
                *mode = CurMode;
        else if(option == SETMODE){
                if(*mode == 0)
                        CurMode = DEFAULTMODE;
                else if(*mode == 1)
                        CurMode = AUTOSCANMODE;
        }
}

void scanpvc_parse_rxpacket( UINT8 * data, UINT32* pbxStatus, PBCMXTMRT_DEV_CONTEXT pDevCtx, UINT32* PotocolType)
{
        UINT8* parse_data_p;
	UINT8* Mac_addr = pDevCtx->pDev->dev_addr;
       // uint16 result = 0;

#if 0
#if SCANPVC_DBG
        unsigned char* testdump_p;
        int dump_idx1;
        testdump_p = parse_data_p = skb ;
#endif
#endif
        parse_data_p = data ;

#if 0
                /* Sam add for debug */
#if SCANPVC_DBG
                for(dump_idx1=0;dump_idx1 < 40;dump_idx1++,testdump_p++)
                printk("%02x ",*testdump_p);
                printk("\n");
#endif
#endif
#if 0
        int i =0;
        for(i=0;i<50;i++){
        printk("%02x ",data[i]);
        }
        printk("\n");
#endif
        if ( *parse_data_p == 0xaa && *(parse_data_p+1) == 0xaa && *(parse_data_p+2) == 0x03)
        {       /* uh... it seems like  rfc2684 llc header */

           if ( *(parse_data_p + 3)== 0x00 && *(parse_data_p + 4) == 0x80 && *(parse_data_p + 5) == 0xc2)
           {
                parse_data_p = data + RFC2684B_LLC_HEADER_LEN;
//printk("1>> %02x-%02x-%02x-%02x-%02x-%02x <<\n",Mac_addr[0],Mac_addr[1],Mac_addr[2],Mac_addr[3],Mac_addr[4],Mac_addr[5]);
//printk("2>> %02x-%02x-%02x-%02x-%02x-%02x <<\n",*parse_data_p,*(parse_data_p+1),*(parse_data_p + 2),*(parse_data_p + 3),*(parse_data_p + 4),*(parse_data_p + 5));

             if ( (*parse_data_p == Mac_addr[0] && *(parse_data_p+1) == Mac_addr[1] &&
                        *(parse_data_p + 2)== Mac_addr[2] && *(parse_data_p + 3)== Mac_addr[3] &&
                        *(parse_data_p + 4)== Mac_addr[4] && *(parse_data_p + 5) == Mac_addr[5]) ||
                  (*parse_data_p == 0xff && *(parse_data_p+1) == 0xff &&
                        *(parse_data_p + 2)== 0xff && *(parse_data_p + 3)== 0xff &&
                        *(parse_data_p + 4)== 0xff && *(parse_data_p + 5) == 0xff ) )
             {
                if (*(parse_data_p + MAC_PROTOCOL_OFFSET) == 0x88 && *(parse_data_p + MAC_PROTOCOL_OFFSET + 1) == 0x63)
                {
#if SCANPVC_DBG
                        printk("2617 Parse to pppoe llc protocol\n");
#endif
                        PotocolType[PPPOE_2684_LLC] = 1;
                        *pbxStatus = XTMSTS_SUCCESS;
                }
                else if (*(parse_data_p + MAC_PROTOCOL_OFFSET) == 0x08 && *(parse_data_p + MAC_PROTOCOL_OFFSET +1) == 0x06)
                {
                        if (scanpvc_needip_flag)
                        {
#if SCANPVC_DBG
                                printk("2624 Parse to fixip 2684B LLC protocol\n");
#endif
                              /*  result = FIXIP_2684B_LLC_VALID;*/
                                /* *pbaStatus = STS_SUCCESS;*/
                        }
                }
                else if (*(parse_data_p + UDP_DST_PORT_OFFSET) == 0x00 && *(parse_data_p + UDP_DST_PORT_OFFSET +1) == 0x44)
                {

#if SCANPVC_DBG
                        printk("2630 Parse to dhcp client llc protocol\n");
#endif
                        PotocolType[DHCPCCLIENT_2684_LLC] = 1;
                        *pbxStatus = XTMSTS_SUCCESS;
                }
                else
                {

#if SCANPVC_DBG
                        //printk("2635 encap is llc but protocol unknown\n");
#endif
                        /*result = RFC2684B_LLC_VALID;*/
                        /* *pbaStatus = STS_SUCCESS;*/
                }
            }
            else if (*(parse_data_p + UDP_DST_PORT_OFFSET) == 0x00 && *(parse_data_p + UDP_DST_PORT_OFFSET +1) == 0x44)
            {
#if SCANPVC_DBG
                        printk("2641 Parse to dhcp client llc protocol\n");
#endif
                        PotocolType[DHCPCCLIENT_2684_LLC] = 1;
                        *pbxStatus = XTMSTS_SUCCESS;
            }
         }
         else if ( *(parse_data_p + 3)== 0x00 && *(parse_data_p + 4) == 0x00 && *(parse_data_p + 5) == 0x00)
         {
                parse_data_p = data + RFC2684R_LLC_HEADER_LEN;
                if ( scanpvc_needip_flag && *(parse_data_p+IP_HEADER_PROTOCOL_OFFSET) == 0x01 && *(parse_data_p+IP_ICMP_TYPE_OFFSET) == 0x00)
                {        /*result = FIXIP_2684R_LLC_VALID;*/
#if SCANPVC_DBG
                        printk("2650 FIXIP_2684R_LLC_VALID\n");
#endif
                        /* *pbaStatus = STS_SUCCESS;*/
                }
         }
        }
        else if ( *parse_data_p == 0x00 && *(parse_data_p+1) == 0x00 )
        {       /* uh... it seems like rfc2684 vc header */
                 parse_data_p = data + RFC2684B_VC_HEADER_LEN;

             if ( (*parse_data_p == Mac_addr[0] && *(parse_data_p+1) == Mac_addr[1] &&
                        *(parse_data_p + 2)== Mac_addr[2] && *(parse_data_p + 3)== Mac_addr[3] &&
                        *(parse_data_p + 4)== Mac_addr[4] && *(parse_data_p + 5) == Mac_addr[5]) ||
                  (*parse_data_p == 0xff && *(parse_data_p+1) == 0xff &&
                    *(parse_data_p + 2)== 0xff && *(parse_data_p + 3)== 0xff &&
                        *(parse_data_p + 4)== 0xff && *(parse_data_p + 5) == 0xff ) )

             {
                if (*(parse_data_p + MAC_PROTOCOL_OFFSET) == 0x88 && *(parse_data_p + MAC_PROTOCOL_OFFSET + 1) == 0x63)
                {
#if SCANPVC_DBG
                        printk("2664 Parse to pppoe vc protocol\n");
#endif
                        PotocolType[PPPOE_2684_VC] = 1;
                        *pbxStatus = XTMSTS_SUCCESS;
                }
                else if (*(parse_data_p + MAC_PROTOCOL_OFFSET) == 0x08 && *(parse_data_p + MAC_PROTOCOL_OFFSET +1) == 0x06)
                {
                        if (scanpvc_needip_flag)
                        {
#if SCANPVC_DBG
                                printk("2671 Parse to fixip 2684B VC protocol\n");
#endif
                                /* *pbaStatus = STS_SUCCESS;*/
                        }
                }
                else if (*(parse_data_p + UDP_DST_PORT_OFFSET) == 0x00 && *(parse_data_p + UDP_DST_PORT_OFFSET +1) == 0x44)
                {
#if SCANPVC_DBG
                        printk("2677 Parse to dhcp client vc protocol\n");
#endif
                        PotocolType[DHCPCCLIENT_2684_VC] = 1;
                        *pbxStatus = XTMSTS_SUCCESS;
                }
                else
                {
#if SCANPVC_DBG
                        printk("2682 encap is vc but protocol unknown\n");
#endif
                        /*result = RFC2684B_VC_VALID;*/
                        /* *pbaStatus = STS_SUCCESS;*/
                }
             }
             else if (*(parse_data_p + UDP_DST_PORT_OFFSET) == 0x00 && *(parse_data_p + UDP_DST_PORT_OFFSET +1) == 0x44)
             {
#if SCANPVC_DBG
                        printk("2688 Parse to dhcp client vc protocol\n");
#endif
                        PotocolType[DHCPCCLIENT_2684_VC] = 1;
                        *pbxStatus = XTMSTS_SUCCESS;
             }
        }

        else if ( *parse_data_p == 0xfe && *(parse_data_p+1) == 0xfe && *(parse_data_p+2) == 0x03 && *(parse_data_p+3) == 0xcf )
        {
#if SCANPVC_DBG
                printk("2695 Surely Its PPPoA LLC header\n");
#endif
                PotocolType[PPPOA_LLC] = 1;
                *pbxStatus = XTMSTS_SUCCESS;
        }

        else if ( *parse_data_p == 0xc0 && *(parse_data_p+1) == 0x21 )
        {
#if SCANPVC_DBG
                printk("2700 Surely Its PPPoA VCC header\n");
#endif
                PotocolType[PPPOA_VC] = 1;
                *pbxStatus = XTMSTS_SUCCESS;
        }
        else if (  *parse_data_p == 0xff && *(parse_data_p+1) == 0x03 && *(parse_data_p +2) == 0xc0 && *(parse_data_p+3) == 0x21 )
        {
#if SCANPVC_DBG
                printk("2706 Surely Its PPPoA VCC header\n");
#endif
                PotocolType[PPPOA_VC] = 1;
                *pbxStatus = XTMSTS_SUCCESS;
        }
        else if ( *parse_data_p == 0x45 && *(parse_data_p+IP_HEADER_PROTOCOL_OFFSET) == 0x01 && *(parse_data_p+IP_ICMP_TYPE_OFFSET) == 0x00)
        {
                if (scanpvc_needip_flag)
                {
                /*result = FIXIP_2684R_VC_VALID;*/
#if SCANPVC_DBG
                printk("2714 FIXIP_2684R_VC_VALID\n");
#endif
                /* *pbaStatus = STS_SUCCESS;*/
                }
        }
        else
        {
		;
        }
#if 0
        if (result > 0)
             fill_scanpvc_ret_table(vc, result);
        dev_kfree_skb(data);
#endif
}

