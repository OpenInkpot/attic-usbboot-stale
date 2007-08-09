/*
 * nandflash_4730.c
 *
 * Low-level operations to NAND flash.
 *
 * Copyright (c) 2005-2007  Ingenic Semiconductor Inc.
 *
 * Author: <jlwei@ingenic.cn>
 *
 */

#include "jz4730.h"

/*
 * Standard NAND commands.
 */
#define CMD_READA	0x00
#define CMD_READB	0x01
#define CMD_READC	0x50
#define CMD_ERASE_SETUP	0x60
#define CMD_ERASE	0xD0
#define CMD_READ_STATUS 0x70
#define CMD_CONFIRM	0x30
#define CMD_SEQIN	0x80
#define CMD_PGPROG	0x10
#define CMD_READID	0x90
#define CMD_RESET	0xff

#define ECC_BLOCK	256  /* 3-bytes HW ECC per 256-bytes data */
#define ECC_OFFSET      4    /* ECC store location offset to the spare area */

/*
 * NAND routines.
 */
#define nand_enable()		(REG_EMC_NFCSR |= EMC_NFCSR_NFE | EMC_NFCSR_FCE)
#define nand_disable()		(REG_EMC_NFCSR &= ~(EMC_NFCSR_NFE | EMC_NFCSR_FCE))
#define nand_ecc_enable()	(REG_EMC_NFCSR |= EMC_NFCSR_ECCE | EMC_NFCSR_ERST)
#define nand_ecc_disable()	(REG_EMC_NFCSR &= ~EMC_NFCSR_ECCE)
#define nand_ready()		(REG_EMC_NFCSR & EMC_NFCSR_RB)
#define nand_ecc()		(REG_EMC_NFECC & 0x00ffffff)
#define nand_cmd(n)		(REG8(cmdport) = (n))
#define nand_addr(n)		(REG8(addrport) = (n))
#define nand_data8()		REG8(dataport)
#define nand_data16()		REG16(dataport)

static inline void nand_wait_ready(void)
{
	u32 to = 1000;
	while (nand_ready() && to--);
	while (!nand_ready());
}

static volatile unsigned char *emcbase = 0;
static volatile unsigned char *addrport = 0;
static volatile unsigned char *dataport = 0;
static volatile unsigned char *cmdport = 0;

static u32 bus = 8, row = 2, pagesize = 512, oobsize = 16, ppb = 32;
static u32 bad_block_pos = 0;

/*
 * notify(int param)
 *
 * param value:
 * 0 : Ok
 * -1: page op fail
 * -2: hit bad block, skip it.
 */

static int (*write_proc)(char *, int) = 0;
static int (*read_proc)(char *, int) = 0;

static u8 badbuf[2048 + 64] = {0};
static u8 oobbuf[64] = {0};

/* 
 * I/O read/write interface.
 */
static inline int nand_data_write8(char *buf, int count)
{
	int i;
	u8 *p = (u8 *)buf;

	for (i = 0; i < count; i++)
		nand_data8() = *p++;
	return 0;
}

static inline int nand_data_write16(char *buf, int count)
{
	int i;
	u16 *p = (u16 *)buf;

	for (i = 0; i < count/2; i++)
		nand_data16() = *p++;
	return 0;
}

static inline int nand_data_read8(char *buf, int count)
{
	int i;
	u8 *p = (u8 *)buf;

	for (i = 0; i < count; i++)
		*p++ = nand_data8();
	return 0;
}

static inline int nand_data_read16(char *buf, int count)
{
	int i;
	u16 *p = (u16 *)buf;

	for (i = 0; i < count/2; i++)
		*p++ = nand_data16();
	return 0;
}

/*
 * Init nand parameters and enable nand controller.
 */
