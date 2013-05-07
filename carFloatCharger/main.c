/* Lithium Ion battery circuit */

/* Include useful pre-defined functions */
#include <avr/interrupt.h>    // Enable interrupt functions.
#define F_CPU 1000000	      // Sets up the default speed for delay.h
#include <avr/io.h>           // Defines pins, ports, etc to make programs easier to read
#include <util/delay.h>
#include <math.h>
#include <stdlib.h>
#include <avr/sleep.h>
#include <avr/eeprom.h>

#include "analog.h"


/// ADC Stuff ///
volatile uint8_t  voltageIn  = 144; // Current car system voltage.
volatile uint8_t  voltageOut = 144; // Current charging battery voltage.
volatile uint16_t result1; // The ADC raw value.
volatile uint16_t result2; // The ADC raw value.
volatile uint8_t  adcExpected = 0; // 0 = throwaway/no use, 1 = voltageIn, 2 = voltageOut.
volatile uint8_t  newData = 0; // Have the ADC values been updated?
volatile uint16_t  goodCount = 0; // Number of reads that the battery has read good.
volatile uint8_t  faultBlink = 0; // Blink the fault light?


void delay_ms(uint16_t ms)
{
	// Apparently this makes the delay cheaper? (Yeah, I dunno either.)
    while(ms){
        _delay_ms(1);
        ms--;
    }
}

ISR(SIG_ADC) // ADC interrupt. Simply pulls the value and returns, letting the program process the data later.
{
	//PORTB ^= (1<<PB0);
	if(adcExpected == 1)
		result1 = ADC; 
	else if(adcExpected == 2)
		result2 = ADC;
	
	adcExpected = 0;
	delay_ms(100);
	//PORTB ^= (1<<PB0);
}

// The timer was freezing the whole AVR for some reason. I struck it and just threw the ADC runs in main().

/*ISR(TIM1_OVF_vect)
{
	PORTA ^= (1<<PA3);
	// Timed info gather, ~67 sec apart.
	if(!newData) // Don't update if the handler is in the middle of processing the data.
	{
		adcExpected = 1;
		startConvert(0);
		while(adcExpected);
		adcExpected = 2;
		startConvert(1);
		while(adcExpected);
		newData = 1;
	}
	delay_ms(100);
	PORTA ^= (1<<PA3);
}*/

