/*
*********************************************************************************************************
*                                              uC/Probe
*
*                         (c) Copyright 2007-2009; Micrium, Inc.; Weston, FL
*
*               All rights reserved.  Protected by international copyright laws.
*               Knowledge of the source code may NOT be used to develop a similar product.
*               Please help us continue to provide the Embedded community with the finest
*               software available.  Your honesty is greatly appreciated.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*
*                                                uC/Probe
*                                            INTRODUCTION DEMO
*
*
* Filename      : probe_demo_intro.c
* Version       : V2.20
* Programmer(s) : FT
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/

#define    PROBE_DEMO_INTRO_MODULE
#include  <probe_demo_intro.h>


/*
*********************************************************************************************************
*                                            LOCAL DEFINES
*********************************************************************************************************
*/

#define  PROBE_DEMO_INTRO_LED_SEL_POLL_RATE_mS              10


/*
*********************************************************************************************************
*                                           LOCAL CONSTANTS
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                          LOCAL DATA TYPES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                            LOCAL TABLES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                       LOCAL GLOBAL VARIABLES
*********************************************************************************************************
*/

                                                                /* -------- GLOBAL VARIABLES TO BE MONITORED  ------- */
static  CPU_INT32U   ProbeDemoIntro_Dial;                       /* Test variable for the Dial component demo.         */

static  CPU_BOOLEAN  ProbeDemoIntro_LED_Sel;                    /* LEDs select value.                                 */
static  CPU_BOOLEAN  ProbeDemoIntro_LED1;                       /* LED 1 value                                        */
static  CPU_BOOLEAN  ProbeDemoIntro_LED2;                       /* LED 2 value                                        */
static  CPU_BOOLEAN  ProbeDemoIntro_LED3;                       /* LED 3 value                                        */
                                                                

static  CPU_INT32U   ProbeDemoIntro_PicIx;                      /* Test variable for the Picture component demo.      */

                                                                /* ----------- PROBE DEMO INTRO TASKS STACK  -------- */
                                                                /* LED 1 and 2 selection task.                        */
static  OS_STK       ProbeDemoIntro_TaskLED_Stk[PROBE_DEMO_INTRO_CFG_TASK_LED_STK_SIZE]; 


/*
*********************************************************************************************************
*                                      LOCAL FUNCTION PROTOTYPES
*********************************************************************************************************
*/

static  void  ProbeDemoIntro_TaskLED (void  *p_arg);


/*
*********************************************************************************************************
*                                     LOCAL CONFIGURATION ERRORS
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                             ProbeDemoIntro_Init()
*
* Description : Initialize the uC/Probe Introduction demo.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  ProbeDemoIntro_Init (void)
{
    CPU_INT08U  os_err;


    (void)&ProbeDemoIntro_Dial;                                 /* Avoid warning.                                     */
    (void)&ProbeDemoIntro_LED_Sel;
    (void)&ProbeDemoIntro_LED1;
    (void)&ProbeDemoIntro_LED2;
    (void)&ProbeDemoIntro_LED3;
    (void)&ProbeDemoIntro_PicIx;
    

#if (OS_TASK_CREATE_EXT_EN > 0)                                 /* ---------------- CREATE KSD TASKS ---------------- */
#if (OS_STK_GROWTH == 1)
    os_err = OSTaskCreateExt((void (*)(void *)) ProbeDemoIntro_TaskLED,
                             (void           *) 0,
                             (OS_STK         *)&ProbeDemoIntro_TaskLED_Stk[PROBE_DEMO_INTRO_CFG_TASK_LED_STK_SIZE - 1],   
                             (INT8U           ) PROBE_DEMO_INTRO_CFG_TASK_LED_PRIO,                            
                             (INT16U          ) PROBE_DEMO_INTRO_CFG_TASK_LED_PRIO,                              
                             (OS_STK         *)&ProbeDemoIntro_TaskLED_Stk[0],                                
                             (INT32U          ) PROBE_DEMO_INTRO_CFG_TASK_LED_STK_SIZE,                      
                             (void           *) 0,                                          
                             (INT16U          )(OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR));
    
