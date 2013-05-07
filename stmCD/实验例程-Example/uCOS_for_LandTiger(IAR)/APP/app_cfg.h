/*
*********************************************************************************************************
*                                              uC/OS-II
*                                        The Real-Time Kernel
*
*                          (c) Copyright 2004-2009; Micrium, Inc.; Weston, FL               
*
*               All rights reserved.  Protected by international copyright laws.
*
*               uC/OS-II is provided in source form for FREE evaluation, for educational
*               use or peaceful research.  If you plan on using uC/OS-II in a commercial    
*               product you need to contact Micrium to properly license its use in your     
*               product.  We provide ALL the source code for your convenience and to        
*               help you experience uC/OS-II.  The fact that the source code is provided
*               does NOT mean that you can use it without paying a licensing fee.
*
*               Knowledge of the source code may NOT be used to develop a similar product.
*
*               Please help us continue to provide the Embedded community with the finest
*               software available.  Your honesty is greatly appreciated.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*
*                                       APPLICATION CONFIGURATION
*
*                            NXP LPC 1768 ON THE IAR LPC1768-SK KICKSTART KIT
*
*
* Filename      : app_cfg.h
* Version       : V1.00
* Programmer(s) : FT
*********************************************************************************************************
*/

#ifndef  APP_CFG_MODULE_PRESENT
#define  APP_CFG_MODULE_PRESENT


/*
*********************************************************************************************************
*                                       ADDITIONAL uC/MODULE ENABLES
*
* Note(s)  (1) The following #define's enables or disables the uC/modules

*              (a) APP_CFG_PROBE_OS_PLUGIN_EN   Enables the uC/OS-II plugin in uC/Probe
*
*              (b) APP_CFG_PROBE_COM_EN         Enables communication in uC/Probe 
*                                               Look at the probe_com_cfg.h file to see all the available 
*                                               comunication methods.
* 
*              (c) APP_CFG_PROBE_DEMO_INTRO_EN  Enables The introductory demo for uC/Probe
* 
*              (d) APP_CFG_LCD_EN               Enables the Graphical Color LCD functionality.
*********************************************************************************************************
*/

#define  APP_CFG_PROBE_OS_PLUGIN_EN             DEF_ENABLED     /* DEF_ENABLED = Present, DEF_DISABLED = Not Present    */
#define  APP_CFG_PROBE_COM_EN                   DEF_ENABLED
#define  APP_CFG_PROBE_DEMO_INTRO_EN            DEF_ENABLED
#define  APP_CFG_LCD_EN                         DEF_ENABLED

/*
*********************************************************************************************************
*                                            TASK PRIORITIES
*********************************************************************************************************
*/

#define  APP_CFG_TASK_START_PRIO                           2
#define  APP_CFG_TASK_JOY_PRIO                             4

#define  OS_PROBE_TASK_PRIO                                6
#define  OS_PROBE_TASK_ID                                  6

#define  PROBE_DEMO_INTRO_CFG_TASK_LED_PRIO                7

#define  APP_CFG_TASK_LCD_PRIO                            15

#define  OS_TASK_TMR_PRIO                         (OS_LOWEST_PRIO - 2)


/*
*********************************************************************************************************
*                                            TASK STACK SIZES
*********************************************************************************************************
*/

#define  APP_CFG_TASK_START_STK_SIZE                     128
#define  APP_CFG_TASK_JOY_STK_SIZE                       128
#define  APP_CFG_TASK_LCD_STK_SIZE                       512

#define  PROBE_DEMO_INTRO_CFG_TASK_LED_STK_SIZE          128

#define  OS_PROBE_TASK_STK_SIZE                          128

/*
*********************************************************************************************************
*                               uC/Probe plug-in for uC/OS-II CONFIGURATION
*********************************************************************************************************
*/

#define  OS_PROBE_TASK                                     1    /* Task will be created for uC/Probe OS Plug-In              */
#define  OS_PROBE_TMR_32_BITS                              1    /* uC/Probe OS Plug-In timer is a 32-bit timer               */
#define  OS_PROBE_HOOKS_EN                                 1    /* Hooks to update OS_TCB profiling members will be included */

/*
*********************************************************************************************************
*                                       uC/OS-II DCC CONFIGURATION
*********************************************************************************************************
*/

#define  OS_CPU_ARM_DCC_EN                                 1


/*
*********************************************************************************************************
*                                             uC/LIB CONFIGURATION
*********************************************************************************************************
*/

#define  LIB_MEM_CFG_OPTIMIZE_ASM_EN             DEF_ENABLED
#define  LIB_MEM_CFG_ARG_CHK_EXT_EN              DEF_ENABLED
#define  LIB_MEM_CFG_ALLOC_EN                    DEF_DISABLED

/*
*********************************************************************************************************
*                                       uC/BSP CONFIGURATION
*********************************************************************************************************
*/

#define  BSP_CFG_SER_COMM_SEL                   BSP_SER_COMM_UART_00

/*
*********************************************************************************************************
*                                     TRACE / DEBUG CONFIGURATION
*********************************************************************************************************
*/

#define  TRACE_LEVEL_OFF                                   0
#define  TRACE_LEVEL_INFO                                  1
#define  TRACE_LEVEL_DBG                                   2

#define  APP_CFG_TRACE_LEVEL                    TRACE_LEVEL_INFO
#define  APP_CFG_TRACE                          BSP_SerPrintf          

#define  APP_TRACE_INFO(x)                     ((APP_CFG_TRACE_LEVEL >= TRACE_LEVEL_INFO)  ? (void)(APP_CFG_TRACE x) : (void)0)
#define  APP_TRACE_DBG(x)                      ((APP_CFG_TRACE_LEVEL >= TRACE_LEVEL_DBG)   ? (void)(APP_CFG_TRACE x) : (void)0)

#endif
