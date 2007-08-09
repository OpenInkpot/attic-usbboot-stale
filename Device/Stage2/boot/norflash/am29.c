/*
 * am29.c -- generic algorithm for AM29 flash types.
 *           e.g. AM29F010, AM29F800B, AM29PDL128G
 *                AT49BV040, AT49BV1614 etc.
 */

#include "flash.h"

/* setup addresses */
#define FLASH_Setup_Addr1               (info->setup_addr1)
#define FLASH_Setup_Addr2               (info->setup_addr2)

/* am29 commands */
#define FLASH_Read_ID                   FLASHWORD(info, 0x90)
#define FLASH_Reset                     FLASHWORD(info, 0xF0)
#define FLASH_Program                   FLASHWORD(info, 0xA0)
#define FLASH_Sector_Erase              FLASHWORD(info, 0x30)
#define FLASH_Chip_Erase                FLASHWORD(info, 0x10)
#define FLASH_Setup_Code1               FLASHWORD(info, 0xAA)
#define FLASH_Setup_Code2               FLASHWORD(info, 0x55)
#define FLASH_Setup_Erase               FLASHWORD(info, 0x80)

#define FLASH_Status_Ready 		FLASHWORD(info, 0x80)
#define FLASH_Toggle_Bit 		FLASHWORD(info, 0x40)

int am29_query(flash_info_t *info)
{
	volatile u8 *cp; // base addresses
	volatile u16 *wp;
	volatile u32 *lp;
	u32 vend = 0, prod = 0;

	// init pointers
	cp = (volatile u8 *)((u32)info->start);
	wp = (volatile u16 *)((u32)info->start);
	lp = (volatile u32 *)((u32)info->start);

	// issue read_id command
	switch (info->portwidth) {
	case FLASH_CFI_8BIT:
		*(cp + FLASH_Setup_Addr1) = FLASH_Setup_Code1;
		*(cp + FLASH_Setup_Addr2) = FLASH_Setup_Code2;
		*(cp + FLASH_Setup_Addr1) = FLASH_Read_ID;
		break;
	case FLASH_CFI_16BIT:
		*(wp + FLASH_Setup_Addr1) = FLASH_Setup_Code1;
		*(wp + FLASH_Setup_Addr2) = FLASH_Setup_Code2;
		*(wp + FLASH_Setup_Addr1) = FLASH_Read_ID;
		break;
	case FLASH_CFI_32BIT:
		*(lp + FLASH_Setup_Addr1) = FLASH_Setup_Code1;
		*(lp + FLASH_Setup_Addr2) = FLASH_Setup_Code2;
		*(lp + FLASH_Setup_Addr1) = FLASH_Read_ID;
		break;
	}

	// read back ids
	switch (info->portwidth) {
	case FLASH_CFI_8BIT:
		vend = *(cp + 0);
		prod = *(cp + 1);
		break;
	case FLASH_CFI_16BIT:
		vend = *(wp + 0);
		prod = *(wp + 1);
		break;
	case FLASH_CFI_32BIT:
		vend = *(lp + 0);
		prod = *(lp + 1);
		break;
	}

	info->flash_id = ((vend & 0xffff) << 16) | (prod & 0xffff);

	// issue exit read_id command
	switch (info->portwidth) {
	case FLASH_CFI_8BIT:
		*(cp) = FLASH_Reset;
		break;
	case FLASH_CFI_16BIT:
		*(wp) = FLASH_Reset;
		break;
	case FLASH_CFI_32BIT:
		*(lp) = FLASH_Reset;
		break;
	}

	return ERR_OK;
}

