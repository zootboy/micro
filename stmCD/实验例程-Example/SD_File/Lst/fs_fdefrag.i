#line 1 "FlashFS\\fs_fdefrag.c"









 

#line 1 "d:\\Keil\\ARM\\RV31\\INC\\File_Config.h"









 




#line 1 "d:\\Keil\\ARM\\RV31\\INC\\RTL.h"









 




 

 


#line 27 "d:\\Keil\\ARM\\RV31\\INC\\RTL.h"







 typedef unsigned int   size_t;


typedef signed char     S8;
typedef unsigned char   U8;
typedef short           S16;
typedef unsigned short  U16;
typedef int             S32;
typedef unsigned int    U32;
typedef long long       S64;
typedef unsigned long long U64;
typedef unsigned char   BIT;
typedef unsigned int    BOOL;

#line 54 "d:\\Keil\\ARM\\RV31\\INC\\RTL.h"



 





 
typedef U32 OS_SEM[2];

 

typedef U32 OS_MBX[];

 
typedef U32 OS_MUT[3];

 
typedef U32 OS_TID;

 
typedef void *OS_ID;

 
typedef U32 OS_RESULT;

 












 




#line 182 "d:\\Keil\\ARM\\RV31\\INC\\RTL.h"



 



 
extern void      os_set_env    (void);
extern void      rt_sys_init   (void (*task)(void), U8 priority, void *stk);
extern void      rt_tsk_pass   (void);
extern OS_TID    rt_tsk_self   (void);
extern OS_RESULT rt_tsk_prio   (OS_TID task_id, U8 new_prio);
extern OS_TID    rt_tsk_create (void (*task)(void), U8 priority, void *stk, void *argv);
extern OS_RESULT rt_tsk_delete (OS_TID task_id);

#line 218 "d:\\Keil\\ARM\\RV31\\INC\\RTL.h"

extern void      _os_sys_init(U32 p, void (*task)(void), U32 prio_stksz,
                                     void *stk)                        __svc_indirect(0);
extern OS_TID    _os_tsk_create (U32 p, void (*task)(void), U32 prio_stksz,
                                        void *stk, void *argv)         __svc_indirect(0);
extern OS_TID    _os_tsk_create_ex (U32 p, void (*task)(void *), U32 prio_stksz,
                                           void *stk, void *argv)      __svc_indirect(0);
extern OS_TID    _os_tsk_self (U32 p)                                  __svc_indirect(0);
extern void      _os_tsk_pass (U32 p)                                  __svc_indirect(0);
extern OS_RESULT _os_tsk_prio (U32 p, OS_TID task_id, U8 new_prio)     __svc_indirect(0);
extern OS_RESULT _os_tsk_delete (U32 p, OS_TID task_id)                __svc_indirect(0);

 
extern OS_RESULT rt_evt_wait (U16 wait_flags,  U16 timeout, BOOL and_wait);
extern void      rt_evt_set  (U16 event_flags, OS_TID task_id);
extern void      rt_evt_clr  (U16 clear_flags, OS_TID task_id);
extern U16       rt_evt_get  (void);







extern OS_RESULT _os_evt_wait(U32 p, U16 wait_flags, U16 timeout,
                                     BOOL and_wait)                    __svc_indirect(0);
extern void      _os_evt_set (U32 p, U16 event_flags, OS_TID task_id)  __svc_indirect(0);
extern void      _os_evt_clr (U32 p, U16 clear_flags, OS_TID task_id)  __svc_indirect(0);
extern U16       _os_evt_get (U32 p)                                   __svc_indirect(0);
extern void      isr_evt_set (U16 event_flags, OS_TID task_id);

 
extern void      rt_sem_init (OS_ID semaphore, U16 token_count);
extern OS_RESULT rt_sem_send (OS_ID semaphore);
extern OS_RESULT rt_sem_wait (OS_ID semaphore, U16 timeout);





extern void      _os_sem_init (U32 p, OS_ID semaphore, 
                                      U16 token_count)                 __svc_indirect(0);
