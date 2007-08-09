/*
 * flash.c
 *
 * Flash initialization.
 *
 * Copyright (c) 2005 Ingenic Semiconductor <jlwei@ingenic.cn>
 */

#include "flash.h"

/*-----------------------------------------------------------------------
 * Prototypes
 */
int flash_init(flash_info_t *info);

int (*flash_query)(flash_info_t *info);
int (*flash_write)(flash_info_t *info, void *buf, void *addr, int len);
int (*flash_erase_chip)(flash_info_t *info);
int (*flash_erase_sector)(flash_info_t *info, void *saddr, int size);

/*
 * supported flash list
 */
static struct {
	int (*init)(flash_info_t *info);
	int (*write)(flash_info_t *info, void *buf, void *addr, int len);
	int (*erase_chip)(flash_info_t *info);
	int (*erase_sector)(flash_info_t *info, void *saddr, int size);
} flash_list[] = {
	{sst28_init, sst28_write, sst28_erase_chip, sst28_erase_sector},
	{sst39x8_init, sst39x8_write, sst39x8_erase_chip, sst39x8_erase_sector},
	{sst39x16_init, sst39x16_write, sst39x16_erase_chip, sst39x16_erase_sector},
	{cfi_init, cfi_write, cfi_erase_chip, cfi_erase_sector},
};

#define NUM_FLASH_LIST	(sizeof(flash_list)/sizeof(*flash_list))

static int null_query(flash_info_t *info)
{
	return ERR_OK;
}

/*
 * query flash infos and get flash ops
 */
int flash_init(flash_info_t *info)
{
	int i, ret = 0;

	if (info->chiptype == CHIPTYPE_AUTO) {
		for (i = 0; i < NUM_FLASH_LIST; i++) {
			if (flash_list[i].init) {
				ret = flash_list[i].init(info);
				if (ret == ERR_OK)
					break;
			}
		}

		if (i == NUM_FLASH_LIST)
			return ret;

		flash_query        = null_query;
		flash_write        = flash_list[i].write;
		flash_erase_chip   = flash_list[i].erase_chip;
		flash_erase_sector = flash_list[i].erase_sector;
	}
	else {
		switch (info->chiptype) {
		case CHIPTYPE_AM29:
			flash_query        = am29_query;
			flash_write        = am29_write;
			flash_erase_chip   = am29_erase_chip;
			flash_erase_sector = am29_erase_sector;

			break;

		case CHIPTYPE_I28F:
			flash_query        = i28f_query;
			flash_write        = i28f_write;
			flash_erase_chip   = i28f_erase_chip;
			flash_erase_sector = i28f_erase_sector;

			break;

		case CHIPTYPE_I28FL:
			flash_query        = i28fl_query;
			flash_write        = i28fl_write;
			flash_erase_chip   = i28fl_erase_chip;
			flash_erase_sector = i28fl_erase_sector;

			break;
		default:
			break;
		}
	}

	return ret;
}
