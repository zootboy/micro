/*----------------------------------------------------------------------------
 *      RL-ARM - FlashFS
 *----------------------------------------------------------------------------
 *      Name:    FS_FAT.C 
 *      Purpose: FAT File System Class Implementation
 *      Rev.:    V4.05
 *----------------------------------------------------------------------------
 *      This code is part of the RealView Run-Time Library.
 *      Copyright (c) 2004-2009 KEIL - An ARM Company. All rights reserved.
 *---------------------------------------------------------------------------*/

#include "File_Config.h"
#include <string.h>

#define INVAL_SECT  0xFFFFFFFF

#define EX(f,r) if ((f) == __FALSE) return (r);

/* Possible "search_for_name" function actions definitions */
#define ACT_NONE    0x00
#define ACT_KEEPFCB 0x01

/* Local Constants */
static const DEVPAR IniDevCfg[10] = {
/*  FatType  SecClus  SecClus32 NumHeads NumSect NumCyl BootRecSec */
  { FS_FAT12,    16,       0,        2,    16,     512,    65 },   /*    8 MB */
  { FS_FAT12,    16,       0,        2,    16,    1024,    65 },   /*   16 MB */
  { FS_FAT12,    32,       0,        2,    32,    1024,    65 },   /*   32 MB */
  { FS_FAT12,    32,       0,        4,    32,    1024,    65 },   /*   64 MB */
  { FS_FAT16,    16,       0,        8,    32,    1024,    65 },   /*  128 MB */
  { FS_FAT16,    16,       4,       16,    32,    1024,   129 },   /*  256 MB */
  { FS_FAT16,    32,       8,       32,    32,    1024,   129 },   /*  512 MB */
  { FS_FAT16,    32,      16,       64,    32,    1024,   257 },   /*    1 GB */
  { FS_FAT16,    64,      32,      256,    32,     512,   257 },   /*    2 GB */
  { FS_FAT32,    64,      64,      256,    32,    1024,   257 }};  /*    4 GB */
/* Parameters in this table are optimized for SD/MMC memory cards.            */
/* Optimal file system is FAT12/FAT16 with Cluster sizes 8k, 16k, 32k.        */
/* Cluster 2 shall be block aligned (32K aligned)                             */

static const U8 ChIndex[13] = { 1, 3, 5, 7, 9, 14, 16, 18, 20, 22, 24, 28, 30 };

/* Local Variables */
static FCACHE  fat;
static DCACHE  ca;
static FATINFO mmc;
static U32 free_clus;
static U32 top_clus;
static U32 startDirClus;
static U32 firstEntClus;
static U16 firstEntOffs;
static U8  numOfEntries;
static BIT in_root_1x;
static BIT warm_restart;

static char name_buf[260];              /* Name buffer */

/* Local Function Prototypes */
static int  init_dev          (void);
static BOOL write_mbr         (U32 iSz);
static BOOL write_br          (U32 sernum);
static BOOL wipe_disk         (U32 dsize);
static BOOL fat_find_dir      (const char *fn, IOB *fcb, U8 create);
static BOOL write_label       (const char *label);
static BOOL set_next_clus     (U32 *ptr_clus);
static BOOL get_free_clus     (U32 *ptr_clus);
static BOOL clus_in_use       (U32 clus);
static BOOL clear_clus        (U32 clus);
static BOOL write_fat_link    (U32 clus, U32 next_clus);
static BOOL unlink_clus_chain (U32 clus);
static BOOL alloc_new_clus    (U32 *ptr_clus, U8 wr_fat_link);
static U32  count_free_clus   (void);
static U32  clus_to_sect      (U32 clus);
static U32  get_fat_sect      (U32 clus);
static BOOL read_sector       (U32 sect);
static BOOL write_sector      (U32 sect);
static BOOL read_cache        (U32 sect, U32 cnt);
static BOOL write_cache       (U32 sect);
static BOOL cache_fat         (U32 sect);
static BOOL is_EOC            (U32 clus);
static U32  get_EOC           (void);
static BOOL get_mbrec         (void);
static BOOL get_bootrec       (void);
static BOOL is_fat_valid      (void);
static U16  get_time          (void);
static U16  get_date          (void);
static void set_time_date     (FINFO *info, FILEREC *frec);
static BOOL cvt_fatname       (const char *fn, char *en);
static BOOL check_lfn         (const char *fn);
static U8   val_char          (U8 ch);
static BOOL val_char_sn       (U8 ch);
//static BOOL val_char_ln     (U8 ch);
static U8   val_char_lab      (U8 ch);
static U16  get_u16           (U8 *nr);
static void set_u16           (U8 *nr, U16 val);
static U32  get_u32           (U8 *nr);
static void set_u32           (U8 *nr, U32 val);
static BOOL get_dir_name      (const char *fn, char *dn, unsigned int *sz);
static BOOL get_nt_name       (const char *fn, char *sn, int num);
static U32  get_dir_sect      (U32 clus);
static BOOL search_for_name   (const char *name, IOB *fcb, U8 type, U8 keep_fcb);
static BOOL find_name         (const char *name, IOB *fcb, U8 type);
static BOOL check_name        (const char *name, IOB *fcb, U8 type);
static BOOL alloc_name        (const char *name, IOB *fcb);
static BOOL get_next_info     (FINFO *info, IOB *fcb);
static BOOL chk_dir_empty     (IOB *fcb);
static BOOL read_last_entry   (IOB *fcb, FILEREC *filerec);
static BOOL write_last_entry  (IOB *fcb, FILEREC *filerec);
static BOOL write_entries     (const char *name, IOB *fcb, U8 type, FILEREC *last_entry);
static BOOL delete_entries    (IOB *fcb, U8 action);
static BOOL rename_entries    (const char *new_name, IOB *fcb, U8 type);
static BOOL write_dot_entries (IOB *fcb);
static U8   lfn_calc_chksum   (U8 *fn);
static void lfn_copy_name     (U8 *lfn, char *fn);
static BOOL lfn_cmp_name      (U8 *lfn, char *fn);
static BOOL sfn_cmp_name      (U8 *sfn, char *fn);
static void lfn_copy_info     (S8 *fn, U8 *lfn);
static BOOL chk_param         (const char *par, const char *sp);

/*--------------------------- fat_init --------------------------------------*/

int fat_init (void) {
  /* Initialize FAT File System driver. */

  /* Initialize Flash Card interface. */
  if (mmc_init () == __FALSE) {
    /* Failed to Initialize or No Card error. */
    return (1);
  }
  /* Initialize FAT file system. */
  return (init_dev ());
}


/*--------------------------- init_dev --------------------------------------*/

static int init_dev (void) {
  U32 root_scnt;

  /* Invalidate Cached Sectors. */
  fat.sect = INVAL_SECT;
  fat.buf  = (U8 *)&mc_cache[0];
  fat.dirty= __FALSE;

  ca.sect  = INVAL_SECT;
  ca.buf   = (U8 *)&mc_cache[128];
  ca.cbuf  = (U8 *)&mc_cache[256];
  ca.nwr   = 0;
  ca.nrd   = 0;

  /* First 2 clusters are always reserved. */
  top_clus = 2;

  /* Clear MMC info record. */
  memset (&mmc, 0, sizeof (mmc));

  if (get_mbrec () == __FALSE) {
    /* Failed to read or invalid MBR. */
    warm_restart = __FALSE;
    return (2);
  }

  /* Read Boot Record Info. */
  if (get_bootrec () == __FALSE) {
    /* Failed to read or Invalid Boot Record. */
    warm_restart = __FALSE;
    return (3);
  }

  if (is_fat_valid () == __FALSE) {
    /* Invalid FAT table. */
    warm_restart = __FALSE;
    return (4);
  }

  /* Calculate Root Sector Count. */
  root_scnt = (mmc.RootEntCnt * 32 + mmc.BytesPerSec - 1) / mmc.BytesPerSec;

  /* Count Data Sectors/Clusters */
  mmc.DataSecCnt  = mmc.DskSize - (mmc.RsvdSecCnt + 
                                   mmc.NumOfFat * mmc.FatSize + root_scnt);
  mmc.DataClusCnt = mmc.DataSecCnt / mmc.SecPerClus;
  mmc.RootDirAddr = mmc.RsvdSecCnt + mmc.NumOfFat * mmc.FatSize;
  mmc.RootSecCnt  = root_scnt;
  mmc.ClusSize    = mmc.SecPerClus * mmc.BytesPerSec;
  mmc.EntsPerClus = mmc.ClusSize / 32;

  /* Determine Fat Type. */
  if (mmc.DataClusCnt < 4085) {
    mmc.FatType = FS_FAT12;
    warm_restart = __FALSE;
  }
  else if (mmc.DataClusCnt < 65525) {
    mmc.FatType = FS_FAT16;
    warm_restart = __FALSE;
  }
  else {
    mmc.FatType = FS_FAT32;
    /* Calculate number of free cluster the first time. */
    if (warm_restart == __FALSE) {
      warm_restart = __TRUE;
      free_clus = count_free_clus ();
    }
  }

  return (0);
}


/*--------------------------- fat_format ------------------------------------*/

BOOL fat_format (const char *label) {
  /* Format a Flash Card for FAT12 or FAT16. */
  U32 datSect,volSz,iSz,secClus,i,sec;
  MMCFG mcfg;

  /* Read MMC/SD Card configuration. */
  EX(mmc_read_config (&mcfg),__FALSE);

  /* Check Read and Write Block sizes. */
  if (mcfg.read_blen != mcfg.write_blen) {
    return (__FALSE);
  }
  switch (mcfg.read_blen) {
    case 512:
      /* Up to 1GB cards. */
      break;

    case 1024:
      /* 2 GB cards. */
      mcfg.blocknr *= 2;
      break;

    case 2048:
      /* 4 GB cards. */
      mcfg.blocknr *= 4;
      break;

    default:
      /* Block Size not supported. */
      return (__FALSE);
  }

  volSz = mcfg.blocknr >> 11;
  for (iSz = 0, i = 8; iSz < 10; i <<= 1, iSz++) {
    if (volSz < i) break;
  }
  if (iSz == 10) {
    /* Only Flash Card up to 4GB supported. */
    return (__FALSE);
  }

  /* Check for parameter: /WIPE */
  if (chk_param ("WIPE", label) == __TRUE) {
    /* Clear the whole disk. */
    EX(wipe_disk (mcfg.blocknr),__FALSE);
  }

  /* Format with Partition Table and BPB. */
  mmc.BootRecSec = IniDevCfg[iSz].BootRecSec;
  mmc.DskSize    = mcfg.blocknr - mmc.BootRecSec;
  mmc.RsvdSecCnt = 1;
  mmc.BytesPerSec= 512;
  mmc.NumOfFat   = 2;

  /* Set Volume Parameter Info. */
  mmc.FatType    = IniDevCfg[iSz].FatType;
  secClus        = IniDevCfg[iSz].SecClus;

  /* Check for parameter: /FAT32 */
  if (chk_param ("FAT32", label) == __TRUE) {
    /* Force FAT32 */
    mmc.FatType = FS_FAT32;
    secClus     = IniDevCfg[iSz].SecClus32;
    if (secClus == 0) {
      /* Not possible to use FAT32, size is too small. */
      return (__FALSE);
    }
  }

  mmc.SecPerClus = secClus;
  mmc.ClusSize   = secClus * 512;

  datSect = mmc.DskSize - mmc.RsvdSecCnt;
  /* Calculate Data Space and FAT Table Size. */
  switch (mmc.FatType) {
    case FS_FAT12:
      datSect -= 32;
      mmc.RootEntCnt  = 512;
      mmc.RootSecCnt  = 32;
      mmc.DataClusCnt = (datSect * 512 - 1022) / (secClus * 512 + 3);
      mmc.FatSize     = (mmc.DataClusCnt * 3 + 1022) / 1024;
      break;
    case FS_FAT16:
      datSect -= 32;
      mmc.RootEntCnt  = 512;
      mmc.RootSecCnt  = 32;
      mmc.DataClusCnt = (datSect * 128 - 255) / (secClus * 128 + 1);
      mmc.FatSize     = (mmc.DataClusCnt + 255) / 256;
      break;
    case FS_FAT32:
      mmc.RootSecCnt  = 0;
      mmc.DataClusCnt = (datSect * 64 - 127) / (secClus * 64 + 1);
      mmc.FatSize     = (mmc.DataClusCnt + 127) / 128;
      break;
  }

  /* Count Data Sectors/Clusters */
  mmc.DataSecCnt  = mmc.DskSize - (mmc.RsvdSecCnt + mmc.RootSecCnt +
                                   mmc.NumOfFat * mmc.FatSize);
  mmc.RootDirAddr = mmc.RsvdSecCnt + mmc.NumOfFat * mmc.FatSize;

  /* 2nd Cluster should be 32K aligned for optimal Card performance. */
  sec = mmc.RootDirAddr + mmc.RootSecCnt;
  mmc.BootRecSec = ((mmc.BootRecSec + sec + 32) & ~0x3F) - sec;

  warm_restart = __FALSE;
  /* Write MBR, create Partition Table. */
  EX(write_mbr (iSz),__FALSE);

  /* Generate Boot Record  */
  EX(write_br (mcfg.sernum),__FALSE);

  /* Clear FAT Table and Root Directory. */
  memset (ca.buf, 0, 512);

  /* Write Reserved Clusters 0,1 to FAT table. */
  switch (mmc.FatType) {
    case FS_FAT12:
      set_u32 (&ca.buf[0], 0xFFFFF8);
      break;
    case FS_FAT16:
      set_u32 (&ca.buf[0], 0xFFFFFFF8);
      break;
    case FS_FAT32:
      /* Write also Root Dir Cluster to FAT table. */
      set_u32 (&ca.buf[0], 0x0FFFFFF8);
      set_u32 (&ca.buf[4], 0xFFFFFFFF);
      set_u32 (&ca.buf[8], 0x0FFFFFFF);
      break;
  }
  sec = mmc.BootRecSec + mmc.RsvdSecCnt;
  /* Use cache for faster write. */
  EX(write_cache (sec),__FALSE);
  memset (ca.buf, 0, 12);

  datSect = mmc.RootSecCnt;
  if (mmc.FatType == FS_FAT32) {
    /* Clear first Data Cluster (Root Dir) for FAT32. */
    datSect = mmc.SecPerClus;
  }
  datSect += mmc.FatSize * 2;

  for (i = 1; i < datSect; i++) {
    EX(write_cache (sec + i),__FALSE);
  }
  /* Flush the cache when done. */
  EX(write_cache (0),__FALSE);

  if (*label != 0) {
    /* If provided, write also a Volume Label. */
    EX(write_label (label),__FALSE);
  }
  return (__TRUE);
}


