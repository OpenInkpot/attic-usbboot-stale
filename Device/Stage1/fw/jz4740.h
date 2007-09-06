/*
 * Include file for Ingenic Semiconductor's JZ4740 CPU.
 */
#ifndef __JZ4740_H__
#define __JZ4740_H__

#ifndef __ASSEMBLY__

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

#define REG8(addr)	*((volatile u8 *)(addr))
#define REG16(addr)	*((volatile u16 *)(addr))
#define REG32(addr)	*((volatile u32 *)(addr))

#else

#define REG8(addr)	(addr)
#define REG16(addr)	(addr)
#define REG32(addr)	(addr)

#endif /* !ASSEMBLY */

//----------------------------------------------------------------------
// Register Definitions
//
#define	CPM_BASE	0xB0000000
#define	TCU_BASE	0xB0002000
#define	WDT_BASE	0xB0002000
#define	DMAC_BASE	0xB3020000
#define	GPIO_BASE	0xB0010000
#define	UART0_BASE	0xB0030000
#define	AIC_BASE	0xB0020000
#define	ICDC_BASE	0xB0020000
#define	EMC_BASE	0xB3010000
#define	UDC_BASE	0xB3040000
#define	LCD_BASE	0xB3050000
#define	CIM_BASE	0xB3060000
#define	ETH_BASE	0xB3100000
#define	INTC_BASE	0xB0001000
#define	RTC_BASE	0xB0003000
#define	MSC_BASE	0xB0021000
#define	I2C_BASE	0xB0042000
#define	SSI_BASE	0xB0043000


/*************************************************************************
 * INTC (Interrupt Controller)
 *************************************************************************/
#define INTC_ISR	(INTC_BASE + 0x00)
#define INTC_IMR	(INTC_BASE + 0x04)
#define INTC_IMSR	(INTC_BASE + 0x08)
#define INTC_IMCR	(INTC_BASE + 0x0c)
#define INTC_IPR	(INTC_BASE + 0x10)

#define REG_INTC_ISR	REG32(INTC_ISR)
#define REG_INTC_IMR	REG32(INTC_IMR)
#define REG_INTC_IMSR	REG32(INTC_IMSR)
#define REG_INTC_IMCR	REG32(INTC_IMCR)
#define REG_INTC_IPR	REG32(INTC_IPR)

// 1st-level interrupts
#define IRQ_I2C		1
#define IRQ_UART0	9
#define IRQ_SADC	12
#define IRQ_MSC		14
#define IRQ_RTC		15
#define IRQ_SSI		16
#define IRQ_CIM		17
#define IRQ_AIC		18
#define IRQ_DMAC	20
#define IRQ_TCU2	21
#define IRQ_TCU1	22
#define IRQ_TCU0	23
#define IRQ_UDC 	24
#define IRQ_GPIO3	25
#define IRQ_GPIO2	26
#define IRQ_GPIO1	27
#define IRQ_GPIO0	28
#define IRQ_IPU		29
#define IRQ_LCD		30

// 2nd-level interrupts
#define IRQ_DMA_0	32  /* 32 to 37 for DMAC channel 0 to 5 */
#define IRQ_GPIO_0	48  /* 48 to 175 for GPIO pin 0 to 127 */


/*************************************************************************
 * CPM (Clock reset and Power control Management)
 *************************************************************************/
#define CPM_CPCCR	(CPM_BASE+0x00)
#define CPM_CPPCR	(CPM_BASE+0x10)
#define CPM_I2SCDR	(CPM_BASE+0x60)
#define CPM_LPCDR	(CPM_BASE+0x64)
#define CPM_MSCCDR	(CPM_BASE+0x68)

#define CPM_LCR		(CPM_BASE+0x04)
#define CPM_CLKGR	(CPM_BASE+0x20)
#define CPM_SCR		(CPM_BASE+0x24)
#define CPM_HCR		(CPM_BASE+0x30)
#define CPM_HWFCR	(CPM_BASE+0x34)
#define CPM_HRCR	(CPM_BASE+0x38)
#define CPM_HWCR	(CPM_BASE+0x3c)
#define CPM_HWSR	(CPM_BASE+0x40)
#define CPM_HSPR	(CPM_BASE+0x44)

#define CPM_RSR		(CPM_BASE+0x08)


#define REG_CPM_CPCCR	REG32(CPM_CPCCR)
#define REG_CPM_CPPCR	REG32(CPM_CPPCR)
#define REG_CPM_I2SCDR	REG32(CPM_I2SCDR)
#define REG_CPM_LPCDR	REG32(CPM_LPCDR)
#define REG_CPM_MSCCDR	REG32(CPM_MSCCDR)

#define REG_CPM_LCR	REG32(CPM_LCR)
#define REG_CPM_CLKGR	REG32(CPM_CLKGR)
#define REG_CPM_SCR	REG32(CPM_SCR)
#define REG_CPM_HCR	REG32(CPM_HCR)
#define REG_CPM_HWFCR	REG32(CPM_HWFCR)
#define REG_CPM_HRCR	REG32(CPM_HRCR)
#define REG_CPM_HWCR	REG32(CPM_HWCR)
#define REG_CPM_HWSR	REG32(CPM_HWSR)
#define REG_CPM_HSPR	REG32(CPM_HSPR)

#define REG_CPM_RSR	REG32(CPM_RSR)


/* Clock Control Register */
#define CPM_CPCCR_I2CS		(1 << 31)
#define CPM_CPCCR_CLKOEN	(1 << 30)
#define CPM_CPCCR_UCS		(1 << 29)
#define CPM_CPCCR_UDIV_BIT	23
#define CPM_CPCCR_UDIV_MASK	(0x3f << CPM_CPCCR_UDIV_BIT)
#define CPM_CPCCR_CE		(1 << 22)
#define CPM_CPCCR_PCS		(1 << 21)
#define CPM_CPCCR_LDIV_BIT	16
#define CPM_CPCCR_LDIV_MASK	(0x1f << CPM_CPCCR_LDIV_BIT)
#define CPM_CPCCR_MDIV_BIT	12
#define CPM_CPCCR_MDIV_MASK	(0x0f << CPM_CPCCR_MDIV_BIT)
#define CPM_CPCCR_PDIV_BIT	8
#define CPM_CPCCR_PDIV_MASK	(0x0f << CPM_CPCCR_PDIV_BIT)
#define CPM_CPCCR_HDIV_BIT	4
#define CPM_CPCCR_HDIV_MASK	(0x0f << CPM_CPCCR_HDIV_BIT)
#define CPM_CPCCR_CDIV_BIT	0
#define CPM_CPCCR_CDIV_MASK	(0x0f << CPM_CPCCR_CDIV_BIT)

/* I2S Clock Divider Register */
#define CPM_I2SCDR_I2SDIV_BIT	0
#define CPM_I2SCDR_I2SDIV_MASK	(0x1ff << CPM_I2SCDR_I2SDIV_BIT)

/* LCD Pixel Clock Divider Register */
#define CPM_LPCDR_PIXDIV_BIT	0
#define CPM_LPCDR_PIXDIV_MASK	(0x1ff << CPM_LPCDR_PIXDIV_BIT)

/* MSC Clock Divider Register */
#define CPM_MSCCDR_MSCDIV_BIT	0
#define CPM_MSCCDR_MSCDIV_MASK	(0x1f << CPM_MSCCDR_MSCDIV_BIT)

/* PLL Control Register */
#define CPM_CPPCR_PLLM_BIT	23
#define CPM_CPPCR_PLLM_MASK	(0x1ff << CPM_CPPCR_PLLM_BIT)
#define CPM_CPPCR_PLLN_BIT	18
#define CPM_CPPCR_PLLN_MASK	(0x1f << CPM_CPPCR_PLLN_BIT)
#define CPM_CPPCR_PLLOD_BIT	16
#define CPM_CPPCR_PLLOD_MASK	(0x03 << CPM_CPPCR_PLLOD_BIT)
#define CPM_CPPCR_PLLS		(1 << 10)
#define CPM_CPPCR_PLLBP		(1 << 9)
#define CPM_CPPCR_PLLEN		(1 << 8)
#define CPM_CPPCR_PLLST_BIT	0
#define CPM_CPPCR_PLLST_MASK	(0xff << CPM_CPPCR_PLLST_BIT)

/* Low Power Control Register */
#define CPM_LCR_DOZE_DUTY_BIT 	3
#define CPM_LCR_DOZE_DUTY_MASK 	(0x1f << CPM_LCR_DOZE_DUTY_BIT)
#define CPM_LCR_DOZE_ON		(1 << 2)
#define CPM_LCR_LPM_BIT		0
#define CPM_LCR_LPM_MASK	(0x3 << CPM_LCR_LPM_BIT)
  #define CPM_LCR_LPM_IDLE	(0x0 << CPM_LCR_LPM_BIT)
  #define CPM_LCR_LPM_SLEEP	(0x1 << CPM_LCR_LPM_BIT)

/* Clock Gate Register */
#define CPM_CLKGR_MCLK		(1 << 14)
#define CPM_CLKGR_IPU		(1 << 13)
#define CPM_CLKGR_DMAC		(1 << 12)
#define CPM_CLKGR_USB		(1 << 11)
#define CPM_CLKGR_LCD		(1 << 10)
#define CPM_CLKGR_CIM		(1 << 9)
#define CPM_CLKGR_SADC		(1 << 8)
#define CPM_CLKGR_MSC		(1 << 7)
#define CPM_CLKGR_AIC1		(1 << 6)
#define CPM_CLKGR_AIC2		(1 << 5)
#define CPM_CLKGR_SSI		(1 << 4)
#define CPM_CLKGR_I2C		(1 << 3)
#define CPM_CLKGR_RTC		(1 << 2)
#define CPM_CLKGR_TCU		(1 << 1)
#define CPM_CLKGR_UART0		(1 << 0)

/* Sleep Control Register */
#define CPM_SCR_O1ST_BIT	8
#define CPM_SCR_O1ST_MASK	(0xff << CPM_SCR_O1ST_BIT)
#define CPM_SCR_USBPHY_SUSPEND	(1 << 6)
#define CPM_SCR_OSC_ENABLE	(1 << 4)

/* Hibernate Control Register */
#define CPM_HCR_PD		(1 << 0)

/* Wakeup Filter Counter Register in Hibernate Mode */
#define CPM_HWFCR_TIME_BIT	0
#define CPM_HWFCR_TIME_MASK	(0x3ff << CPM_HWFCR_TIME_BIT)

/* Reset Counter Register in Hibernate Mode */
#define CPM_HRCR_TIME_BIT	0
#define CPM_HRCR_TIME_MASK	(0x7f << CPM_HRCR_TIME_BIT)

/* Wakeup Control Register in Hibernate Mode */
#define CPM_HWCR_WLE_HIGH	(1 << 2)
#define CPM_HWCR_PIN_WAKEUP	(1 << 1)
#define CPM_HWCR_RTC_WAKEUP	(1 << 0)

/* Wakeup Status Register in Hibernate Mode */
#define CPM_HWSR_WSR_PIN	(1 << 1)
#define CPM_HWSR_WSR_RTC	(1 << 0)

/* Reset Status Register */
#define CPM_RSR_HR		(1 << 2)
#define CPM_RSR_WR		(1 << 1)
#define CPM_RSR_PR		(1 << 0)

/*************************************************************************
 * UDC 
 *************************************************************************/
#define USB_BASE  UDC_BASE

#define USB_REG_FADDR		(USB_BASE + 0x00) /* Function Address 8-bit */
#define USB_REG_POWER		(USB_BASE + 0x01) /* Power Managemetn 8-bit */
#define USB_REG_INTRIN		(USB_BASE + 0x02) /* Interrupt IN 16-bit */
#define USB_REG_INTROUT		(USB_BASE + 0x04) /* Interrupt OUT 16-bit */
#define USB_REG_INTRINE		(USB_BASE + 0x06) /* Intr IN enable 16-bit */
#define USB_REG_INTROUTE	(USB_BASE + 0x08) /* Intr OUT enable 16-bit */
#define USB_REG_INTRUSB		(USB_BASE + 0x0a) /* Interrupt USB 8-bit */
#define USB_REG_INTRUSBE	(USB_BASE + 0x0b) /* Interrupt USB Enable 8-bit */
#define USB_REG_FRAME		(USB_BASE + 0x0c) /* Frame number 16-bit */
#define USB_REG_INDEX		(USB_BASE + 0x0e) /* Index register 8-bit */
#define USB_REG_TESTMODE	(USB_BASE + 0x0f) /* USB test mode 8-bit */

#define USB_REG_CSR0		(USB_BASE + 0x12) /* EP0 CSR 8-bit */
#define USB_REG_INMAXP		(USB_BASE + 0x10) /* EP1-2 IN Max Pkt Size 16-bit */
#define USB_REG_INCSR		(USB_BASE + 0x12) /* EP1-2 IN CSR LSB 8/16bit */
#define USB_REG_INCSRH		(USB_BASE + 0x13) /* EP1-2 IN CSR MSB 8-bit */
#define USB_REG_OUTMAXP		(USB_BASE + 0x14) /* EP1 OUT Max Pkt Size 16-bit */
#define USB_REG_OUTCSR		(USB_BASE + 0x16) /* EP1 OUT CSR LSB 8/16bit */
#define USB_REG_OUTCSRH		(USB_BASE + 0x17) /* EP1 OUT CSR MSB 8-bit */
#define USB_REG_OUTCOUNT	(USB_BASE + 0x18) /* bytes in EP0/1 OUT FIFO 16-bit */

#define USB_FIFO_EP0		(USB_BASE + 0x20)
#define USB_FIFO_EP1		(USB_BASE + 0x24)
#define USB_FIFO_EP2		(USB_BASE + 0x28)

#define USB_REG_EPINFO		(USB_BASE + 0x78) /* Endpoint information */
#define USB_REG_RAMINFO		(USB_BASE + 0x79) /* RAM information */

#define USB_REG_INTR		(USB_BASE + 0x200) /* DMA pending interrupts */
#define USB_REG_CNTL1		(USB_BASE + 0x204) /* DMA channel 1 control */
#define USB_REG_ADDR1		(USB_BASE + 0x208) /* DMA channel 1 AHB memory addr */
#define USB_REG_COUNT1		(USB_BASE + 0x20c) /* DMA channel 1 byte count */
#define USB_REG_CNTL2		(USB_BASE + 0x214) /* DMA channel 2 control */
#define USB_REG_ADDR2		(USB_BASE + 0x218) /* DMA channel 2 AHB memory addr */
#define USB_REG_COUNT2		(USB_BASE + 0x21c) /* DMA channel 2 byte count */


/*************************************************************************
 * TCU (Timer Counter Unit)
 *************************************************************************/
#define TCU_TSR		(TCU_BASE + 0x1C) /* Timer Stop Register */
#define TCU_TSSR	(TCU_BASE + 0x2C) /* Timer Stop Set Register */
#define TCU_TSCR	(TCU_BASE + 0x3C) /* Timer Stop Clear Register */
#define TCU_TER		(TCU_BASE + 0x10) /* Timer Counter Enable Register */
#define TCU_TESR	(TCU_BASE + 0x14) /* Timer Counter Enable Set Register */
#define TCU_TECR	(TCU_BASE + 0x18) /* Timer Counter Enable Clear Register */
#define TCU_TFR		(TCU_BASE + 0x20) /* Timer Flag Register */
#define TCU_TFSR	(TCU_BASE + 0x24) /* Timer Flag Set Register */
#define TCU_TFCR	(TCU_BASE + 0x28) /* Timer Flag Clear Register */
#define TCU_TMR		(TCU_BASE + 0x30) /* Timer Mask Register */
#define TCU_TMSR	(TCU_BASE + 0x34) /* Timer Mask Set Register */
#define TCU_TMCR	(TCU_BASE + 0x38) /* Timer Mask Clear Register */
#define TCU_TDFR0	(TCU_BASE + 0x40) /* Timer Data Full Register */
#define TCU_TDHR0	(TCU_BASE + 0x44) /* Timer Data Half Register */
#define TCU_TCNT0	(TCU_BASE + 0x48) /* Timer Counter Register */
#define TCU_TCSR0	(TCU_BASE + 0x4C) /* Timer Control Register */
#define TCU_TDFR1	(TCU_BASE + 0x50)
#define TCU_TDHR1	(TCU_BASE + 0x54)
#define TCU_TCNT1	(TCU_BASE + 0x58)
#define TCU_TCSR1	(TCU_BASE + 0x5C)
#define TCU_TDFR2	(TCU_BASE + 0x60)
#define TCU_TDHR2	(TCU_BASE + 0x64)
#define TCU_TCNT2	(TCU_BASE + 0x68)
#define TCU_TCSR2	(TCU_BASE + 0x6C)
#define TCU_TDFR3	(TCU_BASE + 0x70)
#define TCU_TDHR3	(TCU_BASE + 0x74)
#define TCU_TCNT3	(TCU_BASE + 0x78)
#define TCU_TCSR3	(TCU_BASE + 0x7C)
#define TCU_TDFR4	(TCU_BASE + 0x80)
#define TCU_TDHR4	(TCU_BASE + 0x84)
#define TCU_TCNT4	(TCU_BASE + 0x88)
#define TCU_TCSR4	(TCU_BASE + 0x8C)
#define TCU_TDFR5	(TCU_BASE + 0x90)
#define TCU_TDHR5	(TCU_BASE + 0x94)
#define TCU_TCNT5	(TCU_BASE + 0x98)
#define TCU_TCSR5	(TCU_BASE + 0x9C)

#define REG_TCU_TSR	REG32(TCU_TSR)
#define REG_TCU_TSSR	REG32(TCU_TSSR)
#define REG_TCU_TSCR	REG32(TCU_TSCR)
#define REG_TCU_TER	REG8(TCU_TER)
#define REG_TCU_TESR	REG8(TCU_TESR)
#define REG_TCU_TECR	REG8(TCU_TECR)
#define REG_TCU_TFR	REG32(TCU_TFR)
#define REG_TCU_TFSR	REG32(TCU_TFSR)
#define REG_TCU_TFCR	REG32(TCU_TFCR)
#define REG_TCU_TMR	REG32(TCU_TMR)
#define REG_TCU_TMSR	REG32(TCU_TMSR)
#define REG_TCU_TMCR	REG32(TCU_TMCR)
#define REG_TCU_TDFR0	REG16(TCU_TDFR0)
#define REG_TCU_TDHR0	REG16(TCU_TDHR0)
#define REG_TCU_TCNT0	REG16(TCU_TCNT0)
#define REG_TCU_TCSR0	REG16(TCU_TCSR0)
#define REG_TCU_TDFR1	REG16(TCU_TDFR1)
#define REG_TCU_TDHR1	REG16(TCU_TDHR1)
#define REG_TCU_TCNT1	REG16(TCU_TCNT1)
#define REG_TCU_TCSR1	REG16(TCU_TCSR1)
#define REG_TCU_TDFR2	REG16(TCU_TDFR2)
#define REG_TCU_TDHR2	REG16(TCU_TDHR2)
#define REG_TCU_TCNT2	REG16(TCU_TCNT2)
#define REG_TCU_TCSR2	REG16(TCU_TCSR2)
#define REG_TCU_TDFR3	REG16(TCU_TDFR3)
#define REG_TCU_TDHR3	REG16(TCU_TDHR3)
#define REG_TCU_TCNT3	REG16(TCU_TCNT3)
#define REG_TCU_TCSR3	REG16(TCU_TCSR3)
#define REG_TCU_TDFR4	REG16(TCU_TDFR4)
#define REG_TCU_TDHR4	REG16(TCU_TDHR4)
#define REG_TCU_TCNT4	REG16(TCU_TCNT4)
#define REG_TCU_TCSR4	REG16(TCU_TCSR4)

// n = 0,1,2,3,4,5
#define TCU_TDFR(n)	(TCU_BASE + (0x40 + (n)*0x10)) /* Timer Data Full Reg */
#define TCU_TDHR(n)	(TCU_BASE + (0x44 + (n)*0x10)) /* Timer Data Half Reg */
#define TCU_TCNT(n)	(TCU_BASE + (0x48 + (n)*0x10)) /* Timer Counter Reg */
#define TCU_TCSR(n)	(TCU_BASE + (0x4C + (n)*0x10)) /* Timer Control Reg */

#define REG_TCU_TDFR(n)	REG16(TCU_TDFR((n)))
#define REG_TCU_TDHR(n)	REG16(TCU_TDHR((n)))
#define REG_TCU_TCNT(n)	REG16(TCU_TCNT((n)))
#define REG_TCU_TCSR(n)	REG16(TCU_TCSR((n)))

// Register definitions
#define TCU_TCSR_PWM_SD		(1 << 9)
#define TCU_TCSR_PWM_INITL_HIGH	(1 << 8)
#define TCU_TCSR_PWM_EN		(1 << 7)
#define TCU_TCSR_PRESCALE_BIT	3
#define TCU_TCSR_PRESCALE_MASK	(0x7 << TCU_TCSR_PRESCALE_BIT)
  #define TCU_TCSR_PRESCALE1	(0x0 << TCU_TCSR_PRESCALE_BIT)
  #define TCU_TCSR_PRESCALE4	(0x1 << TCU_TCSR_PRESCALE_BIT)
  #define TCU_TCSR_PRESCALE16	(0x2 << TCU_TCSR_PRESCALE_BIT)
  #define TCU_TCSR_PRESCALE64	(0x3 << TCU_TCSR_PRESCALE_BIT)
  #define TCU_TCSR_PRESCALE256	(0x4 << TCU_TCSR_PRESCALE_BIT)
  #define TCU_TCSR_PRESCALE1024	(0x5 << TCU_TCSR_PRESCALE_BIT)
#define TCU_TCSR_EXT_EN		(1 << 2)
#define TCU_TCSR_RTC_EN		(1 << 1)
#define TCU_TCSR_PCK_EN		(1 << 0)

#define TCU_TER_TCEN5		(1 << 5)
#define TCU_TER_TCEN4		(1 << 4)
#define TCU_TER_TCEN3		(1 << 3)
#define TCU_TER_TCEN2		(1 << 2)
#define TCU_TER_TCEN1		(1 << 1)
#define TCU_TER_TCEN0		(1 << 0)

#define TCU_TESR_TCST5		(1 << 5)
#define TCU_TESR_TCST4		(1 << 4)
#define TCU_TESR_TCST3		(1 << 3)
#define TCU_TESR_TCST2		(1 << 2)
#define TCU_TESR_TCST1		(1 << 1)
#define TCU_TESR_TCST0		(1 << 0)

#define TCU_TECR_TCCL5		(1 << 5)
#define TCU_TECR_TCCL4		(1 << 4)
#define TCU_TECR_TCCL3		(1 << 3)
#define TCU_TECR_TCCL2		(1 << 2)
#define TCU_TECR_TCCL1		(1 << 1)
#define TCU_TECR_TCCL0		(1 << 0)

#define TCU_TFR_HFLAG5		(1 << 21)
#define TCU_TFR_HFLAG4		(1 << 20)
#define TCU_TFR_HFLAG3		(1 << 19)
#define TCU_TFR_HFLAG2		(1 << 18)
#define TCU_TFR_HFLAG1		(1 << 17)
#define TCU_TFR_HFLAG0		(1 << 16)
#define TCU_TFR_FFLAG5		(1 << 5)
#define TCU_TFR_FFLAG4		(1 << 4)
#define TCU_TFR_FFLAG3		(1 << 3)
#define TCU_TFR_FFLAG2		(1 << 2)
#define TCU_TFR_FFLAG1		(1 << 1)
#define TCU_TFR_FFLAG0		(1 << 0)

#define TCU_TFSR_HFLAG5		(1 << 21)
#define TCU_TFSR_HFLAG4		(1 << 20)
#define TCU_TFSR_HFLAG3		(1 << 19)
#define TCU_TFSR_HFLAG2		(1 << 18)
#define TCU_TFSR_HFLAG1		(1 << 17)
#define TCU_TFSR_HFLAG0		(1 << 16)
#define TCU_TFSR_FFLAG5		(1 << 5)
#define TCU_TFSR_FFLAG4		(1 << 4)
#define TCU_TFSR_FFLAG3		(1 << 3)
#define TCU_TFSR_FFLAG2		(1 << 2)
#define TCU_TFSR_FFLAG1		(1 << 1)
#define TCU_TFSR_FFLAG0		(1 << 0)

#define TCU_TFCR_HFLAG5		(1 << 21)
#define TCU_TFCR_HFLAG4		(1 << 20)
#define TCU_TFCR_HFLAG3		(1 << 19)
#define TCU_TFCR_HFLAG2		(1 << 18)
#define TCU_TFCR_HFLAG1		(1 << 17)
#define TCU_TFCR_HFLAG0		(1 << 16)
#define TCU_TFCR_FFLAG5		(1 << 5)
#define TCU_TFCR_FFLAG4		(1 << 4)
#define TCU_TFCR_FFLAG3		(1 << 3)
#define TCU_TFCR_FFLAG2		(1 << 2)
#define TCU_TFCR_FFLAG1		(1 << 1)
#define TCU_TFCR_FFLAG0		(1 << 0)

#define TCU_TMR_HMASK5		(1 << 21)
#define TCU_TMR_HMASK4		(1 << 20)
#define TCU_TMR_HMASK3		(1 << 19)
#define TCU_TMR_HMASK2		(1 << 18)
#define TCU_TMR_HMASK1		(1 << 17)
#define TCU_TMR_HMASK0		(1 << 16)
#define TCU_TMR_FMASK5		(1 << 5)
#define TCU_TMR_FMASK4		(1 << 4)
#define TCU_TMR_FMASK3		(1 << 3)
#define TCU_TMR_FMASK2		(1 << 2)
#define TCU_TMR_FMASK1		(1 << 1)
#define TCU_TMR_FMASK0		(1 << 0)

#define TCU_TMSR_HMST5		(1 << 21)
#define TCU_TMSR_HMST4		(1 << 20)
#define TCU_TMSR_HMST3		(1 << 19)
#define TCU_TMSR_HMST2		(1 << 18)
#define TCU_TMSR_HMST1		(1 << 17)
#define TCU_TMSR_HMST0		(1 << 16)
#define TCU_TMSR_FMST5		(1 << 5)
#define TCU_TMSR_FMST4		(1 << 4)
#define TCU_TMSR_FMST3		(1 << 3)
#define TCU_TMSR_FMST2		(1 << 2)
#define TCU_TMSR_FMST1		(1 << 1)
#define TCU_TMSR_FMST0		(1 << 0)

#define TCU_TMCR_HMCL5		(1 << 21)
#define TCU_TMCR_HMCL4		(1 << 20)
#define TCU_TMCR_HMCL3		(1 << 19)
#define TCU_TMCR_HMCL2		(1 << 18)
#define TCU_TMCR_HMCL1		(1 << 17)
#define TCU_TMCR_HMCL0		(1 << 16)
#define TCU_TMCR_FMCL5		(1 << 5)
#define TCU_TMCR_FMCL4		(1 << 4)
#define TCU_TMCR_FMCL3		(1 << 3)
#define TCU_TMCR_FMCL2		(1 << 2)
#define TCU_TMCR_FMCL1		(1 << 1)
#define TCU_TMCR_FMCL0		(1 << 0)

