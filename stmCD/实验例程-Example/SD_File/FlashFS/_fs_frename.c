/*----------------------------------------------------------------------------
 *      RL-ARM - FlashFS
 *----------------------------------------------------------------------------
 *      Name:    _FS_FRENAME.C 
 *      Purpose: Low level File Rename Function
 *      Rev.:    V4.05
 *----------------------------------------------------------------------------
 *      This code is part of the RealView Run-Time Library.
 *      Copyright (c) 2004-2009 KEIL - An ARM Company. All rights reserved.
 *---------------------------------------------------------------------------*/

#include "File_Config.h"

/*--------------------------- _frename --------------------------------------*/

int _frename (const char *filename, IOB *fcb) {
  /* Low level file rename function. */
  FALLOC fa;
  U32 adr;

  /* Mark old 'filename' block as invalid. */
  adr = fs_adr_sig (fcb->_fblock, fcb) - 8;
  do {
    adr = fs_rd_alloc (adr, &fa);
    if (fa.fileID == (fcb->fileID | 0x8000)) {
      /* Clear only the 'fileID' value */
      fa.end = ~fcb->InitVal;
      fs_WriteBlock ((adr & ~1) + 12, &fa.end, 4, fcb);
      break;
    }
  } while (fa.end != fcb->InitVal);
  /* Create new 'filename' for an existing file */
  return (_fcreate (filename, fcb));
}

/*----------------------------------------------------------------------------
 * end of file
 *---------------------------------------------------------------------------*/
