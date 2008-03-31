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
	la	$29, 0x80004000		// sp
	la	$0, c_main
	j	c_main
	nop

	.set reorder