#define TCU_TSR_WDTS		(1 << 16)
#define TCU_TSR_STOP5		(1 << 5)
#define TCU_TSR_STOP4		(1 << 4)
#define TCU_TSR_STOP3		(1 << 3)
#define TCU_TSR_STOP2		(1 << 2)
#define TCU_TSR_STOP1		(1 << 1)
#define TCU_TSR_STOP0		(1 << 0)

#define TCU_TSSR_WDTSS		(1 << 16)
#define TCU_TSSR_STPS5		(1 << 5)
#define TCU_TSSR_STPS4		(1 << 4)
#define TCU_TSSR_STPS3		(1 << 3)
#define TCU_TSSR_STPS2		(1 << 2)
#define TCU_TSSR_STPS1		(1 << 1)
#define TCU_TSSR_STPS0		(1 << 0)

#define TCU_TSSR_WDTSC		(1 << 16)
#define TCU_TSSR_STPC5		(1 << 5)
#define TCU_TSSR_STPC4		(1 << 4)
#define TCU_TSSR_STPC3		(1 << 3)
#define TCU_TSSR_STPC2		(1 << 2)
#define TCU_TSSR_STPC1		(1 << 1)
#define TCU_TSSR_STPC0		(1 << 0)


/*************************************************************************
 * WDT (WatchDog Timer)
 *************************************************************************/
#define WDT_TDR		(WDT_BASE + 0x00)
#define WDT_TCER	(WDT_BASE + 0x04)
#define WDT_TCNT	(WDT_BASE + 0x08)
#define WDT_TCSR	(WDT_BASE + 0x0C)

#define REG_WDT_TDR	REG16(WDT_TDR)
#define REG_WDT_TCER	REG8(WDT_TCER)
#define REG_WDT_TCNT	REG16(WDT_TCNT)
#define REG_WDT_TCSR	REG16(WDT_TCSR)

// Register definition
#define WDT_TCSR_PRESCALE_BIT	3
#define WDT_TCSR_PRESCALE_MASK	(0x7 << WDT_TCSR_PRESCALE_BIT)
  #define WDT_TCSR_PRESCALE1	(0x0 << WDT_TCSR_PRESCALE_BIT)
  #define WDT_TCSR_PRESCALE4	(0x1 << WDT_TCSR_PRESCALE_BIT)
  #define WDT_TCSR_PRESCALE16	(0x2 << WDT_TCSR_PRESCALE_BIT)
  #define WDT_TCSR_PRESCALE64	(0x3 << WDT_TCSR_PRESCALE_BIT)
  #define WDT_TCSR_PRESCALE256	(0x4 << WDT_TCSR_PRESCALE_BIT)
  #define WDT_TCSR_PRESCALE1024	(0x5 << WDT_TCSR_PRESCALE_BIT)
#define WDT_TCSR_EXT_EN		(1 << 2)
#define WDT_TCSR_RTC_EN		(1 << 1)
#define WDT_TCSR_PCK_EN		(1 << 0)

#define WDT_TCER_TCEN		(1 << 0)


/*************************************************************************
 * DMAC (DMA Controller)
 *************************************************************************/

#define MAX_DMA_NUM	6  /* max 6 channels */

#define DMAC_DSAR(n)	(DMAC_BASE + (0x00 + (n) * 0x20)) /* DMA source address */
#define DMAC_DTAR(n)	(DMAC_BASE + (0x04 + (n) * 0x20)) /* DMA target address */
#define DMAC_DTCR(n)	(DMAC_BASE + (0x08 + (n) * 0x20)) /* DMA transfer count */
#define DMAC_DRSR(n)	(DMAC_BASE + (0x0c + (n) * 0x20)) /* DMA request source */
#define DMAC_DCCSR(n)	(DMAC_BASE + (0x10 + (n) * 0x20)) /* DMA control/status */
#define DMAC_DCMD(n)	(DMAC_BASE + (0x14 + (n) * 0x20)) /* DMA command */
#define DMAC_DDA(n)	(DMAC_BASE + (0x18 + (n) * 0x20)) /* DMA descriptor address */
#define DMAC_DMACR	(DMAC_BASE + 0x0300)              /* DMA control register */
#define DMAC_DMAIPR	(DMAC_BASE + 0x0304)              /* DMA interrupt pending */
#define DMAC_DMADBR	(DMAC_BASE + 0x0308)              /* DMA doorbell */
#define DMAC_DMADBSR	(DMAC_BASE + 0x030C)              /* DMA doorbell set */

// channel 0
#define DMAC_DSAR0      DMAC_DSAR(0)
#define DMAC_DTAR0      DMAC_DTAR(0)
#define DMAC_DTCR0      DMAC_DTCR(0)
#define DMAC_DRSR0      DMAC_DRSR(0)
#define DMAC_DCCSR0     DMAC_DCCSR(0)
#define DMAC_DCMD0	DMAC_DCMD(0)
#define DMAC_DDA0	DMAC_DDA(0)

// channel 1
#define DMAC_DSAR1      DMAC_DSAR(1)
#define DMAC_DTAR1      DMAC_DTAR(1)
#define DMAC_DTCR1      DMAC_DTCR(1)
#define DMAC_DRSR1      DMAC_DRSR(1)
#define DMAC_DCCSR1     DMAC_DCCSR(1)
#define DMAC_DCMD1	DMAC_DCMD(1)
#define DMAC_DDA1	DMAC_DDA(1)

// channel 2
#define DMAC_DSAR2      DMAC_DSAR(2)
#define DMAC_DTAR2      DMAC_DTAR(2)
#define DMAC_DTCR2      DMAC_DTCR(2)
#define DMAC_DRSR2      DMAC_DRSR(2)
#define DMAC_DCCSR2     DMAC_DCCSR(2)
#define DMAC_DCMD2	DMAC_DCMD(2)
#define DMAC_DDA2	DMAC_DDA(2)

// channel 3
#define DMAC_DSAR3      DMAC_DSAR(3)
#define DMAC_DTAR3      DMAC_DTAR(3)
#define DMAC_DTCR3      DMAC_DTCR(3)
#define DMAC_DRSR3      DMAC_DRSR(3)
#define DMAC_DCCSR3     DMAC_DCCSR(3)
#define DMAC_DCMD3	DMAC_DCMD(3)
#define DMAC_DDA3	DMAC_DDA(3)

// channel 4
#define DMAC_DSAR4      DMAC_DSAR(4)
#define DMAC_DTAR4      DMAC_DTAR(4)
#define DMAC_DTCR4      DMAC_DTCR(4)
#define DMAC_DRSR4      DMAC_DRSR(4)
#define DMAC_DCCSR4     DMAC_DCCSR(4)
#define DMAC_DCMD4	DMAC_DCMD(4)
#define DMAC_DDA4	DMAC_DDA(4)

// channel 5
#define DMAC_DSAR5      DMAC_DSAR(5)
#define DMAC_DTAR5      DMAC_DTAR(5)
#define DMAC_DTCR5      DMAC_DTCR(5)
#define DMAC_DRSR5      DMAC_DRSR(5)
#define DMAC_DCCSR5     DMAC_DCCSR(5)
#define DMAC_DCMD5	DMAC_DCMD(5)
#define DMAC_DDA5	DMAC_DDA(5)

#define REG_DMAC_DSAR(n)	REG32(DMAC_DSAR((n)))
#define REG_DMAC_DTAR(n)	REG32(DMAC_DTAR((n)))
#define REG_DMAC_DTCR(n)	REG32(DMAC_DTCR((n)))
#define REG_DMAC_DRSR(n)	REG32(DMAC_DRSR((n)))
#define REG_DMAC_DCCSR(n)	REG32(DMAC_DCCSR((n)))
#define REG_DMAC_DCMD(n)	REG32(DMAC_DCMD((n)))
#define REG_DMAC_DDA(n)		REG32(DMAC_DDA((n)))
#define REG_DMAC_DMACR		REG32(DMAC_DMACR)
#define REG_DMAC_DMAIPR		REG32(DMAC_DMAIPR)
#define REG_DMAC_DMADBR		REG32(DMAC_DMADBR)
#define REG_DMAC_DMADBSR	REG32(DMAC_DMADBSR)

// DMA request source register
#define DMAC_DRSR_RS_BIT	0
#define DMAC_DRSR_RS_MASK	(0x1f << DMAC_DRSR_RS_BIT)
  #define DMAC_DRSR_RS_AUTO	(8 << DMAC_DRSR_RS_BIT)
  #define DMAC_DRSR_RS_UART0OUT	(20 << DMAC_DRSR_RS_BIT)
  #define DMAC_DRSR_RS_UART0IN	(21 << DMAC_DRSR_RS_BIT)
  #define DMAC_DRSR_RS_SSIOUT	(22 << DMAC_DRSR_RS_BIT)
  #define DMAC_DRSR_RS_SSIIN	(23 << DMAC_DRSR_RS_BIT)
  #define DMAC_DRSR_RS_AICOUT	(24 << DMAC_DRSR_RS_BIT)
  #define DMAC_DRSR_RS_AICIN	(25 << DMAC_DRSR_RS_BIT)
  #define DMAC_DRSR_RS_MSCOUT	(26 << DMAC_DRSR_RS_BIT)
  #define DMAC_DRSR_RS_MSCIN	(27 << DMAC_DRSR_RS_BIT)
  #define DMAC_DRSR_RS_TCU	(28 << DMAC_DRSR_RS_BIT)

// DMA channel control/status register
#define DMAC_DCCSR_NDES		(1 << 31) /* descriptor (0) or not (1) ? */
#define DMAC_DCCSR_CDOA_BIT	16        /* copy of DMA offset address */
#define DMAC_DCCSR_CDOA_MASK	(0xff << DMAC_DCCSR_CDOA_BIT)
#define DMAC_DCCSR_INV		(1 << 6)  /* descriptor invalid */
#define DMAC_DCCSR_AR		(1 << 4)  /* address error */
#define DMAC_DCCSR_TT		(1 << 3)  /* transfer terminated */
#define DMAC_DCCSR_HLT		(1 << 2)  /* DMA halted */
#define DMAC_DCCSR_CT		(1 << 1)  /* count terminated */
#define DMAC_DCCSR_EN		(1 << 0)  /* channel enable bit */

// DMA channel command register 
#define DMAC_DCMD_SAI		(1 << 23) /* source address increment */
#define DMAC_DCMD_DAI		(1 << 22) /* dest address increment */
#define DMAC_DCMD_RDIL_BIT	16        /* request detection interval length */
#define DMAC_DCMD_RDIL_MASK	(0x0f << DMAC_DCMD_RDIL_BIT)
  #define DMAC_DCMD_RDIL_IGN	(0 << DMAC_DCMD_RDIL_BIT)
  #define DMAC_DCMD_RDIL_2	(1 << DMAC_DCMD_RDIL_BIT)
  #define DMAC_DCMD_RDIL_4	(2 << DMAC_DCMD_RDIL_BIT)
  #define DMAC_DCMD_RDIL_8	(3 << DMAC_DCMD_RDIL_BIT)
  #define DMAC_DCMD_RDIL_12	(4 << DMAC_DCMD_RDIL_BIT)
  #define DMAC_DCMD_RDIL_16	(5 << DMAC_DCMD_RDIL_BIT)
  #define DMAC_DCMD_RDIL_20	(6 << DMAC_DCMD_RDIL_BIT)
  #define DMAC_DCMD_RDIL_24	(7 << DMAC_DCMD_RDIL_BIT)
  #define DMAC_DCMD_RDIL_28	(8 << DMAC_DCMD_RDIL_BIT)
  #define DMAC_DCMD_RDIL_32	(9 << DMAC_DCMD_RDIL_BIT)
  #define DMAC_DCMD_RDIL_48	(10 << DMAC_DCMD_RDIL_BIT)
  #define DMAC_DCMD_RDIL_60	(11 << DMAC_DCMD_RDIL_BIT)
  #define DMAC_DCMD_RDIL_64	(12 << DMAC_DCMD_RDIL_BIT)
  #define DMAC_DCMD_RDIL_124	(13 << DMAC_DCMD_RDIL_BIT)
  #define DMAC_DCMD_RDIL_128	(14 << DMAC_DCMD_RDIL_BIT)
  #define DMAC_DCMD_RDIL_200	(15 << DMAC_DCMD_RDIL_BIT)
#define DMAC_DCMD_SWDH_BIT	14  /* source port width */
#define DMAC_DCMD_SWDH_MASK	(0x03 << DMAC_DCMD_SWDH_BIT)
  #define DMAC_DCMD_SWDH_32	(0 << DMAC_DCMD_SWDH_BIT)
  #define DMAC_DCMD_SWDH_8	(1 << DMAC_DCMD_SWDH_BIT)
  #define DMAC_DCMD_SWDH_16	(2 << DMAC_DCMD_SWDH_BIT)
#define DMAC_DCMD_DWDH_BIT	12  /* dest port width */
#define DMAC_DCMD_DWDH_MASK	(0x03 << DMAC_DCMD_DWDH_BIT)
  #define DMAC_DCMD_DWDH_32	(0 << DMAC_DCMD_DWDH_BIT)
  #define DMAC_DCMD_DWDH_8	(1 << DMAC_DCMD_DWDH_BIT)
  #define DMAC_DCMD_DWDH_16	(2 << DMAC_DCMD_DWDH_BIT)
#define DMAC_DCMD_DS_BIT	8  /* transfer data size of a data unit */
#define DMAC_DCMD_DS_MASK	(0x07 << DMAC_DCMD_DS_BIT)
  #define DMAC_DCMD_DS_32BIT	(0 << DMAC_DCMD_DS_BIT)
  #define DMAC_DCMD_DS_8BIT	(1 << DMAC_DCMD_DS_BIT)
  #define DMAC_DCMD_DS_16BIT	(2 << DMAC_DCMD_DS_BIT)
  #define DMAC_DCMD_DS_16BYTE	(3 << DMAC_DCMD_DS_BIT)
  #define DMAC_DCMD_DS_32BYTE	(4 << DMAC_DCMD_DS_BIT)
#define DMAC_DCMD_TM		(1 << 7)  /* transfer mode: 0-single 1-block */
#define DMAC_DCMD_DES_V		(1 << 4)  /* descriptor valid flag */
#define DMAC_DCMD_DES_VM	(1 << 3)  /* descriptor valid mask: 1:support V-bit */
#define DMAC_DCMD_DES_VIE	(1 << 2)  /* DMA valid error interrupt enable */
#define DMAC_DCMD_TIE		(1 << 1)  /* DMA transfer interrupt enable */
#define DMAC_DCMD_LINK		(1 << 0)  /* descriptor link enable */

// DMA descriptor address register
#define DMAC_DDA_BASE_BIT	12  /* descriptor base address */
#define DMAC_DDA_BASE_MASK	(0x0fffff << DMAC_DDA_BASE_BIT)
#define DMAC_DDA_OFFSET_BIT	4  /* descriptor offset address */
#define DMAC_DDA_OFFSET_MASK	(0x0ff << DMAC_DDA_OFFSET_BIT)

// DMA control register
#define DMAC_DMACR_PR_BIT	8  /* channel priority mode */
#define DMAC_DMACR_PR_MASK	(0x03 << DMAC_DMACR_PR_BIT)
  #define DMAC_DMACR_PR_012345	(0 << DMAC_DMACR_PR_BIT)
  #define DMAC_DMACR_PR_023145	(1 << DMAC_DMACR_PR_BIT)
  #define DMAC_DMACR_PR_201345	(2 << DMAC_DMACR_PR_BIT)
  #define DMAC_DMACR_PR_RR	(3 << DMAC_DMACR_PR_BIT) /* round robin */
#define DMAC_DMACR_HLT		(1 << 3)  /* DMA halt flag */
#define DMAC_DMACR_AR		(1 << 2)  /* address error flag */
#define DMAC_DMACR_DMAE		(1 << 0)  /* DMA enable bit */

// DMA doorbell register
#define DMAC_DMADBR_DB5		(1 << 5)  /* doorbell for channel 5 */
#define DMAC_DMADBR_DB4		(1 << 5)  /* doorbell for channel 4 */
#define DMAC_DMADBR_DB3		(1 << 5)  /* doorbell for channel 3 */
#define DMAC_DMADBR_DB2		(1 << 5)  /* doorbell for channel 2 */
#define DMAC_DMADBR_DB1		(1 << 5)  /* doorbell for channel 1 */
#define DMAC_DMADBR_DB0		(1 << 5)  /* doorbell for channel 0 */

// DMA doorbell set register
#define DMAC_DMADBSR_DBS5	(1 << 5)  /* enable doorbell for channel 5 */
#define DMAC_DMADBSR_DBS4	(1 << 5)  /* enable doorbell for channel 4 */
#define DMAC_DMADBSR_DBS3	(1 << 5)  /* enable doorbell for channel 3 */
#define DMAC_DMADBSR_DBS2	(1 << 5)  /* enable doorbell for channel 2 */
#define DMAC_DMADBSR_DBS1	(1 << 5)  /* enable doorbell for channel 1 */
#define DMAC_DMADBSR_DBS0	(1 << 5)  /* enable doorbell for channel 0 */

// DMA interrupt pending register
#define DMAC_DMAIPR_CIRQ5	(1 << 5)  /* irq pending status for channel 5 */
#define DMAC_DMAIPR_CIRQ4	(1 << 4)  /* irq pending status for channel 4 */
#define DMAC_DMAIPR_CIRQ3	(1 << 3)  /* irq pending status for channel 3 */
#define DMAC_DMAIPR_CIRQ2	(1 << 2)  /* irq pending status for channel 2 */
#define DMAC_DMAIPR_CIRQ1	(1 << 1)  /* irq pending status for channel 1 */
#define DMAC_DMAIPR_CIRQ0	(1 << 0)  /* irq pending status for channel 0 */


/*************************************************************************
 * GPIO (General-Purpose I/O Ports)
 *************************************************************************/
#define MAX_GPIO_NUM	128

//n = 0,1,2,3
#define GPIO_PXPIN(n)	(GPIO_BASE + (0x00 + (n)*0x100)) /* PIN Level Register */
#define GPIO_PXDAT(n)	(GPIO_BASE + (0x10 + (n)*0x100)) /* Port Data Register */
#define GPIO_PXDATS(n)	(GPIO_BASE + (0x14 + (n)*0x100)) /* Port Data Set Register */
#define GPIO_PXDATC(n)	(GPIO_BASE + (0x18 + (n)*0x100)) /* Port Data Clear Register */
#define GPIO_PXIM(n)	(GPIO_BASE + (0x20 + (n)*0x100)) /* Interrupt Mask Register */
#define GPIO_PXIMS(n)	(GPIO_BASE + (0x24 + (n)*0x100)) /* Interrupt Mask Set Reg */
#define GPIO_PXIMC(n)	(GPIO_BASE + (0x28 + (n)*0x100)) /* Interrupt Mask Clear Reg */
#define GPIO_PXPE(n)	(GPIO_BASE + (0x30 + (n)*0x100)) /* Pull Enable Register */
#define GPIO_PXPES(n)	(GPIO_BASE + (0x34 + (n)*0x100)) /* Pull Enable Set Reg. */
#define GPIO_PXPEC(n)	(GPIO_BASE + (0x38 + (n)*0x100)) /* Pull Enable Clear Reg. */
#define GPIO_PXFUN(n)	(GPIO_BASE + (0x40 + (n)*0x100)) /* Function Register */
#define GPIO_PXFUNS(n)	(GPIO_BASE + (0x44 + (n)*0x100)) /* Function Set Register */
#define GPIO_PXFUNC(n)	(GPIO_BASE + (0x48 + (n)*0x100)) /* Function Clear Register */
#define GPIO_PXSEL(n)	(GPIO_BASE + (0x50 + (n)*0x100)) /* Select Register */
#define GPIO_PXSELS(n)	(GPIO_BASE + (0x54 + (n)*0x100)) /* Select Set Register */
#define GPIO_PXSELC(n)	(GPIO_BASE + (0x58 + (n)*0x100)) /* Select Clear Register */
#define GPIO_PXDIR(n)	(GPIO_BASE + (0x60 + (n)*0x100)) /* Direction Register */
#define GPIO_PXDIRS(n)	(GPIO_BASE + (0x64 + (n)*0x100)) /* Direction Set Register */
#define GPIO_PXDIRC(n)	(GPIO_BASE + (0x68 + (n)*0x100)) /* Direction Clear Register */
#define GPIO_PXTRG(n)	(GPIO_BASE + (0x70 + (n)*0x100)) /* Trigger Register */
#define GPIO_PXTRGS(n)	(GPIO_BASE + (0x74 + (n)*0x100)) /* Trigger Set Register */
#define GPIO_PXTRGC(n)	(GPIO_BASE + (0x78 + (n)*0x100)) /* Trigger Set Register */
#define GPIO_PXFLG(n)	(GPIO_BASE + (0x80 + (n)*0x100)) /* Port Flag Register */

#define REG_GPIO_PXPIN(n)	REG32(GPIO_PXPIN((n)))  /* PIN level */
#define REG_GPIO_PXDAT(n)	REG32(GPIO_PXDAT((n)))  /* 1: interrupt pending */
#define REG_GPIO_PXDATS(n)	REG32(GPIO_PXDATS((n)))
#define REG_GPIO_PXDATC(n)	REG32(GPIO_PXDATC((n)))
#define REG_GPIO_PXIM(n)	REG32(GPIO_PXIM((n)))   /* 1: mask pin interrupt */
#define REG_GPIO_PXIMS(n)	REG32(GPIO_PXIMS((n)))
#define REG_GPIO_PXIMC(n)	REG32(GPIO_PXIMC((n)))
#define REG_GPIO_PXPE(n)	REG32(GPIO_PXPE((n)))   /* 1: disable pull up/down */
#define REG_GPIO_PXPES(n)	REG32(GPIO_PXPES((n)))
#define REG_GPIO_PXPEC(n)	REG32(GPIO_PXPEC((n)))
#define REG_GPIO_PXFUN(n)	REG32(GPIO_PXFUN((n)))  /* 0:GPIO or intr, 1:FUNC */
#define REG_GPIO_PXFUNS(n)	REG32(GPIO_PXFUNS((n)))
#define REG_GPIO_PXFUNC(n)	REG32(GPIO_PXFUNC((n)))
#define REG_GPIO_PXSEL(n)	REG32(GPIO_PXSEL((n))) /* 0:GPIO/Fun0,1:intr/fun1*/
#define REG_GPIO_PXSELS(n)	REG32(GPIO_PXSELS((n)))
#define REG_GPIO_PXSELC(n)	REG32(GPIO_PXSELC((n)))
#define REG_GPIO_PXDIR(n)	REG32(GPIO_PXDIR((n))) /* 0:input/low-level-trig/falling-edge-trig, 1:output/high-level-trig/rising-edge-trig */
#define REG_GPIO_PXDIRS(n)	REG32(GPIO_PXDIRS((n)))
#define REG_GPIO_PXDIRC(n)	REG32(GPIO_PXDIRC((n)))
#define REG_GPIO_PXTRG(n)	REG32(GPIO_PXTRG((n))) /* 0:level-trigger, 1:edge-trigger */
#define REG_GPIO_PXTRGS(n)	REG32(GPIO_PXTRGS((n)))
#define REG_GPIO_PXTRGC(n)	REG32(GPIO_PXTRGC((n)))
#define REG_GPIO_PXFLG(n)	REG32(GPIO_PXFLG((n))) /* interrupt flag */


/*************************************************************************
 * UART
 *************************************************************************/

#define IRDA_BASE	UART0_BASE
#define UART_BASE	UART0_BASE
#define UART_OFF	0x1000

/* Register Offset */
#define OFF_RDR		(0x00)	/* R  8b H'xx */
#define OFF_TDR		(0x00)	/* W  8b H'xx */
#define OFF_DLLR	(0x00)	/* RW 8b H'00 */
#define OFF_DLHR	(0x04)	/* RW 8b H'00 */
#define OFF_IER		(0x04)	/* RW 8b H'00 */
#define OFF_ISR		(0x08)	/* R  8b H'01 */
#define OFF_FCR		(0x08)	/* W  8b H'00 */
#define OFF_LCR		(0x0C)	/* RW 8b H'00 */
#define OFF_MCR		(0x10)	/* RW 8b H'00 */
#define OFF_LSR		(0x14)	/* R  8b H'00 */
#define OFF_MSR		(0x18)	/* R  8b H'00 */
#define OFF_SPR		(0x1C)	/* RW 8b H'00 */
#define OFF_SIRCR	(0x20)	/* RW 8b H'00, UART0 */
#define OFF_UMR		(0x24)	/* RW 8b H'00, UART M Register */
#define OFF_UACR	(0x28)	/* RW 8b H'00, UART Add Cycle Register */

/* Register Address */
#define UART0_RDR	(UART0_BASE + OFF_RDR)
#define UART0_TDR	(UART0_BASE + OFF_TDR)
#define UART0_DLLR	(UART0_BASE + OFF_DLLR)
#define UART0_DLHR	(UART0_BASE + OFF_DLHR)
#define UART0_IER	(UART0_BASE + OFF_IER)
#define UART0_ISR	(UART0_BASE + OFF_ISR)
#define UART0_FCR	(UART0_BASE + OFF_FCR)
#define UART0_LCR	(UART0_BASE + OFF_LCR)
#define UART0_MCR	(UART0_BASE + OFF_MCR)
#define UART0_LSR	(UART0_BASE + OFF_LSR)
#define UART0_MSR	(UART0_BASE + OFF_MSR)
#define UART0_SPR	(UART0_BASE + OFF_SPR)
#define UART0_SIRCR	(UART0_BASE + OFF_SIRCR)
#define UART0_UMR	(UART0_BASE + OFF_UMR)
#define UART0_UACR	(UART0_BASE + OFF_UACR)

/*
 * Define macros for UART_IER
 * UART Interrupt Enable Register
 */
#define UART_IER_RIE	(1 << 0)	/* 0: receive fifo "full" interrupt disable */
#define UART_IER_TIE	(1 << 1)	/* 0: transmit fifo "empty" interrupt disable */
#define UART_IER_RLIE	(1 << 2)	/* 0: receive line status interrupt disable */
#define UART_IER_MIE	(1 << 3)	/* 0: modem status interrupt disable */
#define UART_IER_RTIE	(1 << 4)	/* 0: receive timeout interrupt disable */

/*
 * Define macros for UART_ISR
 * UART Interrupt Status Register
 */
#define UART_ISR_IP	(1 << 0)	/* 0: interrupt is pending  1: no interrupt */
#define UART_ISR_IID	(7 << 1)	/* Source of Interrupt */
#define UART_ISR_IID_MSI		(0 << 1)	/* Modem status interrupt */
#define UART_ISR_IID_THRI	(1 << 1)	/* Transmitter holding register empty */
#define UART_ISR_IID_RDI		(2 << 1)	/* Receiver data interrupt */
#define UART_ISR_IID_RLSI	(3 << 1)	/* Receiver line status interrupt */
#define UART_ISR_FFMS	(3 << 6)	/* FIFO mode select, set when UART_FCR.FE is set to 1 */
#define UART_ISR_FFMS_NO_FIFO	(0 << 6)
#define UART_ISR_FFMS_FIFO_MODE	(3 << 6)

/*
 * Define macros for UART_FCR
 * UART FIFO Control Register
 */
