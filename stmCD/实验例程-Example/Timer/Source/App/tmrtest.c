/****************************************Copyright (c)****************************************************
**                                 http://www.PowerAVR.com
**								   http://www.PowerMCU.com
**--------------File Info---------------------------------------------------------------------------------
** File name:           tmrtest.c
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
#include "lpc17xx.h"
#include "timer.h"

extern uint32_t timer0_counter;

/*****************************************************************************
**   Main Function  main()
*****************************************************************************/
int main (void)
{	    		
  uint32_t counter = 0;
   
  SystemInit();
  
  LPC_GPIO2->FIODIR = 0x000000FF;		/* P2.0...P2.7 defined as Outputs */
  LPC_GPIO2->FIOCLR = 0x000000FF;		/* turn off all the LEDs */
    
  init_timer( 0, TIME_INTERVAL ); // 10ms	
  enable_timer( 0 );

  while (1) 
  {					/* Loop forever */
	if ( timer0_counter >= (50 * counter) )	   // 0.5s
	{
	  LPC_GPIO2->FIOSET = 1 << counter;
	  counter++;
	  if ( counter > 8 )
	  {
		counter = 0;	
		timer0_counter = 0;
		LPC_GPIO2->FIOCLR = 0x000000FF;
	  }
	}
  }
}

/*****************************************************************************
**                            End Of File
******************************************************************************/
