/*----------------------------------------------------------------------------
 *      RL-ARM - FlashFS
 *----------------------------------------------------------------------------
 *      Name:    FS_FCHECK.C 
 *      Purpose: File System Analyse Function
 *      Rev.:    V4.05
 *----------------------------------------------------------------------------
 *      This code is part of the RealView Run-Time Library.
 *      Copyright (c) 2004-2009 KEIL - An ARM Company. All rights reserved.
 *---------------------------------------------------------------------------*/

#include "File_Config.h"

/*--------------------------- fcheck ----------------------------------------*/

int fcheck (const char *drive) {
  /* Analyse the FlashFS and check for allocation errors. */
  FALLOC fa;
  IOB *fcb;
  int handle;
  U32 bl,adr,prev,sa;

  START_LOCK (int);

  /* Find an unused _iob structure. */
  if ((handle = fs_find_iob ()) == EOF) {
    RETURN (1);
  }
  fcb = &_iob[handle];
  /* Get the drive index. */
  fcb->drive = fs_get_drive (drive);
  if (fcb->drive == DRV_NONE && *drive == 0) {
    /* Empty string provided for a drive name. */
    fcb->drive = _DEF_DRIVE;
  }
  if (fcb->drive == DRV_MCARD) {
    /* Memory Card currently not supported. */
    RETURN (1);
  }
  /* Set drive parameters. */
  if (fs_set_params (fcb) == __FALSE) {
    RETURN (1);
  }

  for (bl = 0; bl < fcb->NumSect; bl++) {
    /* Check all File Blocks for invalid FID and check file pointers for */
    /* reasonable values in ascending order.                             */
    adr = fs_adr_sig (bl, fcb);
    adr = fs_rd_sig (adr, &fa.end);
    if (fa.end != fcb->InitVal) {
      sa = ((DEVCONF *)fcb->DevCfg)[bl].bStart;
      for (prev = 0; ; prev = fa.end) {
        adr = fs_rd_alloc (adr, &fa);
        if (fa.end == fcb->InitVal) {
          /* End of Allocation info. */
          break;
        }
        if (fa.fileID == 0x8000) {
          /* Error, not existing file ID. */
          RETURN (1);
        }
        if (fa.end < prev) {
          /* Error, not ascending allocation pointers. */
          RETURN (1);
        }
        if ((sa + fa.end) > (adr & ~1)) {
          /* Error, overlapping file allocation record. */
          RETURN (1);
        }
      }
    }
  }
  /* OK, file integrity passed. */
  RETURN (0);

  END_LOCK;
}

/*----------------------------------------------------------------------------
 * end of file
 *---------------------------------------------------------------------------*/
