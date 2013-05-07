/*****************************************************************************
 *   i2stest.c:  main C entry file for NXP LPC17xx Family Microprocessors
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

extern volatile uint8_t *I2STXBuffer, *I2SRXBuffer;
extern volatile uint32_t I2SReadLength;
extern volatile uint32_t I2SWriteLength;
extern volatile uint32_t I2SRXDone, I2STXDone;
extern volatile uint32_t I2SDMA0Done, I2SDMA1Done;

/*******************************************************************************
**   Main Function  main()
*******************************************************************************/
int main (void)
{
  uint32_t i;

  SystemInit();
  /* The test program is to connect CLK, WS, and SDA lines between the
  TX and RX. DAO is the master output, DAI is the slave input. This test
  is not a real-world application but test both TX and RX channel in
  a single program. However, due to the sync issue, the TX will start with 
  MUTE data 0 once it starts while RX is not ready. So, it may begins
  with some MUTE value in the beginning of the RX buffer. This is beyond
  control unless throw away the very first few bytes in the RX buffer. 
  In this program, the very first byte is not compared between the TX buffer 
  and RX buffer due to this synchonization issue. */

  /* Configure temp register before reading */
  for ( i = 0; i < BUFSIZE; i++ )	/* clear buffer */
  {
	I2STXBuffer[i] = i;
	I2SRXBuffer[i] = 0;
  }

  if ( I2SInit() == 0 )	/* initialize I2S */
  {
	while ( 1 );			/* Fatal error */
  }

#if I2S_DMA_ENABLED
  /* USB RAM is used for test.
  Please note, Ethernet has its own SRAM, but GPDMA can't access
  that. GPDMA can access USB SRAM and IRAM. Ethernet DMA controller can 
  access both IRAM and Ethernet SRAM. */
  LPC_SC->PCONP |= (1 << 29);	/* Enable GPDMA clock */

  LPC_GPDMA->DMACIntTCClear = 0x03;
  LPC_GPDMA->DMACIntErrClr = 0x03;

  LPC_GPDMA->DMACConfig = 0x01;	/* Enable DMA channels, little endian */
  while ( !(LPC_GPDMA->DMACConfig & 0x01) );

  /* on DMA channel 0, Source is memory, destination is I2S TX FIFO, 
  on DMA channel 1, source is I2S RX FIFO, Destination is memory */
  /* Enable channel and IE bit */
  DMA_Init( 0, M2P );
  LPC_GPDMACH0->DMACCConfig |= 0x18001 | (0x00 << 1) | (0x05 << 6) | (0x01 << 11);
  DMA_Init( 1, P2M );
  LPC_GPDMACH1->DMACCConfig |= 0x08001 | (0x06 << 1) | (0x00 << 6) | (0x02 << 11);
  
  NVIC_EnableIRQ(DMA_IRQn);
	  
  I2SStart();
  
  LPC_I2S->I2SDMA2 = (0x01<<0) | (0x08<<8);	/* Channel 2 is for RX, enable RX first. */
  LPC_I2S->I2SDMA1 = (0x01<<1) | (0x01<<16);/* Channel 1 is for TX. */

  /* Wait for both DMA0 and DMA1 to finish before verifying. */
  while ( !I2SDMA0Done || !I2SDMA1Done );
#else
  /* Not DMA mode, enable I2S interrupts. */
  /* RX FIFO depth is 1, TX FIFO depth is 8. */
  I2SStart();
  LPC_I2S->I2SIRQ = (8 << 16) | (1 << 8) | (0x01 << 0);

  while ( I2SWriteLength < BUFSIZE )
  {
	while (((LPC_I2S->I2SSTATE >> 16) & 0xFF) == TXFIFO_FULL);
	LPC_I2S->I2STXFIFO = I2STXBuffer[I2SWriteLength++];
  }

  I2STXDone = 1;
  /* Wait for RX and TX complete before comparison */
  while ( !I2SRXDone || !I2STXDone );
#endif

  /* Validate TX and RX buffer */
  for ( i=1; i<BUFSIZE; i++ )
  {
	if ( I2SRXBuffer[i] != I2STXBuffer[i-1] )
	{
	  while ( 1 );	/* Validation error */
	}
  }
  return 0;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