#define UART_FCR_FE	(1 << 0)	/* 0: non-FIFO mode  1: FIFO mode */
#define UART_FCR_RFLS	(1 << 1)	/* write 1 to flush receive FIFO */
#define UART_FCR_TFLS	(1 << 2)	/* write 1 to flush transmit FIFO */
#define UART_FCR_DMS	(1 << 3)	/* 0: disable DMA mode */
#define UART_FCR_UUE	(1 << 4)	/* 0: disable UART */
#define UART_FCR_RTRG	(3 << 6)	/* Receive FIFO Data Trigger */
#define UART_FCR_RTRG_1	(0 << 6)
#define UART_FCR_RTRG_4	(1 << 6)
#define UART_FCR_RTRG_8	(2 << 6)
#define UART_FCR_RTRG_15	(3 << 6)

/*
 * Define macros for UART_LCR
 * UART Line Control Register
 */
#define UART_LCR_WLEN	(3 << 0)	/* word length */
#define UART_LCR_WLEN_5	(0 << 0)
#define UART_LCR_WLEN_6	(1 << 0)
#define UART_LCR_WLEN_7	(2 << 0)
#define UART_LCR_WLEN_8	(3 << 0)
#define UART_LCR_STOP	(1 << 2)	/* 0: 1 stop bit when word length is 5,6,7,8
					   1: 1.5 stop bits when 5; 2 stop bits when 6,7,8 */
#define UART_LCR_STOP_1	(0 << 2)	/* 0: 1 stop bit when word length is 5,6,7,8
					   1: 1.5 stop bits when 5; 2 stop bits when 6,7,8 */
#define UART_LCR_STOP_2	(1 << 2)	/* 0: 1 stop bit when word length is 5,6,7,8
					   1: 1.5 stop bits when 5; 2 stop bits when 6,7,8 */

#define UART_LCR_PE	(1 << 3)	/* 0: parity disable */
#define UART_LCR_PROE	(1 << 4)	/* 0: even parity  1: odd parity */
#define UART_LCR_SPAR	(1 << 5)	/* 0: sticky parity disable */
#define UART_LCR_SBRK	(1 << 6)	/* write 0 normal, write 1 send break */
#define UART_LCR_DLAB	(1 << 7)	/* 0: access UART_RDR/TDR/IER  1: access UART_DLLR/DLHR */

/*
 * Define macros for UART_LSR
 * UART Line Status Register
 */
#define UART_LSR_DR	(1 << 0)	/* 0: receive FIFO is empty  1: receive data is ready */
#define UART_LSR_ORER	(1 << 1)	/* 0: no overrun error */
#define UART_LSR_PER	(1 << 2)	/* 0: no parity error */
#define UART_LSR_FER	(1 << 3)	/* 0; no framing error */
#define UART_LSR_BRK	(1 << 4)	/* 0: no break detected  1: receive a break signal */
#define UART_LSR_TDRQ	(1 << 5)	/* 1: transmit FIFO half "empty" */
#define UART_LSR_TEMT	(1 << 6)	/* 1: transmit FIFO and shift registers empty */
#define UART_LSR_RFER	(1 << 7)	/* 0: no receive error  1: receive error in FIFO mode */

/*
 * Define macros for UART_MCR
 * UART Modem Control Register
 */
#define UART_MCR_DTR	(1 << 0)	/* 0: DTR_ ouput high */
#define UART_MCR_RTS	(1 << 1)	/* 0: RTS_ output high */
#define UART_MCR_OUT1	(1 << 2)	/* 0: UART_MSR.RI is set to 0 and RI_ input high */
#define UART_MCR_OUT2	(1 << 3)	/* 0: UART_MSR.DCD is set to 0 and DCD_ input high */
#define UART_MCR_LOOP	(1 << 4)	/* 0: normal  1: loopback mode */
#define UART_MCR_MCE	(1 << 7)	/* 0: modem function is disable */

/*
 * Define macros for UART_MSR
 * UART Modem Status Register
 */
#define UART_MSR_DCTS	(1 << 0)	/* 0: no change on CTS_ pin since last read of UART_MSR */
#define UART_MSR_DDSR	(1 << 1)	/* 0: no change on DSR_ pin since last read of UART_MSR */
#define UART_MSR_DRI	(1 << 2)	/* 0: no change on RI_ pin since last read of UART_MSR */
#define UART_MSR_DDCD	(1 << 3)	/* 0: no change on DCD_ pin since last read of UART_MSR */
#define UART_MSR_CTS	(1 << 4)	/* 0: CTS_ pin is high */
#define UART_MSR_DSR	(1 << 5)	/* 0: DSR_ pin is high */
#define UART_MSR_RI	(1 << 6)	/* 0: RI_ pin is high */
#define UART_MSR_DCD	(1 << 7)	/* 0: DCD_ pin is high */

/*
 * Define macros for SIRCR
 * Slow IrDA Control Register
 */
#define SIRCR_TSIRE	(1 << 0)	/* 0: transmitter is in UART mode  1: IrDA mode */
#define SIRCR_RSIRE	(1 << 1)	/* 0: receiver is in UART mode  1: IrDA mode */
#define SIRCR_TPWS	(1 << 2)	/* 0: transmit 0 pulse width is 3/16 of bit length
					   1: 0 pulse width is 1.6us for 115.2Kbps */
#define SIRCR_TXPL	(1 << 3)	/* 0: encoder generates a positive pulse for 0 */
#define SIRCR_RXPL	(1 << 4)	/* 0: decoder interprets positive pulse as 0 */


/*************************************************************************
 * AIC (AC97/I2S Controller)
 *************************************************************************/
#define	AIC_FR			(AIC_BASE + 0x000)
#define	AIC_CR			(AIC_BASE + 0x004)
#define	AIC_ACCR1		(AIC_BASE + 0x008)
#define	AIC_ACCR2		(AIC_BASE + 0x00C)
#define	AIC_I2SCR		(AIC_BASE + 0x010)
#define	AIC_SR			(AIC_BASE + 0x014)
#define	AIC_ACSR		(AIC_BASE + 0x018)
#define	AIC_I2SSR		(AIC_BASE + 0x01C)
#define	AIC_ACCAR		(AIC_BASE + 0x020)
#define	AIC_ACCDR		(AIC_BASE + 0x024)
#define	AIC_ACSAR		(AIC_BASE + 0x028)
#define	AIC_ACSDR		(AIC_BASE + 0x02C)
#define	AIC_I2SDIV		(AIC_BASE + 0x030)
#define	AIC_DR			(AIC_BASE + 0x034)

#define	REG_AIC_FR		REG32(AIC_FR)
#define	REG_AIC_CR		REG32(AIC_CR)
#define	REG_AIC_ACCR1		REG32(AIC_ACCR1)
#define	REG_AIC_ACCR2		REG32(AIC_ACCR2)
#define	REG_AIC_I2SCR		REG32(AIC_I2SCR)
#define	REG_AIC_SR		REG32(AIC_SR)
#define	REG_AIC_ACSR		REG32(AIC_ACSR)
#define	REG_AIC_I2SSR		REG32(AIC_I2SSR)
#define	REG_AIC_ACCAR		REG32(AIC_ACCAR)
#define	REG_AIC_ACCDR		REG32(AIC_ACCDR)
#define	REG_AIC_ACSAR		REG32(AIC_ACSAR)
#define	REG_AIC_ACSDR		REG32(AIC_ACSDR)
#define	REG_AIC_I2SDIV		REG32(AIC_I2SDIV)
#define	REG_AIC_DR		REG32(AIC_DR)

/* AIC Controller Configuration Register (AIC_FR) */

#define	AIC_FR_RFTH_BIT		12        /* Receive FIFO Threshold */
#define	AIC_FR_RFTH_MASK	(0xf << AIC_FR_RFTH_BIT)
#define	AIC_FR_TFTH_BIT		8         /* Transmit FIFO Threshold */
#define	AIC_FR_TFTH_MASK	(0xf << AIC_FR_TFTH_BIT)
#define	AIC_FR_ICDC		(1 << 5)  /* External(0) or Internal CODEC(1) */
#define	AIC_FR_AUSEL		(1 << 4)  /* AC97(0) or I2S/MSB-justified(1) */
#define	AIC_FR_RST		(1 << 3)  /* AIC registers reset */
#define	AIC_FR_BCKD		(1 << 2)  /* I2S BIT_CLK direction, 0:input,1:output */
#define	AIC_FR_SYNCD		(1 << 1)  /* I2S SYNC direction, 0:input,1:output */
#define	AIC_FR_ENB		(1 << 0)  /* AIC enable bit */

/* AIC Controller Common Control Register (AIC_CR) */

#define	AIC_CR_OSS_BIT		19  /* Output Sample Size from memory (AIC V2 only) */
#define	AIC_CR_OSS_MASK		(0x7 << AIC_CR_OSS_BIT)
  #define AIC_CR_OSS_8BIT	(0x0 << AIC_CR_OSS_BIT)
  #define AIC_CR_OSS_16BIT	(0x1 << AIC_CR_OSS_BIT)
  #define AIC_CR_OSS_18BIT	(0x2 << AIC_CR_OSS_BIT)
  #define AIC_CR_OSS_20BIT	(0x3 << AIC_CR_OSS_BIT)
  #define AIC_CR_OSS_24BIT	(0x4 << AIC_CR_OSS_BIT)
#define	AIC_CR_ISS_BIT		16  /* Input Sample Size from memory (AIC V2 only) */
#define	AIC_CR_ISS_MASK		(0x7 << AIC_CR_ISS_BIT)
  #define AIC_CR_ISS_8BIT	(0x0 << AIC_CR_ISS_BIT)
  #define AIC_CR_ISS_16BIT	(0x1 << AIC_CR_ISS_BIT)
  #define AIC_CR_ISS_18BIT	(0x2 << AIC_CR_ISS_BIT)
  #define AIC_CR_ISS_20BIT	(0x3 << AIC_CR_ISS_BIT)
  #define AIC_CR_ISS_24BIT	(0x4 << AIC_CR_ISS_BIT)
#define	AIC_CR_RDMS		(1 << 15)  /* Receive DMA enable */
#define	AIC_CR_TDMS		(1 << 14)  /* Transmit DMA enable */
#define	AIC_CR_M2S		(1 << 11)  /* Mono to Stereo enable */
#define	AIC_CR_ENDSW		(1 << 10)  /* Endian switch enable */
#define	AIC_CR_AVSTSU		(1 << 9)   /* Signed <-> Unsigned toggle enable */
#define	AIC_CR_FLUSH		(1 << 8)   /* Flush FIFO */
#define	AIC_CR_EROR		(1 << 6)   /* Enable ROR interrupt */
#define	AIC_CR_ETUR		(1 << 5)   /* Enable TUR interrupt */
#define	AIC_CR_ERFS		(1 << 4)   /* Enable RFS interrupt */
#define	AIC_CR_ETFS		(1 << 3)   /* Enable TFS interrupt */
#define	AIC_CR_ENLBF		(1 << 2)   /* Enable Loopback Function */
#define	AIC_CR_ERPL		(1 << 1)   /* Enable Playback Function */
#define	AIC_CR_EREC		(1 << 0)   /* Enable Record Function */

/* AIC Controller AC-link Control Register 1 (AIC_ACCR1) */

#define	AIC_ACCR1_RS_BIT	16          /* Receive Valid Slots */
#define	AIC_ACCR1_RS_MASK	(0x3ff << AIC_ACCR1_RS_BIT)
  #define AIC_ACCR1_RS_SLOT12	  (1 << 25) /* Slot 12 valid bit */
  #define AIC_ACCR1_RS_SLOT11	  (1 << 24) /* Slot 11 valid bit */
  #define AIC_ACCR1_RS_SLOT10	  (1 << 23) /* Slot 10 valid bit */
  #define AIC_ACCR1_RS_SLOT9	  (1 << 22) /* Slot 9 valid bit, LFE */
  #define AIC_ACCR1_RS_SLOT8	  (1 << 21) /* Slot 8 valid bit, Surround Right */
  #define AIC_ACCR1_RS_SLOT7	  (1 << 20) /* Slot 7 valid bit, Surround Left */
  #define AIC_ACCR1_RS_SLOT6	  (1 << 19) /* Slot 6 valid bit, PCM Center */
  #define AIC_ACCR1_RS_SLOT5	  (1 << 18) /* Slot 5 valid bit */
  #define AIC_ACCR1_RS_SLOT4	  (1 << 17) /* Slot 4 valid bit, PCM Right */
  #define AIC_ACCR1_RS_SLOT3	  (1 << 16) /* Slot 3 valid bit, PCM Left */
#define	AIC_ACCR1_XS_BIT	0          /* Transmit Valid Slots */
#define	AIC_ACCR1_XS_MASK	(0x3ff << AIC_ACCR1_XS_BIT)
  #define AIC_ACCR1_XS_SLOT12	  (1 << 9) /* Slot 12 valid bit */
  #define AIC_ACCR1_XS_SLOT11	  (1 << 8) /* Slot 11 valid bit */
  #define AIC_ACCR1_XS_SLOT10	  (1 << 7) /* Slot 10 valid bit */
  #define AIC_ACCR1_XS_SLOT9	  (1 << 6) /* Slot 9 valid bit, LFE */
  #define AIC_ACCR1_XS_SLOT8	  (1 << 5) /* Slot 8 valid bit, Surround Right */
  #define AIC_ACCR1_XS_SLOT7	  (1 << 4) /* Slot 7 valid bit, Surround Left */
  #define AIC_ACCR1_XS_SLOT6	  (1 << 3) /* Slot 6 valid bit, PCM Center */
  #define AIC_ACCR1_XS_SLOT5	  (1 << 2) /* Slot 5 valid bit */
  #define AIC_ACCR1_XS_SLOT4	  (1 << 1) /* Slot 4 valid bit, PCM Right */
  #define AIC_ACCR1_XS_SLOT3	  (1 << 0) /* Slot 3 valid bit, PCM Left */

/* AIC Controller AC-link Control Register 2 (AIC_ACCR2) */

#define	AIC_ACCR2_ERSTO		(1 << 18) /* Enable RSTO interrupt */
#define	AIC_ACCR2_ESADR		(1 << 17) /* Enable SADR interrupt */
#define	AIC_ACCR2_ECADT		(1 << 16) /* Enable CADT interrupt */
#define	AIC_ACCR2_OASS_BIT	8  /* Output Sample Size for AC-link */
#define	AIC_ACCR2_OASS_MASK	(0x3 << AIC_ACCR2_OASS_BIT)
  #define AIC_ACCR2_OASS_20BIT	  (0 << AIC_ACCR2_OASS_BIT) /* Output Audio Sample Size is 20-bit */
  #define AIC_ACCR2_OASS_18BIT	  (1 << AIC_ACCR2_OASS_BIT) /* Output Audio Sample Size is 18-bit */
  #define AIC_ACCR2_OASS_16BIT	  (2 << AIC_ACCR2_OASS_BIT) /* Output Audio Sample Size is 16-bit */
  #define AIC_ACCR2_OASS_8BIT	  (3 << AIC_ACCR2_OASS_BIT) /* Output Audio Sample Size is 8-bit */
#define	AIC_ACCR2_IASS_BIT	6  /* Output Sample Size for AC-link */
#define	AIC_ACCR2_IASS_MASK	(0x3 << AIC_ACCR2_IASS_BIT)
  #define AIC_ACCR2_IASS_20BIT	  (0 << AIC_ACCR2_IASS_BIT) /* Input Audio Sample Size is 20-bit */
  #define AIC_ACCR2_IASS_18BIT	  (1 << AIC_ACCR2_IASS_BIT) /* Input Audio Sample Size is 18-bit */
  #define AIC_ACCR2_IASS_16BIT	  (2 << AIC_ACCR2_IASS_BIT) /* Input Audio Sample Size is 16-bit */
  #define AIC_ACCR2_IASS_8BIT	  (3 << AIC_ACCR2_IASS_BIT) /* Input Audio Sample Size is 8-bit */
#define	AIC_ACCR2_SO		(1 << 3)  /* SDATA_OUT output value */
#define	AIC_ACCR2_SR		(1 << 2)  /* RESET# pin level */
#define	AIC_ACCR2_SS		(1 << 1)  /* SYNC pin level */
#define	AIC_ACCR2_SA		(1 << 0)  /* SYNC and SDATA_OUT alternation */

/* AIC Controller I2S/MSB-justified Control Register (AIC_I2SCR) */

#define	AIC_I2SCR_STPBK		(1 << 12) /* Stop BIT_CLK for I2S/MSB-justified */
#define	AIC_I2SCR_WL_BIT	1  /* Input/Output Sample Size for I2S/MSB-justified */
#define	AIC_I2SCR_WL_MASK	(0x7 << AIC_I2SCR_WL_BIT)
  #define AIC_I2SCR_WL_24BIT	  (0 << AIC_I2SCR_WL_BIT) /* Word Length is 24 bit */
  #define AIC_I2SCR_WL_20BIT	  (1 << AIC_I2SCR_WL_BIT) /* Word Length is 20 bit */
  #define AIC_I2SCR_WL_18BIT	  (2 << AIC_I2SCR_WL_BIT) /* Word Length is 18 bit */
  #define AIC_I2SCR_WL_16BIT	  (3 << AIC_I2SCR_WL_BIT) /* Word Length is 16 bit */
  #define AIC_I2SCR_WL_8BIT	  (4 << AIC_I2SCR_WL_BIT) /* Word Length is 8 bit */
#define	AIC_I2SCR_AMSL		(1 << 0) /* 0:I2S, 1:MSB-justified */

/* AIC Controller FIFO Status Register (AIC_SR) */

#define	AIC_SR_RFL_BIT		24  /* Receive FIFO Level */
#define	AIC_SR_RFL_MASK		(0x3f << AIC_SR_RFL_BIT)
#define	AIC_SR_TFL_BIT		8   /* Transmit FIFO level */
#define	AIC_SR_TFL_MASK		(0x3f << AIC_SR_TFL_BIT)
#define	AIC_SR_ROR		(1 << 6) /* Receive FIFO Overrun */
#define	AIC_SR_TUR		(1 << 5) /* Transmit FIFO Underrun */
#define	AIC_SR_RFS		(1 << 4) /* Receive FIFO Service Request */
#define	AIC_SR_TFS		(1 << 3) /* Transmit FIFO Service Request */

/* AIC Controller AC-link Status Register (AIC_ACSR) */

#define	AIC_ACSR_SLTERR		(1 << 21) /* Slot Error Flag */
#define	AIC_ACSR_CRDY		(1 << 20) /* External CODEC Ready Flag */
#define	AIC_ACSR_CLPM		(1 << 19) /* External CODEC low power mode flag */
#define	AIC_ACSR_RSTO		(1 << 18) /* External CODEC regs read status timeout */
#define	AIC_ACSR_SADR		(1 << 17) /* External CODEC regs status addr and data received */
#define	AIC_ACSR_CADT		(1 << 16) /* Command Address and Data Transmitted */

/* AIC Controller I2S/MSB-justified Status Register (AIC_I2SSR) */

#define	AIC_I2SSR_BSY		(1 << 2)  /* AIC Busy in I2S/MSB-justified format */

/* AIC Controller AC97 codec Command Address Register (AIC_ACCAR) */

#define	AIC_ACCAR_CAR_BIT	0
#define	AIC_ACCAR_CAR_MASK	(0xfffff << AIC_ACCAR_CAR_BIT)

/* AIC Controller AC97 codec Command Data Register (AIC_ACCDR) */

#define	AIC_ACCDR_CDR_BIT	0
#define	AIC_ACCDR_CDR_MASK	(0xfffff << AIC_ACCDR_CDR_BIT)

/* AIC Controller AC97 codec Status Address Register (AIC_ACSAR) */

#define	AIC_ACSAR_SAR_BIT	0
#define	AIC_ACSAR_SAR_MASK	(0xfffff << AIC_ACSAR_SAR_BIT)

/* AIC Controller AC97 codec Status Data Register (AIC_ACSDR) */

#define	AIC_ACSDR_SDR_BIT	0
#define	AIC_ACSDR_SDR_MASK	(0xfffff << AIC_ACSDR_SDR_BIT)

/* AIC Controller I2S/MSB-justified Clock Divider Register (AIC_I2SDIV) */

#define	AIC_I2SDIV_DIV_BIT	0
#define	AIC_I2SDIV_DIV_MASK	(0x7f << AIC_I2SDIV_DIV_BIT)
  #define AIC_I2SDIV_BITCLK_3072KHZ	(0x0C << AIC_I2SDIV_DIV_BIT) /* BIT_CLK of 3.072MHz */
  #define AIC_I2SDIV_BITCLK_2836KHZ	(0x0D << AIC_I2SDIV_DIV_BIT) /* BIT_CLK of 2.836MHz */
  #define AIC_I2SDIV_BITCLK_1418KHZ	(0x1A << AIC_I2SDIV_DIV_BIT) /* BIT_CLK of 1.418MHz */
  #define AIC_I2SDIV_BITCLK_1024KHZ	(0x24 << AIC_I2SDIV_DIV_BIT) /* BIT_CLK of 1.024MHz */
  #define AIC_I2SDIV_BITCLK_7089KHZ	(0x34 << AIC_I2SDIV_DIV_BIT) /* BIT_CLK of 708.92KHz */
  #define AIC_I2SDIV_BITCLK_512KHZ	(0x48 << AIC_I2SDIV_DIV_BIT) /* BIT_CLK of 512.00KHz */


/*************************************************************************
 * ICDC (Internal CODEC)
 *************************************************************************/
#define	ICDC_CR			(ICDC_BASE + 0x0400)  /* ICDC Control Register */
#define	ICDC_APWAIT		(ICDC_BASE + 0x0404)  /* Anti-Pop WAIT Stage Timing Control Register */
#define	ICDC_APPRE		(ICDC_BASE + 0x0408)  /* Anti-Pop HPEN-PRE Stage Timing Control Register */
#define	ICDC_APHPEN		(ICDC_BASE + 0x040C)  /* Anti-Pop HPEN Stage Timing Control Register */
#define	ICDC_APSR		(ICDC_BASE + 0x0410)  /* Anti-Pop Status Register */

#define	REG_ICDC_CR		REG32(ICDC_CR)
#define	REG_ICDC_APWAIT		REG32(ICDC_APWAIT)
#define	REG_ICDC_APPRE		REG32(ICDC_APPRE)
#define	REG_ICDC_APHPEN		REG32(ICDC_APHPEN)
#define	REG_ICDC_APSR		REG32(ICDC_APSR)

/* ICDC Control Register */
#define	ICDC_CR_LINVOL_BIT	24 /* LINE Input Volume Gain: GAIN=LINVOL*1.5-34.5 */
#define	ICDC_CR_LINVOL_MASK	(0x1f << ICDC_CR_LINVOL_BIT)
#define	ICDC_CR_ASRATE_BIT	20 /* Audio Sample Rate */
#define	ICDC_CR_ASRATE_MASK	(0x0f << ICDC_CR_ASRATE_BIT)
  #define ICDC_CR_ASRATE_8000	(0x0 << ICDC_CR_ASRATE_BIT)
  #define ICDC_CR_ASRATE_11025	(0x1 << ICDC_CR_ASRATE_BIT)
  #define ICDC_CR_ASRATE_12000	(0x2 << ICDC_CR_ASRATE_BIT)
  #define ICDC_CR_ASRATE_16000	(0x3 << ICDC_CR_ASRATE_BIT)
  #define ICDC_CR_ASRATE_22050	(0x4 << ICDC_CR_ASRATE_BIT)
  #define ICDC_CR_ASRATE_24000	(0x5 << ICDC_CR_ASRATE_BIT)
  #define ICDC_CR_ASRATE_32000	(0x6 << ICDC_CR_ASRATE_BIT)
  #define ICDC_CR_ASRATE_44100	(0x7 << ICDC_CR_ASRATE_BIT)
  #define ICDC_CR_ASRATE_48000	(0x8 << ICDC_CR_ASRATE_BIT)
#define	ICDC_CR_MICBG_BIT	18 /* MIC Boost Gain */
#define	ICDC_CR_MICBG_MASK	(0x3 << ICDC_CR_MICBG_BIT)
  #define ICDC_CR_MICBG_0DB	(0x0 << ICDC_CR_MICBG_BIT)
  #define ICDC_CR_MICBG_6DB	(0x1 << ICDC_CR_MICBG_BIT)
  #define ICDC_CR_MICBG_12DB	(0x2 << ICDC_CR_MICBG_BIT)
  #define ICDC_CR_MICBG_20DB	(0x3 << ICDC_CR_MICBG_BIT)
#define	ICDC_CR_HPVOL_BIT	16 /* Headphone Volume Gain */
#define	ICDC_CR_HPVOL_MASK	(0x3 << ICDC_CR_HPVOL_BIT)
  #define ICDC_CR_HPVOL_0DB	(0x0 << ICDC_CR_HPVOL_BIT)
  #define ICDC_CR_HPVOL_2DB	(0x1 << ICDC_CR_HPVOL_BIT)
  #define ICDC_CR_HPVOL_4DB	(0x2 << ICDC_CR_HPVOL_BIT)
  #define ICDC_CR_HPVOL_6DB	(0x3 << ICDC_CR_HPVOL_BIT)
#define ICDC_CR_ELINEIN		(1 << 13) /* Enable LINE Input */
#define ICDC_CR_EMIC		(1 << 12) /* Enable MIC Input */
#define ICDC_CR_SW1ON		(1 << 11) /* Switch 1 in CODEC is on */
#define ICDC_CR_EADC		(1 << 10) /* Enable ADC */
#define ICDC_CR_SW2ON		(1 << 9)  /* Switch 2 in CODEC is on */
#define ICDC_CR_EDAC		(1 << 8)  /* Enable DAC */
#define ICDC_CR_HPMUTE		(1 << 5)  /* Headphone Mute */
#define ICDC_CR_HPTON		(1 << 4)  /* Headphone Amplifier Trun On */
#define ICDC_CR_HPTOFF		(1 << 3)  /* Headphone Amplifier Trun Off */
#define ICDC_CR_TAAP		(1 << 2)  /* Turn Around of the Anti-Pop Procedure */
#define ICDC_CR_EAP		(1 << 1)  /* Enable Anti-Pop Procedure */
#define ICDC_CR_SUSPD		(1 << 0)  /* CODEC Suspend */

/* Anti-Pop WAIT Stage Timing Control Register */
#define	ICDC_APWAIT_WAITSN_BIT	0
#define	ICDC_APWAIT_WAITSN_MASK	(0x7ff << ICDC_APWAIT_WAITSN_BIT)

/* Anti-Pop HPEN-PRE Stage Timing Control Register */
#define	ICDC_APPRE_PRESN_BIT	0
#define	ICDC_APPRE_PRESN_MASK	(0x1ff << ICDC_APPRE_PRESN_BIT)

/* Anti-Pop HPEN Stage Timing Control Register */
#define	ICDC_APHPEN_HPENSN_BIT	0
#define	ICDC_APHPEN_HPENSN_MASK	(0x3fff << ICDC_APHPEN_HPENSN_BIT)

