/*
 * timer.c
 *
 * Perform the system ticks.
 *
 * Author: Seeger Chin
 * e-mail: seeger.chin@gmail.com
 *
 * Copyright (C) 2006 Ingenic Semiconductor Inc.
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 */

#include <bsp.h>
#include <jz4740.h>


void timerHander(unsigned int arg)
{
	OSTimeTick();
}

void JZ_StartTicker(unsigned int tps)
{
	unsigned int latch;
	__cpm_start_tcu();

	__tcu_disable_pwm_output(0);
	__tcu_select_extalclk(0);
	__tcu_select_clk_div4(0);
	
	__tcu_mask_half_match_irq(0); 
	__tcu_unmask_full_match_irq(0);

	latch = (EXTAL_CLK / 4 + (tps>>1)) / tps;
	REG_TCU_TDFR(0) = latch;
	REG_TCU_TDHR(0) = latch;

	__tcu_clear_full_match_flag(0);
	__tcu_start_counter(0);

	request_irq(IRQ_TCU0,timerHander,0);

}

void JZ_StopTicker(void)
{
	__tcu_stop_counter(0);
}


