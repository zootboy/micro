/*----------------------------------------------------------------------------
 *      RL-ARM - FlashFS
 *----------------------------------------------------------------------------
 *      Name:    FS_FLASHPRG.C
 *      Purpose: Default Flash Programming Functions
 *      Rev.:    V4.05
 *----------------------------------------------------------------------------
 *      This code is part of the RealView Run-Time Library.
 *      Copyright (c) 2004-2009 KEIL - An ARM Company. All rights reserved.
 *---------------------------------------------------------------------------*/

#include "File_Config.h"

/*--------------------------- fs_Init ---------------------------------------*/

__weak int fs_Init (U32 adr, U32 clk) {
  /* Library default fs_Init function. */
  adr = adr;
  clk = clk;
  return (0);
}


/*--------------------------- fs_EraseSector --------------------------------*/

__weak int fs_EraseSector (U32 adr)  {
  /* Library default fs_EraseSector function. */
  adr = adr;
  return (0);
}


/*--------------------------- fs_ProgramPage --------------------------------*/

__weak int fs_ProgramPage (U32 adr, U32 sz, U8 *buf)  {
  /* Library default fs_ProgramPage function. */
  adr = adr;
  sz  = sz;
  buf = buf;
  return (0);
}


/*--------------------------- fs_spi_Init -----------------------------------*/

__weak int fs_spi_Init (void) {
  /* Library default fs_spi_Init function. */
  return (0);
}


/*--------------------------- fs_spi_ReadData -------------------------------*/

__weak int fs_spi_ReadData (U32 adr, U32 sz, U8 *buf) {
  /* Library default fs_spi_ReadData function. */
  adr = adr;
  sz  = sz;
  buf = buf;
  return (0);
}


/*--------------------------- fs_spi_EraseSector ----------------------------*/

__weak int fs_spi_EraseSector (U32 adr) {
  /* Library default fs_spi_EraseSector function. */
  adr = adr;
  return (0);
}


/*--------------------------- fs_spi_ProgramPage ----------------------------*/

__weak int fs_spi_ProgramPage (U32 adr, U32 sz, U8 *buf) {
  /* Library default fs_spi_ProgramPage function. */
  adr = adr;
  sz  = sz;
  buf = buf;
  return (0);
}


/*----------------------------------------------------------------------------
 * end of file
 *---------------------------------------------------------------------------*/
