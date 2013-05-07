#define F_CPU 8000000	      // Sets up the default speed for delay.h
#include <avr/io.h> 		  // Defines pins, ports, etc to make programs easier to read
#include <avr/interrupt.h>    // Allows interrupts
//#include <avr/signal.h>
#include <util/delay.h>


INTERRUPT(SIG_OUTPUT_COMPARE1A)
{
  static uint8_t ledon;

  if (ledon) 
  {
    ledon = 0;
    PORTB = 0;
  }
  else
  {
    ledon = 1;
    PORTB = 1;
  }
  return(0);
}


void main(){
  DDRB = 1; // Assign PB1 to outpot status
  //PORTB = 1; // Turn PB1 on 
  
  TIMSK = _BV(OCIE1A);
  TCCR1B = _BV(CS12)    // 256 prescale
         | _BV(WGM12);  // CTC mode, TOP = OCR1A
  OCR1A = 15625;        // count up to TOP   1hz with 8 meg system clock
  while (1)
    asm volatile("nop" ::);  // we spin!  Could also put processor to sleep
  return(0);
}
