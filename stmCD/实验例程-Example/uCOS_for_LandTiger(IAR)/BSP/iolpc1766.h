/***************************************************************************
 **
 **    This file defines the Special Function Registers for
 **    NXP LPC1766
 **
 **    Used with ARM IAR C/C++ Compiler and Assembler.
 **
 **    (c) Copyright IAR Systems 2008
 **
 **    $Revision: 30123 $
 **
 **    Note: Only little endian addressing of 8 bit registers.
 ***************************************************************************/

#ifndef __IOLPC1766_H
#define __IOLPC1766_H

#if (((__TID__ >> 8) & 0x7F) != 0x4F)     /* 0x4F = 79 dec */
#error This file should only be compiled by ARM IAR compiler and assembler
#endif

#include "io_macros.h"

/***************************************************************************
 ***************************************************************************
 **
 **    LPC1766 SPECIAL FUNCTION REGISTERS
 **
 ***************************************************************************
 ***************************************************************************
 ***************************************************************************/

/* C-compiler specific declarations  ***************************************/
#ifdef __IAR_SYSTEMS_ICC__

#ifndef _SYSTEM_BUILD
#pragma system_include
#endif

#if __LITTLE_ENDIAN__ == 0
#error This file should only be compiled in little endian mode
#endif

/* Reset Source Identification Register */
typedef struct{
__REG32 POR         : 1;
__REG32 EXTR        : 1;
__REG32 WDTR        : 1;
__REG32 BODR        : 1;
__REG32             :28;
} __rsid_bits;

/* External interrupt register */
typedef struct{
__REG32 EINT0       : 1;
__REG32 EINT1       : 1;
__REG32 EINT2       : 1;
__REG32 EINT3       : 1;
__REG32             :28;
} __extint_bits;

/* External Interrupt Mode Register */
typedef struct{
__REG32 EXTMODE0    : 1;
__REG32 EXTMODE1    : 1;
__REG32 EXTMODE2    : 1;
__REG32 EXTMODE3    : 1;
__REG32             :28;
} __extmode_bits;

/* External Interrupt Polarity Register */
typedef struct{
__REG32 EXTPOLAR0   : 1;
__REG32 EXTPOLAR1   : 1;
__REG32 EXTPOLAR2   : 1;
__REG32 EXTPOLAR3   : 1;
__REG32             :28;
} __extpolar_bits;

/* System Controls and Status register */
typedef struct{
__REG32             : 4;
__REG32 OSCRANGE    : 1;
__REG32 OSCEN       : 1;
__REG32 OSCSTAT     : 1;
__REG32             :25;
} __scs_bits;

/* Clock Soucre Select register */
typedef struct{
__REG32 CLKSRC      : 2;
__REG32             :30;
} __clksrcsel_bits;

/* PLL control register */
typedef struct{
__REG32 PLLE        : 1;
__REG32 PLLC        : 1;
__REG32             :30;
} __pllcon_bits;

/* PLL config register */
typedef struct{
__REG32 MSEL        :15;
__REG32             : 1;
__REG32 NSEL        : 8;
__REG32             : 8;
} __pllcfg_bits;

/* PLL1 config register */
typedef struct{
__REG32 MSEL        : 5;
__REG32 PSEL        : 2;
__REG32             :25;
} __pll1cfg_bits;

/* PLL status register */
typedef struct{
__REG32 MSEL        :15;
__REG32             : 1;
__REG32 NSEL        : 8;
__REG32 PLLE        : 1;
__REG32 PLLC        : 1;
__REG32 PLOCK       : 1;
__REG32             : 5;
} __pllstat_bits;

/* PLL1 status register */
typedef struct{
__REG32 MSEL        : 5;
__REG32 PSEL        : 2;
__REG32             : 1;
__REG32 PLLE        : 1;
__REG32 PLLC        : 1;
__REG32 PLOCK       : 1;
__REG32             :21;
} __pll1stat_bits;

/* PLL feed register */
typedef struct{
__REG32 FEED        : 8;
__REG32             :24;
} __pllfeed_bits;

/* CPU Clock Configuration register */
typedef struct{
__REG32 CCLKSEL     : 8;
__REG32             :24;
} __cclkcfg_bits;

/* USB Clock Configuration register */
typedef struct{
__REG32 USBSEL      : 4;
__REG32             :28;
} __usbclkcfg_bits;

/* IRC Trim Register (IRCTRIM - 0xE01FC1A4) */
typedef struct{
__REG32 IRCTRIM     : 8;
__REG32             :24;
} __irctrim_bits;

/* Peripheral Clock Selection registers 0 */
typedef struct{
__REG32 PCLK_WDT    : 2;
__REG32 PCLK_TIMER0 : 2;
__REG32 PCLK_TIMER1 : 2;
__REG32 PCLK_UART0  : 2;
__REG32 PCLK_UART1  : 2;
__REG32             : 2;
__REG32 PCLK_PWM1   : 2;
__REG32 PCLK_I2C0   : 2;
__REG32 PCLK_SPI    : 2;
__REG32             : 2;
__REG32 PCLK_SSP1   : 2;
__REG32 PCLK_DAC    : 2;
__REG32 PCLK_ADC    : 2;
__REG32 PCLK_CAN1   : 2;
__REG32 PCLK_CAN2   : 2;
__REG32 PCLK_ACF    : 2;
} __pclksel0_bits;

/* Peripheral Clock Selection registers 1 */
typedef struct{
__REG32 PCLK_QEI    : 2;
__REG32 PCLK_GPIOINT: 2;
__REG32 PCLK_PCB    : 2;
__REG32 PCLK_I2C1   : 2;
__REG32             : 2;
__REG32 PCLK_SSP0   : 2;
__REG32 PCLK_TIMER2 : 2;
__REG32 PCLK_TIMER3 : 2;
__REG32 PCLK_UART2  : 2;
__REG32 PCLK_UART3  : 2;
__REG32 PCLK_I2C2   : 2;
__REG32 PCLK_I2S    : 2;
__REG32             : 2;
__REG32 PCLK_RIT    : 2;
__REG32 PCLK_SYSCON : 2;
__REG32 PCLK_MC     : 2;
} __pclksel1_bits;

/* Power control register */
typedef struct{
__REG32 PM0         : 1;
__REG32 PM1         : 1;
__REG32 BODPDM      : 1;
__REG32 BOGD        : 1;
__REG32 BORD        : 1;
__REG32             : 3;
__REG32 SMFLAG      : 1;
__REG32 DSFLAG      : 1;
__REG32 PDFLAG      : 1;
__REG32 DPDFLAG     : 1;
__REG32             :20;
}__pcon_bits;

/* Power control for peripherals register */
typedef struct{
__REG32             : 1;
__REG32 PCTIM0      : 1;
__REG32 PCTIM1      : 1;
__REG32 PCUART0     : 1;
__REG32 PCUART1     : 1;
__REG32             : 1;
__REG32 PCPWM1      : 1;
__REG32 PCI2C0      : 1;
__REG32 PCSPI       : 1;
__REG32 PCRTC       : 1;
__REG32 PCSSP1      : 1;
__REG32             : 1;
__REG32 PCAD        : 1;
__REG32 PCAN1       : 1;
__REG32 PCAN2       : 1;
__REG32 PCGPIO      : 1;
__REG32 PCRIT       : 1;
__REG32 PCMC        : 1;
__REG32 PCQEI       : 1;
__REG32 PCI2C1      : 1;
__REG32             : 1;
__REG32 PCSSP0      : 1;
__REG32 PCTIM2      : 1;
__REG32 PCTIM3      : 1;
__REG32 PCUART2     : 1;
__REG32 PCUART3     : 1;
__REG32 PCI2C2      : 1;
__REG32 PCI2S       : 1;
__REG32             : 1;
__REG32 PCGPDMA     : 1;
__REG32 PCENET      : 1;
__REG32 PCUSB       : 1;
} __pconp_bits;

/* Clock Output Configuration register */
typedef struct{
__REG32 CLKOUTSEL   : 4;
__REG32 CLKOUTDIV   : 4;
__REG32 CLKOUT_EN   : 1;
__REG32 CLKOUT_ACT  : 1;
__REG32             :22;
} __clkoutcfg_bits;

/* Flash Accelerator Configuration register */
typedef struct{
__REG32             :12;
__REG32 FLASHTIM    : 4;
__REG32             :16;
} __flashcfg_bits;

/* Interrupt Controller Type Register */
typedef struct {
  __REG32  INTLINESNUM    : 5;
  __REG32                 :27;
} __nvic_bits;

/* SysTick Control and Status Register */
typedef struct {
  __REG32  ENABLE         : 1;
  __REG32  TICKINT        : 1;
  __REG32  CLKSOURCE      : 1;
  __REG32                 :13;
  __REG32  COUNTFLAG      : 1;
  __REG32                 :15;
} __systickcsr_bits;

/* SysTick Reload Value Register */
typedef struct {
  __REG32  RELOAD         :24;
  __REG32                 : 8;
} __systickrvr_bits;

/* SysTick Current Value Register */
typedef struct {
  __REG32  CURRENT        :24;
  __REG32                 : 8;
} __systickcvr_bits;

/* SysTick Calibration Value Register */
typedef struct {
  __REG32  TENMS          :24;
  __REG32                 : 6;
  __REG32  SKEW           : 1;
  __REG32  NOREF          : 1;
} __systickcalvr_bits;

/* Interrupt Set-Enable Registers 0-31 */
typedef struct {
  __REG32  SETENA0        : 1;
  __REG32  SETENA1        : 1;
  __REG32  SETENA2        : 1;
  __REG32  SETENA3        : 1;
  __REG32  SETENA4        : 1;
  __REG32  SETENA5        : 1;
  __REG32  SETENA6        : 1;
  __REG32  SETENA7        : 1;
  __REG32  SETENA8        : 1;
  __REG32  SETENA9        : 1;
  __REG32  SETENA10       : 1;
  __REG32  SETENA11       : 1;
  __REG32  SETENA12       : 1;
  __REG32  SETENA13       : 1;
  __REG32  SETENA14       : 1;
  __REG32  SETENA15       : 1;
  __REG32  SETENA16       : 1;
  __REG32  SETENA17       : 1;
  __REG32  SETENA18       : 1;
  __REG32  SETENA19       : 1;
  __REG32  SETENA20       : 1;
  __REG32  SETENA21       : 1;
  __REG32  SETENA22       : 1;
  __REG32  SETENA23       : 1;
  __REG32  SETENA24       : 1;
  __REG32  SETENA25       : 1;
  __REG32  SETENA26       : 1;
  __REG32  SETENA27       : 1;
  __REG32  SETENA28       : 1;
  __REG32  SETENA29       : 1;
  __REG32  SETENA30       : 1;
  __REG32  SETENA31       : 1;
} __setena0_bits;

/* Interrupt Set-Enable Registers 32-63 */
typedef struct {
  __REG32  SETENA32       : 1;
  __REG32  SETENA33       : 1;
  __REG32  SETENA34       : 1;
  __REG32  SETENA35       : 1;
  __REG32  SETENA36       : 1;
  __REG32  SETENA37       : 1;
  __REG32  SETENA38       : 1;
  __REG32  SETENA39       : 1;
  __REG32  SETENA40       : 1;
  __REG32  SETENA41       : 1;
  __REG32  SETENA42       : 1;
  __REG32  SETENA43       : 1;
  __REG32  SETENA44       : 1;
  __REG32  SETENA45       : 1;
  __REG32  SETENA46       : 1;
  __REG32  SETENA47       : 1;
  __REG32  SETENA48       : 1;
  __REG32  SETENA49       : 1;
  __REG32  SETENA50       : 1;
  __REG32  SETENA51       : 1;
  __REG32  SETENA52       : 1;
  __REG32  SETENA53       : 1;
  __REG32  SETENA54       : 1;
  __REG32  SETENA55       : 1;
  __REG32  SETENA56       : 1;
  __REG32  SETENA57       : 1;
  __REG32  SETENA58       : 1;
  __REG32  SETENA59       : 1;
  __REG32  SETENA60       : 1;
  __REG32  SETENA61       : 1;
  __REG32  SETENA62       : 1;
  __REG32  SETENA63       : 1;
} __setena1_bits;

/* Interrupt Clear-Enable Registers 0-31 */
typedef struct {
  __REG32  CLRENA0        : 1;
  __REG32  CLRENA1        : 1;
  __REG32  CLRENA2        : 1;
  __REG32  CLRENA3        : 1;
  __REG32  CLRENA4        : 1;
  __REG32  CLRENA5        : 1;
  __REG32  CLRENA6        : 1;
  __REG32  CLRENA7        : 1;
  __REG32  CLRENA8        : 1;
  __REG32  CLRENA9        : 1;
  __REG32  CLRENA10       : 1;
  __REG32  CLRENA11       : 1;
  __REG32  CLRENA12       : 1;
  __REG32  CLRENA13       : 1;
  __REG32  CLRENA14       : 1;
  __REG32  CLRENA15       : 1;
  __REG32  CLRENA16       : 1;
  __REG32  CLRENA17       : 1;
  __REG32  CLRENA18       : 1;
  __REG32  CLRENA19       : 1;
  __REG32  CLRENA20       : 1;
  __REG32  CLRENA21       : 1;
  __REG32  CLRENA22       : 1;
  __REG32  CLRENA23       : 1;
  __REG32  CLRENA24       : 1;
  __REG32  CLRENA25       : 1;
  __REG32  CLRENA26       : 1;
  __REG32  CLRENA27       : 1;
  __REG32  CLRENA28       : 1;
  __REG32  CLRENA29       : 1;
  __REG32  CLRENA30       : 1;
  __REG32  CLRENA31       : 1;
} __clrena0_bits;

/* Interrupt Clear-Enable Registers 32-63 */
typedef struct {
  __REG32  CLRENA32       : 1;
  __REG32  CLRENA33       : 1;
  __REG32  CLRENA34       : 1;
  __REG32  CLRENA35       : 1;
  __REG32  CLRENA36       : 1;
  __REG32  CLRENA37       : 1;
  __REG32  CLRENA38       : 1;
  __REG32  CLRENA39       : 1;
  __REG32  CLRENA40       : 1;
  __REG32  CLRENA41       : 1;
  __REG32  CLRENA42       : 1;
  __REG32  CLRENA43       : 1;
  __REG32  CLRENA44       : 1;
  __REG32  CLRENA45       : 1;
  __REG32  CLRENA46       : 1;
  __REG32  CLRENA47       : 1;
  __REG32  CLRENA48       : 1;
  __REG32  CLRENA49       : 1;
  __REG32  CLRENA50       : 1;
  __REG32  CLRENA51       : 1;
  __REG32  CLRENA52       : 1;
  __REG32  CLRENA53       : 1;
  __REG32  CLRENA54       : 1;
  __REG32  CLRENA55       : 1;
  __REG32  CLRENA56       : 1;
  __REG32  CLRENA57       : 1;
  __REG32  CLRENA58       : 1;
  __REG32  CLRENA59       : 1;
  __REG32  CLRENA60       : 1;
  __REG32  CLRENA61       : 1;
  __REG32  CLRENA62       : 1;
  __REG32  CLRENA63       : 1;
} __clrena1_bits;

/* Interrupt Set-Pending Register 0-31 */
typedef struct {
  __REG32  SETPEND0       : 1;
  __REG32  SETPEND1       : 1;
  __REG32  SETPEND2       : 1;
  __REG32  SETPEND3       : 1;
  __REG32  SETPEND4       : 1;
  __REG32  SETPEND5       : 1;
  __REG32  SETPEND6       : 1;
  __REG32  SETPEND7       : 1;
  __REG32  SETPEND8       : 1;
  __REG32  SETPEND9       : 1;
  __REG32  SETPEND10      : 1;
  __REG32  SETPEND11      : 1;
  __REG32  SETPEND12      : 1;
  __REG32  SETPEND13      : 1;
  __REG32  SETPEND14      : 1;
  __REG32  SETPEND15      : 1;
  __REG32  SETPEND16      : 1;
  __REG32  SETPEND17      : 1;
  __REG32  SETPEND18      : 1;
  __REG32  SETPEND19      : 1;
  __REG32  SETPEND20      : 1;
  __REG32  SETPEND21      : 1;
  __REG32  SETPEND22      : 1;
  __REG32  SETPEND23      : 1;
  __REG32  SETPEND24      : 1;
  __REG32  SETPEND25      : 1;
  __REG32  SETPEND26      : 1;
  __REG32  SETPEND27      : 1;
  __REG32  SETPEND28      : 1;
  __REG32  SETPEND29      : 1;
  __REG32  SETPEND30      : 1;
  __REG32  SETPEND31      : 1;
} __setpend0_bits;

/* Interrupt Set-Pending Register 32-63 */
typedef struct {
  __REG32  SETPEND32      : 1;
  __REG32  SETPEND33      : 1;
  __REG32  SETPEND34      : 1;
  __REG32  SETPEND35      : 1;
  __REG32  SETPEND36      : 1;
  __REG32  SETPEND37      : 1;
  __REG32  SETPEND38      : 1;
  __REG32  SETPEND39      : 1;
  __REG32  SETPEND40      : 1;
  __REG32  SETPEND41      : 1;
  __REG32  SETPEND42      : 1;
  __REG32  SETPEND43      : 1;
  __REG32  SETPEND44      : 1;
  __REG32  SETPEND45      : 1;
  __REG32  SETPEND46      : 1;
  __REG32  SETPEND47      : 1;
  __REG32  SETPEND48      : 1;
  __REG32  SETPEND49      : 1;
  __REG32  SETPEND50      : 1;
  __REG32  SETPEND51      : 1;
  __REG32  SETPEND52      : 1;
  __REG32  SETPEND53      : 1;
  __REG32  SETPEND54      : 1;
  __REG32  SETPEND55      : 1;
  __REG32  SETPEND56      : 1;
  __REG32  SETPEND57      : 1;
  __REG32  SETPEND58      : 1;
  __REG32  SETPEND59      : 1;
  __REG32  SETPEND60      : 1;
  __REG32  SETPEND61      : 1;
  __REG32  SETPEND62      : 1;
  __REG32  SETPEND63      : 1;
} __setpend1_bits;

/* Interrupt Clear-Pending Register 0-31 */
typedef struct {
  __REG32  CLRPEND0       : 1;
  __REG32  CLRPEND1       : 1;
  __REG32  CLRPEND2       : 1;
  __REG32  CLRPEND3       : 1;
  __REG32  CLRPEND4       : 1;
  __REG32  CLRPEND5       : 1;
  __REG32  CLRPEND6       : 1;
  __REG32  CLRPEND7       : 1;
  __REG32  CLRPEND8       : 1;
  __REG32  CLRPEND9       : 1;
  __REG32  CLRPEND10      : 1;
  __REG32  CLRPEND11      : 1;
  __REG32  CLRPEND12      : 1;
  __REG32  CLRPEND13      : 1;
  __REG32  CLRPEND14      : 1;
  __REG32  CLRPEND15      : 1;
  __REG32  CLRPEND16      : 1;
  __REG32  CLRPEND17      : 1;
  __REG32  CLRPEND18      : 1;
  __REG32  CLRPEND19      : 1;
  __REG32  CLRPEND20      : 1;
  __REG32  CLRPEND21      : 1;
  __REG32  CLRPEND22      : 1;
  __REG32  CLRPEND23      : 1;
  __REG32  CLRPEND24      : 1;
  __REG32  CLRPEND25      : 1;
  __REG32  CLRPEND26      : 1;
  __REG32  CLRPEND27      : 1;
  __REG32  CLRPEND28      : 1;
  __REG32  CLRPEND29      : 1;
  __REG32  CLRPEND30      : 1;
  __REG32  CLRPEND31      : 1;
} __clrpend0_bits;

/* Interrupt Clear-Pending Register 32-63 */
typedef struct {
  __REG32  CLRPEND32      : 1;
  __REG32  CLRPEND33      : 1;
  __REG32  CLRPEND34      : 1;
  __REG32  CLRPEND35      : 1;
  __REG32  CLRPEND36      : 1;
  __REG32  CLRPEND37      : 1;
  __REG32  CLRPEND38      : 1;
  __REG32  CLRPEND39      : 1;
  __REG32  CLRPEND40      : 1;
  __REG32  CLRPEND41      : 1;
  __REG32  CLRPEND42      : 1;
  __REG32  CLRPEND43      : 1;
  __REG32  CLRPEND44      : 1;
  __REG32  CLRPEND45      : 1;
  __REG32  CLRPEND46      : 1;
  __REG32  CLRPEND47      : 1;
  __REG32  CLRPEND48      : 1;
  __REG32  CLRPEND49      : 1;
  __REG32  CLRPEND50      : 1;
  __REG32  CLRPEND51      : 1;
  __REG32  CLRPEND52      : 1;
  __REG32  CLRPEND53      : 1;
  __REG32  CLRPEND54      : 1;
  __REG32  CLRPEND55      : 1;
  __REG32  CLRPEND56      : 1;
  __REG32  CLRPEND57      : 1;
  __REG32  CLRPEND58      : 1;
  __REG32  CLRPEND59      : 1;
  __REG32  CLRPEND60      : 1;
  __REG32  CLRPEND61      : 1;
  __REG32  CLRPEND62      : 1;
  __REG32  CLRPEND63      : 1;
} __clrpend1_bits;

/* Active Bit Register 0-31 */
typedef struct {
  __REG32  ACTIVE0        : 1;
  __REG32  ACTIVE1        : 1;
  __REG32  ACTIVE2        : 1;
  __REG32  ACTIVE3        : 1;
  __REG32  ACTIVE4        : 1;
  __REG32  ACTIVE5        : 1;
  __REG32  ACTIVE6        : 1;
  __REG32  ACTIVE7        : 1;
  __REG32  ACTIVE8        : 1;
  __REG32  ACTIVE9        : 1;
  __REG32  ACTIVE10       : 1;
  __REG32  ACTIVE11       : 1;
  __REG32  ACTIVE12       : 1;
  __REG32  ACTIVE13       : 1;
  __REG32  ACTIVE14       : 1;
  __REG32  ACTIVE15       : 1;
  __REG32  ACTIVE16       : 1;
  __REG32  ACTIVE17       : 1;
  __REG32  ACTIVE18       : 1;
  __REG32  ACTIVE19       : 1;
  __REG32  ACTIVE20       : 1;
  __REG32  ACTIVE21       : 1;
  __REG32  ACTIVE22       : 1;
  __REG32  ACTIVE23       : 1;
  __REG32  ACTIVE24       : 1;
  __REG32  ACTIVE25       : 1;
  __REG32  ACTIVE26       : 1;
  __REG32  ACTIVE27       : 1;
  __REG32  ACTIVE28       : 1;
  __REG32  ACTIVE29       : 1;
  __REG32  ACTIVE30       : 1;
  __REG32  ACTIVE31       : 1;
} __active0_bits;

/* Active Bit Register 32-63 */
typedef struct {
  __REG32  ACTIVE32       : 1;
  __REG32  ACTIVE33       : 1;
  __REG32  ACTIVE34       : 1;
  __REG32  ACTIVE35       : 1;
  __REG32  ACTIVE36       : 1;
  __REG32  ACTIVE37       : 1;
  __REG32  ACTIVE38       : 1;
  __REG32  ACTIVE39       : 1;
  __REG32  ACTIVE40       : 1;
  __REG32  ACTIVE41       : 1;
  __REG32  ACTIVE42       : 1;
  __REG32  ACTIVE43       : 1;
  __REG32  ACTIVE44       : 1;
  __REG32  ACTIVE45       : 1;
  __REG32  ACTIVE46       : 1;
  __REG32  ACTIVE47       : 1;
  __REG32  ACTIVE48       : 1;
  __REG32  ACTIVE49       : 1;
  __REG32  ACTIVE50       : 1;
  __REG32  ACTIVE51       : 1;
  __REG32  ACTIVE52       : 1;
  __REG32  ACTIVE53       : 1;
  __REG32  ACTIVE54       : 1;
  __REG32  ACTIVE55       : 1;
  __REG32  ACTIVE56       : 1;
  __REG32  ACTIVE57       : 1;
  __REG32  ACTIVE58       : 1;
  __REG32  ACTIVE59       : 1;
  __REG32  ACTIVE60       : 1;
  __REG32  ACTIVE61       : 1;
  __REG32  ACTIVE62       : 1;
  __REG32  ACTIVE63       : 1;
} __active1_bits;

/* Interrupt Priority Registers 0-3 */
typedef struct {
  __REG32  PRI_0          : 8;
  __REG32  PRI_1          : 8;
  __REG32  PRI_2          : 8;
  __REG32  PRI_3          : 8;
} __pri0_bits;

/* Interrupt Priority Registers 4-7 */
typedef struct {
  __REG32  PRI_4          : 8;
  __REG32  PRI_5          : 8;
  __REG32  PRI_6          : 8;
  __REG32  PRI_7          : 8;
} __pri1_bits;

/* Interrupt Priority Registers 8-11 */
typedef struct {
  __REG32  PRI_8          : 8;
  __REG32  PRI_9          : 8;
  __REG32  PRI_10         : 8;
  __REG32  PRI_11         : 8;
} __pri2_bits;

/* Interrupt Priority Registers 12-15 */
typedef struct {
  __REG32  PRI_12         : 8;
  __REG32  PRI_13         : 8;
  __REG32  PRI_14         : 8;
  __REG32  PRI_15         : 8;
} __pri3_bits;

/* Interrupt Priority Registers 16-19 */
typedef struct {
  __REG32  PRI_16         : 8;
  __REG32  PRI_17         : 8;
  __REG32  PRI_18         : 8;
  __REG32  PRI_19         : 8;
} __pri4_bits;

/* Interrupt Priority Registers 20-23 */
typedef struct {
  __REG32  PRI_20         : 8;
  __REG32  PRI_21         : 8;
  __REG32  PRI_22         : 8;
  __REG32  PRI_23         : 8;
} __pri5_bits;

/* Interrupt Priority Registers 24-27 */
typedef struct {
  __REG32  PRI_24         : 8;
  __REG32  PRI_25         : 8;
  __REG32  PRI_26         : 8;
  __REG32  PRI_27         : 8;
} __pri6_bits;

/* Interrupt Priority Registers 28-31 */
typedef struct {
  __REG32  PRI_28         : 8;
  __REG32  PRI_29         : 8;
  __REG32  PRI_30         : 8;
  __REG32  PRI_31         : 8;
} __pri7_bits;

/* Interrupt Priority Registers 32-35 */
typedef struct {
  __REG32  PRI_32         : 8;
  __REG32  PRI_33         : 8;
  __REG32  PRI_34         : 8;
  __REG32  PRI_35         : 8;
} __pri8_bits;

/* Interrupt Priority Registers 36-39 */
typedef struct {
  __REG32  PRI_36         : 8;
  __REG32  PRI_37         : 8;
  __REG32  PRI_38         : 8;
  __REG32  PRI_39         : 8;
} __pri9_bits;

/* Interrupt Priority Registers 40-43 */
typedef struct {
  __REG32  PRI_40         : 8;
  __REG32  PRI_41         : 8;
  __REG32  PRI_42         : 8;
  __REG32  PRI_43         : 8;
} __pri10_bits;

/* Interrupt Priority Registers 44-47 */
typedef struct {
  __REG32  PRI_44         : 8;
  __REG32  PRI_45         : 8;
  __REG32  PRI_46         : 8;
  __REG32  PRI_47         : 8;
} __pri11_bits;

/* Interrupt Priority Registers 48-51 */
typedef struct {
  __REG32  PRI_48         : 8;
  __REG32  PRI_49         : 8;
  __REG32  PRI_50         : 8;
  __REG32  PRI_51         : 8;
} __pri12_bits;

/* Interrupt Priority Registers 52-55 */
typedef struct {
  __REG32  PRI_52         : 8;
  __REG32  PRI_53         : 8;
  __REG32  PRI_54         : 8;
  __REG32  PRI_55         : 8;
} __pri13_bits;

/* Interrupt Priority Registers 56-59 */
typedef struct {
  __REG32  PRI_56         : 8;
  __REG32  PRI_57         : 8;
  __REG32  PRI_58         : 8;
  __REG32  PRI_59         : 8;
} __pri14_bits;

/* Interrupt Priority Registers 60-63 */
typedef struct {
  __REG32  PRI_60         : 8;
  __REG32  PRI_61         : 8;
  __REG32  PRI_62         : 8;
  __REG32  PRI_63         : 8;
} __pri15_bits;

/* CPU ID Base Register */
typedef struct {
  __REG32  REVISION       : 4;
  __REG32  PARTNO         :12;
  __REG32                 : 4;
  __REG32  VARIANT        : 4;
  __REG32  IMPLEMENTER    : 8;
} __cpuidbr_bits;

/* Interrupt Control State Register */
typedef struct {
  __REG32  VECTACTIVE     :10;
  __REG32                 : 1;
  __REG32  RETTOBASE      : 1;
  __REG32  VECTPENDING    :10;
  __REG32  ISRPENDING     : 1;
  __REG32  ISRPREEMPT     : 1;
  __REG32                 : 1;
  __REG32  PENDSTCLR      : 1;
  __REG32  PENDSTSET      : 1;
  __REG32  PENDSVCLR      : 1;
  __REG32  PENDSVSET      : 1;
  __REG32                 : 2;
  __REG32  NMIPENDSET     : 1;
} __icsr_bits;

/* Vector Table Offset Register */
typedef struct {
  __REG32                 : 7;
  __REG32  TBLOFF         :22;
  __REG32  TBLBASE        : 1;
  __REG32                 : 2;
} __vtor_bits;

/* Application Interrupt and Reset Control Register */
typedef struct {
  __REG32  VECTRESET      : 1;
  __REG32  VECTCLRACTIVE  : 1;
  __REG32  SYSRESETREQ    : 1;
  __REG32                 : 5;
  __REG32  PRIGROUP       : 3;
  __REG32                 : 4;
  __REG32  ENDIANESS      : 1;
  __REG32  VECTKEY        :16;
} __aircr_bits;

/* System Control Register */
typedef struct {
  __REG32                 : 1;
  __REG32  SLEEPONEXIT    : 1;
  __REG32  SLEEPDEEP      : 1;
  __REG32                 : 1;
  __REG32  SEVONPEND      : 1;
  __REG32                 :27;
} __scr_bits;

/* Configuration Control Register */
typedef struct {
  __REG32  NONEBASETHRDENA: 1;
  __REG32  USERSETMPEND   : 1;
  __REG32                 : 1;
  __REG32  UNALIGN_TRP    : 1;
  __REG32  DIV_0_TRP      : 1;
  __REG32                 : 3;
  __REG32  BFHFNMIGN      : 1;
  __REG32  STKALIGN       : 1;
  __REG32                 :22;
} __ccr_bits;

/* System Handler Control and State Register */
typedef struct {
  __REG32  MEMFAULTACT    : 1;
  __REG32  BUSFAULTACT    : 1;
  __REG32                 : 1;
  __REG32  USGFAULTACT    : 1;
  __REG32                 : 3;
  __REG32  SVCALLACT      : 1;
  __REG32  MONITORACT     : 1;
  __REG32                 : 1;
  __REG32  PENDSVACT      : 1;
  __REG32  SYSTICKACT     : 1;
  __REG32                 : 1;
  __REG32  MEMFAULTPENDED : 1;
  __REG32  BUSFAULTPENDED : 1;
  __REG32  SVCALLPENDED   : 1;
  __REG32  MEMFAULTENA    : 1;
  __REG32  BUSFAULTENA    : 1;
  __REG32  USGFAULTENA    : 1;
  __REG32                 :13;
} __shcsr_bits;

/* Configurable Fault Status Registers */
typedef struct {
  __REG32  IACCVIOL       : 1;
  __REG32  DACCVIOL       : 1;
  __REG32                 : 1;
  __REG32  MUNSTKERR      : 1;
  __REG32  MSTKERR        : 1;
  __REG32                 : 2;
  __REG32  MMARVALID      : 1;
  __REG32  IBUSERR        : 1;
  __REG32  PRECISERR      : 1;
  __REG32  IMPRECISERR    : 1;
  __REG32  UNSTKERR       : 1;
  __REG32  STKERR         : 1;
  __REG32                 : 2;
  __REG32  BFARVALID      : 1;
  __REG32  UNDEFINSTR     : 1;
  __REG32  INVSTATE       : 1;
  __REG32  INVPC          : 1;
  __REG32  NOCP           : 1;
  __REG32                 : 4;
  __REG32  UNALIGNED      : 1;
  __REG32  DIVBYZERO      : 1;
  __REG32                 : 6;
} __cfsr_bits;

/* Hard Fault Status Register */
typedef struct {
  __REG32                 : 1;
  __REG32  VECTTBL        : 1;
  __REG32                 :28;
  __REG32  FORCED         : 1;
  __REG32  DEBUGEVT       : 1;
} __hfsr_bits;

