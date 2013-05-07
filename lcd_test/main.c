/* Blinker Demo */

/* Include useful pre-defined functions */
//#include <avr/interrupt.h>    // Defines pins, ports, etc to make programs easier to read
#define F_CPU 8000000	      // Sets up the default speed for delay.h
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "cbuff.h" // UART buffer.
#include "util.h"
#include "lcd.h"

// UART buffer stuff;
#define BUFFLEN 60
char uba[BUFFLEN];
c_buffer_t ub;
#define CPUT(x) c_buffer_write(&ub, (x)); pushUART()

void pushUART(void)
{
	char cnext;
	if( (UCSR0A & (1<<UDRE0)) && (c_buffer_read(&ub, &cnext ) == 0) )
	{// USART TX buffer empty && content in circ. buffer...
		UDR0 = cnext; // Transmission begins as soon as write completes.
	}
}

void str2lcd(char *s)
{
	uint8_t i = 0;
	while(s[i] != '\0') 
	{
		CPUT(s[i]);
		i++;
	}
}

ISR(USART_TX_vect)
{
	pushUART();
}

int main(void)
{
	// Set up USART stuff.
	ub = c_buffer_init(uba, BUFFLEN); // Create buffer struct.
	UCSR0B = (1<<TXCIE0)|(1<<TXEN0); // TX complete interrupt enable, TX enable.
	UCSR0C = (1<<UCSZ01)|(1<<UCSZ00); // 8-bit, 1 stop, no parity.
	UBRR0 = 51; // 9600 baud @ 8MHz clock.

	// IO
	DDRB = 0xFF;
	DDRD = 0xFF;

	delay_ms(50); // Let things settle.
  	sei(); // Enable interrupts.

	CPUT(0xFE); CPUT(0x41); // Display on.
	CPUT(0xFE); CPUT(0x46); // Cursor home.
	CPUT(0xFE); CPUT(0x53); CPUT(0x04); // Backlight brightness 4.

	//CPUT('t'); //
	//CPUT('e'); //
	//CPUT('s'); //
	//CPUT('t'); //
	str2lcd("test1");

	lcd_init(LCD_DISP_ON);
	lcd_clrscr();
	lcd_puts("test2");

	while(1)
  	{
		delay_ms(5000);
		CPUT(0xFE); CPUT(0x53); CPUT(0x01); // Backlight brightness 4.
		delay_ms(5000);
		CPUT(0xFE); CPUT(0x53); CPUT(0x08); // Backlight brightness 4.
		//uint8_t i;
		//for(i=1;i<9;i++)
		//{
		//	CPUT(0xFE); CPUT(0x53); CPUT(i); // Backlight brightness 4.
  		//	delay_ms(500);
		//}
	}
}