extern OS_RESULT _os_sem_send (U32 p, OS_ID semaphore)                 __svc_indirect(0);
extern OS_RESULT _os_sem_wait (U32 p, OS_ID semaphore, U16 timeout)    __svc_indirect(0);
extern void      isr_sem_send (OS_ID semaphore);

 
extern void      rt_mbx_init  (OS_ID mailbox, U16 mbx_size);
extern OS_RESULT rt_mbx_send  (OS_ID mailbox, void *p_msg,    U16 timeout);
extern OS_RESULT rt_mbx_wait  (OS_ID mailbox, void **message, U16 timeout);
extern OS_RESULT rt_mbx_check (OS_ID mailbox);







extern void      _os_mbx_init (U32 p, OS_ID mailbox, U16 mbx_size)     __svc_indirect(0);
extern OS_RESULT _os_mbx_send (U32 p, OS_ID mailbox, void *message_ptr,
                                      U16 timeout)                     __svc_indirect(0);
extern OS_RESULT _os_mbx_wait (U32 p, OS_ID mailbox, void  **message,
                                      U16 timeout)                     __svc_indirect(0);
extern OS_RESULT _os_mbx_check (U32 p, OS_ID mailbox)                  __svc_indirect(0);
extern void      isr_mbx_send (OS_ID mailbox, void *message_ptr);
extern OS_RESULT isr_mbx_receive (OS_ID mailbox, void **message);

 
extern void      rt_mut_init    (OS_ID mutex);
extern OS_RESULT rt_mut_release (OS_ID mutex);
extern OS_RESULT rt_mut_wait    (OS_ID mutex, U16 timeout);





extern void      _os_mut_init (U32 p, OS_ID mutex)                     __svc_indirect(0);
extern OS_RESULT _os_mut_release (U32 p, OS_ID mutex)                  __svc_indirect(0);
extern OS_RESULT _os_mut_wait (U32 p, OS_ID mutex, U16 timeout)        __svc_indirect(0);

 
extern void      rt_dly_wait (U16 delay_time);
extern void      rt_itv_set  (U16 interval_time);
extern void      rt_itv_wait (void);





extern void      _os_dly_wait (U32 p, U16 delay_time)                  __svc_indirect(0);
extern void      _os_itv_set (U32 p, U16 interval_time)                __svc_indirect(0);
extern void      _os_itv_wait (U32 p)                                  __svc_indirect(0);

 
extern OS_ID     rt_tmr_create (U16 tcnt, U16 info);
extern OS_ID     rt_tmr_kill   (OS_ID timer);




extern OS_ID     _os_tmr_create (U32 p, U16 tcnt, U16 info)            __svc_indirect(0);
extern OS_ID     _os_tmr_kill (U32 p, OS_ID timer)                     __svc_indirect(0);

 
extern void      rt_tsk_lock   (void);
extern void      rt_tsk_unlock (void);




extern void      _os_tsk_lock (U32 p)                                  __svc_indirect(0);
extern void      _os_tsk_unlock (U32 p)                                __svc_indirect(0);

 
extern int       _init_box (void *box_mem, U32 box_size, U32 blk_size);
extern void     *_alloc_box (void *box_mem);
extern void     *_calloc_box (void *box_mem);
extern int       _free_box (void *box_mem, void *box);








 




 

typedef struct {                         
  U8  hr;                                
  U8  min;                               
  U8  sec;                               
  U8  day;                               
  U8  mon;                               
  U16 year;                              
} RL_TIME;

typedef struct {                         
  S8  name[256];                         
  U32 size;                              
  U16 fileID;                            
  U8  attrib;                            
  RL_TIME time;                          
} FINFO;

extern int finit (void);
extern int fdelete (const char *filename);
extern int frename (const char *oldname, const char *newname);
extern int ffind (const char *pattern, FINFO *info);
extern U64 ffree (const char *drive);
extern int fformat (const char *drive);
extern int fanalyse (const char *drive);
extern int fcheck (const char *drive);
extern int fdefrag (const char *drive);

 




 

 



 






 
#line 403 "d:\\Keil\\ARM\\RV31\\INC\\RTL.h"

 
#line 416 "d:\\Keil\\ARM\\RV31\\INC\\RTL.h"

 





 
#line 430 "d:\\Keil\\ARM\\RV31\\INC\\RTL.h"

 




 



