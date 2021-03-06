/*
**  tc3162_atm_ioc.h,  version:1.4  2005/May/25,  Sam Hung/Billion
**  1.Add new definition supoprt UDP checksum 
**  2.fix some test packet content
*
**  tc3162_atm_ioc.h,  version:1.3.1,  2005/Feb/04,  Sam Hung/Billion
**  1.Add new definition FIXIP_2684R_LLC_VALID and FIXIP_2684R_VC_VALID
**  2.Add rfc2684r_llc_icmp_pattrern and rfc2684r_vc_icmp_pattern
**
**  tc3162_atm_ioc.h,  version:1.3,  2005/Feb/02,  Sam Hung/Billion
**  1.Add pvcmap_t members uint8_t src_ip[IP_ADDR_SIZE] and uint8_t dst_ip[IP_ADDR_SIZE]
**    to provide IP information for scanpvc 
**  2.Add new definition FIXIP_2684B_LLC_VALID and FIXIP_2684B_VC_VALID
**
**  tc3162_atm_ioc.h,  version:1.2,  2005/Feb/01,  Sam Hung/Billion
**  1.Change the scanpvc packet type definition from unsigned integer to bit mask
**    for support determine multi-protocol in one pvc 
**  2.Change pvcmap_t member result type from uint8_t to uint16_t for enough bit mask space
**  3.Add new definition for OAM packet type,mode,and function
**
**  tc3162_atm_ioc.h,  version:1.1,  2005/Jan/29,  Sam Hung/Billion
**  Specify data structure for tc3162 sar driver ioctl function
*/

#define RFC2684B_LLC_HEADER_LEN		10
#define RFC2684B_VC_HEADER_LEN          2
#define ETH_SRC_MAC_OFFSET              6
#define MAC_ADDR_SIZE                   6
#define BOOTP_CLI_HWADR_OFFSET          70
#define BOOTP_CLI_ID_HWADR_OFFSET       288
#define IP_OFFSET_HEADER_START          14
#define IP_HEADER_SIZE                  20
#define ETH_UDP_OFFSET_CHECKSUM         (IP_OFFSET_HEADER_START + IP_HEADER_SIZE + UDP_HEADER_CHECKSUM)
#define UDP_HEADER_CHECKSUM             6
#define SIZE_DHCPC_LLC_2684_TESTPKT     410
#define SIZE_DHCPC_VC_2684_TESTPKT      402
#define IP_OFFSET_CHECKSUM              10
#define ETH_IP_OFFSET_CHECKSUM          (IP_OFFSET_HEADER_START + IP_OFFSET_CHECKSUM)
#define IP_HEADER_HALF_WORDS            10
#define ICMP_OFFSET_HEADER_START        IP_HEADER_SIZE
#define SIZE_ICMP_TESTPKT_HALFWORDS     14
#define MAC_PROTOCOL_OFFSET             12
#define UDP_DST_PORT_OFFSET             36
#define RFC2684R_LLC_HEADER_LEN         8
#define IP_HEADER_PROTOCOL_OFFSET       9
#define IP_ICMP_TYPE_OFFSET             20

#if 0
#define RFC2684R_VC_HEADER_LEN		0
#define IP_ADDR_SIZE			4
//#define IP_OFFSET_CHECKSUM		(IP_OFFSET_HEADER_START + 10)
#define ICMP_OFFSET_CHECKSUM		(ICMP_OFFSET_HEADER_START + 2)

#define ARP_PROTOCOL_OFFSET		12
#define ARP_SRC_MAC_OFFSET		22
#define ARP_SRC_IP_OFFSET		28
#define ARP_DST_IP_OFFSET		38
#define ICMP_SRC_IP_OFFSET		12
#define ICMP_DST_IP_OFFSET		16

#define UDP_HEADER_CHECKSUM		6

#define MAX_SCANPVC			16

#if 0
#define PROTOCOL_UNKNOWN		0
#define OAM_F5_VALID			1
#define RFC2684B_LLC_VALID		2
#define RFC2684B_VC_VALID		3
#define DHCPC_LLC_VALID			4
#define DHCPC_VC_VALID			5
#define PPPOE_LLC_VALID			6
#define PPPOE_VC_VALID			7
#define PPPOA_LLC_VALID			8
#define PPPOA_VC_VALID			9
#endif

