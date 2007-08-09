/*
 * nandflash_4740.c
 */

#include "nandflash.h"
#include "jz4740.h"

#define __nand_enable()		(REG_EMC_NFCSR |= EMC_NFCSR_NFE1 | EMC_NFCSR_NFCE1)
#define __nand_disable()	(REG_EMC_NFCSR &= ~(EMC_NFCSR_NFCE1))
#define __nand_ecc_rs_encoding()	(REG_EMC_NFECR = EMC_NFECR_ECCE | EMC_NFECR_ERST | EMC_NFECR_RS | EMC_NFECR_RS_ENCODING)
#define __nand_ecc_rs_decoding()	(REG_EMC_NFECR = EMC_NFECR_ECCE | EMC_NFECR_ERST | EMC_NFECR_RS | EMC_NFECR_RS_DECODING)
#define __nand_ecc_disable()	(REG_EMC_NFECR &= ~EMC_NFECR_ECCE)
#define __nand_ecc_encode_sync() while (!(REG_EMC_NFINTS & EMC_NFINTS_ENCF))
#define __nand_ecc_decode_sync() while (!(REG_EMC_NFINTS & EMC_NFINTS_DECF))

#define __nand_ready()		((REG_GPIO_PXPIN(2) & 0x40000000) ? 1 : 0)
#define __nand_ecc()		(REG_EMC_NFECC & 0x00ffffff)
#define __nand_cmd(n)		(REG8(cmdport) = (n))
#define __nand_addr(n)		(REG8(addrport) = (n))
#define __nand_data8()		REG8(dataport)
#define __nand_data16()		REG16(dataport)

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

#define OOB_BAD_OFF	0x00
#define OOB_ECC_OFF	0x04

#define OP_ERASE	0
#define OP_WRITE	1
#define OP_READ		2

#define ECC_BLOCK	512
#define ECC_POS	        6
#define PAR_SIZE        9

static volatile unsigned char *gpio_base;
static volatile unsigned char *emc_base;
static volatile unsigned char *addrport;
static volatile unsigned char *dataport;
static volatile unsigned char *cmdport;

static int bus = 8, row = 2, pagesize = 512, oobsize = 16, ppb = 32;
static u32 bad_block_pos = 0;
static u8 data_buf[2048] = {0};
static u8 oob_buf[128] = {0};


static inline void __nand_sync(void)
{
	unsigned int timeout = 100000;
	while ((REG_GPIO_PXPIN(2) & 0x40000000) && timeout--);
	while (!(REG_GPIO_PXPIN(2) & 0x40000000));
}

static int read_oob(void *buf, u32 size, u32 pg);
static int nand_data_write8(char *buf, int count);
static int nand_data_write16(char *buf, int count);
static int nand_data_read8(char *buf, int count);
static int nand_data_read16(char *buf, int count);

static int (*write_proc)(char *, int) = NULL;
static int (*read_proc)(char *, int) = NULL;

extern void dumpbuf(u8 *p, int count);

static nand_init_gpio(void)
{
	//modify this fun to a specifical borad
	//this fun init those gpio use by all flash chip
	//select the gpio function related to flash chip
	__gpio_as_nand();
}

void nand_enable_4740(unsigned int csn)
{
	//modify this fun to a specifical borad
	//this fun to enable the chip select pin csn
	//the choosn chip can work after this fun
	printf("\n Enable chip select :%d",csn);
	__nand_enable();
}

void nand_disable_4740(unsigned int csn)
{
	//modify this fun to a specifical borad
	//this fun to enable the chip select pin csn
	//the choosn chip can not work after this fun
	printf("\n Disable chip select :%d",csn);
	__nand_disable();
}

unsigned int nand_query_4740(void)
{
	u16 vid, did;

	__nand_sync();
	__nand_cmd(CMD_READID);
	__nand_addr(0);

	vid = __nand_data8();
	did = __nand_data8();

	return (vid << 16) | did;
}

