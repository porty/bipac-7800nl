/*
<:copyright-broadcom 
 
 Copyright (c) 2008 Broadcom Corporation 
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
#ifndef _BCMMII_EXPORT_H_
#define _BCMMII_EXPORT_H_

void ethsw_switch_manage_port_power_mode(int portnumber, int power_mode);
int ethsw_switch_get_port_power_mode(int portnumber);
int ethsw_switch_manage_ports_leds(int led_mode);

#endif /* _BCMMII_EXPORT_H_ */