/* Debug Fault Status Register */
typedef struct {
  __REG32  HALTED         : 1;
  __REG32  BKPT           : 1;
  __REG32  DWTTRAP        : 1;
  __REG32  VCATCH         : 1;
  __REG32  EXTERNAL       : 1;
  __REG32                 :27;
} __dfsr_bits;

/* Software Trigger Interrupt Register */
typedef struct {
  __REG32  INTID          : 9;
  __REG32                 :23;
} __stir_bits;

/* Pin function select register 0 */
typedef struct{
__REG32 P0_0   : 2;
__REG32 P0_1   : 2;
__REG32 P0_2   : 2;
__REG32 P0_3   : 2;
__REG32 P0_4   : 2;
__REG32 P0_5   : 2;
__REG32 P0_6   : 2;
__REG32 P0_7   : 2;
__REG32 P0_8   : 2;
__REG32 P0_9   : 2;
__REG32 P0_10  : 2;
__REG32 P0_11  : 2;
__REG32 P0_12  : 2;
__REG32 P0_13  : 2;
__REG32 P0_14  : 2;
__REG32 P0_15  : 2;
} __pinsel0_bits;

/* Pin function select register 1 */
typedef struct{
__REG32 P0_16  : 2;
__REG32 P0_17  : 2;
__REG32 P0_18  : 2;
__REG32 P0_19  : 2;
__REG32 P0_20  : 2;
__REG32 P0_21  : 2;
__REG32 P0_22  : 2;
__REG32 P0_23  : 2;
__REG32 P0_24  : 2;
__REG32 P0_25  : 2;
__REG32 P0_26  : 2;
__REG32 P0_27  : 2;
__REG32 P0_28  : 2;
__REG32 P0_29  : 2;
__REG32 P0_30  : 2;
__REG32 P0_31  : 2;
} __pinsel1_bits;

/* Pin function select register 2 */
typedef struct{
__REG32 P1_0   : 2;
__REG32 P1_1   : 2;
__REG32 P1_2   : 2;
__REG32 P1_3   : 2;
__REG32 P1_4   : 2;
__REG32 P1_5   : 2;
__REG32 P1_6   : 2;
__REG32 P1_7   : 2;
__REG32 P1_8   : 2;
__REG32 P1_9   : 2;
__REG32 P1_10  : 2;
__REG32 P1_11  : 2;
__REG32 P1_12  : 2;
__REG32 P1_13  : 2;
__REG32 P1_14  : 2;
__REG32 P1_15  : 2;
} __pinsel2_bits;

/* Pin function select register 3 */
typedef struct{
__REG32 P1_16  : 2;
__REG32 P1_17  : 2;
__REG32 P1_18  : 2;
__REG32 P1_19  : 2;
__REG32 P1_20  : 2;
__REG32 P1_21  : 2;
__REG32 P1_22  : 2;
__REG32 P1_23  : 2;
__REG32 P1_24  : 2;
__REG32 P1_25  : 2;
__REG32 P1_26  : 2;
__REG32 P1_27  : 2;
__REG32 P1_28  : 2;
__REG32 P1_29  : 2;
__REG32 P1_30  : 2;
__REG32 P1_31  : 2;
} __pinsel3_bits;

/* Pin function select register 4 */
typedef struct{
__REG32 P2_0   : 2;
__REG32 P2_1   : 2;
__REG32 P2_2   : 2;
__REG32 P2_3   : 2;
__REG32 P2_4   : 2;
__REG32 P2_5   : 2;
__REG32 P2_6   : 2;
__REG32 P2_7   : 2;
__REG32 P2_8   : 2;
__REG32 P2_9   : 2;
__REG32 P2_10  : 2;
__REG32 P2_11  : 2;
__REG32 P2_12  : 2;
__REG32 P2_13  : 2;
__REG32 P2_14  : 2;
__REG32 P2_15  : 2;
} __pinsel4_bits;

/* Pin function select register 5 */
typedef struct{
__REG32 P2_16  : 2;
__REG32 P2_17  : 2;
__REG32 P2_18  : 2;
__REG32 P2_19  : 2;
__REG32 P2_20  : 2;
__REG32 P2_21  : 2;
__REG32 P2_22  : 2;
__REG32 P2_23  : 2;
__REG32 P2_24  : 2;
__REG32 P2_25  : 2;
__REG32 P2_26  : 2;
__REG32 P2_27  : 2;
__REG32 P2_28  : 2;
__REG32 P2_29  : 2;
__REG32 P2_30  : 2;
__REG32 P2_31  : 2;
} __pinsel5_bits;

/* Pin function select register 6 */
typedef struct{
__REG32 P3_0   : 2;
__REG32 P3_1   : 2;
__REG32 P3_2   : 2;
__REG32 P3_3   : 2;
__REG32 P3_4   : 2;
__REG32 P3_5   : 2;
__REG32 P3_6   : 2;
__REG32 P3_7   : 2;
__REG32 P3_8   : 2;
__REG32 P3_9   : 2;
__REG32 P3_10  : 2;
__REG32 P3_11  : 2;
__REG32 P3_12  : 2;
__REG32 P3_13  : 2;
__REG32 P3_14  : 2;
__REG32 P3_15  : 2;
} __pinsel6_bits;

/* Pin function select register 7 */
typedef struct{
__REG32 P3_16  : 2;
__REG32 P3_17  : 2;
__REG32 P3_18  : 2;
__REG32 P3_19  : 2;
__REG32 P3_20  : 2;
__REG32 P3_21  : 2;
__REG32 P3_22  : 2;
__REG32 P3_23  : 2;
__REG32 P3_24  : 2;
__REG32 P3_25  : 2;
__REG32 P3_26  : 2;
__REG32 P3_27  : 2;
__REG32 P3_28  : 2;
__REG32 P3_29  : 2;
__REG32 P3_30  : 2;
__REG32 P3_31  : 2;
} __pinsel7_bits;

/* Pin function select register 8 */
typedef struct{
__REG32 P4_0   : 2;
__REG32 P4_1   : 2;
__REG32 P4_2   : 2;
__REG32 P4_3   : 2;
__REG32 P4_4   : 2;
__REG32 P4_5   : 2;
__REG32 P4_6   : 2;
__REG32 P4_7   : 2;
__REG32 P4_8   : 2;
__REG32 P4_9   : 2;
__REG32 P4_10  : 2;
__REG32 P4_11  : 2;
__REG32 P4_12  : 2;
__REG32 P4_13  : 2;
__REG32 P4_14  : 2;
__REG32 P4_15  : 2;
} __pinsel8_bits;

/* Pin function select register 9 */
typedef struct{
__REG32 P4_16  : 2;
__REG32 P4_17  : 2;
__REG32 P4_18  : 2;
__REG32 P4_19  : 2;
__REG32 P4_20  : 2;
__REG32 P4_21  : 2;
__REG32 P4_22  : 2;
__REG32 P4_23  : 2;
__REG32 P4_24  : 2;
__REG32 P4_25  : 2;
__REG32 P4_26  : 2;
__REG32 P4_27  : 2;
__REG32 P4_28  : 2;
__REG32 P4_29  : 2;
__REG32 P4_30  : 2;
__REG32 P4_31  : 2;
} __pinsel9_bits;

/* Pin function select register 10 */
typedef struct{
__REG32             : 3;
__REG32 GPIO_TRACE  : 1;
__REG32             :28;
} __pinsel10_bits;

/* I2C Pin Configuration register */
typedef struct{
__REG32 SDADRV0     : 1;
__REG32 SDAI2C0     : 1;
__REG32 SCLDRV0     : 1;
__REG32 SCLI2C0     : 1;
__REG32             :28;
} __i2cpadcfg_bits;

/* GPIO 0 Registers */
typedef struct {
__REG32 P0_0   : 1;
__REG32 P0_1   : 1;
__REG32 P0_2   : 1;
__REG32 P0_3   : 1;
__REG32 P0_4   : 1;
__REG32 P0_5   : 1;
__REG32 P0_6   : 1;
__REG32 P0_7   : 1;
__REG32 P0_8   : 1;
__REG32 P0_9   : 1;
__REG32 P0_10  : 1;
__REG32 P0_11  : 1;
__REG32 P0_12  : 1;
__REG32 P0_13  : 1;
__REG32 P0_14  : 1;
__REG32 P0_15  : 1;
__REG32 P0_16  : 1;
__REG32 P0_17  : 1;
__REG32 P0_18  : 1;
__REG32 P0_19  : 1;
__REG32 P0_20  : 1;
__REG32 P0_21  : 1;
__REG32 P0_22  : 1;
__REG32 P0_23  : 1;
__REG32 P0_24  : 1;
__REG32 P0_25  : 1;
__REG32 P0_26  : 1;
__REG32 P0_27  : 1;
__REG32 P0_28  : 1;
__REG32 P0_29  : 1;
__REG32 P0_30  : 1;
__REG32 P0_31  : 1;
} __gpio0_bits;

/* FGPIO 0 Registers*/
typedef union{
  //FIO0DIR
  //FIO0MASK
  //FIO0PIN
  //FIO0SET
  //FIO0CLR
  struct {
    __REG32 P0_0   : 1;
    __REG32 P0_1   : 1;
    __REG32 P0_2   : 1;
    __REG32 P0_3   : 1;
    __REG32 P0_4   : 1;
    __REG32 P0_5   : 1;
    __REG32 P0_6   : 1;
    __REG32 P0_7   : 1;
    __REG32 P0_8   : 1;
    __REG32 P0_9   : 1;
    __REG32 P0_10  : 1;
    __REG32 P0_11  : 1;
    __REG32 P0_12  : 1;
    __REG32 P0_13  : 1;
    __REG32 P0_14  : 1;
    __REG32 P0_15  : 1;
    __REG32 P0_16  : 1;
    __REG32 P0_17  : 1;
    __REG32 P0_18  : 1;
    __REG32 P0_19  : 1;
    __REG32 P0_20  : 1;
    __REG32 P0_21  : 1;
    __REG32 P0_22  : 1;
    __REG32 P0_23  : 1;
    __REG32 P0_24  : 1;
    __REG32 P0_25  : 1;
    __REG32 P0_26  : 1;
    __REG32 P0_27  : 1;
    __REG32 P0_28  : 1;
    __REG32 P0_29  : 1;
    __REG32 P0_30  : 1;
    __REG32 P0_31  : 1;
  };

  struct
  {
    union
    {
    //FIO0DIR0
    //FIO0MASK0
    //FIO0PIN0
    //FIO0SET0
    //FIO0CLR0
      struct{
        __REG8  P0_0   : 1;
        __REG8  P0_1   : 1;
        __REG8  P0_2   : 1;
        __REG8  P0_3   : 1;
        __REG8  P0_4   : 1;
        __REG8  P0_5   : 1;
        __REG8  P0_6   : 1;
        __REG8  P0_7   : 1;
      } __byte0_bit;
      __REG8 __byte0;
    };
    union
    {
    //FIO0DIR1
    //FIO0MASK1
    //FIO0PIN1
    //FIO0SET1
    //FIO0CLR1
      struct{
        __REG8  P0_0   : 1;
        __REG8  P0_1   : 1;
        __REG8  P0_2   : 1;
        __REG8  P0_3   : 1;
        __REG8  P0_4   : 1;
        __REG8  P0_5   : 1;
        __REG8  P0_6   : 1;
        __REG8  P0_7   : 1;
      } __byte1_bit;
      __REG8 __byte1;
    };
    union
    {
     //FIO0DIR2
     //FIO0MASK2
     //FIO0PIN2
     //FIO0SET2
     //FIO0CLR2
      struct{
        __REG8  P0_0   : 1;
        __REG8  P0_1   : 1;
        __REG8  P0_2   : 1;
        __REG8  P0_3   : 1;
        __REG8  P0_4   : 1;
        __REG8  P0_5   : 1;
        __REG8  P0_6   : 1;
        __REG8  P0_7   : 1;
      } __byte2_bit;
      __REG8 __byte2;
    };
    union
    {
      //FIO0DIR3
      //FIO0MASK3
      //FIO0PIN3
      //FIO0SET3
      //FIO0CLR3
      struct{
        __REG8  P0_0   : 1;
        __REG8  P0_1   : 1;
        __REG8  P0_2   : 1;
        __REG8  P0_3   : 1;
        __REG8  P0_4   : 1;
        __REG8  P0_5   : 1;
        __REG8  P0_6   : 1;
        __REG8  P0_7   : 1;
      } __byte3_bit;
      __REG8 __byte3;
    };
  };

  struct
  {
    union
    {
      //FIO0DIRL
      //FIO0MASKL
      //FIO0PINL
      //FIO0SETL
      //FIO0CLRL
      struct{
        __REG16 P0_0   : 1;
        __REG16 P0_1   : 1;
        __REG16 P0_2   : 1;
        __REG16 P0_3   : 1;
        __REG16 P0_4   : 1;
        __REG16 P0_5   : 1;
        __REG16 P0_6   : 1;
        __REG16 P0_7   : 1;
        __REG16 P0_8   : 1;
        __REG16 P0_9   : 1;
        __REG16 P0_10  : 1;
        __REG16 P0_11  : 1;
        __REG16 P0_12  : 1;
        __REG16 P0_13  : 1;
        __REG16 P0_14  : 1;
        __REG16 P0_15  : 1;
      } __shortl_bit;
      __REG16 __shortl;
    };
    union
    {
      //FIO0DIRU
      //FIO0MASKU
      //FIO0PINU
      //FIO0SETU
      //FIO0CLRU
      struct{
        __REG16 P0_0   : 1;
        __REG16 P0_1   : 1;
        __REG16 P0_2   : 1;
        __REG16 P0_3   : 1;
        __REG16 P0_4   : 1;
        __REG16 P0_5   : 1;
        __REG16 P0_6   : 1;
        __REG16 P0_7   : 1;
        __REG16 P0_8   : 1;
        __REG16 P0_9   : 1;
        __REG16 P0_10  : 1;
        __REG16 P0_11  : 1;
        __REG16 P0_12  : 1;
        __REG16 P0_13  : 1;
        __REG16 P0_14  : 1;
        __REG16 P0_15  : 1;
      } __shortu_bit;
      __REG16 __shortu;
    };
  };
} __fgpio0_bits;

/* GPIO 1 Registers */
typedef struct {
__REG32 P1_0   : 1;
__REG32 P1_1   : 1;
__REG32 P1_2   : 1;
__REG32 P1_3   : 1;
__REG32 P1_4   : 1;
__REG32 P1_5   : 1;
__REG32 P1_6   : 1;
__REG32 P1_7   : 1;
__REG32 P1_8   : 1;
__REG32 P1_9   : 1;
__REG32 P1_10  : 1;
__REG32 P1_11  : 1;
__REG32 P1_12  : 1;
__REG32 P1_13  : 1;
__REG32 P1_14  : 1;
__REG32 P1_15  : 1;
__REG32 P1_16  : 1;
__REG32 P1_17  : 1;
__REG32 P1_18  : 1;
__REG32 P1_19  : 1;
__REG32 P1_20  : 1;
__REG32 P1_21  : 1;
__REG32 P1_22  : 1;
__REG32 P1_23  : 1;
__REG32 P1_24  : 1;
__REG32 P1_25  : 1;
__REG32 P1_26  : 1;
__REG32 P1_27  : 1;
__REG32 P1_28  : 1;
__REG32 P1_29  : 1;
__REG32 P1_30  : 1;
__REG32 P1_31  : 1;
} __gpio1_bits;

/* FGPIO 1 Registers*/
typedef union{
  //FIO1DIR
  //FIO1MASK
  //FIO1PIN
  //FIO1SET
  //FIO1CLR
  struct {
    __REG32 P1_0   : 1;
    __REG32 P1_1   : 1;
    __REG32 P1_2   : 1;
    __REG32 P1_3   : 1;
    __REG32 P1_4   : 1;
    __REG32 P1_5   : 1;
    __REG32 P1_6   : 1;
    __REG32 P1_7   : 1;
    __REG32 P1_8   : 1;
    __REG32 P1_9   : 1;
    __REG32 P1_10  : 1;
    __REG32 P1_11  : 1;
    __REG32 P1_12  : 1;
    __REG32 P1_13  : 1;
    __REG32 P1_14  : 1;
    __REG32 P1_15  : 1;
    __REG32 P1_16  : 1;
    __REG32 P1_17  : 1;
    __REG32 P1_18  : 1;
    __REG32 P1_19  : 1;
    __REG32 P1_20  : 1;
    __REG32 P1_21  : 1;
    __REG32 P1_22  : 1;
    __REG32 P1_23  : 1;
    __REG32 P1_24  : 1;
    __REG32 P1_25  : 1;
    __REG32 P1_26  : 1;
    __REG32 P1_27  : 1;
    __REG32 P1_28  : 1;
    __REG32 P1_29  : 1;
    __REG32 P1_30  : 1;
    __REG32 P1_31  : 1;
  };

  struct
  {
    union
    {
      //FIO1DIR0
      //FIO1MASK0
      //FIO1PIN0
      //FIO1SET0
      //FIO1CLR0
      struct{
        __REG8  P1_0   : 1;
        __REG8  P1_1   : 1;
        __REG8  P1_2   : 1;
        __REG8  P1_3   : 1;
        __REG8  P1_4   : 1;
        __REG8  P1_5   : 1;
        __REG8  P1_6   : 1;
        __REG8  P1_7   : 1;
      } __byte0_bit;
      __REG8 __byte0;
    };
    union
    {
      //FIO1DIR1
      //FIO1MASK1
      //FIO1PIN1
      //FIO1SET1
      //FIO1CLR1
      struct{
        __REG8  P1_0   : 1;
        __REG8  P1_1   : 1;
        __REG8  P1_2   : 1;
        __REG8  P1_3   : 1;
        __REG8  P1_4   : 1;
        __REG8  P1_5   : 1;
        __REG8  P1_6   : 1;
        __REG8  P1_7   : 1;
      } __byte1_bit;
      __REG8 __byte1;
    };
    union
    {
      //FIO1DIR2
      //FIO1MASK2
      //FIO1PIN2
      //FIO1SET2
      //FIO1CLR2
      struct{
        __REG8  P1_0   : 1;
        __REG8  P1_1   : 1;
        __REG8  P1_2   : 1;
        __REG8  P1_3   : 1;
        __REG8  P1_4   : 1;
        __REG8  P1_5   : 1;
        __REG8  P1_6   : 1;
        __REG8  P1_7   : 1;
      } __byte2_bit;
      __REG8 __byte2;
    };
    union
    {
      //FIO1DIR3
      //FIO1MASK3
      //FIO1PIN3
      //FIO1SET3
      //FIO1CLR3
      struct{
        __REG8  P1_0   : 1;
        __REG8  P1_1   : 1;
        __REG8  P1_2   : 1;
        __REG8  P1_3   : 1;
        __REG8  P1_4   : 1;
        __REG8  P1_5   : 1;
        __REG8  P1_6   : 1;
        __REG8  P1_7   : 1;
      } __byte3_bit;
      __REG8 __byte3;
    };
  };

  struct
  {
    union
    {
      //FIO1DIRL
      //FIO1MASKL
      //FIO1PINL
      //FIO1SETL
      //FIO1CLRL
      struct{
        __REG16 P1_0   : 1;
        __REG16 P1_1   : 1;
        __REG16 P1_2   : 1;
        __REG16 P1_3   : 1;
        __REG16 P1_4   : 1;
        __REG16 P1_5   : 1;
        __REG16 P1_6   : 1;
        __REG16 P1_7   : 1;
        __REG16 P1_8   : 1;
        __REG16 P1_9   : 1;
        __REG16 P1_10  : 1;
        __REG16 P1_11  : 1;
        __REG16 P1_12  : 1;
        __REG16 P1_13  : 1;
        __REG16 P1_14  : 1;
        __REG16 P1_15  : 1;
      } __shortl_bit;
      __REG16 __shortl;
    };
    union
    {
      //FIO1DIRU
      //FIO1MASKU
      //FIO1PINU
      //FIO1SETU
      //FIO1CLRU
      struct{
        __REG16 P1_0   : 1;
        __REG16 P1_1   : 1;
        __REG16 P1_2   : 1;
        __REG16 P1_3   : 1;
        __REG16 P1_4   : 1;
        __REG16 P1_5   : 1;
        __REG16 P1_6   : 1;
        __REG16 P1_7   : 1;
        __REG16 P1_8   : 1;
        __REG16 P1_9   : 1;
        __REG16 P1_10  : 1;
        __REG16 P1_11  : 1;
        __REG16 P1_12  : 1;
        __REG16 P1_13  : 1;
        __REG16 P1_14  : 1;
        __REG16 P1_15  : 1;
      } __shortu_bit;
      __REG16 __shortu;
    };
  };
} __fgpio1_bits;

/* GPIO 2 Registers */
typedef struct {
__REG32 P2_0   : 1;
__REG32 P2_1   : 1;
__REG32 P2_2   : 1;
__REG32 P2_3   : 1;
__REG32 P2_4   : 1;
__REG32 P2_5   : 1;
__REG32 P2_6   : 1;
__REG32 P2_7   : 1;
__REG32 P2_8   : 1;
__REG32 P2_9   : 1;
__REG32 P2_10  : 1;
__REG32 P2_11  : 1;
__REG32 P2_12  : 1;
__REG32 P2_13  : 1;
__REG32 P2_14  : 1;
__REG32 P2_15  : 1;
__REG32 P2_16  : 1;
__REG32 P2_17  : 1;
__REG32 P2_18  : 1;
__REG32 P2_19  : 1;
__REG32 P2_20  : 1;
__REG32 P2_21  : 1;
__REG32 P2_22  : 1;
__REG32 P2_23  : 1;
__REG32 P2_24  : 1;
__REG32 P2_25  : 1;
__REG32 P2_26  : 1;
__REG32 P2_27  : 1;
__REG32 P2_28  : 1;
__REG32 P2_29  : 1;
__REG32 P2_30  : 1;
__REG32 P2_31  : 1;
} __gpio2_bits;

/* FGPIO 2 Registers*/
typedef union{
  //FIO2DIR
  //FIO2MASK
  //FIO2PIN
  //FIO2SET
  //FIO2CLR
  struct {
    __REG32 P2_0   : 1;
    __REG32 P2_1   : 1;
    __REG32 P2_2   : 1;
    __REG32 P2_3   : 1;
    __REG32 P2_4   : 1;
    __REG32 P2_5   : 1;
    __REG32 P2_6   : 1;
    __REG32 P2_7   : 1;
    __REG32 P2_8   : 1;
    __REG32 P2_9   : 1;
    __REG32 P2_10  : 1;
    __REG32 P2_11  : 1;
    __REG32 P2_12  : 1;
    __REG32 P2_13  : 1;
    __REG32 P2_14  : 1;
    __REG32 P2_15  : 1;
    __REG32 P2_16  : 1;
    __REG32 P2_17  : 1;
    __REG32 P2_18  : 1;
    __REG32 P2_19  : 1;
    __REG32 P2_20  : 1;
    __REG32 P2_21  : 1;
    __REG32 P2_22  : 1;
    __REG32 P2_23  : 1;
    __REG32 P2_24  : 1;
    __REG32 P2_25  : 1;
    __REG32 P2_26  : 1;
    __REG32 P2_27  : 1;
    __REG32 P2_28  : 1;
    __REG32 P2_29  : 1;
    __REG32 P2_30  : 1;
    __REG32 P2_31  : 1;
  };

  struct
  {
    union
    {
      //FIO2DIR0
      //FIO2MASK0
      //FIO2PIN0
      //FIO2SET0
      //FIO2CLR0
      struct{
        __REG8  P2_0   : 1;
        __REG8  P2_1   : 1;
        __REG8  P2_2   : 1;
        __REG8  P2_3   : 1;
        __REG8  P2_4   : 1;
        __REG8  P2_5   : 1;
        __REG8  P2_6   : 1;
        __REG8  P2_7   : 1;
      } __byte0_bit;
      __REG8 __byte0;
    };
    union
    {
      //FIO2DIR1
      //FIO2MASK1
      //FIO2PIN1
      //FIO2SET1
      //FIO2CLR1
      struct{
        __REG8  P2_0   : 1;
        __REG8  P2_1   : 1;
        __REG8  P2_2   : 1;
        __REG8  P2_3   : 1;
        __REG8  P2_4   : 1;
        __REG8  P2_5   : 1;
        __REG8  P2_6   : 1;
        __REG8  P2_7   : 1;
      } __byte1_bit;
      __REG8 __byte1;
    };
    union
    {
      //FIO2DIR2
      //FIO2MASK2
      //FIO2PIN2
      //FIO2SET2
      //FIO2CLR2
      struct{
        __REG8  P2_0   : 1;
        __REG8  P2_1   : 1;
        __REG8  P2_2   : 1;
        __REG8  P2_3   : 1;
        __REG8  P2_4   : 1;
        __REG8  P2_5   : 1;
        __REG8  P2_6   : 1;
        __REG8  P2_7   : 1;
      } __byte2_bit;
      __REG8 __byte2;
    };
    union
    {
      //FIO2DIR3
      //FIO2MASK3
      //FIO2PIN3
      //FIO2SET3
      //FIO2CLR3
      struct{
        __REG8  P2_0   : 1;
        __REG8  P2_1   : 1;
        __REG8  P2_2   : 1;
        __REG8  P2_3   : 1;
        __REG8  P2_4   : 1;
        __REG8  P2_5   : 1;
        __REG8  P2_6   : 1;
        __REG8  P2_7   : 1;
      } __byte3_bit;
      __REG8 __byte3;
    };
  };

  struct
  {
    union
    {
      //FIO2DIRL
      //FIO2MASKL
      //FIO2PINL
      //FIO2SETL
      //FIO2CLRL
      struct{
        __REG16 P2_0   : 1;
        __REG16 P2_1   : 1;
        __REG16 P2_2   : 1;
        __REG16 P2_3   : 1;
        __REG16 P2_4   : 1;
        __REG16 P2_5   : 1;
        __REG16 P2_6   : 1;
        __REG16 P2_7   : 1;
        __REG16 P2_8   : 1;
        __REG16 P2_9   : 1;
        __REG16 P2_10  : 1;
        __REG16 P2_11  : 1;
        __REG16 P2_12  : 1;
        __REG16 P2_13  : 1;
        __REG16 P2_14  : 1;
        __REG16 P2_15  : 1;
      } __shortl_bit;
      __REG16 __shortl;
    };
    union
    {
      //FIO2DIRU
      //FIO2MASKU
      //FIO2PINU
      //FIO2SETU
      //FIO2CLRU
      struct{
        __REG16 P2_0   : 1;
        __REG16 P2_1   : 1;
        __REG16 P2_2   : 1;
        __REG16 P2_3   : 1;
        __REG16 P2_4   : 1;
        __REG16 P2_5   : 1;
        __REG16 P2_6   : 1;
        __REG16 P2_7   : 1;
        __REG16 P2_8   : 1;
        __REG16 P2_9   : 1;
        __REG16 P2_10  : 1;
        __REG16 P2_11  : 1;
        __REG16 P2_12  : 1;
        __REG16 P2_13  : 1;
        __REG16 P2_14  : 1;
        __REG16 P2_15  : 1;
      } __shortu_bit;
      __REG16 __shortu;
    };
  };
} __fgpio2_bits;

/* GPIO 3 Registers */
typedef struct {
__REG32 P3_0   : 1;
__REG32 P3_1   : 1;
__REG32 P3_2   : 1;
__REG32 P3_3   : 1;
__REG32 P3_4   : 1;
__REG32 P3_5   : 1;
__REG32 P3_6   : 1;
__REG32 P3_7   : 1;
__REG32 P3_8   : 1;
__REG32 P3_9   : 1;
__REG32 P3_10  : 1;
__REG32 P3_11  : 1;
__REG32 P3_12  : 1;
__REG32 P3_13  : 1;
__REG32 P3_14  : 1;
__REG32 P3_15  : 1;
__REG32 P3_16  : 1;
__REG32 P3_17  : 1;
__REG32 P3_18  : 1;
__REG32 P3_19  : 1;
__REG32 P3_20  : 1;
__REG32 P3_21  : 1;
__REG32 P3_22  : 1;
__REG32 P3_23  : 1;
__REG32 P3_24  : 1;
__REG32 P3_25  : 1;
__REG32 P3_26  : 1;
__REG32 P3_27  : 1;
__REG32 P3_28  : 1;
__REG32 P3_29  : 1;
__REG32 P3_30  : 1;
__REG32 P3_31  : 1;
} __gpio3_bits;

/* FGPIO 3 Registers*/
typedef union{
  //FIO3DIR
  //FIO3MASK
  //FIO3PIN
  //FIO3SET
  //FIO3CLR
  struct {
    __REG32 P3_0   : 1;
    __REG32 P3_1   : 1;
    __REG32 P3_2   : 1;
    __REG32 P3_3   : 1;
    __REG32 P3_4   : 1;
    __REG32 P3_5   : 1;
    __REG32 P3_6   : 1;
    __REG32 P3_7   : 1;
    __REG32 P3_8   : 1;
    __REG32 P3_9   : 1;
    __REG32 P3_10  : 1;
    __REG32 P3_11  : 1;
    __REG32 P3_12  : 1;
    __REG32 P3_13  : 1;
    __REG32 P3_14  : 1;
    __REG32 P3_15  : 1;
    __REG32 P3_16  : 1;
    __REG32 P3_17  : 1;
    __REG32 P3_18  : 1;
    __REG32 P3_19  : 1;
    __REG32 P3_20  : 1;
    __REG32 P3_21  : 1;
    __REG32 P3_22  : 1;
    __REG32 P3_23  : 1;
    __REG32 P3_24  : 1;
    __REG32 P3_25  : 1;
    __REG32 P3_26  : 1;
    __REG32 P3_27  : 1;
    __REG32 P3_28  : 1;
    __REG32 P3_29  : 1;
    __REG32 P3_30  : 1;
    __REG32 P3_31  : 1;
  };

  struct
  {
    union
    {
      //FIO3DIR0
      //FIO3MASK0
      //FIO3PIN0
      //FIO3SET0
      //FIO3CLR0
      struct{
        __REG8  P3_0   : 1;
        __REG8  P3_1   : 1;
        __REG8  P3_2   : 1;
        __REG8  P3_3   : 1;
        __REG8  P3_4   : 1;
        __REG8  P3_5   : 1;
        __REG8  P3_6   : 1;
        __REG8  P3_7   : 1;
      } __byte0_bit;
      __REG8 __byte0;
    };
    union
    {
      //FIO3DIR1
      //FIO3MASK1
      //FIO3PIN1
      //FIO3SET1
      //FIO3CLR1
      struct{
        __REG8  P3_0   : 1;
        __REG8  P3_1   : 1;
        __REG8  P3_2   : 1;
        __REG8  P3_3   : 1;
        __REG8  P3_4   : 1;
        __REG8  P3_5   : 1;
        __REG8  P3_6   : 1;
        __REG8  P3_7   : 1;
      } __byte1_bit;
      __REG8 __byte1;
    };
    union
    {
      //FIO3DIR2
      //FIO3MASK2
      //FIO3PIN2
      //FIO3SET2
      //FIO3CLR2
      struct{
        __REG8  P3_0   : 1;
        __REG8  P3_1   : 1;
        __REG8  P3_2   : 1;
        __REG8  P3_3   : 1;
        __REG8  P3_4   : 1;
        __REG8  P3_5   : 1;
        __REG8  P3_6   : 1;
        __REG8  P3_7   : 1;
      } __byte2_bit;
      __REG8 __byte2;
    };
    union
    {
      //FIO3DIR3
      //FIO3MASK3
      //FIO3PIN3
      //FIO3SET3
      //FIO3CLR3
      struct{
        __REG8  P3_0   : 1;
        __REG8  P3_1   : 1;
        __REG8  P3_2   : 1;
        __REG8  P3_3   : 1;
        __REG8  P3_4   : 1;
        __REG8  P3_5   : 1;
        __REG8  P3_6   : 1;
        __REG8  P3_7   : 1;
      } __byte3_bit;
      __REG8 __byte3;
    };
  };

  struct
  {
    union
    {
      //FIO3DIRL
      //FIO3MASKL
      //FIO3PINL
      //FIO3SETL
      //FIO3CLRL
      struct{
        __REG16 P3_0   : 1;
        __REG16 P3_1   : 1;
        __REG16 P3_2   : 1;
        __REG16 P3_3   : 1;
        __REG16 P3_4   : 1;
        __REG16 P3_5   : 1;
        __REG16 P3_6   : 1;
        __REG16 P3_7   : 1;
        __REG16 P3_8   : 1;
        __REG16 P3_9   : 1;
        __REG16 P3_10  : 1;
        __REG16 P3_11  : 1;
        __REG16 P3_12  : 1;
        __REG16 P3_13  : 1;
        __REG16 P3_14  : 1;
        __REG16 P3_15  : 1;
      } __shortl_bit;
      __REG16 __shortl;
    };
    union
    {
      //FIO3DIRU
      //FIO3MASKU
      //FIO3PINU
      //FIO3SETU
      //FIO3CLRU
      struct{
        __REG16 P3_0   : 1;
        __REG16 P3_1   : 1;
        __REG16 P3_2   : 1;
        __REG16 P3_3   : 1;
        __REG16 P3_4   : 1;
        __REG16 P3_5   : 1;
        __REG16 P3_6   : 1;
        __REG16 P3_7   : 1;
        __REG16 P3_8   : 1;
        __REG16 P3_9   : 1;
        __REG16 P3_10  : 1;
        __REG16 P3_11  : 1;
        __REG16 P3_12  : 1;
        __REG16 P3_13  : 1;
        __REG16 P3_14  : 1;
        __REG16 P3_15  : 1;
      } __shortu_bit;
      __REG16 __shortu;
    };
  };
} __fgpio3_bits;

