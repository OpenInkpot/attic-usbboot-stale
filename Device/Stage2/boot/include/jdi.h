#ifndef __JDI_H__
#define __JDI_H__

#include "memmap.h"
#include "hand.h"
#include "flash_info.h"
#include "error.h"

#define TAP_MODE_ACC    0
#define TAP_MODE_EJTAG  1

typedef struct {
	int tap_mode;
	char *config_file;
	char *jdi_path;
	char data_file[256];
} jdi_t;

typedef struct {
	void *ptr;
	int len;
} mm_buf_t;

typedef struct {
	int burst;
	int write;
	int size;
	unsigned int addr;
	unsigned int burst_addr;
	unsigned int data;
} request_t;

extern int devfd;
extern jdi_t jdi_data;
extern request_t req_data;

extern hand_t hand __attribute__ ((aligned(4)));
extern flash_info_t flash_info __attribute__ ((aligned(4)));
extern unsigned char stack[STCK_SIZE] __attribute__ ((aligned(4)));

/* stub, data, stack, hand and flashinfo buffers */
extern mm_buf_t stubbuf, databuf, stackbuf, handbuf, flashinfobuf, nullbuf;

extern int hwreset_ms;

extern void show_data_progress(int offset);
extern void show_erase_progress(void);
extern int parse_config(const char *fname);
extern void parse_cmdline(int argc, char *argv[]);
extern void do_request(void);

static inline unsigned int str2num (const unsigned char *str)
{
	unsigned int num;
	char *p = NULL;

	switch (str[0])
	{
	case '0':
		switch (str[1])
		{
		case 'x':
		case 'X':
			num = strtoul(&str[2], &p, 16);
			break;
		default:			
			num = strtoul(&str[1], &p, 8);
		}
		break;
	default:
		num = strtoul (&str[0], &p, 0);
	}
	
	if (!p)
		return num;
	switch (*p)
	{
	case 'k':
	case 'K':
		num <<= 10;
		break;
	case 'm':
	case 'M':
		num <<= 20;
		break;
	}

	return num;
}

#endif /* __JDI_H__ */