/* Anti-Pop Status Register */
#define	ICDC_SR_HPST_BIT	14  /* Headphone Amplifier State */
#define	ICDC_SR_HPST_MASK	(0x7 << ICDC_SR_HPST_BIT)
#define ICDC_SR_HPST_HP_OFF	 (0x0 << ICDC_SR_HPST_BIT) /* HP amplifier is off */
#define ICDC_SR_HPST_TON_WAIT	 (0x1 << ICDC_SR_HPST_BIT) /* wait state in turn-on */
  #define ICDC_SR_HPST_TON_PRE	 (0x2 << ICDC_SR_HPST_BIT) /* pre-enable state in turn-on */
#define ICDC_SR_HPST_TON_HPEN	 (0x3 << ICDC_SR_HPST_BIT) /* HP enable state in turn-on */
  #define ICDC_SR_HPST_TOFF_HPEN (0x4 << ICDC_SR_HPST_BIT) /* HP enable state in turn-off */
  #define ICDC_SR_HPST_TOFF_PRE  (0x5 << ICDC_SR_HPST_BIT) /* pre-enable state in turn-off */
  #define ICDC_SR_HPST_TOFF_WAIT (0x6 << ICDC_SR_HPST_BIT) /* wait state in turn-off */
  #define ICDC_SR_HPST_HP_ON	 (0x7 << ICDC_SR_HPST_BIT) /* HP amplifier is on */
#define	ICDC_SR_SNCNT_BIT	0  /* Sample Number Counter */
#define	ICDC_SR_SNCNT_MASK	(0x3fff << ICDC_SR_SNCNT_BIT)


/*************************************************************************
 * I2C
 *************************************************************************/
#define	I2C_DR			(I2C_BASE + 0x000)
#define	I2C_CR			(I2C_BASE + 0x004)
#define	I2C_SR			(I2C_BASE + 0x008)
#define	I2C_GR			(I2C_BASE + 0x00C)

#define	REG_I2C_DR		REG8(I2C_DR)
#define	REG_I2C_CR		REG8(I2C_CR)
#define REG_I2C_SR		REG8(I2C_SR)
#define REG_I2C_GR		REG16(I2C_GR)

/* I2C Control Register (I2C_CR) */

#define I2C_CR_IEN		(1 << 4)
#define I2C_CR_STA		(1 << 3)
#define I2C_CR_STO		(1 << 2)
#define I2C_CR_AC		(1 << 1)
#define I2C_CR_I2CE		(1 << 0)

/* I2C Status Register (I2C_SR) */

#define I2C_SR_STX		(1 << 4)
#define I2C_SR_BUSY		(1 << 3)
#define I2C_SR_TEND		(1 << 2)
#define I2C_SR_DRF		(1 << 1)
#define I2C_SR_ACKF		(1 << 0)


/*************************************************************************
 * SSI
 *************************************************************************/
#define	SSI_DR			(SSI_BASE + 0x000)
#define	SSI_CR0			(SSI_BASE + 0x004)
#define	SSI_CR1			(SSI_BASE + 0x008)
#define	SSI_SR			(SSI_BASE + 0x00C)
#define	SSI_ITR			(SSI_BASE + 0x010)
#define	SSI_ICR			(SSI_BASE + 0x014)
#define	SSI_GR			(SSI_BASE + 0x018)

#define	REG_SSI_DR		REG32(SSI_DR)
#define	REG_SSI_CR0		REG16(SSI_CR0)
#define	REG_SSI_CR1		REG32(SSI_CR1)
#define	REG_SSI_SR		REG32(SSI_SR)
#define	REG_SSI_ITR		REG16(SSI_ITR)
#define	REG_SSI_ICR		REG8(SSI_ICR)
#define	REG_SSI_GR		REG16(SSI_GR)

/* SSI Data Register (SSI_DR) */

#define	SSI_DR_GPC_BIT		0
#define	SSI_DR_GPC_MASK		(0x1ff << SSI_DR_GPC_BIT)

/* SSI Control Register 0 (SSI_CR0) */

#define SSI_CR0_SSIE		(1 << 15)
#define SSI_CR0_TIE		(1 << 14)
#define SSI_CR0_RIE		(1 << 13)
#define SSI_CR0_TEIE		(1 << 12)
#define SSI_CR0_REIE		(1 << 11)
#define SSI_CR0_LOOP		(1 << 10)
#define SSI_CR0_RFINE		(1 << 9)
#define SSI_CR0_RFINC		(1 << 8)
#define SSI_CR0_FSEL		(1 << 6)
#define SSI_CR0_TFLUSH		(1 << 2)
#define SSI_CR0_RFLUSH		(1 << 1)
#define SSI_CR0_DISREV		(1 << 0)

/* SSI Control Register 1 (SSI_CR1) */

#define SSI_CR1_FRMHL_BIT	30
#define SSI_CR1_FRMHL_MASK	(0x3 << SSI_CR1_FRMHL_BIT)
  #define SSI_CR1_FRMHL_CELOW_CE2LOW	(0 << SSI_CR1_FRMHL_BIT) /* SSI_CE_ is low valid and SSI_CE2_ is low valid */
  #define SSI_CR1_FRMHL_CEHIGH_CE2LOW	(1 << SSI_CR1_FRMHL_BIT) /* SSI_CE_ is high valid and SSI_CE2_ is low valid */
  #define SSI_CR1_FRMHL_CELOW_CE2HIGH	(2 << SSI_CR1_FRMHL_BIT) /* SSI_CE_ is low valid  and SSI_CE2_ is high valid */
  #define SSI_CR1_FRMHL_CEHIGH_CE2HIGH	(3 << SSI_CR1_FRMHL_BIT) /* SSI_CE_ is high valid and SSI_CE2_ is high valid */
#define SSI_CR1_TFVCK_BIT	28
#define SSI_CR1_TFVCK_MASK	(0x3 << SSI_CR1_TFVCK_BIT)
  #define SSI_CR1_TFVCK_0	  (0 << SSI_CR1_TFVCK_BIT)
  #define SSI_CR1_TFVCK_1	  (1 << SSI_CR1_TFVCK_BIT)
  #define SSI_CR1_TFVCK_2	  (2 << SSI_CR1_TFVCK_BIT)
  #define SSI_CR1_TFVCK_3	  (3 << SSI_CR1_TFVCK_BIT)
#define SSI_CR1_TCKFI_BIT	26
#define SSI_CR1_TCKFI_MASK	(0x3 << SSI_CR1_TCKFI_BIT)
  #define SSI_CR1_TCKFI_0	  (0 << SSI_CR1_TCKFI_BIT)
  #define SSI_CR1_TCKFI_1	  (1 << SSI_CR1_TCKFI_BIT)
  #define SSI_CR1_TCKFI_2	  (2 << SSI_CR1_TCKFI_BIT)
  #define SSI_CR1_TCKFI_3	  (3 << SSI_CR1_TCKFI_BIT)
#define SSI_CR1_LFST		(1 << 25)
#define SSI_CR1_ITFRM		(1 << 24)
#define SSI_CR1_UNFIN		(1 << 23)
#define SSI_CR1_MULTS		(1 << 22)
#define SSI_CR1_FMAT_BIT	20
#define SSI_CR1_FMAT_MASK	(0x3 << SSI_CR1_FMAT_BIT)
  #define SSI_CR1_FMAT_SPI	  (0 << SSI_CR1_FMAT_BIT) /* Motorola¡¯s SPI format */
  #define SSI_CR1_FMAT_SSP	  (1 << SSI_CR1_FMAT_BIT) /* TI's SSP format */
  #define SSI_CR1_FMAT_MW1	  (2 << SSI_CR1_FMAT_BIT) /* National Microwire 1 format */
  #define SSI_CR1_FMAT_MW2	  (3 << SSI_CR1_FMAT_BIT) /* National Microwire 2 format */
#define SSI_CR1_MCOM_BIT	12
#define SSI_CR1_MCOM_MASK	(0xf << SSI_CR1_MCOM_BIT)
  #define SSI_CR1_MCOM_1BIT	  (0x0 << SSI_CR1_MCOM_BIT) /* 1-bit command selected */
  #define SSI_CR1_MCOM_2BIT	  (0x1 << SSI_CR1_MCOM_BIT) /* 2-bit command selected */
  #define SSI_CR1_MCOM_3BIT	  (0x2 << SSI_CR1_MCOM_BIT) /* 3-bit command selected */
  #define SSI_CR1_MCOM_4BIT	  (0x3 << SSI_CR1_MCOM_BIT) /* 4-bit command selected */
  #define SSI_CR1_MCOM_5BIT	  (0x4 << SSI_CR1_MCOM_BIT) /* 5-bit command selected */
  #define SSI_CR1_MCOM_6BIT	  (0x5 << SSI_CR1_MCOM_BIT) /* 6-bit command selected */
  #define SSI_CR1_MCOM_7BIT	  (0x6 << SSI_CR1_MCOM_BIT) /* 7-bit command selected */
  #define SSI_CR1_MCOM_8BIT	  (0x7 << SSI_CR1_MCOM_BIT) /* 8-bit command selected */
  #define SSI_CR1_MCOM_9BIT	  (0x8 << SSI_CR1_MCOM_BIT) /* 9-bit command selected */
  #define SSI_CR1_MCOM_10BIT	  (0x9 << SSI_CR1_MCOM_BIT) /* 10-bit command selected */
  #define SSI_CR1_MCOM_11BIT	  (0xA << SSI_CR1_MCOM_BIT) /* 11-bit command selected */
  #define SSI_CR1_MCOM_12BIT	  (0xB << SSI_CR1_MCOM_BIT) /* 12-bit command selected */
  #define SSI_CR1_MCOM_13BIT	  (0xC << SSI_CR1_MCOM_BIT) /* 13-bit command selected */
  #define SSI_CR1_MCOM_14BIT	  (0xD << SSI_CR1_MCOM_BIT) /* 14-bit command selected */
  #define SSI_CR1_MCOM_15BIT	  (0xE << SSI_CR1_MCOM_BIT) /* 15-bit command selected */
  #define SSI_CR1_MCOM_16BIT	  (0xF << SSI_CR1_MCOM_BIT) /* 16-bit command selected */
#define SSI_CR1_TTRG_BIT	10
#define SSI_CR1_TTRG_MASK	(0x3 << SSI_CR1_TTRG_BIT)
  #define SSI_CR1_TTRG_1	  (0 << SSI_CR1_TTRG_BIT)/* Less than or equal to 1 */
  #define SSI_CR1_TTRG_4	  (1 << SSI_CR1_TTRG_BIT) /* Less than or equal to 4 */
  #define SSI_CR1_TTRG_8	  (2 << SSI_CR1_TTRG_BIT) /* Less than or equal to 8 */
  #define SSI_CR1_TTRG_14	  (3 << SSI_CR1_TTRG_BIT) /* Less than or equal to 14 */
#define SSI_CR1_RTRG_BIT	8
#define SSI_CR1_RTRG_MASK	(0x3 << SSI_CR1_RTRG_BIT)
  #define SSI_CR1_RTRG_1	  (0 << SSI_CR1_RTRG_BIT) /* More than or equal to 1 */
  #define SSI_CR1_RTRG_4	  (1 << SSI_CR1_RTRG_BIT) /* More than or equal to 4 */
  #define SSI_CR1_RTRG_8	  (2 << SSI_CR1_RTRG_BIT) /* More than or equal to 8 */
  #define SSI_CR1_RTRG_14	  (3 << SSI_CR1_RTRG_BIT) /* More than or equal to 14 */
#define SSI_CR1_FLEN_BIT	4
#define SSI_CR1_FLEN_MASK	(0xf << SSI_CR1_FLEN_BIT)
  #define SSI_CR1_FLEN_2BIT	  (0x0 << SSI_CR1_FLEN_BIT)
  #define SSI_CR1_FLEN_3BIT	  (0x1 << SSI_CR1_FLEN_BIT)
  #define SSI_CR1_FLEN_4BIT	  (0x2 << SSI_CR1_FLEN_BIT)
  #define SSI_CR1_FLEN_5BIT	  (0x3 << SSI_CR1_FLEN_BIT)
  #define SSI_CR1_FLEN_6BIT	  (0x4 << SSI_CR1_FLEN_BIT)
  #define SSI_CR1_FLEN_7BIT	  (0x5 << SSI_CR1_FLEN_BIT)
  #define SSI_CR1_FLEN_8BIT	  (0x6 << SSI_CR1_FLEN_BIT)
  #define SSI_CR1_FLEN_9BIT	  (0x7 << SSI_CR1_FLEN_BIT)
  #define SSI_CR1_FLEN_10BIT	  (0x8 << SSI_CR1_FLEN_BIT)
  #define SSI_CR1_FLEN_11BIT	  (0x9 << SSI_CR1_FLEN_BIT)
  #define SSI_CR1_FLEN_12BIT	  (0xA << SSI_CR1_FLEN_BIT)
  #define SSI_CR1_FLEN_13BIT	  (0xB << SSI_CR1_FLEN_BIT)
  #define SSI_CR1_FLEN_14BIT	  (0xC << SSI_CR1_FLEN_BIT)
  #define SSI_CR1_FLEN_15BIT	  (0xD << SSI_CR1_FLEN_BIT)
  #define SSI_CR1_FLEN_16BIT	  (0xE << SSI_CR1_FLEN_BIT)
  #define SSI_CR1_FLEN_17BIT	  (0xF << SSI_CR1_FLEN_BIT)
#define SSI_CR1_PHA		(1 << 1)
#define SSI_CR1_POL		(1 << 0)

/* SSI Status Register (SSI_SR) */

#define SSI_SR_TFIFONUM_BIT	13
#define SSI_SR_TFIFONUM_MASK	(0x1f << SSI_SR_TFIFONUM_BIT)
#define SSI_SR_RFIFONUM_BIT	8
#define SSI_SR_RFIFONUM_MASK	(0x1f << SSI_SR_RFIFONUM_BIT)
#define SSI_SR_END		(1 << 7)
#define SSI_SR_BUSY		(1 << 6)
#define SSI_SR_TFF		(1 << 5)
#define SSI_SR_RFE		(1 << 4)
#define SSI_SR_TFHE		(1 << 3)
#define SSI_SR_RFHF		(1 << 2)
#define SSI_SR_UNDR		(1 << 1)
#define SSI_SR_OVER		(1 << 0)

/* SSI Interval Time Control Register (SSI_ITR) */

#define	SSI_ITR_CNTCLK		(1 << 15)
#define SSI_ITR_IVLTM_BIT	0
#define SSI_ITR_IVLTM_MASK	(0x7fff << SSI_ITR_IVLTM_BIT)


/*************************************************************************
 * MSC
 *************************************************************************/
#define	MSC_STRPCL		(MSC_BASE + 0x000)
#define	MSC_STAT		(MSC_BASE + 0x004)
#define	MSC_CLKRT		(MSC_BASE + 0x008)
#define	MSC_CMDAT		(MSC_BASE + 0x00C)
#define	MSC_RESTO		(MSC_BASE + 0x010)
#define	MSC_RDTO		(MSC_BASE + 0x014)
#define	MSC_BLKLEN		(MSC_BASE + 0x018)
#define	MSC_NOB			(MSC_BASE + 0x01C)
#define	MSC_SNOB		(MSC_BASE + 0x020)
#define	MSC_IMASK		(MSC_BASE + 0x024)
#define	MSC_IREG		(MSC_BASE + 0x028)
#define	MSC_CMD			(MSC_BASE + 0x02C)
#define	MSC_ARG			(MSC_BASE + 0x030)
#define	MSC_RES			(MSC_BASE + 0x034)
#define	MSC_RXFIFO		(MSC_BASE + 0x038)
#define	MSC_TXFIFO		(MSC_BASE + 0x03C)

#define	REG_MSC_STRPCL		REG16(MSC_STRPCL)
#define	REG_MSC_STAT		REG32(MSC_STAT)
#define	REG_MSC_CLKRT		REG16(MSC_CLKRT)
#define	REG_MSC_CMDAT		REG32(MSC_CMDAT)
#define	REG_MSC_RESTO		REG16(MSC_RESTO)
#define	REG_MSC_RDTO		REG16(MSC_RDTO)
#define	REG_MSC_BLKLEN		REG16(MSC_BLKLEN)
#define	REG_MSC_NOB		REG16(MSC_NOB)
#define	REG_MSC_SNOB		REG16(MSC_SNOB)
#define	REG_MSC_IMASK		REG16(MSC_IMASK)
#define	REG_MSC_IREG		REG16(MSC_IREG)
#define	REG_MSC_CMD		REG8(MSC_CMD)
#define	REG_MSC_ARG		REG32(MSC_ARG)
#define	REG_MSC_RES		REG16(MSC_RES)
#define	REG_MSC_RXFIFO		REG32(MSC_RXFIFO)
#define	REG_MSC_TXFIFO		REG32(MSC_TXFIFO)

/* MSC Clock and Control Register (MSC_STRPCL) */

#define MSC_STRPCL_EXIT_MULTIPLE	(1 << 7)
#define MSC_STRPCL_EXIT_TRANSFER	(1 << 6)
#define MSC_STRPCL_START_READWAIT	(1 << 5)
#define MSC_STRPCL_STOP_READWAIT	(1 << 4)
#define MSC_STRPCL_RESET		(1 << 3)
#define MSC_STRPCL_START_OP		(1 << 2)
#define MSC_STRPCL_CLOCK_CONTROL_BIT	0
#define MSC_STRPCL_CLOCK_CONTROL_MASK	(0x3 << MSC_STRPCL_CLOCK_CONTROL_BIT)
  #define MSC_STRPCL_CLOCK_CONTROL_STOP	  (0x1 << MSC_STRPCL_CLOCK_CONTROL_BIT) /* Stop MMC/SD clock */
  #define MSC_STRPCL_CLOCK_CONTROL_START  (0x2 << MSC_STRPCL_CLOCK_CONTROL_BIT) /* Start MMC/SD clock */

/* MSC Status Register (MSC_STAT) */

#define MSC_STAT_IS_RESETTING		(1 << 15)
#define MSC_STAT_SDIO_INT_ACTIVE	(1 << 14)
#define MSC_STAT_PRG_DONE		(1 << 13)
#define MSC_STAT_DATA_TRAN_DONE		(1 << 12)
#define MSC_STAT_END_CMD_RES		(1 << 11)
#define MSC_STAT_DATA_FIFO_AFULL	(1 << 10)
#define MSC_STAT_IS_READWAIT		(1 << 9)
#define MSC_STAT_CLK_EN			(1 << 8)
#define MSC_STAT_DATA_FIFO_FULL		(1 << 7)
#define MSC_STAT_DATA_FIFO_EMPTY	(1 << 6)
#define MSC_STAT_CRC_RES_ERR		(1 << 5)
#define MSC_STAT_CRC_READ_ERROR		(1 << 4)
#define MSC_STAT_CRC_WRITE_ERROR_BIT	2
#define MSC_STAT_CRC_WRITE_ERROR_MASK	(0x3 << MSC_STAT_CRC_WRITE_ERROR_BIT)
  #define MSC_STAT_CRC_WRITE_ERROR_NO		(0 << MSC_STAT_CRC_WRITE_ERROR_BIT) /* No error on transmission of data */
  #define MSC_STAT_CRC_WRITE_ERROR		(1 << MSC_STAT_CRC_WRITE_ERROR_BIT) /* Card observed erroneous transmission of data */
  #define MSC_STAT_CRC_WRITE_ERROR_NOSTS	(2 << MSC_STAT_CRC_WRITE_ERROR_BIT) /* No CRC status is sent back */
#define MSC_STAT_TIME_OUT_RES		(1 << 1)
#define MSC_STAT_TIME_OUT_READ		(1 << 0)

/* MSC Bus Clock Control Register (MSC_CLKRT) */

#define	MSC_CLKRT_CLK_RATE_BIT		0
#define	MSC_CLKRT_CLK_RATE_MASK		(0x7 << MSC_CLKRT_CLK_RATE_BIT)
  #define MSC_CLKRT_CLK_RATE_DIV_1	  (0x0 << MSC_CLKRT_CLK_RATE_BIT) /* CLK_SRC */
  #define MSC_CLKRT_CLK_RATE_DIV_2	  (0x1 << MSC_CLKRT_CLK_RATE_BIT) /* 1/2 of CLK_SRC */
  #define MSC_CLKRT_CLK_RATE_DIV_4	  (0x2 << MSC_CLKRT_CLK_RATE_BIT) /* 1/4 of CLK_SRC */
  #define MSC_CLKRT_CLK_RATE_DIV_8	  (0x3 << MSC_CLKRT_CLK_RATE_BIT) /* 1/8 of CLK_SRC */
  #define MSC_CLKRT_CLK_RATE_DIV_16	  (0x4 << MSC_CLKRT_CLK_RATE_BIT) /* 1/16 of CLK_SRC */
  #define MSC_CLKRT_CLK_RATE_DIV_32	  (0x5 << MSC_CLKRT_CLK_RATE_BIT) /* 1/32 of CLK_SRC */
  #define MSC_CLKRT_CLK_RATE_DIV_64	  (0x6 << MSC_CLKRT_CLK_RATE_BIT) /* 1/64 of CLK_SRC */
  #define MSC_CLKRT_CLK_RATE_DIV_128	  (0x7 << MSC_CLKRT_CLK_RATE_BIT) /* 1/128 of CLK_SRC */

/* MSC Command Sequence Control Register (MSC_CMDAT) */

#define	MSC_CMDAT_IO_ABORT		(1 << 11)
#define	MSC_CMDAT_BUS_WIDTH_BIT		9
#define	MSC_CMDAT_BUS_WIDTH_MASK	(0x3 << MSC_CMDAT_BUS_WIDTH_BIT)
  #define MSC_CMDAT_BUS_WIDTH_1BIT	  (0x0 << MSC_CMDAT_BUS_WIDTH_BIT) /* 1-bit data bus */
  #define MSC_CMDAT_BUS_WIDTH_4BIT	  (0x2 << MSC_CMDAT_BUS_WIDTH_BIT) /* 4-bit data bus */
  #define CMDAT_BUS_WIDTH1	  (0x0 << MSC_CMDAT_BUS_WIDTH_BIT)
  #define CMDAT_BUS_WIDTH4	  (0x2 << MSC_CMDAT_BUS_WIDTH_BIT)
#define	MSC_CMDAT_DMA_EN		(1 << 8)
#define	MSC_CMDAT_INIT			(1 << 7)
#define	MSC_CMDAT_BUSY			(1 << 6)
#define	MSC_CMDAT_STREAM_BLOCK		(1 << 5)
#define	MSC_CMDAT_WRITE			(1 << 4)
#define	MSC_CMDAT_READ			(0 << 4)
#define	MSC_CMDAT_DATA_EN		(1 << 3)
#define	MSC_CMDAT_RESPONSE_BIT	0
#define	MSC_CMDAT_RESPONSE_MASK	(0x7 << MSC_CMDAT_RESPONSE_BIT)
  #define MSC_CMDAT_RESPONSE_NONE  (0x0 << MSC_CMDAT_RESPONSE_BIT) /* No response */
  #define MSC_CMDAT_RESPONSE_R1	  (0x1 << MSC_CMDAT_RESPONSE_BIT) /* Format R1 and R1b */
  #define MSC_CMDAT_RESPONSE_R2	  (0x2 << MSC_CMDAT_RESPONSE_BIT) /* Format R2 */
  #define MSC_CMDAT_RESPONSE_R3	  (0x3 << MSC_CMDAT_RESPONSE_BIT) /* Format R3 */
  #define MSC_CMDAT_RESPONSE_R4	  (0x4 << MSC_CMDAT_RESPONSE_BIT) /* Format R4 */
  #define MSC_CMDAT_RESPONSE_R5	  (0x5 << MSC_CMDAT_RESPONSE_BIT) /* Format R5 */
  #define MSC_CMDAT_RESPONSE_R6	  (0x6 << MSC_CMDAT_RESPONSE_BIT) /* Format R6 */

#define	CMDAT_DMA_EN	(1 << 8)
#define	CMDAT_INIT	(1 << 7)
#define	CMDAT_BUSY	(1 << 6)
#define	CMDAT_STREAM	(1 << 5)
#define	CMDAT_WRITE	(1 << 4)
#define	CMDAT_DATA_EN	(1 << 3)

/* MSC Interrupts Mask Register (MSC_IMASK) */

#define	MSC_IMASK_SDIO			(1 << 7)
#define	MSC_IMASK_TXFIFO_WR_REQ		(1 << 6)
#define	MSC_IMASK_RXFIFO_RD_REQ		(1 << 5)
#define	MSC_IMASK_END_CMD_RES		(1 << 2)
#define	MSC_IMASK_PRG_DONE		(1 << 1)
#define	MSC_IMASK_DATA_TRAN_DONE	(1 << 0)


/* MSC Interrupts Status Register (MSC_IREG) */

#define	MSC_IREG_SDIO			(1 << 7)
#define	MSC_IREG_TXFIFO_WR_REQ		(1 << 6)
#define	MSC_IREG_RXFIFO_RD_REQ		(1 << 5)
#define	MSC_IREG_END_CMD_RES		(1 << 2)
#define	MSC_IREG_PRG_DONE		(1 << 1)
#define	MSC_IREG_DATA_TRAN_DONE		(1 << 0)


/*************************************************************************
 * EMC
 *************************************************************************/
#define EMC_BCR		(EMC_BASE + 0x00)
#define EMC_SMCR0	(EMC_BASE + 0x10)
#define EMC_SMCR1	(EMC_BASE + 0x14)
#define EMC_SMCR2	(EMC_BASE + 0x18)
#define EMC_SMCR3	(EMC_BASE + 0x1c)
#define EMC_SMCR4	(EMC_BASE + 0x20)
#define EMC_SMCR5	(EMC_BASE + 0x24)
#define EMC_SMCR6	(EMC_BASE + 0x28)
#define EMC_SMCR7	(EMC_BASE + 0x2c)
#define EMC_SACR0	(EMC_BASE + 0x30)
#define EMC_SACR1	(EMC_BASE + 0x34)
#define EMC_SACR2	(EMC_BASE + 0x38)
#define EMC_SACR3	(EMC_BASE + 0x3c)
#define EMC_SACR4	(EMC_BASE + 0x40)
#define EMC_SACR5	(EMC_BASE + 0x44)
#define EMC_SACR6	(EMC_BASE + 0x48)
#define EMC_SACR7	(EMC_BASE + 0x4c)
#define EMC_NFCSR	(EMC_BASE + 0x50)
#define EMC_NFECC	(EMC_BASE + 0x54)
#define EMC_PCCR1	(EMC_BASE + 0x60)
#define EMC_PCCR2	(EMC_BASE + 0x64)
#define EMC_PCCR3	(EMC_BASE + 0x68)
#define EMC_PCCR4	(EMC_BASE + 0x6c)
#define EMC_DMCR	(EMC_BASE + 0x80)
#define EMC_RTCSR	(EMC_BASE + 0x84)
#define EMC_RTCNT	(EMC_BASE + 0x88)
#define EMC_RTCOR	(EMC_BASE + 0x8c)
#define EMC_DMAR1	(EMC_BASE + 0x90)
#define EMC_DMAR2	(EMC_BASE + 0x94)
#define EMC_DMAR3	(EMC_BASE + 0x98)
#define EMC_DMAR4	(EMC_BASE + 0x9c)

#define EMC_SDMR0	(EMC_BASE + 0xa000)
#define EMC_SDMR1	(EMC_BASE + 0xb000)
#define EMC_SDMR2	(EMC_BASE + 0xc000)
#define EMC_SDMR3	(EMC_BASE + 0xd000)