/* GPIO 4 Registers */
typedef struct {
__REG32 P4_0   : 1;
__REG32 P4_1   : 1;
__REG32 P4_2   : 1;
__REG32 P4_3   : 1;
__REG32 P4_4   : 1;
__REG32 P4_5   : 1;
__REG32 P4_6   : 1;
__REG32 P4_7   : 1;
__REG32 P4_8   : 1;
__REG32 P4_9   : 1;
__REG32 P4_10  : 1;
__REG32 P4_11  : 1;
__REG32 P4_12  : 1;
__REG32 P4_13  : 1;
__REG32 P4_14  : 1;
__REG32 P4_15  : 1;
__REG32 P4_16  : 1;
__REG32 P4_17  : 1;
__REG32 P4_18  : 1;
__REG32 P4_19  : 1;
__REG32 P4_20  : 1;
__REG32 P4_21  : 1;
__REG32 P4_22  : 1;
__REG32 P4_23  : 1;
__REG32 P4_24  : 1;
__REG32 P4_25  : 1;
__REG32 P4_26  : 1;
__REG32 P4_27  : 1;
__REG32 P4_28  : 1;
__REG32 P4_29  : 1;
__REG32 P4_30  : 1;
__REG32 P4_31  : 1;
} __gpio4_bits;

/* FGPIO 4 Registers*/
typedef union{
  //FIO4DIR
  //FIO4MASK
  //FIO4PIN
  //FIO4SET
  //FIO4CLR
  struct {
    __REG32 P4_0   : 1;
    __REG32 P4_1   : 1;
    __REG32 P4_2   : 1;
    __REG32 P4_3   : 1;
    __REG32 P4_4   : 1;
    __REG32 P4_5   : 1;
    __REG32 P4_6   : 1;
    __REG32 P4_7   : 1;
    __REG32 P4_8   : 1;
    __REG32 P4_9   : 1;
    __REG32 P4_10  : 1;
    __REG32 P4_11  : 1;
    __REG32 P4_12  : 1;
    __REG32 P4_13  : 1;
    __REG32 P4_14  : 1;
    __REG32 P4_15  : 1;
    __REG32 P4_16  : 1;
    __REG32 P4_17  : 1;
    __REG32 P4_18  : 1;
    __REG32 P4_19  : 1;
    __REG32 P4_20  : 1;
    __REG32 P4_21  : 1;
    __REG32 P4_22  : 1;
    __REG32 P4_23  : 1;
    __REG32 P4_24  : 1;
    __REG32 P4_25  : 1;
    __REG32 P4_26  : 1;
    __REG32 P4_27  : 1;
    __REG32 P4_28  : 1;
    __REG32 P4_29  : 1;
    __REG32 P4_30  : 1;
    __REG32 P4_31  : 1;
  };

  struct
  {
    union
    {
      //FIO4DIR0
      //FIO4MASK0
      //FIO4PIN0
      //FIO4SET0
      //FIO4CLR0
      struct{
        __REG8  P4_0   : 1;
        __REG8  P4_1   : 1;
        __REG8  P4_2   : 1;
        __REG8  P4_3   : 1;
        __REG8  P4_4   : 1;
        __REG8  P4_5   : 1;
        __REG8  P4_6   : 1;
        __REG8  P4_7   : 1;
      } __byte0_bit;
      __REG8 __byte0;
    };
    union
    {
      //FIO4DIR1
      //FIO4MASK1
      //FIO4PIN1
      //FIO4SET1
      //FIO4CLR1
      struct{
        __REG8  P4_0   : 1;
        __REG8  P4_1   : 1;
        __REG8  P4_2   : 1;
        __REG8  P4_3   : 1;
        __REG8  P4_4   : 1;
        __REG8  P4_5   : 1;
        __REG8  P4_6   : 1;
        __REG8  P4_7   : 1;
      } __byte1_bit;
      __REG8 __byte1;
    };
    union
    {
      //FIO4DIR2
      //FIO4MASK2
      //FIO4PIN2
      //FIO4SET2
      //FIO4CLR2
      struct{
        __REG8  P4_0   : 1;
        __REG8  P4_1   : 1;
        __REG8  P4_2   : 1;
        __REG8  P4_3   : 1;
        __REG8  P4_4   : 1;
        __REG8  P4_5   : 1;
        __REG8  P4_6   : 1;
        __REG8  P4_7   : 1;
      } __byte2_bit;
      __REG8 __byte2;
    };
    union
    {
      //FIO4DIR3
      //FIO4MASK3
      //FIO4PIN3
      //FIO4SET3
      //FIO4CLR3
      struct{
        __REG8  P4_0   : 1;
        __REG8  P4_1   : 1;
        __REG8  P4_2   : 1;
        __REG8  P4_3   : 1;
        __REG8  P4_4   : 1;
        __REG8  P4_5   : 1;
        __REG8  P4_6   : 1;
        __REG8  P4_7   : 1;
      } __byte3_bit;
      __REG8 __byte3;
    };
  };

  struct
  {
    union
    {
      //FIO4DIRL
      //FIO4MASKL
      //FIO4PINL
      //FIO4SETL
      //FIO4CLRL
      struct{
        __REG16 P4_0   : 1;
        __REG16 P4_1   : 1;
        __REG16 P4_2   : 1;
        __REG16 P4_3   : 1;
        __REG16 P4_4   : 1;
        __REG16 P4_5   : 1;
        __REG16 P4_6   : 1;
        __REG16 P4_7   : 1;
        __REG16 P4_8   : 1;
        __REG16 P4_9   : 1;
        __REG16 P4_10  : 1;
        __REG16 P4_11  : 1;
        __REG16 P4_12  : 1;
        __REG16 P4_13  : 1;
        __REG16 P4_14  : 1;
        __REG16 P4_15  : 1;
      } __shortl_bit;
      __REG16 __shortl;
    };
    union
    {
      //FIO4DIRU
      //FIO4MASKU
      //FIO4PINU
      //FIO4SETU
      //FIO4CLRU
      struct{
        __REG16 P4_0   : 1;
        __REG16 P4_1   : 1;
        __REG16 P4_2   : 1;
        __REG16 P4_3   : 1;
        __REG16 P4_4   : 1;
        __REG16 P4_5   : 1;
        __REG16 P4_6   : 1;
        __REG16 P4_7   : 1;
        __REG16 P4_8   : 1;
        __REG16 P4_9   : 1;
        __REG16 P4_10  : 1;
        __REG16 P4_11  : 1;
        __REG16 P4_12  : 1;
        __REG16 P4_13  : 1;
        __REG16 P4_14  : 1;
        __REG16 P4_15  : 1;
      } __shortu_bit;
      __REG16 __shortu;
    };
  };
} __fgpio4_bits;

/* GPIO overall Interrupt Status register */
typedef struct{
__REG32 P0INT  : 1;
__REG32        : 1;
__REG32 P2INT  : 1;
__REG32        :29;
}__iointst_bits;

/* MAC Configuration Register 1 */
typedef struct{
__REG32 RE        : 1;
__REG32 PARF      : 1;
__REG32 RXFC      : 1;
__REG32 TXFC      : 1;
__REG32 LB        : 1;
__REG32           : 3;
__REG32 RSTTX     : 1;
__REG32 RSTMCSTX  : 1;
__REG32 RSTRX     : 1;
__REG32 RSTMCSRX  : 1;
__REG32           : 2;
__REG32 SIMRST    : 1;
__REG32 SOFTRST   : 1;
__REG32           :16;
}__mac1_bits;

/* MAC Configuration Register 2 */
typedef struct{
__REG32 FD        : 1;
__REG32 FLC       : 1;
__REG32 HFE       : 1;
__REG32 DLYCRC    : 1;
__REG32 CRCEN     : 1;
__REG32 PADCRCEN  : 1;
__REG32 VLANCRCEN : 1;
__REG32 ADPE      : 1;
__REG32 PPE       : 1;
__REG32 LPE       : 1;
__REG32           : 2;
__REG32 NB        : 1;
__REG32 BP        : 1;
__REG32 ED        : 1;
__REG32           :17;
}__mac2_bits;

/* Back-to-Back Inter-Packet-Gap Register */
typedef struct{
__REG32 IPG       : 7;
__REG32           :25;
}__ipgt_bits;

/* Non Back-to-Back Inter-Packet-Gap Register */
typedef struct{
__REG32 IPGR2     : 7;
__REG32           : 1;
__REG32 IPGR1     : 7;
__REG32           :17;
}__ipgr_bits;

/*Collision Window / Retry Register */
typedef struct{
__REG32 RM        : 4;
__REG32           : 4;
__REG32 CW        : 6;
__REG32           :18;
}__clrt_bits;

/* Maximum Frame Register */
typedef struct{
__REG32 MAXF      :16;
__REG32           :16;
}__maxf_bits;

/* PHY Support Register */
typedef struct{
__REG32             : 8;
__REG32 SPEED       : 1;
__REG32             :23;
}__supp_bits;

/* Test Register */
typedef struct{
__REG32 SPQ         : 1;
__REG32 TP          : 1;
__REG32 TB          : 1;
__REG32             :29;
}__test_bits;

/* MII Mgmt Configuration Register */
typedef struct{
__REG32 SI          : 1;
__REG32 SP          : 1;
__REG32 CS          : 4;
__REG32             : 9;
__REG32 RSTMIIMGMT  : 1;
__REG32             :16;
}__mcfg_bits;

/* MII Mgmt Command Register */
typedef struct{
__REG32 READ        : 1;
__REG32 SCAN        : 1;
__REG32             :30;
}__mcmd_bits;

/* MII Mgmt Address Register */
typedef struct{
__REG32 REGADDR     : 5;
__REG32             : 3;
__REG32 PHY_ADDR    : 5;
__REG32             :19;
}__madr_bits;

/* MII Mgmt Write Data Register */
typedef struct{
__REG32 WRITEDATA   :16;
__REG32             :16;
}__mwtd_bits;

/* MII Mgmt Read Data Register */
typedef struct{
__REG32 READDATA    :16;
__REG32             :16;
}__mrdd_bits;

/* MII Mgmt Indicators Register */
typedef struct{
__REG32 BUSY          : 1;
__REG32 SCANNING      : 1;
__REG32 NOT_VALID     : 1;
__REG32 MII_LINK_FAIL : 1;
__REG32               :28;
}__mind_bits;

/* Station Address 0 Register */
typedef struct{
__REG32 STATION_ADDR_2  : 8;
__REG32 STATION_ADDR_1  : 8;
__REG32                 :16;
}__sa0_bits;

/* Station Address 1 Register */
typedef struct{
__REG32 STATION_ADDR_4  : 8;
__REG32 STATION_ADDR_3  : 8;
__REG32                 :16;
}__sa1_bits;

/* Station Address 2 Register */
typedef struct{
__REG32 STATION_ADDR_6  : 8;
__REG32 STATION_ADDR_5  : 8;
__REG32                 :16;
}__sa2_bits;

/* Command Register */
typedef struct{
__REG32 RXENABLE        : 1;
__REG32 TXENABLE        : 1;
__REG32                 : 1;
__REG32 REGRESET        : 1;
__REG32 TXRESET         : 1;
__REG32 RXRESET         : 1;
__REG32 PASSRUNTFRAME   : 1;
__REG32 PASSRXFILTER    : 1;
__REG32 TXFLOWCONTROL   : 1;
__REG32 RMII            : 1;
__REG32 FULLDUPLEX      : 1;
__REG32                 :21;
}__command_bits;

/* Status Register */
typedef struct{
__REG32 RXSTATUS        : 1;
__REG32 TXSTATUS        : 1;
__REG32                 :30;
}__status_bits;

/* Receive Number of Descriptors Register */
typedef struct{
__REG32 RXDESCRIPTORNUMBER  :16;
__REG32                     :16;
}__rxdescrn_bits;

/* Receive Produce Index Register */
typedef struct{
__REG32 RXPRODUCDINDEX  :16;
__REG32                 :16;
}__rxprodind_bits;

/* Receive Consume Index Register */
typedef struct{
__REG32 RXCONSUMEINDEX  :16;
__REG32                 :16;
}__rxcomind_bits;

/* Transmit Number of Descriptors Register */
typedef struct{
__REG32 TXDESCRIPTORNUMBER  :16;
__REG32                     :16;
}__txdescrn_bits;

/* Transmit Produce Index Register */
typedef struct{
__REG32 TXPRODUCDINDEX  :16;
__REG32                 :16;
}__txprodind_bits;

/* Transmit Consume Index Register */
typedef struct{
__REG32 TXCONSUMEINDEX  :16;
__REG32                 :16;
}__txcomind_bits;

/* Transmit Status Vector 0 Register */
typedef struct{
__REG32 CCR_ERR         : 1;
__REG32 LCERR           : 1;
__REG32 LOOR            : 1;
__REG32 DONE            : 1;
__REG32 MULTICAST       : 1;
__REG32 BROADCAST       : 1;
__REG32 PD              : 1;
__REG32 ED              : 1;
__REG32 EC              : 1;
__REG32 LC              : 1;
__REG32 GIANT           : 1;
__REG32 UNDERRUN        : 1;
__REG32 TB              :16;
__REG32 CF              : 1;
__REG32 PAUSE           : 1;
__REG32 BACKPRESSURE    : 1;
__REG32 VLAN            : 1;
}__tsv0_bits;

/* Transmit Status Vector 1 Register */
typedef struct{
__REG32 TBC             :16;
__REG32 TCC             : 4;
__REG32                 :12;
}__tsv1_bits;

/* Receive Status Vector Register */
typedef struct{
__REG32 RBC             :16;
__REG32 PPI             : 1;
__REG32 RXDVEPS         : 1;
__REG32 CEPS            : 1;
__REG32 RCV             : 1;
__REG32 CRC_ERR         : 1;
__REG32 LCE             : 1;
__REG32 LOOR            : 1;
__REG32 R_OK            : 1;
__REG32 MULTICAST       : 1;
__REG32 BROADCAST       : 1;
__REG32 DN              : 1;
__REG32 CF              : 1;
__REG32 PAUSE           : 1;
__REG32 UO              : 1;
__REG32 VLAN            : 1;
__REG32                 : 1;
}__rsv_bits;

/* Flow Control Counter Register */
typedef struct{
__REG32 MC              :16;
__REG32 PT              :16;
}__fwctrlcnt_bits;

/* Flow Control Status Register */
typedef struct{
__REG32 MCC             :16;
__REG32                 :16;
}__fwctrlstat_bits;

/* Receive Filter Control Register */
typedef struct{
__REG32 AUE             : 1;
__REG32 ABE             : 1;
__REG32 AME             : 1;
__REG32 AUHE            : 1;
__REG32 AMHE            : 1;
__REG32 APE             : 1;
__REG32                 : 6;
__REG32 MPEWOL          : 1;
__REG32 RXFEWOL         : 1;
__REG32                 :18;
}__rxflctrl_bits;

/* Receive Filter WoL Status Register */
typedef struct{
__REG32 AUWOL           : 1;
__REG32 ABWOL           : 1;
__REG32 AMWOL           : 1;
__REG32 AUHWOL          : 1;
__REG32 AMHWOL          : 1;
__REG32 APWOL           : 1;
__REG32                 : 1;
__REG32 RXFWOL          : 1;
__REG32 MPWOL           : 1;
__REG32                 :23;
}__rxflwolstat_bits;

/* Receive Filter WoL Clear Register */
typedef struct{
__REG32 AUWOLC          : 1;
__REG32 ABWOLC          : 1;
__REG32 AMWOLC          : 1;
__REG32 AUHWOLC         : 1;
__REG32 AMHWOLC         : 1;
__REG32 APWOLC          : 1;
__REG32                 : 1;
__REG32 RXFWOLC         : 1;
__REG32 MPWOLC          : 1;
__REG32                 :23;
}__rxflwolclr_bits;

/* Interrupt Status Register */
typedef struct{
__REG32 RXOVERRUNINT    : 1;
__REG32 RXERRORINT      : 1;
__REG32 RXFINISHEDINT   : 1;
__REG32 RXDONEINT       : 1;
__REG32 TXUNDERRUNINT   : 1;
__REG32 TXERRORINT      : 1;
__REG32 TXFINISHEDINT   : 1;
__REG32 TXDONEINT       : 1;
__REG32                 : 4;
__REG32 SOFTINT         : 1;
__REG32 WAKEUPINT       : 1;
__REG32                 :18;
}__intstat_bits;

/* Interrupt Enable Register */
typedef struct{
__REG32 RXOVERRUNINTEN  : 1;
__REG32 RXERRORINTEN    : 1;
__REG32 RXFINISHEDINTEN : 1;
__REG32 RXDONEINTEN     : 1;
__REG32 TXUNDERRUNINTEN : 1;
__REG32 TXERRORINTEN    : 1;
__REG32 TXFINISHEDINTEN : 1;
__REG32 TXDONEINTEN     : 1;
__REG32                 : 4;
__REG32 SOFTINTEN       : 1;
__REG32 WAKEUPINTEN     : 1;
__REG32                 :18;
}__intena_bits;

/* Interrupt Clear Register */
typedef struct{
__REG32 RXOVERRUNINTCLR : 1;
__REG32 RXERRORINTCLR   : 1;
__REG32 RXFINISHEDINTCLR: 1;
__REG32 RXDONEINTCLR    : 1;
__REG32 TXUNDERRUNINTCLR: 1;
__REG32 TXERRORINTCLR   : 1;
__REG32 TXFINISHEDINTCLR: 1;
__REG32 TXDONEINTCLR    : 1;
__REG32                 : 4;
__REG32 SOFTINTCLR      : 1;
__REG32 WAKEUPINTCLR    : 1;
__REG32                 :18;
}__intclr_bits;

/* Interrupt Set Register */
typedef struct{
__REG32 RXOVERRUNINTSET : 1;
__REG32 RXERRORINTSET   : 1;
__REG32 RXFINISHEDINTSET: 1;
__REG32 RXDONEINTSET    : 1;
__REG32 TXUNDERRUNINTSET: 1;
__REG32 TXERRORINTSET   : 1;
__REG32 TXFINISHEDINTSET: 1;
__REG32 TXDONEINTSET    : 1;
__REG32                 : 4;
__REG32 SOFTINTSET      : 1;
__REG32 WAKEUPINTSET    : 1;
__REG32                 :18;
}__intset_bits;

/* Power Down Register */
typedef struct{
__REG32                 :31;
__REG32 POWERDOWN       : 1;
}__pwrdn_bits;

/* OTG_status and control Register */
typedef struct {
__REG32 PORT_FUNC           : 2;
__REG32 TMR_SCALE           : 2;
__REG32 TMR_MODE            : 1;
__REG32 TMR_EN              : 1;
__REG32 TMR_RST             : 1;
__REG32                     : 1;
__REG32 B_HNP_TRACK         : 1;
__REG32 A_HNP_TRACK         : 1;
__REG32 PU_REMOVED          : 1;
__REG32                     : 5;
__REG32 TMR_CNT             :16;
} __otgstctrl_bits;

/* USB Clock Control register */
/* OTG_clock Registers */
typedef union {
  // USBCLKCTRL
  struct{
__REG32                 : 1;
__REG32 DEV_CLK_EN      : 1;
__REG32                 : 1;
__REG32 PORTSEL_CLK_EN  : 1;
__REG32 AHB_CLK_EN      : 1;
__REG32                 :27;
  };
  // OTGCLKCTRL
  struct{
__REG32 _HOST_CLK_EN  : 1;
__REG32 _DEV_CLK_EN   : 1;
__REG32 _I2C_CLK_EN   : 1;
__REG32 _OTG_CLK_EN   : 1;
__REG32 _AHB_CLK_EN   : 1;
__REG32               :27;
  };
} __usbclkctrl_bits;

/* USB Clock Status register */
/* OTG_status Registers */
typedef union {
  // USBCLKST
  struct{
__REG32                 : 1;
__REG32 DEV_CLK_ON      : 1;
__REG32                 : 1;
__REG32 PORTSEL_CLK_ON  : 1;
__REG32 AHB_CLK_ON      : 1;
__REG32                 :27;
  };
  // OTGCLKST
  struct{
__REG32 _HOST_CLK_ON : 1;
__REG32 _DEV_CLK_ON  : 1;
__REG32 _I2C_CLK_ON  : 1;
__REG32 _OTG_CLK_ON  : 1;
__REG32 _AHB_CLK_ON  : 1;
__REG32              :27;
  };
} __usbclkst_bits;

/* USB - Device Interrupt Status Register */
typedef struct {
  __REG32 USB_INT_REQ_LP    : 1;
  __REG32 USB_INT_REQ_HP    : 1;
  __REG32 USB_INT_REQ_DMA   : 1;
  __REG32 USB_HOST_INT      : 1;
  __REG32 USB_ATX_INT       : 1;
  __REG32 USB_OTG_INT       : 1;
  __REG32 USB_I2C_INT       : 1;
  __REG32                   : 1;
  __REG32 USB_NEED_CLOCK    : 1;
  __REG32                   :22;
  __REG32 EN_USB_INTS       : 1;
} __usbints_bits;

/* USB - Device Interrupt Status Register */
/* USB - Device Interrupt Enable Register */
/* USB - Device Interrupt Clear Register */
/* USB - Device Interrupt Set Register */
typedef struct {
  __REG32 FRAME             : 1;
  __REG32 EP_FAST           : 1;
  __REG32 EP_SLOW           : 1;
  __REG32 DEV_STAT          : 1;
  __REG32 CCEMTY            : 1;
  __REG32 CDFULL            : 1;
  __REG32 RXENDPKT          : 1;
  __REG32 TXENDPKT          : 1;
  __REG32 EP_RLZED          : 1;
  __REG32 ERR_INT           : 1;
  __REG32                   :22;
} __usbdevintst_bits;

/* USB - Device Interrupt Priority Register */
typedef struct {
  __REG8  FRAME             : 1;
  __REG8  EP_FAST           : 1;
  __REG8                    : 6;
} __usbdevintpri_bits;

/* USB - Endpoint Interrupt Status Register */
/* USB - Endpoint Interrupt Enable Register */
/* USB - Endpoint Interrupt Clear Register */
/* USB - Endpoint Interrupt Set Register */
/* USB - Endpoint Interrupt Priority Register */
typedef struct {
  __REG32 EP_0RX            : 1;
  __REG32 EP_0TX            : 1;
  __REG32 EP_1RX            : 1;
  __REG32 EP_1TX            : 1;
  __REG32 EP_2RX            : 1;
  __REG32 EP_2TX            : 1;
  __REG32 EP_3RX            : 1;
  __REG32 EP_3TX            : 1;
  __REG32 EP_4RX            : 1;
  __REG32 EP_4TX            : 1;
  __REG32 EP_5RX            : 1;
  __REG32 EP_5TX            : 1;
  __REG32 EP_6RX            : 1;
  __REG32 EP_6TX            : 1;
  __REG32 EP_7RX            : 1;
  __REG32 EP_7TX            : 1;
  __REG32 EP_8RX            : 1;
  __REG32 EP_8TX            : 1;
  __REG32 EP_9RX            : 1;
  __REG32 EP_9TX            : 1;
  __REG32 EP_10RX           : 1;
  __REG32 EP_10TX           : 1;
  __REG32 EP_11RX           : 1;
  __REG32 EP_11TX           : 1;
  __REG32 EP_12RX           : 1;
  __REG32 EP_12TX           : 1;
  __REG32 EP_13RX           : 1;
  __REG32 EP_13TX           : 1;
  __REG32 EP_14RX           : 1;
  __REG32 EP_14TX           : 1;
  __REG32 EP_15RX           : 1;
  __REG32 EP_15TX           : 1;
} __usbepintst_bits;

/* USB - Realize Enpoint Register */
/* USB - DMA Request Status Register */
/* USB - DMA Request Clear Register */
/* USB - DMA Request Set Regiser */
/* USB - EP DMA Status Register */
/* USB - EP DMA Enable Register */
/* USB - EP DMA Disable Register */
/* USB - New DD Request Interrupt Status Register */
/* USB - New DD Request Interrupt Clear Register */
/* USB - New DD Request Interrupt Set Register */
/* USB - End Of Transfer Interrupt Status Register */
/* USB - End Of Transfer Interrupt Clear Register */
/* USB - End Of Transfer Interrupt Set Register */
/* USB - System Error Interrupt Status Register */
/* USB - System Error Interrupt Clear Register */
/* USB - System Error Interrupt Set Register */
typedef struct {
  __REG32 EP0               : 1;
  __REG32 EP1               : 1;
  __REG32 EP2               : 1;
  __REG32 EP3               : 1;
  __REG32 EP4               : 1;
  __REG32 EP5               : 1;
  __REG32 EP6               : 1;
  __REG32 EP7               : 1;
  __REG32 EP8               : 1;
  __REG32 EP9               : 1;
  __REG32 EP10              : 1;
  __REG32 EP11              : 1;
  __REG32 EP12              : 1;
  __REG32 EP13              : 1;
  __REG32 EP14              : 1;
  __REG32 EP15              : 1;
  __REG32 EP16              : 1;
  __REG32 EP17              : 1;
  __REG32 EP18              : 1;
  __REG32 EP19              : 1;
  __REG32 EP20              : 1;
  __REG32 EP21              : 1;
  __REG32 EP22              : 1;
  __REG32 EP23              : 1;
  __REG32 EP24              : 1;
  __REG32 EP25              : 1;
  __REG32 EP26              : 1;
  __REG32 EP27              : 1;
  __REG32 EP28              : 1;
  __REG32 EP29              : 1;
  __REG32 EP30              : 1;
  __REG32 EP31              : 1;
} __usbreep_bits;

/* USB - Endpoint Index Register */
typedef struct {
  __REG32 PHY_ENDP          : 5;
  __REG32                   :27;
} __usbepin_bits;

/* USB - MaxPacketSize Register */
typedef struct {
  __REG32 MPS               :10;
  __REG32                   :22;
} __usbmaxpsize_bits;

/* USB - Receive Packet Length Register */
typedef struct {
  __REG32 PKT_LNGTH         :10;
  __REG32 DV                : 1;
  __REG32 PKT_RDY           : 1;
  __REG32                   :20;
} __usbrxplen_bits;

/* USB - Transmit Packet Length Register */
typedef struct {
  __REG32 PKT_LNGHT         :10;
  __REG32                   :22;
} __usbtxplen_bits;

/* USB - Control Register */
typedef struct {
  __REG32 RD_EN             : 1;
  __REG32 WR_EN             : 1;
  __REG32 LOG_ENDPOINT      : 4;
  __REG32                   :26;
} __usbctrl_bits;

/* USB - Command Code Register */
typedef struct {
  __REG32                   : 8;
  __REG32 CMD_PHASE         : 8;
  __REG32 CMD_CODE          : 8;
  __REG32                   : 8;
} __usbcmdcode_bits;

/* USB - Command Data Register */
typedef struct {
  __REG32 CMD_DATA          : 8;
  __REG32                   :24;
} __usbcmddata_bits;

/* USB - DMA Interrupt Status Register */
/* USB - DMA Interrupt Enable Register */
typedef struct {
  __REG32 EOT       : 1;
  __REG32 NDDR      : 1;
  __REG32 ERR       : 1;
  __REG32           :29;
} __usbdmaintst_bits;

/* HcRevision Register */
typedef struct {
  __REG32 REV               : 8;
  __REG32                   :24;
} __hcrevision_bits;

/* HcControl Register */
typedef struct {
  __REG32 CBSR              : 2;
  __REG32 PLE               : 1;
  __REG32 IE                : 1;
  __REG32 CLE               : 1;
  __REG32 BLE               : 1;
  __REG32 HCFS              : 2;
  __REG32 IR                : 1;
  __REG32 RWC               : 1;
  __REG32 RWE               : 1;
  __REG32                   :21;
} __hccontrol_bits;

/* HcCommandStatus Register */
typedef struct {
  __REG32 HCR               : 1;
  __REG32 CLF               : 1;
  __REG32 BLF               : 1;
  __REG32 OCR               : 1;
  __REG32                   :12;
  __REG32 SOC               : 2;
  __REG32                   :14;
} __hccommandstatus_bits;

/* HcInterruptStatus Register */
typedef struct {
  __REG32 SO                : 1;
  __REG32 WDH               : 1;
  __REG32 SF                : 1;
  __REG32 RD                : 1;
  __REG32 UE                : 1;
  __REG32 FNO               : 1;
  __REG32 RHSC              : 1;
  __REG32                   :23;
  __REG32 OC                : 1;
  __REG32                   : 1;
} __hcinterruptstatus_bits;

/* HcInterruptEnable Register
   HcInterruptDisable Register */
typedef struct {
  __REG32 SO                : 1;
  __REG32 WDH               : 1;
  __REG32 SF                : 1;
  __REG32 RD                : 1;
  __REG32 UE                : 1;
  __REG32 FNO               : 1;
  __REG32 RHSC              : 1;
  __REG32                   :23;
  __REG32 OC                : 1;
  __REG32 MIE               : 1;
} __hcinterruptenable_bits;

/* HcHCCA Register */
typedef struct {
  __REG32                   : 8;
  __REG32 HCCA              :24;
} __hchcca_bits;

/* HcPeriodCurrentED Register */
typedef struct {
  __REG32                   : 4;
  __REG32 PCED              :28;
} __hcperiodcurrented_bits;

/* HcControlHeadED Registerr */
typedef struct {
  __REG32                   : 4;
  __REG32 CHED              :28;
} __hccontrolheaded_bits;

/* HcControlCurrentED Register */
typedef struct {
  __REG32                   : 4;
  __REG32 CCED              :28;
} __hccontrolcurrented_bits;

/* HcBulkHeadED Register */
typedef struct {
  __REG32                   : 4;
  __REG32 BHED              :28;
} __hcbulkheaded_bits;

/* HcBulkCurrentED Register */
typedef struct {
  __REG32                   : 4;
  __REG32 BCED              :28;
} __hcbulkcurrented_bits;

/* HcDoneHead Register */
typedef struct {
  __REG32                   : 4;
  __REG32 DH                :28;
} __hcdonehead_bits;

/* HcFmInterval Register */
typedef struct {
  __REG32 FI                :14;
  __REG32                   : 2;
  __REG32 FSMPS             :15;
  __REG32 FIT               : 1;
} __hcfminterval_bits;

/* HcFmRemaining Register */
typedef struct {
  __REG32 FR                :14;
  __REG32                   :17;
  __REG32 FRT               : 1;
} __hcfmremaining_bits;

/* HcFmNumber Register */
typedef struct {
  __REG32 FN                :16;
  __REG32                   :16;
} __hcfmnumber_bits;

/* HcPeriodicStart Register */
typedef struct {
  __REG32 PS                :14;
  __REG32                   :18;
} __hcperiodicstart_bits;

/* HcLSThreshold Register */
typedef struct {
  __REG32 LST               :12;
  __REG32                   :20;
} __hclsthreshold_bits;

/* HcRhDescriptorA Register */
typedef struct {
  __REG32 NDP               : 8;
  __REG32 PSM               : 1;  // ??
  __REG32 NPS               : 1;  // ??
  __REG32 DT                : 1;
  __REG32 OCPM              : 1;
  __REG32 NOCP              : 1;
  __REG32                   :11;
  __REG32 POTPGT            : 8;
} __hcrhdescriptora_bits;

/* HcRhDescriptorB Register */
typedef struct {
  __REG32 DR                :16;
  __REG32 PPCM              :16;
} __hcrhdescriptorb_bits;

/* HcRhStatus Register */
typedef struct {
  __REG32 LPS               : 1;
  __REG32 OCI               : 1;
  __REG32                   :13;
  __REG32 DRWE              : 1;
  __REG32 LPSC              : 1;
  __REG32 CCIC              : 1;
  __REG32                   :13;
  __REG32 CRWE              : 1;
} __hcrhstatus_bits;

