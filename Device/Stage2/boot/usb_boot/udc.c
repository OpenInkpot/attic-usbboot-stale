#include <includes.h>
#include <jz4740.h>
#include "usb.h"
#include "udc.h"
#include "usb_boot.h"
#define dprintf(x...) 
//printf(x)

//extern code_buf;
//static u32 rx_buf[1024];
u32 Bulk_in_buf[BULK_IN_BUF_SIZE];
u32 Bulk_out_buf[BULK_OUT_BUF_SIZE];
static u32 rx_buf[512];
static u32 tx_buf[1024];
static u32 tx_size, rx_size, finished;
//static 
u32 Bulk_in_size,Bulk_in_finish,Bulk_out_size;
static u32 fifo, curep;
static OS_EVENT *udcEvent;
u8 ep0state;
u8 USB_Version;
int udc_state;
u16 handshake_PKT[4]={0xaa55,0xaa55,0xaa55};

void (*tx_done)(void) = NULL;

u32 hwRxFifoCount(void) { return rx_size; }
u32 hwTxFifoCount(void) { return tx_size - finished; }

#define UDC_TASK_PRIO	2

// UDC FIFO
#define TXFIFOEP0 USB_FIFO_EP0

static u32 fifoaddr[] = 
{
	TXFIFOEP0, TXFIFOEP0+4 ,TXFIFOEP0+8
};

static u32 fifosize[] = {
	MAX_EP0_SIZE, MAX_EP1_SIZE
};


static void udcReadFifo(u8 *ptr, int size)
{
	u32 *d = (u32 *)ptr;
	int s;
	s = (size + 3) >> 2;
	while (s--)
		*d++ = REG32(fifo);
#if 0
	dprintf("recv:(%d)", size);
	for (s=0;s<size;s++) {
		if (s % 16 == 0)
			dprintf("\n");
		dprintf(" %02x", *(ptr+s));
	}
	dprintf("\n");
#endif
}

static void udcWriteFifo(u8 *ptr, int size)
{
	u32 *d = (u32 *)ptr;
	u8 *c;
	int s, q;

#if 0
	dprintf("send:(%d)", size);
	for (s=0;s<size;s++) {
		IF (s % 16 == 0)
			dprintf("\n");
		dprintf(" %02x", ptr[s]);
	}
	dprintf("\n");
#endif
	if (size > 0) {
		s = size >> 2;
		while (s--)
			REG32(fifo) = *d++;
		q = size & 3;
		if (q) {
			c = (u8 *)d;
			while (q--)
				REG8(fifo) = *c++;
		}
	} 
}

void HW_SendZeroPKT(int ep)
{
	jz_writeb(USB_REG_INDEX, ep);
	REG32(fifo)=0;
	usb_setb(USB_REG_INCSR, USB_INCSR_INPKTRDY);
	usb_setb(USB_REG_CSR0, USB_CSR0_DATAEND);
}

void HW_SendPKT(int ep, const u8 *buf, int size)
{
	dprintf("EP%d send pkt :%d\n", ep, size);
	//memcpy((void *)tx_buf, buf, size);
	fifo = fifoaddr[ep];
	//tx_size = size;
	//finished = 0;

	if (ep!=0)
	{
		Bulk_in_size = size;
		Bulk_in_finish = 0;
		jz_writeb(USB_REG_INDEX, ep);
		if (Bulk_in_size - Bulk_in_finish <= fifosize[ep]) 
		{
			udcWriteFifo((u8 *)((u32)buf+Bulk_in_finish),
				     Bulk_in_size - Bulk_in_finish);
			usb_setb(USB_REG_INCSR, USB_INCSR_INPKTRDY);
			Bulk_in_finish = Bulk_in_size;
		} else 
		{
			udcWriteFifo((u8 *)((u32)buf+Bulk_in_finish),
				     fifosize[ep]);
			usb_setb(USB_REG_INCSR, USB_INCSR_INPKTRDY);
			Bulk_in_finish += fifosize[ep];
		}
	}
	else  //EP0
	{
		tx_size = size;
		finished = 0;
		memcpy((void *)tx_buf, buf, size);
		ep0state = USB_EP0_TX;		
	}
}

void HW_GetPKT(int ep, const u8 *buf, int size)
{
	dprintf("EP%d read pkt :%d\n", ep, size);
	memcpy((void *)buf, (u8 *)rx_buf, size);
	fifo = fifoaddr[ep];
	if (rx_size > size)
		rx_size -= size;
	else {
		size = rx_size;
		rx_size = 0;
	}
	memcpy((u8 *)rx_buf, (u8 *)((u32)rx_buf+size), rx_size);
}

