#ifndef _CONFIGS_H
#define _CONFIGS_H

//Here are these common definitions
//Once your system configration change,just modify the file

//SDRAM configs:
#define SDRAM_BW16		0	/* Data bus width: 0-32bit, 1-16bit */
#define SDRAM_BANK4		1	/* Banks each chip: 0-2bank, 1-4bank */
#define SDRAM_ROW		13	/* Row address: 11 to 13 */
#define SDRAM_COL		9	/* Column address: 8 to 12 */
#define SDRAM_CASL		2	/* CAS latency: 2 or 3 */

//freq configs:
#define CFG_CPU_SPEED		336000000	/* CPU clock def: 336 MHz */
#define CFG_EXTAL		12000000	/* EXTAL freq must=12 MHz !! */
#define CONFIG_BAUDRATE         57600           // baubrate for serail port

#endif 
