/*
 * cfi.c -- Common Flash Interface (CFI) driver
 *
 * Work with little-endian systems only.
 */

#include "flash.h"
#include "cfi.h"

typedef union {
	unsigned char c;
	unsigned short w;
	unsigned long l;
	unsigned long long ll;
} cfiword_t;

typedef union {
	volatile unsigned char *cp;
	volatile unsigned short *wp;
	volatile unsigned long *lp;
	volatile unsigned long long *llp;
} cfiptr_t;

// prototypes
static int cfi_single_write(flash_info_t *info, void *buf, void *addr, int len);
static int cfi_buffer_write(flash_info_t *info, void *buf, void *addr, int len);

/*-----------------------------------------------------------------------
 * create an address based on the offset and the port width
 */
static inline u8 *flash_make_addr (flash_info_t * info, u32 start, u32 offset)
{
	return ((u8 *) (start + (offset * info->portwidth)));
}

/*-----------------------------------------------------------------------
 * make a proper sized command based on the port and chip widths
 */
static inline void flash_make_cmd (flash_info_t * info, u8 cmd, void *cmdbuf)
{
	int i;
	u16 stmpw;
	u32 stmpi;

	u8 *cp = (u8 *) cmdbuf;

	for (i = 0; i < info->portwidth; i++)
		*cp++ = ((i + 1) & (info->chipwidth - 1)) ? '\0' : cmd;

	// swap for little-endian
	switch (info->portwidth) {
	case FLASH_CFI_8BIT:
		break;
	case FLASH_CFI_16BIT:
		stmpw = *(u16 *) cmdbuf;
		*(u16 *) cmdbuf = __swab16 (stmpw);
		break;
	case FLASH_CFI_32BIT:
		stmpi = *(u32 *) cmdbuf;
		*(u32 *) cmdbuf = __swab32 (stmpi);
		break;
	}
}

/*
 * Write a proper sized command to the correct address
 */
static inline void flash_write_cmd (flash_info_t *info, u32 start, u32 offset, u8 cmd)
{
	volatile cfiptr_t addr;
	cfiword_t cword;

	addr.cp = flash_make_addr (info, start, offset);
	flash_make_cmd (info, cmd, &cword);
	switch (info->portwidth) {
	case FLASH_CFI_8BIT:
		*addr.cp = cword.c;
		break;
	case FLASH_CFI_16BIT:
		*addr.wp = cword.w;
		break;
	case FLASH_CFI_32BIT:
		*addr.lp = cword.l;
		break;
	case FLASH_CFI_64BIT:
		*addr.llp = cword.ll;
		break;
	}
}

/*-----------------------------------------------------------------------
 */
static inline int flash_isequal (flash_info_t * info, u32 start, u32 offset, u8 cmd)
{
	cfiptr_t cptr;
	cfiword_t cword;
	int retval;

	cptr.cp = flash_make_addr (info, start, offset);
	flash_make_cmd (info, cmd, &cword);

	switch (info->portwidth) {
	case FLASH_CFI_8BIT:
		retval = (cptr.cp[0] == cword.c);
		break;
	case FLASH_CFI_16BIT:
		retval = (cptr.wp[0] == cword.w);
		break;
	case FLASH_CFI_32BIT:
		retval = (cptr.lp[0] == cword.l);
		break;
	case FLASH_CFI_64BIT:
		retval = (cptr.llp[0] == cword.ll);
		break;
	default:
		retval = 0;
		break;
	}
	return retval;
}

/*-----------------------------------------------------------------------
 * read a character at a port width address
 */
static inline u8 flash_read_uchar (flash_info_t * info, u32 offset)
{
	u8 *cp;
	cp = flash_make_addr (info, info->start, offset);
	return (cp[0]);
}

/*-----------------------------------------------------------------------
 * read a short word
 */
static inline u16 flash_read_ushort (flash_info_t * info, u32 start, u32 offset)
{
	u8 *addr;
	u16 retval;

	addr = flash_make_addr (info, start, offset);
	retval = ((addr[(info->portwidth)] << 8) | addr[0]);

	return retval;
}

/*-----------------------------------------------------------------------
 * read a long word by picking the least significant byte of each maiximum
 * port size word.
 */
static inline u32 flash_read_long (flash_info_t * info, u32 start, u32 offset)
{
	u8 *addr;
	u32 retval;

	addr = flash_make_addr (info, start, offset);
	retval = (addr[0]) | (addr[(info->portwidth)] << 8) |
		(addr[(2 * info->portwidth)] << 16) | (addr[(3 * info->portwidth)] << 24);

	return retval;
}

