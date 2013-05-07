/* Trinity Bot - Co-Pilot */

#include <avr/io.h>
//#include <avr/iom328p.h>
#include <avr/interrupt.h>   
#include <util/twi.h>
#include <stdlib.h>
#include "util.h"
#include "analog.h"

/* --- Pins ---
 * PORT B:        | PORT C:       | PORT D: 
 * PBO - Step L1  | PC0 - ArcIR4  | PD0 - 
 * PB1 - Step L2  | PC1 - ArcIR5  | PD1 - 
 * PB2 - Step L3  | PC2 - ArcIR6  | PD2 - 
 * PB3 - Step L4  | PC3 - ArcIR7  | PD3 - 
 * PB4 - Step R1  | PC4 - [i2c]   | PD4 - 
 * PB5 - Step R2  | PC5 - [i2c]   | PD5 - 
 * PB6 - Step R3  |               | PD6 - 
 * PB7 - Step R4  |               | PD7 - 
 * 
 */

// i2c defines
#define I2C_ADDR 0b01001000 // last bit determines response to general call; 0=ignore.
#define I2C_REG1 (1<<TWEN)|(1<<TWEA)|(1<<TWIE) // TWCR
#define I2C_REG2 0x02 // TWBR - 400 KHz mode.
#define I2C_REG3 (1<<TWPS0) // TWSR - Prescale of 4x.

// Timer 1 - 1024x prescale, CTC on ICR1
#define TIM1_CRA 0x00 // TCCR1A
#define TIM1_CRB (1<<WGM13)|(1<<WGM12)|(1<<CS12)|(1<<CS10); // TCCR1B
//#define TIM1_TOP_DEF 0x003F // Default top - ICR1
#define TIM1_TOP_DEF 0x005D
#define TIM1_MSK (1<<ICIE1) // TIMSK1

// Globals.
uint8_t stepPatternL[4] = { 0b00000001, 0b00000010, 0b00000100, 0b00001000 };
uint8_t stepPatternR[4] = { 0b10000000, 0b01000000, 0b00100000, 0b00010000 };
#define STEP_INDEX_SIZE 4
uint8_t stepStateL = 0;
uint8_t stepStateR = 0;
uint32_t prevStepL = 0xFFF; // Holds the differential values for the stepper timer.
uint32_t prevStepR = 0xFFF; // These should only be modified by the ISR.

/// Interupt Service Routines ///
ISR(TWI_vect)
{
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
		TWCR |= (1<<TWEA); // ACK it.
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

ISR(TIMER1_CAPT_vect) // Stepper timer.
{
	// Left side.
	if(stepperCountLeft > prevStepL)
	{
		stepStateL++;
		if(stepStateL >= 4) stepStateL = 0;
		PORTB = ((PORTB & 0xF0) | stepPatternL[stepStateL]); // Preserve high nibble (right state), overwrite low nibble (left state).
		prevStepL++;
	}
	else if(stepperCountLeft < prevStepL)
	{
		if(!stepStateL) stepStateL = 3;
		else stepStateL--;
		PORTB = ((PORTB & 0xF0) | stepPatternL[stepStateL]);
		prevStepL--;
	}
	
	// Right side.
	if(stepperCountRight > prevStepR)
	{
		stepStateR++;
		if(stepStateR >= 4) stepStateR = 0;
		PORTB = ((PORTB & 0x0F) | stepPatternR[stepStateR]); 
		prevStepR++;
	}
	else if(stepperCountRight < prevStepR)
	{
		if(!stepStateR) stepStateR = 3;
		else stepStateR--;
		PORTB = ((PORTB & 0x0F) | stepPatternR[stepStateR]);
		prevStepR--;
	}
}

/// Functions ///
int main(void)
{
	// Initialize inputs and outputs.
	DDRB = 0xff; // All outputs.
	
	// i2c initialization.
	TWAR = I2C_ADDR; // Set slave address.
	TWBR = I2C_REG2; // Set bit-rate.
	TWSR = I2C_REG3; // Set prescale.
	TWCR = I2C_REG1; // Enable TWI.
	
	// Stepper timer initialization.
	TCCR1A = TIM1_CRA;
	TCCR1B = TIM1_CRB;
	ICR1 = TIM1_TOP_DEF; // Just a default...
	TIMSK1 = TIM1_MSK; // AND THAT TOO!
	
	adcInit();
	
	delay_ms(100);

	
	sei(); // Enable interrupts globally.
	
	uint16_t mem = 0;
	
	while(1)
	{
		//servoPos1 = 60;
		//delay_ms(1000);
		//servoPos1 = 260;
		//delay_ms(1000);
		//stepperCountLeft++;
		
		analogGather();
		/*if(mem != arcIR4[0])
		{
			mem = arcIR4[0];
			stepperCountLeft+=mem;
			delay_ms(10000);
		}*/
		delay_ms(20);
	}
	
	return 0; // This shouldn't run, this just makes gcc happy.
}
