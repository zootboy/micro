/*----------------------------------------------------------------------------
 *      RL-ARM - FlashFS
 *----------------------------------------------------------------------------
 *      Name:    FS_FRENAME.C 
 *      Purpose: File Rename Function
 *      Rev.:    V4.05
 *----------------------------------------------------------------------------
 *      This code is part of the RealView Run-Time Library.
 *      Copyright (c) 2004-2009 KEIL - An ARM Company. All rights reserved.
 *---------------------------------------------------------------------------*/

#include <string.h>                   /* string and memory functions         */
#include "File_Config.h"

/*--------------------------- frename ---------------------------------------*/

int frename (const char *oldname, const char *newname) {
  /* Rename a file from 'oldname' to 'newname'. */
  IOB *fcb;
  int handle;
  int drv2;
  int i;
  char newname_w_path[81];

  START_LOCK (int);

  /* Find an unused _iob structure. */
  if ((handle = fs_find_iob ()) == EOF) {
    RETURN (1);
  }
  fcb = &_iob[handle];
  fcb->drive = fs_get_drive (oldname);
  if (fcb->drive != DRV_NONE) {
    /* Skip drive letter 'X:' */
    oldname += 2;
  }
  else {
    fcb->drive = _DEF_DRIVE;
  }
  drv2 = fs_get_drive (newname);
  if (drv2 != DRV_NONE) {
    newname += 2;
    if (drv2 != fcb->drive) {
      /* If provided, both drives must be the same. */
      RETURN (1);
    }
  }
  if (fcb->drive == DRV_MCARD) {
    /* Find path part of old name. */
    for (i = (strlen(oldname) - 1); i >= 0; i --) {
      if (oldname[i] == '\\') {
        break;
      }
    }
    if (i) {
      /* If path exists, add path to new name to search if it exists. */
      memcpy(newname_w_path, oldname, i + 1);
      newname_w_path[i+1] = 0;
      strcat(newname_w_path, newname);
    }
    else {
      memcpy(newname_w_path, newname, strlen(newname));
    }

    /* Rename a file located on Flash Memory Card. */
    if (fat_find_file (newname_w_path, fcb) == __TRUE) {
      /* File with 'newname' already exists */
      RETURN (1);
    }
    if (fat_rename (oldname, newname, fcb) == __TRUE) {
      RETURN (0);
    }
    RETURN (1);
  }
  /* Set drive parameters. */
  if (fs_set_params (fcb) == __FALSE) {
    RETURN (1);
  }

  if (fs_Find_File (newname, fcb) == 0) {
    /* File with 'newname' already exists */
    RETURN (1);
  }
  if (fs_Find_File (oldname, fcb) == 0) {
    RETURN (_frename (newname, fcb));
  }
  /* File with 'oldname' not found */
  RETURN (1);

  END_LOCK;
}

/*----------------------------------------------------------------------------
 * end of file
 *---------------------------------------------------------------------------*/
