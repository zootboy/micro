/* Dehumidifier software */

/* Include useful pre-defined functions */
#include <avr/interrupt.h>    
#define F_CPU 1000000
#include <avr/io.h>
#include <avr/eeprom.h>
#include <util/delay.h>
#include "sevseg.h"
#include "funct.h"


#define WAITFOR 1000

#define RELAYPORT PORTC
#define RELAY1 PC5
#define RELAY2 PC4

#define SCROLLWAIT 600

#define BUFFSIZE 50
volatile uint8_t buffer[BUFFSIZE]; // Sensor ring buffer.
volatile uint8_t indux = 0; // Buffer index. Intentionally misspelled because index is a reserved word.
volatile uint8_t humidity = 00; // Humidity value 00-99.

// Calibration constants. ADx = ADC value (0-1023), HUx = humidity (0-99)
#define AD1 264
#define HU1 34
#define AD2 565
#define HU2 70

ISR(ADC_vect) // New ADC result.
{
	// Two-stage ADC -> Humidity math. Old, do not use.
	/*float voltage = 2.56 * ADC * 2 / 1024.0;
	buffer[indux] = (uint8_t)(((voltage/5.0)-0.1515)/0.00636);*/
	
	buffer[indux] = (((((float)HU2-(float)HU1)/((float)AD2-(float)AD1)) * (ADC - (float)AD1)) + ((float)HU1)); // OMG, that's a lot of floats!
	indux++;
	if(indux >= BUFFSIZE) indux = 0;
	uint16_t avg = 0;
	for(uint8_t i=0;i<BUFFSIZE;i++)
	{
		avg += buffer[i];
	}
	avg /= BUFFSIZE;
	humidity = avg;
}

