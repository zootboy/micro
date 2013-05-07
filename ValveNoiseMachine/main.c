/* Valve Noise Circuit */

/* Include useful pre-defined functions */
#include <avr/interrupt.h>    // Enable interrupt functions.
#define F_CPU 9600000	      // Sets up the default speed for delay.h
#include <avr/io.h>           // Defines pins, ports, etc to make programs easier to read
#include <util/delay.h>
#include <stdlib.h>
#include <avr/sleep.h>
#include <avr/eeprom.h>

/*
 * PB0 - MOSI - 
 * PB1 - MISO - Reed Switch input
 * PB2 - SCK  - 
 * PB3 - Relay output
 * PB4 - Play Button output
 * PB5 - RESET
 */

#define BTNPRESSTIME 250
volatile uint16_t timerTick;

void delay_ms(uint16_t ms)
{
    while(ms){
        _delay_ms(1);
        ms--;
    }
}

ISR(TIM0_OVF_vect)
{
    if(timerTick) 
    {
        timerTick += 26; // Milliseconds.
        
        if(timerTick > 60000)
        {
            timerTick = 0;
            PORTB &= ~(1<<PB3); // Turn relay off.
            PORTB = 0b00101000;
        }
    }
}

int main(void)
{
	delay_ms(10); // Let the power stabilize.
	cli(); // Disable interrupts.
        
        DDRB = (1<<PB3)|(1<<PB4); // Two outputs.
	PORTB = (1<<PB1); // Enable internal pullup on reed switch.
        timerTick = 0;
        
        TCCR0A = 0;
        TCCR0B = (1<<CS02)|(1<<CS00); // Prescale /1024
        TIMSK0 = (1<<TOIE0); // Overflow interrupt.
        // Interrupt should occur every ~25 ms.
        
	sei(); // Enable interrupts.
	
	delay_ms(50);
	
	while(1) // Main loop.
	{
            while(bit_is_clear(PINB,PB1)) delay_ms(5);
            delay_ms(20);
            if(bit_is_set(PINB,PB1))
            {
                PORTB |= (1<<PB4)|(1<<PB3); // Relay and Play Button on.
                delay_ms(BTNPRESSTIME);
                PORTB &= ~(1<<PB4);
                timerTick = BTNPRESSTIME;
                delay_ms(15000); // Wait for sound to play out.
                while(bit_is_set(PINB,PB1)) delay_ms(5);
            }
	}
}
