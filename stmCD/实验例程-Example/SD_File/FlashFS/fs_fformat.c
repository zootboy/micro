/*----------------------------------------------------------------------------
 *      RL-ARM - FlashFS
 *----------------------------------------------------------------------------
 *      Name:    FS_FFORMAT.C 
 *      Purpose: File System Format Function
 *      Rev.:    V4.05
 *----------------------------------------------------------------------------
 *      This code is part of the RealView Run-Time Library.
 *      Copyright (c) 2004-2009 KEIL - An ARM Company. All rights reserved.
 *---------------------------------------------------------------------------*/

#include "File_Config.h"

/*--------------------------- fformat ---------------------------------------*/

int fformat (const char *drive) {
  /* Format the FlashFS storage media. This function call is required  */
  /* before first use of the FlashFS to initialize the storage device. */
  IOB *fcb,*iop;
  int handle;
  U32 i;

  START_LOCK (int);

  /* Find an unused _iob structure. */
  if ((handle = fs_find_iob ()) == EOF) {
    RETURN (1);
  }
  fcb = &_iob[handle];
  /* Get the drive index. */
  fcb->drive = fs_get_drive (drive);
  if (fcb->drive != DRV_NONE) {
    /* Skip drive letter 'X:' */
    drive += 2;
  }
  else {
    /* Empty string or label provided. */
    fcb->drive = _DEF_DRIVE;
  }
  if (fcb->drive == DRV_MCARD) {
    /* Format a Flash Card. */
    if (fat_format (drive) == __TRUE) {
      RETURN (0);
    }
    /* FAT formatting error. */
    RETURN (1);
  }
  /* Set drive parameters. */
  if (fs_set_params (fcb) == __FALSE) {
    RETURN (1);
  }

  /* Reset any opened file handles for this drive */
  for (i = 0, iop = &_iob[0]; i < _NFILE; i++, iop++) {
    if (iop->drive != fcb->drive) {
      continue;
    }
    if (iop->flags & (_IOREAD|_IOWRT)) {
      iop->flags  = 0;
      iop->fileID = 0;
    }
  }
  for (i = 0; i < fcb->NumSect; i++) {
    if (fs_InitBlock (i, fcb) == __FALSE) {
      /* Error, return nonzero value. */
      RETURN (1);
    }
  }
  RETURN (0);

  END_LOCK;
}

/*----------------------------------------------------------------------------
 * end of file
 *---------------------------------------------------------------------------*/
