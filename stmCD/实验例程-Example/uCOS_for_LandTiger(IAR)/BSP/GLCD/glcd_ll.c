/*************************************************************************
 *
 *    Used with ICCARM and AARM.
 *
 *    (c) Copyright IAR Systems 2006
 *
 *    File name   : glcd_ll.c
 *    Description : GLCD low level functions
 *
 *    History :
 *    1. Date        : December 2, 2006
 *       Author      : Stanimir Bonev
 *       Description : Create
 *
 *    $Revision: 30123 $
 **************************************************************************/
#include "glcd_ll.h"
#include <cpu_def.h>

extern CPU_INT32U  BSP_SysCtrl_PerClkFreqGet (CPU_INT08U  per_nbr);

/*************************************************************************
 * Function Name: GLCD_SetReset
 * Parameters: Boolean State
 * Return: none
 *
 * Description: Set reset pin state
 *
 *************************************************************************/
void GLCD_SetReset (Boolean State)
{
	if(State)
	{
    LCD_RST_FSET = LCD_RST_MASK;
	}
	else
	{
    LCD_RST_FCLR = LCD_RST_MASK;
	}
}

/*************************************************************************
 * Function Name: GLCD_Backlight
 * Parameters: Int8U Light
 * Return: none
 *
 * Description: Set backlight pin state
 *
 *************************************************************************/
void GLCD_Backlight (Int8U Light)
{
  PWM1MR3 = BACKLIGHT_OFF + Light;
  PWM1LER_bit.EM3L = 1;
}

/*************************************************************************
 * Function Name: GLCD_LLInit
 * Parameters: none
 * Return: none
 *
 * Description: Init Reset and Backlight control outputs
 *
 *************************************************************************/
void GLCD_LLInit (void)
{
	// LCD Reset output
  LCD_RST_FDIR |= LCD_RST_MASK;

  GLCD_SetReset(0);

	// LCD backlight PWM 8bit init
  LCD_BL_PIN_SEL = 3;       // assign P3.26 to PWM1
  PCONP_bit.PCPWM1 = 1;     // enable clock of PWM1
  PWM1TCR_bit.PWMEN = 0;    // enable PWM function
  PWM1TCR_bit.CE = 0;       // disable counting
  PWM1TCR_bit.CR = 1;       // reset
  PWM1CTCR_bit.CM = 0;      // from prescaler
  PWM1MCR = 2;              // Reset on PWMMR0
  PWM1PCR_bit.PWMSEL3 = 0;  // Selects single edge controlled mode for PWM6
  PWM1PCR_bit.PWMENA3 = 1;  // The PWM3 output enabled
  PWM1PR = 0;
  PWM1MR0 = 0xFF;           // 8bit resolution
  PWM1LER_bit.EM0L = 1;
  PWM1MR3 = 0;
  PWM1LER_bit.EM3L = 1;
  PWM1TCR_bit.PWMEN = 1;    // enable PWM function
  PWM1TCR_bit.CR = 0;       // release reset
  PWM1TCR_bit.CE = 1;       // enable counting
  GLCD_Backlight(0);
}

/*************************************************************************
 * Function Name: GLCD_SPI_ChipSelect
 * Parameters: Boolean Select
 * Return: none
 *
 * Description: SSP0 Chip select control
 * Select = true  - Chip is enable
 * Select = false - Chip is disable
 *
 *************************************************************************/
void GLCD_SPI_ChipSelect (Boolean Select)
{
  if (Select)
  {
    LCD_CS_FCLR = LCD_CS_MASK;
  }
  else
  {
    LCD_CS_FSET = LCD_CS_MASK;
  }
}

/*************************************************************************
 * Function Name: GLCD_SPI_SetWordWidth
 * Parameters: Int32U Width
 * Return: Boolean
 *
 * Description: Set SSP 0 word width
 *
 *************************************************************************/
Boolean GLCD_SPI_SetWordWidth (Int32U Width)
{
  if(4 > Width || Width > 16)
  {
    return(FALSE);
  }

  SSP0CR0_bit.DSS = Width - 1;
  return(TRUE);
}

/*************************************************************************
 * Function Name: GLCD_SPI_SetClockFreq
 * Parameters: Int32U Frequency
 * Return: Int32U
 *
 * Description: Set SSP 0 clock
 *
 *************************************************************************/
