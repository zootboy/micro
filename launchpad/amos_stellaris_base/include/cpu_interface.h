/*
 * File:	cpu_interface.h
 * Author:	James Letendre
 *
 * Interface from Stellaris to the CPU
 */
#ifndef CPU_INTERFACE_H
#define CPU_INTERFACE_H

#include <stdint.h>

/*
 * Periodic message ids
 */
enum {
	VOLTAGE_MESSAGE		= 0,
	CURRENT_MESSAGE		= 1,
	TEMP_MESSAGE		= 2,
	POSITION_MESSAGE	= 3
} periodic_message_id;

/*
 * Message classes
 */
typedef enum {
	CPU_MSG_CONTROL		= 0,
	CPU_MSG_CLOSED_LOOP	= 1,
	CPU_MSG_OPEN_LOOP	= 2,
	CPU_MSG_MONITOR		= 3
} cpu_msg_class;

/*
 * Message indices for control class
 */
typedef enum {
	CPU_CONTROL_HEARTBEAT	= 0,
	CPU_CONTROL_RESET		= 1,
	CPU_CONTROL_STOP		= 2,
	CPU_CONTROL_START		= 3,
	CPU_CONTROL_CLOSED_LOOP	= 4,
	CPU_CONTROL_OPEN_LOOP	= 5
} cpu_control_idx;

/*
 * Message indices for closed loop control
 */
typedef enum {
	CPU_CLOSED_LOOP_SET_P		= 0,
	CPU_CLOSED_LOOP_SET_I		= 1,
	CPU_CLOSED_LOOP_SET_D		= 2,
	CPU_CLOSED_LOOP_SET_SPEED	= 3
} cpu_closed_loop_idx;

/*
 * Message indices for open loop control
 */
typedef enum {
	CPU_OPEN_LOOP_SET_VOLT	= 0
} cpu_open_loop_idx;

/*
 * Message indices for monitor class
 */
typedef enum {
	CPU_MONITOR_VOLTAGE		= 0,
	CPU_MONITOR_CURRENT		= 1,
	CPU_MONITOR_TEMP		= 2,
	CPU_MONITOR_POSITION	= 3
} cpu_monitor_idx;

/*
 * Message packet format
 */
typedef union {
	uint8_t all;
	struct {
		uint8_t size	: 3;
		uint8_t index	: 3;
		uint8_t class	: 2;
	};
} cpu_message_info_t;

typedef struct {
	cpu_message_info_t message_info;
	uint8_t data[8];
} cpu_message_t;

/* 
 * initialize system
 */
void cpu_message_init( void );

/* 
 * send a cpu message 
 */
void cpu_message_send( cpu_message_t *message );

/*
 * create a message
 */
int cpu_message_create( cpu_message_t *message, cpu_msg_class msg_class, 
		uint8_t msg_idx, uint8_t size, uint8_t data[] );

/* 
 * process a cpu message 
 *
 * returns: 1 if no message processed
 */
int cpu_message_process( void );

/*
 * Periodic messages
 */
void cpu_message_periodic( void );

#endif
