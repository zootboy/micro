/*****************************************************************************
 *   timer.c:  Timer C file for NXP LPC17xx Family Microprocessors
 *
 *   Copyright(C) 2009, NXP Semiconductor
 *   All rights reserved.
 *
 *   History
 *   2009.05.26  ver 1.00    Prelimnary version, first Release
 *
******************************************************************************/
#include "lpc17xx.h"
#include "timer.h"

volatile uint32_t timer0_counter = 0;
volatile uint32_t timer1_counter = 0;

/*****************************************************************************
** Function name:		delayMs
**
** Descriptions:		Start the timer delay in milo seconds
**						until elapsed
**
** parameters:			timer number, Delay value in milo second			 
** 						
** Returned value:		None
** 
*****************************************************************************/
void delayMs(uint8_t timer_num, uint32_t delayInMs)
{
  if ( timer_num == 0 )
  {
	LPC_TIM0->TCR = 0x02;		/* reset timer */
	LPC_TIM0->PR  = 0x00;		/* set prescaler to zero */
	LPC_TIM0->MR0 = delayInMs * (9000000 / 1000-1);
	LPC_TIM0->IR  = 0xff;		/* reset all interrrupts */
	LPC_TIM0->MCR = 0x04;		/* stop timer on match */
	LPC_TIM0->TCR = 0x01;		/* start timer */
  
	/* wait until delay time has elapsed */
	while (LPC_TIM0->TCR & 0x01);
  }
  else if ( timer_num == 1 )
  {
	LPC_TIM1->TCR = 0x02;		/* reset timer */
	LPC_TIM1->PR  = 0x00;		/* set prescaler to zero */
	LPC_TIM1->MR0 = delayInMs * (9000000 / 1000-1);
	LPC_TIM1->IR  = 0xff;		/* reset all interrrupts */
	LPC_TIM1->MCR = 0x04;		/* stop timer on match */
	LPC_TIM1->TCR = 0x01;		/* start timer */
  
	/* wait until delay time has elapsed */
	while (LPC_TIM1->TCR & 0x01);
  }
  return;
}


/******************************************************************************
** Function name:		Timer0_IRQHandler
**
** Descriptions:		Timer/Counter 0 interrupt handler
**
** parameters:			None
** Returned value:		None
** 
******************************************************************************/
void TIMER0_IRQHandler (void) 
{  
  LPC_TIM0->IR = 1;			/* clear interrupt flag */
  timer0_counter++;
  return;
}


/******************************************************************************
** Function name:		Timer1_IRQHandler
**
** Descriptions:		Timer/Counter 1 interrupt handler
**
** parameters:			None
** Returned value:		None
** 
******************************************************************************/
void TIMER1_IRQHandler (void)  
{  
  LPC_TIM1->IR = 1;			/* clear interrupt flag */
  timer1_counter++;
  return;
}



/******************************************************************************
** Function name:		enable_timer
**
** Descriptions:		Enable timer
**
** parameters:			timer number: 0 or 1
** Returned value:		None
** 
******************************************************************************/
void enable_timer( uint8_t timer_num )
{
  if ( timer_num == 0 )
  {
	LPC_TIM0->TCR = 1;
  }
  else
  {
	LPC_TIM1->TCR = 1;
  }
  return;
}

/******************************************************************************
** Function name:		disable_timer
**
** Descriptions:		Disable timer
**
** parameters:			timer number: 0 or 1
** Returned value:		None
** 
******************************************************************************/
void disable_timer( uint8_t timer_num )
{
  if ( timer_num == 0 )
  {
	LPC_TIM0->TCR = 0;
  }
  else
  {
	LPC_TIM1->TCR = 0;
  }
  return;
}

/******************************************************************************
** Function name:		reset_timer
**
** Descriptions:		Reset timer
**
** parameters:			timer number: 0 or 1
** Returned value:		None
** 
******************************************************************************/
void reset_timer( uint8_t timer_num )
{
  uint32_t regVal;

  if ( timer_num == 0 )
  {
	regVal = LPC_TIM0->TCR;
	regVal |= 0x02;
	LPC_TIM0->TCR = regVal;
  }
  else
  {
	regVal = LPC_TIM1->TCR;
	regVal |= 0x02;
	LPC_TIM1->TCR = regVal;
  }
  return;
}
/****************************************Copyright (c)****************************************************
**                                 http://www.PowerAVR.com
**								   http://www.PowerMCU.com
**--------------File Info---------------------------------------------------------------------------------
** File name:           timer.c
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
uint32_t init_timer ( uint8_t timer_num, uint32_t TimerInterval ) 
{
  if ( timer_num == 0 )
  {
	timer0_counter = 0;
	LPC_TIM0->MR0 = TimerInterval;
	LPC_TIM0->MCR = 3;				/* Interrupt and Reset on MR0 */

	NVIC_EnableIRQ(TIMER0_IRQn);
	return (1);
  }
  else if ( timer_num == 1 )
  {
	timer1_counter = 0;
	LPC_TIM1->MR0 = TimerInterval;
	LPC_TIM1->MCR = 3;				/* Interrupt and Reset on MR1 */

	NVIC_EnableIRQ(TIMER1_IRQn);
	return (1);
  }
  return (0);
}

/******************************************************************************
**                            End Of File
******************************************************************************/
