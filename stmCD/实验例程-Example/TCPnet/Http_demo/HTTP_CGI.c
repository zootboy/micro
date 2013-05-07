/*----------------------------------------------------------------------------
 *      RL-ARM - TCPnet
 *----------------------------------------------------------------------------
 *      Name:    HTTP_CGI.C
 *      Purpose: HTTP Server CGI Module
 *      Rev.:    V4.05
 *----------------------------------------------------------------------------
 *      This code is part of the RealView Run-Time Library.
 *      Copyright (c) 2004-2009 KEIL - An ARM Company. All rights reserved.
 *---------------------------------------------------------------------------*/

#include <Net_Config.h>
#include <stdio.h>
#include <string.h>

/* ---------------------------------------------------------------------------
 * The HTTP server provides a small scripting language.
 *
 * The script language is simple and works as follows. Each script line starts
 * with a command character, either "i", "t", "c", "#" or ".".
 *   "i" - command tells the script interpreter to "include" a file from the
 *         virtual file system and output it to the web browser.
 *   "t" - command should be followed by a line of text that is to be output
 *         to the browser.
 *   "c" - command is used to call one of the C functions from the this file.
 *         It may be followed by the line of text. This text is passed to
 *         'cgi_func()' as a pointer to environment variable.
 *   "#' - command is a comment line and is ignored (the "#" denotes a comment)
 *   "." - denotes the last script line.
 *
 * --------------------------------------------------------------------------*/

/* http_demo.c */
extern U16 AD_in (U32 ch);
extern U8  get_button (void);

/* at_System.c */
extern  LOCALM localm[];
#define LocM   localm[NETIF_ETH]

/* Net_Config.c */
extern struct tcp_info tcp_socket[];
extern U8 const tcp_NumSocks;
extern U8 const http_EnAuth;
extern U8       http_auth_passw[20];

extern BOOL LEDrun;
extern void LED_out (U32 val);
extern BOOL LCDupdate;
extern U8   lcd_text[2][16+1];

/* Local variables. */
static U8 P2;
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

/* My structure of CGI status U32 variable. This variable is private for */
/* each HTTP Session and is not altered by HTTP Server. It is only set to  */
/* zero when the cgi_func() is called for the first time.                  */
typedef struct {
  U16 xcnt;
  U16 unused;
} MY_BUF;
#define MYBUF(p)        ((MY_BUF *)p)

/*----------------------------------------------------------------------------
 * HTTP Server Common Gateway Interface Functions
 *---------------------------------------------------------------------------*/

/*--------------------------- cgi_process_var -------------------------------*/

void cgi_process_var (U8 *qs) {
  /* This function is called by HTTP server to process the Querry_String   */
  /* for the CGI Form GET method. It is called on SUBMIT from the browser. */
  /*.The Querry_String.is SPACE terminated.                                */
  U8 *var;
  int s[4];

  var = (U8 *)alloc_mem (40);
  do {
    /* Loop through all the parameters. */
    qs = http_get_var (qs, var, 40);
    /* Check the returned string, 'qs' now points to the next. */
    if (var[0] != 0) {
      /* Returned string is non 0-length. */
      if (str_scomp (var, "ip=") == __TRUE) {
        /* My IP address parameter. */
        sscanf ((const char *)&var[3], "%d.%d.%d.%d",&s[0],&s[1],&s[2],&s[3]);
        LocM.IpAdr[0]   = s[0];
        LocM.IpAdr[1]   = s[1];
        LocM.IpAdr[2]   = s[2];
        LocM.IpAdr[3]   = s[3];
      }
      else if (str_scomp (var, "msk=") == __TRUE) {
        /* Net mask parameter. */
        sscanf ((const char *)&var[4], "%d.%d.%d.%d",&s[0],&s[1],&s[2],&s[3]);
        LocM.NetMask[0] = s[0];
        LocM.NetMask[1] = s[1];
        LocM.NetMask[2] = s[2];
        LocM.NetMask[3] = s[3];
      }
      else if (str_scomp (var, "gw=") == __TRUE) {
        /* Default gateway parameter. */
        sscanf ((const char *)&var[3], "%d.%d.%d.%d",&s[0],&s[1],&s[2],&s[3]);
        LocM.DefGW[0]   = s[0];
        LocM.DefGW[1]   = s[1];
        LocM.DefGW[2]   = s[2];
        LocM.DefGW[3]   = s[3];
      }
      else if (str_scomp (var, "pdns=") == __TRUE) {
        /* Default gateway parameter. */
        sscanf ((const char *)&var[5], "%d.%d.%d.%d",&s[0],&s[1],&s[2],&s[3]);
        LocM.PriDNS[0]  = s[0];
        LocM.PriDNS[1]  = s[1];
        LocM.PriDNS[2]  = s[2];
        LocM.PriDNS[3]  = s[3];
      }
      else if (str_scomp (var, "sdns=") == __TRUE) {
        /* Default gateway parameter. */
        sscanf ((const char *)&var[5], "%d.%d.%d.%d",&s[0],&s[1],&s[2],&s[3]);
        LocM.SecDNS[0]  = s[0];
        LocM.SecDNS[1]  = s[1];
        LocM.SecDNS[2]  = s[2];
        LocM.SecDNS[3]  = s[3];
      }
    }
  }while (qs);
  free_mem ((OS_FRAME *)var);
}