int nand_init_4740(int bus_width, int row_cycle, int page_size, int page_per_block,
	      u32 gbase, u32 ebase, u32 aport, u32 dport, u32 cport)
{
	bus = bus_width;
	row = row_cycle;
	pagesize = page_size;
	oobsize = pagesize / 32;
	ppb = page_per_block;

	gpio_base = (u8 *)gbase;
	emc_base = (u8 *)ebase;
	addrport = (u8 *)aport;
	dataport = (u8 *)dport;
	cmdport = (u8 *)cport;

	/* Initialize NAND Flash Pins */
	//__gpio_as_nand();
	nand_init_gpio();

	//__nand_enable();

	if (bus == 8) {
		write_proc = nand_data_write8;
		read_proc = nand_data_read8;
	} else {
		write_proc = nand_data_write16;
		read_proc = nand_data_read16;
	}
	return 0;
}

int nand_fini_4740(void)
{
	__nand_disable();
	return 0;
}

/*
 * Read oob <pagenum> pages from <startpage> page.
 * Don't skip bad block.
 * Don't use HW ECC.
 */
int nand_read_oob_4740(void *buf, u32 startpage, u32 pagenum)
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

static int nand_check_block(u32 block)
{
	u32 pg;

	pg = block * ppb;

	read_oob(oob_buf, oobsize, pg);
	if (oob_buf[bad_block_pos] != 0xff)
		return 1;
	read_oob(oob_buf, oobsize, pg + 1);
	if (oob_buf[bad_block_pos] != 0xff)
		return 1;

	return 0;
}


/*
 * Read data <pagenum> pages from <startpage> page.
 * Don't skip bad block.
 * Don't use HW ECC.
 */
int nand_read_raw_4740(void *buf, u32 startpage, u32 pagenum)
{
	u32 cnt, j;
	u32 cur_page, rowaddr;
	u8 *tmpbuf;

	tmpbuf = (u8 *)buf;

	cur_page = startpage;
	cnt = 0;
	while (cnt < pagenum) {
		__nand_sync();
		__nand_cmd(CMD_READA);
		__nand_addr(0);
		if (pagesize == 2048)
			__nand_addr(0);

		rowaddr = cur_page;
		for (j = 0; j < row; j++) {
			__nand_addr(rowaddr & 0xff);
			rowaddr >>= 8;
		}

		if (pagesize == 2048)
			__nand_cmd(CMD_CONFIRM);

		__nand_sync();
		read_proc(tmpbuf, pagesize);

		tmpbuf += pagesize;
		cur_page++;
		cnt++;
	}

	return 0;
}


int nand_erase_4740(int blk_num, int sblk, int force, void (*notify)(int))
{
	int i, j;
	u32 cur, rowaddr;

	cur = sblk * ppb;
	for (i = 0; i < blk_num; i++) {
		rowaddr = cur;

		if (!force) {	/* if set, erase anything */
			/* test Badflag. */
			__nand_sync();

			__nand_cmd(CMD_READA);

			__nand_addr(0);
			if (pagesize == 2048)
				__nand_addr(0);
			for (j=0;j<row;j++) {
				__nand_addr(rowaddr & 0xff);
				rowaddr >>= 8;
			}

			if (pagesize == 2048)
				__nand_cmd(CMD_CONFIRM);

			__nand_sync();

			read_proc((u8 *)data_buf, pagesize);
			read_proc((u8 *)oob_buf, oobsize);

			if (oob_buf[0] != 0xff) { /* Bad block, skip */
				cur += ppb;
				if (notify)
					notify(-2);
				continue;
			}
			rowaddr = cur;
		}

		__nand_cmd(CMD_ERASE_SETUP);

		for (j = 0; j < row; j++) {
			__nand_addr(rowaddr & 0xff);
			rowaddr >>= 8;
		}
		__nand_cmd(CMD_ERASE);

		__nand_sync();

		__nand_cmd(CMD_READ_STATUS);

		if (__nand_data8() & 0x01) {
			if (notify)
				notify(-1);
		} else
			if (notify)
				notify(0);

		cur += ppb;
	}

	return 0;
}

static int read_oob(void *buf, u32 size, u32 pg)
{
	u32 i, coladdr, rowaddr;

	if (pagesize == 512)
		coladdr = 0;
	else
		coladdr = pagesize;

	if (pagesize == 512)
		/* Send READOOB command */
		__nand_cmd(CMD_READC);
	else
		/* Send READ0 command */
		__nand_cmd(CMD_READA);

	/* Send column address */
	__nand_addr(coladdr & 0xff);
	if (pagesize != 512)
		__nand_addr(coladdr >> 8);

	/* Send page address */
	rowaddr = pg;
	for (i = 0; i < row; i++) {
		__nand_addr(rowaddr & 0xff);
		rowaddr >>= 8;
	}

	/* Send READSTART command for 2048 ps NAND */
	if (pagesize != 512)
		__nand_cmd(CMD_CONFIRM);

	/* Wait for device ready */
	__nand_sync();

	/* Read oob data */
	read_proc(buf, size);

	return 0;
}

