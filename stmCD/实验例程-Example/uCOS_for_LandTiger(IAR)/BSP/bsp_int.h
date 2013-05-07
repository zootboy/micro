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
*                                         BOARD SUPPORT PACKAGE
*                                      LPC17xx INTERRUPT CONTROLLER
*
*
* Filename      : bsp_int.h
* Version       : V1.00
* Programmer(s) : FT
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                                 MODULE
*
* Note(s) : (1) This header file is protected from multiple pre-processor inclusion through use of the
*               BSP_INT present pre-processor macro definition.
*********************************************************************************************************
*/

#ifndef  BSP_INT_PRESENT
#define  BSP_INT_PRESENT


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


#ifdef   BSP_INT_MODULE
#define  BSP_INT_EXT
#else
#define  BSP_INT_EXT  extern
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

                                                                /* -------------- INTERRUPT SOURCE ------------------ */
#define  BSP_INT_SRC_NBR_WDT                                0   /* Watchdog                                           */
#define  BSP_INT_SRC_NBR_TMR0                               1   /* Timer 0 (Match 0-3 Capture 0-3)                    */
#define  BSP_INT_SRC_NBR_TMR1                               2   /* Timer 1 (Match 0-3 Capture 0-3)                    */
#define  BSP_INT_SRC_NBR_TMR2                               3   /* Timer 2 (Match 0-3 Capture 0-3)                    */
#define  BSP_INT_SRC_NBR_TMR3                               4   /* Timer 2 (Match 0-3 Capture 0-3)                    */
#define  BSP_INT_SRC_NBR_UART0                              5   /* UART 0  (RLS, THRE, RDA, CTI)                      */
#define  BSP_INT_SRC_NBR_UART1                              6   /* UART 1  (RLS, THRE, RDA, CTI, MSI)                 */
#define  BSP_INT_SRC_NBR_UART2                              7   /* UART 1  (RLS, THRE, RDA, CTI, MSI)                 */
#define  BSP_INT_SRC_NBR_UART3                              8   /* UART 1  (RLS, THRE, RDA, CTI, MSI)                 */
#define  BSP_INT_SRC_NBR_PWM1                               9   /* PWM 1   (Match 0-6 Capture 0-3)                    */
#define  BSP_INT_SRC_NBR_I2C0                              10   /* I2C     (SI)                                       */
#define  BSP_INT_SRC_NBR_I2C1                              11   /* I2C     (SI)                                       */
#define  BSP_INT_SRC_NBR_I2C2                              12   /* I2C     (SI)                                       */
#define  BSP_INT_SRC_NBR_SPI0                              13   /* SPI0    (SPIF, MODF)                               */
#define  BSP_INT_SRC_NBR_SSP0                              14   /* SSP0    Tx/Rx FIFO Int. Rx Timeout/Overrun         */
#define  BSP_INT_SRC_NBR_SSP1                              14   /* SSP1    Tx/Rx FIFO Int. Rx Timeout/Overrun         */
#define  BSP_INT_SRC_NBR_PLL0                              16   /* PLL lock (PLOCK)                                   */
#define  BSP_INT_SRC_NBR_RTC                               17   /* RTC     (RTCCIF, RTCALF)                           */
#define  BSP_INT_SRC_NBR_EINT0                             18   /* External interrupt 0 (EINT0)                       */
#define  BSP_INT_SRC_NBR_EINT1                             19   /* External interrupt 1 (EINT1)                       */
#define  BSP_INT_SRC_NBR_EINT2                             20   /* External interrupt 2 (EINT2)                       */
#define  BSP_INT_SRC_NBR_EINT3                             21   /* External interrupt 3 (EINT3)                       */
#define  BSP_INT_SRC_NBR_ADC0                              22   /* A/D Converter 0 end of conversion                  */
#define  BSP_INT_SRC_NBR_BOD                               23   /* Brown out detect                                   */
#define  BSP_INT_SRC_NBR_USB                               24   /* USB Interrupts, DMA Interrupt                      */
#define  BSP_INT_SRC_NBR_CAN                               25   /* CAN Interrupt                                      */
#define  BSP_INT_SRC_NBR_GPDMA                             26   /* IntSattus of DMA channel 0/1                       */
#define  BSP_INT_SRC_NBR_I2S                               27   /* SI (state change)                                  */
#define  BSP_INT_SRC_NBR_EMAC                              28   /* Ethernet Interrupt                                 */
#define  BSP_INT_SRC_NBR_RITINT                            28   /* Repetitive interrupt timer                         */
#define  BSP_INT_SRC_NBR_MOTOR_PWM                         29   /* Motor Control PWM                                  */
#define  BSP_INT_SRC_NBR_QUAD_ENCODER                      30   /* Quadrature Encoder                                 */
#define  BSP_INT_SRC_NBR_PLL1                              31   /* PLL1 lock (PLOCK)                                  */
#define  BSP_INT_SRC_NBR_USB_ACT                           32   /* USB Activity                                       */
#define  BSP_INT_SRC_NBR_CAN_ACT                           33   /* CAN Activity                                       */

