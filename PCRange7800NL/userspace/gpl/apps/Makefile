#
# To add an app, add it to APP_DIRS, and write the target rule in the
# last section of this Makefile
#
APP_DIRS = atm2684 bridge-utils busybox dproxy-nexgen ebtables ftpd \
           iproute2 iptables radvd udhcp urlfilterd zebra \
           dynahelper mtd-utils ntfs-3g samba conntrack openl2tpd rng-tools-2 pptp

#
# We need to declare these directory names as phony targets,
# otherwise make will think the directories themselves are
# the targets and will never execute the cmds.
# See GNU Make, 4.6 
#
.PHONY : $(APP_DIRS)


# Some apps have names that are different from their directory
# name, so need to list them explictly here.
all : $(APP_DIRS) brctl dproxy


#
# Cleaning rules
# See example in GNU Make, 4.6
#
clean:
	for dir in $(APP_DIRS); do \
		if [ -d $$dir ] ; then \
			$(MAKE) -C $$dir clean; \
		fi \
	done


#
# Set our CommEngine directory (by splitting the pwd into two words
# at /userspace and taking the first word only).
# Then include the common defines under CommEngine.
# You do not need to modify this part.
#
CURR_DIR := $(shell pwd)
BUILD_DIR:=$(subst /userspace, /userspace,$(CURR_DIR))
BUILD_DIR:=$(word 1, $(BUILD_DIR))

include $(BUILD_DIR)/make.common

export BUILD_DIR



##############################################################
# 
# Rules for inidividual apps
# apps can be compiled or not depending on the profile (which
# is modified via make menuconfig)
#
##############################################################


ifneq ($(strip $(BUILD_BRCTL)),)
brctl: sanity_check
	mkdir -p $(INSTALL_DIR)/bin
	(tar xkfj bridge-utils.tar.bz2 2> /dev/null || true)
	$(MAKE) -C bridge-utils $(BUILD_BRCTL)
else
brctl: sanity_check
endif


ifeq ($(strip $(BRCM_IKOS)),y)
BUSYBOX_CONFIG=ikos.config
else
BUSYBOX_CONFIG=brcm.config
endif

ifneq ($(strip $(BUILD_BUSYBOX)),)
busybox: sanity_check
	mkdir -p $(INSTALL_DIR)/bin
	(tar xkfj busybox.tar.bz2 2> /dev/null || true)
	cd busybox; cp -f $(BUSYBOX_CONFIG) .config
	$(MAKE) -C busybox install
else
busybox: sanity_check
	@echo "skipping busybox (not configured)"
endif


ifneq ($(strip $(BUILD_DPROXY)),)
dproxy: sanity_check
	mkdir -p $(INSTALL_DIR)/bin
	(tar xkfj dproxy-nexgen.tar.bz2 2> /dev/null || true)
	$(MAKE) -C dproxy-nexgen $(BUILD_DPROXY)
else
dproxy: sanity_check
	@echo "skipping dproxy (not configured)"
endif


# in userapps->Dynamic ALG loader
ifneq ($(strip $(BUILD_DYNAHELPER)),)
dynahelper: sanity_check
	$(MAKE) -C dynahelper $(BUILD_DYNAHELPER)
else
dynahelper: sanity_check
	@echo "skipping dynahelper (not configured)"
endif


ifneq ($(strip $(BUILD_EBTABLES)),)
ebtables: sanity_check
	mkdir -p $(INSTALL_DIR)/bin
	(tar xkfj ebtables.tar.bz2 2> /dev/null || true)
	$(MAKE) -C ebtables $(BUILD_EBTABLES)
else
ebtables: sanity_check
	@echo "skipping ebtables (not configured)"
endif


# ftpd does sanity check in its own Makefile
ifneq ($(strip $(BUILD_FTPD)),)
ftpd:
	(tar xkfj ftpd.tar.bz2 2> /dev/null || true)
	$(MAKE) -C ftpd $(BUILD_FTPD)
else
ftpd:
	@echo "skipping ftpd (not configured)"
endif


# Build the iproute2 package whenever IPROUTE2, IPV6, or BRCM_KERNEL_NETQOS
# is defined.  In make menuconfig, "traffic control" enables BRCM_KERNEL_NETQOS
ifneq ($(strip $(BUILD_IPROUTE2)),)
DO_BUILD_IPROUTE2=y
endif

ifneq ($(strip $(BUILD_IPV6)),)
DO_BUILD_IPROUTE2=y
endif

ifneq ($(strip $(BRCM_KERNEL_NETQOS)),)
DO_BUILD_IPROUTE2=y
endif

ifneq ($(strip $(DO_BUILD_IPROUTE2)),)
iproute2: sanity_check
	(tar xkfj iproute2.tar.bz2 2> /dev/null || true)
	$(MAKE) -C iproute2 dynamic
