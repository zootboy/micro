/* Lithium Ion battery circuit */

/* Include useful pre-defined functions */
#include <avr/interrupt.h>    
#define F_CPU 9600000	      // Sets up the default speed for delay.h
#include <avr/io.h>           // Defines pins, ports, etc to make programs easier to read
#include <util/delay.h>
#include <math.h>
#include <avr/sleep.h>



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


int main(void)
{
	// Enable LEDs & transistor outputs.
	DDRB = (1<<PB4)|(1<<PB3)|(1<<PB0);
	
	// Boot-up test sequence.
	PORTB = (1<<PB4)|(1<<PB3);
	delay_ms(500);
	PORTB = (1<<PB4);
	delay_ms(500);
	PORTB = (1<<PB3);
	delay_ms(500);
	PORTB = 0;
	
	// Set up ADC.
    ADMUX = (1<<REFS0); // Use the intenal  ref.
	ADMUX |= (1<<MUX0); // PB2 is analog input.
	ADCSRA = (1<<ADEN)|(1<<ADPS1)|(1<<ADPS0); // Enable the ADC, set P.S. to 8x.
	
	while(1)
	{
		delay_ms(10); // Let the power stabilize.
		
		ADCSRA |= (1<<ADSC); // Start a conversion.
		
		while(bit_is_set(ADCSRA,ADSC)) delay_ms(10); // Wait for conversion to finish.
		
		// Math:      resistorDiv * (vRef * ADCoutput / ADCresolution).
		float vPack = 16.0 * (1.1 * ADC / 1024.0);
		
		if(vPack <= 15.0) // Voltage is too low. Shut down everything. (AIM: 14v)
		{
			// Blink the yellow led.
			for(int i=0;i<20;i++)
			{
				PORTB ^= (1<<PB4);
				delay_ms(50);
			}
			PORTB = 0; // Disable transistor & leds.
			ADCSRA &= ~(1<<ADEN); // Disable the ADC.
			
			MCUCR=(1<<SE)|(1<<SM1); // Enable sleep and set mode to deep power down.
			sleep_cpu(); // And finally, nap time.	
		}
		else
		{
			PORTB = (1<<PB4)|(1<<PB0); // Enable yellow LED & transistor.
			if(vPack > 16.0) PORTB |= (1<<PB3); // Enable green LED if voltage is high enough. AIM: 15v
			if(vPack < 15.4) // AIM: 14.3v
			{ // Blink yellow if close to dead.
				for(int i=0;i<4;i++)
				{
					delay_ms(1000);
					PORTB ^= (1<<PB4);
				}
			}
		}
	}
  return(0); // Feh.
}
