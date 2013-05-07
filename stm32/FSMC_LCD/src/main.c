/**
  ******************************************************************************
  * @file FSMC_LCD/src/main.c 
  * @author   MCD Application Team
  * @version  V2.0.0
  * @date     04/27/2009
  * @brief    Main program body
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
/** @addtogroup FSMC_LCD
  * @{
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "misc.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_exti.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_adc.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static __IO ErrorStatus HSEStartUpStatus = SUCCESS;
static __IO uint32_t TimingDelay = 0;
static __IO uint32_t SELStatus = 0;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval : None
  */
int main(void)
{
  /* Intialize the STM32 LCD Demo */
  STM32_LCD_Demo();

  /* Infinite loop */
  while(1)
  {
    /* If SEL pushbutton is pressed */
    if(SELStatus == 1)
    {
      /* External Interrupt Disable */
      IntExtOnOffConfig(DISABLE);

      /* Execute Sel Function */
      SelFunc();

      /* External Interrupt Enable */
      IntExtOnOffConfig(ENABLE);

      /* Reset SELStatus value */
      SELStatus = 0;
    } 
  }
}

/**
  * @brief  Intializes the STM32 LCD Demo.
  * @param  None
  * @retval : None
  */
void STM32_LCD_Demo(void)
{
  /* Setup STM32 system (clock, PLL and Flash configuration) */
  SystemInit();

  /* Enable GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, GPIOF, GPIOG and AFIO clocks */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB |RCC_APB2Periph_GPIOC 
         | RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOE | RCC_APB2Periph_GPIOF | RCC_APB2Periph_GPIOG 
         | RCC_APB2Periph_AFIO | RCC_APB2Periph_ADC1, ENABLE);
  
  /* DMA1 and DMA2 clock enable */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1 | RCC_AHBPeriph_DMA2, ENABLE);
 
/*------------------- Resources Initialization -----------------------------*/
  /* GPIO Configuration */
  GPIO_Config();

  /* ADC Configuration */
  ADC_Config();

  /* Interrupt Configuration */
  InterruptConfig();

  /* Configure the systick */    
  SysTick_Configuration();

/*------------------- Drivers Initialization -------------------------------*/
  /* Initialize the LCD */
  STM3210E_LCD_Init();

  /* Clear the LCD */ 
  LCD_Clear(White);
  
  /* Checks the availability of the bitmap files */
  CheckBitmapFilesStatus();
  
  /* Display the STM32 LCD Demo introduction */
  STM32_LCD_DemoIntro();

  /* Clear the LCD */ 
  LCD_Clear(White);

  /* Set the LCD Back Color */
  LCD_SetBackColor(Blue);

  /* Set the LCD Text Color */
  LCD_SetTextColor(White);
  
  /* Initialize the Menu */
  Menu_Init();

  /* Display the main menu icons */
  ShowMenuIcons();
}

/**
  * @brief  Configures the used IRQ Channels and sets their priority.
  * @param  None
  * @retval : None
  */
void InterruptConfig(void)
{ 
  NVIC_InitTypeDef NVIC_InitStructure;

  /* Set the Vector Table base address at 0x08000000 */
  NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x00);

  /* Configure the Priority Group to 2 bits */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

  /* Configure the SysTick handler priority */
  NVIC_SetPriority(SysTick_IRQn, 0x0);

  /* Enable the EXTI3 Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  /* Enable the EXTI9_5 Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  
  /* Enable the EXTI15_10 Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  /* Enable DMA channel3 IRQ Channel */
  NVIC_InitStructure.NVIC_IRQChannel =  DMA1_Channel3_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  NVIC_InitStructure.NVIC_IRQChannel = SDIO_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  
}

/**
  * @brief  Configure a SysTick Base time to 10 ms.
  * @param  None
  * @retval : None
  */
void SysTick_Configuration(void)
{
  /* Setup SysTick Timer for 10 msec interrupts  */
  if (SysTick_Config(SystemCoreClock / 100))
  { 
    /* Capture error */ 
    while (1);
  }
}

/**
  * @brief  Enables or disables EXTI for the menu navigation keys :
  *   EXTI lines 3, 7 and 15 which correpond respectively
  *   to "DOWN", "SEL" and "UP".
  * @param wState: New state of the navigation keys. This parameter
  *   can be: ENABLE or DISABLE.
  * @retval : None
  */
void IntExtOnOffConfig(FunctionalState NewState)
{
  EXTI_InitTypeDef EXTI_InitStructure;

  /* Initializes the EXTI_InitStructure */
  EXTI_StructInit(&EXTI_InitStructure);

  /* Disable the EXTI line 3, 7 and 15 on falling edge */
  if(NewState == DISABLE)
  {
    EXTI_InitStructure.EXTI_Line = EXTI_Line3 | EXTI_Line7 | EXTI_Line15;
    EXTI_InitStructure.EXTI_LineCmd = DISABLE;
    EXTI_Init(&EXTI_InitStructure);
  }
  /* Enable the EXTI line 3, 7 and 15 on falling edge */
  else
  {
    /* Clear the the EXTI line 3, 7 and 15 interrupt pending bit */
    EXTI_ClearITPendingBit(EXTI_Line3 | EXTI_Line7 | EXTI_Line15);

    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Line = EXTI_Line3 | EXTI_Line7 | EXTI_Line15;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);
  }
}

