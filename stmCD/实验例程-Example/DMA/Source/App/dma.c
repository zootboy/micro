/****************************************Copyright (c)****************************************************
**                                 http://www.PowerAVR.com
**								   http://www.PowerMCU.com
**--------------File Info---------------------------------------------------------------------------------
** File name:           dma.c
** Last modified Date:  2010-05-12
** Last Version:        V1.00
** Descriptions:        
**
**--------------------------------------------------------------------------------------------------------
** Created by:          PowerAVR
** Created date:        2010-05-10
** Version:             V1.00
** Descriptions:        ±àÐ´Ê¾Àý´úÂë
**
**--------------------------------------------------------------------------------------------------------       
*********************************************************************************************************/
#include "lpc17xx.h"
#include "dma.h"

volatile uint32_t DMATCCount = 0;
volatile uint32_t DMAErrCount = 0;

/******************************************************************************
** Function name:		DMA_IRQHandler
**
** Descriptions:		DMA interrupt handler
**
** parameters:			None
** Returned value:		None
** 
******************************************************************************/
void DMA_IRQHandler (void) 
{
  uint32_t regVal;

  regVal = LPC_GPDMA->DMACIntTCStat;
  if ( regVal )
  {
	DMATCCount++;
	LPC_GPDMA->DMACIntTCClear |= regVal;
  } 

  regVal = LPC_GPDMA->DMACIntErrStat;
  if ( regVal )
  {
	DMAErrCount++;
	LPC_GPDMA->DMACIntErrClr |= regVal;
  } 
  return;
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
uint32_t DMA_Init( uint32_t DMAMode )
{
  LPC_SC->PCONP |= (1 << 29);	/* Enable GPDMA clock */

  /* clear all interrupts on channel 0 */
  LPC_GPDMA->DMACIntTCClear = 0x01;
  LPC_GPDMA->DMACIntErrClr = 0x01;
   
  if ( DMAMode == M2M )
  {
	/* Ch0 is used for M2M test, for M2P and P2M, go to peripheral directories
	where both DAM and non DMA examples are provided. */
	LPC_GPDMACH0->DMACCSrcAddr = DMA_SRC;
	LPC_GPDMACH0->DMACCDestAddr = DMA_DST;
	/* Terminal Count Int enable */
	LPC_GPDMACH0->DMACCControl = ((DMA_SIZE/4) & 0x0FFF) | (0x04 << 12) | (0x04 << 15) 
		| (0x02 << 18) | (0x02 << 21) | (1 << 26) | (1 << 27) | 0x80000000;	
  }
  else
  {
	return ( 0 );
  }
	
  LPC_GPDMA->DMACConfig = 0x01;	/* Enable DMA channels, little endian */
  while ( !(LPC_GPDMA->DMACConfig & 0x01) );    

  NVIC_EnableIRQ(DMA_IRQn);
  return (1);
}

/******************************************************************************
**                            End Of File
******************************************************************************/
