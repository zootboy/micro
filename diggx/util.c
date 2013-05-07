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

void delay_ms(unsigned char ms)
{
  unsigned short delay_count = F_CPU / 4000;
  
  unsigned short cnt;
  asm volatile ("\n"
		"L_dl1%=:\n\t"
		"mov %A0, %A2\n\t"
		"mov %B0, %B2\n"
		"L_dl2%=:\n\t"
		"sbiw %A0, 1\n\t"
		"brne L_dl2%=\n\t"
		"wdr\n\t"
		"dec %1\n\t" "brne L_dl1%=\n\t":"=&w" (cnt)
		:"r"(ms), "r"((unsigned short) (delay_count))
		);
}


