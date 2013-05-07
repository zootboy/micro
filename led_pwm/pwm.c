/* Tiny PWM */

/* Include useful pre-defined functions */
#include <avr/io.h>
#include <avr/interrupt.h>   
#define F_CPU 8000000   
#include <util/delay.h>

#define PWM_DDR  DDRB
#define PWM_PORT PORTB
#define PWM_PIN  PB0

// Target frequency: 50kHz
//  8MHz / 50kHz = 160 clock cycles
// Timer clocked straight off system clock
// Reset timer at 160, turning ON signal.
// Interrupt at _PWM width_, turning OFF signal.

volatile uint16_t analogInput = 0; // Reading (out of 1023) from ADC.
volatile uint8_t  pwmDuty = 0; // Duty cycle of PWM, out of 160.
#define MAX_PWM 80 //[32] Out of 160. What value the PWM should hit when ADC hits 1023.
#define PWM_PERIOD 250

ISR(TIMER0_COMPA_vect) // Turn off.
{
	PWM_PORT &= ~(1<<PWM_PIN);
}

ISR(TIMER0_COMPB_vect) // Loop and turn on.
{
	TCNT0 = 0; // Loop.
	if (pwmDuty != 0)
	{
		PWM_PORT |= (1<<PWM_PIN);
	}
}

int main(void)
{
	PWM_DDR = (1<<PWM_PIN); // Set PWM as output.
	PWM_PORT = 0; // Ensure we're off.
	
	cli(); // Global interrupts off.
	// Timer0 settings.
	TCCR0A = 0;
	TCCR0B = (0<<CS01)|(1<<CS00); // Enable system clock to timer, no prescale.
	OCR0A = pwmDuty;
	OCR0B = PWM_PERIOD;
	TIMSK0 = (1<<OCIE0A)|(1<<OCIE0B); // Enable both compare interrupts.

	// ADC settings.
	ADMUX = (1<<REFS0); // AVcc reference, PC0 input.
	ADCSRA = (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1); // Enable, prescale by x64.
	DIDR0 = (1<<ADC0D); // Disable digital circuitry on PC0.
	
	sei(); // Global interrupts on.

	#define AVG_COUNT 50
	uint16_t avgs[AVG_COUNT];
	uint8_t pointer = 0;
	uint64_t totaler = 0;
	
	while(1)
	{
		// Do an ADC reading.
		ADCSRA |= (1<<ADSC);
		while(bit_is_set(ADCSRA, ADSC)) _delay_ms(1); //asm volatile("nop"::);
		avgs[pointer] = ADC;
		pointer++;
		if(pointer >= AVG_COUNT) pointer = 0;

		// Compute the moving average.
		totaler = 0;
		for(uint8_t i = 0; i < AVG_COUNT; i++)
		{
			totaler += avgs[i] / (float)AVG_COUNT;
		}
		//totaler /= AVG_COUNT;
		analogInput = totaler;

		//analogInput = ADC; // Lol?

		// Compute the PWM counts.
		float holder = (float)analogInput / 1023.0;
		if (holder < 0.05)
		{
			holder = 0.0;
		}
		else if(holder > 0.95)
		{
			holder = 1.0;
		}
		
		holder *= (float)MAX_PWM;

		pwmDuty = (uint8_t)holder;
		OCR0A = pwmDuty;
		
    }
}
