/*
*********************************************************************************************************
*                                              EXAMPLE CODE
*
*                          (c) Copyright 2003-2007; Micrium, Inc.; Weston, FL
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
*                                            EXAMPLE CODE
*
*                           NXP LPC1768 ON THE IAR LPC1768-SK KICKSTART KIT
*
* Filename      : app.c
* Version       : V1.00
* Programmer(s) : FT
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                             INCLUDE FILES
*********************************************************************************************************
*/

#include <includes.h>

/*
*********************************************************************************************************
*                                            LOCAL DEFINES
*********************************************************************************************************
*/

                                                               /* Application Colors 12-bits pallete                         */
#define  APP_COLOR_WHITE                          0xFFF
#define  APP_COLOR_BLACK                          0x000
#define  APP_COLOR_BLUE                           0x00A
#define  APP_COLOR_RED                            0xA00
#define  APP_COLOR_GREEN                          0x0F0
#define  APP_COLOR_YELLOW                         0xFF0
#define  APP_COLOR_ORANGE                         0xFA0

#define  APP_LCD_SCR_SIGN_ON                          1
#define  APP_LCD_SCR_OS_STAT                          2
#define  APP_LCD_SCR_TASK_INFO                        3
#define  APP_LCD_SCR_BOARD_INFO                       4

#define  APP_LCD_SCR_FIRST                  APP_LCD_SCR_SIGN_ON
#define  APP_LCD_SCR_LAST                   APP_LCD_SCR_BOARD_INFO

#define  APP_LCD_PAGE_MAX                             5        /* Max page per screen                                        */
#define  APP_LCD_PAGE_MIN                             1        /* Min page per screen                                        */

/*
*********************************************************************************************************
*                                       LOCAL GLOBAL VARIABLES
*********************************************************************************************************
*/

                                                                /* ----------------- APPLICATION GLOBALS ------------------ */
                                                                /* -------- uC/OS-II APPLICATION TASK STACKS -------------- */
static  OS_STK         App_TaskStartStk[APP_CFG_TASK_START_STK_SIZE];


#if (APP_CFG_LCD_EN == DEF_ENABLED)
static  OS_STK         App_TaskJoyStk[APP_CFG_TASK_JOY_STK_SIZE];
static  OS_STK         App_TaskLCDStk[APP_CFG_TASK_LCD_STK_SIZE];
#endif
                                                                /* ---------- uC/OS-II APPLICATION EVENTS ----------------- */
#if (APP_CFG_LCD_EN == DEF_ENABLED)
static  OS_EVENT      *App_LCDMbox1;
static  OS_EVENT      *App_LCDMbox2;
#endif

#if (APP_CFG_LCD_EN == DEF_ENABLED)
extern  FontType_t     Terminal_6_8_6;
extern  FontType_t     Terminal_9_12_6;
extern  FontType_t     Terminal_18_24_12;
#endif
                                                                /* -------------- uC/PROBE RELATED GLOBALS ---------------- */
/*
*********************************************************************************************************
*                                      LOCAL FUNCTION PROTOTYPES
*********************************************************************************************************
*/

static  void  App_EventCreate        (void);
static  void  App_TaskCreate         (void);
static  void  App_TaskStart          (void       *p_arg);

#if (APP_CFG_LCD_EN == DEF_ENABLED)
static  void  App_TaskLCD            (void       *p_arg);
static  void  App_TaskJoy            (void       *p_arg);

static  void  App_DispScr_SignOn     (void);
static  void  App_DispScr_OSStat     (void);
static  void  App_DispScr_OSTaskInfo (CPU_INT08U  page);
static  void  App_DispScr_BoardInfo  (void);
#endif


/*
*********************************************************************************************************
*                                                main()
*
* Description : This is the standard entry point for C code.  It is assumed that your code will call
*               main() once you have performed all necessary initialization.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : This the main standard entry point.
*
* Note(s)     : none.
*********************************************************************************************************
*/

