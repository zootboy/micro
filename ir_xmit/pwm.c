/* Tiny PWM */

/* Include useful pre-defined functions */
#include <avr/io.h>
#include <avr/interrupt.h>   
#define F_CPU 9600000   
#include <util/delay.h>

// Target frequency: 38kHz

int main(void)
{
	// Timer0 settings.
	TCCR0A = (1<<COM0A0)|(1<<WGM01); // Toggle OC0A on compare.
	TCCR0B = (1<<CS00); // Enable system clock to timer, no prescale.
	OCR0A = 245/2;
	DDRB = (1<<0); // PB0 = output

	uint8_t i;
		
	while(1)
	{
		i=20; // ms delay
		while(i)
		{
			_delay_ms(1);
			i--;
		}
		DDRB ^= (1<<0);
    }
}
