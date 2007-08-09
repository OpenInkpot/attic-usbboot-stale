/*
 * board.c
 *
 * Board init routines.
 *
 * Copyright (C) 2006 Ingenic Semiconductor Inc.
 *
 */

#include "jz4740.h"


void leds(char *s)
{
	volatile unsigned char* led = (unsigned char *)0xb6000058;
	int i = 0;

	while ( s[i] && (i < 8)) {
		led[i] = s[i];
		i++;
	}
	while (i < 8)
		led[i++] = ' ';
}

void gpio_init(void)
{
	/*
	 * Initialize SDRAM pins
	 */

	/* PORT A: D0 ~ D31 */
	REG_GPIO_PXFUNS(0) = 0xffffffff;
	REG_GPIO_PXSELC(0) = 0xffffffff;

	/* PORT B: A0 ~ A16, DCS#, RAS#, CAS#, CKE#, RDWE#, CKO#, WE0# */
	REG_GPIO_PXFUNS(1) = 0x81f9ffff;
	REG_GPIO_PXSELC(1) = 0x81f9ffff;

	/* PORT C: WE1#, WE2#, WE3# */
	REG_GPIO_PXFUNS(2) = 0x07000000;
	REG_GPIO_PXSELC(2) = 0x07000000;


	/*
	 * Initialize Static Memory Pins
	 */

	/* CS4# */
	REG_GPIO_PXFUNS(1) = 0x10000000;
	REG_GPIO_PXSELC(1) = 0x10000000;


	/*
	 * Initialize UART0 pins
	 */

	/* PORT D: TXD/RXD */
	REG_GPIO_PXFUNS(3) = 0x06000000;
	REG_GPIO_PXSELS(3) = 0x06000000;


	/*
	 * Initialize LED pins
	 */

	/* PORT B: CS2# */
	REG_GPIO_PXFUNS(1) = 0x04000000;
	REG_GPIO_PXSELC(1) = 0x04000000;
}

//----------------------------------------------------------------------------
// SDRAM paramters
#define SDRAM_BW16		0	/* Data bus width: 0-32bit, 1-16bit */
#define SDRAM_BANK4		1	/* Banks each chip: 0-2bank, 1-4bank */
#define SDRAM_ROW		13	/* Row address: 11 to 13 */
#define SDRAM_COL		9	/* Column address: 8 to 12 */
#define SDRAM_CASL		2	/* CAS latency: 2 or 3 */

// SDRAM Timings, unit: ns
#define SDRAM_TRAS		45	/* RAS# Active Time */
#define SDRAM_RCD		20	/* RAS# to CAS# Delay */
#define SDRAM_TPC		20	/* RAS# Precharge Time */
#define SDRAM_TRWL		7	/* Write Latency Time */
#define SDRAM_TREF	        15625	/* Refresh period: 4096 refresh cycles/64ms */

#define CPU_CLK			8000000
#define MEM_CLK			8000000

void sdram_init(void)
{
	register unsigned int dmcr, sdmode, tmp, ns;
	volatile unsigned int *p;

	unsigned int cas_latency_sdmr[2] = {
		EMC_SDMR_CAS_2,
		EMC_SDMR_CAS_3,
	};

	unsigned int cas_latency_dmcr[2] = {
		1 << EMC_DMCR_TCL_BIT,	/* CAS latency is 2 */
		2 << EMC_DMCR_TCL_BIT	/* CAS latency is 3 */
	};

	REG_EMC_RTCSR = EMC_RTCSR_CKS_DISABLE;
	REG_EMC_RTCOR = 0;
	REG_EMC_RTCNT = 0;

	/* Basic DMCR register value. */
	dmcr = ((SDRAM_ROW-11)<<EMC_DMCR_RA_BIT) |
		((SDRAM_COL-8)<<EMC_DMCR_CA_BIT) |
		(SDRAM_BANK4<<EMC_DMCR_BA_BIT) |
		(SDRAM_BW16<<EMC_DMCR_BW_BIT) |
		EMC_DMCR_EPIN |
		cas_latency_dmcr[((SDRAM_CASL == 3) ? 1 : 0)];

	/* SDRAM timing parameters */
	ns = 1000000000 / MEM_CLK;

	tmp = SDRAM_TRAS/ns;
	if (tmp < 4)
		tmp = 4;
	if (tmp > 11)
		tmp = 11;
	dmcr |= ((tmp-4) << EMC_DMCR_TRAS_BIT);
	tmp = SDRAM_RCD/ns;
	if (tmp > 3)
		tmp = 3;
	dmcr |= (tmp << EMC_DMCR_RCD_BIT);
	tmp = SDRAM_TPC/ns;
	if (tmp > 7)
		tmp = 7;
	dmcr |= (tmp << EMC_DMCR_TPC_BIT);
	tmp = SDRAM_TRWL/ns;
	if (tmp > 3)
		tmp = 3;
	dmcr |= (tmp << EMC_DMCR_TRWL_BIT);
	tmp = (SDRAM_TRAS + SDRAM_TPC)/ns;
	if (tmp > 14)
		tmp = 14;
	dmcr |= (((tmp + 1) >> 1) << EMC_DMCR_TRC_BIT);

	/* SDRAM mode values */
	sdmode = EMC_SDMR_BT_SEQ | 
		 EMC_SDMR_OM_NORMAL |
		 EMC_SDMR_BL_4 | 
		 cas_latency_sdmr[((SDRAM_CASL == 3) ? 1 : 0)];

	if (SDRAM_BW16)
		sdmode <<= 1;
	else
		sdmode <<= 2;

	/* First, precharge phase */
	REG_EMC_DMCR = dmcr;

	/* Set refresh registers */
	tmp = SDRAM_TREF/ns;
	tmp = tmp/64 + 1;
	if (tmp > 0xff)
		tmp = 0xff;

	REG_EMC_RTCOR = tmp;
	REG_EMC_RTCSR = EMC_RTCSR_CKS_64;	/* Divisor is 64, CKO/64 */

	/* precharge all chip-selects */
	REG8(EMC_SDMR0|sdmode) = 0;
	REG8(EMC_SDMR1|sdmode) = 0;

	/* wait for precharge, > 200us */
	tmp = (CPU_CLK / 1000000) * 200;
	while (tmp--);

	/* enable refresh and set SDRAM mode */
	REG_EMC_DMCR = dmcr | EMC_DMCR_RFSH | EMC_DMCR_MRSET;

	/* write sdram mode register for each chip-select */
	REG8(EMC_SDMR0|sdmode) = 0;
	REG8(EMC_SDMR1|sdmode) = 0;

	/* do simple memory check */
	p = (volatile unsigned int *)(0xa0100000);
	*p = 0x12345678;
	p += 1;
	*p = 0x87654321;    
	p -= 1;

	if (*p != 0x12345678) {
		/* memory initialization failed */
		while(1);
	}

	/* everything is ok now */
}
