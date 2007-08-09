/*
 * sst28.c -- SST 28SFxxx serials 8-bit flash driver.
 */

#include "flash.h"
#include "sst.h"

struct sst_flash_info sst28_flash_infos [] = {
	{0x02, 256, 1024},		/* SST28SF020 */
	{0x04, 256, 2048},		/* SST28SF040 */
	{0},
};

int sst28_init(flash_info_t *info)
{
	volatile u8 *start = (volatile u8 *)info->start;
	u16 vid, did;
	u32 sector;
	int i, j;

	FLASH_28_COMMAND(start,  FLASH_28_Reset);
	FLASH_28_COMMAND(start,  FLASH_28_Read_ID);

	vid = start[0];
	did = start[1];

	FLASH_28_COMMAND(start,  FLASH_28_Reset);

	if (vid != SST_MANUFACT)
		return ERR_UNKNOWN_FLASH_VENDOR;

	for (i = 0; sst28_flash_infos[i].id != 0; i++) {
		if (sst28_flash_infos[i].id == did) {
			info->flash_id = (SST_MANUFACT << 16) | did;
			info->portwidth = FLASH_CFI_8BIT;
			info->chipwidth = FLASH_CFI_8BIT;
			info->chipsize = sst28_flash_infos[i].sector_size * sst28_flash_infos[i].sector_count;
			info->sector_count = sst28_flash_infos[i].sector_count;

			sector = (u32)start;
			for (j = 0; j < info->sector_count; j++) {
				info->sector_start[j] = sector;
				info->sector_size[j] = sst28_flash_infos[i].sector_size;
				sector += sst28_flash_infos[i].sector_size;
			}

			return ERR_OK;
		}
	}

	return ERR_UNKNOWN_FLASH_TYPE;
}

int sst28_write(flash_info_t *info, void *buf, void *addr, int len)
{
	volatile u8 *start = (volatile u8 *)info->start;
	volatile u8 *src = (volatile u8 *)buf;
	volatile u8 *dst = (volatile u8 *)addr;
	unsigned char temp;

	FLASH_28_COMMAND(start,  FLASH_28_Reset);

	/* disable protection */
	temp = *(start + 0x1823);
	temp = *(start + 0x1820);
	temp = *(start + 0x1822);
	temp = *(start + 0x0418);
	temp = *(start + 0x041b);
	temp = *(start + 0x0419);
	temp = *(start + 0x041a);

	while (len > 0) {
		unsigned char pre, cur;
		int timeout = 0x07ffffff;

		FLASH_28_COMMAND (dst, FLASH_28_Program);
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

		DELAY(1000);
		FLASH_28_COMMAND(start,  FLASH_28_Reset);

		// verify data - also increment pointers
		if (*dst++ != *src++)
			return ERR_WRITE_VERIFY;
	}

	/* enable protection */
	temp = *(start + 0x1823);
	temp = *(start + 0x1820);
	temp = *(start + 0x1822);
	temp = *(start + 0x0418);
	temp = *(start + 0x041b);
	temp = *(start + 0x0419);
	temp = *(start + 0x040a);

	FLASH_28_COMMAND(start,  FLASH_28_Reset);

	return ERR_OK;
}

int sst28_erase_chip(flash_info_t *info)
{
	volatile u8 *start = (volatile u8 *)info->start;
	volatile unsigned char pre, cur, temp;
	int timeout = 0x07ffffff;
	u32 chipsize;

	FLASH_28_COMMAND(start, FLASH_28_Reset);

	/* disable protection */
	temp = *(start + 0x1823);
	temp = *(start + 0x1820);
	temp = *(start + 0x1822);
	temp = *(start + 0x0418);
	temp = *(start + 0x041b);
	temp = *(start + 0x0419);
	temp = *(start + 0x041a);

	FLASH_28_COMMAND(start, FLASH_28_Erase_Chip);
	FLASH_28_COMMAND(start, FLASH_28_Erase_Chip);

	cur = *(start) & 0x40;
	pre = ~cur;
	while( timeout-- > 0 ) {
		if(pre == cur)
			break;
		pre = cur;
		cur = *(start) & 0x40;
	}

	/* enable protection */
	temp = *(start + 0x1823);
	temp = *(start + 0x1820);
	temp = *(start + 0x1822);
	temp = *(start + 0x0418);
	temp = *(start + 0x041b);
	temp = *(start + 0x0419);
	temp = *(start + 0x040a);

	DELAY(1000);
	FLASH_28_COMMAND(start,  FLASH_28_Reset);

	if (pre != cur)
		return ERR_ERASE_ERROR;

	// check if erasing passed?
	chipsize = info->chipsize;
	while (chipsize-- > 0) {
		if (*start++ != 0xff)
			return ERR_ERASE_ERROR;
	}

	return ERR_OK;
}

int sst28_erase_sector(flash_info_t *info, void *saddr, int size)
{
	volatile u8 *start = (volatile u8 *)info->start;
	volatile u8 *sector = (volatile u8 *)saddr;
	volatile unsigned char pre, cur, temp;
	int timeout = 0x07ffffff;
	u32 sect, sectsize;

	FLASH_28_COMMAND(start, FLASH_28_Reset);

	/* disable protection */
	temp = *(start + 0x1823);
	temp = *(start + 0x1820);
	temp = *(start + 0x1822);
	temp = *(start + 0x0418);
	temp = *(start + 0x041b);
	temp = *(start + 0x0419);
	temp = *(start + 0x041a);

	FLASH_28_COMMAND(sector, FLASH_28_Erase_Sector1);
	FLASH_28_COMMAND(sector, FLASH_28_Erase_Sector2);

	cur = *(sector) & 0x40;
	pre = ~cur;
	while( timeout-- > 0 ) {
		if(pre == cur)
			break;
		pre = cur;
		cur = *(sector) & 0x40;
	}

	/* enable protection */
	temp = *(start + 0x1823);
	temp = *(start + 0x1820);
	temp = *(start + 0x1822);
	temp = *(start + 0x0418);
	temp = *(start + 0x041b);
	temp = *(start + 0x0419);
	temp = *(start + 0x040a);

	DELAY(1000);
	FLASH_28_COMMAND(start,  FLASH_28_Reset);

	if (pre != cur)
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
