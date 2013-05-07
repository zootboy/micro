/* 
* diggX v1.1
* 07/28/07
*
* The software for the digg button is available for use in accordance with the 
* following open source license (MIT License). For more information about
* OS licensing, please visit -> http://www.opensource.org/
*
* For more information about the digg buttom project, please visit
* -> http://www.ladyada.net/make/digg
*
*                                     *****
* Copyright (c) 2007 Limor Fried
* 
* diggX modifications:
* Copyright (c) 2007 Robert Gallup
*
* Permission is hereby granted, free of charge, to any person obtaining a 
* copy of this software and associated documentation files (the "Software"), 
* to deal in the Software without restriction, including without limitation
* the rights to use, copy, modify, merge, publish, distribute, sublicense, 
* and/or sell copies of the Software, and to permit persons to whom the 
* Software is furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in 
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
* FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS 
* IN THE SOFTWARE.
*                                     *****
*
*/


#include <avr/io.h>      // this contains all the IO port definitions
#include <avr/interrupt.h>
#include <avr/eeprom.h>
#include <avr/pgmspace.h>
#include <string.h>
#include "util.h"
#include "main.h"

// Button states
#define button_up 1
#define button_down 0

// Blink num and rate for flashing message
#define blink_num 3
#define blink_rate 50

// Number of diggs stored in eeprom
uint16_t EEMEM stored_number = 0;

// Array for number digits
uint8_t digit_array[3];

// temp var
uint8_t temp = 0;

// Display modes
#define mode_scroll 0
#define mode_number 1
#define mode_flash 2
uint8_t display_mode = mode_scroll;

// Used for manually setting segments on/off
//uint8_t manual_segments = 0;

// Tables mapping characters into LED segments
const uint8_t numbertable[] PROGMEM = { 
	0x7E, /* 0 */
	0x30, /* 1 */
	0x6D, /* 2 */
	0x79, /* 3 */
	0x33, /* 4 */
	0x5B, /* 5 */
	0x5F, /* 6 */
	0x70, /* 7 */
	0x7F, /* 8 */
	0x73, /* 9 */
};
PGM_P numbertable_p PROGMEM = numbertable;

const uint8_t alphatable[] PROGMEM = {
	0x7D, /* a */
	0x1F, /* b */
	0x0D, /* c */
	0x3D, /* d */
	0x6F, /* e */
	0x47, /* f */
	0x7B, /* g */
	0x17, /* h */
	0x30, /* i */
	0x3C, /* j */
	0x57, /* k */
	0x0E, /* l */
	0x55, /* m */
	0x15, /* n */
	0x1D, /* o */
	0x67, /* p */
	0xF3, /* q */
	0x05, /* r */
	0x5B, /* s */
	0x0F, /* t */
	0x1C, /* u */
	0x1C, /* v */ //FIX? Looks like "U"
	0x5C, /* w */
	0x37, /* x */
	0x3B, /* y */
	0x6d, /* z */
	/* more */
};
PGM_P alphatable_p PROGMEM = alphatable;

volatile uint8_t digit1, digit2, digit3;

uint8_t manual_segments = 2;

// Segment FX sequences (6 per FX)
// Seconc set of 6 digits is for jumper OUT, first set is jumper IN
//
//			   0x40
//		     ---
//  0x02 /		/ 0x20
//		    ---  <--------- 0x01
// 0x04 /    / 0x10
//       ---
//      0x08
//
//uint8_t segFX[12] = {0x1, 0x40, 0x8, 0x1, 0x40, 0x08, 0x10, 0x20, 0x40, 0x2, 0x4, 0x08};
//uint8_t segFX[12] = {0x10, 0x02, 0x10, 0x02, 0x10, 0x02, 0x10, 0x20, 0x40, 0x2, 0x4, 0x08};
//uint8_t segFX[12] = {0x00, 0x40, 0x20, 0x01, 0x04, 0x08, 0x10, 0x20, 0x40, 0x2, 0x4, 0x08};

uint8_t segFX[12] = {0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x10, 0x20, 0x40, 0x2, 0x4, 0x08};
uint8_t fxNum = 0;

volatile int16_t button_timer;
#define SHORT_PRESS_TIME 50 // short click milliseconds
#define LONG_PRESS_TIME 3000 // long (press and hold) 3 seconds timeout

volatile uint16_t number;
#define DIGITS 3
volatile uint8_t current_digit_displayed = 0;
volatile uint8_t per_digit_timer;

// For some reason, the power off times are off by a factor of two, so double them ("2 *" at the beginning)
volatile uint32_t poweroff_timer = 0;
#define POWEROFF_TIME 2 * 5 * 60 * 1000UL // 5 minutes * 60 seconds/min * 1000 millisec/sec
#define SCREENSAVE_TIME 2 * 2 * 60 * 1000UL

//char *display_string = "abcdefghijklmnopqrstuvwxyz  ";
char *display_string = "   zootboy";
volatile uint8_t string_index = 0;
volatile uint16_t display_timer = 0;
#define SCROLL_SPEED 500UL

