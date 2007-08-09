#ifndef __SST_H__
#define __SST_H__

/*
 * SST28xxxx command MACROs
 */
#define FLASH_28_Reset            0xff
#define FLASH_28_Read_ID          0x90
#define FLASH_28_Erase_Chip       0x30
#define FLASH_28_Erase_Sector1    0x20
#define FLASH_28_Erase_Sector2    0xd0
#define FLASH_28_Program          0x10

#define FLASH_28_COMMAND(addr, op)		\
do {						\
    *((volatile u8 *)(addr)) = (op);		\
} while (0)

/*
 * SST39xxxx command MACROs
 */
#define FLASH_39_Read_ID      0x90
#define FLASH_39_Exit_ID      0xF0
#define FLASH_39_Erase_Chip   0x80
#define FLASH_39_Erase_Sector 0x30
#define FLASH_39_Erase_All    0x10
#define FLASH_39_Program      0xA0

#define FLASH_39_COMMAND(base, op)		\
do {						\
    *((volatile u8 *)(base) + 0x5555) = 0xAA;	\
    *((volatile u8 *)(base) + 0x2AAA) = 0x55;	\
    *((volatile u8 *)(base) + 0x5555) = (op);	\
} while (0)

/*
 * SST flash infos
 */
struct sst_flash_info {
	u16 id;
	u32 sector_size;
	u32 sector_count;
};

#endif /* __SST_H__ */
