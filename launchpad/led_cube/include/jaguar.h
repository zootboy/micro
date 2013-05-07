/*
 * File:	jaguar.h
 * Author:	James Letendre
 *
 * Interface for UART -> Jaguar Motor Controller
 */
#ifndef _JAGUAR_H_
#define _JAGUAR_H_

#include <stdint.h>
#include "inc/lm4f120h5qr.h"

#define JAG_UART UART1_BASE

#define LEFT_MOTOR	(2)
#define RIGHT_MOTOR	(3)

typedef union
{
	uint8_t  *i8;
	uint16_t *i16;
	uint32_t *i32;
} message_conv_t;

/*
 * Device types
 */
typedef enum {
	BROADCAST_TYPE			= 0,
	ROBOT_CONTROLLER		= 1,
	MOTOR_CONTROLLER		= 2,
	RELAY_CONTROLLER		= 3,
	GYRO_SENSOR				= 4,
	ACCEL_SENSOR			= 5,
	ULTRASONIC_SENSOR		= 6,
	GEAR_TOOTH_SENSOR		= 7,
	FIRMWARE_UPDATE_TYPE	= 31
} device_type;

/*
 * Manufacturer types
 */
typedef enum {
	BROADCAST_MANUFACTURER	= 0,
	NI						= 1,
	TI						= 2,
	DEKA					= 3
} manufacturer_type;

/*
 * API class codes
 */
typedef enum {
	SYSTEM_CONTROL			= -1,
	VOLTAGE_CONTROL			= 0,
	SPEED_CONTROL			= 1,
	VOLTAGE_COMP_CONTROL	= 2,
	POSITION_CONTROL		= 3,
	CURRENT_CONTROL			= 4,
	STATUS					= 5,
	PERIODIC_STATUS			= 6,
	CONFIGURATION			= 7,
	ACK						= 8
} api_class_t;

/*
 * System control api commands
 */
typedef enum {
	SYSTEM_HALT			= 0,
	SYSTEM_RESET		= 1,
	DEVICE_ASSIGNMENT	= 2,
	DEVICE_QUERY		= 3,
	HEARTBEAT			= 5,
	SYNC_UPDATE			= 6,
	FIRMWARE_UPDATE		= 7,
	FIRMWARE_VERSION	= 8,
	ENUMERATION			= 9,
	SYSTEM_RESUME		= 10
} sys_control_api;

/*
 * Voltage control api commands
 */
typedef enum {
	VOLTAGE_MODE_ENABLE		= 0,
	VOLTAGE_MODE_DISABLE	= 1,
	VOLTAGE_SET				= 2,
	VOLTAGE_RAMP_SET		= 3,
	VOLTAGE_SET_NO_ACK		= 8
} voltage_control_api;

/*
 * Voltage compensation control api commands
 */
typedef enum {
	VOLTAGE_COMP_MODE_ENABLE		= 0,
	VOLTAGE_COMP_MODE_DISABLE		= 1,
	VOLTAGE_COMP_VOLT_SET			= 2,
	VOLTAGE_COMP_RAMP_SET			= 3,
	VOLTAGE_COMP_SET				= 4,
	VOLTAGE_COMP_VOLT_SET_NO_ACK	= 9
} voltage_comp_control_api;

/*
 * Closed loop control api commands
 */
typedef enum {
	MODE_ENABLE		= 0,
	MODE_DISABLE	= 1,
	SET				= 2,
	SET_P			= 3,
	SET_I			= 4,
	SET_D			= 5,
	REFERENCE		= 6,
	SET_NO_ACK		= 11
} control_mode_api;

/*
 * Closed Loop references
 */
typedef enum {
	ENCODER_POS		= 0,
	POTENTIOMETER	= 1,
	ENCODER_NEG		= 2,
	QUAD_ENCODER	= 3
} control_mode_ref_t;

/*
 * Status api commands
 */
typedef enum {
	OUTPUT_VOLTAGE_PERCENT	= 0,
	BUS_VOLTAGE				= 1,
	CURRENT					= 2,
	TEMPERATURE				= 3,
	POSITION				= 4,
	SPEED					= 5,
	LIMIT					= 6,
	FAULT					= 7,
	POWER					= 8,
	CONTROL_MODE			= 9,
	OUTPUT_VOLTAGE			= 10,
	STICKY_FAULT			= 11,
	FAULT_COUNT				= 12
} status_api;

/*
 * Motor controller config api commands
 */
