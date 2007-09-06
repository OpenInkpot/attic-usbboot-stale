/*
 * main.c
 *
 * Main routine of the firmware.
 *
 * Copyright (C) 2006 Ingenic Semiconductor Inc.
 *
 */
#include "jz4740.h"

extern void leds(char *s);
extern void gpio_init(void);
extern void sdram_init(void);
extern void serial_init(void);
extern void serial_puts(const char *s);
extern void pll_init(void);

static void check_sdram(void)
{
	volatile unsigned int *addr = (volatile unsigned int *)0xa0100000;

	*addr = 0x12345678;
	*(addr+1) = 0x87654321;
}

void c_main(void)
{
	gpio_init();
	pll_init();
	serial_init();
	sdram_init();
	check_sdram();
}
