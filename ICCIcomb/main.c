/* Blinker Demo */

/* Include useful pre-defined functions */
#include <avr/interrupt.h>    // Defines pins, ports, etc to make programs easier to read
#define F_CPU 8000000	      // Sets up the default speed for delay.h
#include <avr/io.h>
#include <util/delay.h>

#define WAITFOR 120

#define CHS1 PD6
#define CHS2 PD7
#define CHS3 PD0
#define CHS4 PD1

#define STA1 PC5
#define STA2 PC4
#define STA3 PC3
#define STA4 PC2
#define STA5 PC1

int main(void) {

  DDRD |= (1<<CHS1)|(1<<CHS2)|(1<<CHS3)|(1<<CHS4); // Enable output on chaser LED pins.
  DDRC |= (1<<STA1)|(1<<STA2)|(1<<STA3)|(1<<STA4)|(1<<STA5); // Enable output on status LED pins.
  //DDRD = 0;
  //PORTD = 1;
  //PORTB = 255;	

	PORTD = 0xff;
	PORTC = 0xff;
	
	_delay_ms(1000);
  while(1){
  
  PORTD = DDRD;
  _delay_ms(WAITFOR*2);
	PORTC = DDRC;
 _delay_ms(WAITFOR*2);
 PORTC = 0;
  
    PORTD = (1<<CHS1);
	_delay_ms(WAITFOR);
	PORTD = (1<<CHS2);
	_delay_ms(WAITFOR);
	PORTD = (1<<CHS3);
	_delay_ms(WAITFOR);
	PORTD = (1<<CHS4);
	_delay_ms(WAITFOR);
	
	PORTD = 0;
	
	PORTC |= (1<<STA1);
	_delay_ms(WAITFOR*2);
	PORTC |= (1<<STA2);
	_delay_ms(WAITFOR*2);
	PORTC |= (1<<STA3);
	_delay_ms(WAITFOR*2);
	PORTC |= (1<<STA4);
	_delay_ms(WAITFOR*2);
	PORTC |= (1<<STA5);
	_delay_ms(WAITFOR*2);
	/*uint8_t i = 1;
	for(;i<=64;i*=2);
	{
		PORTC = i;
		_delay_ms(500);
	}*/
	
	
	PORTC = 0;
   
  }

  return(0);
}
