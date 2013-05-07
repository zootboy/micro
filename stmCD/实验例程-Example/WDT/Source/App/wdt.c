/****************************************Copyright (c)****************************************************
**                                 http://www.PowerAVR.com
**								   http://www.PowerMCU.com
**--------------File Info---------------------------------------------------------------------------------
** File name:           wdt.c
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
#include "LPC17xx.h"
#include "timer.h"
#include "wdt.h"

volatile uint32_t wdt_counter;

/*****************************************************************************
** Function name:		WDT_IRQHandler
**
** Descriptions:		Watchdog timer interrupt handler
**
** parameters:			None
** Returned value:		None
** 
*****************************************************************************/
void WDT_IRQHandler(void) 
{
  LPC_WDT->WDMOD &= ~WDTOF;		/* clear the time-out terrupt flag */
  wdt_counter++;
  return;
}

/*****************************************************************************
** Function name:		WDTInit
**
** Descriptions:		Initialize watchdog timer, install the
**				watchdog timer interrupt handler
**
** parameters:			None
** Returned value:		true or false, return false if the VIC table
**				is full and WDT interrupt handler can be
**				installed.
** 
*****************************************************************************/
uint32_t WDTInit( void )
{
  wdt_counter = 0;

  NVIC_EnableIRQ(WDT_IRQn);

  LPC_WDT->WDTC = WDT_FEED_VALUE;	/* once WDEN is set, the WDT will start after feeding */
  LPC_WDT->WDMOD = WDEN;

  LPC_WDT->WDFEED = 0xAA;		/* Feeding sequence */
  LPC_WDT->WDFEED = 0x55;    
  return( 1 );
}

/*****************************************************************************
** Function name:		WDTFeed
**
** Descriptions:		Feed watchdog timer to prevent it from timeout
**
** parameters:			None
** Returned value:		None
** 
*****************************************************************************/
void WDTFeed( void )
{
  LPC_WDT->WDFEED = 0xAA;		/* Feeding sequence */
  LPC_WDT->WDFEED = 0x55;
  return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
