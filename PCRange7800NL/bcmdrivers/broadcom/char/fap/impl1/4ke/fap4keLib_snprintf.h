#ifndef __FAP4KE_SNPRINTF_H_INCLUDED__
#define __FAP4KE_SNPRINTF_H_INCLUDED__

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
 * File Name  : fap4ke_snprintf.h
 *
 * Description: This file contains ...
 *
 *******************************************************************************
 */

int fap4ke_snprintf(char *buf,int len,const char *templat,...);
int fap4ke_xvsprintf(char *outbuf,const char *templat,va_list marker);

#endif  /* defined(__FAP4KE_SNPRINTF_H_INCLUDED__) */