int main(void)
{
	delay_ms(70); // Required delay to let the humidity sensor stabilize.
	
	
	DDRC |= (1<<RELAY1)|(1<<RELAY2); // Enable output on relay pins.	  
	PORTB = (1<<PB1)|(1<<PB0); // Enable button pull-up.

	sevsegTest(); // Start-up sequence.
	PORTB |= 3; // Enable pull-ups.

	sevsegDuality(1); // Enable display mulitplexing.
	
	// Run relay tests.
	segl = 0b10000000;
	segr = 0b00000000;
	delay_ms(5);
	PORTC |= (1<<RELAY1);
	delay_ms(500);
	PORTC &= ~(1<<RELAY1);
	PORTC |= (1<<RELAY2);
	segl = 0b00000000;
	segr = 0b10000000;
	delay_ms(500);
	PORTC &= ~(1<<RELAY2);
	
	// Get stored values from EEPROM.
	uint8_t humidLo = eeprom_read_byte((uint8_t*)0x00);
	uint8_t humidHi = eeprom_read_byte((uint8_t*)0x01);
	if(humidLo > 90 || humidLo < 10 || humidLo > humidHi) humidLo = 25;
	if(humidHi > 90 || humidHi < 10 || humidLo > humidHi) humidHi = 50;
	
	// Set up analog/digital converter.
	ADMUX = (1<<REFS1)|(1<<REFS0); // Set ref to internal 2.56 and channel to 0 (indirectly).
	ADCSRA = (1<<ADEN)|(1<<ADIE)|(1<<ADPS2); // Enable adc, enable interrupt, prescale by 16x.
	sei();
	
	// Test spiral loading screen.
	/*for(uint8_t i=0;i<13;i++)
	{
		sevsegLoading(i);
		delay_ms(150);
	}*/
	
	// Test hex display
	/*for (uint8_t i=0;i<0xff;i+=0x11)
	{
		sevsegHex(i);
		delay_ms(600);
	}
	sevsegHex(0xff);
	delay_ms(600);*/
	
	// Two dashes.
	segl = 0b01000000;
	segr = 0b01000000;
	
	while(1)
	{	
		/*// Two dashes.
		segl = 0b01000000;
		segr = 0b01000000;*/
		
		if(bit_is_clear(PINB,PB1)) // If upper button is pressed...
		{
			delay_ms(20); // 
			uint8_t counter = 0;
			while(bit_is_clear(PINB,PB1))
			{
				delay_ms(5);
				counter++;
				if((counter*5) > 500) break; // Leave the loop once long time press is detected.
			}
			
			if((counter*5) > 500)
			{
				// Long press, go to options.
				
				// Scroll "OPT".
				// "O"
				segl = 0;
				segr = 0b00111111;
				delay_ms(SCROLLWAIT);
				// "OP"
				segl = 0b00111111;
				segr = 0b01110011;
				delay_ms(SCROLLWAIT);
				// "PT"
				segl = 0b01110011;
				segr = 0b01111000;
				delay_ms(SCROLLWAIT);
				// "T"
				segl = 0b01111000;
				segr = 0b10000000;
				
				while(bit_is_clear(PINB,PB1)) delay_ms(5);
				segl = 0b10000000;
				segr = 0;
				delay_ms(200);
				
				// Turn off the relays.
				RELAYPORT &= ~((1<<RELAY1)|(1<<RELAY2));
				
				// Display menu...
				uint8_t menu = 1;
				uint8_t selec = 1;
				uint8_t delay = 120;
				while(menu)
				{
					if(selec == 0) // End (exit menu)
					{
						// "En"
						segl = 0b11111001;
						segr = 0b01010100;
						for(;delay>0;delay-=1)
						{
							if(bit_is_clear(PINB,PB1)) break;
							if(bit_is_clear(PINB,PB0))
							{
								// Quit menu.
								menu = 0;
								break;
							}
							delay_ms(5);
						}
						delay = 255;
						// "nd"
						segl = 0b11010100;
						segr = 0b01011110;
						for(;delay>0;delay-=1)
						{
							if(bit_is_clear(PINB,PB1)) break;
							if(bit_is_clear(PINB,PB0))
							{
								// Quit menu.
								menu = 0;
								break;
							}
							delay_ms(5);
						}
						delay = 120;
					}
					
					else if(selec == 1) // Test...
					{
						// "TE"
						segl = 0b11111000;
						segr = 0b01111001;
						for(;delay>0;delay-=1)
						{
							if(bit_is_clear(PINB,PB1)) break;
							if(bit_is_clear(PINB,PB0))
							{
								// Test relays.
								testRelays();
							}
							delay_ms(5);
						}
						delay = 120;
						// "ES"
						segl = 0b11111001;
						segr = 0b01101101;
						for(;delay>0;delay-=1)
						{
							if(bit_is_clear(PINB,PB1)) break;
							if(bit_is_clear(PINB,PB0))
							{
								// Test relays.
								testRelays();
							}
							delay_ms(5);
						}
						delay = 255;
						// "ST"
						segl = 0b11101101;
						segr = 0b01111000;
						for(;delay>0;delay-=1)
						{
							if(bit_is_clear(PINB,PB1)) break;
							if(bit_is_clear(PINB,PB0))
							{
								// Test relays.
								testRelays();
							}
							delay_ms(5);
						}
						delay = 120;
					}
					
					else if(selec == 2) // Lo (low setting)
					{
						// "Lo"
						segl = 0b10111000;
						segr = 0b01011100;
						delay = 255;
						uint8_t skip = 0;
						for(;delay>0;delay-=1)
						{
							if(bit_is_clear(PINB,PB1)) {while(bit_is_clear(PINB,PB1)) delay_ms(5);skip = 1;break;}
							if(bit_is_clear(PINB,PB0))
							{
								while(bit_is_clear(PINB,PB0)) delay_ms(5);
								break;
							}
							delay_ms(10);
						}
						delay = 255;
						
						uint8_t hold = humidLo; // Store unmodified value.
						
						while(bit_is_set(PINB,PB0) && skip == 0) // While the lower button remains unpressed...
						{
							sevsegNumber(humidLo);
							segl |= 0b10000000; // Add in the decimal.
							if(bit_is_clear(PINB, PB1)) // If upper button (increment) is pressed.
							{
								while(bit_is_clear(PINB,PB1)) delay_ms(5);
								humidLo += 5;
								if(humidLo > 90) humidLo = 10;
							}
						}
						
						if(humidHi <= humidLo) // Error!
						{
							segl = 0b11111001;
							segr = 0b01010000;
							delay_ms(1000);
							humidLo = hold;
						}
						else
						{
							if(humidLo != hold) eeprom_write_byte((uint8_t*)0x00, humidLo);
						}
						while(bit_is_clear(PINB,PB0)) delay_ms(5);
						selec++;
					}
					
					else if(selec == 3) // Hi (high setting)
					{
						// "Hi"
						segl = 0b11110110;
						segr = 0b00010000;
						delay = 255;
						uint8_t skip = 0;
						for(;delay>0;delay-=1)
						{
							if(bit_is_clear(PINB,PB1)) {while(bit_is_clear(PINB,PB1)) delay_ms(5); skip = 1;break;} // TODO: fix this if new menu option added.
							if(bit_is_clear(PINB,PB0))
							{
								while(bit_is_clear(PINB,PB0)) delay_ms(5);
								break;
							}
							delay_ms(10);
						}
						delay = 255;
						
						uint8_t hold = humidHi; // Store unmodified value.
						
						while(bit_is_set(PINB,PB0) && skip == 0) // While the lower button remains unpressed...
						{
							sevsegNumber(humidHi);
							segl |= 0b10000000; // Add in the decimal.
							if(bit_is_clear(PINB, PB1)) // If upper button (increment) is pressed.
							{
								while(bit_is_clear(PINB,PB1)) delay_ms(5);
								humidHi += 5;
								if(humidHi > 90) humidHi = 10;
							}
						}
						if(humidHi <= humidLo) // Error!
						{
							segl = 0b11111001;
							segr = 0b01010000;
							delay_ms(1000);
							humidHi = hold;
							
						}
						else
						{
							if(humidHi != hold) eeprom_write_byte((uint8_t*)0x01, humidHi);
						}
						while(bit_is_clear(PINB,PB0)) delay_ms(5);
						selec++;
					}
					
					else if(selec == 4) // ADC readout.
					{
						// "Ad"
						segl = 0b11110111;
						segr = 0b01011110;
						for(;delay>0;delay-=1)
						{
							if(bit_is_clear(PINB,PB1)) break;
							if(bit_is_clear(PINB,PB0))
							{
								// Show ADC value.
								adcReadout();
							}
							delay_ms(5);
						}
						delay = 255;
						// "dc"
						segl = 0b11011110;
						segr = 0b01011000;
						for(;delay>0;delay-=1)
						{
							if(bit_is_clear(PINB,PB1)) break;
							if(bit_is_clear(PINB,PB0))
							{
								// Show ADC value.
								adcReadout();
							}
							delay_ms(5);
						}						
						delay = 120;
					}
					
					if(bit_is_clear(PINB,PB1))
					{
						delay_ms(20);
						if(bit_is_clear(PINB,PB1))
						{
							selec++;
							if(selec > 4) selec = 0; // Change when adding new menu options.
							while(bit_is_clear(PINB,PB1)) delay_ms(5);
						}
					}
				}
				while(bit_is_clear(PINB,PB0)) delay_ms(5);
			}
			else if(counter > 2)
			{
				segl = 0b00000001;
				segr = 0;
				delay_ms(1000);
			}
			// Else we ignore it. Not pressed long enough.
		}
		else if(bit_is_clear(PINB,PB0)) // If lower button is pressed...
		{
			delay_ms(20);
			if(bit_is_clear(PINB,PB0))
			{
				while(bit_is_clear(PINB,PB0)) delay_ms(5);
				segl = 0b00001000;
				segr = 0;
				delay_ms(1000);
			}
		}
		
		// ADC stuff run every loop.
		ADCSRA |= (1<<ADSC);
		delay_ms(5);
		sevsegNumber(humidity);
		
		// And act on it.
		if(humidity > humidHi) RELAYPORT |= (1<<RELAY1);
		if(humidity < humidLo) RELAYPORT &= ~(1<<RELAY1);
	}
	
	return 0;
}
