/*----------------------------------------------------------------------------
 *      RL-ARM - FlashFS
 *----------------------------------------------------------------------------
 *      Name:    FILE_CONFIG.C
 *      Purpose: Configuration of RL FlashFS by user
 *      Rev.:    V4.05
 *----------------------------------------------------------------------------
 *      This code is part of the RealView Run-Time Library.
 *      Copyright (c) 2004-2009 KEIL - An ARM Company. All rights reserved.
 *---------------------------------------------------------------------------*/

#include <File_Config.h>
#include <stdio.h>
#include <absacc.h>

/*----------------------------------------------------------------------------
 *      User configuration part
 *---------------------------------------------------------------------------*/

//-------- <<< Use Configuration Wizard in Context Menu >>> -----------------
//
// <e>Flash Drive
// ==============
// <i> Enable support Embedded Flash Drive [F:]
#define FL_DEV      0

//   <o>Target device Base address <0x0-0xFFFFF000:0x1000>
//   <i> Define the target device Base address.
//   <i> Default: 0x80000000
#define FL_BADR     0x80000000

//   <o>Device Size in bytes <0x10000-0xFFFFF000:0x8000>
//   <i> Define the size of Flash device
//   <i> Default: 0x100000 (1MB)
#define FL_SIZE     0x0200000

//   <o>Initial Content of Erased Memory <0=> 0x00 <0xFF=> 0xFF
//   <i> Define the initial value for erased Flash data
//   <i> Default: 0xFF
#define FL_INITV    0xFF

//   <s.80>Device Description file
//   <i> Specify a file name with a relative path
//   <i> Default: FS_FlashDev.h
#define FL_HFILE    "Flash\FS_FlashDev.h"

// </e>
// <e>SPI Flash Drive
// ==================
// <i> Enable support SPI Flash Drive [S:]
#define SF_DEV      0

//   <o>Initial Content of Erased Memory <0=> 0x00 <0xFF=> 0xFF
//   <i> Define the initial value for erased Flash data
//   <i> Default: 0xFF
#define SF_INITV    0xFF

//   <s.80>Device Description file
//   <i> Specify a file name with a relative path
//   <i> Default: FS_SPI_FlashDev.h
#define SF_HFILE    "FS_SPI_FlashDev.h"

// </e>
// <e>RAM Drive
// ============
// <i> Enable support for Embedded RAM Drive  [R:]
#define RAM_DEV     0

//   <o>Target device Base address <0x0-0xFFFFF000:0x1000>
//   <i> Define the target device Base address.
//   <i> Default: 0x81000000
#define RAM_BADR    0x81000000

//   <o>Device Size in bytes <0x4000-0xFFFFF000:0x4000>
//   <i> Define the size of RAM device
//   <i> Default: 0x40000
#define RAM_SIZE    0x040000

//   <o>Number of Sectors   <8=> 8  <16=> 16  <32=> 32 <64=> 64 <128=> 128
//   <i> Define number of virtual sectors for RAM device
//   <i> Default: 32
#define RAM_NSECT   8

// </e>
// <e>Memory Card Drive
// ====================
// <i> Enable support for Memory Card Drive  [M:]
#define MC_DEV      1

//   <o>File Data Cache  <0=> OFF  <2=> 1KB  <4=>  2KB <8=> 4KB 
//                       <16=> 8KB  <32=> 16KB  <64=> 32KB
//   <i> Define Data Cache buffer size for file IO. 
//   <i> Increase this number for faster r/w access.
//   <i> Default: 4 kB
#define MC_CSIZE    8

//   <e>Relocate Cache Buffer
//   <i> Locate Cache Buffer at a specific address.
//   <i> Some devices like NXP LPC23xx require a Cache buffer
//   <i> for DMA transfer located at specific address.
#define MC_RELOC    0

//   <o>Cache Buffer address <0x0000-0xFFFFFE00:0x200>
//   <i> Define the Cache buffer base address.
//   <i> For LPC23xx/24xx devices this is USB RAM
//   <i> starting at 0x7FD00000.
#define MC_CADR     0x7FD00000