int main(void)
{
	delay_ms(10); // Let the power stabilize.
	
	cli(); // Disable interrupts.
		
	// Initialize the ADC.
	// Note that an interrupt is generated when the ADC finishes.
	// This interrupt is handled in main.c, not analog.c.
	adcOn();
	
	// Initialize the LEDs and relay, then run test patterns.
	DDRA = (1<<PA2)|(1<<PA3); // Chg, fault.
	DDRB = (1<<PB0)|(1<<PB2); // Pwr, relay.

	PORTA |= (1<<PA2)|(1<<PA3);
	PORTB |= (1<<PB0); 
	delay_ms(400); // All 3 lights on.	
	PORTA &= ~((1<<PA2)|(1<<PA3));
	PORTB |= (1<<PB2);
	delay_ms(200); // Pwr on, relay closed.	
	PORTB &= ~(1<<PB2);
	delay_ms(200); // Pwr on, relay open.	
	PORTB &= ~(1<<PB0);
	PORTB |= (1<<PB2);
	PORTA |= (1<<PA2);
	delay_ms(200); // Chg on, relay closed.
	PORTB &= ~(1<<PB2);
	delay_ms(200); // Chg on, relay open.
	PORTA &= ~(1<<PA2);
	PORTA |= (1<<PA3);
	PORTB |= (1<<PB2);
	delay_ms(200); // Fault on, relay closed.
	PORTB &= ~(1<<PB2);
	delay_ms(200); // Fault on, relay open.
	PORTA &= ~(1<<PA3); // Fault off. 
	PORTB |= (1<<PB0); // Power on.
	// End test patterns.

	// Enable timer1 for auto-adc runs.
	//TCCR1B = (1<<CS12)|(1<<CS10); // Set prescaler to CLK/1024.
	//TCCR1B = (1<<CS12);
	//TIMSK1 |= (1<<TOIE1); // Enable overflow interrupt.

	
	// Enable interrupts.
	sei();
	
	delay_ms(50);
	
	// Get some initial reads.
	adcExpected = 1;
	startConvert(0);
	while(adcExpected);
	adcExpected = 2;
	startConvert(1);
	while(adcExpected);
	newData = 1;
	
	delay_ms(50);
	
	// Commment this section out if not debugging!
	//delay_ms(5000);
	//eeprom_write_word((uint16_t*)0x0000, result1);
	//eeprom_write_word((uint16_t*)0x0002, result2);
	//cd /cygdrive/c/Data/micro/carFloatCharger
	//avrdude -c usbtiny -p t44 -U eeprom:r:eeprom.hex:r
	

	while(1) // Main loop.
	{
	
		if(newData)
		{
			// Get the actual voltage values.
			voltageIn  = analog2v1(result1);
			voltageOut = analog2v2(result2);
			faultBlink = 0; // If there's still a fault, we'll keep blinking.
			
			if(voltageIn < 124) // If the input voltage is too low, we must stop consuming power.
			{
				PORTB &= ~(1<<PB2); // Turn off the relay.
				PORTA &= ~(1<<PA2); // Turn off the chg LED.
				delay_ms(10000); // Wait 10 seconds, this may just be that car starting...
				// Check voltageIn again.
				adcExpected = 1;
				startConvert(0);
				while(adcExpected);
				voltageIn  = analog2v1(result1);
				
				if(voltageIn < 124) // And if we're still low, go ahead and shut down.
				{
					PORTA |= (1<<PA3); // Fault LED on.
					delay_ms(1000);
					PORTA = 0;
					PORTB = 0;
					
					// Sleep mode...
					cli(); // Disable interrupts.
					adcOff(); // Shut down ADC.
					DDRA = 0; DDRB = 0; // Set all ports to hi-Z.
					set_sleep_mode(SLEEP_MODE_PWR_DOWN); // Set sleep level to practically off.
					sleep_enable(); // Duh.
					sleep_cpu(); // And nappy time. Wake up only on power cycle / external reset.	
				}
			}
			else if(voltageOut < 100) // If there's less than 10v on the output, there's probably no battery attached.
			{
				faultBlink = 1;
				PORTB &= ~(1<<PB2); // Turn off the relay.
				PORTA &= ~(1<<PA2); // Turn off the chg LED.
			}
			else if(abs(voltageIn - voltageOut) > 10) // If the voltage difference between in and out is greater then 1v, don't charge.
			{										  //  That's a recepie for blown traces.
				PORTA |= (1<<PA3); // Fault light on.
				PORTB &= ~(1<<PB2); // Turn off the relay.
				PORTA &= ~(1<<PA2); // Turn off the chg LED.
				goodCount = 0;
				
			}
			else if(voltageOut > 128) // If the battery has been sufficently charged, prepare to stop charging it.
			{
				goodCount++;
				faultBlink = 0;
			}
			else if((voltageOut < 124) && (voltageIn > 124)) // If the battery needs charging and we have 
			{												  // sufficent voltage to charge, begin charging.
				PORTB |= (1<<PB2); // Turn on the relay.
				PORTA |= (1<<PA2); // Turn on the chg LED.
				goodCount = 0;
				faultBlink = 0;
			}
			
			
			if(voltageOut < 128) goodCount = 0; // Reset the good count if we get a too-low voltage.
			
			newData = 0; // We're done processing the new data.
		}
		
		if(goodCount > (120 * 5)) // If the battery reads good for over 5 minutes, disconnect it from the charge power.
		{					
			PORTB &= ~(1<<PB2); // Turn off the relay.
			PORTA &= ~(1<<PA2); // Turn off the chg LED.
			goodCount = 0; // Reset the good count. If it was a false alarm (very possible), the next ADC run will
		}				  // catch it and start up charging again. There's no good way to check charge while charging...
		
		delay_ms(500); // Keep everything at a good pace and let the voltages stablize before doing more readings.
		
		if(faultBlink) PORTA ^= (1<<PA3); // Fault LED toggle.
		else PORTA &= ~(1<<PA3); // If we're not blinking, make sure it's off.
		
		// And run another round of ADC.
		adcExpected = 1;
		startConvert(0);
		while(adcExpected);
		adcExpected = 2;
		startConvert(1);
		while(adcExpected);
		newData = 1;
		
	}
	
	return(0); // This line should NEVER run. Don't break out of the while(1) loop.

}