int am29_write(flash_info_t *info, void *buf, void *addr, int len)
{
	volatile u8 *cp; // base addresses
	volatile u16 *wp;
	volatile u32 *lp;
	volatile u8 *cps; // src addresses
	volatile u16 *wps;
	volatile u32 *lps;
	volatile u8 *cpd; // dst addresses
	volatile u16 *wpd;
	volatile u32 *lpd;

	u32 src, dst, val, i;
	u32 cur = 0, pre = 0, timeout = 0x07ffffff;

	// init pointers
	cp = (volatile u8 *)((u32)info->start);
	wp = (volatile u16 *)((u32)info->start);
	lp = (volatile u32 *)((u32)info->start);

	src = (u32)buf;
	cps = (volatile u8 *)src;
	wps = (volatile u16 *)src;
	lps = (volatile u32 *)src;

	dst = (u32)addr;
	cpd = (volatile u8 *)dst;
	wpd = (volatile u16 *)dst;
	lpd = (volatile u32 *)dst;

	// reset the device
	switch (info->portwidth) {
	case FLASH_CFI_8BIT:
		*(cp) = FLASH_Reset;
		break;
	case FLASH_CFI_16BIT:
		*(wp) = FLASH_Reset;
		break;
	case FLASH_CFI_32BIT:
		*(lp) = FLASH_Reset;
		break;
	}

	while (len >= info->portwidth) {
		// issue commands
		switch (info->portwidth) {
		case FLASH_CFI_8BIT:
			*(cp + FLASH_Setup_Addr1) = FLASH_Setup_Code1;
			*(cp + FLASH_Setup_Addr2) = FLASH_Setup_Code2;
			*(cp + FLASH_Setup_Addr1) = FLASH_Program;
			break;
		case FLASH_CFI_16BIT:
			*(wp + FLASH_Setup_Addr1) = FLASH_Setup_Code1;
			*(wp + FLASH_Setup_Addr2) = FLASH_Setup_Code2;
			*(wp + FLASH_Setup_Addr1) = FLASH_Program;
			break;
		case FLASH_CFI_32BIT:
			*(lp + FLASH_Setup_Addr1) = FLASH_Setup_Code1;
			*(lp + FLASH_Setup_Addr2) = FLASH_Setup_Code2;
			*(lp + FLASH_Setup_Addr1) = FLASH_Program;
			break;
		}

		// write data
		switch (info->portwidth) {
		case FLASH_CFI_8BIT:
			*cpd = *cps;
			break;
		case FLASH_CFI_16BIT:
			*wpd = *wps;
			break;
		case FLASH_CFI_32BIT:
			*lpd = *lps;
			break;
		}

		// check toggle bit
		switch (info->portwidth) {
		case FLASH_CFI_8BIT:
			cur = *(cpd) & FLASH_Toggle_Bit;
			break;
		case FLASH_CFI_16BIT:
			cur = *(wpd) & FLASH_Toggle_Bit;
			break;
		case FLASH_CFI_32BIT:
			cur = *(lpd) & FLASH_Toggle_Bit;
			break;
		}
		pre = ~cur;
		timeout = WRITE_TIMEOUT;
		while (timeout-- > 0) {
			if (pre == cur)
				break;
			pre = cur;
			switch (info->portwidth) {
			case FLASH_CFI_8BIT:
				cur = *(cpd) & FLASH_Toggle_Bit;
				break;
			case FLASH_CFI_16BIT:
				cur = *(wpd) & FLASH_Toggle_Bit;
				break;
			case FLASH_CFI_32BIT:
				cur = *(lpd) & FLASH_Toggle_Bit;
				break;
			}
		}

		// reset the device
		switch (info->portwidth) {
		case FLASH_CFI_8BIT:
			*(cp) = FLASH_Reset;
			break;
		case FLASH_CFI_16BIT:
			*(wp) = FLASH_Reset;
			break;
		case FLASH_CFI_32BIT:
			*(lp) = FLASH_Reset;
			break;
		}

		// program timeout
		if (timeout == 0)
			return ERR_TIMOUT;

		// verify data - also increment pointers
		switch (info->portwidth) {
		case FLASH_CFI_8BIT:
			if (*cpd++ != *cps++)
				return ERR_WRITE_VERIFY;
			break;
		case FLASH_CFI_16BIT:
			if (*wpd++ != *wps++)
				return ERR_WRITE_VERIFY;
			break;
		case FLASH_CFI_32BIT:
			if (*lpd++ != *lps++)
				return ERR_WRITE_VERIFY;
			break;
		}

		// decrement data length
		src += info->portwidth;
		dst += info->portwidth;
		len -= info->portwidth;
	}

	// reset the device
	switch (info->portwidth) {
	case FLASH_CFI_8BIT:
		*(cp) = FLASH_Reset;
		break;
	case FLASH_CFI_16BIT:
		*(wp) = FLASH_Reset;
		break;
	case FLASH_CFI_32BIT:
		*(lp) = FLASH_Reset;
		break;
	}

	if (len == 0) {
		return ERR_OK;
	}

	/*
	 * handle unaligned tail bytes
	 */
	cps = (volatile u8 *)src;
	cpd = (volatile u8 *)dst;
	val = 0;
	for (i = 0; (i < info->portwidth) && (len > 0); i++) {
		val |= (*cps++ << (i*8));
		len--;
	}
	for (; i < info->portwidth; i++) {
		val |= (*(cpd + i) << (i*8));
	}

	return am29_write(info, (void *)&val, (void *)dst, info->portwidth);
}