int nand_init_4730(int bus_width, int row_cycle, int page_size, int page_per_block,
	      u32 ebase, u32 aport, u32 dport, u32 cport)
{
	bus = bus_width;
	row = row_cycle;
	pagesize = page_size;
	oobsize = pagesize / 32;
	ppb = page_per_block;

	if (bus == 8) {
		write_proc = nand_data_write8;
		read_proc = nand_data_read8;
	} else {
		write_proc = nand_data_write16;
		read_proc = nand_data_read16;
	}

	emcbase = (u8 *)ebase;
	addrport = (u8 *)aport;
	dataport = (u8 *)dport;
	cmdport = (u8 *)cport;

	nand_enable();

	return 0;
}

/*
 * Disable nand operation.
 */
int nand_fini_4730(void)
{
	nand_disable();
	return 0;
}

/*
 * Read ID.
 */
unsigned int nand_query_4730(void)
{
	u16 vid, did;

	nand_cmd(CMD_READID);
	nand_addr(0);

	vid = nand_data8();
	did = nand_data8();

	return (vid << 16) | did;
}

/*
 * Read oob data for 512B pagesize.
 */
static void read_oob_512(void *buf, u32 oobsize, u32 pg)
{
	int i;
	u32 rowaddr;

	rowaddr = pg;

	nand_cmd(0x50);
	nand_addr(0);
	for (i = 0; i < row; i++) {
		nand_addr(rowaddr & 0xff);
		rowaddr >>= 8;
	}
	nand_wait_ready();

	read_proc(buf, oobsize);
}

/*
 * Read oob data for 2KB pagesize.
 */
static void read_oob_2048(void *buf, u32 oobsize, u32 pg)
{
	u32 i, coladdr, rowaddr;

	coladdr = 2048;
	rowaddr = pg;

	nand_cmd(CMD_READA);

	nand_addr(coladdr & 0xff);
	nand_addr(coladdr >> 8);
	for (i = 0; i < row; i++) {
		nand_addr(rowaddr & 0xff);
		rowaddr >>= 8;
	}
	nand_cmd(CMD_CONFIRM);
	nand_wait_ready();

	read_proc(buf, oobsize);
}

/*
 * Read oob data.
 */
static void read_oob(void *buf, int oobsize, int pg)
{
	if (pagesize == 2048)
		read_oob_2048(buf, oobsize, pg);
	else
		read_oob_512(buf, oobsize, pg);
}

/*
 * Return 1 if the block is bad block, else return 0.
 */
static int nand_check_block(u32 block)
{
	u32 pg;

	pg = block * ppb;

	read_oob(oobbuf, oobsize, pg);
	if (oobbuf[bad_block_pos] != 0xff)
		return 1;
	read_oob(oobbuf, oobsize, pg + 1);
	if (oobbuf[bad_block_pos] != 0xff)
		return 1;

	return 0;
}

/*
 * Mark a block bad.
 */
static void nand_block_markbad(u32 block)
{
	u32 i, rowaddr;

	for (i = 0; i < pagesize + oobsize; i++)
		badbuf[i] = 0xff;
	badbuf[pagesize + bad_block_pos] = 0; /* bad block flag */

	rowaddr = block * ppb;

	nand_cmd(CMD_READA);
	nand_cmd(CMD_SEQIN);

	nand_addr(0);
	if (pagesize == 2048)
		nand_addr(0);
	for (i = 0; i < row; i++) {
		nand_addr(rowaddr & 0xff);
		rowaddr >>= 8;
	}

	write_proc((char *)badbuf, pagesize + oobsize);
	nand_cmd(CMD_PGPROG);
	nand_wait_ready();
}

/*
 * Erase <blk_num> blocks from block <sblk>.
 */
