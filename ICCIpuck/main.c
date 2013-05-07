/* Lithium Ion battery circuit */

/* Include useful pre-defined functions */
#include <avr/interrupt.h>    // Enable interrupt functions.
#define F_CPU 1000000	      // Sets up the default speed for delay.h
#include <avr/io.h>           // Defines pins, ports, etc to make programs easier to read
#include <util/delay.h>
#include <math.h>
#include <avr/sleep.h>

#include "analog.h"

#define SHORTWAIT 75
#define LONGWAIT  500

// LED stuff
#define LEDDDR  DDRA
#define LEDPORT PORTA
#define LED1 7
#define LED2 6
#define LED3 5
#define LED4 4
#define LED5 2

/// Code revision number ///
uint8_t version = (1<<LED3)|(1<<LED2); // Version 6

/// Pulse LED stuff ///
volatile unsigned int counter = 0; // Counter var for pulse brightness.
volatile unsigned int brightness = 0x10; // Brightness of LED.
volatile int pulseLED; // Which LED is being pulsed.
volatile int up = 1; // Going up or down?

/// ADC Stuff ///
volatile double voltage = 4.2; // Current battery voltage.
volatile unsigned int result; // The ADC raw value.
volatile int adcCounter = 0; // Debug counter for ADC conversions.

/// Misc. vars ///
volatile unsigned int sleepcount = 0; // Counter for auto-sleep.
volatile uint8_t sreg_save; // SREG storage container.
float sleeptime = 2.0; // After X hours, power down.
volatile uint8_t interrupter = 0; // Test var for false wakeup.


void delay_ms(unsigned int ms)
{
	// Apparently this makes the delay cheaper? (Yeah, I dunno either.)
    while(ms){
        _delay_ms(1);
        ms--;
    }
}

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

ISR(SIG_OVERFLOW0)
{
	// When the pulse timer completes one cycle.
	PORTA |= pulseLED; // Turn on the LED.
	counter++;
	if(counter > 2)
	{
		if(brightness >= 0xfe) { up = 0; }// Go down again.
		if(brightness <= 0x10) { up = 1; }// Go up again.
		
		if(up == 1) { brightness += 0x01; } // Inc. or dec. the brightness.
		else {   brightness -= 0x01; }
		
		OCR0A = brightness; // Set the timer interrupt to the desired brightness.
		
		counter = 0;
	}
}

ISR(SIG_OUTPUT_COMPARE0A)
{
	// When the pulse timer hits the brightness value.
	PORTA &= ~pulseLED; // Shut off the LED.
}

ISR(SIG_OVERFLOW1)
{
	sleepcount++;
	startConvert(); // Run the conversion.
}

ISR(SIG_ADC)
{
	// When the ADC has spit out a value.

    result = ADC; // Get value from ADC buffer.

	adcCounter++;
	if(adcCounter > 31) adcCounter = 0;
}

