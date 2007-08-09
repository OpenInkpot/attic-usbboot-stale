#ifndef __EJTAG_H__
#define __EJTAG_H__

/*------------------------------------------------------------------------*/
/*  TARGET JTAG INSTRUCTIONS  						  */
/*------------------------------------------------------------------------*/
#define IDCODE      	0x01    //TAP select chip ID register
#define IMPCODE		0x03    //TAP select chip implementation code
#define ADDRESS_IR 	0x08    //JTAG address register
#define DATA_IR		0x09    //JTAG data register
#define CONTROL_IR 	0x0A    //JTAG control register
#define ALL_IR		0x0B    //JTAG all IR regs. linked together
#define EJBOOT		0x0C    //EJTAG boot target (mips mode)
#define NMLBOOT		0x0D    //Normal boot target
#define EJBOOTA		0x1C    //JTAG boota target (acc mode)
#define CONTROLA	0x1D    //JTAG controla
#define BYPASS		0x1f    //TAP Bypass mode (no registers in chain)

/*
 * Address in ACC mode 
 */
typedef struct {
	unsigned int addr;
	unsigned int ctrl;
} acc_addr_t;

/*
 * EJTAG APIs
 */
extern unsigned char tapmove(unsigned char tms, unsigned char tdi);
extern void tapreset(void);
extern void ejtag_reset(void);
extern void hwreset(void);
extern unsigned char ejtag_instr(unsigned char din);
extern unsigned int ejtag_data(unsigned int din);
extern unsigned int ejtag_data_n(unsigned int din, unsigned int n);
extern unsigned int ejtag_acc_data(unsigned int din);
extern void ejtag_acc_addr(acc_addr_t *acc);
extern unsigned int ejtag_idcode(void);
extern unsigned int ejtag_impcode(void);
extern void ejtag_open(void);
extern void ejtag_close(void);
extern void led_on(void);
extern void led_off(void);
extern void set_hwreset_ms(int ms);

#endif /* __EJTAG_H__ */
