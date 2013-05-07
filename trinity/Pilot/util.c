/* Pilot - util.c */
#include "util.h"
#include <avr/io.h>
#include <util/twi.h>

/// Globals ///
uint16_t servoPos1 = 95; // Array head. 95=straight forward, 230=straight backward
uint16_t servoPos2 = 110; // CO2 actuator. 110=closed, 215=open
uint8_t globalError = 0; // Error condition if non-zero. 1=invalid servo pos, 2=unknown i2c command, 3=TX data error
uint8_t i2cMode = 0; // State of i2c receiver/transmitter.
uint8_t gStatus = 0;
uint8_t i2cTxMode = 0; // Mode to use when i2c ST mode called.

uint8_t bytesCount = 0;


void delay_us(uint16_t delah)
{
	while(delah)
	{
		_delay_us(1);
		delah--;
	}
}

void delay_ms(uint16_t delah)
{
	while(delah)
	{
		_delay_ms(1);
		delah--;
	}
}

// Sets position of either servo, from 0 to 255.
void setServo(uint8_t servo, uint8_t position) // 1 = tilt head, 2 = CO2 actuator.
{
	//float temp = (float)position;
	//temp *= 0.79431372549;
	//temp += 80.0;
	if(servo == 1)
	{
		//servoPos1 = (int)temp;
		servoPos1 = position;
	}
	else if(servo == 2)
	{
		//servoPos2 = (int)temp;
		servoPos2 = position;
	}
}

void co2Burst(void)
{
	servoPos2 = 215;
	delay_ms(1000);
	servoPos2 = 110;
}

void rxDataHandler(uint8_t data)
{
	if(i2cMode == 0)
	{
		i2cMode = data;
	}
	else
	{
		switch (i2cMode)
		{
			case 1: // System global mode.
				gStatus = data;
				bytesCount = 0;
				i2cMode = 0;
				break;
			case 9: // Slave TX mode set.
				i2cTxMode = data;
				//servoPos1 = 120;
				bytesCount = 0;
				i2cMode = 0;
				break;
			case 21: // Set servo 1.
				setServo(1,data);
				i2cMode = 0; // And we're done with that.
				bytesCount = 0;
				break;
			case 22: // Set servo 2.
				setServo(2,data);
				i2cMode = 0; // And we're done with that.
				bytesCount = 0;
				break;
			case 29: // CO2 burst.
				//while(data)
				//{
					co2Burst();
				//	data--;
				//}
				i2cMode = 0;
				bytesCount = 0;
				break;
			default: // Unknown command
				i2cMode = 0;
				globalError = 2;
				break;
		}
	}
}

uint32_t holder = 0;

void txDataHandler(void) // Generates the data to be transmitted over i2c.
{
	switch (i2cTxMode)
	{
		case 42: // IR array data
			switch (bytesCount)
			{
				case 0:
					holder = (arcIR1[0] + arcIR1[1] + arcIR1[2] + arcIR1[3]);
					holder /= 4;
					TWDR = (uint8_t)(holder >> 8);
					TWCR |= (1<<TWEA);
					break;
				case 1:
					TWDR = (uint8_t)holder;
					TWCR |= (1<<TWEA);
					break;
				case 2:
					holder = (arcIR2[0] + arcIR2[1] + arcIR2[2] + arcIR2[3]);
					holder /= 4;
					TWDR = (uint8_t)(holder >> 8);
					TWCR |= (1<<TWEA);
					break;
				case 3:
					TWDR = (uint8_t)holder;
					TWCR |= (1<<TWEA);
					break;
				case 4:
					holder = (arcIR3[0] + arcIR3[1] + arcIR3[2] + arcIR3[3]);
					holder /= 4;
					TWDR = (uint8_t)(holder >> 8);
					TWCR |= (1<<TWEA);
					break;
				case 5:
					TWDR = (uint8_t)holder;
					TWCR &= ~(1<<TWEA); // Last byte, expect NACK.
					i2cTxMode = 0; // And we're done.
					break;
			}
			bytesCount++;
			break;
		case 90: // Battery voltage report.
			holder = (battMon[0] + battMon[1] + battMon[2] + battMon[3]);
			holder /= 4;
			if(!bytesCount) 
			{
				TWDR = (uint8_t)(holder >> 8);
				bytesCount++;
				TWCR |= (1<<TWEA);
			}
			else 
			{
				TWDR = (uint8_t)holder;
				bytesCount++;
				TWCR &= ~(1<<TWEA); // Last byte, expect NACK.
				i2cTxMode = 0;
			}
			break;
		case 99: // Send error condition, if any.
			break;
		default:
			globalError = 3;
			break;
	}
}