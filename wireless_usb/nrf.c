/* nrf.c - nRF24L01 radio functions */

#include "nrf.h"
#include "util.h"
#include <stdlib.h>

// Vars.
/* States:
 * 0 = Doing nothing
 * 1 = sending command
 * 2 = sending nulls to do an RX (maybe)
 * 3 = sending real data
 */
uint8_t spi_state = 0;
uint8_t spi_command = 0x00; // The command being sent/last sent.
uint8_t spi_bytes_sent = 0; // Counter for multibyte data transfers.
uint8_t nrf_last_status = 0; // Last status register received.

char buffer[7]; // Buffer for string conversion.

// Functions.
void nrf_init(void)
{
	//lcd_clrscr(); lcd_puts("Setup running...");
	fputs("\r\nInitializing nRF...\r\n", &USBSerialStream);
	
	NRF_SS_DDR |= (1<<NRF_SS_PIN); NRF_SS_PORT |= (1<<NRF_SS_PIN); // SS starts high.
	NRF_CE_DDR |= (1<<NRF_CE_PIN); NRF_CE_PORT &= ~(1<<NRF_CE_PIN); // CE (radio enable) starts low.
	SPI_DDR |= (1<<SPI_MOSI)|(1<<SPI_SCK); SPI_DDR &= ~(1<<SPI_MISO); // Set the correct directions for SPI.
	
	SPCR = NRF_SPCR; // Set registers. This officially turns on the SPI hardware.

	delay_us(200);
	
	// Do a test call to the nRF
	SS_DOWN; // Bring the nRF SS line low to begin transaction.
	SPI_WRITE(NOP); // Start up the SPI transfer.
	nrf_last_status = SPDR;
	SS_UP;
	itoa(nrf_last_status, buffer, 16);
	fputs("Status register: 0x", &USBSerialStream);
	fputs(buffer, &USBSerialStream);
	fputs("\r\n", &USBSerialStream);
	
	if(!nrf_last_status || (nrf_last_status & (1<<7))) // On reset, the RX FIFO should be empty (setting some bits) and bit 7 should be zero.
	{
		//lcd_clrscr();
		//lcd_puts("no nRF detected");
		fputs("No nRF detected...\r\n", &USBSerialStream);
		delay_ms(2000);
	}
	else
	{
		// Set all addresses.
		SS_DOWN;
		SPI_WRITE(W_REGISTER | NRG_SETUP_AW);
		SPI_WRITE(0x03); // 5-byte addresses.
		SS_UP;
		delay_us(1);
		SS_DOWN;
		SPI_WRITE(W_REGISTER | NRG_TX_ADDR); // Transmitting address.
		SPI_WRITE(0xFF & (NRF_ADDRESS >> 0));
		SPI_WRITE(0xFF & (NRF_ADDRESS >> 8));
		SPI_WRITE(0xFF & (NRF_ADDRESS >> 16));
		SPI_WRITE(0xFF & (NRF_ADDRESS >> 24));
		SPI_WRITE(0xFF & (NRF_ADDRESS >> 32));
		SS_UP;
		delay_us(1);
		SS_DOWN;
		SPI_WRITE(W_REGISTER | NRG_RX_ADDR_P0); // Ack/Receiving address.
		SPI_WRITE(0xFF & (NRF_ADDRESS >> 0));
		SPI_WRITE(0xFF & (NRF_ADDRESS >> 8));
		SPI_WRITE(0xFF & (NRF_ADDRESS >> 16));
		SPI_WRITE(0xFF & (NRF_ADDRESS >> 24));
		SPI_WRITE(0xFF & (NRF_ADDRESS >> 32));
		SS_UP;
		delay_us(1);
		SS_DOWN;
		SPI_WRITE(W_REGISTER | NRG_RX_PW_P0);
		SPI_WRITE(0x3F & NRF_PAYLOADBYTES);
		SS_UP;
		delay_us(1);
		SS_DOWN;
		SPI_WRITE(W_REGISTER | NRG_EN_RXADDR);
		SPI_WRITE(0x01); // Only enable pipe 0.
		SS_UP;
		delay_us(1);
		SS_DOWN;
		SPI_WRITE(W_REGISTER | NRG_RF_CH);
		SPI_WRITE(0x7F & NRF_CHANNEL);
		SS_UP;
		delay_us(1);
		SS_DOWN;
		SPI_WRITE(W_REGISTER | NRG_RF_SETUP);
		SPI_WRITE(0x0F & ((NRF_RATE<<RF_DR)|(NRF_POWER<<RF_PWR)|(NRF_RXGAIN<<LNA_HCURR)));
		SS_UP;
		delay_us(1);
		SS_DOWN;
		SPI_WRITE(W_REGISTER | NRG_EN_AA);
		SPI_WRITE(0x01 & NRF_AUTOACK);
		SS_UP;
		delay_us(1);
		SS_DOWN;
		SPI_WRITE(W_REGISTER | NRG_CONFIG);
		SPI_WRITE(0x7F & ((NRF_INTERRUPTS<<MASK_ALL)|(NRF_CRCEN<<EN_CRC)|(NRF_CRCTWO<<CRCO)|(1<<PWR_UP)|(NRF_RX<<PRIM_RX)));
		SS_UP;
		delay_us(10);
		//lcd_clrscr(); lcd_puts("Setup complete. ");
	}
	
}

