ifndef KERNEL_DIR
KERNEL_DIR = ../kernel/linux
endif
ifndef BRCM_BOARD
BRCM_BOARD = bcm963xx
endif
ifndef TARGETS_DIR
TARGETS_DIR = ../targets
endif
ifndef SHARED_DIR
SHARED_DIR = ../shared
endif
ifndef INC_BRCMBOARDPARMS_PATH
INC_BRCMBOARDPARMS_PATH = $(SHARED_DIR)/opensource/boardparms
endif

# host tools should not use cross compiler
unexport AR AS LD CC CPP CXX NM STRIP SSTRIP OBJCOPY OBJDUMP RANLIB

INCLUDEDIR = -I$(INC_BRCMDRIVER_PUB_PATH)/$(BRCM_BOARD) -I$(INC_BRCMSHARED_PUB_PATH)/$(BRCM_BOARD) -I.

CONFIG_SHELL := $(shell if [ -x "$$BASH" ]; then echo $$BASH; \
	else if [ -x /bin/bash ]; then echo /bin/bash; \
	else echo sh; fi ; fi)
TOPDIR	:= $(shell /bin/pwd)
SSHD_DIR = $(BUILD_DIR)/userspace/public/apps/sshd
GENKEY_DIR = $(SSHD_DIR)/genkey
HOST_GENKEY = $(TOPDIR)/host_genkey
CC = gcc
STRIP = strip
RSA_KEY = $(TARGETS_DIR)/fs.src/etc/rsa_host_key
###DSS_KEY = $(TARGETS_DIR)/fs.src/etc/dss_host_key
export SSHD_DIR HOST_GENKEY CC STRIP

#WARNINGS= -Wall

#export DEFS		= -DDEBUG
CFLAGS_NOARCH	= $(DEFS) $(WARNINGS) -O2 -DGNU $(INCLUDEDIR)
CFLAGS		= $(CFLAGS_NOARCH) -m32
ifeq ($(strip $(BUILD_SQUASH_HIGH)),y)
	CFLAGS += -DBUILD_SQUASH_HIGH
endif
ifeq ($(strip $(BUILD_SQUASH_NORMAL)),y)
	CFLAGS += -DBUILD_SQUASH_NORMAL
endif
ifeq ($(strip $(BUILD_SQUASH_LOW)),y)
	CFLAGS += -DBUILD_SQUASH_LOW
endif
ifeq ($(strip $(BRCM_IKOS)),y)
	CFLAGS += -DCONFIG_BRCM_IKOS
endif
# sarah add, 20100125
ifneq ($(strip $(BN_BUILD_CUSTOMER)),)
	CFLAGS += -DBILLION_PROD
endif
export CFLAGS


ifeq ($(strip $(BRCM_KERNEL_ROOTFS)),nfs)
BUILD_SET =
else
BUILD_SET = build_mkfs build_cmplzma build_hostgenkey build_imageutil fakeroot
endif


.PHONY: mklzma_sqfs mklzma_cmd $(BUILD_SET)
all: $(BUILD_SET)


build_imageutil: bcmImageBuilder addvtoken createimg image_modify_qc_cfg cfg_checksum

bcmImageBuilder: bcmImageBuilder.c
	$(CC) $(CFLAGS) -o bcmImageBuilder bcmImageBuilder.c
addvtoken: addvtoken.c
	$(CC) $(CFLAGS) -o addvtoken addvtoken.c 
createimg: createimg.c
	$(CC) $(CFLAGS) -o createimg createimg.c -lm
image_modify_qc_cfg: image_modify_qc_cfg.c
	$(CC) image_modify_qc_cfg.c -o image_modify_qc_cfg
cfg_checksum: cfg_checksum.c
	$(CC) cfg_checksum.c -o cfg_checksum

ifeq ($(strip $(BRCM_KERNEL_ROOTFS)),squashfs)
ifneq ($(strip $(BRCM_ROOTFS_SQUASHFS_4_0)),)
build_mkfs: untar_lzma457 mksquashfs
else
build_mkfs: mksquashfs
endif
else
ifeq ($(strip $(BRCM_KERNEL_ROOTFS)),cramfs)
build_mkfs: mkcramfs $(LZMAOBJS)
else
ifeq ($(strip $(BRCM_KERNEL_ROOTFS)),jffs2)
build_mkfs: mkjffs2
else
ifeq ($(strip $(BRCM_KERNEL_ROOTFS)),ubifs)
build_mkfs:
endif
endif
endif
endif

