/* Trinity Bot - Captain */

#include <avr/io.h>
#include <avr/interrupt.h>    
#include <stdlib.h>
#include "lcd.h"
#include "util.h"
#include "i2c.h"

/* --- Pins ---
 * PORT B:        | PORT C:       | PORT D: 
 * PBO - StartBtn | PC0 - LCD D4  | PD0 - 
 * PB1 - LCD RS   | PC1 - LCD D5  | PD1 - 
 * PB2 - LCD RW   | PC2 - LCD D6  | PD2 - 
 * PB3 - LCD En   | PC3 - LCD D7  | PD3 - 
 * PB4 -          | PC4 - i2c     | PD4 - 
 * PB5 -          | PC5 - i2c     | PD5 - 
 * PB6 -          |               | PD6 - 
 * PB7 -          |               | PD7 - 
 * 
 */

/// Globals ///
char buffer[7]; // Buffer for string conversion.
uint8_t errorCode = 0; // 0=no error, 1=i2c fault, 2/3/4=nav/pilot/copilot offline, 5=servo i2c error, 6=stepper i2c error, 7=slave_read error, 8-11=IR read error, 12=rx choice error, 
uint8_t gState = 0; // States: 0=boot, 1=ready, 2=mapping, 3=searching, 4=candle_alignment, 5=extinguishing, 6=returning_home
uint8_t servoPos1 = 95;
uint8_t servoPos2 = 110;
uint8_t stepperCountTempL = 0x00; // Sign magnitude, MSB = 1 = negative.
uint8_t stepperCountTempR = 0x00;
uint8_t linearMotion = 0; // Centimeters, MSB is direction (1 = reverse).

uint16_t batteryADC = 0x0000;
uint16_t arcIR1 = 0x0000;
uint16_t arcIR2 = 0x0000;
uint16_t arcIR3 = 0x0000;
uint16_t arcIR4 = 0x0000;
uint16_t arcIR5 = 0x0000;
uint16_t arcIR6 = 0x0000;
uint16_t arcIR7 = 0x0000;
uint16_t tempData = 0x0000;
	
int main(void)
{
	DDRB = 0b00001110; // LCD lines.
	DDRC = 0b00001111; // LCD lines.
	PORTB |= (1<<PB0); // Enable pull-up on switch.
	
	//PORTC = (1<<PC4)|(1<<PC5); // Enable pull-ups on i2c pins.

	lcd_init(LCD_DISP_ON); // LCD on, cursor off.
	lcd_clrscr();
	lcd_puts("SYSTEM BOOTING\nWISP OS Ver 0.1"); // Some debug data for the LCD.
	
	i2cInit();
	
	delay_ms(1000);
	
	servoPos1 = 150;
	//servoPos2 = 200;
	
	/*
	servoPos2 = 215;
	i2cStart(22);
	delay_ms(1000);
	servoPos2 = 110;
	i2cStart(22);
	//i2cStart(22);
	 */
	
	lcd_clrscr();
	lcd_puts("Press start..."); // Some debug data for the LCD.
	
	
	while(bit_is_set(PINB,PB0)) delay_ms(1);
	/*stepperCountTempL = 127;
	stepperCountTempR = (0x80 | 127);
	i2cStart(24);
	while(i2cMode) delay_us(40);
	i2cStart(23);
	 */
	//stepperSendTicks(2001,-2001);
	linearMotion = 0x0A;
	i2cStart(25);
	//PORTD = 1;
	//PORTB = 255;	 
	//uint8_t num = 10;
	while(1)
	{
		lcd_clrscr();
		if(errorCode)
		{
			lcd_puts("ERROR: ");
			itoa(errorCode, buffer, 10);
			lcd_puts(buffer);
			//delay_ms(2000);
			//errorCode = 0;
		}
		else
		{
			double volts = (double)batteryADC / 1023.0 * 5.0 * 2.0; 
			lcd_puts("Voltage: ");
			dtostrf(volts, 4, 2, buffer);
			lcd_puts(buffer);
			
			lcd_puts("\nData: ");
			itoa(tempData, buffer, 10);
			lcd_puts(buffer);
			/*lcd_puts(" ");
			itoa(arcIR2, buffer, 10);
			lcd_puts(buffer);
			lcd_puts(" ");
			itoa(arcIR3, buffer, 10);
			lcd_puts(buffer);*/
		}
		
		/*if(!stepperCountTempL)
		{
			stepperCountTempL = 0x7f;
			stepperCountTempR = 0x7f;
			i2cStart(24);
			while(i2cMode) delay_ms(1);
			i2cStart(23);
		}*/
		

		while(rxMode || i2cMode) delay_ms(10);
		rxMode = 90; // Battery voltage.
		i2cStart(9); // And go.
		while(rxMode) delay_us(1);
		delay_us(40);
		//rxMode = 42;
		//i2cStart(9);
		//while(i2cMode) delay_us(1);
		//delay_us(40);
		rxMode = 95;
		i2cStart(9);
		while(i2cMode) delay_us(1);
		/*while(i2cMode) delay_ms(1);
		rxMode = 43;
		i2cStart(9);*/
		
		/*
		while(bit_is_set(PINB,PB0)) delay_ms(1);
		servoPos1 = 0xC0; // Rear straight.
		i2cStart(21);
		while(i2cMode) delay_ms(1);
		delay_ms(500);
		
		while(bit_is_set(PINB,PB0)) delay_ms(1);
		servoPos1 = 0x15; // Front straight.
		i2cStart(21);
		while(i2cMode) delay_ms(1);
		*/
		//if(bit_is_clear(PINB,PB0)) 
		//	i2cStart(29); // CO2!
		
		delay_ms(500);
		
		/*lcd_puts("Hello, fucking \n");
		           
		itoa(num, buffer, 10);
		
		lcd_puts("world!  Num: ");
		lcd_puts(buffer);
		
		delay_ms(200);
		
		num++;*/
	}
	
	return 0; // This shouldn't run, this just makes gcc happy.
}