void nrf_tx(uint16_t payload)
{
	SS_DOWN;
	SPI_WRITE(W_TX_PAYLOAD);
	nrf_last_status = SPDR;
	SPI_WRITE(0xFF & payload);
	SPI_WRITE(0xFF & (payload >> 8));
	SS_UP;
	delay_us(5);
	// Strobe CE to start transmission.
	CE_UP;
	delay_us(20);
	CE_DOWN;
}

uint16_t nrf_rx(void)
{
	uint16_t payload;
	if(!NRF_RX) return 0;
	SS_DOWN; // Bring the nRF SS line low to begin transaction.
	SPI_WRITE(NOP); // Start up the SPI transfer.
	nrf_last_status = SPDR;
	SS_UP;
	if(nrf_last_status & (1<<RX_DR))
	{
		delay_us(1);
		SS_DOWN;
		SPI_WRITE(R_RX_PAYLOAD);
		SPI_WRITE(0x00); payload = SPDR;
		SPI_WRITE(0x00); payload |= ((uint16_t)SPDR << 8);
		SS_UP;
		delay_us(1);
		SS_DOWN;
		SPI_WRITE(R_REGISTER | NRG_FIFO_STATUS);
		nrf_last_status = SPDR;
		SPI_WRITE(0x00); 
		SS_UP;
		if(SPDR & (1<<RX_EMPTY))
		{
			delay_us(1);
			SS_DOWN;
			SPI_WRITE(W_REGISTER | NRG_STATUS);
			SPI_WRITE(0x7f & (1<<RX_DR));
		}
		return payload;
	}
	else return 0;
	
}

// Spill contents of all relevent registers.
void nrf_spillRegisters(void)
{
	fputs("Spilling registers...\r\n", &USBSerialStream);
	
	delay_us(1);
	SS_DOWN;
	SPI_WRITE(R_REGISTER | NRG_CONFIG);
	SPI_WRITE(0xFF);
	SS_UP;
	itoa(SPDR, buffer, 16);
	fputs("Status register: 0x", &USBSerialStream);
	fputs(buffer, &USBSerialStream);
	fputs("\r\n", &USBSerialStream);
	
	delay_us(1);
	SS_DOWN;
	SPI_WRITE(R_REGISTER | NRG_EN_AA);
	SPI_WRITE(0xFF);
	SS_UP;
	itoa(SPDR, buffer, 16);
	fputs("EN_AA register: 0x", &USBSerialStream);
	fputs(buffer, &USBSerialStream);
	fputs("\r\n", &USBSerialStream);

	delay_us(1);
	SS_DOWN;
	SPI_WRITE(R_REGISTER | NRG_EN_RXADDR);
	SPI_WRITE(0xFF);
	SS_UP;
	itoa(SPDR, buffer, 16);
	fputs("EN_RXADDR register: 0x", &USBSerialStream);
	fputs(buffer, &USBSerialStream);
	fputs("\r\n", &USBSerialStream);
	
	delay_us(1);
	SS_DOWN;
	SPI_WRITE(R_REGISTER | NRG_RF_CH);
	SPI_WRITE(0xFF);
	SS_UP;
	itoa(SPDR, buffer, 16);
	fputs("RC_CH register: 0x", &USBSerialStream);
	fputs(buffer, &USBSerialStream);
	fputs("\r\n", &USBSerialStream);
	
	delay_us(1);
	SS_DOWN;
	SPI_WRITE(R_REGISTER | NRG_STATUS);
	SPI_WRITE(0xFF);
	SS_UP;
	itoa(SPDR, buffer, 16);
	fputs("Status register: 0x", &USBSerialStream);
	fputs(buffer, &USBSerialStream);
	fputs("\r\n", &USBSerialStream);
	
	delay_us(1);
	SS_DOWN;
	SPI_WRITE(R_REGISTER | NRG_OBSERVE_TX);
	SPI_WRITE(0xFF);
	SS_UP;
	itoa(SPDR, buffer, 16);
	fputs("Observe TX register: 0x", &USBSerialStream);
	fputs(buffer, &USBSerialStream);
	fputs("\r\n", &USBSerialStream);
	
	delay_us(1);
	SS_DOWN;
	SPI_WRITE(R_REGISTER | NRG_FIFO_STATUS);
	SPI_WRITE(0xFF);
	SS_UP;
	itoa(SPDR, buffer, 16);
	fputs("FIFO Status register: 0x", &USBSerialStream);
	fputs(buffer, &USBSerialStream);
	fputs("\r\n", &USBSerialStream);
}