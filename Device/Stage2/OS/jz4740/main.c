#include "includes.h"
#include <stdio.h>


/* ********************************************************************* */
/* Global definitions */


/* ********************************************************************* */
/* File local definitions */
//#define  TASK_START_PRIO 12
#define  TASK_STK_SIZE   1024                      /* Size of each task's stacks (# of WORDs) */
#define  NO_TASKS        1                      /* Number of identical tasks */

OS_STK   TaskStk[NO_TASKS][TASK_STK_SIZE];      /* Tasks stacks */
OS_STK   TaskStartStk[TASK_STK_SIZE];
char     TaskData[NO_TASKS];                    /* Parameters to pass to each task */


void TaskStart (void *data)
{
        U8 i;
        char key;

        data = data;                            /* Prevent compiler warning */
        JZ_StartTicker(OS_TICKS_PER_SEC);	/* os_cfg.h */
        printf("\n USB Boot Device Software!");
	printf("\n Waiting for host command!");
	OSStatInit();
	while(1)
	{	
		//printf(" OSTaskCtr:%d", OSTaskCtr);    /* Display #tasks running */
		//printf(" OSCPUUsage:%d", OSCPUUsage);   /* Display CPU usage in % */
		//printf(" OSCtxSwCt:%d\n", OSCtxSwCtr); /* Display #context switches per second */
		//OSCtxSwCtr = 0;
		//printf("\nI am still alive!");
		OSTimeDlyHMSM(0, 0, 5, 0);     /* Wait one second */
	}	
        //OSStatInit();                           /* Initialize uC/OS-II's statistics */
}


/* ********************************************************************* */
/* Global functions */

void APP_vMain (void)
{
	
        OSTaskCreate(TaskStart, (void *)0, (void *)&TaskStartStk[TASK_STK_SIZE - 1], 1);
	udc_init();
        OSStart();                              /* Start multitasking */
	while(1);
}


/* ********************************************************************* */
