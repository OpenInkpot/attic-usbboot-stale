/*
 * sst39.c -- SST 39xFxxx serials 8-bit flash driver.
 */

#include "flash.h"
#include "sst.h"

struct sst_flash_info sst39x8_flash_infos [] = {
	{0xD5, 4096,   32},		/* SST39VF010 */
	{0xD6, 4096,   64},		/* SST39VF020 */
	{0xD7, 4096,  128},		/* SST39VF040 */
	{0xB5, 4096,   32},		/* SST39SF010 */
	{0xB6, 4096,   64},		/* SST39SF020 */
	{0xB7, 4096,  128},		/* SST39SF040 */
	{0},
};

int sst39x8_init(flash_info_t *info)
{
	volatile u8 *start = (volatile u8 *)info->start;
	u16 vid, did;
	u32 sector;
	int i, j;

	FLASH_39_COMMAND(start, FLASH_39_Read_ID);

	vid = start[0];
	did = start[1];

	FLASH_39_COMMAND(start, FLASH_39_Exit_ID);

	if (vid != SST_MANUFACT)
		return ERR_UNKNOWN_FLASH_VENDOR;

	for (i = 0; sst39x8_flash_infos[i].id != 0; i++)
		if (sst39x8_flash_infos[i].id == did) {
			info->flash_id = (SST_MANUFACT << 16) | did;
			info->portwidth = FLASH_CFI_8BIT;
			info->chipwidth = FLASH_CFI_8BIT;
			info->chipsize = sst39x8_flash_infos[i].sector_size * sst39x8_flash_infos[i].sector_count;
			info->sector_count = sst39x8_flash_infos[i].sector_count;

			sector = (u32)start;
			for (j = 0; j < info->sector_count; j++) {
				info->sector_start[j] = sector;
				info->sector_size[j] = sst39x8_flash_infos[i].sector_size;
				sector += sst39x8_flash_infos[i].sector_size;
			}

			return ERR_OK;

		}

	return ERR_UNKNOWN_FLASH_TYPE;
}

int sst39x8_write(flash_info_t *info, void *buf, void *addr, int len)
{
	volatile u8 *start = (volatile u8 *)info->start;
	volatile u8 *src = (volatile u8 *)buf;
	volatile u8 *dst = (volatile u8 *)addr;

	while (len > 0) {
		int timeout = 0x07ffffff;
		unsigned char pre, cur;

		FLASH_39_COMMAND (start, FLASH_39_Program);
		*dst = *src;
		len -= sizeof(unsigned char);
		
		cur = *(dst) & 0x40;
		pre = ~cur;
		while( timeout-- > 0 ) {
			if(pre == cur)
				break;
			pre = cur;
			cur = *(dst) & 0x40;
		}
		if(pre != cur)
			return ERR_PROG_ERROR;

		// verify data - also increment pointers
		if (*dst++ != *src++)
			return ERR_WRITE_VERIFY;
	}

	return ERR_OK;
}

int sst39x8_erase_chip(flash_info_t *info)
{
	volatile u8 *start = (volatile u8 *)info->start;
	int len;
	u32 chipsize;

	FLASH_39_COMMAND (start, FLASH_39_Erase_Chip);
	FLASH_39_COMMAND (start, FLASH_39_Erase_All);

	len = 0x07ffffff;
	while (len) {
		if ((*(start) & 0x80) == 0x80)
			break;
		len --;
	}

	if (len == 0)
		return ERR_ERASE_ERROR;

	// check if erasing passed?
	chipsize = info->chipsize;
	while (chipsize-- > 0) {
		if (*start++ != 0xff)
			return ERR_ERASE_ERROR;
	}

	return ERR_OK;
}

int sst39x8_erase_sector(flash_info_t *info, void *saddr, int size)
{
	volatile u8 *start = (volatile u8 *)info->start;
	volatile u8 *sector = (volatile u8 *)saddr;
	int len;
	u32 sect, sectsize;

	FLASH_39_COMMAND (start, FLASH_39_Erase_Chip);

	*(start + 0x5555) = 0xAA;
	*(start + 0x2AAA) = 0x55;
	*(sector) = FLASH_39_Erase_Sector;

	len = 0x07ffffff;
	while (len) {
		if ((*(sector) & 0x80) == 0x80)
			break;
		len --;
	}

	if (len == 0)
		return ERR_ERASE_ERROR;

	// check if erasing passed?
	sect = find_sector(info, (u32)saddr);
	sectsize = info->sector_size[sect];
	while (sectsize-- > 0) {
		if (*sector++ != 0xff)
			return ERR_ERASE_ERROR;
	}

	return ERR_OK;
}
