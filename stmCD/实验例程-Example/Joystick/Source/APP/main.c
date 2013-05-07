/**************************************************************************//**
 * @file     main.c
 * @brief    CMSIS Cortex-M3 Joystick example
 *   
 * @version  V1.30
 * @date     24. Jan 2010
 * @Design by PowerAVR
 * @note
 ******************************************************************************/

#include "lpc17xx.h"

/*------------------------------------------------------------------------------
  configer LED pins
 *------------------------------------------------------------------------------*/
void LED_Config(void) {

  LPC_GPIO2->FIODIR   |= ((1UL<< 0)|(1UL<< 1)|
  						  (1UL<< 2)|(1UL<< 3)|
                          (1UL<< 4)|(1UL<< 5)|
                          (1UL<< 6)|(1UL<< 7)) ; /* P2.0..7             is output (LED) */

  LPC_GPIO1->FIODIR   &= ~((1<<25)|(1<<26)|
                           (1<<27)|(1<<28)|
                           (1<<29)           ); /* P1.25..29    is input  (Joystick) */

  LPC_GPIO0->FIODIR = 0x00200000; 
  LPC_GPIO0->FIOPIN |=  0x00200000; 
}

/*----------------------------------------------------------------------------
  MAIN function
 *----------------------------------------------------------------------------*/
int main (void) 
{ 
	uint8_t kbd_val;

  	LED_Config();                             
 	SystemInit();                               /* initialize clocks */
  	while(1) 
  	{
	 	kbd_val = (LPC_GPIO1->FIOPIN >> 25) & 0x1F; 
  		LPC_GPIO2->FIOPIN = (~kbd_val) & 0x1F;
	}
}