static USB_DeviceDescriptor devDesc = 
{
	sizeof(USB_DeviceDescriptor),
	DEVICE_DESCRIPTOR,	//1
	0x0200,     //Version 2.0
	0xff,    //Vendor spec class
	0xff,
	0xff,
	64,	/* Ep0 FIFO size */
	0x601a,  //vendor ID
	0x4740,  //Product ID
	0xffff,
	0x00,
	0x00,
	0x00,
	0x01
};

#define	CONFIG_DESCRIPTOR_LEN	(sizeof(USB_ConfigDescriptor) + \
				 sizeof(USB_InterfaceDescriptor) + \
				 sizeof(USB_EndPointDescriptor) * 2)

static struct {
	USB_ConfigDescriptor    configuration_descriptor;
	USB_InterfaceDescriptor interface_descritor;
	USB_EndPointDescriptor  endpoint_descriptor[2];
} __attribute__ ((packed)) confDesc = {
	{
		sizeof(USB_ConfigDescriptor),
		CONFIGURATION_DESCRIPTOR,
		CONFIG_DESCRIPTOR_LEN,
		0x01,
		0x01,
		0x00,
		0xc0,	// Self Powered, no remote wakeup
		0x64	// Maximum power consumption 2000 mA
	},
	{
		sizeof(USB_InterfaceDescriptor),
		INTERFACE_DESCRIPTOR,
		0x00,
		0x00,
		0x02,	/* ep number */
		0xff,
		0xff,
		0xff,
		0x00
	},
	{
		{
			sizeof(USB_EndPointDescriptor),
			ENDPOINT_DESCRIPTOR,
			(1 << 7) | 1,// endpoint 2 is IN endpoint
			2, /* bulk */
			512,
			16
		},
		{
			sizeof(USB_EndPointDescriptor),
			ENDPOINT_DESCRIPTOR,
			(0 << 7) | 1,// endpoint 5 is OUT endpoint
			2, /* bulk */
			512, /* OUT EP FIFO size */
			16
		}
	}
};

void sendDevDescString(int size)
{
	u16 str_ret[13] = {
		   0x031a,//0x1a=26 byte
		   0x0041,
		   0x0030,
		   0x0030,
		   0x0041,
		   0x0030,
		   0x0030,
		   0x0041,
		   0x0030,
		   0x0030,
		   0x0041,
		   0x0030,
		   0x0030
		  };
	dprintf("sendDevDescString size = %d\r\n",size);
	if(size >= 26)
		size = 26;
	str_ret[0] = (0x0300 | size);
	HW_SendPKT(0, str_ret,size);
	
}

void sendDevDesc(int size)
{
       switch (size) {
	case 18:
		//devDesc.iSerialNumber = GetMassDevNum();
		//if(devDesc.iSerialNumber > 0)
		//devDesc.iSerialNumber--;
		HW_SendPKT(0, &devDesc, sizeof(devDesc));
		break;
	default:
		HW_SendPKT(0, &devDesc, 8);
		break;
	}
}

void sendConfDesc(int size)
{
	switch (size) {
	case 9:
		HW_SendPKT(0, &confDesc, 9);
		break;
	case 8:
		HW_SendPKT(0, &confDesc, 8);
		break;
	default:
		HW_SendPKT(0, &confDesc, sizeof(confDesc));
		break;
	}
}

void EP0_init(u32 out, u32 out_size, u32 in, u32 in_size)
{
	//epout = out;
	//epin = in;
	confDesc.endpoint_descriptor[0].bEndpointAddress = (1<<7) | in;
	confDesc.endpoint_descriptor[0].wMaxPacketSize = in_size;
	confDesc.endpoint_descriptor[1].bEndpointAddress = (0<<7) | out;
	confDesc.endpoint_descriptor[1].wMaxPacketSize = out_size;
}

