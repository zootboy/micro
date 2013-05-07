/*----------------------------------------------------------------------------
 *      RL-ARM - TCPnet
 *----------------------------------------------------------------------------
 *      Name:    TELNET_UIF.C
 *      Purpose: Telnet Server User Interface Module
 *      Rev.:    V4.05
 *----------------------------------------------------------------------------
 *      This code is part of the RealView Run-Time Library.
 *      Copyright (c) 2004-2009 KEIL - An ARM Company. All rights reserved.
 *---------------------------------------------------------------------------*/

#include <Net_Config.h>
#include <string.h>
#include <stdio.h>

/* Net_Config.c */
extern struct tcp_info tcp_socket[];
extern U8 const tcp_NumSocks;
extern U8 const tnet_EnAuth;
extern U8       tnet_auth_passw[20];

/* ANSI ESC Sequences for terminal control. */
#define CLS     "\033[2J"
#define TBLUE   "\033[37;44m"
#define TNORM   "\033[0m"

extern BOOL LEDrun;
extern BOOL LCDupdate;
extern U8   lcd_text[2][16+1];

/* My structure of a Telnet U32 storage variable. This variable is private */
/* for each Telnet Session and is not altered by Telnet Server. It is only */
/* set to zero when tnet_process_cmd() is called for the first time.       */
typedef struct {
  U8 id;
  U8 nmax;
  U8 idx;
} MY_BUF;
#define MYBUF(p)        ((MY_BUF *)p)

/* Local variables */
static U8 const tnet_header[] = {
  CLS "\r\n"
  "        " TBLUE
  "*=============================================================*\r\n" TNORM
  "        " TBLUE
  "*            Keil Embedded Telnet Server Demo v3.00           *\r\n" TNORM
  "        " TBLUE
  "*=============================================================*\r\n" TNORM
  };
static U8 const tnet_help1[] = {
  "\r\n\r\n"
  "    Available Commands:\r\n"
  "    ----------------------------\r\n"
  "    led xx      - write hexval xx to LED port\r\n"
  "    led         - enable running lights\r\n"
  "    adin x      - read AD converter intput x\r\n"
  "    meas n      - display n measurements\r\n"
  "    tcpstat     - display a tcp status\r\n"
  "    rinfo       - display remote machine info\r\n"
  "    lcdN text   - write a text to LCD line N\r\n"};
static U8 const tnet_help2[] = {
  "    passw [new] - change system password\r\n"
  "    passwd      - display current password\r\n"};
static U8 const tnet_help3[] = {
  "    help, ?     - display this help\r\n"
  "    bye         - disconnect\r\n\r\n"
  "    <ESC>,<^C>  - disconnect\r\n"
  "    <BS>        - delete Character left\r\n"
  "    <UP><DOWN>  - recall Command History\r\n"};

static U8 const meas_header[] = {
  "\r\n"
  " Nr.   ADIN0  ADIN1  ADIN2  ADIN3  ADIN4  ADIN5  ADIN6  ADIN7\r\n"
  "=============================================================="};

static U8 const tcp_stat[] = {
  CLS "\r\n"
  "     " TBLUE
  "=============================================================\r\n" TNORM
  "     " TBLUE
  " Socket   State       Rem_IP       Rem_Port  Loc_Port  Timer \r\n" TNORM
  "     " TBLUE
  "=============================================================\r\n" TNORM
  };

static char const state[][11] = {
  "FREE",
  "CLOSED",
  "LISTEN",
  "SYN_REC",
  "SYN_SENT",
  "FINW1",
  "FINW2",
  "CLOSING",
  "LAST_ACK",
  "TWAIT",
  "CONNECT"};

/*----------------------------------------------------------------------------
 *      Functions
 *---------------------------------------------------------------------------*/

extern void LED_out (U32 val);
extern U16 AD_in (U32 ch);

/*----------------------------------------------------------------------------
 *      Telnet CallBack Functions
 *---------------------------------------------------------------------------*/

/*--------------------------- tnet_cbfunc -----------------------------------*/

U16 tnet_cbfunc (U8 code, U8 *buf, U16 buflen) {
  /* This function is called by the Telnet Client to get formated system    */
  /* messages for different code values.                                    */
  /* Values for 'code':                                                     */
  /*    0 - initial header                                                  */
  /*    1 - prompt string                                                   */
  /*    2 - header for login only if authorization is enabled               */
  /*    3 - string 'Username' for login                                     */
  /*    4 - string 'Password' for login                                     */
  /*    5 - message 'Login incorrect'                                       */
  /*    6 - message 'Login timeout'                                         */
  /*    7 - Unsolicited messages from Server (ie. Basic Interpreter)        */
  U16 len = 0;

  /* Make a reference to disable compiler warning. */
  buflen = buflen;

  switch (code) {
    case 0:
      /* Write initial header after login. */
      len = str_copy (buf, (U8 *)&tnet_header);
      break;
    case 1:
      /* Write a prompt string. */
      len = str_copy (buf, "\r\nMcb1700> ");
      break;
    case 2:
      /* Write Login header. */
      len = str_copy (buf, CLS "\r\nKeil Embedded Telnet Server V3.00,"
                               " please login...\r\n");
      break;
    case 3:
      /* Write 'username' prompt. */
      len = str_copy (buf, "\r\nUsername: ");
      break;
    case 4:
      /* Write 'Password' prompt. */
      len = str_copy (buf, "\r\nPassword: ");
      break;
    case 5:
      /* Write 'Login incorrect'.message. */
      len = str_copy (buf, "\r\nLogin incorrect");
      break;
    case 6:
      /* Write 'Login Timeout' message. */
      len = str_copy (buf, "\r\nLogin timed out after 60 seconds.\r\n");
      break;
  }
  return (len);
}


