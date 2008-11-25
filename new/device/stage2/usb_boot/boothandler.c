/* USB_BOOT Handle routines*/

#include"jz4740.h"
#include "usb.h" 
#include "error.h"
//#include "flash.h"
#include "usb_boot.h"
#include "hand.h"
#include "nandflash.h"
#include "udc.h"
#define dprintf(x) serial_puts(x)
//printf(x)

unsigned int (*nand_query)(u8 *);
int (*nand_init)(int bus_width, int row_cycle, int page_size, int page_per_block,
		 int,int,int,int);
int (*nand_fini)(void);
u32 (*nand_program)(void *context, int spage, int pages,int option);
u32 (*nand_erase)(int blk_num, int sblk, int force);
u32 (*nand_read)(void *buf, u32 startpage, u32 pagenum,int option);
u32 (*nand_read_oob)(void *buf, u32 startpage, u32 pagenum);
u32 (*nand_read_raw)(void *buf, u32 startpage, u32 pagenum,int);
u32 (*nand_mark_bad) (int bad);
void (*nand_enable) (unsigned int csn);
void (*nand_disable) (unsigned int csn);

hand_t Hand,*Hand_p;
//flash_info_t Info,*Info_p;
extern u32 Bulk_out_buf[BULK_OUT_BUF_SIZE];
extern u32 Bulk_in_buf[BULK_IN_BUF_SIZE];
extern u16 handshake_PKT[4];
u32 ret_dat;
extern udc_state;
u32 start_addr;  //program operation start address or sector
u32 ops_length;  //number of operation unit ,in byte or sector
u32 ram_addr;


void config_flash_info()
{
}

void dump_data(unsigned int *p, int size)
{
	int i;
	for(i = 0; i < size; i ++)
		serial_put_hex(*p++);
}

void config_hand()
{
	hand_t *hand_p;
	hand_p=( hand_t *)Bulk_out_buf;
	memcpy( &Hand, (unsigned char *)Bulk_out_buf, sizeof(hand_t));

#if 0
	Hand.nand_bw=hand_p->nand_bw;
	Hand.nand_rc=hand_p->nand_rc;
	Hand.nand_ps=hand_p->nand_ps;
	Hand.nand_ppb=hand_p->nand_ppb;
	Hand.nand_force_erase=hand_p->nand_force_erase;
	Hand.nand_pn=hand_p->nand_pn;
	Hand.nand_os=hand_p->nand_os;

	Hand.nand_eccpos=hand_p->nand_eccpos;
	Hand.nand_bbpos=hand_p->nand_bbpos;
	Hand.nand_bbpage=hand_p->nand_bbpage;
//	memcpy( &Hand.fw_args, (unsigned char *)(start_addr + 0x8), 32 );

//	serial_putc(Hand.nand_eccpos + 48);
//	serial_putc(Hand.nand_bbpos + 48);
//	serial_putc(Hand.nand_bbpage + 48);
//	dprintf("\n Hand : bw %d rc %d ps %d ppb %d erase %d pn %d os %d",
//		Hand.nand_bw,Hand.nand_rc,Hand.nand_ps,Hand.nand_ppb,Hand.nand_force_erase,Hand.nand_pn,Hand.nand_os);
	serial_put_hex(Hand.fw_args.cpu_id);
	serial_put_hex(Hand.fw_args.ext_clk);
#endif
}

int GET_CUP_INFO_Handle()
{
	char temp1[8]="Boot4740",temp2[8]="Boot4750";
//	dprintf("\n GET_CPU_INFO!");
	if ( Hand.fw_args.cpu_id == 0x4740 )
		HW_SendPKT(0,temp1,8);
	else
		HW_SendPKT(0,temp2,8);
	udc_state = IDLE;
	return ERR_OK; 
}
	       
int SET_DATA_ADDERSS_Handle(u8 *buf)
{
	USB_DeviceRequest *dreq = (USB_DeviceRequest *)buf;
	start_addr=(((u32)dreq->wValue)<<16)+(u32)dreq->wIndex;
//	dprintf("\n SET ADDRESS:");
//	serial_put_hex(start_addr);
	return ERR_OK;
}
		
int SET_DATA_LENGTH_Handle(u8 *buf)
{
	USB_DeviceRequest *dreq = (USB_DeviceRequest *)buf;
	ops_length=(((u32)dreq->wValue)<<16)+(u32)dreq->wIndex;
//	dprintf("\n DATA_LENGTH :");
//	serial_put_hex(ops_length);
	return ERR_OK;
}

int FLUSH_CACHES_Handle()
{
	return ERR_OK;
}
    
int PROGRAM_START1_Handle(u8 *buf)
{
	USB_DeviceRequest *dreq = (USB_DeviceRequest *)buf;
	ram_addr=(((u32)dreq->wValue)<<16)+(u32)dreq->wIndex;
//	dprintf("\n RAM ADDRESS :%x", ram_addr);
	return ERR_OK;
}

