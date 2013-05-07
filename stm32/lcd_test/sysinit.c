#include "stm32f10x.h"

void SystemInit(void); //called from crt0.s

void SystemInit()
{ //sets clock to 72MHz - no error checks - assumes 8MHz xtal
  FLASH->ACR = FLASH_ACR_PRFTBE | FLASH_ACR_LATENCY_2;
  RCC->CR |= RCC_CR_HSEON;
  while ((RCC->CR & RCC_CR_HSERDY) == 0);
  //RCC->CFGR = RCC_CFGR_PLLMULL9 | RCC_CFGR_PLLSRC_HSE | RCC_CFGR_PPRE1_DIV2; 
  RCC->CFGR = RCC_CFGR_PLLMULL2 | RCC_CFGR_PLLSRC_HSE | RCC_CFGR_PPRE1_DIV2; 
  RCC->CR |= RCC_CR_PLLON;
  while ((RCC->CR & RCC_CR_PLLRDY) == 0);
  RCC->CFGR |= RCC_CFGR_SW_PLL;
}
// for simplest blinky example, eliminate this file and include
// void SystemInit(void) { __NOP();} 
// in main.c

// for correct behavior per CMSIS, replace this file with
// CMSIS/Device/ST/STM32F10x/Source/Templates/system_stm32f10x.c