int am29_erase_chip(flash_info_t *info)
{
	volatile u8 *cp; // base addresses
	volatile u16 *wp;
	volatile u32 *lp;

	u32 chipsize = info->chipsize;
	u32 cur = 0, pre = 0, timeout = 0x07ffffff;

	// init pointers
	cp = (volatile u8 *)((u32)info->start);
	wp = (volatile u16 *)((u32)info->start);
	lp = (volatile u32 *)((u32)info->start);

	// reset the device
	switch (info->portwidth) {
	case FLASH_CFI_8BIT:
		*(cp) = FLASH_Reset;
		break;
	case FLASH_CFI_16BIT:
		*(wp) = FLASH_Reset;
		break;
	case FLASH_CFI_32BIT:
		*(lp) = FLASH_Reset;
		break;
	}

	// issue commands
	switch (info->portwidth) {
	case FLASH_CFI_8BIT:
		*(cp + FLASH_Setup_Addr1) = FLASH_Setup_Code1;
		*(cp + FLASH_Setup_Addr2) = FLASH_Setup_Code2;
		*(cp + FLASH_Setup_Addr1) = FLASH_Setup_Erase;
		*(cp + FLASH_Setup_Addr1) = FLASH_Setup_Code1;
		*(cp + FLASH_Setup_Addr2) = FLASH_Setup_Code2;
		*(cp + FLASH_Setup_Addr1) = FLASH_Chip_Erase;
		break;
	case FLASH_CFI_16BIT:
		*(wp + FLASH_Setup_Addr1) = FLASH_Setup_Code1;
		*(wp + FLASH_Setup_Addr2) = FLASH_Setup_Code2;
		*(wp + FLASH_Setup_Addr1) = FLASH_Setup_Erase;
		*(wp + FLASH_Setup_Addr1) = FLASH_Setup_Code1;
		*(wp + FLASH_Setup_Addr2) = FLASH_Setup_Code2;
		*(wp + FLASH_Setup_Addr1) = FLASH_Chip_Erase;
		break;
	case FLASH_CFI_32BIT:
		*(lp + FLASH_Setup_Addr1) = FLASH_Setup_Code1;
		*(lp + FLASH_Setup_Addr2) = FLASH_Setup_Code2;
		*(lp + FLASH_Setup_Addr1) = FLASH_Setup_Erase;
		*(lp + FLASH_Setup_Addr1) = FLASH_Setup_Code1;
		*(lp + FLASH_Setup_Addr2) = FLASH_Setup_Code2;
		*(lp + FLASH_Setup_Addr1) = FLASH_Chip_Erase;
		break;
	}

	// check toggle bit
	switch (info->portwidth) {
	case FLASH_CFI_8BIT:
		cur = *(cp) & FLASH_Toggle_Bit;
		break;
	case FLASH_CFI_16BIT:
		cur = *(wp) & FLASH_Toggle_Bit;
		break;
	case FLASH_CFI_32BIT:
		cur = *(lp) & FLASH_Toggle_Bit;
		break;
	}
	pre = ~cur;
	timeout = ERASE_TIMEOUT;
	while (timeout-- > 0) {
		if (pre == cur)
			break;
		pre = cur;
		switch (info->portwidth) {
		case FLASH_CFI_8BIT:
			cur = *(cp) & FLASH_Toggle_Bit;
			break;
		case FLASH_CFI_16BIT:
			cur = *(wp) & FLASH_Toggle_Bit;
			break;
		case FLASH_CFI_32BIT:
			cur = *(lp) & FLASH_Toggle_Bit;
			break;
		}
	}

	// reset the device
	switch (info->portwidth) {
	case FLASH_CFI_8BIT:
		*(cp) = FLASH_Reset;
		break;
	case FLASH_CFI_16BIT:
		*(wp) = FLASH_Reset;
		break;
	case FLASH_CFI_32BIT:
		*(lp) = FLASH_Reset;
		break;
	}

	// erase timeout
	if (timeout == 0)
		return ERR_TIMOUT;

	// check if erasing passed?
	while (chipsize > 0) {
		switch (info->portwidth) {
		case FLASH_CFI_8BIT:
			if (*cp++ != 0xff)
				return ERR_ERASE_ERROR;
			break;
		case FLASH_CFI_16BIT:
			if (*wp++ != 0xffff)
				return ERR_ERASE_ERROR;
			break;
		case FLASH_CFI_32BIT:
			if (*lp++ != 0xffffffff)
				return ERR_ERASE_ERROR;
			break;
		}
		chipsize -= info->portwidth;
	}

	return ERR_OK;
}