/*--------------------------- write_mbr -------------------------------------*/

static BOOL write_mbr (U32 iSz) {
  /* Construct and write a Master Boot Record to sector 0. */
  U32 val;

  memset (ca.buf, 0, 512);

  /* Boot Descriptor: Non Bootable Device. */
  ca.buf[446] = 0;

  /* Beginning of Partition - Head */
  ca.buf[447] = 1;

  /* First Partition Cylinder/Sector */
  set_u16 (&ca.buf[448], 1);

  /* File System Descriptor. */
  switch (mmc.FatType) {
    case FS_FAT12:
      /* Type 12-bit FAT */
      ca.buf[450] = 0x01;
      break;
    case FS_FAT16:
      if (iSz < 3) {
        /* Type 16-bit FAT, Partition < 32 MB */
        ca.buf[450] = 0x04;
      }
      else {
        /* Type 16-bit FAT, Partition > 32MB */
        ca.buf[450] = 0x06;
      }
      break;
    case FS_FAT32:
        /* Type 32-bit FAT, Partition < 2047GB */
      ca.buf[450] = 0x0b;
      break;
  }

  /* End of Partition - Head */
  ca.buf[451] = IniDevCfg[iSz].NumHeads - 1;

  /* End of Partition Cylinder/Sector. */
  val = IniDevCfg[iSz].NumSect | ((IniDevCfg[iSz].NumCyl - 1) << 6);
  set_u16 (&ca.buf[452], val);

  /* First Sector Position Relative to Beginning of Device. */
  set_u32 (&ca.buf[454], mmc.BootRecSec);

  /* Number of Sectors in Partition */
  set_u32 (&ca.buf[458], mmc.DskSize - mmc.BootRecSec);

  /* Executable Marker */
  set_u16 (&ca.buf[510], 0xAA55);
  return (write_sector (0));
}


/*--------------------------- write_br --------------------------------------*/

static BOOL write_br (U32 sernum) {
  /* Construct and write a Boot Rrecord. */

  memset (ca.buf, 0, 512);

  /* Boot Code: E9 00 90 */
  ca.buf[0] = 0xE9;
  ca.buf[1] = 0x00;
  ca.buf[2] = 0x90;

  /* OEM name */
  memcpy (&ca.buf[3], "MSWIN4.1", 8);

  /* Bytes per Sector */
  set_u16 (&ca.buf[11], 512);

  /* Sectors per Cluster */
  ca.buf[13] = mmc.SecPerClus;

  /* Reserved Sectors */
  ca.buf[14] = mmc.RsvdSecCnt;

  /* Number of FAT Tables */
  ca.buf[16] = 2;

  /* Root Entry Count */
  if (mmc.FatType != FS_FAT32) {
    /* Must be 0 for FAT32. */
    set_u16 (&ca.buf[17], 512);
  }

  /* Total Sector Count */
  if (mmc.DskSize < 0x10000) {
    set_u16 (&ca.buf[19], mmc.DskSize);
  }
  else {
    set_u32 (&ca.buf[32], mmc.DskSize);
  }

  /* Media Type, must be the same as FAT byte 0 */
  ca.buf[21] = 0xF8;

  /* Number of Hidden Sectors */
  set_u32 (&ca.buf[28], mmc.BootRecSec);

  if (mmc.FatType != FS_FAT32) {
    /* FAT Size */
    set_u16 (&ca.buf[22], mmc.FatSize);

    /* Physical Disk Number */
    ca.buf[36] = 0x80;

    /* Boot Sig */
    ca.buf[38] = 0x29;

    /* Volume ID */
    set_u32 (&ca.buf[39], sernum);

    /* Volume Label */
    memcpy (&ca.buf[43], "NO NAME    ", 11);

    /* File System Type. */
    if (mmc.FatType == FS_FAT12) {
      memcpy (&ca.buf[54], "FAT12   ", 8);
    }
    else {
      memcpy (&ca.buf[54], "FAT16   ", 8);
    }
  }
  else {
    /* FAT32 Structure different from offset 36. */

    /* FAT Size */
    set_u32 (&ca.buf[36], mmc.FatSize);

    /* Root Cluster Number. */
    set_u32 (&ca.buf[44], 2);

    /* FSInfo */
    set_u16 (&ca.buf[48], 1);

    /* Backup Boot Sector */
    set_u16 (&ca.buf[50], 6);

    /* Physical Disk Number */
    ca.buf[64] = 0x80;

    /* Boot Sig */
    ca.buf[66] = 0x29;

    /* Volume ID */
    set_u32 (&ca.buf[67], sernum);

    /* Volume Label */
    memcpy (&ca.buf[71], "NO NAME    ", 11);

    /* File System Type. */
    memcpy (&ca.buf[82], "FAT32   ", 8);
  }

  /* Executable Marker */
  set_u16 (&ca.buf[510], 0xAA55);

  return (write_sector (mmc.BootRecSec));
}


/*--------------------------- wipe_disk -------------------------------------*/

static BOOL wipe_disk (U32 dsize) {
  /* Clear the whole disk, write FF to all sectors. */
  U32 i,csize;

  /* Invalidate the cache. */
  ca.nwr = 0;
  ca.nrd = 0;

  /* Use the cache buffer. */
  csize = _MC_CSIZE;
  if (csize == 0) {
    csize = 1;
  }
  memset (ca.buf, 0xFF, csize * 512);

  for (i = 0; i < dsize; i += csize) {
    EX(mmc_write_sect (i, ca.buf, csize),__FALSE);
  }
  return (__TRUE);
}


/*--------------------------- fat_free --------------------------------------*/

U64 fat_free (void) {
  /* Calculate a free space for Flash Card. */

  if (mmc.FatType == FS_RAW) {
    /* RAW File System or FAT not initialized. */
    return (0);
  }

  /* For FAT32 count only once. */
  if (mmc.FatType != FS_FAT32) {
    free_clus = count_free_clus ();
  }

  if (free_clus > mmc.DataClusCnt) {
    /* Error, something wrong. */
    return (0);
  }
  /* Return free data space in bytes. */
  return (free_clus * mmc.ClusSize);
}


/*--------------------------- fat_find_dir ----------------------------------*/

static BOOL fat_find_dir (const char *fn, IOB *fcb, U8 create) {
  /* Look for directory if it exists and leave fcb to point to directory, 
     if it does not exist and create == 1, create it. */
  U8  creating_f;
  U32 sz;

  creating_f = 0;

  while (get_dir_name (fn, name_buf, &sz) == __TRUE) {

    if (!creating_f) {
      if (find_name (name_buf, fcb, ENT_DIR) == __FALSE) {
        /* Directory does not exist. */
        if (!create) {
          /* Directory not found. */
          return (__FALSE);
        }
        /* Create requested, set creating_f flag to 1. */
        creating_f = 1;
      }
    }

    if (creating_f) {
      /* If creation of unexisting directory requested. */
      EX(alloc_name (name_buf, fcb),__FALSE);
      /* fcb points to unallocated entry. */
      EX(write_entries (name_buf, fcb, ENT_DIR, ACT_NONE),__FALSE);
      /* Create '.' and '..' entries in created folder. */
      EX(write_dot_entries (fcb),__FALSE);
    }
    fn += sz;
  }

  /* Searched directory was found or created and fcb points to it, in 
     case of creating directory fcb points to entry after ".." entry. */
  return (__TRUE);
}


/*--------------------------- fat_find_file ---------------------------------*/

BOOL fat_find_file (const char *fn, IOB *fcb) {
  /* Look for file if it exists in requested directory, the fcb is left 
     pointing to requested file entries. */

  if (mmc.FatType == FS_RAW) {
    /* RAW File System or FAT not initialized. */
    return (__FALSE);
  }

  /* Remove starting '\' if it exists. */
  if (*fn == '\\') fn++;

  /* Exit function if "fn" is not given. */
  if (*fn == 0) return(__FALSE);

  /* To force search of path from root. */
  fcb->_firstClus = 0;

  /* Search for directory. */
  if (fat_find_dir (fn, fcb, ACT_NONE) == __FALSE) {
    /* Directory does not exist. */
    return (__FALSE);
  }

  /* Search for file. */
  if (find_name (name_buf, fcb, ENT_FILE) == __FALSE) {
    /* File does not exist. */
    return (__FALSE);
  }

  /* Set _currDatSect and _currDat Clus to show to data of found file. */
  fcb->_currDatSect  = 0;
  fcb->_currDatClus  = fcb->_firstClus;

  /* If file exists. */
  return (__TRUE);
}


/*--------------------------- fat_ffind -------------------------------------*/

BOOL fat_ffind (const char *fn, FINFO *info, IOB *fcb) {
  /* Find a file or directory in requested directory. */

  if (mmc.FatType == FS_RAW) {
    /* RAW File System or FAT not initialized. */
    return (__FALSE);
  }

  /* Remove starting '\' if it exists. */
  if (*fn == '\\') fn++;

  /* Exit function if "fn" is not given. */
  if (*fn == 0) return(__FALSE);

  /* To force search of path from root. */
  fcb->_firstClus = 0;

  /* Search for directory. */
  if (fat_find_dir (fn, fcb, 0) == __FALSE) {
    /* Directory does not exist. */
    return (__FALSE);
  }

  /* Get next valid info. */
  if (get_next_info (info, fcb) == __FALSE) {
    /* No more valid infos in current directory. */
    return (__FALSE);
  }

  /* Info found. */
  return (__TRUE);
}


/*--------------------------- fat_create ------------------------------------*/

BOOL fat_create (const char *fn, IOB *fcb) {
  /* Create a file or directory in requested directory. */

  if (mmc.FatType == FS_RAW) {
    /* RAW File System or FAT not initialized. */
    return (__FALSE);
  }

  /* Remove starting '\' if it exists. */
  if (*fn == '\\') fn++;

  /* Exit function if "fn" is not given. */
  if (*fn == 0) return(__FALSE);

  /* To force search of path from root. */
  fcb->_firstClus = 0;

  /* Search for directory. */
  if (fat_find_dir (fn, fcb, 1) == __FALSE) {
    /* Directory does not exist and could not be created. */
    return (__FALSE);
  }

  /* File does not exist, create one. */
  if (alloc_name (name_buf, fcb) == __FALSE) {
    /* If unable to find unallocated entry to create file. */
    return (__FALSE);
  }

  /* fcb points to unallocated entry. */
  if (write_entries (name_buf, fcb, ENT_FILE, ACT_NONE) == __FALSE) {
    /* If unable to write entries for new file. */
    return (__FALSE);
  }

  /* File created. */
  return (__TRUE);
}


