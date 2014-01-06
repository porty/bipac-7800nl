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
#ifndef _BCMSWACCESS_H_
#define _BCMSWACCESS_H_

void bcmsw_pmdio_rreg(int page, int reg, uint8 *data, int len);
void bcmsw_pmdio_wreg(int page, int reg, uint8 *data, int len);
void get_ext_switch_access_info(int usConfigType, int *bus_type, int *spi_id);
void bcmsw_spi_rreg(int spi_ss, int chip_id, int page, int reg, uint8 *data, int len);
void bcmsw_spi_wreg(int spi_ss, int chip_id, int page, int reg, uint8 *data, int len);
int enet_ioctl_ethsw_regaccess(struct ethswctl_data *e);
int enet_ioctl_ethsw_spiaccess(struct ethswctl_data *e);
int enet_ioctl_ethsw_pmdioaccess(struct net_device *dev, struct ethswctl_data *e);
int enet_ioctl_ethsw_info(struct net_device *dev, struct ethswctl_data *e);

#endif /* _BCMSWACCESS_H_ */

