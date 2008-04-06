#ifndef __jz4740_usbdefines__h_
#define __jz4740_usbdefines__h_

//#define dprintf(x...) printf(x)
#define SDRAM_SIZE ( 32 * 1024 * 1024 )        //此处定义SDRAM大小
#define CODE_SIZE  ( 3 * 1024 * 1024 )
#define START_ADDR ( 0x80000000 + SDRAM_SIZE - CODE_SIZE )

#define MAX_COMMAND_LENGTH 100
#define COMMAND_NUM 31
#define NAND_MAX_BLK_NUM  10000000//((Hand.nand_pn / Hand.nand_ppb) + 1)
#define NAND_MAX_PAGE_NUM 1073740824 //Hand.nand_pn
#define NAND_SECTION_NUM 9
#define MAX_TRANSFER_SIZE 0x100000
#define MAX_LOAD_SIZE 0x3000
#define NAND_MAX_BYTE_NUM (Hand.nand_pn * Hand.nand_ps)
#define	IOCTL_INBUF_SIZE	512
#define	IOCTL_OUTBUF_SIZE	512
#define MAX_DEV_NUM 16 

enum CPUTYPE 
{
	JZ4740,
	JZ4750,
};

enum USB_Boot_State 
{
	DISCONNECT,
	CONNECT,
	BOOT,
	UNBOOT
};

enum OPTION
{
	OOB_ECC,
	OOB_NO_ECC,
	NO_OOB,
};

enum NOR_OPS_TYPE
{
	NOR_INIT = 0,
	NOR_QUERY,
	NOR_WRITE,
	NOR_ERASE_CHIP,
	NOR_ERASE_SECTOR
};

enum NOR_FLASH_TYPE
{
	NOR_AM29 = 0,
	NOR_SST28,
	NOR_SST39x16,
	NOR_SST39x8
};

enum NAND_OPS_TYPE
{
	NAND_QUERY = 0,
	NAND_INIT,
	NAND_MARK_BAD,
	NAND_READ_OOB,
	NAND_READ_RAW,
	NAND_ERASE,
	NAND_READ,
	NAND_PROGRAM,
	NAND_READ_TO_RAM
};

enum SDRAM_OPS_TYPE
{
	SDRAM_LOAD,

};

enum DATA_STRUCTURE_OB
{
	DS_flash_info ,
	DS_hand
};




typedef struct {

	/* nand flash info */
	int pt;             //cpu type 
	int nand_bw;		//bus width
	int nand_rc;		//row cycle
	int nand_ps;		//page size
	int nand_ppb;		//page number per block
	int nand_force_erase;//
	int nand_pn;		//page number in total
	int nand_os;		//oob size
	int nand_eccpos;
	int nand_bbpage;
	int nand_bbpos;
	unsigned int nand_ids;  /* vendor_id & device_id */

} hand_t;

#endif