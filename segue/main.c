/* Wireless tester*/

#include <avr/io.h>
#include <avr/interrupt.h>    
#include <stdlib.h>
#include <math.h>
#include "lcd.h"
#include "util.h"
#include "nrf.h"

/* --- Pins ---
 * PORT B:        | PORT C:       | PORT D: 
 * PBO - radio_ce | PC0 -         | PD0 - LCD D4
 * PB1 -          | PC1 -         | PD1 - LCD D5 
 * PB2 - radio_csn| PC2 -         | PD2 - LCD D6  
 * PB3 - MOSI     | PC3 -         | PD3 - LCD D7
 * PB4 - MISO     | PC4 - i2c     | PD4 - LCD RS
 * PB5 - SCK      | PC5 - i2c     | PD5 - LCD RW
 * PB6 -          |               | PD6 - LCD EN
 * PB7 -          |               | PD7 - 
 * 
 */

/// Globals ///
char buffer[9]; // Buffer for string conversion.

#define TILTRBSIZE 80
#define GYRORBSIZE 10	

double tilt = 0.0;
double gyro = 0.0;
uint16_t tilt_rb[TILTRBSIZE];
uint16_t gyro_rb[GYRORBSIZE];
uint8_t tilt_index = 0;
uint8_t gyro_index = 0;
double gyro_steadystate = -0.24;
double tilt_zero = -1.9;
uint8_t calibrate_count = 0;
uint8_t tilt_count = 0;
double tilt_min = 0;
double tilt_max = 0;

#define INTEGRATE_TIME 0.03264 // 8000000/1024/256 = ~30; 1/30 = ~0.03
#define TILT_THRESHOLD 0.5 // Delta degrees allowed for tilt gyro calibration.
#define TILT_CALFREQ 5 // Frequency of tilt calibrate. Lower = more often. Shouldn't be too often...
#define OFFSET_STRENGTH 0.25 // Percentage strength of tilt offset tweak. Should never be over 1.0


int main(void)
{
	DDRD = 0b01111111; // LCD lines.
	//DDRC = 0b00001111; // LCD lines.
	PORTB |= (1<<PB1); // Enable pull-up on button.
	
	//PORTC = (1<<PC4)|(1<<PC5); // Enable pull-ups on i2c pins.

	lcd_init(LCD_DISP_ON); // LCD on, cursor off.
	lcd_clrscr();
	lcd_puts("SYSTEM BOOTING\nSEGUE"); // Some debug data for the LCD.
	
	ADMUX = (1<<REFS0)|(0<<MUX0); // AVCC reference, pin select.
	ADCSRA = (1<<ADEN)|(1<<ADPS2)|(1<<ADPS0)|(1<<ADIE); // Enable ADC, precsaler x32, enable interrupt.
	DIDR0 = (1<<ADC0D)|(1<<ADC1D); // Disable digital input buffer on ADC0 & 1.
	
	TCCR0A = 0;
	TCCR0B = (1<<CS02)|(1<<CS00); // Prescale by 1024
	TIMSK0 = (1<<TOIE0);
	
	delay_ms(100);
	
	sei();
	
	ADCSRA |= (1<<ADSC);
	
	//nrf_init();
	//CE_UP; // Enable radio.
	
	//delay_ms(1000);
	
	//lcd_clrscr();
	//lcd_puts("Press start..."); // Some debug data for the LCD.

	
	while(1)
	{	
		uint32_t value = 0;
		for(uint8_t i = 0;i<TILTRBSIZE;i++) value += tilt_rb[i];
		value /= TILTRBSIZE;
		
		tilt = asin(((double)value / 512.0) - 1.0) * 180.0 * M_1_PI * 0.45;
		if(bit_is_clear(PINB,PB1) && !calibrate_count) 
		{
			cli();
			tilt_zero = tilt;
			calibrate_count = 1;
			gyro_steadystate = 0.0;
			gyro = 0;
			sei();
		}
		tilt -= tilt_zero;
		
		lcd_clrscr();
		lcd_puts("Tilt: ");
		dtostrf(tilt, 3, 1, buffer);
		lcd_puts(buffer);
		lcd_puts("\nGyro: ");
		if(calibrate_count) lcd_puts("CAL");
		else
		{
			dtostrf(gyro, 3, 1, buffer);
			lcd_puts(buffer);
		}
		
		/*if(nrf_last_status & (1<<MAX_RT))
		{
			lcd_puts("\nRe-tx max hit.");
			SS_DOWN;
			SPI_WRITE(W_REGISTER | NRG_STATUS);
			SPI_WRITE(0x7F & (1<<MAX_RT));
			SS_UP;
			delay_us(1);
			SS_DOWN;
			SPI_WRITE(NOP);
			SS_UP;
			nrf_last_status = SPDR;
			delay_us(1);
		}*/
	
		
		delay_ms(100);

	}
	
	return 0; // This shouldn't run, but it makes gcc happy.
}


ISR(TIMER0_OVF_vect) // Integrator timer.
{
	uint32_t value = 0;
	double hold = 0.0;
	for(uint8_t i = 0;i<GYRORBSIZE;i++) value += gyro_rb[i];
	value /= GYRORBSIZE;
	
	if(calibrate_count == 0) 
	{
		hold = ((double)value / 512.0) - 1.0 - gyro_steadystate; // Scale to -1 thru +1.
		
		// Tilt calibration routines.
		tilt_count++;
		if(tilt_count >= TILT_CALFREQ) tilt_count = 0;
		if(!tilt_count)
		{
			if((tilt - tilt_min) < TILT_THRESHOLD && (tilt_max - tilt) < TILT_THRESHOLD)
			{ // Tilt is steady. Calibrate gyro.
				double offset = gyro - tilt;
				offset /= (INTEGRATE_TIME * -80.0 * (TILT_CALFREQ-1));
				gyro_steadystate += offset * OFFSET_STRENGTH;
				
				// Also reset the absolute angle.
				gyro = (tilt+gyro)/2.0; // Average the current angle and desired angle to make the jump less abrupt.
			}	
			tilt_min = tilt; tilt_max = tilt; // And reset.
		}
		else
		{
			if(tilt < tilt_min) tilt_min = tilt;
			if(tilt > tilt_max) tilt_max = tilt;
		}
	}
	else
	{
		if(calibrate_count == 255)
		{
			gyro_steadystate = (gyro / 254.0);
			calibrate_count = 0;
			gyro = 0;
		}
		else 
		{
			calibrate_count++;
			hold = ((double)value / 512.0) - 1.0;
		}
	}
	/*if(bit_is_clear(PINB,PB1))
	{
		gyro_steadystate += hold * 0.7;
		gyro = 0;
	}*/
	
	//tilt = hold; //TEMP TEST
	
	if(calibrate_count != 0) gyro += hold;
	else gyro += (hold * INTEGRATE_TIME * -80.0);
}

ISR(ADC_vect)
{
	if(bit_is_set(ADMUX,MUX0)) // Gyro
	{
		gyro_index++; if(gyro_index >= GYRORBSIZE) gyro_index = 0;
		gyro_rb[gyro_index] = ADC;
		
		ADMUX &= ~(1<<MUX0);
	}
	else // Tilt
	{
		tilt_index++; if(tilt_index >= TILTRBSIZE) tilt_index = 0;
		tilt_rb[tilt_index] = ADC;
		
		ADMUX |= (1<<MUX0);
	}
	
	ADCSRA |= (1<<ADSC); // Begin next conversion.
}
