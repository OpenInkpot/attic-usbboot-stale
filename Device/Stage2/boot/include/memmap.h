#ifndef __MEMMAP_H__
#define __MEMMAP_H__

/* 
 * EJTAG memory in ACC mode:
 *
 *      +------------------+ 0xffff,ffff
 *      |                  |
 *      |                  |
 *      |                  |
 *      |     Extended     |
 *      |      (12M)       |               WT Cacheable
 *      |                  |
 *      |                  |
 *      |                  |
 *      |                  |
 *      +------------------+ 0xff40,0000
 *      |    drseg (1M)    |
 *      |                  |               Not used
 *      +------------------+ 0xff30,0000
 *      |    dmseg (1M)    |   
 *      |                  |               Uncacheable
 *      +------------------+ 0xff20,0000
 *      |                  |
 *      |     Extended     |
 *      |      (2M)        |               WT Cacheable
 *      |                  |
 *      +------------------+ 0xff00,0000
 *
 * Address 0xff200000-0xff280000 are shadowed to 0xff000000-0xff080000.
 *
 */

#define STUB_BASE                 0xff000000  /* Cacheable */
#define STUB_SIZE                 0x00280000  /* 2MB + 512KB */

#define HAND_BASE                 0xff280000  /* Uncacheable */
#define HAND_SIZE                 0x00080000  /* 512KB */

#define INFO_BASE                 0xff400000  /* Cacheable */
#define INFO_SIZE                 0x00100000  /* 1MB */

#define STCK_BASE                 0xff500000  /* Cacheable */
#define STCK_SIZE                 0x00100000  /* 1MB */

#define DATA_BASE                 0xff600000  /* Cacheable */
#define DATA_SIZE                 0x00a00000  /* 10MB */

#ifndef __ASSEMBLY__
#define IS_STUB_ADDR(a) ((((a) >= STUB_BASE) && ((a) < (STUB_BASE + STUB_SIZE))) ? 1:0)
#define IS_HAND_ADDR(a) ((((a) >= HAND_BASE) && ((a) < (HAND_BASE + HAND_SIZE))) ? 1:0)
#define IS_INFO_ADDR(a) ((((a) >= INFO_BASE) && ((a) < (INFO_BASE + INFO_SIZE))) ? 1:0)
#define IS_STCK_ADDR(a) ((((a) >= STCK_BASE) && ((a) < (STCK_BASE + STCK_SIZE))) ? 1:0)
#define IS_DATA_ADDR(a) (((a) >= DATA_BASE) ? 1: 0)
#endif /* __ASSEMBLY__ */

#endif /* __MEMMAP_H__ */