Int32U GLCD_SPI_SetClockFreq (Int32U Frequency)
{
#if 0
Int32U Fspi =  SYS_GetFpclk(SSP0_PCLK_OFFSET);
#else 
Int32U Fspi =  BSP_PM_PerClkFreqGet(BSP_PM_PER_NBR_SSP0);
#endif

Int32U Div = 2;
  while((Div * Frequency) < Fspi)
  {
    if((Div += 2) == 254)
    {
      break;
    }
  }
  SSP0CPSR = Div;
  return(Fspi/Div);
}

/*************************************************************************
 * Function Name: GLCD_SPI_Init
 * Parameters: Int32U Clk, Int32U Width
 * Return: none
 *
 * Description: Init SSP0
 *
 *************************************************************************/
void GLCD_SPI_Init(Int32U Clk, Int32U Width)
{
  // Assign GPIO to SSP0 - SCK, MOSI, MISO
  PINSEL3_bit.P1_20 = 3;  // SCK
  PINSEL3_bit.P1_23 = 3;  // MISO
  PINSEL3_bit.P1_24 = 3;  // MOS1

  // Chip select
  LCD_CS_FDIR |= LCD_CS_MASK;

  GLCD_SPI_ChipSelect(FALSE);

  // Spi init
  PCONP_bit.PCSSP0 = 1;			// SSP0 clock enable
  SSP0CR1_bit.SSE  = 0;     // Disable module
  SSP0CR1_bit.LBM  = 0;     // Disable Loop Back Mode
  SSP0CR1_bit.MS   = 0;     // Master mode
  SSP0CR0_bit.FRF  = 0;			// SPI
  SSP0CR0_bit.CPOL = 0;
	SSP0CR0_bit.CPHA = 0;
  SSP0IMSC = 0;             // disable all interrupts
  SSP0DMACR = 0;            // disable DMA
  SSP0CR1_bit.SSE  = 1;     // Enable module
  for (Int32U i = 0; i < 8; i++ )
  {
    volatile Int32U Dummy = SSP0DR; // clear the RxFIFO
  }
  // Set SSP clock frequency
  GLCD_SPI_SetClockFreq(Clk);
  // Set data width
  GLCD_SPI_SetWordWidth(Width);

}

/*************************************************************************
 * Function Name: GLCD_SPI_TranserByte
 * Parameters: Int32U Data
 * Return: Int32U
 *
 * Description: Transfer byte from SSP0
 *
 *************************************************************************/
Int32U GLCD_SPI_TranserByte (Int32U Data)
{
  while(!SSP0SR_bit.TNF);
  SSP0DR = Data;
  while(SSP0SR_bit.BSY);
  return(SSP0DR);
}

/*************************************************************************
 * Function Name: GLCD_SPI_SendBlock
 * Parameters: pInt8U pData, Int32U Size
 *
 * Return: void
 *
 * Description: Write block of data to SSP
 *
 *************************************************************************/
void GLCD_SPI_SendBlock (pInt8U pData, Int32U Size)
{
Int32U OutCount = Size;
  while (OutCount)
  {
    while(SSP0SR_bit.TNF && OutCount)
    {
      SSP0DR = *pData++ | 0x100;  // Data
      --OutCount;
    }
  }
  while(SSP0SR_bit.BSY);
  // draining RX Fifo
  while (SSP0SR_bit.RNE)
  {
    volatile Int32U Dummy = SSP0DR;
  }
}

/*************************************************************************
 * Function Name: GLCD_SPI_ReceiveBlock
 * Parameters: pInt8U pData, Int32U Size
 *
 * Return: void
 *
 * Description: Read block of data from SSP
 *
 *************************************************************************/
void GLCD_SPI_ReceiveBlock (pInt8U pData, Int32U Size)
{
Int32U Delta = 0;
  while (Size || Delta)
  {
    while(SSP0SR_bit.TNF && (Delta < SSP_FIFO_SIZE) && Size)
    {
      SSP0DR = 0xFFFF;
      --Size; ++Delta;
    }
    while (SSP0SR_bit.RNE)
    {
      *pData++ = SSP0DR;
       --Delta;
    }
  }
}