/*--------------------------- fat_delete ------------------------------------*/

BOOL fat_delete (const char *fn, IOB *fcb) {
  /* Delete a file or directory from requested directory. */

  if (mmc.FatType == FS_RAW) {
    /* RAW File System or FAT not initialized. */
    return (__FALSE);
  }

  /* Remove starting '\' if it exists. */
  if (*fn == '\\') fn++;

  /* Exit function if "fn" is not given. */
  if (*fn == 0) return(__FALSE);

  /* To force search of path from root. */
  fcb->_firstClus = 0;

  /* Search for directory. */
  if (fat_find_dir (fn, fcb, 0) == __FALSE) {
    /* Directory does not exist. */
    return (__FALSE);
  }

  if (name_buf[0]) {
    /* Search for file. */
    if (find_name (name_buf, fcb, ENT_FILE) == __FALSE) {
      /* File does not exist. */
      return (__FALSE);
    }
  }
  else {
    /* We want to delete a directory, see if it is empty. */
    if (chk_dir_empty (fcb) == __FALSE) {
      /* Directory is not empty, do not delete it. */
      return (__FALSE);
    }
  }

  /* File or directory entries found and fcb points to first entry. */
  if (delete_entries (fcb, 0) == __FALSE) {
    /* If file or directory was not deleted successfully. */
    return (__FALSE);
  }

  /* File was deleted. */
  return (__TRUE);
}


/*--------------------------- fat_read --------------------------------------*/

U32 fat_read (IOB *fcb, U8 *buf, U32 len) {
  /* Read data from file at current file position. */
  U32 sect,pos,nr,rlen;

  if (mmc.FatType == FS_RAW) {
    /* RAW File System or FAT not initialized. */
    return (0);
  }
  if (fcb->fpos + len > fcb->fsize) {
    /* Check for End Of File. */
    len = fcb->fsize - fcb->fpos;
    if (len == 0) {
      /* End of File. */
      return (0);
    }
  }

  pos = fcb->fpos & 0x1FF;
  for (nr = 0; nr < len; nr += rlen) {
    sect = clus_to_sect (fcb->_currDatClus) + fcb->_currDatSect;
    /* Try to cache current cluster. */
    EX(read_cache (sect, mmc.SecPerClus - fcb->_currDatSect),0);

    rlen = len - nr;
    if ((rlen + pos) > 512) {
      rlen = 512 - pos;
    }

    memcpy (&buf[nr], &ca.buf[pos], rlen);
    pos = (pos + rlen) & 0x1FF;
    if (pos == 0) {
      /* Current sector complete, get next one. */
      if (++fcb->_currDatSect == mmc.SecPerClus) {
        /* This cluster is processed, get next one. */
        fcb->_currDatSect = 0;
        EX(set_next_clus (&fcb->_currDatClus),0);
      }
    }
  }
  fcb->fpos += nr;
  /* Number of characters read. */
  return (len);
}


/*--------------------------- fat_write -------------------------------------*/

BOOL fat_write (IOB *fcb, const U8 *buf, U32 len) {
  /* Write data to file at current file position. */
  U32 sect,pos,nw,wlen,clus;

  if (mmc.FatType == FS_RAW) {
    /* RAW File System or FAT not initialized. */
    return (__FALSE);
  }
  if (fcb->_firstClus == 0) {
    /* Data cluster not allocated yet, allocate one. */
    EX(get_free_clus (&fcb->_currDatClus),__FALSE);
    fcb->_firstClus   = fcb->_currDatClus;
    fcb->_currDatSect = 0;
  }

  pos = fcb->fpos & 0x1FF;
  for (nw = 0; nw < len; nw += wlen) {
    wlen = len - nw;
    if ((wlen + pos) > 512) {
      wlen = 512 - pos;
    }
    sect = clus_to_sect (fcb->_currDatClus) + fcb->_currDatSect;
    if (pos != 0) {
      /* File position not 512-byte aligned. */
      EX(read_sector (sect),__FALSE);
    }
    memcpy (&ca.buf[pos], &buf[nw], wlen);
    EX(write_cache (sect),__FALSE);

    pos = (pos + wlen) & 0x1FF;

    if (pos == 0) {
      /* Current sector is full, get next one. */
      if (++fcb->_currDatSect == mmc.SecPerClus) {
        /* This cluster is processed, get next one. */
        fcb->_currDatSect = 0;
        clus = fcb->_currDatClus;
        /* Allocate a free cluster. */
        EX(get_free_clus (&fcb->_currDatClus),__FALSE);
        /* Update also a FAT cluster chain. */
        EX(write_fat_link (clus, fcb->_currDatClus),__FALSE);
      }
    }
  }
  fcb->fpos += nw;
  return (__TRUE);
}


/*--------------------------- fat_close_write -------------------------------*/

BOOL fat_close_write (IOB *fcb) {
  /* Close an opened file, update FAT and Directory record. */
  FILEREC last_frec;

  if (mmc.FatType == FS_RAW) {
    /* RAW File System or FAT not initialized. */
    return (__FALSE);
  }

  if (fcb->fpos > fcb->fsize) {
    /* Write an EOC marker to FAT table Cluster chain. */
    EX(write_fat_link (fcb->_currDatClus, get_EOC()),__FALSE);

    /* Update File Length info from Directory Entry record. */
    /* Read last entry to keep some informations from it. */
    EX(read_last_entry  (fcb, &last_frec),__FALSE);
    last_frec.FirstClusHI = (U16)(fcb->_firstClus >> 16);
    last_frec.FirstClusLO = (U16)(fcb->_firstClus      );
    last_frec.FileSize    = fcb->fpos;
    /* Write updated last entry. */
    EX(write_last_entry (fcb, &last_frec),__FALSE);
  }
  /* Write also cached Data and FAT table. */
  EX(write_cache (0),__FALSE);
  EX(cache_fat (0),__FALSE);
  return (__TRUE);
}


/*--------------------------- fat_set_fpos ----------------------------------*/

BOOL fat_set_fpos (IOB *fcb, U32 pos) {
  /* Set File Position pointer. */
  U32 i;

  if (pos > fcb->fsize) {
    pos = fcb->fsize;
  }
  fcb->_currDatSect = (pos / 512) % mmc.SecPerClus;
  fcb->_currDatClus = fcb->_firstClus;
  for (i = pos / mmc.ClusSize; i; i--) {
    /* Scan the cluster chain. */
    EX(set_next_clus (&fcb->_currDatClus),__FALSE);
  }
  fcb->fpos = pos;

  return (__TRUE);
}


/*--------------------------- fat_rename ------------------------------------*/

BOOL fat_rename (const char *old, const char *newn, IOB *fcb) {
  /* Rename a file or directory to new name. */
  U8 type;

  if (mmc.FatType == FS_RAW) {
    /* RAW File System or FAT not initialized. */
    return (__FALSE);
  }

  /* Remove starting '\' if it exists. */
  if (*old == '\\') old++;

  /* Remove starting '\' if it exists. */
  if (*newn == '\\') newn++;

  /* Exit function if "old" on "new" is not given. */
  if (*old == 0 || *newn == 0) {
    return(__FALSE);
  }

  /* Search for directory. */
  fcb->_firstClus = 0;
  if (fat_find_dir (old, fcb, 0) == __FALSE) {
    /* Directory does not exist. */
    return (__FALSE);
  }

  type = ENT_DIR;
  if (name_buf[0]) {
    if (check_name (newn, fcb, ENT_FILE) == __TRUE) {
      /* New file already exist. */
      return (__FALSE);
    }

    type = ENT_FILE;
    /* Search for file if file name exists. */
    if (find_name (name_buf, fcb, ENT_FILE) == __FALSE) {
      /* File does not exist. */
      return (__FALSE);
    }
  }
  else {
    if (check_name (newn, fcb, ENT_DIR) == __TRUE) {
      /* New directory already exist. */
      return (__FALSE);
    }
  }

  if (rename_entries (newn, fcb, type) == __FALSE) {
    /* If rename was unsuccessfully. */
    return (__FALSE);
  }

  /* File or directory renamed. */
  return (__TRUE);
}


/*--------------------------- write_label -----------------------------------*/

static BOOL write_label (const char *label) {
  /* Write a drive label to Root Directory. */
  FILEREC *frec;
  U32 i;
  U8 ch;

  EX(read_sector (mmc.BootRecSec + mmc.RootDirAddr),__FALSE);
  frec = (FILEREC *)&ca.buf[0];
  memset (frec, 0, 32);
  for (i = 0; i < 11; i++) {
    ch = val_char_lab (label[i]);
    if (ch == 0) break;
    frec->FileName[i] = ch;
  }
  for (  ; i < 11; i++) {
    frec->FileName[i] = ' ';
  }
  frec->Attr      = ATTR_VOLUME_ID;
  set_u16 ((U8 *)&frec->WriteDate, get_date ());
  set_u16 ((U8 *)&frec->WriteTime, get_time ());
  EX(write_sector (mmc.BootRecSec + mmc.RootDirAddr),__FALSE);
  return (__TRUE);
}


/*--------------------------- set_next_clus ---------------------------------*/

static BOOL set_next_clus (U32 *ptr_clus) {
  /* Read next Cluster address from FAT table. */
  U32 sect,ofs,next;
  U32 clus = *ptr_clus;

  /* Read a part of FAT table to buffer. */
  sect = get_fat_sect (clus);
  EX(cache_fat (sect),__FALSE);
  next = 0;
  switch (mmc.FatType) {
    case FS_FAT12:
      ofs  = ((clus * 3) / 2) & 0x1FF;
      if (ofs < 511) {
        next = get_u16 (&fat.buf[ofs]);
      }
      else {
        /* This cluster spans on two sectors in the FAT. */
        next = fat.buf[511];
        EX(cache_fat (sect+1),__FALSE);
        next |= fat.buf[0] << 8;
      }
      if (clus & 0x001) {
        next >>= 4;
      }
      else {
        next &= 0xFFF;
      }
      break;

    case FS_FAT16:
      ofs  = (clus & 0xFF) << 1;
      next = *(U16 *)&fat.buf[ofs];
      break;

    case FS_FAT32:
      ofs  = (clus & 0x7F) << 2;
      next = *(U32 *)&fat.buf[ofs];
      break;

    default:
      return (__FALSE);
  }
  *ptr_clus = next;
  return (__TRUE);
}


/*--------------------------- get_free_clus ---------------------------------*/

static BOOL get_free_clus (U32 *ptr_clus) {
  /* Scan FAT Table and find first free cluster. */
  U32 sect,ofs,next;
  U32 clus = *ptr_clus;

  for (clus = top_clus; clus < (mmc.DataClusCnt + 2); clus++) {
    /* Read a part of FAT table to buffer. */
    sect = get_fat_sect (clus);
    EX(cache_fat (sect),__FALSE);
    switch (mmc.FatType) {
      case FS_FAT12:
        ofs  = ((clus * 3) / 2) & 0x1FF;
        if (ofs < 511) {
          next = get_u16 (&fat.buf[ofs]);
        }
        else {
          /* This cluster spans on two sectors in the FAT. */
          next = fat.buf[511];
          EX(cache_fat (sect+1),__FALSE);
          next |= fat.buf[0] << 8;
        }
        if (clus & 0x001) {
          next >>= 4;
        }
        else {
          next &= 0xFFF;
        }
        break;

      case FS_FAT16:
        ofs  = (clus & 0xFF) << 1;
        next = get_u16 (&fat.buf[ofs]);
        break;

      case FS_FAT32:
        ofs  = (clus & 0x7F) << 2;
        next = get_u32 (&fat.buf[ofs]);
        break;

      default:
        return (__FALSE);
    }
    if (next == 0) {
      if (clus_in_use (clus) == __FALSE) {
        *ptr_clus = clus;
        top_clus  = clus + 1;
        return (__TRUE);
      }
    }
  }
  /* Disk Full, no free clusters found. */
  top_clus = clus;
  return (__FALSE);
}


/*--------------------------- clus_in_use -----------------------------------*/

static BOOL clus_in_use (U32 clus) {
  /* Check if cluster in use by another file. */
  IOB *fcb;
  U32 i,nfile = _NFILE;

  for (i = 0, fcb = &_iob[0]; i < nfile; fcb++, i++) {
    if (!(fcb->flags & _IOWRT)) {
      /* File not opened for writing. */
      continue;
    }
    if (fcb->_currDatClus == clus) {
      /* This cluster used by another file. */
      return (__TRUE);
    }
  }
  return (__FALSE);
}