int main(void)
{
	delay_ms(10); // Let the power stabilize.
	
	cli(); // Disable interrupts.
	
	// Set up the various ins and outs.
	DDRB = (1<<PB4); // Enable the IR transistor controller output.
	PORTB = (1<<PB5)|(1<<PB6); // Pull-up enabled for debug & hw interrupt.
	
	// Set up the pulse timer.
	TCCR0B = (1<<CS01)|(0<<CS00); // Enable tim0 with clk/1024 prescale.
	OCR0A = brightness; // Set the timer interrupt to the desired brightness.
	
	//TIMSK |= (1<<OCIE0A)|(1<<TOIE0); // Enable interrupt on compare-A match & overflow.
	// ^ Run this line when you want to pulse.
	
	
	// Initialize the ADC.
	// Note that an interrupt is generated when the ADC finishes.
	// This interrupt is handled in main.c, not analog.c.
	adcOn();
	
	startConvert(); // Kick off the conversion loop.
	
	// Set up auto shutdown timer.
	TCCR1B = (1<<CS13)|(1<<CS12)|(1<<CS11)|(1<<CS10); // 16384x prescale.
	
	// Initialize the LEDs & run test patterns.
	LEDDDR = (1<<LED1)|(1<<LED2)|(1<<LED3)|(1<<LED4)|(1<<LED5);
	LEDPORT = (1<<LED1)|(1<<LED2)|(1<<LED3)|(1<<LED4)|(1<<LED5);
	delay_ms(LONGWAIT);
	
	LEDPORT = (1<<LED1);
	delay_ms(SHORTWAIT);
	LEDPORT = (1<<LED2);
	delay_ms(SHORTWAIT);
	LEDPORT = (1<<LED3);
	delay_ms(SHORTWAIT);
	LEDPORT = (1<<LED4);
	delay_ms(SHORTWAIT);
	LEDPORT = (1<<LED5);
	delay_ms(SHORTWAIT);

	
	LEDPORT = 0;
	delay_ms(2*LONGWAIT);
	// End test patterns.	
	
	sei(); // Enable interrupts.
	
	// Pulse the software version.
	pulseLED = version;
	TIMSK |= (1<<OCIE0A)|(1<<TOIE0);
	delay_ms(2750);
	TIMSK &= ~((1<<OCIE0A)|(1<<TOIE0));
	
	LEDPORT = 0;
	
	delay_ms(1000);
	
	TIMSK |= (1<<TOIE1); // Enable Timer1 overflow interrupt.
	// The timer overfows every 4.1 seconds, so there are 14.3 timers per minute.
	
	
	PORTB |= (1<<PB4); // Turn on the IR LEDs.
	
	
	while(1) // Main program loop.
	{
		MCUCR = 0; // Disable sleep mode.
		
		voltage = analog2v(result); // Get the actual voltage.
				
		if(voltage < 3.0 && bit_is_clear(PINB, PB3)) // Also, we're not charging.
		{
			// ^ Voltage is too low. Power down.
			
			for(int i=0;i<20;i++) // Blink the light to indicate powering down.
			{
				LEDPORT ^= (1<<LED1);
				delay_ms(50);
			}
			
			// Disable the ADC.
			adcOff();
			
			// Disable the pulsing timer interrupt.
			TIMSK &= ~(1<<OCIE0A)|(1<<TOIE0);
			
			// Disable IR leds.
			PORTB &= ~(1<<PB4);
			
			// Disable all fuel gauge LEDs.
			LEDPORT = 0;
			
			// Enable the hardware interrupt.
			GIMSK = (1<<INT0);
			
			// Enable sleep mode (power down level).
			MCUCR = (1<<SE)|(1<<SM1);
			
			sreg_save = SREG; // Save the SREG.
			
			interrupter = 0; // Set up interrupt verifier.
			
			// And finally, nap time.
			sleep_cpu();
			
			while(!interrupter)
			{
				sleep_cpu(); // If the CPU was woken
				// by an erroneous condition, go back to sleep.
			}
			
			// We've woken back up now.
			SREG = sreg_save; // Restore the SREG.
			
			GIMSK = 0; // Disable HW interrupt.
			
			MCUCR = 0; // Disable sleep mode.
			
			adcOn(); // Augh!
			
			PORTB |= (1<<PB4); // Enable IR leds.
			
			
			
		}
		
		if(bit_is_set(PINB,PB3))
		{
			// We're charging.
			
			sleeptime = 0.25; // Sleep after 15 mins to speed up charging.
			PORTB &= ~(1<<PB4); // Turn off the IR LEDs. They're not needed when charging.
			
			if(voltage > 4.0) 
			{ 
				pulseLED = 0;
				LEDPORT |= (1<<LED1)|(1<<LED2)|(1<<LED3)|(1<<LED4)|(1<<LED5);
			}
			else if(voltage > 3.9)
			{
				pulseLED = (1<<LED5);
				LEDPORT |= (1<<LED1)|(1<<LED2)|(1<<LED3)|(1<<LED4);
			}
			else if(voltage > 3.8)
			{
				pulseLED = (1<<LED4);
				LEDPORT |= (1<<LED1)|(1<<LED2)|(1<<LED3);
				LEDPORT &= ~(1<<LED5);
			}
			else if(voltage > 3.3)
			{
				pulseLED = (1<<LED3);
				LEDPORT |= (1<<LED1)|(1<<LED2);
				LEDPORT &= ~((1<<LED5)|(1<<LED4));
			}
			else
			{
				pulseLED = (1<<LED2);
				LEDPORT |= (1<<LED1);
				LEDPORT &= ~((1<<LED5)|(1<<LED4)|(1<<LED3));
			}
			
			TIMSK |= (1<<OCIE0A)|(1<<TOIE0); // Enable interrupt on compare-A match & overflow.
			// In other words, pulse the LED.
		}
		else
		{
			// We're just running. Display the battery level.
			
			sleeptime = 2.0; // Back to the regular sleep time of 2 hours.
			PORTB |= (1<<PB4); // IR LEDs back on if they were off for charging.
			
			TIMSK &= ~((1<<OCIE0A)|(1<<TOIE0)); // Disable the pulse timer.
			LEDPORT = (1<<LED1);
			if(voltage > 3.2) LEDPORT |= (1<<LED2);
			if(voltage > 3.4) LEDPORT |= (1<<LED3);
			if(voltage > 3.7) LEDPORT |= (1<<LED4);
			if(voltage > 4.0) LEDPORT |= (1<<LED5);
			delay_ms(2); // Dim the LEDs.
			LEDPORT = 0;
		}
		
		if(bit_is_clear(PINB,PB6) || (sleepcount > sleeptime * 60 * 14.3))
		{
			delay_ms(20); // Debounce the button.
			if(bit_is_clear(PINB,PB6) || (sleepcount > sleeptime * 60 * 14.3))
			{
				// Power off button has been pressed.
				for(int i=0;i<21;i++) // Blink the light to indicate powering down.
				{
					LEDPORT ^= (1<<LED1);
					delay_ms(50);
				}
				
				// Disable the ADC.
				adcOff();
				
				// Disable the pulsing timer interrupt.
				TIMSK &= ~(1<<OCIE0A)|(1<<TOIE0);
				
				// Disable IR leds.
				PORTB &= ~(1<<PB4);
				
				// Wait until the button is released. 
				while(bit_is_clear(PINB,PB6)) delay_ms(10); // Fixes an infinite loop bug.
				
				// Disable all fuel gauge LEDs.
				LEDPORT = 0;
				
				// Enable the hardware interrupt.
				GIMSK = (1<<INT0);
				
				// Enable sleep mode (power down level).
				MCUCR = (1<<SE)|(1<<SM1);
				
				sreg_save = SREG; // Save the SREG.
				
				interrupter = 0; // Set up interrupt verifier.
				
				// And finally, nap time.
				sleep_cpu();
				
				while(!interrupter)
				{
					sleep_cpu(); // If the CPU was woken
					// by an erroneous condition, go back to sleep.
				}
				
				// We've woken back up now.
				SREG = sreg_save; // Restore the SREG.
				
				MCUCR = 0; // Disable sleep mode.
				
				GIMSK = 0; // Disable HW interrupt.
				
				adcOn(); // Augh!
				
				PORTB |= (1<<PB4); // Enable IR leds.
				
				sleepcount = 0; // Reset sleep count.
				
			}
		}
		
		
		if(bit_is_clear(PINB,PB5))
		{
			// Do debuggy stuff.
			LEDPORT = 0;
			
			// If the pulser is on, turn it off for now.
			uint8_t pulser = 0;
			if(TIMSK | (1<<OCIE0A))
			{
				TIMSK &= ~((1<<OCIE0A)|(1<<TOIE0));
				pulser = 1;
			}
			
			double val = voltage;
			int before = (int)(floor(val)); // Get the ones digit.
			val *= 10.0;
			int after = (int)((int)val % 10); // Get the tenths digit.
			
			// Display the ones digit.
			if(before >= 8)
			{
				LEDPORT |= (1<<LED4);
				before -= 8;
			}
			if(before >= 4)
			{
				LEDPORT |= (1<<LED3);
				before -= 4;
			}
			if(before >= 2)
			{
				LEDPORT |= (1<<LED2);
				before -= 2;
			}
			if(before >= 1)
			{
				LEDPORT |= (1<<LED1);
				before -= 1;
			}
			
			delay_ms(1000);
			LEDPORT = (1<<LED5);
			delay_ms(800);
			LEDPORT = 0;
			
			if(after >= 8)
			{
				LEDPORT |= (1<<LED4);
				after -= 8;
			}
			if(after >= 4)
			{
				LEDPORT |= (1<<LED3);
				after -= 4;
			}
			if(after >= 2)
			{
				LEDPORT |= (1<<LED2);
				after -= 2;
			}
			if(after >= 1)
			{
				LEDPORT |= (1<<LED1);
				after -= 1;
			}
			
			delay_ms(1000);
			LEDPORT = 0;
			delay_ms(100);
			
			int adcCount = adcCounter;
			
			if(adcCount >= 16)
			{
				LEDPORT |= (1<<LED5);
				adcCount -= 16;
			}
			if(adcCount >= 8)
			{
				LEDPORT |= (1<<LED4);
				adcCount -= 8;
			}
			if(adcCount >= 4)
			{
				LEDPORT |= (1<<LED3);
				adcCount -= 4;
			}
			if(adcCount >= 2)
			{
				LEDPORT |= (1<<LED2);
				adcCount -= 2;
			}
			if(adcCount >= 1)
			{
				LEDPORT |= (1<<LED1);
				adcCount -= 1;
			}
			delay_ms(1000);
			
			if(pulser) TIMSK |= (1<<OCIE0A)|(1<<TOIE0); // Restore the pulsar if needed.
			
		}
		
		// And chill for a sec.
		delay_ms(10);
		
		if(bit_is_set(PINB,PB3)) delay_ms(40);
	}
	
	return(0); // This line should NEVER run. Don't break out of the while(1) loop.
}