static void udc_reset(void)
{
	u8 byte;
	//data init
	ep0state = USB_EP0_IDLE;
	Bulk_in_size = 0;
	Bulk_in_finish = 0;
	Bulk_out_size = 0;
	udc_state = IDLE;
	tx_size = 0;
	rx_size = 0;
	finished = 0;
	//__cpm_stop_udc();
	/* Enable the USB PHY */
	REG_CPM_SCR |= CPM_SCR_USBPHY_ENABLE;
	/* Disable interrupts */
	jz_writew(USB_REG_INTRINE, 0);
	jz_writew(USB_REG_INTROUTE, 0);
	jz_writeb(USB_REG_INTRUSBE, 0);
	jz_writeb(USB_REG_FADDR,0);
	jz_writeb(USB_REG_POWER,0x60);   //High speed
	jz_writeb(USB_REG_INDEX,0);
	jz_writeb(USB_REG_CSR0,0xc0);
	jz_writeb(USB_REG_INDEX,1);
	jz_writew(USB_REG_INMAXP,512);
	jz_writew(USB_REG_INCSR,0x2048);
	jz_writeb(USB_REG_INDEX,1);
	jz_writew(USB_REG_OUTMAXP,512);
	jz_writew(USB_REG_OUTCSR,0x0090);
	jz_writew(USB_REG_INTRINE,0x3);   //enable intr
	jz_writew(USB_REG_INTROUTE,0x2);
	jz_writeb(USB_REG_INTRUSBE,0x4);

	byte=jz_readb(USB_REG_POWER);
	dprintf("\nREG_POWER: %02x",byte);
	if ((byte&0x10)==0) 
	{
		jz_writeb(USB_REG_INDEX,1);
		jz_writew(USB_REG_INMAXP,64);
		jz_writew(USB_REG_INCSR,0x2048);
		jz_writeb(USB_REG_INDEX,1);
		jz_writew(USB_REG_OUTMAXP,64);
		jz_writew(USB_REG_OUTCSR,0x0090);
		USB_Version=USB_FS;
		fifosize[1]=64;
		EP0_init(1,64,1,64);
	}
	else
	{
		jz_writeb(USB_REG_INDEX,1);
		jz_writew(USB_REG_INMAXP,512);
		jz_writew(USB_REG_INCSR,0x2048);
		jz_writeb(USB_REG_INDEX,1);
		jz_writew(USB_REG_OUTMAXP,512);
		jz_writew(USB_REG_OUTCSR,0x0090);
		USB_Version=USB_HS;
		fifosize[1]=512;
		EP0_init(1,512,1,512);
	}

}


void usbHandleStandDevReq(u8 *buf)
{
	USB_DeviceRequest *dreq = (USB_DeviceRequest *)buf;
	switch (dreq->bRequest) {
	case GET_DESCRIPTOR:
		if (dreq->bmRequestType == 0x80)	/* Dev2Host */
			switch(dreq->wValue >> 8) 
			{
			case DEVICE_DESCRIPTOR:
				dprintf("get device\n");
				sendDevDesc(dreq->wLength);
				break;
			case CONFIGURATION_DESCRIPTOR:
				dprintf("get config\n");
				sendConfDesc(dreq->wLength);
				break;
			case STRING_DESCRIPTOR:
				if (dreq->wLength == 0x02)
					HW_SendPKT(0, "\x04\x03", 2);
				else
					sendDevDescString(dreq->wLength);
				//HW_SendPKT(0, "\x04\x03\x09\x04", 2);
				break;
			}
		dprintf("\nSet ep0state=TX!");
		ep0state=USB_EP0_TX;
		
		break;
	case SET_ADDRESS:
		dprintf("\nSET_ADDRESS!");
		jz_writeb(USB_REG_FADDR,dreq->wValue);
		break;
	case GET_STATUS:
		switch (dreq->bmRequestType) {
		case 80:	/* device */
			HW_SendPKT(0, "\x01\x00", 2);
			break;
		case 81:	/* interface */
		case 82:	/* ep */
			HW_SendPKT(0, "\x00\x00", 2);
			break;
		}
		ep0state=USB_EP0_TX;
		break;
	case CLEAR_FEATURE:
	case SET_CONFIGURATION:
	case SET_INTERFACE:
	case SET_FEATURE:
#if 0
		dprintf("Send ZERO packet at 0.\n");
		HW_SendZeroPKT(0);
#endif
		break;
	}
}

