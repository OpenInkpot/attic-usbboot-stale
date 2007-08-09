/*
 * main.c
 *
 * Main routine of the firmware.
 *
 * Copyright (C) 2006 Ingenic Semiconductor Inc.
 *
 */

extern void leds(char *s);
extern void gpio_init(void);
extern void sdram_init(void);
extern void serial_init(void);
extern void serial_puts(const char *s);

static void check_sdram(void)
{
	volatile unsigned int *addr = (volatile unsigned int *)0xa0100000;

	*addr = 0x12345678;
	*(addr+1) = 0x87654321;

	//if (*addr != 0x12345678)
		//serial_puts("fw1 sdram failed\n");
	//else
		//serial_puts("fw1 sdram ok\n");
}

void c_main(void)
{
	gpio_init();
	serial_init();
	sdram_init();
	check_sdram();

	//serial_puts("fw1 runs ok\n");
}
