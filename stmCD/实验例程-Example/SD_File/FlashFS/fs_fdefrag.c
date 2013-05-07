/*----------------------------------------------------------------------------
 *      RL-ARM - FlashFS
 *----------------------------------------------------------------------------
 *      Name:    FS_FDEFRAG.C 
 *      Purpose: File System Defragment Function
 *      Rev.:    V4.05
 *----------------------------------------------------------------------------
 *      This code is part of the RealView Run-Time Library.
 *      Copyright (c) 2004-2009 KEIL - An ARM Company. All rights reserved.
 *---------------------------------------------------------------------------*/

#include "File_Config.h"

static BOOL alloc_free_bl (FDBUF *fb, IOB *fcb);
static BOOL get_next_file (IOB *fcb);
static BOOL copy_file (FDBUF *fb, IOB *fcb);
static U32  read_cbuf (IOB *fcb);
static BOOL write_cbuf (FDBUF *fb, IOB *fcb, U32 len);
static BOOL get_fblock (IOB *fcb);
static void delete_file (IOB *fcb, BOOL del_temp);

#define CBUFLEN  256
static U32 cbuf[CBUFLEN/4+1];
static FALLOC alloc;

/*--------------------------- fdefrag ---------------------------------------*/

int fdefrag (const char *drive) {
  /* Re-sort FlashFS files so that used Flash pages are reduced. */
  IOB *fcb,*iop;
  int handle;
  FDBUF fwr;
  BOOL defrag_fail;
  U32 i,adr,bl,bflag;

  START_LOCK (int);

  /* Find an unused _iob structure. */
  if ((handle = fs_find_iob ()) == EOF) {
    RETURN (1);
  }
  fcb = &_iob[handle];
  /* Get the drive index. */
  fcb->drive = fs_get_drive (drive);
  if (fcb->drive == DRV_NONE && *drive == 0) {
    /* Empty string provided for a drive name. */
    fcb->drive = _DEF_DRIVE;
  }
  if (fcb->drive == DRV_MCARD) {
    /* Memory Card currently not supported. */
    RETURN (1);
  }
  /* Set drive parameters. */
  if (fs_set_params (fcb) == __FALSE) {
    RETURN (1);
  }

  /* Check if there is an opened file. */
  for (i = 0, iop = &_iob[0]; i < _NFILE; iop++, i++) {
    if (iop->drive != fcb->drive) {
      continue;
    }
    if ((iop->flags & (_IOWRT | _IOREAD))) {
      /* Error, a file is opened. */
      RETURN (1);
    }
  }

  /* Erase all invalidated Flash Blocks if any. */
  for (bl = 0; bl < fcb->NumSect; bl++) {
    adr = fs_adr_sig (bl, fcb);
    fs_rd_sig (adr, &bflag);
    if (bflag != fcb->InitVal) {
      /* Check if this Flash Block is all invalidated */
      if (fs_BlockInvalid (bl, fcb) == __TRUE) {
        fs_InitBlock (bl, fcb);
      }
    }
  }

  /* Scan all files stored to FlashFS. */
  fcb->fileID = 0;
  fwr.ftop    = 0;
  fwr.fbot    = 0;
  defrag_fail = __FALSE;
  while (get_next_file (fcb) == __TRUE) {
    if (copy_file (&fwr, fcb) == __FALSE) {
      /* Defragmentation failed, delete last temp file. */
      delete_file (fcb, __TRUE);
      defrag_fail = __TRUE;
      break;
    }
    delete_file (fcb, __FALSE);
  }

  /* Update FBlock usage signatures, and erase old pages. */
  for (bl = 0; bl < fcb->NumSect; bl++) {
    adr = fs_adr_sig (bl, fcb);
    fs_rd_sig (adr, &bflag);
    if (bflag == fcb->InitVal) {
      continue;
    }
    if ((bflag ^ BlockTEMP) == fcb->InitVal) {
      bflag = fcb->InitVal ^ BlockUSED;
      if (fs_get_freeMem (bl, fcb) == 0) {
        bflag = fcb->InitVal ^ BlockFULL;
      }
      fs_WriteBlock ((adr & ~1), &bflag, 4, fcb);
      continue;
    }
    if (defrag_fail == __FALSE) {
      fs_InitBlock (bl, fcb);
    }
  }
  if (defrag_fail == __TRUE) {
    RETURN (2);
  }
  RETURN (0);

  END_LOCK;
}


/*--------------------------- alloc_free_bl ---------------------------------*/

