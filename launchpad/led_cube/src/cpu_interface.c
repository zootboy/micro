/*
 * File:	cpu_interface.c
 * Author:	James Letendre
 *
 * Interface from Stellaris to the CPU
 */
#include "cpu_interface.h"
#include "jaguar.h"

#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "inc/lm4f120h5qr.h"

#include "driverlib/timer.h"
#include "driverlib/uart.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/systick.h"
#include "driverlib/watchdog.h"

#include <stdlib.h>

#define LED_RED 0x2
#define LED_BLUE 0x4
#define LED_GREEN 0x8


/*
 * Buffer space to build a message object into
 */
uint8_t message_buffer[18];
int8_t message_buffer_index = -1;
int8_t message_escape_received = 0;	// received the 0xFE byte

enum {
	INVALID,
	CLOSED_LOOP,
	OPEN_LOOP
} jaguar_mode;

// PID
uint16_t jaguar_P = 0x0000000;
uint16_t jaguar_I = 0x0000000;
uint16_t jaguar_D = 0x0000000;


/*
 * Functions to handle each type of message
 */
typedef int (*cpu_message_handle)(cpu_message_t *message );

// CONTROL
int cpu_message_control_heartbeat( cpu_message_t *message );
int cpu_message_control_reset( cpu_message_t *message );
int cpu_message_control_stop( cpu_message_t *message );
int cpu_message_control_start( cpu_message_t *message );
int cpu_message_control_closed_loop( cpu_message_t *message );
int cpu_message_control_open_loop( cpu_message_t *message );

// CLOSED LOOP
int cpu_message_closed_loop_set_P( cpu_message_t *message );
int cpu_message_closed_loop_set_I( cpu_message_t *message );
int cpu_message_closed_loop_set_D( cpu_message_t *message );
int cpu_message_closed_loop_set_speed( cpu_message_t *message );

// OPEN LOOP
int cpu_message_open_loop_set_voltage( cpu_message_t *message );

// MONITOR
int cpu_message_monitor_get_voltage( cpu_message_t *message );
int cpu_message_monitor_get_current( cpu_message_t *message );
int cpu_message_monitor_get_temp( cpu_message_t *message );
int cpu_message_monitor_get_position( cpu_message_t *message );

// invalid
int invalid_message( cpu_message_t *message );

int handle_message( cpu_message_t *message );

/*
 * Lookup table to handle different messages
 */
cpu_message_handle message_handlers[4][8] = 
{
	// CONTROL
	{
		cpu_message_control_heartbeat,
		cpu_message_control_reset,
		cpu_message_control_stop,
		cpu_message_control_start,
		cpu_message_control_closed_loop,
		cpu_message_control_open_loop,
		invalid_message,
		invalid_message
	},
	// CLOSED LOOP
	{
		cpu_message_closed_loop_set_P,
		cpu_message_closed_loop_set_I,
		cpu_message_closed_loop_set_D,
		cpu_message_closed_loop_set_speed,
		invalid_message,
		invalid_message,
		invalid_message,
		invalid_message
	},
	// OPEN LOOP
	{
		cpu_message_open_loop_set_voltage,
		invalid_message,
		invalid_message,
		invalid_message,
		invalid_message,
		invalid_message,
		invalid_message,
		invalid_message
	},
	// MONITOR
	{
		cpu_message_monitor_get_voltage,
		cpu_message_monitor_get_current,
		cpu_message_monitor_get_temp,
		cpu_message_monitor_get_position,
		invalid_message,
		invalid_message,
		invalid_message,
		invalid_message
	}
};

/* 
 * initialize system
 */
