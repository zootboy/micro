/*
* ADC functions for attiny13.
* Author: Guido Socher, Copyright: GPL 
* http://tuxgraphics.org/electronics/
*/
#include <avr/io.h>

//----------------EDIT HERE----------------------------------------
// ~~~ VDIV ~~~
// VDIV = (Rx+Ry)/Rx, this is the division factor of the resistor 
//      voltage divider. The circuit goes:
// Vcc -> Ry -V- Rx -> Gnd
//            |
//           ADC                                  
//
// In this case, we're using a 1000 ohm and a 1000 ohm to get a 
//      Vdiv of 2. You should use 1% tolerance resistors for this.
// 
#define VDIV 2

// ~~~ Vref ~~~
// This is the reference voltage provided to the ADC. The internal ref.
//       can usually be used without much issue. Refer to the datasheet
//       for the internal voltage value. For the mega8, it's 2.56v.
//       For the tiny13, it's 1.1v. 
#define VREF 2.56

// ~~~ CALIBRATION ~~~
// This is the calibration value.
// Due to tolerances and uncertainties, the meter will not be perfectly
//      accurate. Use this value to match the value output by the ADC
//      to the actual voltage as read by a trusted meter.
//
// 		Raise it to push the meter up, lower it to push it down. 
// 		Use 0.01 increments. Known good: 0.98
//      Use 1 as base value. 
#define CALIB 0.98

//----------------END EDIT----------------------------------------


void adcOn(void)
{
	// Set up the ADC and enable the interrupt.
   
	// Use the intenal vref of 2.56v
    ADMUX = (1<<REFS1)|(1<<REFS0);  	
	ADCSRB = (1<<REFS2); // ...with a bypass capacitor on Vref.
	
	// Switch off digital input lines.
	// NOTE: THIS IS HARD CODED TO THE CHANNEL (0). FIXME IF CHANGING CHANNEL. 
    DIDR0=(1<<ADC0D)|(1<<AREFD);
  
	// Enable the A/D Converter, set the prescaler (125kHz), enable the interrupt.
    ADCSRA=(1<<ADEN)|(1<<ADPS1)|(1<<ADPS0)|(1<<ADIE);


}

void adcOff(void)
{
	ADCSRA &= ~((1<<ADEN)|(1<<ADIE)); 
	// Shut off the ADC and disable the interrupt. 
	// This lowers the power consumption of the uC.
}

// convert adc reading to voltage (display values)
double analog2v(unsigned int aval)
{
        double r;
		//            ADCout * Vref * Vdiv
        // Voltage = ---------------------- * Calibration Value
		//                     1024
		//
		r = ((double)aval * VREF * VDIV * CALIB)/(1024); // Hint: 1024 is the resolution of the ADC.
        return(r);
}


// Start the ADC conversion. Results are handled by an interrupt in main.c.
void startConvert(void) 
{
	// Set channel
	//ADMUX &= ~0x03; // Clear out existing channel.
	//ADMUX |= (CHANNEL & 0x03); // Add in new channel.
	// This is unnecessary because channel 0 sets all mux vals to 0.
	
    //  start conversion 
	
	//if(bit_is_clear(ADCSRA,ADSC))
		ADCSRA |= (1<<ADSC); 
}