typedef enum {
	NUM_BRUSHES				= 0,
	ENCODER_PPR				= 1,
	NUM_POT_TURNS			= 2,
	BREAK_COAST				= 3,
	LIMIT_MODE				= 4,
	FORWARD_DIRECTION_LIMIT	= 5,
	REVERSE_DIRECTION_LIMIT	= 6,
	MAX_OUTPUT_VOLTAGE		= 7,
	FAULT_TIME				= 8
} motor_control_config_api;

/*
 * Periodic status api commands
 */
typedef enum {
	ENABLE_MESSAGE_0		= 0,
	ENABLE_MESSAGE_1		= 1,
	ENABLE_MESSAGE_2		= 2,
	ENABLE_MESSAGE_3		= 3,
	CONFIGURE_MESSAGE_0		= 4,
	CONFIGURE_MESSAGE_1		= 5,
	CONFIGURE_MESSAGE_2		= 6,
	CONFIGURE_MESSAGE_3		= 7,
	PERIODIC_STATUS_0		= 8,
	PERIODIC_STATUS_1		= 9,
	PERIODIC_STATUS_2		= 10,
	PERIODIC_STATUS_3		= 11
} periodic_status_api;

typedef enum {
	END_OF_MESSAGE				= 0,
	OUTPUT_VOLTAGE_PERCENT_0	= 1,
	OUTPUT_VOLTAGE_PERCENT_1	= 2,
	BUS_VOLTAGE_0				= 3,
	BUS_VOLTAGE_1				= 4,
	MOTOR_CURRENT_0				= 5,
	MOTOR_CURRENT_1				= 6,
	TEMPERATURE_0				= 7,
	TEMPERATURE_1				= 8,
	POSITION_0					= 9,
	POSITION_1					= 10,
	POSITION_2					= 11,
	POSITION_3					= 12,
	SPEED_0						= 13,
	SPEED_1						= 14,
	SPEED_2						= 15,
	SPEED_3						= 16,
	LIMIT_NON_CLEARING			= 17,
	LIMIT_CLEARING				= 18,
	FAULTS						= 19,
	STICKY_FAULTS_NON_CLEARING	= 20,
	STICKY_FAULTS_CLEARING		= 21,
	OUTPUT_VOLTAGE_0			= 22,
	OUTPUT_VOLTAGE_1			= 23,
	CURRENT_FAULT_COUNTER		= 24,
	TEMPERATURE_FAULT_COUNTER	= 25,
	BUS_VOLTAGE_FAULT_COUNTER	= 26,
	GATE_FAULT_COUNTER			= 27,
	COMMUNICATION_FAULT_COUNTER = 28
} periodic_status_ids;
/*
 * Packet format
 */
typedef struct {
	uint32_t dev_id		: 6;
	uint32_t api_idx	: 4;
	uint32_t api_class	: 6;
	uint32_t manufact	: 8;
	uint32_t devType	: 5;
	uint32_t rsv		: 3;
} jaguar_header_t;

typedef char *jaguar_packet_data;

typedef struct {
	uint8_t			size;
	jaguar_header_t	header;
	uint8_t			data[8];
} jaguar_packet_t;


/*
 * Functions
 */
void init_jaguar(void);
//jaguar_packet_data jaguar_device_query( uint8_t dev_id );
//
void jaguar_device_assign( uint8_t dev_id );
void jaguar_sys_reset( uint8_t dev_id );
void jaguar_sys_stop( uint8_t dev_id );
void jaguar_sys_start( uint8_t dev_id );
void jaguar_get_firmware_version( uint8_t dev_id );

void jaguar_status( uint8_t dev_id, status_api id );

void jaguar_voltage_control_enable( uint8_t dev_id, int on );
void jaguar_voltage_control_set( uint8_t dev_id, int16_t voltage );

void jaguar_motor_config( uint8_t dev_id, motor_control_config_api config, uint32_t val );

void jaguar_control_mode_enable( api_class_t api, uint8_t dev_id, int on );
void jaguar_control_mode_setPID( api_class_t api, uint8_t dev_id, uint32_t p, uint32_t i, uint32_t d );
void jaguar_control_mode_set   ( api_class_t api, uint8_t dev_id, uint32_t val );
void jaguar_control_mode_reference( api_class_t api, uint8_t dev_id, control_mode_ref_t ref );

void jaguar_heartbeat( void );

void jaguar_periodic_status_config( uint8_t dev_id, uint8_t message_id, uint8_t size, ... );
void jaguar_periodic_status_enable( uint8_t dev_id, uint8_t message_id, uint16_t ms );

int jaguar_message_process( void );

#endif
