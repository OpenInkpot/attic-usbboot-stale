/*
 * head.S
 *
 * Entry point of the firmware.
 * The firmware code are executed in the ICache.
 *
 * Copyright (C) 2006 Ingenic Semiconductor Inc.
 *
 */

	.text

	.extern c_main

	.globl _start
	.set noreorder
_start:
	//----------------------------------------------------
	// display LED for debug
	//----------------------------------------------------
	la	$9, 0xb6000058		// LED address
	la	$8, led_display_data
	li	$7, 8
_led_display:
	lb	$6, 0($8)
	sb	$6, 0($9)
	sub	$7, $7, 1
	addi	$8, $8, 1
	bgtz	$7, _led_display
	addi	$9, $9, 1

	//----------------------------------------------------
	// Init CP0 registers
	//----------------------------------------------------
	mtc0	$0, $18			// CP0_WATCHLO
	mtc0	$0, $19			// CP0_WATCHHI

	li	$8, 0x0040FC04
	mtc0	$8, $12			// CP0_STATUS

	li	$9, 0x00800000		// IV=1, clear cause
	mtc0	$9, $13			// CP0_CAUSE

	//----------------------------------------------------
	// setup stack, jump to C code
	//----------------------------------------------------
	la	$29, 0x80002000		// sp
	j	c_main
	nop

	.align	2
led_display_data:
	.byte	0x4a
	.byte	0x5a
	.byte	0x34
	.byte	0x37
	.byte	0x34
	.byte	0x30
	.byte	0x56
	.byte	0x31

	.set reorder