/*--------------------------- clear_clus ------------------------------------*/

static BOOL clear_clus (U32 clus) {
  /* Clear current cluster. */
  U32 i;
  U32 sect = clus_to_sect(clus);

  /* Use cache for faster write. */
  memset(ca.buf, 0, 512);
  for (i = 0; i < mmc.SecPerClus; i++) {
    EX(write_cache(sect + i),__FALSE);
  }
  /* Flush the cache buffer when done. */
  EX(write_cache (0),__FALSE);
  return (__TRUE);
}


/*--------------------------- write_fat_link --------------------------------*/

static BOOL write_fat_link (U32 clus, U32 next_clus) {
  /* Write FAT table, update link cluster at cluster address. */
  U32 sect,ofs,temp;

  sect = get_fat_sect (clus);
  EX(cache_fat (sect),__FALSE);

  switch (mmc.FatType) {
    case FS_FAT12:
      next_clus &= 0x0FFF;
      ofs  = ((clus * 3) / 2) & 0x1FF;
      if (ofs < 511) {
        temp = get_u16 (&fat.buf[ofs]);
        if (clus & 0x001) {
          temp = (temp & 0x000F) | (next_clus << 4);
        }
        else {
          temp = (temp & 0xF000) | next_clus;
        }
        set_u16 (&fat.buf[ofs], temp);
      }
      else {
        /* This cluster spans on two sectors in the FAT. */
        if (clus & 0x001) {
          fat.buf[511] = (fat.buf[511] & 0x0F) | (next_clus << 4);
        }
        else {
          fat.buf[511] = (U8)next_clus;
        }
        fat.dirty = __TRUE;
        sect++;
        EX(cache_fat (sect),__FALSE);
        if (clus & 0x001) {
          fat.buf[0] = next_clus >> 4;
        }
        else {
          fat.buf[0] = (fat.buf[0] & 0xF0) | (next_clus >> 8);
        }
      }
      break;

    case FS_FAT16:
      ofs  = (clus & 0xFF) << 1;
      set_u16 (&fat.buf[ofs], next_clus);
      break;

    case FS_FAT32:
      ofs  = (clus & 0x7F) << 2;
      if ((get_u32(&fat.buf[ofs]) == 0) && free_clus) {
        free_clus--;
      }

      set_u32 (&fat.buf[ofs], next_clus);
      break;

    default:
      return (__FALSE);
  }
  fat.dirty = __TRUE;
  return (__TRUE);
}


/*--------------------------- unlink_clus_chain -----------------------------*/

static BOOL unlink_clus_chain (U32 clus) {
  /* Remove a cluster chain starting with 'clus'. Reset the values to 0.*/
  U32 sect,ofs,next,temp;

  if (clus < 2) {
    /* An empty file, do nothing here. */
    return (__TRUE);
  }

  while (clus < (mmc.DataClusCnt + 2)) {
    /* Reset top used cluster index. */
    if (clus < top_clus) {
      top_clus = clus;
    }
    sect = get_fat_sect (clus);
    EX(cache_fat (sect),__FALSE);

    switch (mmc.FatType) {
      case FS_FAT12:
        ofs  = ((clus * 3) / 2) & 0x1FF;
        if (ofs < 511) {
          next = get_u16 (&fat.buf[ofs]);
          if (clus & 0x001) {
            temp = next & 0x000F;
            next >>= 4;
          }
          else {
            temp = next & 0xF000;
            next &= 0xFFF;
          }
          set_u16 (&fat.buf[ofs], temp);
        }
        else {
          /* This cluster spans on two sectors in the FAT. */
          next = fat.buf[511];
          if (clus & 0x001) {
            fat.buf[511] &= 0x0F;
          }
          else {
            fat.buf[511] = 0;
          }
          fat.dirty = __TRUE;
          sect++;
          EX(cache_fat (sect),__FALSE);
          next |= fat.buf[0] << 8;
          if (clus & 0x001) {
            fat.buf[0] = 0;
            next >>= 4;
          }
          else {
            fat.buf[0] &= 0xF0;
            next &= 0xFFF;
          }
        }
        goto chk_eoc;

      case FS_FAT16:
        ofs  = (clus & 0xFF) << 1;
        next = get_u16 (&fat.buf[ofs]);
        *(U16 *)&fat.buf[ofs] = 0;
        goto chk_eoc;

      case FS_FAT32:
        ofs  = (clus & 0x7F) << 2;
        next = get_u32 (&fat.buf[ofs]);
        *(U32 *)&fat.buf[ofs] = 0;
        free_clus++;
chk_eoc:fat.dirty = __TRUE;
        if (is_EOC (next) == __TRUE) {
          EX(cache_fat (0),__FALSE);
          return (__TRUE);
        }
        break;

      default:
        return (__FALSE);
    }
    clus = next;
  }
  EX(cache_fat (0),__FALSE);
  /* Failed, something wrong with FAT table. */
  return (__FALSE);
}


/*--------------------------- alloc_new_clus --------------------------------*/

static BOOL alloc_new_clus (U32 *ptr_clus, U8 wr_fat_link) {
  /* Allocate a new cluster. */
  U32 clus = *ptr_clus;

  EX(get_free_clus (ptr_clus),__FALSE);

  EX(write_fat_link (*ptr_clus, get_EOC()),__FALSE);
  if (wr_fat_link) {
    /* Update also a FAT cluster chain. */
    EX(write_fat_link (clus, *ptr_clus),__FALSE);
  }
  EX(cache_fat (0),__FALSE);

  /* New cluster allocated successfully. */
  return (__TRUE);
}


/*--------------------------- count_free_clus -------------------------------*/

static U32 count_free_clus (void) {
  /* Scan FAT table and Count number of free clusters. */
  U32 clus,sect,ofs,next,nfree;

  nfree = 0;
  if (mmc.FatType == FS_FAT12) {
    for (clus = 2; clus < (mmc.DataClusCnt + 2); clus++) {
      /* Read a part of FAT table to buffer. */
      sect = get_fat_sect (clus);
      EX(cache_fat (sect),nfree);
      ofs  = ((clus * 3) / 2) & 0x1FF;
      if (ofs < 511) {
        next = get_u16 (&fat.buf[ofs]);
      }
      else {
        /* This cluster spans on two sectors in the FAT. */
        next = fat.buf[511];
        EX(cache_fat (sect+1),nfree);
        next |= fat.buf[0] << 8;
      }
      if (clus & 0x001) {
        next >>= 4;
      }
      else {
        next &= 0xFFF;
      }
      if (next == 0) {
        nfree++;
      }
    }
    return (nfree);
  }
  if (mmc.FatType == FS_FAT16) {
    sect = get_fat_sect (2);
    EX(cache_fat (sect),nfree);
    for (clus = 2; clus < (mmc.DataClusCnt + 2); clus++) {
      if ((clus & 0xFF) == 0) {
        /* Read a part of FAT table to buffer. */
        sect++;
        EX(cache_fat (sect),nfree);
      }
      /* if 'next' == 0 (LE or BE) */
      if (((U16 *)fat.buf)[clus & 0xFF] == 0) {
        nfree++;
      }
    }
    return (nfree);
  }
  if (mmc.FatType == FS_FAT32) {
    sect = get_fat_sect (2);
    EX(cache_fat (sect),nfree);
    for (clus = 2; clus < (mmc.DataClusCnt + 2); clus++) {
      if ((clus & 0x7F) == 0) {
        /* Read a part of FAT table to buffer. */
        sect++;
        EX(cache_fat (sect),nfree);
      }
      /* if 'next' == 0 (LE or BE) */
      if (((U32 *)fat.buf)[clus & 0x7F] == 0) {
        nfree++;
      }
    }
    return (nfree);
  }
  return (0);
}


/*--------------------------- clus_to_sect ----------------------------------*/

static U32 clus_to_sect (U32 clus) {
  /* Calculate absolute sector address from the cluster index. */
  U32 sect,base;

  base = mmc.BootRecSec + mmc.RootDirAddr;
  if (mmc.FatType != FS_FAT32) {
    base += mmc.RootSecCnt;
  }
  sect = (clus - 2) * mmc.SecPerClus;
  return (base + sect);
}


/*--------------------------- get_fat_sect ----------------------------------*/

static U32 get_fat_sect (U32 clus) {
  /* Calculate absolute FAT Sector address from cluster address. */
  U32 fats;

  switch (mmc.FatType) {
    case FS_FAT12:
      /* FAT Cluster width 12 bits. */
      fats = (clus * 3) / 1024;
      break;

    case FS_FAT16:
      /* FAT Cluster width 16 bits. */
      fats = clus / 256;
      break;

    case FS_FAT32:
      /* FAT Cluster width 32 bits. */
      fats = clus / 128;
      break;

    default:
      /* Not supported. */
      return (0);
  }
  if (fats >= mmc.FatSize) {
    return (0);
  }
  fats += (mmc.BootRecSec + mmc.RsvdSecCnt);
  return (fats);
}


/*--------------------------- read_sector -----------------------------------*/

static BOOL read_sector (U32 sect) {
  /* Read a 512 byte sector from Flash Card. */

  if (sect == ca.sect) {
    /* Required sector already in buffer. */
    return (__TRUE);
  }

  if (sect >= ca.csect && sect < (ca.csect + ca.nwr)) {
    /* This sector is in write cache buffer. */
    memcpy (ca.buf, ca.cbuf + (sect - ca.csect) * 512, 512);
    ca.sect = sect;
    return (__TRUE);
  }

  /* Sector not in cache, read it from the Memory Card. */
  if (mmc_read_sect (sect, ca.buf, 1) == __TRUE) {
    ca.sect = sect;
    return (__TRUE);
  }
  ca.sect = INVAL_SECT;
  return (__FALSE);
}


/*--------------------------- write_sector ----------------------------------*/

static BOOL write_sector (U32 sect) {
  /* Write a 512 byte sector to Flash Card. */

  if (mmc_write_sect (sect, ca.buf, 1) == __TRUE) {
    ca.sect = sect;
    return (__TRUE);
  }
  return (__FALSE);
}


/*--------------------------- read_cache ------------------------------------*/

static BOOL read_cache (U32 sect, U32 cnt) {
  /* Read a 512 byte sector from Flash Card. */

  if ((_MC_CSIZE == 0) || (ca.nwr > 0)) {
    /* File Caching switched off or write caching active. */
    return (read_sector (sect));
  }

  if (ca.nrd > 0) {
    if ((ca.csect <= sect) && sect < (ca.csect + ca.nrd)) {
      /* Requested sector is already cached. */
      memcpy (ca.buf, ca.cbuf + (sect - ca.csect) * 512, 512);
      ca.sect = sect;
      return (__TRUE);
    }
  }

  if (cnt > _MC_CSIZE) {
    cnt = _MC_CSIZE;
  }

  /* Sector not in cache, read it from the Memory Card. */
  if (mmc_read_sect (sect, ca.buf, cnt) == __TRUE) {
    ca.sect  = sect;
    /* First sector is used, the rest is cached. */
    ca.csect = sect + 1;
    ca.nrd   = cnt - 1;
    return (__TRUE);
  }
  ca.sect = INVAL_SECT;
  ca.nrd  = 0;
  return (__FALSE);
}


/*--------------------------- write_cache -----------------------------------*/

static BOOL write_cache (U32 sect) {
  /* Write a 512 byte sector to Data cache. */

  if (_MC_CSIZE == 0) {
    /* File Caching switched off. */
    if (sect) {
      EX(write_sector (sect),__FALSE);
    }
    return (__TRUE);
  }
  if (sect == 0) {
    /* Flush cache request. */
    if (ca.nwr) {
      EX(mmc_write_sect (ca.csect, ca.cbuf, ca.nwr),__FALSE);
      ca.nwr = 0;
    }
    return (__TRUE);
  }
  ca.sect = sect;
  if (ca.nwr > 0) {
    if (sect == (ca.csect + ca.nwr) && ca.nwr < _MC_CSIZE) {
      /* Next sector is continuous, still space in cache. */
      memcpy (ca.cbuf + (ca.nwr * 512), ca.buf, 512);
      ca.nwr++;
      return (__TRUE);
    }
    /* Not continuous sector or buffer full, flush the cache. */
    EX(mmc_write_sect (ca.csect, ca.cbuf, ca.nwr),__FALSE);
    ca.nwr = 0;
  }
  /* Write Data cache is empty. */
  memcpy (ca.cbuf, ca.buf, 512);
  ca.csect = sect;
  ca.nwr   = 1;
  ca.nrd   = 0;
  return (__TRUE);
}