#define REG_EMC_BCR	REG32(EMC_BCR)
#define REG_EMC_SMCR0	REG32(EMC_SMCR0)
#define REG_EMC_SMCR1	REG32(EMC_SMCR1)
#define REG_EMC_SMCR2	REG32(EMC_SMCR2)
#define REG_EMC_SMCR3	REG32(EMC_SMCR3)
#define REG_EMC_SMCR4	REG32(EMC_SMCR4)
#define REG_EMC_SMCR5	REG32(EMC_SMCR5)
#define REG_EMC_SMCR6	REG32(EMC_SMCR6)
#define REG_EMC_SMCR7	REG32(EMC_SMCR7)
#define REG_EMC_SACR0	REG32(EMC_SACR0)
#define REG_EMC_SACR1	REG32(EMC_SACR1)
#define REG_EMC_SACR2	REG32(EMC_SACR2)
#define REG_EMC_SACR3	REG32(EMC_SACR3)
#define REG_EMC_SACR4	REG32(EMC_SACR4)
#define REG_EMC_SACR5	REG32(EMC_SACR5)
#define REG_EMC_SACR6	REG32(EMC_SACR6)
#define REG_EMC_SACR7	REG32(EMC_SACR7)
#define REG_EMC_NFCSR	REG32(EMC_NFCSR)
#define REG_EMC_NFECC	REG32(EMC_NFECC)
#define REG_EMC_DMCR	REG32(EMC_DMCR)
#define REG_EMC_RTCSR	REG16(EMC_RTCSR)
#define REG_EMC_RTCNT	REG16(EMC_RTCNT)
#define REG_EMC_RTCOR	REG16(EMC_RTCOR)
#define REG_EMC_DMAR1	REG32(EMC_DMAR1)
#define REG_EMC_DMAR2	REG32(EMC_DMAR2)
#define REG_EMC_DMAR3	REG32(EMC_DMAR3)
#define REG_EMC_DMAR4	REG32(EMC_DMAR4)
#define REG_EMC_PCCR1	REG32(EMC_PCCR1)
#define REG_EMC_PCCR2	REG32(EMC_PCCR2)
#define REG_EMC_PCCR3	REG32(EMC_PCCR3)
#define REG_EMC_PCCR4	REG32(EMC_PCCR4)


#define EMC_BCR_BRE		(1 << 1)

#define EMC_SMCR_STRV_BIT	24
#define EMC_SMCR_STRV_MASK	(0x0f << EMC_SMCR_STRV_BIT)
#define EMC_SMCR_TAW_BIT	20
#define EMC_SMCR_TAW_MASK	(0x0f << EMC_SMCR_TAW_BIT)
#define EMC_SMCR_TBP_BIT	16
#define EMC_SMCR_TBP_MASK	(0x0f << EMC_SMCR_TBP_BIT)
#define EMC_SMCR_TAH_BIT	12
#define EMC_SMCR_TAH_MASK	(0x07 << EMC_SMCR_TAH_BIT)
#define EMC_SMCR_TAS_BIT	8
#define EMC_SMCR_TAS_MASK	(0x07 << EMC_SMCR_TAS_BIT)
#define EMC_SMCR_BW_BIT		6
#define EMC_SMCR_BW_MASK	(0x03 << EMC_SMCR_BW_BIT)
  #define EMC_SMCR_BW_8BIT	(0 << EMC_SMCR_BW_BIT)
  #define EMC_SMCR_BW_16BIT	(1 << EMC_SMCR_BW_BIT)
  #define EMC_SMCR_BW_32BIT	(2 << EMC_SMCR_BW_BIT)
#define EMC_SMCR_BCM		(1 << 3)
#define EMC_SMCR_BL_BIT		1
#define EMC_SMCR_BL_MASK	(0x03 << EMC_SMCR_BL_BIT)
  #define EMC_SMCR_BL_4		(0 << EMC_SMCR_BL_BIT)
  #define EMC_SMCR_BL_8		(1 << EMC_SMCR_BL_BIT)
  #define EMC_SMCR_BL_16	(2 << EMC_SMCR_BL_BIT)
  #define EMC_SMCR_BL_32	(3 << EMC_SMCR_BL_BIT)
#define EMC_SMCR_SMT		(1 << 0)

#define EMC_SACR_BASE_BIT	8
#define EMC_SACR_BASE_MASK	(0xff << EMC_SACR_BASE_BIT)
#define EMC_SACR_MASK_BIT	0
#define EMC_SACR_MASK_MASK	(0xff << EMC_SACR_MASK_BIT)

#define EMC_NFCSR_RB		(1 << 7)
#define EMC_NFCSR_BOOT_SEL_BIT	4
#define EMC_NFCSR_BOOT_SEL_MASK	(0x07 << EMC_NFCSR_BOOT_SEL_BIT)
#define EMC_NFCSR_ERST		(1 << 3)
#define EMC_NFCSR_ECCE		(1 << 2)
#define EMC_NFCSR_FCE		(1 << 1)
#define EMC_NFCSR_NFE		(1 << 0)

#define EMC_NFECC_ECC2_BIT	16
#define EMC_NFECC_ECC2_MASK	(0xff << EMC_NFECC_ECC2_BIT)
#define EMC_NFECC_ECC1_BIT	8
#define EMC_NFECC_ECC1_MASK	(0xff << EMC_NFECC_ECC1_BIT)
#define EMC_NFECC_ECC0_BIT	0
#define EMC_NFECC_ECC0_MASK	(0xff << EMC_NFECC_ECC0_BIT)

#define EMC_DMCR_BW_BIT		31
#define EMC_DMCR_BW		(1 << EMC_DMCR_BW_BIT)
#define EMC_DMCR_CA_BIT		26
#define EMC_DMCR_CA_MASK	(0x07 << EMC_DMCR_CA_BIT)
  #define EMC_DMCR_CA_8		(0 << EMC_DMCR_CA_BIT)
  #define EMC_DMCR_CA_9		(1 << EMC_DMCR_CA_BIT)
  #define EMC_DMCR_CA_10	(2 << EMC_DMCR_CA_BIT)
  #define EMC_DMCR_CA_11	(3 << EMC_DMCR_CA_BIT)
  #define EMC_DMCR_CA_12	(4 << EMC_DMCR_CA_BIT)
#define EMC_DMCR_RMODE		(1 << 25)
#define EMC_DMCR_RFSH		(1 << 24)
#define EMC_DMCR_MRSET		(1 << 23)
#define EMC_DMCR_RA_BIT		20
#define EMC_DMCR_RA_MASK	(0x03 << EMC_DMCR_RA_BIT)
  #define EMC_DMCR_RA_11	(0 << EMC_DMCR_RA_BIT)
  #define EMC_DMCR_RA_12	(1 << EMC_DMCR_RA_BIT)
  #define EMC_DMCR_RA_13	(2 << EMC_DMCR_RA_BIT)
#define EMC_DMCR_BA_BIT		19
#define EMC_DMCR_BA		(1 << EMC_DMCR_BA_BIT)
#define EMC_DMCR_PDM		(1 << 18)
#define EMC_DMCR_EPIN		(1 << 17)
#define EMC_DMCR_TRAS_BIT	13
#define EMC_DMCR_TRAS_MASK	(0x07 << EMC_DMCR_TRAS_BIT)
#define EMC_DMCR_RCD_BIT	11
#define EMC_DMCR_RCD_MASK	(0x03 << EMC_DMCR_RCD_BIT)
#define EMC_DMCR_TPC_BIT	8
#define EMC_DMCR_TPC_MASK	(0x07 << EMC_DMCR_TPC_BIT)
#define EMC_DMCR_TRWL_BIT	5
#define EMC_DMCR_TRWL_MASK	(0x03 << EMC_DMCR_TRWL_BIT)
#define EMC_DMCR_TRC_BIT	2
#define EMC_DMCR_TRC_MASK	(0x07 << EMC_DMCR_TRC_BIT)
#define EMC_DMCR_TCL_BIT	0
#define EMC_DMCR_TCL_MASK	(0x03 << EMC_DMCR_TCL_BIT)

#define EMC_RTCSR_CMF		(1 << 7)
#define EMC_RTCSR_CKS_BIT	0
#define EMC_RTCSR_CKS_MASK	(0x07 << EMC_RTCSR_CKS_BIT)
  #define EMC_RTCSR_CKS_DISABLE	(0 << EMC_RTCSR_CKS_BIT)
  #define EMC_RTCSR_CKS_4	(1 << EMC_RTCSR_CKS_BIT)
  #define EMC_RTCSR_CKS_16	(2 << EMC_RTCSR_CKS_BIT)
  #define EMC_RTCSR_CKS_64	(3 << EMC_RTCSR_CKS_BIT)
  #define EMC_RTCSR_CKS_256	(4 << EMC_RTCSR_CKS_BIT)
  #define EMC_RTCSR_CKS_1024	(5 << EMC_RTCSR_CKS_BIT)
  #define EMC_RTCSR_CKS_2048	(6 << EMC_RTCSR_CKS_BIT)
  #define EMC_RTCSR_CKS_4096	(7 << EMC_RTCSR_CKS_BIT)

#define EMC_DMAR_BASE_BIT	8
#define EMC_DMAR_BASE_MASK	(0xff << EMC_DMAR_BASE_BIT)
#define EMC_DMAR_MASK_BIT	0
#define EMC_DMAR_MASK_MASK	(0xff << EMC_DMAR_MASK_BIT)

#define EMC_SDMR_BM		(1 << 9)
#define EMC_SDMR_OM_BIT		7
#define EMC_SDMR_OM_MASK	(3 << EMC_SDMR_OM_BIT)
  #define EMC_SDMR_OM_NORMAL	(0 << EMC_SDMR_OM_BIT)
#define EMC_SDMR_CAS_BIT	4
#define EMC_SDMR_CAS_MASK	(7 << EMC_SDMR_CAS_BIT)
  #define EMC_SDMR_CAS_1	(1 << EMC_SDMR_CAS_BIT)
  #define EMC_SDMR_CAS_2	(2 << EMC_SDMR_CAS_BIT)
  #define EMC_SDMR_CAS_3	(3 << EMC_SDMR_CAS_BIT)
#define EMC_SDMR_BT_BIT		3
#define EMC_SDMR_BT_MASK	(1 << EMC_SDMR_BT_BIT)
  #define EMC_SDMR_BT_SEQ	(0 << EMC_SDMR_BT_BIT)
  #define EMC_SDMR_BT_INTR	(1 << EMC_SDMR_BT_BIT)
#define EMC_SDMR_BL_BIT		0
#define EMC_SDMR_BL_MASK	(7 << EMC_SDMR_BL_BIT)
  #define EMC_SDMR_BL_1		(0 << EMC_SDMR_BL_BIT)
  #define EMC_SDMR_BL_2		(1 << EMC_SDMR_BL_BIT)
  #define EMC_SDMR_BL_4		(2 << EMC_SDMR_BL_BIT)
  #define EMC_SDMR_BL_8		(3 << EMC_SDMR_BL_BIT)

#define EMC_SDMR_CAS2_16BIT \
  (EMC_SDMR_CAS_2 | EMC_SDMR_BT_SEQ | EMC_SDMR_BL_2)
#define EMC_SDMR_CAS2_32BIT \
  (EMC_SDMR_CAS_2 | EMC_SDMR_BT_SEQ | EMC_SDMR_BL_4)
#define EMC_SDMR_CAS3_16BIT \
  (EMC_SDMR_CAS_3 | EMC_SDMR_BT_SEQ | EMC_SDMR_BL_2)
#define EMC_SDMR_CAS3_32BIT \
  (EMC_SDMR_CAS_3 | EMC_SDMR_BT_SEQ | EMC_SDMR_BL_4)

#define EMC_PCCR12_AMW		(1 << 31)
#define EMC_PCCR12_AMAS_BIT	28
#define EMC_PCCR12_AMAS_MASK	(0x07 << EMC_PCCR12_AMAS_BIT)
#define EMC_PCCR12_AMAH_BIT	24
#define EMC_PCCR12_AMAH_MASK	(0x07 << EMC_PCCR12_AMAH_BIT)
#define EMC_PCCR12_AMPW_BIT	20
#define EMC_PCCR12_AMPW_MASK	(0x0f << EMC_PCCR12_AMPW_BIT)
#define EMC_PCCR12_AMRT_BIT	16
#define EMC_PCCR12_AMRT_MASK	(0x0f << EMC_PCCR12_AMRT_BIT)
#define EMC_PCCR12_CMW		(1 << 15)
#define EMC_PCCR12_CMAS_BIT	12
#define EMC_PCCR12_CMAS_MASK	(0x07 << EMC_PCCR12_CMAS_BIT)
#define EMC_PCCR12_CMAH_BIT	8
#define EMC_PCCR12_CMAH_MASK	(0x07 << EMC_PCCR12_CMAH_BIT)
#define EMC_PCCR12_CMPW_BIT	4
#define EMC_PCCR12_CMPW_MASK	(0x0f << EMC_PCCR12_CMPW_BIT)
#define EMC_PCCR12_CMRT_BIT	0
#define EMC_PCCR12_CMRT_MASK	(0x07 << EMC_PCCR12_CMRT_BIT)

#define EMC_PCCR34_DRS_BIT	16
#define EMC_PCCR34_DRS_MASK	(0x03 << EMC_PCCR34_DRS_BIT)
  #define EMC_PCCR34_DRS_SPKR	(1 << EMC_PCCR34_DRS_BIT)
  #define EMC_PCCR34_DRS_IOIS16	(2 << EMC_PCCR34_DRS_BIT)
  #define EMC_PCCR34_DRS_INPACK	(3 << EMC_PCCR34_DRS_BIT)
#define EMC_PCCR34_IOIS16	(1 << 15)
#define EMC_PCCR34_IOW		(1 << 14)
#define EMC_PCCR34_TCB_BIT	12
#define EMC_PCCR34_TCB_MASK	(0x03 << EMC_PCCR34_TCB_BIT)
#define EMC_PCCR34_IORT_BIT	8
#define EMC_PCCR34_IORT_MASK	(0x07 << EMC_PCCR34_IORT_BIT)
#define EMC_PCCR34_IOAE_BIT	6
#define EMC_PCCR34_IOAE_MASK	(0x03 << EMC_PCCR34_IOAE_BIT)
  #define EMC_PCCR34_IOAE_NONE	(0 << EMC_PCCR34_IOAE_BIT)
  #define EMC_PCCR34_IOAE_1	(1 << EMC_PCCR34_IOAE_BIT)
  #define EMC_PCCR34_IOAE_2	(2 << EMC_PCCR34_IOAE_BIT)
  #define EMC_PCCR34_IOAE_5	(3 << EMC_PCCR34_IOAE_BIT)
#define EMC_PCCR34_IOAH_BIT	4
#define EMC_PCCR34_IOAH_MASK	(0x03 << EMC_PCCR34_IOAH_BIT)
  #define EMC_PCCR34_IOAH_NONE	(0 << EMC_PCCR34_IOAH_BIT)
  #define EMC_PCCR34_IOAH_1	(1 << EMC_PCCR34_IOAH_BIT)
  #define EMC_PCCR34_IOAH_2	(2 << EMC_PCCR34_IOAH_BIT)
  #define EMC_PCCR34_IOAH_5	(3 << EMC_PCCR34_IOAH_BIT)
#define EMC_PCCR34_IOPW_BIT	0
#define EMC_PCCR34_IOPW_MASK	(0x0f << EMC_PCCR34_IOPW_BIT)


/*************************************************************************
 * ETH
 *************************************************************************/
#define ETH_BMR		(ETH_BASE + 0x1000)
#define ETH_TPDR	(ETH_BASE + 0x1004)
#define ETH_RPDR	(ETH_BASE + 0x1008)
#define ETH_RAR		(ETH_BASE + 0x100C)
#define ETH_TAR		(ETH_BASE + 0x1010)
#define ETH_SR		(ETH_BASE + 0x1014)
#define ETH_CR		(ETH_BASE + 0x1018)
#define ETH_IER		(ETH_BASE + 0x101C)
#define ETH_MFCR	(ETH_BASE + 0x1020)
#define ETH_CTAR	(ETH_BASE + 0x1050)
#define ETH_CRAR	(ETH_BASE + 0x1054)
#define ETH_MCR		(ETH_BASE + 0x0000)
#define ETH_MAHR	(ETH_BASE + 0x0004)
#define ETH_MALR	(ETH_BASE + 0x0008)
#define ETH_HTHR	(ETH_BASE + 0x000C)
#define ETH_HTLR	(ETH_BASE + 0x0010)
#define ETH_MIAR	(ETH_BASE + 0x0014)
#define ETH_MIDR	(ETH_BASE + 0x0018)
#define ETH_FCR		(ETH_BASE + 0x001C)
#define ETH_VTR1	(ETH_BASE + 0x0020)
#define ETH_VTR2	(ETH_BASE + 0x0024)
#define ETH_WKFR	(ETH_BASE + 0x0028)
#define ETH_PMTR	(ETH_BASE + 0x002C)

#define REG_ETH_BMR	REG32(ETH_BMR)
#define REG_ETH_TPDR	REG32(ETH_TPDR)
#define REG_ETH_RPDR	REG32(ETH_RPDR)
#define REG_ETH_RAR	REG32(ETH_RAR)
#define REG_ETH_TAR	REG32(ETH_TAR)
#define REG_ETH_SR	REG32(ETH_SR)
#define REG_ETH_CR	REG32(ETH_CR)
#define REG_ETH_IER	REG32(ETH_IER)
#define REG_ETH_MFCR	REG32(ETH_MFCR)
#define REG_ETH_CTAR	REG32(ETH_CTAR)
#define REG_ETH_CRAR	REG32(ETH_CRAR)
#define REG_ETH_MCR	REG32(ETH_MCR)
#define REG_ETH_MAHR	REG32(ETH_MAHR)
#define REG_ETH_MALR	REG32(ETH_MALR)
#define REG_ETH_HTHR	REG32(ETH_HTHR)
#define REG_ETH_HTLR	REG32(ETH_HTLR)
#define REG_ETH_MIAR	REG32(ETH_MIAR)
#define REG_ETH_MIDR	REG32(ETH_MIDR)
#define REG_ETH_FCR	REG32(ETH_FCR)
#define REG_ETH_VTR1	REG32(ETH_VTR1)
#define REG_ETH_VTR2	REG32(ETH_VTR2)
#define REG_ETH_WKFR	REG32(ETH_WKFR)
#define REG_ETH_PMTR	REG32(ETH_PMTR)

/* Bus Mode Register (ETH_BMR) */

#define ETH_BMR_DBO		(1 << 20)
#define ETH_BMR_PBL_BIT		8
#define ETH_BMR_PBL_MASK	(0x3f << ETH_BMR_PBL_BIT)
  #define ETH_BMR_PBL_1		  (0x1 << ETH_BMR_PBL_BIT)
  #define ETH_BMR_PBL_4		  (0x4 << ETH_BMR_PBL_BIT)
#define ETH_BMR_BLE		(1 << 7)
#define ETH_BMR_DSL_BIT		2
#define ETH_BMR_DSL_MASK	(0x1f << ETH_BMR_DSL_BIT)
  #define ETH_BMR_DSL_0		  (0x0 << ETH_BMR_DSL_BIT)
  #define ETH_BMR_DSL_1		  (0x1 << ETH_BMR_DSL_BIT)
  #define ETH_BMR_DSL_2		  (0x2 << ETH_BMR_DSL_BIT)
  #define ETH_BMR_DSL_4		  (0x4 << ETH_BMR_DSL_BIT)
  #define ETH_BMR_DSL_8		  (0x8 << ETH_BMR_DSL_BIT)
#define ETH_BMR_SWR		(1 << 0)

/* DMA Status Register (ETH_SR) */

#define ETH_SR_EB_BIT		23
#define ETH_SR_EB_MASK		(0x7 << ETH_SR_EB_BIT)
  #define ETH_SR_EB_TX_ABORT	  (0x1 << ETH_SR_EB_BIT)
  #define ETH_SR_EB_RX_ABORT	  (0x2 << ETH_SR_EB_BIT)
#define ETH_SR_TS_BIT		20
#define ETH_SR_TS_MASK		(0x7 << ETH_SR_TS_BIT)
  #define ETH_SR_TS_STOP	  (0x0 << ETH_SR_TS_BIT)
  #define ETH_SR_TS_FTD		  (0x1 << ETH_SR_TS_BIT)
  #define ETH_SR_TS_WEOT	  (0x2 << ETH_SR_TS_BIT)
  #define ETH_SR_TS_QDAT	  (0x3 << ETH_SR_TS_BIT)
  #define ETH_SR_TS_SUSPEND	  (0x6 << ETH_SR_TS_BIT)
  #define ETH_SR_TS_CTD		  (0x7 << ETH_SR_TS_BIT)
#define ETH_SR_RS_BIT		17
#define ETH_SR_RS_MASK		(0x7 << ETH_SR_RS_BIT)
  #define ETH_SR_RS_STOP	  (0x0 << ETH_SR_RS_BIT)
  #define ETH_SR_RS_FRD		  (0x1 << ETH_SR_RS_BIT)
  #define ETH_SR_RS_CEOR	  (0x2 << ETH_SR_RS_BIT)
  #define ETH_SR_RS_WRP		  (0x3 << ETH_SR_RS_BIT)
  #define ETH_SR_RS_SUSPEND	  (0x4 << ETH_SR_RS_BIT)
  #define ETH_SR_RS_CRD		  (0x5 << ETH_SR_RS_BIT)
  #define ETH_SR_RS_FCF		  (0x6 << ETH_SR_RS_BIT)
  #define ETH_SR_RS_QRF		  (0x7 << ETH_SR_RS_BIT)
#define ETH_SR_NIS		(1 << 16)
#define ETH_SR_AIS		(1 << 15)
#define ETH_SR_ERI		(1 << 14)
#define ETH_SR_FBE		(1 << 13)
#define ETH_SR_ETI		(1 << 10)
#define ETH_SR_RWT		(1 << 9)
#define ETH_SR_RPS		(1 << 8)
#define ETH_SR_RU		(1 << 7)
#define ETH_SR_RI		(1 << 6)
#define ETH_SR_UNF		(1 << 5)
#define ETH_SR_TJT		(1 << 3)
#define ETH_SR_TU		(1 << 2)
#define ETH_SR_TPS		(1 << 1)
#define ETH_SR_TI		(1 << 0)

/* Control (Operation Mode) Register (ETH_CR) */

#define ETH_CR_TTM		(1 << 22)
#define ETH_CR_SF		(1 << 21)
#define ETH_CR_TR_BIT		14
#define ETH_CR_TR_MASK		(0x3 << ETH_CR_TR_BIT)
#define ETH_CR_ST		(1 << 13)
#define ETH_CR_OSF		(1 << 2)
#define ETH_CR_SR		(1 << 1)

/* Interrupt Enable Register (ETH_IER) */

#define ETH_IER_NI		(1 << 16)
#define ETH_IER_AI		(1 << 15)
#define ETH_IER_ERE		(1 << 14)
#define ETH_IER_FBE		(1 << 13)
#define ETH_IER_ET		(1 << 10)
#define ETH_IER_RWE		(1 << 9)
#define ETH_IER_RS		(1 << 8)
#define ETH_IER_RU		(1 << 7)
#define ETH_IER_RI		(1 << 6)
#define ETH_IER_UN		(1 << 5)
#define ETH_IER_TJ		(1 << 3)
#define ETH_IER_TU		(1 << 2)
#define ETH_IER_TS		(1 << 1)
#define ETH_IER_TI		(1 << 0)

/* Missed Frame and Buffer Overflow Counter Register (ETH_MFCR) */

#define ETH_MFCR_OVERFLOW_BIT	17
#define ETH_MFCR_OVERFLOW_MASK	(0x7ff << ETH_MFCR_OVERFLOW_BIT)
#define ETH_MFCR_MFC_BIT	0
#define ETH_MFCR_MFC_MASK	(0xffff << ETH_MFCR_MFC_BIT)

/* MAC Control Register (ETH_MCR) */

#define ETH_MCR_RA		(1 << 31)
#define ETH_MCR_HBD		(1 << 28)
#define ETH_MCR_PS		(1 << 27)
#define ETH_MCR_DRO		(1 << 23)
#define ETH_MCR_OM_BIT		21
#define ETH_MCR_OM_MASK		(0x3 << ETH_MCR_OM_BIT)
  #define ETH_MCR_OM_NORMAL	  (0x0 << ETH_MCR_OM_BIT)
  #define ETH_MCR_OM_INTERNAL	  (0x1 << ETH_MCR_OM_BIT)
  #define ETH_MCR_OM_EXTERNAL	  (0x2 << ETH_MCR_OM_BIT)
#define ETH_MCR_F		(1 << 20)
#define ETH_MCR_PM		(1 << 19)
#define ETH_MCR_PR		(1 << 18)
#define ETH_MCR_IF		(1 << 17)
#define ETH_MCR_PB		(1 << 16)
#define ETH_MCR_HO		(1 << 15)
#define ETH_MCR_HP		(1 << 13)
#define ETH_MCR_LCC		(1 << 12)
#define ETH_MCR_DBF		(1 << 11)
#define ETH_MCR_DTRY		(1 << 10)
#define ETH_MCR_ASTP		(1 << 8)
#define ETH_MCR_BOLMT_BIT	6
#define ETH_MCR_BOLMT_MASK	(0x3 << ETH_MCR_BOLMT_BIT)
  #define ETH_MCR_BOLMT_10	  (0 << ETH_MCR_BOLMT_BIT)
  #define ETH_MCR_BOLMT_8	  (1 << ETH_MCR_BOLMT_BIT)
  #define ETH_MCR_BOLMT_4	  (2 << ETH_MCR_BOLMT_BIT)
  #define ETH_MCR_BOLMT_1	  (3 << ETH_MCR_BOLMT_BIT)
#define ETH_MCR_DC		(1 << 5)
#define ETH_MCR_TE		(1 << 3)
#define ETH_MCR_RE		(1 << 2)

/* MII Address Register (ETH_MIAR) */

#define ETH_MIAR_PHY_ADDR_BIT	11
#define ETH_MIAR_PHY_ADDR_MASK	(0x1f << ETH_MIAR_PHY_ADDR_BIT)
#define ETH_MIAR_MII_REG_BIT	6
#define ETH_MIAR_MII_REG_MASK	(0x1f << ETH_MIAR_MII_REG_BIT)
#define ETH_MIAR_MII_WRITE	(1 << 1)
#define ETH_MIAR_MII_BUSY	(1 << 0)

/* Flow Control Register (ETH_FCR) */

#define	ETH_FCR_PAUSE_TIME_BIT	16
#define	ETH_FCR_PAUSE_TIME_MASK	(0xffff << ETH_FCR_PAUSE_TIME_BIT)
#define	ETH_FCR_PCF		(1 << 2)
#define	ETH_FCR_FCE		(1 << 1)
#define	ETH_FCR_BUSY		(1 << 0)

/* PMT Control and Status Register (ETH_PMTR) */

#define ETH_PMTR_GU		(1 << 9)
#define ETH_PMTR_RF		(1 << 6)
#define ETH_PMTR_MF		(1 << 5)
#define ETH_PMTR_RWK		(1 << 2)
#define ETH_PMTR_MPK		(1 << 1)