ifneq ($(strip $(BRCM_ROOTFS_SQUASHFS_4_0)),)
SQUASHFS_VER="4.0"
SQUASHFS_DIR=$(TOPDIR)/squashfs_4.0
export Sqlzma=$(SQUASHFS_DIR)
export LzmaAlone=$(TOPDIR)/lzma457/CPP/7zip/Compress/LZMA_Alone
export LzmaC=$(TOPDIR)/lzma457/C/Compress/Lzma
else
SQUASHFS_VER="3.0"
SQUASHFS_DIR = $(TOPDIR)/squashfs
export Sqlzma= $(SQUASHFS_DIR)
export LzmaAlone= $(TOPDIR)/lzma/7zip/Compress/LZMA_Alone
export LzmaC= $(TOPDIR)/lzma/7zip/Compress/LZMA_C
endif
JFFS2_DIR = $(TOPDIR)/jffs2

untar_lzma457:
	if [ ! -e lzma457/lzma.txt ]; then \
	echo Untarring lzma 4.57 source...; \
	(tar xkfj lzma457.tar.bz2 2> /dev/null || true); \
	fi

mklzma_cmd:
	@echo building lzma host tool ...
	make -C $(LzmaAlone) -f makefile.gcc
	cp -f $(LzmaAlone)/lzma lzmacmd

mklzma_sqfs:
	@echo building lzma library and host tool for squashfs $(SQUASHFS_VER) ...
	make -C $(LzmaAlone) -f sqlzma.mk
	make -C $(LzmaC) -f sqlzma.mk

mksquashfs: mklzma_sqfs
	@echo building mksqushfs host tool ...
	make -C $(SQUASHFS_DIR)
	mv $(SQUASHFS_DIR)/mksquashfs mksquashfs

mkcramfs:  cramfs/mkcramfs.cpp $(LZMAOBJS)
	@if [ ! -e /usr/include/zlib.h ]; then \
          echo *****You need to install zlib-devel package to build mkcramfs! ; \
          echo *****You may find it in your Linux distribution CDs. ; \
	  exit ;\
        fi
	g++ $(CFLAGS) -I$(KERNEL_DIR)/include -c cramfs/mkcramfs.cpp
	g++ -m32 -o mkcramfs mkcramfs.o $(LZMAOBJS) -lz -lm

mkjffs2:
	@echo building mkjffs2 host tool ...
	make -C $(JFFS2_DIR)
	mv jffs2/mkfs.jffs2 .

build_cmplzma: mklzma_cmd cmplzma.cpp
	g++ $(CFLAGS) -c cmplzma.cpp
	g++  -m32 -o cmplzma cmplzma.o -lm


ifeq ($(strip $(BUILD_SSHD)),y)
ifeq ($(strip $(BUILD_SSHD_MIPS_GENKEY)),y)
build_hostgenkey:
	@if [ -e $(RSA_KEY) ]; then \
		rm -fr $(RSA_KEY); \
	  exit ;\
        fi
###	@if [ -e $(DSS_KEY) ]; then \
###		rm -fr $(DSS_KEY); \
###	  exit ;\
###        fi
else
build_hostgenkey:	
	@if [ ! -e $(RSA_KEY) ]; then \
		cd $(GENKEY_DIR) && $(MAKE); \
		$(HOST_GENKEY) -t rsa -f $(RSA_KEY); \
	  exit ;\
        fi
###	@if [ ! -e $(DSS_KEY) ]; then \
###		$(HOST_GENKEY) -t dss -f $(DSS_KEY); \
###	  exit ;\
###     fi
endif
else
build_hostgenkey:
	@if [ -e $(RSA_KEY) ]; then \
		rm -fr $(RSA_KEY); \
	  exit ;\
        fi
###	@if [ -e $(DSS_KEY) ]; then \
###		rm -fr $(DSS_KEY); \
###	  exit ;\
###     fi
endif

$(LZMAOBJS): %.o: %.cpp
	g++ -c $(CFLAGS) $^ -o $@


export FAKEROOT_DIR = $(TOPDIR)/fakeroot

