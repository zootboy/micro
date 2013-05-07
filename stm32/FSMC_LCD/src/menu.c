/**
  ******************************************************************************
  * @file FSMC_LCD/src/menu.c 
  * @author   MCD Application Team
  * @version  V2.0.0
  * @date     04/27/2009
  * @brief    This file includes the menu navigation driver for the
  *           STM3210E-EVAL demonstration.
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
#include <stdio.h>
#include <string.h>
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_sdio.h"
#include "stm32f10x_dma.h"
#include "stm32f10x_flash.h"
#include "misc.h"
/* Private typedef -----------------------------------------------------------*/
typedef void (* tMenuFunc)(void);
typedef struct sMenuItem * tMenuItem;
typedef struct sMenu * tMenu;

/* Private define ------------------------------------------------------------*/
#define NumberOfIcons        5

#define BlockSize            512 /* Block Size in Bytes */
#define BufferWordsSize      (BlockSize >> 2)

#define Bank1_SRAM_ADDR      0x68000000
#define Bank1_NOR_ADDR       0x64000000
#define LCD_RAM_ADDR         0x6C000002
#define Bank1_NAND_ADDR      0x70000000
#define START_ADDR           0x08019000
#define FLASH_PAGE_SIZE      0x800

#define NAND_OK   0
#define NAND_FAIL 1
#define MAX_PHY_BLOCKS_PER_ZONE  1024
#define MAX_LOG_BLOCKS_PER_ZONE  1000

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint8_t MenuItemIndex = 0, nMenuLevel = 0;
uint8_t ItemNumb[MAX_MENU_LEVELS];

tMenuItem psMenuItem, psCurrentMenuItem;
tMenu psPrevMenu[MAX_MENU_LEVELS];
tMenu psCurrentMenu;

struct sMenuItem
{
  uint8_t* pszTitle;
  tMenuFunc pfMenuFunc;
  tMenuFunc pfUpDownMenuFunc;
  tMenu psSubMenu;
};

struct sMenu
{
  uint8_t* pszTitle;
  tMenuItem psItems;
  uint8_t nItems;
};

typedef struct __SPARE_AREA
{
  uint16_t LogicalIndex;
  uint16_t DataStatus;
  uint16_t BlockStatus;
} SPARE_AREA;

SD_CardInfo SDCardInfo;
NOR_IDTypeDef NOR_ID;
SD_Error Status = SD_OK;
NAND_ADDRESS wAddress;

extern __IO uint32_t DMAComplete;
extern __IO uint32_t FirstEntry;

uint32_t Buffer_Block_Rx[BufferWordsSize * 20];
uint8_t pBuffer[16384], TxBuffer[256];
__IO uint32_t DMASourceAddress = 0;
__IO uint32_t fractionaltimeunits = 0;

const uint32_t IconsAddr[] = {0x6404B084, 0x6404D0C6, 0x6404F108, 0x6405114A, 0x6405318C};
uint8_t SlidesCheck[6] = {0x42, 0x4D, 0x42, 0x58, 0x02, 0x00};
uint8_t Icons64Check[6] = {0x42, 0x4D, 0x42, 0x20, 0x00, 0x00};

/*------------------------------ Menu level 4 -------------------------------*/

/*------------------------------ Menu level 3 -------------------------------*/

/*------------------------------ Menu level 2 -------------------------------*/

struct sMenuItem SDCardMenuItems[] = {{" Copy images in SD  ", CopyToSDCard, IdleFunc},
                                      {"  SD CARD->CPU->LCD ", SDCardToLCD, IdleFunc},
                                      {" SD CARD->LCD Speed ", SDCardToLCD_Speed, IdleFunc},
                                      {"       Return       ", ReturnFunc, IdleFunc}};
struct sMenu SDCardMenu = {"      SD Card       ", SDCardMenuItems, countof(SDCardMenuItems)};

struct sMenuItem NANDFlashMenuItems[] = {{"Copy images in NAND ", CopyToNANDFlash, IdleFunc},
                                         {"  NAND ->CPU->LCD   ", NANDFlashToLCD, IdleFunc},
                                         {"   NAND->LCD Speed  ", NANDFlashToLCD_Speed, IdleFunc},
                                         {"NAND Physical Format", NAND_PhysicalErase, IdleFunc},
                                         {"       Return       ", ReturnFunc, IdleFunc}};
struct sMenu NANDFlashMenu = {"      NAND FLASH    ", NANDFlashMenuItems, countof(NANDFlashMenuItems)};

struct sMenuItem ExternalSRAMMenuItems[] = {{"Copy images in SRAM ", CopyToExternalSRAM, IdleFunc},
                                            {" EXT SRAM->CPU->LCD ", ExternalSRAMToLCD, IdleFunc},
                                            {" EXT SRAM->DMA->LCD ", ExternalSRAMToLCD_DMA, IdleFunc},
                                            {"EXT SRAM->LCD Speed ", ExternalSRAMToLCD_Speed, IdleFunc},
                                            {"       Return       ", ReturnFunc, IdleFunc}};
struct sMenu ExternalSRAMMenu = {"    External SRAM   ", ExternalSRAMMenuItems, countof(ExternalSRAMMenuItems)};


struct sMenuItem NORFlashMenuItems[] = {{" NOR FLASH->CPU->LCD", NORFlashToLCD, IdleFunc},
                                        {" NOR FLASH->DMA->LCD", NORFlashToLCD_DMA, IdleFunc},
                                        {"NOR FLASH->LCD Speed", NORFlashToLCD_Speed, IdleFunc},
                                        {"       Return       ", ReturnFunc, IdleFunc}};
struct sMenu NORFlashMenu = {"      NOR FLASH     ", NORFlashMenuItems, countof(NORFlashMenuItems)};

struct sMenuItem InternalFlashMenuItems[] = {{"Copy images in FLASH", CopyToInternalFlash, IdleFunc},
                                             {"INT FLASH->CPU->LCD ", InternalFlashToLCD, IdleFunc},
                                             {"INT FLASH->DMA->LCD ", InternalFlashToLCD_DMA, IdleFunc},
                                             {"INT FLASH->LCD Speed", InternalFlashToLCD_Speed, IdleFunc},
                                             {"       Return       ", ReturnFunc, IdleFunc}};
struct sMenu InternalFlashMenu = {"    Internal FLASH  ", InternalFlashMenuItems, countof(InternalFlashMenuItems)};

/*------------------------------ Menu level 1 -------------------------------*/
struct sMenuItem MainMenuItems[] = {
  {"    Internal FLASH  ", IdleFunc, IdleFunc, &InternalFlashMenu},
  {"      NOR FLASH     ", IdleFunc, IdleFunc, &NORFlashMenu},
  {"    External SRAM   ", IdleFunc, IdleFunc, &ExternalSRAMMenu},
  {"      NAND FLASH    ", IdleFunc, IdleFunc, &NANDFlashMenu},
  {"      SD Card       ", IdleFunc, IdleFunc, &SDCardMenu},
};
struct sMenu MainMenu = {"     Main menu      ", MainMenuItems, countof(MainMenuItems)};

/* Private function prototypes -----------------------------------------------*/
static uint8_t Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t BufferLength);
static SD_Error LCD_SDDisplay(uint32_t address);
static SD_Error LCD_WriteSD(uint32_t address, uint32_t *pointer);
static uint32_t LCD_NANDDisplay(uint32_t address);
static void LCD_WriteDMA(uint32_t address);
static uint16_t NAND_Write(uint32_t Memory_Offset, uint8_t *Writebuff, uint16_t Transfer_Length);
static uint16_t NAND_Read(uint32_t Memory_Offset, uint8_t *Readbuff, uint16_t Transfer_Length);
static NAND_ADDRESS NAND_GetAddress (uint32_t Address);
static SPARE_AREA ReadSpareArea (uint32_t address);
static NAND_ADDRESS NAND_ConvertPhyAddress (uint32_t Address);
static void Media_BufferRead(uint8_t* pBuffer, uint32_t ReadAddr, uint16_t NumByteToRead);
static uint32_t InternalFlashCheckBitmapFiles(void);
static uint32_t ExternalSRAMCheckBitmapFiles(void);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Initializes the navigation menu.
  * @param  None
  * @retval : None
  */
void Menu_Init(void)
{
  psCurrentMenu = &MainMenu;
  psPrevMenu[nMenuLevel] = psCurrentMenu;
  psMenuItem = MainMenuItems;
}

/**
  * @brief  Displays the current menu.
  * @param  None
  * @retval : None
  */
void DisplayMenu(void)
{
  uint32_t Line = 0, index = 0;
  tMenuItem psMenuItem2;

  /* Set the Back Color */
  LCD_SetBackColor(Blue);
  /* Set the Text Color */
  LCD_SetTextColor(White);

  /* Clear the LCD Screen */
  LCD_Clear(White);

  LCD_DisplayStringLine(Line, psCurrentMenu->pszTitle);
  Line += 24;

  /* Set the Back Color */
  LCD_SetBackColor(White);

  /* Set the Text Color */
  LCD_SetTextColor(Blue);

  while(!(index >= (psCurrentMenu->nItems)))
  {
    psMenuItem2 = &(psCurrentMenu->psItems[index]);
    LCD_DisplayStringLine(Line, psMenuItem2->pszTitle);
    index++;
    Line += 24;
  }
  /* Set the Back Color */
  LCD_SetBackColor(Green);

  /* Set the Text Color */
  LCD_SetTextColor(White);

  /* Get the current menu */
  psMenuItem = &(psCurrentMenu->psItems[MenuItemIndex]);

  LCD_DisplayStringLine(((MenuItemIndex + 1) * 24), psMenuItem->pszTitle);
}

/**
  * @brief  This function is executed when "SEL" push-buttton is pressed.
  * @param  None
  * @retval : None
  */
void SelFunc(void)
{
  psCurrentMenuItem = psMenuItem;

  if(psMenuItem->psSubMenu != '\0')
  {
    /* Update the current Item by the submenu */
    MenuItemIndex = 0;
    psCurrentMenu = psMenuItem->psSubMenu;
    psMenuItem = &(psCurrentMenu->psItems)[MenuItemIndex];
    DisplayMenu();
    nMenuLevel++;
    psPrevMenu[nMenuLevel] = psCurrentMenu;
  } 
  psCurrentMenuItem->pfMenuFunc();
}

/**
  * @brief  This function is executed when any of "UP" push-butttons
  *   is pressed.
  * @param  None
  * @retval : None
  */
void UpFunc(void)
{
  /* Set the Back Color */
  LCD_SetBackColor(White);
  /* Set the Text Color */
  LCD_SetTextColor(Blue);
  psMenuItem = &psCurrentMenu->psItems[MenuItemIndex];
  LCD_DisplayStringLine(((MenuItemIndex + 1) * 24), psMenuItem->pszTitle);

  if(MenuItemIndex > 0)
  {
    MenuItemIndex--;
  }
  else
  {
    MenuItemIndex = psCurrentMenu->nItems - 1;
  }
  /* Set the Back Color */
  LCD_SetBackColor(Green);
  /* Set the Text Color */
  LCD_SetTextColor(White);
  psMenuItem = &psCurrentMenu->psItems[MenuItemIndex];
  LCD_DisplayStringLine(((MenuItemIndex + 1) * 24), psMenuItem->pszTitle);
  ItemNumb[nMenuLevel] = MenuItemIndex;
}

/**
  * @brief  This function is executed when any of "Down" push-butttons
  *   is pressed.
  * @param  None
  * @retval : None
  */