void cpu_message_init( void )
{
	jaguar_mode = INVALID;

	jaguar_P = 0x00000000;
	jaguar_I = 0x00000000;
	jaguar_D = 0x00000000;

	/*
	// setup periodic messages
	// disable them
	jaguar_periodic_status_enable( 0, VOLTAGE_MESSAGE,  0 );
	jaguar_periodic_status_enable( 0, CURRENT_MESSAGE,  0 );
	jaguar_periodic_status_enable( 0, TEMP_MESSAGE,     0 );
	jaguar_periodic_status_enable( 0, POSITION_MESSAGE, 0 );

	// setup contents
	jaguar_periodic_status_config( 0, VOLTAGE_MESSAGE,  2, BUS_VOLTAGE_0,   BUS_VOLTAGE_1, END_OF_MESSAGE );
	jaguar_periodic_status_config( 0, CURRENT_MESSAGE,  2, MOTOR_CURRENT_0, MOTOR_CURRENT_1, END_OF_MESSAGE );
	jaguar_periodic_status_config( 0, TEMP_MESSAGE,     2, TEMPERATURE_0,   TEMPERATURE_1, END_OF_MESSAGE );
	jaguar_periodic_status_config( 0, POSITION_MESSAGE, 4, POSITION_0, POSITION_1, POSITION_2, POSITION_3, END_OF_MESSAGE );

	// enable them at 1 Hz
	jaguar_periodic_status_enable( 0, VOLTAGE_MESSAGE,  256 );
	jaguar_periodic_status_enable( 0, CURRENT_MESSAGE,  256 );
	jaguar_periodic_status_enable( 0, TEMP_MESSAGE,     256 );
	jaguar_periodic_status_enable( 0, POSITION_MESSAGE, 256 );
	*/

	SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);

	// setup timer for heartbeat
	TimerDisable( TIMER0_BASE, TIMER_BOTH );
	TimerConfigure( TIMER0_BASE, TIMER_CFG_PERIODIC );
	
	// 75 ms period
	uint32_t period_val = SysCtlClockGet() / 4;
	TimerLoadSet( TIMER0_BASE, TIMER_A, period_val );

	// setup interrupts
	TimerIntRegister( TIMER0_BASE, TIMER_A, cpu_message_periodic );
	TimerIntEnable( TIMER0_BASE, TIMER_TIMA_TIMEOUT );

	// go
	TimerEnable( TIMER0_BASE, TIMER_A );
}

void cpu_message_periodic( void )
{
	static uint8_t idx = 0;

	uint32_t status = TimerIntStatus( TIMER0_BASE, 0 );
	TimerIntClear( TIMER0_BASE, status );
	
	for( int i = 2; i <= 3; i++ )
	{
		// request all the status items
		switch( idx )
		{
			case 0:
				jaguar_status(i, BUS_VOLTAGE);
				break;
			case 1:
				jaguar_status(i, CURRENT);
				break;
			case 2:
				jaguar_status(i, TEMPERATURE);
				break;
			case 3:
				jaguar_status(i, POSITION);
				break;
		}
	}

	idx = (idx+1) % 4;
}

/*
 * create a cpu message
 *
 * returns 0 if valid message was created
 */
int cpu_message_create( cpu_message_t *message, cpu_msg_class msg_class, 
		uint8_t msg_idx, uint8_t size, uint8_t data[] )
{
	if( size > 8 || ( size > 0 && data == NULL ) ||
			message == NULL) 
		return -1;

	// set new message info
	message->message_info.size	= size;
	message->message_info.index	= msg_idx;
	message->message_info.class	= msg_class;

	for( int i = 0; i < size; i++ )
	{
		message->data[i] = data[i];
	}

	return 0;
}

/* 
 * send a cpu message 
 */