/* HcRhPortStatus[1:2] Register */
typedef struct {
  __REG32 CCS               : 1;
  __REG32 PES               : 1;
  __REG32 PSS               : 1;
  __REG32 POCI              : 1;
  __REG32 PRS               : 1;
  __REG32                   : 3;
  __REG32 PPS               : 1;
  __REG32 LSDA              : 1;
  __REG32                   : 6;
  __REG32 CSC               : 1;
  __REG32 PESC              : 1;
  __REG32 PSSC              : 1;
  __REG32 OCIC              : 1;
  __REG32 PRSC              : 1;
  __REG32                   :11;
} __hcrhportstatus_bits;

/* OTG_int_status Register
   OTG_int_enable Register
   OTG_int_set Register
   OTG_int_clr Register */
typedef struct{
__REG32 TMR                 : 1;
__REG32 REMOVE_PU           : 1;
__REG32 HNP_FAILURE         : 1;
__REG32 HNP_SUCCESS         : 1;
__REG32                     :28;
} __otgintst_bits;

/* OTG Timer Register */
typedef struct{
__REG32 TIMEOUT_CNT         :16;
__REG32                     :16;
} __otgtmr_bits;

/* OTG I2C Clock High Register */
typedef struct{
__REG32 CDHI                : 8;
__REG32                     :24;
} __i2c_clkhi_bits;

/* OTG I2C Clock Low Register */
typedef struct{
__REG32 CDLO                : 8;
__REG32                     :24;
} __i2c_clklo_bits;

/* OTG I2C_TX/I2C_RX Register */
typedef union{
  //I2C_RX
  struct {
__REG32 RX_DATA  : 8;
__REG32          :24;
  };
  //I2C_TX
  struct {
__REG32 TX_DATA  : 8;
__REG32 START    : 1;
__REG32 STOP     : 1;
__REG32          :22;
  };
} __otg_i2c_rx_tx_bits;

/* OTG I2C_STS Register */
typedef struct{
__REG32 TDI     : 1;
__REG32 AFI     : 1;
__REG32 NAI     : 1;
__REG32 DRMI    : 1;
__REG32 DRSI    : 1;
__REG32 ACTIVE  : 1;
__REG32 SCL     : 1;
__REG32 SDA     : 1;
__REG32 RFF     : 1;
__REG32 RFE     : 1;
__REG32 TFF     : 1;
__REG32 TFE     : 1;
__REG32         :20;
} __otg_i2c_sts_bits;

/* OTG I2C_CTL Register */
typedef struct{
__REG32 TDIE    : 1;
__REG32 AFIE    : 1;
__REG32 NAIE    : 1;
__REG32 DRMIE   : 1;
__REG32 DRSIE   : 1;
__REG32 RFFIE   : 1;
__REG32 RFDAIE  : 1;
__REG32 TFFIE   : 1;
__REG32 SRST    : 1;
__REG32         :23;
} __otg_i2c_ctl_bits;

/* UART interrupt enable register */
typedef struct{
__REG32 RDAIE     : 1;
__REG32 THREIE    : 1;
__REG32 RXLSIE    : 1;
__REG32           : 5;
__REG32 ABEOINTEN : 1;
__REG32 ABTOINTEN : 1;
__REG32           :22;
} __uartier0_bits;

/* UART1 interrupt enable register */
typedef struct{
__REG32 RDAIE     : 1;
__REG32 THREIE    : 1;
__REG32 RXLSIE    : 1;
__REG32 RXMSIE    : 1;
__REG32           : 3;
__REG32 CTSIE     : 1;
__REG32 ABEOINTEN : 1;
__REG32 ABTOINTEN : 1;
__REG32           :22;
} __uartier1_bits;

/* UART Transmit Enable Register */
typedef struct{
__REG8        : 7;
__REG8  TXEN  : 1;
} __uartter_bits;

/* UART line status register */
typedef struct{
__REG8  DR    : 1;
__REG8  OE    : 1;
__REG8  PE    : 1;
__REG8  FE    : 1;
__REG8  BI    : 1;
__REG8  THRE  : 1;
__REG8  TEMT  : 1;
__REG8  RXFE  : 1;
} __uartlsr_bits;

/* UART line control register */
typedef struct{
__REG8  WLS   : 2;
__REG8  SBS   : 1;
__REG8  PE    : 1;
__REG8  PS    : 2;
__REG8  BC    : 1;
__REG8  DLAB  : 1;
} __uartlcr_bits;

/* UART interrupt identification register and fifo control register */
typedef union {
  //UxIIR
  struct {
__REG32 IP     : 1;
__REG32 IID    : 3;
__REG32        : 2;
__REG32 IIRFE  : 2;
__REG32 ABEOINT: 1;
__REG32 ABTOINT: 1;
__REG32        :22;
  };
  //UxFCR
  struct {
__REG32 FCRFE  : 1;
__REG32 RFR    : 1;
__REG32 TFR    : 1;
__REG32 DMA    : 1;
__REG32        : 2;
__REG32 RTLS   : 2;
__REG32        :24;
  };
} __uartfcriir_bits;

/* UART modem control register */
typedef struct{
__REG8  DTR   : 1;
__REG8  RTS   : 1;
__REG8        : 2;
__REG8  LMS   : 1;
__REG8        : 1;
__REG8  RTSEN : 1;
__REG8  CTSEN : 1;
} __uartmcr_bits;

/* UART modem status register */
typedef union{
  //UxMSR
  struct {
__REG8  DCTS  : 1;
__REG8  DDSR  : 1;
__REG8  TERI  : 1;
__REG8  DDCD  : 1;
__REG8  CTS   : 1;
__REG8  DSR   : 1;
__REG8  RI    : 1;
__REG8  DCD   : 1;
  };
  //UxMSR
  struct {
__REG8  MSR0  : 1;
__REG8  MSR1  : 1;
__REG8  MSR2  : 1;
__REG8  MSR3  : 1;
__REG8  MSR4  : 1;
__REG8  MSR5  : 1;
__REG8  MSR6  : 1;
__REG8  MSR7  : 1;
  };
} __uartmsr_bits;

/* UART Auto-baud Control Register */
typedef struct{
__REG32 START        : 1;
__REG32 MODE         : 1;
__REG32 AUTORESTART  : 1;
__REG32              : 5;
__REG32 ABEOINTCLR   : 1;
__REG32 ABTOINTCLR   : 1;
__REG32              :22;
} __uartacr_bits;

/* IrDA Control Register for UART3 Only */
typedef struct{
__REG32 IRDAEN       : 1;
__REG32 IRDAINV      : 1;
__REG32 FIXPULSEEN   : 1;
__REG32 PULSEDIV     : 3;
__REG32              :26;
} __uarticr_bits;

/* UART Fractional Divider Register */
typedef struct{
__REG32 DIVADDVAL  : 4;
__REG32 MULVAL     : 4;
__REG32            :24;
} __uartfdr_bits;

/* UART1 RS485 Control register */
typedef struct{
__REG32 NMMEN      : 1;
__REG32 RXDIS      : 1;
__REG32 AADEN      : 1;
__REG32 SEL        : 1;
__REG32 DCTRL      : 1;
__REG32 OINV       : 1;
__REG32            :26;
} __u1rs485ctrl_bits;

/* UART1 FIFO Level register */
typedef struct{
__REG32 RXFIFILVL  : 4;
__REG32            : 4;
__REG32 TXFIFOLVL  : 4;
__REG32            :20;
} __uartfifolvl_bits;

/* CAN acceptance filter mode register */
typedef struct {
  __REG32 ACCOFF          :1;
  __REG32 ACCBP           :1;
  __REG32 EFCAN           :1;
  __REG32                 :29;
} __afmr_bits;

/* CAN LUT Error Register */
typedef struct {
  __REG32 LUTERR          :1;
  __REG32                 :31;
} __luterr_bits;

/* Global FullCANInterrupt Enable register */
typedef struct {
  __REG32 FCANIE          :1;
  __REG32                 :31;
} __fcanie_bits;

/* FullCAN Interrupt and Capture registers 0 */
typedef struct {
  __REG32 INTPND0         :1;
  __REG32 INTPND1         :1;
  __REG32 INTPND2         :1;
  __REG32 INTPND3         :1;
  __REG32 INTPND4         :1;
  __REG32 INTPND5         :1;
  __REG32 INTPND6         :1;
  __REG32 INTPND7         :1;
  __REG32 INTPND8         :1;
  __REG32 INTPND9         :1;
  __REG32 INTPND10        :1;
  __REG32 INTPND11        :1;
  __REG32 INTPND12        :1;
  __REG32 INTPND13        :1;
  __REG32 INTPND14        :1;
  __REG32 INTPND15        :1;
  __REG32 INTPND16        :1;
  __REG32 INTPND17        :1;
  __REG32 INTPND18        :1;
  __REG32 INTPND19        :1;
  __REG32 INTPND20        :1;
  __REG32 INTPND21        :1;
  __REG32 INTPND22        :1;
  __REG32 INTPND23        :1;
  __REG32 INTPND24        :1;
  __REG32 INTPND25        :1;
  __REG32 INTPND26        :1;
  __REG32 INTPND27        :1;
  __REG32 INTPND28        :1;
  __REG32 INTPND29        :1;
  __REG32 INTPND30        :1;
  __REG32 INTPND31        :1;
} __fcanic0_bits;

/* FullCAN Interrupt and Capture registers 1 */
typedef struct {
  __REG32 INTPND32        :1;
  __REG32 INTPND33        :1;
  __REG32 INTPND34        :1;
  __REG32 INTPND35        :1;
  __REG32 INTPND36        :1;
  __REG32 INTPND37        :1;
  __REG32 INTPND38        :1;
  __REG32 INTPND39        :1;
  __REG32 INTPND40        :1;
  __REG32 INTPND41        :1;
  __REG32 INTPND42        :1;
  __REG32 INTPND43        :1;
  __REG32 INTPND44        :1;
  __REG32 INTPND45        :1;
  __REG32 INTPND46        :1;
  __REG32 INTPND47        :1;
  __REG32 INTPND48        :1;
  __REG32 INTPND49        :1;
  __REG32 INTPND50        :1;
  __REG32 INTPND51        :1;
  __REG32 INTPND52        :1;
  __REG32 INTPND53        :1;
  __REG32 INTPND54        :1;
  __REG32 INTPND55        :1;
  __REG32 INTPND56        :1;
  __REG32 INTPND57        :1;
  __REG32 INTPND58        :1;
  __REG32 INTPND59        :1;
  __REG32 INTPND60        :1;
  __REG32 INTPND61        :1;
  __REG32 INTPND62        :1;
  __REG32 INTPND63        :1;
} __fcanic1_bits;

/* CAN central transmit status register */
typedef struct {
  __REG32 TS1             : 1;
  __REG32 TS2             : 1;
  __REG32                 : 6;
  __REG32 TBS1            : 1;
  __REG32 TBS2            : 1;
  __REG32                 : 6;
  __REG32 TCS1            : 1;
  __REG32 TCS2            : 1;
  __REG32                 :14;
} __cantxsr_bits;

/* CAN central receive status register */
typedef struct {
  __REG32 RS1             : 1;
  __REG32 RS2             : 1;
  __REG32                 : 6;
  __REG32 RBS1            : 1;
  __REG32 RBS2            : 1;
  __REG32                 : 6;
  __REG32 DOS1            : 1;
  __REG32 DOS2            : 1;
  __REG32                 :14;
} __canrxsr_bits;

/* CAN miscellaneous status register */
typedef struct {
  __REG32 E1              : 1;
  __REG32 E2              : 1;
  __REG32                 : 6;
  __REG32 BS1             : 1;
  __REG32 BS2             : 1;
  __REG32                 :22;
} __canmsr_bits;

/* CAN mode register */
typedef struct {
  __REG32 RM              :1;
  __REG32 LOM             :1;
  __REG32 STM             :1;
  __REG32 TPM             :1;
  __REG32 SM              :1;
  __REG32 RPM             :1;
  __REG32                 :1;
  __REG32 TM              :1;
  __REG32                 :24;
} __canmod_bits;

/* CAN command register */
typedef struct {
  __REG32 TR              :1;
  __REG32 AT              :1;
  __REG32 RRB             :1;
  __REG32 CDO             :1;
  __REG32 SRR             :1;
  __REG32 STB1            :1;
  __REG32 STB2            :1;
  __REG32 STB3            :1;
  __REG32                 :24;
} __cancmr_bits;

/* CAN global status register */
typedef struct {
  __REG32 RBS              :1;
  __REG32 DOS              :1;
  __REG32 TBS              :1;
  __REG32 TCS              :1;
  __REG32 RS               :1;
  __REG32 TS               :1;
  __REG32 ES               :1;
  __REG32 BS               :1;
  __REG32                  :8;
  __REG32 RXERR            :8;
  __REG32 TXERR            :8;
} __cangsr_bits;

/* CAN interrupt capture register */
typedef struct {
  __REG32 RI               :1;
  __REG32 TI1              :1;
  __REG32 EI               :1;
  __REG32 DOI              :1;
  __REG32 WUI              :1;
  __REG32 EPI              :1;
  __REG32 ALI              :1;
  __REG32 BEI              :1;
  __REG32 IDI              :1;
  __REG32 TI2              :1;
  __REG32 TI3              :1;
  __REG32                  :5;
  __REG32 ERRBIT           :5;
  __REG32 ERRDIR           :1;
  __REG32 ERRC             :2;
  __REG32 ALCBIT           :8;
} __canicr_bits;

/* CAN interrupt enable register */
typedef struct {
  __REG32 RIE               :1;
  __REG32 TIE1              :1;
  __REG32 EIE               :1;
  __REG32 DOIE              :1;
  __REG32 WUIE              :1;
  __REG32 EPIE              :1;
  __REG32 ALIE              :1;
  __REG32 BEIE              :1;
  __REG32 IDIE              :1;
  __REG32 TIE2              :1;
  __REG32 TIE3              :1;
  __REG32                   :21;
} __canier_bits;

/* CAN bus timing register */
typedef struct {
  __REG32 BRP                :10;
  __REG32                    :4;
  __REG32 SJW                :2;
  __REG32 TSEG1              :4;
  __REG32 TSEG2              :3;
  __REG32 SAM                :1;
  __REG32                    :8;
} __canbtr_bits;

/* CAN error warning limit register */
typedef struct {
  __REG32 EWL                :8;
  __REG32                    :24;
} __canewl_bits;

/* CAN status register */
typedef struct {
  __REG32 RBS                :1;
  __REG32 DOS                :1;
  __REG32 TBS1               :1;
  __REG32 TCS1               :1;
  __REG32 RS                 :1;
  __REG32 TS1                :1;
  __REG32 ES                 :1;
  __REG32 BS                 :1;
  __REG32 /*RBS*/            :1;
  __REG32 /*DOS*/            :1;
  __REG32 TBS2               :1;
  __REG32 TCS2               :1;
  __REG32 /*RS*/             :1;
  __REG32 TS2                :1;
  __REG32 /*ES*/             :1;
  __REG32 /*BS*/             :1;
  __REG32 /*RBS*/            :1;
  __REG32 /*DOS*/            :1;
  __REG32 TBS3               :1;
  __REG32 TCS3               :1;
  __REG32 /*RS*/             :1;
  __REG32 TS3                :1;
  __REG32 /*ES*/             :1;
  __REG32 /*BS*/             :1;
  __REG32                    :8;
} __cansr_bits;

/* CAN rx frame status register */
typedef struct {
  __REG32 IDINDEX            :10;
  __REG32 BP                 :1;
  __REG32                    :5;
  __REG32 DLC                :4;
  __REG32                    :10;
  __REG32 RTR                :1;
  __REG32 FF                 :1;
} __canrfs_bits;

/* CAN rx identifier register */
typedef union {
  //CANxRID
  struct {
   __REG32 ID10_0             :11;
   __REG32                    :21;
  };
  //CANxRID
  struct {
   __REG32 ID29_18            :11;
   __REG32                    :21;
  };
  //CANxRID
  struct {
   __REG32 ID29_0             :29;
   __REG32                    :3;
  };
} __canrid_bits;

/* CAN rx data register A */
typedef struct {
  __REG32 DATA1               :8;
  __REG32 DATA2               :8;
  __REG32 DATA3               :8;
  __REG32 DATA4               :8;
} __canrda_bits;

/* CAN rx data register B */
typedef struct {
  __REG32 DATA5               :8;
  __REG32 DATA6               :8;
  __REG32 DATA7               :8;
  __REG32 DATA8               :8;
} __canrdb_bits;

/* CAN tx frame information register */
typedef struct {
  __REG32 PRIO              :8;
  __REG32                   :8;
  __REG32 DLC               :4;
  __REG32                   :10;
  __REG32 RTR               :1;
  __REG32 FF                :1;
} __cantfi_bits;

/* CAN tx identifier register */
typedef union {
  //CANxTIDy
  struct {
   __REG32 ID10_0             :11;
   __REG32                    :21;
  };
  //CANxTIDy
  struct {
   __REG32 ID29_18            :11;
   __REG32                    :21;
  };
  //CANxTIDy
  struct {
   __REG32 ID29_0             :29;
   __REG32                    :3;
  };
} __cantid_bits;

/* CAN tx data register A */
typedef struct {
  __REG32 DATA1               :8;
  __REG32 DATA2               :8;
  __REG32 DATA3               :8;
  __REG32 DATA4               :8;
} __cantda_bits;

/* CAN tx data register B */
typedef struct {
  __REG32 DATA5               :8;
  __REG32 DATA6               :8;
  __REG32 DATA7               :8;
  __REG32 DATA8               :8;
} __cantdb_bits;

/* CAN Sleep Clear register */
typedef struct {
  __REG32                     :1;
  __REG32 CAN1SLEEP           :1;
  __REG32 CAN2SLEEP           :1;
  __REG32                     :29;
} __cansleepclr_bits;

/* CAN Wakeup Flags register */
typedef struct {
  __REG32                     :1;
  __REG32 CAN1WAKE            :1;
  __REG32 CAN2WAKE            :1;
  __REG32                     :29;
} __canwakeflags_bits;

/* SPI control register */
typedef struct{
__REG32           : 2;
__REG32 BITENABLE : 1;
__REG32 CPHA      : 1;
__REG32 CPOL      : 1;
__REG32 MSTR      : 1;
__REG32 LSBF      : 1;
__REG32 SPIE      : 1;
__REG32 BITS      : 4;
__REG32           :20;
} __spcr_bits;

/* SPI status register */
typedef struct{
__REG32         : 3;
__REG32 ABRT    : 1;
__REG32 MODF    : 1;
__REG32 ROVR    : 1;
__REG32 WCOL    : 1;
__REG32 SPIF    : 1;
__REG32         :24;
} __spsr_bits;

/* SPI clock counter register */
typedef struct{
__REG32 COUNTER  : 8;
__REG32          :24;
} __spccr_bits;

/* SPI interrupt register */
typedef struct{
__REG32 SPIINT  : 1;
__REG32         :31;
} __spint_bits;

/* SPI Test control register */
typedef struct{
__REG8          : 1;
__REG8  TEST    : 7;
} __sptcr_bits;

/* SPI Test Status Register */
typedef struct{
__REG8          : 3;
__REG8  ABRT    : 1;
__REG8  MODF    : 1;
__REG8  ROVR    : 1;
__REG8  WCOL    : 1;
__REG8  SPIF    : 1;
} __sptsr_bits;

/* SSP Control Register 0 */
typedef struct{
__REG32 DSS  : 4;
__REG32 FRF  : 2;
__REG32 CPOL : 1;
__REG32 CPHA : 1;
__REG32 SCR  : 8;
__REG32      :16;
} __sspcr0_bits;

/* SSP Control Register 1 */
typedef struct{
__REG32 LBM  : 1;
__REG32 SSE  : 1;
__REG32 MS   : 1;
__REG32 SOD  : 1;
__REG32      :28;
} __sspcr1_bits;

/* SSP Data Register */
typedef struct{
__REG32 DATA :16;
__REG32      :16;
} __sspdr_bits;

/* SSP Status Register */
typedef struct{
__REG32 TFE  : 1;
__REG32 TNF  : 1;
__REG32 RNE  : 1;
__REG32 RFF  : 1;
__REG32 BSY  : 1;
__REG32      :27;
} __sspsr_bits;

/* SSP Clock Prescale Register */
typedef struct{
__REG32 CPSDVSR : 8;
__REG32         :24;
} __sspcpsr_bits;

/* SSP Interrupt Mask Set/Clear Register */
typedef struct{
__REG32 RORIM  : 1;
__REG32 RTIM   : 1;
__REG32 RXIM   : 1;
__REG32 TXIM   : 1;
__REG32        :28;
} __sspimsc_bits;

/* SSP Raw Interrupt Status Register */
typedef struct{
__REG32 RORRIS  : 1;
__REG32 RTRIS   : 1;
__REG32 RXRIS   : 1;
__REG32 TXRIS   : 1;
__REG32         :28;
} __sspris_bits;

/* SSP Masked Interrupt Status Register */
typedef struct{
__REG32 RORMIS  : 1;
__REG32 RTMIS   : 1;
__REG32 RXMIS   : 1;
__REG32 TXMIS   : 1;
__REG32         :28;
} __sspmis_bits;

/* SSP Interrupt Clear Register */
typedef struct{
__REG32 RORIC  : 1;
__REG32 RTIC   : 1;
__REG32        :30;
} __sspicr_bits;

/* SSP DMA Control Register */
typedef struct{
__REG32 RXDMAE : 1;
__REG32 TXDMAE : 1;
__REG32        :30;
} __sspdmacr_bits;

/* I2C control set register */
typedef struct{
__REG32       : 2;
__REG32 AA    : 1;
__REG32 SI    : 1;
__REG32 STO   : 1;
__REG32 STA   : 1;
__REG32 I2EN  : 1;
__REG32       :25;
} __i2conset_bits;

/* I2C control clear register */
typedef struct{
__REG32        : 2;
__REG32 AAC    : 1;
__REG32 SIC    : 1;
__REG32        : 1;
__REG32 STAC   : 1;
__REG32 I2ENC  : 1;
__REG32        :25;
} __i2conclr_bits;

/* I2C status register */
typedef struct{
__REG32 STATUS  : 8;
__REG32         :24;
} __i2stat_bits;

/* I2C data register */
typedef struct{
__REG32 DATA  : 8;
__REG32       :24;
} __i2dat_bits;

/* I2C Monitor mode control register */
typedef struct{
__REG32 MM_ENA    : 1;
__REG32 ENA_SCL   : 1;
__REG32           : 1;
__REG32 MATCH_ALL : 1;
__REG32           :28;
} __i2cmmctrl_bits;

/* I2C slave address register */
typedef struct{
__REG32 GC    : 1;
__REG32 ADDR  : 7;
__REG32       :24;
} __i2adr_bits;

/* I2C Mask registers */
typedef struct{
__REG32       : 1;
__REG32 MASK  : 7;
__REG32       :24;
} __i2cmask_bits;

/* I2C SCL High Duty Cycle register */
typedef struct{
__REG32 SCLH   :16;
__REG32        :16;
} __i2sch_bits;

/* I2C scl duty cycle register */
typedef struct{
__REG32 SCLL   :16;
__REG32        :16;
} __i2scl_bits;

/* I2S Digital Audio Output Registes */
typedef struct{
__REG32 WORS_WIDTH    : 2;
__REG32 MONO          : 1;
__REG32 STOP          : 1;
__REG32 RESET         : 1;
__REG32 WS_SEL        : 1;
__REG32 WS_HALFPERIOD : 9;
__REG32 MUTE          : 1;
__REG32               :16;
} __i2sdao_bits;

/* I2S Digital Audio Input Register */
typedef struct{
__REG32 WORS_WIDTH    : 2;
__REG32 MONO          : 1;
__REG32 STOP          : 1;
__REG32 RESET         : 1;
__REG32 WS_SEL        : 1;
__REG32 WS_HALFPERIOD : 9;
__REG32               :17;
} __i2sdai_bits;

/* I2S Status Feedback Register */
typedef struct{
__REG32 IRQ           : 1;
__REG32 DMAREQ1       : 1;
__REG32 DMAREQ2       : 1;
__REG32               : 5;
__REG32 RX_LEVEL      : 5;
__REG32               : 3;
__REG32 TX_LEVEL      : 5;
__REG32               :11;
} __i2sstate_bits;

/* I2S DMA Configuration Register */
typedef struct{
__REG32 RX_DMA_EN     : 1;
__REG32 TX_DMA_EN     : 1;
__REG32               : 6;
__REG32 RX_DEPTH_DMA  : 5;
__REG32               : 3;
__REG32 TX_DEPTH_DMA  : 5;
__REG32               :11;
} __i2sdma_bits;

/* I2S Interrupt Request Control register */
typedef struct{
__REG32 RX_IRQ_EN     : 1;
__REG32 TX_IRQ_EN     : 1;
__REG32               : 6;
__REG32 RX_DEPTH_IRQ  : 5;
__REG32               : 3;
__REG32 TX_DEPTH_IRQ  : 5;
__REG32               :11;
} __i2sirq_bits;

/* I2S Transmit Clock Rate Register */
typedef struct{
__REG32 Y_DIVIDER     : 8;
__REG32 X_DIVIDER     : 8;
__REG32               :16;
} __i2stxrate_bits;

/* Transmit Clock Rate register */
typedef struct{
__REG32 TX_BITRATE    : 6;
__REG32               :26;
} __i2stxbitrate_bits;

/* Receive Clock Rate register */
typedef struct{
__REG32 RX_BITRATE    : 6;
__REG32               :26;
} __i2srxbitrate_bits;

/* Transmit Mode Control register */
typedef struct{
__REG32 TXCLKSEL      : 2;
__REG32 TX4PIN        : 1;
__REG32 TXMCDIR       : 1;
__REG32               :28;
} __i2stxmode_bits;

/* Receive Mode Control register */
typedef struct{
__REG32 RXCLKSEL      : 2;
__REG32 RX4PIN        : 1;
__REG32 RXMCDIR       : 1;
__REG32               :28;
} __i2srxmode_bits;

/* TIMER interrupt register */
typedef struct{
__REG32 MR0INT  : 1;
__REG32 MR1INT  : 1;
__REG32 MR2INT  : 1;
__REG32 MR3INT  : 1;
__REG32 CR0INT  : 1;
__REG32 CR1INT  : 1;
__REG32         :26;
} __ir_bits;

/* TIMER control register */
typedef struct{
__REG32 CE  : 1;
__REG32 CR  : 1;
__REG32     :30;
} __tcr_bits;

/* TIMER count control register */
typedef struct{
__REG32 CTM : 2;     //Counter/Timer Mode
__REG32 CIS : 2;     //Count Input Select
__REG32     :28;
} __ctcr_bits;

/* TIMER match control register */
typedef struct{
__REG32 MR0I     : 1;
__REG32 MR0R     : 1;
__REG32 MR0S     : 1;
__REG32 MR1I     : 1;
__REG32 MR1R     : 1;
__REG32 MR1S     : 1;
__REG32 MR2I     : 1;
__REG32 MR2R     : 1;
__REG32 MR2S     : 1;
__REG32 MR3I     : 1;
__REG32 MR3R     : 1;
__REG32 MR3S     : 1;
__REG32          :20;
} __mcr_bits;

/* TIMER capture control register */
typedef struct{
__REG32 CAP0RE   : 1;
__REG32 CAP0FE   : 1;
__REG32 CAP0I    : 1;
__REG32 CAP1RE   : 1;
__REG32 CAP1FE   : 1;
__REG32 CAP1I    : 1;
__REG32          :26;
} __tccr_bits;

/* TIMER external match register */
typedef struct{
__REG32 EM0   : 1;
__REG32 EM1   : 1;
__REG32 EM2   : 1;
__REG32 EM3   : 1;
__REG32 EMC0  : 2;
__REG32 EMC1  : 2;
__REG32 EMC2  : 2;
__REG32 EMC3  : 2;
__REG32       :20;
} __emr_bits;

/* RI Control register */
typedef struct{
__REG32 RITINT   : 1;
__REG32 RITENCLR : 1;
__REG32 RITENBR  : 1;
__REG32 RITEN    : 1;
__REG32          :28;
} __rictrl_bits;

/* PWM interrupt register */
typedef struct{
__REG32 PWMMR0I : 1;
__REG32 PWMMR1I : 1;
__REG32 PWMMR2I : 1;
__REG32 PWMMR3I : 1;
__REG32 PWMCAP0 : 1;
__REG32 PWMCAP1 : 1;
__REG32         : 2;
__REG32 PWMMR4I : 1;
__REG32 PWMMR5I : 1;
__REG32 PWMMR6I : 1;
__REG32         :21;
} __pwmir_bits;

/* PWM1 timer control register */
typedef struct{
__REG32 CE     : 1;
__REG32 CR     : 1;
__REG32        : 1;
__REG32 PWMEN  : 1;
__REG32        :28;
} __pwmtcr1_bits;

/* PWM Count Control Register */
typedef struct{
__REG32 CM     : 2;
__REG32 CIS    : 2;
__REG32        :28;
} __pwmctcr_bits;

/* PWM match control register */
typedef struct{
__REG32 PWMMR0I  : 1;
__REG32 PWMMR0R  : 1;
__REG32 PWMMR0S  : 1;
__REG32 PWMMR1I  : 1;
__REG32 PWMMR1R  : 1;
__REG32 PWMMR1S  : 1;
__REG32 PWMMR2I  : 1;
__REG32 PWMMR2R  : 1;
__REG32 PWMMR2S  : 1;
__REG32 PWMMR3I  : 1;
__REG32 PWMMR3R  : 1;
__REG32 PWMMR3S  : 1;
__REG32 PWMMR4I  : 1;
__REG32 PWMMR4R  : 1;
__REG32 PWMMR4S  : 1;
__REG32 PWMMR5I  : 1;
__REG32 PWMMR5R  : 1;
__REG32 PWMMR5S  : 1;
__REG32 PWMMR6I  : 1;
__REG32 PWMMR6R  : 1;
__REG32 PWMMR6S  : 1;
__REG32          :11;
} __pwmmcr_bits;

/* PWM Capture Control Register */
typedef struct{
__REG32 CAP0RE   : 1;
__REG32 CAP0FE   : 1;
__REG32 CAP0INT  : 1;
__REG32 CAP1RE   : 1;
__REG32 CAP1FE   : 1;
__REG32 CAP1INT  : 1;
__REG32          :26;
} __pwmccr_bits;

/* PWM  control register */
typedef struct{
__REG32         : 2;
__REG32 PWMSEL2 : 1;
__REG32 PWMSEL3 : 1;
__REG32 PWMSEL4 : 1;
__REG32 PWMSEL5 : 1;
__REG32 PWMSEL6 : 1;
__REG32         : 2;
__REG32 PWMENA1 : 1;
__REG32 PWMENA2 : 1;
__REG32 PWMENA3 : 1;
__REG32 PWMENA4 : 1;
__REG32 PWMENA5 : 1;
__REG32 PWMENA6 : 1;
__REG32         :17;
} __pwmpcr_bits;

/* PWM latch enable register */
typedef struct{
__REG32 EM0L  : 1;
__REG32 EM1L  : 1;
__REG32 EM2L  : 1;
__REG32 EM3L  : 1;
__REG32 EM4L  : 1;
__REG32 EM5L  : 1;
__REG32 EM6L  : 1;
__REG32       :25;
} __pwmler_bits;

/* MCPWM Control read address */
typedef struct{
__REG32 RUN0    : 1;
__REG32 CENTER0 : 1;
__REG32 POLA0   : 1;
__REG32 DTE0    : 1;
__REG32 DISUP0  : 1;
__REG32         : 3;
__REG32 RUN1    : 1;
__REG32 CENTER1 : 1;
__REG32 POLA1   : 1;
__REG32 DTE1    : 1;
__REG32 DISUP1  : 1;
__REG32         : 3;
__REG32 RUN2    : 1;
__REG32 CENTER2 : 1;
__REG32 POLA2   : 1;
__REG32 DTE2    : 1;
__REG32 DISUP2  : 1;
__REG32         : 8;
__REG32 INVBDC  : 1;
__REG32 ACMODE  : 1;
__REG32 DCMODE  : 1;
} __mccon_bits;

/* Capture control register */
typedef struct{
__REG32 CAP0MCI0_RE : 1;
__REG32 CAP0MCI0_FE : 1;
__REG32 CAP0MCI1_RE : 1;
__REG32 CAP0MCI1_FE : 1;
__REG32 CAP0MCI2_RE : 1;
__REG32 CAP0MCI2_FE : 1;
__REG32 CAP1MCI0_RE : 1;
__REG32 CAP1MCI0_FE : 1;
__REG32 CAP1MCI1_RE : 1;
__REG32 CAP1MCI1_FE : 1;
__REG32 CAP1MCI2_RE : 1;
__REG32 CAP1MCI2_FE : 1;
__REG32 CAP2MCI0_RE : 1;
__REG32 CAP2MCI0_FE : 1;
__REG32 CAP2MCI1_RE : 1;
__REG32 CAP2MCI1_FE : 1;
__REG32 CAP2MCI2_RE : 1;
__REG32 CAP2MCI2_FE : 1;
__REG32 RT0         : 1;
__REG32 RT1         : 1;
__REG32 RT2         : 1;
__REG32 HNFCAP0     : 1;
__REG32 HNFCAP1     : 1;
__REG32 HNFCAP2     : 1;
__REG32             : 8;
} __mccapcon_bits;