/* Receive Descriptor 0 (ETH_RD0) Bits */

#define ETH_RD0_OWN		(1 << 31)
#define ETH_RD0_FF		(1 << 30)
#define ETH_RD0_FL_BIT		16
#define ETH_RD0_FL_MASK		(0x3fff << ETH_RD0_FL_BIT)
#define ETH_RD0_ES		(1 << 15)
#define ETH_RD0_DE		(1 << 14)
#define ETH_RD0_LE		(1 << 12)
#define ETH_RD0_RF		(1 << 11)
#define ETH_RD0_MF		(1 << 10)
#define ETH_RD0_FD		(1 << 9)
#define ETH_RD0_LD		(1 << 8)
#define ETH_RD0_TL		(1 << 7)
#define ETH_RD0_CS		(1 << 6)
#define ETH_RD0_FT		(1 << 5)
#define ETH_RD0_WT		(1 << 4)
#define ETH_RD0_ME		(1 << 3)
#define ETH_RD0_DB		(1 << 2)
#define ETH_RD0_CE		(1 << 1)

/* Receive Descriptor 1 (ETH_RD1) Bits */

#define ETH_RD1_RER		(1 << 25)
#define ETH_RD1_RCH		(1 << 24)
#define ETH_RD1_RBS2_BIT	11
#define ETH_RD1_RBS2_MASK	(0x7ff << ETH_RD1_RBS2_BIT)
#define ETH_RD1_RBS1_BIT	0
#define ETH_RD1_RBS1_MASK	(0x7ff << ETH_RD1_RBS1_BIT)

/* Transmit Descriptor 0 (ETH_TD0) Bits */

#define ETH_TD0_OWN		(1 << 31)
#define ETH_TD0_FA		(1 << 15)
#define ETH_TD0_LOC		(1 << 11)
#define ETH_TD0_NC		(1 << 10)
#define ETH_TD0_LC		(1 << 9)
#define ETH_TD0_EC		(1 << 8)
#define ETH_TD0_HBF		(1 << 7)
#define ETH_TD0_CC_BIT		3
#define ETH_TD0_CC_MASK		(0xf << ETH_TD0_CC_BIT)
#define ETH_TD0_ED		(1 << 2)
#define ETH_TD0_UF		(1 << 1)
#define ETH_TD0_DF		(1 << 0)

/* Transmit Descriptor 1 (ETH_TD1) Bits */

#define ETH_TD1_IC		(1 << 31)
#define ETH_TD1_LS		(1 << 30)
#define ETH_TD1_FS		(1 << 29)
#define ETH_TD1_AC		(1 << 26)
#define ETH_TD1_TER		(1 << 25)
#define ETH_TD1_TCH		(1 << 24)
#define ETH_TD1_DPD		(1 << 23)
#define ETH_TD1_TBS2_BIT	11
#define ETH_TD1_TBS2_MASK	(0x7ff << ETH_TD1_TBS2_BIT)
#define ETH_TD1_TBS1_BIT	0
#define ETH_TD1_TBS1_MASK	(0x7ff << ETH_TD1_TBS1_BIT)


//----------------------------------------------------------------------
//
// Module Operation Definitions
//
//----------------------------------------------------------------------
#ifndef __ASSEMBLY__

/***************************************************************************
 * GPIO
 ***************************************************************************/

//------------------------------------------------------
// GPIO Pins Description
//
// PORT 0:
//
// PIN/BIT N		FUNC0		FUNC1
//	0		D0		-
//	1		D1		-
//	2		D2		-
//	3		D3		-
//	4		D4		-
//	5		D5		-
//	6		D6		-
//	7		D7		-
//	8		D8		-
//	9		D9		-
//	10		D10		-
//	11		D11		-
//	12		D12		-
//	13		D13		-
//	14		D14		-
//	15		D15		-
//	16		D16		-
//	17		D17		-
//	18		D18		-
//	19		D19		-
//	20		D20		-
//	21		D21		-
//	22		D22		-
//	23		D23		-
//	24		D24		-
//	25		D25		-
//	26		D26		-
//	27		D27		-
//	28		D28		-
//	29		D29		-
//	30		D30		-
//	31		D31		-
//
//------------------------------------------------------
// PORT 1:
//
// PIN/BIT N		FUNC0		FUNC1
//	0		A0		-
//	1		A1		-
//	2		A2		-
//	3		A3		-
//	4		A4		-
//	5		A5		-
//	6		A6		-
//	7		A7		-
//	8		A8		-
//	9		A9		-
//	10		A10		-
//	11		A11		-
//	12		A12		-
//	13		A13		-
//	14		A14		-
//	15		A15/CL		-
//	16		A16/AL		-
//	17		A17		-
//	18		A18		-
//	19		DCS#		-
//	20		RAS#		-
//	21		CAS#		-
//	22		CKE		-
//	23		SDWE#/BUFD#	-
//	24		CKO		-
//	25		CS1#		-
//	26		CS2#		-
//	27		CS3#		-
//	28		CS4#		-
//	29		RD#		-
//	30		WR#		-
//	31		WE0#		-
//
// Note: PIN15&16 are CL&AL when connecting to NAND flash.
//------------------------------------------------------
// PORT 2:
//
// PIN/BIT N		FUNC0		FUNC1
//	0		LCD_D0		-
//	1		LCD_D1		-
//	2		LCD_D2		-
//	3		LCD_D3		-
//	4		LCD_D4		-
//	5		LCD_D5		-
//	6		LCD_D6		-
//	7		LCD_D7		-
//	8		LCD_D8		-
//	9		LCD_D9		-
//	10		LCD_D10		-
//	11		LCD_D11		-
//	12		LCD_D12		-
//	13		LCD_D13		-
//	14		LCD_D14		-
//	15		LCD_D15		-
//	16		LCD_SPL		LCD_D16
//	17		LCD_CLS		LCD_D17
//	18		LCD_PCLK	-
//	19		LCD_HSYNC	-
//	20		LCD_VSYNC	-
//	21		LCD_DE		-
//	22		LCD_PS		-
//	23		LCD_DEV		-
//	24		WE1#		-
//	25		WE2#		-
//	26		WE3#		-
//	27		WAIT#		-
//	28		FRE#		-
//	29		FWE#		-
//	30(NOTE:FRB#)	-		-
//	31		-		-
//
// NOTE(1): PIN30 is used for FRB# when connecting to NAND flash.
//------------------------------------------------------
// PORT 3:
//
// PIN/BIT N		FUNC0		FUNC1
//	0		CIM_D0		SYS_CLK(I2S)
//	1		CIM_D1		ARESET#(AC97)
//	2		CIM_D2		-
//	3		CIM_D3		-
//	4		CIM_D4		-
//	5		CIM_D5		-
//	6		CIM_D6		-
//	7		CIM_D7		-
//	8		MSC_CMD		-
//	9		MSC_CLK		-
//	10		MSC_D0		-
//	11		MSC_D1		-
//	12		MSC_D2		-
//	13		MSC_D3		-
//	14		CIM_MCLK	BIT_CLK(AIC)
//	15		CIM_PCLK	SDATA_IN(AIC)
//	16		CIM_VSYNC	SDATA_OUT(AIC)
//	17		CIM_HSYNC	SYNC(AIC)
//	18		SSI_CLK		-
//	19		SSI_CE0#	-
//	20		SSI_DT		-
//	21		SSI_DR		-
//	22		SSI_CE1#&GPC	-
//	23		PWM0		I2C_SDA
//	24		PWM1		I2C_SCK
//	25		PWM2		UART_TxD
//	26		PWM3		UART_RxD
//	27		PWM4		-
//	28		PWM5		-
//	29		-		-
//	30		-		-
//	31		-		-
//
//////////////////////////////////////////////////////////

/* 
 * p is the port number (0,1,2,3)
 * o is the pin offset (0-31) inside the port
 * n is the absolute number of a pin (0-127), regardless of the port
 */

//-------------------------------------------
// Function Pins Mode

#define __gpio_as_func0(n)			\
do {						\
	unsigned int p, o;			\
	p = (n) / 32;				\
	o = (n) % 32;				\
	REG_GPIO_PXFUNS(p) = (1 << o);		\
	REG_GPIO_PXSELC(p) = (1 << o);		\
} while (0)

#define __gpio_as_func1(n)			\
do {						\
	unsigned int p, o;			\
	p = (n) / 32;				\
	o = (n) % 32;				\
	REG_GPIO_PXFUNS(p) = (1 << o);		\
	REG_GPIO_PXSELS(p) = (1 << o);		\
} while (0)

#define __gpio_as_emc()				\
do {						\
	REG_GPIO_PXFUNS(0) = 0xffffffff;	\
	REG_GPIO_PXSELC(0) = 0xffffffff;	\
	REG_GPIO_PXFUNS(1) = 0xffffffff;	\
	REG_GPIO_PXSELC(1) = 0xffffffff;	\
	REG_GPIO_PXFUNS(2) = 0x3f000000;	\
	REG_GPIO_PXSELC(2) = 0x3f000000;	\
	__gpio_as_input(94); /* FRB */		\
} while (0)

#define __gpio_as_lcd_16bit()			\
do {						\
	REG_GPIO_PXFUNS(2) = 0x00ffffff;	\
	REG_GPIO_PXSELC(2) = 0x00ffffff;	\
} while (0)

#define __gpio_as_lcd_18bit()			\
do {						\
	REG_GPIO_PXFUNS(2) = 0x00fcffff;	\
	REG_GPIO_PXSELC(2) = 0x00fcffff;	\
	REG_GPIO_PXFUNS(2) = 0x00030000;	\
	REG_GPIO_PXSELS(2) = 0x00030000;	\
} while (0)

#define __gpio_as_cim()				\
do {						\
	REG_GPIO_PXFUNS(3) = 0x0003c0ff;	\
	REG_GPIO_PXSELC(3) = 0x0003c0ff;	\
} while (0)

#define __gpio_as_aic()				\
do {						\
	REG_GPIO_PXFUNS(2) = 0x0003c003;	\
	REG_GPIO_PXSELS(2) = 0x0003c003;	\
} while (0)

#define __gpio_as_msc()				\
do {						\
	REG_GPIO_PXFUNS(3) = 0x00003f00;	\
	REG_GPIO_PXSELC(3) = 0x00003f00;	\
} while (0)

#define __gpio_as_ssi()				\
do {						\
	REG_GPIO_PXFUNS(3) = 0x003c0000;	\
	REG_GPIO_PXSELC(3) = 0x003c0000;	\
} while (0)

#define __gpio_as_i2c()				\
do {						\
	REG_GPIO_PXFUNS(3) = 0x01800000;	\
	REG_GPIO_PXSELS(3) = 0x01800000;	\
} while (0)

#define __gpio_as_uart0()			\
do {						\
	REG_GPIO_PXFUNS(3) = 0x06000000;	\
	REG_GPIO_PXSELS(3) = 0x06000000;	\
} while (0)

#define __gpio_as_pwm0()			\
do {						\
	REG_GPIO_PXFUNS(3) = 0x00800000;	\
	REG_GPIO_PXSELC(3) = 0x00800000;	\
} while (0)

#define __gpio_as_pwm1()			\
do {						\
	REG_GPIO_PXFUNS(3) = 0x01000000;	\
	REG_GPIO_PXSELC(3) = 0x01000000;	\
} while (0)

#define __gpio_as_pwm2()			\
do {						\
	REG_GPIO_PXFUNS(3) = 0x02000000;	\
	REG_GPIO_PXSELC(3) = 0x02000000;	\
} while (0)

#define __gpio_as_pwm3()			\
do {						\
	REG_GPIO_PXFUNS(3) = 0x04000000;	\
	REG_GPIO_PXSELC(3) = 0x04000000;	\
} while (0)

#define __gpio_as_pwm4()			\
do {						\
	REG_GPIO_PXFUNS(3) = 0x08000000;	\
	REG_GPIO_PXSELC(3) = 0x08000000;	\
} while (0)

#define __gpio_as_pwm5()			\
do {						\
	REG_GPIO_PXFUNS(3) = 0x10000000;	\
	REG_GPIO_PXSELC(3) = 0x10000000;	\
} while (0)


//-------------------------------------------
// GPIO or Interrupt Mode

#define __gpio_get_port(p)	(REG_GPIO_PXPIN(p))

#define __gpio_port_as_output(p, o)		\
do {						\
    REG_GPIO_PXFUNC(p) = (1 << (o));		\
    REG_GPIO_PXSELC(p) = (1 << (o));		\
    REG_GPIO_PXDIRS(p) = (1 << (o));		\
} while (0)

#define __gpio_port_as_input(p, o)		\
do {						\
    REG_GPIO_PXFUNC(p) = (1 << (o));		\
    REG_GPIO_PXSELC(p) = (1 << (o));		\
    REG_GPIO_PXDIRC(p) = (1 << (o));		\
} while (0)

#define __gpio_as_output(n)			\
do {						\
	unsigned int p, o;			\
	p = (n) / 32;				\
	o = (n) % 32;				\
	__gpio_port_as_output(p, o);		\
} while (0)

#define __gpio_as_input(n)			\
do {						\
	unsigned int p, o;			\
	p = (n) / 32;				\
	o = (n) % 32;				\
	__gpio_port_as_input(p, o);		\
} while (0)

#define __gpio_set_pin(n)			\
do {						\
	unsigned int p, o;			\
	p = (n) / 32;				\
	o = (n) % 32;				\
	REG_GPIO_PXDATS(p) = (1 << o);		\
} while (0)

#define __gpio_clear_pin(n)			\
do {						\
	unsigned int p, o;			\
	p = (n) / 32;				\
	o = (n) % 32;				\
	REG_GPIO_PXDATC(p) = (1 << o);		\
} while (0)

static __inline__ unsigned int __gpio_get_pin(unsigned int n)
{
	unsigned int p, o;
	p = (n) / 32;
	o = (n) % 32;
	if (__gpio_get_port(p) & (1 << o))
		return 1;
	else
		return 0;
}

#define __gpio_as_irq_high_level(n)		\
do {						\
	unsigned int p, o;			\
	p = (n) / 32;				\
	o = (n) % 32;				\
	REG_GPIO_PXIMS(p) = (1 << o);		\
	REG_GPIO_PXFUNC(p) = (1 << o);		\
	REG_GPIO_PXSELS(p) = (1 << o);		\
	REG_GPIO_PXTRGC(p) = (1 << o);		\
	REG_GPIO_PXDIRS(p) = (1 << o);		\
	REG_GPIO_PXDATC(p) = (1 << o);		\
	REG_GPIO_PXIMC(p) = (1 << o);		\
} while (0)

#define __gpio_as_irq_low_level(n)		\
do {						\
	unsigned int p, o;			\
	p = (n) / 32;				\
	o = (n) % 32;				\
	REG_GPIO_PXIMS(p) = (1 << o);		\
	REG_GPIO_PXFUNC(p) = (1 << o);		\
	REG_GPIO_PXSELS(p) = (1 << o);		\
	REG_GPIO_PXTRGC(p) = (1 << o);		\
	REG_GPIO_PXDIRC(p) = (1 << o);		\
	REG_GPIO_PXDATC(p) = (1 << o);		\
	REG_GPIO_PXIMC(p) = (1 << o);		\
} while (0)

#define __gpio_as_irq_rise_edge(n)		\
do {						\
	unsigned int p, o;			\
	p = (n) / 32;				\
	o = (n) % 32;				\
	REG_GPIO_PXIMS(p) = (1 << o);		\
	REG_GPIO_PXFUNC(p) = (1 << o);		\
	REG_GPIO_PXSELS(p) = (1 << o);		\
	REG_GPIO_PXTRGS(p) = (1 << o);		\
	REG_GPIO_PXDIRS(p) = (1 << o);		\
	REG_GPIO_PXDATC(p) = (1 << o);		\
	REG_GPIO_PXIMC(p) = (1 << o);		\
} while (0)

#define __gpio_as_irq_fall_edge(n)		\
do {						\
	unsigned int p, o;			\
	p = (n) / 32;				\
	o = (n) % 32;				\
	REG_GPIO_PXIMS(p) = (1 << o);		\
	REG_GPIO_PXFUNC(p) = (1 << o);		\
	REG_GPIO_PXSELS(p) = (1 << o);		\
	REG_GPIO_PXTRGS(p) = (1 << o);		\
	REG_GPIO_PXDIRC(p) = (1 << o);		\
	REG_GPIO_PXDATC(p) = (1 << o);		\
	REG_GPIO_PXIMC(p) = (1 << o);		\
} while (0)

#define __gpio_mask_irq(n)			\
do {						\
	unsigned int p, o;			\
	p = (n) / 32;				\
	o = (n) % 32;				\
	REG_GPIO_PXIMS(p) = (1 << o);		\
} while (0)

#define __gpio_unmask_irq(n)			\
do {						\
	unsigned int p, o;			\
	p = (n) / 32;				\
	o = (n) % 32;				\
	REG_GPIO_PXIMC(p) = (1 << o);		\
} while (0)

#define __gpio_ack_irq(n)			\
do {						\
	unsigned int p, o;			\
	p = (n) / 32;				\
	o = (n) % 32;				\
	REG_GPIO_PXDATC(p) = (1 << o);		\
} while (0)

static __inline__ unsigned int __gpio_get_irq(void)
{
	unsigned int p, i, tmp;

	for (p = 3; p >= 0; p--) {
		tmp = REG_GPIO_PXFLG(p);
		for (i = 0; i < 32; i++)
			if (tmp & (1 << i))
				return (32 * p + i);
	}
	return 0;
}

#define __gpio_group_irq(n)			\
({						\
	register int tmp, i;			\
	tmp = REG_GPIO_PXFLG((n));		\
	for (i=31;i>=0;i--)			\
		if (tmp & (1 << i))		\
			break;			\
	i;					\
})

#define __gpio_enable_pull(n)			\
do {						\
	unsigned int p, o;			\
	p = (n) / 32;				\
	o = (n) % 32;				\
	REG_GPIO_PXPEC(p) = (1 << o);		\
} while (0)

#define __gpio_disable_pull(n)			\
do {						\
	unsigned int p, o;			\
	p = (n) / 32;				\
	o = (n) % 32;				\
	REG_GPIO_PXPES(p) = (1 << o);		\
} while (0)


/***************************************************************************
 * CPM
 ***************************************************************************/
#define __cpm_get_pllm() \
	((REG_CPM_CPPCR & CPM_CPPCR_PLLM_MASK) >> CPM_CPPCR_PLLM_BIT)
#define __cpm_get_plln() \
	((REG_CPM_CPPCR & CPM_CPPCR_PLLN_MASK) >> CPM_CPPCR_PLLN_BIT)
#define __cpm_get_pllod() \
	((REG_CPM_CPPCR & CPM_CPPCR_PLLOD_MASK) >> CPM_CPPCR_PLLOD_BIT)

#define __cpm_get_cdiv() \
	((REG_CPM_CPCCR & CPM_CPCCR_CDIV_MASK) >> CPM_CPCCR_CDIV_BIT)
#define __cpm_get_hdiv() \
	((REG_CPM_CPCCR & CPM_CPCCR_HDIV_MASK) >> CPM_CPCCR_HDIV_BIT)
#define __cpm_get_pdiv() \
	((REG_CPM_CPCCR & CPM_CPCCR_PDIV_MASK) >> CPM_CPCCR_PDIV_BIT)
#define __cpm_get_mdiv() \
	((REG_CPM_CPCCR & CPM_CPCCR_MDIV_MASK) >> CPM_CPCCR_MDIV_BIT)
#define __cpm_get_ldiv() \
	((REG_CPM_CPCCR & CPM_CPCCR_LDIV_MASK) >> CPM_CPCCR_LDIV_BIT)
#define __cpm_get_udiv() \
	((REG_CPM_CPCCR & CPM_CPCCR_UDIV_MASK) >> CPM_CPCCR_UDIV_BIT)
#define __cpm_get_i2sdiv() \
	((REG_CPM_I2SCDR & CPM_I2SCDR_I2SDIV_MASK) >> CPM_I2SCDR_I2SDIV_BIT)
#define __cpm_get_pixdiv() \
	((REG_CPM_LPCDR & CPM_LPCDR_PIXDIV_MASK) >> CPM_LPCDR_PIXDIV_BIT)
#define __cpm_get_mscdiv() \
	((REG_CPM_MSCCDR & CPM_MSCCDR_MSCDIV_MASK) >> CPM_MSCCDR_MSCDIV_BIT)

#define __cpm_set_cdiv(v) \
	(REG_CPM_CPCCR = (REG_CPM_CPCCR & ~CPM_CPCCR_CDIV_MASK) | ((v) << (CPM_CPCCR_CDIV_BIT)))
#define __cpm_set_hdiv(v) \
	(REG_CPM_CPCCR = (REG_CPM_CPCCR & ~CPM_CPCCR_HDIV_MASK) | ((v) << (CPM_CPCCR_HDIV_BIT)))
#define __cpm_set_pdiv(v) \
	(REG_CPM_CPCCR = (REG_CPM_CPCCR & ~CPM_CPCCR_PDIV_MASK) | ((v) << (CPM_CPCCR_PDIV_BIT)))
#define __cpm_set_mdiv(v) \
	(REG_CPM_CPCCR = (REG_CPM_CPCCR & ~CPM_CPCCR_MDIV_MASK) | ((v) << (CPM_CPCCR_MDIV_BIT)))
#define __cpm_set_ldiv(v) \
	(REG_CPM_CPCCR = (REG_CPM_CPCCR & ~CPM_CPCCR_LDIV_MASK) | ((v) << (CPM_CPCCR_LDIV_BIT)))
#define __cpm_set_udiv(v) \
	(REG_CPM_CPCCR = (REG_CPM_CPCCR & ~CPM_CPCCR_UDIV_MASK) | ((v) << (CPM_CPCCR_UDIV_BIT)))
#define __cpm_set_i2sdiv(v) \
	(REG_CPM_I2SCDR = (REG_CPM_I2SCDR & ~CPM_I2SCDR_I2SDIV_MASK) | ((v) << (CPM_I2SCDR_I2SDIV_BIT)))
#define __cpm_set_pixdiv(v) \
	(REG_CPM_LPCDR = (REG_CPM_LPCDR & ~CPM_LPCDR_PIXDIV_MASK) | ((v) << (CPM_LPCDR_PIXDIV_BIT)))
#define __cpm_set_mscdiv(v) \
	(REG_CPM_MSCCDR = (REG_CPM_MSCCDR & ~CPM_MSCCDR_MSCDIV_MASK) | ((v) << (CPM_MSCCDR_MSCDIV_BIT)))

#define __cpm_select_i2sclk_exclk()	(REG_CPM_CPCCR &= ~CPM_CPCCR_I2CS)
#define __cpm_select_i2sclk_pll()	(REG_CPM_CPCCR |= CPM_CPCCR_I2CS)
#define __cpm_enable_cko()		(REG_CPM_CPCCR |= CPM_CPCCR_CLKOEN)
#define __cpm_select_usbclk_exclk()	(REG_CPM_CPCCR &= ~CPM_CPCCR_UCS)
#define __cpm_select_usbclk_pll()	(REG_CPM_CPCCR |= CPM_CPCCR_UCS)
#define __cpm_enable_pll_change()	(REG_CPM_CPCCR |= CPM_CPCCR_CE)
#define __cpm_pllout_direct()		(REG_CPM_CPCCR |= CPM_CPCCR_PCS)
#define __cpm_pllout_div2()		(REG_CPM_CPCCR &= ~CPM_CPCCR_PCS)

#define __cpm_pll_is_on()		(REG_CPM_CPPCR & CPM_CPPCR_PLLS)
#define __cpm_pll_bypass()		(REG_CPM_CPPCR |= CPM_CPPCR_PLLBP)
#define __cpm_pll_enable()		(REG_CPM_CPPCR |= CPM_CPPCR_PLLEN)

#define __cpm_get_cclk_doze_duty() \
	((REG_CPM_LCR & CPM_LCR_DOZE_DUTY_MASK) >> CPM_LCR_DOZE_DUTY_BIT)
#define __cpm_set_cclk_doze_duty(v) \
	(REG_CPM_LCR = (REG_CPM_LCR & ~CPM_LCR_DOZE_DUTY_MASK) | ((v) << (CPM_LCR_DOZE_DUTY_BIT)))

#define __cpm_doze_mode()		(REG_CPM_LCR |= CPM_LCR_DOZE_ON)
#define __cpm_idle_mode() \
	(REG_CPM_LCR = (REG_CPM_LCR & ~CPM_LCR_LPM_MASK) | CPM_LCR_LPM_IDLE)
#define __cpm_sleep_mode() \
	(REG_CPM_LCR = (REG_CPM_LCR & ~CPM_LCR_LPM_MASK) | CPM_LCR_LPM_SLEEP)
#define __cpm_hibernate_mode()		(REG_CPM_HCR |= CPM_HCR_PD)


#define __cpm_stop_all() 	(REG_CPM_CLKGR = 0x7fff)
#define __cpm_stop_mclk()	(REG_CPM_CLKGR |= CPM_CLKGR_MCLK)
#define __cpm_stop_dmac()	(REG_CPM_CLKGR |= CPM_CLKGR_DMAC)
#define __cpm_stop_usb()	(REG_CPM_CLKGR |= CPM_CLKGR_USB)
#define __cpm_stop_lcd()	(REG_CPM_CLKGR |= CPM_CLKGR_LCD)
#define __cpm_stop_cim()	(REG_CPM_CLKGR |= CPM_CLKGR_CIM)
#define __cpm_stop_sadc()	(REG_CPM_CLKGR |= CPM_CLKGR_SADC)
#define __cpm_stop_msc()	(REG_CPM_CLKGR |= CPM_CLKGR_MSC)
#define __cpm_stop_aic1()	(REG_CPM_CLKGR |= CPM_CLKGR_AIC1)
#define __cpm_stop_aic2()	(REG_CPM_CLKGR |= CPM_CLKGR_AIC2)
#define __cpm_stop_ssi()	(REG_CPM_CLKGR |= CPM_CLKGR_SSI)
#define __cpm_stop_i2c()	(REG_CPM_CLKGR |= CPM_CLKGR_I2C)
#define __cpm_stop_rtc()	(REG_CPM_CLKGR |= CPM_CLKGR_RTC)
#define __cpm_stop_tcu()	(REG_CPM_CLKGR |= CPM_CLKGR_TCU)
#define __cpm_stop_uart0()	(REG_CPM_CLKGR |= CPM_CLKGR_UART0)