void cpu_message_send( cpu_message_t *message )
{
	// valid message ptr?
	if( !message ) return;

	uint8_t size = message->message_info.size;

	// SOF
	UARTCharPut( UART0_BASE, 0xFF );

	// Message info
	if( message->message_info.all == 0xFF )
	{
		UARTCharPut( UART0_BASE, 0xFE );
		UARTCharPut( UART0_BASE, 0xFE );
	}
	else if( message->message_info.all == 0xFE )
	{
		UARTCharPut( UART0_BASE, 0xFE );
		UARTCharPut( UART0_BASE, 0xFD );
	}
	else
	{
		UARTCharPut( UART0_BASE, message->message_info.all );
	}

	// data bytes
	for( int i = 0; i < size; i++ )
	{
		if( message->data[i] == 0xFF )
		{
			UARTCharPut( UART0_BASE, 0xFE );
			UARTCharPut( UART0_BASE, 0xFE );
		}
		else if( message->data[i] == 0xFE )
		{
			UARTCharPut( UART0_BASE, 0xFE );
			UARTCharPut( UART0_BASE, 0xFD );
		}
		else
		{
			UARTCharPut( UART0_BASE, message->data[i] );
		}
	}
}

/* 
 * process a cpu message 
 *
 * returns: 1 if no message processed
 */
int cpu_message_process( void )
{
	static unsigned long last_cpu_command = 0;

	GPIO_PORTF_DATA_R &= ~(LED_GREEN|LED_BLUE);

	switch( jaguar_mode )
	{
		case INVALID:
			//GPIO_PORTF_DATA_R |= LED_RED;
			break;
		case CLOSED_LOOP:
			GPIO_PORTF_DATA_R |= LED_BLUE;
			break;
		case OPEN_LOOP:
			GPIO_PORTF_DATA_R |= LED_GREEN;
			break;
	}

	if( UARTCharsAvail( UART0_BASE ) )
	{
		uint8_t byte = UARTCharGet( UART0_BASE );
		if( byte == 0xFF )
		{
			// start of message found
			message_buffer_index = 0;
			message_escape_received = 0;
		}
		else if( message_buffer_index >= 0 )
		{
			// Next byte of data
			if( byte == 0xFE && message_escape_received == 0 ) 
			{
				// escape character byte
				message_escape_received = 1;

				return 1;
			}
			else if( message_escape_received == 1 )
			{
				// was escaped before
				message_escape_received = 0;

				if( byte == 0xFE )		byte = 0xFF;
				else if( byte == 0xFD ) byte = 0xFE;
				else
				{
					// Badly formated message, restart
					message_buffer_index = -1;
					return 1;
				}
			}
			// else -> normal byte

			message_buffer[message_buffer_index++] = byte;

			// check if the message is done being received
			cpu_message_info_t info = (cpu_message_info_t)message_buffer[0];
			if( info.size == message_buffer_index - 1 )
			{
				// have whole message, create object
				cpu_message_t msg;
				cpu_message_create( &msg, info.class, info.index, info.size, &message_buffer[1] );

				int is_heartbeat = (info.class == CPU_MSG_CONTROL && info.index == CPU_CONTROL_HEARTBEAT);
				if( !is_heartbeat )
				{
					// not a heartbeat, so command
					last_cpu_command = SysTickValueGet();
				}

				unsigned long elapsed_time = SysTickValueGet() - last_cpu_command;
				elapsed_time /= (SysCtlClockGet()/10);

				if( !is_heartbeat || ( is_heartbeat && (last_cpu_command < 15) ) )
				{
					// handle this message, if it isn't a heartbeat, or the last command came in at most 1.5 seconds ago
					handle_message( &msg );
				}

				message_buffer_index = -1;

				return 0;

			}
		}
	}
	return 1;
}

extern volatile uint8_t clear_watchdog;
int handle_message( cpu_message_t *message )
{
	if( !message_handlers[message->message_info.class][message->message_info.index]( message ) )
	{
		// reset the watchdog timer, if message was handled successfully
		clear_watchdog = 1;
	}
	return 0;
}

// CONTROL
int cpu_message_control_heartbeat( cpu_message_t *message )
{
	jaguar_heartbeat( );
	return 0;
}

int cpu_message_control_reset( cpu_message_t *message )
{
	jaguar_sys_reset( LEFT_MOTOR );
	jaguar_sys_reset( RIGHT_MOTOR );

	return 0;
}