int  main (void)
{
#if (CPU_CFG_NAME_EN == DEF_ENABLED)
    CPU_ERR     cpu_err;
#endif    
    
#if (OS_TASK_NAME_EN > 0u)    
    CPU_INT08U  err;
#endif

    CPU_Init();

#if (CPU_CFG_NAME_EN == DEF_ENABLED) 
    CPU_NameSet((CPU_CHAR *)"NXP LPC1768",
                (CPU_ERR  *)&cpu_err);
    (void)&cpu_err;
#endif
             
    BSP_IntDisAll();                                            /* Disable all interrupts until we are ready to accept them */

    OSInit();                                                   /* Initialize "uC/OS-II, The Real-Time Kernel"              */

    OSTaskCreateExt((void (*)(void *)) App_TaskStart,           /* Create the start task                                    */
                    (void           *) 0,
                    (OS_STK         *)&App_TaskStartStk[APP_CFG_TASK_START_STK_SIZE - 1],
                    (INT8U           ) APP_CFG_TASK_START_PRIO,
                    (INT16U          ) APP_CFG_TASK_START_PRIO,
                    (OS_STK         *)&App_TaskStartStk[0],
                    (INT32U          ) APP_CFG_TASK_START_STK_SIZE,
                    (void           *) 0,
                    (INT16U          )(OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR));

#if (OS_TASK_NAME_EN > 0u)
    OSTaskNameSet(APP_CFG_TASK_START_PRIO, "Start", &err);
#endif

    OSStart();                                                  /* Start multitasking (i.e. give control to uC/OS-II)       */
}

/*
*********************************************************************************************************
*                                          App_TaskStart()
*
* Description : This is an example of a startup task.  As mentioned in the book's text, you MUST
*               initialize the ticker only once multitasking has started.
*
* Argument(s) : p_arg   is the argument passed to 'App_TaskStart()' by 'OSTaskCreate()'.
*
* Return(s)   : none.
*
* Caller(s)   : This is a task.
*
* Notes       : (1) The first line of code is used to prevent a compiler warning because 'p_arg' is not
*                   used.  The compiler should not generate any code for this statement.
*********************************************************************************************************
*/

static  void  App_TaskStart (void *p_arg)
{
    
    (void)p_arg;                                                /* See Note #1                                          */

    BSP_Init();                                                 /* Initialize BSP functions                             */

    BSP_OS_TmrTickInit(OS_TICKS_PER_SEC);                       /* Initialize the uC/OS-II ticker                       */

#if (OS_TASK_STAT_EN > 0)
    OSStatInit();                                               /* Determine CPU capacity                               */
#endif

    BSP_SerInit(115200);                                        /* Initialize Serial port for tracing                   */
    APP_TRACE_INFO(("\n\n"));
    
#if (APP_CFG_PROBE_COM_EN       == DEF_ENABLED) || \
    (APP_CFG_PROBE_OS_PLUGIN_EN == DEF_ENABLED)
    App_ProbeInit();    
#endif

    APP_TRACE_INFO(("Creating Application Events...\n\r"));    
    App_EventCreate();                                          /* Create application events                            */

    APP_TRACE_INFO(("Creating Application Tasks...\n\r"));
    App_TaskCreate();                                           /* Create application tasks                             */

    BSP_LED_Off(0);

    while (DEF_TRUE) {                                          /* Task body, always written as an infinite loop.       */
        BSP_LED_Toggle(0);
        OSTimeDlyHMSM(0, 0, 0, 100);
    }
}

/*
*********************************************************************************************************
*                                      App_EventCreate
*
* Description:  Creates the application events.
*
* Argument(s) :  none.
*
* Return(s)   :  none.
*
* Caller(s)   :  App_TaskStart().
*
* Note(s)     :  none.
*********************************************************************************************************
*/