/*-----------------------------------------------------------------------
 */
static inline int flash_isset (flash_info_t * info, u32 start, u32 offset, u8 cmd)
{
	cfiptr_t cptr;
	cfiword_t cword;
	int retval;

	cptr.cp = flash_make_addr (info, start, offset);
	flash_make_cmd (info, cmd, &cword);
	switch (info->portwidth) {
	case FLASH_CFI_8BIT:
		retval = ((cptr.cp[0] & cword.c) == cword.c);
		break;
	case FLASH_CFI_16BIT:
		retval = ((cptr.wp[0] & cword.w) == cword.w);
		break;
	case FLASH_CFI_32BIT:
		retval = ((cptr.lp[0] & cword.l) == cword.l);
		break;
	case FLASH_CFI_64BIT:
		retval = ((cptr.llp[0] & cword.ll) == cword.ll);
		break;
	default:
		retval = 0;
		break;
	}
	return retval;
}

/*-----------------------------------------------------------------------
 * detect if flash is compatible with the Common Flash Interface (CFI)
 * http://www.jedec.org/download/search/jesd68.pdf
 *
 */
static int flash_detect_cfi (flash_info_t * info)
{
	int i;

	for (info->portwidth = FLASH_CFI_8BIT;
	     info->portwidth <= FLASH_CFI_32BIT; info->portwidth <<= 1) {
		for (info->chipwidth = FLASH_CFI_BY8;
		     info->chipwidth <= info->portwidth;
		     info->chipwidth <<= 1) {
			flash_write_cmd (info, info->start, 0, FLASH_CMD_RESET);
			flash_write_cmd (info, info->start, FLASH_OFFSET_CFI, FLASH_CMD_CFI);
			for (i = 0; i < 100; i++); /* delay */
			if (flash_isequal (info, info->start, FLASH_OFFSET_CFI_RESP, 'Q')
			    && flash_isequal (info, info->start, FLASH_OFFSET_CFI_RESP + 1, 'R')
			    && flash_isequal (info, info->start, FLASH_OFFSET_CFI_RESP + 2, 'Y')) {
				info->interface = flash_read_ushort (info, info->start, FLASH_OFFSET_INTERFACE);
				return 1;
			}
		}
	}
	return 0;
}

static void cfi_query (flash_info_t *info)
{
	int i, j;
	u32 sect_cnt;
	unsigned long sector;
	unsigned long tmp;
	int size_ratio;
	u8 num_erase_regions;
	int erase_region_size;
	int erase_region_count;

	info->sector_start[0] = info->start;

	if (flash_detect_cfi (info)) {
		info->vendor = flash_read_ushort (info, info->start, FLASH_OFFSET_PRIMARY_VENDOR);
		switch (info->vendor) {
		case CFI_CMDSET_INTEL_STANDARD:
		case CFI_CMDSET_INTEL_EXTENDED:
		default:
			info->cmd_reset = FLASHWORD(info, FLASH_CMD_RESET);
			break;
		case CFI_CMDSET_AMD_STANDARD:
		case CFI_CMDSET_AMD_EXTENDED:
			info->cmd_reset = FLASHWORD(info, AMD_CMD_RESET);
			break;
		}

		size_ratio = info->portwidth / info->chipwidth;
		/* if the chip is x8/x16 reduce the ratio by half */
		if ((info->interface == FLASH_CFI_X8X16)
		    && (info->chipwidth == FLASH_CFI_BY8)) {
			size_ratio >>= 1;
		}
		num_erase_regions = flash_read_uchar (info, FLASH_OFFSET_NUM_ERASE_REGIONS);
		sect_cnt = 0;
		sector = info->start;
		for (i = 0; i < num_erase_regions; i++) {
			tmp = flash_read_long (info, info->start,
					       FLASH_OFFSET_ERASE_REGIONS +
					       i * 4);
			erase_region_count = (tmp & 0xffff) + 1;
			tmp >>= 16;
			erase_region_size =
				(tmp & 0xffff) ? ((tmp & 0xffff) * 256) : 128;
			for (j = 0; j < erase_region_count; j++) {
				info->sector_start[sect_cnt] = sector;
				info->sector_size[sect_cnt] = (erase_region_size * size_ratio);
				sector += info->sector_size[sect_cnt];
				sect_cnt++;
			}
		}

		info->sector_count = sect_cnt;
		/* multiply the size by the number of chips */
		info->chipsize = (1 << flash_read_uchar (info, FLASH_OFFSET_SIZE)) * size_ratio;
		info->buffer_size = (1 << flash_read_ushort (info, info->start, FLASH_OFFSET_BUFFER_SIZE));
		tmp = 1 << flash_read_uchar (info, FLASH_OFFSET_ETOUT);
		info->erase_blk_tout = (tmp * (1 << flash_read_uchar (info, FLASH_OFFSET_EMAX_TOUT)));
		tmp = 1 << flash_read_uchar (info, FLASH_OFFSET_WBTOUT);
		info->buffer_write_tout = (tmp * (1 << flash_read_uchar (info, FLASH_OFFSET_WBMAX_TOUT)));
		tmp = 1 << flash_read_uchar (info, FLASH_OFFSET_WTOUT);
		info->write_tout = (tmp * (1 << flash_read_uchar (info, FLASH_OFFSET_WMAX_TOUT))) / 1000;
		info->flash_id = FLASH_MAN_CFI;
		if ((info->interface == FLASH_CFI_X8X16) && (info->chipwidth == FLASH_CFI_BY8)) {
			info->portwidth >>= 1;	/* XXX - Need to test on x8/x16 in parallel. */
		}
	}

	flash_write_cmd (info, info->start, 0, FLASH_CMD_RESET);
}

