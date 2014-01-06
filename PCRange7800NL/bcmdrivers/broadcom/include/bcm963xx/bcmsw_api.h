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

#ifndef _BCMSW_API_H_
#define _BCMSW_API_H_

#if defined(CONFIG_BCM96816) || defined(CHIP_6816)
/* Exports from Enet driver */
extern int reset_switch(void);
extern int is_switch_locked(void);
#endif

#endif /* _BCMSW_API_H_ */