int nand_erase_4730(int blk_num, int sblk, int force, void (*notify)(int))
{
	int i, cnt;
	u32 cur_blk, rowaddr;

	/* Send reset command to nand */
	nand_cmd(CMD_RESET);
	nand_wait_ready();

	cur_blk = sblk;
	cnt = 0;
	while (cnt < blk_num) {
		/*
		 * if force flag was not set, check for bad block.
		 * if force flag was set, erase anything.
		 */
		if (!force) {
			if (nand_check_block(cur_blk)) {
				cur_blk ++;  /* Bad block, set to next block */
				if (notify)
					notify(-2);
				continue;
			}
		}

		nand_cmd(CMD_ERASE_SETUP);

		rowaddr = cur_blk * ppb;
		for (i = 0; i < row; i++) {
			nand_addr(rowaddr & 0xff);
			rowaddr >>= 8;
		}

		nand_cmd(CMD_ERASE);
		nand_wait_ready();

		nand_cmd(CMD_READ_STATUS);
		nand_wait_ready();

		if (nand_data8() & 0x01) {
			/* Erase Error, mark it as bad block */
			nand_block_markbad(cur_blk);

			if (notify)
				notify(-1);
		} else {
			/* Erase OK */
			if (notify)
				notify(0);

			cnt++;
		}

		cur_blk++;		
	}

	return 0;
}


/*
 * Do nand hw ecc correction.
 */
static int nand_hw_ecc_correct(u8 *buf, u32 *stored_ecc, u32 *calc_ecc, int eccblock)
{
	u32 i, j, tmp, ecc_bit;
	int res = 0;

	for (i = 0; i < eccblock; i++) {
		tmp = stored_ecc[i] ^ calc_ecc[i];
		if (tmp) { /* ECC error */
			ecc_bit = 0;
			for (j = 0; j < 24; j++)
				if ((tmp >> j) & 0x01)
					ecc_bit ++;
			if (ecc_bit == 11) { /* Correctable error */
				u8 idx;

				ecc_bit = 0;
				for (j = 12; j >= 1; j--) {
					ecc_bit <<= 1;
					ecc_bit |= ((tmp >> (j*2-1)) & 0x01);
				}
				idx = ecc_bit & 0x07;

				buf[i * ECC_BLOCK + (ecc_bit >> 3)] ^= (1 << idx);
			}
			else { /* Fatal error */
				res = -1;
			}
		}
	}
	return res;
}

/*
 * Read data <pagenum> pages from <startpage> page.
 * Skip bad block if detected.
 * HW ECC is used.
 */
int nand_read_4730(void *buf, u32 startpage, u32 pagenum)
{
	u32 cnt, i, calc_ecc[8], *stored_ecc;
	u32 cur_page, rowaddr, eccblock, cur_blk;
	u8 *tmpbuf;

	eccblock = pagesize / ECC_BLOCK;

	cur_page = startpage;
	cnt = 0;
	while (cnt < pagenum) {
		/* If this is the first page of the block, check for bad. */
		if ((cur_page % ppb) == 0) {
			cur_blk = cur_page / ppb;
			if (nand_check_block(cur_blk)) {
				cur_page += ppb;   /* Bad block, set to next block */
				continue;
			}
		}

		nand_cmd(CMD_READA);
		nand_addr(0);
		if (pagesize == 2048)
			nand_addr(0);

		rowaddr = cur_page;
		for (i = 0; i < row; i++) {
			nand_addr(rowaddr & 0xff);
			rowaddr >>= 8;
		}

		if (pagesize == 2048)
			nand_cmd(CMD_CONFIRM);

		nand_wait_ready();

		tmpbuf = (u8 *)((u32)buf + cnt * pagesize);
		for (i = 0; i < eccblock; i++) {
			nand_ecc_enable();
			read_proc(tmpbuf, ECC_BLOCK);
			nand_ecc_disable();

			calc_ecc[i] = nand_ecc();
			tmpbuf += ECC_BLOCK;
		}
		read_proc((u8 *)oobbuf, oobsize);

		tmpbuf = (u8 *)((u32)buf + cnt * pagesize);
		stored_ecc = (u32 *)(((u32)oobbuf) + ECC_OFFSET);

		/* Check ECC */
		nand_hw_ecc_correct(tmpbuf, stored_ecc, calc_ecc, eccblock);

		cur_page++;
		cnt++;
	}

	return 0;
}

