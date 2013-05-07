/*****************************************************************************
 *   dma.c:  DMA module file for NXP LPC17xx Family Microprocessors
 *
 *   Copyright(C) 2009, NXP Semiconductor
 *   All rights reserved.
 *
 *   History
 *   2009.05.26  ver 1.00    Prelimnary version, first Release
 *
******************************************************************************/
#include "lpc17xx.h"
#include "i2s.h"
#include "dma.h"

#if I2S_DMA_ENABLED
volatile uint32_t DMATCCount = 0;
volatile uint32_t DMAErrCount = 0;
volatile uint32_t I2SDMA0Done = 0;
volatile uint32_t I2SDMA1Done = 0;

/******************************************************************************
** Function name:		DMA_IRQHandler
**
** Descriptions:		DMA interrupt handler
**
** parameters:			None
** Returned value:		None
** 
******************************************************************************/
void DMA_IRQHandler(void) 
{
  uint32_t regVal;

  regVal = LPC_GPDMA->DMACIntTCStat;
  if ( regVal )
  {
	DMATCCount++;
	LPC_GPDMA->DMACIntTCClear |= regVal;
	if ( regVal & 0x01 )
	{
	  I2SDMA0Done = 1;
	}
	else if ( regVal & 0x02 )
	{
	  I2SDMA1Done = 1;
	}
  } 

  regVal = LPC_GPDMA->DMACIntErrStat;
  if ( regVal )
  {
	DMAErrCount++;
	LPC_GPDMA->DMACIntErrClr |= regVal;
  }

}

/******************************************************************************
** Function name:		DMA_Init
**
** Descriptions:		
**
** parameters:			
** Returned value:		
** 
******************************************************************************/
uint32_t DMA_Init( uint32_t ChannelNum, uint32_t DMAMode )
{
  if ( ChannelNum == 0 )
  {
	LPC_GPDMA->DMACIntTCClear = 0x01;   
	if ( DMAMode == M2P )
	{
	  /* Ch0 set for M2P transfer from mempry to I2S TX FIFO. */
	  LPC_GPDMACH0->DMACCSrcAddr = DMA_SRC;
	  LPC_GPDMACH0->DMACCDestAddr = DMA_I2S_TX_FIFO;
	  /* The burst size is set to 1. Terminal Count Int enable */
	  LPC_GPDMACH0->DMACCControl = (DMA_SIZE & 0x0FFF) | (0x00 << 12) | (0x00 << 15)
		| (1 << 26) | 0x80000000;
	}
	else if ( DMAMode == P2M )
	{
	  /* Ch0 set for P2M transfer from I2S RX FIFO to memory. */
	  LPC_GPDMACH0->DMACCSrcAddr = DMA_I2S_RX_FIFO;
	  LPC_GPDMACH0->DMACCDestAddr = DMA_DST;
	  /* The burst size is set to 1. Terminal Count Int enable. */
	  LPC_GPDMACH0->DMACCControl = (DMA_SIZE & 0x0FFF) | (0x00 << 12) | (0x00 << 15)
		| (1 << 27) | 0x80000000;
	}
	else if ( DMAMode == P2P )
	{
	  /* Ch0 set for P2P transfer from I2S DAO to I2S DAI. */
	  LPC_GPDMACH0->DMACCSrcAddr = DMA_I2S_TX_FIFO;
	  LPC_GPDMACH0->DMACCDestAddr = DMA_I2S_RX_FIFO;
	  /* The burst size is set to 32. */
	  LPC_GPDMACH0->DMACCControl = (DMA_SIZE & 0x0FFF) | (0x04 << 12) | (0x04 << 15) 
		| 0x80000000;
	}
	else
	{
	  return ( 0 );
	}
  }
  else if ( ChannelNum == 1 )
  {   
	LPC_GPDMA->DMACIntTCClear = 0x02;
	if ( DMAMode == M2P )
	{
	  /* Ch1 set for M2P transfer from mempry to I2S TX FIFO. */
	  LPC_GPDMACH1->DMACCSrcAddr = DMA_SRC;
	  LPC_GPDMACH1->DMACCDestAddr = DMA_I2S_TX_FIFO;
	  /* The burst size is set to 1. Terminal Count Int enable. */
	  LPC_GPDMACH1->DMACCControl = (DMA_SIZE & 0x0FFF) | (0x00 << 12) | (0x00 << 15)
		| (1 << 26) | 0x80000000;
	}
	else if ( DMAMode == P2M )
	{
	  /* Ch1 set for P2M transfer from I2S RX FIFO to memory. */
	  LPC_GPDMACH1->DMACCSrcAddr = DMA_I2S_RX_FIFO;
	  LPC_GPDMACH1->DMACCDestAddr = DMA_DST;
	  /* The burst size is set to 1. Terminal Count Int enable. */
	  LPC_GPDMACH1->DMACCControl = (DMA_SIZE & 0x0FFF) | (0x00 << 12) | (0x00 << 15)
		| (1 << 27) | 0x80000000;
	}
	else if ( DMAMode == P2P )
	{
	  /* Ch1 set for P2P transfer from I2S DAO to I2S DAI. */
	  LPC_GPDMACH1->DMACCSrcAddr = DMA_I2S_TX_FIFO;
	  LPC_GPDMACH1->DMACCDestAddr = DMA_I2S_RX_FIFO;
	  /* The burst size is set to 32. */
	  LPC_GPDMACH1->DMACCControl = (DMA_SIZE & 0x0FFF) | (0x04 << 12) | (0x04 << 15) 
		| 0x80000000;
	}
	else
	{
	  return ( 0 );
	}
  }
  else
  {
	return ( 0 );
  }
  return( 1 );
}

#endif	/* end if DMA_ENABLED */

/******************************************************************************
**                            End Of File
******************************************************************************/