/* PWM interrupt enable register */
typedef struct{
__REG32 ILIM0       : 1;
__REG32 IMAT0       : 1;
__REG32 ICAP0       : 1;
__REG32             : 1;
__REG32 ILIM1       : 1;
__REG32 IMAT1       : 1;
__REG32 ICAP1       : 1;
__REG32             : 1;
__REG32 ILIM2       : 1;
__REG32 IMAT2       : 1;
__REG32 ICAP2       : 1;
__REG32             :21;
} __mcinten_bits;

/* Count control register */
typedef struct{
__REG32 TC0MCI0_RE  : 1;
__REG32 TC0MCI0_FE  : 1;
__REG32 TC0MCI1_RE  : 1;
__REG32 TC0MCI1_FE  : 1;
__REG32 TC0MCI2_RE  : 1;
__REG32 TC0MCI2_FE  : 1;
__REG32 TC1MCI0_RE  : 1;
__REG32 TC1MCI0_FE  : 1;
__REG32 TC1MCI1_RE  : 1;
__REG32 TC1MCI1_FE  : 1;
__REG32 TC1MCI2_RE  : 1;
__REG32 TC1MCI2_FE  : 1;
__REG32 TC2MCI0_RE  : 1;
__REG32 TC2MCI0_FE  : 1;
__REG32 TC2MCI1_RE  : 1;
__REG32 TC2MCI1_FE  : 1;
__REG32 TC2MCI2_RE  : 1;
__REG32 TC2MCI2_FE  : 1;
__REG32             :11;
__REG32 CNTR0       : 1;
__REG32 CNTR1       : 1;
__REG32 CNTR2       : 1;
} __mccntcon_bits;

/* Dead-time register */
typedef struct{
__REG32 DT0         :10;
__REG32 DT1         :10;
__REG32 DT2         :10;
__REG32             : 2;
} __mcdt_bits;

/* Current communication pattern register */
typedef struct{
__REG32 CCPA0       : 1;
__REG32 CCPB0       : 1;
__REG32 CCPA1       : 1;
__REG32 CCPB1       : 1;
__REG32 CCPA2       : 1;
__REG32 CCPB2       : 1;
__REG32             :26;
} __mcccp_bits;

/* Capture clear register */
typedef struct{
__REG32 CAP_CLR0    : 1;
__REG32 CAP_CLR1    : 1;
__REG32 CAP_CLR2    : 1;
__REG32             :29;
} __mccap_clr_bits;

/* QEI Control register */
typedef struct{
__REG32 RESP        : 1;
__REG32 RESPI       : 1;
__REG32 RESV        : 1;
__REG32 RESI        : 1;
__REG32             :28;
} __qeicon_bits;

/* QEI Configuration register */
typedef struct{
__REG32 DIRINV      : 1;
__REG32 SIGMODE     : 1;
__REG32 CAPMODE     : 1;
__REG32 INVINX      : 1;
__REG32             :28;
} __qeiconf_bits;

/* QEI Status register */
typedef struct{
__REG32 DIR         : 1;
__REG32             :31;
} __qeistat_bits;

/* QEI Interrupt Status register */
/* QEI Interrupt Set register */
/* QEI Interrupt Clear register */
typedef struct{
__REG32 INX_INT     : 1;
__REG32 TIM_INT     : 1;
__REG32 VELC_INT    : 1;
__REG32 DIR_INT     : 1;
__REG32 ERR_INT     : 1;
__REG32 ENCLK_INT   : 1;
__REG32 POS0_INT    : 1;
__REG32 POS1_INT    : 1;
__REG32 POS2_INT    : 1;
__REG32 REV_INT     : 1;
__REG32 POS0REV_INT : 1;
__REG32 POS1REV_INT : 1;
__REG32 POS2REV_INT : 1;
__REG32             :19;
} __qeiintstat_bits;

/* RTC interrupt location register */
typedef struct{
__REG32 RTCCIF  : 1;
__REG32 RTCALF  : 1;
__REG32         :30;
} __ilr_bits;

/* RTC clock control register */
typedef struct{
__REG32 CLKEN   : 1;
__REG32 CTCRST  : 1;
__REG32         : 2;
__REG32 CCALEN  : 1;
__REG32         :27;
} __rtcccr_bits;

/* RTC counter increment interrupt register */
typedef struct{
__REG32 IMSEC   : 1;
__REG32 IMMIN   : 1;
__REG32 IMHOUR  : 1;
__REG32 IMDOM   : 1;
__REG32 IMDOW   : 1;
__REG32 IMDOY   : 1;
__REG32 IMMON   : 1;
__REG32 IMYEAR  : 1;
__REG32         :24;
} __ciir_bits;

/* RTC Counter Increment Select Mask Register */
typedef struct{
__REG32 CALVAL    :17;
__REG32 CALDIR    : 1;
__REG32           :14;
} __calibration_bits;

/* RTC alarm mask register */
typedef struct{
__REG32 AMRSEC   : 1;
__REG32 AMRMIN   : 1;
__REG32 AMRHOUR  : 1;
__REG32 AMRDOM   : 1;
__REG32 AMRDOW   : 1;
__REG32 AMRDOY   : 1;
__REG32 AMRMON   : 1;
__REG32 AMRYEAR  : 1;
__REG32          :24;
} __amr_bits;

/* RTC Auxiliary control register */
typedef struct{
__REG32           : 4;
__REG32 RTC_OSCF  : 1;
__REG32           :27;
} __rtcaux_bits;

/* RTC Auxiliary Enable register */
typedef struct{
__REG32           : 4;
__REG32 RTC_OSCFEN: 1;
__REG32           :27;
} __rtcauxen_bits;

/* RTC consolidated time register 0 */
typedef struct{
__REG32 SEC   : 6;
__REG32       : 2;
__REG32 MIN   : 6;
__REG32       : 2;
__REG32 HOUR  : 5;
__REG32       : 3;
__REG32 DOW   : 3;
__REG32       : 5;
} __ctime0_bits;

/* RTC consolidated time register 1 */
typedef struct{
__REG32 DOM   : 5;
__REG32       : 3;
__REG32 MON   : 4;
__REG32       : 4;
__REG32 YEAR  :12;
__REG32       : 4;
} __ctime1_bits;

/* RTC consolidated time register 2 */
typedef struct{
__REG32 DOY  :12;
__REG32      :20;
} __ctime2_bits;

/* RTC second register */
typedef struct{
__REG32 SEC  : 6;
__REG32      :26;
} __sec_bits;

/* RTC minute register */
typedef struct{
__REG32 MIN  : 6;
__REG32      :26;
} __min_bits;

/* RTC hour register */
typedef struct{
__REG32 HOUR  : 5;
__REG32       :27;
} __hour_bits;

/* RTC day of month register */
typedef struct{
__REG32 DOM  : 5;
__REG32      :27;
} __dom_bits;

/* RTC day of week register */
typedef struct{
__REG32 DOW  : 3;
__REG32      :29;
} __dow_bits;

/* RTC day of year register */
typedef struct{
__REG32 DOY  : 9;
__REG32      :23;
} __doy_bits;

/* RTC month register */
typedef struct{
__REG32 MON  : 4;
__REG32      :28;
} __month_bits;

/* RTC year register */
typedef struct{
__REG32 YEAR  :12;
__REG32       :20;
} __year_bits;

/* Watchdog mode register */
typedef struct{
__REG32 WDEN     : 1;
__REG32 WDRESET  : 1;
__REG32 WDTOF    : 1;
__REG32 WDINT    : 1;
__REG32          :28;
} __wdmod_bits;

/* Watchdog feed register */
typedef struct{
__REG32 FEED  : 8;
__REG32       :24;
} __wdfeed_bits;

/* Watchdog feed register */
typedef struct{
__REG32 WDSEL : 2;
__REG32       :29;
__REG32 WDLOCK: 1;
} __wdclksel_bits;

/* A/D Control Register */
typedef struct{
__REG32 SEL     : 8;
__REG32 CLKDIV  : 8;
__REG32 BURST   : 1;
__REG32         : 4;
__REG32 PDN     : 1;
__REG32         : 2;
__REG32 START   : 3;
__REG32 EDGE    : 1;
__REG32         : 4;
} __adcr_bits;

/* A/D Global Data Register */
typedef struct{
__REG32         : 4;
__REG32 RESULT  :12;
__REG32         : 8;
__REG32 CHN     : 3;
__REG32         : 3;
__REG32 OVERUN  : 1;
__REG32 DONE    : 1;
} __adgdr_bits;

/* A/D Status Register */
typedef struct{
__REG32 DONE0     : 1;
__REG32 DONE1     : 1;
__REG32 DONE2     : 1;
__REG32 DONE3     : 1;
__REG32 DONE4     : 1;
__REG32 DONE5     : 1;
__REG32 DONE6     : 1;
__REG32 DONE7     : 1;
__REG32 OVERRUN0  : 1;
__REG32 OVERRUN1  : 1;
__REG32 OVERRUN2  : 1;
__REG32 OVERRUN3  : 1;
__REG32 OVERRUN4  : 1;
__REG32 OVERRUN5  : 1;
__REG32 OVERRUN6  : 1;
__REG32 OVERRUN7  : 1;
__REG32 ADINT     : 1;
__REG32           :15;
} __adstat_bits;

/* A/D Intrrupt Enable Register */
typedef struct{
__REG32 ADINTEN0  : 1;
__REG32 ADINTEN1  : 1;
__REG32 ADINTEN2  : 1;
__REG32 ADINTEN3  : 1;
__REG32 ADINTEN4  : 1;
__REG32 ADINTEN5  : 1;
__REG32 ADINTEN6  : 1;
__REG32 ADINTEN7  : 1;
__REG32 ADGINTEN  : 1;
__REG32           :23;
} __adinten_bits;

/* A/D Data Register */
typedef struct{
__REG32         : 4;
__REG32 RESULT  :12;
__REG32         :14;
__REG32 OVERUN  : 1;
__REG32 DONE    : 1;
} __addr_bits;

/* A/D Trim register */
typedef struct{
__REG32         : 4;
__REG32 ADCOFFS : 4;
__REG32 TRIM    : 4;
__REG32         :20;
} __adtrm_bits;

/* D/A Converter Register */
typedef struct{
__REG32        : 6;
__REG32 VALUE  :10;
__REG32 BIAS   : 1;
__REG32        :15;
} __dacr_bits;

/* D/A Converter Control register */
typedef struct{
__REG32 INT_DMA_REQ : 1;
__REG32 DBLBUF_ENA  : 1;
__REG32 CNT_ENA     : 1;
__REG32 DMA_ENA     : 1;
__REG32             :28;
} __dacctrl_bits;

/* D/A Converter Counter Value register */
typedef struct{
__REG32 VALUE       :16;
__REG32             :16;
} __daccntval_bits;

/* DMA Interrupt Status Register */
typedef struct{
__REG32 INTSTATUS0  : 1;
__REG32 INTSTATUS1  : 1;
__REG32 INTSTATUS2  : 1;
__REG32 INTSTATUS3  : 1;
__REG32 INTSTATUS4  : 1;
__REG32 INTSTATUS5  : 1;
__REG32 INTSTATUS6  : 1;
__REG32 INTSTATUS7  : 1;
__REG32             :24;
} __dmacintstatus_bits;

/* DMA Interrupt Terminal Count Request Status Register */
typedef struct{
__REG32 INTTCSTATUS0  : 1;
__REG32 INTTCSTATUS1  : 1;
__REG32 INTTCSTATUS2  : 1;
__REG32 INTTCSTATUS3  : 1;
__REG32 INTTCSTATUS4  : 1;
__REG32 INTTCSTATUS5  : 1;
__REG32 INTTCSTATUS6  : 1;
__REG32 INTTCSTATUS7  : 1;
__REG32               :24;
} __dmacinttcstatus_bits;

/* DMA Interrupt Terminal Count Request Clear Register */
typedef struct{
__REG32 INTTCCLEAR0   : 1;
__REG32 INTTCCLEAR1   : 1;
__REG32 INTTCCLEAR2   : 1;
__REG32 INTTCCLEAR3   : 1;
__REG32 INTTCCLEAR4   : 1;
__REG32 INTTCCLEAR5   : 1;
__REG32 INTTCCLEAR6   : 1;
__REG32 INTTCCLEAR7   : 1;
__REG32               :24;
} __dmacinttcclear_bits;

/* DMA Interrupt Error Status Register */
typedef struct{
__REG32 INTERRORSTATUS0 : 1;
__REG32 INTERRORSTATUS1 : 1;
__REG32 INTERRORSTATUS2 : 1;
__REG32 INTERRORSTATUS3 : 1;
__REG32 INTERRORSTATUS4 : 1;
__REG32 INTERRORSTATUS5 : 1;
__REG32 INTERRORSTATUS6 : 1;
__REG32 INTERRORSTATUS7 : 1;
__REG32                 :24;
} __dmacinterrstat_bits;

/* DMA Interrupt Error Clear Register */
typedef struct{
__REG32 INTERRCLR0      : 1;
__REG32 INTERRCLR1      : 1;
__REG32 INTERRCLR2      : 1;
__REG32 INTERRCLR3      : 1;
__REG32 INTERRCLR4      : 1;
__REG32 INTERRCLR5      : 1;
__REG32 INTERRCLR6      : 1;
__REG32 INTERRCLR7      : 1;
__REG32                 :24;
} __dmacinterrclr_bits;

/* DMA Raw Interrupt Terminal Count Status Register */
typedef struct{
__REG32 RAWINTTCSTATUS0 : 1;
__REG32 RAWINTTCSTATUS1 : 1;
__REG32 RAWINTTCSTATUS2 : 1;
__REG32 RAWINTTCSTATUS3 : 1;
__REG32 RAWINTTCSTATUS4 : 1;
__REG32 RAWINTTCSTATUS5 : 1;
__REG32 RAWINTTCSTATUS6 : 1;
__REG32 RAWINTTCSTATUS7 : 1;
__REG32                 :24;
} __dmacrawinttcstatus_bits;

/* DMA Raw Error Interrupt Status Register */
typedef struct{
__REG32 RAWINTERRORSTATUS0  : 1;
__REG32 RAWINTERRORSTATUS1  : 1;
__REG32 RAWINTERRORSTATUS2  : 1;
__REG32 RAWINTERRORSTATUS3  : 1;
__REG32 RAWINTERRORSTATUS4  : 1;
__REG32 RAWINTERRORSTATUS5  : 1;
__REG32 RAWINTERRORSTATUS6  : 1;
__REG32 RAWINTERRORSTATUS7  : 1;
__REG32                     :24;
} __dmacrawinterrorstatus_bits;

/* DMA Enabled Channel Register */
typedef struct{
__REG32 ENABLEDCHANNELS0  : 1;
__REG32 ENABLEDCHANNELS1  : 1;
__REG32 ENABLEDCHANNELS2  : 1;
__REG32 ENABLEDCHANNELS3  : 1;
__REG32 ENABLEDCHANNELS4  : 1;
__REG32 ENABLEDCHANNELS5  : 1;
__REG32 ENABLEDCHANNELS6  : 1;
__REG32 ENABLEDCHANNELS7  : 1;
__REG32                   :24;
} __dmacenbldchns_bits;

/* DMA Software Burst Request Register */
typedef struct{
__REG32 SOFTBREQSSP0TX    : 1;
__REG32 SOFTBREQSSP0RX    : 1;
__REG32 SOFTBREQSSP1TX    : 1;
__REG32 SOFTBREQSSP1RX    : 1;
__REG32 SOFTBREQSADC      : 1;
__REG32 SOFTBREQSI2S0     : 1;
__REG32 SOFTBREQSI2S1     : 1;
__REG32 SOFTBREQSDAC      : 1;
__REG32 SOFTBREQSU0TXM00  : 1;
__REG32 SOFTBREQSU0RXM01  : 1;
__REG32 SOFTBREQSU1TXM10  : 1;
__REG32 SOFTBREQSU1RXM11  : 1;
__REG32 SOFTBREQSU2TXM20  : 1;
__REG32 SOFTBREQSU2RXM21  : 1;
__REG32 SOFTBREQSU3TXM30  : 1;
__REG32 SOFTBREQSU3RXM31  : 1;
__REG32                   :16;
} __dmacsoftbreq_bits;

/* DMA Software Single Request Register */
typedef struct{
__REG32 SOFTREQSSP0TX     : 1;
__REG32 SOFTREQSSP0RX     : 1;
__REG32 SOFTREQSSP1TX     : 1;
__REG32 SOFTREQSSP1RX     : 1;
__REG32 SOFTREQSADC       : 1;
__REG32                   :27;
} __dmacsoftsreq_bits;

/* DMA Software Last Burst Request Register */
typedef struct{
__REG32 SOFTLBREQSSP0TX    : 1;
__REG32 SOFTLBREQSSP0RX    : 1;
__REG32 SOFTLBREQSSP1TX    : 1;
__REG32 SOFTLBREQSSP1RX    : 1;
__REG32 SOFTLBREQSADC      : 1;
__REG32 SOFTLBREQSI2S0     : 1;
__REG32 SOFTLBREQSI2S1     : 1;
__REG32 SOFTLBREQSDAC      : 1;
__REG32 SOFTLBREQSU0TXM00  : 1;
__REG32 SOFTLBREQSU0RXM01  : 1;
__REG32 SOFTLBREQSU1TXM10  : 1;
__REG32 SOFTLBREQSU1RXM11  : 1;
__REG32 SOFTLBREQSU2TXM20  : 1;
__REG32 SOFTLBREQSU2RXM21  : 1;
__REG32 SOFTLBREQSU3TXM30  : 1;
__REG32 SOFTLBREQSU3RXM31  : 1;
__REG32                    :16;
} __dmacsoftlbreq_bits;

/* DMA Software Last Single Request Register */
typedef struct{
__REG32 SOFTLSREQSSP0TX     : 1;
__REG32 SOFTLSREQSSP0RX     : 1;
__REG32 SOFTLSREQSSP1TX     : 1;
__REG32 SOFTLSREQSSP1RX     : 1;
__REG32 SOFTLSREQSADC       : 1;
__REG32                     :27;
} __dmacsoftlsreq_bits;

/* DMA Synchronization Register */
typedef struct{
__REG32 DMACSYNC0   : 1;
__REG32 DMACSYNC1   : 1;
__REG32 DMACSYNC2   : 1;
__REG32 DMACSYNC3   : 1;
__REG32 DMACSYNC4   : 1;
__REG32 DMACSYNC5   : 1;
__REG32 DMACSYNC6   : 1;
__REG32 DMACSYNC7   : 1;
__REG32 DMACSYNC8   : 1;
__REG32 DMACSYNC9   : 1;
__REG32 DMACSYNC10  : 1;
__REG32 DMACSYNC11  : 1;
__REG32 DMACSYNC12  : 1;
__REG32 DMACSYNC13  : 1;
__REG32 DMACSYNC14  : 1;
__REG32 DMACSYNC15  : 1;
__REG32             :16;
} __dmacsync_bits;

/* DMA Configuration Register */
typedef struct{
__REG32 E   : 1;
__REG32 M   : 1;
__REG32     :30;
} __dmacconfig_bits;

/* DMA Request Select register */
typedef struct{
__REG32 DMASEL08  : 1;
__REG32 DMASEL09  : 1;
__REG32 DMASEL10  : 1;
__REG32 DMASEL11  : 1;
__REG32 DMASEL12  : 1;
__REG32 DMASEL13  : 1;
__REG32 DMASEL14  : 1;
__REG32 DMASEL15  : 1;
__REG32           :24;
} __dmareqsel_bits;

/* DMA Channel Control Registers */
typedef struct{
__REG32 TRANSFERSIZE  :12;
__REG32 SBSIZE        : 3;
__REG32 DBSIZE        : 3;
__REG32 SWIDTH        : 3;
__REG32 DWIDTH        : 3;
__REG32               : 2;
__REG32 SI            : 1;
__REG32 DI            : 1;
__REG32 PROT1         : 1;
__REG32 PROT2         : 1;
__REG32 PROT3         : 1;
__REG32 I             : 1;
} __dma_ctrl_bits;

/* DMA Channel Configuration Registers */
typedef struct{
__REG32 E               : 1;
__REG32 SRCPERIPHERAL   : 5;
__REG32 DESTPERIPHERAL  : 5;
__REG32 FLOWCNTRL       : 3;
__REG32 IE              : 1;
__REG32 ITC             : 1;
__REG32 L               : 1;
__REG32 A               : 1;
__REG32 H               : 1;
__REG32                 :13;
} __dma_cfg_bits;

/* Memory mapping control register */
typedef struct{
__REG32 MAP         : 2;
__REG32             :30;
} __memmap_bits;

#endif    /* __IAR_SYSTEMS_ICC__ */

/* Declarations common to compiler and assembler **************************/

/***************************************************************************
 **
 ** NVIC
 **
 ***************************************************************************/
__IO_REG32_BIT(NVIC,                  0xE000E004,__READ       ,__nvic_bits);
__IO_REG32_BIT(SYSTICKCSR,            0xE000E010,__READ_WRITE ,__systickcsr_bits);
#define STCTRL      SYSTICKCSR
#define STCTRL_bit  SYSTICKCSR_bit
__IO_REG32_BIT(SYSTICKRVR,            0xE000E014,__READ_WRITE ,__systickrvr_bits);
#define STRELOAD      SYSTICKRVR
#define STRELOAD_bit  SYSTICKRVR_bit
__IO_REG32_BIT(SYSTICKCVR,            0xE000E018,__READ_WRITE ,__systickcvr_bits);
#define STCURR      SYSTICKCVR
#define STCURR_bit  SYSTICKCVR_bit
__IO_REG32_BIT(SYSTICKCALVR,          0xE000E01C,__READ       ,__systickcalvr_bits);
#define STCALIB      SYSTICKCALVR
#define STCALIB_bit  SYSTICKCALVR_bit
__IO_REG32_BIT(SETENA0,               0xE000E100,__READ_WRITE ,__setena0_bits);
__IO_REG32_BIT(SETENA1,               0xE000E104,__READ_WRITE ,__setena1_bits);
__IO_REG32_BIT(CLRENA0,               0xE000E180,__READ_WRITE ,__clrena0_bits);
__IO_REG32_BIT(CLRENA1,               0xE000E184,__READ_WRITE ,__clrena1_bits);
__IO_REG32_BIT(SETPEND0,              0xE000E200,__READ_WRITE ,__setpend0_bits);
__IO_REG32_BIT(SETPEND1,              0xE000E204,__READ_WRITE ,__setpend1_bits);
__IO_REG32_BIT(CLRPEND0,              0xE000E280,__READ_WRITE ,__clrpend0_bits);
__IO_REG32_BIT(CLRPEND1,              0xE000E284,__READ_WRITE ,__clrpend1_bits);
__IO_REG32_BIT(ACTIVE0,               0xE000E300,__READ       ,__active0_bits);
__IO_REG32_BIT(ACTIVE1,               0xE000E304,__READ       ,__active1_bits);
__IO_REG32_BIT(IP0,                   0xE000E400,__READ_WRITE ,__pri0_bits);
__IO_REG32_BIT(IP1,                   0xE000E404,__READ_WRITE ,__pri1_bits);
__IO_REG32_BIT(IP2,                   0xE000E408,__READ_WRITE ,__pri2_bits);
__IO_REG32_BIT(IP3,                   0xE000E40C,__READ_WRITE ,__pri3_bits);
__IO_REG32_BIT(IP4,                   0xE000E410,__READ_WRITE ,__pri4_bits);
__IO_REG32_BIT(IP5,                   0xE000E414,__READ_WRITE ,__pri5_bits);
__IO_REG32_BIT(IP6,                   0xE000E418,__READ_WRITE ,__pri6_bits);
__IO_REG32_BIT(IP7,                   0xE000E41C,__READ_WRITE ,__pri7_bits);
__IO_REG32_BIT(IP8,                   0xE000E420,__READ_WRITE ,__pri8_bits);
__IO_REG32_BIT(IP9,                   0xE000E424,__READ_WRITE ,__pri9_bits);
__IO_REG32_BIT(IP10,                  0xE000E428,__READ_WRITE ,__pri10_bits);
__IO_REG32_BIT(IP11,                  0xE000E42C,__READ_WRITE ,__pri11_bits);
__IO_REG32_BIT(IP12,                  0xE000E430,__READ_WRITE ,__pri12_bits);
__IO_REG32_BIT(IP13,                  0xE000E434,__READ_WRITE ,__pri13_bits);
__IO_REG32_BIT(IP14,                  0xE000E438,__READ_WRITE ,__pri14_bits);
__IO_REG32_BIT(IP15,                  0xE000E43C,__READ_WRITE ,__pri15_bits);
__IO_REG32_BIT(CPUIDBR,               0xE000ED00,__READ       ,__cpuidbr_bits);
__IO_REG32_BIT(ICSR,                  0xE000ED04,__READ_WRITE ,__icsr_bits);
__IO_REG32_BIT(VTOR,                  0xE000ED08,__READ_WRITE ,__vtor_bits);
__IO_REG32_BIT(AIRCR,                 0xE000ED0C,__READ_WRITE ,__aircr_bits);
__IO_REG32_BIT(SCR,                   0xE000ED10,__READ_WRITE ,__scr_bits);
__IO_REG32_BIT(CCR,                   0xE000ED14,__READ_WRITE ,__ccr_bits);
__IO_REG32_BIT(SHPR0,                 0xE000ED18,__READ_WRITE ,__pri1_bits);
__IO_REG32_BIT(SHPR1,                 0xE000ED1C,__READ_WRITE ,__pri2_bits);
__IO_REG32_BIT(SHPR2,                 0xE000ED20,__READ_WRITE ,__pri3_bits);
__IO_REG32_BIT(SHCSR,                 0xE000ED24,__READ_WRITE ,__shcsr_bits);
__IO_REG32_BIT(CFSR,                  0xE000ED28,__READ_WRITE ,__cfsr_bits);
__IO_REG32_BIT(HFSR,                  0xE000ED2C,__READ_WRITE ,__hfsr_bits);
__IO_REG32_BIT(DFSR,                  0xE000ED30,__READ_WRITE ,__dfsr_bits);
__IO_REG32(    MMFAR,                 0xE000ED34,__READ_WRITE);
__IO_REG32(    BFAR,                  0xE000ED38,__READ_WRITE);
__IO_REG32_BIT(STIR,                  0xE000EF00,__WRITE      ,__stir_bits);

/***************************************************************************
 **
 ** System control block
 **
 ***************************************************************************/
__IO_REG32_BIT(MEMMAP,                0x400FC040,__READ_WRITE ,__memmap_bits);
__IO_REG32_BIT(EXTINT,                0x400FC140,__READ_WRITE ,__extint_bits);
__IO_REG32_BIT(EXTMODE,               0x400FC148,__READ_WRITE ,__extmode_bits);
__IO_REG32_BIT(EXTPOLAR,              0x400FC14C,__READ_WRITE ,__extpolar_bits);
__IO_REG32_BIT(RSID,                  0x400FC180,__READ_WRITE ,__rsid_bits);
__IO_REG32_BIT(SCS,                   0x400FC1A0,__READ_WRITE ,__scs_bits);
__IO_REG32_BIT(CLKSRCSEL,             0x400FC10C,__READ_WRITE ,__clksrcsel_bits);
__IO_REG32_BIT(PLL0CON,               0x400FC080,__READ_WRITE ,__pllcon_bits);
__IO_REG32_BIT(PLL0CFG,               0x400FC084,__READ_WRITE ,__pllcfg_bits);
__IO_REG32_BIT(PLL0STAT,              0x400FC088,__READ       ,__pllstat_bits);
__IO_REG32_BIT(PLL0FEED,              0x400FC08C,__WRITE      ,__pllfeed_bits);
__IO_REG32_BIT(PLL1CON,               0x400FC0A0,__READ_WRITE ,__pllcon_bits);
__IO_REG32_BIT(PLL1CFG,               0x400FC0A4,__READ_WRITE ,__pll1cfg_bits);
__IO_REG32_BIT(PLL1STAT,              0x400FC0A8,__READ       ,__pll1stat_bits);
__IO_REG32_BIT(PLL1FEED,              0x400FC0AC,__WRITE      ,__pllfeed_bits);
__IO_REG32_BIT(CCLKCFG,               0x400FC104,__READ_WRITE ,__cclkcfg_bits);
__IO_REG32_BIT(USBCLKCFG,             0x400FC108,__READ_WRITE ,__usbclkcfg_bits);
__IO_REG32_BIT(IRCTRIM,               0x400FC1A4,__READ_WRITE ,__irctrim_bits);
__IO_REG32_BIT(PCLKSEL0,              0x400FC1A8,__READ_WRITE ,__pclksel0_bits);
__IO_REG32_BIT(PCLKSEL1,              0x400FC1AC,__READ_WRITE ,__pclksel1_bits);
__IO_REG32_BIT(PCON,                  0x400FC0C0,__READ_WRITE ,__pcon_bits);
__IO_REG32_BIT(PCONP,                 0x400FC0C4,__READ_WRITE ,__pconp_bits);
__IO_REG32_BIT(CLKOUTCFG,             0x400FC1C8,__READ_WRITE ,__clkoutcfg_bits);

/***************************************************************************
 **
 ** Flash Accelerator
 **
 ***************************************************************************/
__IO_REG32_BIT(FLASHCFG,              0x400FC000,__READ_WRITE ,__flashcfg_bits);

/***************************************************************************
 **
 ** Pin connect block
 **
 ***************************************************************************/
__IO_REG32_BIT(PINSEL0,               0x4002C000,__READ_WRITE ,__pinsel0_bits);
__IO_REG32_BIT(PINSEL1,               0x4002C004,__READ_WRITE ,__pinsel1_bits);
__IO_REG32_BIT(PINSEL2,               0x4002C008,__READ_WRITE ,__pinsel2_bits);
__IO_REG32_BIT(PINSEL3,               0x4002C00C,__READ_WRITE ,__pinsel3_bits);
__IO_REG32_BIT(PINSEL4,               0x4002C010,__READ_WRITE ,__pinsel4_bits);
//__IO_REG32_BIT(PINSEL5,               0x4002C014,__READ_WRITE ,__pinsel5_bits);
//__IO_REG32_BIT(PINSEL6,               0x4002C018,__READ_WRITE ,__pinsel6_bits);
__IO_REG32_BIT(PINSEL7,               0x4002C01C,__READ_WRITE ,__pinsel7_bits);
__IO_REG32_BIT(PINSEL8,               0x4002C020,__READ_WRITE ,__pinsel8_bits);
__IO_REG32_BIT(PINSEL9,               0x4002C024,__READ_WRITE ,__pinsel9_bits);
__IO_REG32_BIT(PINSEL10,              0x4002C028,__READ_WRITE ,__pinsel10_bits);
__IO_REG32_BIT(PINMODE0,              0x4002C040,__READ_WRITE ,__pinsel0_bits);
__IO_REG32_BIT(PINMODE1,              0x4002C044,__READ_WRITE ,__pinsel1_bits);
__IO_REG32_BIT(PINMODE2,              0x4002C048,__READ_WRITE ,__pinsel2_bits);
__IO_REG32_BIT(PINMODE3,              0x4002C04C,__READ_WRITE ,__pinsel3_bits);
__IO_REG32_BIT(PINMODE4,              0x4002C050,__READ_WRITE ,__pinsel4_bits);
__IO_REG32_BIT(PINMODE5,              0x4002C054,__READ_WRITE ,__pinsel5_bits);
__IO_REG32_BIT(PINMODE6,              0x4002C058,__READ_WRITE ,__pinsel6_bits);
__IO_REG32_BIT(PINMODE7,              0x4002C05C,__READ_WRITE ,__pinsel7_bits);
__IO_REG32_BIT(PINMODE8,              0x4002C060,__READ_WRITE ,__pinsel8_bits);
__IO_REG32_BIT(PINMODE9,              0x4002C064,__READ_WRITE ,__pinsel9_bits);
__IO_REG32_BIT(PINMODE_OD0,           0x4002C068,__READ_WRITE ,__gpio0_bits);
__IO_REG32_BIT(PINMODE_OD1,           0x4002C06C,__READ_WRITE ,__gpio1_bits);
__IO_REG32_BIT(PINMODE_OD2,           0x4002C070,__READ_WRITE ,__gpio2_bits);
__IO_REG32_BIT(PINMODE_OD3,           0x4002C074,__READ_WRITE ,__gpio3_bits);
__IO_REG32_BIT(PINMODE_OD4,           0x4002C078,__READ_WRITE ,__gpio4_bits);
__IO_REG32_BIT(I2CPADCFG,             0x4002C07C,__READ_WRITE ,__i2cpadcfg_bits);

