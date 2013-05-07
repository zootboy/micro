/* chairBot */

#include <avr/interrupt.h> // Enable interrupt functions.
#define F_CPU 8000000	   // Sets up the default speed for delay.h
#include <avr/io.h>        // Defines pins, ports, etc to make programs easier to read
#include <avr/iom8.h>	   // This shouldn't be here. It's just for netbeans (grumble, grumble).
#include <util/delay.h>
#include <avr/eeprom.h>

// IO stuff
#define IODDR  DDRB
#define IOPORT PORTB
#define IOPIN  PINB
#define LEDR   PB3
#define LEDG   PB4
#define PWMP1  PB1 // L
#define PWMP2  PB2 // R
#define BUTTON1 PB0
#define BUTTON2 PB5
// ADC (joystick) defines.
#define JOYCHANX 0
#define JOYCHANY 1
#define IRCHAN1  2
// EEPROM addresses for calibration values.
#define EEXMAX 0
#define EEXNEU 1
#define EEXMIN 2
#define EEYMAX 3
#define EEYNEU 4
#define EEYMIN 5
// Safety value (lower means cuts off foreward motion sooner). Maximum of 30.
#define SAFETY_FACTOR 15
uint8_t eexmin = 0;
uint8_t eexneu = 0;
uint8_t eexmax = 0;
uint8_t eeymin = 0;
uint8_t eeyneu = 0;
uint8_t eeymax = 0;
int8_t joyEnabled = 0; // Accept input from the joystick?
// 0 = off, 1 = on, -1 = calibrate first
uint8_t joyx = 0x00; // ADC value for joystick x-axis.
uint8_t joyy = 0x00; // ADC value for joystick y-axis.
uint8_t irval = 0x00; // ADC value for IR sensor.
uint8_t reader = 0; // 1 for x, 2 for y, 3 for IR.


// UART
// Define baud rate
#define FOSC 8000000// Clock Speed
#define BAUD 9600
#define MYUBRR (FOSC/16/BAUD)-1
/*void uart_init(void)
{
	// Set baud rate
	UBRRH = (unsigned char)(MYUBRR >> 8);
	UBRRL = (unsigned char)(MYUBRR);

	// Enable receiver and transmitter
	UCSRB = (1<<TXEN);
	
	// Set frame format to 8 data bits, no parity, 1 stop bit
	UCSRC = (1<<URSEL)|(0<<USBS)|(1<<UCSZ1)|(1<<UCSZ0);
	// NOTE: ^^^^^^^^ This is SUPER DUPER important. Don't remove it. 
}
void uart_tx(uint8_t u8Data)
{
	// Wait if a byte is being transmitted
	while((UCSRA&(1<<UDRE)) == 0);

	// Transmit data
	UDR = u8Data;
}*/

// PWM vars.
volatile uint8_t pwm1 = 20; // Channel 1; 0-100.
volatile uint8_t pwm2 = 20; // Channel 2; 0-100.
// PWM pins (actual outputs).

void delay_ms(uint16_t ms)
{
	while (ms)
	{
		_delay_ms(1);
		ms--;
	}
}


// E-stop interrupt.
ISR(INT0_vect)
{
	pwm1 = 50;
	pwm2 = 50;
	uint8_t wasOn = 0;
	if(joyEnabled == 1) wasOn = 1;
	joyEnabled = 0;
	IOPORT &= ~(1<<LEDG);
	while(bit_is_clear(PIND,PD2))
	{
		delay_ms(200);
		IOPORT ^= (1<<LEDR);
	}
	IOPORT |= (1<<LEDG);
	IOPORT &= ~(1<<LEDR);
	if(wasOn) joyEnabled = 1;
}

