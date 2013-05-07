/* Blinker Demo */

/* Include useful pre-defined functions */
//#include <avr/interrupt.h>    // Defines pins, ports, etc to make programs easier to read
#define F_CPU 8000000	      // Sets up the default speed for delay.h
#include <avr/io.h>
#include <util/delay.h>

uint16_t waittime = 2400;
uint8_t plus = 0;
#define LED PB0

//uint16_t waittime = 600;

void delay_us(uint16_t delah)
{
	while(delah)
	{
		_delay_us(1);
		delah--;
	}
}
/*
#define PAT4  0b10000001
#define PAT3  0b01000010
#define PAT2  0b00100100
#define PAT1  0b00011000
**/

#define PAT4  0b11000011
#define PAT3  0b01100110
#define PAT2  0b00111100
#define PAT1  0b10011001

/*
#define PAT15 0b11000011
#define PAT25 0b01100110
#define PAT35 0b00111100
#define PAT45 0b10011001

*/
#define PAT15 PAT1
#define PAT25 PAT2
#define PAT35 PAT3
#define PAT45 PAT4

void main()
{
  //DDRB |= _BV(LED); //Enable output on LED pin	
  DDRB = 0b11111111;
  //PORTD = 1;
  //PORTB = 255;	     
  while(1){
	  //waittime+=plus;
	  //plus++;
  //if(bit_is_clear(DDRD,PD0));
    PORTB = PAT1;
	delay_us(waittime);
	
	PORTB = PAT15;
	delay_us(waittime);
	
	//PORTB = 0b01010101;
	//delay_us(waittime);
  
	PORTB = PAT2;
	delay_us(waittime);
	
	PORTB = PAT25;
	delay_us(waittime);
	
	//PORTB = 0b01100110;
	//delay_us(waittime);
	
	PORTB = PAT3;
	delay_us(waittime);
	
	PORTB = PAT35;
	delay_us(waittime);
	
	//PORTB = 0b10101010;
	//delay_us(waittime);
	
	PORTB = PAT4;
	delay_us(waittime);
	
	PORTB = PAT45;
	delay_us(waittime);
	
	//PORTB = 0b10011001;
	//delay_us(waittime);
	//}
  }
}
