/*----------------------------------------------------------------------------
 *      RL-ARM - FlashFS
 *----------------------------------------------------------------------------
 *      Name:    _FS_FLUSHBUF.C 
 *      Purpose: Low level File Flush Buffer Function
 *      Rev.:    V4.05
 *----------------------------------------------------------------------------
 *      This code is part of the RealView Run-Time Library.
 *      Copyright (c) 2004-2009 KEIL - An ARM Company. All rights reserved.
 *---------------------------------------------------------------------------*/

#include "File_Config.h"

/*--------------------------- __flushbuf ------------------------------------*/

int __flushbuf (int handle) {
  /* Low level file flush function. */
  FALLOC alloc;
  IOB *fcb;

  START_LOCK (int);

  fcb = &_iob[handle];
  if (!(fcb->flags & _IOWRT)) {
    /* File not opened for write */
    fcb->flags |= _IOERR;
    RETURN (-1);
  }
  if (fcb->drive == DRV_MCARD) {
    RETURN (0);
  }
  if (fcb->flags & _IOWALLOC) {
    /* buffer present and buffered I/O requested */
    alloc.end    = fcb->_fbot;
    alloc.fileID = fcb->fileID;
    alloc.index  = fcb->_fidx++;
    fs_WriteBlock (((DEVCONF *)fcb->DevCfg)[fcb->_fblock].bStart + fcb->_ftop,
                   &alloc, sizeof (FALLOC), fcb);
    /* Always write on 4-byte boundaries. */
    fcb->_ftop -= sizeof (FALLOC);
    fcb->_fbot = (fcb->_fbot + 3) & ~3;
    fcb->flags &= ~_IOWALLOC;
  }
  RETURN (0);

  END_LOCK;
}

/*----------------------------------------------------------------------------
 * end of file
 *---------------------------------------------------------------------------*/