void DownFunc(void)
{
  /* Set the Back Color */
  LCD_SetBackColor(White);
  /* Set the Text Color */
  LCD_SetTextColor(Blue);
  psMenuItem = &psCurrentMenu->psItems[MenuItemIndex];
  LCD_DisplayStringLine(((MenuItemIndex + 1) * 24), psMenuItem->pszTitle);
      
  /* Test on the MenuItemIndex value before incrementing it */
  if(MenuItemIndex >= ((psCurrentMenu->nItems)-1))
  {
    MenuItemIndex = 0;
  }
  else
  {
    MenuItemIndex++;
  }
  /* Set the Back Color */
  LCD_SetBackColor(Green);
  /* Set the Text Color */
  LCD_SetTextColor(White);
  /* Get the current menu */
  psMenuItem = &(psCurrentMenu->psItems[MenuItemIndex]);
  LCD_DisplayStringLine(((MenuItemIndex + 1) * 24), psMenuItem->pszTitle);
  ItemNumb[nMenuLevel] = MenuItemIndex;
}

/**
  * @brief  This function is executed when the "RETURN" menu is selected.
  * @param  None
  * @retval : None
  */
void ReturnFunc(void)
{
  psMenuItem->pfUpDownMenuFunc();

  if(nMenuLevel == 0)
  {
    nMenuLevel++;
  }

  psCurrentMenu = psPrevMenu[nMenuLevel-1];
  psMenuItem = &psCurrentMenu->psItems[0];
  ItemNumb[nMenuLevel] = 0;
  MenuItemIndex = 0;
  nMenuLevel--;

  if(nMenuLevel != 0)
  {
    DisplayMenu();
  }
  else
  {
    ShowMenuIcons();
  }
}

/**
  * @brief  Reads key from demoboard.
  * @param  None
  * @retval : Return RIGHT, LEFT, SEL, UP, DOWN or NOKEY
  */
uint8_t ReadKey(void)
{
  /* "right" key is pressed */
  if(!GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_13))
  {
    while(GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_13) == Bit_RESET)
    {
    } 
    return RIGHT; 
  }	
  /* "left" key is pressed */
  if(!GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_14))
  {
    while(GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_14) == Bit_RESET)
    {
    }
    return LEFT; 
  }
  /* "up" key is pressed */
  if(!GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_15))
  {
    while(GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_15) == Bit_RESET)
    {
    }
    return UP; 
  }
  /* "down" key is pressed */
  if(!GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_3))
  {
    while(GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_3) == Bit_RESET)
    {
    } 
    return DOWN; 
  }
  /* "sel" key is pressed */
  if(!GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_7))
  {
    while(GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_7) == Bit_RESET)
    {
    } 
    return SEL; 
  }
  /* "KEY" key is pressed */
  if(!GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_8))
  {
    while(GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_8) == Bit_RESET)
    {
    } 
    return KEY; 
  }
  /* No key is pressed */
  else 
  {
    return NOKEY;
  }
}

/**
  * @brief  Idle function.
  * @param  None
  * @retval : None
  */
void IdleFunc(void)
{
  /* Nothing to execute: return */
  return;
}

/**
  * @brief  Display menu icons.
  * @param  None
  * @retval : None
  */
void DisplayIcons(void)
{
  uint32_t i = 0, j = 0, l = 0,  iconline = 0, iconcolumn = 0;
  
  iconline = 98;
  iconcolumn = 290 ;
    
  for(i = 0; i < 3; i++)
  {
    for(j = 0; j < 4; j++)
    {
      RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC, ENABLE); 
      LCD_SetDisplayWindow(iconline, iconcolumn, 64, 64);
      RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC, DISABLE); 
      LCD_NORDisplay(IconsAddr[l]);
      iconcolumn -= 65;
      l++;
      if(l == NumberOfIcons)
      {
        return;
      }
    }
    iconline += 65;
    iconcolumn = 290;
  }
}

/**
  * @brief  Show the main menu icon.
  * @param  None
  * @retval : None
  */
void ShowMenuIcons(void)
{
  uint32_t MyKey = 0, i = 0;  
  uint16_t IconRect[12][2] ={{34, 290}, {34, 225}, {34, 160}, {34, 95},
                       {99, 290}, {99, 225}, {99, 160}, {99, 95},
                       {164, 290}, {164, 225}, {164, 160}, {164, 95}};

  /* Disable the JoyStick interrupts */
  IntExtOnOffConfig(DISABLE);

  while(ReadKey() != NOKEY)
  {
  }

  /* Initializes the Menu state machine */
  Menu_Init();

  MenuItemIndex = 0;
  
  /* Clear*/
  LCD_Clear(White);

  /* Set the Back Color */
  LCD_SetBackColor(Blue);

  /* Set the Text Color */
  LCD_SetTextColor(White);

  LCD_DisplayStringLine(Line0, psMenuItem->pszTitle);
  
  /* Set the Back Color */
  LCD_SetBackColor(White);

  /* Set the Text Color */
  LCD_SetTextColor(Blue);

  /* Displays Icons */    
  DisplayIcons();

  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC, ENABLE);
  /* Disable LCD Window mode */
  LCD_WindowModeDisable(); 


  LCD_DrawRect(IconRect[0][0], IconRect[0][1], 64, 65);

  while(GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_13) == RESET)
  {
  }
  /* Endless loop */
  while(1)
  {
    /* Check which key is pressed */
    MyKey = ReadKey();

    /* If "UP" pushbutton is pressed */
    if(MyKey == UP)
    {
      /* Set the Text Color */
      LCD_SetTextColor(White);

      LCD_DrawRect(IconRect[i][0], IconRect[i][1], 64, 65);

      if(i <= 3)
      {
        i += 8;
        if(i >= NumberOfIcons)
        {
          i = (NumberOfIcons - 1);
        }
      }
      else
      {
        i -= 4;
      }
      /* Set the Text Color */
      LCD_SetTextColor(Blue);
      LCD_DrawRect(IconRect[i][0], IconRect[i][1], 64, 65);

      /* Set the Back Color */
      LCD_SetBackColor(Blue);
      /* Set the Text Color */
      LCD_SetTextColor(White);
      /* Test on the MenuItemIndex value before incrementing it */
      if(MenuItemIndex <= 3)
      {
        MenuItemIndex += 8;
        if(MenuItemIndex >= NumberOfIcons)
        {
          MenuItemIndex = (NumberOfIcons - 1);
        }
      }
      else
      {
        MenuItemIndex -= 4;
      }
      /* Get the current menu */
      psMenuItem = &(psCurrentMenu->psItems[MenuItemIndex]);
      LCD_DisplayStringLine(Line0, psMenuItem->pszTitle);
      ItemNumb[nMenuLevel] = MenuItemIndex;
    }
    /* If "DOWN" pushbutton is pressed */
    if(MyKey == DOWN)
    {
      /* Set the Text Color */
      LCD_SetTextColor(White);
      LCD_DrawRect(IconRect[i][0], IconRect[i][1], 64, 65);
      if(i >= 8)
      {
        i -= 8;
      }
      else
      {
        i += 4;
        if(i >= NumberOfIcons)
        {
          i = (NumberOfIcons - 1);
        }
      }
      /* Set the Text Color */
      LCD_SetTextColor(Blue);
      LCD_DrawRect(IconRect[i][0], IconRect[i][1], 64, 65);

      /* Set the Back Color */
      LCD_SetBackColor(Blue);
      /* Set the Text Color */
      LCD_SetTextColor(White);
      /* Test on the MenuItemIndex value before incrementing it */
      if(MenuItemIndex >= 8)
      {
        MenuItemIndex -= 8;
      }
      else
      {
        MenuItemIndex += 4;
        if(MenuItemIndex >= NumberOfIcons)
        {
          MenuItemIndex = (NumberOfIcons - 1);
        }
      }
      /* Get the current menu */
      psMenuItem = &(psCurrentMenu->psItems[MenuItemIndex]);
      LCD_DisplayStringLine(Line0, psMenuItem->pszTitle);
      ItemNumb[nMenuLevel] = MenuItemIndex;
    }
    /* If "LEFT" pushbutton is pressed */
    if(MyKey == LEFT)
    {
      /* Set the Text Color */
      LCD_SetTextColor(White);
      LCD_DrawRect(IconRect[i][0], IconRect[i][1], 64, 65);
      if(i == 0)
      {
        i = (NumberOfIcons - 1);
      }
      else
      {
        i--;
      }
      /* Set the Text Color */
      LCD_SetTextColor(Blue);
      LCD_DrawRect(IconRect[i][0], IconRect[i][1], 64, 65);

      /* Set the Back Color */
      LCD_SetBackColor(Blue);
      /* Set the Text Color */
      LCD_SetTextColor(White);
      if(MenuItemIndex > 0)
      {
        MenuItemIndex--;
      }
      else
      {
        MenuItemIndex = psCurrentMenu->nItems - 1;
      }

      psMenuItem = &psCurrentMenu->psItems[MenuItemIndex];
      LCD_DisplayStringLine(Line0, psMenuItem->pszTitle);
      ItemNumb[nMenuLevel] = MenuItemIndex;
    }
    /* If "RIGHT" pushbutton is pressed */
    if(MyKey == RIGHT)
    {
      /* Set the Text Color */
      LCD_SetTextColor(White);
      LCD_DrawRect(IconRect[i][0], IconRect[i][1], 64, 65);
      if(i == (NumberOfIcons - 1))
      {
        i = 0x00;
      }
      else
      {
        i++;
      }
      /* Set the Text Color */
      LCD_SetTextColor(Blue);
      LCD_DrawRect(IconRect[i][0], IconRect[i][1], 64, 65);

      /* Set the Back Color */
      LCD_SetBackColor(Blue);
      /* Set the Text Color */
      LCD_SetTextColor(White);
      /* Test on the MenuItemIndex value before incrementing it */
      if(MenuItemIndex >= ((psCurrentMenu->nItems) - 1))
      {
        MenuItemIndex = 0;
      }
      else
      {
        MenuItemIndex++;
      }
      /* Get the current menu */
      psMenuItem = &(psCurrentMenu->psItems[MenuItemIndex]);
      LCD_DisplayStringLine(Line0, psMenuItem->pszTitle);
      ItemNumb[nMenuLevel] = MenuItemIndex;
    }
    /* If "SEL" pushbutton is pressed */
    if(MyKey == SEL)
    {
      SelFunc();
      IntExtOnOffConfig(ENABLE);
      return;
    }
  }
}

/**
  * @brief  Display a picture from the NOR Flash.
  * @param  None
  * @retval : None
  */
void LCD_NORDisplay(uint32_t address)
{
  /* Write/read to/from FSMC SRAM memory  *************************************/
  /* Enable the FSMC Clock */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC, ENABLE);
  
  /* Configure FSMC Bank1 NOR/SRAM2 */
  FSMC_NOR_Init();
  
  /* Read NOR memory ID */
  FSMC_NOR_ReadID(&NOR_ID);

  FSMC_NOR_ReturnToReadMode();

  /* Slide nÝ: index */
  LCD_WriteBMP(address);
}

/**
  * @brief  Display the STM32 LCD Demo introduction.
  * @param  None
  * @retval : None
  */
void STM32_LCD_DemoIntro(void)
{
  LCD_SetDisplayWindow(239, 0x13F, 240, 320);
  LCD_NORDisplay(SLIDE1);
  Delay(100);
  
  LCD_SetDisplayWindow(239, 0x13F, 240, 320);
  LCD_NORDisplay(SLIDE2);  
  Delay(100);
}

/**
  * @brief  Display images from the internal FLASH on LCD.
  * @param  None
  * @retval : None
  */
