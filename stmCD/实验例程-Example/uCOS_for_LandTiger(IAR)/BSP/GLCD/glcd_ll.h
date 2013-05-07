/*************************************************************************
 *
 *    Used with ICCARM and AARM.
 *
 *    (c) Copyright IAR Systems 2006
 *
 *    File name   : glcd_ll.h
 *    Description : GLCD low level include file
 *
 *    History :
 *    1. Date        : December 2, 2006
 *       Author      : Stanimir Bonev
 *       Description : Create
 *
 *    $Revision: 28532 $
 **************************************************************************/

#include    "arm_comm.h"
#include    "board.h"
#include    "drv_glcd_cnfg.h"
#include    "drv_glcd.h"


#ifndef __GLCD_LL_H
#define __GLCD_LL_H

#define BACKLIGHT_OFF   0x40
#define BACKLIGHT_ON    0x20
#define SSP_FIFO_SIZE   8

extern Int32U SYS_GetFpclk(Int32U Periphery);

/*************************************************************************
 * Function Name: GLCD_SetReset
 * Parameters: Boolean State
 * Return: none
 *
 * Description: Set reset pin state
 *
 *************************************************************************/
void GLCD_SetReset (Boolean State);

/*************************************************************************
 * Function Name: GLCD_Backlight
 * Parameters: Int8U Light
 * Return: none
 *
 * Description: Set backlight level
 *
 *************************************************************************/
void GLCD_Backlight (Int8U Light);

/*************************************************************************
 * Function Name: GLCD_LLInit
 * Parameters: none
 * Return: none
 *
 * Description: Init Reset and Backlight control outputs
 *
 *************************************************************************/
void GLCD_LLInit (void);

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
void GLCD_SPI_ChipSelect(Boolean Select);

/*************************************************************************
 * Function Name: GLCD_SPI_SetWordWidth
 * Parameters: Int32U Width
 * Return: Boolean
 *
 * Description: Set SSP 0 word width
 *
 *************************************************************************/
Boolean GLCD_SPI_SetWordWidth (Int32U Width);

/*************************************************************************
 * Function Name: GLCD_SPI_SetClockFreq
 * Parameters: Int32U Frequency
 * Return: Int32U
 *
 * Description: Set SSP 0 clock
 *
 *************************************************************************/
Int32U GLCD_SPI_SetClockFreq (Int32U Frequency);

/*************************************************************************
 * Function Name: GLCD_SPI_Init
 * Parameters: Int32U Clk, Int32U Width
 * Return: none
 *
 * Description: Init SSP0
 *
 *************************************************************************/
void GLCD_SPI_Init(Int32U Clk, Int32U Width);

/*************************************************************************
 * Function Name: GLCD_SPI_TranserByte
 * Parameters: Int32U Data
 * Return: Int32U
 *
 * Description: Transfer byte from SSP0
 *
 *************************************************************************/
Int32U GLCD_SPI_TranserByte (Int32U Data);

/*************************************************************************
 * Function Name: GLCD_SPI_SendBlock
 * Parameters: pInt8U pData, Int32U Size
 *
 * Return: void
 *
 * Description: Read byte from SSP
 *
 *************************************************************************/
void GLCD_SPI_SendBlock (pInt8U pData, Int32U Size);

/*************************************************************************
 * Function Name: GLCD_SPI_ReceiveBlock
 * Parameters: pInt8U pData, Int32U Size
 *
 * Return: void
 *
 * Description: Read byte from SSP
 *
 *************************************************************************/
void GLCD_SPI_ReceiveBlock (pInt8U pData, Int32U Size);

#endif // __GLCD_LL_H
