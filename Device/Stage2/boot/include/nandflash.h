#ifndef __NANDLIB_H__
#define __NANDLIB_H__

#ifndef NULL
#define NULL	0
#endif

#define u8	unsigned char
#define u16	unsigned short
#define u32	unsigned int

#ifdef __cplusplus
extern "C" {
#endif
/*  Jz4740 nandflash interface */
unsigned int nand_query_4740(void);
int nand_init_4740(int bus_width, int row_cycle, int page_size, int page_per_block,
	      u32 gbase, u32 ebase, u32 aport, u32 dport, u32 cport);
int nand_fini_4740(void);
int nand_program_4740(void *context, int spage, int pages, void (*notify)(int));
int nand_erase_4740(int blk_num, int sblk, int force, void (*notify)(int));
int nand_read_4740(void *buf, u32 startpage, u32 pagenum);
int nand_read_oob_4740(void *buf, u32 startpage, u32 pagenum);
int nand_read_raw_4740(void *buf, u32 startpage, u32 pagenum);
void nand_enable_4740(u32 csn);
void nand_disable_4740(u32 csn);

/*  Jz4730 nandflash interface */
int nand_init_4730(int bus_width, int row_cycle, int page_size, int page_per_block,
	      u32 ebase, u32 aport, u32 dport, u32 cport);
int nand_fini_4730(void);
unsigned int nand_query_4730(void);
int nand_erase_4730(int blk_num, int sblk, int force, void (*notify)(int));
int nand_program_4730(void *buf, int startpage, int pagenum, void (*notify)(int));
int nand_read_4730(void *buf, u32 startpage, u32 pagenum);
int nand_read_raw_4730(void *buf, u32 startpage, u32 pagenum);
int nand_read_oob_4730(void *buf, u32 startpage, u32 pagenum);
#ifdef __cplusplus
}
#endif

#endif