void InternalFlashToLCD(void)
{
  IntExtOnOffConfig(DISABLE);
 
  while(ReadKey() != NOKEY)
  {
  }

  /* Clear the LCD */
  LCD_Clear(White);

  /* Checks if the Bitmap files are loaded */
  if(InternalFlashCheckBitmapFiles() != 0)
  {
    /* Set the LCD Back Color */
    LCD_SetBackColor(Blue);

    /* Set the LCD Text Color */
    LCD_SetTextColor(White);    
    LCD_DisplayStringLine(Line0, "      Warning       ");
    LCD_DisplayStringLine(Line1, "You need to copy    ");
    LCD_DisplayStringLine(Line2, "bitmap images in    ");
    LCD_DisplayStringLine(Line3, "internal FLASH.     ");

    LCD_DisplayStringLine(Line7, " Push JoyStick to   ");
    LCD_DisplayStringLine(Line8, "continue.           ");  
    while(ReadKey() == NOKEY)
    {
    }

    while(ReadKey() != NOKEY)
    {
    }

    LCD_Clear(White);
    DisplayMenu();
    IntExtOnOffConfig(ENABLE);
    return;
  }
  
  LCD_SetTextColor(Red);
  LCD_DisplayStringLine(Line4, " Push Key Button to ");
  LCD_DisplayStringLine(Line5, " start or stop.     ");


  /* Set the Text Color */
  LCD_SetTextColor(Blue);
  LCD_DisplayStringLine(Line1, "   LCD on FSMC Demo ");  
  LCD_DisplayStringLine(Line2, "    Internal FLASH  ");

  while(GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_8) != RESET)
  {
  }
  while(GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_8) == RESET)
  {
  }

  /* Set the LCD display window */
  LCD_SetDisplayWindow(239, 0x13F, 240, 320);

  /* Push key Push Button to exit */
  while(GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_8) != RESET)
  {
    GPIO_ResetBits(GPIOF, GPIO_Pin_6);

    /* Timing measurement base time config */
    TimingMeasurement_Config();
    
    /* Start timing counter: measure display time */
	SysTick->CTRL |= SysTick_CTRL_ENABLE;

    LCD_WriteBMP(START_ADDR);

    /* Stop timing counter */
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE;

    DisplayTimingCompute();

    GPIO_SetBits(GPIOF, GPIO_Pin_6);


    LCD_WriteBMP((START_ADDR + 0x25842));
  }

  while(ReadKey() != NOKEY)
  {
  }

  /* Clear the LCD */
  LCD_Clear(White);

  /* Set the Back Color */
  LCD_SetBackColor(White);

  /* Set the Text Color */
  LCD_SetTextColor(Blue);
  LCD_DisplayStringLine(Line1, "    Internal FLASH  ");
  sprintf((char*)TxBuffer,"Time = %d e-6 s  ", fractionaltimeunits);
  
  LCD_DisplayStringLine(Line2, TxBuffer);

  /* Set the Text Color */
  LCD_SetTextColor(Green);
  sprintf((char*)TxBuffer,"  %d fps (Frames per Second)", 1000000/fractionaltimeunits); 
  LCD_DisplayStringLine(Line3, TxBuffer);
  LCD_DisplayStringLine(Line4, "Second)");

  LCD_DisplayStringLine(Line6, "Press any Key to    ");
  LCD_DisplayStringLine(Line7, "continue.           ");

  while(ReadKey() == NOKEY)
  {
  }

  while(ReadKey() != NOKEY)
  {
  }

  LCD_Clear(White);
  DisplayMenu();
  IntExtOnOffConfig(ENABLE);
}

/**
  * @brief  Display images from the internal FLASH on LCD using DMA.
  * @param  None
  * @retval : None
  */
void InternalFlashToLCD_DMA(void)
{

  IntExtOnOffConfig(DISABLE);
 
  while(ReadKey() != NOKEY)
  {
  }
  
  /* Clear the LCD */
  LCD_Clear(White);

  /* Checks if the Bitmap files are loaded */
  if(InternalFlashCheckBitmapFiles() != 0)
  {
    /* Set the LCD Back Color */
    LCD_SetBackColor(Blue);

    /* Set the LCD Text Color */
    LCD_SetTextColor(White);    
    LCD_DisplayStringLine(Line0, "      Warning       ");
    LCD_DisplayStringLine(Line1, "You need to copy    ");
    LCD_DisplayStringLine(Line2, "bitmap images in    ");
    LCD_DisplayStringLine(Line3, "internal FLASH.     ");

    LCD_DisplayStringLine(Line7, " Push JoyStick to   ");
    LCD_DisplayStringLine(Line8, "continue.           ");  
    while(ReadKey() == NOKEY)
    {
    }

    while(ReadKey() != NOKEY)
    {
    }

    LCD_Clear(White);
    DisplayMenu();
    IntExtOnOffConfig(ENABLE);
    return;
  }

  LCD_SetTextColor(Red);
  LCD_DisplayStringLine(Line4, " Push Key Button to ");
  LCD_DisplayStringLine(Line5, " start or stop.     "); 

    /* Set the Text Color */
  LCD_SetTextColor(Blue);
  LCD_DisplayStringLine(Line1, "   LCD on FSMC Demo ");  
  LCD_DisplayStringLine(Line2, " Internal FLASH DMA ");

  while(GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_8) != RESET)
  {
  }
  while(GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_8) == RESET)
  {
  }

  /* Set the LCD display window */
  LCD_SetDisplayWindow(239, 0x13F, 240, 320);

  /* Push key Push Button to exit */
  while(GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_8) != RESET)
  {
    GPIO_ResetBits(GPIOF, GPIO_Pin_6);

    /* Timing measurement base time config */
    TimingMeasurement_Config();

    /* Start timing counter: measure display time */
	SysTick->CTRL |= SysTick_CTRL_ENABLE;

    LCD_WriteDMA(START_ADDR);

    /* Stop timing counter */
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE;

    DisplayTimingCompute();

    GPIO_SetBits(GPIOF, GPIO_Pin_6);

    LCD_WriteDMA((START_ADDR + 0x25842));
  }

  while(ReadKey() != NOKEY)
  {
  }

  /* Clear the LCD */
  LCD_Clear(White);
  /* Set the Back Color */
  LCD_SetBackColor(White);
  /* Set the Text Color */
  LCD_SetTextColor(Blue);

  LCD_DisplayStringLine(Line1, " Internal FLASH DMA ");
  sprintf((char*)TxBuffer,"Time = %d e-6 s  ", fractionaltimeunits);
  
  LCD_DisplayStringLine(Line2, TxBuffer);

  /* Set the Text Color */
  LCD_SetTextColor(Green);
  sprintf((char*)TxBuffer,"  %d fps (Frames per Second)", 1000000/fractionaltimeunits);  
  LCD_DisplayStringLine(Line3, TxBuffer);
  LCD_DisplayStringLine(Line4, "Second)");  

  LCD_DisplayStringLine(Line6, "Press any Key to    ");
  LCD_DisplayStringLine(Line7, "continue.           ");

  while(ReadKey() == NOKEY)
  {
  }

  while(ReadKey() != NOKEY)
  {
  }

  LCD_Clear(White);
  DisplayMenu();
  IntExtOnOffConfig(ENABLE);  
} 

/**
  * @brief  Display images from the internal FLASH on LCD using CPU
  *   with a controlled speed through the RV1 trimmer.
  * @param  None
  * @retval : None
  */
void InternalFlashToLCD_Speed(void)
{
  uint32_t keystate = 0;
  
  IntExtOnOffConfig(DISABLE);
 
  while(ReadKey() != NOKEY)
  {
  }

  /* Clear the LCD */
  LCD_Clear(White);

  /* Checks if the Bitmap files are loaded */
  if(InternalFlashCheckBitmapFiles() != 0)
  {
    /* Set the LCD Back Color */
    LCD_SetBackColor(Blue);

    /* Set the LCD Text Color */
    LCD_SetTextColor(White);    
    LCD_DisplayStringLine(Line0, "      Warning       ");
    LCD_DisplayStringLine(Line1, "You need to copy    ");
    LCD_DisplayStringLine(Line2, "bitmap images in    ");
    LCD_DisplayStringLine(Line3, "internal FLASH.     ");

    LCD_DisplayStringLine(Line7, " Push JoyStick to   ");
    LCD_DisplayStringLine(Line8, "continue.           ");  
    while(ReadKey() == NOKEY)
    {
    }

    while(ReadKey() != NOKEY)
    {
    }

    LCD_Clear(White);
    DisplayMenu();
    IntExtOnOffConfig(ENABLE);
    return;
  }
  
  /* Clear the LCD */
  LCD_Clear(White);
  
  LCD_SetTextColor(Red);
  LCD_DisplayStringLine(Line4, " Turn the Trimmer to");
  LCD_DisplayStringLine(Line5, " control the delay  ");
  LCD_DisplayStringLine(Line6, " between two frames.");
  LCD_DisplayStringLine(Line7, " Push Key Button to ");
  LCD_DisplayStringLine(Line8, " start or stop.     ");


  /* Set the Text Color */
  LCD_SetTextColor(Blue);
  LCD_DisplayStringLine(Line1, "   LCD on FSMC Demo ");  
  LCD_DisplayStringLine(Line2, "    Internal FLASH  ");

  while(GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_8) != RESET)
  {
  }
  while(GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_8) == RESET)
  {
  }

  /* Set the LCD display window */
  LCD_SetDisplayWindow(239, 0x13F, 240, 320);
  
  /* Configure the systick */    
  SysTick_Configuration();

  /* Push key Push Button to exit */
  while(keystate != KEY)
  {
    GPIO_ResetBits(GPIOF, GPIO_Pin_6);

    LCD_WriteBMP(START_ADDR);

    GPIO_SetBits(GPIOF, GPIO_Pin_6);
    keystate = DelayJoyStick(ADC_GetConversionValue(ADC1)/40);
    
    if(keystate == KEY)
    {
      break;
    }
    
    LCD_WriteBMP((START_ADDR + 0x25842));
    keystate = DelayJoyStick(ADC_GetConversionValue(ADC1)/40);
  }

  while(ReadKey() != NOKEY)
  {
  }

  /* Clear the LCD */
  LCD_Clear(White);

  LCD_DisplayStringLine(Line6, "Press any Key to    ");
  LCD_DisplayStringLine(Line7, "continue.           ");

  while(ReadKey() == NOKEY)
  {
  }

  while(ReadKey() != NOKEY)
  {
  }

  LCD_Clear(White);
  DisplayMenu();
  IntExtOnOffConfig(ENABLE);
}

/**
  * @brief  Display images from the NOR FLASH on LCD .
  * @param  None
  * @retval : None
  */
void NORFlashToLCD(void)
{
  IntExtOnOffConfig(DISABLE);
 
  while(ReadKey() != NOKEY)
  {
  }

  /* Clear the LCD */
  LCD_Clear(White);
  
  LCD_SetTextColor(Red);
  LCD_DisplayStringLine(Line4, " Push Key Button to ");
  LCD_DisplayStringLine(Line5, " start or stop.     ");
  
  /* Set the Text Color */
  LCD_SetTextColor(Blue);
  LCD_DisplayStringLine(Line1, "   LCD on FSMC Demo ");  
  LCD_DisplayStringLine(Line2, "      NOR FLASH     ");

  while(GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_8) != RESET)
  {
  }
  while(GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_8) == RESET)
  {
  }
  
   /* Write/read to/from FSMC SRAM memory  *************************************/
  /* Enable the FSMC Clock */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC, ENABLE);

  /* Configure FSMC Bank1 NOR/SRAM2 */
  FSMC_NOR_Init();
 
  /* Read NOR memory ID */
  FSMC_NOR_ReadID(&NOR_ID);

  FSMC_NOR_ReturnToReadMode();

  /* Set the LCD display window */
  LCD_SetDisplayWindow(239, 0x13F, 240, 320);

  /* Push key Push Button to exit */
  while(GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_8) != RESET)
  {
    GPIO_ResetBits(GPIOF, GPIO_Pin_6);

    /* Timing measurement base time config */
    TimingMeasurement_Config();

    /* Start timing counter: measure display time */
	SysTick->CTRL |= SysTick_CTRL_ENABLE;    

    LCD_WriteBMP(SLIDE1);

    /* Stop timing counter */
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE;

    DisplayTimingCompute();

    GPIO_SetBits(GPIOF, GPIO_Pin_6);

    LCD_WriteBMP(SLIDE2);
  }

  while(ReadKey() != NOKEY)
  {
  }

  /* Clear the LCD */
  LCD_Clear(White);
  /* Set the Back Color */
  LCD_SetBackColor(White);
  /* Set the Text Color */
  LCD_SetTextColor(Blue);

  LCD_DisplayStringLine(Line1, "      NOR FLASH     ");
  sprintf((char*)TxBuffer,"Time = %d e-6 s  ", fractionaltimeunits);
  
  LCD_DisplayStringLine(Line2, TxBuffer);

  /* Set the Text Color */
  LCD_SetTextColor(Green);
  sprintf((char*)TxBuffer,"  %d fps (Frames per Second)", 1000000/fractionaltimeunits);  
  LCD_DisplayStringLine(Line3, TxBuffer);
  LCD_DisplayStringLine(Line4, "Second)");
   
  LCD_DisplayStringLine(Line6, "Press any Key to    ");
  LCD_DisplayStringLine(Line7, "continue.           ");

  while(ReadKey() == NOKEY)
  {
  }

  while(ReadKey() != NOKEY)
  {
  }

  LCD_Clear(White);
  DisplayMenu();
  IntExtOnOffConfig(ENABLE);  
}