extern void init_TcpNet (void);
extern void main_TcpNet (void);
extern void timer_tick (void);
extern U8   udp_get_socket (U8 tos, U8 opt, 
                            U16 (*listener)(U8 socket, U8 *remip, U16 port, U8 *buf, U16 len));
extern BOOL udp_release_socket (U8 socket);
extern BOOL udp_open (U8 socket, U16 locport);
extern BOOL udp_close (U8 socket);
extern BOOL udp_mcast_ttl (U8 socket, U8 ttl);
extern U8  *udp_get_buf (U16 size);
extern BOOL udp_send (U8 socket, U8 *remip, U16 remport, U8 *buf, U16 dlen);
extern U8   tcp_get_socket (U8 type, U8 tos, U16 tout,
                            U16 (*listener)(U8 socket, U8 event, U8 *buf, U16 len));
extern BOOL tcp_release_socket (U8 socket);
extern BOOL tcp_listen (U8 socket, U16 locport);
extern BOOL tcp_connect (U8 socket, U8 *remip, U16 remport, U16 locport);
extern U8  *tcp_get_buf (U16 size);
extern U16  tcp_max_dsize (U8 socket);
extern BOOL tcp_check_send (U8 socket);
extern U8   tcp_get_state (U8 socket);
extern BOOL tcp_send (U8 socket, U8 *buf, U16 dlen);
extern BOOL tcp_close (U8 socket);
extern BOOL tcp_abort (U8 socket);
extern void tcp_reset_window (U8 socket);
extern BOOL arp_cache_ip (U8 *ipadr, U8 type);
extern void ppp_listen (char const *user, char const *passw);
extern void ppp_connect (char const *dialnum, char const *user, char const *passw);
extern void ppp_close (void);
extern BOOL ppp_is_up (void);
extern void slip_listen (void);
extern void slip_connect (char const *dialnum);
extern void slip_close (void);
extern BOOL slip_is_up (void);
extern U8   get_host_by_name (U8 *hostn, void (*cbfunc)(U8 event, U8 *host_ip));
extern BOOL smtp_connect (U8 *ipadr, U16 port, void (*cbfunc)(U8 event));
extern void dhcp_disable (void);
extern BOOL igmp_join (U8 *group_ip);
extern BOOL igmp_leave (U8 *group_ip);
extern BOOL snmp_trap (U8 *manager_ip, U8 gen_trap, U8 spec_trap, U16 *obj_list);
extern BOOL snmp_set_community (const char *community);






 
  

 
#line 16 "d:\\Keil\\ARM\\RV31\\INC\\File_Config.h"

 






 



 


 
typedef struct DevConf {
  U32 bStart;
  U32 bEnd;
} DEVCONF;

 
typedef struct iob {
  U16   fileID;                          
  U16   flags;                           
  U8    drive;                           
  U8    attrib;                          
  U16   NumSect;                         
  U32   InitVal;                         
  void *DevCfg;                          
  U16   _fblock;                         
  U16   _fidx;                           
  U32   _fbot;                           
  U32   _ftop;                           
  U32   _firstClus;                      
  U32   _lastEntClus;                    
  U8    _currDatSect;                    
  U32   _currDatClus;                    
  U32   fsize;                           
  U32   fpos;                            
} IOB;

 

 
#line 69 "d:\\Keil\\ARM\\RV31\\INC\\File_Config.h"

 




 
typedef struct falloc {
  U32 end;
  U16 fileID;
  U16 index;
} FALLOC;

 
typedef struct fdbuf {
  U16 index;
  U16 fblock;
  U32 fbot;
  U32 ftop;
} FDBUF;

 
typedef struct fatinfo {
  U32 BootRecSec;                        
  U8  FatType;                           
  U8  NumOfFat;                          
  U8  SecPerClus;                        
  U16 FatSize;                           
  U16 RsvdSecCnt;                        
  U32 DskSize;                           
  U32 DataSecCnt;                        
  U16 RootEntCnt;                        
  U16 BytesPerSec;                       
  U32 DataClusCnt;                       
  U16 RootDirAddr;                       
  U16 RootSecCnt;                        
  U32 ClusSize;                          
  U16 EntsPerClus;                       
                                         
  U16 FAT32_ExtFlags;                    
  U32 FAT32_RootClus;                    
  U16 FAT32_FSInfo;                      
  U16 FAT32_BkBootSec;                   
} FATINFO;

 
typedef struct filerec {
  U8  FileName[11];                      
  U8  Attr;                              
  U8  NTRsvd;                            
  U8  CrtTimeTenth;                      
  U16 CrtTime;                           
  U16 CrtDate;                           
  U16 LastAccDate;                       
  U16 FirstClusHI;                       
  U16 WriteTime;                         
  U16 WriteDate;                         
  U16 FirstClusLO;                       
  U32 FileSize;                          
} FILEREC;

 
typedef struct lfn_filerec {
  U8  Ordinal;                           
  U8  Unichar0[10];                      
  U8  Attr;                              
  U8  Rsvd;                              
  U8  Checksum;                          
  U8  Unichar1[12];                      
  U16 FirstClusLO;                       
  U8  Unichar2[4];                       
} LFN_FILEREC;



 
typedef struct devpar {
  U8  FatType;                           
  U8  SecClus;                           
  U8  SecClus32;                         
  U16 NumHeads;                          
  U8  NumSect;                           
  U16 NumCyl;                            
  U16 BootRecSec;                        
} DEVPAR;

 
#line 164 "d:\\Keil\\ARM\\RV31\\INC\\File_Config.h"

 


 





 






 
typedef struct fcache {
  U32 sect;
  U8  *buf;
  BIT dirty;
} FCACHE;

 
typedef struct dcache {
  U32 sect;
  U32 csect;
  U8  *buf;
  U8  *cbuf;
  U8  nwr;
  U8  nrd;
} DCACHE;

 
typedef struct mmcfg {
  U32 sernum;
  U32 blocknr;
  U16 read_blen;
  U16 write_blen;
} MMCFG;

 
extern struct iob _iob[];
extern U32    mc_cache[];

 
extern struct DevConf const FlashDev [];
extern struct DevConf const SpiDev[];
extern struct DevConf const RamDev [];
extern U16 const _FlashNumSect;
extern U16 const _SpiNumSect;
extern U16 const _RamNumSect;
extern U32 const _BlockFREE;
extern U32 const _SpiBlFREE;
extern U16 const _NFILE;
extern U16 const _DEF_DRIVE;
extern U16 const _MC_CSIZE;

 
extern int  _fdelete (IOB *fcb);
extern int  _fcreate (const char *fname, IOB *fcb);
extern int  _frename (const char *filename, IOB *fcb);
extern BOOL _ffind (FINFO *info, IOB *fcb);

 
extern int  __fopen (const char *fname, int openmode);
extern int  __fclose (int handle);
extern int  __write (int handle, const U8 *buf, U32 len);
extern int  __flushbuf (int handle);
extern int  __read (int handle, U8 *buf, U32 len);
extern int  __setfpos (int handle, U32 pos);
extern U32  __getfsize (IOB *fcb, BOOL set_fidx);


 
extern U16  fs_get_freeID (U32 maxID, IOB *fcb);
extern U32  fs_get_freeMem (U32 block, IOB *fcb);
extern BOOL fs_check_fwopen (U32 block, IOB *fcb);
extern void fs_mark_freeMem (IOB *fcb);
extern BOOL fs_mark_fileMem (IOB *fcb);
extern U32  fs_Find_File (const char *name, IOB *fcb);
extern BOOL fs_BlockFull (IOB *fcb);
extern BOOL fs_AllocBlock (IOB *fcb);
extern BOOL fs_BlockInvalid (U32 block, IOB *fcb);
extern BOOL fs_InitBlock (U32 block, IOB *fcb);
extern BOOL fs_WriteBlock (U32 adr, void *buf, U32 cnt, IOB *fcb);
extern BOOL fs_ReadBlock (U32 adr, void *buf, U32 cnt, IOB *fcb);
extern U32  fs_adr_sig (U32 bl, IOB *fcb);
extern U32  fs_rd_alloc (U32 adr, FALLOC *fa);
extern U32  fs_rd_sig (U32 adr, U32 *sig);

 
extern BOOL fn_cmp (const char *sp, const char *fp);
extern int  fs_strpos (const char *sp, const char ch);
extern int  fs_get_drive (const char *fn);
extern int  fs_find_iob (void);
extern BOOL fs_set_params (IOB *fcb);
extern int  fs_ReadData (U32 adr, U32 cnt, U8 *buf);
extern int  fs_WriteData (U32 adr, U32 cnt, U8 *buf);

 
extern int  fs_Init (U32 adr, U32 clk);
extern int  fs_EraseSector (U32 adr);
extern int  fs_ProgramPage (U32 adr, U32 sz, U8 *buf);

 
extern int  fs_spi_Init (void);
extern int  fs_spi_EraseSector (U32 adr);
extern int  fs_spi_ProgramPage (U32 adr, U32 sz, U8 *buf);
extern int  fs_spi_ReadData (U32 adr, U32 sz, U8 *buf);

 
extern int  fat_init (void);
extern BOOL fat_find_file (const char *fn, IOB *fcb);
extern BOOL fat_set_fpos (IOB *fcb, U32 pos);
extern U32  fat_read (IOB *fcb, U8 *buf, U32 len);
extern BOOL fat_write (IOB *fcb, const U8 *buf, U32 len);
extern U64  fat_free (void);
extern BOOL fat_delete (const char *fn, IOB *fcb);
extern BOOL fat_close_write (IOB *fcb);
extern BOOL fat_rename (const char *old, const char *newn, IOB *fcb);
extern BOOL fat_create (const char *fn, IOB *fcb);
extern BOOL fat_format (const char *label);
extern BOOL fat_ffind  (const char *fn, FINFO *info, IOB *fcb);

 
extern BOOL mmc_init (void);
extern BOOL mmc_write_sect (U32 sect, U8 *buf, U32 cnt);
extern BOOL mmc_read_sect (U32 sect, U8 *buf, U32 cnt);
extern BOOL mmc_read_config (MMCFG *cfg);

 
extern U32  fs_get_time (void);
extern U32  fs_get_date (void);

 
extern void spi_init (void);
extern U8   spi_send (U8 outb);
extern void spi_ss (U32 ss);
extern void spi_hi_speed (BOOL on);
extern void spi_command (U8 *cmd, U8 *tbuf, U8 *rbuf, U32 sz);

 
#line 315 "d:\\Keil\\ARM\\RV31\\INC\\File_Config.h"

 
__weak void _mutex_acquire (int *mutex);
__weak void _mutex_release (int *mutex);
__weak int  _stream_list_lock;
#line 13 "FlashFS\\fs_fdefrag.c"

