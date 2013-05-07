/*----------------------------------------------------------------------------
 *      RL-ARM - FlashFS
 *----------------------------------------------------------------------------
 *      Name:    FS_FINIT.C 
 *      Purpose: Flash File System Init Function
 *      Rev.:    V4.05
 *----------------------------------------------------------------------------
 *      This code is part of the RealView Run-Time Library.
 *      Copyright (c) 2004-2009 KEIL - An ARM Company. All rights reserved.
 *---------------------------------------------------------------------------*/

#include "File_Config.h"

extern U32 const _BASE_ADR;
extern U32 const _CPU_CLK;

/*---------------------------------------------------------------------------*/

__asm void $$FlashFS$$version (void) {
   /* Export a version number symbol for a version control. */

                EXPORT  __FS_ARM_VER

__FS_ARM_VER    EQU     0x405
}


/*--------------------------- fs_init ---------------------------------------*/

int finit (void) {
  /* Initialize the Flash File System. */
  int res;

  START_LOCK (int);

  res  = fs_Init (_BASE_ADR, _CPU_CLK) << 8;
  res |= fs_spi_Init () << 16;
  res |= fat_init ();

  RETURN (res);

  END_LOCK;
}

/*----------------------------------------------------------------------------
 * end of file
 *---------------------------------------------------------------------------*/
