/* 
 * File: pwm.c
 * Author: Sean Greenslade
 *
 * PWM signal generator for Victor motor controller driving.
 */

#include "cpu_interface.h"
#include "inc/lm4f120h5qr.h"


void pwm_init(void)
{
	SYSCTL_RCGCTIMER_R |= SYSCTL_RCGCTIMER_R0; // Timer clock gate removed. 
	SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R1; // GPIO PORTB enable.

	TIMER0_CTL_R = 0; // Disable timers 0A and 0B.
	TIMER0_CFG_R = TIMER_CFG_16_BIT; // 16-bit timer mode.
	TIMER0_TAMR_R = TIMER_TAMR_TAMR_PERIOD|TIMER_TAMR_TAAMS; // Periodic counter, alt mode (PWM).
	// Sysclock = 48MHz, clkdiv = 16, TimerClk = 3MHz
	TIMER0_TAPR_R = (21)-1; // 16x prescale (0 = 1x prescale).
	TIMER0_TBPR_R = (21)-1; // 16x prescale (0 = 1x prescale).
	// Reset value = 50,000 for period of 1/60.
	TIMER0_TAILR_R = 26613; // Load value for down counter.
	TIMER0_TBILR_R = 26613; // Load value for down counter.
	// Match value should be between 3,000 and 6,000. Neutal center = 4,500.
	TIMER0_TAMATCHR_R = (54464); // Default to neutral.
	TIMER0_TAPMR_R = 1; 
	TIMER0_TBMATCHR_R = 50000-4500; // Default to neutral.

	GPIO_PORTB_DEN_R = (1<<7)|(1<<6); // Enable digital out on PB7,6.
	GPIO_PORTB_PCTL_R = GPIO_PCTL_PB6_T0CCP0|GPIO_PCTL_PB7_T0CCP1; // AFIO mux -> Timer 0 compare.
	GPIO_PORTB_AFSEL_R = (1<<7)|(1<<6); // PB6&7 alternate function enabled.
	TIMER0_CTL_R = TIMER_CTL_TAEN|TIMER_CTL_TBEN|TIMER_CTL_TAPWML|TIMER_CTL_TBPWML; // Enable timers.
}
