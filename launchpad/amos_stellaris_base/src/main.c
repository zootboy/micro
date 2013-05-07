#include <stdio.h>

#include "inc/lm4f120h5qr.h"

#include "inc/hw_types.h"
#include "inc/hw_memmap.h"

#include "driverlib/sysctl.h"
#include "driverlib/systick.h"
#include "driverlib/watchdog.h"

#include "jaguar.h"
#include "cpu_interface.h"
#include "pwm.h"

#define WAIT_1MS ((SysCtlClockGet()/3)/1000)

#define LED_RED 0x2
#define LED_BLUE 0x4
#define LED_GREEN 0x8

volatile uint8_t clear_watchdog = 0;

void watchdog_int(void)
{
	if( clear_watchdog ) 
	{
		WatchdogIntClear( WATCHDOG0_BASE );
	}
	else
	{
		GPIO_PORTF_DATA_R |= LED_GREEN|LED_BLUE|LED_RED;
	}
	clear_watchdog = 0;
}

int main(void)
{
	// enable PORT F GPIO peripheral
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_WDOG0);
	
	// set LED PORT F pins as outputs
	GPIO_PORTF_DIR_R = LED_RED|LED_BLUE|LED_GREEN;

	// enable digital for LED PORT F pins
	GPIO_PORTF_DEN_R = LED_RED|LED_BLUE|LED_GREEN;

	// clear all PORT F pins
	GPIO_PORTF_DATA_R = 0;

	SysCtlDelay( 1000 * WAIT_1MS );

	// Init lines go here...

	SysCtlDelay( 10 * WAIT_1MS );

//	cpu_message_init();


	/*
	// sys tick setup - overflow every 2 seconds
	SysTickPeriodSet( 2 * SysCtlClockGet() );
	SysTickEnable();

	// Watchdog setup
	WatchdogReloadSet( WATCHDOG0_BASE, SysCtlClockGet() / 2 );
	WatchdogResetEnable( WATCHDOG0_BASE );
	WatchdogIntEnable( WATCHDOG0_BASE );
	WatchdogIntRegister( WATCHDOG0_BASE, watchdog_int );

	// Lock and start it
	WatchdogEnable( WATCHDOG0_BASE );
	WatchdogLock( WATCHDOG0_BASE );
	*/

	SysCtlDelay( 10 * WAIT_1MS );

	//jaguar_control_mode_set( SPEED_CONTROL, RIGHT_MOTOR, 20<<16 );
	//jaguar_control_mode_set( SPEED_CONTROL, LEFT_MOTOR, 20<<16 );
	
	pwm_init();

	// loop forever
	for(;;)
	{
		GPIO_PORTF_DATA_R |= LED_GREEN|LED_BLUE|LED_RED;
		
	}
}