static  void  App_EventCreate (void)
{
#if (OS_TASK_NAME_EN > 0u)    
    CPU_INT08U  os_err;
#endif    

    
#if(APP_CFG_LCD_EN == DEF_ENABLED)     
    App_LCDMbox1   = OSMboxCreate((void *)0);                   /* Create MBOX 1, 2 for communication between App_TaskJoy()    */
    App_LCDMbox2   = OSMboxCreate((void *)0);                   /* ... and App_TaskLCD()                                      */

#if (OS_TASK_NAME_EN > 0u)     
    OSEventNameSet(App_LCDMbox1, (INT8U *)"LCD Mbox 1", &os_err);
    OSEventNameSet(App_LCDMbox1, (INT8U *)"LCD Mbox 2", &os_err);
#endif    
#endif    

}
/*
*********************************************************************************************************
*                                      App_TaskCreate()
*
* Description :  This function creates the application tasks.
*
* Argument(s) :  none.
*
* Return(s)   :  none.
*
* Caller(s)   :  App_TaskStart().
*
* Note(s)     :  none.
*********************************************************************************************************
*/

static  void  App_TaskCreate (void)
{
#if (OS_TASK_NAME_EN > 0u)         
    CPU_INT08U      err;
#endif
    
#if (APP_CFG_LCD_EN == DEF_ENABLED)
    OSTaskCreateExt((void (*)(void *)) App_TaskLCD,
                    (void           *) 0,
                    (OS_STK         *)&App_TaskLCDStk[APP_CFG_TASK_LCD_STK_SIZE - 1],
                    (INT8U           ) APP_CFG_TASK_LCD_PRIO,
                    (INT16U          ) APP_CFG_TASK_LCD_PRIO,
                    (OS_STK         *)&App_TaskLCDStk[0],
                    (INT32U          ) APP_CFG_TASK_LCD_STK_SIZE,
                    (void           *) 0,
                    (INT8U           )(OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR));

#if (OS_TASK_NAME_EN > 0u)
    OSTaskNameSet(APP_CFG_TASK_LCD_PRIO, "LCD Disp", &err);
#endif

    OSTaskCreateExt((void (*)(void *)) App_TaskJoy,
                    (void           *) 0,
                    (OS_STK         *)&App_TaskJoyStk[APP_CFG_TASK_JOY_STK_SIZE - 1],
                    (INT8U           ) APP_CFG_TASK_JOY_PRIO,
                    (INT16U          ) APP_CFG_TASK_JOY_PRIO,
                    (OS_STK         *)&App_TaskJoyStk[0],
                    (INT32U          ) APP_CFG_TASK_JOY_STK_SIZE,
                    (void           *) 0,
                    (INT8U           )(OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR));

#if (OS_TASK_NAME_EN > 0u)
    OSTaskNameSet(APP_CFG_TASK_JOY_PRIO, "Joystick", &err);
#endif
#endif
    
}


/*
*********************************************************************************************************
*                                         App_TaskJoy()
*
* Description : Monitors the stat of the Joystick and passes messages to App_TaskLCD()
*
* Argument(s) : p_arg   is the argument passed to 'App_TaskJoy()' by 'OSTaskCreate()'.
*
* Return(s)  : none.
*
* Caller(s)  : This is a task.
*
* Note(s)    : none.
*********************************************************************************************************
*/