/*--------------------------- cache_fat -------------------------------------*/

static BOOL cache_fat (U32 sect) {
  /* Handle MC FAT Cache. Read/write a 512 byte FAT sector. */

  if (sect == fat.sect) {
    /* Required sector already in buffer. */
    return (__TRUE);
  }
  if (fat.dirty == __TRUE) {
    /* Current FAT sector has been changed, write it first. */
    EX(mmc_write_sect (fat.sect, fat.buf, 1),__FALSE);
    fat.dirty = __FALSE;
  }
  if (sect == 0) {
    /* Only write if sector updated. */
    return (__TRUE);
  }
  if (mmc_read_sect (sect, fat.buf, 1) == __TRUE) {
    fat.sect = sect;
    return (__TRUE);
  }
  fat.sect = INVAL_SECT;
  return (__FALSE);
}


/*--------------------------- is_EOC ----------------------------------------*/

static BOOL is_EOC (U32 clus) {
  /* Check if this cluster is an End Of Chain Marker. */

  switch (mmc.FatType) {
    case FS_FAT12:
      if (clus >= 0x0FF8) {
        return (__TRUE);
      }
      break;
    case FS_FAT16:
      if (clus >= 0xFFF8) {
        return (__TRUE);
      }
      break;
    case FS_FAT32:
      if ((clus & 0x0FFFFFFF) >= 0x0FFFFFF8) {
        return (__TRUE);
      }
      break;
  }
  return (__FALSE);
}


/*--------------------------- get_EOC ---------------------------------------*/

static U32 get_EOC (void) {
  /* Return an End Of Chain Marker. */

  switch (mmc.FatType) {
    case FS_FAT12:
      return (0x0FFF);
    case FS_FAT16:
      return (0xFFFF);
    case FS_FAT32:
      return (0x0FFFFFFF);
  }
  return (0);
}


/*--------------------------- get_mbrec -------------------------------------*/

static BOOL get_mbrec (void) {
  /* Read Master Volume Boot Record info. */

  /* Read MBR and set FAT offset address. */
  EX(read_sector (0),__FALSE);

  /* Check Executable Marker. */
  if (get_u16 (&ca.buf[510]) != 0xAA55) {
    /* Invalid Master Boot Record. */
    return (__FALSE);
  }

  if ((ca.buf[0] == 0xE9) || (ca.buf[0] == 0xEB && ca.buf[2] == 0x90)) {
    /* Partition Table does not exist, this is a BPB. */
    mmc.BootRecSec = 0;
  }
  else {
    /* Flash Cards have only one Partition. */
    mmc.BootRecSec = get_u32 (&ca.buf[454]);
  }
  return (__TRUE);
}


/*--------------------------- get_bootrec -----------------------------------*/

static BOOL get_bootrec (void) {
  /* Read Volume Boot Record info. */

  EX(read_sector (mmc.BootRecSec),__FALSE);

  /* Check Executable Marker. */
  if (get_u16 (&ca.buf[510]) != 0xAA55) {
    /* Invalid Master Boot Record. */
    return (__FALSE);
  }
  /* Set Volume Parameter Info. */
  mmc.SecPerClus = ca.buf[13];
  mmc.BytesPerSec= get_u16 (&ca.buf[11]);
  mmc.RsvdSecCnt = get_u16 (&ca.buf[14]);
  mmc.NumOfFat   = ca.buf[16];
  mmc.RootEntCnt = get_u16 (&ca.buf[17]);
  mmc.DskSize    = get_u16 (&ca.buf[19]);
  mmc.FatSize    = get_u16 (&ca.buf[22]);

  if ((mmc.DskSize == 0) && (mmc.FatSize == 0)) {
    /* Read or correct specific data in mmc structure for FAT32. */
    mmc.FAT32_ExtFlags  = get_u16 (&ca.buf[40]);
    mmc.FAT32_RootClus  = get_u32 (&ca.buf[44]);
    mmc.FAT32_FSInfo    = get_u16 (&ca.buf[48]);
    mmc.FAT32_BkBootSec = get_u16 (&ca.buf[50]);
  }

  if (mmc.DskSize == 0) {
    /* If num of sectors > 0xFFFF, this field is nonzero. */
    mmc.DskSize = get_u32 (&ca.buf[32]);
  }

  if (mmc.FatSize == 0) {
    /* Fat size is in this field for FAT32. */
    mmc.FatSize = get_u32 (&ca.buf[36]);
  }

  return (__TRUE);
}


/*--------------------------- is_fat_valid ----------------------------------*/

static BOOL is_fat_valid (void) {
  /* Check if Volume Info is sane. */

  /* We only support 512 byte sectors. */
  if (mmc.BytesPerSec != 512) {
    return (__FALSE);
  }
  /* Check for Valid Sectors per Cluster values. */
  switch (mmc.SecPerClus) {
    case 1:
    case 2:
    case 4:
    case 8:
    case 16:
    case 32:
    case 64: break;
    default: return (__FALSE);
  }
  /* There should be at least 1 reserved sector. */
  if (mmc.RsvdSecCnt == 0 || mmc.RsvdSecCnt > 64) {
    return (__FALSE);
  }
  /* Only 1 or 2 FAT tables supported. */
  switch (mmc.NumOfFat) {
    case 1:
    case 2:  break;
    default: return (__FALSE);
  }
  if (mmc.FatSize > mmc.DskSize) {
    return (__FALSE);
  }
  return (__TRUE);
}


/*--------------------------- get_time --------------------------------------*/

static U16 get_time (void) {
  /* Get current system time for a time stamp of a file. */
  U32 retv, time, v;

  time = fs_get_time ();

  /* Seconds: 0-29 (2-second count) */
  v = (time >> 1) & 0x1F;
  if (v > 29) v = 0;
  retv = v;

  /* Minutes: 0-59 */
  v = (time >> 8) & 0x3F;
  if (v > 59) v = 0;
  retv |= (v << 5);

  /* Hours: 0-23 */
  v = (time >> 16) & 0x1F;
  if (v > 23) v = 23;
  retv |= (v << 11);

  return (retv);
}


/*--------------------------- get_date --------------------------------------*/

static U16 get_date (void) {
  /* Get current system date for a time stamp of a file. */
  U32 retv, date, v;

  date = fs_get_date ();

  /* Days: 1-31 */
  v = date & 0x1F;
  if (v == 0) v = 1;
  retv = v;

  /* Month: 1-12 */
  v = (date >> 8) & 0x0F;
  if (v > 12 || v == 0) v = 1;
  retv |= (v << 5);

  /* Year: 0-127 */
  v  = (date >> 16) - 1980;
  v &= 0x7F;
  retv |= (v << 9);

  return (retv);
}


/*--------------------------- set_time_date ---------------------------------*/

static void set_time_date (FINFO *info, FILEREC *frec) {
  /* Convert date/time info and write to 'info' structure. */
  U32 v;

  v = get_u16 ((U8 *)&frec->WriteTime);
  info->time.hr  = (v >> 11);
  info->time.min = (v >> 5) & 0x3F;
  info->time.sec = (v & 0x1F) << 1;
  v = get_u16 ((U8 *)&frec->WriteDate);
  info->time.day = (v & 0x1F);
  info->time.mon = (v >> 5) & 0x0F;
  info->time.year= ((v >> 9) & 0x7F) + 1980;
}


/*--------------------------- cvt_fatname -----------------------------------*/

static BOOL cvt_fatname (const char *fn, char *en) {
  /* Convert name to short file entry name. */
  /* fn = pointer to the file name
     en = pointer to the entry file name */
  BOOL dot = 0;
  U8   ch0, ch1, ch2;
  U32  i;

  /* Prepare entry name with 'space's. */
  for (i = 0; i < 11; i++) {
    en[i] = ' ';
  }
  /* Terminate entry name. */
  en[i] = 0;

  /* Check for "." and ".." name */
  ch0 = *fn;
  ch1 = *(fn + 1);
  ch2 = *(fn + 2);
  if (ch0 == '.') {
    if (ch1 == 0) {
      en[0] = '.';
      return (__TRUE);
    }
    else if (ch1 == '.' && ch2 == 0) {
      en[0] = '.';
      en[1] = '.';
      return (__TRUE);
    }
  }

  /* Copy name part (maximum 8 characters) */
  for (i = 0; i < 8; ) {
    if (!(*fn))     {          return (__TRUE); }
    if (*fn == '.') { dot = 1; fn++; break;     }
    if (*fn == ' ') {          fn++; continue;  }
    en[i] = val_char(*fn);
    if (en[i] >= 'a' && en[i] <= 'z')
      en[i] = en[i] & (~0x20);
    i  ++;
    fn ++;
  }

  /* Copy extension part (maximum 3 characters) */
  for (i = 8; i < 11; ) {
    if (!(*fn))     {         return (__TRUE); }
    if (*fn == '.') { dot = 1; fn++; continue; }
    if (*fn == ' ') {          fn++; continue; }
    if (dot)        {
      en[i] = val_char(*fn);
      if (en[i] >= 'a' && en[i] <= 'z')
        en[i] = en[i] & (~0x20);
      i  ++;
    }
    fn ++;
  }
  return (__TRUE);
}


/*--------------------------- check_lfn -------------------------------------*/

static BOOL check_lfn (const char *fn) {
  /* Check if "fn" is a long name. */
  BOOL dot = 0;
  U8   ch, prev_ch = 0;
  U32  i = 0, j = 0;

  while (*fn) {
    if (val_char_sn (*fn) == __FALSE) {
      goto lfn;
    }

    /* If 'space' exists in name then it is a long name. */
    if (*fn == ' ') goto lfn;

    /* If '.' exists in name more then once or if there are more then 3 
       valid characters after '.' then it is a long name. */
    if (*fn == '.') {
      if (dot) goto lfn;
      fn ++;
      j   = 0;
      dot = 1;
      continue;
    }

    /* If cases (upper or lower) of letter are different then it is a 
       long name. */
    ch = *fn;
    if ((ch >= 'a' && ch <= 'z') ||
        (ch >= 'A' && ch <= 'Z')) {
      if (prev_ch && ((prev_ch ^ ch) & 0x20)) {
        goto lfn;
      }
      prev_ch = ch;
    }

    if (dot) {
      if (j++ > 2) 
        goto lfn;
    } else if (i >= 8) {
      goto lfn;
    }
    i  ++;
    fn ++;
  }

  if (i >= 12) {
    /* This is a long name. */
lfn:return (__TRUE);
  }

  /* This is a short name. */
  return (__FALSE);
}


/*--------------------------- val_char --------------------------------------*/

static U8 val_char (U8 ch) {
  /* Validate character 'ch' to be a valid character if not convert it 
     to 'X'. */

  if (val_char_sn (ch) == __FALSE) {
    return ('X');
  }

  return (ch);
}


/*--------------------------- val_char_sn -----------------------------------*/

static BOOL val_char_sn (U8 ch) {
  /* Validate character 'ch' to be a valid short name character. */

  if ((ch >= ' ' && ch <= '!') ||
      (ch >= '#' && ch <= ')') ||
      (ch == '-')              ||
      (ch == '.')              ||
      (ch >= '0' && ch <= '9') ||
      (ch == '@')              ||
      (ch >= 'A' && ch <= 'Z') ||
      (ch >= '^' && ch <= '{') ||
      (ch == '}')              ||
      (ch == '~')               ) {

    /* This is a valid short name character. */
    return (__TRUE);
  }

  /* This is not a valid short name character. */
  return (__FALSE);
}


/*--------------------------- val_char_ln -----------------------------------*/
#if 0
static BOOL val_char_ln (U8 ch) {
  /* Validate character 'ch' to be a valid long name character. */

  if (val_char_sn (ch) == __TRUE) {
    /* If character is a valid short name character then it is also a valid 
       long name character. */
    return (__TRUE);
  }

  if (ch == '+' || 
      ch == ',' || 
      ch == ';' || 
      ch == '=' || 
      ch == '[' || 
      ch == ']' ||
      ch >  127) {

    /* This is a valid long name character. */
    return (__TRUE);
  }

  /* This is not a valid long name character. */
  return (__FALSE);
}
#endif

/*--------------------------- val_char_lab ----------------------------------*/