// PWM timer stuff
uint16_t pwmConv(uint16_t percent) // Convert percent (0-100) to timer ticks (1000-2000)
{
	if(percent > 100) { percent = 100; //IOPORT |= (1<<LEDR); 
	}
	return ((percent * 10) + 1000);
}
ISR(TIMER1_COMPB_vect) // Clears the timer on compare. This ensures our 50Hz PWM signal.
{
	TCNT1 = 0x0000; // Reset the timer to 0.
	IOPORT |= (1<<PWMP1)|(1<<PWMP2); // Set both PWM channels to 1.  
	if (pwm1 < pwm2) OCR1A = pwmConv(pwm1);
	else OCR1A = pwmConv(pwm2);
	IOPORT ^= (1<<LEDG);
}
ISR(TIMER1_COMPA_vect) // This is where the actual pulses are generated.
{	
	if (pwmConv(pwm1) > TCNT1) // If pwm1 has not triggered yet... 
	{
		if (pwmConv(pwm2) <= TCNT1) OCR1A = pwmConv(pwm1); // ...and pwm2 is already done, set the trigger to pwm1.
		else if (pwm1 < pwm2) OCR1A = pwmConv(pwm1); // OK, now we know neither have triggered yet. If pwm1 should be first, set it to the trigger.
		else OCR1A = pwmConv(pwm2); // Or else set pwm2 to the trigger.
	} 
	else if (pwmConv(pwm2) > TCNT1) // We know that pwm1 is already done. So if pwm2 is in the future...
	{
		OCR1A = pwmConv(pwm2); // ...set it to the trigger.
	}
	// Or else they are both done and we don't do anything.
	
	// End the pulse when it's time.
	if (TCNT1 >= pwmConv(pwm1)) IOPORT &= ~(1<<PWMP1);
	if (TCNT1 >= pwmConv(pwm2)) IOPORT &= ~(1<<PWMP2);
}
// End PWM timer stuff.

// ADC conversion response.
ISR(ADC_vect) // Note: conversions take about 50ms.
{
	if(reader == 1) 
	{
		joyx = ADCH;
		reader = 2;
		if(joyEnabled == -1)
		{
			if(joyx > eexmax) eexmax = joyx;
			if(joyx < eexmin) eexmin = joyx;
		}
		else if(joyEnabled == -2)
		{
			eexneu = joyx;
			joyEnabled = -3;
		}
		ADMUX = (ADMUX & 0xF0) | (JOYCHANY & 0x0F); // Change to channel 1
		ADCSRA |= (1<<ADSC); // Start a conversion.
	}
	else if(reader == 2) 
	{
		joyy = ADCH;
		reader = 3;
		if(joyEnabled == -1)
		{
			if(joyy > eeymax) eeymax = joyy;
			if(joyy < eeymin) eeymin = joyy;
		}
		else if(joyEnabled == -3)
		{
			eeyneu = joyy;
			joyEnabled = -4;
		}
		ADMUX = (ADMUX & 0xF0) | (IRCHAN1 & 0x0F); // Change to channel 0
		ADCSRA |= (1<<ADSC); // Start a conversion.
	}
	else if(reader == 3)
	{
		irval = ADCH;
		reader = 1;
		ADMUX = (ADMUX & 0xF0) | (JOYCHANX & 0x0F); // Change to channel 0
		ADCSRA |= (1<<ADSC); // Start a conversion.
	}
}

// This function converts the joystick ADC values to PWM values.
void joyToPwm(void)
{
	if(joyEnabled < 1) // If we're out of calibration or off, don't spin the wheels!
	{
		pwm1 = 50; pwm2 = 50;
	}
	else
	{
		uint8_t xval;
		uint8_t yval;
		if(joyx > eexmax) joyx = eexmax;
		if(joyy > eeymax) joyy = eeymax;
		// X
		if(joyx <= eexneu)
			xval = (uint8_t)((50.0/(float)(eexneu-eexmin))*(float)(joyx-eexmin));
		else
			xval = (uint8_t)((50.0/(float)(eexmax-eexneu))*(float)(joyx-eexneu)+50.0);

		// Y
		if(joyy <= eeyneu)
			yval = (uint8_t)((50.0/(float)(eeyneu-eeymin))*(float)(joyy-eeymin));
		else
			yval = (uint8_t)((50.0/(float)(eeymax-eeyneu))*(float)(joyy-eeyneu)+50.0);
		
		if(irval > SAFETY_FACTOR)
		{
			if(((100-yval)-(xval-50)) > 60) pwm1 = 56;
			else if(((100-yval)-(xval-50)) < 50) pwm1 = 50;
			
			if(((100-yval)-(50-xval)) > 60) pwm2 = 60;
			else if(((100-yval)-(50-xval)) < 50) pwm2 = 50;
		}
		else
		{
			pwm1 = (100-yval)-(xval-50);
			pwm2 = (100-yval)-(50-xval);
		}
		
		
	}

}

