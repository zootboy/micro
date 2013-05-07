/* Lithium Ion battery circuit */

/* Include useful pre-defined functions */
#include <avr/interrupt.h>    // Enable interrupt functions.
#define F_CPU 1000000	      // Sets up the default speed for delay.h
#include <avr/io.h>           // Defines pins, ports, etc to make programs easier to read
#include <util/delay.h>
#include <math.h>
#include <avr/sleep.h>
#include <avr/eeprom.h>

#include "analog.h"

#define SHORTWAIT 75
#define LONGWAIT  500

// LED stuff
#define LEDDDR  DDRA
#define LEDPORT PORTA
#define LED1 4
#define LED2 3
#define LED3 2
#define LED4 1
#define LED5 0

/// ADC Stuff ///
volatile uint8_t voltage = 144; // Current battery voltage.
volatile uint16_t result; // The ADC raw value.

volatile uint8_t ack = 0; // Acknowledge alert var.
volatile uint8_t alertCount = 0; // Counter for alert. 

void delay_ms(unsigned int ms)
{
	// Apparently this makes the delay cheaper? (Yeah, I dunno either.)
    while(ms){
        _delay_ms(1);
        ms--;
    }
}

ISR(SIG_ADC)
{
	// When the ADC has spit out a value.
    result = ADC; // Get value from ADC buffer.
}

ISR(TIMER1_OVF_vect)
{
	// Timed trigger of ADC, ~16 sec apart.
	startConvert();
	if(ack > 0) ack--;
	if(alertCount > 0) alertCount++;
}

int main(void)
{
	delay_ms(10); // Let the power stabilize.
	
	cli(); // Disable interrupts.

	PORTB = (1<<PB1); // Pull-up enabled for button.
		
	// Initialize the ADC.
	// Note that an interrupt is generated when the ADC finishes.
	// This interrupt is handled in main.c, not analog.c.
	adcOn();
	
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
	// End test patterns.

	// Enable timer1 for auto-adc runs.
	TCCR1B = (1<<CS12); // Set prescaler to CLK/256.
	TIMSK |= (1<<TOIE1); // Enable obverflow interrupt.

	
	// Enable interrupts.
	sei();
	
	
	startConvert();
	delay_ms(5);
	

	while(1) // Main loop.
	{
		while(bit_is_set(PINB,PB1)) // While button is not pressed.
		{ // This bit does checks and flashes an alert if the battery is low.
			delay_ms(10);
			voltage = analog2v(result); // Do the voltage math.
			
			if(voltage < 110) // If the battery is below 11.0v (dead level)
			{
				if(alertCount == 0) alertCount = 1; // If we're not counting yet, start the counter.
			}
			else
			{
				alertCount = 0; // If the voltage is back up, stop counting.
			}
			
			if(voltage < 110 && alertCount > 4 && ack < 1) // If low voltage AND alertCount has passed at least 4 rounds (~1min) AND we're not ack'd.
			{
				while(bit_is_set(PINB,PB1)) // Blink until bhutan is pressed.
				{
					LEDPORT = (1<<LED5);
					delay_ms(50);
					LEDPORT = 0;
					
					delay_ms(100);
					if(bit_is_clear(PINB,PB1)) break;
					delay_ms(100);
					if(bit_is_clear(PINB,PB1)) break;
					delay_ms(100);
					if(bit_is_clear(PINB,PB1)) break;
					delay_ms(100);
					if(bit_is_clear(PINB,PB1)) break;
					delay_ms(100);
					if(bit_is_clear(PINB,PB1)) break;
					delay_ms(100);
					if(bit_is_clear(PINB,PB1)) break;
					delay_ms(100);
					if(bit_is_clear(PINB,PB1)) break;
					delay_ms(100);
					if(bit_is_clear(PINB,PB1)) break;
					delay_ms(100);
					if(bit_is_clear(PINB,PB1)) break;
					delay_ms(100);
					if(bit_is_clear(PINB,PB1)) break;
					delay_ms(100);
					if(bit_is_clear(PINB,PB1)) break;
					delay_ms(100);
					if(bit_is_clear(PINB,PB1)) break;
				}
				ack = 225; // Ack the light.
			}
			else
				LEDPORT = 0;
		} 
		
		// End waiting for button, it has been pressed now!
		
		startConvert();
		LEDPORT = 0;
		while(bit_is_set(ADCSRA,ADSC)) delay_ms(1); // Wait until ADC finishes.
		delay_ms(20); // and give the interrupt time to trigger.
		
		voltage = analog2v(result); // Do the voltage math.
		
		//eeprom_write_word((uint16_t*)0x00, result);
		//eeprom_write_byte((uint8_t*)0x02, (uint8_t)((double)result * 0.17) - 5.29);
		//eeprom_write_byte((uint8_t*)0x03, analog2v(result));
		
		LEDPORT = (1<<LED1);
		delay_ms(SHORTWAIT);
		if(voltage > 119) LEDPORT |= (1<<LED2);
		delay_ms(SHORTWAIT);
		if(voltage > 122) LEDPORT |= (1<<LED3);
		delay_ms(SHORTWAIT);
		if(voltage > 124) LEDPORT |= (1<<LED4);
		delay_ms(SHORTWAIT);
		if(voltage > 127) LEDPORT |= (1<<LED5);
		
		delay_ms(500); // Let them see the value.
		
		if(bit_is_clear(PINB,PB1)) // If they held the button, they they want loaded values.
		{
			if(voltage > 107) LEDPORT |= (1<<LED2);
			delay_ms(SHORTWAIT);
			if(voltage > 112) LEDPORT |= (1<<LED3);
			delay_ms(SHORTWAIT);
			if(voltage > 117) LEDPORT |= (1<<LED4);
			delay_ms(SHORTWAIT);
			if(voltage > 120) LEDPORT |= (1<<LED5);
			
			delay_ms(500);
		}
		
		delay_ms(1500);
		
		// Shut off the LEDs.
		LEDPORT &= ~(1<<LED5); 
		delay_ms(SHORTWAIT);
		LEDPORT &= ~(1<<LED4); 
		delay_ms(SHORTWAIT);
		LEDPORT &= ~(1<<LED3); 
		delay_ms(SHORTWAIT);
		LEDPORT &= ~(1<<LED2); 
		delay_ms(SHORTWAIT);
		LEDPORT &= ~(1<<LED1); 

		
		// And go back to waiting.
		
	}
	return(0); // This line should NEVER run. Don't break out of the while(1) loop.
}
