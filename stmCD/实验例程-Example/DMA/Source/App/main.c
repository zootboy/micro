/****************************************Copyright (c)****************************************************
**                                 http://www.PowerAVR.com
**								   http://www.PowerMCU.com
**--------------File Info---------------------------------------------------------------------------------
** File name:           main.c
** Last modified Date:  2010-05-12
** Last Version:        V1.00
** Descriptions:        The main() function example template
**
**--------------------------------------------------------------------------------------------------------
** Created by:          PowerAVR
** Created date:        2010-05-10
** Version:             V1.00
** Descriptions:        ±àÐ´Ê¾Àý´úÂë
**
**--------------------------------------------------------------------------------------------------------       
*********************************************************************************************************/
#include "LPC17xx.h"
#include "dma.h"

extern volatile uint32_t DMATCCount;

/******************************************************************************
**   Main Function  main()
******************************************************************************/
int main (void)
{	
  uint32_t i;
  uint32_t *src_addr, *dest_addr;
  
  SystemInit();    
  
  src_addr = (uint32_t *)DMA_SRC;
  dest_addr = (uint32_t *)DMA_DST;
  for ( i = 0; i < DMA_SIZE/4; i++ )
  {
	*src_addr++ = i;
	*dest_addr++ = 0;
  }
	    
  DMA_Init( M2M );
  LPC_GPDMACH0->DMACCConfig |= 0x08001;	/* Enable channel and IE bit */

  while ( !DMATCCount );		/* Wait until DMA is done */

  /* Verify result */
  src_addr = (uint32_t *)DMA_SRC;
  dest_addr = (uint32_t *)DMA_DST;
  for ( i = 0; i < DMA_SIZE/4; i++ )
  {
	if ( *src_addr++ != *dest_addr++ )
	{
	  while ( 1 );	/* fatal error */
	}
  }
}

/******************************************************************************
**                            End Of File
******************************************************************************/
