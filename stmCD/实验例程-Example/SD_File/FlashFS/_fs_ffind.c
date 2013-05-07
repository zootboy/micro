/*----------------------------------------------------------------------------
 *      RL-ARM - FlashFS
 *----------------------------------------------------------------------------
 *      Name:    _FS_FFIND.C 
 *      Purpose: Low level File Find Function
 *      Rev.:    V4.05
 *----------------------------------------------------------------------------
 *      This code is part of the RealView Run-Time Library.
 *      Copyright (c) 2004-2009 KEIL - An ARM Company. All rights reserved.
 *---------------------------------------------------------------------------*/

#include "File_Config.h"

/*--------------------------- _ffind ----------------------------------------*/

BOOL _ffind (FINFO *info, IOB *fcb) {
  /* Low level file find function. Searches for the file with next file ID. */
  FALLOC fa;
  U32 bl,adr,fid,prev,name = 0;

  fid = 0xFFFF;
  for (bl = 0; bl < fcb->NumSect; bl++) {
    /* Search all allocated File Blocks for file with next fileID */
    adr = fs_adr_sig (bl, fcb);
    adr = fs_rd_sig (adr, &fa.end);
    if (fa.end != fcb->InitVal) {
      for (prev = 0; ; prev = fa.end) {
        adr = fs_rd_alloc (adr, &fa);
        if (fa.fileID < fid && fa.fileID > (info->fileID | 0x8000)) {
          fid  = fa.fileID;
          name = ((DEVCONF *)fcb->DevCfg)[bl].bStart + prev;
        }
        if (fa.end == fcb->InitVal) break;
      }
    }
  }
  if (fid != 0xFFFF) {
    /* Filename is stored 4-byte aligned. */
    name = (name + 3) & ~3;
    /* Copy name to buffer. */
    if (fcb->drive == DRV_SPI) {
      fs_spi_ReadData (name, 32, (U8 *)&info->name);
    }
    else {
      fs_ReadData (name, 32, (U8 *)&info->name);
    }
    info->fileID = fid & 0x7FFF;
    /* Currently Embedded Files do not support Time information. */
    info->time.hr  = 12;
    info->time.min = 0;
    info->time.sec = 0;
    info->time.day = 1;
    info->time.mon = 1;
    info->time.year= 1980;
    return (__TRUE);
  }
  return (__FALSE);
}

/*----------------------------------------------------------------------------
 * end of file
 *---------------------------------------------------------------------------*/