//   </e>
// </e>
//   <o>Default Drive  <1=> Flash  <2=> SPI Flash  <3=> RAM  <4=> Memory Card
//   <i> This drive is used when a Drive letter is not provided
#define DEF_DRIVE   4

//   <o>CPU Clock Frequency [Hz]<0-100000000>
//   <i> Define the CPU Clock frequency used for
//   <i> flash programming and erasing
#define CPU_CLK     100000000

//------------- <<< end of configuration section >>> -----------------------

#if FL_DEV == 0 && RAM_DEV == 0 && MC_DEV == 0 && SF_DEV == 0
 #error All Drives disabled
#endif

/* Memory resources allocated by the Flash File System */

struct iob _iob[FOPEN_MAX];

/* Exported Defines to other modules */

U16 const _NFILE        = FOPEN_MAX;
U16 const _DEF_DRIVE    = DEF_DRIVE;
U32 const _CPU_CLK      = CPU_CLK;

/*----------------------------------------------------------------------------
 *      Flash Device configuration part
 *---------------------------------------------------------------------------*/

#if FL_DEV == 1
 #define DFB(size,badr)   { (U32)badr+FL_BADR, ((U32)(badr+size)-4)+FL_BADR }
 #include FL_HFILE

 /* Flash Device Configuration Table */
 struct DevConf const FlashDev [FL_NSECT] =  { FLASH_DEVICE };
 U16 const _FlashNumSect = FL_NSECT;
 U32 const _BlockFREE    = (U32)FL_INITV<<24 | FL_INITV<<16 | FL_INITV<<8 | FL_INITV;
 U32 const _BASE_ADR     = FL_BADR;
#else
 DEVCONF const FlashDev [1] = {0,0};
 U16 const _FlashNumSect = 0;
 U32 const _BlockFREE    = 0x00000000;
 U32 const _BASE_ADR     = FL_BADR;
#endif

/*----------------------------------------------------------------------------
 *      SPI Flash Device configuration part
 *---------------------------------------------------------------------------*/

#if SF_DEV == 1
 #define DSB(size,badr)   { (U32)badr, ((U32)(badr+size)-4) }
 #include SF_HFILE

 /* Flash Device Configuration Table */
 struct DevConf const SpiDev [SF_NSECT] =  { SPI_FLASH_DEVICE };
 U16 const _SpiNumSect   = SF_NSECT;
 U32 const _SpiBlFREE    = (U32)SF_INITV<<24 | SF_INITV<<16 | SF_INITV<<8 | SF_INITV;
#else
 DEVCONF const SpiDev [1] = {0,0};
 U16 const _SpiNumSect   = 0;
 U32 const _SpiBlFREE    = 0x00000000;
#endif

/*----------------------------------------------------------------------------
 *      RAM Device configuration part
 *---------------------------------------------------------------------------*/

#if RAM_DEV == 1
 #define RBS        ((RAM_SIZE / RAM_NSECT) & ~3)
 #define DRB(idx)   {(U32)RBS*idx+RAM_BADR, ((U32)(RBS*(idx+1))-4)+RAM_BADR}

 /* Ram Device Configuration Table */
 struct DevConf const RamDev [RAM_NSECT] =  {
  DRB(0),  DRB(1),  DRB(2),  DRB(3),  DRB(4),  DRB(5),  DRB(6),  DRB(7),
 #if RAM_NSECT > 8
  DRB(8),  DRB(9),  DRB(10), DRB(11), DRB(12), DRB(13), DRB(14), DRB(15),
 #endif
 #if RAM_NSECT > 16
  DRB(16), DRB(17), DRB(18), DRB(19), DRB(20), DRB(21), DRB(22), DRB(23),
  DRB(24), DRB(25), DRB(26), DRB(27), DRB(28), DRB(29), DRB(30), DRB(31),
 #endif
 #if RAM_NSECT > 32
  DRB(32), DRB(33), DRB(34), DRB(35), DRB(36), DRB(37), DRB(38), DRB(39),
  DRB(40), DRB(41), DRB(42), DRB(43), DRB(44), DRB(45), DRB(46), DRB(47),
  DRB(48), DRB(49), DRB(50), DRB(51), DRB(52), DRB(53), DRB(54), DRB(55),
  DRB(56), DRB(57), DRB(58), DRB(59), DRB(60), DRB(61), DRB(62), DRB(63),
 #endif
 #if RAM_NSECT > 64
  DRB(64), DRB(65), DRB(66), DRB(67), DRB(68), DRB(69), DRB(70), DRB(71),
  DRB(72), DRB(73), DRB(74), DRB(75), DRB(76), DRB(77), DRB(78), DRB(79),
  DRB(80), DRB(81), DRB(82), DRB(83), DRB(84), DRB(85), DRB(86), DRB(87),
  DRB(88), DRB(89), DRB(90), DRB(91), DRB(92), DRB(93), DRB(94), DRB(95),
  DRB(96), DRB(97), DRB(98), DRB(99), DRB(100),DRB(101),DRB(102),DRB(103),
  DRB(104),DRB(105),DRB(106),DRB(107),DRB(108),DRB(109),DRB(110),DRB(111),
  DRB(112),DRB(113),DRB(114),DRB(115),DRB(116),DRB(117),DRB(118),DRB(119),
  DRB(120),DRB(121),DRB(122),DRB(123),DRB(124),DRB(125),DRB(126),DRB(127),
 #endif
 };
 U16 const _RamNumSect = RAM_NSECT;