/***************************************************************************
 **
 ** GPIO
 **
 ***************************************************************************/
__IO_REG32_BIT(FIO0DIR,         0x2009C000,__READ_WRITE,__fgpio0_bits);
#define FIO0DIR0          FIO0DIR_bit.__byte0
#define FIO0DIR0_bit      FIO0DIR_bit.__byte0_bit
#define FIO0DIR1          FIO0DIR_bit.__byte1
#define FIO0DIR1_bit      FIO0DIR_bit.__byte1_bit
#define FIO0DIR2          FIO0DIR_bit.__byte2
#define FIO0DIR2_bit      FIO0DIR_bit.__byte2_bit
#define FIO0DIR3          FIO0DIR_bit.__byte3
#define FIO0DIR3_bit      FIO0DIR_bit.__byte3_bit
#define FIO0DIRL          FIO0DIR_bit.__shortl
#define FIO0DIRL_bit      FIO0DIR_bit.__shortl_bit
#define FIO0DIRU          FIO0DIR_bit.__shortu
#define FIO0DIRU_bit      FIO0DIR_bit.__shortu_bit
__IO_REG32_BIT(FIO0MASK,        0x2009C010,__READ_WRITE,__fgpio0_bits);
#define FIO0MASK0         FIO0MASK_bit.__byte0
#define FIO0MASK0_bit     FIO0MASK_bit.__byte0_bit
#define FIO0MASK1         FIO0MASK_bit.__byte1
#define FIO0MASK1_bit     FIO0MASK_bit.__byte1_bit
#define FIO0MASK2         FIO0MASK_bit.__byte2
#define FIO0MASK2_bit     FIO0MASK_bit.__byte2_bit
#define FIO0MASK3         FIO0MASK_bit.__byte3
#define FIO0MASK3_bit     FIO0MASK_bit.__byte3_bit
#define FIO0MASKL         FIO0MASK_bit.__shortl
#define FIO0MASKL_bit     FIO0MASK_bit.__shortl_bit
#define FIO0MASKU         FIO0MASK_bit.__shortu
#define FIO0MASKU_bit     FIO0MASK_bit.__shortu_bit
__IO_REG32_BIT(FIO0PIN,         0x2009C014,__READ_WRITE,__fgpio0_bits);
#define FIO0PIN0          FIO0PIN_bit.__byte0
#define FIO0PIN0_bit      FIO0PIN_bit.__byte0_bit
#define FIO0PIN1          FIO0PIN_bit.__byte1
#define FIO0PIN1_bit      FIO0PIN_bit.__byte1_bit
#define FIO0PIN2          FIO0PIN_bit.__byte2
#define FIO0PIN2_bit      FIO0PIN_bit.__byte2_bit
#define FIO0PIN3          FIO0PIN_bit.__byte3
#define FIO0PIN3_bit      FIO0PIN_bit.__byte3_bit
#define FIO0PINL          FIO0PIN_bit.__shortl
#define FIO0PINL_bit      FIO0PIN_bit.__shortl_bit
#define FIO0PINU          FIO0PIN_bit.__shortu
#define FIO0PINU_bit      FIO0PIN_bit.__shortu_bit
__IO_REG32_BIT(FIO0SET,         0x2009C018,__READ_WRITE,__fgpio0_bits);
#define FIO0SET0          FIO0SET_bit.__byte0
#define FIO0SET0_bit      FIO0SET_bit.__byte0_bit
#define FIO0SET1          FIO0SET_bit.__byte1
#define FIO0SET1_bit      FIO0SET_bit.__byte1_bit
#define FIO0SET2          FIO0SET_bit.__byte2
#define FIO0SET2_bit      FIO0SET_bit.__byte2_bit
#define FIO0SET3          FIO0SET_bit.__byte3
#define FIO0SET3_bit      FIO0SET_bit.__byte3_bit
#define FIO0SETL          FIO0SET_bit.__shortl
#define FIO0SETL_bit      FIO0SET_bit.__shortl_bit
#define FIO0SETU          FIO0SET_bit.__shortu
#define FIO0SETU_bit      FIO0SET_bit.__shortu_bit
__IO_REG32_BIT(FIO0CLR,         0x2009C01C,__WRITE     ,__fgpio0_bits);
#define FIO0CLR0          FIO0CLR_bit.__byte0
#define FIO0CLR0_bit      FIO0CLR_bit.__byte0_bit
#define FIO0CLR1          FIO0CLR_bit.__byte1
#define FIO0CLR1_bit      FIO0CLR_bit.__byte1_bit
#define FIO0CLR2          FIO0CLR_bit.__byte2
#define FIO0CLR2_bit      FIO0CLR_bit.__byte2_bit
#define FIO0CLR3          FIO0CLR_bit.__byte3
#define FIO0CLR3_bit      FIO0CLR_bit.__byte3_bit
#define FIO0CLRL          FIO0CLR_bit.__shortl
#define FIO0CLRL_bit      FIO0CLR_bit.__shortl_bit
#define FIO0CLRU          FIO0CLR_bit.__shortu
#define FIO0CLRU_bit      FIO0CLR_bit.__shortu_bit
__IO_REG32_BIT(FIO1DIR,         0x2009C020,__READ_WRITE,__fgpio1_bits);
#define FIO1DIR0          FIO1DIR_bit.__byte0
#define FIO1DIR0_bit      FIO1DIR_bit.__byte0_bit
#define FIO1DIR1          FIO1DIR_bit.__byte1
#define FIO1DIR1_bit      FIO1DIR_bit.__byte1_bit
#define FIO1DIR2          FIO1DIR_bit.__byte2
#define FIO1DIR2_bit      FIO1DIR_bit.__byte2_bit
#define FIO1DIR3          FIO1DIR_bit.__byte3
#define FIO1DIR3_bit      FIO1DIR_bit.__byte3_bit
#define FIO1DIRL          FIO1DIR_bit.__shortl
#define FIO1DIRL_bit      FIO1DIR_bit.__shortl_bit
#define FIO1DIRU          FIO1DIR_bit.__shortu
#define FIO1DIRU_bit      FIO1DIR_bit.__shortu_bit
__IO_REG32_BIT(FIO1MASK,        0x2009C030,__READ_WRITE,__fgpio1_bits);
#define FIO1MASK0         FIO1MASK_bit.__byte0
#define FIO1MASK0_bit     FIO1MASK_bit.__byte0_bit
#define FIO1MASK1         FIO1MASK_bit.__byte1
#define FIO1MASK1_bit     FIO1MASK_bit.__byte1_bit
#define FIO1MASK2         FIO1MASK_bit.__byte2
#define FIO1MASK2_bit     FIO1MASK_bit.__byte2_bit
#define FIO1MASK3         FIO1MASK_bit.__byte3
#define FIO1MASK3_bit     FIO1MASK_bit.__byte3_bit
#define FIO1MASKL         FIO1MASK_bit.__shortl
#define FIO1MASKL_bit     FIO1MASK_bit.__shortl_bit
#define FIO1MASKU         FIO1MASK_bit.__shortu
#define FIO1MASKU_bit     FIO1MASK_bit.__shortu_bit
__IO_REG32_BIT(FIO1PIN,         0x2009C034,__READ_WRITE,__fgpio1_bits);
#define FIO1PIN0          FIO1PIN_bit.__byte0
#define FIO1PIN0_bit      FIO1PIN_bit.__byte0_bit
#define FIO1PIN1          FIO1PIN_bit.__byte1
#define FIO1PIN1_bit      FIO1PIN_bit.__byte1_bit
#define FIO1PIN2          FIO1PIN_bit.__byte2
#define FIO1PIN2_bit      FIO1PIN_bit.__byte2_bit
#define FIO1PIN3          FIO1PIN_bit.__byte3
#define FIO1PIN3_bit      FIO1PIN_bit.__byte3_bit
#define FIO1PINL          FIO1PIN_bit.__shortl
#define FIO1PINL_bit      FIO1PIN_bit.__shortl_bit
#define FIO1PINU          FIO1PIN_bit.__shortu
#define FIO1PINU_bit      FIO1PIN_bit.__shortu_bit
__IO_REG32_BIT(FIO1SET,         0x2009C038,__READ_WRITE,__fgpio1_bits);
#define FIO1SET0          FIO1SET_bit.__byte0
#define FIO1SET0_bit      FIO1SET_bit.__byte0_bit
#define FIO1SET1          FIO1SET_bit.__byte1
#define FIO1SET1_bit      FIO1SET_bit.__byte1_bit
#define FIO1SET2          FIO1SET_bit.__byte2
#define FIO1SET2_bit      FIO1SET_bit.__byte2_bit
#define FIO1SET3          FIO1SET_bit.__byte3
#define FIO1SET3_bit      FIO1SET_bit.__byte3_bit
#define FIO1SETL          FIO1SET_bit.__shortl
#define FIO1SETL_bit      FIO1SET_bit.__shortl_bit
#define FIO1SETU          FIO1SET_bit.__shortu
#define FIO1SETU_bit      FIO1SET_bit.__shortu_bit
__IO_REG32_BIT(FIO1CLR,         0x2009C03C,__WRITE     ,__fgpio1_bits);
#define FIO1CLR0          FIO1CLR_bit.__byte0
#define FIO1CLR0_bit      FIO1CLR_bit.__byte0_bit
#define FIO1CLR1          FIO1CLR_bit.__byte1
#define FIO1CLR1_bit      FIO1CLR_bit.__byte1_bit
#define FIO1CLR2          FIO1CLR_bit.__byte2
#define FIO1CLR2_bit      FIO1CLR_bit.__byte2_bit
#define FIO1CLR3          FIO1CLR_bit.__byte3
#define FIO1CLR3_bit      FIO1CLR_bit.__byte3_bit
#define FIO1CLRL          FIO1CLR_bit.__shortl
#define FIO1CLRL_bit      FIO1CLR_bit.__shortl_bit
#define FIO1CLRU          FIO1CLR_bit.__shortu
#define FIO1CLRU_bit      FIO1CLR_bit.__shortu_bit
__IO_REG32_BIT(FIO2DIR,         0x2009C040,__READ_WRITE,__fgpio2_bits);
#define FIO2DIR0          FIO2DIR_bit.__byte0
#define FIO2DIR0_bit      FIO2DIR_bit.__byte0_bit
#define FIO2DIR1          FIO2DIR_bit.__byte1
#define FIO2DIR1_bit      FIO2DIR_bit.__byte1_bit
#define FIO2DIR2          FIO2DIR_bit.__byte2
#define FIO2DIR2_bit      FIO2DIR_bit.__byte2_bit
#define FIO2DIR3          FIO2DIR_bit.__byte3
#define FIO2DIR3_bit      FIO2DIR_bit.__byte3_bit
#define FIO2DIRL          FIO2DIR_bit.__shortl
#define FIO2DIRL_bit      FIO2DIR_bit.__shortl_bit
#define FIO2DIRU          FIO2DIR_bit.__shortu
#define FIO2DIRU_bit      FIO2DIR_bit.__shortu_bit
__IO_REG32_BIT(FIO2MASK,        0x2009C050,__READ_WRITE,__fgpio2_bits);
#define FIO2MASK0         FIO2MASK_bit.__byte0
#define FIO2MASK0_bit     FIO2MASK_bit.__byte0_bit
#define FIO2MASK1         FIO2MASK_bit.__byte1
#define FIO2MASK1_bit     FIO2MASK_bit.__byte1_bit
#define FIO2MASK2         FIO2MASK_bit.__byte2
#define FIO2MASK2_bit     FIO2MASK_bit.__byte2_bit
#define FIO2MASK3         FIO2MASK_bit.__byte3
#define FIO2MASK3_bit     FIO2MASK_bit.__byte3_bit
#define FIO2MASKL         FIO2MASK_bit.__shortl
#define FIO2MASKL_bit     FIO2MASK_bit.__shortl_bit
#define FIO2MASKU         FIO2MASK_bit.__shortu
#define FIO2MASKU_bit     FIO2MASK_bit.__shortu_bit
__IO_REG32_BIT(FIO2PIN,         0x2009C054,__READ_WRITE,__fgpio2_bits);
#define FIO2PIN0          FIO2PIN_bit.__byte0
#define FIO2PIN0_bit      FIO2PIN_bit.__byte0_bit
#define FIO2PIN1          FIO2PIN_bit.__byte1
#define FIO2PIN1_bit      FIO2PIN_bit.__byte1_bit
#define FIO2PIN2          FIO2PIN_bit.__byte2
#define FIO2PIN2_bit      FIO2PIN_bit.__byte2_bit
#define FIO2PIN3          FIO2PIN_bit.__byte3
#define FIO2PIN3_bit      FIO2PIN_bit.__byte3_bit
#define FIO2PINL          FIO2PIN_bit.__shortl
#define FIO2PINL_bit      FIO2PIN_bit.__shortl_bit
#define FIO2PINU          FIO2PIN_bit.__shortu
#define FIO2PINU_bit      FIO2PIN_bit.__shortu_bit
__IO_REG32_BIT(FIO2SET,         0x2009C058,__READ_WRITE,__fgpio2_bits);
#define FIO2SET0          FIO2SET_bit.__byte0
#define FIO2SET0_bit      FIO2SET_bit.__byte0_bit
#define FIO2SET1          FIO2SET_bit.__byte1
#define FIO2SET1_bit      FIO2SET_bit.__byte1_bit
#define FIO2SET2          FIO2SET_bit.__byte2
#define FIO2SET2_bit      FIO2SET_bit.__byte2_bit
#define FIO2SET3          FIO2SET_bit.__byte3
#define FIO2SET3_bit      FIO2SET_bit.__byte3_bit
#define FIO2SETL          FIO2SET_bit.__shortl
#define FIO2SETL_bit      FIO2SET_bit.__shortl_bit
#define FIO2SETU          FIO2SET_bit.__shortu
#define FIO2SETU_bit      FIO2SET_bit.__shortu_bit
__IO_REG32_BIT(FIO2CLR,         0x2009C05C,__WRITE     ,__fgpio2_bits);
#define FIO2CLR0          FIO2CLR_bit.__byte0
#define FIO2CLR0_bit      FIO2CLR_bit.__byte0_bit
#define FIO2CLR1          FIO2CLR_bit.__byte1
#define FIO2CLR1_bit      FIO2CLR_bit.__byte1_bit
#define FIO2CLR2          FIO2CLR_bit.__byte2
#define FIO2CLR2_bit      FIO2CLR_bit.__byte2_bit
#define FIO2CLR3          FIO2CLR_bit.__byte3
#define FIO2CLR3_bit      FIO2CLR_bit.__byte3_bit
#define FIO2CLRL          FIO2CLR_bit.__shortl
#define FIO2CLRL_bit      FIO2CLR_bit.__shortl_bit
#define FIO2CLRU          FIO2CLR_bit.__shortu
#define FIO2CLRU_bit      FIO2CLR_bit.__shortu_bit
__IO_REG32_BIT(FIO3DIR,         0x2009C060,__READ_WRITE,__fgpio3_bits);
#define FIO3DIR0          FIO3DIR_bit.__byte0
#define FIO3DIR0_bit      FIO3DIR_bit.__byte0_bit
#define FIO3DIR1          FIO3DIR_bit.__byte1
#define FIO3DIR1_bit      FIO3DIR_bit.__byte1_bit
#define FIO3DIR2          FIO3DIR_bit.__byte2
#define FIO3DIR2_bit      FIO3DIR_bit.__byte2_bit
#define FIO3DIR3          FIO3DIR_bit.__byte3
#define FIO3DIR3_bit      FIO3DIR_bit.__byte3_bit
#define FIO3DIRL          FIO3DIR_bit.__shortl
#define FIO3DIRL_bit      FIO3DIR_bit.__shortl_bit
#define FIO3DIRU          FIO3DIR_bit.__shortu
#define FIO3DIRU_bit      FIO3DIR_bit.__shortu_bit
__IO_REG32_BIT(FIO3MASK,        0x2009C070,__READ_WRITE,__fgpio3_bits);
#define FIO3MASK0         FIO3MASK_bit.__byte0
#define FIO3MASK0_bit     FIO3MASK_bit.__byte0_bit
#define FIO3MASK1         FIO3MASK_bit.__byte1
#define FIO3MASK1_bit     FIO3MASK_bit.__byte1_bit
#define FIO3MASK2         FIO3MASK_bit.__byte2
#define FIO3MASK2_bit     FIO3MASK_bit.__byte2_bit
#define FIO3MASK3         FIO3MASK_bit.__byte3
#define FIO3MASK3_bit     FIO3MASK_bit.__byte3_bit
#define FIO3MASKL         FIO3MASK_bit.__shortl
#define FIO3MASKL_bit     FIO3MASK_bit.__shortl_bit
#define FIO3MASKU         FIO3MASK_bit.__shortu
#define FIO3MASKU_bit     FIO3MASK_bit.__shortu_bit
__IO_REG32_BIT(FIO3PIN,         0x2009C074,__READ_WRITE,__fgpio3_bits);
#define FIO3PIN0          FIO3PIN_bit.__byte0
#define FIO3PIN0_bit      FIO3PIN_bit.__byte0_bit
#define FIO3PIN1          FIO3PIN_bit.__byte1
#define FIO3PIN1_bit      FIO3PIN_bit.__byte1_bit
#define FIO3PIN2          FIO3PIN_bit.__byte2
#define FIO3PIN2_bit      FIO3PIN_bit.__byte2_bit
#define FIO3PIN3          FIO3PIN_bit.__byte3
#define FIO3PIN3_bit      FIO3PIN_bit.__byte3_bit
#define FIO3PINL          FIO3PIN_bit.__shortl
#define FIO3PINL_bit      FIO3PIN_bit.__shortl_bit
#define FIO3PINU          FIO3PIN_bit.__shortu
#define FIO3PINU_bit      FIO3PIN_bit.__shortu_bit
__IO_REG32_BIT(FIO3SET,         0x2009C078,__READ_WRITE,__fgpio3_bits);
#define FIO3SET0          FIO3SET_bit.__byte0
#define FIO3SET0_bit      FIO3SET_bit.__byte0_bit
#define FIO3SET1          FIO3SET_bit.__byte1
#define FIO3SET1_bit      FIO3SET_bit.__byte1_bit
#define FIO3SET2          FIO3SET_bit.__byte2
#define FIO3SET2_bit      FIO3SET_bit.__byte2_bit
#define FIO3SET3          FIO3SET_bit.__byte3
#define FIO3SET3_bit      FIO3SET_bit.__byte3_bit
#define FIO3SETL          FIO3SET_bit.__shortl
#define FIO3SETL_bit      FIO3SET_bit.__shortl_bit
#define FIO3SETU          FIO3SET_bit.__shortu
#define FIO3SETU_bit      FIO3SET_bit.__shortu_bit
__IO_REG32_BIT(FIO3CLR,         0x2009C07C,__WRITE     ,__fgpio3_bits);
#define FIO3CLR0          FIO3CLR_bit.__byte0
#define FIO3CLR0_bit      FIO3CLR_bit.__byte0_bit
#define FIO3CLR1          FIO3CLR_bit.__byte1
#define FIO3CLR1_bit      FIO3CLR_bit.__byte1_bit
#define FIO3CLR2          FIO3CLR_bit.__byte2
#define FIO3CLR2_bit      FIO3CLR_bit.__byte2_bit
#define FIO3CLR3          FIO3CLR_bit.__byte3
#define FIO3CLR3_bit      FIO3CLR_bit.__byte3_bit
#define FIO3CLRL          FIO3CLR_bit.__shortl
#define FIO3CLRL_bit      FIO3CLR_bit.__shortl_bit
#define FIO3CLRU          FIO3CLR_bit.__shortu
#define FIO3CLRU_bit      FIO3CLR_bit.__shortu_bit
__IO_REG32_BIT(FIO4DIR,         0x2009C080,__READ_WRITE,__fgpio4_bits);
#define FIO4DIR0          FIO4DIR_bit.__byte0
#define FIO4DIR0_bit      FIO4DIR_bit.__byte0_bit
#define FIO4DIR1          FIO4DIR_bit.__byte1
#define FIO4DIR1_bit      FIO4DIR_bit.__byte1_bit
#define FIO4DIR2          FIO4DIR_bit.__byte2
#define FIO4DIR2_bit      FIO4DIR_bit.__byte2_bit
#define FIO4DIR3          FIO4DIR_bit.__byte3
#define FIO4DIR3_bit      FIO4DIR_bit.__byte3_bit
#define FIO4DIRL          FIO4DIR_bit.__shortl
#define FIO4DIRL_bit      FIO4DIR_bit.__shortl_bit
#define FIO4DIRU          FIO4DIR_bit.__shortu
#define FIO4DIRU_bit      FIO4DIR_bit.__shortu_bit
__IO_REG32_BIT(FIO4MASK,        0x2009C090,__READ_WRITE,__fgpio4_bits);
#define FIO4MASK0         FIO4MASK_bit.__byte0
#define FIO4MASK0_bit     FIO4MASK_bit.__byte0_bit
#define FIO4MASK1         FIO4MASK_bit.__byte1
#define FIO4MASK1_bit     FIO4MASK_bit.__byte1_bit
#define FIO4MASK2         FIO4MASK_bit.__byte2
#define FIO4MASK2_bit     FIO4MASK_bit.__byte2_bit
#define FIO4MASK3         FIO4MASK_bit.__byte3
#define FIO4MASK3_bit     FIO4MASK_bit.__byte3_bit
#define FIO4MASKL         FIO4MASK_bit.__shortl
#define FIO4MASKL_bit     FIO4MASK_bit.__shortl_bit
#define FIO4MASKU         FIO4MASK_bit.__shortu
#define FIO4MASKU_bit     FIO4MASK_bit.__shortu_bit
__IO_REG32_BIT(FIO4PIN,         0x2009C094,__READ_WRITE,__fgpio4_bits);
#define FIO4PIN0          FIO4PIN_bit.__byte0
#define FIO4PIN0_bit      FIO4PIN_bit.__byte0_bit
#define FIO4PIN1          FIO4PIN_bit.__byte1
#define FIO4PIN1_bit      FIO4PIN_bit.__byte1_bit
#define FIO4PIN2          FIO4PIN_bit.__byte2
#define FIO4PIN2_bit      FIO4PIN_bit.__byte2_bit
#define FIO4PIN3          FIO4PIN_bit.__byte3
#define FIO4PIN3_bit      FIO4PIN_bit.__byte3_bit
#define FIO4PINL          FIO4PIN_bit.__shortl
#define FIO4PINL_bit      FIO4PIN_bit.__shortl_bit
#define FIO4PINU          FIO4PIN_bit.__shortu
#define FIO4PINU_bit      FIO4PIN_bit.__shortu_bit
__IO_REG32_BIT(FIO4SET,         0x2009C098,__READ_WRITE,__fgpio4_bits);
#define FIO4SET0          FIO4SET_bit.__byte0
#define FIO4SET0_bit      FIO4SET_bit.__byte0_bit
#define FIO4SET1          FIO4SET_bit.__byte1
#define FIO4SET1_bit      FIO4SET_bit.__byte1_bit
#define FIO4SET2          FIO4SET_bit.__byte2
#define FIO4SET2_bit      FIO4SET_bit.__byte2_bit
#define FIO4SET3          FIO4SET_bit.__byte3
#define FIO4SET3_bit      FIO4SET_bit.__byte3_bit
#define FIO4SETL          FIO4SET_bit.__shortl
#define FIO4SETL_bit      FIO4SET_bit.__shortl_bit
#define FIO4SETU          FIO4SET_bit.__shortu
#define FIO4SETU_bit      FIO4SET_bit.__shortu_bit
__IO_REG32_BIT(FIO4CLR,         0x2009C09C,__WRITE     ,__fgpio4_bits);
#define FIO4CLR0          FIO4CLR_bit.__byte0
#define FIO4CLR0_bit      FIO4CLR_bit.__byte0_bit
#define FIO4CLR1          FIO4CLR_bit.__byte1
#define FIO4CLR1_bit      FIO4CLR_bit.__byte1_bit
#define FIO4CLR2          FIO4CLR_bit.__byte2
#define FIO4CLR2_bit      FIO4CLR_bit.__byte2_bit
#define FIO4CLR3          FIO4CLR_bit.__byte3
#define FIO4CLR3_bit      FIO4CLR_bit.__byte3_bit
#define FIO4CLRL          FIO4CLR_bit.__shortl
#define FIO4CLRL_bit      FIO4CLR_bit.__shortl_bit
#define FIO4CLRU          FIO4CLR_bit.__shortu
#define FIO4CLRU_bit      FIO4CLR_bit.__shortu_bit
__IO_REG32_BIT(IO0INTENR,             0x40028090,__READ_WRITE ,__gpio0_bits);
__IO_REG32_BIT(IO0INTENF,             0x40028094,__READ_WRITE ,__gpio0_bits);
__IO_REG32_BIT(IO0INTSTATR,           0x40028084,__READ       ,__gpio0_bits);
__IO_REG32_BIT(IO0INTSTATF,           0x40028088,__READ       ,__gpio0_bits);
__IO_REG32_BIT(IO0INTCLR,             0x4002808C,__WRITE      ,__gpio0_bits);
__IO_REG32_BIT(IO2INTENR,             0x400280B0,__READ_WRITE ,__gpio2_bits);
__IO_REG32_BIT(IO2INTENF,             0x400280B4,__READ_WRITE ,__gpio2_bits);
__IO_REG32_BIT(IO2INTSTATR,           0x400280A4,__READ       ,__gpio2_bits);
__IO_REG32_BIT(IO2INTSTATF,           0x400280A8,__READ       ,__gpio2_bits);
__IO_REG32_BIT(IO2INTCLR,             0x400280AC,__WRITE      ,__gpio2_bits);
__IO_REG32_BIT(IOINTSTATUS,           0x40028080,__READ       ,__iointst_bits);

/***************************************************************************
 **
 **  ETHERNET
 **
 ***************************************************************************/
__IO_REG32_BIT(MAC1,                  0x50000000,__READ_WRITE ,__mac1_bits);
__IO_REG32_BIT(MAC2,                  0x50000004,__READ_WRITE ,__mac2_bits);
__IO_REG32_BIT(IPGT,                  0x50000008,__READ_WRITE ,__ipgt_bits);
__IO_REG32_BIT(IPGR,                  0x5000000C,__READ_WRITE ,__ipgr_bits);
__IO_REG32_BIT(CLRT,                  0x50000010,__READ_WRITE ,__clrt_bits);
__IO_REG32_BIT(MAXF,                  0x50000014,__READ_WRITE ,__maxf_bits);
__IO_REG32_BIT(SUPP,                  0x50000018,__READ_WRITE ,__supp_bits);
__IO_REG32_BIT(TEST,                  0x5000001C,__READ_WRITE ,__test_bits);
__IO_REG32_BIT(MCFG,                  0x50000020,__READ_WRITE ,__mcfg_bits);
__IO_REG32_BIT(MCMD,                  0x50000024,__READ_WRITE ,__mcmd_bits);
__IO_REG32_BIT(MADR,                  0x50000028,__READ_WRITE ,__madr_bits);
__IO_REG32_BIT(MWTD,                  0x5000002C,__WRITE      ,__mwtd_bits);
__IO_REG32_BIT(MRDD,                  0x50000030,__READ       ,__mrdd_bits);
__IO_REG32_BIT(MIND,                  0x50000034,__READ       ,__mind_bits);
__IO_REG32_BIT(SA0,                   0x50000040,__READ_WRITE ,__sa0_bits);
__IO_REG32_BIT(SA1,                   0x50000044,__READ_WRITE ,__sa1_bits);
__IO_REG32_BIT(SA2,                   0x50000048,__READ_WRITE ,__sa2_bits);
__IO_REG32_BIT(COMMAND,               0x50000100,__READ_WRITE ,__command_bits);
__IO_REG32_BIT(STATUS,                0x50000104,__READ       ,__status_bits);
__IO_REG32(    RXDESCRIPTOR,          0x50000108,__READ_WRITE );
__IO_REG32(    RXSTATUS,              0x5000010C,__READ_WRITE );
__IO_REG32_BIT(RXDESCRIPTORNUMBER,    0x50000110,__READ_WRITE ,__rxdescrn_bits);
__IO_REG32_BIT(RXPRODUCEINDEX,        0x50000114,__READ       ,__rxprodind_bits);
__IO_REG32_BIT(RXCONSUMEINDEX,        0x50000118,__READ_WRITE ,__rxcomind_bits);
__IO_REG32(    TXDESCRIPTOR,          0x5000011C,__READ_WRITE );
__IO_REG32(    TXSTATUS,              0x50000120,__READ_WRITE );
__IO_REG32_BIT(TXDESCRIPTORNUMBER,    0x50000124,__READ_WRITE ,__txdescrn_bits);
__IO_REG32_BIT(TXPRODUCEINDEX,        0x50000128,__READ_WRITE ,__txprodind_bits);
__IO_REG32_BIT(TXCONSUMEINDEX,        0x5000012C,__READ       ,__txcomind_bits);
__IO_REG32_BIT(TSV0,                  0x50000158,__READ       ,__tsv0_bits);
__IO_REG32_BIT(TSV1,                  0x5000015C,__READ       ,__tsv1_bits);
__IO_REG32_BIT(RSV,                   0x50000160,__READ       ,__rsv_bits);
__IO_REG32_BIT(FLOWCONTROLCOUNTER,    0x50000170,__READ_WRITE ,__fwctrlcnt_bits);
__IO_REG32_BIT(FLOWCONTROLSTATUS,     0x50000174,__READ       ,__fwctrlstat_bits);
__IO_REG32_BIT(RXFILTERCTRL,          0x50000200,__READ_WRITE ,__rxflctrl_bits);
__IO_REG32_BIT(RXFILTERWOLSTATUS,     0x50000204,__READ_WRITE ,__rxflwolstat_bits);
__IO_REG32_BIT(RXFILTERWOLCLEAR,      0x50000208,__READ_WRITE ,__rxflwolclr_bits);
__IO_REG32(    HASHFILTERL,           0x50000210,__READ_WRITE );
__IO_REG32(    HASHFILTERH,           0x50000214,__READ_WRITE );
__IO_REG32_BIT(INTSTATUS,             0x50000FE0,__READ       ,__intstat_bits);
__IO_REG32_BIT(INTENABLE,             0x50000FE4,__READ_WRITE ,__intena_bits);
__IO_REG32_BIT(INTCLEAR,              0x50000FE8,__WRITE      ,__intclr_bits);
__IO_REG32_BIT(INTSET,                0x50000FEC,__WRITE      ,__intset_bits);
__IO_REG32_BIT(POWERDOWN,             0x50000FF4,__READ_WRITE ,__pwrdn_bits);

/***************************************************************************
 **
 ** USB
 **
 ***************************************************************************/
