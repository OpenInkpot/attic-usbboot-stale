#
# Copyright (C) 2006 Ingenic Semiconductor Inc.
#
# Makefile for the JZ4740 internal bootrom code.
#

CROSS	:= mipsel-linux-

CFLAGS	:= -O2 -G 0 -mno-abicalls -fno-pic -mips32
LDFLAGS	:= -nostdlib -EL -Ttarget.ld

OBJS	= head.o main.o board.o serial.o

fw.bin: fw.elf
	$(CROSS)objcopy -O binary $< $@
	$(CROSS)objdump -D $< > fw.dump
	$(CROSS)objdump -h $< > fw.map
	$(CROSS)nm -n $< > System.map

fw.elf: $(OBJS)
	$(CROSS)ld $(LDFLAGS) $^ -o $@
.c.o:
	$(CROSS)gcc $(CFLAGS) -c $< -o $@
.S.o:
	$(CROSS)gcc $(CFLAGS) -c $< -o $@

clean:
	rm -fr *.o *.elf *.bin *.dump *.map