int main(void)
{
	delay_ms(10); // Let the power stabilize.	
	cli(); // Disable interrupts.

	IODDR = (1<<PWMP1)|(1<<PWMP2)|(1<<LEDG)|(1<<LEDR); // Pins B1 - B4 are outputs.
	
	IOPORT |= (1<<LEDG)|(1<<LEDR)|(1<<BUTTON1)|(1<<BUTTON2); // LEDs on, pullups on.
	delay_ms(200);
	IOPORT &= ~((1<<LEDG)|(1<<LEDR)); // LEDs off.
	
	// E-stop interrupt.
	GICR |= (1<<INT0);
	
	// Read the calibration values from EEPROM
	eexmin = eeprom_read_byte((uint8_t*)EEXMIN);
	eexneu = eeprom_read_byte((uint8_t*)EEXNEU);
	eexmax = eeprom_read_byte((uint8_t*)EEXMAX);
	eeymin = eeprom_read_byte((uint8_t*)EEYMIN);
	eeyneu = eeprom_read_byte((uint8_t*)EEYNEU);
	eeymax = eeprom_read_byte((uint8_t*)EEYMAX);
	
//	uart_init();
//	uart_tx((uint8_t)"t");
	
	// Timer stuff for PWM.
	OCR1B = 20000; // 20000 ticks = 50Hz timer runs (see spreadsheet).
	OCR1A = pwmConv(50);
	TCCR1A = 0; // Normal mode, no pin triggers.
	TCCR1B = (1 << CS11); // Clk/8
	TIMSK = (1 << OCIE1A)|(1 << OCIE1B); // Enable both compare interrupts.
	
	// ADC init.
	ADMUX = (1<<REFS0)|(1<<ADLAR); // AVcc ref, left-adjusted output.
	ADCSRA = (1<<ADEN)|(1<<ADIE)|(1<<ADPS2)|(1<<ADPS0); // Enable ADC, clkdiv of 32.
	reader = 1;
	ADCSRA |= (1<<ADSC); // Kick off the conversion.

	sei(); // Enable interrupts.

	// Run some basic sanity checks on the data. If it seems insane, the joystick needs calibration.
	if(eexmin == 0xFF || eeymin == 0xFF || eexmin >= eexmax || eeymin >= eeymax || eexneu >= eexmax || eeyneu >= eeymax)
	{
		while(reader != 2) delay_ms(1);
		eexmin = joyx;
		eexmax = joyx;
		eexneu = joyx;
		eeymin = joyx;
		eeymax = joyx;
		eeyneu = joyx;
		joyEnabled = -1; // Calibrate that bastard!
	}
	
	
	while (1) // Main loop.
	{
		/*while(1)
		{
			pwm1 = 50; pwm2 = 50;
			delay_ms(4000);
			pwm1 = 0; pwm2 = 0;
			delay_ms(2000);
			pwm1 = 50; pwm2 = 50;
			delay_ms(2000);
			pwm1 = 100; pwm2 = 100;
			delay_ms(2000);
			//pwm1 += 10;
			//if(pwm1 >= 101) pwm1 = 0
			for(uint8_t i=0;i<100;i+=1)
			{
				delay_ms(100);
				pwm1 = i;pwm2 = 50;
			}
		}*/
		
		if(joyEnabled == -1) // Start calibrating.
		{
			pwm1 = 50; pwm2 = 50;
			IOPORT ^= (1<<LEDR); // Blink the red LED.
			delay_ms(250);
			//uart_tx(joyx); uart_tx((uint8_t)"\n");
			if(bit_is_clear(IOPIN, BUTTON1))
			{
				joyEnabled = -2;
				while(joyEnabled != -4) delay_ms(1);
				joyEnabled = 1;
				
				eeprom_write_byte(&eexmin, (uint8_t)EEXMIN);
				eeprom_write_byte(&eexneu, (uint8_t)EEXNEU);
				eeprom_write_byte(&eexmax, (uint8_t)EEXMAX);
				eeprom_write_byte(&eeymin, (uint8_t)EEYMIN);
				eeprom_write_byte(&eeyneu, (uint8_t)EEYNEU);
				eeprom_write_byte(&eeymax, (uint8_t)EEYMAX);
				
				IOPORT &= ~((1<<LEDR));
				IOPORT |= (1<<LEDG);
			}
		}
		else if(joyEnabled == 1)
		{
			joyToPwm();
			if(irval > SAFETY_FACTOR) IOPORT ^= (1<<LEDR);
			else IOPORT &= ~(1<<LEDR);
		}
		
	}
	return (0); // This line should NEVER run. Don't break out of the while(1) loop.
}