/*
 * Read data <pagenum> pages from <startpage> page.
 * Don't skip bad block.
 * Don't use HW ECC.
 */
int nand_read_raw_4730(void *buf, u32 startpage, u32 pagenum)
{
	u32 cnt, i;
	u32 cur_page, rowaddr;
	u8 *tmpbuf;

	tmpbuf = (u8 *)buf;

	cur_page = startpage;
	cnt = 0;
	while (cnt < pagenum) {
		nand_cmd(CMD_READA);
		nand_addr(0);
		if (pagesize == 2048)
			nand_addr(0);

		rowaddr = cur_page;
		for (i = 0; i < row; i++) {
			nand_addr(rowaddr & 0xff);
			rowaddr >>= 8;
		}

		if (pagesize == 2048)
			nand_cmd(CMD_CONFIRM);

		nand_wait_ready();

		read_proc(tmpbuf, pagesize);

		tmpbuf += pagesize;
		cur_page++;
		cnt++;
	}

	return 0;
}

/*
 * Read oob <pagenum> pages from <startpage> page.
 * Don't skip bad block.
 * Don't use HW ECC.
 */
int nand_read_oob_4730(void *buf, u32 startpage, u32 pagenum)
{
	u32 cnt, cur_page;
	u8 *tmpbuf;

	tmpbuf = (u8 *)buf;

	cur_page = startpage;
	cnt = 0;
	while (cnt < pagenum) {
		read_oob((void *)tmpbuf, oobsize, cur_page);

		tmpbuf += oobsize;
		cur_page++;
		cnt++;
	}

	return 0;
}

/*
 * Write <pagenum> pages from <startpage> page.
 * Skip bad block if detected.
 */
int nand_program_4730(void *buf, int startpage, int pagenum, void (*notify)(int))
{
	u32 cnt, i, *calc_ecc;
	u32 cur_page, rowaddr, eccblock, cur_blk;
	u8 *tmpbuf;

	tmpbuf = (u8 *)buf;

	eccblock = pagesize / ECC_BLOCK;

	cur_page = startpage;
	cnt = 0;
	while (cnt < pagenum) {
		/* If this is the first page of the block, check for bad. */
		if ((cur_page % ppb) == 0) {
			cur_blk = cur_page / ppb;
			if (nand_check_block(cur_blk)) {
				cur_page += ppb;   /* Bad block, set to next block */
				continue;
			}
		}

		nand_wait_ready();
		nand_cmd(CMD_READA);
		nand_cmd(CMD_SEQIN);

		nand_addr(0);
		if (pagesize == 2048)
			nand_addr(0);

		rowaddr = cur_page;
		for (i = 0; i < row; i++) {
			nand_addr(rowaddr & 0xff);
			rowaddr >>= 8;
		}

		/* Write out data */
		calc_ecc = (u32 *)(((u32)oobbuf) + ECC_OFFSET);
		for (i = 0; i < eccblock; i++) {
			nand_ecc_enable();
			write_proc(tmpbuf, ECC_BLOCK);
			nand_ecc_disable();
			calc_ecc[i] = nand_ecc();
			tmpbuf += ECC_BLOCK;
		}

		/* Write out oob including ECC */
		write_proc((u8 *)oobbuf, oobsize);

		nand_cmd(CMD_PGPROG);
		nand_wait_ready();

		nand_cmd(CMD_READ_STATUS);
		nand_wait_ready();

		if (nand_data8() & 0x01) {
			/* Page program error.
			 * Note: we should mark this block bad, and copy data of this
			 * block to a new block.
			 */
			if (notify)
				notify(-1);
		} else {
			if (notify)
				notify(0);
		}

		cur_page ++;
		cnt ++;
	}

	return 0;
}
