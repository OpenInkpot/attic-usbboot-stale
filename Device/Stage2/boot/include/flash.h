#ifndef __FLASH_H__
#define __FLASH_H__

#include "flash_info.h"
#include "error.h"

/*-----------------------------------------------------------------------
 * Timeout and delay
 */
#define ERASE_TIMEOUT  0x07ffffff
#define WRITE_TIMEOUT  0x07ffffff

#define DELAY(x)		\
do {				\
	u32 i = x;		\
	while (i--);		\
} while(0)

/*-----------------------------------------------------------------------
 * define the flashword macro
 */
#define FLASHWORD(info, v) 				\
({ 							\
	unsigned int ret = 0;				\
	switch (info->portwidth) {			\
	case FLASH_CFI_8BIT:				\
			ret = v;			\
			break;				\
		break;					\
	case FLASH_CFI_16BIT:				\
		switch (info->chipwidth) {		\
		case FLASH_CFI_BY8:			\
			ret = v + (v<<8);		\
			break;				\
		case FLASH_CFI_BY16:			\
			ret = v;			\
			break;				\
		}					\
		break;					\
	case FLASH_CFI_32BIT:				\
		switch (info->chipwidth) {		\
		case FLASH_CFI_BY8:			\
			ret = v+(v<<8)+(v<<16)+(v<<24);	\
			break;				\
		case FLASH_CFI_BY16:			\
			ret = v + (v<<16);		\
			break;				\
		case FLASH_CFI_BY32:			\
			ret = v;			\
			break;				\
		}					\
		break;					\
	}						\
	ret;						\
})

#define __swab16(x) \
	((u16)( \
		(((u16)(x) & (u16)0x00ffU) << 8) | \
		(((u16)(x) & (u16)0xff00U) >> 8) ))
#define __swab32(x) \
	((u32)( \
		(((u32)(x) & (u32)0x000000ffUL) << 24) | \
		(((u32)(x) & (u32)0x0000ff00UL) <<  8) | \
		(((u32)(x) & (u32)0x00ff0000UL) >>  8) | \
		(((u32)(x) & (u32)0xff000000UL) >> 24) ))

#define find_sector(info, addr)				\
({							\
	u32 sect = 0;					\
	for (sect = info->sector_count - 1; 		\
		     sect >= 0; sect--) { 		\
		if (addr >= info->sector_start[sect])	\
			break;				\
	}						\
	sect;						\
})

/*
 * NOR Flash Operations
 */
extern int flash_init(flash_info_t *info);

//extern int (*flash_init)(flash_info_t *info);
extern int (*flash_query)(flash_info_t *info);
extern int (*flash_write)(flash_info_t *info, void *buf, void *addr, int len);
extern int (*flash_erase_chip)(flash_info_t *info);
extern int (*flash_erase_sector)(flash_info_t *info, void *saddr, int size);

extern int cfi_init(flash_info_t *info);
extern int cfi_write(flash_info_t *info, void *buf, void *addr, int len);
extern int cfi_erase_chip(flash_info_t *info);
extern int cfi_erase_sector(flash_info_t *info, void *saddr, int size);

extern int sst28_init(flash_info_t *info);
extern int sst28_write(flash_info_t *info, void *buf, void *addr, int len);
extern int sst28_erase_chip(flash_info_t *info);
extern int sst28_erase_sector(flash_info_t *info, void *saddr, int size);

extern int sst39x8_init(flash_info_t *info);
extern int sst39x8_write(flash_info_t *info, void *buf, void *addr, int len);
extern int sst39x8_erase_chip(flash_info_t *info);
extern int sst39x8_erase_sector(flash_info_t *info, void *saddr, int size);

extern int sst39x16_init(flash_info_t *info);
extern int sst39x16_write(flash_info_t *info, void *buf, void *addr, int len);
extern int sst39x16_erase_chip(flash_info_t *info);
extern int sst39x16_erase_sector(flash_info_t *info, void *saddr, int size);

extern int am29_query(flash_info_t *info);
extern int am29_write(flash_info_t *info, void *buf, void *addr, int len);
extern int am29_erase_chip(flash_info_t *info);
extern int am29_erase_sector(flash_info_t *info, void *saddr, int size);

extern int i28f_query(flash_info_t *info);
extern int i28f_write(flash_info_t *info, void *buf, void *addr, int len);
extern int i28f_erase_chip(flash_info_t *info);
extern int i28f_erase_sector(flash_info_t *info, void *saddr, int size);

extern int i28fl_query(flash_info_t *info);
extern int i28fl_write(flash_info_t *info, void *buf, void *addr, int len);
extern int i28fl_erase_chip(flash_info_t *info);
extern int i28fl_erase_sector(flash_info_t *info, void *saddr, int size);

/*
 * NAND flash operations
 */
 /*
extern int nand_init(int, int, int, int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int);
extern unsigned int nand_query(void);
extern int nand_program(void *, int, int, void (*notify)(int));
extern int nand_erase(int, int, int, void (*notify)(int));
extern int nand_fini(void);
extern int nand_read(void *, unsigned int, unsigned int);
extern int nand_read_raw(void *, unsigned int, unsigned int);
extern int nand_read_oob(void *, unsigned int, unsigned int);
*/

/* status routine */
extern void status(const char *str);

#endif /* __FLASH_H__ */