//SIGNAL (SIG_INT0) {
ISR (INT0_vect) {
  GIMSK = 0;
  poweroff_timer = 0;
  button_timer == 0xFFFF;
  while (! (BUTTON_PIN & _BV(BUTTON)))  {
    delay_ms(10);
  }
}

ISR (TIMER0_COMPA_vect) {
  if (button_timer != 0xFFFF) {
    button_timer++;
  }

  if (display_timer != 0xFFFF) {
    display_timer++;
    if (display_timer >= SCROLL_SPEED) {
      display_timer = 0;
      string_index++;
      if (string_index > strlen(display_string)+3)
	string_index -= strlen(display_string);
    }
  }

	// Maintain the poweroff timer even if the pin is connected
	// so the screen saver kicks in
  if (poweroff_timer < POWEROFF_TIME) {
    poweroff_timer++;
  } else if (PINA & 0x1) {
    // time to sleep!
    // turn off all LEDs
      
    display_digit(9, 99);
    MCUCR |= _BV(SM1) | _BV(SM0) | _BV(SE);
    GIMSK = _BV(INT0);
    sei();
    asm("sleep");
  }
  
  per_digit_timer--;
  if (per_digit_timer == 0) {		
    current_digit_displayed++;
    if (current_digit_displayed >= 3)
      current_digit_displayed = 0;
    
    if (current_digit_displayed == 0) { 
      if (segments(digit1) == 0) {
	SEG_CC1_PORT |= _BV(SEG_CC1);
	current_digit_displayed = 1;
      } else {
	display_digit(0, digit1);
	per_digit_timer = segments(digit1);
      }
    }
    if (current_digit_displayed == 1) {
      if (segments(digit2) == 0) {
	SEG_CC2_PORT |= _BV(SEG_CC2);
	current_digit_displayed = 2;
      } else {
	display_digit(1, digit2);
	per_digit_timer = segments(digit2);
      }
    } 
    if (current_digit_displayed == 2) {
      if (segments(digit3) == 0) {
	SEG_CC3_PORT |= _BV(SEG_CC3);
	per_digit_timer = 1;
      } else {
	display_digit(2, digit3);
	per_digit_timer = segments(digit3);
      }
    }
  }
}



void display_one(uint8_t d) {
	if (d & 0x1)  // G 
		PORTD |= _BV(SEG_G);
	else
		PORTD &= ~_BV(SEG_G);

	if (d & 0x2)  // F 
		PORTB  |= _BV(SEG_F);
	else
		PORTB &= ~_BV(SEG_F);

	if (d & 0x4)  // E
		PORTB  |= _BV(SEG_E);
	else
		PORTB &= ~_BV(SEG_E);

	if (d & 0x8)  // D
		PORTB  |= _BV(SEG_D);
	else
		PORTB &= ~_BV(SEG_D);

	if (d & 0x10)  // C
		PORTB  |= _BV(SEG_C);
	else
		PORTB &= ~_BV(SEG_C);

	if (d & 0x20)  // B
		PORTB  |= _BV(SEG_B);
	else
		PORTB &= ~_BV(SEG_B);

	if (d & 0x40)  // A
		PORTB  |= _BV(SEG_A);
	else
		PORTB &= ~_BV(SEG_A);

	if (d & 0x80)  // dot
		PORTD  |= _BV(SEG_DP);
	else
		PORTD &= ~_BV(SEG_DP);
}

void display_digit(uint8_t digit, uint8_t value) {

	// turn them all off (to prevent ghosting)
	SEG_CC1_PORT |= _BV(SEG_CC1);
	SEG_CC2_PORT |= _BV(SEG_CC2);
	SEG_CC3_PORT |= _BV(SEG_CC3);
	SEG_DCC_PORT |= _BV(SEG_DCC);	

	// set the anodes
	if (value <= 9) {
	  display_one(pgm_read_byte(numbertable_p + value));
	} else if ((value >= 'a') && (value <= 'z')) {
	  display_one(pgm_read_byte(alphatable_p + value - 'a'));

	} else if (value == '@') {
		display_one(manual_segments);

	} else if (value == ' ') {
		display_one(0x0);
	}
	
	// turn on cathodes
	if (digit == 0) {
		SEG_CC1_PORT &= ~_BV(SEG_CC1);
	} else if (digit == 1) {
		SEG_CC2_PORT &= ~_BV(SEG_CC2);
	} else if (digit == 2) {
		SEG_CC3_PORT &= ~_BV(SEG_CC3);
	} else if (digit == 3) {
		SEG_DCC_PORT &= ~_BV(SEG_DCC);
	}
}

uint8_t segments(uint8_t value) {
	
	uint8_t x, j;

	if (value <= 9) {
	  x = pgm_read_byte(numbertable_p + value);
	} else if ((value >= 'a') && (value <= 'z')) {
	  x = pgm_read_byte(alphatable_p + value - 'a');

	} else if (value == '@') {
		x = manual_segments;

	} else {
	  return 0x0;
	}
	
// Count number of (bits) segments
	j = 0;
	while (x) {
		j += (x & 0x1);
		x >>= 1;
	}
	return j;
}

