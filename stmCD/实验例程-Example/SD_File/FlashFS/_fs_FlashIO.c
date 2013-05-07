/*----------------------------------------------------------------------------
 *      RL-ARM - FlashFS
 *----------------------------------------------------------------------------
 *      Name:    _FS_FLASHIO.C 
 *      Purpose: Common low level Flash File Routines
 *      Rev.:    V4.05
 *----------------------------------------------------------------------------
 *      This code is part of the RealView Run-Time Library.
 *      Copyright (c) 2004-2009 KEIL - An ARM Company. All rights reserved.
 *---------------------------------------------------------------------------*/

#include "File_Config.h"

/*----------------------------------------------------------------------------
 *  Search for free/unused File Identification Number.  
 *    Parameter:      maxID:  max ID found in Allocation Table
 *    Return Value:   fileID
 *---------------------------------------------------------------------------*/

U16 fs_get_freeID (U32 maxID, IOB *fcb) {
  FALLOC fa;
  U32 bl,fid,adr;

  maxID |= 0x8000;
  for (fid = 0x8001; fid < maxID;  ) {
    for (bl = 0; bl < fcb->NumSect; bl++) {
      adr = fs_adr_sig (bl, fcb) - 8;
      for (;;) {
        adr = fs_rd_alloc (adr, &fa);
        /* If this fileID is used, go and check next one */
        if (fa.fileID == fid) goto nextfid;
        if (fa.end == fcb->InitVal) break;
      }
    }
    return (fid & 0x7FFF);
nextfid:
    fid++;
  }
  return ((maxID + 1) & 0x7FFF);
}


/*----------------------------------------------------------------------------
 *  Get remaining free space in Flash Block.
 *    Parameter:      block:  block index
 *    Return Value:   free space in bytes
 *---------------------------------------------------------------------------*/

U32 fs_get_freeMem (U32 block, IOB *fcb) {
  FALLOC fa;
  U32 size,adr,prev;

  adr = fs_adr_sig (block, fcb) - 8;
  for (prev = 0; ; prev = fa.end) {
    adr = fs_rd_alloc (adr, &fa);
    if (fa.end == fcb->InitVal) break;
  }
  size = (adr & ~1) + 8 - ((DEVCONF *)fcb->DevCfg)[block].bStart - prev;
  if (size < 256) {
    /* This block is considered to be full. */
    return (0);
  }
  return (size);
}


/*----------------------------------------------------------------------------
 *  Check if there exist a file opened for writing in this Flash Block
 *    Parameter:      block:  block index
 *                    fcb  :  file control block
 *    Return Value:   __TRUE  - block is busy
 *                    __FALSE - block is free
 *---------------------------------------------------------------------------*/

BOOL fs_check_fwopen (U32 block, IOB *fcb) {
  U32 i;

  for (i = 0; i < _NFILE; i++) {
    if (&_iob[i] == fcb) {
      continue;
    }
    if ((_iob[i].flags & _IOWRT) && (_iob[i]._fblock == block)) {
      /* Another File is already opened for writing in this Flash Block */
      return (__TRUE);
    }
  }
  return (__FALSE);
}


/*----------------------------------------------------------------------------
 *  Set the 'fcb' top and bottom addresses of free memory in a Flash Block
 *    Parameter:      fcb: file control block
 *---------------------------------------------------------------------------*/

void fs_mark_freeMem (IOB *fcb) {
  FALLOC fa;
  U32 adr,prev;

  adr = fs_adr_sig (fcb->_fblock, fcb) - 8;
  for (prev = 0; ; prev = fa.end) {
    adr = fs_rd_alloc (adr, &fa);
    if (fa.end == fcb->InitVal) break;
  }
  /* All file blocks are 4-byte aligned. */
  fcb->_fbot = (prev + 3) & ~3;
  fcb->_ftop = (adr & ~1) + 8 - ((DEVCONF *)fcb->DevCfg)[fcb->_fblock].bStart;
}


