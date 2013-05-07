/* Lithium Ion battery circuit */

/* Include useful pre-defined functions */
#include <avr/interrupt.h>    
#define F_CPU 8000000	      // Sets up the default speed for delay.h
#include <avr/io.h>           // Defines pins, ports, etc to make programs easier to read
#include <util/delay.h>
#include <math.h>
#include <avr/sleep.h>

#include "sevseg.h"
#include "analog.h"

#define WAITFOR 400




void delay_ms(unsigned int ms)
{
    // if we would use the library function _delay_ms
    // everywhere then the code would become very fat(?)
    // We just need integers therefore we wrap it.
    while(ms){
        _delay_ms(1);
        ms--;
    }
}

void battmeter(double voltage)
{
	DDRD  |= 31; // Enable 5 outs
	PORTD &= ~31; // Make sure they're all off.
	
	// All the math is to convert the 3v - 4.2v range of the 
	// battery to a percentage (0% - 100%)
	double perc = voltage - 3.0; // 0 - 1.2
	perc *= 83.333; // 0 - 99.9996
	
	// Now we turn on the lights.
	               PORTD |= _BV(0); // The red light is always on.
	//delay_ms(10);
	if(perc >= 25) PORTD |= _BV(1); // Orange at 25%
	//delay_ms(10);
	if(perc >= 50) PORTD |= _BV(2); // 1 green at 50%
	//delay_ms(10);
	if(perc >= 65) PORTD |= _BV(3); // 2 greens at 65%
	//delay_ms(10);
	if(perc >= 80) PORTD |= _BV(4); // 3 greens at 80%
}

int main(void){
	DDRD  |= _BV(PD7); // Enable output on decimal pt.
	PORTD |= _BV(PD7); // Bring decimal pt. high (off).
	DDRD  |= _BV(PD6); // Enable output on display CA.
	PORTD |= _BV(PD6); // Bring CA high (display on).
		
	// Scroll through all numbers to test display
	/*int digit = 0;     
	while(1){
		digit = 0;
		while(digit < 10)
		{
			set7seg(digit);
			digit += 1;
			delay_ms(WAITFOR);
			PORTD ^= _BV(PD7); // Toggle the decimal pt.
		}
	}*/
	while(1)
	{
		DDRD  &= ~_BV(PD6); // Disable the display.
		delay_ms(10); // And let the power stabilize.
		
		//Get the value from the A/D Conv. and convert it to volts
		double adc = analog2v(convertanalog(0));
		battmeter(adc); // Update the battery meter.
		
		//double adc = 5.2;
		//debug_puts((char)adc); //DEBUG
		int before = (int)(floor(adc)); // Get the ones digit.
		adc *= 10.0;
		int after = (int)((int)adc % 10); // Get the tenths digit.
		adc /= 10.0;
		// Now we run the display.
		DDRD  |= _BV(PD6); // Enable the display
		set7seg(before);
		PORTD &= ~_BV(PD7); // Enable the decimal pt.
		delay_ms(1000);
		set7seg(after);
		PORTD |= _BV(PD7); // Disable the decimal pt.
		delay_ms(1000);
		
		// If the power is too low, we shut down the AVR.
		if(adc < 3.1)
		{
			DDRD |= _BV(PD6);
			PORTD |= _BV(PD6);
			PORTB = 0xff;
			for(int i=0;i<24;i++)
			{
				PORTD ^= _BV(PD7);
				delay_ms(100);
			}
			// Shut down all outputs.
			PORTB = 0;
			PORTC = 0;
			PORTD = 0;
			DDRB = 0;
			DDRC = 0;
			DDRD = 0;
			
			
			// Shut down all interrupts.
			cli();
			
			// Shut down the A/D Converter (to disable the 
			// internal Vref).
			ADCSRA &= ~(1<<ADEN);
			
			MCUCR=(1<<SE)|(1<<SM1); // Enable sleep and set mode
			                        // to deep power down.
			
			// And finally, nap time.
			sleep_cpu();
		}
	}
	

  return(0);
}
