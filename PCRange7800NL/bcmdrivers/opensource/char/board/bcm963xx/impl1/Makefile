# Makefile for the bcm963xx board drivers
#


obj-y := board.o bcm63xx_flash.o bcm63xx_led.o

ifeq ($(strip $(BRCM_CHIP)),6816)
obj-y += spidevices.o
endif

ifneq ($(strip $(CONFIG_BCM_CPLD1)),)
    obj-y += bcmcpld1.o
	EXTRA_CFLAGS += -DCONFIG_BCM_CPLD1
endif

EXTRA_CFLAGS += -I. -I$(INC_BRCMDRIVER_PUB_PATH)/$(BRCM_BOARD) -I$(INC_BRCMSHARED_PUB_PATH)/$(BRCM_BOARD) -I$(INC_BRCMSHARED_PUB_PATH)/$(BRCM_BOARD)

ifneq ($(strip $(CONFIG_BCM_WLAN)),)
	EXTRA_CFLAGS += -DWIRELESS
endif

# howard add on 20090522
ifneq ($(strip $(BIGUARD_LOAD_BALANCE)),)
EXTRA_CFLAGS += -DCONFIG_BIGUARD_LOAD_BALANCE
endif
# # howard end

-include $(TOPDIR)/Rules.make

clean:
	rm -f core *.o *.a *.s