#define __cpm_start_all() 	(REG_CPM_CLKGR = 0x0)
#define __cpm_start_mclk()	(REG_CPM_CLKGR &= ~CPM_CLKGR_MCLK)
#define __cpm_start_dmac()	(REG_CPM_CLKGR &= ~CPM_CLKGR_DMAC)
#define __cpm_start_usb()	(REG_CPM_CLKGR &= ~CPM_CLKGR_USB)
#define __cpm_start_lcd()	(REG_CPM_CLKGR &= ~CPM_CLKGR_LCD)
#define __cpm_start_cim()	(REG_CPM_CLKGR &= ~CPM_CLKGR_CIM)
#define __cpm_start_sadc()	(REG_CPM_CLKGR &= ~CPM_CLKGR_SADC)
#define __cpm_start_msc()	(REG_CPM_CLKGR &= ~CPM_CLKGR_MSC)
#define __cpm_start_aic1()	(REG_CPM_CLKGR &= ~CPM_CLKGR_AIC1)
#define __cpm_start_aic2()	(REG_CPM_CLKGR &= ~CPM_CLKGR_AIC2)
#define __cpm_start_ssi()	(REG_CPM_CLKGR &= ~CPM_CLKGR_SSI)
#define __cpm_start_i2c()	(REG_CPM_CLKGR &= ~CPM_CLKGR_I2C)
#define __cpm_start_rtc()	(REG_CPM_CLKGR &= ~CPM_CLKGR_RTC)
#define __cpm_start_tcu()	(REG_CPM_CLKGR &= ~CPM_CLKGR_TCU)
#define __cpm_start_uart0()	(REG_CPM_CLKGR &= ~CPM_CLKGR_UART0)

#define __cpm_get_o1st() \
	((REG_CPM_SCR & CPM_SCR_O1ST_MASK) >> CPM_SCR_O1ST_BIT)
#define __cpm_set_o1st(v) \
	(REG_CPM_SCR = (REG_CPM_SCR & ~CPM_SCR_O1ST_MASK) | ((v) << (CPM_SCR_O1ST_BIT)))
#define __cpm_suspend_usbphy()		(REG_CPM_SCR |= CPM_SCR_USBPHY_SUSPEND)
#define __cpm_enable_osc_in_sleep()	(REG_CPM_SCR |= CPM_SCR_OSC_ENABLE)


/***************************************************************************
 * TCU
 ***************************************************************************/
// where 'n' is the TCU channel
#define __tcu_select_extalclk(n) \
	(REG_TCU_TCSR((n)) = (REG_TCU_TCSR((n)) & ~(TCU_TCSR_EXT_EN | TCU_TCSR_RTC_EN | TCU_TCSR_PCK_EN)) | TCU_TCSR_EXT_EN)
#define __tcu_select_rtcclk(n) \
	(REG_TCU_TCSR((n)) = (REG_TCU_TCSR((n)) & ~(TCU_TCSR_EXT_EN | TCU_TCSR_RTC_EN | TCU_TCSR_PCK_EN)) | TCU_TCSR_RTC_EN)
#define __tcu_select_pclk(n) \
	(REG_TCU_TCSR((n)) = (REG_TCU_TCSR((n)) & ~(TCU_TCSR_EXT_EN | TCU_TCSR_RTC_EN | TCU_TCSR_PCK_EN)) | TCU_TCSR_PCK_EN)

#define __tcu_select_clk_div1(n) \
	(REG_TCU_TCSR((n)) = (REG_TCU_TCSR((n)) & ~TCU_TCSR_PRESCALE_MASK) | TCU_TCSR_PRESCALE1)
#define __tcu_select_clk_div4(n) \
	(REG_TCU_TCSR((n)) = (REG_TCU_TCSR((n)) & ~TCU_TCSR_PRESCALE_MASK) | TCU_TCSR_PRESCALE4)
#define __tcu_select_clk_div16(n) \
	(REG_TCU_TCSR((n)) = (REG_TCU_TCSR((n)) & ~TCU_TCSR_PRESCALE_MASK) | TCU_TCSR_PRESCALE16)
#define __tcu_select_clk_div64(n) \
	(REG_TCU_TCSR((n)) = (REG_TCU_TCSR((n)) & ~TCU_TCSR_PRESCALE_MASK) | TCU_TCSR_PRESCALE64)
#define __tcu_select_clk_div256(n) \
	(REG_TCU_TCSR((n)) = (REG_TCU_TCSR((n)) & ~TCU_TCSR_PRESCALE_MASK) | TCU_TCSR_PRESCALE256)
#define __tcu_select_clk_div1024(n) \
	(REG_TCU_TCSR((n)) = (REG_TCU_TCSR((n)) & ~TCU_TCSR_PRESCALE_MASK) | TCU_TCSR_PRESCALE1024)

#define __tcu_enable_pwm_output(n)	( REG_TCU_TCSR((n)) |= TCU_TCSR_PWM_EN )
#define __tcu_disable_pwm_output(n)	( REG_TCU_TCSR((n)) &= ~TCU_TCSR_PWM_EN )

#define __tcu_init_pwm_output_high(n)	( REG_TCU_TCSR((n)) |= TCU_TCSR_PWM_INITL_HIGH )
#define __tcu_init_pwm_output_low(n)	( REG_TCU_TCSR((n)) &= ~TCU_TCSR_PWM_INITL_HIGH )

#define __tcu_set_pwm_output_shutdown_graceful(n)	( REG_TCU_TCSR((n)) &= ~TCU_TCSR_PWM_SD )
#define __tcu_set_pwm_output_shutdown_abrupt(n)		( REG_TCU_TCSR((n)) |= TCU_TCSR_PWM_SD )

#define __tcu_start_counter(n)		( REG_TCU_TESR |= (1 << (n)) )
#define __tcu_stop_counter(n)		( REG_TCU_TECR |= (1 << (n)) )

#define __tcu_half_match_flag(n)	( REG_TCU_TFR & (1 << ((n) + 16)) )
#define __tcu_full_match_flag(n)	( REG_TCU_TFR & (1 << (n)) )
#define __tcu_set_half_match_flag(n)	( REG_TCU_TFSR = (1 << ((n) + 16)) )
#define __tcu_set_full_match_flag(n)	( REG_TCU_TFSR = (1 << (n)) )
#define __tcu_clear_half_match_flag(n)	( REG_TCU_TFCR = (1 << ((n) + 16)) )
#define __tcu_clear_full_match_flag(n)	( REG_TCU_TFCR = (1 << (n)) )
#define __tcu_mask_half_match_irq(n)	( REG_TCU_TMSR = (1 << ((n) + 16)) )
#define __tcu_mask_full_match_irq(n)	( REG_TCU_TMSR = (1 << (n)) )
#define __tcu_unmask_half_match_irq(n)	( REG_TCU_TMCR = (1 << ((n) + 16)) )
#define __tcu_unmask_full_match_irq(n)	( REG_TCU_TMCR = (1 << (n)) )

#define __tcu_wdt_clock_stopped()	( REG_TCU_TSR & TCU_TSSR_WDTSC )
#define __tcu_timer_clock_stopped(n)	( REG_TCU_TSR & (1 << (n)) )

#define __tcu_start_wdt_clock()		( REG_TCU_TSCR = TCU_TSSR_WDTSC )
#define __tcu_start_timer_clock(n)	( REG_TCU_TSCR = (1 << (n)) )

#define __tcu_stop_wdt_clock()		( REG_TCU_TSSR = TCU_TSSR_WDTSC )
#define __tcu_stop_timer_clock(n)	( REG_TCU_TSSR = (1 << (n)) )

#define __tcu_get_count(n)		( REG_TCU_TCNT((n)) )
#define __tcu_set_count(n,v)		( REG_TCU_TCNT((n)) = (v) )
#define __tcu_set_full_data(n,v)	( REG_TCU_TDFR((n)) = (v) )
#define __tcu_set_half_data(n,v)	( REG_TCU_TDHR((n)) = (v) )


/***************************************************************************
 * WDT
 ***************************************************************************/
#define __wdt_start()			( REG_WDT_TCER |= WDT_TCER_TCEN )
#define __wdt_stop()			( REG_WDT_TCER &= ~WDT_TCER_TCEN )
#define __wdt_set_counter(v)		( REG_WDT_TCNT = (v) )
#define __wdt_set_data(v)		( REG_WDT_TDR = (v) )

#define __wdt_select_extalclk() \
	(REG_WDT_TCSR = (REG_WDT_TCSR & ~(WDT_TCSR_EXT_EN | WDT_TCSR_RTC_EN | WDT_TCSR_PCK_EN)) | WDT_TCSR_EXT_EN)
#define __wdt_select_rtcclk() \
	(REG_WDT_TCSR = (REG_WDT_TCSR & ~(WDT_TCSR_EXT_EN | WDT_TCSR_RTC_EN | WDT_TCSR_PCK_EN)) | WDT_TCSR_RTC_EN)
#define __wdt_select_pclk() \
	(REG_WDT_TCSR = (REG_WDT_TCSR & ~(WDT_TCSR_EXT_EN | WDT_TCSR_RTC_EN | WDT_TCSR_PCK_EN)) | WDT_TCSR_PCK_EN)

#define __wdt_select_clk_div1() \
	(REG_WDT_TCSR = (REG_WDT_TCSR & ~WDT_TCSR_PRESCALE_MASK) | WDT_TCSR_PRESCALE1)
#define __wdt_select_clk_div4() \
	(REG_WDT_TCSR = (REG_WDT_TCSR & ~WDT_TCSR_PRESCALE_MASK) | WDT_TCSR_PRESCALE4)
#define __wdt_select_clk_div16() \
	(REG_WDT_TCSR = (REG_WDT_TCSR & ~WDT_TCSR_PRESCALE_MASK) | WDT_TCSR_PRESCALE16)
#define __wdt_select_clk_div64() \
	(REG_WDT_TCSR = (REG_WDT_TCSR & ~WDT_TCSR_PRESCALE_MASK) | WDT_TCSR_PRESCALE64)
#define __wdt_select_clk_div256() \
	(REG_WDT_TCSR = (REG_WDT_TCSR & ~WDT_TCSR_PRESCALE_MASK) | WDT_TCSR_PRESCALE256)
#define __wdt_select_clk_div1024() \
	(REG_WDT_TCSR = (REG_WDT_TCSR & ~WDT_TCSR_PRESCALE_MASK) | WDT_TCSR_PRESCALE1024)


/***************************************************************************
 * UART
 ***************************************************************************/

#define __uart_enable()			( REG8(UART0_FCR) |= UARTFCR_UUE | UARTFCR_FE )
#define __uart_disable()		( REG8(UART0_FCR) = ~UARTFCR_UUE )

#define __uart_enable_transmit_irq()	( REG8(UART0_IER) |= UARTIER_TIE )
#define __uart_disable_transmit_irq()	( REG8(UART0_IER) &= ~UARTIER_TIE )

#define __uart_enable_receive_irq() \
  ( REG8(UART0_IER) |= UARTIER_RIE | UARTIER_RLIE | UARTIER_RTIE )
#define __uart_disable_receive_irq() \
  ( REG8(UART0_IER) &= ~(UARTIER_RIE | UARTIER_RLIE | UARTIER_RTIE) )

#define __uart_enable_loopback()  	( REG8(UART0_MCR) |= UARTMCR_LOOP )
#define __uart_disable_loopback() 	( REG8(UART0_MCR) &= ~UARTMCR_LOOP )

#define __uart_set_8n1()		( REG8(UART0_LCR) = UARTLCR_WLEN_8 )

#define __uart_set_baud(devclk, baud)				\
  do {								\
	REG8(UART0_LCR) |= UARTLCR_DLAB;			\
	REG8(UART0_DLLR) = (devclk / 16 / baud) & 0xff;		\
	REG8(UART0_DLHR) = ((devclk / 16 / baud) >> 8) & 0xff;	\
	REG8(UART0_LCR) &= ~UARTLCR_DLAB;			\
  } while (0)

#define __uart_parity_error()		( (REG8(UART0_LSR) & UARTLSR_PER) != 0 )
#define __uart_clear_errors() \
  ( REG8(UART0_LSR) &= ~(UARTLSR_ORER | UARTLSR_BRK | UARTLSR_FER | UARTLSR_PER | UARTLSR_RFER) )

#define __uart_transmit_fifo_empty()	( (REG8(UART0_LSR) & UARTLSR_TDRQ) != 0 )
#define __uart_transmit_end()		( (REG8(UART0_LSR) & UARTLSR_TEMT) != 0 )
#define __uart_transmit_char(ch)	( REG8(UART0_TDR) = (ch) )
#define __uart_receive_fifo_full()	( (REG8(UART0_LSR) & UARTLSR_DR) != 0 )
#define __uart_receive_ready()		( (REG8(UART0_LSR) & UARTLSR_DR) != 0 )
#define __uart_receive_char()		REG8(UART0_RDR)
#define __uart_disable_irda()		( REG8(UART0_SIRCR) &= ~(SIRCR_TSIRE | SIRCR_RSIRE) )
#define __uart_enable_irda() \
  /* Tx high pulse as 0, Rx low pulse as 0 */ \
  ( REG8(UART0_SIRCR) = SIRCR_TSIRE | SIRCR_RSIRE | SIRCR_RXPL | SIRCR_TPWS )


/***************************************************************************
 * DMAC
 ***************************************************************************/

/* n is the DMA channel (0 - 5) */

#define __dmac_enable_module() \
  ( REG_DMAC_DMACR |= DMAC_DMACR_DMAE | DMAC_DMACR_PR_RR )
#define __dmac_disable_module() \
  ( REG_DMAC_DMACR &= ~DMAC_DMACR_DMAE )

/* p=0,1,2,3 */
#define __dmac_set_priority(p) 				\
do {							\
	REG_DMAC_DMACR &= ~DMAC_DMACR_PR_MASK;		\
	REG_DMAC_DMACR |= ((p) << DMAC_DMACR_PR_BIT);	\
} while (0)

#define __dmac_test_halt_error() ( REG_DMAC_DMACR & DMAC_DMACR_HLT )
#define __dmac_test_addr_error() ( REG_DMAC_DMACR & DMAC_DMACR_AR )

#define __dmac_enable_descriptor(n) \
  ( REG_DMAC_DCCSR((n)) &= ~DMAC_DCCSR_NDES )
#define __dmac_disable_descriptor(n) \
  ( REG_DMAC_DCCSR((n)) |= DMAC_DCCSR_NDES )

#define __dmac_enable_channel(n) \
  ( REG_DMAC_DCCSR((n)) |= DMAC_DCCSR_EN )
#define __dmac_disable_channel(n) \
  ( REG_DMAC_DCCSR((n)) &= ~DMAC_DCCSR_EN )
#define __dmac_channel_enabled(n) \
  ( REG_DMAC_DCCSR((n)) & DMAC_DCCSR_EN )

#define __dmac_channel_enable_irq(n) \
  ( REG_DMAC_DCMD((n)) |= DMAC_DCMD_TIE )
#define __dmac_channel_disable_irq(n) \
  ( REG_DMAC_DCMD((n)) &= ~DMAC_DCMD_TIE )

#define __dmac_channel_transmit_halt_detected(n) \
  (  REG_DMAC_DCCSR((n)) & DMAC_DCCSR_HLT )
#define __dmac_channel_transmit_end_detected(n) \
  (  REG_DMAC_DCCSR((n)) & DMAC_DCCSR_TT )
#define __dmac_channel_address_error_detected(n) \
  (  REG_DMAC_DCCSR((n)) & DMAC_DCCSR_AR )
#define __dmac_channel_count_terminated_detected(n) \
  (  REG_DMAC_DCCSR((n)) & DMAC_DCCSR_CT )
#define __dmac_channel_descriptor_invalid_detected(n) \
  (  REG_DMAC_DCCSR((n)) & DMAC_DCCSR_INV )

#define __dmac_channel_clear_transmit_halt(n) \
  (  REG_DMAC_DCCSR(n) &= ~DMAC_DCCSR_HLT )
#define __dmac_channel_clear_transmit_end(n) \
  (  REG_DMAC_DCCSR(n) &= ~DMAC_DCCSR_TT )
#define __dmac_channel_clear_address_error(n) \
  (  REG_DMAC_DCCSR(n) &= ~DMAC_DCCSR_AR )
#define __dmac_channel_clear_count_terminated(n) \
  (  REG_DMAC_DCCSR((n)) &= ~DMAC_DCCSR_CT )
#define __dmac_channel_clear_descriptor_invalid(n) \
  (  REG_DMAC_DCCSR((n)) &= ~DMAC_DCCSR_INV )

#define __dmac_channel_set_single_mode(n) \
  (  REG_DMAC_DCMD((n)) &= ~DMAC_DCMD_TM )
#define __dmac_channel_set_block_mode(n) \
  (  REG_DMAC_DCMD((n)) |= DMAC_DCMD_TM )

#define __dmac_channel_set_transfer_unit_32bit(n)	\
do {							\
	REG_DMAC_DCMD((n)) &= ~DMAC_DCMD_DS_MASK;	\
	REG_DMAC_DCMD((n)) |= DMAC_DCMD_DS_32BIT;	\
} while (0)

#define __dmac_channel_set_transfer_unit_16bit(n)	\
do {							\
	REG_DMAC_DCMD((n)) &= ~DMAC_DCMD_DS_MASK;	\
	REG_DMAC_DCMD((n)) |= DMAC_DCMD_DS_16BIT;	\
} while (0)

#define __dmac_channel_set_transfer_unit_8bit(n)	\
do {							\
	REG_DMAC_DCMD((n)) &= ~DMAC_DCMD_DS_MASK;	\
	REG_DMAC_DCMD((n)) |= DMAC_DCMD_DS_8BIT;	\
} while (0)

#define __dmac_channel_set_transfer_unit_16byte(n)	\
do {							\
	REG_DMAC_DCMD((n)) &= ~DMAC_DCMD_DS_MASK;	\
	REG_DMAC_DCMD((n)) |= DMAC_DCMD_DS_16BYTE;	\
} while (0)

#define __dmac_channel_set_transfer_unit_32byte(n)	\
do {							\
	REG_DMAC_DCMD((n)) &= ~DMAC_DCMD_DS_MASK;	\
	REG_DMAC_DCMD((n)) |= DMAC_DCMD_DS_32BYTE;	\
} while (0)

/* w=8,16,32 */
#define __dmac_channel_set_dest_port_width(n,w)		\
do {							\
	REG_DMAC_DCMD((n)) &= ~DMAC_DCMD_DWDH_MASK;	\
	REG_DMAC_DCMD((n)) |= DMAC_DCMD_DWDH_##w;	\
} while (0)

/* w=8,16,32 */
#define __dmac_channel_set_src_port_width(n,w)		\
do {							\
	REG_DMAC_DCMD((n)) &= ~DMAC_DCMD_SWDH_MASK;	\
	REG_DMAC_DCMD((n)) |= DMAC_DCMD_SWDH_##w;	\
} while (0)