#define PROTOCOL_UNKNOWN		0
#define OAM_F5_VALID			(1 << 0)
#define RFC2684B_LLC_VALID		(1 << 1)
#define RFC2684B_VC_VALID		(1 << 2)
#define DHCPC_LLC_VALID			(1 << 3)
#define DHCPC_VC_VALID			(1 << 4)
#define PPPOE_LLC_VALID			(1 << 5)
#define PPPOE_VC_VALID			(1 << 6)
#define PPPOA_LLC_VALID			(1 << 7)
#define PPPOA_VC_VALID			(1 << 8)
#define FIXIP_2684B_LLC_VALID		(1 << 9)
#define FIXIP_2684B_VC_VALID		(1 << 10)
#define FIXIP_2684R_LLC_VALID		(1 << 11)
#define FIXIP_2684R_VC_VALID		(1 << 12)

#define ATM_AAL5_MODE			0	
#define	ATM_SCANPVC_MODE		1

#define SIZE_PPPOE_LLC_2684_TESTPKT 	70
#define SIZE_PPPOE_VC_2684_TESTPKT	62
#define SIZE_PPPOA_LLC_TESTPKT 		16
#define SIZE_PPPOA_VC_TESTPKT 		12
#define SIZE_RFC2684B_LLC_ARP_TESTPKT   70
#define SIZE_RFC2684B_VC_ARP_TESTPKT	62
#define SIZE_RFC2684R_LLC_ICMP_TESTPKT	56
#define SIZE_RFC2684R_VC_ICMP_TESTPKT	48



/* Definition of OAM packet */
#define OAM_F4_TYPE			0
#define OAM_F5_TYPE			1

#define OAM_SEG2SEG			0
#define OAM_END2END			1

#define OAM_FUNC_AIS			0
#define OAM_FUNC_RDI			1
#define OAM_FUNC_LOOPBACK		2
#define OAM_FUNC_CC			3
/* End of Definetion of OAM packet */

typedef struct oamdatareq_s {
/*	
        unsigned char  vpi;
        unsigned short vci;
*/
        int  vpi;
        int  vci;
        unsigned char  f5;
        unsigned char  endtoEnd;
        //unsigned char  funcType;
        int  funcType;
}oamdatareq_t;
/* vpi   : the vpi number
   vci   : the vci number
   f5    : 1 for OAM F5, others for OAM F4
   endtoEnd : 1 for end to end, others for segament
   Functype : OAM_AIS 0x0, OAM_RDI 0x1, OAM_CC 0x4, OAM_LOOPBACK 0x8
*/


typedef struct pvcmap_s{
			uint8_t vpi;
                        uint16_t vci;
			uint16_t result;
        }pvcmap_t;



typedef struct pvc_table_list_s{
				uint8_t mac_addr[MAC_ADDR_SIZE];
				uint8_t src_ip[IP_ADDR_SIZE];
				uint8_t dst_ip[IP_ADDR_SIZE];
				uint8_t pvc_count;
				pvcmap_t pvc_table[MAX_SCANPVC];
	}pvc_table_list_t;

#endif
#ifdef __KERNEL__ 
//
UINT8 dhcpclient_2684_llc_pattern[410]={0xaa,0xaa,0x03,0x00,0x80,0xc2,0x00,0x07,
				0x00,0x00,0xff,0xff,0xff,0xff,0xff,0xff,
	    		 	0xee,0xee,0xee,0xee,0xee,0xee,0x08,0x00,
				0x45,0x00,0x01,0x82,0x00,0x01,0x00,0x00,
                                0x80,0x11,0x00,0x00,0x00,0x00,0x00,0x00,
				0xff,0xff,0xff,0xff,0x00,0x44,0x00,0x43,
				0x01,0x6e,0x00,0x00,0x01,0x01,0x06,0x00,
				0x00,0x23,0x10,0x01,0x00,0x00,0x00,0x00,
	                        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                                0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0xee,0xee,0xee,0xee,0xee,0xee,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x63,0x82,0x53,0x63,0x35,0x01,0x01,0x3d,
				0x07,0x01,0xee,0xee,0xee,0xee,0xee,0xee,
				0x3c,0x0b,0x75,0x64,0x68,0x63,0x70,0x20,
				0x30,0x2e,0x39,0x2e,0x37,0x37,0x07,0x01,
				0x03,0x06,0x0c,0x0f,0x1c,0x2c,0xff,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00};