/*----------------------------------------------------------------------
 * Flash operation routines
 */
int cfi_init(flash_info_t *info)
{
	info->flash_id = FLASH_UNKNOWN;
	cfi_query(info);

	if (info->flash_id == FLASH_UNKNOWN)
		return ERR_UNKNOWN_FLASH_VENDOR;

	return ERR_OK;
}

int cfi_write(flash_info_t *info, void *buf, void *addr, int len)
{
	u32 dest = (u32)addr;

	/* unaligned destination addresses are invalid  */
	if ((dest - (dest & ~(info->portwidth - 1))) != 0) {
		return ERR_ALIGN;
	}

	if ((info->vendor == CFI_CMDSET_AMD_STANDARD) ||
	    (info->vendor == CFI_CMDSET_AMD_EXTENDED))
		return cfi_single_write(info, buf, addr, len);
	else
		return cfi_buffer_write(info, buf, addr, len);
}

/*-------------------------------------------------------------------------
 * %@-&%#!
 * Ugly implementation of the next routines!!!
 * We want to avoid any procedure calls from one to another, since this
 * will induce many stack push&pop operations. 
 * The stack was mapped to external EJTAG memory (Cacheable&Write-Through), 
 * and too many stack push&pop operations will reduce the Flash programming 
 * speed. 2006-02-09, wjl.
 */