$(FAKEROOT_DIR)/.configured:
	(tar -jkxf fakeroot.tar.bz2 2> /dev/null || true)
	cd $(FAKEROOT_DIR); CFLAGS="$(CFLAGS_NOARCH)" ./configure --prefix=/usr --disable-nls
	touch $@

fakeroot: $(FAKEROOT_DIR)/.configured
	make -C $(FAKEROOT_DIR)
	sed -e 's,^PREFIX=.*,PREFIX=$(FAKEROOT_DIR),g' -e 's,^BINDIR=.*,BINDIR=$(FAKEROOT_DIR),g' -e 's,^PATHS=.*,PATHS=$(FAKEROOT_DIR)/.libs:/lib:/usr/lib,g' $(FAKEROOT_DIR)/scripts/fakeroot > $(FAKEROOT_DIR)/fakeroot
	chmod u+x $(FAKEROOT_DIR)/fakeroot


######################################################################
#
# This section deals with doxygen
#
# Note that if you want to change the settings in the config file,
# (Doxyfile), you should do it in this makefile.
# Any modifications to the config file itself will be
# wiped out next time you make the build_doxygen target.
#
######################################################################

doxygen:
	tar -jxf doxygen.tar.bz2
	cd doxygen; ./configure


build_doxygen: doxygen
	cd doxygen; make; \
	cd bin; rm -f Doxyfile; \
	./doxygen -g > /dev/null; \
	sed -i 's,\(PROJECT_NAME[ \t]*=\),\1 CMS,' Doxyfile; \
	sed -i 's,\(OUTPUT_DIRECTORY[ \t]*=\),\1 $(BUILD_DIR)/docs/doxygen,' Doxyfile; \
	sed -i 's,\(JAVADOC_AUTOBRIEF[ \t]*=\)[ \tA-Z]*,\1 YES,' Doxyfile; \
	sed -i 's,\(OPTIMIZE_OUTPUT_FOR_C[ \t]*=\)[ \tA-Z]*,\1 YES,' Doxyfile; \
	sed -i 's,\(WARN_NO_PARAMDOC[ \t]*=\)[ \tA-Z]*,\1 YES,' Doxyfile; \
	sed -i 's,\(ENUM_VALUES_PER_LINE[ \t]*=\)[ \t0-9]*,\1 1,' Doxyfile; \
	sed -i 's,\(INPUT[ \t]*=\),\1 $(BUILD_DIR)/userspace/public/include,' Doxyfile; \
	sed -i 's,\(INPUT[ \t]*=\),\1 $(BUILD_DIR)/userspace/private/include,' Doxyfile; \
	sed -i 's,\(INPUT[ \t]*=\),\1 $(BUILD_DIR)/userspace/private/libs/cms_core,' Doxyfile; \
	sed -i 's,\(RECURSIVE[ \t]*=\)[ \tA-Z]*,\1 YES,' Doxyfile; \
	sed -i 's,\(GENERATE_LATEX[ \t]*=\)[ \tA-Z]*,\1 NO,' Doxyfile; \
	sed -i 's,\(PREDEFINED[ \t]*=\)[ \tA-Z]*,\1 MDM_SHARED_MEM CMS_MEM_DEBUG,' Doxyfile;

# if we want to generate documentation for the unittests 
#sed -i 's,\(INPUT[ \t]*=\),\1 $(BUILD_DIR)/unittests,' Doxyfile; 

######################################################################
#
# Cleaning rules
#
######################################################################


clean:
	rm -f bcmImageBuilder addvtoken createimg image_modify_qc_cfg cfg_checksum mksquashfs mkcramfs lzmacmd cmplzma $(HOST_GENKEY)
	rm -fr *.o core
	rm -fr $(GENKEY_DIR)/*.o
	make -C $(SQUASHFS_DIR) clean
	make -C $(LzmaAlone) -f sqlzma.mk clean
	make -C $(LzmaC) -f sqlzma.mk clean
	if [ -e $(FAKEROOT_DIR)/Makefile ];  then make -C $(FAKEROOT_DIR) distclean; fi
	rm -f $(FAKEROOT_DIR)/fakeroot
	rm -f $(FAKEROOT_DIR)/.configured
	make -C libcreduction clean

clean_doxygen:
	rm -fr doxygen
