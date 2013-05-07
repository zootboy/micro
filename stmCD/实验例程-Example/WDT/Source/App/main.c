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
#include "timer.h"
#include "wdt.h"

extern volatile uint32_t timer0_counter;
volatile uint32_t feed_counter = 0;

/*****************************************************************************
**   Main Function  main()
******************************************************************************/
int main (void)
{ 
	SystemInit();
		    		
  /*** The main Function is an endless loop ****/
  init_timer( 0, TIME_INTERVAL);
    
  WDTInit();
  enable_timer( 0 );

  while( 1 ) 
  {
	if ( timer0_counter > 0 )
	{
	  /* Feed the watchdog timer */
	  feed_counter++;
	  WDTFeed();
	  timer0_counter = 0;
	}
  }
}

/*********************************************************************************
**                            End Of File
*********************************************************************************/