/**
  * @brief  Configures the different GPIO ports pins.
  * @param  None
  * @retval : None
  */
void GPIO_Config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  /* Configure PG.07, PG.08, PG.13, PG.14 and PG.15 as input floating */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOG, &GPIO_InitStructure);

  /* Configure PD.03 as input floating */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOD, &GPIO_InitStructure);

  /* RIGHT Button */
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOG, GPIO_PinSource13);

  /* LEFT Button */
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOG, GPIO_PinSource14);

  /* DOWN Button */
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOD, GPIO_PinSource3);

  /* UP Button */
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOG, GPIO_PinSource15);

  /* SEL Button */
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOG, GPIO_PinSource7);

  /* KEY Button */
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOG, GPIO_PinSource8);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOG, &GPIO_InitStructure);

  /* Configure PC.04 (ADC Channel14) as analog input -------------------------*/
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
  GPIO_Init(GPIOC, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOF, &GPIO_InitStructure);
  GPIO_SetBits(GPIOF, GPIO_Pin_6);
}

/**
  * @brief  Inserts a delay time.
  * @param ount: specifies the delay time length (time base 10 ms).
  * @retval : None
  */
void Delay(uint32_t nCount)
{
  TimingDelay = nCount;
 
  while(TimingDelay != 0)
  {
  }
}

/**
  * @brief  Inserts a delay time while no joystick no key is pressed.
  * @param ount: specifies the delay time length (time base 10 ms).
  * @retval : JoyStick Pressed key.
  */
uint32_t DelayJoyStick(uint32_t nTime)
{
  __IO uint32_t keystate = 0;

  TimingDelay = nTime;
  
  keystate = ReadKey();
  
  while((TimingDelay != 0) && (keystate == NOKEY))
  {
    keystate = ReadKey();
  }
  return keystate;
}

/**
  * @brief  Decrements the TimingDelay variable.
  * @param  None
  * @retval : None
  */
void Decrement_TimingDelay(void)
{
  if (TimingDelay != 0x00)
  {
    TimingDelay--;
  }
}

/**
  * @brief  Checks the bitmap files availability and display a warning 
  *   message if these files doesn't exit.
  * @param  None
  * @retval : None
  */
void CheckBitmapFilesStatus(void)
{
  /* Checks if the Bitmap files are loaded */
  if(CheckBitmapFiles() != 0)
  {
    /* Set the LCD Back Color */
    LCD_SetBackColor(Blue);

    /* Set the LCD Text Color */
    LCD_SetTextColor(White);    
    LCD_DisplayStringLine(Line0, "      Warning       ");
    LCD_DisplayStringLine(Line1, "No loaded Bitmap    ");
    LCD_DisplayStringLine(Line2, "files. LCD Demo     ");
    LCD_DisplayStringLine(Line3, "can't be executed.  ");
    LCD_DisplayStringLine(Line4, "Please make sure    ");
    LCD_DisplayStringLine(Line5, "that all files are  ");
    LCD_DisplayStringLine(Line6, "correctly programmed");
    LCD_DisplayStringLine(Line7, "in the NOR FLASH and");
    LCD_DisplayStringLine(Line8, "restart the Demo.   ");
    LCD_DisplayStringLine(Line9, "                    ");
       
    /* Deinitializes the RCC */
    RCC_DeInit();
    
    /* Demo Can't Start */
    while(1)
    {
    }
  }
}

/**
  * @brief  Configure the ADC1.
  * @param  None
  * @retval : None
  */
void ADC_Config(void)
{
  ADC_InitTypeDef ADC_InitStructure;

  /* ADC1 configuration ------------------------------------------------------*/
  ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
  ADC_InitStructure.ADC_ScanConvMode = ENABLE;
  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  ADC_InitStructure.ADC_NbrOfChannel = 1;
  ADC_Init(ADC1, &ADC_InitStructure);

  /* ADC1 regular channel14 configuration */ 
  ADC_RegularChannelConfig(ADC1, ADC_Channel_14, 1, ADC_SampleTime_55Cycles5);
 
  /* Enable ADC1 */
  ADC_Cmd(ADC1, ENABLE);
 
  /* Start ADC1 Software Conversion */ 
  ADC_SoftwareStartConvCmd(ADC1, ENABLE);
}

/**
  * @brief  Sets the SELStatus variable.
  * @param  None
  * @retval : None
  */
void Set_SELStatus(void)
{
  SELStatus = 1;
}

#ifdef USE_FULL_ASSERT


/**
  *   Description:    : Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param file: pointer to the source file name
  * @param line: assert_param error line source number
  * @retval : None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */ 

/**
  * @}
  */ 

/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/