#if (APP_CFG_LCD_EN     == DEF_ENABLED)
static  void  App_TaskJoy (void *p_arg)
{
    CPU_BOOLEAN  joy_pos;
    CPU_BOOLEAN  joy_pos_prev;
    CPU_INT08U   lcd_scr_msg;
    CPU_INT08U   lcd_page_msg;
    

    (void)p_arg;

    joy_pos_prev = BSP_JOY_NONE;
    lcd_scr_msg  = APP_LCD_SCR_FIRST;
    lcd_page_msg = APP_LCD_PAGE_MIN;
     

    while (DEF_TRUE) {
        joy_pos = BSP_Joy_GetPos();

        if (joy_pos == BSP_JOY_RIGHT && joy_pos_prev != BSP_JOY_RIGHT) {           
            if (lcd_scr_msg == APP_LCD_SCR_LAST) {
                lcd_scr_msg = APP_LCD_SCR_FIRST;
            } else {
                lcd_scr_msg++;   
            }
            OSMboxPost(App_LCDMbox1, (void *)lcd_scr_msg);
        }

        if (joy_pos == BSP_JOY_LEFT && joy_pos_prev != BSP_JOY_LEFT) {           
            if (lcd_scr_msg == APP_LCD_SCR_FIRST) {
                lcd_scr_msg = APP_LCD_SCR_LAST;
            } else {
                lcd_scr_msg--;   
            }
            OSMboxPost(App_LCDMbox1, (void *)lcd_scr_msg);
        }

        if (joy_pos == BSP_JOY_UP && joy_pos_prev != BSP_JOY_UP) {           
            if (lcd_page_msg == APP_LCD_PAGE_MAX) {
                lcd_page_msg = APP_LCD_PAGE_MAX;
            } else {
                lcd_page_msg++;   
            }
            OSMboxPost(App_LCDMbox2, (void *)lcd_page_msg);
            }

        if (joy_pos == BSP_JOY_DOWN && joy_pos_prev != BSP_JOY_DOWN) {           
            if (lcd_page_msg == APP_LCD_PAGE_MIN) {
                lcd_page_msg = APP_LCD_PAGE_MIN;
            } else {
                lcd_page_msg--;   
            }
            OSMboxPost(App_LCDMbox2, (void *)lcd_page_msg);
        }
                
        joy_pos_prev = joy_pos;

        OSTimeDlyHMSM(0, 0, 0, 150);
    }
}
#endif

/*
*********************************************************************************************************
*                                         App_TaskLCD()
*
* Description : This task updates the LCD screen based on messages passed by App_TaskJoy().
*
* Arguments   : p_arg   is the argument passed to 'App_TaskLCD()' by 'OSTaskCreate()'.
*
* Return(s)  : none.
*
* Caller(s)  : This is a task.
*
* Note(s)    : none.
*********************************************************************************************************
*/

#if (APP_CFG_LCD_EN     == DEF_ENABLED)
static  void  App_TaskLCD (void *p_arg)
{
    CPU_INT08U  *p_msg;
    CPU_INT08U   os_err;
    CPU_INT32U   nstate;
    CPU_INT32U   pstate;
    CPU_INT08U   page;


    (void)p_arg;
    
  
    GLCD_PowerUpInit((pInt8U)0);
    GLCD_Backlight(BACKLIGHT_ON);
    GLCD_TextSetPos(0,0);
 
    nstate   = APP_LCD_SCR_FIRST;
    pstate   = APP_LCD_SCR_FIRST;
    page     = 1;

    
    while (DEF_TRUE) {
        p_msg = (CPU_INT08U *)(OSMboxPend(App_LCDMbox1, OS_TICKS_PER_SEC / 4, &os_err));
        if (os_err == OS_NO_ERR) {
            nstate = (CPU_INT32U)p_msg;
        }

        if (nstate != pstate) {    
            GLCD_print("\f");
            pstate  = nstate;
        }

        p_msg = (CPU_INT08U *)(OSMboxPend(App_LCDMbox2, OS_TICKS_PER_SEC / 4, &os_err));
        if (os_err == OS_NO_ERR) {
            GLCD_print("\f");
            page  = (CPU_INT32U)p_msg;
        }
        
         switch (nstate) {
            case APP_LCD_SCR_BOARD_INFO:
                 App_DispScr_BoardInfo();
                 break;

            case APP_LCD_SCR_OS_STAT:
                 App_DispScr_OSStat();
                 break;

            case APP_LCD_SCR_TASK_INFO:
                 App_DispScr_OSTaskInfo(page - 1);
                 break;

            case APP_LCD_SCR_SIGN_ON:
            default:
                 App_DispScr_SignOn();            
                 break;
        }
        OSTimeDlyHMSM(0, 0, 0, 150);
    }
}
#endif
/*
*********************************************************************************************************
*                                         App_DispScr_SignOn()
*                                         App_DispScr_OSStat()
*                                       App_DispScr_OSTaskInfo()
*                                       App_DispScr_BoardInfo()
*
* Descrition:  These functions each display one of the screens used in the demonstration.
*
* Arguments :  none.
*
* Returns   :  none.
*
* Caller(s) : App_TaskLCD()
*
* Note(s)   : none
*********************************************************************************************************
*/

