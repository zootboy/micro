/* PWM test */

/* Include useful pre-defined functions */
#include <avr/interrupt.h>    // Enable interrupt functions.
#define F_CPU 8000000	      // Sets up the default speed for delay.h
#include <avr/io.h>           // Defines pins, ports, etc to make programs easier to read
#include <util/delay.h>

void delay_ms(uint16_t ms)
{
    while(ms){
        _delay_ms(1);
        ms--;
    }
}

int main(void)
{
	delay_ms(10); // Let the power stabilize.	
	cli(); // Disable interrupts.
        
    DDRB = 0b00000111; // Pins B0-2 are output.
    
    // Timer stuff for PWM
    ICR1 = 200; // Freq.
    OCR1A = 100; // Test start values.
    OCR1B = 100;
    
    TCCR1A = (1<<COM1A1)|(1<<COM1A0)|(1<<COM1B1); // OC1A = noninvert, OC1B = invert.
	TCCR1B = (1<<WGM13)|(1<<CS10); // Phase/Freq. correct PWM, Clk/1.

	PORTB |= (1<<PB0); // Enable controller.

	while(1) // Main loop.
	{
        //OCR1A = 50; OCR1B = 50;
        //delay_ms(4000);
        OCR1A = 100; OCR1B = 100;
        delay_ms(4000);
		
		uint8_t i;
		for(i=0; i<100; i++)
		{
			OCR1A = 100-i; OCR1B = OCR1A;
			delay_ms(50);
		}
	}
	return(0); // This line should NEVER run. Don't break out of the while(1) loop.
}
