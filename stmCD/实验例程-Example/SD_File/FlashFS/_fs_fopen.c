/*----------------------------------------------------------------------------
 *      RL-ARM - FlashFS
 *----------------------------------------------------------------------------
 *      Name:    _FS_FOPEN.C 
 *      Purpose: Low level File Open Function
 *      Rev.:    V4.05
 *----------------------------------------------------------------------------
 *      This code is part of the RealView Run-Time Library.
 *      Copyright (c) 2004-2009 KEIL - An ARM Company. All rights reserved.
 *---------------------------------------------------------------------------*/

#include <stdio.h>
#include <rt_sys.h>
#include <rt_misc.h>
#include "File_Config.h"

/*--------------------------- __fopen ---------------------------------------*/

int __fopen (const char *fname, int openmode) {
  /* Low level file open function. */
  U32 i,fid;
  int handle;
  IOB *fcb;

  START_LOCK (int);

  /* Find unused _iob[] structure. */
  if ((handle = fs_find_iob ()) == EOF) {
    /* Cannot find any unused _iob[] structure */
    RETURN (-1);
  }

  fcb = &_iob[handle];
  fcb->drive = fs_get_drive (fname);
  if (fcb->drive != DRV_NONE) {
    /* Skip drive letter 'X:' */
    fname += 2;
  }
  else {
    fcb->drive = _DEF_DRIVE;
  }

  if (openmode & OPEN_PLUS) {
    /* File mode "rw" is currently not supported. */
    goto err;
  }
  fcb->flags = (openmode & (OPEN_W | OPEN_A)) ? _IOWRT : _IOREAD;
  if (openmode & OPEN_A) {
    fcb->flags |= _IOAPPEND;
  }

  if (fcb->drive == DRV_MCARD) {
    /* Open a file on Flash Memory Card. */
    fid = (fat_find_file (fname, fcb) == __TRUE) ? 0 : 1;
  }
  else {
    /* Open a file on Embedded Flash/RAM device. */
    if (fs_set_params (fcb) == __FALSE) {
      goto err;
    }
    fcb->_fidx = 0;
    fid = fs_Find_File (fname, fcb);
  }
  if (fid == 0) {
    /* File with a given 'fname' has been found */
    for (i = 0; i < _NFILE; i++) {
      if (i == handle) {
        /* Skip own file handle. */
        continue;
      }
      if (!(_iob[i].flags & (_IOREAD|_IOWRT))) {
        /* File closed. */
        continue;
      }
      if (_iob[i].drive != fcb->drive) {
        /* File opened on different drives. */
        continue;
      }
      if (_iob[i].fileID != fcb->fileID) {
        /* Different file IDs. */
        continue;
      }
      if ((_iob[i].drive == DRV_MCARD) &&
         (_iob[i]._currDatClus != fcb->_currDatClus)) {
        /* Different starting clusters for SD card. */
        continue;
      }
      /* This file is opened. */
      if ((_iob[i].flags & _IOWRT) || (fcb->flags & _IOWRT)) {
        /* Only multiple fopen for read is allowed. */
        goto err;
      }
    }
    if (fcb->flags & _IOAPPEND) {
      /* Append mode, done here, block appended by _setfpos(). */
      fcb->fsize  = __getfsize (fcb, __TRUE);
      RETURN (handle);
    }

    if (fcb->drive == DRV_MCARD) {
      /* Open a file on Flash Memory Card. */
      if (fcb->flags & _IOWRT) {
        fat_delete (fname, fcb);
        goto mc;
      }
    }
    else {
      /* Open a file on embedded Flash/RAM Device. */
      if (fcb->flags & _IOWRT) {
        _fdelete (fcb);
        goto fd;
      }
      /* Open also 0-size file for reading. */
      fcb->_ftop = fcb->_fbot;
    }
    RETURN (handle);
  }
  /* File not found */
  if (fcb->flags & _IOREAD) {
err:fcb->flags = 0;
    RETURN (-1);
  }

  if (fcb->drive == DRV_MCARD) {
mc: if (fat_create (fname, fcb) == __FALSE) {
      goto err;
    }
  }
  else {
    /* The max. 'fid' found in previous 'fs_Find_File' is here. */
    fcb->fileID = fs_get_freeID (fid, fcb);
fd: if (_fcreate (fname, fcb) != 0) {
      goto err;
    }
  }
  RETURN (handle);

  END_LOCK;
}

/*----------------------------------------------------------------------------
 * end of file
 *---------------------------------------------------------------------------*/