/* v=0-15 */
#define __dmac_channel_set_rdil(n,v)				\
do {								\
	REG_DMAC_DCMD((n)) &= ~DMAC_DCMD_RDIL_MASK;		\
	REG_DMAC_DCMD((n) |= ((v) << DMAC_DCMD_RDIL_BIT);	\
} while (0)

#define __dmac_channel_dest_addr_fixed(n) \
  (  REG_DMAC_DCMD((n)) &= ~DMAC_DCMD_DAI )
#define __dmac_channel_dest_addr_increment(n) \
  (  REG_DMAC_DCMD((n)) |= DMAC_DCMD_DAI )

#define __dmac_channel_src_addr_fixed(n) \
  (  REG_DMAC_DCMD((n)) &= ~DMAC_DCMD_SAI )
#define __dmac_channel_src_addr_increment(n) \
  (  REG_DMAC_DCMD((n)) |= DMAC_DCMD_SAI )

#define __dmac_channel_set_doorbell(n) \
  (  REG_DMAC_DMADBSR = (1 << (n)) )

#define __dmac_channel_irq_detected(n)  ( REG_DMAC_DMAIPR & (1 << (n)) )
#define __dmac_channel_ack_irq(n)       ( REG_DMAC_DMAIPR &= ~(1 << (n)) )

static __inline__ int __dmac_get_irq(void)
{
	int i;
	for (i = 0; i < MAX_DMA_NUM; i++)
		if (__dmac_channel_irq_detected(i))
			return i;
	return -1;
}


/***************************************************************************
 * AIC (AC'97 & I2S Controller)
 ***************************************************************************/

#define __aic_enable()		( REG_AIC_FR |= AIC_FR_ENB )
#define __aic_disable()		( REG_AIC_FR &= ~AIC_FR_ENB )
#define __aic_reset()		( REG_AIC_FR |= AIC_FR_RST )
#define __aic_select_ac97()	( REG_AIC_FR &= ~AIC_FR_AUSEL )
#define __aic_select_i2s()	( REG_AIC_FR |= AIC_FR_AUSEL )

#define __i2s_as_master()	( REG_AIC_FR |= AIC_FR_BCKD | AIC_FR_SYNCD )
#define __i2s_as_slave()	( REG_AIC_FR &= ~(AIC_FR_BCKD | AIC_FR_SYNCD) )

#define __aic_set_transmit_trigger(n) 			\
do {							\
	REG_AIC_FR &= ~AIC_FR_TFTH_MASK;		\
	REG_AIC_FR |= ((n) << AIC_FR_TFTH_BIT);		\
} while(0)

#define __aic_set_receive_trigger(n) 			\
do {							\
	REG_AIC_FR &= ~AIC_FR_RFTH_MASK;		\
	REG_AIC_FR |= ((n) << AIC_FR_RFTH_BIT);		\
} while(0)

#define __aic_enable_record()	( REG_AIC_CR |= AIC_CR_EREC )
#define __aic_disable_record()	( REG_AIC_CR &= ~AIC_CR_EREC )
#define __aic_enable_replay()	( REG_AIC_CR |= AIC_CR_ERPL )
#define __aic_disable_replay()	( REG_AIC_CR &= ~AIC_CR_ERPL )
#define __aic_enable_loopback()	( REG_AIC_CR |= AIC_CR_ENLBF )
#define __aic_disable_loopback() ( REG_AIC_CR &= ~AIC_CR_ENLBF )

#define __aic_flush_fifo()	( REG_AIC_CR |= AIC_CR_FLUSH )
#define __aic_unflush_fifo()	( REG_AIC_CR &= ~AIC_CR_FLUSH )

#define __aic_enable_transmit_intr() \
  ( REG_AIC_CR |= (AIC_CR_ETFS | AIC_CR_ETUR) )
#define __aic_disable_transmit_intr() \
  ( REG_AIC_CR &= ~(AIC_CR_ETFS | AIC_CR_ETUR) )
#define __aic_enable_receive_intr() \
  ( REG_AIC_CR |= (AIC_CR_ERFS | AIC_CR_EROR) )
#define __aic_disable_receive_intr() \
  ( REG_AIC_CR &= ~(AIC_CR_ERFS | AIC_CR_EROR) )

#define __aic_enable_transmit_dma()  ( REG_AIC_CR |= AIC_CR_TDMS )
#define __aic_disable_transmit_dma() ( REG_AIC_CR &= ~AIC_CR_TDMS )
#define __aic_enable_receive_dma()   ( REG_AIC_CR |= AIC_CR_RDMS )
#define __aic_disable_receive_dma()  ( REG_AIC_CR &= ~AIC_CR_RDMS )

#define __aic_enable_mono2stereo()   ( REG_AIC_CR |= AIC_CR_M2S )
#define __aic_disable_mono2stereo()  ( REG_AIC_CR &= ~AIC_CR_M2S )
#define __aic_enable_byteswap()      ( REG_AIC_CR |= AIC_CR_ENDSW )
#define __aic_disable_byteswap()     ( REG_AIC_CR &= ~AIC_CR_ENDSW )
#define __aic_enable_unsignadj()     ( REG_AIC_CR |= AIC_CR_AVSTSU )
#define __aic_disable_unsignadj()    ( REG_AIC_CR &= ~AIC_CR_AVSTSU )

#define AC97_PCM_XS_L_FRONT   	AIC_ACCR1_XS_SLOT3
#define AC97_PCM_XS_R_FRONT   	AIC_ACCR1_XS_SLOT4
#define AC97_PCM_XS_CENTER    	AIC_ACCR1_XS_SLOT6
#define AC97_PCM_XS_L_SURR    	AIC_ACCR1_XS_SLOT7
#define AC97_PCM_XS_R_SURR    	AIC_ACCR1_XS_SLOT8
#define AC97_PCM_XS_LFE       	AIC_ACCR1_XS_SLOT9

#define AC97_PCM_RS_L_FRONT   	AIC_ACCR1_RS_SLOT3
#define AC97_PCM_RS_R_FRONT   	AIC_ACCR1_RS_SLOT4
#define AC97_PCM_RS_CENTER    	AIC_ACCR1_RS_SLOT6
#define AC97_PCM_RS_L_SURR    	AIC_ACCR1_RS_SLOT7
#define AC97_PCM_RS_R_SURR    	AIC_ACCR1_RS_SLOT8
#define AC97_PCM_RS_LFE       	AIC_ACCR1_RS_SLOT9

#define __ac97_set_xs_none()	( REG_AIC_ACCR1 &= ~AIC_ACCR1_XS_MASK )
#define __ac97_set_xs_mono() 						\
do {									\
	REG_AIC_ACCR1 &= ~AIC_ACCR1_XS_MASK;				\
	REG_AIC_ACCR1 |= AC97_PCM_XS_R_FRONT;				\
} while(0)
#define __ac97_set_xs_stereo() 						\
do {									\
	REG_AIC_ACCR1 &= ~AIC_ACCR1_XS_MASK;				\
	REG_AIC_ACCR1 |= AC97_PCM_XS_L_FRONT | AC97_PCM_XS_R_FRONT;	\
} while(0)

/* In fact, only stereo is support now. */ 
#define __ac97_set_rs_none()	( REG_AIC_ACCR1 &= ~AIC_ACCR1_RS_MASK )
#define __ac97_set_rs_mono() 						\
do {									\
	REG_AIC_ACCR1 &= ~AIC_ACCR1_RS_MASK;				\
	REG_AIC_ACCR1 |= AC97_PCM_RS_R_FRONT;				\
} while(0)
#define __ac97_set_rs_stereo() 						\
do {									\
	REG_AIC_ACCR1 &= ~AIC_ACCR1_RS_MASK;				\
	REG_AIC_ACCR1 |= AC97_PCM_RS_L_FRONT | AC97_PCM_RS_R_FRONT;	\
} while(0)

#define __ac97_warm_reset_codec()		\
 do {						\
	REG_AIC_ACCR2 |= AIC_ACCR2_SA;		\
	REG_AIC_ACCR2 |= AIC_ACCR2_SS;		\
	udelay(2);				\
	REG_AIC_ACCR2 &= ~AIC_ACCR2_SS;		\
	REG_AIC_ACCR2 &= ~AIC_ACCR2_SA;		\
 } while (0)

#define __ac97_cold_reset_codec()		\
 do {						\
	REG_AIC_ACCR2 |=  AIC_ACCR2_SR;		\
	udelay(2);				\
	REG_AIC_ACCR2 &= ~AIC_ACCR2_SR;		\
 } while (0)

/* n=8,16,18,20 */
#define __ac97_set_iass(n) \
 ( REG_AIC_ACCR2 = (REG_AIC_ACCR2 & ~AIC_ACCR2_IASS_MASK) | AIC_ACCR2_IASS_##n##BIT )
#define __ac97_set_oass(n) \
 ( REG_AIC_ACCR2 = (REG_AIC_ACCR2 & ~AIC_ACCR2_OASS_MASK) | AIC_ACCR2_OASS_##n##BIT )

#define __i2s_select_i2s()            ( REG_AIC_I2SCR &= ~AIC_I2SCR_AMSL )
#define __i2s_select_msbjustified()   ( REG_AIC_I2SCR |= AIC_I2SCR_AMSL )

/* n=8,16,18,20,24 */
#define __i2s_set_sample_size(n) \
 ( REG_AIC_I2SCR |= (REG_AIC_I2SCR & ~AIC_I2SCR_WL_MASK) | AIC_I2SCR_WL_##n##BIT )

#define __i2s_stop_bitclk()   ( REG_AIC_I2SCR |= AIC_I2SCR_STPBK )
#define __i2s_start_bitclk()  ( REG_AIC_I2SCR &= ~AIC_I2SCR_STPBK )

#define __aic_transmit_request()  ( REG_AIC_SR & AIC_SR_TFS )
#define __aic_receive_request()   ( REG_AIC_SR & AIC_SR_RFS )
#define __aic_transmit_underrun() ( REG_AIC_SR & AIC_SR_TUR )
#define __aic_receive_overrun()   ( REG_AIC_SR & AIC_SR_ROR )

#define __aic_clear_errors()      ( REG_AIC_SR &= ~(AIC_SR_TUR | AIC_SR_ROR) )

#define __aic_get_transmit_resident() \
  ( (REG_AIC_SR & AIC_SR_TFL_MASK) >> AIC_SR_TFL_BIT )
#define __aic_get_receive_count() \
  ( (REG_AIC_SR & AIC_SR_RFL_MASK) >> AIC_SR_RFL_BIT )

#define __ac97_command_transmitted()     ( REG_AIC_ACSR & AIC_ACSR_CADT )
#define __ac97_status_received()         ( REG_AIC_ACSR & AIC_ACSR_SADR )
#define __ac97_status_receive_timeout()  ( REG_AIC_ACSR & AIC_ACSR_RSTO )
#define __ac97_codec_is_low_power_mode() ( REG_AIC_ACSR & AIC_ACSR_CLPM )
#define __ac97_codec_is_ready()          ( REG_AIC_ACSR & AIC_ACSR_CRDY )
#define __ac97_slot_error_detected()     ( REG_AIC_ACSR & AIC_ACSR_SLTERR )
#define __ac97_clear_slot_error()        ( REG_AIC_ACSR &= ~AIC_ACSR_SLTERR )

#define __i2s_is_busy()         ( REG_AIC_I2SSR & AIC_I2SSR_BSY )

#define CODEC_READ_CMD	        (1 << 19)
#define CODEC_WRITE_CMD	        (0 << 19)
#define CODEC_REG_INDEX_BIT     12
#define CODEC_REG_INDEX_MASK	(0x7f << CODEC_REG_INDEX_BIT)	/* 18:12 */
#define CODEC_REG_DATA_BIT      4
#define CODEC_REG_DATA_MASK	(0x0ffff << 4)	/* 19:4 */

#define __ac97_out_rcmd_addr(reg) 					\
do { 									\
    REG_AIC_ACCAR = CODEC_READ_CMD | ((reg) << CODEC_REG_INDEX_BIT); 	\
} while (0)

#define __ac97_out_wcmd_addr(reg) 					\
do { 									\
    REG_AIC_ACCAR = CODEC_WRITE_CMD | ((reg) << CODEC_REG_INDEX_BIT); 	\
} while (0)

#define __ac97_out_data(value) 						\
do { 									\
    REG_AIC_ACCDR = ((value) << CODEC_REG_DATA_BIT); 			\
} while (0)

#define __ac97_in_data() \
 ( (REG_AIC_ACSDR & CODEC_REG_DATA_MASK) >> CODEC_REG_DATA_BIT )

#define __ac97_in_status_addr() \
 ( (REG_AIC_ACSAR & CODEC_REG_INDEX_MASK) >> CODEC_REG_INDEX_BIT )

#define __i2s_set_sample_rate(i2sclk, sync) \
  ( REG_AIC_I2SDIV = ((i2sclk) / (4*64)) / (sync) )

#define __aic_write_tfifo(v)  ( REG_AIC_DR = (v) )
#define __aic_read_rfifo()    ( REG_AIC_DR )

//
// Define next ops for AC97 compatible
//

#define AC97_ACSR	AIC_ACSR

#define __ac97_enable()		__aic_enable(); __aic_select_ac97()
#define __ac97_disable()	__aic_disable()
#define __ac97_reset()		__aic_reset()

#define __ac97_set_transmit_trigger(n)	__aic_set_transmit_trigger(n)
#define __ac97_set_receive_trigger(n)	__aic_set_receive_trigger(n)

#define __ac97_enable_record()		__aic_enable_record()
#define __ac97_disable_record()		__aic_disable_record()
#define __ac97_enable_replay()		__aic_enable_replay()
#define __ac97_disable_replay()		__aic_disable_replay()
#define __ac97_enable_loopback()	__aic_enable_loopback()
#define __ac97_disable_loopback()	__aic_disable_loopback()

#define __ac97_enable_transmit_dma()	__aic_enable_transmit_dma()
#define __ac97_disable_transmit_dma()	__aic_disable_transmit_dma()
#define __ac97_enable_receive_dma()	__aic_enable_receive_dma()
#define __ac97_disable_receive_dma()	__aic_disable_receive_dma()

#define __ac97_transmit_request()	__aic_transmit_request()
#define __ac97_receive_request()	__aic_receive_request()
#define __ac97_transmit_underrun()	__aic_transmit_underrun()
#define __ac97_receive_overrun()	__aic_receive_overrun()

#define __ac97_clear_errors()		__aic_clear_errors()

#define __ac97_get_transmit_resident()	__aic_get_transmit_resident()
#define __ac97_get_receive_count()	__aic_get_receive_count()

#define __ac97_enable_transmit_intr()	__aic_enable_transmit_intr()
#define __ac97_disable_transmit_intr()	__aic_disable_transmit_intr()
#define __ac97_enable_receive_intr()	__aic_enable_receive_intr()
#define __ac97_disable_receive_intr()	__aic_disable_receive_intr()

#define __ac97_write_tfifo(v)		__aic_write_tfifo(v)
#define __ac97_read_rfifo()		__aic_read_rfifo()

//
// Define next ops for I2S compatible
//

#define I2S_ACSR	AIC_I2SSR

#define __i2s_enable()		 __aic_enable(); __aic_select_i2s()
#define __i2s_disable()		__aic_disable()
#define __i2s_reset()		__aic_reset()

#define __i2s_set_transmit_trigger(n)	__aic_set_transmit_trigger(n)
#define __i2s_set_receive_trigger(n)	__aic_set_receive_trigger(n)

#define __i2s_enable_record()		__aic_enable_record()
#define __i2s_disable_record()		__aic_disable_record()
#define __i2s_enable_replay()		__aic_enable_replay()
#define __i2s_disable_replay()		__aic_disable_replay()
#define __i2s_enable_loopback()		__aic_enable_loopback()
#define __i2s_disable_loopback()	__aic_disable_loopback()

#define __i2s_enable_transmit_dma()	__aic_enable_transmit_dma()
#define __i2s_disable_transmit_dma()	__aic_disable_transmit_dma()
#define __i2s_enable_receive_dma()	__aic_enable_receive_dma()
#define __i2s_disable_receive_dma()	__aic_disable_receive_dma()

#define __i2s_transmit_request()	__aic_transmit_request()
#define __i2s_receive_request()		__aic_receive_request()
#define __i2s_transmit_underrun()	__aic_transmit_underrun()
#define __i2s_receive_overrun()		__aic_receive_overrun()

#define __i2s_clear_errors()		__aic_clear_errors()

#define __i2s_get_transmit_resident()	__aic_get_transmit_resident()
#define __i2s_get_receive_count()	__aic_get_receive_count()

#define __i2s_enable_transmit_intr()	__aic_enable_transmit_intr()
#define __i2s_disable_transmit_intr()	__aic_disable_transmit_intr()
#define __i2s_enable_receive_intr()	__aic_enable_receive_intr()
#define __i2s_disable_receive_intr()	__aic_disable_receive_intr()

#define __i2s_write_tfifo(v)		__aic_write_tfifo(v)
#define __i2s_read_rfifo()		__aic_read_rfifo()

#define __i2s_reset_codec()			\
 do {						\
 } while (0)


/***************************************************************************
 * ICDC
 ***************************************************************************/


/***************************************************************************
 * INTC
 ***************************************************************************/
#define __intc_unmask_irq(n)	( REG_INTC_IMCR = (1 << (n)) )
#define __intc_mask_irq(n)	( REG_INTC_IMSR = (1 << (n)) )
#define __intc_ack_irq(n)	( REG_INTC_IPR = (1 << (n)) )


/***************************************************************************
 * I2C
 ***************************************************************************/

#define __i2c_enable()		( REG_I2C_CR |= I2C_CR_I2CE )
#define __i2c_disable()		( REG_I2C_CR &= ~I2C_CR_I2CE )

#define __i2c_send_start()	( REG_I2C_CR |= I2C_CR_STA )
#define __i2c_send_stop()	( REG_I2C_CR |= I2C_CR_STO )
#define __i2c_send_ack()	( REG_I2C_CR &= ~I2C_CR_AC )
#define __i2c_send_nack()	( REG_I2C_CR |= I2C_CR_AC )

#define __i2c_set_drf()		( REG_I2C_SR |= I2C_SR_DRF )
#define __i2c_clear_drf()	( REG_I2C_SR &= ~I2C_SR_DRF )
#define __i2c_check_drf()	( REG_I2C_SR & I2C_SR_DRF )

#define __i2c_received_ack()	( !(REG_I2C_SR & I2C_SR_ACKF) )
#define __i2c_is_busy()		( REG_I2C_SR & I2C_SR_BUSY )
#define __i2c_transmit_ended()	( REG_I2C_SR & I2C_SR_TEND )

#define __i2c_set_clk(dev_clk, i2c_clk) \
  ( REG_I2C_GR = (dev_clk) / (16*(i2c_clk)) - 1 )

#define __i2c_read()		( REG_I2C_DR )
#define __i2c_write(val)	( REG_I2C_DR = (val) )


/***************************************************************************
 * MSC
 ***************************************************************************/

#define __msc_start_op() \
  ( REG_MSC_STRPCL = MSC_STRPCL_START_OP | MSC_STRPCL_CLOCK_CONTROL_START )

#define __msc_set_resto(to) 	( REG_MSC_RESTO = to )
#define __msc_set_rdto(to) 	( REG_MSC_RDTO = to )
#define __msc_set_cmd(cmd) 	( REG_MSC_CMD = cmd )
#define __msc_set_arg(arg) 	( REG_MSC_ARG = arg )
#define __msc_set_nob(nob) 	( REG_MSC_NOB = nob )
#define __msc_get_nob() 	( REG_MSC_NOB )
#define __msc_set_blklen(len) 	( REG_MSC_BLKLEN = len )
#define __msc_set_cmdat(cmdat) 	( REG_MSC_CMDAT = cmdat )
#define __msc_set_cmdat_ioabort() 	( REG_MSC_CMDAT |= MSC_CMDAT_IO_ABORT )
#define __msc_clear_cmdat_ioabort() 	( REG_MSC_CMDAT &= ~MSC_CMDAT_IO_ABORT )

#define __msc_set_cmdat_bus_width1() 			\
do { 							\
	REG_MSC_CMDAT &= ~MSC_CMDAT_BUS_WIDTH_MASK; 	\
	REG_MSC_CMDAT |= MSC_CMDAT_BUS_WIDTH_1BIT; 	\
} while(0)

#define __msc_set_cmdat_bus_width4() 			\
do { 							\
	REG_MSC_CMDAT &= ~MSC_CMDAT_BUS_WIDTH_MASK; 	\
	REG_MSC_CMDAT |= MSC_CMDAT_BUS_WIDTH_4BIT; 	\
} while(0)

#define __msc_set_cmdat_dma_en() ( REG_MSC_CMDAT |= MSC_CMDAT_DMA_EN )
#define __msc_set_cmdat_init() 	( REG_MSC_CMDAT |= MSC_CMDAT_INIT )
#define __msc_set_cmdat_busy() 	( REG_MSC_CMDAT |= MSC_CMDAT_BUSY )
#define __msc_set_cmdat_stream() ( REG_MSC_CMDAT |= MSC_CMDAT_STREAM_BLOCK )
#define __msc_set_cmdat_block() ( REG_MSC_CMDAT &= ~MSC_CMDAT_STREAM_BLOCK )
#define __msc_set_cmdat_read() 	( REG_MSC_CMDAT &= ~MSC_CMDAT_WRITE_READ )
#define __msc_set_cmdat_write() ( REG_MSC_CMDAT |= MSC_CMDAT_WRITE_READ )
#define __msc_set_cmdat_data_en() ( REG_MSC_CMDAT |= MSC_CMDAT_DATA_EN )

/* r is MSC_CMDAT_RESPONSE_FORMAT_Rx or MSC_CMDAT_RESPONSE_FORMAT_NONE */
#define __msc_set_cmdat_res_format(r) 				\
do { 								\
	REG_MSC_CMDAT &= ~MSC_CMDAT_RESPONSE_FORMAT_MASK; 	\
	REG_MSC_CMDAT |= (r); 					\
} while(0)

#define __msc_clear_cmdat() \
  REG_MSC_CMDAT &= ~( MSC_CMDAT_IO_ABORT | MSC_CMDAT_DMA_EN | MSC_CMDAT_INIT| \
  MSC_CMDAT_BUSY | MSC_CMDAT_STREAM_BLOCK | MSC_CMDAT_WRITE_READ | \
  MSC_CMDAT_DATA_EN | MSC_CMDAT_RESPONSE_FORMAT_MASK )

#define __msc_get_imask() 		( REG_MSC_IMASK )
#define __msc_mask_all_intrs() 		( REG_MSC_IMASK = 0xff )
#define __msc_unmask_all_intrs() 	( REG_MSC_IMASK = 0x00 )
#define __msc_mask_rd() 		( REG_MSC_IMASK |= MSC_IMASK_RXFIFO_RD_REQ )
#define __msc_unmask_rd() 		( REG_MSC_IMASK &= ~MSC_IMASK_RXFIFO_RD_REQ )
#define __msc_mask_wr() 		( REG_MSC_IMASK |= MSC_IMASK_TXFIFO_WR_REQ )
#define __msc_unmask_wr() 		( REG_MSC_IMASK &= ~MSC_IMASK_TXFIFO_WR_REQ )
#define __msc_mask_endcmdres() 		( REG_MSC_IMASK |= MSC_IMASK_END_CMD_RES )
#define __msc_unmask_endcmdres() 	( REG_MSC_IMASK &= ~MSC_IMASK_END_CMD_RES )
#define __msc_mask_datatrandone() 	( REG_MSC_IMASK |= MSC_IMASK_DATA_TRAN_DONE )
#define __msc_unmask_datatrandone() 	( REG_MSC_IMASK &= ~MSC_IMASK_DATA_TRAN_DONE )
#define __msc_mask_prgdone() 		( REG_MSC_IMASK |= MSC_IMASK_PRG_DONE )
#define __msc_unmask_prgdone() 		( REG_MSC_IMASK &= ~MSC_IMASK_PRG_DONE )

/* n=0,1,2,3,4,5,6,7 */
#define __msc_set_clkrt(n) 	\
do { 				\
	REG_MSC_CLKRT = n;	\
} while(0)

#define __msc_get_ireg() 		( REG_MSC_IREG )
#define __msc_ireg_rd() 		( REG_MSC_IREG & MSC_IREG_RXFIFO_RD_REQ )
#define __msc_ireg_wr() 		( REG_MSC_IREG & MSC_IREG_TXFIFO_WR_REQ )
#define __msc_ireg_end_cmd_res() 	( REG_MSC_IREG & MSC_IREG_END_CMD_RES )
#define __msc_ireg_data_tran_done() 	( REG_MSC_IREG & MSC_IREG_DATA_TRAN_DONE )
#define __msc_ireg_prg_done() 		( REG_MSC_IREG & MSC_IREG_PRG_DONE )
#define __msc_ireg_clear_end_cmd_res() 	( REG_MSC_IREG = MSC_IREG_END_CMD_RES )
#define __msc_ireg_clear_data_tran_done() ( REG_MSC_IREG = MSC_IREG_DATA_TRAN_DONE )
#define __msc_ireg_clear_prg_done() 	( REG_MSC_IREG = MSC_IREG_PRG_DONE )

#define __msc_get_stat() 		( REG_MSC_STAT )
#define __msc_stat_not_end_cmd_res() 	( (REG_MSC_STAT & MSC_STAT_END_CMD_RES) == 0)
#define __msc_stat_crc_err() \
  ( REG_MSC_STAT & (MSC_STAT_CRC_RES_ERR | MSC_STAT_CRC_READ_ERROR | MSC_STAT_CRC_WRITE_ERROR_YES) )
#define __msc_stat_res_crc_err() 	( REG_MSC_STAT & MSC_STAT_CRC_RES_ERR )
#define __msc_stat_rd_crc_err() 	( REG_MSC_STAT & MSC_STAT_CRC_READ_ERROR )
#define __msc_stat_wr_crc_err() 	( REG_MSC_STAT & MSC_STAT_CRC_WRITE_ERROR_YES )
#define __msc_stat_resto_err() 		( REG_MSC_STAT & MSC_STAT_TIME_OUT_RES )
#define __msc_stat_rdto_err() 		( REG_MSC_STAT & MSC_STAT_TIME_OUT_READ )

#define __msc_rd_resfifo() 		( REG_MSC_RES )
#define __msc_rd_rxfifo()  		( REG_MSC_RXFIFO )
#define __msc_wr_txfifo(v)  		( REG_MSC_TXFIFO = v )

#define __msc_reset() 						\
do { 								\
	REG_MSC_STRPCL = MSC_STRPCL_RESET;			\
 	while (REG_MSC_STAT & MSC_STAT_IS_RESETTING);		\
} while (0)

#define __msc_start_clk() 					\
do { 								\
	REG_MSC_STRPCL = MSC_STRPCL_CLOCK_CONTROL_START;	\
} while (0)

#define __msc_stop_clk() 					\
do { 								\
	REG_MSC_STRPCL = MSC_STRPCL_CLOCK_CONTROL_STOP;	\
} while (0)

#define MMC_CLK 19169200
#define SD_CLK  24576000

/* msc_clk should little than pclk and little than clk retrieve from card */
#define __msc_calc_clk_divisor(type,dev_clk,msc_clk,lv)		\
do {								\
	unsigned int rate, pclk, i;				\
	pclk = dev_clk;						\
	rate = type?SD_CLK:MMC_CLK;				\
  	if (msc_clk && msc_clk < pclk)				\
    		pclk = msc_clk;					\
	i = 0;							\
  	while (pclk < rate)					\
    	{							\
      		i ++;						\
      		rate >>= 1;					\
    	}							\
  	lv = i;							\
} while(0)

/* divide rate to little than or equal to 400kHz */
#define __msc_calc_slow_clk_divisor(type, lv)			\
do {								\
	unsigned int rate, i;					\
	rate = (type?SD_CLK:MMC_CLK)/1000/400;			\
	i = 0;							\
	while (rate > 0)					\
    	{							\
      		rate >>= 1;					\
      		i ++;						\
    	}							\
  	lv = i;							\
} while(0)


/***************************************************************************
 * SSI
 ***************************************************************************/

#define __ssi_enable()    ( REG_SSI_CR0 |= SSI_CR0_SSIE )
#define __ssi_disable()   ( REG_SSI_CR0 &= ~SSI_CR0_SSIE )
#define __ssi_select_ce() ( REG_SSI_CR0 &= ~SSI_CR0_FSEL )

#define __ssi_normal_mode() ( REG_SSI_ITR &= ~SSI_ITR_IVLTM_MASK )

#define __ssi_select_ce2() 		\
do { 					\
	REG_SSI_CR0 |= SSI_CR0_FSEL; 	\
	REG_SSI_CR1 &= ~SSI_CR1_MULTS; 	\
} while (0)

#define __ssi_select_gpc() 		\
do { 					\
	REG_SSI_CR0 &= ~SSI_CR0_FSEL; 	\
	REG_SSI_CR1 |= SSI_CR1_MULTS; 	\
} while (0)

#define __ssi_enable_tx_intr() 	\
  ( REG_SSI_CR0 |= SSI_CR0_TIE | SSI_CR0_TEIE )

#define __ssi_disable_tx_intr() \
  ( REG_SSI_CR0 &= ~(SSI_CR0_TIE | SSI_CR0_TEIE) )

#define __ssi_enable_rx_intr() 	\
  ( REG_SSI_CR0 |= SSI_CR0_RIE | SSI_CR0_REIE )

#define __ssi_disable_rx_intr() \
  ( REG_SSI_CR0 &= ~(SSI_CR0_RIE | SSI_CR0_REIE) )

#define __ssi_enable_loopback()  ( REG_SSI_CR0 |= SSI_CR0_LOOP )
#define __ssi_disable_loopback() ( REG_SSI_CR0 &= ~SSI_CR0_LOOP )

#define __ssi_enable_receive()   ( REG_SSI_CR0 &= ~SSI_CR0_DISREV )
#define __ssi_disable_receive()  ( REG_SSI_CR0 |= SSI_CR0_DISREV )

#define __ssi_finish_receive() 	\
  ( REG_SSI_CR0 |= (SSI_CR0_RFINE | SSI_CR0_RFINC) )

#define __ssi_disable_recvfinish() \
  ( REG_SSI_CR0 &= ~(SSI_CR0_RFINE | SSI_CR0_RFINC) )

#define __ssi_flush_txfifo()   ( REG_SSI_CR0 |= SSI_CR0_TFLUSH )
#define __ssi_flush_rxfifo()   ( REG_SSI_CR0 |= SSI_CR0_RFLUSH )

#define __ssi_flush_fifo() \
  ( REG_SSI_CR0 |= SSI_CR0_TFLUSH | SSI_CR0_RFLUSH )

#define __ssi_finish_transmit() ( REG_SSI_CR1 &= ~SSI_CR1_UNFIN )

#define __ssi_spi_format() 					\
do { 								\
	REG_SSI_CR1 &= ~SSI_CR1_FMAT_MASK; 			\
	REG_SSI_CR1 |= SSI_CR1_FMAT_SPI; 			\
	REG_SSI_CR1 &= ~(SSI_CR1_TFVCK_MASK|SSI_CR1_TCKFI_MASK);\
	REG_SSI_CR1 |= (SSI_CR1_TFVCK_1 | SSI_CR1_TCKFI_1);	\
} while (0)

/* TI's SSP format, must clear SSI_CR1.UNFIN */
#define __ssi_ssp_format() 					\
do { 								\
	REG_SSI_CR1 &= ~(SSI_CR1_FMAT_MASK | SSI_CR1_UNFIN); 	\
	REG_SSI_CR1 |= SSI_CR1_FMAT_SSP; 			\
} while (0)

/* National's Microwire format, must clear SSI_CR0.RFINE, and set max delay */
#define __ssi_microwire_format() 				\
do { 								\
	REG_SSI_CR1 &= ~SSI_CR1_FMAT_MASK; 			\
	REG_SSI_CR1 |= SSI_CR1_FMAT_MW1; 			\
	REG_SSI_CR1 &= ~(SSI_CR1_TFVCK_MASK|SSI_CR1_TCKFI_MASK);\
	REG_SSI_CR1 |= (SSI_CR1_TFVCK_3 | SSI_CR1_TCKFI_3);	\
	REG_SSI_CR0 &= ~SSI_CR0_RFINE; 				\
} while (0)

/* CE# level (FRMHL), CE# in interval time (ITFRM),
   clock phase and polarity (PHA POL),
   interval time (SSIITR), interval characters/frame (SSIICR) */

 /* frmhl,endian,mcom,flen,pha,pol MASK */
#define SSICR1_MISC_MASK 					\
	( SSI_CR1_FRMHL_MASK | SSI_CR1_LFST | SSI_CR1_MCOM_MASK	\
	| SSI_CR1_FLEN_MASK | SSI_CR1_PHA | SSI_CR1_POL )	\

#define __ssi_spi_set_misc(frmhl,endian,flen,mcom,pha,pol)	\
do { 								\
	REG_SSI_CR1 &= ~SSICR1_MISC_MASK; 			\
	REG_SSI_CR1 |= ((frmhl) << 30) | ((endian) << 25) | 	\
		 (((mcom) - 1) << 12) | (((flen) - 2) << 4) | 	\
	         ((pha) << 1) | (pol); 				\
} while(0)

/* Transfer with MSB or LSB first */
#define __ssi_set_msb() ( REG_SSI_CR1 &= ~SSI_CR1_LFST )
#define __ssi_set_lsb() ( REG_SSI_CR1 |= SSI_CR1_LFST )

#define __ssi_set_frame_length(n) \
    REG_SSI_CR1 = (REG_SSI_CR1 & ~SSI_CR1_FLEN_MASK) | (((n) - 2) << 4) 

/* n = 1 - 16 */
#define __ssi_set_microwire_command_length(n) \
    ( REG_SSI_CR1 = ((REG_SSI_CR1 & ~SSI_CR1_MCOM_MASK) | SSI_CR1_MCOM_##n##BIT) )

/* Set the clock phase for SPI */
#define __ssi_set_spi_clock_phase(n) \
    ( REG_SSI_CR1 = ((REG_SSI_CR1 & ~SSI_CR1_PHA) | (n&0x1)) )

/* Set the clock polarity for SPI */
#define __ssi_set_spi_clock_polarity(n) \
    ( REG_SSI_CR1 = ((REG_SSI_CR1 & ~SSI_CR1_POL) | (n&0x1)) )

/* n = 1,4,8,14 */
#define __ssi_set_tx_trigger(n) 		\
do { 						\
	REG_SSI_CR1 &= ~SSI_CR1_TTRG_MASK; 	\
	REG_SSI_CR1 |= SSI_CR1_TTRG_##n; 	\
} while (0)

/* n = 1,4,8,14 */
#define __ssi_set_rx_trigger(n) 		\
do { 						\
	REG_SSI_CR1 &= ~SSI_CR1_RTRG_MASK; 	\
	REG_SSI_CR1 |= SSI_CR1_RTRG_##n; 	\
} while (0)

#define __ssi_get_txfifo_count() \
    ( (REG_SSI_SR & SSI_SR_TFIFONUM_MASK) >> SSI_SR_TFIFONUM_BIT )

#define __ssi_get_rxfifo_count() \
    ( (REG_SSI_SR & SSI_SR_RFIFONUM_MASK) >> SSI_SR_RFIFONUM_BIT )

#define __ssi_clear_errors() \
    ( REG_SSI_SR &= ~(SSI_SR_UNDR | SSI_SR_OVER) )

#define __ssi_transfer_end()	( REG_SSI_SR & SSI_SR_END )
#define __ssi_is_busy()		( REG_SSI_SR & SSI_SR_BUSY )

#define __ssi_txfifo_full()	( REG_SSI_SR & SSI_SR_TFF )
#define __ssi_rxfifo_empty()	( REG_SSI_SR & SSI_SR_RFE )
#define __ssi_rxfifo_noempty()	( REG_SSI_SR & SSI_SR_RFHF )

#define __ssi_set_clk(dev_clk, ssi_clk) \
  ( REG_SSI_GR = (dev_clk) / (2*(ssi_clk)) - 1 )

#define __ssi_receive_data()    REG_SSI_DR
#define __ssi_transmit_data(v)  ( REG_SSI_DR = (v) )

#endif /* !__ASSEMBLY__ */

#endif /* __JZ4740_H__ */
