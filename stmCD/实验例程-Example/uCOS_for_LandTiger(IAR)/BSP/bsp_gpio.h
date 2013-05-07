/*
*********************************************************************************************************
*                                     MICIRUM BOARD SUPPORT PACKAGE
*
*                              (c) Copyright 2009; Micrium, Inc.; Weston, FL
*
*                   All rights reserved.  Protected by international copyright laws.
*                   Knowledge of the source code may not be used to write a similar
*                   product.  This file may only be used in accordance with a license
*                   and should not be redistributed in any way.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*
*                                       MICRIUM BOARD SUPPORT PACKAGE
*                                         LPC17xx GENERAL PURPOSE I/O
*
*
* Filename      : bsp_gpio.h
* Version       : V1.00
* Programmer(s) : FT
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                                 MODULE
*
* Note(s) : (1) This header file is protected from multiple pre-processor inclusion through use of the
*               BSP_GPIO present pre-processor macro definition.
*********************************************************************************************************
*/

#ifndef  BSP_GPIO_PRESENT
#define  BSP_GPIO_PRESENT


/*
*********************************************************************************************************
*                                              INCLUDE FILES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                               EXTERNS
*********************************************************************************************************
*/


#ifdef   BSP_GPIO_MODULE
#define  BSP_GPIO_EXT
#else
#define  BSP_GPIO_EXT  extern
#endif


/*
*********************************************************************************************************
*                                        DEFAULT CONFIGURATION
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                               DEFINES
*********************************************************************************************************
*/

#define  BSP_GPIO_PORT0                                    0
#define  BSP_GPIO_PORT1                                    1
#define  BSP_GPIO_PORT0_FAST                               2
#define  BSP_GPIO_PORT1_FAST                               3
#define  BSP_GPIO_PORT2_FAST                               4
#define  BSP_GPIO_PORT3_FAST                               5
#define  BSP_GPIO_PORT4_FAST                               6


#define  BSP_GPIO_OPT_NONE                       DEF_BIT_NONE
#define  BSP_GPIO_OPT_OUT_EN                     DEF_BIT_01
#define  BSP_GPIO_OPT_IN_EN                      DEF_BIT_02
#define  BSP_GPIO_OPT_RD_WR_EN                   DEF_BIT_03
#define  BSP_GPIO_OPT_RD_WR_DIS                  DEF_BIT_04

#define  BSP_GPIO_OPT_FNCT_1                     DEF_BIT_05
#define  BSP_GPIO_OPT_FNCT_2                     DEF_BIT_06
#define  BSP_GPIO_OPT_FNCT_3                     DEF_BIT_07
#define  BSP_GPIO_OPT_FNCT_4                     DEF_BIT_08

#define  BSP_GPIO_OPT_MODE_PULLUP                DEF_BIT_09
#define  BSP_GPIO_OPT_MODE_RESERVED              DEF_BIT_10
#define  BSP_GPIO_OPT_MODE_NONE                  DEF_BIT_11
#define  BSP_GPIO_OPT_MODE_PULLDOWN              DEF_BIT_12
#define  BSP_GPIO_OPT_MODE_REPEATER              DEF_BIT_13
#define  BSP_GPIO_OPT_MODE_OPEN_DRAIN            DEF_BIT_14

/*
*********************************************************************************************************
*                                          GLOBAL VARIABLES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                               MACRO'S
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*********************************************************************************************************
*/


void         BSP_GPIO_Cfg         (CPU_INT08U   gpio_port,
                                   CPU_INT32U   gpio_pin,
                                   CPU_INT16U   gpio_opt);
void         BSP_GPIO_Clr         (CPU_INT08U   gpio_port,
                                   CPU_INT32U   gpio_pin);
void         BSP_GPIO_Set         (CPU_INT08U   gpio_port,
                                   CPU_INT32U   gpio_pin);

void         BSP_GPIO_Toggle      (CPU_INT08U   gpio_port,
                                   CPU_INT32U   gpio_pin);

CPU_INT32U   BSP_GPIO_StatusGet   (CPU_INT08U   gpio_port);


/*
*********************************************************************************************************
*                                              ERROR CHECKING
*********************************************************************************************************
*/

            
/*
*********************************************************************************************************
*                                              MODULE END
*********************************************************************************************************
*/

#endif                                                          /* End of module include.                               */
