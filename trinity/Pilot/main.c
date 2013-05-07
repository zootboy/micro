/* Trinity Bot - Pilot */

#include <avr/io.h>
//#include <avr/iom328p.h>
#include <avr/interrupt.h>   
#include <util/twi.h>
#include <stdlib.h>
#include "util.h"
#include "analog.h"

/* --- Pins ---
 * PORT B:        | PORT C:       | PORT D: 
 * PBO - SERVO 1  | PC0 - ArcIR1  | PD0 - 
 * PB1 - SERVO 2  | PC1 - ArcIR2  | PD1 - 
 * PB2 -          | PC2 - ArcIR3  | PD2 - 
 * PB3 -          | PC3 - BatSens | PD3 - 
 * PB4 -          | PC4 - i2c     | PD4 - 
 * PB5 -          | PC5 - i2c     | PD5 - 
 * PB6 -          |               | PD6 - 
 * PB7 -          |               | PD7 - 
 * 
 */

// PWM timer defines.
// CTC mode, clear on ICR1.
#define PWM_TIMER_PRESCALE 64 // CS11 & CS10.
#define PWM_TIMER_TOP 6000 // ICR set to this.
#define PWM_REG1 (0<<WGM11)|(0<<WGM10) // TCCR1A
#define PWM_REG2 (1<<WGM13)|(1<<WGM12)|(1<<CS11)|(1<<CS10) // TCCR1B
#define PWM_REG3 (1<<OCIE1A)|(1<<OCIE1B) // TIMSK1
#define PWM_PORT PORTB
#define PWM_PIN1 PB0
#define PWM_PIN2 PB1

// i2c defines
#define I2C_ADDR 0b01000110 // last bit determines response to general call; 0=ignore.
#define I2C_REG1 (1<<TWEN)|(1<<TWEA)|(1<<TWIE) // TWCR
#define I2C_REG2 0x02 // TWBR - 400 KHz mode.
#define I2C_REG3 (1<<TWPS0) // TWSR - Prescale of 4x.

extern uint16_t battMon[4];


/// Interupt Service Routines ///
ISR(TIMER1_COMPA_vect)
{
	if(!OCR1A) // We're at zero.
	{
		PWM_PORT |= (1<<PWM_PIN1); // Set PWM to one.
		if(servoPos1) OCR1A = servoPos1;
		else globalError = 1;
	}
	else // We're at the point.
	{
		PWM_PORT &= ~(1<<PWM_PIN1); // Set PWM to zero.
		OCR1A = 0; // Trigger at rollover.
	}
}

ISR(TIMER1_COMPB_vect)
{
	if(!OCR1B) // We're at zero.
	{
		PWM_PORT |= (1<<PWM_PIN2); // Set PWM to one.
		if(servoPos2) OCR1B = servoPos2;
		else globalError = 1;
	}
	else // We're at the point.
	{
		PWM_PORT &= ~(1<<PWM_PIN2); // Set PWM to zero.
		OCR1B = 0; // Trigger at rollover.
	}
}

ISR(TWI_vect)
{
	//servoPos2 += 10;
	uint8_t status = TW_STATUS; // Get status register.
	
	/// RX ///
	if(status == TW_SR_SLA_ACK) // SLA+W received, ACK response sent.
	{
		TWCR |= (1<<TWEA); // Read and ACK the next byte.
	}
	else if(status == TW_SR_DATA_ACK) // Data from SLA+W received, ACK'd.
	{
		rxDataHandler(TWDR); // Handle the received data.
	}
	else if(status == TW_SR_STOP)
	{
		//servoPos2 = 180;
		TWCR |= (1<<TWEA); // ACK it.
		i2cMode = 0;
		// And we're done.
	}
	
	/// TX ///
	else if(status == TW_ST_SLA_ACK) // SLA+R received, ACK'd.
	{
		bytesCount = 0;
		txDataHandler(); // This auto-fills TWDR.
	}
	else if(status == TW_ST_DATA_ACK) // Data ACK'd.
	{
		txDataHandler();
	}
	else if(status == TW_ST_LAST_DATA || status == TW_ST_DATA_NACK) // Data NACK'd or last byte ACK'd.
	{
		i2cMode = 0;
		bytesCount = 0;
		TWCR |= (1<<TWEA);
	}
	
	TWCR |= (1<<TWINT)|(1<<TWIE); // Clear the interrupt flag (seriously), allowing the TWI to continue.
}

/// Functions ///
int main(void)
{
	// Initialize inputs and outputs.
	DDRB = 0b00000011; 
	
	// Servo timer initialization.
	ICR1 = PWM_TIMER_TOP;
	OCR1A = servoPos1;
	OCR1B = servoPos2;
	TCCR1A = PWM_REG1;
	TCCR1B = PWM_REG2;
	TIMSK1 = PWM_REG3;
	
	// i2c initialization.
	TWAR = I2C_ADDR; // Set slave address.
	TWBR = I2C_REG2; // Set bit-rate.
	TWSR = I2C_REG3; // Set prescale.
	TWCR = I2C_REG1; // Enable TWI.
	
	adcInit();
	
	PRR = 0x00;
	
	delay_ms(10);
	
	sei(); // Enable interrupts globally.
	
	delay_ms(100);
	
	/*setServo(1,200);
	delay_ms(1000);
	setServo(1,100);
	delay_ms(1000);
	*/
	
	while(1)
	{
		//servoPos1 = 60;
		//delay_ms(1000);
		//servoPos1 = 260;
		//delay_ms(1000);
		delay_ms(10);
		analogGather();
		
		//co2Burst();
		//delay_ms(2000);
	}
	
	return 0; // This shouldn't run, this just makes gcc happy.
}