void usbHandleVendorReq(u8 *buf)
{
	int ret_state;
	USB_DeviceRequest *dreq = (USB_DeviceRequest *)buf;
	switch (dreq->bRequest) {
	case VR_GET_CUP_INFO:
		ret_state=GET_CUP_INFO_Handle();
		//no support yet! 
		break;
	case VR_SET_DATA_ADDERSS:
		//printf("\n set address!");
		ret_state=SET_DATA_ADDERSS_Handle(buf);
		break;
	case VR_SET_DATA_LENGTH:
		//printf("\n set length!");
		ret_state=SET_DATA_LENGTH_Handle(buf);
		break;
	case VR_FLUSH_CACHES:
		ret_state=FLUSH_CACHES_Handle();
		break;
	case VR_PROGRAM_START1:
		ret_state=PROGRAM_START1_Handle(buf);
		break;
	case VR_PROGRAM_START2:
		ret_state=PROGRAM_START2_Handle(buf);
		break;
	case VR_NOR_OPS:
		ret_state=NOR_OPS_Handle(buf);
		Bulk_out_size = 0;
		//Bulk_in_size = 0;
		break;
	case VR_NAND_OPS:
		NAND_OPS_Handle(buf);
		Bulk_out_size = 0;
		//Bulk_in_size = 0;
		//handshake_PKT[3]=(u16)ret_state;
		//HW_SendPKT(0,handshake_PKT,sizeof(handshake_PKT));
		break;
	case VR_CONFIGRATION:
		ret_state=CONFIGRATION_Handle(buf);
		handshake_PKT[3]=(u16)ret_state;
		HW_SendPKT(1,handshake_PKT,sizeof(handshake_PKT));
		Bulk_out_size = 0;
		//Bulk_in_size = 0;
		break;
	}
	//handshake_PKT[3]=(u16)ret_state;
	//HW_SendPKT(0, 0, 0);
	//HW_SendPKT(1,&handshake_PKT,sizeof(handshake_PKT));
}

void Handshake_PKT()
{
	
	if (udc_state!=IDLE)
	{
		HW_SendPKT(1,handshake_PKT,sizeof(handshake_PKT));
		udc_state = IDLE;
		dprintf("\n Send handshake PKT!");
	}
	//else udc_state=IDLE;
}

void usbHandleDevReq(u8 *buf)
{
	dprintf("dev req:%d\n", (buf[0] & (3 << 5)) >> 5);
	switch ((buf[0] & (3 << 5)) >> 5) {
	case 0: /* Standard request */
		usbHandleStandDevReq(buf);
		break;
	case 1: /* Class request */
		//usbHandleClassDevReq(buf);
		//ep0state=USB_EP0_TX;
		break;
	case 2: /* Vendor request */
		usbHandleVendorReq(buf);
		//ep0state=USB_EP0_TX;
		break;
	}
}

void EP0_Handler ()
{
u8			byCSR0;

/* Read CSR0 */
jz_writeb(USB_REG_INDEX, 0);
byCSR0 = jz_readb(USB_REG_CSR0);

/* Check for SentStall 
if sendtall is set ,clear the sendstall bit*/
if (byCSR0 & USB_CSR0_SENTSTALL) 
{
	jz_writeb(USB_REG_CSR0, (byCSR0 & ~USB_CSR0_SENDSTALL));
	ep0state = USB_EP0_IDLE;
	dprintf("\nSentstall!");
	return;
}

/* Check for SetupEnd */
if (byCSR0 & USB_CSR0_SETUPEND) 
{
	jz_writeb(USB_REG_CSR0, (byCSR0 | USB_CSR0_SVDSETUPEND));
	ep0state = USB_EP0_IDLE;
	dprintf("\nSetupend!");
	return;
}
/* Call relevant routines for endpoint 0 state */
if (ep0state == USB_EP0_IDLE) 
{
	if (byCSR0 & USB_CSR0_OUTPKTRDY)   //There are datas in fifo
	{
		USB_DeviceRequest *dreq;
		fifo=fifoaddr[0];
		udcReadFifo((u8 *)rx_buf, sizeof(USB_DeviceRequest));
		usb_setb(USB_REG_CSR0, 0x48);//clear OUTRD bit
		dreq = (USB_DeviceRequest *)rx_buf;
		dprintf("\nbmRequestType:%02x\nbRequest:%02x\n"
			"wValue:%04x\nwIndex:%04x\n"
			"wLength:%04x\n",
			dreq->bmRequestType,
			dreq->bRequest,
			dreq->wValue,
			dreq->wIndex,
			dreq->wLength);
		usbHandleDevReq(rx_buf);
	} else 
	{
		dprintf("0:R DATA\n");
	}
	rx_size = 0;
}

if (ep0state == USB_EP0_TX) 
{
	fifo=fifoaddr[0];
	if (tx_size - finished <= 64) 
	{
		udcWriteFifo((u8 *)((u32)tx_buf+finished),
			     tx_size - finished);
		finished = tx_size;
		usb_setb(USB_REG_CSR0, USB_CSR0_INPKTRDY);
		usb_setb(USB_REG_CSR0, USB_CSR0_DATAEND); //Set dataend!
		ep0state=USB_EP0_IDLE;
	} else 
	{
		udcWriteFifo((u8 *)((u32)tx_buf+finished), 64);
		usb_setb(USB_REG_CSR0, USB_CSR0_INPKTRDY);
		finished += 64;
	}
}
return;
}