__IO_REG32_BIT(USBCLKCTRL,            0x5000CFF4,__READ_WRITE ,__usbclkctrl_bits);
__IO_REG32_BIT(USBCLKST,              0x5000CFF8,__READ       ,__usbclkst_bits);
__IO_REG32_BIT(USBINTS,               0x400FC1C0,__READ_WRITE ,__usbints_bits);
__IO_REG32_BIT(USBDEVINTST,           0x5000C200,__READ       ,__usbdevintst_bits);
__IO_REG32_BIT(USBDEVINTEN,           0x5000C204,__READ_WRITE ,__usbdevintst_bits);
__IO_REG32_BIT(USBDEVINTCLR,          0x5000C208,__WRITE      ,__usbdevintst_bits);
__IO_REG32_BIT(USBDEVINTSET,          0x5000C20C,__WRITE      ,__usbdevintst_bits);
__IO_REG8_BIT( USBDEVINTPRI,          0x5000C22C,__WRITE      ,__usbdevintpri_bits);
__IO_REG32_BIT(USBEPINTST,            0x5000C230,__READ       ,__usbepintst_bits);
__IO_REG32_BIT(USBEPINTEN,            0x5000C234,__READ_WRITE ,__usbepintst_bits);
__IO_REG32_BIT(USBEPINTCLR,           0x5000C238,__WRITE      ,__usbepintst_bits);
__IO_REG32_BIT(USBEPINTSET,           0x5000C23C,__WRITE      ,__usbepintst_bits);
__IO_REG32_BIT(USBEPINTPRI,           0x5000C240,__WRITE      ,__usbepintst_bits);
__IO_REG32_BIT(USBREEP,               0x5000C244,__READ_WRITE ,__usbreep_bits);
__IO_REG32_BIT(USBEPIN,               0x5000C248,__WRITE      ,__usbepin_bits);
__IO_REG32_BIT(USBMAXPSIZE,           0x5000C24C,__READ_WRITE ,__usbmaxpsize_bits);
__IO_REG32(    USBRXDATA,             0x5000C218,__READ);
__IO_REG32_BIT(USBRXPLEN,             0x5000C220,__READ       ,__usbrxplen_bits);
__IO_REG32(    TDATA,                 0x5000C21C,__WRITE);
__IO_REG32_BIT(USBTXPLEN,             0x5000C224,__WRITE      ,__usbtxplen_bits);
__IO_REG32_BIT(USBCTRL,               0x5000C228,__READ_WRITE ,__usbctrl_bits);
__IO_REG32_BIT(USBCMDCODE,            0x5000C210,__WRITE      ,__usbcmdcode_bits);
__IO_REG32_BIT(USBCMDDATA,            0x5000C214,__READ       ,__usbcmddata_bits);
__IO_REG32_BIT(USBDMARST,             0x5000C250,__READ       ,__usbreep_bits);
__IO_REG32_BIT(USBDMARCLR,            0x5000C254,__WRITE      ,__usbreep_bits);
__IO_REG32_BIT(USBDMARSET,            0x5000C258,__WRITE      ,__usbreep_bits);
__IO_REG32(    USBUDCAH,              0x5000C280,__READ_WRITE );
__IO_REG32_BIT(USBEPDMAST,            0x5000C284,__READ       ,__usbreep_bits);
__IO_REG32_BIT(USBEPDMAEN,            0x5000C288,__WRITE      ,__usbreep_bits);
__IO_REG32_BIT(USBEPDMADIS,           0x5000C28C,__WRITE      ,__usbreep_bits);
__IO_REG32_BIT(USBDMAINTST,           0x5000C290,__READ       ,__usbdmaintst_bits);
__IO_REG32_BIT(USBDMAINTEN,           0x5000C294,__READ_WRITE ,__usbdmaintst_bits);
__IO_REG32_BIT(USBEOTINTST,           0x5000C2A0,__READ       ,__usbreep_bits);
__IO_REG32_BIT(USBEOTINTCLR,          0x5000C2A4,__WRITE      ,__usbreep_bits);
__IO_REG32_BIT(USBEOTINTSET,          0x5000C2A8,__WRITE      ,__usbreep_bits);
__IO_REG32_BIT(USBNDDRINTST,          0x5000C2AC,__READ       ,__usbreep_bits);
__IO_REG32_BIT(USBNDDRINTCLR,         0x5000C2B0,__WRITE      ,__usbreep_bits);
__IO_REG32_BIT(USBNDDRINTSET,         0x5000C2B4,__WRITE      ,__usbreep_bits);
__IO_REG32_BIT(USBSYSERRINTST,        0x5000C2B8,__READ       ,__usbreep_bits);
__IO_REG32_BIT(USBSYSERRINTCLR,       0x5000C2BC,__WRITE      ,__usbreep_bits);
__IO_REG32_BIT(USBSYSERRINTSET,       0x5000C2C0,__WRITE      ,__usbreep_bits);

/***************************************************************************
 **
 ** USB HOST (OHCI) CONTROLLER
 **
 ***************************************************************************/
__IO_REG32_BIT(HCREVISION,            0x5000C000,__READ       ,__hcrevision_bits);
__IO_REG32_BIT(HCCONTROL,             0x5000C004,__READ_WRITE ,__hccontrol_bits);
__IO_REG32_BIT(HCCOMMANDSTATUS,       0x5000C008,__READ_WRITE ,__hccommandstatus_bits);
__IO_REG32_BIT(HCINTERRUPTSTATUS,     0x5000C00C,__READ_WRITE ,__hcinterruptstatus_bits);
__IO_REG32_BIT(HCINTERRUPTENABLE,     0x5000C010,__READ_WRITE ,__hcinterruptenable_bits);
__IO_REG32_BIT(HCINTERRUPTDISABLE,    0x5000C014,__READ_WRITE ,__hcinterruptenable_bits);
__IO_REG32_BIT(HCHCCA,                0x5000C018,__READ_WRITE ,__hchcca_bits);
__IO_REG32_BIT(HCPERIODCURRENTED,     0x5000C01C,__READ       ,__hcperiodcurrented_bits);
__IO_REG32_BIT(HCCONTROLHEADED,       0x5000C020,__READ_WRITE ,__hccontrolheaded_bits);
__IO_REG32_BIT(HCCONTROLCURRENTED,    0x5000C024,__READ_WRITE ,__hccontrolcurrented_bits);
__IO_REG32_BIT(HCBULKHEADED,          0x5000C028,__READ_WRITE ,__hcbulkheaded_bits);
__IO_REG32_BIT(HCBULKCURRENTED,       0x5000C02C,__READ_WRITE ,__hcbulkcurrented_bits);
__IO_REG32_BIT(HCDONEHEAD,            0x5000C030,__READ       ,__hcdonehead_bits);
__IO_REG32_BIT(HCFMINTERVAL,          0x5000C034,__READ_WRITE ,__hcfminterval_bits);
__IO_REG32_BIT(HCFMREMAINING,         0x5000C038,__READ       ,__hcfmremaining_bits);
__IO_REG32_BIT(HCFMNUMBER,            0x5000C03C,__READ       ,__hcfmnumber_bits);
__IO_REG32_BIT(HCPERIODICSTART,       0x5000C040,__READ_WRITE ,__hcperiodicstart_bits);
__IO_REG32_BIT(HCLSTHRESHOLD,         0x5000C044,__READ_WRITE ,__hclsthreshold_bits);
__IO_REG32_BIT(HCRHDESCRIPTORA,       0x5000C048,__READ_WRITE ,__hcrhdescriptora_bits);
__IO_REG32_BIT(HCRHDESCRIPTORB,       0x5000C04C,__READ_WRITE ,__hcrhdescriptorb_bits);
__IO_REG32_BIT(HCRHSTATUS,            0x5000C050,__READ_WRITE ,__hcrhstatus_bits);
__IO_REG32_BIT(HCRHPORTSTATUS1,       0x5000C054,__READ_WRITE ,__hcrhportstatus_bits);
__IO_REG32_BIT(HCRHPORTSTATUS2,       0x5000C058,__READ_WRITE ,__hcrhportstatus_bits);
__IO_REG32(    HCRMID,                0x5000C0FC,__READ);

/***************************************************************************
 **
 ** USB OTG Controller
 **
 ***************************************************************************/
__IO_REG32_BIT(OTGINTST,              0x5000C100,__READ       ,__otgintst_bits);
__IO_REG32_BIT(OTGINTEN,              0x5000C104,__READ_WRITE ,__otgintst_bits);
__IO_REG32_BIT(OTGINTSET,             0x5000C108,__WRITE      ,__otgintst_bits);
__IO_REG32_BIT(OTGINTCLR,             0x5000C10C,__WRITE      ,__otgintst_bits);
__IO_REG32_BIT(OTGSTCTRL,             0x5000C110,__READ_WRITE ,__otgstctrl_bits);
__IO_REG32_BIT(OTGTMR,                0x5000C114,__READ_WRITE ,__otgtmr_bits);
__IO_REG32_BIT(I2C_RX,                0x5000C300,__READ_WRITE ,__otg_i2c_rx_tx_bits);
#define I2C_TX      I2C_RX
#define I2C_TX_bit  I2C_RX_bit
__IO_REG32_BIT(I2C_STS,               0x5000C304,__READ_WRITE ,__otg_i2c_sts_bits);
__IO_REG32_BIT(I2C_CTL,               0x5000C308,__READ_WRITE ,__otg_i2c_ctl_bits);
__IO_REG32_BIT(I2C_CLKHI,             0x5000C30C,__READ_WRITE ,__i2c_clkhi_bits);
__IO_REG32_BIT(I2C_CLKLO,             0x5000C310,__READ_WRITE ,__i2c_clklo_bits);
#define OTGCLKCTRL        USBCLKCTRL
#define OTGCLKCTRL_bit    USBCLKCTRL_bit
#define OTGCLKST          USBCLKST
#define OTGCLKST_bit      USBCLKST_bit

/***************************************************************************
 **
 **  UART0
 **
 ***************************************************************************/
/* U0DLL, U0RBR and U0THR share the same address */
__IO_REG8(     U0RBRTHR,              0x4000C000,__READ_WRITE);
#define U0DLL U0RBRTHR
#define U0RBR U0RBRTHR
#define U0THR U0RBRTHR

/* U0DLM and U0IER share the same address */
__IO_REG32_BIT(U0IER,                 0x4000C004,__READ_WRITE ,__uartier0_bits);
#define U0DLM      U0IER

/* U0FCR and U0IIR share the same address */
__IO_REG32_BIT(U0FCR,                 0x4000C008,__READ_WRITE ,__uartfcriir_bits);
#define U0IIR      U0FCR
#define U0IIR_bit  U0FCR_bit

__IO_REG8_BIT( U0LCR,                 0x4000C00C,__READ_WRITE ,__uartlcr_bits);
__IO_REG8_BIT( U0LSR,                 0x4000C014,__READ       ,__uartlsr_bits);
__IO_REG8(     U0SCR,                 0x4000C01C,__READ_WRITE);
__IO_REG32_BIT(U0ACR,                 0x4000C020,__READ_WRITE ,__uartacr_bits);
__IO_REG32_BIT(U0FDR,                 0x4000C028,__READ_WRITE ,__uartfdr_bits);
__IO_REG8_BIT( U0TER,                 0x4000C030,__READ_WRITE ,__uartter_bits);
__IO_REG32_BIT(U0FIFOLVL,             0x4000C058,__READ       ,__uartfifolvl_bits);

/***************************************************************************
 **
 **  UART1
 **
 ***************************************************************************/
/* U1DLL, U1RBR and U1THR share the same address */
__IO_REG8(     U1RBRTHR,              0x40010000,__READ_WRITE);
#define U1DLL U1RBRTHR
#define U1RBR U1RBRTHR
#define U1THR U1RBRTHR

/* U1DLM and U1IER share the same address */
__IO_REG32_BIT(U1IER,                 0x40010004,__READ_WRITE ,__uartier1_bits);
#define U1DLM      U1IER

/* U1FCR and U1IIR share the same address */
__IO_REG32_BIT(U1FCR,                 0x40010008,__READ_WRITE ,__uartfcriir_bits);
#define U1IIR      U1FCR
#define U1IIR_bit  U1FCR_bit

__IO_REG8_BIT( U1LCR,                 0x4001000C,__READ_WRITE ,__uartlcr_bits);
__IO_REG8_BIT( U1MCR,                 0x40010010,__READ_WRITE ,__uartmcr_bits);
__IO_REG8_BIT( U1LSR,                 0x40010014,__READ       ,__uartlsr_bits);
__IO_REG8_BIT( U1MSR,                 0x40010018,__READ       ,__uartmsr_bits);
__IO_REG8(     U1SCR,                 0x4001001C,__READ_WRITE);
__IO_REG32_BIT(U1ACR,                 0x40010020,__READ_WRITE ,__uartacr_bits);
__IO_REG32_BIT(U1FDR,                 0x40010028,__READ_WRITE ,__uartfdr_bits);
__IO_REG8_BIT( U1TER,                 0x40010030,__READ_WRITE ,__uartter_bits);
__IO_REG32_BIT(U1RS485CTRL,           0x4001004C,__READ_WRITE ,__u1rs485ctrl_bits);
__IO_REG8(     U1ADRMATCH,            0x40010050,__READ_WRITE );
__IO_REG8(     U1RS485DLY,            0x40010054,__READ_WRITE );
__IO_REG32_BIT(U1FIFOLVL,             0x40010058,__READ       ,__uartfifolvl_bits);

/***************************************************************************
 **
 **  UART2
 **
 ***************************************************************************/
/* U2DLL, U2RBR and U2THR share the same address */
__IO_REG8(     U2RBRTHR,              0x40098000,__READ_WRITE);
#define U2DLL U2RBRTHR
#define U2RBR U2RBRTHR
#define U2THR U2RBRTHR

/* U2DLM and U2IER share the same address */
__IO_REG32_BIT(U2IER,                 0x40098004,__READ_WRITE ,__uartier0_bits);
#define U2DLM      U2IER

/* U2FCR and U2IIR share the same address */
__IO_REG32_BIT(U2FCR,                 0x40098008,__READ_WRITE ,__uartfcriir_bits);
#define U2IIR      U2FCR
#define U2IIR_bit  U2FCR_bit

__IO_REG8_BIT( U2LCR,                 0x4009800C,__READ_WRITE ,__uartlcr_bits);
__IO_REG8_BIT( U2LSR,                 0x40098014,__READ       ,__uartlsr_bits);
__IO_REG8(     U2SCR,                 0x4009801C,__READ_WRITE);
__IO_REG32_BIT(U2ACR,                 0x40098020,__READ_WRITE ,__uartacr_bits);
__IO_REG32_BIT(U2FDR,                 0x40098028,__READ_WRITE ,__uartfdr_bits);
__IO_REG8_BIT( U2TER,                 0x40098030,__READ_WRITE ,__uartter_bits);
__IO_REG32_BIT(U2FIFOLVL,             0x40098058,__READ       ,__uartfifolvl_bits);

/***************************************************************************
 **
 **  UART3
 **
 ***************************************************************************/
/* U3DLL, U3RBR and U3THR share the same address */
__IO_REG8(     U3RBRTHR,              0x4009C000,__READ_WRITE);
#define U3DLL U3RBRTHR
#define U3RBR U3RBRTHR
#define U3THR U3RBRTHR

/* U3DLM and U3IER share the same address */
__IO_REG32_BIT(U3IER,                 0x4009C004,__READ_WRITE ,__uartier0_bits);
#define U3DLM      U3IER

/* U3FCR and U3IIR share the same address */
__IO_REG32_BIT(U3FCR,                 0x4009C008,__READ_WRITE ,__uartfcriir_bits);
#define U3IIR      U3FCR
#define U3IIR_bit  U3FCR_bit

__IO_REG8_BIT( U3LCR,                 0x4009C00C,__READ_WRITE ,__uartlcr_bits);
__IO_REG8_BIT( U3LSR,                 0x4009C014,__READ       ,__uartlsr_bits);
__IO_REG8(     U3SCR,                 0x4009C01C,__READ_WRITE);
__IO_REG32_BIT(U3ACR,                 0x4009C020,__READ_WRITE ,__uartacr_bits);
__IO_REG32_BIT(U3ICR,                 0x4009C024,__READ_WRITE ,__uarticr_bits);
__IO_REG32_BIT(U3FDR,                 0x4009C028,__READ_WRITE ,__uartfdr_bits);
__IO_REG8_BIT( U3TER,                 0x4009C030,__READ_WRITE ,__uartter_bits);
__IO_REG32_BIT(U3FIFOLVL,             0x4009C058,__READ       ,__uartfifolvl_bits);

/***************************************************************************
 **
 ** CAN
 **
 ***************************************************************************/
__IO_REG32_BIT(AFMR,                  0x4003C000,__READ_WRITE ,__afmr_bits);
__IO_REG32(    SFF_SA,                0x4003C004,__READ_WRITE);
__IO_REG32(    SFF_GRP_SA,            0x4003C008,__READ_WRITE);
__IO_REG32(    EFF_SA,                0x4003C00C,__READ_WRITE);
__IO_REG32(    EFF_GRP_SA,            0x4003C010,__READ_WRITE);
__IO_REG32(    ENDOFTABLE,            0x4003C014,__READ_WRITE);
__IO_REG32(    LUTERRAD,              0x4003C018,__READ);
__IO_REG32_BIT(LUTERR,                0x4003C01C,__READ       ,__luterr_bits);
__IO_REG32_BIT(FCANIE,                0x4003C020,__READ_WRITE ,__fcanie_bits);
__IO_REG32_BIT(FCANIC0,               0x4003C024,__READ_WRITE ,__fcanic0_bits);
__IO_REG32_BIT(FCANIC1,               0x4003C028,__READ_WRITE ,__fcanic1_bits);
__IO_REG32_BIT(CANTXSR,               0x40040000,__READ       ,__cantxsr_bits);
__IO_REG32_BIT(CANRXSR,               0x40040004,__READ       ,__canrxsr_bits);
__IO_REG32_BIT(CANMSR,                0x40040008,__READ       ,__canmsr_bits);
__IO_REG32_BIT(CAN1MOD,               0x40044000,__READ_WRITE ,__canmod_bits);
__IO_REG32_BIT(CAN1CMR,               0x40044004,__WRITE      ,__cancmr_bits);
__IO_REG32_BIT(CAN1GSR,               0x40044008,__READ_WRITE ,__cangsr_bits);
__IO_REG32_BIT(CAN1ICR,               0x4004400C,__READ       ,__canicr_bits);
__IO_REG32_BIT(CAN1IER,               0x40044010,__READ_WRITE ,__canier_bits);
__IO_REG32_BIT(CAN1BTR,               0x40044014,__READ_WRITE ,__canbtr_bits);
__IO_REG32_BIT(CAN1EWL,               0x40044018,__READ_WRITE ,__canewl_bits);
__IO_REG32_BIT(CAN1SR,                0x4004401C,__READ       ,__cansr_bits);
__IO_REG32_BIT(CAN1RFS,               0x40044020,__READ_WRITE ,__canrfs_bits);
__IO_REG32_BIT(CAN1RID,               0x40044024,__READ_WRITE ,__canrid_bits);
__IO_REG32_BIT(CAN1RDA,               0x40044028,__READ_WRITE ,__canrda_bits);
__IO_REG32_BIT(CAN1RDB,               0x4004402C,__READ_WRITE ,__canrdb_bits);
__IO_REG32_BIT(CAN1TFI1,              0x40044030,__READ_WRITE ,__cantfi_bits);
__IO_REG32_BIT(CAN1TID1,              0x40044034,__READ_WRITE ,__cantid_bits);
__IO_REG32_BIT(CAN1TDA1,              0x40044038,__READ_WRITE ,__cantda_bits);
__IO_REG32_BIT(CAN1TDB1,              0x4004403C,__READ_WRITE ,__cantdb_bits);
__IO_REG32_BIT(CAN1TFI2,              0x40044040,__READ_WRITE ,__cantfi_bits);
__IO_REG32_BIT(CAN1TID2,              0x40044044,__READ_WRITE ,__cantid_bits);
__IO_REG32_BIT(CAN1TDA2,              0x40044048,__READ_WRITE ,__cantda_bits);
__IO_REG32_BIT(CAN1TDB2,              0x4004404C,__READ_WRITE ,__cantdb_bits);
__IO_REG32_BIT(CAN1TFI3,              0x40044050,__READ_WRITE ,__cantfi_bits);
__IO_REG32_BIT(CAN1TID3,              0x40044054,__READ_WRITE ,__cantid_bits);
__IO_REG32_BIT(CAN1TDA3,              0x40044058,__READ_WRITE ,__cantda_bits);
__IO_REG32_BIT(CAN1TDB3,              0x4004405C,__READ_WRITE ,__cantdb_bits);
__IO_REG32_BIT(CAN2MOD,               0x40048000,__READ_WRITE ,__canmod_bits);
__IO_REG32_BIT(CAN2CMR,               0x40048004,__WRITE      ,__cancmr_bits);
__IO_REG32_BIT(CAN2GSR,               0x40048008,__READ_WRITE ,__cangsr_bits);
__IO_REG32_BIT(CAN2ICR,               0x4004800C,__READ       ,__canicr_bits);
__IO_REG32_BIT(CAN2IER,               0x40048010,__READ_WRITE ,__canier_bits);
__IO_REG32_BIT(CAN2BTR,               0x40048014,__READ_WRITE ,__canbtr_bits);
__IO_REG32_BIT(CAN2EWL,               0x40048018,__READ_WRITE ,__canewl_bits);
__IO_REG32_BIT(CAN2SR,                0x4004801C,__READ       ,__cansr_bits);
__IO_REG32_BIT(CAN2RFS,               0x40048020,__READ_WRITE ,__canrfs_bits);
__IO_REG32_BIT(CAN2RID,               0x40048024,__READ_WRITE ,__canrid_bits);
__IO_REG32_BIT(CAN2RDA,               0x40048028,__READ_WRITE ,__canrda_bits);
__IO_REG32_BIT(CAN2RDB,               0x4004802C,__READ_WRITE ,__canrdb_bits);
__IO_REG32_BIT(CAN2TFI1,              0x40048030,__READ_WRITE ,__cantfi_bits);
__IO_REG32_BIT(CAN2TID1,              0x40048034,__READ_WRITE ,__cantid_bits);
__IO_REG32_BIT(CAN2TDA1,              0x40048038,__READ_WRITE ,__cantda_bits);
__IO_REG32_BIT(CAN2TDB1,              0x4004803C,__READ_WRITE ,__cantdb_bits);
__IO_REG32_BIT(CAN2TFI2,              0x40048040,__READ_WRITE ,__cantfi_bits);
__IO_REG32_BIT(CAN2TID2,              0x40048044,__READ_WRITE ,__cantid_bits);
__IO_REG32_BIT(CAN2TDA2,              0x40048048,__READ_WRITE ,__cantda_bits);
__IO_REG32_BIT(CAN2TDB2,              0x4004804C,__READ_WRITE ,__cantdb_bits);
__IO_REG32_BIT(CAN2TFI3,              0x40048050,__READ_WRITE ,__cantfi_bits);
__IO_REG32_BIT(CAN2TID3,              0x40048054,__READ_WRITE ,__cantid_bits);
__IO_REG32_BIT(CAN2TDA3,              0x40048058,__READ_WRITE ,__cantda_bits);
__IO_REG32_BIT(CAN2TDB3,              0x4004805C,__READ_WRITE ,__cantdb_bits);
__IO_REG32_BIT(CANSLEEPCLR,           0x400FC110,__READ_WRITE ,__cansleepclr_bits);
__IO_REG32_BIT(CANWAKEFLAGS,          0x400FC114,__READ_WRITE ,__canwakeflags_bits);

/***************************************************************************
 **
 ** SPI
 **
 ***************************************************************************/
__IO_REG32_BIT(S0SPCR,                0x40020000,__READ_WRITE ,__spcr_bits);
__IO_REG32_BIT(S0SPSR,                0x40020004,__READ       ,__spsr_bits);
__IO_REG16(    S0SPDR,                0x40020008,__READ_WRITE);
__IO_REG32_BIT(S0SPCCR,               0x4002000C,__READ_WRITE ,__spccr_bits);
__IO_REG8_BIT( SPTCR,                 0x40020010,__READ_WRITE ,__sptcr_bits);
__IO_REG8_BIT( SPTSR,                 0x40020014,__READ_WRITE ,__sptsr_bits);
__IO_REG32_BIT(S0SPINT,               0x4002001C,__READ_WRITE ,__spint_bits);

/***************************************************************************
 **
 ** SSP0
 **
 ***************************************************************************/
__IO_REG32_BIT(SSP0CR0,               0x40088000,__READ_WRITE ,__sspcr0_bits);
__IO_REG32_BIT(SSP0CR1,               0x40088004,__READ_WRITE ,__sspcr1_bits);
__IO_REG32_BIT(SSP0DR,                0x40088008,__READ_WRITE ,__sspdr_bits);
__IO_REG32_BIT(SSP0SR,                0x4008800C,__READ       ,__sspsr_bits);
__IO_REG32_BIT(SSP0CPSR,              0x40088010,__READ_WRITE ,__sspcpsr_bits);
__IO_REG32_BIT(SSP0IMSC,              0x40088014,__READ_WRITE ,__sspimsc_bits);
__IO_REG32_BIT(SSP0RIS,               0x40088018,__READ_WRITE ,__sspris_bits);
__IO_REG32_BIT(SSP0MIS,               0x4008801C,__READ_WRITE ,__sspmis_bits);
__IO_REG32_BIT(SSP0ICR,               0x40088020,__READ_WRITE ,__sspicr_bits);
__IO_REG32_BIT(SSP0DMACR,             0x40088024,__READ_WRITE ,__sspdmacr_bits);

/***************************************************************************
 **
 ** SSP1
 **
 ***************************************************************************/
__IO_REG32_BIT(SSP1CR0,               0x40030000,__READ_WRITE ,__sspcr0_bits);
__IO_REG32_BIT(SSP1CR1,               0x40030004,__READ_WRITE ,__sspcr1_bits);
__IO_REG32_BIT(SSP1DR,                0x40030008,__READ_WRITE ,__sspdr_bits);
__IO_REG32_BIT(SSP1SR,                0x4003000C,__READ       ,__sspsr_bits);
__IO_REG32_BIT(SSP1CPSR,              0x40030010,__READ_WRITE ,__sspcpsr_bits);
__IO_REG32_BIT(SSP1IMSC,              0x40030014,__READ_WRITE ,__sspimsc_bits);
__IO_REG32_BIT(SSP1RIS,               0x40030018,__READ_WRITE ,__sspris_bits);
__IO_REG32_BIT(SSP1MIS,               0x4003001C,__READ_WRITE ,__sspmis_bits);
__IO_REG32_BIT(SSP1ICR,               0x40030020,__READ_WRITE ,__sspicr_bits);
__IO_REG32_BIT(SSP1DMACR,             0x40030024,__READ_WRITE ,__sspdmacr_bits);

/***************************************************************************
 **
 ** I2C0
 **
 ***************************************************************************/
__IO_REG32_BIT(I2C0CONSET,            0x4001C000,__READ_WRITE ,__i2conset_bits);
__IO_REG32_BIT(I2C0STAT,              0x4001C004,__READ       ,__i2stat_bits);
__IO_REG32_BIT(I2C0DAT,               0x4001C008,__READ_WRITE ,__i2dat_bits);
__IO_REG32_BIT(I2C0ADR,               0x4001C00C,__READ_WRITE ,__i2adr_bits);
__IO_REG32_BIT(I2C0SCLH,              0x4001C010,__READ_WRITE ,__i2sch_bits);
__IO_REG32_BIT(I2C0SCLL,              0x4001C014,__READ_WRITE ,__i2scl_bits);
__IO_REG32_BIT(I2C0CONCLR,            0x4001C018,__WRITE      ,__i2conclr_bits);
__IO_REG32_BIT(I2C0MMCTRL,            0x4001C01C,__READ_WRITE ,__i2cmmctrl_bits);
__IO_REG32_BIT(I2C0ADR1,              0x4001C020,__READ_WRITE ,__i2adr_bits);
__IO_REG32_BIT(I2C0ADR2,              0x4001C024,__READ_WRITE ,__i2adr_bits);
__IO_REG32_BIT(I2C0ADR3,              0x4001C028,__READ_WRITE ,__i2adr_bits);
__IO_REG32_BIT(I2C0DATABUFFER,        0x4001C02C,__READ       ,__i2dat_bits);
__IO_REG32_BIT(I2C0MASK0,             0x4001C030,__READ_WRITE ,__i2cmask_bits);
__IO_REG32_BIT(I2C0MASK1,             0x4001C034,__READ_WRITE ,__i2cmask_bits);
__IO_REG32_BIT(I2C0MASK2,             0x4001C038,__READ_WRITE ,__i2cmask_bits);
__IO_REG32_BIT(I2C0MASK3,             0x4001C03C,__READ_WRITE ,__i2cmask_bits);

/***************************************************************************
 **
 ** I2C1
 **
 ***************************************************************************/
__IO_REG32_BIT(I2C1CONSET,            0x4005C000,__READ_WRITE ,__i2conset_bits);
__IO_REG32_BIT(I2C1STAT,              0x4005C004,__READ       ,__i2stat_bits);
__IO_REG32_BIT(I2C1DAT,               0x4005C008,__READ_WRITE ,__i2dat_bits);
__IO_REG32_BIT(I2C1ADR,               0x4005C00C,__READ_WRITE ,__i2adr_bits);
__IO_REG32_BIT(I2C1SCLH,              0x4005C010,__READ_WRITE ,__i2sch_bits);
__IO_REG32_BIT(I2C1SCLL,              0x4005C014,__READ_WRITE ,__i2scl_bits);
__IO_REG32_BIT(I2C1CONCLR,            0x4005C018,__WRITE      ,__i2conclr_bits);
__IO_REG32_BIT(I2C1MMCTRL,            0x4005C01C,__READ_WRITE ,__i2cmmctrl_bits);
__IO_REG32_BIT(I2C1ADR1,              0x4005C020,__READ_WRITE ,__i2adr_bits);
__IO_REG32_BIT(I2C1ADR2,              0x4005C024,__READ_WRITE ,__i2adr_bits);
__IO_REG32_BIT(I2C1ADR3,              0x4005C028,__READ_WRITE ,__i2adr_bits);
__IO_REG32_BIT(I2C1DATABUFFER,        0x4005C02C,__READ       ,__i2dat_bits);
__IO_REG32_BIT(I2C1MASK0,             0x4005C030,__READ_WRITE ,__i2cmask_bits);
__IO_REG32_BIT(I2C1MASK1,             0x4005C034,__READ_WRITE ,__i2cmask_bits);
__IO_REG32_BIT(I2C1MASK2,             0x4005C038,__READ_WRITE ,__i2cmask_bits);
__IO_REG32_BIT(I2C1MASK3,             0x4005C03C,__READ_WRITE ,__i2cmask_bits);

/***************************************************************************
 **
 ** I2C2
 **
 ***************************************************************************/
__IO_REG32_BIT(I2C2CONSET,            0x400A0000,__READ_WRITE ,__i2conset_bits);
__IO_REG32_BIT(I2C2STAT,              0x400A0004,__READ       ,__i2stat_bits);
__IO_REG32_BIT(I2C2DAT,               0x400A0008,__READ_WRITE ,__i2dat_bits);
__IO_REG32_BIT(I2C2ADR,               0x400A000C,__READ_WRITE ,__i2adr_bits);
__IO_REG32_BIT(I2C2SCLH,              0x400A0010,__READ_WRITE ,__i2sch_bits);
__IO_REG32_BIT(I2C2SCLL,              0x400A0014,__READ_WRITE ,__i2scl_bits);
__IO_REG32_BIT(I2C2CONCLR,            0x400A0018,__WRITE      ,__i2conclr_bits);
__IO_REG32_BIT(I2C2MMCTRL,            0x400A001C,__READ_WRITE ,__i2cmmctrl_bits);
__IO_REG32_BIT(I2C2ADR1,              0x400A0020,__READ_WRITE ,__i2adr_bits);
__IO_REG32_BIT(I2C2ADR2,              0x400A0024,__READ_WRITE ,__i2adr_bits);
__IO_REG32_BIT(I2C2ADR3,              0x400A0028,__READ_WRITE ,__i2adr_bits);
__IO_REG32_BIT(I2C2DATABUFFER,        0x400A002C,__READ       ,__i2dat_bits);
__IO_REG32_BIT(I2C2MASK0,             0x400A0030,__READ_WRITE ,__i2cmask_bits);
__IO_REG32_BIT(I2C2MASK1,             0x400A0034,__READ_WRITE ,__i2cmask_bits);
__IO_REG32_BIT(I2C2MASK2,             0x400A0038,__READ_WRITE ,__i2cmask_bits);
__IO_REG32_BIT(I2C2MASK3,             0x400A003C,__READ_WRITE ,__i2cmask_bits);

/***************************************************************************
 **
 ** I2S
 **
 ***************************************************************************/
__IO_REG32_BIT(I2SDAO,                0x400A8000,__READ_WRITE ,__i2sdao_bits);
__IO_REG32_BIT(I2SDAI,                0x400A8004,__READ_WRITE ,__i2sdai_bits);
__IO_REG32(    I2STXFIFO,             0x400A8008,__WRITE);
__IO_REG32(    I2SRXFIFO,             0x400A800C,__READ);
__IO_REG32_BIT(I2SSTATE,              0x400A8010,__READ       ,__i2sstate_bits);
__IO_REG32_BIT(I2SDMA1,               0x400A8014,__READ_WRITE ,__i2sdma_bits);
__IO_REG32_BIT(I2SDMA2,               0x400A8018,__READ_WRITE ,__i2sdma_bits);
__IO_REG32_BIT(I2SIRQ,                0x400A801C,__READ_WRITE ,__i2sirq_bits);
__IO_REG32_BIT(I2STXRATE,             0x400A8020,__READ_WRITE ,__i2stxrate_bits);
__IO_REG32_BIT(I2SRXRATE,             0x400A8024,__READ_WRITE ,__i2stxrate_bits);
__IO_REG32_BIT(I2STXBITRATE,          0x400A8028,__READ_WRITE ,__i2stxbitrate_bits);
__IO_REG32_BIT(I2SRXBITRATE,          0x400A802C,__READ_WRITE ,__i2srxbitrate_bits);
__IO_REG32_BIT(I2STXMODE,             0x400A8030,__READ_WRITE ,__i2stxmode_bits);
__IO_REG32_BIT(I2SRXMODE,             0x400A8034,__READ_WRITE ,__i2srxmode_bits);

