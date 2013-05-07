#include "util.h"
#include <avr/io.h>
#include <util/twi.h>

/// Globals ///
uint8_t globalError = 0; // Error condition if non-zero. 1=invalid servo pos, 2=unknown i2c command
uint8_t i2cMode = 0; // State of i2c receiver/transmitter.
uint8_t gState = 0; // Global robot system mode.
uint32_t stepperCountLeft  = 0x00000FFF;
uint32_t stepperCountRight = 0x00000FFF;

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

void rxDataHandler(uint8_t data)
{
	if(i2cMode == 0)
	{
		i2cMode = data;
		//setServo(1,21);
	}
	else
	{
		switch (i2cMode)
		{
			case 1:
				gState = data;
				bytesCount = 0;
				i2cMode = 0;
				break;
			case 9: // Slave TX mode set.
				i2cTxMode = data;
				bytesCount = 0;
				i2cMode = 0;
				break;
			case 23: // Left wheel (mm) input. -127 thru 127, signed magnitude via MSB.
				// TODO: convert mm to steps.
				if(data & 0x80) stepperCountLeft -= (data & 0x7F); // MSB = 1 = Negative.
				else stepperCountLeft += data;// Positive.
				i2cMode = 0;
				break;
			case 24:// Right wheel (mm) input. -127 thru 127, signed magnitude via MSB.
				// TODO: convert mm to steps.
				if(data & 0x80) stepperCountRight -= (data & 0x7F); // MSB = 1 = Negative.
				else stepperCountRight += data;// Positive.
				i2cMode = 0;
				break;
			case 25:
				if(data & 0x80) 
				{
					stepperCountLeft  -= (TICKS_PER_CM * (data & 0x7F)); // MSB = 1 = Negative.
					stepperCountRight -= (TICKS_PER_CM * (data & 0x7F));
				}
				else
				{
					stepperCountLeft  += (TICKS_PER_CM * data); // Positive.
					stepperCountRight += (TICKS_PER_CM * data);
				}
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
		case 43: // IR array data
			switch (bytesCount)
			{
				case 0:
					holder = (arcIR4[0] + arcIR4[1] + arcIR4[2] + arcIR4[3]);
					holder /= 4;
					TWDR = (uint8_t)(holder >> 8);
					TWCR |= (1<<TWEA);
					break;
				case 1:
					TWDR = (uint8_t)holder;
					TWCR |= (1<<TWEA);
					break;
				case 2:
					holder = (arcIR5[0] + arcIR5[1] + arcIR5[2] + arcIR5[3]);
					holder /= 4;
					TWDR = (uint8_t)(holder >> 8);
					TWCR |= (1<<TWEA);
					break;
				case 3:
					TWDR = (uint8_t)holder;
					TWCR |= (1<<TWEA);
					break;
				case 4:
					holder = (arcIR6[0] + arcIR6[1] + arcIR6[2] + arcIR6[3]);
					holder /= 4;
					TWDR = (uint8_t)(holder >> 8);
					TWCR |= (1<<TWEA);
					break;
				case 5:
					TWDR = (uint8_t)holder;
					TWCR |= (1<<TWEA);
					break;
				case 6:
					holder = (arcIR7[0] + arcIR7[1] + arcIR7[2] + arcIR7[3]);
					holder /= 4;
					TWDR = (uint8_t)(holder >> 8);
					TWCR |= (1<<TWEA);
					break;
				case 7:
					TWDR = (uint8_t)holder;
					TWCR &= ~(1<<TWEA); // Last byte, expect NACK.
					i2cTxMode = 0; // And we're done.
					break;
			}
			bytesCount++;
			break;
		case 99: // Send error condition, if any.
			break;
		default:
			globalError = 3;
			break;
	}
}