/*--------------------------- cgi_process_data ------------------------------*/

void cgi_process_data (U8 code, U8 *dat, U16 len) {
  /* This function is called by HTTP server to process the returned Data    */
  /* for the CGI Form POST method. It is called on SUBMIT from the browser. */
  /* Parameters:                                                            */
  /*   code  - callback context code                                        */
  /*           0 = www-url-encoded form data                                */
  /*           1 = filename for file upload (0-terminated string)           */
  /*           2 = file upload raw data                                     */
  /*           3 = end of file upload (file close requested)                */
  /*           4 = any xml encoded POST data (single or last stream)        */
  /*           5 = the same as 4, but with more xml data to follow          */
  /*               Use http_get_content_type() to check the content type    */  
  /*   dat   - pointer to POST received data                                */
  /*   len   - received data length                                         */
  U8 passw[12],retyped[12];
  U8 *var,stpassw;

  switch (code) {
    case 0:
      /* Url encoded form data received. */
      break;

    default:
      /* Ignore all other codes. */
      return;
  }

  P2 = 0;
  LEDrun = __TRUE;
  if (len == 0) {
    /* No data or all items (radio, checkbox) are off. */
    LED_out (P2);
    return;
  }
  stpassw = 0;
  var = (U8 *)alloc_mem (40);
  do {
    /* Parse all returned parameters. */
    dat = http_get_var (dat, var, 40);
    if (var[0] != 0) {
      /* Parameter found, returned string is non 0-length. */
      if (str_scomp (var, "led0=on") == __TRUE) {
        P2 |= 0x01;
      }
      else if (str_scomp (var, "led1=on") == __TRUE) {
        P2 |= 0x02;
      }
      else if (str_scomp (var, "led2=on") == __TRUE) {
        P2 |= 0x04;
      }
      else if (str_scomp (var, "led3=on") == __TRUE) {
        P2 |= 0x08;
      }
      else if (str_scomp (var, "led4=on") == __TRUE) {
        P2 |= 0x10;
      }
      else if (str_scomp (var, "led5=on") == __TRUE) {
        P2 |= 0x20;
      }
      else if (str_scomp (var, "led6=on") == __TRUE) {
        P2 |= 0x40;
      }
      else if (str_scomp (var, "led7=on") == __TRUE) {
        P2 |= 0x80;
      }
      else if (str_scomp (var, "ctrl=Browser") == __TRUE) {
        LEDrun = __FALSE;
      }
      else if (str_scomp (var, "pw=") == __TRUE) {
        /* Change password. */
        str_copy (passw, var+3);
        stpassw |= 1;
      }
      else if (str_scomp (var, "pw2=") == __TRUE) {
        /* Retyped password. */
        str_copy (retyped, var+4);
        stpassw |= 2;
      }
      else if (str_scomp (var, "lcd1=") == __TRUE) {
        /* LCD Module Line 1 text. */
        str_copy (lcd_text[0], var+5);
        LCDupdate = __TRUE;
      }
      else if (str_scomp (var, "lcd2=") == __TRUE) {
        /* LCD Module Line 2 text. */
        str_copy (lcd_text[1], var+5);
        LCDupdate = __TRUE;
      }
    }
  }while (dat);
  free_mem ((OS_FRAME *)var);
  LED_out (P2);

  if (stpassw == 0x03) {
    len = strlen ((const char *)passw);
    if (mem_comp (passw, retyped, len) == __TRUE) {
      /* OK, both entered passwords the same, change it. */
      str_copy (http_auth_passw, passw);
    }
  }
}