static U8 val_char_lab (U8 ch) {
  /* Validate character 'ch' to be a valid disk label character. */

  if ((ch >= '0' && ch <= '9') ||
      (ch >= 'A' && ch <= 'Z') ||
      (ch == '_') || (ch == ' ')) {
    return (ch);
  }
  if (ch >= 'a' && ch <= 'z') {
    /* Convert to uppercase. */
    return (ch & ~0x20);
  }
  /* This is not a valid disk label character. */
  return (0);
}


/*--------------------------- get_dir_name ----------------------------------*/

static BOOL get_dir_name (const char *fn, char *dn, unsigned int *sz) {
  /* Return first name (dir or file) if "fn" given as path + file name, and 
     also calculates number of characters until the end of name (sz).
     It returns __TRUE if directory name else it returns __FALSE.           */
  /* Example: *fn  = "Some Folder\Test\Some file.txt"
              *dn  = "Some Folder"                                    
               sz  = 12                                                     */
  U8  ch;
  U32 i, j;

  for (i = 0, j = 0; ; i++) {
    ch = *(fn + i);
    if (ch == '\\' || ch == '\"') {
      dn[j] = 0;
      *sz   = i + 1;
      return (__TRUE);
    }
    if (ch == 0) {
      dn[j] = 0;
      return (__FALSE);
    }
    dn[j++] = ch;
  }
}


/*--------------------------- get_nt_name -----------------------------------*/

static BOOL get_nt_name (const char *fn, char *sn, int num) {
  /* Create a short name in "sn" with numeric tail (with value num) 
     of a long name given in "fn".
     It returns __TRUE if successfull else it returns __FALSE.              */
  /* Example: *fn   = "Some file.txt"
              *sn   = "SOMEFI~3.TXT
               num  = 3                                                     */
  U8  ch = 0;
  S8  num_sz;
  U32 dot_pos  = 0xFFFF;
  U32 val, i, j;

  /* Calculate how many digits requested number has (maximum 6). */
  if      (num > 99999) num_sz = 6;
  else if (num >  9999) num_sz = 5;
  else if (num >   999) num_sz = 4;
  else if (num >    99) num_sz = 3;
  else if (num >     9) num_sz = 2;
  else                  num_sz = 1;

  /* Find position of last dot (.) in long name. */
  for (i = 0; *(fn + i); i++) {
    if (*(fn + i) == '.') dot_pos = i;
  }

  if (num == 0) {
    /* Enable name creation if 0 without numerical ending */
    num_sz = - 1;
  }

  /* Copy first part of the name. */
  for (i = 0, j = 0; (i < dot_pos) && (j < (7 - num_sz)); i++) {
    ch = *(fn + i);
    if ((ch == ' ') || (ch == '.')) {
      continue;
    }
    if (ch == 0) {
      break;
    }
    else {
      if (ch >= 'a' && ch <= 'z') {
        /* Convert to uppercase. */
        ch &= ~0x20;
      }
      sn[j++] = val_char (ch);
    }
  }
  if (num == 0) goto finish_name;

  sn[j++] = '~';

  switch (num_sz) {
    case 6: 
      val            = num / 100000;
      num           -= val * 100000;
      if (val > 9) val = 9;
      sn[j++]  = '0' + val;
    case 5: 
      val            = num /  10000;
      num           -= val *  10000;
      sn[j++]  = '0' + val;
    case 4: 
      val            = num /   1000;
      num           -= val *   1000;
      sn[j++]  = '0' + val;
    case 3: 
      val            = num /    100;
      num           -= val *    100;
      sn[j++]  = '0' + val;
    case 2: 
      val            = num /     10;
      num           -= val *     10;
      sn[j++]  = '0' + val;
    case 1: 
      sn[j++]  = '0' + num;
      break;
  }

finish_name:
  if (ch == 0) goto terminate_name;

  sn[j++] = '.';

  if (dot_pos != 0xFFFF) {
    for (i = dot_pos + 1; (i < dot_pos + 4); i++) {
      ch = *(fn + i);
      if (!ch) {
        break;
      }
      if (ch >= 'a' && ch <= 'z') {
        /* Convert to uppercase. */
        ch &= ~0x20;
      }
      sn[j++] = val_char (ch);
    }
  }

terminate_name:
  sn[j] = 0;                           /* Terminate name string */

  return (__TRUE);
}


/*--------------------------- get_dir_sect ---------------------------------*/

static U32 get_dir_sect (U32 clus) {
  /* Calculate sector address of the cluster, and update in_root_1x flag. */
  U32 sect;

  in_root_1x = 0;
  if (clus == 0) {
    startDirClus = 0;

    /* This is a ROOT folder. */
    if (mmc.FatType == FS_FAT32) {
      /* This is a ROOT folder on FAT32. */
      sect = clus_to_sect (mmc.FAT32_RootClus);
    }
    else {
      /* This is a ROOT folder on FAT12 or FAT16. */
      sect = mmc.BootRecSec + mmc.RootDirAddr;
      in_root_1x = 1;
    }
  }
  else {
    /* This is a subfolder. */
    sect = clus_to_sect (clus);
  }
  return (sect);
}


/*--------------------------- search_for_name -------------------------------*/

static BOOL search_for_name (const char *name, IOB *fcb, U8 type, U8 keep_fcb) {
  /* Search for entries with requested name and of requested type 
     (file or dir).                                                         */

  char         sen[13];
  FILEREC     *frec;
  U8           lfn_f         = 0;
  U8           dir_f         = (type == ENT_DIR);
  U8           same_f        = 1;
  U8           type_f        = 0;
  U8           sfn_name_f    = __FALSE;
  U8           chksum        = 0;
  U8           ents          = 0;
  U8           name_ents     = 1;
  U32          clus          = fcb->_firstClus;
  U32          idx;
  U32          first_clus    = 0;
  U32          first_offs    = 0;
  U32          sect;
  U32          i;

  startDirClus = fcb->_firstClus;

  /* Calculate number of requested entries needed for name. */
  if (check_lfn(name) == __TRUE) {
    /* Add number of LFN entries. */
    name_ents += ((strlen(name) + 12) / 13);
  }

  /* Convert name to short entry type (8.3) */
  sfn_name_f = cvt_fatname (name, sen);

  /* Calculate current sector address for folder. */
  sect = get_dir_sect (clus);

  /* Search through name entries. */
  for (idx = 0;  ; idx++) {
    if (in_root_1x) {
      if (idx == 512) {
        return (__FALSE);
      }
    }
    else {
      /* Check if step to next cluster is needed. */
      if (idx == mmc.EntsPerClus) {
        idx = 0;
        if (clus < mmc.FAT32_RootClus) {
          clus = mmc.FAT32_RootClus;
        }
        EX(set_next_clus (&clus),__FALSE);
        if (is_EOC (clus)) {
          /* No more entries, end of current directory. */
          goto not_found;
        }
        sect = clus_to_sect (clus);
      }
    }

    EX(read_sector (sect + (idx >> 4)),__FALSE);
    frec = (FILEREC *)ca.buf + (idx & 0x0F);

    if (frec->FileName[0] == 0x00) {
      /* There are no allocated entries after this one. */
      goto not_found;
    }

    if (frec->FileName[0] == 0xE5) {
      /* Erased file, first character is 0xE5. */
      continue;
    }

    if (frec->Attr == ATTR_VOLUME_ID) {
      /* Skip Volume ID entry. */
      continue;
    }

    if ((frec->Attr == ATTR_LONG_NAME) && (LFN_REC(frec)->Ordinal & ORD_LONG_NAME_LAST)) {
      /* Long name last entry found. */
      lfn_f           = 1;
      same_f          = 1;
      if (((LFN_REC(frec)->Ordinal & ~ORD_LONG_NAME_LAST) + 1) != name_ents) {
        same_f       = 0;
      }
      first_clus      = clus;
      first_offs      = idx;
      ents            = 0;
      chksum          = LFN_REC(frec)->Checksum;
    }

    /* type_f == 1 if type of entry we are searching for is the same 
       one we are checking now. */
    type_f = !(dir_f ^ ((frec->Attr & ATTR_DIRECTORY) == ATTR_DIRECTORY));

    if (lfn_f) {
      /* Long name entry found. */
      ents ++;

      if (frec->Attr != ATTR_LONG_NAME) {
        /* If this is long name's accompanying short entry. */
        lfn_f = 0;

        /* Calculate short name's checksum. */
        if ((same_f) && (chksum == lfn_calc_chksum(frec->FileName))) {
          if (type_f) {
            /* If this is the file or directory we searched for. */
            if (keep_fcb) {
              goto found_keep_fcb;
            }
            goto found;
          }
        }
        else {
          /* Check also if name is same as only short name (for checking 
             if short name already exists). */
          if (name_ents == 1)
            goto chk_short;
        }
      }

      if (!same_f) {
        /* If this is not the entry we are searching for. */
        continue;
      }

      if (chksum != LFN_REC(frec)->Checksum) {
        /* If any of long entries does not have the same checksum 
           as previous ones then this name is invalid. */
        same_f = 0;
        continue;
      }

      /* Long name checking in progress. */
      i = ((LFN_REC(frec)->Ordinal & 0x1F) - 1) * 13;

      /* Compare 13 chars of name with 13 chars of entry name, ignore case. */
      same_f = lfn_cmp_name ((U8 *)frec, (char *)&name[i]);
    }
    else if (name_ents == 1) {
      /* Short name entry found. */
      first_clus = clus;
      first_offs = idx;
      ents       = 1;

      /* If this is not the type of entry we are searching for. */
      if (!type_f) { 
        continue; 
      }

chk_short:
      /* Check if name converted to short entry name is valid. */
      if (sfn_name_f == __FALSE) { 
        continue; 
      }

      /* Compare name with entry name, ignore case. */
      same_f = sfn_cmp_name (frec->FileName, sen);

      /* If this is entry we searched for. */
      if (same_f) {
        if (keep_fcb) {
          goto found_keep_fcb;
        }
        goto found;
      }
    }
  }

not_found:
  return (__FALSE);

found_keep_fcb:
  return (__TRUE);

found:
  fcb->attrib       = frec->Attr;
  fcb->_firstClus   = (((U32)get_u16 ((U8 *)&frec->FirstClusHI)) << 16) +
                      (((U32)get_u16 ((U8 *)&frec->FirstClusLO))      ) ;
  fcb->fileID       = idx;
  fcb->_lastEntClus = clus;
  firstEntClus      = first_clus;
  firstEntOffs      = first_offs;
  numOfEntries      = ents;
  fcb->fpos         = 0;
  fcb->fsize        = get_u32 ((U8 *)&frec->FileSize);
  return (__TRUE);
}


/*--------------------------- find_name -------------------------------------*/

static BOOL find_name (const char *name, IOB *fcb, U8 type) {
  /* Search for entries with requested name and of requested type 
     (file or dir).                                                         */

  return (search_for_name (name, fcb, type, ACT_NONE));
}


/*--------------------------- check_name ------------------------------------*/

static BOOL check_name (const char *name, IOB *fcb, U8 type) {
  /* Check if requested name of requested type exists.                      */

  return (search_for_name (name, fcb, type, ACT_KEEPFCB));
}


/*--------------------------- alloc_name ------------------------------------*/

static BOOL alloc_name (const char *name, IOB *fcb) {
  /* Find unused position or enough of erased entries for new entries for 
     "name" (file or dir).                                                  */
  FILEREC     *frec;
  U8           name_ents     = 1;
  U8           ents          = 0;
  U16          first_offs    = 0;
  U32          first_clus    = 0;
  U32          clus          = fcb->_firstClus;
  U32          sect;
  U32          idx;

  /* Calculate number of requested entries needed for name. */
  if (check_lfn(name) == __TRUE) {
    /* Add number of LFN entries. */
    name_ents += ((strlen(name) + 12) / 13);
  }

  /* Calculate current sector address for folder. */
  sect = get_dir_sect (clus);

  /* Search through name entries. */
  for (idx = 0;  ; idx++) {
    if (in_root_1x) {
      if (idx == 512) {
        return (__FALSE);
      }
    }
    else {
      /* Check if step to next cluster is needed. */
      if (idx == mmc.EntsPerClus) {
        idx = 0;
        if (clus < mmc.FAT32_RootClus) {
          clus = mmc.FAT32_RootClus;
        }
        first_clus = clus;
        EX(set_next_clus (&clus),__FALSE);
        if (is_EOC (clus)) {
          /* No more entries, end of current directory. */

          /* Allocate new cluster. */
          clus = first_clus;
          EX(alloc_new_clus (&clus, 1),__FALSE);
          EX(clear_clus (clus),__FALSE);
          first_offs = 0;
          first_clus = clus;
          goto allocated;
        }
        sect = clus_to_sect (clus);
      }
    }

    EX(read_sector (sect + (idx >> 4)),__FALSE);
    frec = (FILEREC *)ca.buf + (idx & 0x0F);

    if ((frec->FileName[0] == 0x00) || (frec->FileName[0] == 0xFF)) {
      /* Unused entry. */

      if (ents) {
        /* If we found unused entry, and it is after erased entries. */
        goto allocated;
      }
      /* If we found first unused entry. */
      first_offs = idx;
      first_clus = clus;
      goto allocated;
    }

    if (frec->FileName[0] == 0xE5) {
      /* Erased file, first character is 0xE5. */

      if (ents++ == 0) {
        /* If this is first erased entry. */
        first_offs = idx;
        first_clus = clus;
        if (name_ents == 1) {
          goto allocated;
        }
        continue;
      }
      if (ents >= name_ents) {
        goto allocated;
      }
      continue;
    }

    /* If we are searching for entry for allocation skip the rest of loop. */
    ents = 0;
  }

allocated:
  firstEntOffs      = first_offs;
  firstEntClus      = first_clus;
  return (__TRUE);
}


