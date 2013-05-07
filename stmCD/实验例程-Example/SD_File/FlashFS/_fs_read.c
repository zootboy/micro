/*----------------------------------------------------------------------------
 *      RL-ARM - FlashFS
 *----------------------------------------------------------------------------
 *      Name:    _FS_READ.C 
 *      Purpose: Low level File Read Block Function
 *      Rev.:    V4.05
 *----------------------------------------------------------------------------
 *      This code is part of the RealView Run-Time Library.
 *      Copyright (c) 2004-2009 KEIL - An ARM Company. All rights reserved.
 *---------------------------------------------------------------------------*/

#include "File_Config.h"

/*--------------------------- __read ----------------------------------------*/

int __read (int handle, U8 *buf, U32 len) {
  /* Low level file read function */
  U32 size,rlen,nr;
  IOB *fcb;

  START_LOCK (int);

  if (buf == NULL) {
    /* Invalid buffer, return error. */
    RETURN (-1);
  }
  fcb = &_iob[handle];

  if (fcb->drive == DRV_MCARD) {
    /* Read data from Flash Memory Card. */
    rlen = fat_read (fcb, buf, len);
    /* Return number of bytes NOT read. */
    if (rlen == 0) {
      /* No data read, must be End of File.     */
      /* Note: Early End of File does not work for fseek(). */
      RETURN (0x80000000 | len);
    }
    /* Return number of bytes NOT read. */
    RETURN (len - rlen);
  }

  for (nr = 0; nr < len;  ) {
    if (fcb->_ftop == fcb->_fbot) {
      if (fs_mark_fileMem (fcb) == __FALSE) {
        /* Invalid File or End Of File found */
        if (nr == 0) {
          /* Early End of File does not work for fseek(). */
          RETURN (0x80000000 | len);
        }
        RETURN (len - nr);
      }
    }
    rlen = len - nr;
    size = fcb->_ftop - fcb->_fbot;
    if (size < rlen) {
      rlen = size;
    }

    fs_ReadBlock (((DEVCONF *)fcb->DevCfg)[fcb->_fblock].bStart + fcb->_fbot,
                  &buf[nr], rlen, fcb);
    fcb->_fbot += rlen;
    nr         += rlen;
  }
  /* Return number of bytes NOT read. */
  RETURN (0);

  END_LOCK;
}

/*----------------------------------------------------------------------------
 * end of file
 *---------------------------------------------------------------------------*/
