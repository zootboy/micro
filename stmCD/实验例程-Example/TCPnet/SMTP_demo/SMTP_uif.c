/*----------------------------------------------------------------------------
 *      RL-ARM - TCPnet
 *----------------------------------------------------------------------------
 *      Name:    SMTP_UIF.C
 *      Purpose: SMTP Client User Interface Module
 *      Rev.:    V4.05
 *----------------------------------------------------------------------------
 *      This code is part of the RealView Run-Time Library.
 *      Copyright (c) 2004-2009 KEIL - An ARM Company. All rights reserved.
 *---------------------------------------------------------------------------*/

#include <Net_Config.h>
#include <string.h>
#include <stdio.h>

/* Email definitions */
#define MAIL_FROM       "mcb@keil.com"
#define RCPT_TO         "somebody@keil.com"
#define SMTP_USER       "user"
#define SMTP_PASSWORD   "password"
#define MAIL_SUBJECT    "Reported measurements"

#define MSG_HEADER                                                    \
  "Hello!\r\n\r\n"                                                    \
  "This is measurement report sent from '%s' embedded system.\r\n"    \
  "Measurements are taken from analog inputs AIN0 - AIN7\r\n\r\n"     \
  "--------------------------------------------------------------\r\n"

#define MSG_FOOTER                                                    \
  "--------------------------------------------------------------\r\n"\
  "The end of measurements.\r\n\r\n"                                  \
  "Bye..."


/* My structure of SMTP U32 storage variable. This variable is private and  */
/* is not altered by SMTP Client. It is only set to zero when smtp_cbfunc() */
/* is called for the first time.  */
typedef struct {
  U8  id;
  U16 idx;
} MY_BUF;
#define MYBUF(p)        ((MY_BUF *)p)

/* Net_Config.c */
extern U8 lhost_name[];

/*----------------------------------------------------------------------------
 *      Functions
 *---------------------------------------------------------------------------*/

extern U16 AD_in (U32 ch);

/*----------------------------------------------------------------------------
 *      SMTP CallBack Functions
 *---------------------------------------------------------------------------*/

/*--------------------------- smtp_cbfunc -----------------------------------*/

U16 smtp_cbfunc (U8 code, U8 *buf, U16 buflen, U32 *pvar) {
  /* This function is called by the SMTP client to get email parameters and */
  /* data. It returns the number of bytes written to the output buffer.     */
  /* Hi-bit of return value (len is or-ed with 0x8000) is a repeat flag the */
  /* SMTP client. If this bit is set to 1, the system will call this func   */
  /* again with parameter 'pvar' pointing to a 4-byte buffer. This buffer   */
  /* can be used for storing different status variables for this function.  */
  /* It is set to 0 by SMTP client on first call and is not altered by SMTP */
  /* client for repeated calls. This function should NEVER write more than  */
  /* 'buflen' bytes to the buffer.                                          */
  /* Parameters:                                                            */
  /*   code   - function code with following values:                        */
  /*             0 - Username:   - for SMTP authentication if requested     */
  /*             1 - Password:   - for SMTP authentication if requested     */
  /*             2 - 'From   : ' - get email address of the sender          */
  /*             3 - 'To     : ' - get email address of recipient           */
  /*             4 - 'Subject: ' - get subject of email                     */
  /*             5 - 'Data   : ' - get email data in plain ascii format     */
  /*   buf    - SMTP transmit buffer                                        */
  /*   buflen - length of this buffer (500-1400 bytes - depends on MSS)     */
  /*   pvar   - pointer to local storage buffer used for repeated loops     */
  /*            This is a U32 variable - size is 4 bytes. Value is:         */
  /*            - on 1st call = 0                                           */
  /*            - 2nd call    = as set by this function on first call       */
  U32 i,len = 0;

  switch (code) {
    case 0:
      /* Enter Username for SMTP Server authentication. */
      len = str_copy (buf, SMTP_USER);
      break;

    case 1:
      /* Enter Password for SMTP Server authentication. */
      len = str_copy (buf, SMTP_PASSWORD);
      break;

    case 2:
      /* Enter email address of the sender. */
      len = str_copy (buf, MAIL_FROM);
      break;

    case 3:
      /* Enter email address of the recipient. */
      len = str_copy (buf, RCPT_TO);
      break;

    case 4:
      /* Enter email subject. */
      len = str_copy (buf, MAIL_SUBJECT);
      break;

    case 5:
      /* Enter email data. */
      switch (MYBUF(pvar)->id) {
        case 0:
          /* First call, enter an email header text. */
          len = sprintf ((char *)buf, MSG_HEADER, lhost_name);
          MYBUF(pvar)->id  = 1;
          MYBUF(pvar)->idx = 1;
          goto rep;

        case 1:
          /* Add email message body. */
          for (len = 0; len < buflen-150; ) {
            /* Let's use as much of the buffer as possible. */
            /* This will produce less packets and speedup the transfer. */
            len += sprintf ((char *)(buf+len), "%d. ",MYBUF(pvar)->idx);
            for (i = 0; i < 8; i++) {
              len += sprintf ((char *)(buf+len), "AD%d= %d  ",i,AD_in(i));
            }
            len += str_copy (buf+len, "\r\n");
            if (++MYBUF(pvar)->idx > 500) {
              MYBUF(pvar)->id = 2;
              break;
            }
          }
          /* Request a repeated call, bit 15 is a repeat flag. */
rep:      len |= 0x8000;
          break;

        case 2:
          /* Last one, add a footer text to this email. */
          len = str_copy (buf, MSG_FOOTER);
          break;
      }
  }
  return ((U16)len);
}


/*--------------------------- smtp_accept_auth ------------------------------*/

BOOL smtp_accept_auth (U8 *srv_ip) {
  /* SMTP server with address 'srv_ip' is asking for user authentication. */
  /* Return value: __TRUE  = use the authentication                       */
  /*               __FALSE = do not use the authentication                */

  /* Accept the authentication. */
  return (__TRUE);
}

/*----------------------------------------------------------------------------
 * end of file
 *---------------------------------------------------------------------------*/
