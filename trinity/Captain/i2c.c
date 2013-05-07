/* Captain - i2c.c */

#include <avr/io.h>
//#include <avr/iom328p.h>
#include <avr/interrupt.h>
#include <util/twi.h>
#include "i2c.h"
#include "util.h"
#include "lcd.h"

extern char buffer[7];

uint8_t i2cMode = 0; // Var to let the data functions know what to do.
					/* Master I2C command code list:
					 * ---------------------
					 * 0  = Idle
					 * 1  = System mode announce 
					 * 9  = Slave next TX mode
					 * 21 = Set servo 1 (pilot)
					 * 22 = Set servo 2 (pilot)
					 * 23 = Wheel command Left (mm) (copilot)
					** 53 = Wheel command Left high-byte (LShift-8)
					 * 24 = Wheel command Right (mm) (copilot)
					** 54 = Wheel command Right high-byte (LShift-8)
					 * 25 = Linear movement command (cm, direction) (copilit)
					 * 26 = Rotational movement command (degrees, direction) (copilot)
					 * 27 = Set stepper speed (copilot)
	DO NOT USE! ->	 * 29 = Activate CO2 burst (data byte = no. of bursts) (pilot)
					 * 30 = Request map confidence (navigator)
					 * 31 = Request destination direction (navigator)
					 * 40 = Request IR ranger data  (navigator)
					 * 41 = Request IR proximity sensor data (navigator)
					 * 42 = Request IR arch data 1-3 (pilot) (6 byets)
					 * 43 = Request IR arch data 4-7 (copilot) (8 bytes)
					 * 44 = Request UVTron data [optional]
					 * 90 = Battery voltage request (2 bytes)
					 * 95 = TEST DATA ONLY
					 * 97 = Error request Navigator
					 * 98 = Error request Copilot
					 * 99 = Error request Pilot
					 */
uint8_t i2cByteIndex = 0; // Which byte are we on!? WHAT YEAR IS IT!!?? OH GOD HOW DID THIS GET HERE I AM NOT GOOD WITH COMPUTER--
uint8_t dataSent = 0;
uint8_t rxMode = 0; // Which mode to use when RX'ing.

