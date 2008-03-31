#ifndef __HAND_H__
#define __HAND_H__

#if 0
#define MAX_ICMD  1024

#define ICMD_CNT    (HAND_BASE + 0*4)
#define ICMD_TYPE   (ICMD_CNT + 1*4)
#define ICMD_ADDR   (ICMD_TYPE + MAX_ICMD*4)
#define ICMD_DATA   (ICMD_ADDR + MAX_ICMD*4)
#define ICMD_DATA2  (ICMD_DATA + MAX_ICMD*4)
#endif

typedef struct {
#if 0
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
#endif

	/* nand flash info */
//	int nand_start;
	int pt;                 //cpu type: jz4740/jz4750 .....
	int nand_bw;
	int nand_rc;
	int nand_ps;
	int nand_ppb;
	int nand_force_erase;
	int nand_pn;
	int nand_os;
	int nand_eccpos;        //ECC position
	int nand_bbpage;        //bad block position
	int nand_bbpos;         //bad block position
	unsigned int nand_ids;  /* vendor_id & device_id */

#if 0
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
#endif

} hand_t;

#if 0
/* Device types */
#define DEV_NOR                  0
#define DEV_NAND                 1
#define DEV_EEPROM               2

/* Operation types */
#define OP_READ	                 0
#define OP_WRITE                 1
#define OP_ERASE_SECTOR          2
#define OP_ERASE_CHIP            3
#define OP_QUERY                 4
#define OP_WRITEV                5
#define OP_HWRESET               6
#define OP_READ_RAW              7
#define OP_READ_OOB              8

/* Command types */
#define CMD_WM32                 0
#define CMD_WM16                 1
#define CMD_WM8                  2
#define CMD_WCP0                 3

/* Debug levels */
#define DEBUG_NONE               0
#define DEBUG_IDS                1 /* read target idcode and impcode */
#define DEBUG_CPU                2 /* debug cpu activities */
#define DEBUG_HW1                3 /* test target pins connection */
#define DEBUG_HW2                4 /* test target pins connection */
#define DEBUG_MEM                5 /* do memory test  */
#define DEBUG_GPIOS              6 /* GPIO set */
#define DEBUG_GPIOC              7 /* GPIO clear */

#endif

#endif /* __HAND_H__ */