#else
 DEVCONF const RamDev [1] = {0,0};
 U16 const _RamNumSect = 0;
#endif

/*----------------------------------------------------------------------------
 *      Memory Card configuration part
 *---------------------------------------------------------------------------*/

#if MC_DEV == 1
 #if MC_RELOC == 1
  #define __AT_MC_CADR  __at(MC_CADR)
 #else
  #define __AT_MC_CADR
 #endif
 /* MC Cache Buffer for Data and FAT Caching. */
 U32 mc_cache[128 * (MC_CSIZE + 2)] __AT_MC_CADR;
 U16 const _MC_CSIZE = MC_CSIZE;
#else
/* Provide empty functions to reduce code size when MC not used. */

int fat_init (void) {
  /* Initialize FAT File System driver. */
  return (0);
}

BOOL fat_find_file (const char *fn, IOB *fcb) {
  /* Find a file in Flash Card Root Directory. */
  fn  = fn;
  fcb = fcb;
  return (__FALSE);
}

BOOL fat_set_fpos (IOB *fcb, U32 pos) {
  /* Set File Position pointer. */
  fcb = fcb;
  pos = pos;
  return (__FALSE);
}

U32 fat_read (IOB *fcb, U8 *buf, U32 len) {
  /* Read data from file at current file position. */
  fcb = fcb;
  buf = buf;
  len = len;
  return (0);
}

BOOL fat_write (IOB *fcb, const U8 *buf, U32 len) {
  /* Write data to file at current file position. */
  fcb = fcb;
  buf = buf;
  len = len;
  return (__FALSE);
}

U32 fat_free (void) {
  /* Calculate a free space for Flash Card. */
  return (0);
}

BOOL fat_delete (const char *fn, IOB *fcb) {
  /* Delete a file from Flash Card Root Directory. */
  fn  = fn;
  fcb = fcb;
  return (__FALSE);
}

BOOL fat_close_write (IOB *fcb) {
  /* Close an opened file, update FAT and Directory record. */
  fcb = fcb;
  return (__FALSE);
}

BOOL fat_rename (const char *old, const char *new, IOB *fcb) {
  /* Rename a file to new name. */
  old = old;
  new = new;
  fcb = fcb;
  return (__FALSE);
}

BOOL fat_create (const char *fn, IOB *fcb) {
  /* Create a file in Flash Card Root Directory. */
  fn  = fn;
  fcb = fcb;
  return (__FALSE);
}

BOOL fat_format (const char *label) {
  /* Format a Flash Card for FAT12 or FAT16. */
  label = label;
  return (__FALSE);
}

BOOL fat_ffind (const char *fn, FINFO *info, IOB *fcb) {
  /* Find a file in Flash Card Root Directory. */
  info = info;
  fcb  = fcb;
  return (__FALSE);
}

#endif

/*----------------------------------------------------------------------------
 * end of file
 *---------------------------------------------------------------------------*/