#define  BSP_INT_SRC_NBR_MAX                               33   /* Interrupt controller maximum source id number      */
#define  BSP_INT_SRC_NBR_TOTAL                             32   /* Total number of sources                            */


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

void  BSP_IntInit                 (void);

void  BSP_IntEn                   (CPU_DATA       int_id);

void  BSP_IntDis                  (CPU_DATA       int_id);

void  BSP_IntClr                  (CPU_DATA       int_id);

void  BSP_IntVectSet              (CPU_DATA       int_id,
                                   CPU_FNCT_VOID  isr);

void  BSP_IntPrioSet              (CPU_DATA       int_id,
                                   CPU_INT08U     prio);


/*
*********************************************************************************************************
*                                      STATIC INTERRUPT HANDLERS
*********************************************************************************************************
*/

void  BSP_IntHandlerWDT           (void);
void  BSP_IntHandlerTMR0          (void);
void  BSP_IntHandlerTMR1          (void);
void  BSP_IntHandlerTMR2          (void);
void  BSP_IntHandlerTMR3          (void);
void  BSP_IntHandlerUART0         (void);
void  BSP_IntHandlerUART1         (void);
void  BSP_IntHandlerUART2         (void);
void  BSP_IntHandlerUART3         (void);
void  BSP_IntHandlerPWM1          (void);
void  BSP_IntHandlerI2C0          (void);
void  BSP_IntHandlerI2C1          (void);
void  BSP_IntHandlerI2C2          (void);
void  BSP_IntHandlerSPI0          (void);
void  BSP_IntHandlerSSP0          (void);
void  BSP_IntHandlerSSP1          (void);
void  BSP_IntHandlerPLL0          (void);
void  BSP_IntHandlerRTC           (void);
void  BSP_IntHandlerEINT0         (void);
void  BSP_IntHandlerEINT1         (void);
void  BSP_IntHandlerEINT2         (void);
void  BSP_IntHandlerEINT3         (void);
void  BSP_IntHandlerADC0          (void);
void  BSP_IntHandlerBOD           (void);
void  BSP_IntHandlerUSB           (void); 
void  BSP_IntHandlerCAN           (void);
void  BSP_IntHandlerGPDMA         (void);
void  BSP_IntHandlerI2S           (void);
void  BSP_IntHandlerEMAC          (void);
void  BSP_IntHandlerRITINT        (void);
void  BSP_IntHandlerMOTOR_PWM     (void);
void  BSP_IntHandlerQUAD_ENCODER  (void);
void  BSP_IntHandlerPLL1          (void);
void  BSP_IntHandlerUSB_ACT       (void);
void  BSP_IntHandlerCAN_ACT       (void);


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