/*----------------------------------------------------------------------------
 *  Set the 'fcb' bottom, top address and Flash Block index of opened file
 *    Parameter:      fcb: file control block with valid parameters
 *                          'fcb->fileID'  - file identification number
 *                          'fcb->_fblock' - start scanning Flash Block
 *                          'fcb->_fidx'   - file block sequence index
 *    Return Value:   __TRUE  - parameters set OK
 *                    __FALSE - error, empty/invalid file found or End Of File
 *---------------------------------------------------------------------------*/

BOOL fs_mark_fileMem (IOB *fcb) {
  FALLOC fa;
  U32 i,adr,bl,prev;

  bl = fcb->_fblock;
  for (i = 0; i < fcb->NumSect; i++) {
    /* Search for file blocks identified with identification 'fileID' */
    adr = fs_adr_sig (bl, fcb);
    adr = fs_rd_sig (adr, &fa.end);
    if (fa.end != fcb->InitVal) {
      for (prev = 0; ; prev = fa.end) {
        adr = fs_rd_alloc (adr, &fa);
        if (fa.fileID == fcb->fileID && fa.index == fcb->_fidx) {
          /* Set Current File Block parameters */ 
          fcb->_fblock = bl;
          fcb->_fbot = (prev + 3) & ~3;
          fcb->_ftop = fa.end;
          fcb->_fidx++; 
          return (__TRUE); 
        }
        if (fa.end == fcb->InitVal) break;
      }
    }
    if (++bl == fcb->NumSect) {
      bl = 0;
    }
  }
  return (__FALSE);
}


/*----------------------------------------------------------------------------
 *  Low level File Find.  
 *    Parameter:      fname:  name of the file to search for
 *                    fcb  :  file control block
 *    Return Value:   0 - file found, fcb-updated accordingly
 *                    maxID - max fileID found in File Allocation Table when
 *                            the file was not found
 *---------------------------------------------------------------------------*/

U32 fs_Find_File (const char *fname, IOB *fcb) {
  FALLOC fa;
  U8 buf[32];
  U32 bl,adr,prev,name;
  U32 fid = 0x8000;

  for (bl = 0; bl < fcb->NumSect; bl++) {
    /* Search all allocated File Blocks for a given 'fname */
    adr = fs_adr_sig (bl, fcb);
    adr = fs_rd_sig (adr, &fa.end);
    if (fa.end != fcb->InitVal) {
      for (prev = 0; ; prev = fa.end) {
        adr = fs_rd_alloc (adr, &fa);
        if (fa.fileID > 0x8000 && fa.fileID < 0xFFFF) {
          /* Filename is 4-byte aligned. */
          name = ((DEVCONF *)fcb->DevCfg)[bl].bStart + prev;
          name = (name + 3) & ~3;
          if (adr & 0x01) {
            /* Copy name for SPI Flash Drive. */
            fs_spi_ReadData (name, sizeof (buf), (U8 *)&buf);
          }
          else {
            fs_ReadData (name, sizeof (buf), (U8 *)&buf);
          }
          buf[31] = 0;
          if (fn_cmp (fname, (char *)&buf) == __TRUE) {
            /* File with 'fname' has been found */
            fcb->fileID  = fa.fileID & 0x7FFF;
            fcb->_fblock = bl;
            return (0);
          }
          /* Search for the max fileID in use */
          if (fa.fileID > fid) {
            fid = fa.fileID;
          }
        }
        if (fa.end == fcb->InitVal) break;
      }
    }
  }
  /* 'fid' is a nonzero value here */
  return (fid);
}


/*----------------------------------------------------------------------------
 *  Check if Block Full, write File Allocation Info when it is full
 *    Parameter:      fcb:  file control block
 *    Return Value:   __FALSE  - enough free space
 *                    __TRUE   - full, FAT written
 *---------------------------------------------------------------------------*/

