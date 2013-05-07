/*----------------------------------------------------------------------------
 *      RL-ARM - FlashFS
 *----------------------------------------------------------------------------
 *      Name:    FS_FFREE.C 
 *      Purpose: Get File System Free Space Function
 *      Rev.:    V4.05
 *----------------------------------------------------------------------------
 *      This code is part of the RealView Run-Time Library.
 *      Copyright (c) 2004-2009 KEIL - An ARM Company. All rights reserved.
 *---------------------------------------------------------------------------*/

#include "File_Config.h"

/*--------------------------- ffree -----------------------------------------*/

U64 ffree (const char *drive) {
  /* Find a free space in the Flash File System. */
  IOB *fcb;
  int handle;
  U32 bl, free = 0;

  START_LOCK (U32);

  /* Find an unused _iob structure. */
  if ((handle = fs_find_iob ()) == EOF) {
    RETURN (0);
  }
  fcb = &_iob[handle];
  /* Get the drive index. */
  fcb->drive = fs_get_drive (drive);
  if (fcb->drive == DRV_NONE && *drive == 0) {
    /* Empty string provided for a drive name. */
    fcb->drive = _DEF_DRIVE;
  }
  if (fcb->drive == DRV_NONE) {
    /* Invalid drive letter specified. */
    RETURN (0);
  }
  if (fcb->drive == DRV_MCARD) {
    /* Calculate Free Memory for a Flash Card. */
    free = fat_free ();
    RETURN (free);
  }
  /* Set drive parameters. */
  if (fs_set_params (fcb) == __FALSE) {
    RETURN (0);
  }

  for (bl = 0; bl < fcb->NumSect; bl++) {
    /* Search all File Blocks for free space. */
    free += fs_get_freeMem (bl, fcb);
  }
  RETURN (free);

  END_LOCK;
}

/*----------------------------------------------------------------------------
 * end of file
 *---------------------------------------------------------------------------*/