#if (APP_CFG_LCD_EN == DEF_ENABLED)
static  void App_DispScr_SignOn (void)
{    
    GLCD_TextSetPos(0 , 1);

    GLCD_SetFont(&Terminal_9_12_6, APP_COLOR_ORANGE, APP_COLOR_WHITE);
    GLCD_print(" Micrium uC/OS-II   \n\n\r");    
    
    GLCD_SetFont(&Terminal_9_12_6, APP_COLOR_RED, APP_COLOR_WHITE);
    GLCD_print(" LPC1768-SK         \n\r");           
    GLCD_print(" Cortex-M3          \n\n\n\n\r");          
        
    GLCD_SetFont(&Terminal_6_8_6, APP_COLOR_RED, APP_COLOR_WHITE);
    GLCD_print(" OS Version: ");    
    GLCD_SetFont(&Terminal_6_8_6, APP_COLOR_BLUE, APP_COLOR_WHITE);    
    GLCD_print("%.2f \n\r", (CPU_FP32)OSVersion() / 100.0);

    GLCD_SetFont(&Terminal_6_8_6, APP_COLOR_RED, APP_COLOR_WHITE);
    GLCD_print(" Tick Rate : ");
    GLCD_SetFont(&Terminal_6_8_6, APP_COLOR_BLUE, APP_COLOR_WHITE);        
    GLCD_print("%d \n\r",(CPU_INT32U)OS_TICKS_PER_SEC);         
}

static  void App_DispScr_OSStat (void)
{
    
    GLCD_TextSetPos(0 , 1);

    GLCD_SetFont(&Terminal_9_12_6, APP_COLOR_ORANGE, APP_COLOR_WHITE);
    GLCD_print(" uC/OS-II Stat  \n\n\n\r");    

    GLCD_SetFont(&Terminal_6_8_6, APP_COLOR_RED, APP_COLOR_WHITE);
    GLCD_print("#Ticks   : ");        
    GLCD_SetFont(&Terminal_6_8_6, APP_COLOR_BLUE, APP_COLOR_WHITE);    
    GLCD_print("%d \n\r",(CPU_INT32U)OSTime); 
    
    GLCD_SetFont(&Terminal_6_8_6, APP_COLOR_RED, APP_COLOR_WHITE);
    GLCD_print("#CtxSw   : ");        
    GLCD_SetFont(&Terminal_6_8_6, APP_COLOR_BLUE, APP_COLOR_WHITE);    
    GLCD_print("%d \n\r",(CPU_INT32U)OSCtxSwCtr); 
    
    GLCD_SetFont(&Terminal_6_8_6, APP_COLOR_RED, APP_COLOR_WHITE);
    GLCD_print("#Tasks   : ");        
    GLCD_SetFont(&Terminal_6_8_6, APP_COLOR_BLUE, APP_COLOR_WHITE);    
    GLCD_print("%d \n\r",(CPU_INT32U)OS_MAX_TASKS); 
    
    GLCD_SetFont(&Terminal_6_8_6, APP_COLOR_RED, APP_COLOR_WHITE);
    GLCD_print("CPU Usage: ");        
    GLCD_SetFont(&Terminal_6_8_6, APP_COLOR_BLUE, APP_COLOR_WHITE);    
    GLCD_print("%d \n\r",(CPU_INT32U)OSCPUUsage);     
}