#else
    os_err = OSTaskCreateExt((void (*)(void *)) ProbeDemoIntro_TaskLED,
                             (void           *) 0,
                             (OS_STK         *)&ProbeDemoIntro_TaskLED_Stk[0],                                   
                             (INT8U           ) PROBE_DEMO_INTRO_CFG_TASK_LED_PRIO,                              
                             (INT16U          ) PROBE_DEMO_INTRO_CFG_TASK_LED_PRIO,                                
                             (OS_STK         *)&ProbeDemoIntro_TaskLED_Stk[PROBE_DEMO_INTRO_CFG_TASK_LED_STK_SIZE - 1],    
                             (INT32U          ) PROBE_DEMO_INTRO_CFG_TASK_LED_STK_SIZE,                          
                             (void           *) 0,                                              
                             (INT16U          )(OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR));

#endif
#else
#if (OS_STK_GROWTH == 1)
    os_err = OSTaskCreate((void (*)(void *)) ProbeDemoIntro_TaskLED,
                          (void           *) 0,
                          (OS_STK         *)&ProbeDemoIntro_TaskLED_Stk[PROBE_DEMO_INTRO_CFG_TASK_LED_STK_SIZE - 1],
                          (INT8U           ) PROBE_DEMO_INTRO_CFG_TASK_LED_PRIO);


#else
    os_err = OSTaskCreate((void (*)(void *)) ProbeDemoIntro_TaskLED,
                          (void           *) 0,
                          (OS_STK         *)&ProbeDemoIntro_TaskLED_Stk[0],
                          (INT8U           ) PROBE_DEMO_INTRO_CFG_TASK_LED_PRIO);
#endif
#endif
    

#if (OS_VERSION < 287)
#if (OS_TASK_NAME_SIZE > 17)
    OSTaskNameSet(PROBE_DEMO_INTRO_CFG_TASK_LED_PRIO, (CPU_INT08U *)"Probe Demo Intro", &os_err);
#endif
#else
#if (OS_TASK_NAME_EN > 0)
    OSTaskNameSet(PROBE_DEMO_INTRO_CFG_TASK_LED_PRIO, (CPU_INT08U *)"Probe Demo Intro", &os_err);
#endif
#endif
    
}


/*
*********************************************************************************************************
*                                         ProbeDemoIntro_TaskLED()
*
* Description : Monitors the ProbeDemoIntro_LED_Sel variable
*
* Argument(s) : p_arg       Pointer to task initialization argument.
*
* Return(s)   : none.
*
* Caller(s)   : This is a task.
*
* Note(s)     : (1) If ProbeDemoIntro_LED_Sel == 0 then
*                   (a) ProbeDemoIntro_LED1 is turned OFF.
*                   (b) ProbeDemoIntro_LED2 is turned ON.
*
*               (2) If ProbeDemoIntro_LED_Sel != 0 then
*                   (a) ProbeDemoIntro_LED1 is turned ON.
*                   (b) ProbeDemoIntro_LED2 is turned FF.
*
*               (3) Virtual LED3 toggled at 1 Hz.
*********************************************************************************************************
*/

static  void  ProbeDemoIntro_TaskLED (void *p_arg)
{
    CPU_INT32U  ms_ctr;


    ms_ctr              = 0;
    ProbeDemoIntro_LED1 = DEF_OFF;
    ProbeDemoIntro_LED2 = DEF_OFF;
    ProbeDemoIntro_LED3 = DEF_OFF;

    while(DEF_TRUE) {
        if(ProbeDemoIntro_LED_Sel == DEF_OFF) {
            ProbeDemoIntro_LED1 = DEF_OFF;
            ProbeDemoIntro_LED2 = DEF_ON;
        } else {
            ProbeDemoIntro_LED1 = DEF_ON;
            ProbeDemoIntro_LED2 = DEF_OFF;
        }

        if (ms_ctr > (DEF_TIME_NBR_mS_PER_SEC / PROBE_DEMO_INTRO_LED_SEL_POLL_RATE_mS)) {
            if (ProbeDemoIntro_LED3 == DEF_OFF) {
               ProbeDemoIntro_LED3 = DEF_ON;
            } else {
               ProbeDemoIntro_LED3 = DEF_OFF;
            }
            ms_ctr = 0;
        } else {
            ms_ctr++;
        }

        OSTimeDlyHMSM(0, 0, 0, PROBE_DEMO_INTRO_LED_SEL_POLL_RATE_mS);
    }
}
