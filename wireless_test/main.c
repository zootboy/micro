/* Wireless tester*/

#include <avr/io.h>
#include <avr/interrupt.h>    
#include <stdlib.h>
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
char buffer[7]; // Buffer for string conversion.

int main(void)
{
	DDRD = 0b01111111; // LCD lines.
	//DDRC = 0b00001111; // LCD lines.
	//PORTB |= (1<<PB0); // Enable pull-up on switch.
	
	//PORTC = (1<<PC4)|(1<<PC5); // Enable pull-ups on i2c pins.

	lcd_init(LCD_DISP_ON); // LCD on, cursor off.
	lcd_clrscr();
	//lcd_puts("SYSTEM BOOTING\nWIRELESS TESTER"); // Some debug data for the LCD.
	lcd_puts("BOOTING\nWIRELESS"); // Some debug data for the LCD.
	
	delay_ms(100);
	
	nrf_init();
	CE_UP; // Enable radio.
	
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
		//lcd_puts("Payload: ");
		lcd_puts("P: ");
		itoa(num, buffer, 16);
		lcd_puts(buffer);
		//lcd_puts("\nMsd. pkts: ");
		lcd_puts("\nMP: ");
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
