/* vim: set sw=8 ts=8 si et: */
/*
* ADC functions for atmega8.
* Author: Guido Socher, Copyright: GPL 
* http://tuxgraphics.org/electronics/
*/
#include <avr/io.h>

//----------------EDIT HERE----------------------------------------
// VDIV = (Rx+Ry)/Rx, change this according to the division factor of Rx and Ry
//
// This is if you do not use any resistor for Rx and Ry=4K7 (measure up to 2.5V):
//#define VDIV 1.0
//
// Ry=4K7 Rx=4K7 -> divide by 2 (measure up to 5V)
#define VDIV 2
// amplifier with amplification factor of 5.12-> measure 0-500mV
// This is (1/5.12) *10 = 1.953 (below is calibrated to the resistors in use)
//#define VDIV 1.96

// convert adc reading to voltage (display values)
unsigned int analog2v(unsigned int aval)
{
        double r;
        // 100* 2.56*VDIV/1024:
        r=((double)aval * VDIV )/4.0;
        return((unsigned int)r);
}

//-------------END EDIT HERE----------------------------------------

// return analog value of a given channel. Works without interrupt 
unsigned int convertanalog(unsigned char channel) 
{
        unsigned char adlow,adhigh;
        /* enable analog to digital conversion in single run mode
        *  without noise canceler function. See datasheet of atmega88 page 250
        * We set ADPS2=1 ADPS0=1 ADPS1=1 to have a clock division factor of 128.
        * This is needed to stay in the recommended range of 50-200kHz 
        * Clock freq= 14MHz or 18 MHz
        * ADEN: Analog Digital Converter Enable
        * ADIE: ADC Interrupt Enable  (0=no interrupt)
        * ADIF: ADC Interrupt Flag
        * ADCSR: ADC Control and Status Register
        * ADPS2..ADPS0: ADC Prescaler Select Bits
        * REFS: Reference Selection Bits (page 203)
        */

        // int-ref with external capacitor at AREF pin: 
        // atmega8: 2.56V int ref=REFS1=1,REFS0=1
        // atmega88: 1.1V int ref=REFS1=1,REFS0=1
        // write only the lower 3 bit for channel selection
        //
#ifdef USEAVCCREF
        // AVcc ref
        ADMUX=(1<<REFS0)|(channel & 0x0f);
#else
        // Use the intenal  ref:
        ADMUX=(1<<REFS1)|(1<<REFS0)|(channel & 0x0f);
#endif
        // 
#ifdef VAR_88CHIP
        ADCSRA=(1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
#else
        ADCSR=(1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
#endif
        // switch off digital input line:
        //DIDR0=(1<<channel)& 0x1f;

#ifdef VAR_88CHIP
        //  start conversion 
        ADCSRA|= (1<<ADSC);
        while(bit_is_set(ADCSRA,ADSC)); // wait for result 
#else
        //  start conversion 
        ADCSR|= (1<<ADSC);
        while(bit_is_set(ADCSR,ADSC)); // wait for result 
#endif
        adlow=ADCL; // read low first !! 
        adhigh=ADCH; 
        return((unsigned int)((adhigh<<8)|(adlow & 0xFF)));
}


