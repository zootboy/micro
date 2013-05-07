/*
*********************************************************************************************************
*                                     MICRIUM BOARD SUPPORT SUPPORT
*
*                          (c) Copyright 2003-2008; Micrium, Inc.; Weston, FL
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
*                                         BOARD SUPPORT PACKAGE
*
*                                         NXP LPC1766 (Cortex-M3)
*                                                on the
*
*                                            IAR LPC1766-SK 
*                                             Kickstart Kit
*
* Filename      : bsp.h
* Version       : V1.00
* Programmer(s) : FT
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                                 MODULE
*
* Note(s) : (1) This header file is protected from multiple pre-processor inclusion through use of the
*               BSP present pre-processor macro definition.
*********************************************************************************************************
*/

#ifndef  BSP_PRESENT
#define  BSP_PRESENT


/*
*********************************************************************************************************
*                                            INCLUDE FILES
*
* Note(s) : (1) The following common software files are located in the following directories :
*
*               (a) \<Custom Library Directory>\lib*.*
*
*               (b) (1) \<CPU-Compiler Directory>\cpu_def.h
*
*                   (2) \<CPU-Compiler Directory>\<cpu>\<compiler>\cpu*.*
*
*                           where
*                                   <Custom Library Directory>      directory path for custom   library      software
*                                   <CPU-Compiler Directory>        directory path for common   CPU-compiler software
*                                   <cpu>                           directory name for specific processor (CPU)
*                                   <compiler>                      directory name for specific compiler
*
*           (2) Compiler MUST be configured to include the '\<Custom Library Directory>\uC-LIB\',
*               '\<CPU-Compiler Directory>\' directory, & the specific CPU-compiler directory as
*               additional include path directories.
*
*           (3) NO compiler-supplied standard library functions SHOULD be used.
*********************************************************************************************************
*/

#include  <cpu.h>
#include  <cpu_core.h>

#include  <lib_def.h>
#include  <lib_ascii.h>

#include  <app_cfg.h>

#include  <bsp_gpio.h>
#include  <bsp_int.h>
#include  <bsp_os.h>
#include  <bsp_ser.h>
#include  <bsp_pm.h>


/*
*********************************************************************************************************
*                                                 EXTERNS
*********************************************************************************************************
*/


#ifdef   BSP_MODULE
#define  BSP_EXT
#else
#define  BSP_EXT  extern
#endif


/*
*********************************************************************************************************
*                                                 INCLUDES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                          JOYSTICK POSITION DEFINES
*********************************************************************************************************
*/

#define  BSP_JOY_NONE                 DEF_BIT_NONE              /* Joystick's position ID                                    */
#define  BSP_JOY_UP                   DEF_BIT_01
#define  BSP_JOY_DOWN                 DEF_BIT_02
#define  BSP_JOY_RIGHT                DEF_BIT_03
#define  BSP_JOY_LEFT                 DEF_BIT_04
#define  BSP_JOY_CENTER               DEF_BIT_05


/*
*********************************************************************************************************
*                                              ADC ID DEFINES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                          GLOBAL VARIABLES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*********************************************************************************************************
*/

void         BSP_Init               (void);
void         BSP_IntDisAll          (void);

CPU_INT32U   BSP_CPU_ClkFreq        (void);
CPU_INT32U   BSP_CPU_PclkFreq       (CPU_INT08U   pclk);


/*
*********************************************************************************************************
*                                             LED SERVICES
*********************************************************************************************************
*/

void         BSP_LED_On             (CPU_INT08U   led_id);
void         BSP_LED_Off            (CPU_INT08U   led_id);
void         BSP_LED_Toggle         (CPU_INT08U   led_id);


/*
*********************************************************************************************************
*                                         PUSH BUTTON SERVICES
*********************************************************************************************************
*/

CPU_BOOLEAN  BSP_PB_GetStatus       (CPU_INT08U   pb_id);


/*
*********************************************************************************************************
*                                           JOYSTICK SERVICES
*********************************************************************************************************
*/

CPU_INT08U   BSP_Joy_GetPos         (void);
CPU_BOOLEAN  BSP_Joy_GetStatus      (CPU_INT08U   joy_pos);


/*
*********************************************************************************************************
*                                          CONFIGURATION ERRORS
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                              MODULE END
*********************************************************************************************************
*/

#endif    
