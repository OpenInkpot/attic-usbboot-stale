/*
 * i28f.c -- generic algorithm for Intel 28FXXX flash types.
 *           no buffer write support.
 *           e.g. 28F032B3.
 */

#include "flash.h"

/* i28f commands */
#define FLASH_Read_ID      FLASHWORD(info, 0x90)
#define FLASH_Read_Status  FLASHWORD(info, 0x70)
#define FLASH_Clear_Status FLASHWORD(info, 0x50)
#define FLASH_Status_Ready FLASHWORD(info, 0x80)
#define FLASH_Program      FLASHWORD(info, 0x40)
#define FLASH_Block_Erase  FLASHWORD(info, 0x20)
#define FLASH_Suspend      FLASHWORD(info, 0xB0)
#define FLASH_Resume       FLASHWORD(info, 0xD0)
#define FLASH_Confirm      FLASHWORD(info, 0xD0)
#define FLASH_Reset        FLASHWORD(info, 0xFF)

int i28f_query(flash_info_t *info)
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
		*(cp) = FLASH_Read_ID;
		break;
	case FLASH_CFI_16BIT:
		*(wp) = FLASH_Read_ID;
		break;
	case FLASH_CFI_32BIT:
		*(lp) = FLASH_Read_ID;
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

int i28f_write(flash_info_t *info, void *buf, void *addr, int len)
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
	u32 stat, timeout = 0x07ffffff;

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

	// Clear any error conditions
	switch (info->portwidth) {
	case FLASH_CFI_8BIT:
		*(cp) = FLASH_Clear_Status;
		break;
	case FLASH_CFI_16BIT:
		*(wp) = FLASH_Clear_Status;
		break;
	case FLASH_CFI_32BIT:
		*(lp) = FLASH_Clear_Status;
		break;
	}

	while (len >= info->portwidth) {
		// issue commands
		switch (info->portwidth) {
		case FLASH_CFI_8BIT:
			*(cp) = FLASH_Program;
			break;
		case FLASH_CFI_16BIT:
			*(wp) = FLASH_Program;
			break;
		case FLASH_CFI_32BIT:
			*(lp) = FLASH_Program;
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

		// check status
		stat = 0;
		timeout = WRITE_TIMEOUT;
		while((stat & FLASH_Status_Ready) != FLASH_Status_Ready) {
			if (--timeout == 0) break;
			switch (info->portwidth) {
			case FLASH_CFI_8BIT:
				stat = *cp;
				break;
			case FLASH_CFI_16BIT:
				stat = *wp;
				break;
			case FLASH_CFI_32BIT:
				stat = *lp;
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

	return i28f_write(info, (void *)&val, (void *)dst, info->portwidth);
}

int i28f_erase_chip(flash_info_t *info)
{
	return ERR_NOT_SUPPORT;
}

int i28f_erase_sector(flash_info_t *info, void *saddr, int size)
{
	volatile u8 *cp; // base addresses
	volatile u16 *wp;
	volatile u32 *lp;
	volatile u8 *cps; // sector addresses
	volatile u16 *wps;
	volatile u32 *lps;

	u32 sectsize = size;
	u32 stat, timeout = 0x07ffffff;

	// init pointers
	cp = (volatile u8 *)((u32)info->start);
	wp = (volatile u16 *)((u32)info->start);
	lp = (volatile u32 *)((u32)info->start);

	cps = (volatile u8 *)((u32)saddr);
	wps = (volatile u16 *)((u32)saddr);
	lps = (volatile u32 *)((u32)saddr);

	// Clear any error conditions
	switch (info->portwidth) {
	case FLASH_CFI_8BIT:
		*(cp) = FLASH_Clear_Status;
		break;
	case FLASH_CFI_16BIT:
		*(wp) = FLASH_Clear_Status;
		break;
	case FLASH_CFI_32BIT:
		*(lp) = FLASH_Clear_Status;
		break;
	}

	// issue commands
	switch (info->portwidth) {
	case FLASH_CFI_8BIT:
		*(cp) = FLASH_Block_Erase;
		*(cps) = FLASH_Confirm;
		break;
	case FLASH_CFI_16BIT:
		*(wp) = FLASH_Block_Erase;
		*(wps) = FLASH_Confirm;
		break;
	case FLASH_CFI_32BIT:
		*(lp) = FLASH_Block_Erase;
		*(lps) = FLASH_Confirm;
		break;
	}

	// check status
	stat = 0;
        timeout = ERASE_TIMEOUT;
        while((stat & FLASH_Status_Ready) != FLASH_Status_Ready) {
            if (--timeout == 0) break;
	    switch (info->portwidth) {
	    case FLASH_CFI_8BIT:
		    stat = *cp;
		    break;
	    case FLASH_CFI_16BIT:
		    stat = *wp;
		    break;
	    case FLASH_CFI_32BIT:
		    stat = *lp;
		    break;
	    }
	}

	// Restore to "normal" mode
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
