/*----------------------------------------------------------------------------
 *      RL-ARM - TCPnet
 *----------------------------------------------------------------------------
 *      Name:    HTTP_UIF.C
 *      Purpose: HTTP Server User Interface Module
 *      Rev.:    V4.05
 *----------------------------------------------------------------------------
 *      This code is part of the RealView Run-Time Library.
 *      Copyright (c) 2004-2009 KEIL - An ARM Company. All rights reserved.
 *---------------------------------------------------------------------------*/

#include <stdio.h>
#include "Net_Config.h"

/*----------------------------------------------------------------------------
 * HTTP Server File Access CallBack Functions
 *---------------------------------------------------------------------------*/

/*--------------------------- http_fopen ------------------------------------*/

void *http_fopen (U8 *fname) {
  /* Open file 'fname' for reading. Return file handle. */
  return (fopen ((const char *)fname, "r"));
}


/*--------------------------- http_fclose -----------------------------------*/

void http_fclose (void *f) {
  /* Close the file opened for reading. */
  fclose (f);
}


/*--------------------------- http_fread ------------------------------------*/

U16 http_fread (void *f, U8 *buf, U16 len) {
  /* Read 'len' bytes from file to buffer 'buf'. The file will be closed, */
  /* when the number of read bytes is less than 'len'.                    */
  return (fread (buf, 1, len, f));
}


/*--------------------------- http_fgets ------------------------------------*/

BOOL http_fgets (void *f, U8 *buf, U16 size) {
  /* Read a string from file to buffer 'buf'. The file will be closed, */
  /* when this function returns __FALSE.                               */
  if (fgets ((char *)buf, size, f) == NULL) {
    return (__FALSE);
  }
  return (__TRUE);
}

/*--------------------------- http_finfo ------------------------------------*/

U32 http_finfo (U8 *fname) {
  /* Read last modification time of a file. Return lm time in UTC format. */
  FINFO *info;
  U32 utc;

  info = (FINFO *)alloc_mem (sizeof (FINFO));
  info->fileID = 0;
  utc = 0;
  if (ffind ((const char *)fname, info) == 0) {
    /* File found, save creation date in UTC format. */
    utc = http_date (&info->time);
  }
  free_mem ((OS_FRAME *)info);
  return (utc);
}

/*----------------------------------------------------------------------------
 * end of file
 *---------------------------------------------------------------------------*/