int cpu_message_control_stop( cpu_message_t *message )
{
	jaguar_sys_stop( LEFT_MOTOR );
	jaguar_sys_stop( RIGHT_MOTOR );

	return 0;
}

int cpu_message_control_start( cpu_message_t *message )
{
	jaguar_sys_start( LEFT_MOTOR );
	jaguar_sys_start( RIGHT_MOTOR );

	return 0;
}

int cpu_message_control_closed_loop( cpu_message_t *message )
{
	jaguar_voltage_control_enable( 0, 0 );
	jaguar_control_mode_enable( SPEED_CONTROL, 0, 1 );

	jaguar_control_mode_reference( SPEED_CONTROL, 0, QUAD_ENCODER );

	jaguar_mode = CLOSED_LOOP;
	
	return 0;
}

int cpu_message_control_open_loop( cpu_message_t *message )
{
	jaguar_control_mode_enable( SPEED_CONTROL, 0, 0 );
	jaguar_voltage_control_enable( 0, 1 );

	jaguar_mode = OPEN_LOOP;

	return 0;
}

// CLOSED LOOP
void setPID( int dev_id )
{
	jaguar_control_mode_setPID( SPEED_CONTROL, dev_id, jaguar_P, jaguar_I, jaguar_D );
}

int cpu_message_closed_loop_set_P( cpu_message_t *message )
{
	if( jaguar_mode != CLOSED_LOOP ) return -1;

	message_conv_t conv;
	conv.i8 = message->data;

	jaguar_P = conv.i16[0];

	setPID( LEFT_MOTOR );
	setPID( RIGHT_MOTOR );

	return 0;
}

int cpu_message_closed_loop_set_I( cpu_message_t *message )
{
	if( jaguar_mode != CLOSED_LOOP ) return -1;

	message_conv_t conv;
	conv.i8 = message->data;

	jaguar_I = conv.i16[0];

	setPID( LEFT_MOTOR );
	setPID( RIGHT_MOTOR );

	return 0;
}

int cpu_message_closed_loop_set_D( cpu_message_t *message )
{
	if( jaguar_mode != CLOSED_LOOP ) return -1;

	message_conv_t conv;
	conv.i8 = message->data;

	jaguar_D = conv.i16[0];

	setPID( LEFT_MOTOR );
	setPID( RIGHT_MOTOR );

	return 0;
}

int cpu_message_closed_loop_set_speed( cpu_message_t *message )
{
	uint32_t r_speed, l_speed;

	if( jaguar_mode != CLOSED_LOOP ) return -1;

	GPIO_PORTF_DATA_R |= LED_RED;
	
	message_conv_t conv;
	conv.i8 = message->data;

	r_speed = conv.i32[0];
	l_speed = conv.i32[1];

	jaguar_control_mode_set( SPEED_CONTROL, RIGHT_MOTOR, r_speed);
	jaguar_control_mode_set( SPEED_CONTROL, LEFT_MOTOR, l_speed);

	return 0;
}

// OPEN LOOP
int cpu_message_open_loop_set_voltage( cpu_message_t *message )
{
	uint16_t r_speed, l_speed;

	if( jaguar_mode != OPEN_LOOP ) return -1;

	message_conv_t conv;
	conv.i8 = message->data;

	r_speed = conv.i16[0];
	l_speed = conv.i16[1];

	jaguar_voltage_control_set( RIGHT_MOTOR, r_speed);
	jaguar_voltage_control_set( LEFT_MOTOR, l_speed);

	return 0;
}

// MONITOR
int cpu_message_monitor_get_voltage( cpu_message_t *message )
{
	return 0;
}

int cpu_message_monitor_get_current( cpu_message_t *message )
{
	return 0;
}

int cpu_message_monitor_get_temp( cpu_message_t *message )
{
	return 0;
}

int cpu_message_monitor_get_position( cpu_message_t *message )
{
	return 0;
}

// invalid
int invalid_message( cpu_message_t *message )
{
	return -1;
}