/**
  * @brief  Display images from the NOR FLASH on LCD using DMA.
  * @param  None
  * @retval : None
  */
void NORFlashToLCD_DMA(void)
{

  IntExtOnOffConfig(DISABLE);
 
  while(ReadKey() != NOKEY)
  {
  }

  /* Clear the LCD */
  LCD_Clear(White);
  
  LCD_SetTextColor(Red);
  LCD_DisplayStringLine(Line4, " Push Key Button to ");
  LCD_DisplayStringLine(Line5, " start or stop.     ");  
  
  /* Set the Text Color */
  LCD_SetTextColor(Blue);
  LCD_DisplayStringLine(Line1, "   LCD on FSMC Demo ");  
  LCD_DisplayStringLine(Line2, "    NOR FLASH DMA   ");

  while(GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_8) != RESET)
  {
  }
  while(GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_8) == RESET)
  {
  }

   /* Write/read to/from FSMC SRAM memory  *************************************/
  /* Enable the FSMC Clock */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC, ENABLE);

  /* Configure FSMC Bank1 NOR/SRAM2 */
  FSMC_NOR_Init();
 
  /* Read NOR memory ID */
  FSMC_NOR_ReadID(&NOR_ID);

  FSMC_NOR_ReturnToReadMode();

  /* Set the LCD display window */
  LCD_SetDisplayWindow(239, 0x13F, 240, 320);

  /* Push key Push Button to exit */
  while(GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_8) != RESET)
  {
    GPIO_ResetBits(GPIOF, GPIO_Pin_6);

    /* Timing measurement base time config */
    TimingMeasurement_Config();

    /* Start timing counter: measure display time */
	SysTick->CTRL |= SysTick_CTRL_ENABLE;

    LCD_WriteDMA(SLIDE1);

    /* Stop timing counter */
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE;

    DisplayTimingCompute();

    GPIO_SetBits(GPIOF, GPIO_Pin_6);

    LCD_WriteDMA(SLIDE2);
  }

  while(ReadKey() != NOKEY)
  {
  }

  /* Clear the LCD */
  LCD_Clear(White);
  /* Set the Back Color */
  LCD_SetBackColor(White);
  /* Set the Text Color */
  LCD_SetTextColor(Blue);

  LCD_DisplayStringLine(Line1, "    NOR FLASH DMA   ");
  sprintf((char*)TxBuffer,"Time = %d e-6 s  ", fractionaltimeunits);
  
  LCD_DisplayStringLine(Line2, TxBuffer);

  /* Set the Text Color */
  LCD_SetTextColor(Green);
  sprintf((char*)TxBuffer,"  %d fps (Frames per Second)", 1000000/fractionaltimeunits);  
  LCD_DisplayStringLine(Line3, TxBuffer);
  LCD_DisplayStringLine(Line4, "Second)");
 
  LCD_DisplayStringLine(Line6, "Press any Key to    ");
  LCD_DisplayStringLine(Line7, "continue.           ");

  while(ReadKey() == NOKEY)
  {
  }

  while(ReadKey() != NOKEY)
  {
  }

  LCD_Clear(White);
  DisplayMenu();
  IntExtOnOffConfig(ENABLE);  
}

/**
  * @brief  Display images from the NOR FLASH on LCD using CPU
  *   with a controlled speed through the RV1 trimmer.
  * @param  None
  * @retval : None
  */
void NORFlashToLCD_Speed(void)
{
  uint32_t keystate = 0;
  
  IntExtOnOffConfig(DISABLE);
 
  while(ReadKey() != NOKEY)
  {
  }

  /* Clear the LCD */
  LCD_Clear(White);
  
  LCD_SetTextColor(Red);
  LCD_DisplayStringLine(Line4, " Turn the Trimmer to");
  LCD_DisplayStringLine(Line5, " control the delay  ");
  LCD_DisplayStringLine(Line6, " between two frames.");
  LCD_DisplayStringLine(Line7, " Push Key Button to ");
  LCD_DisplayStringLine(Line8, " start or stop.     ");


  /* Set the Text Color */
  LCD_SetTextColor(Blue);
  LCD_DisplayStringLine(Line1, "   LCD on FSMC Demo ");  
  LCD_DisplayStringLine(Line2, "      NOR FLASH     ");

  while(GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_8) != RESET)
  {
  }
  while(GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_8) == RESET)
  {
  }


  while(GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_8) != RESET)
  {
  }
  while(GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_8) == RESET)
  {
  }
  
   /* Write/read to/from FSMC SRAM memory  *************************************/
  /* Enable the FSMC Clock */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC, ENABLE);

  /* Configure FSMC Bank1 NOR/SRAM2 */
  FSMC_NOR_Init();
 
  /* Read NOR memory ID */
  FSMC_NOR_ReadID(&NOR_ID);

  FSMC_NOR_ReturnToReadMode();

  /* Set the LCD display window */
  LCD_SetDisplayWindow(239, 0x13F, 240, 320);

  /* Configure the systick */    
  SysTick_Configuration();

  /* Push key Push Button to exit */
  while(keystate != KEY)
  {
    GPIO_ResetBits(GPIOF, GPIO_Pin_6);
    LCD_WriteBMP(SLIDE1);
    GPIO_SetBits(GPIOF, GPIO_Pin_6);
    keystate = DelayJoyStick(ADC_GetConversionValue(ADC1)/40);

    if(keystate == KEY)
    {
      break;
    }
    
    LCD_WriteBMP(SLIDE2);
    keystate = DelayJoyStick(ADC_GetConversionValue(ADC1)/40);
  }

  while(ReadKey() != NOKEY)
  {
  }

  /* Clear the LCD */
  LCD_Clear(White);
  
  LCD_DisplayStringLine(Line6, "Press any Key to    ");
  LCD_DisplayStringLine(Line7, "continue.           ");

  while(ReadKey() == NOKEY)
  {
  }

  while(ReadKey() != NOKEY)
  {
  }

  LCD_Clear(White);
  DisplayMenu();
  IntExtOnOffConfig(ENABLE);
}

/**
  * @brief  Display images from the NAND FLASH on LCD.
  * @param  None
  * @retval : None
  */
void NANDFlashToLCD(void)
{
  IntExtOnOffConfig(DISABLE);
 
  while(ReadKey() != NOKEY)
  {
  }

  /* Clear the LCD */
  LCD_Clear(White);
  
  LCD_SetTextColor(Red);
  LCD_DisplayStringLine(Line4, " Push Key Button to ");
  LCD_DisplayStringLine(Line5, " start or stop.     ");  

    /* Set the Text Color */
  LCD_SetTextColor(Blue);
  LCD_DisplayStringLine(Line1, "   LCD on FSMC Demo ");  
  LCD_DisplayStringLine(Line2, "      NAND FLASH    ");

  while(GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_8) != RESET)
  {
  }
  while(GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_8) == RESET)
  {
  }

  FSMC_NAND_Init();   

  /* Set the LCD display window */
  LCD_SetDisplayWindow(239, 0x13F, 240, 320);

  /* Push key Push Button to exit */
  while(GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_8) != RESET)
  {
    GPIO_ResetBits(GPIOF, GPIO_Pin_6);

    /* Timing measurement base time config */
    TimingMeasurement_Config();

    /* Start timing counter: measure display time */
	SysTick->CTRL |= SysTick_CTRL_ENABLE;

    LCD_NANDDisplay(0);

    /* Stop timing counter */
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE;

    DisplayTimingCompute();

    GPIO_SetBits(GPIOF, GPIO_Pin_6);

    LCD_NANDDisplay(320);
  }

  while(ReadKey() != NOKEY)
  {
  }

  /* Clear the LCD */
  LCD_Clear(White);
  /* Set the Back Color */
  LCD_SetBackColor(White);
  /* Set the Text Color */
  LCD_SetTextColor(Blue);

  LCD_DisplayStringLine(Line1, "      NAND FLASH    ");
  sprintf((char*)TxBuffer,"Time = %d e-6 s  ", fractionaltimeunits);
  
  LCD_DisplayStringLine(Line2, TxBuffer);

  /* Set the Text Color */
  LCD_SetTextColor(Green);
  sprintf((char*)TxBuffer,"  %d fps (Frames per Second)", 1000000/fractionaltimeunits);  
  LCD_DisplayStringLine(Line3, TxBuffer);
  LCD_DisplayStringLine(Line4, "Second)");
    
  LCD_DisplayStringLine(Line6, "Press any Key to    ");
  LCD_DisplayStringLine(Line7, "continue.           ");

  while(ReadKey() == NOKEY)
  {
  }

  while(ReadKey() != NOKEY)
  {
  }

  LCD_Clear(White);
  DisplayMenu();
  IntExtOnOffConfig(ENABLE);  
}

/**
  * @brief  Display images from the NAND FLASH on LCD using CPU
  *   with a controlled speed through the RV1 trimmer.
  * @param  None
  * @retval : None
  */
void NANDFlashToLCD_Speed(void)
{
  uint32_t keystate = 0;
  
  IntExtOnOffConfig(DISABLE);
 
  while(ReadKey() != NOKEY)
  {
  }

  /* Clear the LCD */
  LCD_Clear(White);
  
  LCD_SetTextColor(Red);
  LCD_DisplayStringLine(Line4, " Turn the Trimmer to");
  LCD_DisplayStringLine(Line5, " control the delay  ");
  LCD_DisplayStringLine(Line6, " between two frames.");
  LCD_DisplayStringLine(Line7, " Push Key Button to ");
  LCD_DisplayStringLine(Line8, " start or stop.     ");


  /* Set the Text Color */
  LCD_SetTextColor(Blue);
  LCD_DisplayStringLine(Line1, "   LCD on FSMC Demo ");  
  LCD_DisplayStringLine(Line2, "      NAND FLASH    ");

  while(GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_8) != RESET)
  {
  }
  while(GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_8) == RESET)
  {
  }

  FSMC_NAND_Init();   

  /* Set the LCD display window */
  LCD_SetDisplayWindow(239, 0x13F, 240, 320);

  /* Configure the systick */    
  SysTick_Configuration();

  /* Push key Push Button to exit */
  while(keystate != KEY)
  {
    GPIO_ResetBits(GPIOF, GPIO_Pin_6);
    LCD_NANDDisplay(0);
    GPIO_SetBits(GPIOF, GPIO_Pin_6);
    keystate = DelayJoyStick(ADC_GetConversionValue(ADC1)/40);

    if(keystate == KEY)
    {
      break;
    }
    
    LCD_NANDDisplay(320);
    keystate = DelayJoyStick(ADC_GetConversionValue(ADC1)/40);
  }

  while(ReadKey() != NOKEY)
  {
  }

  /* Clear the LCD */
  LCD_Clear(White);

  LCD_DisplayStringLine(Line6, "Press any Key to    ");
  LCD_DisplayStringLine(Line7, "continue.           ");

  while(ReadKey() == NOKEY)
  {
  }

  while(ReadKey() != NOKEY)
  {
  }

  LCD_Clear(White);
  DisplayMenu();
  IntExtOnOffConfig(ENABLE);
}

