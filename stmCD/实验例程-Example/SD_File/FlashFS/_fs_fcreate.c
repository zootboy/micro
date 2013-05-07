/*----------------------------------------------------------------------------
 *      RL-ARM - FlashFS
 *----------------------------------------------------------------------------
 *      Name:    _FS_FCREATE.C 
 *      Purpose: Low level File Create Function
 *      Rev.:    V4.05
 *----------------------------------------------------------------------------
 *      This code is part of the RealView Run-Time Library.
 *      Copyright (c) 2004-2009 KEIL - An ARM Company. All rights reserved.
 *---------------------------------------------------------------------------*/

#include <stdio.h>
#include <rt_sys.h>
#include <rt_misc.h>
#include "File_Config.h"

/*--------------------------- _fcreate --------------------------------------*/

int _fcreate (const char *fname, IOB *fcb) {
  /* Low level file create function. This function creates a file */
  /* with name 'fname' for writing in the Flash File System.      */
  FALLOC fa;
  U32 i,bl,adr;
  U8  fn[32];

  bl = 0;
  for (i = 0; i < fcb->NumSect; i++) {
    adr = fs_adr_sig (i, fcb);
    adr = fs_rd_sig (adr, &fa.end);
    if ((fa.end ^ BlockUSED) == fcb->InitVal) {
      /* Check if a file already opened for writing in this Block */
      if (fs_check_fwopen (i, fcb) == __TRUE) {
        continue;
      } 
      /* Try already used Flash Block and check for free space */
      if (fs_get_freeMem (i, fcb) == 0) {
        fa.end = fcb->InitVal ^ BlockFULL;
        fs_WriteBlock (((DEVCONF *)fcb->DevCfg)[i].bEnd, &fa.end, 4, fcb);
        continue;
      }
      bl = i + 1;
      break;
    }
    if (fa.end == fcb->InitVal) {
      if (bl == 0) {
        bl = i + 1;
      }
    }
  } 
  if (bl == 0) {
    /* No Flash Blocks free. */
    return (1);
  }
  /* Write a filename to empty space in Flash Block */
  fcb->_fblock = bl - 1;
  fs_mark_freeMem (fcb);

  /* Write Block Signature (=usage) value. */
  adr = fs_adr_sig (fcb->_fblock, fcb);
  fs_rd_sig (adr, &fa.end);
  if (fa.end == fcb->InitVal) {
    fa.end = fcb->InitVal ^ BlockUSED;
    fs_WriteBlock ((adr & ~1), &fa.end, 4, fcb);
  }

  /* 'fname' must be stored 0-terminated */
  for (i = 0; fname[i] && i < 31; i++) {
    fn[i] = fname[i];
  }
  fn[i] = 0;
  i = (i + 4) & ~3;

  /* Make sure that 'fname' starts 4-byte aligned */
  fs_WriteBlock (((DEVCONF *)fcb->DevCfg)[fcb->_fblock].bStart + fcb->_fbot,
                 fn, i, fcb);
  fcb->_fbot += i;

  /* Not always correct, but 'fname' is 0-terminated anyway. */
  fa.end    = fcb->_fbot;
  fa.fileID = fcb->fileID | 0x8000;
  /* 'index' can be used later for file attributes like ReadOnly etc. */
  fa.index  = 0;
  fs_WriteBlock (((DEVCONF *)fcb->DevCfg)[fcb->_fblock].bStart + fcb->_ftop,
                  &fa, sizeof (FALLOC), fcb);
  fcb->_ftop -= sizeof (FALLOC);
  return (0);
}

/*----------------------------------------------------------------------------
 * end of file
 *---------------------------------------------------------------------------*/
