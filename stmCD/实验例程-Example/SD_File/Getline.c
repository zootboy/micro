/*----------------------------------------------------------------------------
 *      RL-ARM - FlashFS
 *----------------------------------------------------------------------------
 *      Name:    GETLINE.C
 *      Purpose: Line Edited Character Input
 *----------------------------------------------------------------------------
 *      This code is part of the RealView Run-Time Library.
 *      Copyright (c) 2004-2009 KEIL - An ARM Company. All rights reserved.
 *---------------------------------------------------------------------------*/

#include <RTL.h>
#include <stdio.h>
#include "SD_File.h"

/*----------------------------------------------------------------------------
 *      Line Editor
 *---------------------------------------------------------------------------*/
BOOL getline (char *lp, U32 n) {
  U32 cnt = 0;
  char c;

  do {
    c = getkey ();
    switch (c) {
      case CNTLQ:                          /* ignore Control S/Q             */
      case CNTLS:
        break;;
      case BACKSPACE:
      case DEL:
        if (cnt == 0) {
          break;
        }
        cnt--;                             /* decrement count                */
        lp--;                              /* and line pointer               */
        putchar (0x08);                    /* echo backspace                 */
        putchar (' ');
        putchar (0x08);
        fflush (stdout);
        break;
      case ESC:
        *lp = 0;                           /* ESC - stop editing line        */
        return (__FALSE);
      case CR:                             /* CR - done, stop editing line   */
        *lp = c;
        lp++;                              /* increment line pointer         */
        cnt++;                             /* and count                      */
        c = LF;
      default:
        putchar (*lp = c);                 /* echo and store character       */
        fflush (stdout);
        lp++;                              /* increment line pointer         */
        cnt++;                             /* and count                      */
        break;
    }
  } while (cnt < n - 2  &&  c != LF);      /* check limit and CR             */
  *lp = 0;                                 /* mark end of string             */
  return (__TRUE);
}

/*----------------------------------------------------------------------------
 * end of file
 *---------------------------------------------------------------------------*/