/**
  * @brief  Display images from the External SRAM on LCD.
  * @param  None
  * @retval : None
  */
void ExternalSRAMToLCD(void)
{
  IntExtOnOffConfig(DISABLE);
 
  while(ReadKey() != NOKEY)
  {
  }
  
  /* Clear the LCD */
  LCD_Clear(White);

  /* Checks if the Bitmap files are loaded */
  if(ExternalSRAMCheckBitmapFiles() != 0)
  {
    /* Set the LCD Back Color */
    LCD_SetBackColor(Blue);

    /* Set the LCD Text Color */
    LCD_SetTextColor(White);    
    LCD_DisplayStringLine(Line0, "      Warning       ");
    LCD_DisplayStringLine(Line1, "You need to copy    ");
    LCD_DisplayStringLine(Line2, "bitmap images in    ");
    LCD_DisplayStringLine(Line3, "external SRAM.      ");

    LCD_DisplayStringLine(Line7, " Push JoyStick to   ");
    LCD_DisplayStringLine(Line8, "continue.           ");  
    while(ReadKey() == NOKEY)
    {
    }

    while(ReadKey() != NOKEY)
    {
    }

    LCD_Clear(White);
    DisplayMenu();
    IntExtOnOffConfig(ENABLE);
    return;
  }
 
  LCD_SetTextColor(Red);
  LCD_DisplayStringLine(Line4, " Push Key Button to ");
  LCD_DisplayStringLine(Line5, " start or stop.     ");  

  /* Set the Text Color */
  LCD_SetTextColor(Blue);
  LCD_DisplayStringLine(Line1, "   LCD on FSMC Demo ");  
  LCD_DisplayStringLine(Line2, "    External SRAM   ");

  while(GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_8) != RESET)
  {
  }
  while(GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_8) == RESET)
  {
  }

  /* Configure FSMC Bank1 NOR/SRAM3 */
  FSMC_SRAM_Init();

  /* Set the LCD display window */
  LCD_SetDisplayWindow(239, 0x13F, 240, 320);

  /* Push key Push Button to exit */
  while(GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_8) != RESET)
  {
    GPIO_ResetBits(GPIOF, GPIO_Pin_6);

    /* Timing measurement base time config */
    TimingMeasurement_Config();

    /* Start timing counter: measure display time */
	SysTick->CTRL |= SysTick_CTRL_ENABLE;

    LCD_WriteBMP((uint32_t)Bank1_SRAM_ADDR);

    /* Stop timing counter */
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE;

    DisplayTimingCompute();

    GPIO_SetBits(GPIOF, GPIO_Pin_6);

    LCD_WriteBMP((uint32_t) (Bank1_SRAM_ADDR + (2 * SLIDE_SIZE)));    
  }

  while(ReadKey() != NOKEY)
  {
  }

  /* Clear the LCD */
  LCD_Clear(White);
  /* Set the Back Color */
  LCD_SetBackColor(White);
  /* Set the Text Color */
  LCD_SetTextColor(Blue);

  LCD_DisplayStringLine(Line1, "    External SRAM   ");
  sprintf((char*)TxBuffer,"Time = %d e-6 s  ", fractionaltimeunits);
  
  LCD_DisplayStringLine(Line2, TxBuffer);

  /* Set the Text Color */
  LCD_SetTextColor(Green);
  sprintf((char*)TxBuffer,"  %d fps (Frames per Second)", 1000000/fractionaltimeunits); 
  LCD_DisplayStringLine(Line3, TxBuffer);
  LCD_DisplayStringLine(Line4, "Second)");
    
  LCD_DisplayStringLine(Line6, "Press any Key to    ");
  LCD_DisplayStringLine(Line7, "continue.           ");

  while(ReadKey() == NOKEY)
  {
  }

  while(ReadKey() != NOKEY)
  {
  }

  LCD_Clear(White);
  DisplayMenu();
  IntExtOnOffConfig(ENABLE);  
}

/**
  * @brief  Display images from the External SRAM on LCD using DMA.
  * @param  None
  * @retval : None
  */
void ExternalSRAMToLCD_DMA(void)
{
  IntExtOnOffConfig(DISABLE);
 
  while(ReadKey() != NOKEY)
  {
  }
  
  /* Clear the LCD */
  LCD_Clear(White);

  /* Checks if the Bitmap files are loaded */
  if(ExternalSRAMCheckBitmapFiles() != 0)
  {
    /* Set the LCD Back Color */
    LCD_SetBackColor(Blue);

    /* Set the LCD Text Color */
    LCD_SetTextColor(White);    
    LCD_DisplayStringLine(Line0, "      Warning       ");
    LCD_DisplayStringLine(Line1, "You need to copy    ");
    LCD_DisplayStringLine(Line2, "bitmap images in    ");
    LCD_DisplayStringLine(Line3, "external SRAM.      ");

    LCD_DisplayStringLine(Line7, " Push JoyStick to   ");
    LCD_DisplayStringLine(Line8, "continue.           ");  
    while(ReadKey() == NOKEY)
    {
    }

    while(ReadKey() != NOKEY)
    {
    }

    LCD_Clear(White);
    DisplayMenu();
    IntExtOnOffConfig(ENABLE);
    return;
  }

  LCD_SetTextColor(Red);
  LCD_DisplayStringLine(Line4, " Push Key Button to ");
  LCD_DisplayStringLine(Line5, " start or stop.     ");  
  
  /* Set the Text Color */
  LCD_SetTextColor(Blue);
  LCD_DisplayStringLine(Line1, "   LCD on FSMC Demo ");  
  LCD_DisplayStringLine(Line2, "  External SRAM DMA ");

  while(GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_8) != RESET)
  {
  }
  while(GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_8) == RESET)
  {
  }

  /* Configure FSMC Bank1 NOR/SRAM3 */
  FSMC_SRAM_Init();

  /* Set the LCD display window */
  LCD_SetDisplayWindow(239, 0x13F, 240, 320);

  /* Push key Push Button to exit */
  while(GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_8) != RESET)
  {
    GPIO_ResetBits(GPIOF, GPIO_Pin_6);

    /* Timing measurement base time config */
    TimingMeasurement_Config();

    /* Start timing counter: measure display time */
	SysTick->CTRL |= SysTick_CTRL_ENABLE;

    LCD_WriteDMA(Bank1_SRAM_ADDR);

    /* Stop timing counter */
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE;

    DisplayTimingCompute();

    GPIO_SetBits(GPIOF, GPIO_Pin_6);

    LCD_WriteDMA((Bank1_SRAM_ADDR + (2 * SLIDE_SIZE)));	
  }

  while(ReadKey() != NOKEY)
  {
  }  

  /* Clear the LCD */
  LCD_Clear(White);
  /* Set the Back Color */
  LCD_SetBackColor(White);
  /* Set the Text Color */
  LCD_SetTextColor(Blue);

  LCD_DisplayStringLine(Line1, "  External SRAM DMA ");
  sprintf((char*)TxBuffer,"Time = %d e-6 s  ", fractionaltimeunits);
  
  LCD_DisplayStringLine(Line2, TxBuffer);

  /* Set the Text Color */
  LCD_SetTextColor(Green);
  sprintf((char*)TxBuffer,"  %d fps (Frames per Second)", 1000000/fractionaltimeunits);  
  LCD_DisplayStringLine(Line3, TxBuffer);
  LCD_DisplayStringLine(Line4, "Second)");

  LCD_DisplayStringLine(Line6, "Press any Key to    ");
  LCD_DisplayStringLine(Line7, "continue.           ");

  while(ReadKey() == NOKEY)
  {
  }

  while(ReadKey() != NOKEY)
  {
  }

  LCD_Clear(White);
  DisplayMenu();
  IntExtOnOffConfig(ENABLE);  
}

/**
  * @brief  Display images from the External SRAM on LCD using CPU
  *   with a controlled speed through the RV1 trimmer.
  * @param  None
  * @retval : None
  */
void ExternalSRAMToLCD_Speed(void)
{
  uint32_t keystate = 0;
  
  IntExtOnOffConfig(DISABLE);
 
  while(ReadKey() != NOKEY)
  {
  }
  
  /* Clear the LCD */
  LCD_Clear(White);

  /* Checks if the Bitmap files are loaded */
  if(ExternalSRAMCheckBitmapFiles() != 0)
  {
    /* Set the LCD Back Color */
    LCD_SetBackColor(Blue);

    /* Set the LCD Text Color */
    LCD_SetTextColor(White);    
    LCD_DisplayStringLine(Line0, "      Warning       ");
    LCD_DisplayStringLine(Line1, "You need to copy    ");
    LCD_DisplayStringLine(Line2, "bitmap images in    ");
    LCD_DisplayStringLine(Line3, "external SRAM.      ");

    LCD_DisplayStringLine(Line7, " Push JoyStick to   ");
    LCD_DisplayStringLine(Line8, "continue.           ");  
    while(ReadKey() == NOKEY)
    {
    }

    while(ReadKey() != NOKEY)
    {
    }

    LCD_Clear(White);
    DisplayMenu();
    IntExtOnOffConfig(ENABLE);
    return;
  }
 
  /* Clear the LCD */
  LCD_Clear(White);
  
  LCD_SetTextColor(Red);
  LCD_DisplayStringLine(Line4, " Turn the Trimmer to");
  LCD_DisplayStringLine(Line5, " control the delay  ");
  LCD_DisplayStringLine(Line6, " between two frames.");
  LCD_DisplayStringLine(Line7, " Push Key Button to ");
  LCD_DisplayStringLine(Line8, " start or stop.     ");


  /* Set the Text Color */
  LCD_SetTextColor(Blue);
  LCD_DisplayStringLine(Line1, "   LCD on FSMC Demo ");  
  LCD_DisplayStringLine(Line2, "    External SRAM   ");

  while(GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_8) != RESET)
  {
  }
  while(GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_8) == RESET)
  {
  }

  /* Configure FSMC Bank1 NOR/SRAM3 */
  FSMC_SRAM_Init();

  /* Set the LCD display window */
  LCD_SetDisplayWindow(239, 0x13F, 240, 320);
  
  /* Configure the systick */    
  SysTick_Configuration();

  /* Push key Push Button to exit */
  while(keystate != KEY)
  {
    GPIO_ResetBits(GPIOF, GPIO_Pin_6);
    LCD_WriteBMP((uint32_t)Bank1_SRAM_ADDR);
    GPIO_SetBits(GPIOF, GPIO_Pin_6);
    keystate = DelayJoyStick(ADC_GetConversionValue(ADC1)/40);

    if(keystate == KEY)
    {
      break;
    }
    
    LCD_WriteBMP((uint32_t) (Bank1_SRAM_ADDR + (2 * SLIDE_SIZE)));
    keystate = DelayJoyStick(ADC_GetConversionValue(ADC1)/40);    
  }

  while(ReadKey() != NOKEY)
  {
  }

  /* Clear the LCD */
  LCD_Clear(White);

  LCD_DisplayStringLine(Line6, "Press any Key to    ");
  LCD_DisplayStringLine(Line7, "continue.           ");

  while(ReadKey() == NOKEY)
  {
  }

  while(ReadKey() != NOKEY)
  {
  }

  LCD_Clear(White);
  DisplayMenu();
  IntExtOnOffConfig(ENABLE);
}

