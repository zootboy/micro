#include "stm32f10x.h"
#include <math.h>
#include <string.h>

#define DELAY                1 << 17
#define LED1                 1 << 0
#define LED2                 1 << 1
//void EXTI2_IRQHandler(void);

// User Key A = PC13
void EXTI15_10_IRQHandler(void)
{
	if(EXTI->PR & (1<<13))
	{
		EXTI->PR = (1<<13); // Clear the interrupt.
		if(GPIOB->ODR & LED2) GPIOB->BRR = LED2;
		else GPIOB->BSRR = LED2;
	}
}

int main(void)
{
  	int d;

  	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN | RCC_APB2ENR_IOPCEN | RCC_APB2ENR_AFIOEN; // Enable GPIOB, AltFuncIO.
	GPIOB->CRL = 0x44444422;            // Cfg GPIOB.0,1 as output

	// External interrupt stuff.
	AFIO->EXTICR[3] &= 0xFF0F; // Clear the section we want to write.
	AFIO->EXTICR[3] = AFIO_EXTICR4_EXTI13_PC; // Set external interrupt 13 to port C.
	EXTI->IMR = EXTI_IMR_MR13; // Unmask EXT13 interrupt.
	EXTI->FTSR = EXTI_FTSR_TR13; // Enable interrupt on falling edge.	
	////NVIC->ISER[0] |= NVIC_ISER_SETENA_8; // Enable IRQ 8 (EXTI2)
	NVIC_EnableIRQ(EXTI15_10_IRQn);
	__enable_irq(); // Enable interrupts globally.

  	// PWM stuff.
  	//TIM1->CR1 |= TIM_CR1_CEN; // Enable counter.
  	//TIM1->CR2 |= 0;

  	while (1) {
     	GPIOB->BSRR = LED1;
		for (d = DELAY; d; d--);
     	GPIOB->BRR = LED1;
     	for (d = DELAY << 2; d; d--);
		//if(!(GPIOC->IDR & (1<<13))) GPIOB->BSRR = LED2;
		//else GPIOB->BRR = LED2;
  	}
  	/* return 0; */
}
