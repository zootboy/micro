#include "util.h"
#include "i2c.h"

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

// Move the steppers by X,Y ticks.
void stepperSendTicks(int16_t left, int16_t right)
{
	while(left && right)
	{
		if(left > 127)
		{
			stepperCountTempL = 127;
			while(i2cMode) delay_us(40);
			i2cStart(23);
			left -= 127;
		}
		else if(left < -127)
		{
			stepperCountTempL = (127 | 0x80);
			while(i2cMode) delay_us(40);
			i2cStart(23);
			left += 127;
		}
		else if(left < 0)
		{
			left *= -1;
			stepperCountTempL = (left | 0x80);
			while(i2cMode) delay_us(40);
			i2cStart(23);
			left = 0;
		}
		else
		{
			stepperCountTempL = (left | 0x80);
			while(i2cMode) delay_us(40);
			i2cStart(23);
			left = 0;
		}
		
		
		if(right > 127)
		{
			stepperCountTempR = 127;
			while(i2cMode) delay_us(40);
			i2cStart(24);
			right -= 127;
		}
		else if(right < -127)
		{
			stepperCountTempR = (127 | 0x80);
			while(i2cMode) delay_us(40);
			i2cStart(24);
			right += 127;
		}
		else if(right < 0)
		{
			right *= -1;
			stepperCountTempR = (right | 0x80);
			while(i2cMode) delay_us(40);
			i2cStart(24);
			right = 0;
		}
		else
		{
			stepperCountTempR = (right | 0x80);
			while(i2cMode) delay_us(40);
			i2cStart(24);
			right = 0;
		}
	}
}