#ifndef __jz4740_usbdefines__h_
#define __jz4740_usbdefines__h_

//#define dprintf(x...) printf(x)

#define MAX_COMMAND_LENGTH 100
#define COMMAND_NUM 30
#define NAND_MAX_BLK_NUM  10000000//((Hand.nand_pn / Hand.nand_ppb) + 1)
#define NAND_MAX_PAGE_NUM 1073740824 //Hand.nand_pn
//#define MAX_BULK_SIZE 0x100000
#define NAND_SECTION_NUM 6
#define MAX_TRANSFER_SIZE 0x210000 //0x420000			//1024KB
#define NAND_MAX_BYTE_NUM (Hand.nand_pn * Hand.nand_ps)
#define	IOCTL_INBUF_SIZE	512
#define	IOCTL_OUTBUF_SIZE	512
#define MAX_DEV_NUM 16

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
	NAND_FINI,
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
	/* target init command, must be first */
	/*unsigned int icmd_cnt;
	unsigned int icmd_type[MAX_ICMD];
	unsigned int icmd_addr[MAX_ICMD];
	unsigned int icmd_data[MAX_ICMD];
	unsigned int icmd_data2[MAX_ICMD];*/		//not support now

	unsigned int devtype;   /* device types: nor/nand/eeprom etc. */
	unsigned int optype;    /* operation types: read/write/erase etc. */
	unsigned int address;   /* operation address value */
	unsigned int count;     /* operation count value */
	int finished;           /* operation finished flag */
	int error;              /* operation error flag */
	unsigned int done_count; /* count value that has been done */

	/* host data buffer */
	unsigned int database;  /* data buffer base */
	unsigned int datasize;  /* data buffer size in bytes */

	/* nor flash fields */
	unsigned int chiptype;    /* chip type */
	unsigned int chipwidth;   /* chip width 8/16/32 */
	unsigned int buswidth;    /* data bus width 8/16/32 */
	unsigned int baseaddr;    /* flash base address */
	unsigned int chipsize;    /* chip size in bytes */
	unsigned int sectorsize;  /* sector size in bytes */
	unsigned int setup_addr1; /* flash setup address 1 */
	unsigned int setup_addr2; /* flash setup address 2 */

	/* nand flash info */
	int nand_start;
	int nand_bw;		//bus width
	int nand_rc;		//row cycle
	int nand_ps;		//page size
	int nand_ppb;		//oob size per block
	int nand_force_erase;//
	int nand_pn;		//page number in total
	int nand_os;		//oob size
	unsigned int nand_ids;  /* vendor_id & device_id */

	/* sdram info */
	int sdram_bw;
	int sdram_banks;
	int sdram_rows;
	int sdram_cols;
	int sdram_casl; 

	int sdram_status_enable;
	int sdram_address;
	int sdram_true_value;
	int sdram_bad_value;

	/* i2c eeprom info */
	/*int eeprom_addr;
	int eeprom_subaddr;
	unsigned char eeprom_v[256];
	int eeprom_vcnt;*/					//not support now

	/* others */
	/*int debug_level;
	int target_printf_enable;
	char target_printf_buf[64];
	char dummy[32];*/
} hand_t;


#define MAX_FLASH_SECT 0x10000  /* 64K, large enough */
#define u32 unsigned int
#define u16 unsigned short
#define u8 unsigned char

typedef struct {
	u32	flash_id;	/* combined manufacturer & device code	*/
	u8	portwidth;	/* the width of the port		*/
	u8	chipwidth;	/* the width of the chip		*/
	u32	chiptype;	/* the type of the chip			*/
	u32	chipsize;	/* the chip size in bytes		*/
	u32	sector_count;	/* number of erase units		*/
	u32	start; 		/* virtual flash start address 		*/
	u32	sector_start[MAX_FLASH_SECT];  /* virtual sector start addresses */
	u32	sector_size[MAX_FLASH_SECT];   /* sector size in bytes  */

	u32	setup_addr1;     /* flash first setup address */
	u32	setup_addr2;     /* flash second setup address */

	/* CFI specified */
	u16	buffer_size;	/* # of bytes in write buffer		*/
	u32	erase_blk_tout;	/* maximum block erase timeout		*/
	u32	write_tout;	/* maximum write timeout		*/
	u32	buffer_write_tout;/* maximum buffer write timeout	*/
	u16	vendor;		/* the primary vendor id		*/
	u16	cmd_reset;	/* Vendor specific reset command	*/
	u16	interface;	/* used for x8/x16 adjustments		*/

	/* others */
	void	(*printf)(const char *format, ...);
	u8	reserved[32];
} flash_info_t;

