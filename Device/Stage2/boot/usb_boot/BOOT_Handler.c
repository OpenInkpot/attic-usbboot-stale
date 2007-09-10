/* USB_BOOT Handle routines*/

#include "jz4740.h"
#include "usb.h" 
#include "flash.h"
#include "usb_boot.h"
#include "hand.h"
#include "nandflash.h"
#include "udc.h"
#define dprintf(x...) printf(x)

unsigned int (*nand_query)(void);
int (*nand_init)(int bus_width, int row_cycle, int page_size, int page_per_block,
	      u32 gbase, u32 ebase, u32 aport, u32 dport, u32 cport);
int (*nand_fini)(void);
int (*nand_program)(void *context, int spage, int pages, void (*notify)(int),int option);
int (*nand_program_oob)(void *context, int spage, int pages, void (*notify)(int));
int (*nand_erase)(int blk_num, int sblk, int force, void (*notify)(int));
int (*nand_read)(void *buf, u32 startpage, u32 pagenum,int option);
int (*nand_read_oob)(void *buf, u32 startpage, u32 pagenum);
int (*nand_read_raw)(void *buf, u32 startpage, u32 pagenum);
void (*nand_enable) (unsigned int csn);
void (*nand_disable) (unsigned int csn);

hand_t Hand,*Hand_p;
flash_info_t Info,*Info_p;
extern u32 Bulk_out_buf[BULK_OUT_BUF_SIZE];
extern u32 Bulk_in_buf[BULK_IN_BUF_SIZE];
extern u16 handshake_PKT[4];
extern udc_state;
u32 start_addr;  //program operation start address or sector
u32 ops_length;  //number of operation unit ,in byte or sector
u32 ram_addr;


void config_flash_info()
{
}

void config_hand()
{
	hand_t *hand_p;
	hand_p=( hand_t *)Bulk_out_buf;
	Hand.nand_bw=hand_p->nand_bw;
	Hand.nand_rc=hand_p->nand_rc;
	Hand.nand_ps=hand_p->nand_ps;
	Hand.nand_ppb=hand_p->nand_ppb;
	Hand.nand_force_erase=hand_p->nand_force_erase;
	Hand.nand_pn=hand_p->nand_pn;
	Hand.nand_os=hand_p->nand_os;
	dprintf("\n Hand : bw %d rc %d ps %d ppb %d erase %d pn %d os %d",
		Hand.nand_bw,Hand.nand_rc,Hand.nand_ps,Hand.nand_ppb,Hand.nand_force_erase,Hand.nand_pn,Hand.nand_os);
}

int GET_CUP_INFO_Handle()
{
	char temp[8]="BOOTED!!";
	dprintf("\n GET_CPU_INFO!");
	HW_SendPKT(0,temp,8);
	udc_state = IDLE;
	return ERR_OK; 
}
	      
int SET_DATA_ADDERSS_Handle(u8 *buf)
{
	USB_DeviceRequest *dreq = (USB_DeviceRequest *)buf;
	start_addr=(((u32)dreq->wValue)<<16)+(u32)dreq->wIndex;
	dprintf("\n SET ADDRESS: %x",start_addr);
	return ERR_OK;
}
		