/***************************************************************************
 **
 ** TIMER0
 **
 ***************************************************************************/
__IO_REG32_BIT(T0IR,                  0x40004000,__READ_WRITE ,__ir_bits);
__IO_REG32_BIT(T0TCR,                 0x40004004,__READ_WRITE ,__tcr_bits);
__IO_REG32(    T0TC,                  0x40004008,__READ_WRITE);
__IO_REG32(    T0PR,                  0x4000400C,__READ_WRITE);
__IO_REG32(    T0PC,                  0x40004010,__READ_WRITE);
__IO_REG32_BIT(T0MCR,                 0x40004014,__READ_WRITE ,__mcr_bits);
__IO_REG32(    T0MR0,                 0x40004018,__READ_WRITE);
__IO_REG32(    T0MR1,                 0x4000401C,__READ_WRITE);
__IO_REG32(    T0MR2,                 0x40004020,__READ_WRITE);
__IO_REG32(    T0MR3,                 0x40004024,__READ_WRITE);
__IO_REG32_BIT(T0CCR,                 0x40004028,__READ_WRITE ,__tccr_bits);
__IO_REG32(    T0CR0,                 0x4000402C,__READ);
__IO_REG32(    T0CR1,                 0x40004030,__READ);
__IO_REG32_BIT(T0EMR,                 0x4000403C,__READ_WRITE ,__emr_bits);
__IO_REG32_BIT(T0CTCR,                0x40004070,__READ_WRITE ,__ctcr_bits);

/***************************************************************************
 **
 ** TIMER1
 **
 ***************************************************************************/
__IO_REG32_BIT(T1IR,                  0x40008000,__READ_WRITE ,__ir_bits);
__IO_REG32_BIT(T1TCR,                 0x40008004,__READ_WRITE ,__tcr_bits);
__IO_REG32(    T1TC,                  0x40008008,__READ_WRITE);
__IO_REG32(    T1PR,                  0x4000800C,__READ_WRITE);
__IO_REG32(    T1PC,                  0x40008010,__READ_WRITE);
__IO_REG32_BIT(T1MCR,                 0x40008014,__READ_WRITE ,__mcr_bits);
__IO_REG32(    T1MR0,                 0x40008018,__READ_WRITE);
__IO_REG32(    T1MR1,                 0x4000801C,__READ_WRITE);
__IO_REG32(    T1MR2,                 0x40008020,__READ_WRITE);
__IO_REG32(    T1MR3,                 0x40008024,__READ_WRITE);
__IO_REG32_BIT(T1CCR,                 0x40008028,__READ_WRITE ,__tccr_bits);
__IO_REG32(    T1CR0,                 0x4000802C,__READ);
__IO_REG32(    T1CR1,                 0x40008030,__READ);
__IO_REG32_BIT(T1EMR,                 0x4000803C,__READ_WRITE ,__emr_bits);
__IO_REG32_BIT(T1CTCR,                0x40008070,__READ_WRITE ,__ctcr_bits);

/***************************************************************************
 **
 ** TIMER2
 **
 ***************************************************************************/
__IO_REG32_BIT(T2IR,                  0x40090000,__READ_WRITE ,__ir_bits);
__IO_REG32_BIT(T2TCR,                 0x40090004,__READ_WRITE ,__tcr_bits);
__IO_REG32(    T2TC,                  0x40090008,__READ_WRITE);
__IO_REG32(    T2PR,                  0x4009000C,__READ_WRITE);
__IO_REG32(    T2PC,                  0x40090010,__READ_WRITE);
__IO_REG32_BIT(T2MCR,                 0x40090014,__READ_WRITE ,__mcr_bits);
__IO_REG32(    T2MR0,                 0x40090018,__READ_WRITE);
__IO_REG32(    T2MR1,                 0x4009001C,__READ_WRITE);
__IO_REG32(    T2MR2,                 0x40090020,__READ_WRITE);
__IO_REG32(    T2MR3,                 0x40090024,__READ_WRITE);
__IO_REG32_BIT(T2CCR,                 0x40090028,__READ_WRITE ,__tccr_bits);
__IO_REG32(    T2CR0,                 0x4009002C,__READ);
__IO_REG32(    T2CR1,                 0x40090030,__READ);
__IO_REG32_BIT(T2EMR,                 0x4009003C,__READ_WRITE ,__emr_bits);
__IO_REG32_BIT(T2CTCR,                0x40090070,__READ_WRITE ,__ctcr_bits);

/***************************************************************************
 **
 ** TIMER3
 **
 ***************************************************************************/
__IO_REG32_BIT(T3IR,                  0x40094000,__READ_WRITE ,__ir_bits);
__IO_REG32_BIT(T3TCR,                 0x40094004,__READ_WRITE ,__tcr_bits);
__IO_REG32(    T3TC,                  0x40094008,__READ_WRITE);
__IO_REG32(    T3PR,                  0x4009400C,__READ_WRITE);
__IO_REG32(    T3PC,                  0x40094010,__READ_WRITE);
__IO_REG32_BIT(T3MCR,                 0x40094014,__READ_WRITE ,__mcr_bits);
__IO_REG32(    T3MR0,                 0x40094018,__READ_WRITE);
__IO_REG32(    T3MR1,                 0x4009401C,__READ_WRITE);
__IO_REG32(    T3MR2,                 0x40094020,__READ_WRITE);
__IO_REG32(    T3MR3,                 0x40094024,__READ_WRITE);
__IO_REG32_BIT(T3CCR,                 0x40094028,__READ_WRITE ,__tccr_bits);
__IO_REG32(    T3CR0,                 0x4009402C,__READ);
__IO_REG32(    T3CR1,                 0x40094030,__READ);
__IO_REG32_BIT(T3EMR,                 0x4009403C,__READ_WRITE ,__emr_bits);
__IO_REG32_BIT(T3CTCR,                0x40094070,__READ_WRITE ,__ctcr_bits);

/***************************************************************************
 **
 ** Repetitive Interrupt Timer
 **
 ***************************************************************************/
__IO_REG32(    RICOMPVAL,             0x400B0000,__READ_WRITE );
__IO_REG32(    RIMASK,                0x400B0004,__READ_WRITE );
__IO_REG32_BIT(RICTRL,                0x400B0008,__READ_WRITE ,__rictrl_bits);
__IO_REG32(    RICOUNTER,             0x400B000C,__READ_WRITE );

/***************************************************************************
 **
 ** PWM1
 **
 ***************************************************************************/
__IO_REG32_BIT(PWM1IR,                0x40018000,__READ_WRITE ,__pwmir_bits);
__IO_REG32_BIT(PWM1TCR,               0x40018004,__READ_WRITE ,__pwmtcr1_bits);
__IO_REG32(    PWM1TC,                0x40018008,__READ_WRITE);
__IO_REG32(    PWM1PR,                0x4001800C,__READ_WRITE);
__IO_REG32(    PWM1PC,                0x40018010,__READ_WRITE);
__IO_REG32_BIT(PWM1MCR,               0x40018014,__READ_WRITE ,__pwmmcr_bits);
__IO_REG32(    PWM1MR0,               0x40018018,__READ_WRITE);
__IO_REG32(    PWM1MR1,               0x4001801C,__READ_WRITE);
__IO_REG32(    PWM1MR2,               0x40018020,__READ_WRITE);
__IO_REG32(    PWM1MR3,               0x40018024,__READ_WRITE);
__IO_REG32_BIT(PWM1CCR,               0x40018028,__READ_WRITE ,__pwmccr_bits);
__IO_REG32(    PWM1CR0,               0x4001802C,__READ);
__IO_REG32(    PWM1CR1,               0x40018030,__READ);
__IO_REG32(    PWM1CR2,               0x40018034,__READ);
__IO_REG32(    PWM1CR3,               0x40018038,__READ);
__IO_REG32(    PWM1MR4,               0x40018040,__READ_WRITE);
__IO_REG32(    PWM1MR5,               0x40018044,__READ_WRITE);
__IO_REG32(    PWM1MR6,               0x40018048,__READ_WRITE);
__IO_REG32_BIT(PWM1PCR,               0x4001804C,__READ_WRITE ,__pwmpcr_bits);
__IO_REG32_BIT(PWM1LER,               0x40018050,__READ_WRITE ,__pwmler_bits);
__IO_REG32_BIT(PWM1CTCR,              0x40018070,__READ_WRITE ,__pwmctcr_bits);

/***************************************************************************
 **
 ** Motor control PWM
 **
 ***************************************************************************/
__IO_REG32_BIT(MCCON,                 0x400B8000,__READ       ,__mccon_bits);
__IO_REG32_BIT(MCCON_SET,             0x400B8004,__WRITE      ,__mccon_bits);
__IO_REG32_BIT(MCCON_CLR,             0x400B8008,__WRITE      ,__mccon_bits);
__IO_REG32_BIT(MCCAPCON,              0x400B800C,__READ       ,__mccapcon_bits);
__IO_REG32_BIT(MCCAPCON_SET,          0x400B8010,__WRITE      ,__mccapcon_bits);
__IO_REG32_BIT(MCCAPCON_CLR,          0x400B8014,__WRITE      ,__mccapcon_bits);
__IO_REG32(    MCTC0,                 0x400B8018,__READ_WRITE );
__IO_REG32(    MCTC1,                 0x400B801C,__READ_WRITE );
__IO_REG32(    MCTC2,                 0x400B8020,__READ_WRITE );
__IO_REG32(    MCLIM0,                0x400B8024,__READ_WRITE );
__IO_REG32(    MCLIM1,                0x400B8028,__READ_WRITE );
__IO_REG32(    MCLIM2,                0x400B802C,__READ_WRITE );
__IO_REG32(    MCMAT0,                0x400B8030,__READ_WRITE );
__IO_REG32(    MCMAT1,                0x400B8034,__READ_WRITE );
__IO_REG32(    MCMAT2,                0x400B8038,__READ_WRITE );
__IO_REG32_BIT(MCDT,                  0x400B803C,__READ_WRITE ,__mcdt_bits);
__IO_REG32_BIT(MCCCP,                 0x400B8040,__READ_WRITE ,__mcccp_bits);
__IO_REG32(    MCCAP0,                0x400B8044,__READ       );
__IO_REG32(    MCCAP1,                0x400B8048,__READ       );
__IO_REG32(    MCCAP2,                0x400B804C,__READ       );
__IO_REG32_BIT(MCINTEN,               0x400B8050,__READ       ,__mcinten_bits);
__IO_REG32_BIT(MCINTEN_SET,           0x400B8054,__WRITE      ,__mcinten_bits);
__IO_REG32_BIT(MCINTEN_CLR,           0x400B8058,__WRITE      ,__mcinten_bits);
__IO_REG32_BIT(MCCNTCON,              0x400B805C,__READ       ,__mccntcon_bits);
__IO_REG32_BIT(MCCNTCON_SET,          0x400B8060,__WRITE      ,__mccntcon_bits);
__IO_REG32_BIT(MCCNTCON_CLR,          0x400B8064,__WRITE      ,__mccntcon_bits);
__IO_REG32_BIT(MCINTF,                0x400B8068,__READ       ,__mcinten_bits);
__IO_REG32_BIT(MCINTF_SET,            0x400B806C,__WRITE      ,__mcinten_bits);
__IO_REG32_BIT(MCINTF_CLR,            0x400B8070,__WRITE      ,__mcinten_bits);
__IO_REG32_BIT(MCCAP_CLR,             0x400B8074,__WRITE      ,__mccap_clr_bits);

/***************************************************************************
 **
 ** Quadrature Encoder Interface
 **
 ***************************************************************************/
__IO_REG32_BIT(QEICON,                0x400BC000,__WRITE      ,__qeicon_bits);
__IO_REG32_BIT(QEISTAT,               0x400BC004,__READ       ,__qeistat_bits);
__IO_REG32_BIT(QEICONF,               0x400BC008,__READ_WRITE ,__qeiconf_bits);
__IO_REG32(    QEIPOS,                0x400BC00C,__READ       );
__IO_REG32(    QEIMAXPSOS,            0x400BC010,__READ_WRITE );
__IO_REG32(    CMPOS0,                0x400BC014,__READ_WRITE );
__IO_REG32(    CMPOS1,                0x400BC018,__READ_WRITE );
__IO_REG32(    CMPOS2,                0x400BC01C,__READ_WRITE );
__IO_REG32(    INXCNT,                0x400BC020,__READ       );
__IO_REG32(    INXCMP,                0x400BC024,__READ_WRITE );
__IO_REG32(    QEILOAD,               0x400BC028,__READ_WRITE );
__IO_REG32(    QEITIME,               0x400BC02C,__READ       );
__IO_REG32(    QEIVEL,                0x400BC030,__READ       );
__IO_REG32(    QEICAP,                0x400BC034,__READ       );
__IO_REG32(    VELCOMP,               0x400BC038,__READ_WRITE );
__IO_REG32(    FILTER,                0x400BC03C,__READ_WRITE );
__IO_REG32_BIT(QEIIEC,                0x400BCFD8,__WRITE      ,__qeiintstat_bits);
__IO_REG32_BIT(QEIIES,                0x400BCFDC,__WRITE      ,__qeiintstat_bits);
__IO_REG32_BIT(QEIINTSTAT,            0x400BCFE0,__READ       ,__qeiintstat_bits);
__IO_REG32_BIT(QEIIE,                 0x400BCFE4,__READ       ,__qeiintstat_bits);
__IO_REG32_BIT(QEICLR,                0x400BCFE8,__WRITE      ,__qeiintstat_bits);
__IO_REG32_BIT(QEISET,                0x400BCFEC,__WRITE      ,__qeiintstat_bits);

/***************************************************************************
 **
 ** RTC
 **
 ***************************************************************************/
__IO_REG32_BIT(RTCILR,                0x40024000,__READ_WRITE ,__ilr_bits);
__IO_REG32_BIT(RTCCCR,                0x40024008,__READ_WRITE ,__rtcccr_bits);
__IO_REG32_BIT(RTCCIIR,               0x4002400C,__READ_WRITE ,__ciir_bits);
__IO_REG32_BIT(RTCAMR,                0x40024010,__READ_WRITE ,__amr_bits);
__IO_REG32_BIT(RTCCTIME0,             0x40024014,__READ       ,__ctime0_bits);
__IO_REG32_BIT(RTCCTIME1,             0x40024018,__READ       ,__ctime1_bits);
__IO_REG32_BIT(RTCCTIME2,             0x4002401C,__READ       ,__ctime2_bits);
__IO_REG32_BIT(RTCSEC,                0x40024020,__READ_WRITE ,__sec_bits);
__IO_REG32_BIT(RTCMIN,                0x40024024,__READ_WRITE ,__min_bits);
__IO_REG32_BIT(RTCHOUR,               0x40024028,__READ_WRITE ,__hour_bits);
__IO_REG32_BIT(RTCDOM,                0x4002402C,__READ_WRITE ,__dom_bits);
__IO_REG32_BIT(RTCDOW,                0x40024030,__READ_WRITE ,__dow_bits);
__IO_REG32_BIT(RTCDOY,                0x40024034,__READ_WRITE ,__doy_bits);
__IO_REG32_BIT(RTCMONTH,              0x40024038,__READ_WRITE ,__month_bits);
__IO_REG32_BIT(RTCYEAR,               0x4002403C,__READ_WRITE ,__year_bits);
__IO_REG32_BIT(RTCCALIBRATION,        0x40024040,__READ_WRITE ,__calibration_bits);
__IO_REG32(    RTCGPREG0,             0x40024044,__READ_WRITE );
__IO_REG32(    RTCGPREG1,             0x40024048,__READ_WRITE );
__IO_REG32(    RTCGPREG2,             0x4002404C,__READ_WRITE );
__IO_REG32(    RTCGPREG3,             0x40024050,__READ_WRITE );
__IO_REG32(    RTCGPREG4,             0x40024054,__READ_WRITE );
__IO_REG32_BIT(RTCAUXEN,              0x40024058,__READ_WRITE ,__rtcauxen_bits);
__IO_REG32_BIT(RTCAUX,                0x4002405C,__READ_WRITE ,__rtcaux_bits);
__IO_REG32_BIT(RTCALSEC,              0x40024060,__READ_WRITE ,__sec_bits);
__IO_REG32_BIT(RTCALMIN,              0x40024064,__READ_WRITE ,__min_bits);
__IO_REG32_BIT(RTCALHOUR,             0x40024068,__READ_WRITE ,__hour_bits);
__IO_REG32_BIT(RTCALDOM,              0x4002406C,__READ_WRITE ,__dom_bits);
__IO_REG32_BIT(RTCALDOW,              0x40024070,__READ_WRITE ,__dow_bits);
__IO_REG32_BIT(RTCALDOY,              0x40024074,__READ_WRITE ,__doy_bits);
__IO_REG32_BIT(RTCALMON,              0x40024078,__READ_WRITE ,__month_bits);
__IO_REG32_BIT(RTCALYEAR,             0x4002407C,__READ_WRITE ,__year_bits);

/***************************************************************************
 **
 ** Watchdog
 **
 ***************************************************************************/
__IO_REG32_BIT(WDMOD,                 0x40000000,__READ_WRITE ,__wdmod_bits);
__IO_REG32(    WDTC,                  0x40000004,__READ_WRITE);
__IO_REG32_BIT(WDFEED,                0x40000008,__WRITE      ,__wdfeed_bits);
__IO_REG32(    WDTV,                  0x4000000C,__READ);
__IO_REG32_BIT(WDCLKSEL,              0x40000010,__READ_WRITE ,__wdclksel_bits);

/***************************************************************************
 **
 ** A/D Converters
 **
 ***************************************************************************/
__IO_REG32_BIT(AD0CR,                 0x40034000,__READ_WRITE ,__adcr_bits);
__IO_REG32_BIT(AD0GDR,                0x40034004,__READ_WRITE ,__adgdr_bits);
__IO_REG32_BIT(ADINTEN,               0x4003400C,__READ_WRITE ,__adinten_bits);
__IO_REG32_BIT(ADDR0,                 0x40034010,__READ       ,__addr_bits);
__IO_REG32_BIT(ADDR1,                 0x40034014,__READ       ,__addr_bits);
__IO_REG32_BIT(ADDR2,                 0x40034018,__READ       ,__addr_bits);
__IO_REG32_BIT(ADDR3,                 0x4003401C,__READ       ,__addr_bits);
__IO_REG32_BIT(ADDR4,                 0x40034020,__READ       ,__addr_bits);
__IO_REG32_BIT(ADDR5,                 0x40034024,__READ       ,__addr_bits);
__IO_REG32_BIT(ADDR6,                 0x40034028,__READ       ,__addr_bits);
__IO_REG32_BIT(ADDR7,                 0x4003402C,__READ       ,__addr_bits);
__IO_REG32_BIT(ADSTAT,                0x40034030,__READ       ,__adstat_bits);
__IO_REG32_BIT(ADTRM,                 0x40034034,__READ_WRITE ,__adtrm_bits);

/***************************************************************************
 **
 ** D/A Converter
 **
 ***************************************************************************/
__IO_REG32_BIT(DACR,                  0x4008C000,__READ_WRITE ,__dacr_bits);
__IO_REG32_BIT(DACCTRL,               0x4008C004,__READ_WRITE ,__dacctrl_bits);
__IO_REG32_BIT(DACCNTVAL,             0x4008C008,__READ_WRITE ,__daccntval_bits);

/***************************************************************************
 **
 ** GPDMA
 **
 ***************************************************************************/
__IO_REG32_BIT(DMACINTSTATUS,         0x50004000,__READ      ,__dmacintstatus_bits);
__IO_REG32_BIT(DMACINTTCSTATUS,       0x50004004,__READ      ,__dmacinttcstatus_bits);
__IO_REG32_BIT(DMACINTTCCLEAR,        0x50004008,__WRITE     ,__dmacinttcclear_bits);
__IO_REG32_BIT(DMACINTERRSTAT,        0x5000400C,__READ      ,__dmacinterrstat_bits);
__IO_REG32_BIT(DMACINTERRCLR,         0x50004010,__WRITE     ,__dmacinterrclr_bits);
__IO_REG32_BIT(DMACRAWINTTCSTATUS,    0x50004014,__READ      ,__dmacrawinttcstatus_bits);
__IO_REG32_BIT(DMACRAWINTERRORSTATUS, 0x50004018,__READ      ,__dmacrawinterrorstatus_bits);
__IO_REG32_BIT(DMACENBLDCHNS,         0x5000401C,__READ      ,__dmacenbldchns_bits);
__IO_REG32_BIT(DMACSOFTBREQ,          0x50004020,__READ_WRITE,__dmacsoftbreq_bits);
__IO_REG32_BIT(DMACSOFTSREQ,          0x50004024,__READ_WRITE,__dmacsoftsreq_bits);
__IO_REG32_BIT(DMACSOFTLBREQ,         0x50004028,__READ_WRITE,__dmacsoftlbreq_bits);
__IO_REG32_BIT(DMACSOFTLSREQ,         0x5000402C,__READ_WRITE,__dmacsoftlsreq_bits);
__IO_REG32_BIT(DMACCONFIGURATION,     0x50004030,__READ_WRITE,__dmacconfig_bits);
__IO_REG32_BIT(DMACSYNC,              0x50004034,__READ_WRITE,__dmacsync_bits);
__IO_REG32_BIT(DMAREQSEL,             0x4000C1C4,__READ_WRITE,__dmareqsel_bits);
__IO_REG32(    DMACC0SRCADDR,         0x50004100,__READ_WRITE);
__IO_REG32(    DMACC0DESTADDR,        0x50004104,__READ_WRITE);
__IO_REG32(    DMACC0LLI,             0x50004108,__READ_WRITE);
__IO_REG32_BIT(DMACC0CONTROL,         0x5000410C,__READ_WRITE,__dma_ctrl_bits);
__IO_REG32_BIT(DMACC0CONFIGURATION,   0x50004110,__READ_WRITE,__dma_cfg_bits);
__IO_REG32(    DMACC1SRCADDR,         0x50004120,__READ_WRITE);
__IO_REG32(    DMACC1DESTADDR,        0x50004124,__READ_WRITE);
__IO_REG32(    DMACC1LLI,             0x50004128,__READ_WRITE);
__IO_REG32_BIT(DMACC1CONTROL,         0x5000412C,__READ_WRITE,__dma_ctrl_bits);
__IO_REG32_BIT(DMACC1CONFIGURATION,   0x50004130,__READ_WRITE,__dma_cfg_bits);
__IO_REG32(    DMACC2SRCADDR,         0x50004140,__READ_WRITE);
__IO_REG32(    DMACC2DESTADDR,        0x50004144,__READ_WRITE);
__IO_REG32(    DMACC2LLI,             0x50004148,__READ_WRITE);
__IO_REG32_BIT(DMACC2CONTROL,         0x5000414C,__READ_WRITE,__dma_ctrl_bits);
__IO_REG32_BIT(DMACC2CONFIGURATION,   0x50004150,__READ_WRITE,__dma_cfg_bits);
__IO_REG32(    DMACC3SRCADDR,         0x50004160,__READ_WRITE);
__IO_REG32(    DMACC3DESTADDR,        0x50004164,__READ_WRITE);
__IO_REG32(    DMACC3LLI,             0x50004168,__READ_WRITE);
__IO_REG32_BIT(DMACC3CONTROL,         0x5000416C,__READ_WRITE,__dma_ctrl_bits);
__IO_REG32_BIT(DMACC3CONFIGURATION,   0x50004170,__READ_WRITE,__dma_cfg_bits);
__IO_REG32(    DMACC4SRCADDR,         0x50004180,__READ_WRITE);
__IO_REG32(    DMACC4DESTADDR,        0x50004184,__READ_WRITE);
__IO_REG32(    DMACC4LLI,             0x50004188,__READ_WRITE);
__IO_REG32_BIT(DMACC4CONTROL,         0x5000418C,__READ_WRITE,__dma_ctrl_bits);
__IO_REG32_BIT(DMACC4CONFIGURATION,   0x50004190,__READ_WRITE,__dma_cfg_bits);
__IO_REG32(    DMACC5SRCADDR,         0x500041A0,__READ_WRITE);
__IO_REG32(    DMACC5DESTADDR,        0x500041A4,__READ_WRITE);
__IO_REG32(    DMACC5LLI,             0x500041A8,__READ_WRITE);
__IO_REG32_BIT(DMACC5CONTROL,         0x500041AC,__READ_WRITE,__dma_ctrl_bits);
__IO_REG32_BIT(DMACC5CONFIGURATION,   0x500041B0,__READ_WRITE,__dma_cfg_bits);
__IO_REG32(    DMACC6SRCADDR,         0x500041C0,__READ_WRITE);
__IO_REG32(    DMACC6DESTADDR,        0x500041C4,__READ_WRITE);
__IO_REG32(    DMACC6LLI,             0x500041C8,__READ_WRITE);
__IO_REG32_BIT(DMACC6CONTROL,         0x500041CC,__READ_WRITE,__dma_ctrl_bits);
__IO_REG32_BIT(DMACC6CONFIGURATION,   0x500041D0,__READ_WRITE,__dma_cfg_bits);
__IO_REG32(    DMACC7SRCADDR,         0x500041E0,__READ_WRITE);
__IO_REG32(    DMACC7DESTADDR,        0x500041E4,__READ_WRITE);
__IO_REG32(    DMACC7LLI,             0x500041E8,__READ_WRITE);
__IO_REG32_BIT(DMACC7CONTROL,         0x500041EC,__READ_WRITE,__dma_ctrl_bits);
__IO_REG32_BIT(DMACC7CONFIGURATION,   0x500041F0,__READ_WRITE,__dma_cfg_bits);

/***************************************************************************
 **  Assembler-specific declarations
 ***************************************************************************/

#ifdef __IAR_SYSTEMS_ASM__
#endif    /* __IAR_SYSTEMS_ASM__ */


/***************************************************************************
 **
 **  GPDMA Controller peripheral devices lines
 **
 ***************************************************************************/
#define GPDMA_SSP0TX           0   /* SPI0 Tx                                 */
#define GPDMA_SSP0RX           1   /* SPI0 Rx                                 */
#define GPDMA_SSP1TX           2   /* SPI1 Tx                                 */
#define GPDMA_SSP1RX           3   /* SPI1 Rx                                 */
#define GPDMA_ADC              4   /* ADC                                     */
#define GPDMA_I2S0             5   /* I2S Channel 0                           */
#define GPDMA_I2S1             6   /* I2S Channel 1                           */
#define GPDMA_DAC              7   /* DAC                                     */
#define GPDMA_U0TX_MAT0_0      8   /* UART 0 Tx/MAT0.0                        */
#define GPDMA_U0RX_MAT0_1      9   /* UART 0 Rx/MAT0.1                        */
#define GPDMA_U1TX_MAT1_0     10   /* UART 1 Tx/MAT1.0                        */
#define GPDMA_U1RX_MAT1_1     11   /* UART 1 Rx/MAT1.1                        */
#define GPDMA_U2TX_MAT2_0     12   /* UART 2 Tx/MAT2.0                        */
#define GPDMA_U2RX_MAT2_1     13   /* UART 2 Rx/MAT2.1                        */
#define GPDMA_U3TX_MAT3_0     14   /* UART 3 Tx/MAT3.0                        */
#define GPDMA_U3RX_MAT3_1     15   /* UART 3 Rx/MAT3.1                        */

/***************************************************************************
 **
 **  NVIC Interrupt channels
 **
 ***************************************************************************/
#define MAIN_STACK             0  /* Main Stack                                             */
#define RESETI                 1  /* Reset                                                  */
#define NMII                   2  /* Non-maskable Interrupt                                 */
#define HFI                    3  /* Hard Fault                                             */
#define MMI                    4  /* Memory Management                                      */
#define BFI                    5  /* Bus Fault                                              */
#define UFI                    6  /* Usage Fault                                            */
#define SVCI                  11  /* SVCall                                                 */
#define DMI                   12  /* Debug Monitor                                          */
#define PSI                   14  /* PendSV                                                 */
#define STI                   15  /* SysTick                                                */
#define NVIC_WDT              16  /* Watchdog Interrupt (WDINT)                             */
#define NVIC_TIMER0           17  /* Match 0 - 1 (MR0, MR1), Capture 0 - 1 (CR0, CR1)       */
#define NVIC_TIMER1           18  /* Match 0 - 2 (MR0, MR1, MR2), Capture 0 - 1 (CR0, CR1)  */
#define NVIC_TIMER2           19  /* Match 0-3, Capture 0-1                                 */
#define NVIC_TIMER3           20  /* Match 0-3, Capture 0-1                                 */
#define NVIC_UART0            21  /* UART0                                                  */
#define NVIC_UART1            22  /* UART1                                                  */
#define NVIC_UART2            23  /* UART2                                                  */
#define NVIC_UART3            24  /* UART3                                                  */
#define NVIC_PWM1             25  /* Match 0 - 6 of PWM1, Capture 0-1 of PWM1               */
#define NVIC_I2C0             26  /* SI (state change)                                      */
#define NVIC_I2C1             27  /* SI (state change)                                      */
#define NVIC_I2C2             28  /* SI (state change)                                      */
#define NVIC_SPI              29  /* SPI Interrupt Flag (SPIF), Mode Fault (MODF)           */
#define NVIC_SSP0             30  /* SSP0                                                   */
#define NVIC_SSP1             31  /* SSP1                                                   */
#define NVIC_PLL0             32  /* PLL0 Lock                                              */
#define NVIC_RTC              33  /* Counter Increment (RTCCIF), Alarm (RTCALF)             */
#define NVIC_EINT0            34  /* External Interrupt 0 (EINT0)                           */
#define NVIC_EINT1            35  /* External Interrupt 1 (EINT1)                           */
#define NVIC_EINT2            36  /* External Interrupt 2 (EINT2)                           */
#define NVIC_EINT3            37  /* External Interrupt 3 (EINT3)                           */
#define NVIC_ADC              38  /* A/D Converter end of conversion                        */
#define NVIC_BOD              39  /* Brown Out detect                                       */
#define NVIC_USB              40  /* USB                                                    */
#define NVIC_CAN              41  /* CAN Common, CAN 0 Tx, CAN 0 Rx, CAN 1 Tx, CAN 1 Rx     */
#define NVIC_GP_DMA           42  /* IntStatus of DMA channel 0, IntStatus of DMA channel 1 */
#define NVIC_I2S              43  /* irq, dmareq1, dmareq2                                  */
#define NVIC_ETHR             44  /* Ethernet                                               */
#define NVIC_RIT              45  /* Repetitive Interrupt Timer                             */
#define NVIC_MC               46  /* Motor Control PWM                                      */
#define NVIC_QE               47  /* Quadrature Encoder                                     */
#define NVIC_PLL1             48  /* PLL1 Lock                                              */
#define NVIC_USB_ACT          49  /* USB Activity Interrupt                                 */
#define NVIC_CAN_ACT          50  /* CAN Activity Interrupt                                 */

#endif    /* __IOLPC1766_H */

/*###DDF-INTERRUPT-BEGIN###
Interrupt0   = NMI            0x08
Interrupt1   = HardFault      0x0C
Interrupt2   = MemManage      0x10
Interrupt3   = BusFault       0x14
Interrupt4   = UsageFault     0x18
Interrupt5   = SVC            0x2C
Interrupt6   = DebugMon       0x30
Interrupt7   = PendSV         0x38
Interrupt8   = SysTick        0x3C
Interrupt9   = WDT            0x40
Interrupt10  = TIMER0         0x44
Interrupt11  = TIMER1         0x48
Interrupt12  = TIMER2         0x4C
Interrupt13  = TIMER3         0x50
Interrupt14  = UART0          0x54
Interrupt15  = UART1          0x58
Interrupt16  = UART2          0x5C
Interrupt17  = UART3          0x60
Interrupt18  = PWM1           0x64
Interrupt19  = I2C0           0x68
Interrupt20  = I2C1           0x6C
Interrupt21  = I2C2           0x70
Interrupt22  = SPI            0x74
Interrupt23  = SSP0           0x78
Interrupt24  = SSP1           0x7C
Interrupt25  = PLL0           0x80
Interrupt26  = RTC            0x84
Interrupt27  = EINT0          0x88
Interrupt28  = EINT1          0x8C
Interrupt29  = EINT2          0x90
Interrupt30  = EINT3          0x94
Interrupt31  = ADC            0x98
Interrupt32  = BOR            0x9C
Interrupt33  = USB            0xA0
Interrupt34  = CAN            0xA4
Interrupt35  = GPDMA          0xA8
Interrupt36  = I2S            0xAC
Interrupt37  = ETHR           0xB0
Interrupt38  = RIT            0xB4
Interrupt39  = MC             0xB8
Interrupt40  = QE             0xBC
Interrupt41  = PLL1           0xC0
Interrupt42  = USB_ACT        0xC4
Interrupt43  = CAN_ACT        0xC8
###DDF-INTERRUPT-END###*/
