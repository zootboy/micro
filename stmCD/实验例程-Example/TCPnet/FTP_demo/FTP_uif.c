/*----------------------------------------------------------------------------
 *      RL-ARM - TCPnet
 *----------------------------------------------------------------------------
 *      Name:    FTP_UIF.C
 *      Purpose: FTP Server User Interface Module
 *      Rev.:    V4.05
 *----------------------------------------------------------------------------
 *      This code is part of the RealView Run-Time Library.
 *      Copyright (c) 2004-2009 KEIL - An ARM Company. All rights reserved.
 *---------------------------------------------------------------------------*/

#include <stdio.h>
#include <File_Config.h>

/*----------------------------------------------------------------------------
 * FTP Server File Access CallBack Functions
 *---------------------------------------------------------------------------*/

/*--------------------------- ftp_fopen -------------------------------------*/

void *ftp_fopen (U8 *fname, U8 *mode) {
  /* Open file 'fname' for reading or writing. Return file handle. */
  return (fopen ((const char *)fname, (const char *)mode));
}


/*--------------------------- ftp_fclose ------------------------------------*/

void ftp_fclose (void *file) {
  /* Close the file opened for reading or writing. */
  fclose (file);
}


/*--------------------------- ftp_fread -------------------------------------*/

U16 ftp_fread (void *file, U8 *buf, U16 len) {
  /* Read 'len' bytes from file to buffer 'buf'. The file will be closed, */
  /* when the number of bytes read is less than 'len'. */
  return (fread (buf, 1, len, file));
}


/*--------------------------- ftp_fwrite ------------------------------------*/

U16 ftp_fwrite (void *file, U8 *buf, U16 len) {
  /* Write 'len' bytes from buffer 'buf' to a file. */
  return (fwrite (buf, 1, len, file));
}


/*--------------------------- ftp_fdelete -----------------------------------*/

BOOL ftp_fdelete (U8 *fname) {
  /* Delete a file, return __TRUE on success. */
  if (fdelete((char *)fname) == 0) {
    return (__TRUE);
  }
  return (__FALSE);
}


/*--------------------------- ftp_frename -----------------------------------*/

BOOL ftp_frename (U8 *fname, U8 *newn) {
  /* Rename a file, return __TRUE on success. */
  if (frename((char *)fname, (char *)newn) == 0) {
    return (__TRUE);
  }
  return (__FALSE);
}


/*--------------------------- ftp_ffind -------------------------------------*/

U16 ftp_ffind (U8 *buf, U8 *mask, U16 len) {
  /* List a file directory. */
  static FINFO info;
  U32 rlen,v;
  U8 *tp;

  if (len & 0x8000) {
    /* First ffind, initialize the info. */
    info.fileID = 0;
    len &= 0x7FFF;
  }
  rlen = 0;
next:
  if (ffind ((char *)mask, &info) == 0) {
    /* File found, print file information. */
    if (info.name[0] == '.') {
      if ((info.name[1] == 0) || (info.name[1] == '.' && info.name[2]) == 0) {
        /* Ignore the '.' and '..' folders. */
        goto next;
      }
    }
    rlen  = sprintf ((char *)buf,"%02d-%02d-%02d", info.time.mon,
                                                   info.time.day,
                                                   info.time.year%100);
    /* Convert time to "AM/PM" format. */
    v = info.time.hr % 12;
    if (v == 0) v = 12;
    if (info.time.hr < 12) tp = "AM";
    else                   tp = "PM";
    rlen += sprintf ((char *)&buf[rlen],"  %02d:%02d%s",v,info.time.min,tp);
    if (info.attrib & ATTR_DIRECTORY) {
      rlen += sprintf ((char *)&buf[rlen],"%-21s","       <DIR>");
    }
    else {
      rlen += sprintf ((char *)&buf[rlen],"%21d", info.size);
    }
    rlen += sprintf ((char *)&buf[rlen]," %s\r\n", info.name);
  }
  return (rlen);
}


/*----------------------------------------------------------------------------
 * end of file
 *---------------------------------------------------------------------------*/