ISR(TWI_vect)
{
	uint8_t status = TW_STATUS; // Get status register.
	switch (i2cMode)
	{
		case 1: // System mode announce.
			if(status == TW_START) // Start sent.
			{
				if(i2cByteIndex == 0) // Send to nav.
				{
					TWDR = (I2C_ADDR_NAVIGATOR & ~0x01); // Write = 0.
				}
				else if(i2cByteIndex == 1) // Send to pilot.
				{
					TWDR = (I2C_ADDR_PILOT & ~0x01);
				}
				else if(i2cByteIndex == 2) // Send to copilot.
				{
					TWDR = (I2C_ADDR_COPILOT & ~0x01);
				}
				else
				{
					errorCode = 1; // We've set an invalid byte index. Bad!
				}
				TWCR |= (1<<TWINT); // Start address transmission.
			}
			else if((status == TW_MT_SLA_NACK) || (status == TW_MT_DATA_NACK)) // If we don't get an ACK, that uC is most likely down.
			{
				errorCode = 2 + i2cByteIndex; // Error! Oh god!
				TWCR |= (1<<TWINT)|(1<<TWSTO); // Send stop command.
			}
			else if(status == TW_MT_SLA_ACK) // The slave is ready to recieve.
			{ // First data byte is command.
				TWDR = 0x01; // System mode announce.
				TWCR |= (1<<TWINT); // Go go go!
			}
			else if(status == TW_MT_DATA_ACK) // Command ack'd, send system mode.
			{
				if(dataSent == 0)
				{
					TWDR = gState; // Global state
					dataSent = 1;
					TWCR |= (1<<TWINT); // Go go go!
				}
				else
				{
					TWCR |= (1<<TWINT)|(1<<TWSTO); // Send stop command.
					dataSent = 0;
					i2cMode = 0; // Back to idle.
				}
			}
			break;
		case 9: // RX from slave. Runs a TX first...
			if(status == TW_START) // Start sent.
			{
				switch (rxMode) 
				{
					case 90: // Battery
					case 42: // IR 1-3
						TWDR = (I2C_ADDR_PILOT & ~0x01); // Write to slave Pilot.
						break;
					case 43: // IR 4-7
						TWDR = (I2C_ADDR_COPILOT & ~0x01); // Write to slave Co-Pilot.
						break;
					case 95: // testData
						TWDR = (I2C_ADDR_NAVIGATOR & ~0x01); // Write to slave Navigator.
						break;
					default:
						errorCode = 12;
						TWDR = 0x00;
						i2cMode = 0;
				}
				TWCR |= (1<<TWINT); // Start transmission.
				//errorCode = 6;
			}
			else if((status == TW_MT_SLA_NACK) || (status == TW_MT_DATA_NACK)) // If we don't get an ACK, that uC is most likely down.
			{
				errorCode = 5; // Error! Oh god!
				TWCR &= ~(1<<TWSTA); // Clear start bit.
				TWCR |= (1<<TWINT)|(1<<TWSTO); // Send stop command.
			}
			else if(status == TW_MT_SLA_ACK) // The slave is ready to recieve.
			{ // Data byte is TX command.
				TWDR = 9;
				dataSent = 0;
				TWCR &= ~(1<<TWSTA); // Clear start bit.
				TWCR |= (1<<TWINT); // Go go go!
			}
			else if(status == TW_MT_DATA_ACK)
			{
				if(!dataSent)
				{
					TWDR = rxMode;
					dataSent = 1;
					TWCR |= (1<<TWINT);
				}
				else
				{
					//errorCode = 10;
					TWCR |= (1<<TWINT)|(1<<TWSTO); // Send stop command.
					dataSent = 0;
					delay_us(40);
					i2cMode = rxMode; // Go straight on to RX'ing the data.
					TWCR |= (1<<TWSTA)|(1<<TWINT); // Send start signal.
				}
			}
			else errorCode = status;
			break;
		case 21: // Servo 1.
		case 22: // Servo 2.
			if(status == TW_START) // Start sent.
			{
				TWDR = (I2C_ADDR_PILOT & ~0x01); // Write to slave Pilot.
				//TWDR = 0x00;
				TWCR |= (1<<TWINT); // Start transmission.
				//errorCode = 6;
			}
			else if((status == TW_MT_SLA_NACK) || (status == TW_MT_DATA_NACK)) // If we don't get an ACK, that uC is most likely down.
			{
				errorCode = 5; // Error! Oh god!
				TWCR &= ~(1<<TWSTA); // Clear start bit.
				TWCR |= (1<<TWINT)|(1<<TWSTO); // Send stop command.
			}
			else if(status == TW_MT_SLA_ACK) // The slave is ready to recieve.
			{ // First data byte is command.
				TWDR = i2cMode; // Servo position command.
				//TWDR = 0xff;
				TWCR &= ~(1<<TWSTA); // Clear start bit.
				//if(TWCR & (1<<TWINT)) errorCode = 30;
				//errorCode = TWCR;
				TWCR |= (1<<TWINT); // Go go go!
			}
			else if(status == TW_MT_DATA_ACK)
			{
				if(dataSent == 0)
				{
					if(i2cMode == 21) TWDR = servoPos1;
					else TWDR = servoPos2;
					dataSent = 1;
					TWCR |= (1<<TWINT); // Go go go!
				}
				else
				{
					//errorCode = 10;
					TWCR |= (1<<TWINT)|(1<<TWSTO); // Send stop command.
					dataSent = 0;
					//lcd_clrscr(); itoa(errorCode, buffer, 10); lcd_puts(buffer);
					//delay_ms(500);
					//errorCode = 0;
					i2cMode = 0; // Back to idle.
				}
			}
			else errorCode = status;
			
			break;
		case 23: // Stepper left (mm).
		case 24: // Stepper right (mm).
		case 53:
		case 54:
			if(status == TW_START) // Start sent.
			{
				TWDR = (I2C_ADDR_COPILOT & ~0x01); // Write to slave Co-Pilot.
				//TWDR = 0x00;
				TWCR |= (1<<TWINT); // Start transmission.
				//errorCode = 6;
			}
			else if((status == TW_MT_SLA_NACK) || (status == TW_MT_DATA_NACK)) // If we don't get an ACK, that uC is most likely down.
			{
				errorCode = 6; // Error! Oh god!
				TWCR &= ~(1<<TWSTA); // Clear start bit.
				TWCR |= (1<<TWINT)|(1<<TWSTO); // Send stop command.
			}
			else if(status == TW_MT_SLA_ACK) // The slave is ready to recieve.
			{ // First data byte is command.
				//errorCode = 7;
				TWDR = i2cMode; // Servo position command.
				//TWDR = 0xff;
				TWCR &= ~(1<<TWSTA); // Clear start bit.
				//if(TWCR & (1<<TWINT)) errorCode = 30;
				//errorCode = TWCR;
				TWCR |= (1<<TWINT); // Go go go!
			}
			else if(status == TW_MT_DATA_ACK)
			{
				if(dataSent == 0)
				{
					if(i2cMode == 23) TWDR = stepperCountTempL;
					else if(i2cMode == 24) TWDR = stepperCountTempR;
					dataSent = 1;
					TWCR |= (1<<TWINT); // Go go go!
				}
				else
				{
					//errorCode = 10;
					TWCR |= (1<<TWINT)|(1<<TWSTO); // Send stop command.
					dataSent = 0;
					//lcd_clrscr(); itoa(errorCode, buffer, 10); lcd_puts(buffer);
					//delay_ms(500);
					//errorCode = 0;
					if(i2cMode == 23) stepperCountTempL = 0;
					else stepperCountTempR = 0;
					i2cMode = 0; // Back to idle.
				}
			}
			else errorCode = status;
			break;
		case 25: // Linear movement, in cm.
			if(status == TW_START) // Start sent.
			{
				TWDR = (I2C_ADDR_COPILOT & ~0x01); // Write to slave Co-Pilot.
				//TWDR = 0x00;
				TWCR |= (1<<TWINT); // Start transmission.
				//errorCode = 6;
			}
			else if((status == TW_MT_SLA_NACK) || (status == TW_MT_DATA_NACK)) // If we don't get an ACK, that uC is most likely down.
			{
				errorCode = 6; // Error! Oh god!
				TWCR &= ~(1<<TWSTA); // Clear start bit.
				TWCR |= (1<<TWINT)|(1<<TWSTO); // Send stop command.
			}
			else if(status == TW_MT_SLA_ACK) // The slave is ready to recieve.
			{ // First data byte is command.
				//errorCode = 7;
				TWDR = i2cMode; // Servo position command.
				//TWDR = 0xff;
				TWCR &= ~(1<<TWSTA); // Clear start bit.
				//if(TWCR & (1<<TWINT)) errorCode = 30;
				//errorCode = TWCR;
				TWCR |= (1<<TWINT); // Go go go!
			}
			else if(status == TW_MT_DATA_ACK)
			{
				if(dataSent == 0)
				{
					TWDR = linearMotion;
					dataSent = 1;
					TWCR |= (1<<TWINT); // Go go go!
				}
				else
				{
					//errorCode = 10;
					TWCR |= (1<<TWINT)|(1<<TWSTO); // Send stop command.
					dataSent = 0;
					linearMotion = 0;
					i2cMode = 0; // Back to idle.
				}
			}
			else errorCode = status;
			break;
		case 29: // CO2 burst!
			if(status == TW_START) // Start sent.
			{
				TWDR = (I2C_ADDR_PILOT & ~0x01); // Write to slave Pilot.
				//TWDR = 0x00;
				TWCR |= (1<<TWINT); // Start transmission.
				//errorCode = 6;
			}
			else if((status == TW_MT_SLA_NACK) || (status == TW_MT_DATA_NACK)) // If we don't get an ACK, that uC is most likely down.
			{
				errorCode = 5; // Error! Oh god!
				TWCR &= ~(1<<TWSTA); // Clear start bit.
				TWCR |= (1<<TWINT)|(1<<TWSTO); // Send stop command.
			}
			else if(status == TW_MT_SLA_ACK) // The slave is ready to recieve.
			{ // First data byte is command.
				TWDR = i2cMode; // Servo position command.
				TWCR &= ~(1<<TWSTA); // Clear start bit.
				TWCR |= (1<<TWINT); // Go go go!
			}
			else if(status == TW_MT_DATA_ACK)
			{
				if(dataSent == 0)
				{
					TWDR = BURST_COUNT;
					dataSent = 1;
					TWCR |= (1<<TWINT); // Go go go!
				}
				else
				{
					TWCR |= (1<<TWINT)|(1<<TWSTO); // Send stop command.
					dataSent = 0;
					i2cMode = 0; // Back to idle.
				}
			}
			else errorCode = status;
			
			break;
		case 42: // Get arch IR 1-3.
			if(status == TW_START) // Start sent.
			{
				TWDR = (I2C_ADDR_PILOT | 0x01); // Read from slave Pilot.
				TWCR |= (1<<TWINT); // Start RX, ACK bytes.
				i2cByteIndex = 0; // We'll use this to keep track of the 6 bytes coming in.
			}
			else if(status == TW_MR_SLA_ACK) // Slave ack'd.
			{
				TWCR &= ~(1<<TWSTA); // Clear start bit.
				TWCR |= (1<<TWINT)|(1<<TWEA); // Receive and ACK the next byte.
			}
			else if(status == TW_MR_SLA_NACK) // ERROR.
			{
				errorCode = 8; // Error! Oh god!
				TWCR &= ~(1<<TWSTA); // Clear start bit.
				TWCR |= (1<<TWINT)|(1<<TWSTO); // Send stop command.
			}
			else if(status == TW_MR_DATA_ACK)
			{
				switch (i2cByteIndex)
				{
					case 0:
						arcIR1 = TWDR;
						arcIR1 <<= 8;
						TWCR |= (1<<TWINT)|(1<<TWEA); // Receive and ACK the next byte.
						break;
					case 1:
						arcIR1 |= TWDR;
						TWCR |= (1<<TWINT)|(1<<TWEA); 
						break;
					case 2:
						arcIR2 = TWDR;
						arcIR2 <<= 8;
						TWCR |= (1<<TWINT)|(1<<TWEA); 
						break;
					case 3:
						arcIR2 |= TWDR;
						TWCR |= (1<<TWINT)|(1<<TWEA); 
						break;
					case 4:
						arcIR3 = TWDR;
						arcIR3 <<= 8;
						TWCR &= ~(1<<TWEA); // Don't ACK!
						break;
				}
				i2cByteIndex++;
				TWCR |= (1<<TWINT); // Go on...
			}
			else if(status == TW_MR_DATA_NACK)
			{
				if(i2cByteIndex == 5)
					arcIR3 |= TWDR;
				else errorCode = 9;
				TWCR |= (1<<TWINT)|(1<<TWSTO); // Send stop command.
				i2cMode = 0;
				rxMode = 0;
				i2cByteIndex = 0;
			}
			break;
		case 43: // Get arch IR 4-7.
			if(status == TW_START) // Start sent.
			{
				TWDR = (I2C_ADDR_COPILOT | 0x01); // Read from slave Pilot.
				TWCR |= (1<<TWINT); // Start RX, ACK bytes.
				i2cByteIndex = 0; // We'll use this to keep track of the 6 bytes coming in.
			}
			else if(status == TW_MR_SLA_ACK) // Slave ack'd.
			{
				TWCR &= ~(1<<TWSTA); // Clear start bit.
				TWCR |= (1<<TWINT)|(1<<TWEA); // Receive and ACK the next byte.
			}
			else if(status == TW_MR_SLA_NACK) // ERROR.
			{
				errorCode = 10; // Error! Oh god!
				TWCR &= ~(1<<TWSTA); // Clear start bit.
				TWCR |= (1<<TWINT)|(1<<TWSTO); // Send stop command.
			}
			else if(status == TW_MR_DATA_ACK)
			{
				switch (i2cByteIndex)
				{
					case 0:
						arcIR4 = TWDR;
						arcIR4 <<= 8;
						TWCR |= (1<<TWINT)|(1<<TWEA); // Receive and ACK the next byte.
						break;
					case 1:
						arcIR4 |= TWDR;
						TWCR |= (1<<TWINT)|(1<<TWEA); 
						break;
					case 2:
						arcIR5 = TWDR;
						arcIR5 <<= 8;
						TWCR |= (1<<TWINT)|(1<<TWEA); 
						break;
					case 3:
						arcIR5 |= TWDR;
						TWCR |= (1<<TWINT)|(1<<TWEA); 
						break;
					case 4:
						arcIR6 = TWDR;
						arcIR6 <<= 8;
						TWCR |= (1<<TWINT)|(1<<TWEA); 
						break;
					case 5:
						arcIR6 |= TWDR;
						TWCR |= (1<<TWINT)|(1<<TWEA); 
						break;
					case 6:
						arcIR7 = TWDR;
						arcIR7 <<= 8;
						TWCR &= ~(1<<TWEA); // Don't ACK!
						break;
				}
				i2cByteIndex++;
				TWCR |= (1<<TWINT); // Go on...
			}
			else if(status == TW_MR_DATA_NACK)
			{
				if(i2cByteIndex == 7)
					arcIR7 |= TWDR;
				else errorCode = 11;
				TWCR |= (1<<TWINT)|(1<<TWSTO); // Send stop command.
				i2cMode = 0;
				rxMode = 0;
				i2cByteIndex = 0;
			}
			break;
		case 90: // Get battery voltage (2 bytes).
			if(status == TW_START) // Start sent.
			{
				TWDR = (I2C_ADDR_PILOT | 0x01); // Read from slave Pilot.
				TWCR |= (1<<TWINT); // Start RX, ACK bytes.
			}
			else if(status == TW_MR_SLA_ACK) // Slave ack'd.
			{
				TWCR &= ~(1<<TWSTA); // Clear start bit.
				TWCR |= (1<<TWINT)|(1<<TWEA); // Receive and ACK the next byte.
			}
			else if(status == TW_MR_SLA_NACK) // ERROR.
			{
				errorCode = 7; // Error! Oh god!
				TWCR &= ~(1<<TWSTA); // Clear start bit.
				TWCR |= (1<<TWINT)|(1<<TWSTO); // Send stop command.
				i2cMode = 0;
			}
			else if(status == TW_MR_DATA_ACK)
			{
				batteryADC = TWDR;
				batteryADC <<= 8;
				TWCR &= ~(1<<TWEA); // Don't ACK!
				TWCR |= (1<<TWINT); // Receive and NACK the next byte.
			}
			else if(status == TW_MR_DATA_NACK)
			{
				batteryADC |= TWDR;
				TWCR |= (1<<TWINT)|(1<<TWSTO); // Send stop command.
				i2cMode = 0;
				rxMode = 0;
			}
			break;
		case 95: // RX text data.
			if(status == TW_START) // Start sent.
			{
				TWDR = (I2C_ADDR_NAVIGATOR | 0x01); // Read from slave Navigator.
				TWCR |= (1<<TWINT); // Start RX, ACK bytes.
			}
			else if(status == TW_MR_SLA_ACK) // Slave ack'd.
			{
				TWCR &= ~(1<<TWSTA); // Clear start bit.
				TWCR |= (1<<TWINT)|(1<<TWEA); // Receive and ACK the next byte.
			}
			else if(status == TW_MR_SLA_NACK) // ERROR.
			{
				errorCode = 7; // Error! Oh god!
				TWCR &= ~(1<<TWSTA); // Clear start bit.
				TWCR |= (1<<TWINT)|(1<<TWSTO); // Send stop command.
				i2cMode = 0;
			}
			else if(status == TW_MR_DATA_ACK)
			{
				tempData = TWDR;
				tempData <<= 8;
				TWCR &= ~(1<<TWEA); // Don't ACK!
				TWCR |= (1<<TWINT); // Receive and NACK the next byte.
			}
			else if(status == TW_MR_DATA_NACK)
			{
				tempData |= TWDR;
				TWCR |= (1<<TWINT)|(1<<TWSTO); // Send stop command.
				i2cMode = 0;
				rxMode = 0;
			}
			break;
		case 0: // Idle.
		default: 
			errorCode = 1; // I2C fault.
			break;
	}
}

void i2cInit(void)
{
	// Set control registers.
	TWBR = I2C_TWBR;
	TWSR = I2C_TWSR;
	TWCR = I2C_TWCR;

	sei(); // Enable interrupts.
}

void i2cStart(uint8_t type) // Send an i2c start command.
{
	while(i2cMode) delay_ms(1); // Wait until previous i2c transmission finishes.
	i2cMode = type; // And set transmission type. The interrupt will handle things from here.
	TWCR |= (1<<TWSTA)|(1<<TWINT); // Send start signal.	
}