static BOOL alloc_free_bl (FDBUF *fb, IOB *fcb) {
  U32 bl,adr,bflag;

  /* Allocate an empty Flash Block. */
  for (bl = 0; bl < fcb->NumSect; bl++) {
    adr = fs_adr_sig (bl, fcb);
    fs_rd_sig (adr, &bflag);
    if (bflag == fcb->InitVal) {
      bflag = fcb->InitVal ^ BlockTEMP;
      fs_WriteBlock ((adr & ~1), &bflag, 4, fcb);
      fb->fblock = bl;
      fb->fbot   = 0;
      fb->ftop   = ((DEVCONF *)fcb->DevCfg)[bl].bEnd   -
                   ((DEVCONF *)fcb->DevCfg)[bl].bStart -  sizeof(FALLOC);
      return (__TRUE);
    }
  }
  return (__FALSE);
}


/*--------------------------- get_next_file ---------------------------------*/

static BOOL get_next_file (IOB *fcb) {
  FALLOC fa;
  U32 bl,adr,prev;
  U32 fid,nid;

  /* Search for file with next higher fileID. */
  fid = fcb->fileID | 0x8000;
  nid = 0xFFFF;
  for (bl = 0; bl < fcb->NumSect; bl++) {
    adr = fs_adr_sig (bl, fcb);
    adr = fs_rd_sig (adr, &fa.end);
    if (fa.end == fcb->InitVal || fa.end == (fcb->InitVal ^ BlockTEMP)) {
      /* Skip free or temp Flash Blocks. */
      continue;
    }
    for (prev = 0; ; prev = fa.end) {
      adr = fs_rd_alloc (adr, &fa);
      if (fa.fileID > fid && fa.fileID < nid) {
        nid = fa.fileID;
        /* File name block is word aligned. */
        fcb->_fblock = bl;
        fcb->_fbot   = (prev + 3) & ~3;
        fcb->_ftop   = fa.end;
        if (nid == fid+1) {
          goto x;
        }
      }
      if (fa.end == fcb->InitVal) break;
    }
  }
  if (nid == 0xFFFF) {
    /* Next file not found. */
    return (__FALSE);
  }
x:fcb->fileID = nid & 0x7FFF;
  fcb->_fidx  = 0;
  return (__TRUE);
}


/*--------------------------- copy_file -------------------------------------*/

static BOOL copy_file (FDBUF *fb, IOB *fcb) {
  U32 n,nr;

  /* Make sure that 'filename' starts on 4-byte boundary */
  fb->fbot = (fb->fbot + 3) & ~3;
  if (fb->ftop < fb->fbot + 256) {
    /* Allocate an empty Flash Block. */
    if (alloc_free_bl (fb, fcb) == __FALSE) {
      /* Error, no empty Flash Blocks left */
      return (__FALSE);
    }
  }
  /* Copy File Name first. */
  n = (fcb->_ftop - fcb->_fbot + 3) & ~3;
  if (n > CBUFLEN) {
    n = CBUFLEN;
  }
  fs_ReadBlock  (((DEVCONF *)fcb->DevCfg)[fcb->_fblock].bStart + fcb->_fbot,
                 &cbuf, n, fcb);
  fs_WriteBlock (((DEVCONF *)fcb->DevCfg)[fb->fblock].bStart + fb->fbot, 
                 &cbuf, n, fcb);

  fb->fbot += n;

  alloc.end    = fb->fbot;
  alloc.fileID = fcb->fileID | 0x8000;
  alloc.index  = 0;
  fs_WriteBlock (((DEVCONF *)fcb->DevCfg)[fb->fblock].bStart + fb->ftop,
                 &alloc, sizeof (FALLOC), fcb);
  fb->ftop  -= sizeof (FALLOC);

  /* Copy the file content. */
  fcb->_ftop = 0;
  fcb->_fbot = 0;
  fcb->_fidx = 0;
  fb->index  = 0;

  while ((nr = read_cbuf (fcb)) != 0) {
    if (write_cbuf (fb, fcb, nr) == __FALSE) {
      return (__FALSE);
    }
    if (nr < CBUFLEN) {
      break;
    }
  }

  /* Close this file, write File Allocation Information. */
  alloc.end    = fb->fbot;
  alloc.fileID = fcb->fileID;
  alloc.index  = fb->index;
  fs_WriteBlock (((DEVCONF *)fcb->DevCfg)[fb->fblock].bStart + fb->ftop, 
                 &alloc, sizeof (FALLOC), fcb);
  fb->ftop -= sizeof (FALLOC);
  return (__TRUE);
}


/*--------------------------- read_cbuf --------------------------------------*/

