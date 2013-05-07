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
*                                     MICRIUM BOARD SUPPORT PACKAGE
*                                           POWER MANAGMENT
*
*
* Filename      : bsp_pm.h
* Version       : V1.00
* Programmer(s) : FT
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                                 MODULE
*
* Note(s) : (1) This header file is protected from multiple pre-processor inclusion through use of the
*               BSP_SYS_CTRL present pre-processor macro definition.
*********************************************************************************************************
*/

#ifndef  BSP_PM_PRESENT
#define  BSP_PM_PRESENT


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


#ifdef   BSP_PM_MODULE
#define  BSP_PM_EXT
#else
#define  BSP_PM_EXT  extern
#endif

/*
*********************************************************************************************************
*                                         DEFAULT CONFIGURATION
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                            FREQUENCY DEFINES
*********************************************************************************************************
*/

#define  BSP_PM_OSC_MAIN_OSC_FREQ_HZ               12000000L
#define  BSP_PM_OSC_INT_RC_FREQ_HZ                  4000000L
#define  BSP_PM_OSC_RTC_FREQ_HZ                        32768


/*
*********************************************************************************************************
*                                                CPU POWER MODES
*********************************************************************************************************
*/

#define  BSP_PM_CPU_MODE_NORMAL                            0
#define  BSP_PM_CPU_MODE_PWR_DOWN                          1
#define  BSP_PM_CPU_MODE_IDLE                              2
#define  BSP_PM_CPU_MODE_SLEEP                             3


/*
*********************************************************************************************************
*                                             PERIPHERAL CLOCK DEFINES
* 
* Note(s) : (1) Some peripheral bit numbers doesn't match between the Power Coontrol for periphreal (PCONP) 
*               register and the Peripheral Clock Selection register (PCLKSEL0/1)
*
*               For example the bit 15 in the PCONP register is for GPIO clock, but in the PCLKSEL0 register bits 30:31 
*               (uses two bit per peripheral) is for CAN acceptance filtering (ACF). 
*
*               To solve this inconsistency BSP_SYS_CTRL_PER_NBR_GPIO and  BSP_SYS_CTRL_PER_NBR_PCLKSEL_ACF are defined
*               to the same value. 
*
*               - BSP_SYS_CTRL_PER_NBR_GPIO  should be used with BSP_SysCtrl_PerClkDis() and BSP_SysCtrl_PerClkEn() 
*                 functions.
*
*               - BSP_SYS_CTRL_PER_NBR_PCLKSEL_ACF should be used with BSP_SysCtrl_PerClkFreqCfg() and 
*                 BSP_SysCtrl_PerClkFreqCfg() functions.
**********************************************************************************************************
*/

#define  BSP_PM_PER_NBR_WDT                                0    /* Watchdog Timer                                     */
#define  BSP_PM_PER_NBR_RESERVED0                          0    /* Reserved                                           */

#define  BSP_PM_PER_NBR_TMR0                                1   /* Timer 0                                            */
#define  BSP_PM_PER_NBR_TMR1                                2   /* Timer 1                                            */
#define  BSP_PM_PER_NBR_UART0                               3   /* UART 0                                             */
#define  BSP_PM_PER_NBR_UART1                               4   /* UART 1                                             */

#define  BSP_PM_PER_NBR_RESERVED1                           5   /* Reserved                                           */
#define  BSP_PM_PER_NBR_PCLKSEL_RESERVED0                   5   /* Reserved (Peripheral Clock Selection)              */

#define  BSP_PM_PER_NBR_PWM1                                6   /* PWM1                                               */
#define  BSP_PM_PER_NBR_I2C0                                7   /* I2C 0                                              */
#define  BSP_PM_PER_NBR_SPI0                                8   /* SPI 0                                              */

#define  BSP_PM_PER_NBR_RTC                                 9   /* RTC                                                */
#define  BSP_PM_PER_NBR_PCLKSEL_RESERVED1                   9   /* Reserved (Peripheral Clock Selection)              */