int cfi_erase_sector(flash_info_t *info, void *saddr, int size)
{
	volatile u8 *cp;
	volatile u16 *wp;
	volatile u32 *lp;
	u32 stat = 0, stat2 = 0, sect, sectsize;
	int timeout = 0x07ffffff;

	cp = (volatile u8 *)((u32)saddr);
	wp = (volatile u16 *)((u32)saddr);
	lp = (volatile u32 *)((u32)saddr);

	switch (info->vendor) {
	case CFI_CMDSET_INTEL_STANDARD:
	case CFI_CMDSET_INTEL_EXTENDED:
		switch (info->portwidth) {
		case FLASH_CFI_8BIT:
			*cp = FLASHWORD(info, FLASH_CMD_CLEAR_STATUS);
			*cp = FLASHWORD(info, FLASH_CMD_BLOCK_ERASE);
			*cp = FLASHWORD(info, FLASH_CMD_ERASE_CONFIRM);
			break;
		case FLASH_CFI_16BIT:
			*wp = FLASHWORD(info, FLASH_CMD_CLEAR_STATUS);
			*wp = FLASHWORD(info, FLASH_CMD_BLOCK_ERASE);
			*wp = FLASHWORD(info, FLASH_CMD_ERASE_CONFIRM);
			break;
		case FLASH_CFI_32BIT:
			*lp = FLASHWORD(info, FLASH_CMD_CLEAR_STATUS);
			*lp = FLASHWORD(info, FLASH_CMD_BLOCK_ERASE);
			*lp = FLASHWORD(info, FLASH_CMD_ERASE_CONFIRM);
			break;
		}
		break;
	case CFI_CMDSET_AMD_STANDARD:
	case CFI_CMDSET_AMD_EXTENDED:
		switch (info->portwidth) {
		case FLASH_CFI_8BIT:
			//unlock seq
			*(cp + AMD_ADDR_START) = FLASHWORD(info, AMD_CMD_UNLOCK_START);
			*(cp + AMD_ADDR_ACK) = FLASHWORD(info, AMD_CMD_UNLOCK_ACK);
			
			*(cp + AMD_ADDR_ERASE_START) = FLASHWORD(info, AMD_CMD_ERASE_START);

			//unlock seq
			*(cp + AMD_ADDR_START) = FLASHWORD(info, AMD_CMD_UNLOCK_START);
			*(cp + AMD_ADDR_ACK) = FLASHWORD(info, AMD_CMD_UNLOCK_ACK);

			*(cp + 0) = FLASHWORD(info, AMD_CMD_ERASE_SECTOR);
			break;
		case FLASH_CFI_16BIT:
			//unlock seq
			*(wp + AMD_ADDR_START) = FLASHWORD(info, AMD_CMD_UNLOCK_START);
			*(wp + AMD_ADDR_ACK) = FLASHWORD(info, AMD_CMD_UNLOCK_ACK);
			
			*(wp + AMD_ADDR_ERASE_START) = FLASHWORD(info, AMD_CMD_ERASE_START);

			//unlock seq
			*(wp + AMD_ADDR_START) = FLASHWORD(info, AMD_CMD_UNLOCK_START);
			*(wp + AMD_ADDR_ACK) = FLASHWORD(info, AMD_CMD_UNLOCK_ACK);

			*(wp + 0) = FLASHWORD(info, AMD_CMD_ERASE_SECTOR);
			break;
		case FLASH_CFI_32BIT:
			//unlock seq
			*(lp + AMD_ADDR_START) = FLASHWORD(info, AMD_CMD_UNLOCK_START);
			*(lp + AMD_ADDR_ACK) = FLASHWORD(info, AMD_CMD_UNLOCK_ACK);
			
			*(lp + AMD_ADDR_ERASE_START) = FLASHWORD(info, AMD_CMD_ERASE_START);

			//unlock seq
			*(lp + AMD_ADDR_START) = FLASHWORD(info, AMD_CMD_UNLOCK_START);
			*(lp + AMD_ADDR_ACK) = FLASHWORD(info, AMD_CMD_UNLOCK_ACK);

			*(lp + 0) = FLASHWORD(info, AMD_CMD_ERASE_SECTOR);
			break;
		}
		break;
	default:
		break;
	}

	// check status: AMD types check toggle bit, INTEL types check ready bit
	stat = 0;
	timeout = 0x07ffffff;
	if ((info->vendor == CFI_CMDSET_AMD_STANDARD) ||
	    (info->vendor == CFI_CMDSET_AMD_EXTENDED)) {
		switch (info->portwidth) {
		case FLASH_CFI_8BIT:
			stat = *cp;
			stat2 = *cp;
			break;
		case FLASH_CFI_16BIT:
			stat = *wp;
			stat2 = *wp;
			break;
		case FLASH_CFI_32BIT:
			stat = *lp;
			stat2 = *lp;
			break;
		}
		while ((stat & FLASHWORD(info, AMD_STATUS_TOGGLE)) !=
		       (stat2 & FLASHWORD(info, AMD_STATUS_TOGGLE))) {
			if (--timeout == 0)
				break;
			switch (info->portwidth) {
			case FLASH_CFI_8BIT:
				stat = *cp;
				stat2 = *cp;
				break;
			case FLASH_CFI_16BIT:
				stat = *wp;
				stat2 = *wp;
				break;
			case FLASH_CFI_32BIT:
				stat = *lp;
				stat2 = *lp;
				break;
			}
		}
	}
	else { // INTEL types
		while((stat & FLASHWORD(info, FLASH_STATUS_DONE)) 
		      != FLASHWORD(info, FLASH_STATUS_DONE)) {
			if (--timeout == 0)
				break;
			switch (info->portwidth) {
			case FLASH_CFI_8BIT:
				stat = *cp;
				break;
			case FLASH_CFI_16BIT:
				stat = *wp;
				break;
			case FLASH_CFI_32BIT:
				stat = *lp;
				break;
			}
		}
	}

	// reset the device
	switch (info->portwidth) {
	case FLASH_CFI_8BIT:
		*cp = info->cmd_reset;
		break;
	case FLASH_CFI_16BIT:
		*wp = info->cmd_reset;
		break;
	case FLASH_CFI_32BIT:
		*lp = info->cmd_reset;
		break;
	}

	if (timeout == 0)
		return ERR_ERASE_ERROR;

	/*
	 * check if erasing passed ?
	 */
	sect = find_sector(info, (u32)saddr);
	sectsize = info->sector_size[sect];
	while (sectsize > 0) {
		switch (info->portwidth) {
		case FLASH_CFI_8BIT:
			if (*cp++ != 0xff)
				return ERR_ERASE_ERROR;
			break;
		case FLASH_CFI_16BIT:
			if (*wp++ != 0xffff)
				return ERR_ERASE_ERROR;
			break;
		case FLASH_CFI_32BIT:
			if (*lp++ != 0xffffffff)
				return ERR_ERASE_ERROR;
			break;
		}
		sectsize -= info->portwidth;
	}
	return ERR_OK;
}

