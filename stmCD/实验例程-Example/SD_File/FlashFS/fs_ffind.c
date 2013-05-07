/*----------------------------------------------------------------------------
 *      RL-ARM - FlashFS
 *----------------------------------------------------------------------------
 *      Name:    FS_FFIND.C 
 *      Purpose: File System Format Function
 *      Rev.:    V4.05
 *----------------------------------------------------------------------------
 *      This code is part of the RealView Run-Time Library.
 *      Copyright (c) 2004-2009 KEIL - An ARM Company. All rights reserved.
 *---------------------------------------------------------------------------*/

#include "File_Config.h"
#include <string.h>

/*--------------------------- ffind -----------------------------------------*/

int ffind (const char *pattern, FINFO *info) {
  /* Find a file that matches the search pattern. */
  IOB *fcb;
  const char *pat;
  char *ch1_ptr;
  char *ch2_ptr;
  char ch1,ch2;
  int handle;
  int len1,len2,len,len_aux;
  BOOL joker;

  START_LOCK (int);

  /* Find unused _iob[] structure. */
  if ((handle = fs_find_iob ()) == EOF) {
    /* Cannot find any unused _iob[] structure */
    RETURN (1);
  }

  fcb = &_iob[handle];
  fcb->drive = fs_get_drive (pattern);
  if (fcb->drive != DRV_NONE) {
    /* Skip drive letter 'X:' */
    pattern += 2;
  }
  else {
    fcb->drive = _DEF_DRIVE;
  }
  if (fcb->drive != DRV_MCARD) {
    /* Set drive parameters. */
    if (fs_set_params (fcb) == __FALSE) {
      RETURN (1);
    }
  }

  pat  = pattern;
  len1 = 0;
  len2 = 0;
  while (*pat != 0) {
    len1 ++;
    if (*pat == '\\') {
      len2 = len1;
    }
    pat ++;
  }
  pat = pattern + len2;

  if (strcmp (pat,"*.*") == 0) {
    joker = __TRUE;
    len1 = len2 = 0;
  }
  else {
    len1 = fs_strpos (pat, '*');
    len2 = strlen (pat);
    if (len1 == -1) {
      /* Joker character not found in pattern. */
      joker = __FALSE;
    }
    else {
      /* Joker character '*' found in pattern. */
      joker  = __TRUE;
      len2  -= (len1 + 1);
    }
  }

  for (;;) {
    if (fcb->drive == DRV_MCARD) {
      if (fat_ffind (pattern, info, fcb) == __FALSE) {
        RETURN (1);
      }
    }
    else {
      if (_ffind (info, fcb) == __FALSE) {
        RETURN (1);
      }
    }
    info->name[255] = 0;

    if (joker == __FALSE) {
      /* No joker character, must exactly match (case insensitive). */
      /* Check if name is same as pat (case insensitive). */
      ch1_ptr = (char *)&info->name;
      ch2_ptr = (char *) pat;
      while (*ch1_ptr) {
        ch1 = *ch1_ptr++;
        ch2 = *ch2_ptr++;
        if (ch1 >= 'a' && ch1 <= 'z') {
          ch1 &= ~0x20;
        }
        if (ch2 >= 'a' && ch2 <= 'z') {
          ch2 &= ~0x20;
        }
        if (ch1 ^ ch2) {
          /* Filename does not match pattern. */
          goto not_match;
        }
      }
found:fcb->fileID = info->fileID;
      if (fcb->drive == DRV_MCARD) {
        info->attrib = fcb->attrib;
        info->size   = fcb->fsize;
      }
      else {
        fcb->_fblock = 0;
        info->size   = __getfsize (fcb, __FALSE);
        info->attrib = 0;
      }
      RETURN (0);
    }
    else {
      /* Joker character found. */
      if (len1 == 0 && len2 == 0) {
        goto found;
      }
      if (len1) {
        ch1_ptr = (char *) pat;
        for (len_aux = 0; len_aux < len1; len_aux++) {
          /* Check pattern case insensitive. */
          ch1 = *ch1_ptr++;
          ch2 = info->name[len_aux];
          if (ch1 >= 'a' && ch1 <= 'z') {
            ch1 &= ~0x20;
          }
          if (ch2 >= 'a' && ch2 <= 'z') {
            ch2 &= ~0x20;
          }
          if (ch1 ^ ch2) {
            /* First part of filename does not match pattern. */
            goto not_match;
          }
        }
      }
      if (len2 == 0) {
        goto found;
      }
      len = strlen ((char *)info->name);
      if (len < len1+len2) {
        /* 'fname' not long enough. */
        continue;
      }
      /* Check last part of filename. */
      ch1_ptr = (char *) &pat[len1+1];
      for (len_aux = len-len2; len_aux < len; len_aux++) {
        /* Check pattern case insensitive. */
        ch1 = *ch1_ptr++;
        ch2 = info->name[len_aux];
        if (ch1 >= 'a' && ch1 <= 'z') {
          ch1 &= ~0x20;
        }
        if (ch2 >= 'a' && ch2 <= 'z') {
          ch2 &= ~0x20;
        }
        if (ch1 ^ ch2) {
          /* Last part of filename does not match pattern. */
          goto not_match;
        }
      }
      /* OK, last part of filename matches pattern. */
      goto found;
    }
not_match:
    continue;
  }

  END_LOCK;
}

/*----------------------------------------------------------------------------
 * end of file
 *---------------------------------------------------------------------------*/
