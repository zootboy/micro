/* Captain - operations.c */
#include <avr/io.h>
#include "operations.h"

/* roomScan
 * Activates a 360-degree rotation in place, with safety checks for wall 
 * proximity first. It asks the Navigator to do a ping scan (and IR, possibly)
 * and gather a circle of data points. It will be the navigator's job to deal
 * with the data.
 */
void roomScan(void)
{
	
}