static BOOL alloc_free_bl (FDBUF *fb, IOB *fcb);
static BOOL get_next_file (IOB *fcb);
static BOOL copy_file (FDBUF *fb, IOB *fcb);
static U32  read_cbuf (IOB *fcb);
static BOOL write_cbuf (FDBUF *fb, IOB *fcb, U32 len);
static BOOL get_fblock (IOB *fcb);
static void delete_file (IOB *fcb, BOOL del_temp);


static U32 cbuf[256/4+1];
static FALLOC alloc;

 

int fdefrag (const char *drive) {
   
  IOB *fcb,*iop;
  int handle;
  FDBUF fwr;
  BOOL defrag_fail;
  U32 i,adr,bl,bflag;

  int rval; _mutex_acquire(&_stream_list_lock);;

   
  if ((handle = fs_find_iob ()) == -1) {
    rval = (1); goto end_of_func;;
  }
  fcb = &_iob[handle];
   
  fcb->drive = fs_get_drive (drive);
  if (fcb->drive == 0 && *drive == 0) {
     
    fcb->drive = _DEF_DRIVE;
  }
  if (fcb->drive == 4) {
     
    rval = (1); goto end_of_func;;
  }
   
  if (fs_set_params (fcb) == 0) {
    rval = (1); goto end_of_func;;
  }

   
  for (i = 0, iop = &_iob[0]; i < _NFILE; iop++, i++) {
    if (iop->drive != fcb->drive) {
      continue;
    }
    if ((iop->flags & (0x0002 | 0x0001))) {
       
      rval = (1); goto end_of_func;;
    }
  }

   
  for (bl = 0; bl < fcb->NumSect; bl++) {
    adr = fs_adr_sig (bl, fcb);
    fs_rd_sig (adr, &bflag);
    if (bflag != fcb->InitVal) {
       
      if (fs_BlockInvalid (bl, fcb) == 1) {
        fs_InitBlock (bl, fcb);
      }
    }
  }

   
  fcb->fileID = 0;
  fwr.ftop    = 0;
  fwr.fbot    = 0;
  defrag_fail = 0;
  while (get_next_file (fcb) == 1) {
    if (copy_file (&fwr, fcb) == 0) {
       
      delete_file (fcb, 1);
      defrag_fail = 1;
      break;
    }
    delete_file (fcb, 0);
  }

   
  for (bl = 0; bl < fcb->NumSect; bl++) {
    adr = fs_adr_sig (bl, fcb);
    fs_rd_sig (adr, &bflag);
    if (bflag == fcb->InitVal) {
      continue;
    }
    if ((bflag ^ 0x03) == fcb->InitVal) {
      bflag = fcb->InitVal ^ 0x0F;
      if (fs_get_freeMem (bl, fcb) == 0) {
        bflag = fcb->InitVal ^ 0xFF;
      }
      fs_WriteBlock ((adr & ~1), &bflag, 4, fcb);
      continue;
    }
    if (defrag_fail == 0) {
      fs_InitBlock (bl, fcb);
    }
  }
  if (defrag_fail == 1) {
    rval = (2); goto end_of_func;;
  }
  rval = (0); goto end_of_func;;

  end_of_func: _mutex_release(&_stream_list_lock); return (rval);;
}


 

