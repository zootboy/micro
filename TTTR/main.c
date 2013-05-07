/* Thermal Target Tester Redux */

#include <avr/io.h>
#include <avr/interrupt.h>    
#include <stdlib.h>
#include "lcd.h"
#include "util.h"

/* --- Pins ---
 * PORT B:        | PORT C:        | PORT D: 
 * PBO - LCD_D6   | PC0 - Backlite | PD0 - FTDI  
 * PB1 - LCD_D5   | PC1 - TP1      | PD1 - FTDI   
 * PB2 - LCD_D7   | PC2 - Relay 1  | PD2 - Btn 2   
 * PB3 - mosi     | PC3 - Relay 2  | PD3 - Btn 1 
 * PB4 - miso     | PC4 - Btn 4    | PD4 - LCD_RS
 * PB5 - sck      | PC5 - Btn 3    | PD5 - LCD_RW
 * PB6 - [xtal1]  | ADC6- Current  | PD6 - LCD_E 
 * PB7 - [xtal2]  | ADC7- Therm    | PD7 - LCD_D4
 * 
 */
#define BTN1 3
#define BTN2 2
#define BTN3 5
#define BTN4 4
#define BTNPORT1 PORTD
#define BTNPORT2 PORTD
#define BTNPORT3 PORTC
#define BTNPORT4 PORTC
#define RELAYPORT PORTC
#define RELAY1 2
#define RELAY2 3


/// Globals ///
char buffer[7]; // Buffer for string conversion.

int main(void)
{
        // Initialize all IO and pullups.
	DDRB = 0b00000111;
        DDRC = 0b00001111;
        PORTC = (1<<BTN3)|(1<<BTN4);
        DDRD = 0b11110000;
        PORTD = (1<<BTN1)|(1<<BTN2);
        
        

	lcd_init(LCD_DISP_ON); // LCD on, cursor off.
	lcd_clrscr();
	lcd_puts("SYSTEM BOOTING\nTHERM. TESTER"); // Some debug data for the LCD.
	
	delay_ms(100);
	
	delay_ms(1000);
	
	//lcd_clrscr();
	//lcd_puts("Press start..."); // Some debug data for the LCD.
	
	uint16_t num = 0;
	uint16_t missed = 0;
	
	while(1)
	{
		uint16_t temp = nrf_rx();
		if(temp) 
		{
			num = temp;
			missed = 0;
		}
		else missed++;
		
		lcd_clrscr();
		lcd_puts("Payload: ");
		itoa(num, buffer, 16);
		lcd_puts(buffer);
		lcd_puts("\nMsd. pkts: ");
		itoa(missed, buffer, 10);
		lcd_puts(buffer);
		
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
		
		/*delay_us(1);
		SS_DOWN;
		SPI_WRITE(R_REGISTER | NRG_EN_AA);
		SPI_WRITE(0xFF);
		SS_UP;
		itoa(SPDR, buffer, 16);
		lcd_puts("\nREGISTER: 0x");
		lcd_puts(buffer);
		//if(SPDR & 0xF0) lcd_puts("\nLost packets.");
		//else if(SPDR & 0x0F) lcd_puts("\nRe-tx'd packets.);
		*/
		
		delay_ms(500);

	}
	
	return 0; // This shouldn't run, but it makes gcc happy.
}