/*--------------------------- get_next_info ---------------------------------*/

static BOOL get_next_info (FINFO *info, IOB *fcb) {
  /* Return next name (file or directory). */
  FILEREC     *frec;
  U8           lfn_f         = 0;
  U8           valid_f       = 0;
  U8           chksum        = 0;
  U8           calc_chksum;
  U32          clus          = fcb->_firstClus;
  U32          idx;
  U32          idx_inc       = 0;
  U32          sect;
  U32          i, j;

  sect = get_dir_sect (clus);

  /* Search through name entries. */
  for (idx = info->fileID;  ; idx++) {
    if (in_root_1x) {
      if (idx == 512) {
        return (__FALSE);
      }
    }
    else {
      /* Check if step to next cluster is needed. */
      while (idx >= mmc.EntsPerClus) {
        idx -= mmc.EntsPerClus;
        if (clus < mmc.FAT32_RootClus) {
          clus = mmc.FAT32_RootClus;
        }
        EX(set_next_clus (&clus),__FALSE);
        if (is_EOC (clus)) {
          /* No more entries. */
          goto no_more_entries;
        }
        sect = clus_to_sect (clus);
      }
    }
    idx_inc ++;

    EX(read_sector (sect + (idx >> 4)),__FALSE);
    frec      = (FILEREC *)ca.buf + (idx & 0x0F);

    if (frec->FileName[0] == 0x00) {
      /* There are no allocated entries after this one. */
      goto no_more_entries;
    }

    if (frec->FileName[0] == 0xE5) {
      /* Erased file, first character is 0xE5. */
      continue;
    }

    if (frec->Attr == ATTR_VOLUME_ID) {
      /* Skip Volume ID entry. */
      continue;
    }

    if ((frec->Attr == ATTR_LONG_NAME) && (LFN_REC(frec)->Ordinal & ORD_LONG_NAME_LAST)) {
      /* Long name last entry found. */
      lfn_f   = 1;
      valid_f = 1;
      chksum  = LFN_REC(frec)->Checksum;
    }

    if (lfn_f) {
      /* Long name entry found. */

      if (frec->Attr != ATTR_LONG_NAME) {
        /* If this is long name's accompanying short entry. */
        lfn_f = 0;

        /* Calculate short name's checksum. */
        calc_chksum = lfn_calc_chksum (frec->FileName);
        if ((valid_f) && (calc_chksum == chksum)) {
          goto found;
        }
      }

      if (!valid_f) {
        /* If this is not a valid entry. */
        continue;
      }

      if (chksum != LFN_REC(frec)->Checksum) {
        /* If any of long entries does not have the same checksum 
           as previous ones then this name is invalid. */
        valid_f = 0;
        continue;
      }

      /* Long name checking in progress. */
      i = ((LFN_REC(frec)->Ordinal & 0x1F) - 1) * 13;

      /* Copy all 13 name characters to info->name array. */
      lfn_copy_info (&info->name[i], (U8 *)frec);
      i += 13;

      if (LFN_REC(frec)->Ordinal & ORD_LONG_NAME_LAST) {
        info->name[i] = 0;
      }
    }
    else {
      /* Short name entry found. */

      i = 7;
      while (frec->FileName[i] == ' ') {
        i--;
      }
      ++ i;
      for (j = 0; j < i; j++) {
        info->name[j] = frec->FileName[j];
      }
      if (frec->FileName[8] != ' ') {
        info->name[j++] = '.';
        i = 8;
        while ((frec->FileName[i] != ' ') && (i < 11)) {
          info->name[j++] = frec->FileName[i++];
        }
      }
      info->name[j] = 0;
      goto found;
    }
  }

no_more_entries:
  return (__FALSE);

found:
  info->fileID += idx_inc;
  fcb->attrib   = frec->Attr;
  fcb->fsize    = get_u32 ((U8 *)&frec->FileSize);
  set_time_date (info, frec);
  return (__TRUE);
}


/*--------------------------- chk_dir_empty ---------------------------------*/

static BOOL chk_dir_empty (IOB *fcb) {
  /* Return __TRUE if directory is empty (has only "." and ".." entries) or 
     __FALSE if directory is not empty. */
  FILEREC     *frec;
  U32          clus          = fcb->_firstClus;
  U32          idx;
  U32          sect;

  if (clus == 0) {
    /* If checking for root, always return not empty. */
    goto dir_not_empty;
  }

  /* Calculate address of sector where search starts. */
  sect = clus_to_sect (clus);

  /* Search until unallocated entry found. */
  for (idx = 0; ; idx ++) {
    /* Check if step to next cluster is needed. */
    if (idx == mmc.EntsPerClus) {
      idx = 0;
      EX(set_next_clus (&clus),__FALSE);
      if (is_EOC (clus)) {
        /* No more entries, end of current directory. */
        goto dir_empty;
      }
      sect = clus_to_sect (clus);
    }

    EX(read_sector (sect + (idx >> 4)),__FALSE);
    frec      = (FILEREC *)ca.buf + (idx & 0x0F);

    if (frec->FileName[0] == '.') {
      if (strcmp ((const char *)&frec->FileName[0], ".          \x10") == 0) {
        /* Dot entry. */
        continue;
      }
      if (strcmp ((const char *)&frec->FileName[0], "..         \x10") == 0) {
        /* Dot dot entry. */
        continue;
      }
    }

    if (frec->FileName[0] == 0x00) {
      /* There are no allocated entries after this one. */
      goto dir_empty;
    }

    if (frec->FileName[0] == 0xE5) {
      /* Erased file, first character is 0xE5. */
      continue;
    }

    if (frec->Attr == ATTR_VOLUME_ID) {
      /* Skip Volume ID entry. */
      continue;
    }

    goto dir_not_empty;
  }

dir_not_empty:
  return (__FALSE);

dir_empty:
  return (__TRUE);
}


/*--------------------------- read_last_entry -------------------------------*/

static BOOL read_last_entry (IOB *fcb, FILEREC *filerec) {
  /* Read last entry that fcb is pointing to.*/
  FILEREC     *frec;
  U32          clus          = fcb->_lastEntClus;
  U32          idx           = (U32)fcb->fileID;
  U32          sect;

  /* Calculate sector index. */
  sect = get_dir_sect (clus);

  EX(read_sector (sect + (idx >> 4)),__FALSE);
  frec = (FILEREC *)ca.buf + (idx & 0x0F);

  /* Copy data from last file record. */
  memcpy (filerec, frec, 32);

  /* Last file record read successfully. */
  return (__TRUE);
}


/*--------------------------- write_last_entry ------------------------------*/

static BOOL write_last_entry (IOB *fcb, FILEREC *filerec) {
  /* Write last entry that fcb is pointing to.*/
  FILEREC     *frec;
  U32          clus          = fcb->_lastEntClus;
  U32          idx           = (U32)fcb->fileID;
  U32          sect;

  /* Calculate sector index. */
  sect = get_dir_sect (clus);

  EX(read_sector  (sect + (idx >> 4)),__FALSE);
  frec = (FILEREC *)ca.buf + (idx & 0x0F);

  /* Copy data from last file record. */
  memcpy (frec, filerec, 32);

  EX(write_sector (sect + (idx >> 4)),__FALSE);

  /* Last file record written successfully. */
  return (__TRUE);
}


/*--------------------------- write_entries ---------------------------------*/

static BOOL write_entries (const char *name, IOB *fcb, U8 type, FILEREC *copy_frec) {
  /* Write entries to where fcb is pointing to, if copy_frec != NULL then keep 
     some info from file record that copy_frec is pointing, when done leave fcb 
     to point to last entry of entries that were written. */
  char         sfn[13];
  char         sen[13];
  FILEREC     *frec;
  U8           lfn_f         = 0;
  U8           dir_f         = (type == ENT_DIR);
  U8           name_lfn_f    = check_lfn (name);
  U8           calc_chksum   = 0;
  U32          clus          = firstEntClus;
  U32          idx           = firstEntOffs;
  U32          sect;
  U32          sz            = strlen (name);
  U32          i, j;

  /* Calculate address of sector where write will start. */
  sect = get_dir_sect (clus);

  if (!name_lfn_f) {
    /* Convert name to short entry type (8.3) */
    cvt_fatname (name, sen);
  }
  else {
    /* Find unexisting short name for long name. */
    i = 0;
    while (get_nt_name  (name, sfn, i++) == __TRUE) {
      if (check_name (sfn, fcb, ENT_FILE) == __FALSE) {
        /* If the short name does not exist convert it to entry name. */
        cvt_fatname (sfn, sen);
        break;
      }
      if (i > (999999 - 1)) {
        /* Unable to reserve short entry name. */
        return (__FALSE);
      }
    }
  }

  /* At this point we have information if we are writing long name 
     (name_lfn_f == 1), if we are writing a file or directory entries 
     (dir_f == 1), we have short name (sen) prepared. */

  /* Calculate short name's checksum. */
  if (name_lfn_f) {
    calc_chksum = lfn_calc_chksum ((U8 *)sen);
  }

  /* Go through entries. */
  for ( ; ; idx ++) {
    /* Check if step to next cluster is needed. */
    if (in_root_1x) {
      if (idx == 512) {
        goto fail;
      }
    }
    else {
      /* Check if step to next cluster is needed. */
      if (idx == mmc.EntsPerClus) {
        idx = 0;
        /* If we have written to last entry of current cluster then 
           allocate new for remaining entries. */
        if (clus < mmc.FAT32_RootClus) {
          clus = mmc.FAT32_RootClus;
        }
        EX(alloc_new_clus (&clus, 1),__FALSE);
        EX(clear_clus (clus),__FALSE);
        sect = clus_to_sect (clus);
      }
    }

    EX(read_sector (sect + (idx >> 4)),__FALSE);
    frec      = (FILEREC *)ca.buf + (idx & 0x0F);

    if (name_lfn_f) {
      /* We are handling long name. */
      if (lfn_f) {
        /* If long name last entry created already. */
        LFN_REC(frec)->Ordinal = 0;
      }
      else {
        /* Long name last entry creation. */
        lfn_f = 1;
        LFN_REC(frec)->Ordinal = ORD_LONG_NAME_LAST;
      }

      if (sz) {
        /* Long name's long entry creation. */
        LFN_REC(frec)->Ordinal    |= ((sz + 12) / 13);
        LFN_REC(frec)->Checksum    = calc_chksum;
        LFN_REC(frec)->FirstClusLO = 0;
        LFN_REC(frec)->Attr        = ATTR_LONG_NAME;

        /* Long name creation in progress. */
        i = ((LFN_REC(frec)->Ordinal & 0x1F) - 1) * 13;

        /* Copy 13 characters of name to 13 characters of entry name. */
        lfn_copy_name ((U8 *)frec, (char *)&name[i]);

        if (sz > 12) {
          sz -= 13;
        }
        else {
          sz = 0;
        }

        if ((idx & 0x0F) == 0x0F) {
          /* Write last previously used sector as we are going to use 
             next one. */
          EX(write_sector (sect + (idx >> 4)),__FALSE);
        }
      }
      else {
        /* Long name's short entry creation. */
        goto wr_short;
      }
    }
    else {
      /* We are handling short name. */

wr_short:
      /* Copy the name to the entry. */
      for (j = 0; j < 11; j++) {
        frec->FileName[j]  = sen[j];
      }

      if (copy_frec == NULL) {
        /* If no copying of informations from frec was requested. */

        frec->NTRsvd         = 0;
        frec->CrtTimeTenth   = 0;
        set_u16 ((U8 *)&frec->CrtTime, get_time ());
        set_u16 ((U8 *)&frec->CrtDate, get_date ());
        frec->LastAccDate    = frec->CrtDate;
        frec->WriteTime      = frec->CrtTime;
        frec->WriteDate      = frec->CrtDate;
        frec->FileSize       = 0;

        fcb->fpos            = 0;
        fcb->fsize           = 0;

        if (dir_f) {
          /* If directory entry was created. */
          frec->Attr        = ATTR_DIRECTORY;
          fcb->_lastEntClus = clus;
          fcb->fileID       = idx;
          /* Allocate an unused cluster for directory data. */
          if (clus < mmc.FAT32_RootClus) {
            clus = mmc.FAT32_RootClus;
          }
          EX(alloc_new_clus (&clus, 0),__FALSE);
          fcb->_firstClus   = clus;

          set_u16 ((U8 *)&frec->FirstClusHI, clus >> 16);
          set_u16 ((U8 *)&frec->FirstClusLO, clus      );

          EX(write_sector (sect + (idx >> 4)),__FALSE);

          EX(clear_clus (clus),__FALSE);
          goto success_dir;
        }
        else {
          /* If file was created. */
          frec->Attr        = ATTR_ARCHIVE;
          frec->FirstClusHI = 0;
          frec->FirstClusLO = 0;
          fcb->_firstClus   = 0;

          EX(write_sector (sect + (idx >> 4)),__FALSE);
        }
      }
      else {
        /* If copying of informations from frec was requested. */
        frec->Attr           = copy_frec->Attr;
        frec->NTRsvd         = 0;
        frec->CrtTimeTenth   = 0;
        frec->CrtTime        = copy_frec->CrtTime;
        frec->CrtDate        = copy_frec->CrtDate;
        set_u16 ((U8 *)&frec->LastAccDate, get_date ());
        frec->FirstClusHI    = copy_frec->FirstClusHI;
        set_u16 ((U8 *)&frec->WriteTime, get_time ());
        frec->WriteDate      = frec->LastAccDate;
        frec->FirstClusLO    = copy_frec->FirstClusLO;
        frec->FileSize       = copy_frec->FileSize;

        fcb->fpos            = 0;
        fcb->fsize           = copy_frec->FileSize;
        fcb->_firstClus      = (((U32)get_u16 ((U8 *)&copy_frec->FirstClusHI)) << 16) +
                               (((U32)get_u16 ((U8 *)&copy_frec->FirstClusLO))      ) ;

        EX(write_sector (sect + (idx >> 4)),__FALSE);
      }


      /* Entries written successfully. */
      goto success;
    }
  }

fail:
  return (__FALSE);

success:
  fcb->fileID       = idx;
  fcb->_lastEntClus = clus;

success_dir:
  return (__TRUE);
}