int am29_erase_sector(flash_info_t *info, void *saddr, int size)
{
	volatile u8 *cp; // base addresses
	volatile u16 *wp;
	volatile u32 *lp;
	volatile u8 *cps; // sector addresses
	volatile u16 *wps;
	volatile u32 *lps;

	u32 sectsize = size;
	u32 cur = 0, pre = 0, timeout = 0x07ffffff;

	// init pointers
	cp = (volatile u8 *)((u32)info->start);
	wp = (volatile u16 *)((u32)info->start);
	lp = (volatile u32 *)((u32)info->start);

	cps = (volatile u8 *)((u32)saddr);
	wps = (volatile u16 *)((u32)saddr);
	lps = (volatile u32 *)((u32)saddr);

	// reset the device
	switch (info->portwidth) {
	case FLASH_CFI_8BIT:
		*(cp) = FLASH_Reset;
		break;
	case FLASH_CFI_16BIT:
		*(wp) = FLASH_Reset;
		break;
	case FLASH_CFI_32BIT:
		*(lp) = FLASH_Reset;
		break;
	}

	// issue commands
	switch (info->portwidth) {
	case FLASH_CFI_8BIT:
		*(cp + FLASH_Setup_Addr1) = FLASH_Setup_Code1;
		*(cp + FLASH_Setup_Addr2) = FLASH_Setup_Code2;
		*(cp + FLASH_Setup_Addr1) = FLASH_Setup_Erase;
		*(cp + FLASH_Setup_Addr1) = FLASH_Setup_Code1;
		*(cp + FLASH_Setup_Addr2) = FLASH_Setup_Code2;
		*(cps) = FLASH_Sector_Erase;
		break;
	case FLASH_CFI_16BIT:
		*(wp + FLASH_Setup_Addr1) = FLASH_Setup_Code1;
		*(wp + FLASH_Setup_Addr2) = FLASH_Setup_Code2;
		*(wp + FLASH_Setup_Addr1) = FLASH_Setup_Erase;
		*(wp + FLASH_Setup_Addr1) = FLASH_Setup_Code1;
		*(wp + FLASH_Setup_Addr2) = FLASH_Setup_Code2;
		*(wps) = FLASH_Sector_Erase;
		break;
	case FLASH_CFI_32BIT:
		*(lp + FLASH_Setup_Addr1) = FLASH_Setup_Code1;
		*(lp + FLASH_Setup_Addr2) = FLASH_Setup_Code2;
		*(lp + FLASH_Setup_Addr1) = FLASH_Setup_Erase;
		*(lp + FLASH_Setup_Addr1) = FLASH_Setup_Code1;
		*(lp + FLASH_Setup_Addr2) = FLASH_Setup_Code2;
		*(lps) = FLASH_Sector_Erase;
		break;
	}

	// check toggle bit
	switch (info->portwidth) {
	case FLASH_CFI_8BIT:
		cur = *(cps) & FLASH_Toggle_Bit;
		break;
	case FLASH_CFI_16BIT:
		cur = *(wps) & FLASH_Toggle_Bit;
		break;
	case FLASH_CFI_32BIT:
		cur = *(lps) & FLASH_Toggle_Bit;
		break;
	}
	pre = ~cur;
	timeout = ERASE_TIMEOUT;
	while (timeout-- > 0) {
		if (pre == cur)
			break;
		pre = cur;
		switch (info->portwidth) {
		case FLASH_CFI_8BIT:
			cur = *(cps) & FLASH_Toggle_Bit;
			break;
		case FLASH_CFI_16BIT:
			cur = *(wps) & FLASH_Toggle_Bit;
			break;
		case FLASH_CFI_32BIT:
			cur = *(lps) & FLASH_Toggle_Bit;
			break;
		}
	}

	// reset the device
	switch (info->portwidth) {
	case FLASH_CFI_8BIT:
		*(cp) = FLASH_Reset;
		break;
	case FLASH_CFI_16BIT:
		*(wp) = FLASH_Reset;
		break;
	case FLASH_CFI_32BIT:
		*(lp) = FLASH_Reset;
		break;
	}

	// erase timeout
	if (timeout == 0)
		return ERR_TIMOUT;

	// check if erasing passed?
	while (sectsize > 0) {
		switch (info->portwidth) {
		case FLASH_CFI_8BIT:
			if (*cps++ != 0xff)
				return ERR_ERASE_ERROR;
			break;
		case FLASH_CFI_16BIT:
			if (*wps++ != 0xffff)
				return ERR_ERASE_ERROR;
			break;
		case FLASH_CFI_32BIT:
			if (*lps++ != 0xffffffff)
				return ERR_ERASE_ERROR;
			break;
		}
		sectsize -= info->portwidth;
	}

	return ERR_OK;
}