static  void App_DispScr_OSTaskInfo (CPU_INT08U page)
{
    OS_TCB     *p_tcb;
    CPU_INT32U  prio;
    CPU_INT08U  nbr_page;
    CPU_INT08U  i;
    CPU_INT08U  j;
    CPU_CHAR    nbr_str[4];

    
    GLCD_SetFont(&Terminal_6_8_6, APP_COLOR_ORANGE, APP_COLOR_WHITE);
    GLCD_TextSetPos(0 , 1);
    GLCD_print("uC/OS-II Task Info  \n\r");    

    GLCD_SetFont(&Terminal_6_8_6, APP_COLOR_BLACK, APP_COLOR_WHITE);
    GLCD_print("Prio | Task Name \n\r");        

    GLCD_SetFont(&Terminal_6_8_6, APP_COLOR_BLUE, APP_COLOR_WHITE);    
    GLCD_print("\n\r");    

    p_tcb      = &OSTCBTbl[0];
    nbr_page   = ((OSTaskCtr - 1u) / 6u);
    
    i          = 0u;
    j          = 0u;

    if (page > nbr_page) {
        page = nbr_page;
    }
    
    while (p_tcb != NULL) {
        if (i > page * 6) {
            if (j >= 6) {
                break;
            }                    
            prio = p_tcb->OSTCBPrio;
            Str_Copy(&nbr_str[0], "     |");     
            
            Str_FmtNbr_Int32U ((CPU_INT32U  )prio,
                               (CPU_INT08U  )4,
                               (CPU_INT08U  )10,
                               (CPU_CHAR    )0,
                               (CPU_BOOLEAN )DEF_NO,
                               (CPU_BOOLEAN )DEF_NO,
                               (CPU_CHAR   *)&nbr_str[0]);

            GLCD_SetFont(&Terminal_6_8_6, APP_COLOR_BLUE, APP_COLOR_WHITE);
            GLCD_print("%s", nbr_str); 
        
            GLCD_SetFont(&Terminal_6_8_6, APP_COLOR_RED, APP_COLOR_WHITE);
            GLCD_print("%s \n\r", p_tcb->OSTCBTaskName); 
            j++;
        }
        p_tcb = p_tcb->OSTCBPrev;        
        i++;
    }

    GLCD_print("\n\r"); 
    GLCD_print("Page # %d of %d \n\r", page + 1, nbr_page + 1);                 
    
    if (nbr_page > 1)
        if (page == 0 ) {        
            GLCD_print("Up->Next");      
        } else if (page == nbr_page){
            GLCD_print("Down->Last");          
        } else {
            GLCD_print("Up->Next.  Down->Last");              
        }
}

static  void  App_DispScr_BoardInfo (void)
{  
    GLCD_TextSetPos(0 , 1);

    GLCD_SetFont(&Terminal_9_12_6, APP_COLOR_ORANGE, APP_COLOR_WHITE);
    GLCD_print(" LPC1766-SK  \n\n\n\r");    
    
    GLCD_SetFont(&Terminal_6_8_6, APP_COLOR_RED, APP_COLOR_WHITE);
    GLCD_print("CPU Speed:  ");        
    GLCD_SetFont(&Terminal_6_8_6, APP_COLOR_BLUE, APP_COLOR_WHITE);    
    GLCD_print("%d Mhz \n\r", (CPU_INT32U)BSP_CPU_ClkFreq() / 1000000L);
        
    GLCD_SetFont(&Terminal_6_8_6, APP_COLOR_RED, APP_COLOR_WHITE);
    GLCD_print("PB1 State:  ");        

    GLCD_SetFont(&Terminal_6_8_6, APP_COLOR_BLUE, APP_COLOR_WHITE);    

    if (BSP_PB_GetStatus(1) == DEF_TRUE) {
        GLCD_print("ON \n\r");    
    } else {
        GLCD_print("OFF \n\r");    
    }
    
    GLCD_SetFont(&Terminal_6_8_6, APP_COLOR_RED, APP_COLOR_WHITE);
    GLCD_print("PB2 State:  ");        

    GLCD_SetFont(&Terminal_6_8_6, APP_COLOR_BLUE, APP_COLOR_WHITE);    

    if (BSP_PB_GetStatus(2) == DEF_TRUE) {
        GLCD_print("ON \n\r");    
    } else {
        GLCD_print("OFF \n\r");    
    }
}
#endif

