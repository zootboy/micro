/* Tiny PWM */

/* Include useful pre-defined functions */
#include <avr/io.h>
#include <avr/interrupt.h>   
#define F_CPU 8000000   

// Target frequency: 38kHz

int main(void)
{
	// Timer0 settings.
	TCCR0A = (1<<COM0A0)|(1<<WGM01); // Toggle OC0A on compare.
	TCCR0B = (1<<CS00); // Enable system clock to timer, no prescale.
	OCR0A = 211;

	while(1)
	{
		asm("nop");	
    }
}