/**
  * @brief  Display images from the SD Card on LCD.
  * @param  None
  * @retval : None
  */
void SDCardToLCD(void)
{
  IntExtOnOffConfig(DISABLE);
 
  while(ReadKey() != NOKEY)
  {
  }

  /* Clear the LCD */
  LCD_Clear(White);
  
  LCD_SetTextColor(Red);
  LCD_DisplayStringLine(Line4, " Push Key Button to ");
  LCD_DisplayStringLine(Line5, " start or stop.     ");  
  
  /* Set the Text Color */
  LCD_SetTextColor(Blue);
  LCD_DisplayStringLine(Line1, "   LCD on FSMC Demo ");  
  LCD_DisplayStringLine(Line2, "       SD Card      ");

  while(GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_8) != RESET)
  {
  }
  while(GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_8) == RESET)
  {
  }

  /*-------------------------- SD Init ----------------------------- */
  Status = SD_Init();

  if (Status == SD_OK)
  {
    /*----------------- Read CSD/CID MSD registers ------------------*/
    Status = SD_GetCardInfo(&SDCardInfo);
  }

  if (Status == SD_OK)
  {
    /*----------------- Select Card --------------------------------*/
    Status = SD_SelectDeselect((uint32_t) (SDCardInfo.RCA << 16));
  }

  if (Status == SD_OK)
  {
    Status = SD_EnableWideBusOperation(SDIO_BusWide_4b);
  }

  /* Set Device Transfer Mode */
  if (Status == SD_OK)
  {
    Status = SD_SetDeviceMode(SD_DMA_MODE);
  }
  
  /* Set the LCD display window */
  LCD_SetDisplayWindow(239, 0x13F, 240, 320);

  /* Push key Push Button to exit */
  while(GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_8) != RESET)
  {
    GPIO_ResetBits(GPIOF, GPIO_Pin_6);

    /* Timing measurement base time config */
    TimingMeasurement_Config();

    /* Start timing counter: measure display time */
	SysTick->CTRL |= SysTick_CTRL_ENABLE;

    LCD_SDDisplay(0x00);

    /* Stop timing counter */
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE;

    DisplayTimingCompute();

    GPIO_SetBits(GPIOF, GPIO_Pin_6);

    LCD_SDDisplay(0x25800);
  }

  while(ReadKey() != NOKEY)
  {
  }

  /* Clear the LCD */
  LCD_Clear(White);
  /* Set the Back Color */
  LCD_SetBackColor(White);
  /* Set the Text Color */
  LCD_SetTextColor(Blue);

  LCD_DisplayStringLine(Line1, "       SD Card      ");
  sprintf((char*)TxBuffer,"Time = %d e-6 s  ", fractionaltimeunits);
  
  LCD_DisplayStringLine(Line2, TxBuffer);

  /* Set the Text Color */
  LCD_SetTextColor(Green);
  sprintf((char*)TxBuffer,"  %d fps (Frames per Second)", 1000000/fractionaltimeunits);  
  LCD_DisplayStringLine(Line3, TxBuffer);
  LCD_DisplayStringLine(Line4, "Second)");
  
  LCD_DisplayStringLine(Line6, "Press any Key to    ");
  LCD_DisplayStringLine(Line7, "continue.           ");

  while(ReadKey() == NOKEY)
  {
  }

  while(ReadKey() != NOKEY)
  {
  }

  LCD_Clear(White);
  DisplayMenu();
  IntExtOnOffConfig(ENABLE);  
}

/**
  * @brief  Display images from the SD Card on LCD using CPU
  *   with a controlled speed through the RV1 trimmer.
  * @param  None
  * @retval : None
  */
void SDCardToLCD_Speed(void)
{
  uint32_t keystate = 0;
  
  IntExtOnOffConfig(DISABLE);
 
  while(ReadKey() != NOKEY)
  {
  }

  /* Clear the LCD */
  LCD_Clear(White);
  
  LCD_SetTextColor(Red);
  LCD_DisplayStringLine(Line4, " Turn the Trimmer to");
  LCD_DisplayStringLine(Line5, " control the delay  ");
  LCD_DisplayStringLine(Line6, " between two frames.");
  LCD_DisplayStringLine(Line7, " Push Key Button to ");
  LCD_DisplayStringLine(Line8, " start or stop.     ");


  /* Set the Text Color */
  LCD_SetTextColor(Blue);
  LCD_DisplayStringLine(Line1, "   LCD on FSMC Demo ");  
  LCD_DisplayStringLine(Line2, "       SD Card      ");

  while(GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_8) != RESET)
  {
  }
  while(GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_8) == RESET)
  {
  }

  /*-------------------------- SD Init ----------------------------- */
  Status = SD_Init();

  if (Status == SD_OK)
  {
    /*----------------- Read CSD/CID MSD registers ------------------*/
    Status = SD_GetCardInfo(&SDCardInfo);
  }

  if (Status == SD_OK)
  {
    /*----------------- Select Card --------------------------------*/
    Status = SD_SelectDeselect((uint32_t) (SDCardInfo.RCA << 16));
  }

  if (Status == SD_OK)
  {
    Status = SD_EnableWideBusOperation(SDIO_BusWide_4b);
  }

  /* Set Device Transfer Mode */
  if (Status == SD_OK)
  {
    Status = SD_SetDeviceMode(SD_DMA_MODE);
  }
  
  /* Set the LCD display window */
  LCD_SetDisplayWindow(239, 0x13F, 240, 320);

  /* Configure the systick */    
  SysTick_Configuration();

  /* Push key Push Button to exit */
  while(keystate != KEY)
  {
    GPIO_ResetBits(GPIOF, GPIO_Pin_6);
    LCD_SDDisplay(0x00);
    GPIO_SetBits(GPIOF, GPIO_Pin_6);
    keystate = DelayJoyStick(ADC_GetConversionValue(ADC1)/40);

    if(keystate == KEY)
    {
      break;
    }
    
    LCD_SDDisplay(0x25800);
    keystate = DelayJoyStick(ADC_GetConversionValue(ADC1)/40);
  }

  while(ReadKey() != NOKEY)
  {
  }

  /* Clear the LCD */
  LCD_Clear(White);
  
  LCD_DisplayStringLine(Line6, "Press any Key to    ");
  LCD_DisplayStringLine(Line7, "continue.           ");

  while(ReadKey() == NOKEY)
  {
  }

  while(ReadKey() != NOKEY)
  {
  }


  LCD_Clear(White);
  DisplayMenu();
  IntExtOnOffConfig(ENABLE);
}

/**
  * @brief  Write a full size picture on the SD Card.
  * @param address: SD card memory address to write to.
  * @param pointer: pointer to the buffer to be written in SD card.
  * @retval : None
  */
SD_Error LCD_WriteSD(uint32_t address, uint32_t *pointer)
{
  uint32_t i = 0, sdaddress = address;

  for(i = 0; i < 15; i++)
  {
    if (Status == SD_OK)
    {
      /* Write block of 512 bytes on awddress 0 */
      Status = SD_WriteMultiBlocks(sdaddress, pointer, BlockSize, 20);
      sdaddress += BlockSize * 20;
      pointer += BlockSize * 5;
    }
    else
    {
      break;
    }
  }
  return Status;
}

/**
  * @brief  Write a full size picture on the LCD from SD Card.
  * @param address: SD card memory address to read from.
  * @retval : None
  */
SD_Error LCD_SDDisplay(uint32_t address)
{
  uint32_t i = 0, j = 0, sdaddress = address;
  uint16_t* ptr = (uint16_t *)(Buffer_Block_Rx);
  

  LCD_SetDisplayWindow(239, 0x13F, 240, 320);

  /* Set GRAM write direction and BGR = 1 */
  /* I/D=00 (Horizontal : decrement, Vertical : decrement) */
  /* AM=1 (address is updated in vertical writing direction) */
  LCD_WriteReg(R3, 0x1008);
 
  LCD_WriteRAM_Prepare();
 
  for(i = 0; i < 15; i++)
  {
    if (Status == SD_OK)
    {
      /* Read block of 512*20 bytes from address 0 */
      Status = SD_ReadMultiBlocks(sdaddress, Buffer_Block_Rx, BlockSize, 20);
      for(j = 0; j < 5120; j++)
      {
        LCD_WriteRAM(ptr[j]);
      }
    }
    else
    {
      break;
    }
    ptr = (uint16_t *)Buffer_Block_Rx;
    sdaddress += BlockSize*20;
  }  
  LCD_WriteReg(R3, 0x1018);
  return Status;
}

/**
  * @brief  Write a full size picture on the LCD from NAND Flash.
  * @param address: address to the picture on the NAND Flash.
  * @retval : None
  */
uint32_t LCD_NANDDisplay(uint32_t address)
{
  uint32_t i = 0, j = 0;
  uint16_t *ptr;

  ptr = (uint16_t *) pBuffer;

  LCD_SetDisplayWindow(239, 0x13F, 240, 320);

  LCD_WriteReg(R3, 0x1008);
 
  LCD_WriteRAM_Prepare();
 
  for(i = 0; i < 9; i++)
  {	
    NAND_Read((address * 512), pBuffer, 32);
    address += 32;
    
    for(j = 0; j < 8192; j++)
    {
      LCD_WriteRAM(ptr[j]);
    }
  }

  NAND_Read((address * 512), pBuffer, 32);

  for(j = 0; j < 3072; j++)
  {
    LCD_WriteRAM(ptr[j]);
  }


  LCD_WriteReg(R3, 0x1018);
  return Status;
}

/**
  * @brief  Write a full size picture on the LCD from the selected memory 
  *   using DMA.
  * @param address: address to the picture on the selected memory.
  * @retval : None
  */
void LCD_WriteDMA(uint32_t address)
{
  DMA_InitTypeDef  DMA_InitStructure;

  /* Set GRAM write direction and BGR = 1 */
  /* I/D=00 (Horizontal : decrement, Vertical : decrement) */
  /* AM=1 (address is updated in vertical writing direction) */
  LCD_WriteReg(R3, 0x1008);
 
  LCD_WriteRAM_Prepare();
  
  DMAComplete = 0;
  FirstEntry = 1;
  DMASourceAddress = address + 0x42;
  
  /* DMA1 channel3 configuration */
  DMA_DeInit(DMA1_Channel3);
  DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)DMASourceAddress;  
  DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)LCD_RAM_ADDR;
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
  DMA_InitStructure.DMA_BufferSize = 0xFFFF;
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Enable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Disable;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;
  DMA_InitStructure.DMA_M2M = DMA_M2M_Enable;
  
  DMA_Init(DMA1_Channel3, &DMA_InitStructure);

  /* Enable DMA Channel3 Transfer Complete interrupt */
  DMA_ITConfig(DMA1_Channel3, DMA_IT_TC, ENABLE);

  /* Enable DMA1 channel3 */
  DMA_Cmd(DMA1_Channel3, ENABLE);

  /* Wait for DMA transfer Complete */
  while(DMAComplete == 0)
  {
  }
}

/**
  * @brief  Checks if the bitmap files (slides + icons) are already loaded
  *   in the NOR FLASH.
  * @param  None
  * @retval : None
  */