//
UINT8 dhcpclient_2684_vc_pattern[402]={0x00,0x00,0xff,0xff,0xff,0xff,0xff,0xff,
	    		 	0xee,0xee,0xee,0xee,0xee,0xee,0x08,0x00,
				0x45,0x00,0x01,0x82,0x00,0x01,0x00,0x00,
                                0x80,0x11,0x00,0x00,0x00,0x00,0x00,0x00,
				0xff,0xff,0xff,0xff,0x00,0x44,0x00,0x43,
				0x01,0x6e,0x00,0x00,0x01,0x01,0x06,0x00,
				0x00,0x33,0x10,0x01,0x00,0x00,0x00,0x00,
	                        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                                0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0xee,0xee,0xee,0xee,0xee,0xee,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x63,0x82,0x53,0x63,0x35,0x01,0x01,0x3d,
				0x07,0x01,0xee,0xee,0xee,0xee,0xee,0xee,
				0x3c,0x0b,0x75,0x64,0x68,0x63,0x70,0x20,
				0x30,0x2e,0x39,0x2e,0x37,0x37,0x07,0x01,
				0x03,0x06,0x0c,0x0f,0x1c,0x2c,0xff,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00};
//
#if 0
#ifdef _SEND_DHCPC_RELEASE_
UINT8 dhcpclient_release_2684_llc_pattern[410]={0xaa,0xaa,0x03,0x00,0x80,0xc2,0x00,0x07,
				0x00,0x00,0xff,0xff,0xff,0xff,0xff,0xff,
	    		 	0xee,0xee,0xee,0xee,0xee,0xee,0x08,0x00,
				0x45,0x00,0x01,0x82,0x00,0x01,0x00,0x00,
                                0x80,0x11,0x00,0x00,0x00,0x00,0x00,0x00,
				0xff,0xff,0xff,0xff,0x00,0x44,0x00,0x43,
				0x01,0x6e,0x00,0x00,0x01,0x01,0x06,0x00,
				0x00,0x23,0x10,0x01,0x00,0x00,0x80,0x00,
	                        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                                0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0xee,0xee,0xee,0xee,0xee,0xee,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x63,0x82,0x53,0x63,0x35,0x01,0x07,0x3d,
				0x07,0x01,0xee,0xee,0xee,0xee,0xee,0xee,
				0x3c,0x0b,0x75,0x64,0x68,0x63,0x70,0x20,
				0x30,0x2e,0x39,0x2e,0x37,0x37,0x07,0x01,
				0x03,0x06,0x0c,0x0f,0x1c,0x2c,0xff,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00};
//
UINT8 dhcpclient_release_2684_vc_pattern[402]={0x00,0x00,0xff,0xff,0xff,0xff,0xff,0xff,
	    		 	0xee,0xee,0xee,0xee,0xee,0xee,0x08,0x00,
				0x45,0x00,0x01,0x82,0x00,0x01,0x00,0x00,
                                0x80,0x11,0x00,0x00,0x00,0x00,0x00,0x00,
				0xff,0xff,0xff,0xff,0x00,0x44,0x00,0x43,
				0x01,0x6e,0x00,0x00,0x01,0x01,0x06,0x00,
				0x00,0x33,0x10,0x01,0x00,0x00,0x80,0x00,
	                        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                                0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0xee,0xee,0xee,0xee,0xee,0xee,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x63,0x82,0x53,0x63,0x35,0x01,0x07,0x3d,
				0x07,0x01,0xee,0xee,0xee,0xee,0xee,0xee,
				0x3c,0x0b,0x75,0x64,0x68,0x63,0x70,0x20,
				0x30,0x2e,0x39,0x2e,0x37,0x37,0x07,0x01,
				0x03,0x06,0x0c,0x0f,0x1c,0x2c,0xff,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00};
#endif
#endif
#if 0 
unsigned char pppoe_2684_llc_pattern[70]={0xaa,0xaa,0x03,0x00,0x80,0xc2,0x00,0x07,
                                0x00,0x00,0xff,0xff,0xff,0xff,0xff,0xff,
                                0xee,0xee,0xee,0xee,0xee,0xee,0x88,0x63,
                                0x11,0x09,0x00,0x00,0x00,0x0f,0x01,0x01,
                                0x00,0x00,0x01,0x03,0x00,0x07,0x00,0x04,
                                0xed,0x00,0x1c,0x01,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                                0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00};
//
unsigned char pppoe_2684_vc_pattern[62]={0x00,0x00,0xff,0xff,0xff,0xff,0xff,0xff,
                                0xee,0xee,0xee,0xee,0xee,0xee,0x88,0x63,
                                0x11,0x09,0x00,0x00,0x00,0x0f,0x01,0x01,
                                0x00,0x00,0x01,0x03,0x00,0x07,0x00,0x04,
                                0xed,0x00,0x1c,0x01,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                                0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00};
