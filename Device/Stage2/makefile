# 
# 
# Copyright (C) 2006 Ingenic Semiconductor Inc.
# By Lucifer
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License version 2 as
# published by the Free Software Foundation.
# 

# -----------------------------

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

ABSDIR  := ~/open/01boot/USB_Boot
TOP	:= .

OSDIR	:= $(TOP)/OS/src
ARCHDIR	:= $(TOP)/OS/mips
SOCDIR	:= $(TOP)/OS/jz4740

USBBOOTDIR := $(TOP)/boot

LIBDIR	:= 

SOURCES	:= $(wildcard $(SOCDIR)/*.c) \
	   $(wildcard $(ARCHDIR)/*.c) \
	   $(OSDIR)/ucos_ii.c

SOURCES	+= $(wildcard $(ARCHDIR)/*.S)
SOURCES += $(wildcard $(USBBOOTDIR)/usb_boot/*.c) $(wildcard $(USBBOOTDIR)/norflash/*.c) $(wildcard $(USBBOOTDIR)/nandflash/*.c) 

HEADS	:= $(SOCDIR)/head.S 
CFLAGS	+= -I$(OSDIR) -I$(ARCHDIR) -I$(SOCDIR)/include  -I$(USBBOOTDIR)/usb_boot  -I$(USBBOOTDIR)/nandflash  -I$(USBBOOTDIR)/norflash -I$(USBBOOTDIR)/include

OBJS	:= $(addsuffix .o , $(basename $(notdir $(SOURCES))))
HEADO	:= $(addsuffix .o , $(basename $(notdir $(HEADS))))

APP	:= usb_boot.elf 

VPATH	:= $(ARCHDIR) $(SOCDIR) $(OSDIR) $(USBBOOTDIR)/usb_boot  $(USBBOOTDIR)/norflash $(USBBOOTDIR)/nandflash 

all:	$(APP)
	$(OBJCOPY) -O binary $(APP) usb_boot.bin
	$(OBJDUMP) -d $(APP) > usb_boot.dump
	$(NM) $(APP) | sort > usb_boot.sym
	$(OBJDUMP) -h $(APP) > usb_boot.map
	cp usb_boot.bin /tftpboot/yliu

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

