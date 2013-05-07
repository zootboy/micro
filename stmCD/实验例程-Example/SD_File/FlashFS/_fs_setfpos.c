/*----------------------------------------------------------------------------
 *      RL-ARM - FlashFS
 *----------------------------------------------------------------------------
 *      Name:    _FS_SETFPOS.C 
 *      Purpose: Low level Set File Position Indicator Function
 *      Rev.:    V4.05
 *----------------------------------------------------------------------------
 *      This code is part of the RealView Run-Time Library.
 *      Copyright (c) 2004-2009 KEIL - An ARM Company. All rights reserved.
 *---------------------------------------------------------------------------*/

#include "File_Config.h"

/*--------------------------- __setfpos -------------------------------------*/

int __setfpos (int handle, U32 pos) {
  /* Low level Set file position pointer function. */
  FALLOC fa;
  IOB *fcb;
  U32 bl,adr,fidx,prev;
  U32 i,fpos;

  START_LOCK (int);

  fcb  = &_iob[handle];
  if (fcb->drive == DRV_MCARD) {
    if (fat_set_fpos (fcb, pos) == __TRUE) {
      /* File Position indicator changed. */
      RETURN (0);
    }
    RETURN (-1);
  }
  if (fcb->flags & _IOWRT) {
    if ((fcb->flags & _IOAPPEND) && (fcb->fsize == pos)) {
      if (fs_AllocBlock (fcb) == __TRUE) {
        RETURN (0);
      }
    }
    RETURN (-1);
  }

  fidx = 0;
  fpos = 0;
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
          prev = (prev + 3) & ~3;
          fidx++; 
          if (fpos + (fa.end - prev) < pos) {
            /* Go and try next File Block */
            fpos += (fa.end - prev);
            goto nextbl; 
          }

          /* OK, the right File Block Index is found */
          fcb->_fblock = bl;
          fcb->_fidx = fidx;
          /* File opened for read. */
          fcb->_fbot = prev + pos - fpos;
          fcb->_ftop = fa.end;
          RETURN (0);
        }
        if (fa.end == fcb->InitVal) break;
      }
    }
    if (++bl == fcb->NumSect) {
      bl = 0;
    }
  }
  RETURN (-1);

  END_LOCK;
}

/*----------------------------------------------------------------------------
 * end of file
 *---------------------------------------------------------------------------*/