BOOL fs_BlockFull (IOB *fcb) {
  FALLOC alloc;

  if ((fcb->_ftop - sizeof (FALLOC)) > fcb->_fbot) {
    /* Enough space in current Flash Block */
    return (__FALSE);
  }
  /* No more free space, write File Allocation Information */
  alloc.end    = fcb->_fbot;
  alloc.fileID = fcb->fileID;
  alloc.index  = fcb->_fidx++;
  fs_WriteBlock (((DEVCONF *)fcb->DevCfg)[fcb->_fblock].bStart + fcb->_ftop,
                 &alloc, sizeof (FALLOC), fcb);
  /* Mark this Flash Block as full */
  alloc.end = fcb->InitVal ^ BlockFULL;
  fs_WriteBlock (((DEVCONF *)fcb->DevCfg)[fcb->_fblock].bEnd, &alloc, 4, fcb);
  return (__TRUE);
}


/*----------------------------------------------------------------------------
 *  Allocate next available Block
 *    Parameter:      fcb:  file control block
 *    Return Value:   __TRUE  - allocated
 *                    __FALSE - error, not allocated
 *---------------------------------------------------------------------------*/

BOOL fs_AllocBlock (IOB *fcb) {
  U32 i,bl,adr,bflag;

  bl = fcb->_fblock;
  for (i = 0; i < fcb->NumSect; i++) {
    adr = fs_adr_sig (bl, fcb);
    adr = fs_rd_sig (adr, &bflag);
    if (bflag == fcb->InitVal) {
      /* Free Flash Block allocated */
      fcb->_fblock = bl;
      fcb->_fbot = 0;
      fcb->_ftop = (adr & ~1) - ((DEVCONF *)fcb->DevCfg)[bl].bStart;
      bflag ^= BlockUSED;
      fs_WriteBlock ((adr & ~1) + 8, &bflag, 4, fcb);
      return (__TRUE);
    }
    if ((bflag ^ BlockUSED) == fcb->InitVal) {
      /* Check if a file already opened for writing in this Block */
      if (fs_check_fwopen (bl, fcb) == __FALSE) {
        /* Try already used Flash Block and check for free space */
        if (fs_get_freeMem (bl, fcb) > 0) {
          fcb->_fblock = bl; 
          fs_mark_freeMem (fcb);
          return (__TRUE);
        }
        bflag = fcb->InitVal ^ BlockFULL;
        fs_WriteBlock ((adr & ~1) + 8, &bflag, 4, fcb);
      }
    }
    if (++bl == fcb->NumSect) {
      bl = 0;
    }
  }
  return (__FALSE);
}


/*----------------------------------------------------------------------------
 *  Check if all stored file data in a Flash Block is invalid
 *    Parameter:      block:  block index
 *    Return Value:   __FALSE - valid file blocks found
 *                    __TRUE  - all data is invalidated
 *---------------------------------------------------------------------------*/

BOOL fs_BlockInvalid (U32 block, IOB *fcb)  {
  FALLOC fa;
  U32 adr;
  U16 invalid;

  invalid = ~fcb->InitVal;
  /* Check if this Flash Block is all invalided */
  adr = fs_adr_sig (block, fcb) - 8;
  for (;;) {
    adr = fs_rd_alloc (adr, &fa);
    if (fa.end == fcb->InitVal) break;
    if (fa.fileID != invalid) {
      /* A valid file block found */
      return (__FALSE);
    }
  }
  return (__TRUE);
}


/*----------------------------------------------------------------------------
 *  Initialize a Flash/Ram Block
 *    Parameter: block:  block index
 *               fcb:    file control block
 *    Return Value:   __TRUE  - erase successfull
 *                    __FALSE - erase failed
 *---------------------------------------------------------------------------*/

BOOL fs_InitBlock (U32 block, IOB *fcb)  {
  U32 adr,enda;

  switch (fcb->drive) {
    case DRV_FLASH:
      adr = FlashDev[block].bStart;
      fs_EraseSector (adr);
      break;
    case DRV_SPI:
      adr = SpiDev[block].bStart;
      fs_spi_EraseSector (adr);
      break;
    case DRV_RAM:
      enda = RamDev[block].bEnd;
      for (adr = RamDev[block].bStart; adr <= enda; adr += 4) {
        MVAR (U32, adr) = 0x00;
      }
      break;
  }
  return (__TRUE);
}