int cfi_erase_chip(flash_info_t *info)
{
	return ERR_NOT_SUPPORT;
}

static int cfi_single_write(flash_info_t *info, void *buf, void *addr, int len)
{
	volatile u8 *cp; // control addresses
	volatile u16 *wp;
	volatile u32 *lp;
	volatile u8 *cps; // src addresses
	volatile u16 *wps;
	volatile u32 *lps;
	volatile u8 *cpd; // dst addresses
	volatile u16 *wpd;
	volatile u32 *lpd;

	u32 src, dest, val;
	u32 stat = 0, stat2 = 0;
	int timeout = 0x07ffffff;
	int i;

	// control addresses
	cp = (volatile u8 *)info->sector_start[0];
	wp = (volatile u16 *)info->sector_start[0];
	lp = (volatile u32 *)info->sector_start[0];

	// src addresses
	src = (u32)buf;
	cps = (volatile u8 *)src;
	wps = (volatile u16 *)src;
	lps = (volatile u32 *)src;

	// dst addresses
	dest = (u32)addr;
	cpd = (volatile u8 *)dest;
	wpd = (volatile u16 *)dest;
	lpd = (volatile u32 *)dest;

	/*
	 * handle the big chunk
	 */
	while (len >= info->portwidth) {

		// issue write command
		switch (info->vendor) {
		case CFI_CMDSET_INTEL_EXTENDED:
		case CFI_CMDSET_INTEL_STANDARD:
			// clear status
			// issue write command
			switch (info->portwidth) {
			case FLASH_CFI_8BIT:
				*cp = FLASHWORD(info, FLASH_CMD_CLEAR_STATUS);
				*cp = FLASHWORD(info, FLASH_CMD_WRITE);
				break;
			case FLASH_CFI_16BIT:
				*wp = FLASHWORD(info, FLASH_CMD_CLEAR_STATUS);
				*wp = FLASHWORD(info, FLASH_CMD_WRITE);
				break;
			case FLASH_CFI_32BIT:
				*lp = FLASHWORD(info, FLASH_CMD_CLEAR_STATUS);
				*lp = FLASHWORD(info, FLASH_CMD_WRITE);
				break;
			}
			break;
		case CFI_CMDSET_AMD_EXTENDED:
		case CFI_CMDSET_AMD_STANDARD:
			// unlock seq
			switch (info->portwidth) {
			case FLASH_CFI_8BIT:
				*(cp + AMD_ADDR_START) = FLASHWORD(info, AMD_CMD_UNLOCK_START);
				*(cp + AMD_ADDR_ACK) = FLASHWORD(info, AMD_CMD_UNLOCK_ACK);
				break;
			case FLASH_CFI_16BIT:
				*(wp + AMD_ADDR_START) = FLASHWORD(info, AMD_CMD_UNLOCK_START);
				*(wp + AMD_ADDR_ACK) = FLASHWORD(info, AMD_CMD_UNLOCK_ACK);
				break;
			case FLASH_CFI_32BIT:
				*(lp + AMD_ADDR_START) = FLASHWORD(info, AMD_CMD_UNLOCK_START);
				*(lp + AMD_ADDR_ACK) = FLASHWORD(info, AMD_CMD_UNLOCK_ACK);
				break;
			}

			// issue write command
			switch (info->portwidth) {
			case FLASH_CFI_8BIT:
				*(cp + AMD_ADDR_START) = FLASHWORD(info, AMD_CMD_WRITE);
				break;
			case FLASH_CFI_16BIT:
				*(wp + AMD_ADDR_START) = FLASHWORD(info, AMD_CMD_WRITE);
				break;
			case FLASH_CFI_32BIT:
				*(lp + AMD_ADDR_START) = FLASHWORD(info, AMD_CMD_WRITE);
				break;
			}

			break;
		}

		// write data
		switch (info->portwidth) {
		case FLASH_CFI_8BIT:
			*cpd = *cps;
			break;
		case FLASH_CFI_16BIT:
			*wpd = *wps;
			break;
		case FLASH_CFI_32BIT:
			*lpd = *lps;
			break;
		}

		// check status
		stat = 0;
		timeout = 0x07ffffff;
		if ((info->vendor == CFI_CMDSET_AMD_STANDARD) ||
		    (info->vendor == CFI_CMDSET_AMD_EXTENDED)) {
			switch (info->portwidth) {
			case FLASH_CFI_8BIT:
				stat = *cp;
				stat2 = *cp;
				break;
			case FLASH_CFI_16BIT:
				stat = *wp;
				stat2 = *wp;
				break;
			case FLASH_CFI_32BIT:
				stat = *lp;
				stat2 = *lp;
				break;
			}
			while ((stat & FLASHWORD(info, AMD_STATUS_TOGGLE)) !=
			       (stat2 & FLASHWORD(info, AMD_STATUS_TOGGLE))) {
				if (--timeout == 0)
					break;
				switch (info->portwidth) {
				case FLASH_CFI_8BIT:
					stat = *cp;
					stat2 = *cp;
					break;
				case FLASH_CFI_16BIT:
					stat = *wp;
					stat2 = *wp;
					break;
				case FLASH_CFI_32BIT:
					stat = *lp;
					stat2 = *lp;
					break;
				}
			}
		}
		else { // INTEL types
			while((stat & FLASHWORD(info, FLASH_STATUS_DONE)) 
			      != FLASHWORD(info, FLASH_STATUS_DONE)) {
				if (--timeout == 0)
					break;
				switch (info->portwidth) {
				case FLASH_CFI_8BIT:
					stat = *cp;
					break;
				case FLASH_CFI_16BIT:
					stat = *wp;
					break;
				case FLASH_CFI_32BIT:
					stat = *lp;
					break;
				}
			}
		}

		// reset the device
		switch (info->portwidth) {
		case FLASH_CFI_8BIT:
			*cp = info->cmd_reset;
			break;
		case FLASH_CFI_16BIT:
			*wp = info->cmd_reset;
			break;
		case FLASH_CFI_32BIT:
			*lp = info->cmd_reset;
			break;
		}

		if (timeout == 0) {
			return ERR_TIMOUT;
		}

		// verify the data - also increments the pointers.
		switch (info->portwidth) {
		case FLASH_CFI_8BIT:
			if (*cpd++ != *cps++)
				return ERR_WRITE_VERIFY;
			break;
		case FLASH_CFI_16BIT:
			if (*wpd++ != *wps++)
				return ERR_WRITE_VERIFY;
			break;
		case FLASH_CFI_32BIT:
			if (*lpd++ != *lps++)
				return ERR_WRITE_VERIFY;
			break;
		}

		// increment addr
		src += info->portwidth;
		dest += info->portwidth;
		len -= info->portwidth;
	}

	if (len == 0) {
		return ERR_OK;
	}

	/*
	 * handle unaligned tail bytes
	 */
	cps = (volatile u8 *)src;
	cpd = (volatile u8 *)dest;
	val = 0;
	for (i = 0; (i < info->portwidth) && (len > 0); i++) {
		val |= (*cps++ << (i*8));
		len--;
	}
	for (; i < info->portwidth; i++) {
		val |= (*(cpd + i) << (i*8));
	}

	return cfi_single_write(info, (void *)&val, (void *)dest, info->portwidth);
}