static BOOL alloc_free_bl (FDBUF *fb, IOB *fcb) {
  U32 bl,adr,bflag;

   
  for (bl = 0; bl < fcb->NumSect; bl++) {
    adr = fs_adr_sig (bl, fcb);
    fs_rd_sig (adr, &bflag);
    if (bflag == fcb->InitVal) {
      bflag = fcb->InitVal ^ 0x03;
      fs_WriteBlock ((adr & ~1), &bflag, 4, fcb);
      fb->fblock = bl;
      fb->fbot   = 0;
      fb->ftop   = ((DEVCONF *)fcb->DevCfg)[bl].bEnd   -
                   ((DEVCONF *)fcb->DevCfg)[bl].bStart -  sizeof(FALLOC);
      return (1);
    }
  }
  return (0);
}


 

static BOOL get_next_file (IOB *fcb) {
  FALLOC fa;
  U32 bl,adr,prev;
  U32 fid,nid;

   
  fid = fcb->fileID | 0x8000;
  nid = 0xFFFF;
  for (bl = 0; bl < fcb->NumSect; bl++) {
    adr = fs_adr_sig (bl, fcb);
    adr = fs_rd_sig (adr, &fa.end);
    if (fa.end == fcb->InitVal || fa.end == (fcb->InitVal ^ 0x03)) {
       
      continue;
    }
    for (prev = 0; ; prev = fa.end) {
      adr = fs_rd_alloc (adr, &fa);
      if (fa.fileID > fid && fa.fileID < nid) {
        nid = fa.fileID;
         
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
     
    return (0);
  }
x:fcb->fileID = nid & 0x7FFF;
  fcb->_fidx  = 0;
  return (1);
}


 

static BOOL copy_file (FDBUF *fb, IOB *fcb) {
  U32 n,nr;

   
  fb->fbot = (fb->fbot + 3) & ~3;
  if (fb->ftop < fb->fbot + 256) {
     
    if (alloc_free_bl (fb, fcb) == 0) {
       
      return (0);
    }
  }
   
  n = (fcb->_ftop - fcb->_fbot + 3) & ~3;
  if (n > 256) {
    n = 256;
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

   
  fcb->_ftop = 0;
  fcb->_fbot = 0;
  fcb->_fidx = 0;
  fb->index  = 0;

  while ((nr = read_cbuf (fcb)) != 0) {
    if (write_cbuf (fb, fcb, nr) == 0) {
      return (0);
    }
    if (nr < 256) {
      break;
    }
  }

   
  alloc.end    = fb->fbot;
  alloc.fileID = fcb->fileID;
  alloc.index  = fb->index;
  fs_WriteBlock (((DEVCONF *)fcb->DevCfg)[fb->fblock].bStart + fb->ftop, 
                 &alloc, sizeof (FALLOC), fcb);
  fb->ftop -= sizeof (FALLOC);
  return (1);
}


 

static U32 read_cbuf (IOB *fcb) {
  U32 len,n;

  len = 0;
   
  while (1) {
    if (fcb->_ftop == fcb->_fbot) {
      if (get_fblock (fcb) == 0) {
        break;
      }
    }
    n = fcb->_ftop - fcb->_fbot;
    if (n > 256 - len) {
      n = 256 - len;
    }
    fs_ReadBlock (((DEVCONF *)fcb->DevCfg)[fcb->_fblock].bStart + fcb->_fbot,
                  (U8 *)&cbuf + len, n, fcb);
    fcb->_fbot += n;
    len        += n;
    if (len >= 256) {
      break;
    }
  }
  return (len);
}


 

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
       
      continue;
    }

     
    alloc.end    = fb->fbot;
    alloc.fileID = fcb->fileID;
    alloc.index  = fb->index;
    fs_WriteBlock (((DEVCONF *)fcb->DevCfg)[fb->fblock].bStart + fb->ftop,
                   &alloc, sizeof (FALLOC), fcb);
    fb->ftop -= sizeof (FALLOC);
    fb->index++;

     
    if (alloc_free_bl (fb, fcb) == 0) {
       
      return (0);
    }
  }
  return (1);
}


 