uint32_t CheckBitmapFiles(void)
{
  uint32_t index = 0;
  uint8_t Tab[6];

 
  /* Write/read to/from FSMC SRAM memory  *************************************/
  /* Enable the FSMC Clock */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC, ENABLE);
  
  /* Configure FSMC Bank1 NOR/SRAM2 */
  FSMC_NOR_Init();
  
  /* Read NOR memory ID */
  FSMC_NOR_ReadID(&NOR_ID);

  FSMC_NOR_ReturnToReadMode();


  Tab[0] = 0x00;
  Tab[1] = 0x00;
  Tab[2] = 0x00;
  Tab[3] = 0x00;
  Tab[4] = 0x00;
  Tab[5] = 0x00;


  /* Read bitmap size */
  Media_BufferRead(Tab, SLIDE1, 6);
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC, ENABLE);
  if(Buffercmp(Tab, SlidesCheck, 5)!= 0) return 1;
  Tab[0] = 0x00;
  Tab[1] = 0x00;
  Tab[2] = 0x00;
  Tab[3] = 0x00;
  Tab[4] = 0x00;
  Tab[5] = 0x00;

  /* Read bitmap size */
  Media_BufferRead(Tab, SLIDE2, 6);
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC, ENABLE);
  if(Buffercmp(Tab, SlidesCheck, 5)!= 0) return 1;
  Tab[0] = 0x00;
  Tab[1] = 0x00;
  Tab[2] = 0x00;
  Tab[3] = 0x00;
  Tab[4] = 0x00;
  Tab[5] = 0x00;

  for(index = 0; index < 5; index++)
  {
    /* Read bitmap size */
    Media_BufferRead(Tab, IconsAddr[index], 6);
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC, ENABLE);
    if(Buffercmp(Tab, Icons64Check, 5)!= 0) return 1;
    Tab[0] = 0x00;
    Tab[1] = 0x00;
    Tab[2] = 0x00;
    Tab[3] = 0x00;
    Tab[4] = 0x00;
    Tab[5] = 0x00;
  }

  return 0;
}

/**
  * @brief  Compares two buffers.
  * @param pBuffer1, pBuffer2: buffers to be compared.
  * @param BufferLength: buffer's length
  * @retval : 0: pBuffer1 identical to pBuffer2
  *          1: pBuffer1 differs from pBuffer2
  */
static uint8_t Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t BufferLength)
{
  while(BufferLength--)
  {
    if(*pBuffer1 != *pBuffer2)
    {
      return 1;
    }

    pBuffer1++;
    pBuffer2++;
  }

  return 0;
}

/**
  * @brief  Configure the SysTick Base time.
  * @param  None
  * @retval : None
  */
void TimingMeasurement_Config(void)
{
  RCC_ClocksTypeDef RCC_ClockFreq;

  /* Get HCLK frequency */
  RCC_GetClocksFreq(&RCC_ClockFreq);

  SysTick->CTRL &= ~SysTick_CTRL_ENABLE;

  /* Configure HCLK clock as SysTick clock source */
  SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);

  /* Set SysTick Load value to 0xFFFFFF */
  SysTick->LOAD = 0xFFFFFF;

  /* Disable the SysTick Interrupt */
  SysTick->CTRL &= ~SysTick_CTRL_TICKINT;

  SysTick->VAL = 0x0;
}

/**
  * @brief  Calculate the number of Ýs in the systick counter.
  * @param  None
  * @retval : None
  */
void DisplayTimingCompute(void)
{
  uint32_t counter = 0;

  counter = SysTick->VAL;

  if (counter != 0)
  {
    /* Convert timer ticks to ns */
    counter =  (0xFFFFFF - counter) * 111;
  }
  
  /* Compute timing in microsecond (Ýs) */
  fractionaltimeunits = counter / 1000;

}

/**
  * @brief  Copy images to internal FLASH.
  * @param  None
  * @retval : None
  */
void CopyToInternalFlash(void)
{
  uint32_t EraseCounter = 0x00, NORSourceAddress = 0x00, Address = 0x00;
  FLASH_Status FLASHStatus;

  FLASHStatus = FLASH_COMPLETE;

  IntExtOnOffConfig(DISABLE);
 
  while(ReadKey() != NOKEY)
  {
  }

  /* Clear the LCD */
  LCD_Clear(White);
  
  LCD_SetTextColor(Red);
  LCD_DisplayStringLine(Line4, "Push Key Button to  ");
  LCD_DisplayStringLine(Line5, "start the copy      ");  
  LCD_DisplayStringLine(Line6, "operation from NOR  ");
  LCD_DisplayStringLine(Line7, "to internal FLASH.  ");
  

  while(GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_8) != RESET)
  {
  }
  while(GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_8) == RESET)
  {
  }
  
  /* Clear the LCD */  
  LCD_Clear(White);

  /* Set the Text Color */
  LCD_SetTextColor(Blue);
  LCD_DisplayStringLine(Line4, "Copy in Progress... "); 
  LCD_DisplayStringLine(Line5, "Please wait...      ");
   
 /* Write/read to/from FSMC SRAM memory  *************************************/
  /* Enable the FSMC Clock */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC, ENABLE);
  
  /* Configure FSMC Bank1 NOR/SRAM2 */
  FSMC_NOR_Init();
  
  /* Read NOR memory ID */
  FSMC_NOR_ReadID(&NOR_ID);

  FSMC_NOR_ReturnToReadMode();


  /* Unlock the Flash Program Erase controller */
  FLASH_Unlock();

  /* Clear All pending flags */
  FLASH_ClearFlag(FLASH_FLAG_BSY | FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);	

  /* Erase the FLASH pages */
  for(EraseCounter = 0; (EraseCounter < 151) && (FLASHStatus == FLASH_COMPLETE); EraseCounter++)
  {
    FLASHStatus = FLASH_ErasePage(START_ADDR + (FLASH_PAGE_SIZE * EraseCounter));
  }
  
  Address = START_ADDR;
  NORSourceAddress = SLIDE1;

  while((Address < (START_ADDR + 0x25842)) && (FLASHStatus == FLASH_COMPLETE))
  {
    FLASHStatus =  FLASH_ProgramHalfWord(Address, *(__IO uint16_t *)NORSourceAddress);
    NORSourceAddress += 2;
    Address += 2;
  }

  Address = (START_ADDR + 0x25842);
  NORSourceAddress = SLIDE2;

  while((Address < (START_ADDR + 0x4B084)) && (FLASHStatus == FLASH_COMPLETE))
  {
    FLASHStatus =  FLASH_ProgramHalfWord(Address, *(__IO uint16_t *)NORSourceAddress);
    NORSourceAddress += 2;
    Address += 2;
  }

  /* Set the Text Color */
  LCD_SetTextColor(Blue);
  LCD_DisplayStringLine(Line4, "    Copy finished   ");
  
  LCD_ClearLine(Line5);
  LCD_DisplayStringLine(Line6, "Press any Key to    ");
  LCD_DisplayStringLine(Line7, "continue.           ");

  while(ReadKey() == NOKEY)
  {
  }

  while(ReadKey() != NOKEY)
  {
  }


  LCD_Clear(White);
  DisplayMenu();
  IntExtOnOffConfig(ENABLE);
}

/**
  * @brief  Copy images to the external SRAM.
  * @param  None
  * @retval : None
  */
void CopyToExternalSRAM(void)
{
  IntExtOnOffConfig(DISABLE);
 
  while(ReadKey() != NOKEY)
  {
  }

  /* Clear the LCD */
  LCD_Clear(White);
  
  LCD_SetTextColor(Red);
  LCD_DisplayStringLine(Line4, "Push Key Button to  ");
  LCD_DisplayStringLine(Line5, "start the copy      ");  
  LCD_DisplayStringLine(Line6, "operation from NOR  ");
  LCD_DisplayStringLine(Line7, "to External SRAM.   ");
  

  while(GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_8) != RESET)
  {
  }
  while(GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_8) == RESET)
  {
  }
  
  /* Clear the LCD */  
  LCD_Clear(White);

  /* Set the Text Color */
  LCD_SetTextColor(Blue);
  LCD_DisplayStringLine(Line4, "Copy in Progress... "); 
  LCD_DisplayStringLine(Line5, "Please wait...      ");
   
 /* Write/read to/from FSMC SRAM memory  *************************************/
  /* Enable the FSMC Clock */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC, ENABLE);
  
  /* Configure FSMC Bank1 NOR/SRAM2 */
  FSMC_NOR_Init();
  
  /* Read NOR memory ID */
  FSMC_NOR_ReadID(&NOR_ID);

  FSMC_NOR_ReturnToReadMode();

  /* Configure FSMC Bank1 NOR/SRAM3 */
  FSMC_SRAM_Init();

  FSMC_SRAM_WriteBuffer((uint16_t*)SLIDE1, 0x0000, SLIDE_SIZE);
  FSMC_SRAM_WriteBuffer((uint16_t*)SLIDE2, 2 * SLIDE_SIZE, SLIDE_SIZE);

  /* Set the Text Color */
  LCD_SetTextColor(Blue);
  LCD_DisplayStringLine(Line4, "    Copy finished   ");
  
  LCD_ClearLine(Line5);
  LCD_DisplayStringLine(Line6, "Press any Key to    ");
  LCD_DisplayStringLine(Line7, "continue.           ");

  while(ReadKey() == NOKEY)
  {
  }

  while(ReadKey() != NOKEY)
  {
  }


  LCD_Clear(White);
  DisplayMenu();
  IntExtOnOffConfig(ENABLE);
}

/**
  * @brief  Copy images to the SD Card.
  * @param  None
  * @retval : None
  */
void CopyToSDCard(void)
{
  IntExtOnOffConfig(DISABLE);
 
  while(ReadKey() != NOKEY)
  {
  }

  /* Clear the LCD */
  LCD_Clear(White);
  
  LCD_SetTextColor(Red);
  LCD_DisplayStringLine(Line4, "Push Key Button to  ");
  LCD_DisplayStringLine(Line5, "start the copy      ");  
  LCD_DisplayStringLine(Line6, "operation from NOR  ");
  LCD_DisplayStringLine(Line7, "to SD Card.         ");
  

  while(GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_8) != RESET)
  {
  }
  while(GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_8) == RESET)
  {
  }
  
  /* Clear the LCD */  
  LCD_Clear(White);

  /* Set the Text Color */
  LCD_SetTextColor(Blue);
  LCD_DisplayStringLine(Line4, "Copy in Progress... ");  
  LCD_DisplayStringLine(Line5, "Please wait...      ");

  /* Write/read to/from FSMC SRAM memory  *************************************/
  /* Enable the FSMC Clock */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC, ENABLE);
  
  /* Configure FSMC Bank1 NOR/SRAM2 */
  FSMC_NOR_Init();
  
  /* Read NOR memory ID */
  FSMC_NOR_ReadID(&NOR_ID);

  FSMC_NOR_ReturnToReadMode();

  /*-------------------------- SD Init ----------------------------- */
  Status = SD_Init();

  if (Status == SD_OK)
  {
    /*----------------- Read CSD/CID MSD registers ------------------*/
    Status = SD_GetCardInfo(&SDCardInfo);
  }

  if (Status == SD_OK)
  {
    /*----------------- Select Card --------------------------------*/
    Status = SD_SelectDeselect((uint32_t) (SDCardInfo.RCA << 16));
  }

  if (Status == SD_OK)
  {
    Status = SD_EnableWideBusOperation(SDIO_BusWide_4b);
  }

  /* Set Device Transfer Mode */
  if (Status == SD_OK)
  {
    Status = SD_SetDeviceMode(SD_DMA_MODE);
  }
  
  SDIO->CLKCR &= 0xFFFFFF00;
  SDIO->CLKCR |= 0x5;
  
  LCD_WriteSD(0x0, (uint32_t *)(SLIDE1 + 0x42));
  LCD_WriteSD(0x25800, (uint32_t *)(SLIDE2 + 0x42));

  SDIO->CLKCR &= 0xFFFFFF00;
  SDIO->CLKCR |= 0x1;
  
  /* Set the Text Color */
  LCD_SetTextColor(Blue);
  LCD_DisplayStringLine(Line4, "    Copy finished   ");

  LCD_ClearLine(Line5);
  LCD_DisplayStringLine(Line6, "Press any Key to    ");
  LCD_DisplayStringLine(Line7, "continue.           ");

  while(ReadKey() == NOKEY)
  {
  }

  while(ReadKey() != NOKEY)
  {
  }


  LCD_Clear(White);
  DisplayMenu();
  IntExtOnOffConfig(ENABLE);   
}

