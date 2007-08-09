#ifndef __WCP0_H__
#define __WCP0_H__

/*======================================================================
 * handle WCP0 commands here.
 * WM8/WM16/WM32 commands are handled before PLL initialization in ASM codes.
 * Command format: MTC0 rt, rd, sel
 */
static inline void handle_wcp0_command(void)
{
	int i;
	unsigned int rt, rd, sel;

	for (i = 0; i < handp->icmd_cnt; i++) {
		if (handp->icmd_type[i] != CMD_WCP0) continue;

		/* WCP0 command */
		rd = handp->icmd_addr[i];
		rt = handp->icmd_data[i];
		sel = handp->icmd_data2[i];

		switch (sel) {
		case 0:
		{
			switch (rd) {
			case 0:
				__asm__ __volatile__("mtc0 %0, $0, 0":: "r" (rt));
				break;
			case 1:
				__asm__ __volatile__("mtc0 %0, $1, 0":: "r" (rt));
				break;
			case 2:
				__asm__ __volatile__("mtc0 %0, $2, 0":: "r" (rt));
				break;
			case 3:
				__asm__ __volatile__("mtc0 %0, $3, 0":: "r" (rt));
				break;
			case 4:
				__asm__ __volatile__("mtc0 %0, $4, 0":: "r" (rt));
				break;
			case 5:
				__asm__ __volatile__("mtc0 %0, $5, 0":: "r" (rt));
				break;
			case 6:
				__asm__ __volatile__("mtc0 %0, $6, 0":: "r" (rt));
				break;
			case 7:
				__asm__ __volatile__("mtc0 %0, $7, 0":: "r" (rt));
				break;
			case 8:
				__asm__ __volatile__("mtc0 %0, $8, 0":: "r" (rt));
				break;
			case 9:
				__asm__ __volatile__("mtc0 %0, $9, 0":: "r" (rt));
				break;
			case 10:
				__asm__ __volatile__("mtc0 %0, $19, 0":: "r" (rt));
				break;
			case 11:
				__asm__ __volatile__("mtc0 %0, $11, 0":: "r" (rt));
				break;
			case 12:
				__asm__ __volatile__("mtc0 %0, $12, 0":: "r" (rt));
				break;
			case 13:
				__asm__ __volatile__("mtc0 %0, $13, 0":: "r" (rt));
				break;
			case 14:
				__asm__ __volatile__("mtc0 %0, $14, 0":: "r" (rt));
				break;
			case 15:
				__asm__ __volatile__("mtc0 %0, $15, 0":: "r" (rt));
				break;
			case 16:
				__asm__ __volatile__("mtc0 %0, $16, 0":: "r" (rt));
				break;
			case 17:
				__asm__ __volatile__("mtc0 %0, $17, 0":: "r" (rt));
				break;
			case 18:
				__asm__ __volatile__("mtc0 %0, $18, 0":: "r" (rt));
				break;
			case 19:
				__asm__ __volatile__("mtc0 %0, $19, 0":: "r" (rt));
				break;
			case 20:
				__asm__ __volatile__("mtc0 %0, $20, 0":: "r" (rt));
				break;
			case 21:
				__asm__ __volatile__("mtc0 %0, $21, 0":: "r" (rt));
				break;
			case 22:
				__asm__ __volatile__("mtc0 %0, $22, 0":: "r" (rt));
				break;
			case 23:
				__asm__ __volatile__("mtc0 %0, $23, 0":: "r" (rt));
				break;
			case 24:
				__asm__ __volatile__("mtc0 %0, $24, 0":: "r" (rt));
				break;
			case 25:
				__asm__ __volatile__("mtc0 %0, $25, 0":: "r" (rt));
				break;
			case 26:
				__asm__ __volatile__("mtc0 %0, $26, 0":: "r" (rt));
				break;
			case 27:
				__asm__ __volatile__("mtc0 %0, $27, 0":: "r" (rt));
				break;
			case 28:
				__asm__ __volatile__("mtc0 %0, $28, 0":: "r" (rt));
				break;
			case 29:
				__asm__ __volatile__("mtc0 %0, $29, 0":: "r" (rt));
				break;
			case 30:
				__asm__ __volatile__("mtc0 %0, $30, 0":: "r" (rt));
				break;
			case 31:
				__asm__ __volatile__("mtc0 %0, $31, 0":: "r" (rt));
				break;
			}
			break;
		}
		case 1:
		{
			switch (rd) {
			case 0:
				__asm__ __volatile__("mtc0 %0, $0, 1":: "r" (rt));
				break;
			case 1:
				__asm__ __volatile__("mtc0 %0, $1, 1":: "r" (rt));
				break;
			case 2:
				__asm__ __volatile__("mtc0 %0, $2, 1":: "r" (rt));
				break;
			case 3:
				__asm__ __volatile__("mtc0 %0, $3, 1":: "r" (rt));
				break;
			case 4:
				__asm__ __volatile__("mtc0 %0, $4, 1":: "r" (rt));
				break;
			case 5:
				__asm__ __volatile__("mtc0 %0, $5, 1":: "r" (rt));
				break;
			case 6:
				__asm__ __volatile__("mtc0 %0, $6, 1":: "r" (rt));
				break;
			case 7:
				__asm__ __volatile__("mtc0 %0, $7, 1":: "r" (rt));
				break;
			case 8:
				__asm__ __volatile__("mtc0 %0, $8, 1":: "r" (rt));
				break;
			case 9:
				__asm__ __volatile__("mtc0 %0, $9, 1":: "r" (rt));
				break;
			case 10:
				__asm__ __volatile__("mtc0 %0, $19, 1":: "r" (rt));
				break;
			case 11:
				__asm__ __volatile__("mtc0 %0, $11, 1":: "r" (rt));
				break;
			case 12:
				__asm__ __volatile__("mtc0 %0, $12, 1":: "r" (rt));
				break;
			case 13:
				__asm__ __volatile__("mtc0 %0, $13, 1":: "r" (rt));
				break;
			case 14:
				__asm__ __volatile__("mtc0 %0, $14, 1":: "r" (rt));
				break;
			case 15:
				__asm__ __volatile__("mtc0 %0, $15, 1":: "r" (rt));
				break;
			case 16:
				__asm__ __volatile__("mtc0 %0, $16, 1":: "r" (rt));
				break;
			case 17:
				__asm__ __volatile__("mtc0 %0, $17, 1":: "r" (rt));
				break;
			case 18:
				__asm__ __volatile__("mtc0 %0, $18, 1":: "r" (rt));
				break;
			case 19:
				__asm__ __volatile__("mtc0 %0, $19, 1":: "r" (rt));
				break;
			case 20:
				__asm__ __volatile__("mtc0 %0, $20, 1":: "r" (rt));
				break;
			case 21:
				__asm__ __volatile__("mtc0 %0, $21, 1":: "r" (rt));
				break;
			case 22:
				__asm__ __volatile__("mtc0 %0, $22, 1":: "r" (rt));
				break;
			case 23:
				__asm__ __volatile__("mtc0 %0, $23, 1":: "r" (rt));
				break;
			case 24:
				__asm__ __volatile__("mtc0 %0, $24, 1":: "r" (rt));
				break;
			case 25:
				__asm__ __volatile__("mtc0 %0, $25, 1":: "r" (rt));
				break;
			case 26:
				__asm__ __volatile__("mtc0 %0, $26, 1":: "r" (rt));
				break;
			case 27:
				__asm__ __volatile__("mtc0 %0, $27, 1":: "r" (rt));
				break;
			case 28:
				__asm__ __volatile__("mtc0 %0, $28, 1":: "r" (rt));
				break;
			case 29:
				__asm__ __volatile__("mtc0 %0, $29, 1":: "r" (rt));
				break;
			case 30:
				__asm__ __volatile__("mtc0 %0, $30, 1":: "r" (rt));
				break;
			case 31:
				__asm__ __volatile__("mtc0 %0, $31, 1":: "r" (rt));
				break;
			}
			break;
		}
		case 2:
		{
			switch (rd) {
			case 0:
				__asm__ __volatile__("mtc0 %0, $0, 2":: "r" (rt));
				break;
			case 1:
				__asm__ __volatile__("mtc0 %0, $1, 2":: "r" (rt));
				break;
			case 2:
				__asm__ __volatile__("mtc0 %0, $2, 2":: "r" (rt));
				break;
			case 3:
				__asm__ __volatile__("mtc0 %0, $3, 2":: "r" (rt));
				break;
			case 4:
				__asm__ __volatile__("mtc0 %0, $4, 2":: "r" (rt));
				break;
			case 5:
				__asm__ __volatile__("mtc0 %0, $5, 2":: "r" (rt));
				break;
			case 6:
				__asm__ __volatile__("mtc0 %0, $6, 2":: "r" (rt));
				break;
			case 7:
				__asm__ __volatile__("mtc0 %0, $7, 2":: "r" (rt));
				break;
			case 8:
				__asm__ __volatile__("mtc0 %0, $8, 2":: "r" (rt));
				break;
			case 9:
				__asm__ __volatile__("mtc0 %0, $9, 2":: "r" (rt));
				break;
			case 10:
				__asm__ __volatile__("mtc0 %0, $19, 2":: "r" (rt));
				break;
			case 11:
				__asm__ __volatile__("mtc0 %0, $11, 2":: "r" (rt));
				break;
			case 12:
				__asm__ __volatile__("mtc0 %0, $12, 2":: "r" (rt));
				break;
			case 13:
				__asm__ __volatile__("mtc0 %0, $13, 2":: "r" (rt));
				break;
			case 14:
				__asm__ __volatile__("mtc0 %0, $14, 2":: "r" (rt));
				break;
			case 15:
				__asm__ __volatile__("mtc0 %0, $15, 2":: "r" (rt));
				break;
			case 16:
				__asm__ __volatile__("mtc0 %0, $16, 2":: "r" (rt));
				break;
			case 17:
				__asm__ __volatile__("mtc0 %0, $17, 2":: "r" (rt));
				break;
			case 18:
				__asm__ __volatile__("mtc0 %0, $18, 2":: "r" (rt));
				break;
			case 19:
				__asm__ __volatile__("mtc0 %0, $19, 2":: "r" (rt));
				break;
			case 20:
				__asm__ __volatile__("mtc0 %0, $20, 2":: "r" (rt));
				break;
			case 21:
				__asm__ __volatile__("mtc0 %0, $21, 2":: "r" (rt));
				break;
			case 22:
				__asm__ __volatile__("mtc0 %0, $22, 2":: "r" (rt));
				break;
			case 23:
				__asm__ __volatile__("mtc0 %0, $23, 2":: "r" (rt));
				break;
			case 24:
				__asm__ __volatile__("mtc0 %0, $24, 2":: "r" (rt));
				break;
			case 25:
				__asm__ __volatile__("mtc0 %0, $25, 2":: "r" (rt));
				break;
			case 26:
				__asm__ __volatile__("mtc0 %0, $26, 2":: "r" (rt));
				break;
			case 27:
				__asm__ __volatile__("mtc0 %0, $27, 2":: "r" (rt));
				break;
			case 28:
				__asm__ __volatile__("mtc0 %0, $28, 2":: "r" (rt));
				break;
			case 29:
				__asm__ __volatile__("mtc0 %0, $29, 2":: "r" (rt));
				break;
			case 30:
				__asm__ __volatile__("mtc0 %0, $30, 2":: "r" (rt));
				break;
			case 31:
				__asm__ __volatile__("mtc0 %0, $31, 2":: "r" (rt));
				break;
			}
			break;
		}
		case 3:
		{
			switch (rd) {
			case 0:
				__asm__ __volatile__("mtc0 %0, $0, 3":: "r" (rt));
				break;
			case 1:
				__asm__ __volatile__("mtc0 %0, $1, 3":: "r" (rt));
				break;
			case 2:
				__asm__ __volatile__("mtc0 %0, $2, 3":: "r" (rt));
				break;
			case 3:
				__asm__ __volatile__("mtc0 %0, $3, 3":: "r" (rt));
				break;
			case 4:
				__asm__ __volatile__("mtc0 %0, $4, 3":: "r" (rt));
				break;
			case 5:
				__asm__ __volatile__("mtc0 %0, $5, 3":: "r" (rt));
				break;
			case 6:
				__asm__ __volatile__("mtc0 %0, $6, 3":: "r" (rt));
				break;
			case 7:
				__asm__ __volatile__("mtc0 %0, $7, 3":: "r" (rt));
				break;
			case 8:
				__asm__ __volatile__("mtc0 %0, $8, 3":: "r" (rt));
				break;
			case 9:
				__asm__ __volatile__("mtc0 %0, $9, 3":: "r" (rt));
				break;
			case 10:
				__asm__ __volatile__("mtc0 %0, $19, 3":: "r" (rt));
				break;
			case 11:
				__asm__ __volatile__("mtc0 %0, $11, 3":: "r" (rt));
				break;
			case 12:
				__asm__ __volatile__("mtc0 %0, $12, 3":: "r" (rt));
				break;
			case 13:
				__asm__ __volatile__("mtc0 %0, $13, 3":: "r" (rt));
				break;
			case 14:
				__asm__ __volatile__("mtc0 %0, $14, 3":: "r" (rt));
				break;
			case 15:
				__asm__ __volatile__("mtc0 %0, $15, 3":: "r" (rt));
				break;
			case 16:
				__asm__ __volatile__("mtc0 %0, $16, 3":: "r" (rt));
				break;
			case 17:
				__asm__ __volatile__("mtc0 %0, $17, 3":: "r" (rt));
				break;
			case 18:
				__asm__ __volatile__("mtc0 %0, $18, 3":: "r" (rt));
				break;
			case 19:
				__asm__ __volatile__("mtc0 %0, $19, 3":: "r" (rt));
				break;
			case 20:
				__asm__ __volatile__("mtc0 %0, $20, 3":: "r" (rt));
				break;
			case 21:
				__asm__ __volatile__("mtc0 %0, $21, 3":: "r" (rt));
				break;
			case 22:
				__asm__ __volatile__("mtc0 %0, $22, 3":: "r" (rt));
				break;
			case 23:
				__asm__ __volatile__("mtc0 %0, $23, 3":: "r" (rt));
				break;
			case 24:
				__asm__ __volatile__("mtc0 %0, $24, 3":: "r" (rt));
				break;
			case 25:
				__asm__ __volatile__("mtc0 %0, $25, 3":: "r" (rt));
				break;
			case 26:
				__asm__ __volatile__("mtc0 %0, $26, 3":: "r" (rt));
				break;
			case 27:
				__asm__ __volatile__("mtc0 %0, $27, 3":: "r" (rt));
				break;
			case 28:
				__asm__ __volatile__("mtc0 %0, $28, 3":: "r" (rt));
				break;
			case 29:
				__asm__ __volatile__("mtc0 %0, $29, 3":: "r" (rt));
				break;
			case 30:
				__asm__ __volatile__("mtc0 %0, $30, 3":: "r" (rt));
				break;
			case 31:
				__asm__ __volatile__("mtc0 %0, $31, 3":: "r" (rt));
				break;
			}
			break;
		}
		case 4:
		{
			switch (rd) {
			case 0:
				__asm__ __volatile__("mtc0 %0, $0, 4":: "r" (rt));
				break;
			case 1:
				__asm__ __volatile__("mtc0 %0, $1, 4":: "r" (rt));
				break;
			case 2:
				__asm__ __volatile__("mtc0 %0, $2, 4":: "r" (rt));
				break;
			case 3:
				__asm__ __volatile__("mtc0 %0, $3, 4":: "r" (rt));
				break;
			case 4:
				__asm__ __volatile__("mtc0 %0, $4, 4":: "r" (rt));
				break;
			case 5:
				__asm__ __volatile__("mtc0 %0, $5, 4":: "r" (rt));
				break;
			case 6:
				__asm__ __volatile__("mtc0 %0, $6, 4":: "r" (rt));
				break;
			case 7:
				__asm__ __volatile__("mtc0 %0, $7, 4":: "r" (rt));
				break;
			case 8:
				__asm__ __volatile__("mtc0 %0, $8, 4":: "r" (rt));
				break;
			case 9:
				__asm__ __volatile__("mtc0 %0, $9, 4":: "r" (rt));
				break;
			case 10:
				__asm__ __volatile__("mtc0 %0, $19, 4":: "r" (rt));
				break;
			case 11:
				__asm__ __volatile__("mtc0 %0, $11, 4":: "r" (rt));
				break;
			case 12:
				__asm__ __volatile__("mtc0 %0, $12, 4":: "r" (rt));
				break;
			case 13:
				__asm__ __volatile__("mtc0 %0, $13, 4":: "r" (rt));
				break;
			case 14:
				__asm__ __volatile__("mtc0 %0, $14, 4":: "r" (rt));
				break;
			case 15:
				__asm__ __volatile__("mtc0 %0, $15, 4":: "r" (rt));
				break;
			case 16:
				__asm__ __volatile__("mtc0 %0, $16, 4":: "r" (rt));
				break;
			case 17:
				__asm__ __volatile__("mtc0 %0, $17, 4":: "r" (rt));
				break;
			case 18:
				__asm__ __volatile__("mtc0 %0, $18, 4":: "r" (rt));
				break;
			case 19:
				__asm__ __volatile__("mtc0 %0, $19, 4":: "r" (rt));
				break;
			case 20:
				__asm__ __volatile__("mtc0 %0, $20, 4":: "r" (rt));
				break;
			case 21:
				__asm__ __volatile__("mtc0 %0, $21, 4":: "r" (rt));
				break;
			case 22:
				__asm__ __volatile__("mtc0 %0, $22, 4":: "r" (rt));
				break;
			case 23:
				__asm__ __volatile__("mtc0 %0, $23, 4":: "r" (rt));
				break;
			case 24:
				__asm__ __volatile__("mtc0 %0, $24, 4":: "r" (rt));
				break;
			case 25:
				__asm__ __volatile__("mtc0 %0, $25, 4":: "r" (rt));
				break;
			case 26:
				__asm__ __volatile__("mtc0 %0, $26, 4":: "r" (rt));
				break;
			case 27:
				__asm__ __volatile__("mtc0 %0, $27, 4":: "r" (rt));
				break;
			case 28:
				__asm__ __volatile__("mtc0 %0, $28, 4":: "r" (rt));
				break;
			case 29:
				__asm__ __volatile__("mtc0 %0, $29, 4":: "r" (rt));
				break;
			case 30:
				__asm__ __volatile__("mtc0 %0, $30, 4":: "r" (rt));
				break;
			case 31:
				__asm__ __volatile__("mtc0 %0, $31, 4":: "r" (rt));
				break;
			}
			break;
		}
		case 5:
		{
			switch (rd) {
			case 0:
				__asm__ __volatile__("mtc0 %0, $0, 5":: "r" (rt));
				break;
			case 1:
				__asm__ __volatile__("mtc0 %0, $1, 5":: "r" (rt));
				break;
			case 2:
				__asm__ __volatile__("mtc0 %0, $2, 5":: "r" (rt));
				break;
			case 3:
				__asm__ __volatile__("mtc0 %0, $3, 5":: "r" (rt));
				break;
			case 4:
				__asm__ __volatile__("mtc0 %0, $4, 5":: "r" (rt));
				break;
			case 5:
				__asm__ __volatile__("mtc0 %0, $5, 5":: "r" (rt));
				break;
			case 6:
				__asm__ __volatile__("mtc0 %0, $6, 5":: "r" (rt));
				break;
			case 7:
				__asm__ __volatile__("mtc0 %0, $7, 5":: "r" (rt));
				break;
			case 8:
				__asm__ __volatile__("mtc0 %0, $8, 5":: "r" (rt));
				break;
			case 9:
				__asm__ __volatile__("mtc0 %0, $9, 5":: "r" (rt));
				break;
			case 10:
				__asm__ __volatile__("mtc0 %0, $19, 5":: "r" (rt));
				break;
			case 11:
				__asm__ __volatile__("mtc0 %0, $11, 5":: "r" (rt));
				break;
			case 12:
				__asm__ __volatile__("mtc0 %0, $12, 5":: "r" (rt));
				break;
			case 13:
				__asm__ __volatile__("mtc0 %0, $13, 5":: "r" (rt));
				break;
			case 14:
				__asm__ __volatile__("mtc0 %0, $14, 5":: "r" (rt));
				break;
			case 15:
				__asm__ __volatile__("mtc0 %0, $15, 5":: "r" (rt));
				break;
			case 16:
				__asm__ __volatile__("mtc0 %0, $16, 5":: "r" (rt));
				break;
			case 17:
				__asm__ __volatile__("mtc0 %0, $17, 5":: "r" (rt));
				break;
			case 18:
				__asm__ __volatile__("mtc0 %0, $18, 5":: "r" (rt));
				break;
			case 19:
				__asm__ __volatile__("mtc0 %0, $19, 5":: "r" (rt));
				break;
			case 20:
				__asm__ __volatile__("mtc0 %0, $20, 5":: "r" (rt));
				break;
			case 21:
				__asm__ __volatile__("mtc0 %0, $21, 5":: "r" (rt));
				break;
			case 22:
				__asm__ __volatile__("mtc0 %0, $22, 5":: "r" (rt));
				break;
			case 23:
				__asm__ __volatile__("mtc0 %0, $23, 5":: "r" (rt));
				break;
			case 24:
				__asm__ __volatile__("mtc0 %0, $24, 5":: "r" (rt));
				break;
			case 25:
				__asm__ __volatile__("mtc0 %0, $25, 5":: "r" (rt));
				break;
			case 26:
				__asm__ __volatile__("mtc0 %0, $26, 5":: "r" (rt));
				break;
			case 27:
				__asm__ __volatile__("mtc0 %0, $27, 5":: "r" (rt));
				break;
			case 28:
				__asm__ __volatile__("mtc0 %0, $28, 5":: "r" (rt));
				break;
			case 29:
				__asm__ __volatile__("mtc0 %0, $29, 5":: "r" (rt));
				break;
			case 30:
				__asm__ __volatile__("mtc0 %0, $30, 5":: "r" (rt));
				break;
			case 31:
				__asm__ __volatile__("mtc0 %0, $31, 5":: "r" (rt));
				break;
			}
			break;
		}
		case 6:
		{
			switch (rd) {
			case 0:
				__asm__ __volatile__("mtc0 %0, $0, 6":: "r" (rt));
				break;
			case 1:
				__asm__ __volatile__("mtc0 %0, $1, 6":: "r" (rt));
				break;
			case 2:
				__asm__ __volatile__("mtc0 %0, $2, 6":: "r" (rt));
				break;
			case 3:
				__asm__ __volatile__("mtc0 %0, $3, 6":: "r" (rt));
				break;
			case 4:
				__asm__ __volatile__("mtc0 %0, $4, 6":: "r" (rt));
				break;
			case 5:
				__asm__ __volatile__("mtc0 %0, $5, 6":: "r" (rt));
				break;
			case 6:
				__asm__ __volatile__("mtc0 %0, $6, 6":: "r" (rt));
				break;
			case 7:
				__asm__ __volatile__("mtc0 %0, $7, 6":: "r" (rt));
				break;
			case 8:
				__asm__ __volatile__("mtc0 %0, $8, 6":: "r" (rt));
				break;
			case 9:
				__asm__ __volatile__("mtc0 %0, $9, 6":: "r" (rt));
				break;
			case 10:
				__asm__ __volatile__("mtc0 %0, $19, 6":: "r" (rt));
				break;
			case 11:
				__asm__ __volatile__("mtc0 %0, $11, 6":: "r" (rt));
				break;
			case 12:
				__asm__ __volatile__("mtc0 %0, $12, 6":: "r" (rt));
				break;
			case 13:
				__asm__ __volatile__("mtc0 %0, $13, 6":: "r" (rt));
				break;
			case 14:
				__asm__ __volatile__("mtc0 %0, $14, 6":: "r" (rt));
				break;
			case 15:
				__asm__ __volatile__("mtc0 %0, $15, 6":: "r" (rt));
				break;
			case 16:
				__asm__ __volatile__("mtc0 %0, $16, 6":: "r" (rt));
				break;
			case 17:
				__asm__ __volatile__("mtc0 %0, $17, 6":: "r" (rt));
				break;
			case 18:
				__asm__ __volatile__("mtc0 %0, $18, 6":: "r" (rt));
				break;
			case 19:
				__asm__ __volatile__("mtc0 %0, $19, 6":: "r" (rt));
				break;
			case 20:
				__asm__ __volatile__("mtc0 %0, $20, 6":: "r" (rt));
				break;
			case 21:
				__asm__ __volatile__("mtc0 %0, $21, 6":: "r" (rt));
				break;
			case 22:
				__asm__ __volatile__("mtc0 %0, $22, 6":: "r" (rt));
				break;
			case 23:
				__asm__ __volatile__("mtc0 %0, $23, 6":: "r" (rt));
				break;
			case 24:
				__asm__ __volatile__("mtc0 %0, $24, 6":: "r" (rt));
				break;
			case 25:
				__asm__ __volatile__("mtc0 %0, $25, 6":: "r" (rt));
				break;
			case 26:
				__asm__ __volatile__("mtc0 %0, $26, 6":: "r" (rt));
				break;
			case 27:
				__asm__ __volatile__("mtc0 %0, $27, 6":: "r" (rt));
				break;
			case 28:
				__asm__ __volatile__("mtc0 %0, $28, 6":: "r" (rt));
				break;
			case 29:
				__asm__ __volatile__("mtc0 %0, $29, 6":: "r" (rt));
				break;
			case 30:
				__asm__ __volatile__("mtc0 %0, $30, 6":: "r" (rt));
				break;
			case 31:
				__asm__ __volatile__("mtc0 %0, $31, 6":: "r" (rt));
				break;
			}
			break;
		}
		case 7:
		{
			switch (rd) {
			case 0:
				__asm__ __volatile__("mtc0 %0, $0, 7":: "r" (rt));
				break;
			case 1:
				__asm__ __volatile__("mtc0 %0, $1, 7":: "r" (rt));
				break;
			case 2:
				__asm__ __volatile__("mtc0 %0, $2, 7":: "r" (rt));
				break;
			case 3:
				__asm__ __volatile__("mtc0 %0, $3, 7":: "r" (rt));
				break;
			case 4:
				__asm__ __volatile__("mtc0 %0, $4, 7":: "r" (rt));
				break;
			case 5:
				__asm__ __volatile__("mtc0 %0, $5, 7":: "r" (rt));
				break;
			case 6:
				__asm__ __volatile__("mtc0 %0, $6, 7":: "r" (rt));
				break;
			case 7:
				__asm__ __volatile__("mtc0 %0, $7, 7":: "r" (rt));
				break;
			case 8:
				__asm__ __volatile__("mtc0 %0, $8, 7":: "r" (rt));
				break;
			case 9:
				__asm__ __volatile__("mtc0 %0, $9, 7":: "r" (rt));
				break;
			case 10:
				__asm__ __volatile__("mtc0 %0, $19, 7":: "r" (rt));
				break;
			case 11:
				__asm__ __volatile__("mtc0 %0, $11, 7":: "r" (rt));
				break;
			case 12:
				__asm__ __volatile__("mtc0 %0, $12, 7":: "r" (rt));
				break;
			case 13:
				__asm__ __volatile__("mtc0 %0, $13, 7":: "r" (rt));
				break;
			case 14:
				__asm__ __volatile__("mtc0 %0, $14, 7":: "r" (rt));
				break;
			case 15:
				__asm__ __volatile__("mtc0 %0, $15, 7":: "r" (rt));
				break;
			case 16:
				__asm__ __volatile__("mtc0 %0, $16, 7":: "r" (rt));
				break;
			case 17:
				__asm__ __volatile__("mtc0 %0, $17, 7":: "r" (rt));
				break;
			case 18:
				__asm__ __volatile__("mtc0 %0, $18, 7":: "r" (rt));
				break;
			case 19:
				__asm__ __volatile__("mtc0 %0, $19, 7":: "r" (rt));
				break;
			case 20:
				__asm__ __volatile__("mtc0 %0, $20, 7":: "r" (rt));
				break;
			case 21:
				__asm__ __volatile__("mtc0 %0, $21, 7":: "r" (rt));
				break;
			case 22:
				__asm__ __volatile__("mtc0 %0, $22, 7":: "r" (rt));
				break;
			case 23:
				__asm__ __volatile__("mtc0 %0, $23, 7":: "r" (rt));
				break;
			case 24:
				__asm__ __volatile__("mtc0 %0, $24, 7":: "r" (rt));
				break;
			case 25:
				__asm__ __volatile__("mtc0 %0, $25, 7":: "r" (rt));
				break;
			case 26:
				__asm__ __volatile__("mtc0 %0, $26, 7":: "r" (rt));
				break;
			case 27:
				__asm__ __volatile__("mtc0 %0, $27, 7":: "r" (rt));
				break;
			case 28:
				__asm__ __volatile__("mtc0 %0, $28, 7":: "r" (rt));
				break;
			case 29:
				__asm__ __volatile__("mtc0 %0, $29, 7":: "r" (rt));
				break;
			case 30:
				__asm__ __volatile__("mtc0 %0, $30, 7":: "r" (rt));
				break;
			case 31:
				__asm__ __volatile__("mtc0 %0, $31, 7":: "r" (rt));
				break;
			}
			break;
		}
		}
	}
}

#endif /* __WCP0_H__ */