/*--------------------------- cgi_func --------------------------------------*/

U16 cgi_func (U8 *env, U8 *buf, U16 buflen, U32 *pcgi) {
  /* This function is called by HTTP server script interpreter to make a    */
  /* formated output for 'stdout'. It returns the number of bytes written   */
  /* to the output buffer. Hi-bit of return value (len is or-ed with 0x8000)*/
  /* is a repeat flag for the system script interpreter. If this bit is set */
  /* to 1, the system will call the 'cgi_func()' again for the same script  */
  /* line with parameter 'pcgi' pointing to a 4-byte buffer. This buffer    */
  /* can be used for storing different status variables for this function.  */
  /* It is set to 0 by HTTP Server on first call and is not altered by      */
  /* HTTP server for repeated calls. This function should NEVER write more  */
  /* than 'buflen' bytes to the buffer.                                     */
  /* Parameters:                                                            */
  /*   env    - environment variable string                                 */
  /*   buf    - HTTP transmit buffer                                        */
  /*   buflen - length of this buffer (500-1400 bytes - depends on MSS)     */
  /*   pcgi   - pointer to session local buffer used for repeated loops     */
  /*            This is a U32 variable - size is 4 bytes. Value is:         */
  /*            - on 1st call = 0                                           */
  /*            - 2nd call    = as set by this function on first call       */
  TCP_INFO *tsoc;
  U32 len = 0;
  U8 id, *lang;
  static U32 adv;

  switch (env[0]) {
    /* Analyze the environment string. It is the script 'c' line starting */
    /* at position 2. What you write to the script file is returned here. */
    case 'a' :
      /* Network parameters - file 'network.cgi' */
      switch (env[2]) {
        case 'i':
          /* Write the local IP address. The format string is included */
          /* in environment string of the script line.                 */
          len = sprintf((char *)buf,(const char *)&env[4],LocM.IpAdr[0],
                        LocM.IpAdr[1],LocM.IpAdr[2],LocM.IpAdr[3]);
          break;
        case 'm':
          /* Write local Net mask. */
          len = sprintf((char *)buf,(const char *)&env[4],LocM.NetMask[0],
                        LocM.NetMask[1],LocM.NetMask[2],LocM.NetMask[3]);
          break;
        case 'g':
          /* Write default gateway address. */
          len = sprintf((char *)buf,(const char *)&env[4],LocM.DefGW[0],
                        LocM.DefGW[1],LocM.DefGW[2],LocM.DefGW[3]);
          break;
        case 'p':
          /* Write primary DNS server address. */
          len = sprintf((char *)buf,(const char *)&env[4],LocM.PriDNS[0],
                        LocM.PriDNS[1],LocM.PriDNS[2],LocM.PriDNS[3]);
          break;
        case 's':
          /* Write secondary DNS server address. */
          len = sprintf((char *)buf,(const char *)&env[4],LocM.SecDNS[0],
                        LocM.SecDNS[1],LocM.SecDNS[2],LocM.SecDNS[3]);
          break;
      }
      break;

    case 'b':
      /* LED control - file 'led.cgi' */
      if (env[2] == 'c') {
        /* Select Control */
        len = sprintf((char *)buf,(const char *)&env[4],LEDrun ? "" : "selected",
                                                        LEDrun ? "selected" : "");
        break;
      }
      /* LED CheckBoxes */
      id = env[2] - '0';
      if (id > 7) {
        id = 0;
      }
      id = 1 << id;
      len = sprintf((char *)buf,(const char *)&env[4],(P2 & id) ? "checked" : "");
      break;

    case 'c':
      /* TCP status - file 'tcp.cgi' */
      while ((len + 150) < buflen) {
        tsoc = &tcp_socket[MYBUF(pcgi)->xcnt];
        MYBUF(pcgi)->xcnt++;
        /* 'sprintf' format string is defined here. */
        len += sprintf((char *)(buf+len),"<tr align=\"center\">");
        if (tsoc->State <= TCP_STATE_CLOSED) {
          len += sprintf ((char *)(buf+len),
                          "<td>%d</td><td>%s</td><td>-</td><td>-</td>"
                          "<td>-</td><td>-</td></tr>\r\n",
                          MYBUF(pcgi)->xcnt,state[tsoc->State]);
        }
        else if (tsoc->State == TCP_STATE_LISTEN) {
          len += sprintf ((char *)(buf+len),
                          "<td>%d</td><td>%s</td><td>-</td><td>-</td>"
                          "<td>%d</td><td>-</td></tr>\r\n",
                          MYBUF(pcgi)->xcnt,state[tsoc->State],tsoc->LocPort);
        }
        else {
          len += sprintf ((char *)(buf+len),
                          "<td>%d</td><td>%s</td><td>%d.%d.%d.%d</td>"
                          "<td>%d</td><td>%d</td><td>%d</td></tr>\r\n",
                          MYBUF(pcgi)->xcnt,state[tsoc->State],
                          tsoc->RemIpAdr[0],tsoc->RemIpAdr[1],
                          tsoc->RemIpAdr[2],tsoc->RemIpAdr[3],
                          tsoc->RemPort,tsoc->LocPort,tsoc->AliveTimer);
        }
        /* Repeat for all TCP Sockets. */
        if (MYBUF(pcgi)->xcnt == tcp_NumSocks) {
          break;
        }
      }
      if (MYBUF(pcgi)->xcnt < tcp_NumSocks) {
        /* Hi bit is a repeat flag. */
        len |= 0x8000;
      }
      break;

    case 'd':
      /* System password - file 'system.cgi' */
      switch (env[2]) {
        case '1':
          len = sprintf((char *)buf,(const char *)&env[4],
                        http_EnAuth ? "Enabled" : "Disabled");
          break;
        case '2':
          len = sprintf((char *)buf,(const char *)&env[4],http_auth_passw);
          break;
      }
      break;

    case 'e':
      /* Browser Language - file 'language.cgi' */
      lang = http_get_lang();
      if (strcmp ((const char *)lang, "en") == 0) {
        lang = "English";
      }
      else if (strcmp ((const char *)lang, "en-us") == 0) {
        lang = "English USA";
      }
      else if (strcmp ((const char *)lang, "en-gb") == 0) {
        lang = "English GB";
      }
      else if (strcmp ((const char *)lang, "de") == 0) {
        lang = "German";
      }
      else if (strcmp ((const char *)lang, "de-ch") == 0) {
        lang = "German CH";
      }
      else if (strcmp ((const char *)lang, "de-at") == 0) {
        lang = "German AT";
      }
      else if (strcmp ((const char *)lang, "fr") == 0) {
        lang = "French";
      }
      else if (strcmp ((const char *)lang, "sl") == 0) {
        lang = "Slovene";
      }
      else {
        lang = "Unknown";
      }
      len = sprintf((char *)buf,(const char *)&env[2],lang,http_get_lang());
      break;

    case 'f':
      /* LCD Module control - file 'lcd.cgi' */
      switch (env[2]) {
        case '1':
          len = sprintf((char *)buf,(const char *)&env[4],lcd_text[0]);
          break;
        case '2':
          len = sprintf((char *)buf,(const char *)&env[4],lcd_text[1]);
          break;
      }
      break;

    case 'g':
      /* AD Input - file 'ad.cgi' */
      switch (env[2]) {
        case '1':
          adv = AD_in (2);
          len = sprintf((char *)buf,(const char *)&env[4],adv);
          break;
        case '2':
          len = sprintf((char *)buf,(const char *)&env[4],(float)adv*3.3/1024);
          break;
        case '3':
          adv = (adv * 100) / 1024;
          len = sprintf((char *)buf,(const char *)&env[4],adv);
          break;
      }
      break;

    case 'x':
      /* AD Input - xml file 'ad.cgx' */
      adv = AD_in (2);
      len = sprintf((char *)buf,(const char *)&env[1],adv);
      break;

    case 'y':
      /* Button state - xml file 'button.cgx' */
      len = sprintf((char *)buf,"<checkbox><id>button%c</id><on>%s</on></checkbox>",
                    env[1],(get_button () & (1 << (env[1]-'0'))) ? "true" : "false");
      break;
  }
  return ((U16)len);
}


/*----------------------------------------------------------------------------
 * end of file
 *---------------------------------------------------------------------------*/
