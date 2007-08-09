#ifndef __FLASH_INFO_H__
#define __FLASH_INFO_H__

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

/*-----------------------------------------------------------------------
 * FLASH Info: contains chip specific data
 */

#define MAX_FLASH_SECT 0x10000  /* 64K, large enough */

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
#define MT_MANUFACT	0x0089	/* MT	   manuf. ID */
#define INTEL_MANUFACT	0x0089	/* INTEL   manuf. ID */
#define INTEL_ALT_MANU	0x00B0	/* alternate INTEL namufacturer ID	*/
#define MX_MANUFACT	0x00C2	/* MXIC	   manuf. ID */
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

#endif /* __FLASH_INFO_H__ */