void rs_correct(unsigned char *buf, int idx, int mask)
{
	int i, j;
	unsigned short d, d1, dm;

	i = (idx * 9) >> 3;
	j = (idx * 9) & 0x7;

	i = (j == 0) ? (i - 1) : i;
	j = (j == 0) ? 7 : (j - 1);

	d = (buf[i] << 8) | buf[i - 1];

	d1 = (d >> j) & 0x1ff;
	d1 ^= mask;

	dm = ~(0x1ff << j);
	d = (d & dm) | (d1 << j);

	buf[i - 1] = d & 0xff;
	buf[i] = (d >> 8) & 0xff;
}

 /*
 * Read data <pagenum> pages from <startpage> page.
 * Skip bad block if detected.
 * HW ECC is used.
 */
int nand_read_4740(void *buf, u32 startpage, u32 pagenum)
{
	u32 j, k;
	u32 cur_page, cur_blk, cnt, rowaddr, ecccnt;
	u8 *tmpbuf,*p;
	ecccnt = pagesize / ECC_BLOCK;
	
	cur_page = startpage;
	cnt = 0;
	while (cnt < pagenum) {
		/* If this is the first page of the block, check for bad. */
		if ((cur_page % ppb) == 0) {
			cur_blk = cur_page / ppb;
			if (nand_check_block(cur_blk)) {
				cur_page += ppb;   // Bad block, set to next block 
				continue;
			}
		}
	
		/* read oob first */
		read_oob(oob_buf, oobsize, cur_page);

		__nand_sync();
		__nand_cmd(CMD_READA);

		__nand_addr(0);
		if (pagesize == 2048)
			__nand_addr(0);

		rowaddr = cur_page;
		for (j = 0; j < row; j++) {
			__nand_addr(rowaddr & 0xff);
			rowaddr >>= 8;
		}

		if (pagesize == 2048)
			__nand_cmd(CMD_CONFIRM);

		__nand_sync();
		
		tmpbuf = (u8 *)data_buf;

		for (j = 0; j < ecccnt; j++) {
			volatile u8 *paraddr = (volatile u8 *)EMC_NFPAR0;
			u32 stat;

			/* Read data */
			REG_EMC_NFINTS = 0x0;
			__nand_ecc_rs_decoding();
		
			read_proc(tmpbuf, ECC_BLOCK);

			/* Set PAR values */
			for (k = 0; k < PAR_SIZE; k++) {
				*paraddr++ = oob_buf[ECC_POS + j*PAR_SIZE + k];
			}

			/* Set PRDY */
			REG_EMC_NFECR |= EMC_NFECR_PRDY;

			/* Wait for completion */
			__nand_ecc_decode_sync();
			__nand_ecc_disable();

			/* Check decoding */
			stat = REG_EMC_NFINTS;
		
			if (stat & EMC_NFINTS_ERR) {
				//printf("Error occurred\n");
				if (stat & EMC_NFINTS_UNCOR) {
					//printf("Uncorrectable error occurred\n");
				}
				else {
					u32 errcnt = (stat & EMC_NFINTS_ERRCNT_MASK) >> EMC_NFINTS_ERRCNT_BIT;
					switch (errcnt) {
					case 4:
						rs_correct(data_buf, (REG_EMC_NFERR3 & EMC_NFERR_INDEX_MASK) >> EMC_NFERR_INDEX_BIT, (REG_EMC_NFERR3 & EMC_NFERR_MASK_MASK) >> EMC_NFERR_MASK_BIT);
					case 3:
						rs_correct(data_buf, (REG_EMC_NFERR2 & EMC_NFERR_INDEX_MASK) >> EMC_NFERR_INDEX_BIT, (REG_EMC_NFERR2 & EMC_NFERR_MASK_MASK) >> EMC_NFERR_MASK_BIT);
					case 2:
						rs_correct(data_buf, (REG_EMC_NFERR1 & EMC_NFERR_INDEX_MASK) >> EMC_NFERR_INDEX_BIT, (REG_EMC_NFERR1 & EMC_NFERR_MASK_MASK) >> EMC_NFERR_MASK_BIT);
					case 1:
						rs_correct(data_buf, (REG_EMC_NFERR0 & EMC_NFERR_INDEX_MASK) >> EMC_NFERR_INDEX_BIT, (REG_EMC_NFERR0 & EMC_NFERR_MASK_MASK) >> EMC_NFERR_MASK_BIT);
						break;
					default:
						break;
					}
				
				}
			}
			/* increment pointer */
			tmpbuf += ECC_BLOCK;
		}

		tmpbuf = (u8 *)((u32)buf + cnt * pagesize);
		p = (u8 *)data_buf;
		for (j = 0; j < pagesize; j++)
			tmpbuf[j] = p[j];
		cur_page++;
		cnt++;
	}
	return 0;
}

