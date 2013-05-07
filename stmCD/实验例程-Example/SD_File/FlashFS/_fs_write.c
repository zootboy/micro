/*----------------------------------------------------------------------------
 *      RL-ARM - FlashFS
 *----------------------------------------------------------------------------
 *      Name:    _FS_WRITE.C 
 *      Purpose: Low level File Write Block Function
 *      Rev.:    V4.05
 *----------------------------------------------------------------------------
 *      This code is part of the RealView Run-Time Library.
 *      Copyright (c) 2004-2009 KEIL - An ARM Company. All rights reserved.
 *---------------------------------------------------------------------------*/

#include "File_Config.h"

/*--------------------------- __write ---------------------------------------*/

int __write (int handle, const U8 *buf, U32 len) {
  /* Low level file write function. */
  FALLOC alloc;
  IOB *fcb;
  BOOL wralloc;
  U32 size;

  START_LOCK (int);

  if (buf == NULL) {
    /* Invalid buffer, return error. */
    RETURN (-1);
  }
  fcb = &_iob[handle];

  if (fcb->drive == DRV_MCARD) {
    /* Write data to Flash Memory Card. */
    if (fat_write (fcb, buf, len) == __FALSE) {
      /* Error, data not written to file. */
      RETURN (-1);
    }
    RETURN (0);
  }

  wralloc = __FALSE;
  if (len & 3) {
    wralloc = __TRUE;
  }
  while (len) {
    size = fcb->_ftop - fcb->_fbot - sizeof (FALLOC);
    if (size > len) {
      size = len;
    }
    len -= size;
    fs_WriteBlock (((DEVCONF *)fcb->DevCfg)[fcb->_fblock].bStart + fcb->_fbot,
                   (void *)buf, size, fcb);
    buf += size;
    fcb->_fbot += size;

    if (fs_BlockFull (fcb) == __TRUE) {
      /* Current Flash Block is full, allocate next one */
      if (fs_AllocBlock (fcb) == __FALSE) {
        RETURN (-1);
      }
      /* Do not write alloc record for empty segment. */
      if (len == 0) {
        goto ex;
      }
    }
  }
  if (wralloc == __FALSE) {
    /* Set flag 'Write Allocation Requested'. */
    fcb->flags |= _IOWALLOC;
  }
  else {
    /* If buffer is not full, write also allocation record. */
    alloc.end    = fcb->_fbot;
    alloc.fileID = fcb->fileID;
    alloc.index  = fcb->_fidx++;
    fs_WriteBlock (((DEVCONF *)fcb->DevCfg)[fcb->_fblock].bStart + fcb->_ftop,
                   &alloc, sizeof (FALLOC), fcb);
    /* Always write on 4-byte boundaries. */
    fcb->_ftop -= sizeof (FALLOC);
    fcb->_fbot = (fcb->_fbot + 3) & ~3;
ex: fcb->flags &= ~_IOWALLOC;
  }
  RETURN (0);

  END_LOCK;
}

/*----------------------------------------------------------------------------
 * end of file
 *---------------------------------------------------------------------------*/
