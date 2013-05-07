/*----------------------------------------------------------------------------
 *      RL-ARM - FlashFS
 *----------------------------------------------------------------------------
 *      Name:    _FS_FDELETE.C 
 *      Purpose: Low level File Delete Function
 *      Rev.:    V4.05
 *----------------------------------------------------------------------------
 *      This code is part of the RealView Run-Time Library.
 *      Copyright (c) 2004-2009 KEIL - An ARM Company. All rights reserved.
 *---------------------------------------------------------------------------*/

#include <stdio.h>
#include <rt_sys.h>
#include <rt_misc.h>
#include "File_Config.h"

/*--------------------------- _fdelete --------------------------------------*/

int _fdelete (IOB *fcb) {
  /* Low level file delete function. */
  FALLOC fa;
  U32 i,bl,adr,invalid;

  invalid = ~fcb->InitVal;
  bl = fcb->_fblock;
  for (i = 0; i < fcb->NumSect; i++) {
    /* Search for file blocks identified with identification 'fileID' */
    adr = fs_adr_sig (bl, fcb);
    adr = fs_rd_sig (adr, &fa.end);
    if (fa.end != fcb->InitVal) {
      do {
        adr = fs_rd_alloc (adr, &fa);
        if ((fa.fileID & 0x7FFF) == fcb->fileID) {
          /* Clear the fileID & index values */
          fs_WriteBlock ((adr & ~1) + 12, &invalid, 4, fcb);
        }
      } while (fa.end != fcb->InitVal);

      /* Check if this Flash Block is all invalidated */
      if (fs_BlockInvalid (bl, fcb) == __TRUE) {
        /* All file blocks stored in this Flash Block are invalid */
        fs_InitBlock (bl, fcb);
      }
    }
    if (++bl == fcb->NumSect) {
      bl = 0;
    }
  }
  return (0);
}

/*----------------------------------------------------------------------------
 * end of file
 *---------------------------------------------------------------------------*/
