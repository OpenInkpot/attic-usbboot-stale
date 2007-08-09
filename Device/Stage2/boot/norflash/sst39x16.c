/*
 * sst39x16.c -- SST 39VF160x/320x/640x serials 16-bit flash driver.
 */

#include "flash.h"
#include "sst.h"

struct sst_flash_info sst39x16_flash_infos [] = {
	{0x234B, 4096,   512},	/* SST39VF1601 */
	{0x234A, 4096,   512},	/* SST39VF1602 */
	{0x235B, 4096,   1024},	/* SST39VF3201 */
	{0x235A, 4096,   1024},	/* SST39VF3202 */
	{0x236B, 4096,   2048},	/* SST39VF6401 */
	{0x236A, 4096,   2048},	/* SST39VF6402 */
	{0},
};

int sst39x16_init(flash_info_t *info)
{
	volatile u16 *start = (volatile u16 *)info->start;
	u32 vid, did;
	u32 sector;
	int i, j;

	start[0x5555] = 0xAA;
	start[0x2AAA] = 0x55;
	start[0x5555] = 0x90;

	vid = start[0];
	did = start[1];

	start[0x5555] = 0xAA;
	start[0x2AAA] = 0x55;
	start[0x5555] = 0xF0;

	if (vid != SST_MANUFACT)
		return ERR_UNKNOWN_FLASH_VENDOR;

	for (i = 0; sst39x16_flash_infos[i].id != 0; i++)
		if (sst39x16_flash_infos[i].id == did) {
			info->flash_id = (SST_MANUFACT << 16) | did;
			info->portwidth = FLASH_CFI_16BIT;
			info->chipwidth = FLASH_CFI_16BIT;
			info->chipsize = sst39x16_flash_infos[i].sector_size * sst39x16_flash_infos[i].sector_count;
			info->sector_count = sst39x16_flash_infos[i].sector_count;

			sector = (u32)start;
			for (j = 0; j < info->sector_count; j++) {
				info->sector_start[j] = sector;
				info->sector_size[j] = sst39x16_flash_infos[i].sector_size;
				sector += sst39x16_flash_infos[i].sector_size;
			}

			return ERR_OK;
		}

	return ERR_UNKNOWN_FLASH_TYPE;
}

int sst39x16_write(flash_info_t *info, void *buf, void *addr, int len)
{
	volatile u16 *start = (volatile u16 *)info->start;
	volatile u16 *src = (volatile u16 *)buf;
	volatile u16 *dst = (volatile u16 *)addr;

	while (len >= 2) {
		int timeout = 0x07ffffff;
		u16 pre, cur;

		start[0x5555] = 0xAA;
		start[0x2AAA] = 0x55;
		start[0x5555] = 0xA0;

		*dst = *src;

		len -= sizeof(*dst);
		
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

	if (len > 0) {
		int timeout = 0x07ffffff;
		u16 pre, cur;
		u8 src0, src1;

		src0 = *(volatile u8 *)src;
		src1 = *(volatile u8 *)((u32)dst + 1);

		start[0x5555] = 0xAA;
		start[0x2AAA] = 0x55;
		start[0x5555] = 0xA0;

		// little-endian system
		*dst = (src1 << 8) | src0;

		cur = *(dst) & 0x40;
		pre = ~cur;
		while( timeout-- > 0 ) {
			if(pre == cur)
				break;
			pre = cur;
			cur = *(dst) & 0x40;
		}
		if(pre != cur)
			return ERR_TIMOUT;

		// verify data
		if (*dst != ((src1 << 8) | src0))
			return ERR_WRITE_VERIFY;
	}

	return ERR_OK;
}

int sst39x16_erase_chip(flash_info_t *info)
{
	volatile u16 *start = (volatile u16 *)info->start;
	int i;
	u32 chipsize;

	start[0x5555] = 0xAA;
	start[0x2AAA] = 0x55;
	start[0x5555] = 0x80;
	start[0x5555] = 0xAA;
	start[0x2AAA] = 0x55;
	start[0x5555] = 0x10;

	i = 0x07ffffff;
	while (i) {
		if ((*(start) & 0x80) == 0x80)
			break;
		i --;
	}
	if (i == 0)
		return ERR_TIMOUT;

	// check if erasing passed?
	chipsize = info->chipsize;
	while (chipsize > 0) {
		if (*start++ != 0xffff)
			return ERR_ERASE_ERROR;
		chipsize -= 2;
	}

	return ERR_OK;
}

int sst39x16_erase_sector(flash_info_t *info, void *saddr, int size)
{
	volatile u16 *start = (volatile u16 *)info->start;
	volatile u16 *sector = (volatile u16 *)saddr;
	int i;
	u32 sect, sectsize;

	start[0x5555] = 0xAA;
	start[0x2AAA] = 0x55;
	start[0x5555] = 0x80;
	start[0x5555] = 0xAA;
	start[0x2AAA] = 0x55;
	sector[0x0000] = 0x30;

	i = 0x07ffffff;
	while (i) {
		if ((*(sector) & 0x80) == 0x80)
			break;
		i --;
	}

	if (i == 0)
		return ERR_TIMOUT;

	// check if erasing passed?
	sect = find_sector(info, (u32)saddr);
	sectsize = info->sector_size[sect];
	while (sectsize > 0) {
		if (*sector++ != 0xffff)
			return ERR_ERASE_ERROR;
		sectsize -= 2;
	}

	return ERR_OK;
}