int SET_DATA_LENGTH_Handle(u8 *buf)
{
	USB_DeviceRequest *dreq = (USB_DeviceRequest *)buf;
	ops_length=(((u32)dreq->wValue)<<16)+(u32)dreq->wIndex;
	dprintf("\n DATA_LENGTH :%x", ops_length);
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
	dprintf("\n RAM ADDRESS :%x", ram_addr);
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
	dprintf("\n Execute program at %x",(u32)f);
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
		temp=nand_query();
		HW_SendPKT(1,(u8 *)&temp,4);
		handshake_PKT[3]=(u16)ERR_OK;
		udc_state = BULK_IN;
		break;
	case NAND_INIT:
		dprintf("\n Request : NAND_INIT!");

		break;
	case NAND_FINI:
		dprintf("\n Request : NAND_FINI!");

		break;
	case NAND_READ_OOB:
		dprintf("\n Request : NAND_READ_OOB!");
		//temp = ops_length / Hand.nand_ps + 1;
		//dprintf("\n temp %d",temp);
		memset(Bulk_in_buf,0,ops_length*Hand.nand_ps);
		nand_read_oob(Bulk_in_buf,start_addr,ops_length);
		HW_SendPKT(1,Bulk_in_buf,ops_length*Hand.nand_ps);
		handshake_PKT[3]=(u16)ERR_OK;
		udc_state = BULK_IN;		
		break;
	case NAND_READ_RAW:
		dprintf("\n Request : NAND_READ_RAW!");
		//temp = ops_length / Hand.nand_ps + 1;
		//dprintf("\n temp %d",temp);
		nand_read_raw(Bulk_in_buf,start_addr,ops_length);
		HW_SendPKT(1,Bulk_in_buf,ops_length*(Hand.nand_ps + Hand.nand_os));
		handshake_PKT[3]=(u16)ERR_OK;
		udc_state = BULK_IN;
		break;
	case NAND_ERASE:
		dprintf("\n Request : NAND_ERASE!");
		nand_erase(ops_length,start_addr,
			   Hand.nand_force_erase,NULL);
		handshake_PKT[3]=(u16)ERR_OK;
		HW_SendPKT(1,handshake_PKT,sizeof(handshake_PKT));
		udc_state = IDLE;
		break;
	case NAND_READ:
		dprintf("\n Request : NAND_READ!");
		dprintf("\n Option : %x",option);
		switch (option)
		{
		case 	OOB_ECC:
			nand_read_4740(Bulk_in_buf,start_addr,ops_length,OOB_ECC);
			HW_SendPKT(1,Bulk_in_buf,ops_length*(Hand.nand_ps + Hand.nand_os ));
			handshake_PKT[3]=(u16)ERR_OK;
			udc_state = BULK_IN;
			break;
		case 	OOB_NO_ECC:
			handshake_PKT[3]=(u16)ERR_OK;
			HW_SendPKT(1,handshake_PKT,sizeof(handshake_PKT));
			udc_state = IDLE;
			break;
		case 	NO_OOB:
			nand_read_4740(Bulk_in_buf,start_addr,ops_length,NO_OOB);
			HW_SendPKT(1,Bulk_in_buf,ops_length*Hand.nand_ps);
			handshake_PKT[3]=(u16)ERR_OK;
			udc_state = BULK_IN;
			break;
		}

		break;
	case NAND_PROGRAM:
		dprintf("\n Request : NAND_PROGRAM!");
		dprintf("\n Option : %x",option);
		nand_program((void *)Bulk_out_buf,
			     start_addr,ops_length,NULL,option);
		dprintf("\n NAND_PROGRAM finish!");
		handshake_PKT[3]=(u16)ERR_OK;
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

	nand_disable(CSn);
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
		dprintf("\n Request : SDRAM_LOAD!");
		memcpy((u8 *)start_addr,Bulk_out_buf,ops_length);
		handshake_PKT[3]=(u16)ERR_OK;
		HW_SendPKT(1,handshake_PKT,sizeof(handshake_PKT));
		udc_state = IDLE;
		break;
	}
	return ERR_OK;
}

void Borad_Init()
{
	dprintf("\n Borad_init! ");
	unsigned int gbase = 0xb0010000; /* GPIO registers base */
	unsigned int ebase = 0xb3010000; /* EMC registers base */
	unsigned int aport = 0xb8010000; /* Address base */
	unsigned int dport = 0xb8000000; /* Data base */
	unsigned int cport = 0xb8008000; /* Command base */
	//Init nand flash
	nand_init_4740(Hand.nand_bw,Hand.nand_rc,Hand.nand_ps,Hand.nand_ppb,
		gbase, ebase, aport, dport, cport);
	nand_program=nand_program_4740;
	nand_program_oob=nand_program_oob_4740;
	nand_erase  =nand_erase_4740;
	nand_read   =nand_read_4740;
	nand_read_oob=nand_read_oob_4740;
	nand_read_raw=nand_read_raw_4740;
	nand_query  = nand_query_4740;
	nand_enable = nand_enable_4740;
	nand_disable= nand_disable_4740;
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


