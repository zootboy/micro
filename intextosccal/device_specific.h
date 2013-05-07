/* This file has been prepared for Doxygen automatic documentation generation.*/
/*! \file *********************************************************************
 *
 * \brief
 *      Device specific definitions
 *
 * \par Application note:
 *      AVR055: Using a 32 kHz crystal to calibrate the internal RC oscillator
 *
 * \par Documentation
 *      For comprehensive code documentation, supported compilers, compiler
 *      settings and supported devices see readme.html
 *
 * \author
 *      Atmel Corporation: http://www.atmel.com \n
 *      Support email: avr@atmel.com
 *
 * $Name: RELEASE_1_1 $
 * $Revision: 1.2 $
 * $RCSfile: device_specific.h,v $
 * $Date: 2006/02/17 12:49:26 $  \n
 ******************************************************************************/


#ifndef __DEVICE_SPECIFIC_H__
#define __DEVICE_SPECIFIC_H__

/*! \brief Device specific register names
 *
 * This file conatins all device specific defifinitions for
 * all supported parts used by the compiler
 *
 */

#if defined(__ATmega163__) | defined(__ATmega323__)
#define ASYNC_TIMER                        AS2
#define NO_PRESCALING                      CS20
#define ASYNC_TIMER_CONTROL_REGISTER       TCCR2
#define ASYNC_TIMER_CONTROL_UPDATE_BUSY    TCR2UB
#define OUTPUT_COMPARE_UPDATE_BUSY         OCR2UB
#define TIMER_UPDATE_BUSY                  TCN2UB
#define TIMER                              TCNT2
#define OSCCAL_RESOLUTION                  8
#define LOOP_CYCLES                        6
#endif

#if defined(__ATmega64__) | defined(__ATmega128__)
#define ASYNC_TIMER                        AS0
#define NO_PRESCALING                      CS00
#define ASYNC_TIMER_CONTROL_REGISTER       TCCR0
#define ASYNC_TIMER_CONTROL_UPDATE_BUSY    TCR0UB
#define OUTPUT_COMPARE_UPDATE_BUSY         OCR0UB
#define TIMER_UPDATE_BUSY                  TCN0UB
#define TIMER                              TCNT0
#define OSCCAL_RESOLUTION                  8
#define LOOP_CYCLES                        6
#endif

#if defined(__ATmega8__) | defined(__ATmega16__) | \
    defined(__ATmega32__) | defined(__ATmega8535__)
#define ASYNC_TIMER                        AS2
#define NO_PRESCALING                      CS20
#define ASYNC_TIMER_CONTROL_REGISTER       TCCR2
#define ASYNC_TIMER_CONTROL_UPDATE_BUSY    TCR2UB
#define OUTPUT_COMPARE_UPDATE_BUSY         OCR2UB
#define TIMER_UPDATE_BUSY                  TCN2UB
#define TIMER                              TCNT2
#define OSCCAL_RESOLUTION                  8
#define LOOP_CYCLES                        6
#endif

#if defined(__ATmega162__)
#define ASYNC_TIMER                        AS2
#define NO_PRESCALING                      CS20
#define ASYNC_TIMER_CONTROL_REGISTER       TCCR2
#define ASYNC_TIMER_CONTROL_UPDATE_BUSY    TCR2UB
#define OUTPUT_COMPARE_UPDATE_BUSY         OCR2UB
#define TIMER_UPDATE_BUSY                  TCN2UB
#define TIMER                              TCNT2
#define OSCCAL_RESOLUTION                  7
#define LOOP_CYCLES                        6
#endif

#if defined(__ATmega169__) | defined(__ATmega165__)
#define ASYNC_TIMER                        AS2
#define NO_PRESCALING                      CS20
#define ASYNC_TIMER_CONTROL_REGISTER       TCCR2A
#define ASYNC_TIMER_CONTROL_UPDATE_BUSY    TCR2UB
#define OUTPUT_COMPARE_UPDATE_BUSY         OCR2UB
#define TIMER_UPDATE_BUSY                  TCN2UB
#define TIMER                              TCNT2
#define OSCCAL_RESOLUTION                  7
#define LOOP_CYCLES                        7
// Uncomment the following line for ATmega169P
//#define TWO_RANGES
#endif

#if defined(__ATmega48__) | defined(__ATmega88__) | defined(__ATmega168__)
#define ASYNC_TIMER                        AS2
#define NO_PRESCALING                      CS20
#define ASYNC_TIMER_CONTROL_REGISTER       TCCR2B
#define ASYNC_TIMER_CONTROL_UPDATE_BUSY    TCR2AUB
#define OUTPUT_COMPARE_UPDATE_BUSY         OCR2AUB
#define TIMER_UPDATE_BUSY                  TCN2UB
#define TIMER                              TCNT2
#define OSCCAL_RESOLUTION                  7
#define LOOP_CYCLES                        7
#define TWO_RANGES
#endif

#if defined(__ATmega325__) | defined(__ATmega645__) | \
    defined(__ATmega3250__) | defined(__ATmega6450__) | \
    defined(__ATmega329__) | defined(__ATmega649__) | \
    defined(__ATmega3290__) | defined(__ATmega6490__)
#define ASYNC_TIMER                        AS2
#define NO_PRESCALING                      CS20
#define ASYNC_TIMER_CONTROL_REGISTER       TCCR2A
#define ASYNC_TIMER_CONTROL_UPDATE_BUSY    TCR2UB
#define OUTPUT_COMPARE_UPDATE_BUSY         OCR2UB
#define TIMER_UPDATE_BUSY                  TCN2UB
#define TIMER                              TCNT2
#define OSCCAL_RESOLUTION                  7
#define LOOP_CYCLES                        7
#define TWO_RANGES
#endif

#if defined(__ATmeg1281__) | defined(__ATmega1281) | defined(__ATmega1280) | \
    defined(__ATmega2560__) | defined(__ATmega2561__) | defined(__ATmega640)
#define ASYNC_TIMER                        AS2
#define NO_PRESCALING                      CS20
#define ASYNC_TIMER_CONTROL_REGISTER       TCCR2B
#define ASYNC_TIMER_CONTROL_UPDATE_BUSY    TCR2AUB
#define OUTPUT_COMPARE_UPDATE_BUSY         OCR2AUB
#define TIMER_UPDATE_BUSY                  TCN2UB
#define TIMER                              TCNT2
#define OSCCAL_RESOLUTION                  7
#define LOOP_CYCLES                        7
#define TWO_RANGES
#endif

#if defined(__AT90CAN128__)
#define ASYNC_TIMER                        AS2
#define NO_PRESCALING                      CS20
#define ASYNC_TIMER_CONTROL_REGISTER       TCCR2A
#define ASYNC_TIMER_CONTROL_UPDATE_BUSY    TCR2UB
#define OUTPUT_COMPARE_UPDATE_BUSY         OCR2UB
#define TIMER_UPDATE_BUSY                  TCN2UB
#define TIMER                              TCNT2
#define OSCCAL_RESOLUTION                  7
#define LOOP_CYCLES                        7
#endif

#endif

