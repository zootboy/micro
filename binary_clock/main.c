/* Binary clock */
#include <avr/interrupt.h>    
#define F_CPU 8000000
#include <avr/io.h>
#include <avr/eeprom.h>
#include <util/delay.h>


// This is the calibration value.
// If the clock is slow, reduce the value.
// If it's fast, increase it.
#define TIMERTRIG 31263
// Note: the calibration value is stored in EEPROM.
//       The chip saves EEPROM data across programs, so no need to
//       re-program EEPROM every time.

uint16_t EEMEM timcal = TIMERTRIG; // Set initial calibration value into eeprom file.
//  Note that timcal DOES NOT contain the actual value. It MUST be read from EEPROM.

unsigned int sec = 0;
unsigned int min = 0;
unsigned int hur = 12;

uint16_t calibbytes = TIMERTRIG; 

ISR(TIMER1_COMPA_vect) // Interrupt triggered on timer.
{
	sec++;
	
	if(!bit_is_clear(PINA,PA2)){ // Normal button operation
	if(bit_is_clear(PINA,PA1) && bit_is_clear(PINA,PA0))
	{
		min += 10;
	} else if(bit_is_clear(PINA,PA1))
	{
		min++;
	} else if(bit_is_clear(PINA,PA0))
	{
		hur++;
	}
	} else { // Calibration button operation
		if(bit_is_clear(PINA,PA1))
		{
			// Subtract one from calib.
			calibbytes = eeprom_read_word(&timcal);
			calibbytes -= 1;
			eeprom_write_word(&timcal, calibbytes);
			calibbytes = eeprom_read_word(&timcal); // Just to be sure.
			
			// And actually write in the new value.
			OCR1AH = (unsigned int)(calibbytes >> 8);
			OCR1AL = (unsigned int)calibbytes;
		} else if(bit_is_clear(PINA,PA0))
		{
			// Add one to calib.
			calibbytes = eeprom_read_word(&timcal);
			calibbytes += 1;
			eeprom_write_word(&timcal, calibbytes);
			calibbytes = eeprom_read_word(&timcal); // Just to be sure.
			
			// And actually write in the new value.
			OCR1AH = (unsigned int)(calibbytes >> 8);
			OCR1AL = (unsigned int)calibbytes;
		}
	}
	
	if(sec >= 60)
	{
		min++;
		sec = 0;
	}
	if(min >= 60)
	{
		hur++;
		min = 0;
	}
	if(hur >= 13)
		hur = 1;
}

uint8_t tens(uint16_t n) {
	uint8_t i=0;
	
	while (n >= 100) {
		n-=100;
	}
	while (n >= 10) {
		n-=10;
		i++;
	}
	return i;
}

void delay(void)
{
	_delay_us(500);
}

int main(void)
{
	/* Setup timer */
	cli(); // Disable global interrupts.
	PORTA = 7; // Enable pull-ups on buttons.
	DDRA = 8; // Enable an output on the 4th pin, for shortswitch.
	
	// Prescale the clock by 256 and set clear on compare match.
	TCCR1B = (1<<WGM12)|(1<<CS12); 
	
	// Retreive calibration value from EEPROM
	calibbytes = eeprom_read_word(&timcal);
	
	// Set the compare trigger value.
	OCR1AH = (unsigned int)(calibbytes >> 8);
	OCR1AL = (unsigned int)calibbytes;
	
	TIMSK = (1<<OCIE1A); // Enable compare match interrupt.

	/* Setup display */
	// Ports C & D are the outs.
	DDRC = 0xff;
	DDRD = 0xff;
	
	// Make sure they're all off to start.
	PORTC = 0xFF;
	PORTD = 0x00;
	
	if(bit_is_clear(PINA,PA0)) // Enable display test if 'hours' button is held on powerup.
		_delay_ms(500);
	PORTC = 0x00;
	
	sei(); // Enable global interrupts.

	while(1) // LED driving.
	{
		if(bit_is_set(PINA,PA2)) // If we're running like normal.
		{
			// Get all the column values
			int ca = sec % 10;
			int cb = tens(sec);
			int cc = min % 10;
			int cd = tens(min);
			int ce = hur % 10;
			int cf = tens(hur);
		
			PORTD = ~ca;
			PORTC = (1<<PC0);
			delay();
		
			PORTD = ~cb;
			PORTC = (1<<PC1);
			delay();
		
			PORTD = ~cc;
			PORTC = (1<<PC3);
			delay();
			
			PORTD = ~cd;
			PORTC = (1<<PC4);
			delay();
		
			PORTD = ~ce;
			PORTC = (1<<PC6);
			delay();
		
			PORTD = ~cf;
			PORTC = (1<<PC7);
			delay();
		
			PORTC = 0;
		}
		else // Otherwise, we're in calibration mode.
		{
			// Get the two rows of calibration bytes. 
			calibbytes = eeprom_read_word(&timcal);
			uint8_t row1 = calibbytes;
			uint8_t row2 = (calibbytes >> 8);
			
			// The whole top row is lit to signal calibration mode.
			uint8_t row5 = 0xff;
			
			// Draw the display (row by row instead of col by col).
			PORTC = row1;
			PORTD = ~(1<<PD0);
			delay();
			delay(); // The double delays are intentional.
			
			PORTC = row2;
			PORTD = ~(1<<PD1);
			delay();
			delay();
			
			PORTC = row5;
			PORTD = ~(1<<PD4);
			delay();
			delay();
			
			PORTC = 0;
			PORTD = 0;
			
		}
	}










  /*DDRD = 255;	
  PORTD = pin;

//  GIMSK = 0;
  TCCR0 = _BV(WGM01);
  OCR0 = 1024;
  TIMSK = _BV(OCIE0);
  sei();
  while(1){
    PORTC = 0;
	_delay_ms(WAITFOR);
  
	PORTC = 1;
	_delay_ms(WAITFOR); 
  }*/

  return(0);
}
