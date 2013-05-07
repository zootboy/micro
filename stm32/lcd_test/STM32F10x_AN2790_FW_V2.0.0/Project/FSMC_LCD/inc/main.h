/**
  ******************************************************************************
  * @file FSMC_LCD/inc/main.h 
  * @author   MCD Application Team
  * @version  V2.0.0
  * @date     04/27/2009
  * @brief    Header for main.c module
  ******************************************************************************
  * @copy
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2009 STMicroelectronics</center></h2>
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

/* Includes ------------------------------------------------------------------*/
#include "stm3210e_lcd.h"
#include "stm32f10x_it.h"
#include "menu.h"
#include "sdcard.h"
#include "fsmc_sram.h"
#include "fsmc_nand.h"
#include "fsmc_nor.h"
#include <stdio.h>
#include <string.h>

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void STM32_LCD_Demo(void);
void InterruptConfig(void);
void RCC_Config(void);
void NVIC_Config(void);
void GPIO_Config(void);
void SysTick_Configuration(void);
void Delay(uint32_t nCount);
uint32_t DelayJoyStick(uint32_t nTime);
void Decrement_TimingDelay(void);
void Set_SELStatus(void);
void CheckBitmapFilesStatus(void);
void IntExtOnOffConfig(FunctionalState NewState);
void ADC_Config(void);

#endif /* __MAIN_H */

/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/
