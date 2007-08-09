#ifndef __bsp_h__
#define __bsp_h__

#define EXTAL_CLK	12000000

#define dprintf(x...) printf(x)



#define USE_NAND  0

#define USE_UART0 1
#define USE_UART1 1

#define USE_MSC   1

#define USE_LCD16 1
#define USE_LCD18 0

#define USE_AIC   1

#define USE_CIM   1

/*-----------------------------------------------------------------------
 * Cache Configuration
 */

#define CFG_DCACHE_SIZE		16384
#define CFG_ICACHE_SIZE		16384
#define CFG_CACHELINE_SIZE	32
/*-----------------------------------------------------------------------
*/



#define GPIO_PW_I         97
#define GPIO_PW_O         66
#define GPIO_LED_EN       92
#define GPIO_DISP_OFF_N   93
#define GPIO_RTC_IRQ      96
#define GPIO_USB_CLK_EN   29                            
#define GPIO_CHARG_STAT   125 


#endif