int PROGRAM_START2_Handle(u8 *buf)
{
	void (*f)(void);
	USB_DeviceRequest *dreq = (USB_DeviceRequest *)buf;
	f=(void *) ((((u32)dreq->wValue)<<16)+(u32)dreq->wIndex);
	__dcache_writeback_all();
	//stop udc connet before execute program!
	jz_writeb(USB_REG_POWER,0x0);   //High speed
//	dprintf("\n Execute program at %x",(u32)f);
	f();
	return ERR_OK;
}
	      
int NOR_OPS_Handle(u8 *buf)
{
	USB_DeviceRequest *dreq = (USB_DeviceRequest *)buf;
	return ERR_OK;
}

int NAND_OPS_Handle(u8 *buf)
{
	USB_DeviceRequest *dreq = (USB_DeviceRequest *)buf;
	u32 temp;
	int option;
	u8 CSn;

	CSn = (dreq->wValue>>4) & 0xff;
	option = (dreq->wValue>>12) & 0xff;
	nand_enable(CSn);
	switch ((dreq->wValue)&0xf)
	{
	case NAND_QUERY:
		dprintf("\n Request : NAND_QUERY!");
		nand_query(Bulk_in_buf);
		HW_SendPKT(1, Bulk_in_buf, 8);
		handshake_PKT[3]=(u16)ERR_OK;
		udc_state = BULK_IN;
		break;
	case NAND_INIT:
		dprintf("\n Request : NAND_INIT!");

		break;
	case NAND_MARK_BAD:
		dprintf("\n Request : NAND_MARK_BAD!");
		ret_dat = nand_mark_bad(start_addr);
		handshake_PKT[0] = (u16) ret_dat;
		handshake_PKT[1] = (u16) (ret_dat>>16);
		HW_SendPKT(1,handshake_PKT,sizeof(handshake_PKT));
		udc_state = IDLE;		

		break;
	case NAND_READ_OOB:
		dprintf("\n Request : NAND_READ_OOB!");
		memset(Bulk_in_buf,0,ops_length*Hand.nand_ps);
		ret_dat = nand_read_oob(Bulk_in_buf,start_addr,ops_length);
		handshake_PKT[0] = (u16) ret_dat;
		handshake_PKT[1] = (u16) (ret_dat>>16);
		HW_SendPKT(1,(u8 *)Bulk_in_buf,ops_length*Hand.nand_ps);
		udc_state = BULK_IN;		
		break;
	case NAND_READ_RAW:
		dprintf("\n Request : NAND_READ_RAW!");
		switch (option)
		{
		case OOB_ECC:
			nand_read_raw(Bulk_in_buf,start_addr,ops_length,option);
			HW_SendPKT(1,(u8 *)Bulk_in_buf,ops_length*(Hand.nand_ps + Hand.nand_os));
			handshake_PKT[0] = (u16) ret_dat;
			handshake_PKT[1] = (u16) (ret_dat>>16);
			udc_state = BULK_IN;
			break;
		default:
			nand_read_raw(Bulk_in_buf,start_addr,ops_length,option);
			HW_SendPKT(1,(u8 *)Bulk_in_buf,ops_length*Hand.nand_ps);
			handshake_PKT[0] = (u16) ret_dat;
			handshake_PKT[1] = (u16) (ret_dat>>16);
			udc_state = BULK_IN;
			break;
		}
		break;
	case NAND_ERASE:
		dprintf("\n Request : NAND_ERASE!");
		ret_dat = nand_erase(ops_length,start_addr,
			   Hand.nand_force_erase);
		handshake_PKT[0] = (u16) ret_dat;
		handshake_PKT[1] = (u16) (ret_dat>>16);
		HW_SendPKT(1,handshake_PKT,sizeof(handshake_PKT));
		udc_state = IDLE;
		break;
	case NAND_READ:
		dprintf("\n Request : NAND_READ!");
//		dprintf("\n Option : %x",option);
		switch (option)
		{
		case 	OOB_ECC:
			ret_dat = nand_read(Bulk_in_buf,start_addr,ops_length,OOB_ECC);
			handshake_PKT[0] = (u16) ret_dat;
			handshake_PKT[1] = (u16) (ret_dat>>16);
			HW_SendPKT(1,(u8 *)Bulk_in_buf,ops_length*(Hand.nand_ps + Hand.nand_os ));
			udc_state = BULK_IN;
			break;
		case 	OOB_NO_ECC:
			ret_dat = nand_read(Bulk_in_buf,start_addr,ops_length,OOB_NO_ECC);
			handshake_PKT[0] = (u16) ret_dat;
			handshake_PKT[1] = (u16) (ret_dat>>16);
			HW_SendPKT(1,(u8 *)Bulk_in_buf,ops_length*(Hand.nand_ps + Hand.nand_os ));
			udc_state = BULK_IN;
			break;
		case 	NO_OOB:
			ret_dat = nand_read(Bulk_in_buf,start_addr,ops_length,NO_OOB);
			handshake_PKT[0] = (u16) ret_dat;
			handshake_PKT[1] = (u16) (ret_dat>>16);
			HW_SendPKT(1,(u8 *)Bulk_in_buf,ops_length*Hand.nand_ps);
			udc_state = BULK_IN;
			break;
		}

		break;
	case NAND_PROGRAM:
		dprintf("\n Request : NAND_PROGRAM!");
//		dprintf("\n Option : %x",option);
		ret_dat = nand_program((void *)Bulk_out_buf,
			     start_addr,ops_length,option);
		dprintf("\n NAND_PROGRAM finish!");
		handshake_PKT[0] = (u16) ret_dat;
		handshake_PKT[1] = (u16) (ret_dat>>16);
		HW_SendPKT(1,handshake_PKT,sizeof(handshake_PKT));
		udc_state = IDLE;
		break;
	case NAND_READ_TO_RAM:
		dprintf("\n Request : NAND_READNAND!");
		nand_read((u8 *)ram_addr,start_addr,ops_length,NO_OOB);
		__dcache_writeback_all();
		handshake_PKT[3]=(u16)ERR_OK;
		HW_SendPKT(1,handshake_PKT,sizeof(handshake_PKT));
		udc_state = IDLE;
		break;
	default:
		nand_disable(CSn);
		return ERR_OPS_NOTSUPPORT;
	}

//	nand_disable(CSn);
	return ERR_OK;
}

