/***************************************************************************
 **
 **    This file defines the board specific definition
 **
 **    Used with ARM IAR C/C++ Compiler and Assembler.
 **
 **    (c) Copyright IAR Systems 2005
 **
 **    $Revision: 28532 $
 **
 ***************************************************************************/
#include <intrinsics.h>
#include "arm_comm.h"

#ifndef __BOARD_H
#define __BOARD_H

#define I_RC_OSC_FREQ   (4MHZ)
#define MAIN_OSC_FREQ   (12MHZ)
#define RTC_OSC_FREQ    (32768UL)
#define IAR_LPC_1766_SK

#if defined(IAR_LPC_1766_SK)
// USB Link LED
#define USB_LINK_LED_MASK   (1UL<<18)
#define USB_LINK_LED_FDIR   FIO1DIR
#define USB_LINK_LED_FSET   FIO1SET
#define USB_LINK_LED_FCLR   FIO1CLR
#define USB_LINK_LED_FIO    FIO1PIN
// USB Link LED
#define USB_CONNECT_LED_MASK   (1UL<<9)
#define USB_CONNECT_LED_FDIR   FIO2DIR
#define USB_CONNECT_LED_FSET   FIO2SET
#define USB_CONNECT_LED_FCLR   FIO2CLR
#define USB_CONNECT_LED_FIO    FIO2PIN
// LED1
#define LED1_MASK   (1UL<<25)
#define LED1_FDIR   FIO1DIR
#define LED1_FSET   FIO1SET
#define LED1_FCLR   FIO1CLR
#define LED1_FIO    FIO1PIN
// LED2
#define LED2_MASK   (1UL<<4)
#define LED2_FDIR   FIO0DIR
#define LED2_FSET   FIO0SET
#define LED2_FCLR   FIO0CLR
#define LED2_FIO    FIO0PIN

// LCD Backlight
#define LCD_BL_MASK         (1UL<<26)
#define LCD_BL_FDIR         FIO3DIR
#define LCD_BL_FSET         FIO3SET
#define LCD_BL_FCLR         FIO3CLR
#define LCD_BL_FIO          FIO3PIN

#define LCD_BL_PIN_SEL      PINSEL7_bit.P3_26
// LCD Reset
#define LCD_RST_MASK        (1UL<<25)
#define LCD_RST_FDIR        FIO3DIR
#define LCD_RST_FSET        FIO3SET
#define LCD_RST_FCLR        FIO3CLR
#define LCD_RST_FIO         FIO3PIN
// LCD CS
#define LCD_CS_MASK         (1UL<<21)
#define LCD_CS_FDIR         FIO1DIR
#define LCD_CS_FSET         FIO1SET
#define LCD_CS_FCLR         FIO1CLR
#define LCD_CS_FIO          FIO1PIN

// Buttons
//B1
#define B1_MASK             (1UL<<23)
#define B1_FDIR             FIO0DIR
#define B1_FIO              FIO0PIN
//B2
#define B2_MASK             (1UL<<13)
#define B2_FDIR             FIO2DIR
#define B2_FIO              FIO2PIN
//WAKE_UP
#define WAKE_UP_MASK        (1UL<<12)
#define WAKE_UP_FDIR        FIO2DIR
#define WAKE_UP_FIO         FIO2PIN

// Joystick
#define JS_RIGHT_MASK       (1UL << 8)
#define JS_LEFT_MASK        (1UL << 7)
#define JS_UP_MASK          (1UL << 0)
#define JS_DOWN_MASK        (1UL << 1)
#define JS_CENTER_MASK      (1UL << 5)
#define JS_FDIR             FIO2DIR
#define JS_FIO              FIO2PIN
#define JS_CENTER_FDIR      FIO0DIR
#define JS_CENTER_FIO       FIO0PIN

// MMC/SD card
// Card present
#define MMC_CP_MASK         (1UL << 28)
#define MMC_CP_FDIR         FIO1DIR
#define MMC_CP_FIO          FIO1PIN
#define MMC_CP_MODE         PINMODE3_bit.P1_28
#define MMC_CP_SEL          PINSEL3_bit.P1_28

// Card write protect
#define MMC_WP_MASK         (1UL << 29)
#define MMC_WP_FDIR         FIO1DIR
#define MMC_WP_FIO          FIO1PIN
#define MMC_WP_MODE         PINMODE3_bit.P1_29
#define MMC_WP_SEL          PINSEL3_bit.P1_29

// Card power
#define MMC_PWR_MASK         (1UL << 21)
#define MMC_PWR_FDIR         FIO0DIR
#define MMC_PWR_FSET         FIO0SET
#define MMC_PWR_FCLR         FIO0CLR
#define MMC_PWR_MODE         PINMODE1_bit.P0_21
#define MMC_PWR_SEL          PINSEL1_bit.P0_21
// Card chip select
#define MMC_CS_MASK         (1UL << 6)
#define MMC_CS_FDIR         FIO0DIR
#define MMC_CS_FSET         FIO0SET
#define MMC_CS_FCLR         FIO0CLR
#define MMC_CS_MODE         PINMODE0_bit.P0_6
#define MMC_CS_SEL          PINSEL0_bit.P0_6

// Analog trim
#define ANALOG_TRIM_CHANNEL 5
#define ANALOG_TRIM_PIN_SEL   PINSEL3_bit.P1_31
#define ANALOG_TRIM_PIN_MODE PINMODE3_bit.P1_31
// MIC Input
#define MIC_IN_CHANNEL      2
#define MIC_IN_CHANNEL_SEL  PINSEL1_bit.P0_25

//TEMP
#define TEMP_CHANNEL        1
#define TEMP_PIN_SEL    PINSEL1_bit.P0_24

#else
#error define type of the board
#endif

// PCLK offset
#define WDT_PCLK_OFFSET     0
#define TIMER0_PCLK_OFFSET  2
#define TIMER1_PCLK_OFFSET  4
#define UART0_PCLK_OFFSET   6
#define UART1_PCLK_OFFSET   8
#define PWM0_PCLK_OFFSET    10
#define PWM1_PCLK_OFFSET    12
#define I2C0_PCLK_OFFSET    14
#define SPI_PCLK_OFFSET     16
#define RTC_PCLK_OFFSET     18
#define SSP1_PCLK_OFFSET    20
#define DAC_PCLK_OFFSET     22
#define ADC_PCLK_OFFSET     24
#define CAN1_PCLK_OFFSET    26
#define CAN2_PCLK_OFFSET    28
#define ACF_PCLK_OFFSET     30
#define BAT_RAM_PCLK_OFFSET 32
#define GPIO_PCLK_OFFSET    34
#define PCB_PCLK_OFFSET     36
#define I2C1_PCLK_OFFSET    38
//#define                   40
#define SSP0_PCLK_OFFSET    42
#define TIMER2_PCLK_OFFSET  44
#define TIMER3_PCLK_OFFSET  46
#define UART2_PCLK_OFFSET   48
#define UART3_PCLK_OFFSET   50
#define I2C2_PCLK_OFFSET    52
#define I2S_PCLK_OFFSET     54
#define MCI_PCLK_OFFSET     56
//#define                   58
#define PCLK_PCLK_OFFSET    60
//#define                   62

#define IRQ_FLAG            0x80
#define FIQ_FLAG            0x40

#endif /* __BOARD_H */
