/*
 * i28fl.c -- generic algorithm for Intel 28FXXX flash types.
 *           support lock/unlock sectores.
 *           no buffer write support.
 *           e.g. 28F032B3.
 */

#include "flash.h"

#define FLASH_Read_ID                  0x90
#define FLASH_Reset                    0xFF 
#define FLASH_Program                  0x40
#define FLASH_Write_Buffer             0xe8
#define FLASH_Block_Erase              0x20
#define FLASH_Confirm                  0xD0
#define FLASH_Resume                   0xD0 

#define FLASH_Set_Lock                 0x60
#define FLASH_Set_Lock_Confirm         0x01
#define FLASH_Clear_Lock               0x60 
#define FLASH_Clear_Lock_Confirm       0xd0

#define FLASH_Read_Status              0x70
#define FLASH_Clear_Status             0x50 
#define FLASH_Status_Ready             0x80

// Status that we read back:             
#define FLASH_ErrorMask                0x7E 
#define FLASH_ErrorProgram             0x10
#define FLASH_ErrorErase               0x20
#define FLASH_ErrorLock                0x30
#define FLASH_ErrorLowVoltage          0x08
#define FLASH_ErrorLocked              0x02

// Error flags
#define FLASH_ERR_HWR          0
#define FLASH_ERR_LOW_VOLTAGE  1
#define FLASH_ERR_PROTECT      2
#define FLASH_ERR_ERASE        3
#define FLASH_ERR_DRV_TIMEOUT  4
#define FLASH_ERR_PROGRAM      5

int i28fl_query(flash_info_t *info)
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

static int _i28fl_erase_sector(u32 Sector)
{
	int timeout, res; 
	u16 stat;

	*(volatile u16 *)0xbc000000 = FLASH_Clear_Status;
	*(volatile u16 *)0xbc000000 = FLASH_Block_Erase;
	*(volatile u16 *)Sector = FLASH_Confirm;

	timeout=5000000;
	while(((stat = *(volatile u16 *)0xbc000000) & FLASH_Status_Ready) != FLASH_Status_Ready) 
	{
		if (--timeout == 0) break;
	}
	// Restore ROM to "normal" mode
	*(volatile u16 *)0xbc000000 = FLASH_Reset;

	res = 0;
	if (stat & FLASH_ErrorMask) {
		if (!(stat & FLASH_ErrorErase)) {
			res = FLASH_ERR_HWR;    // Unknown error
		} else {
			if (stat & FLASH_ErrorLowVoltage) 
				res = FLASH_ERR_LOW_VOLTAGE;
			else if (stat & FLASH_ErrorLocked)
				res = FLASH_ERR_PROTECT;
			else
				res = FLASH_ERR_ERASE;
		}
	}
	return res;
}

static void i28fl_unlock(u32 Addr)
{
	*(volatile u16 *)Addr = 0x60;
	*(volatile u16 *)Addr = 0xD0;
	*(volatile u16 *)Addr = 0xFF;
}

#if 0
static void i28fl_lock(u32 Addr)
{
	*(volatile u16 *)0xbc000000 = FLASH_Clear_Status;
	*(volatile u16 *)0xbc000000 = FLASH_Set_Lock;
	*(volatile u16 *)Addr = FLASH_Set_Lock_Confirm;
}
#endif

static int _i28fl_write_word(u32 Addr, u16 Data)
{
	int res = 0, timeout;
	u16 stat;

	// Clear any error conditions
	*(volatile u16 *)0xbc000000 = FLASH_Clear_Status;
	*(volatile u16 *)Addr = FLASH_Program;
	*(volatile u16 *)Addr = Data;

	timeout = 5000000;

	while(((stat = *(volatile u16 *)0xbc000000) & FLASH_Status_Ready) != FLASH_Status_Ready) { 
		if (--timeout == 0) {
			*(volatile u16 *)0xbc000000 = FLASH_Reset;
			return FLASH_ERR_DRV_TIMEOUT;
		}
	}
	if (stat & FLASH_ErrorMask) {
		if (!(stat & FLASH_ErrorProgram)) 
			res = FLASH_ERR_HWR;    // Unknown error
		else {
			if (stat & FLASH_ErrorLowVoltage)
				res = FLASH_ERR_LOW_VOLTAGE;
			else if (stat & FLASH_ErrorLocked) 
				res = FLASH_ERR_PROTECT;
			else
				res = FLASH_ERR_PROGRAM;
		}
	}
	*(volatile u16 *)0xbc000000 = FLASH_Reset;
	return res;
}

int i28fl_write(flash_info_t *info, void *buf, void *addr, int len)
{
	int ret;
	volatile u16 *Src;
	u32 Dst;

	Src = (volatile u16 *)buf;
	Dst = (u32)addr;

	while (len > 0) {
		ret = _i28fl_write_word(Dst, *Src);
		if(ret == FLASH_ERR_PROTECT)
		{
			i28fl_unlock(Dst);
			ret = _i28fl_write_word(Dst, *Src);
		}

		Src ++;
		Dst += 2;
		len -= 2;
	}

	return ERR_OK;
}

int i28fl_erase_chip(flash_info_t *info)
{
	return ERR_NOT_SUPPORT;
}

int i28fl_erase_sector(flash_info_t *info, void *saddr, int size)
{
	int ret;
	u32 Addr = (u32)saddr;

	ret = _i28fl_erase_sector(Addr);
	if (ret == FLASH_ERR_PROTECT)
	{
		i28fl_unlock(Addr);
		ret = _i28fl_erase_sector(Addr);
	}
	return ret;
}
