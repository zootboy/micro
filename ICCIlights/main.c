/* Lithium Ion battery circuit */

/* Include useful pre-defined functions */
#include <avr/interrupt.h>    // Enable interrupt functions.
#define F_CPU 1000000	      // Sets up the default speed for delay.h
#include <avr/io.h>           // Defines pins, ports, etc to make programs easier to read
#include <util/delay.h>
#include <math.h>
#include <avr/sleep.h>

#define SHORTWAIT 75
#define LONGWAIT  500

// LED stuff
#define LEDDDR  DDRB
#define LEDPORT PORTB
#define LED1 0
#define LED2 1
#define LED3 2
#define LED4 4


/// Pulse LED stuff ///
volatile unsigned int counter = 0; // Counter var for pulse brightness.
volatile unsigned int brightness = 0x10; // Brightness of LED.
volatile int pulseLED; // Which LED is being pulsed.
volatile int up = 1; // Going up or down?



void delay_ms(unsigned int ms)
{
	// Apparently this makes the delay cheaper? (Yeah, I dunno either.)
    while(ms){
        _delay_ms(1);
        ms--;
    }
}
/*
ISR(SIG_INTERRUPT0) // Do stuff if HW interrupt button is pressed.
{
	GIMSK = 0; // Disable this interrupt.

	MCUCR = 0; // Disable sleep mode.

	sleepcount = 0; // Reset sleep count.
	
	interrupter = 1; // This is a valid wakeup.
	
	delay_ms(10);	
	
	// Show power up sequence.
	LEDPORT = (1<<LED2);
	delay_ms(300);
	LEDPORT = (1<<LED2)|(1<<LED3);
	delay_ms(300);
	LEDPORT = (1<<LED2)|(1<<LED3)|(1<<LED4);
	delay_ms(300);
	
	// Wait until the button is released. 
	while(bit_is_clear(PINB,PB6)) delay_ms(10); // Fixes an infinite loop bug.
	
	// And we're done. Main loop will now resume.
	
}
*/
ISR(SIG_OVERFLOW0)
{
	// When the pulse timer completes one cycle.
	PORTB |= pulseLED; // Turn on the LED.
	/*counter++;
	if(counter > 2)
	{
		if(brightness >= 0xfe) { up = 0; }// Go down again.
		if(brightness <= 0x10) { up = 1; }// Go up again.
		
		if(up == 1) { brightness += 0x01; } // Inc. or dec. the brightness.
		else {   brightness -= 0x01; }
		
		OCR0A = brightness; // Set the timer interrupt to the desired brightness.
		
		counter = 0;
	}*/
}

ISR(SIG_OUTPUT_COMPARE0A)
{
	// When the pulse timer hits the brightness value.
	PORTB &= ~pulseLED; // Shut off the LED.
}





int main(void)
{
	delay_ms(10); // Let the power stabilize.
	
	cli(); // Disable interrupts.
	
	DDRB = (1<<LED1)|(1<<LED2)|(1<<LED3)|(1<<LED4); // Enable the LED ports.
	PORTB = (1<<LED1)|(1<<LED2)|(1<<LED3)|(1<<LED4);
	
	// Set up the pulse timer.
	TCCR0B = (1<<CS00); // Enable tim0 with clk/1024 prescale.
	OCR0A = brightness; // Set the timer interrupt to the desired brightness.
	
	// Set dimmed led.
	pulseLED = (1<<LED1);
	
	//TIMSK |= (1<<OCIE0A)|(1<<TOIE0); // Enable interrupt on compare-A match & overflow.
	// ^ Run this line when you want to pulse.
	
	
	// Initialize the ADC.
	// Note that an interrupt is generated when the ADC finishes.
	// This interrupt is handled in main.c, not analog.c.
	//adcOn();
	
	//startConvert(); // Kick off the conversion loop.
	
	// Set up auto shutdown timer.
	//TCCR1B = (1<<CS13)|(1<<CS12)|(1<<CS11)|(1<<CS10); // 16384x prescale.

	/*delay_ms(LONGWAIT);
	
	LEDPORT = (1<<LED1);
	delay_ms(SHORTWAIT);
	LEDPORT = (1<<LED2);
	delay_ms(SHORTWAIT);
	LEDPORT = (1<<LED3);
	delay_ms(SHORTWAIT);
	LEDPORT = (1<<LED4);
	delay_ms(SHORTWAIT);

	
	LEDPORT = 0;
	delay_ms(2*LONGWAIT);
	// End test patterns.	*/
	
	sei(); // Enable interrupts.
	
	
	
	//TIMSK |= (1<<TOIE1); // Enable Timer1 overflow interrupt.
	// The timer overfows every 4.1 seconds, so there are 14.3 timers per minute.
	
	
	//PORTB |= (1<<PB4); // Turn on the IR LEDs.
	
	
	while(1) // Main program loop.
	{
		if(bit_is_set(PINB,PB3))
		{
			delay_ms(20);
			if(bit_is_set(PINB,PB3))
			{
				TIMSK |= (1<<OCIE0A)|(1<<TOIE0);
				TCCR0B = (1<<CS00);
			
				pulseLED = (1<<LED1);
				delay_ms(SHORTWAIT);
				pulseLED = (1<<LED2);
				delay_ms(SHORTWAIT);
				pulseLED = (1<<LED3);
				delay_ms(SHORTWAIT);
				pulseLED = (1<<LED4);
				delay_ms(SHORTWAIT);
				
			}
		}
		LEDPORT = 0;
		
		TIMSK &= ~((1<<OCIE0A)|(1<<TOIE0));
		TCCR0B = 0;
		
		delay_ms(10);
	}
	
	return(0); // This line should NEVER run. Don't break out of the while(1) loop.
}