#define  BSP_PM_PER_NBR_SSP1                                10  /* SSP 1                                              */
#define  BSP_PM_PER_NBR_RESERVED2                           11  /* Reserved                                           */
#define  BSP_PM_PER_NBR_AD0                                 12  /* A/D converter                                      */
#define  BSP_PM_PER_NBR_CAN1                                13  /* CAN 1                                              */
#define  BSP_PM_PER_NBR_CAN2                                14  /* CAN 2                                              */

#define  BSP_PM_PER_NBR_GPIO                                15  /* GPIO                                               */
#define  BSP_PM_PER_NBR_PCLKSEL_ACF                         15  /* CAN filtering. (Peripheral Clock Selection)        */

#define  BSP_PM_PER_NBR_RIT                                 16  /* Repetitive Interrupt Timer                         */
#define  BSP_PM_PER_NBR_PCLKSEL_QEI                         16  /* QEI (Peripheral Clock Selection)                   */

#define  BSP_PM_PER_NBR_MCPWM                               17  /* Motor Control PWM                                  */
#define  BSP_PM_PER_NBR_PCLKSEL_GPIOINT                     17  /* QEI (Peripheral Clock Selection)                   */

#define  BSP_PM_PER_NBR_QEI                                 18  /* Quadrature Encoder Interface                       */
#define  BSP_PM_PER_NBR_PCLKSEL_PCB                         18  /* Pin Connect Block (Peripheral Clock Selection)     */

#define  BSP_PM_PER_NBR_I2C1                                19  /* I2C1                                               */

#define  BSP_PM_PER_NBR_RESERVED3                           20  /* Reserved                                           */
#define  BSP_PM_PER_NBR_PCLKSEL_RESERVED2                   20  /* Reserved (Peripheral Clock Selection)              */

#define  BSP_PM_PER_NBR_SSP0                                21  /* SSP0                                               */
#define  BSP_PM_PER_NBR_TMR2                                22  /* TIMER 2                                            */
#define  BSP_PM_PER_NBR_TMR3                                23  /* TIMER 3                                            */
#define  BSP_PM_PER_NBR_UART2                               24  /* UART 2                                             */
#define  BSP_PM_PER_NBR_UART3                               25  /* UART 3                                             */
#define  BSP_PM_PER_NBR_I2C2                                26  /* I2C 2                                              */
#define  BSP_PM_PER_NBR_I2S                                 27  /* I2S                                                */
#define  BSP_PM_PER_NBR_RESERVED4                           28  /* Reserved                                           */
#define  BSP_PM_PER_NBR_PCLKSEL_RESERVED3                   28  /* Reserved (Peripheral Clock Selection)              */


#define  BSP_PM_PER_NBR_GPDMA                               29  /* GP DMA function                                    */
#define  BSP_PM_PER_NBR_PCLKSEL_RIT                         29  /* RIT (Peripheral Clock Selection)                   */

#define  BSP_PM_PER_NBR_ENET                                30  /* Ethernet Controller                                */
#define  BSP_PM_PER_NBR_PCLKSEL_SYSCON                      30  /* Sytem Control Block (Peripheral Clock Selection)   */

#define  BSP_PM_PER_NBR_USB                                 31  /* USB                                                */
#define  BSP_PM_PER_NBR_PCLKSEL_MCPWM                       31  /* Motor Control PWM (Peripheral Clock Selection)     */


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

CPU_INT32U  BSP_PM_CPU_FreqGet    (void);

void        BSP_PM_PerClkEn       (CPU_INT08U  per_nbr);
void        BSP_PM_PerClkDis      (CPU_INT08U  per_nbr);
CPU_INT32U  BSP_PM_PerClkFreqGet  (CPU_INT08U  per_nbr);

/*
*********************************************************************************************************
*                                              ERROR CHECKING
*********************************************************************************************************
*/

            
/*
*********************************************************************************************************
*                                             MODULE END
*********************************************************************************************************
*/

#endif                                                          /* End of module include.                               */
