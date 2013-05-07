/*----------------------------------------------------------------------------
 *      RL-ARM - FlashFS
 *----------------------------------------------------------------------------
 *      Name:    FS_TIME.C 
 *      Purpose: File System Time Support Functions
 *      Rev.:    V4.05
 *----------------------------------------------------------------------------
 *      This code is part of the RealView Run-Time Library.
 *      Copyright (c) 2004-2009 KEIL - An ARM Company. All rights reserved.
 *---------------------------------------------------------------------------*/

#include <RTL.h>

/*----------------------------------------------------------------------------
 *      FS Time Functions
 *----------------------------------------------------------------------------
 *  Required functions for File System Time Support
 *   - U32 fs_get_time ()
 *   - U32 fs_get_date ()
 *---------------------------------------------------------------------------*/

/*--------------------------- fs_get_time -----------------------------------*/

U32 fs_get_time (void) {
  /* Return Current Time for FAT File Time stamp. */
  U32 h,m,s,time;

  /* Modify here, add a system call to read RTC. */
  /* Hours:   0 - 23 */
  /* Minutes: 0 - 59 */
  /* Seconds: 0 - 59 */
  h = 12;
  m = 0;
  s = 0;

  time = (h << 16) | (m << 8) | s;
  return (time);
}


/*--------------------------- fs_get_date -----------------------------------*/

U32 fs_get_date (void) {
  /* Return Current Date for FAT File Time stamp. */
  U32 d,m,y,date;

  /* Modify here, add a system call to read RTC. */
  /* Day:   1 - 31 */
  /* Month: 1 - 12 */
  /* Year:  1980 - 2107 */
  d = 1;
  m = 1;
  y = 2008;

  date = (y << 16) | (m << 8) | d;
  return (date);
}


/*----------------------------------------------------------------------------
 * end of file
 *---------------------------------------------------------------------------*/