/*--------------------------- tnet_process_cmd ------------------------------*/

U16 tnet_process_cmd (U8 *cmd, U8 *buf, U16 buflen, U32 *pvar) {
  /* This is a Telnet Client callback function to make a formatted output   */
  /* for 'stdout'. It returns the number of bytes written to the out buffer.*/
  /* Hi-bit of return value (len is or-ed with 0x8000) is a disconnect flag.*/
  /* Bit 14 (len is or-ed with 0x4000) is a repeat flag for the Tnet client.*/
  /* If this bit is set to 1, the system will call the 'tnet_process_cmd()' */
  /* again with parameter 'pvar' pointing to a 4-byte buffer. This buffer   */
  /* can be used for storing different status variables for this function.  */
  /* It is set to 0 by Telnet server on first call and is not altered by    */
  /* Telnet server for repeated calls. This function should NEVER write     */
  /* more than 'buflen' bytes to the buffer.                                */
  /* Parameters:                                                            */
  /*   cmd    - telnet received command string                              */
  /*   buf    - Telnet transmit buffer                                      */
  /*   buflen - length of this buffer (500-1400 bytes - depends on MSS)     */
  /*   pvar   - pointer to local storage buffer used for repeated loops     */
  /*            This is a U32 variable - size is 4 bytes. Value is:         */
  /*            - on 1st call = 0                                           */
  /*            - 2nd call    = as set by this function on first call       */
  TCP_INFO *tsoc;
  REMOTEM rm;
  U32 val,ch,temp;
  U16 len = 0;

  switch (MYBUF(pvar)->id) {
    case 0:
      /* First call to this function, the value of '*pvar' is 0 */
      break;

    case 1:
      /* Repeated call, command 'MEAS' measurements display. */
      while (len < buflen-80) {
        /* Let's use as much of the buffer as possible. */
        /* This will produce less packets and speedup the transfer. */
        len += sprintf ((char *)(buf+len), "\r\n%4d", MYBUF(pvar)->idx);
        for (val = 0; val < 8; val++) {
          len += sprintf ((char *)(buf+len), "%7d", AD_in(val));
        }
        if (++MYBUF(pvar)->idx >= MYBUF(pvar)->nmax) {
          /* OK, we are done. */
          return (len);
        }
      }
      /* Request a repeated call, bit 14 is a repeat flag. */
      return (len | 0x4000);

    case 2:
      /* Repeated call, TCP status display. */
      while (len < buflen-80) {
        /* Let's use as much of the buffer as possible. */
        /* This will produce less packets and speedup the transfer. */
        if (MYBUF(pvar)->idx == 0) {
          len += str_copy (buf, (U8 *)tcp_stat);
        }
        tsoc = &tcp_socket[MYBUF(pvar)->idx];
        len += sprintf   ((char *)(buf+len), "\r\n%9d %10s  ", MYBUF(pvar)->idx, 
                          state[tsoc->State]);
        if (tsoc->State <= TCP_STATE_CLOSED) {
          len += sprintf ((char *)(buf+len),
                          "        -             -         -       -\r\n");
        }
        else if (tsoc->State == TCP_STATE_LISTEN) {
          len += sprintf ((char *)(buf+len),
                          "        -             -     %5d       -\r\n",
                          tsoc->LocPort);
        }
        else {
          /* First temporary print for alignment. */
          sprintf ((char *)(buf+len+16),"%d.%d.%d.%d",tsoc->RemIpAdr[0],
                tsoc->RemIpAdr[1],tsoc->RemIpAdr[2],tsoc->RemIpAdr[3]);
          len += sprintf ((char *)(buf+len),"%15s    %5d    %5d     %4d\r\n",
                          buf+len+16,tsoc->RemPort,tsoc->LocPort,tsoc->AliveTimer);
        }
        if (++MYBUF(pvar)->idx >= tcp_NumSocks) {
          /* OK, we are done, reset the index counter for next callback. */
          MYBUF(pvar)->idx = 0;
          /* Setup a callback delay. This function will be called again after    */
          /* delay has expired. It is set to 20 system ticks 20 * 100ms = 2 sec. */
          tnet_set_delay (20);
          break;
        }
      }
      /* Request a repeated call, bit 14 is a repeat flag. */
      return (len |= 0x4000);
  }

  /* Simple Command line parser */
  len = strlen ((const char *)cmd);
  if (tnet_ccmp (cmd, "LED") == __TRUE) {
    /* 'LED' command received */
    if (len >= 5) {
      sscanf ((const char *)(cmd+4),"%x", &val);
      LED_out (val);
      len = 0;
      if (LEDrun == __TRUE) {
        len = str_copy (buf," --> Running Lights OFF");
        LEDrun = __FALSE;
      }
      return (len);
    }
    len = 0;
    if (LEDrun == __FALSE) {
      len = str_copy (buf," --> Running Lights ON");
      LEDrun = __TRUE;
    }
    return (len);
  }
  if (tnet_ccmp (cmd, "ADIN") == __TRUE) {
    /* 'ADIN' command received */
    if (len >= 6) {
      sscanf ((const char *)(cmd+5),"%d",&ch);
      val = AD_in (ch);
      len = sprintf ((char *)buf,"\r\n ADIN %d = %d",ch,val);
      return (len);
    }
  }
  if (tnet_ccmp (cmd, "BYE") == __TRUE) {
    /* 'BYE' command, send message and disconnect */
    len = str_copy (buf, "\r\nDisconnect...\r\n");
    /* Hi bit of return value is a disconnect flag */
    return (len | 0x8000);
  }

  if (tnet_ccmp (cmd, "PASSW") == __TRUE && tnet_EnAuth) {
    /* Change the system password. */
    if (len == 5) {
      /* Disable password. */
      tnet_auth_passw[0] = 0;
    }
    else {
      mem_copy (&tnet_auth_passw, &cmd[6], 20);
    }
    len = sprintf ((char *)buf, "\r\n OK, New Password: \"%s\"",tnet_auth_passw);
    return (len);
  }

  if (tnet_ccmp (cmd, "PASSWD") == __TRUE && tnet_EnAuth) {
    /* Only display the current system password. */
    len = sprintf ((char *)buf, "\r\n System Password: \"%s\"",tnet_auth_passw);
    return (len);
  }

  if (tnet_ccmp (cmd, "MEAS") == __TRUE) {
    /* During the repeated call to this function, the 'cmd' buffer is locked,  */
    /* so we can use it for our temporary storage. Each Telnet session has its */
    /* own buffer of size 96 bytes. We can use 95 bytes, last one is not free. */
    /* Here the local storage '*pvar' is initialized to 0 by Telnet Server.    */
    MYBUF(pvar)->id = 1;
    if (len > 5) {
      /* We must be careful here, because data is overlaid. */
      sscanf ((const char *)&cmd[5], "%d", &temp);
      MYBUF(pvar)->nmax = temp;
    }
    len = str_copy (buf,(U8 *)meas_header);
    if (MYBUF(pvar)->nmax) {
      /* Bit 14 is a repeat flag. */
      len |= 0x4000;
    }
    return (len);
  }

  if (tnet_ccmp (cmd, "TCPSTAT") == __TRUE) {
    /* Display a TCP status similar to that in HTTP_Demo example. */
    /* Here the local storage '*pvar' is initialized to 0 by Telnet Server.    */
    MYBUF(pvar)->id = 2;
    len = str_copy (buf, CLS);
    return (len | 0x4000);
  }

  if (tnet_ccmp (cmd, "RINFO") == __TRUE) {
    /* Display Remote Machine IP and MAC address. */
    tnet_get_info (&rm);
    len  = sprintf ((char *)buf,"\r\n Remote IP : %d.%d.%d.%d",
                    rm.IpAdr[0],rm.IpAdr[1],rm.IpAdr[2],rm.IpAdr[3]);
    len += sprintf ((char *)(buf+len),
                    "\r\n Remote MAC: %02X-%02X-%02X-%02X-%02X-%02X",
                    rm.HwAdr[0],rm.HwAdr[1],rm.HwAdr[2],
                    rm.HwAdr[3],rm.HwAdr[4],rm.HwAdr[5]);
    return (len);
  }

  if (tnet_ccmp (cmd, "LCD1") == __TRUE) {
    /* Write a text to LCD Module Line 1. */
    lcd_text[0][0] = 0;
    if (len > 5) {
      mem_copy (&lcd_text[0], &cmd[5], 16);
      LCDupdate = __TRUE;
    }
    return (0);
  }

  if (tnet_ccmp (cmd, "LCD2") == __TRUE) {
    /* Write a text to LCD Module Line 2. */
    lcd_text[1][0] = 0;
    if (len > 5) {
      mem_copy (&lcd_text[1], &cmd[5], 16);
      LCDupdate = __TRUE;
    }
    return (0);
  }

  if (tnet_ccmp (cmd, "HELP") == __TRUE || tnet_ccmp (cmd, "?") == __TRUE) {
    /* 'HELP' command, display help text */
    len = str_copy (buf,(U8 *)tnet_help1);
    if (tnet_EnAuth) {
      len += str_copy (buf+len,(U8 *)tnet_help2);
    }
    len += str_copy (buf+len,(U8 *)tnet_help3);
    return (len);
  }
  /* Unknown command, display message */
  len = str_copy  (buf, "\r\n==> Unknown Command: ");
  len += str_copy (buf+len, cmd);
  return (len);
}


/*----------------------------------------------------------------------------
 * end of file
 *---------------------------------------------------------------------------*/