/*----------------------------------------------------------------------------
 *  Write a Flash/Ram Block
 *    Parameter: adr:  write address
 *               buf:  pointer to data buffer
 *               cnt:  number of bytes to write
 *               fcb:  file control block
 *    Return Value:   __TRUE  - write successfull
 *                    __FALSE - write failed
 *---------------------------------------------------------------------------*/

BOOL fs_WriteBlock (U32 adr, void *buf, U32 cnt, IOB *fcb)  {
  int r = 1;

  /* 'adr' is always 4-byte aligned. */
  cnt = (cnt + 3) & ~3;
  switch (fcb->drive) {
    case DRV_FLASH:
      r = fs_ProgramPage (adr, cnt, buf);
      break;
    case DRV_SPI:
      r = fs_spi_ProgramPage (adr, cnt, buf);
      break;
    case DRV_RAM:
      r = fs_WriteData (adr, cnt, buf);
      break;
  }
  if (r) return (__FALSE);
  return (__TRUE);
}


/*----------------------------------------------------------------------------
 *  Read Block from Flash Memory
 *    Parameter:      adr:  block start address
 *                    buf:  pointer to data buffer
 *                    cnt:  number of words to read
 *    Return Value:   0 - read OK
 *                    1 - read failed
 *---------------------------------------------------------------------------*/

BOOL fs_ReadBlock (U32 adr, void *buf, U32 cnt, IOB *fcb)  {

  /* Both 'adr' and 'buf' may be unaligned. */
  if (fcb->drive == DRV_SPI) {
    /* Read from SPI Flash. */
    fs_spi_ReadData (adr, cnt, buf);
    return (__TRUE);
  }

  /* Read from RAM or Parallel Flash */
  fs_ReadData (adr, cnt, buf);
  return (__TRUE);
}


/*----------------------------------------------------------------------------
 *  Get address of the Signature word from allocation area
 *    Parameter:      bl:   Flash Block (=sector) index
 *                    fcb:  File Control Block
 *    Return Value:   adr:  of Signature Word
 *---------------------------------------------------------------------------*/

U32 fs_adr_sig (U32 bl, IOB *fcb) {
  U32 adr;

  adr = (U32)((DEVCONF *)fcb->DevCfg)[bl].bEnd;
  if (fcb->drive == DRV_SPI) {
    adr |= 0x01;
  }
  return (adr);
}

/*----------------------------------------------------------------------------
 *  Read File Allocation Record
 *    Parameter:      adr:  data address 
 *                          (adr is always 4-byte aligned,
 *                           bit 0 is a flag for SPI access)
 *                    fa:   pointer to Allocation Record
 *    Return Value:   adr:  of the next Allocation Record
 *---------------------------------------------------------------------------*/

U32 fs_rd_alloc (U32 adr, FALLOC *fa) {
  U32 *pa;

  if (adr & 0x01) {
    /* SPI Flash access. */
    fs_spi_ReadData ((adr & ~1), 8, (U8 *)fa);
  }
  else {
    /* Embedded Flash/RAM access. */
    pa = (U32 *)fa;
    pa[0] = MVAR (U32, adr);
    pa[1] = MVAR (U32, adr+4);
  }
  return (adr - 8);
}

/*----------------------------------------------------------------------------
 *  Read Block Signature (=usage)
 *    Parameter:      adr:  signature address
 *                          (adr is always 4-byte aligned,
 *                           bit 0 is a flag for SPI access)
 *                    sig:  return sig value
 *    Return Value:   adr:  of the first Allocation Record
 *---------------------------------------------------------------------------*/

U32 fs_rd_sig (U32 adr, U32 *sig) {

  if (adr & 0x01) {
    /* SPI Flash access. */
    fs_spi_ReadData ((adr & ~1), 4, (U8 *)sig);
  }
  else {
    /* Embedded Flash/RAM access. */
    *sig = MVAR (U32, adr);
  }
  return (adr - 8);
}

/*----------------------------------------------------------------------------
 * end of file
 *---------------------------------------------------------------------------*/