else
iproute2: sanity_check
	@echo "skipping iproute2 (not configured)"
endif


# iptables is dependent on kernel netfilter modules
ifneq ($(strip $(BRCM_KERNEL_NETFILTER)),)
ifneq ($(strip $(BUILD_IPTABLES)),)
iptables: sanity_check
	(tar xkfj iptables.tar.bz2 2> /dev/null || true)
	$(MAKE) -C iptables $(BUILD_IPTABLES)
else
iptables: sanity_check
	@echo "skipping iptables (not configured)"
endif
else
iptables: sanity_check
	@echo Warning: To use iptables, you need to enable netfilter in the kernel !!!!!
endif


ifneq ($(strip $(BUILD_IPTABLES)),)
ifneq ($(strip $(BUILD_URLFILTER)),)
urlfilterd: sanity_check
	$(MAKE) -C urlfilterd $(BUILD_URLFILTER)
else
urlfilterd: sanity_check
endif
else
urlfilterd: sanity_check
	@echo Warning: To use urlfilterd, you need to enable iptables!!!!!
endif



ifneq ($(strip $(BUILD_IPV6)),)
radvd: sanity_check
	(tar xkjf radvd.tar.bz2 2> /dev/null || true)
	$(MAKE) -C radvd
else
radvd: sanity_check
	@echo "skipping radvd (not configured)"
endif



ifneq ($(strip $(BUILD_UDHCP)),)
udhcp: sanity_check
	$(MAKE) -C udhcp $(BUILD_UDHCP)
else
udhcp: sanity_check
	@echo "skipping udhcp (not configured)"
endif


ifneq ($(strip $(BUILD_ZEBRA)),)
zebra: sanity_check
	(tar xkfj zebra.tar.bz2 2> /dev/null || true)
	$(MAKE) -C zebra $(BUILD_ZEBRA)
else
zebra: sanity_check
	@echo "skipping zebra (not configured)"
endif

ifneq ($(strip $(BUILD_MTDUTILS)),)
mtd-utils: sanity_check
	mkdir -p $(INSTALL_DIR)/bin
	(tar xkfz mtd-utils.tar.gz 2> /dev/null || true)
	(cd mtd-utils; $(MAKE) install)
else
mtd-utils: sanity_check
	@echo "skipping mtd-utils (not configured)"
endif

ifneq ($(strip $(BUILD_NTFS_3G)),)
ntfs-3g: sanity_check
	(tar xkfz ntfs-3g.tar.gz 2> /dev/null || true)
	$(MAKE) -C ./ntfs-3g 
	install -m 755 ./ntfs-3g/libntfs-3g/.libs/libntfs-3g.so.54 $(INSTALL_DIR)/lib/libntfs-3g.so.54
	install -m 755 ./ntfs-3g/src/.libs/ntfs-3g  $(INSTALL_DIR)/bin/ntfs-3g	
else
ntfs-3g: sanity_check
	@echo "skipping $@ (not configured)"
endif

ifneq ($(strip $(BUILD_SAMBA)),)
samba: sanity_check
#	(tar xkfz samba.tar.gz 2> /dev/null || true)
#	$(MAKE) -C ./samba
	$(MAKE) -C ./samba-3.0.2
else
samba: sanity_check 
	@echo "skipping $@ (not configured)"
endif

ifneq ($(strip $(BUILD_L2TPAC)),)
openl2tpd: sanity_check
	(tar xkjf openl2tpd.tar.bz2 2> /dev/null || true)
	$(MAKE) -C openl2tpd
else
openl2tpd: sanity_check
	@echo "skipping openl2tpd (not configured)"
endif

ifneq ($(strip $(BUILD_RNGD)),)
rng-tools-2: sanity_check
	mkdir -p $(INSTALL_DIR)/bin
	(tar xkfz rng-tools-2.tar.gz 2> /dev/null || true)
	($(MAKE) -C rng-tools-2 $(BUILD_RNGD))
else
rngd: sanity_check
	@echo "skipping rng-tools-2 (not configured)"
endif

ifneq ($(strip $(BUILD_PPTPAC)),)
pptp: sanity_check
	(tar xkjf pptp.tar.bz2 2> /dev/null || true)
	$(MAKE) -C pptp
else
pptp: sanity_check
	@echo "skipping pptp (not configured)"
endif

ifneq ($(strip $(BUILD_CONNTRACK_TOOLS)),)
conntrack: sanity_check
	(tar xkfz conntrack.tar.gz 2> /dev/null || true)
	$(MAKE) -C ./conntrack
else
conntrack: sanity_check
	@echo "skipping $@ (not configured)"
endif


