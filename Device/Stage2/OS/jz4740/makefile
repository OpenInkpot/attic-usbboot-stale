# 
# 
# Author: Seeger Chin
# e-mail: seeger.chin@gmail.com
# 
# Copyright (C) 2006 Ingenic Semiconductor Inc.
# 
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License version 2 as
# published by the Free Software Foundation.
# 
# 

# select which module to compile, set value to 1 for the module to compile, remain blank for the module not to compile
# -----------------------------
JZ4740_PAV = 1
CAMERA = 0
LWIP   = 0
UCGUI  = 0
UCFS   = 0
MMC    = 1
JPEG   = 0
UDC    = 1
# ------------------------------

CC	:= mipsel-linux-gcc
AR	:= mipsel-linux-ar rcsv
LD	:= mipsel-linux-ld
OBJCOPY	:= mipsel-linux-objcopy
NM	:= mipsel-linux-nm
OBJDUMP	:= mipsel-linux-objdump

CFLAGS	:= -mips32 -O2 -mno-abicalls -fno-pic -fno-builtin \
	   -fno-exceptions -ffunction-sections -finit-priority \
	   -fomit-frame-pointer -msoft-float -G 0

LIBS	:= -lstdc++ -lc -lm -lgcc

TOP	:= ..

OSDIR	:= $(TOP)/src
ARCHDIR	:= $(TOP)/mips
SOCDIR	:= $(TOP)/jz4740
MMCDIR	:= $(TOP)/mmc
UCFSDIR := $(TOP)/ucfs
LWIPDIR := $(TOP)/lwip/src
UCGUIDIR := $(TOP)/ucgui
CORE    :=  $(TOP)/ucgui/Core

UDCDIR  := $(TOP)/jz4740/udc_mmc

LIBDIR	:= 

SOURCES	:= $(wildcard $(SOCDIR)/*.c) \
	   $(wildcard $(ARCHDIR)/*.c) \
	   $(OSDIR)/ucos_ii.c

SOURCES	+= $(wildcard $(ARCHDIR)/*.S)

HEADS	+= $(SOCDIR)/head.S 

CFLAGS  += -DJZ4740_PAV=$(JZ4740_PAV)
CFLAGS	+= -I$(OSDIR) -I$(SOCDIR)/include -I$(ARCHDIR) -I$(SOCDIR)


VPATH	:= $(ARCHDIR) $(SOCDIR) $(OSDIR)

ifeq ($(MMC),1)
SOURCES	+= $(MMCDIR)/mmc.c
SOURCES	+= $(MMCDIR)/mmc_jz4740.c
CFLAGS	+= -I$(MMCDIR)
VPATH   += $(MMCDIR)
endif

ifeq ($(UCFS),1)
SOURCES	+= $(UCFSDIR)/ucfs.c
CFLAGS	+= -I$(UCFSDIR)
VPATH   +=  $(UCFSDIR)
endif

ifeq ($(LWIP),1)
SOURCES	+= $(LWIPDIR)/lwip.c 
CFLAGS	+= -I$(LWIPDIR)  -I$(LWIPDIR)/include -I$(LWIPDIR)/include/lwip
VPATH   += $(LWIPDIR)
endif

ifeq ($(UCGUI),1)
SOURCES	+= $(wildcard $(CORE)/*.c) $(wildcard $(UCGUIDIR)/LCDDriver/*.c) $(wildcard $(UCGUIDIR)/Font/*.c)  $(wildcard $(UCGUIDIR)/ConvertColor/*.c)
CFLAGS	+= -I$(UCGUIDIR)/Font -I$(UCGUIDIR)/LCDDriver -I$(TOP)/ucgui/Config -I$(UCGUIDIR)/Core -I$(UCGUIDIR)/ConvertColor
VPATH   += $(UCGUIDIR) $(CORE)  $(UCGUIDIR)/LCDDriver $(UCGUIDIR)/Font $(TOP)/ucgui/Config $(UCGUIDIR)/ConvertColor
endif

ifeq ($(CAMERA),1)
SOURCES	+= $(wildcard $(SOCDIR)/camera/*.c) $(SOCDIR)/drv/i2c.c 
CFLAGS += -I$(SOCDIR)/camera
VPATH  += $(SOCDIR)/camera
endif

ifeq ($(JPEG),1)
SOURCES	+= $(wildcard $(UCGUIDIR)/JPEG/*.c)
CFLAGS += -I$(UCGUIDIR)/JPEG
VPATH  += $(UCGUIDIR)/JPEG
endif

ifeq ($(UDC),1)
SOURCES	+= $(wildcard $(UDCDIR)/*.c)
CFLAGS += -I$(UDCDIR)
VPATH  += $(UDCDIR)
endif

OBJS	:= $(addsuffix .o , $(basename $(notdir $(SOURCES))))
HEADO	:= $(addsuffix .o , $(basename $(notdir $(HEADS))))


APP	:= ucos.elf


all:	$(APP)
	$(OBJCOPY) -O binary $(APP) ucos.bin
	$(OBJDUMP) -d $(APP) > ucos.dump
	$(NM) $(APP) | sort > ucos.sym
	$(OBJDUMP) -h $(APP) > ucos.map
	cp ucos.bin /tftpboot/yliu/

$(APP):	$(HEADO) $(OBJS) $(EXTLIBS) link.xn makefile
	$(CC) -nostdlib -T link.xn -o $@ $(HEADO) $(OBJS) $(EXTLIBS) $(LIBS)

.c.o:
	$(CC) $(CFLAGS) -o $@ -c $<
.cpp.o:
	$(CC) $(CFLAGS) -fno-rtti -fvtable-gc -o $@ -c $<
.S.o:
	$(CC) $(CFLAGS) -D_ASSEMBLER_ -D__ASSEMBLY__ -o $@ -c $<

clean:
	rm -fr *.o $(APP) $(OBJS) core $(OTHER) *.sym *.map *.dump *.bin *.lib