static int cfi_buffer_write(flash_info_t *info, void *buf, void *addr, int len)
{
	volatile u8 *cp; // sector addresses
	volatile u16 *wp;
	volatile u32 *lp;
	volatile u8 *cps; // src addresses
	volatile u16 *wps;
	volatile u32 *lps;
	volatile u8 *cpd; // dst addresses
	volatile u16 *wpd;
	volatile u32 *lpd;

	u32 src, dest, val;
	u32 stat = 0, stat2 = 0;
	int timeout = 0x07ffffff;
	int wc, cnt = 0, tmp = 0, sector;
	int buffered_size;
	int i;

	// src addresses
	src = (u32)buf;
	cps = (volatile u8 *)src;
	wps = (volatile u16 *)src;
	lps = (volatile u32 *)src;

	// dst addresses
	dest = (u32)addr;
	cpd = (volatile u8 *)dest;
	wpd = (volatile u16 *)dest;
	lpd = (volatile u32 *)dest;

	/*
	 * handle the big chunk
	 */
	buffered_size = (info->portwidth / info->chipwidth);
	buffered_size *= info->buffer_size;
	while (len >= info->portwidth) {
		wc = buffered_size > len ? len : buffered_size;

		// find out which sector the dest addr belonged to
		sector = find_sector(info, dest);

		// get sector address
		cp = (volatile u8 *)info->sector_start[sector];
		wp = (volatile u16 *)info->sector_start[sector];
		lp = (volatile u32 *)info->sector_start[sector];

		// issue FLASH_CMD_CLEAR_STATUS & FLASH_CMD_WRITE_TO_BUFFER
		switch (info->portwidth) {
		case FLASH_CFI_8BIT:
			*cp = FLASHWORD(info, FLASH_CMD_CLEAR_STATUS);
			*cp = FLASHWORD(info, FLASH_CMD_WRITE_TO_BUFFER);
			break;
		case FLASH_CFI_16BIT:
			*wp = FLASHWORD(info, FLASH_CMD_CLEAR_STATUS);
			*wp = FLASHWORD(info, FLASH_CMD_WRITE_TO_BUFFER);
			break;
		case FLASH_CFI_32BIT:
			*lp = FLASHWORD(info, FLASH_CMD_CLEAR_STATUS);
			*lp = FLASHWORD(info, FLASH_CMD_WRITE_TO_BUFFER);
			break;
		}
		
		// check status
		stat = 0;
		timeout = 0x07ffffff;
		if ((info->vendor == CFI_CMDSET_AMD_STANDARD) ||
		    (info->vendor == CFI_CMDSET_AMD_EXTENDED)) {
			switch (info->portwidth) {
			case FLASH_CFI_8BIT:
				stat = *cp;
				stat2 = *cp;
				break;
			case FLASH_CFI_16BIT:
				stat = *wp;
				stat2 = *wp;
				break;
			case FLASH_CFI_32BIT:
				stat = *lp;
				stat2 = *lp;
				break;
			}
			while ((stat & FLASHWORD(info, AMD_STATUS_TOGGLE)) !=
			       (stat2 & FLASHWORD(info, AMD_STATUS_TOGGLE))) {
				if (--timeout == 0)
					break;
				switch (info->portwidth) {
				case FLASH_CFI_8BIT:
					stat = *cp;
					stat2 = *cp;
					break;
				case FLASH_CFI_16BIT:
					stat = *wp;
					stat2 = *wp;
					break;
				case FLASH_CFI_32BIT:
					stat = *lp;
					stat2 = *lp;
					break;
				}
			}
		}
		else {
			while((stat & FLASHWORD(info, FLASH_STATUS_DONE)) 
			      != FLASHWORD(info, FLASH_STATUS_DONE)) {
				if (--timeout == 0)
					break;
				switch (info->portwidth) {
				case FLASH_CFI_8BIT:
					stat = *cp;
					break;
				case FLASH_CFI_16BIT:
					stat = *wp;
					break;
				case FLASH_CFI_32BIT:
					stat = *lp;
					break;
				}
			}
		}

		if (timeout == 0) {
			// reset the device & clear status
			switch (info->portwidth) {
			case FLASH_CFI_8BIT:
				*cp = info->cmd_reset;
				*cp = FLASHWORD(info, FLASH_CMD_CLEAR_STATUS);
				break;
			case FLASH_CFI_16BIT:
				*wp = info->cmd_reset;
				*wp = FLASHWORD(info, FLASH_CMD_CLEAR_STATUS);
				break;
			case FLASH_CFI_32BIT:
				*lp = info->cmd_reset;
				*lp = FLASHWORD(info, FLASH_CMD_CLEAR_STATUS);
				break;
			}
			return ERR_TIMOUT;
		}

		/* reduce the number of loops by the width of the port
		 * issue the write count.
		 */
		switch (info->portwidth) {
		case FLASH_CFI_8BIT:
			cnt = wc;
			tmp = (u8)cnt - 1;
			*cp = FLASHWORD(info, tmp);
			break;
		case FLASH_CFI_16BIT:
			cnt = (wc >> 1);
			tmp = (u8)cnt - 1;
			*wp = FLASHWORD(info, tmp);
			break;
		case FLASH_CFI_32BIT:
			cnt = (wc >> 2);
			tmp = (u8)cnt - 1;
			*lp = FLASHWORD(info, tmp);
			break;
		}

		// write to buffer
		for (i = 0; i < cnt; i++) {
			switch (info->portwidth) {
			case FLASH_CFI_8BIT:
				*(cpd + i) = *(cps + i);
				break;
			case FLASH_CFI_16BIT:
				*(wpd + i) = *(wps + i);
				break;
			case FLASH_CFI_32BIT:
				*(lpd + i) = *(lps + i);
				break;
			}
		}

		// issue confirm
		switch (info->portwidth) {
		case FLASH_CFI_8BIT:
			*cp = FLASHWORD(info, FLASH_CMD_WRITE_BUFFER_CONFIRM);
			break;
		case FLASH_CFI_16BIT:
			*wp = FLASHWORD(info, FLASH_CMD_WRITE_BUFFER_CONFIRM);
			break;
		case FLASH_CFI_32BIT:
			*lp = FLASHWORD(info, FLASH_CMD_WRITE_BUFFER_CONFIRM);
			break;
		}

		// check status
		stat = 0;
		timeout = 0x07ffffff;
		if ((info->vendor == CFI_CMDSET_AMD_STANDARD) ||
		    (info->vendor == CFI_CMDSET_AMD_EXTENDED)) {
			switch (info->portwidth) {
			case FLASH_CFI_8BIT:
				stat = *cp;
				stat2 = *cp;
				break;
			case FLASH_CFI_16BIT:
				stat = *wp;
				stat2 = *wp;
				break;
			case FLASH_CFI_32BIT:
				stat = *lp;
				stat2 = *lp;
				break;
			}
			while ((stat & FLASHWORD(info, AMD_STATUS_TOGGLE)) !=
			       (stat2 & FLASHWORD(info, AMD_STATUS_TOGGLE))) {
				if (--timeout == 0)
					break;
				switch (info->portwidth) {
				case FLASH_CFI_8BIT:
					stat = *cp;
					stat2 = *cp;
					break;
				case FLASH_CFI_16BIT:
					stat = *wp;
					stat2 = *wp;
					break;
				case FLASH_CFI_32BIT:
					stat = *lp;
					stat2 = *lp;
					break;
				}
			}
		}
		else {
			while((stat & FLASHWORD(info, FLASH_STATUS_DONE)) 
			      != FLASHWORD(info, FLASH_STATUS_DONE)) {
				if (--timeout == 0)
					break;
				switch (info->portwidth) {
				case FLASH_CFI_8BIT:
					stat = *cp;
					break;
				case FLASH_CFI_16BIT:
					stat = *wp;
					break;
				case FLASH_CFI_32BIT:
					stat = *lp;
					break;
				}
			}
		}

		// reset device & clear status
		switch (info->portwidth) {
		case FLASH_CFI_8BIT:
			*cp = info->cmd_reset;
			*cp = FLASHWORD(info, FLASH_CMD_CLEAR_STATUS);
			break;
		case FLASH_CFI_16BIT:
			*wp = info->cmd_reset;
			*wp = FLASHWORD(info, FLASH_CMD_CLEAR_STATUS);
			break;
		case FLASH_CFI_32BIT:
			*lp = info->cmd_reset;
			*lp = FLASHWORD(info, FLASH_CMD_CLEAR_STATUS);
			break;
		}

		if (timeout == 0) {
			return ERR_TIMOUT;
		}

		// verify the data - also increments the pointers.
		for (i = 0; i < cnt; i++) {
			switch (info->portwidth) {
			case FLASH_CFI_8BIT:
				if (*cpd++ != *cps++)
					return ERR_WRITE_VERIFY;
				break;
			case FLASH_CFI_16BIT:
				if (*wpd++ != *wps++)
					return ERR_WRITE_VERIFY;
				break;
			case FLASH_CFI_32BIT:
				if (*lpd++ != *lps++)
					return ERR_WRITE_VERIFY;
				break;
			}
		}

		// increment addr
		wc -= wc & (info->portwidth - 1);
		src += wc;
		dest += wc;
		len -= wc;
	}

	if (len == 0) {
		return ERR_OK;
	}

	/*
	 * handle unaligned tail bytes
	 */
	cps = (volatile u8 *)src;
	cpd = (volatile u8 *)dest;
	val = 0;
	for (i = 0; (i < info->portwidth) && (len > 0); i++) {
		val |= (*cps++ << (i*8));
		len--;
	}
	for (; i < info->portwidth; i++) {
		val |= (*(cpd + i) << (i*8));
	}

	return cfi_single_write(info, (void *)&val, (void *)dest, info->portwidth);
}