static BOOL get_fblock (IOB *fcb) {
  FALLOC fa;
  U32 i,bl,adr,prev;

  bl = fcb->_fblock;
  for (i = 0; i < fcb->NumSect; i++) {
     
    adr = fs_adr_sig (bl, fcb);
    adr = fs_rd_sig (adr, &fa.end);
    if (fa.end == fcb->InitVal || fa.end == (fcb->InitVal ^ 0x03)) {
       
      goto next;
    }
    for (prev = 0; ; prev = fa.end) {
      adr = fs_rd_alloc (adr, &fa);
      if (fa.fileID == fcb->fileID  &&  fa.index == fcb->_fidx) {
         
        fcb->_fblock = bl;
         
        fcb->_fbot   = (prev + 3) & ~3;
        fcb->_ftop   = fa.end;
        fcb->_fidx++; 
        return (1);
      }
      if (fa.end == fcb->InitVal) break;
    }
next:if (++bl == fcb->NumSect) {
      bl = 0;
    }
  }
  return (0);
}

 

static void delete_file (IOB *fcb, BOOL del_temp) {
   
  FALLOC fa;
  U32 bl,adr,invalid;

  for (bl = 0; bl < fcb->NumSect; bl++) {
     
    adr = fs_adr_sig (bl, fcb);
    adr = fs_rd_sig (adr, &fa.end);
    if (del_temp == 0) {
      if (fa.end == fcb->InitVal || fa.end == (fcb->InitVal ^ 0x03)) {
         
        continue;
      }
    }
    else {
      if (fa.end != (fcb->InitVal ^ 0x03)) {
         
        continue;
      }
    }
    do {
      adr = fs_rd_alloc (adr, &fa);
      if ((fa.fileID & 0x7FFF) == fcb->fileID) {
         
        invalid = ~fcb->InitVal;
        fs_WriteBlock ((adr & ~1) + 12, &invalid, 4, fcb);
      }
    } while (fa.end != fcb->InitVal);

     
    if (fs_BlockInvalid (bl, fcb) == 1) {
       
      fs_InitBlock (bl, fcb);
    }
  }
}



 
