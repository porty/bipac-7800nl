/*
<:copyright-broadcom

 Copyright (c) 2009 Broadcom Corporation
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
#ifndef BCM_OS_DEPS_USR_H
#define BCM_OS_DEPS_USR_H

#ifdef NON_LINUX_BUILD

/*Open Device File Flags*/
#ifndef O_RDONLY
#define O_RDONLY  00000000
#endif /* O_RDONLY */
#ifndef O_WRONLY
#define O_WRONLY  00000001
#endif /* O_WRONLY */
#ifndef O_RDWR
#define O_RDWR    00000002
#endif /* O_RDWR */
#ifndef O_NONBLOCK
#define O_NONBLOCK  00004000
#endif /* O_NONBLOCK */

/*Open Device File*/
int bcm_dev_open(const char *path, int oflag, ... );

/*Ioctl Device File*/
int bcm_dev_ioctl(int fildes, int request, ... /* arg */);

/*Close Device File*/
int bcm_dev_close(int fildes);

/*Write to Device File*/
int bcm_dev_write(int fildes, const void *buf, unsigned nbyte);

/*Read from Device File*/
int bcm_dev_read(int fildes, void *buf, unsigned nbyte);

#else /*not NON_LINUX_BUILD*/

#include <unistd.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <fcntl.h>

#define bcm_dev_open open
#define bcm_dev_close close
#define bcm_dev_ioctl ioctl
#define bcm_dev_write write
#define bcm_dev_read read

#endif /* NON_LINUX_BUILD */
#endif /* BCM_OS_DEPS_USR_H */