// Convert num to digits in an array
void num2digits (uint16_t my_num, uint8_t my_digits[]) {
uint8_t my_i = 0;


	my_num %= 1000;				// num mod 1000 just to avoid overflowing
	my_digits[2] = my_digits[1] = my_digits[0] = ' ';
	while (my_num >= 0) {
		my_digits[my_i++] = my_num % 10;
		my_num /= 10;
		if (!my_num) break;
	};
	return;
}


int main(void) {

  uint8_t button_state, last_button_state, cleared = 0;

  DDRB = 0xFF;
  DDRD = 0xFF;
  DDRA = 0x0; // the unused crystal pins are for changing the timeout.
  PORTA = 0xF; // but they have pullups
  
  GIMSK = 0;
  
  BUTTON_DDR &= ~_BV(BUTTON);
  BUTTON_PORT |= _BV(BUTTON);
  
  number = eeprom_read_word(&stored_number);
	if (number == -1) {
		number = 0;
		eeprom_write_word(&stored_number, number);
	}
	num2digits (number, digit_array);
  
  // set up an interrupt that goes off @ 1KHz)
  TCCR0A = _BV(WGM01);
  TCCR0B = 2; // 500K/8 = 62.3KHz
  OCR0A = 63; // divide that by 63 -> 1KHz
  TIMSK = _BV(OCIE0A); // turn on the interrupt
  sei(); // turn on interrupts

  // now all the LED stuff (persistence of vision) is done in interrupts, so watch for button presses
  
 	button_timer = 0xFFFF;
  last_button_state = button_state = button_up;

  while (1) {
    
		// first, debounce the switch by performing a lowpass filter: the button
    // must be pressed for 10ms (on or off) for it to count. otherwise we get
    // weird effects from the bouncing.

    if ((! (BUTTON_PIN & _BV(BUTTON))) && (button_state == button_up)) {
      poweroff_timer = 0;

      //button was just pressed
      // wait 10 ms and see if the button is still pressed the entire time
      button_timer = 0;
      while (button_timer < 10) {
				if (BUTTON_PIN & _BV(BUTTON)) { // released
	  			break;
				}
				cleared = 0;
      }
      if (button_timer >= 10) { // was held entire time
				button_state = button_down;
      }
    }
    
    if ((BUTTON_PIN & _BV(BUTTON)) && (!button_state)) {
      poweroff_timer = 0;

      // wait 10 ms and see if the button is released the entire time
      button_timer = 0;
      while (button_timer < 10) {
				if (! (BUTTON_PIN & _BV(BUTTON))) { // pressed
	  			break;
				}
      }
			if (button_timer >= 10) { // was held entire time
				button_state = button_up;
      }
    }

    // debounce/lowpassing done, 
    // button_state tells whether the button is down (0) or up (1)
    // now see if it was a short or long press
    if (!button_state && last_button_state) { // Button down
      last_button_state = button_state;
    }
   
   if (!button_state && !last_button_state && (button_timer >= LONG_PRESS_TIME)) { // Long press
      number = 0;
      eeprom_write_word(&stored_number, number);
			num2digits (number, digit_array);
			cleared = 1; 		// just cleared -- used to skip section (incrementing number) this time around
			display_mode = mode_scroll;
    }

		// On button release, flash message and display number
		if (button_state && !last_button_state && !cleared) { //  Button up
      last_button_state = button_state;

			number++;
			eeprom_write_word(&stored_number, number);
			num2digits (number, digit_array);

			// Twirl the segments when they press the button
			// First, set display_mode to flash so the effect isn't overwritten by a number
			display_mode = mode_flash;

			// The '@' char is a back door into setting segments. Other chars are mapped to a read-only table
			// '@' is mapped to a variable that you can change periodically for different effects
			digit1 = digit2 = digit3 = '@';

			// button animation depending on jumper position
			fxNum = (!(PINA & 0x2)) ? 0 : 6;
			//fxNum = ((PINA & 0x2) >> 1) * 6;
			for (temp=0; temp<(blink_num*6); temp++) {
				manual_segments = segFX[fxNum + (temp % 6)];
				delay_ms(4);
			}

			// Return display mode to number so the diggs display
			display_mode = mode_number;
    }

		// Display number
	  if (display_mode == mode_number) { 
			digit1 = digit_array[2];
			digit2 = digit_array[1];
			digit3 = digit_array[0];
		}
    
		// Display scrolling message
    if (display_mode == mode_scroll) {

			digit1 = display_string[string_index % strlen(display_string)];
      digit2 = display_string[(string_index+1) % strlen(display_string)];
      digit3 = display_string[(string_index+2) % strlen(display_string)];

    }

		// If it's been a while, go into screen save mode (i.e. scrolling message)
		if (poweroff_timer > SCREENSAVE_TIME) display_mode = mode_scroll;

  }
}