#endif

UINT8 pppoe_2684_llc_pattern[70]={0xaa,0xaa,0x03,0x00,0x80,0xc2,0x00,0x07,
                                0x00,0x00,0xff,0xff,0xff,0xff,0xff,0xff,
                                0xee,0xee,0xee,0xee,0xee,0xee,0x88,0x63,
                                0x11,0x09,0x00,0x00,0x00,0x04,0x01,0x01,
                                0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                                0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                                0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00};
//
UINT8 pppoe_2684_vc_pattern[62]={0x00,0x00,0xff,0xff,0xff,0xff,0xff,0xff,
                                0xee,0xee,0xee,0xee,0xee,0xee,0x88,0x63,
                                0x11,0x09,0x00,0x00,0x00,0x00,0x01,0x01,
                                0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                                0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                                0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00};

//
UINT8 pppoa_llc_pattern[16]={0xfe,0xfe,0x03,0xcf,0xc0,0x21,0x01,0x01,
				0x00,0x0a,0x05,0x06,0x24,0x8e,0x65,0x7a};
//
UINT8 pppoa_vc_pattern[12]={0xc0,0x21,0x01,0x01,0x00,0x0a,0x05,0x06,
				0x24,0x8e,0x65,0x7a};
//
#if 0
unsigned char rfc2684b_llc_arp_pattern[70]={0xaa,0xaa,0x03,0x00,0x80,0xc2,0x00,0x07,
                                0x00,0x00,0xff,0xff,0xff,0xff,0xff,0xff,
                                0xee,0xee,0xee,0xee,0xee,0xee,0x08,0x06,
                                0x00,0x01,0x08,0x00,0x06,0x04,0x00,0x01,
                                0xee,0xee,0xee,0xee,0xee,0xee,0xaa,0xaa,
                                0xaa,0xaa,0x00,0x00,0x00,0x00,0x00,0x00,
				0xbb,0xbb,0xbb,0xbb,0x00,0x00,0x00,0x00,
                                0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00};
//
unsigned char rfc2684b_vc_arp_pattern[62]={0x00,0x00,0xff,0xff,0xff,0xff,0xff,0xff,
                                0xee,0xee,0xee,0xee,0xee,0xee,0x08,0x06,
                                0x00,0x01,0x08,0x00,0x06,0x04,0x00,0x01,
                                0xee,0xee,0xee,0xee,0xee,0xee,0xaa,0xaa,
                                0xaa,0xaa,0x00,0x00,0x00,0x00,0x00,0x00,
				0xbb,0xbb,0xbb,0xbb,0x00,0x00,0x00,0x00,
                                0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00};
//
unsigned char rfc2684r_llc_icmp_pattern[56]={0xaa,0xaa,0x03,0x00,0x00,0x00,0x08,0x00,
				0x45,0x00,0x00,0x30,0x00,0x00,0x40,0x00,
				0x40,0x01,0x00,0x00,0xaa,0xaa,0xaa,0xaa,
				0xbb,0xbb,0xbb,0xbb,0x08,0x00,0x00,0x00,
				0x00,0x01,0x00,0x01,0x30,0x31,0x32,0x33,
				0x34,0x35,0x36,0x37,0x38,0x39,0x30,0x31,
				0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39
				};
//
/*unsigned char rfc2684r_vc_icmp_pattern[48]={0x45,0x00,0x00,0x30,0x00,0x00,0x40,0x00,
				0x40,0x01,0xcs,0xum,0xaa,0xaa,0xaa,0xaa,
				0xbb,0xbb,0xbb,0xbb,0x08,0x00,0xcs,0xum,
				0x00,0x01,0x00,0x01,0x30,0x31,0x32,0x33,
				0x34,0x35,0x36,0x37,0x38,0x39,0x30,0x31,
				0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39
				};
*/
//
unsigned char rfc2684r_vc_icmp_pattern[48]={0x45,0x00,0x00,0x30,0x00,0x00,0x40,0x00,
				0x40,0x01,0x00,0x00,0xaa,0xaa,0xaa,0xaa,
				0xbb,0xbb,0xbb,0xbb,0x08,0x00,0x00,0x00,
				0x00,0x01,0x00,0x01,0x30,0x31,0x32,0x33,
				0x34,0x35,0x36,0x37,0x38,0x39,0x30,0x31,
				0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39
				};

#endif


/* End of Sam add */
#endif // __KERNEL__


