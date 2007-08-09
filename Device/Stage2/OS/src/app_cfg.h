#ifndef APP_CFG_H
#define APP_CFG_H
/* 
********************************************************************************************************* 
*                                      TASK PRIORITIES 
********************************************************************************************************* 
*/

#define  OS_TASK_TMR_PRIO     8
#define  TASK_START_PRIO      10
#define  TASK_1_PRIO          11
#define  TASK_CAPTURE_PRIO    12
#define  HTTP_PRIO            21
#define  TELNET_PRIO          22
#define  TFTP_PRIO            23

#define  TASK_START_ID        0      /* Application tasks IDs                         */
#define  TASK_1_ID            1
#define  TASK_CAPTURE_ID      2
/* 
********************************************************************************************************* 
*                                      TASK STACK SIZES 
********************************************************************************************************* 
*/
    
#define APP_TASK_START_STK_SIZE   1024   /* Size of each task's stacks (# of WORDs) */
#define APP_TASK_TASK1_STK_SIZE   200
#define APP_TASK_CAPTURE_STK_SIZE 200
#define TRUE                      1
#endif