/**
  * @brief  Copy images to the NAND Flash.
  * @param  None
  * @retval : None
  */
void CopyToNANDFlash(void)
{
  uint32_t block = 0, i = 0;

  IntExtOnOffConfig(DISABLE);
 
  while(ReadKey() != NOKEY)
  {
  }

  /* Clear the LCD */
  LCD_Clear(White);
  
  LCD_SetTextColor(Red);
  LCD_DisplayStringLine(Line4, "Push Key Button to  ");
  LCD_DisplayStringLine(Line5, "start the copy      ");  
  LCD_DisplayStringLine(Line6, "operation from NOR  ");
  LCD_DisplayStringLine(Line7, "to NAND FLASH.      ");
  

  while(GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_8) != RESET)
  {
  }
  while(GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_8) == RESET)
  {
  }
  
  /* Clear the LCD */  
  LCD_Clear(White);

  /* Set the Text Color */
  LCD_SetTextColor(Blue);
  LCD_DisplayStringLine(Line4, "Copy in Progress... ");  
  LCD_DisplayStringLine(Line5, "Please wait...      ");
  
  /* Write/read to/from FSMC SRAM memory  *************************************/
  /* Enable the FSMC Clock */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC, ENABLE);
  
  /* Configure FSMC Bank1 NOR/SRAM2 */
  FSMC_NOR_Init();
  
  /* Read NOR memory ID */
  FSMC_NOR_ReadID(&NOR_ID);

  FSMC_NOR_ReturnToReadMode();

  FSMC_NAND_Init();

  for(i = 0; i < 10; i++)
  {
    NAND_Write((block * 512), (uint8_t *)(SLIDE1 + 0x42 + (block * 512)), 32);
    block += 32;    
  }

  for(i = 0, block = 320; i < 10; i++)
  {
    NAND_Write((block * 512), (uint8_t *)(SLIDE2 + 0x42 + ((block - 320) * 512)), 32);
    block += 32;    
  }

  /* Set the Text Color */
  LCD_SetTextColor(Blue);
  LCD_DisplayStringLine(Line4, "    Copy finished   ");

  LCD_ClearLine(Line5);
  LCD_DisplayStringLine(Line6, "Press any Key to    ");
  LCD_DisplayStringLine(Line7, "continue.           ");

  while(ReadKey() == NOKEY)
  {
  }

  while(ReadKey() != NOKEY)
  {
  }


  LCD_Clear(White);
  DisplayMenu();
  IntExtOnOffConfig(ENABLE);
}

/**
  * @brief  Erases the NAND Flash Content.
  * @param  None
  * @retval : None
  */
void NAND_PhysicalErase(void)
{
  NAND_ADDRESS phAddress;
  SPARE_AREA  SpareArea;
  uint32_t BlockIndex = 0;

  /* Disble the JoyStick interrupts */
  IntExtOnOffConfig(DISABLE);


  while(ReadKey() != NOKEY)
  {
  }

  LCD_Clear(White);

  /* Set the Back Color */
  LCD_SetBackColor(Blue);
  /* Set the Text Color */
  LCD_SetTextColor(White); 

  LCD_DisplayStringLine(Line4, " Erase NAND Content ");
  LCD_DisplayStringLine(Line5, "Please wait...      ");
 
  /* FSMC Initialization */
  FSMC_NAND_Init();
 
  for (BlockIndex = 0 ; BlockIndex < NAND_ZONE_SIZE * NAND_MAX_ZONE; BlockIndex++)
  {
    phAddress = NAND_ConvertPhyAddress(BlockIndex * NAND_BLOCK_SIZE );
    SpareArea = ReadSpareArea(BlockIndex * NAND_BLOCK_SIZE);
   
    if((SpareArea.DataStatus != 0)||(SpareArea.BlockStatus != 0)){
        FSMC_NAND_EraseBlock (phAddress);
    }  
  }
  
  
  /* Display the "To stop Press SEL" message */
  LCD_DisplayStringLine(Line4, "     NAND Erased    ");
  LCD_DisplayStringLine(Line5, "  To exit Press SEL ");

  /* Loop until SEL key pressed */
  while(ReadKey() != SEL)
  {
  }
  
  LCD_Clear(White);
  DisplayMenu();
  IntExtOnOffConfig(ENABLE);
}

/**
  * @brief  write one sector by once
  * @param  None
  * @retval : Status
  */
static uint16_t NAND_Write(uint32_t Memory_Offset, uint8_t *Writebuff, uint16_t Transfer_Length)
{
  SPARE_AREA sp;

  do 
  {
    sp = ReadSpareArea(Memory_Offset / 512);

    if (sp.BlockStatus != 0)
    {
      /* Check block status and calculate start and end addreses */
      wAddress = NAND_GetAddress(Memory_Offset / 512);
      FSMC_NAND_EraseBlock (wAddress);
      FSMC_NAND_WriteSmallPage(Writebuff, wAddress, Transfer_Length);
	}
    Memory_Offset += 32*512;
  }while(sp.BlockStatus ==0);

  return NAND_OK;
}

/**
  * @brief  Read sectors
  * @param  None
  * @retval : Status
  */
static uint16_t NAND_Read(uint32_t Memory_Offset, uint8_t *Readbuff, uint16_t Transfer_Length)
{ 
  SPARE_AREA sp;

  do 
  {
    sp = ReadSpareArea(Memory_Offset / 512);

    if (sp.BlockStatus !=0 )
    {
      /* Check block status and calculate start and end addreses */
      wAddress = NAND_GetAddress(Memory_Offset / 512);
      FSMC_NAND_ReadSmallPage (Readbuff , wAddress, Transfer_Length);
    }
    Memory_Offset += 32*512;
  }while(sp.BlockStatus ==0);

  return NAND_OK;
}

/**
  * @brief  Translate logical address into a phy one
  * @param  None
  * @retval : Status
  */
static NAND_ADDRESS NAND_GetAddress (uint32_t Address)
{
  NAND_ADDRESS Address_t;

  Address_t.Page  = Address & (NAND_BLOCK_SIZE - 1);
  Address_t.Block = Address / NAND_BLOCK_SIZE;
  Address_t.Zone = 0;

  while (Address_t.Block >= MAX_LOG_BLOCKS_PER_ZONE)
  {
    Address_t.Block -= MAX_LOG_BLOCKS_PER_ZONE;
    Address_t.Zone++;
  }
  return Address_t;
}

/**
  * @brief  Check used block
  * @param  None
  * @retval : Status
  */
static SPARE_AREA ReadSpareArea (uint32_t address)
{
  SPARE_AREA t;
  uint8_t Buffer[16];
  NAND_ADDRESS address_s;
  address_s = NAND_ConvertPhyAddress(address);
  FSMC_NAND_ReadSpareArea(Buffer , address_s, 1) ;

  t = *(SPARE_AREA *)Buffer;

  return t;
}

/**
  * @brief  None
  * @param Address: physical Address
  * @retval : Status
  */
static NAND_ADDRESS NAND_ConvertPhyAddress (uint32_t Address)
{
  NAND_ADDRESS Address_t;

  Address_t.Page  = Address & (NAND_BLOCK_SIZE - 1);
  Address_t.Block = Address / NAND_BLOCK_SIZE;
  Address_t.Zone = 0;

  while (Address_t.Block >= MAX_PHY_BLOCKS_PER_ZONE)
  {
    Address_t.Block -= MAX_PHY_BLOCKS_PER_ZONE;
    Address_t.Zone++;
  }
  return Address_t;
}

/**
  * @brief  Read a buffer from the memory media 
  * @param pBuffer: Destination buffer address
  * @param ReadAddr: start reading position
  * @param NumByteToRead: size of the buffer to read
  * @retval : None.
  */
static void Media_BufferRead(uint8_t* pBuffer, uint32_t ReadAddr, uint16_t NumByteToRead)
{ 
  /* Read the data */
  while(NumByteToRead--)
  {
    *pBuffer++ = *(__IO uint8_t *)ReadAddr++;
  }
}

/**
  * @brief  Checks if the bitmap files (slides) are already loaded
  *   in the internal FLASH.
  * @param  None
  * @retval : None
  */
static uint32_t InternalFlashCheckBitmapFiles(void)
{
  uint8_t Tab[6];

  Tab[0] = *(__IO uint8_t *)(START_ADDR);
  Tab[1] = *(__IO uint8_t *)(START_ADDR + 1);
  Tab[2] = *(__IO uint8_t *)(START_ADDR + 2);
  Tab[3] = *(__IO uint8_t *)(START_ADDR + 3);
  Tab[4] = *(__IO uint8_t *)(START_ADDR + 4);
  Tab[5] = *(__IO uint8_t *)(START_ADDR + 5);

  if(Buffercmp(Tab, SlidesCheck, 5)!= 0) return 1;

  Tab[0] = *(__IO uint8_t *)(START_ADDR);
  Tab[1] = *(__IO uint8_t *)(START_ADDR + 0x25842 + 1);
  Tab[2] = *(__IO uint8_t *)(START_ADDR + 0x25842 + 2);
  Tab[3] = *(__IO uint8_t *)(START_ADDR + 0x25842 + 3);
  Tab[4] = *(__IO uint8_t *)(START_ADDR + 0x25842 + 4);
  Tab[5] = *(__IO uint8_t *)(START_ADDR + 0x25842 + 5);
  if(Buffercmp(Tab, SlidesCheck, 5)!= 0) return 1;

  return 0;
}

/**
  * @brief  Checks if the bitmap files (slides) are already loaded
  *   in the external SRAM.
  * @param  None
  * @retval : None
  */
static uint32_t ExternalSRAMCheckBitmapFiles(void)
{
  uint8_t Tab[6];

  /* Configure FSMC Bank1 NOR/SRAM3 */
  FSMC_SRAM_Init();

  Tab[0] = *(__IO uint8_t *)(Bank1_SRAM_ADDR);
  Tab[1] = *(__IO uint8_t *)(Bank1_SRAM_ADDR + 1);
  Tab[2] = *(__IO uint8_t *)(Bank1_SRAM_ADDR + 2);
  Tab[3] = *(__IO uint8_t *)(Bank1_SRAM_ADDR + 3);
  Tab[4] = *(__IO uint8_t *)(Bank1_SRAM_ADDR + 4);
  Tab[5] = *(__IO uint8_t *)(Bank1_SRAM_ADDR + 5);

  if(Buffercmp(Tab, SlidesCheck, 5)!= 0) return 1;

  Tab[0] = *(__IO uint8_t *)((Bank1_SRAM_ADDR + (2 * SLIDE_SIZE)));
  Tab[1] = *(__IO uint8_t *)((Bank1_SRAM_ADDR + (2 * SLIDE_SIZE)) + 1);
  Tab[2] = *(__IO uint8_t *)((Bank1_SRAM_ADDR + (2 * SLIDE_SIZE)) + 2);
  Tab[3] = *(__IO uint8_t *)((Bank1_SRAM_ADDR + (2 * SLIDE_SIZE)) + 3);
  Tab[4] = *(__IO uint8_t *)((Bank1_SRAM_ADDR + (2 * SLIDE_SIZE)) + 4);
  Tab[5] = *(__IO uint8_t *)((Bank1_SRAM_ADDR + (2 * SLIDE_SIZE)) + 5);
  if(Buffercmp(Tab, SlidesCheck, 5)!= 0) return 1;

  return 0;
}

/**
  * @}
  */

/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/
