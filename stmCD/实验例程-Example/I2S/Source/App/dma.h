/*****************************************************************************
 *   dma.h:  Header file for NXP LPC17xx Family Microprocessors
 *
 *   Copyright(C) 2009, NXP Semiconductor
 *   All rights reserved.
 *
 *   History
 *   2009.05.26  ver 1.00    Prelimnary version, first Release
 *
******************************************************************************/
#ifndef __DMA_H 
#define __DMA_H

/* USB RAM is used for GPDMA operation. */
//#define DMA_SRC			0x7FD00000	
//#define DMA_DST			0x7FD01000		
//#define DMA_I2S_TX_FIFO	0xE0088008
//#define	DMA_I2S_RX_FIFO	0xE008800C

#define DMA_SRC			0x20080000	
#define DMA_DST			0x20081000
#define DMA_I2S_TX_FIFO	0x400A8008
#define	DMA_I2S_RX_FIFO	0x400A800C
 
#define DMA_SIZE		0x200

/* DMA mode */
#define M2M				0x00
#define M2P				0x01
#define P2M				0x02
#define P2P				0x03

extern void DMA_IRQHandler( void ); 
extern uint32_t DMA_Init( uint32_t ChannelNum, uint32_t DMAMode );

#endif /* end __DMA_H */
/****************************************************************************
**                            End Of File
****************************************************************************/
