/****************************************Copyright (c)****************************************************
**                                 http://www.PowerAVR.com
**								   http://www.PowerMCU.com
**--------------File Info---------------------------------------------------------------------------------
** File name:           adc.c
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
#include "lpc17xx.h"                              /* LPC17xx definitions    */
#include "adc.h"

/*----------------------------------------------------------------------------
  initialize ADC Pins
 *----------------------------------------------------------------------------*/
void ADC_Init (void) {

  LPC_PINCON->PINSEL3 &= ~(3UL<<30);               /* P1.31 is GPIO */
  LPC_PINCON->PINSEL3 |=  (3UL<<30);               /* P1.31 is AD0.5 */

  LPC_SC->PCONP       |=  (1<<12);               /* Enable power to ADC block */

  LPC_ADC->ADCR        =  (1<< 5) |              /* select AD0.5 pin */
                          (4<< 8) |              /* ADC clock is 25MHz/5 */
                          (1<<21);               /* enable ADC */ 
}

/*----------------------------------------------------------------------------
  start ADC Conversion
 *----------------------------------------------------------------------------*/
void ADC_StartCnv (void) {
  LPC_ADC->ADCR &= ~(7<<24);                     /* stop conversion  */
  LPC_ADC->ADCR |=  (1<<24);                     /* start conversion */
}


/*----------------------------------------------------------------------------
  stop ADC Conversion
 *----------------------------------------------------------------------------*/
void ADC_StopCnv (void) {
  LPC_ADC->ADCR &= ~(7<<24);                     /* stop conversion */
}

/*----------------------------------------------------------------------------
  get converted ADC value
 *----------------------------------------------------------------------------*/
uint32_t ADC_GetCnv (void) {
  uint32_t adGdr;
//  uint32_t adDr2;

  while (!(LPC_ADC->ADGDR & (1UL<<31)));         /* Wait for Conversion end */
  adGdr = LPC_ADC->ADGDR;
//  adDr2 = LPC_ADC->ADDR2;
  return((adGdr >> 4) & ADC_VALUE_MAX);          /* read converted value */
}

/*------------------------------------------------------------------------------
  read a converted value from the Analog/Digital converter
 *------------------------------------------------------------------------------*/
uint16_t ADC_Get (void) {
  uint16_t val;

  ADC_StartCnv();                                 /* start A/D conversion */
  val = ADC_GetCnv();                             /* use upper 8 bits of 12 bit AD conversion */
  ADC_StopCnv();                                  /* stop A/D conversion */
	
  return (val);
}
/*********************************************************************************
**                            End Of File
*********************************************************************************/
