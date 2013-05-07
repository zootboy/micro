/* This file has been prepared for Doxygen automatic documentation generation.*/
/*! \file *********************************************************************
 *
 * \brief
 *      Configuration and macros
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
 * $RCSfile: calib_values.h,v $
 * $Date: 2006/02/17 12:49:26 $  \n
 ******************************************************************************/


#ifndef __CALIB_VALUES_H__
#define __CALIB_VALUES_H__

/*! \brief User defined values.
 *
 * The following values such as calibration method, calibration frequency,
 * external watch crystal frequency, and external ticks, can be modified by the user
 * to improve accuracy or change desired calibration frequency
 *
 */

/*! Calibration methods, Binary search WITH Neighborsearch is default method
 * Uncomment to use ONE of the two following methods instead:
 */
//#define CALIBRATION_METHOD_BINARY_WITHOUT_NEIGHBOR
//#define CALIBRATION_METHOD_SIMPLE

/*! Modify CALIBRATION_FREQUENCY to desired calibration frequency
 */
#define CALIBRATION_FREQUENCY 8000000

/*! Frequency of the external oscillator. A 32kHz crystal is recommended
 */
#define XTAL_FREQUENCY 8000000
#define EXTERNAL_TICKS 100               // ticks on XTAL. Modify to increase/decrease accuracy

/*! \brief Fixed calibration values and macros
 *
 * These values are fixed and used by all calibration methods. Not to be modified.
 *
 */
#define FALSE 0
#define TRUE 1
#define RUNNING 0
#define FINISHED 1
#define DEFAULT_OSCCAL_MASK        0x00  // Lower half and
#define DEFAULT_OSCCAL_MASK_HIGH   0x80  // upper half for devices with splitted OSCCAL register

#include "device_specific.h"

#define DEFAULT_OSCCAL_HIGH ((1 << (OSCCAL_RESOLUTION - 1)) | DEFAULT_OSCCAL_MASK_HIGH)
#define INITIAL_STEP         (1 << (OSCCAL_RESOLUTION - 2))
#define DEFAULT_OSCCAL      ((1 << (OSCCAL_RESOLUTION - 1)) | DEFAULT_OSCCAL_MASK)

// **** Functions implemented as macros to avoid function calls
#define PREPARE_CALIBRATION() \
calStep = INITIAL_STEP; \
calibration = RUNNING;

#define COMPUTE_COUNT_VALUE() \
countVal = ((EXTERNAL_TICKS*CALIBRATION_FREQUENCY)/(XTAL_FREQUENCY*LOOP_CYCLES));

// Set up timer to be ASYNCHRONOUS from the CPU clock with a second EXTERNAL 32,768kHz CRYSTAL driving it. No prescaling on asynchronous timer.
#define SETUP_ASYNC_TIMER() \
ASSR |= (1<<ASYNC_TIMER); \
ASYNC_TIMER_CONTROL_REGISTER = (1<<NO_PRESCALING);




// For ATmega64 and ATmega128, 8 nop instructions must be run after a
// change in OSCCAL to ensure stability (See errata in datasheet).
// For all other devices, one nop instruction should be run to let
// the RC oscillator stabilize.
// The NOP() macro takes care of this.
#if defined(__AT90Mega64__) | defined(__ATmega64__) | \
    defined(__AT90Mega128__) | defined(__ATmega128__)

#define NOP() \
__no_operation(); \
__no_operation(); \
__no_operation(); \
__no_operation(); \
__no_operation(); \
__no_operation(); \
__no_operation(); \
__no_operation();


#else
#define NOP() __no_operation()
#endif

// Absolute value macro.
#define ABS(var) (((var) < 0) ? -(var) : (var));

#endif