void EPIN_Handler(u8 EP)
{
	jz_writeb(USB_REG_INDEX, EP);
	fifo = fifoaddr[EP];

	if (Bulk_in_size-Bulk_in_finish==0) 
	{
		Handshake_PKT();
		return;
	}

	if (Bulk_in_size - Bulk_in_finish <= fifosize[EP]) 
	{
		udcWriteFifo((u8 *)((u32)Bulk_in_buf+Bulk_in_finish),
			     Bulk_in_size - Bulk_in_finish);
		usb_setw(USB_REG_INCSR, USB_INCSR_INPKTRDY);
		Bulk_in_finish = Bulk_in_size;
	} else 
	{
		udcWriteFifo((u8 *)((u32)Bulk_in_buf+Bulk_in_finish),
			    fifosize[EP]);
		usb_setw(USB_REG_INCSR, USB_INCSR_INPKTRDY);
		Bulk_in_finish += fifosize[EP];
	}
}

void EPOUT_Handler(u8 EP)
{
	u32 size;
	//printf("\n set OUT!");
	jz_writeb(USB_REG_INDEX, EP);
	size = jz_readw(USB_REG_OUTCOUNT);
	fifo = fifoaddr[EP];
	udcReadFifo((u8 *)((u32)Bulk_out_buf+Bulk_out_size), size);
	usb_clearb(USB_REG_OUTCSR,USB_OUTCSR_OUTPKTRDY);
	Bulk_out_size += size;
	//USB_HandleUFICmd();
	dprintf("\nEPOUT_handle return!");
}

void udc4740Proc ()
{
	u8	IntrUSB;
	u16	IntrIn;
	u16	IntrOut;
/* Read interrupt registers */
	IntrUSB = jz_readb(USB_REG_INTRUSB);
	IntrIn  = jz_readw(USB_REG_INTRIN);
	IntrOut = jz_readw(USB_REG_INTROUT);
/* Check for resume from suspend mode */
	if (IntrIn & 2) 
	{
		dprintf("\nUDC EP1 IN operation!");
		EPIN_Handler(1);	     
	}
	if (IntrOut & 2) 
	{
		dprintf("\nUDC EP1 OUT operation!");
		EPOUT_Handler(1);
	}
	if (IntrUSB & USB_INTR_RESET) 
	{
		dprintf("\nUDC reset intrupt!");  
		udc_reset();
	}

/* Check for endpoint 0 interrupt */
	if (IntrIn & USB_INTR_EP0) 
	{
		dprintf("\nUDC EP0 operations!");
		EP0_Handler();
	}
	//jz_readw(USB_REG_INTRIN);
	/* Check for suspend mode */
/*Implement late!!*/
	return;
}

static void udcIntrHandler(unsigned int arg)
{
	u8 err;
	__intc_mask_irq(IRQ_UDC);
	OSSemPost(udcEvent);
}

static void udcTaskEntry(void *arg)
{
	u8 err;

	dprintf("\nInit UDC");
	usb_clearb(USB_REG_POWER,0x40);
	udelay(1000);
	usb_setb(USB_REG_POWER,0x40);
	USB_Version=USB_HS;
//	handshake_PKT="";
	udcEvent = OSSemCreate(0);
	request_irq(IRQ_UDC, udcIntrHandler, 0);
	udc_reset();
	__intc_unmask_irq(IRQ_UDC);
	while (1) {
		OSSemPend(udcEvent, 0, &err);
		//if (USB_Version==USB_FS) printf("\nUDC task!");
		udc4740Proc();
		__intc_unmask_irq(IRQ_UDC);
	}
}

#define UDC_TASK_STK_SIZE	1024 * 5
static OS_STK udcTaskStack[UDC_TASK_STK_SIZE];

void udc_init(void)
{
	dprintf("\nCreate UDC task!");
	OSTaskCreate(udcTaskEntry, (void *)0,
		     (void *)&udcTaskStack[UDC_TASK_STK_SIZE - 1],
		     4);
}

