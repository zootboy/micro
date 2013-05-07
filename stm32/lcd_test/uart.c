// uart.c - uart stuff   //
// Sean Greenslade, 2012 //
#include "uart.h"
#include "stm32f10x.h"

#define BAUD 115200
// BRR = 72E6/(BAUD*16)
#define LOLBRR  39.0625
// MANT = floor(BRR)+[1 if FRAC overflows]
#define DIV_MANT 39
// FRAC = (decimal part of BRR) * 16
#define DIV_FRAC 1

// Globals
char uartTX[80]; // UART transmit buffer.
c_buffer_t uartBuf; // Circular buffer descriptor.

void uart_init(void)
{
	RCC->APB2ENR |= (RCC_APB2ENR_USART1EN | RCC_APB2ENR_AFIOEN); // Enable USART and AFIO clock.
	USART1->CR1 |= (USART_CR1_UE | USART_CR1_TE | USART_CR1_RE | USART_CR1_TXEIE); // Enable everything, including TX ready interrupt.
	USART1->BRR = ((DIV_MANT << 4) | DIV_FRAC); // Set BRR for 115200.
	
	uartBuf = c_buffer_init(uartTX, 80); // Initialize buffer.
	
	NVIC_EnableIRQ(USART1_IRQn); // Enable USART1 interrupt.
	__enable_irq(); // Enable interrupts globally.
}

void txStr(char str[])
{
	uint8_t i;
	for(i=0; str[i] != '\0' && i<255; i++)
	{
		if(c_buffer_write(&uartBuf, str[i])) break;
	}
	NVIC_EnableIRQ(USART1_IRQn); // Enable USART1 interrupt.
}

void USART1_IRQHandler(void)
{
	if(USART1->SR & USART_SR_TXE)
	{
		char out;
		if(c_buffer_read(&uartBuf, &out ) == 0)
		{
			USART1->DR = out;
		}
		else
		{ // We're out of characters, stop the interrupt.
			NVIC_DisableIRQ(USART1_IRQn); 
		}
	}	
}