int SDRAM_OPS_Handle(u8 *buf)
{
	USB_DeviceRequest *dreq = (USB_DeviceRequest *)buf;
	u32 temp,i;
	u8 *obj;

	switch ((dreq->wValue)&0xf)
	{
	case 	SDRAM_LOAD:
//		dprintf("\n Request : SDRAM_LOAD!");
		ret_dat = (u32)memcpy((u8 *)start_addr,Bulk_out_buf,ops_length);
		handshake_PKT[0] = (u16) ret_dat;
		handshake_PKT[1] = (u16) (ret_dat>>16);
		HW_SendPKT(1,handshake_PKT,sizeof(handshake_PKT));
		udc_state = IDLE;
		break;
	}
	return ERR_OK;
}

void Borad_Init()
{
	dprintf("\n Borad_init! ");
	serial_put_hex(Hand.fw_args.cpu_id);
	switch (Hand.fw_args.cpu_id)
	{
	case 0x4740:
		//Init nand flash
		nand_init_4740(Hand.nand_bw,Hand.nand_rc,Hand.nand_ps,Hand.nand_ppb,
		       Hand.nand_bbpage,Hand.nand_bbpos,Hand.nand_force_erase,Hand.nand_eccpos);
	
		nand_program=nand_program_4740;
		nand_erase  =nand_erase_4740;
		nand_read   =nand_read_4740;
		nand_read_oob=nand_read_oob_4740;
		nand_read_raw=nand_read_raw_4740;
		nand_query  = nand_query_4740;
		nand_enable = nand_enable_4740;
		nand_disable= nand_disable_4740;
		nand_mark_bad = nand_mark_bad_4740;
	break;
	case 0x4750:
		//Init nand flash
		nand_init_4750(Hand.nand_bw, Hand.nand_rc, Hand.nand_ps,
			       Hand.nand_ppb, Hand.nand_bchbit, Hand.nand_eccpos,
			       Hand.nand_bbpos, Hand.nand_bbpage, Hand.nand_force_erase);

		nand_program=nand_program_4750;
		nand_erase  =nand_erase_4750;
		nand_read   =nand_read_4750;
		nand_read_oob=nand_read_oob_4750;
		nand_read_raw=nand_read_raw_4750;
		nand_query  = nand_query_4750;
		nand_enable = nand_enable_4750;
		nand_disable= nand_disable_4750;
		nand_mark_bad = nand_mark_bad_4750;
	break;
	default:
		serial_puts("Not support CPU ID!");
	}
}

int CONFIGRATION_Handle(u8 *buf)
{
	USB_DeviceRequest *dreq = (USB_DeviceRequest *)buf;
	switch ((dreq->wValue)&0xf)
	{
	case DS_flash_info:
		dprintf("\n configration :DS_flash_info_t!");
		config_flash_info();
		break;

	case DS_hand:
		dprintf("\n configration :DS_hand_t!");
		config_hand();
		break;
	default:;
		
	}
	Borad_Init();
	return ERR_OK;
}


