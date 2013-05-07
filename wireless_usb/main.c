#include <avr/io.h>
#include <stdlib.h>

#include "VirtualSerial.h"
#include "Descriptors.h"
#include "util.h"
#include "nrf.h"

char buffer[7];

int main(void)
{
	// USB BEGIN //
	SetupHardware();
	/* Create a regular character stream for the interface so that it can be used with the stdio.h functions */
	CDC_Device_CreateStream(&VirtualSerial_CDC_Interface, &USBSerialStream);
	
	TCCR0B = (1<<CS02)|(1<<CS00); // Set up timer to handle USB stuff.
	TIMSK0 = (1<<TOIE0);
	
	sei();
	// USB END //
	
	
	while(rxByte != 0x20)
	{
		fputs(".", &USBSerialStream);
		delay_ms(100);
	}
	rxByte = 0;
	nrf_init();

	delay_ms(500);
	
	nrf_spillRegisters();
	
	uint16_t number = 0;
	
	fputs("Last transmission: ",&USBSerialStream);
	itoa(number, buffer, 10);
	fputs(buffer,&USBSerialStream);
			
	
	for (;;)
	{	
		/*while(!rxByte)
		{
			fputs(".", &USBSerialStream);
			delay_ms(100);
		}*/
		number++;
		nrf_tx((uint16_t)number);
		
		fputs("\rLast transmission: ",&USBSerialStream);
		itoa(number, buffer, 10);
		fputs(buffer,&USBSerialStream);
		
		//rxByte = 0;
		
		GET_STATUS;
		if(nrf_last_status & (1<<MAX_RT))
		{
			fputs("\r\nPacket transmission failed. Clearing MAX_RT...\r\n",&USBSerialStream);
			delay_us(1);
			SS_DOWN;
			SPI_WRITE(W_REGISTER | NRG_STATUS);
			SPI_WRITE(1<<MAX_RT);
			SS_UP;
		}
		else
		{
			
		}
		
		delay_ms(500);
		
		//nrf_spillRegisters();
	}
}

ISR(TIMER0_OVF_vect)
{
	usb_ops();
}