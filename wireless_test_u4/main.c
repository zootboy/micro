/* Wireless tester*/

#include <avr/io.h>
#include <avr/interrupt.h>    
#include <stdlib.h>
#include "lcd.h"
#include "util.h"
#include "nrf.h"

/* --- Pins ---
 * PORT B:        | PORT C:       | PORT D: 
 * PBO - radio_csn| PC0 -         | PD0 - LCD D4
 * PB1 - SCK      | PC1 -         | PD1 - LCD D5 
 * PB2 - MOSI     | PC2 -         | PD2 - LCD D6  
 * PB3 - MISO     | PC3 -         | PD3 - LCD D7
 * PB4 - radio_ce | PC4 - i2c     | PD4 - LCD RS
 * PB5 -          | PC5 - i2c     | PD5 - LCD RW
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
	lcd_puts("SYSTEM BOOTING\nWIRELESS TESTER"); // Some debug data for the LCD.
	
	delay_ms(100);
	
	nrf_init();
	
	delay_ms(1000);
	
	//lcd_clrscr();
	//lcd_puts("Press start..."); // Some debug data for the LCD.
	
	uint16_t num = 0;
	
	while(1)
	{
		num++;
	
		nrf_tx(num);
		
		//lcd_clrscr();
		//lcd_puts("Payload: ");
		//itoa(num, buffer, 16);
		//lcd_puts(buffer);
		
		if(nrf_last_status & (1<<MAX_RT))
		{
			//lcd_puts("\nRe-tx max hit.");
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
		}
		/*SS_DOWN;
		SPI_WRITE(R_REGISTER | NRG_CD);
		SPI_WRITE(0x00); 
		SS_UP;
		delay_us(1);
		if(!(SPDR & 0x01)) lcd_puts("\nCarrier lost.");
		SS_DOWN;
		SPI_WRITE(R_REGISTER | NRG_OBSERVE_TX);
		SPI_WRITE(0x00);
		SS_UP;*/
		//if(SPDR & 0xF0) lcd_puts("\nLost packets.");
		//else if(SPDR & 0x0F) lcd_puts("\nRe-tx'd packets.);
		
		
		delay_ms(500);

	}
	
	return 0; // This shouldn't run, but it makes gcc happy.
}