static U32 read_cbuf (IOB *fcb) {
  U32 len,n;

  len = 0;
  /* Read fragmented file to buffer. */
  while (1) {
    if (fcb->_ftop == fcb->_fbot) {
      if (get_fblock (fcb) == __FALSE) {
        break;
      }
    }
    n = fcb->_ftop - fcb->_fbot;
    if (n > CBUFLEN - len) {
      n = CBUFLEN - len;
    }
    fs_ReadBlock (((DEVCONF *)fcb->DevCfg)[fcb->_fblock].bStart + fcb->_fbot,
                  (U8 *)&cbuf + len, n, fcb);
    fcb->_fbot += n;
    len        += n;
    if (len >= CBUFLEN) {
      break;
    }
  }
  return (len);
}


/*--------------------------- write_cbuf -------------------------------------*/

static BOOL write_cbuf (FDBUF *fb, IOB *fcb, U32 len) {
  U32 size,n;
  S8 *pb;

  pb = (S8 *)&cbuf;
  while (len) {
    n = len;
    size = fb->ftop - fb->fbot - sizeof (FALLOC);
    if (n > size) {
      n = size;
    }
    len -= n;
    fs_WriteBlock (((DEVCONF *)fcb->DevCfg)[fb->fblock].bStart + fb->fbot, 
                   pb, n, fcb);
    fb->fbot += n;
    pb       += n;

    if ((fb->ftop - sizeof (FALLOC)) > fb->fbot) {
      /* Enough space in current Flash Block */
      continue;
    }

    /* No more free space, write File Allocation Information */
    alloc.end    = fb->fbot;
    alloc.fileID = fcb->fileID;
    alloc.index  = fb->index;
    fs_WriteBlock (((DEVCONF *)fcb->DevCfg)[fb->fblock].bStart + fb->ftop,
                   &alloc, sizeof (FALLOC), fcb);
    fb->ftop -= sizeof (FALLOC);
    fb->index++;

    /* Current Flash Block is full, allocate next one */
    if (alloc_free_bl (fb, fcb) == __FALSE) {
      /* Error, no empty Flash Blocks left */
      return (__FALSE);
    }
  }
  return (__TRUE);
}


/*--------------------------- get_fblock -------------------------------------*/

static BOOL get_fblock (IOB *fcb) {
  FALLOC fa;
  U32 i,bl,adr,prev;

  bl = fcb->_fblock;
  for (i = 0; i < fcb->NumSect; i++) {
    /* Search for file blocks identified with identification 'fileID' */
    adr = fs_adr_sig (bl, fcb);
    adr = fs_rd_sig (adr, &fa.end);
    if (fa.end == fcb->InitVal || fa.end == (fcb->InitVal ^ BlockTEMP)) {
      /* Skip free or temp Flash Blocks. */
      goto next;
    }
    for (prev = 0; ; prev = fa.end) {
      adr = fs_rd_alloc (adr, &fa);
      if (fa.fileID == fcb->fileID  &&  fa.index == fcb->_fidx) {
        /* Set Current File Block parameters */
        fcb->_fblock = bl;
        /* All file blocks are 4-byte aligned. */
        fcb->_fbot   = (prev + 3) & ~3;
        fcb->_ftop   = fa.end;
        fcb->_fidx++; 
        return (__TRUE);
      }
      if (fa.end == fcb->InitVal) break;
    }
next:if (++bl == fcb->NumSect) {
      bl = 0;
    }
  }
  return (__FALSE);
}

/*--------------------------- delete_file -----------------------------------*/

static void delete_file (IOB *fcb, BOOL del_temp) {
  /* Low level file delete function. */
  FALLOC fa;
  U32 bl,adr,invalid;

  for (bl = 0; bl < fcb->NumSect; bl++) {
    /* Search for file blocks identified with identification 'fileID' */
    adr = fs_adr_sig (bl, fcb);
    adr = fs_rd_sig (adr, &fa.end);
    if (del_temp == __FALSE) {
      if (fa.end == fcb->InitVal || fa.end == (fcb->InitVal ^ BlockTEMP)) {
        /* Skip free or temp Flash Blocks. */
        continue;
      }
    }
    else {
      if (fa.end != (fcb->InitVal ^ BlockTEMP)) {
        /* Delete a file in temp Flash Block. */
        continue;
      }
    }
    do {
      adr = fs_rd_alloc (adr, &fa);
      if ((fa.fileID & 0x7FFF) == fcb->fileID) {
        /* Clear the fileID values */
        invalid = ~fcb->InitVal;
        fs_WriteBlock ((adr & ~1) + 12, &invalid, 4, fcb);
      }
    } while (fa.end != fcb->InitVal);

    /* Check if this Flash Block is all invalidated */
    if (fs_BlockInvalid (bl, fcb) == __TRUE) {
      /* All file blocks stored in this Flash Block are invalid */
      fs_InitBlock (bl, fcb);
    }
  }
}

/*----------------------------------------------------------------------------
 * end of file
 *---------------------------------------------------------------------------*/