/*--------------------------- delete_entries --------------------------------*/

static BOOL delete_entries (IOB *fcb, U8 keep_data) {
  /* Delete entries that fcb is pointing to.*/
  FILEREC     *frec;
  U8           ents          = numOfEntries;
  U32          clus          = firstEntClus;
  U32          idx           = firstEntOffs;
  U32          sect;

  /* Calculate address of sector where deletion starts. */
  sect = get_dir_sect (clus);

  for ( ; ents != 0; idx ++) {
    /* Check if step to next cluster is needed. */
    if (in_root_1x) {
      if (idx == 512) {
        goto fail;
      }
    }
    else {
      /* Check if step to next cluster is needed. */
      if (idx == mmc.EntsPerClus) {
        idx = 0;
        if (clus < mmc.FAT32_RootClus) {
          clus = mmc.FAT32_RootClus;
        }
        EX(set_next_clus (&clus),__FALSE);
        sect = clus_to_sect (clus);
      }
    }

    EX(read_sector (sect + (idx >> 4)),__FALSE);
    frec              = (FILEREC *)ca.buf + (idx & 0x0F);
    frec->FileName[0] = 0xE5;

    -- ents;
    if (((idx & 0x0F) == 0x0F) || (ents == 0)) {
      /* Write last previously used sector as we are going to use next one. */
      EX(write_sector (sect + (idx >> 4)),__FALSE);
    }
  }

  if (!keep_data) {
    /* Reset FAT table linked clusters to 0. */
    EX(unlink_clus_chain (fcb->_firstClus),__FALSE);
  }

  /* Entries deleted successfully. */
  return (__TRUE);

fail:
  return (__FALSE);
}


/*--------------------------- rename_entries --------------------------------*/


static BOOL rename_entries (const char *new_name, IOB *fcb, U8 type) {
  /* Rename entries that fcb is pointing to to requested new_name. */
  FILEREC      old_frec;
  U8           name_lfn_f    = check_lfn (new_name); 
  U8           longer_f;
  U8           ents          = numOfEntries;

  /* Read last entry to keep some informations from it. */
  EX(read_last_entry (fcb, &old_frec),__FALSE);

  /* See if we can write over old entries. */
  longer_f     = 0;
  if (name_lfn_f) {
    if (ents == 1) {
      longer_f = 1;
    }
    else if (((strlen(new_name) + 12) / 13) > ents) {
      longer_f = 1;
    }
  }

  /* Delete old entries, but keep data. */
  EX(delete_entries (fcb, 1),__FALSE);

  if (longer_f) {
    /* Allocate new space for entries and write them. */

    /* If creation of new entries requested find unallocated entry */
    fcb->_firstClus = firstEntClus;
    if (alloc_name (new_name, fcb) == __FALSE) {
      /* If unable to find unallocated entry. */
      goto fail;
    }
  }

  /* Write new entries. */
  if (write_entries (new_name, fcb, type, &old_frec) == __FALSE) {
    /* Rename was unsuccessfull. */
    goto fail;
  }

  /* Rename successfull. */
  return(__TRUE);

fail:
  return (__FALSE);
}


/*--------------------------- write_dot_entries -----------------------------*/

static BOOL write_dot_entries (IOB *fcb) {
  /* Create "." and ".." directory entries. */
  FILEREC     *frec;
  U16          time, date;
  U32          idx           = 0;
  U32          clus          = fcb->_firstClus;
  U32          sect;

  /* Initialize local variables. */
  time = get_time ();
  date = get_date ();

  /* Clear the buffer. */
  memset (ca.buf, 0, 512);

  /* Create "." entry. */
  frec = (FILEREC *)ca.buf;
  memcpy (&frec->FileName[0], ".          ", 11);
  frec->Attr   = ATTR_DIRECTORY;
  set_u16 ((U8 *)&frec->CrtTime, time);
  set_u16 ((U8 *)&frec->CrtDate, date);
  set_u16 ((U8 *)&frec->LastAccDate, date);
  set_u16 ((U8 *)&frec->WriteTime, time);
  set_u16 ((U8 *)&frec->WriteDate, date);

  /* Copy this record to ".." entry. */
  memcpy (frec + 1, frec, sizeof (FILEREC));

  set_u16 ((U8 *)&frec->FirstClusHI, (fcb->_firstClus >> 16));
  set_u16 ((U8 *)&frec->FirstClusLO, (fcb->_firstClus      ));

  /* Create ".." entry, modify "." entry differences. */
  frec++;
  frec->FileName[1] = '.';

  /* For Root folder FirstClusHI and FirstClusLO are 0. */
  set_u16 ((U8 *)&frec->FirstClusHI, (startDirClus >> 16));
  set_u16 ((U8 *)&frec->FirstClusLO, (startDirClus      ));

  /* Calculate address of sector where write will start. */
  sect = clus_to_sect (clus);
  EX(write_sector (sect),__FALSE);

  /* Clear the remaining sectors in the cluster. */
  memset (ca.buf, 0, 2*sizeof (FILEREC));
  for (idx = 1; idx < mmc.SecPerClus; idx++) {
    EX(write_sector (sect + idx),__FALSE);
  }

  /* Position fcb to point to first entry after ".." entry. */
  fcb->fileID = 2;

  /* Entries written successfully. */
  return (__TRUE);
}


/*--------------------------- lfn_calc_chksum -------------------------------*/

static U8 lfn_calc_chksum (U8 *fn) {
  /* Calculate LFN checksum. */
  U32 i;
  U8  sum;

  sum = 0;
  for (i = 0; i < 11; i++) {
    sum = ((sum & 1) ? 0x80 : 0) + (sum >> 1) + fn[i];
  }
  return (sum);
}


/*--------------------------- lfn_copy_name ---------------------------------*/

static void lfn_copy_name (U8 *lfn, char *fn) {
  /* Copy LFN name to an entry */
  U8 val;
  U32 i;

  for (i = 0; i < 13; i++) {
    if (fn[i] == 0)   break;
    lfn[ChIndex[i]]   = fn[i];
    lfn[ChIndex[i]+1] = 0;
  }
  for (val = 0; i < 13; val = 0xFF, i++) {
    lfn[ChIndex[i]]   = val;
    lfn[ChIndex[i]+1] = val;
  }
}


/*--------------------------- lfn_cmp_name ----------------------------------*/

static BOOL lfn_cmp_name (U8 *lfr, char *fn) {
  /* Compare 13 chars of name with 13 chars of entry name, ignore case. */
  U32 i;

  for (i = 0; i < 13; i++) {
    if ((lfr[ChIndex[i]] ^ fn[i]) & ~0x20) {
      /* Characters different. */
      return (__FALSE);
    }
    if (fn[i] == 0) break;
  }
  return (__TRUE);
}


/*--------------------------- sfn_cmp_name ----------------------------------*/

static BOOL sfn_cmp_name (U8 *sfn, char *fn) {
  /* Compare 11 chars of name with 11 chars of entry name, ignore case. */
  U32 i;

  for (i = 0; i < 11; i++) {
    if ((sfn[i] ^ fn[i]) & ~0x20) {
      /* Characters different. */
      return (__FALSE);
    }
    if (fn[i] == 0) break;
  }
  return (__TRUE);
}


/*--------------------------- lfn_copy_info ---------------------------------*/

static void lfn_copy_info (S8 *fn, U8 *lfn) {
  /* Copy 13 chars from entry name to info name. */
  U32 i;

  for (i = 0; i < 13; i++) {
    fn[i] = lfn[ChIndex[i]];
  }
}


/*--------------------------- chk_param -------------------------------------*/

static BOOL chk_param (const char *par, const char *sp) {
  /* Search for paramter 'par' in the string 'sp'. */

  while (*sp != 0) {
    if (*sp++ == '/') {
      if (fn_cmp (par, sp) == __TRUE) {
        /* Found 'par' in the string 'sp'. */
        return (__TRUE);
      }
    }
  }
  return (__FALSE);
}


/*--------------------------- get_u16 ---------------------------------------*/

static U16 get_u16 (U8 *nr) {
  /* Read an unaligned U16 variable in correct Endian format. */

#ifdef __BIG_ENDIAN
  return ((nr[0] << 8) | nr[1]);
#else
  return ((nr[1] << 8) | nr[0]);
#endif
}


/*--------------------------- get_u32 ---------------------------------------*/

static U32 get_u32 (U8 *nr) {
  /* Read an unaligned U32 variable in correct Endian format. */

#ifdef __BIG_ENDIAN
  return ((nr[0] << 24) | (nr[1] << 16) | (nr[2] << 8) | nr[3]);
#else
  return ((nr[3] << 24) | (nr[2] << 16) | (nr[1] << 8) | nr[0]);
#endif
}


/*--------------------------- set_u16 ---------------------------------------*/

static void set_u16 (U8 *nr, U16 val) {
  /* Write an unaligned U16 variable in correct Endian format. */

#ifdef __BIG_ENDIAN
  nr[0] = val >> 8;
  nr[1] = val;
#else
  nr[1] = val >> 8;
  nr[0] = val;
#endif
}


/*--------------------------- set_var ---------------------------------------*/

static void set_u32 (U8 *nr, U32 val) {
  /* Write an unaligned U32 variable in correct Endian format. */

#ifdef __BIG_ENDIAN
  nr[0] = val >> 24;
  nr[1] = val >> 16;
  nr[2] = val >> 8
  nr[3] = val;
#else
  nr[3] = val >> 24;
  nr[2] = val >> 16;
  nr[1] = val >> 8;
  nr[0] = val;
#endif
}


/*----------------------------------------------------------------------------
 * end of file
 *---------------------------------------------------------------------------*/
