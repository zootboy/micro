/*----------------------------------------------------------------------------
 *      RL-ARM - FlashFS
 *----------------------------------------------------------------------------
 *      Name:    FS_FDELETE.C 
 *      Purpose: File Delete Function
 *      Rev.:    V4.05
 *----------------------------------------------------------------------------
 *      This code is part of the RealView Run-Time Library.
 *      Copyright (c) 2004-2009 KEIL - An ARM Company. All rights reserved.
 *---------------------------------------------------------------------------*/

#include "File_Config.h"

/*--------------------------- fdelete ---------------------------------------*/

int fdelete (const char *filename) {
  /* Delete a file with name 'filename'. */
  IOB *fcb;
  int handle;

  START_LOCK (int);

  /* Find an unused _iob structure. */
  if ((handle = fs_find_iob ()) == EOF) {
    RETURN (1);
  }
  fcb = &_iob[handle];
  /* Get the drive index. */
  fcb->drive = fs_get_drive (filename);
  if (fcb->drive != DRV_NONE) {
    /* Skip drive letter 'X:' */
    filename += 2;
  }
  else {
    fcb->drive = _DEF_DRIVE;
  }
  if (fcb->drive == DRV_MCARD) {
    /* Delete a file on Flash Memory Card. */
    if (fat_delete (filename, fcb) == __TRUE) {
      RETURN (0);
    }
    /* File not found error */
    RETURN (1);
  }
  /* Set drive parameters. */
  if (fs_set_params (fcb) == __FALSE) {
    RETURN (1);
  }

  if (fs_Find_File (filename, fcb) == 0) {
    /* File with 'filename' found, delete it. */
    RETURN (_fdelete (fcb));
  }
  /* File not found error */
  RETURN (1);

  END_LOCK;
}

/*----------------------------------------------------------------------------
 * end of file
 *---------------------------------------------------------------------------*/
