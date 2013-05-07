/*----------------------------------------------------------------------------
 *      RL-ARM - FlashFS
 *----------------------------------------------------------------------------
 *      Name:    FS_FANALYSE.C 
 *      Purpose: File System Analyse Function
 *      Rev.:    V4.05
 *----------------------------------------------------------------------------
 *      This code is part of the RealView Run-Time Library.
 *      Copyright (c) 2004-2009 KEIL - An ARM Company. All rights reserved.
 *---------------------------------------------------------------------------*/

#include "File_Config.h"

/*--------------------------- fanalyse --------------------------------------*/

int fanalyse (const char *drive) {
  /* Analyse the FlashFS and check for file defragmentation. */
  DEVCONF *pd;
  FALLOC fa;
  IOB *fcb;
  int handle;
  U32 total,inval;
  U32 i,adr,prev;

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
    RETURN (0);
  }
  /* Set drive parameters. */
  if (fs_set_params (fcb) == __FALSE) {
    RETURN (0);
  }

  /* Calculate the total size of flash device. */
  total = 0;
  pd = (DEVCONF *)fcb->DevCfg;
  for (i = 0; i < fcb->NumSect; i++, pd++) {
    total += (pd->bEnd - pd->bStart);
  }

  /* Calculate the total size of invalidated blocks. */
  inval = 0;
  for (i = 0; i < fcb->NumSect; i++) {
    /* Search for invalidated file blocks. */
    adr = fs_adr_sig (i, fcb);
    adr = fs_rd_sig (adr, &fa.end);
    if (fa.end != fcb->InitVal) {
      for (prev = 0; ; prev = fa.end) {
        adr = fs_rd_alloc (adr, &fa);
        if (fa.fileID == (U16)(~fcb->InitVal)) {
          /* Add invalidated block size. */
          inval += (fa.end - prev);
        }
        if (fa.end == fcb->InitVal) break;
      }
    }
  }
  total >>= 8;
  /* Return factor range 0..255 */
  RETURN (inval/total);

  END_LOCK;
}

/*----------------------------------------------------------------------------
 * end of file
 *---------------------------------------------------------------------------*/
