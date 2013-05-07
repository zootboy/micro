/*----------------------------------------------------------------------------
 *      RL-ARM - FlashFS
 *----------------------------------------------------------------------------
 *      Name:    _FS_GETFSIZE.C 
 *      Purpose: Low level Get File Size Function
 *      Rev.:    V4.05
 *----------------------------------------------------------------------------
 *      This code is part of the RealView Run-Time Library.
 *      Copyright (c) 2004-2009 KEIL - An ARM Company. All rights reserved.
 *---------------------------------------------------------------------------*/

#include "File_Config.h"

/*--------------------------- __getfsize ------------------------------------*/

U32 __getfsize (IOB *fcb, BOOL set_fidx) {
  /* Low level get file size function. */
  FALLOC fa;
  U32 bl,fidx,adr,prev;
  U32 i,fsize;

  START_LOCK (U32);

  if (fcb->drive == DRV_MCARD) {
    /* This info is available for Flash Card. */
    RETURN (fcb->fsize);
  }
  if ((fcb->flags & _IOAPPEND) && (set_fidx == __FALSE)) {
    /* Size info already set in '__fopen()'. */
    RETURN (fcb->fsize);
  }
  fidx = 0;
  fsize = 0;
  bl = fcb->_fblock;
nextbl:
  for (i = 0; i < fcb->NumSect; i++) {
    /* Search for file blocks identified with identification 'fileID' */
    adr = fs_adr_sig (bl, fcb);
    adr = fs_rd_sig (adr, &fa.end);
    if (fa.end != fcb->InitVal) {
      for (prev = 0; ; prev = fa.end) {
        adr = fs_rd_alloc (adr, &fa);
        if (fa.fileID == fcb->fileID  &&  fa.index == fidx) {
          /* All file blocks are 4-byte aligned. */
          fsize += (fa.end - ((prev + 3) & ~3));
          fidx++;
          goto nextbl;
        }
        if (fa.end == fcb->InitVal) break;
      }
    }
    if (++bl == fcb->NumSect) {
      bl = 0;
    }
  } 
  /* This File Block does not exist so this must be End Of File */
  if (set_fidx == __TRUE) {
    fcb->_fidx = fidx;
  }
  RETURN (fsize);

  END_LOCK;
}

/*----------------------------------------------------------------------------
 * end of file
 *---------------------------------------------------------------------------*/