#define FLASH_TYPEMASK	0x0000FFFF	/* extract FLASH type	information	*/
#define FLASH_VENDMASK	0xFFFF0000	/* extract FLASH vendor information	*/

#define FLASH_UNKNOWN	0xFFFFFFFF	/* unknown flash type			*/

/*-----------------------------------------------------------------------
 * manufacturer IDs
 */

#define AMD_MANUFACT	0x0001	/* AMD	   manuf. ID */
#define FUJ_MANUFACT	0x0004	/* FUJITSU manuf. ID */
#define ATM_MANUFACT	0x001F	/* ATMEL */
#define STM_MANUFACT	0x0020	/* STM (Thomson) manuf. ID */
#define SST_MANUFACT	0x00BF	/* SST	   manuf. ID */
#define MT_MANUFACT		0x0089	/* MT	   manuf. ID */
#define INTEL_MANUFACT	0x0089	/* INTEL   manuf. ID */
#define INTEL_ALT_MANU	0x00B0	/* alternate INTEL namufacturer ID	*/
#define MX_MANUFACT		0x00C2	/* MXIC	   manuf. ID */
#define TOSH_MANUFACT	0x0098	/* TOSHIBA manuf. ID */
#define MT2_MANUFACT	0x002C	/* alternate MICRON manufacturer ID */
#define EXCEL_MANUFACT	0x004A	/* Excel Semiconductor                  */

#define FLASH_MAN_CFI	0x01000000  /* CFI-compliant flash type */

/*-----------------------------------------------------------------------
 * CFI primary vendor IDs
 */
#define CFI_CMDSET_NONE		    	0
#define CFI_CMDSET_INTEL_EXTENDED   	1
#define CFI_CMDSET_AMD_STANDARD	    	2
#define CFI_CMDSET_INTEL_STANDARD   	3
#define CFI_CMDSET_AMD_EXTENDED	    	4
#define CFI_CMDSET_MITSU_STANDARD   	256
#define CFI_CMDSET_MITSU_EXTENDED   	257
#define CFI_CMDSET_SST		    	258

/*-----------------------------------------------------------------------
 * Values for the width of the port
 */
#define FLASH_CFI_8BIT		0x01
#define FLASH_CFI_16BIT		0x02
#define FLASH_CFI_32BIT		0x04
#define FLASH_CFI_64BIT		0x08

/*
 * Values for the width of the chip
 */
#define FLASH_CFI_BY8		0x01
#define FLASH_CFI_BY16		0x02
#define FLASH_CFI_BY32		0x04
#define FLASH_CFI_BY64		0x08

/*
 * Values for the flash device interface
 */
#define FLASH_CFI_X8		0x00
#define FLASH_CFI_X16		0x01
#define FLASH_CFI_X8X16		0x02
#define FLASH_CFI_X32		0x03
#define FLASH_CFI_X16X32	0x05

/* convert between bit value and numeric value */
#define CFI_FLASH_SHIFT_WIDTH	3

/*-----------------------------------------------------------------------
 * chiptype definitions
 */
#define CHIPTYPE_AUTO			0x00  /* Auto detect the chip types */
#define CHIPTYPE_AM29			0x01  /* AM29XXX series */
#define CHIPTYPE_I28F			0x02  /* Intel 28FXXX with no bufferwrite */
#define CHIPTYPE_I28FL			0x04  /* Intel 28FXXX with no bufferwrite and lock/unlock features */

#endif