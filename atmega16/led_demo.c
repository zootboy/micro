/* Blinker Demo */

/* Include useful pre-defined functions */
#include <avr/interrupt.h>    // Defines pins, ports, etc to make programs easier to read
#define F_CPU 1000000	      // Sets up the default speed for delay.h
#include <avr/io.h>
#include <util/delay.h>

#define WAITFOR 1000

int pin = 0;

ISR(TIMER0_OVF_vect)
{
  pin++;
  PORTD = 1;
}

int main(){

  DDRD = 255;	
  PORTD = pin;

//  GIMSK = 0;
  TCCR0 = _BV(WGM01);
  OCR0 = 1024;
  TIMSK = _BV(OCIE0);
  sei();
  /*while(1){
    PORTC = 0;
	_delay_ms(WAITFOR);
  
	PORTC = 1;
	_delay_ms(WAITFOR); 
  }*/

  return(0);
}
