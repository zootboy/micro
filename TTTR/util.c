#include "util.h"

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