int nand_program_4740(void *context, int spage, int pages, void (*notify)(int))
{
	u32 i, j, cur, rowaddr;
	u8 *tmpbuf;
	u32 ecccnt;
	u8 ecc_buf[64];

	//printf("nand_program %d %d\n", spage, pages);

	tmpbuf = (u8 *)context;
	ecccnt = pagesize / ECC_BLOCK;

	i = 0;
	cur = spage;

	while (i < pages) {
		if ((cur % ppb) == 0) { /* First page of block, test BAD. */

			read_oob(oob_buf, oobsize, cur);
			if (oob_buf[0] != 0xff) { /* Bad block, skip */
				//printf("Bad block\n");
				cur += ppb;
				if (notify)
					notify(-2);
				continue;
			}
			rowaddr = cur;
		}
		
		__nand_sync();
		if (pagesize != 2048)
			__nand_cmd(CMD_READA);

		__nand_cmd(CMD_SEQIN);

		__nand_addr(0);
		if (pagesize == 2048)
			__nand_addr(0);
		rowaddr = cur;
		for (j = 0; j < row; j++) {
			__nand_addr(rowaddr & 0xff);
			rowaddr >>= 8;
		}

		/* write out data */
		for (j = 0; j < ecccnt; j++) {
			volatile u8 *paraddr = (volatile u8 *)EMC_NFPAR0;
			int k;

			__nand_ecc_rs_encoding();
			write_proc(tmpbuf, ECC_BLOCK);
			__nand_ecc_encode_sync();
			__nand_ecc_disable();

			/* Read PAR values */
			for (k = 0; k < PAR_SIZE; k++) {
				ecc_buf[j*PAR_SIZE+k] = *paraddr++;
			}

			tmpbuf += ECC_BLOCK;
		}

		/* Init oob buffer */
		for (j = 0; j < oobsize; j++) {
			oob_buf[j] = 0xff;
		}

		for (j = 0; j < ecccnt*PAR_SIZE; j++) {
			oob_buf[ECC_POS + j] = ecc_buf[j];
		}

		/* Set page valid flag */
		oob_buf[2] = 0;
		oob_buf[3] = 0;
		oob_buf[4] = 0;

		/* write out oob buffer */
		write_proc((u8 *)oob_buf, oobsize);

		/* send program confirm command */
		__nand_cmd(CMD_PGPROG);
		__nand_sync();

		__nand_cmd(CMD_READ_STATUS);
		__nand_sync();

		if (__nand_data8() & 0x01) { /* page program error */
			if (notify)
				notify(-1);
		} else
			if (notify)
				notify(0);

		i ++;
		cur ++;
	}
	return 0;
}

static int nand_data_write8(char *buf, int count)
{
	int i;
	u8 *p = (u8 *)buf;
	for (i=0;i<count;i++)
		__nand_data8() = *p++;
	return 0;
}

static int nand_data_write16(char *buf, int count)
{
	int i;
	u16 *p = (u16 *)buf;
	for (i=0;i<count/2;i++)
		__nand_data16() = *p++;
	return 0;
}

static int nand_data_read8(char *buf, int count)
{
	int i;
	u8 *p = (u8 *)buf;
	for (i=0;i<count;i++)
		*p++ = __nand_data8();
	return 0;
}

static int nand_data_read16(char *buf, int count)
{
	int i;
	u16 *p = (u16 *)buf;
	for (i=0;i<count/2;i++)
		*p++ = __nand_data16();
	return 0;
}

