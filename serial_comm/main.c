/* Serial Communication Demo */
// F_CPU IS DEFINED IN THE MAKEFILE //
#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h> 
#include <string.h>

// Define baud rate
#define FOSC 8000000// Clock Speed
#define BAUD 9600
#define MYUBRR (FOSC/16/BAUD)-1


void uart_init(void)
{
	// Set baud rate
	UBRRH = (unsigned char)(MYUBRR >> 8);
	UBRRL = (unsigned char)MYUBRR;

	// Enable receiver and transmitter
	UCSRB = (1<<RXEN)|(1<<TXEN);
	
	// Set frame format to 8 data bits, no parity, 1 stop bit
	UCSRC = (1<<URSEL)|(0<<USBS)|(1<<UCSZ1)|(1<<UCSZ0);
	// NOTE: ^^^^^^^^ This is SUPER DUPER important. Don't remove it. 
}


void uart_tx(uint8_t u8Data)
{
	// Wait if a byte is being transmitted
	while((UCSRA&(1<<UDRE)) == 0);

	// Transmit data
	UDR = u8Data;
}


uint8_t uart_rx(void)
{

	// Wait until a byte has been received
	while((UCSRA&(1<<RXC)) == 0);
	
	
	
	// Return received data
	return UDR;
}

void string_tx(char* string)
{
	unsigned int len = strlen(string);
	for(int i=0;i<len;i++)
	{
		uart_tx(string[i]);
	}
}


int main(void)
{
	uint8_t u8Data;

	// Initialise USART
	uart_init();

	// Send string
	//while(1)
	//{
	string_tx((char*)"ATMega 8 AVR microcontroller initialized. Starting echo...\r\n");
	//}

	// Repeat indefinitely
	while(1)
	{
	// Echo received characters
		u8Data = uart_rx();
		uart_tx(u8Data);
	}
}