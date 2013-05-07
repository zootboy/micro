#line 1 "FlashFS\\fs_fat.c"









 

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
#line 13 "FlashFS\\fs_fat.c"
#line 1 "d:\\Keil\\ARM\\RV31\\INC\\string.h"
 
 
 
 




 








 











#line 37 "d:\\Keil\\ARM\\RV31\\INC\\string.h"


  
  typedef unsigned int size_t;








extern __declspec(__nothrow) void *memcpy(void * __restrict  ,
                    const void * __restrict  , size_t  ) __attribute__((__nonnull__(1,2)));
   




 
extern __declspec(__nothrow) void *memmove(void *  ,
                    const void *  , size_t  ) __attribute__((__nonnull__(1,2)));
   







 
extern __declspec(__nothrow) char *strcpy(char * __restrict  , const char * __restrict  ) __attribute__((__nonnull__(1,2)));
   




 
extern __declspec(__nothrow) char *strncpy(char * __restrict  , const char * __restrict  , size_t  ) __attribute__((__nonnull__(1,2)));
   





 

extern __declspec(__nothrow) char *strcat(char * __restrict  , const char * __restrict  ) __attribute__((__nonnull__(1,2)));
   




 
extern __declspec(__nothrow) char *strncat(char * __restrict  , const char * __restrict  , size_t  ) __attribute__((__nonnull__(1,2)));
   






 






 

extern __declspec(__nothrow) int memcmp(const void *  , const void *  , size_t  ) __attribute__((__nonnull__(1,2)));
   





 
extern __declspec(__nothrow) int strcmp(const char *  , const char *  ) __attribute__((__nonnull__(1,2)));
   




 
extern __declspec(__nothrow) int strncmp(const char *  , const char *  , size_t  ) __attribute__((__nonnull__(1,2)));
   






 
extern __declspec(__nothrow) int strcasecmp(const char *  , const char *  ) __attribute__((__nonnull__(1,2)));
   





 
extern __declspec(__nothrow) int strncasecmp(const char *  , const char *  , size_t  ) __attribute__((__nonnull__(1,2)));
   






 
extern __declspec(__nothrow) int strcoll(const char *  , const char *  ) __attribute__((__nonnull__(1,2)));
   







 

extern __declspec(__nothrow) size_t strxfrm(char * __restrict  , const char * __restrict  , size_t  ) __attribute__((__nonnull__(2)));
   













 


#line 184 "d:\\Keil\\ARM\\RV31\\INC\\string.h"
extern __declspec(__nothrow) void *memchr(const void *  , int  , size_t  ) __attribute__((__nonnull__(1)));

   





 

#line 200 "d:\\Keil\\ARM\\RV31\\INC\\string.h"
extern __declspec(__nothrow) char *strchr(const char *  , int  ) __attribute__((__nonnull__(1)));

   




 

extern __declspec(__nothrow) size_t strcspn(const char *  , const char *  ) __attribute__((__nonnull__(1,2)));
   




 

#line 223 "d:\\Keil\\ARM\\RV31\\INC\\string.h"
extern __declspec(__nothrow) char *strpbrk(const char *  , const char *  ) __attribute__((__nonnull__(1,2)));

   




 

#line 238 "d:\\Keil\\ARM\\RV31\\INC\\string.h"
extern __declspec(__nothrow) char *strrchr(const char *  , int  ) __attribute__((__nonnull__(1)));

   





 

extern __declspec(__nothrow) size_t strspn(const char *  , const char *  ) __attribute__((__nonnull__(1,2)));
   



 

#line 261 "d:\\Keil\\ARM\\RV31\\INC\\string.h"
extern __declspec(__nothrow) char *strstr(const char *  , const char *  ) __attribute__((__nonnull__(1,2)));

   





 

extern __declspec(__nothrow) char *strtok(char * __restrict  , const char * __restrict  ) __attribute__((__nonnull__(2)));
extern __declspec(__nothrow) char *_strtok_r(char *  , const char *  , char **  ) __attribute__((__nonnull__(2,3)));

extern __declspec(__nothrow) char *strtok_r(char *  , const char *  , char **  ) __attribute__((__nonnull__(2,3)));

   

































 

extern __declspec(__nothrow) void *memset(void *  , int  , size_t  ) __attribute__((__nonnull__(1)));
   



 
extern __declspec(__nothrow) char *strerror(int  );
   





 
extern __declspec(__nothrow) size_t strlen(const char *  ) __attribute__((__nonnull__(1)));
   



 

extern __declspec(__nothrow) size_t strlcpy(char *  , const char *  , size_t  ) __attribute__((__nonnull__(1,2)));
   
















 

extern __declspec(__nothrow) size_t strlcat(char *  , const char *  , size_t  ) __attribute__((__nonnull__(1,2)));
   






















 

extern __declspec(__nothrow) void _membitcpybl(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitcpybb(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitcpyhl(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitcpyhb(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitcpywl(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitcpywb(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitmovebl(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitmovebb(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitmovehl(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitmovehb(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitmovewl(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitmovewb(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
    














































 







#line 493 "d:\\Keil\\ARM\\RV31\\INC\\string.h"



 
#line 14 "FlashFS\\fs_fat.c"





 



 
static const DEVPAR IniDevCfg[10] = {
 
  { 1,    16,       0,        2,    16,     512,    65 },    
  { 1,    16,       0,        2,    16,    1024,    65 },    
  { 1,    32,       0,        2,    32,    1024,    65 },    
  { 1,    32,       0,        4,    32,    1024,    65 },    
  { 2,    16,       0,        8,    32,    1024,    65 },    
  { 2,    16,       4,       16,    32,    1024,   129 },    
  { 2,    32,       8,       32,    32,    1024,   129 },    
  { 2,    32,      16,       64,    32,    1024,   257 },    
  { 2,    64,      32,      256,    32,     512,   257 },    
  { 3,    64,      64,      256,    32,    1024,   257 }};   
 
 
 

static const U8 ChIndex[13] = { 1, 3, 5, 7, 9, 14, 16, 18, 20, 22, 24, 28, 30 };

 
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

static char name_buf[260];               

 
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

 

int fat_init (void) {
   

   
  if (mmc_init () == 0) {
     
    return (1);
  }
   
  return (init_dev ());
}


 

static int init_dev (void) {
  U32 root_scnt;

   
  fat.sect = 0xFFFFFFFF;
  fat.buf  = (U8 *)&mc_cache[0];
  fat.dirty= 0;

  ca.sect  = 0xFFFFFFFF;
  ca.buf   = (U8 *)&mc_cache[128];
  ca.cbuf  = (U8 *)&mc_cache[256];
  ca.nwr   = 0;
  ca.nrd   = 0;

   
  top_clus = 2;

   
  memset (&mmc, 0, sizeof (mmc));

  if (get_mbrec () == 0) {
     
    warm_restart = 0;
    return (2);
  }

   
  if (get_bootrec () == 0) {
     
    warm_restart = 0;
    return (3);
  }

  if (is_fat_valid () == 0) {
     
    warm_restart = 0;
    return (4);
  }

   
  root_scnt = (mmc.RootEntCnt * 32 + mmc.BytesPerSec - 1) / mmc.BytesPerSec;

   
  mmc.DataSecCnt  = mmc.DskSize - (mmc.RsvdSecCnt + 
                                   mmc.NumOfFat * mmc.FatSize + root_scnt);
  mmc.DataClusCnt = mmc.DataSecCnt / mmc.SecPerClus;
  mmc.RootDirAddr = mmc.RsvdSecCnt + mmc.NumOfFat * mmc.FatSize;
  mmc.RootSecCnt  = root_scnt;
  mmc.ClusSize    = mmc.SecPerClus * mmc.BytesPerSec;
  mmc.EntsPerClus = mmc.ClusSize / 32;

   
  if (mmc.DataClusCnt < 4085) {
    mmc.FatType = 1;
    warm_restart = 0;
  }
  else if (mmc.DataClusCnt < 65525) {
    mmc.FatType = 2;
    warm_restart = 0;
  }
  else {
    mmc.FatType = 3;
     
    if (warm_restart == 0) {
      warm_restart = 1;
      free_clus = count_free_clus ();
    }
  }

  return (0);
}


 

BOOL fat_format (const char *label) {
   
  U32 datSect,volSz,iSz,secClus,i,sec;
  MMCFG mcfg;

   
  if ((mmc_read_config (&mcfg)) == 0) return (0);;

   
  if (mcfg.read_blen != mcfg.write_blen) {
    return (0);
  }
  switch (mcfg.read_blen) {
    case 512:
       
      break;

    case 1024:
       
      mcfg.blocknr *= 2;
      break;

    case 2048:
       
      mcfg.blocknr *= 4;
      break;

    default:
       
      return (0);
  }

  volSz = mcfg.blocknr >> 11;
  for (iSz = 0, i = 8; iSz < 10; i <<= 1, iSz++) {
    if (volSz < i) break;
  }
  if (iSz == 10) {
     
    return (0);
  }

   
  if (chk_param ("WIPE", label) == 1) {
     
    if ((wipe_disk (mcfg . blocknr)) == 0) return (0);;
  }

   
  mmc.BootRecSec = IniDevCfg[iSz].BootRecSec;
  mmc.DskSize    = mcfg.blocknr - mmc.BootRecSec;
  mmc.RsvdSecCnt = 1;
  mmc.BytesPerSec= 512;
  mmc.NumOfFat   = 2;

   
  mmc.FatType    = IniDevCfg[iSz].FatType;
  secClus        = IniDevCfg[iSz].SecClus;

   
  if (chk_param ("FAT32", label) == 1) {
     
    mmc.FatType = 3;
    secClus     = IniDevCfg[iSz].SecClus32;
    if (secClus == 0) {
       
      return (0);
    }
  }

  mmc.SecPerClus = secClus;
  mmc.ClusSize   = secClus * 512;

  datSect = mmc.DskSize - mmc.RsvdSecCnt;
   
  switch (mmc.FatType) {
    case 1:
      datSect -= 32;
      mmc.RootEntCnt  = 512;
      mmc.RootSecCnt  = 32;
      mmc.DataClusCnt = (datSect * 512 - 1022) / (secClus * 512 + 3);
      mmc.FatSize     = (mmc.DataClusCnt * 3 + 1022) / 1024;
      break;
    case 2:
      datSect -= 32;
      mmc.RootEntCnt  = 512;
      mmc.RootSecCnt  = 32;
      mmc.DataClusCnt = (datSect * 128 - 255) / (secClus * 128 + 1);
      mmc.FatSize     = (mmc.DataClusCnt + 255) / 256;
      break;
    case 3:
      mmc.RootSecCnt  = 0;
      mmc.DataClusCnt = (datSect * 64 - 127) / (secClus * 64 + 1);
      mmc.FatSize     = (mmc.DataClusCnt + 127) / 128;
      break;
  }

   
  mmc.DataSecCnt  = mmc.DskSize - (mmc.RsvdSecCnt + mmc.RootSecCnt +
                                   mmc.NumOfFat * mmc.FatSize);
  mmc.RootDirAddr = mmc.RsvdSecCnt + mmc.NumOfFat * mmc.FatSize;

   
  sec = mmc.RootDirAddr + mmc.RootSecCnt;
  mmc.BootRecSec = ((mmc.BootRecSec + sec + 32) & ~0x3F) - sec;

  warm_restart = 0;
   
  if ((write_mbr (iSz)) == 0) return (0);;

   
  if ((write_br (mcfg . sernum)) == 0) return (0);;

   
  memset (ca.buf, 0, 512);

   
  switch (mmc.FatType) {
    case 1:
      set_u32 (&ca.buf[0], 0xFFFFF8);
      break;
    case 2:
      set_u32 (&ca.buf[0], 0xFFFFFFF8);
      break;
    case 3:
       
      set_u32 (&ca.buf[0], 0x0FFFFFF8);
      set_u32 (&ca.buf[4], 0xFFFFFFFF);
      set_u32 (&ca.buf[8], 0x0FFFFFFF);
      break;
  }
  sec = mmc.BootRecSec + mmc.RsvdSecCnt;
   
  if ((write_cache (sec)) == 0) return (0);;
  memset (ca.buf, 0, 12);

  datSect = mmc.RootSecCnt;
  if (mmc.FatType == 3) {
     
    datSect = mmc.SecPerClus;
  }
  datSect += mmc.FatSize * 2;

  for (i = 1; i < datSect; i++) {
    if ((write_cache (sec + i)) == 0) return (0);;
  }
   
  if ((write_cache (0)) == 0) return (0);;

  if (*label != 0) {
     
    if ((write_label (label)) == 0) return (0);;
  }
  return (1);
}


 

static BOOL write_mbr (U32 iSz) {
   
  U32 val;

  memset (ca.buf, 0, 512);

   
  ca.buf[446] = 0;

   
  ca.buf[447] = 1;

   
  set_u16 (&ca.buf[448], 1);

   
  switch (mmc.FatType) {
    case 1:
       
      ca.buf[450] = 0x01;
      break;
    case 2:
      if (iSz < 3) {
         
        ca.buf[450] = 0x04;
      }
      else {
         
        ca.buf[450] = 0x06;
      }
      break;
    case 3:
         
      ca.buf[450] = 0x0b;
      break;
  }

   
  ca.buf[451] = IniDevCfg[iSz].NumHeads - 1;

   
  val = IniDevCfg[iSz].NumSect | ((IniDevCfg[iSz].NumCyl - 1) << 6);
  set_u16 (&ca.buf[452], val);

   
  set_u32 (&ca.buf[454], mmc.BootRecSec);

   
  set_u32 (&ca.buf[458], mmc.DskSize - mmc.BootRecSec);

   
  set_u16 (&ca.buf[510], 0xAA55);
  return (write_sector (0));
}


 

static BOOL write_br (U32 sernum) {
   

  memset (ca.buf, 0, 512);

   
  ca.buf[0] = 0xE9;
  ca.buf[1] = 0x00;
  ca.buf[2] = 0x90;

   
  memcpy (&ca.buf[3], "MSWIN4.1", 8);

   
  set_u16 (&ca.buf[11], 512);

   
  ca.buf[13] = mmc.SecPerClus;

   
  ca.buf[14] = mmc.RsvdSecCnt;

   
  ca.buf[16] = 2;

   
  if (mmc.FatType != 3) {
     
    set_u16 (&ca.buf[17], 512);
  }

   
  if (mmc.DskSize < 0x10000) {
    set_u16 (&ca.buf[19], mmc.DskSize);
  }
  else {
    set_u32 (&ca.buf[32], mmc.DskSize);
  }

   
  ca.buf[21] = 0xF8;

   
  set_u32 (&ca.buf[28], mmc.BootRecSec);

  if (mmc.FatType != 3) {
     
    set_u16 (&ca.buf[22], mmc.FatSize);

     
    ca.buf[36] = 0x80;

     
    ca.buf[38] = 0x29;

     
    set_u32 (&ca.buf[39], sernum);

     
    memcpy (&ca.buf[43], "NO NAME    ", 11);

     
    if (mmc.FatType == 1) {
      memcpy (&ca.buf[54], "FAT12   ", 8);
    }
    else {
      memcpy (&ca.buf[54], "FAT16   ", 8);
    }
  }
  else {
     

     
    set_u32 (&ca.buf[36], mmc.FatSize);

     
    set_u32 (&ca.buf[44], 2);

     
    set_u16 (&ca.buf[48], 1);

     
    set_u16 (&ca.buf[50], 6);

     
    ca.buf[64] = 0x80;

     
    ca.buf[66] = 0x29;

     
    set_u32 (&ca.buf[67], sernum);

     
    memcpy (&ca.buf[71], "NO NAME    ", 11);

     
    memcpy (&ca.buf[82], "FAT32   ", 8);
  }

   
  set_u16 (&ca.buf[510], 0xAA55);

  return (write_sector (mmc.BootRecSec));
}


 

static BOOL wipe_disk (U32 dsize) {
   
  U32 i,csize;

   
  ca.nwr = 0;
  ca.nrd = 0;

   
  csize = _MC_CSIZE;
  if (csize == 0) {
    csize = 1;
  }
  memset (ca.buf, 0xFF, csize * 512);

  for (i = 0; i < dsize; i += csize) {
    if ((mmc_write_sect (i, ca . buf, csize)) == 0) return (0);;
  }
  return (1);
}


 

U64 fat_free (void) {
   

  if (mmc.FatType == 0) {
     
    return (0);
  }

   
  if (mmc.FatType != 3) {
    free_clus = count_free_clus ();
  }

  if (free_clus > mmc.DataClusCnt) {
     
    return (0);
  }
   
  return (free_clus * mmc.ClusSize);
}


 

static BOOL fat_find_dir (const char *fn, IOB *fcb, U8 create) {
  
 
  U8  creating_f;
  U32 sz;

  creating_f = 0;

  while (get_dir_name (fn, name_buf, &sz) == 1) {

    if (!creating_f) {
      if (find_name (name_buf, fcb, 1) == 0) {
         
        if (!create) {
           
          return (0);
        }
         
        creating_f = 1;
      }
    }

    if (creating_f) {
       
      if ((alloc_name (name_buf, fcb)) == 0) return (0);;
       
      if ((write_entries (name_buf, fcb, 1, 0x00)) == 0) return (0);;
       
      if ((write_dot_entries (fcb)) == 0) return (0);;
    }
    fn += sz;
  }

  
 
  return (1);
}


 

BOOL fat_find_file (const char *fn, IOB *fcb) {
  
 

  if (mmc.FatType == 0) {
     
    return (0);
  }

   
  if (*fn == '\\') fn++;

   
  if (*fn == 0) return(0);

   
  fcb->_firstClus = 0;

   
  if (fat_find_dir (fn, fcb, 0x00) == 0) {
     
    return (0);
  }

   
  if (find_name (name_buf, fcb, 0) == 0) {
     
    return (0);
  }

   
  fcb->_currDatSect  = 0;
  fcb->_currDatClus  = fcb->_firstClus;

   
  return (1);
}


 

BOOL fat_ffind (const char *fn, FINFO *info, IOB *fcb) {
   

  if (mmc.FatType == 0) {
     
    return (0);
  }

   
  if (*fn == '\\') fn++;

   
  if (*fn == 0) return(0);

   
  fcb->_firstClus = 0;

   
  if (fat_find_dir (fn, fcb, 0) == 0) {
     
    return (0);
  }

   
  if (get_next_info (info, fcb) == 0) {
     
    return (0);
  }

   
  return (1);
}


 

BOOL fat_create (const char *fn, IOB *fcb) {
   

  if (mmc.FatType == 0) {
     
    return (0);
  }

   
  if (*fn == '\\') fn++;

   
  if (*fn == 0) return(0);

   
  fcb->_firstClus = 0;

   
  if (fat_find_dir (fn, fcb, 1) == 0) {
     
    return (0);
  }

   
  if (alloc_name (name_buf, fcb) == 0) {
     
    return (0);
  }

   
  if (write_entries (name_buf, fcb, 0, 0x00) == 0) {
     
    return (0);
  }

   
  return (1);
}


 

BOOL fat_delete (const char *fn, IOB *fcb) {
   

  if (mmc.FatType == 0) {
     
    return (0);
  }

   
  if (*fn == '\\') fn++;

   
  if (*fn == 0) return(0);

   
  fcb->_firstClus = 0;

   
  if (fat_find_dir (fn, fcb, 0) == 0) {
     
    return (0);
  }

  if (name_buf[0]) {
     
    if (find_name (name_buf, fcb, 0) == 0) {
       
      return (0);
    }
  }
  else {
     
    if (chk_dir_empty (fcb) == 0) {
       
      return (0);
    }
  }

   
  if (delete_entries (fcb, 0) == 0) {
     
    return (0);
  }

   
  return (1);
}


 

U32 fat_read (IOB *fcb, U8 *buf, U32 len) {
   
  U32 sect,pos,nr,rlen;

  if (mmc.FatType == 0) {
     
    return (0);
  }
  if (fcb->fpos + len > fcb->fsize) {
     
    len = fcb->fsize - fcb->fpos;
    if (len == 0) {
       
      return (0);
    }
  }

  pos = fcb->fpos & 0x1FF;
  for (nr = 0; nr < len; nr += rlen) {
    sect = clus_to_sect (fcb->_currDatClus) + fcb->_currDatSect;
     
    if ((read_cache (sect, mmc . SecPerClus - fcb->_currDatSect)) == 0) return (0);;

    rlen = len - nr;
    if ((rlen + pos) > 512) {
      rlen = 512 - pos;
    }

    memcpy (&buf[nr], &ca.buf[pos], rlen);
    pos = (pos + rlen) & 0x1FF;
    if (pos == 0) {
       
      if (++fcb->_currDatSect == mmc.SecPerClus) {
         
        fcb->_currDatSect = 0;
        if ((set_next_clus (&fcb->_currDatClus)) == 0) return (0);;
      }
    }
  }
  fcb->fpos += nr;
   
  return (len);
}


 

BOOL fat_write (IOB *fcb, const U8 *buf, U32 len) {
   
  U32 sect,pos,nw,wlen,clus;

  if (mmc.FatType == 0) {
     
    return (0);
  }
  if (fcb->_firstClus == 0) {
     
    if ((get_free_clus (&fcb->_currDatClus)) == 0) return (0);;
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
       
      if ((read_sector (sect)) == 0) return (0);;
    }
    memcpy (&ca.buf[pos], &buf[nw], wlen);
    if ((write_cache (sect)) == 0) return (0);;

    pos = (pos + wlen) & 0x1FF;

    if (pos == 0) {
       
      if (++fcb->_currDatSect == mmc.SecPerClus) {
         
        fcb->_currDatSect = 0;
        clus = fcb->_currDatClus;
         
        if ((get_free_clus (&fcb->_currDatClus)) == 0) return (0);;
         
        if ((write_fat_link (clus, fcb->_currDatClus)) == 0) return (0);;
      }
    }
  }
  fcb->fpos += nw;
  return (1);
}


 

BOOL fat_close_write (IOB *fcb) {
   
  FILEREC last_frec;

  if (mmc.FatType == 0) {
     
    return (0);
  }

  if (fcb->fpos > fcb->fsize) {
     
    if ((write_fat_link (fcb->_currDatClus, get_EOC())) == 0) return (0);;

     
     
    if ((read_last_entry (fcb, &last_frec)) == 0) return (0);;
    last_frec.FirstClusHI = (U16)(fcb->_firstClus >> 16);
    last_frec.FirstClusLO = (U16)(fcb->_firstClus      );
    last_frec.FileSize    = fcb->fpos;
     
    if ((write_last_entry (fcb, &last_frec)) == 0) return (0);;
  }
   
  if ((write_cache (0)) == 0) return (0);;
  if ((cache_fat (0)) == 0) return (0);;
  return (1);
}


 

BOOL fat_set_fpos (IOB *fcb, U32 pos) {
   
  U32 i;

  if (pos > fcb->fsize) {
    pos = fcb->fsize;
  }
  fcb->_currDatSect = (pos / 512) % mmc.SecPerClus;
  fcb->_currDatClus = fcb->_firstClus;
  for (i = pos / mmc.ClusSize; i; i--) {
     
    if ((set_next_clus (&fcb->_currDatClus)) == 0) return (0);;
  }
  fcb->fpos = pos;

  return (1);
}


 

BOOL fat_rename (const char *old, const char *newn, IOB *fcb) {
   
  U8 type;

  if (mmc.FatType == 0) {
     
    return (0);
  }

   
  if (*old == '\\') old++;

   
  if (*newn == '\\') newn++;

   
  if (*old == 0 || *newn == 0) {
    return(0);
  }

   
  fcb->_firstClus = 0;
  if (fat_find_dir (old, fcb, 0) == 0) {
     
    return (0);
  }

  type = 1;
  if (name_buf[0]) {
    if (check_name (newn, fcb, 0) == 1) {
       
      return (0);
    }

    type = 0;
     
    if (find_name (name_buf, fcb, 0) == 0) {
       
      return (0);
    }
  }
  else {
    if (check_name (newn, fcb, 1) == 1) {
       
      return (0);
    }
  }

  if (rename_entries (newn, fcb, type) == 0) {
     
    return (0);
  }

   
  return (1);
}


 

static BOOL write_label (const char *label) {
   
  FILEREC *frec;
  U32 i;
  U8 ch;

  if ((read_sector (mmc . BootRecSec + mmc . RootDirAddr)) == 0) return (0);;
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
  frec->Attr      = 0x08;
  set_u16 ((U8 *)&frec->WriteDate, get_date ());
  set_u16 ((U8 *)&frec->WriteTime, get_time ());
  if ((write_sector (mmc . BootRecSec + mmc . RootDirAddr)) == 0) return (0);;
  return (1);
}


 

static BOOL set_next_clus (U32 *ptr_clus) {
   
  U32 sect,ofs,next;
  U32 clus = *ptr_clus;

   
  sect = get_fat_sect (clus);
  if ((cache_fat (sect)) == 0) return (0);;
  next = 0;
  switch (mmc.FatType) {
    case 1:
      ofs  = ((clus * 3) / 2) & 0x1FF;
      if (ofs < 511) {
        next = get_u16 (&fat.buf[ofs]);
      }
      else {
         
        next = fat.buf[511];
        if ((cache_fat (sect+1)) == 0) return (0);;
        next |= fat.buf[0] << 8;
      }
      if (clus & 0x001) {
        next >>= 4;
      }
      else {
        next &= 0xFFF;
      }
      break;

    case 2:
      ofs  = (clus & 0xFF) << 1;
      next = *(U16 *)&fat.buf[ofs];
      break;

    case 3:
      ofs  = (clus & 0x7F) << 2;
      next = *(U32 *)&fat.buf[ofs];
      break;

    default:
      return (0);
  }
  *ptr_clus = next;
  return (1);
}


 

static BOOL get_free_clus (U32 *ptr_clus) {
   
  U32 sect,ofs,next;
  U32 clus = *ptr_clus;

  for (clus = top_clus; clus < (mmc.DataClusCnt + 2); clus++) {
     
    sect = get_fat_sect (clus);
    if ((cache_fat (sect)) == 0) return (0);;
    switch (mmc.FatType) {
      case 1:
        ofs  = ((clus * 3) / 2) & 0x1FF;
        if (ofs < 511) {
          next = get_u16 (&fat.buf[ofs]);
        }
        else {
           
          next = fat.buf[511];
          if ((cache_fat (sect+1)) == 0) return (0);;
          next |= fat.buf[0] << 8;
        }
        if (clus & 0x001) {
          next >>= 4;
        }
        else {
          next &= 0xFFF;
        }
        break;

      case 2:
        ofs  = (clus & 0xFF) << 1;
        next = get_u16 (&fat.buf[ofs]);
        break;

      case 3:
        ofs  = (clus & 0x7F) << 2;
        next = get_u32 (&fat.buf[ofs]);
        break;

      default:
        return (0);
    }
    if (next == 0) {
      if (clus_in_use (clus) == 0) {
        *ptr_clus = clus;
        top_clus  = clus + 1;
        return (1);
      }
    }
  }
   
  top_clus = clus;
  return (0);
}


 

static BOOL clus_in_use (U32 clus) {
   
  IOB *fcb;
  U32 i,nfile = _NFILE;

  for (i = 0, fcb = &_iob[0]; i < nfile; fcb++, i++) {
    if (!(fcb->flags & 0x0002)) {
       
      continue;
    }
    if (fcb->_currDatClus == clus) {
       
      return (1);
    }
  }
  return (0);
}


 

static BOOL clear_clus (U32 clus) {
   
  U32 i;
  U32 sect = clus_to_sect(clus);

   
  memset(ca.buf, 0, 512);
  for (i = 0; i < mmc.SecPerClus; i++) {
    if ((write_cache(sect + i)) == 0) return (0);;
  }
   
  if ((write_cache (0)) == 0) return (0);;
  return (1);
}


 

static BOOL write_fat_link (U32 clus, U32 next_clus) {
   
  U32 sect,ofs,temp;

  sect = get_fat_sect (clus);
  if ((cache_fat (sect)) == 0) return (0);;

  switch (mmc.FatType) {
    case 1:
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
         
        if (clus & 0x001) {
          fat.buf[511] = (fat.buf[511] & 0x0F) | (next_clus << 4);
        }
        else {
          fat.buf[511] = (U8)next_clus;
        }
        fat.dirty = 1;
        sect++;
        if ((cache_fat (sect)) == 0) return (0);;
        if (clus & 0x001) {
          fat.buf[0] = next_clus >> 4;
        }
        else {
          fat.buf[0] = (fat.buf[0] & 0xF0) | (next_clus >> 8);
        }
      }
      break;

    case 2:
      ofs  = (clus & 0xFF) << 1;
      set_u16 (&fat.buf[ofs], next_clus);
      break;

    case 3:
      ofs  = (clus & 0x7F) << 2;
      if ((get_u32(&fat.buf[ofs]) == 0) && free_clus) {
        free_clus--;
      }

      set_u32 (&fat.buf[ofs], next_clus);
      break;

    default:
      return (0);
  }
  fat.dirty = 1;
  return (1);
}


 

static BOOL unlink_clus_chain (U32 clus) {
   
  U32 sect,ofs,next,temp;

  if (clus < 2) {
     
    return (1);
  }

  while (clus < (mmc.DataClusCnt + 2)) {
     
    if (clus < top_clus) {
      top_clus = clus;
    }
    sect = get_fat_sect (clus);
    if ((cache_fat (sect)) == 0) return (0);;

    switch (mmc.FatType) {
      case 1:
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
           
          next = fat.buf[511];
          if (clus & 0x001) {
            fat.buf[511] &= 0x0F;
          }
          else {
            fat.buf[511] = 0;
          }
          fat.dirty = 1;
          sect++;
          if ((cache_fat (sect)) == 0) return (0);;
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

      case 2:
        ofs  = (clus & 0xFF) << 1;
        next = get_u16 (&fat.buf[ofs]);
        *(U16 *)&fat.buf[ofs] = 0;
        goto chk_eoc;

      case 3:
        ofs  = (clus & 0x7F) << 2;
        next = get_u32 (&fat.buf[ofs]);
        *(U32 *)&fat.buf[ofs] = 0;
        free_clus++;
chk_eoc:fat.dirty = 1;
        if (is_EOC (next) == 1) {
          if ((cache_fat (0)) == 0) return (0);;
          return (1);
        }
        break;

      default:
        return (0);
    }
    clus = next;
  }
  if ((cache_fat (0)) == 0) return (0);;
   
  return (0);
}


 

static BOOL alloc_new_clus (U32 *ptr_clus, U8 wr_fat_link) {
   
  U32 clus = *ptr_clus;

  if ((get_free_clus (ptr_clus)) == 0) return (0);;

  if ((write_fat_link (*ptr_clus, get_EOC())) == 0) return (0);;
  if (wr_fat_link) {
     
    if ((write_fat_link (clus, *ptr_clus)) == 0) return (0);;
  }
  if ((cache_fat (0)) == 0) return (0);;

   
  return (1);
}


 

static U32 count_free_clus (void) {
   
  U32 clus,sect,ofs,next,nfree;

  nfree = 0;
  if (mmc.FatType == 1) {
    for (clus = 2; clus < (mmc.DataClusCnt + 2); clus++) {
       
      sect = get_fat_sect (clus);
      if ((cache_fat (sect)) == 0) return (nfree);;
      ofs  = ((clus * 3) / 2) & 0x1FF;
      if (ofs < 511) {
        next = get_u16 (&fat.buf[ofs]);
      }
      else {
         
        next = fat.buf[511];
        if ((cache_fat (sect+1)) == 0) return (nfree);;
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
  if (mmc.FatType == 2) {
    sect = get_fat_sect (2);
    if ((cache_fat (sect)) == 0) return (nfree);;
    for (clus = 2; clus < (mmc.DataClusCnt + 2); clus++) {
      if ((clus & 0xFF) == 0) {
         
        sect++;
        if ((cache_fat (sect)) == 0) return (nfree);;
      }
       
      if (((U16 *)fat.buf)[clus & 0xFF] == 0) {
        nfree++;
      }
    }
    return (nfree);
  }
  if (mmc.FatType == 3) {
    sect = get_fat_sect (2);
    if ((cache_fat (sect)) == 0) return (nfree);;
    for (clus = 2; clus < (mmc.DataClusCnt + 2); clus++) {
      if ((clus & 0x7F) == 0) {
         
        sect++;
        if ((cache_fat (sect)) == 0) return (nfree);;
      }
       
      if (((U32 *)fat.buf)[clus & 0x7F] == 0) {
        nfree++;
      }
    }
    return (nfree);
  }
  return (0);
}


 

static U32 clus_to_sect (U32 clus) {
   
  U32 sect,base;

  base = mmc.BootRecSec + mmc.RootDirAddr;
  if (mmc.FatType != 3) {
    base += mmc.RootSecCnt;
  }
  sect = (clus - 2) * mmc.SecPerClus;
  return (base + sect);
}


 

static U32 get_fat_sect (U32 clus) {
   
  U32 fats;

  switch (mmc.FatType) {
    case 1:
       
      fats = (clus * 3) / 1024;
      break;

    case 2:
       
      fats = clus / 256;
      break;

    case 3:
       
      fats = clus / 128;
      break;

    default:
       
      return (0);
  }
  if (fats >= mmc.FatSize) {
    return (0);
  }
  fats += (mmc.BootRecSec + mmc.RsvdSecCnt);
  return (fats);
}


 

static BOOL read_sector (U32 sect) {
   

  if (sect == ca.sect) {
     
    return (1);
  }

  if (sect >= ca.csect && sect < (ca.csect + ca.nwr)) {
     
    memcpy (ca.buf, ca.cbuf + (sect - ca.csect) * 512, 512);
    ca.sect = sect;
    return (1);
  }

   
  if (mmc_read_sect (sect, ca.buf, 1) == 1) {
    ca.sect = sect;
    return (1);
  }
  ca.sect = 0xFFFFFFFF;
  return (0);
}


 

static BOOL write_sector (U32 sect) {
   

  if (mmc_write_sect (sect, ca.buf, 1) == 1) {
    ca.sect = sect;
    return (1);
  }
  return (0);
}


 

static BOOL read_cache (U32 sect, U32 cnt) {
   

  if ((_MC_CSIZE == 0) || (ca.nwr > 0)) {
     
    return (read_sector (sect));
  }

  if (ca.nrd > 0) {
    if ((ca.csect <= sect) && sect < (ca.csect + ca.nrd)) {
       
      memcpy (ca.buf, ca.cbuf + (sect - ca.csect) * 512, 512);
      ca.sect = sect;
      return (1);
    }
  }

  if (cnt > _MC_CSIZE) {
    cnt = _MC_CSIZE;
  }

   
  if (mmc_read_sect (sect, ca.buf, cnt) == 1) {
    ca.sect  = sect;
     
    ca.csect = sect + 1;
    ca.nrd   = cnt - 1;
    return (1);
  }
  ca.sect = 0xFFFFFFFF;
  ca.nrd  = 0;
  return (0);
}


 

static BOOL write_cache (U32 sect) {
   

  if (_MC_CSIZE == 0) {
     
    if (sect) {
      if ((write_sector (sect)) == 0) return (0);;
    }
    return (1);
  }
  if (sect == 0) {
     
    if (ca.nwr) {
      if ((mmc_write_sect (ca . csect, ca . cbuf, ca . nwr)) == 0) return (0);;
      ca.nwr = 0;
    }
    return (1);
  }
  ca.sect = sect;
  if (ca.nwr > 0) {
    if (sect == (ca.csect + ca.nwr) && ca.nwr < _MC_CSIZE) {
       
      memcpy (ca.cbuf + (ca.nwr * 512), ca.buf, 512);
      ca.nwr++;
      return (1);
    }
     
    if ((mmc_write_sect (ca . csect, ca . cbuf, ca . nwr)) == 0) return (0);;
    ca.nwr = 0;
  }
   
  memcpy (ca.cbuf, ca.buf, 512);
  ca.csect = sect;
  ca.nwr   = 1;
  ca.nrd   = 0;
  return (1);
}


 

static BOOL cache_fat (U32 sect) {
   

  if (sect == fat.sect) {
     
    return (1);
  }
  if (fat.dirty == 1) {
     
    if ((mmc_write_sect (fat . sect, fat . buf, 1)) == 0) return (0);;
    fat.dirty = 0;
  }
  if (sect == 0) {
     
    return (1);
  }
  if (mmc_read_sect (sect, fat.buf, 1) == 1) {
    fat.sect = sect;
    return (1);
  }
  fat.sect = 0xFFFFFFFF;
  return (0);
}


 

static BOOL is_EOC (U32 clus) {
   

  switch (mmc.FatType) {
    case 1:
      if (clus >= 0x0FF8) {
        return (1);
      }
      break;
    case 2:
      if (clus >= 0xFFF8) {
        return (1);
      }
      break;
    case 3:
      if ((clus & 0x0FFFFFFF) >= 0x0FFFFFF8) {
        return (1);
      }
      break;
  }
  return (0);
}


 

static U32 get_EOC (void) {
   

  switch (mmc.FatType) {
    case 1:
      return (0x0FFF);
    case 2:
      return (0xFFFF);
    case 3:
      return (0x0FFFFFFF);
  }
  return (0);
}


 

static BOOL get_mbrec (void) {
   

   
  if ((read_sector (0)) == 0) return (0);;

   
  if (get_u16 (&ca.buf[510]) != 0xAA55) {
     
    return (0);
  }

  if ((ca.buf[0] == 0xE9) || (ca.buf[0] == 0xEB && ca.buf[2] == 0x90)) {
     
    mmc.BootRecSec = 0;
  }
  else {
     
    mmc.BootRecSec = get_u32 (&ca.buf[454]);
  }
  return (1);
}


 

static BOOL get_bootrec (void) {
   

  if ((read_sector (mmc . BootRecSec)) == 0) return (0);;

   
  if (get_u16 (&ca.buf[510]) != 0xAA55) {
     
    return (0);
  }
   
  mmc.SecPerClus = ca.buf[13];
  mmc.BytesPerSec= get_u16 (&ca.buf[11]);
  mmc.RsvdSecCnt = get_u16 (&ca.buf[14]);
  mmc.NumOfFat   = ca.buf[16];
  mmc.RootEntCnt = get_u16 (&ca.buf[17]);
  mmc.DskSize    = get_u16 (&ca.buf[19]);
  mmc.FatSize    = get_u16 (&ca.buf[22]);

  if ((mmc.DskSize == 0) && (mmc.FatSize == 0)) {
     
    mmc.FAT32_ExtFlags  = get_u16 (&ca.buf[40]);
    mmc.FAT32_RootClus  = get_u32 (&ca.buf[44]);
    mmc.FAT32_FSInfo    = get_u16 (&ca.buf[48]);
    mmc.FAT32_BkBootSec = get_u16 (&ca.buf[50]);
  }

  if (mmc.DskSize == 0) {
     
    mmc.DskSize = get_u32 (&ca.buf[32]);
  }

  if (mmc.FatSize == 0) {
     
    mmc.FatSize = get_u32 (&ca.buf[36]);
  }

  return (1);
}


 

static BOOL is_fat_valid (void) {
   

   
  if (mmc.BytesPerSec != 512) {
    return (0);
  }
   
  switch (mmc.SecPerClus) {
    case 1:
    case 2:
    case 4:
    case 8:
    case 16:
    case 32:
    case 64: break;
    default: return (0);
  }
   
  if (mmc.RsvdSecCnt == 0 || mmc.RsvdSecCnt > 64) {
    return (0);
  }
   
  switch (mmc.NumOfFat) {
    case 1:
    case 2:  break;
    default: return (0);
  }
  if (mmc.FatSize > mmc.DskSize) {
    return (0);
  }
  return (1);
}


 

static U16 get_time (void) {
   
  U32 retv, time, v;

  time = fs_get_time ();

   
  v = (time >> 1) & 0x1F;
  if (v > 29) v = 0;
  retv = v;

   
  v = (time >> 8) & 0x3F;
  if (v > 59) v = 0;
  retv |= (v << 5);

   
  v = (time >> 16) & 0x1F;
  if (v > 23) v = 23;
  retv |= (v << 11);

  return (retv);
}


 

static U16 get_date (void) {
   
  U32 retv, date, v;

  date = fs_get_date ();

   
  v = date & 0x1F;
  if (v == 0) v = 1;
  retv = v;

   
  v = (date >> 8) & 0x0F;
  if (v > 12 || v == 0) v = 1;
  retv |= (v << 5);

   
  v  = (date >> 16) - 1980;
  v &= 0x7F;
  retv |= (v << 9);

  return (retv);
}


 

static void set_time_date (FINFO *info, FILEREC *frec) {
   
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


 

static BOOL cvt_fatname (const char *fn, char *en) {
   
  
 
  BOOL dot = 0;
  U8   ch0, ch1, ch2;
  U32  i;

   
  for (i = 0; i < 11; i++) {
    en[i] = ' ';
  }
   
  en[i] = 0;

   
  ch0 = *fn;
  ch1 = *(fn + 1);
  ch2 = *(fn + 2);
  if (ch0 == '.') {
    if (ch1 == 0) {
      en[0] = '.';
      return (1);
    }
    else if (ch1 == '.' && ch2 == 0) {
      en[0] = '.';
      en[1] = '.';
      return (1);
    }
  }

   
  for (i = 0; i < 8; ) {
    if (!(*fn))     {          return (1); }
    if (*fn == '.') { dot = 1; fn++; break;     }
    if (*fn == ' ') {          fn++; continue;  }
    en[i] = val_char(*fn);
    if (en[i] >= 'a' && en[i] <= 'z')
      en[i] = en[i] & (~0x20);
    i  ++;
    fn ++;
  }

   
  for (i = 8; i < 11; ) {
    if (!(*fn))     {         return (1); }
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
  return (1);
}


 

static BOOL check_lfn (const char *fn) {
   
  BOOL dot = 0;
  U8   ch, prev_ch = 0;
  U32  i = 0, j = 0;

  while (*fn) {
    if (val_char_sn (*fn) == 0) {
      goto lfn;
    }

     
    if (*fn == ' ') goto lfn;

    
 
    if (*fn == '.') {
      if (dot) goto lfn;
      fn ++;
      j   = 0;
      dot = 1;
      continue;
    }

    
 
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
     
lfn:return (1);
  }

   
  return (0);
}


 

static U8 val_char (U8 ch) {
  
 

  if (val_char_sn (ch) == 0) {
    return ('X');
  }

  return (ch);
}


 

static BOOL val_char_sn (U8 ch) {
   

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

     
    return (1);
  }

   
  return (0);
}


 
#line 2017 "FlashFS\\fs_fat.c"

 

static U8 val_char_lab (U8 ch) {
   

  if ((ch >= '0' && ch <= '9') ||
      (ch >= 'A' && ch <= 'Z') ||
      (ch == '_') || (ch == ' ')) {
    return (ch);
  }
  if (ch >= 'a' && ch <= 'z') {
     
    return (ch & ~0x20);
  }
   
  return (0);
}


 

static BOOL get_dir_name (const char *fn, char *dn, unsigned int *sz) {
  

 
  

 
  U8  ch;
  U32 i, j;

  for (i = 0, j = 0; ; i++) {
    ch = *(fn + i);
    if (ch == '\\' || ch == '\"') {
      dn[j] = 0;
      *sz   = i + 1;
      return (1);
    }
    if (ch == 0) {
      dn[j] = 0;
      return (0);
    }
    dn[j++] = ch;
  }
}


 

static BOOL get_nt_name (const char *fn, char *sn, int num) {
  

 
  

 
  U8  ch = 0;
  S8  num_sz;
  U32 dot_pos  = 0xFFFF;
  U32 val, i, j;

   
  if      (num > 99999) num_sz = 6;
  else if (num >  9999) num_sz = 5;
  else if (num >   999) num_sz = 4;
  else if (num >    99) num_sz = 3;
  else if (num >     9) num_sz = 2;
  else                  num_sz = 1;

   
  for (i = 0; *(fn + i); i++) {
    if (*(fn + i) == '.') dot_pos = i;
  }

  if (num == 0) {
     
    num_sz = - 1;
  }

   
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
         
        ch &= ~0x20;
      }
      sn[j++] = val_char (ch);
    }
  }

terminate_name:
  sn[j] = 0;                            

  return (1);
}


 

static U32 get_dir_sect (U32 clus) {
   
  U32 sect;

  in_root_1x = 0;
  if (clus == 0) {
    startDirClus = 0;

     
    if (mmc.FatType == 3) {
       
      sect = clus_to_sect (mmc.FAT32_RootClus);
    }
    else {
       
      sect = mmc.BootRecSec + mmc.RootDirAddr;
      in_root_1x = 1;
    }
  }
  else {
     
    sect = clus_to_sect (clus);
  }
  return (sect);
}


 

static BOOL search_for_name (const char *name, IOB *fcb, U8 type, U8 keep_fcb) {
  
 

  char         sen[13];
  FILEREC     *frec;
  U8           lfn_f         = 0;
  U8           dir_f         = (type == 1);
  U8           same_f        = 1;
  U8           type_f        = 0;
  U8           sfn_name_f    = 0;
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

   
  if (check_lfn(name) == 1) {
     
    name_ents += ((strlen(name) + 12) / 13);
  }

   
  sfn_name_f = cvt_fatname (name, sen);

   
  sect = get_dir_sect (clus);

   
  for (idx = 0;  ; idx++) {
    if (in_root_1x) {
      if (idx == 512) {
        return (0);
      }
    }
    else {
       
      if (idx == mmc.EntsPerClus) {
        idx = 0;
        if (clus < mmc.FAT32_RootClus) {
          clus = mmc.FAT32_RootClus;
        }
        if ((set_next_clus (&clus)) == 0) return (0);;
        if (is_EOC (clus)) {
           
          goto not_found;
        }
        sect = clus_to_sect (clus);
      }
    }

    if ((read_sector (sect + (idx >> 4))) == 0) return (0);;
    frec = (FILEREC *)ca.buf + (idx & 0x0F);

    if (frec->FileName[0] == 0x00) {
       
      goto not_found;
    }

    if (frec->FileName[0] == 0xE5) {
       
      continue;
    }

    if (frec->Attr == 0x08) {
       
      continue;
    }

    if ((frec->Attr == (0x01 | 0x02 | 0x04 | 0x08)) && (((LFN_FILEREC *)frec)->Ordinal & 0x40)) {
       
      lfn_f           = 1;
      same_f          = 1;
      if (((((LFN_FILEREC *)frec)->Ordinal & ~0x40) + 1) != name_ents) {
        same_f       = 0;
      }
      first_clus      = clus;
      first_offs      = idx;
      ents            = 0;
      chksum          = ((LFN_FILEREC *)frec)->Checksum;
    }

    
 
    type_f = !(dir_f ^ ((frec->Attr & 0x10) == 0x10));

    if (lfn_f) {
       
      ents ++;

      if (frec->Attr != (0x01 | 0x02 | 0x04 | 0x08)) {
         
        lfn_f = 0;

         
        if ((same_f) && (chksum == lfn_calc_chksum(frec->FileName))) {
          if (type_f) {
             
            if (keep_fcb) {
              goto found_keep_fcb;
            }
            goto found;
          }
        }
        else {
          
 
          if (name_ents == 1)
            goto chk_short;
        }
      }

      if (!same_f) {
         
        continue;
      }

      if (chksum != ((LFN_FILEREC *)frec)->Checksum) {
        
 
        same_f = 0;
        continue;
      }

       
      i = ((((LFN_FILEREC *)frec)->Ordinal & 0x1F) - 1) * 13;

       
      same_f = lfn_cmp_name ((U8 *)frec, (char *)&name[i]);
    }
    else if (name_ents == 1) {
       
      first_clus = clus;
      first_offs = idx;
      ents       = 1;

       
      if (!type_f) { 
        continue; 
      }

chk_short:
       
      if (sfn_name_f == 0) { 
        continue; 
      }

       
      same_f = sfn_cmp_name (frec->FileName, sen);

       
      if (same_f) {
        if (keep_fcb) {
          goto found_keep_fcb;
        }
        goto found;
      }
    }
  }

not_found:
  return (0);

found_keep_fcb:
  return (1);

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
  return (1);
}


 

static BOOL find_name (const char *name, IOB *fcb, U8 type) {
  
 

  return (search_for_name (name, fcb, type, 0x00));
}


 

static BOOL check_name (const char *name, IOB *fcb, U8 type) {
   

  return (search_for_name (name, fcb, type, 0x01));
}


 

static BOOL alloc_name (const char *name, IOB *fcb) {
  
 
  FILEREC     *frec;
  U8           name_ents     = 1;
  U8           ents          = 0;
  U16          first_offs    = 0;
  U32          first_clus    = 0;
  U32          clus          = fcb->_firstClus;
  U32          sect;
  U32          idx;

   
  if (check_lfn(name) == 1) {
     
    name_ents += ((strlen(name) + 12) / 13);
  }

   
  sect = get_dir_sect (clus);

   
  for (idx = 0;  ; idx++) {
    if (in_root_1x) {
      if (idx == 512) {
        return (0);
      }
    }
    else {
       
      if (idx == mmc.EntsPerClus) {
        idx = 0;
        if (clus < mmc.FAT32_RootClus) {
          clus = mmc.FAT32_RootClus;
        }
        first_clus = clus;
        if ((set_next_clus (&clus)) == 0) return (0);;
        if (is_EOC (clus)) {
           

           
          clus = first_clus;
          if ((alloc_new_clus (&clus, 1)) == 0) return (0);;
          if ((clear_clus (clus)) == 0) return (0);;
          first_offs = 0;
          first_clus = clus;
          goto allocated;
        }
        sect = clus_to_sect (clus);
      }
    }

    if ((read_sector (sect + (idx >> 4))) == 0) return (0);;
    frec = (FILEREC *)ca.buf + (idx & 0x0F);

    if ((frec->FileName[0] == 0x00) || (frec->FileName[0] == 0xFF)) {
       

      if (ents) {
         
        goto allocated;
      }
       
      first_offs = idx;
      first_clus = clus;
      goto allocated;
    }

    if (frec->FileName[0] == 0xE5) {
       

      if (ents++ == 0) {
         
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

     
    ents = 0;
  }

allocated:
  firstEntOffs      = first_offs;
  firstEntClus      = first_clus;
  return (1);
}


 

static BOOL get_next_info (FINFO *info, IOB *fcb) {
   
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

   
  for (idx = info->fileID;  ; idx++) {
    if (in_root_1x) {
      if (idx == 512) {
        return (0);
      }
    }
    else {
       
      while (idx >= mmc.EntsPerClus) {
        idx -= mmc.EntsPerClus;
        if (clus < mmc.FAT32_RootClus) {
          clus = mmc.FAT32_RootClus;
        }
        if ((set_next_clus (&clus)) == 0) return (0);;
        if (is_EOC (clus)) {
           
          goto no_more_entries;
        }
        sect = clus_to_sect (clus);
      }
    }
    idx_inc ++;

    if ((read_sector (sect + (idx >> 4))) == 0) return (0);;
    frec      = (FILEREC *)ca.buf + (idx & 0x0F);

    if (frec->FileName[0] == 0x00) {
       
      goto no_more_entries;
    }

    if (frec->FileName[0] == 0xE5) {
       
      continue;
    }

    if (frec->Attr == 0x08) {
       
      continue;
    }

    if ((frec->Attr == (0x01 | 0x02 | 0x04 | 0x08)) && (((LFN_FILEREC *)frec)->Ordinal & 0x40)) {
       
      lfn_f   = 1;
      valid_f = 1;
      chksum  = ((LFN_FILEREC *)frec)->Checksum;
    }

    if (lfn_f) {
       

      if (frec->Attr != (0x01 | 0x02 | 0x04 | 0x08)) {
         
        lfn_f = 0;

         
        calc_chksum = lfn_calc_chksum (frec->FileName);
        if ((valid_f) && (calc_chksum == chksum)) {
          goto found;
        }
      }

      if (!valid_f) {
         
        continue;
      }

      if (chksum != ((LFN_FILEREC *)frec)->Checksum) {
        
 
        valid_f = 0;
        continue;
      }

       
      i = ((((LFN_FILEREC *)frec)->Ordinal & 0x1F) - 1) * 13;

       
      lfn_copy_info (&info->name[i], (U8 *)frec);
      i += 13;

      if (((LFN_FILEREC *)frec)->Ordinal & 0x40) {
        info->name[i] = 0;
      }
    }
    else {
       

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
  return (0);

found:
  info->fileID += idx_inc;
  fcb->attrib   = frec->Attr;
  fcb->fsize    = get_u32 ((U8 *)&frec->FileSize);
  set_time_date (info, frec);
  return (1);
}


 

static BOOL chk_dir_empty (IOB *fcb) {
  
 
  FILEREC     *frec;
  U32          clus          = fcb->_firstClus;
  U32          idx;
  U32          sect;

  if (clus == 0) {
     
    goto dir_not_empty;
  }

   
  sect = clus_to_sect (clus);

   
  for (idx = 0; ; idx ++) {
     
    if (idx == mmc.EntsPerClus) {
      idx = 0;
      if ((set_next_clus (&clus)) == 0) return (0);;
      if (is_EOC (clus)) {
         
        goto dir_empty;
      }
      sect = clus_to_sect (clus);
    }

    if ((read_sector (sect + (idx >> 4))) == 0) return (0);;
    frec      = (FILEREC *)ca.buf + (idx & 0x0F);

    if (frec->FileName[0] == '.') {
      if (strcmp ((const char *)&frec->FileName[0], ".          \x10") == 0) {
         
        continue;
      }
      if (strcmp ((const char *)&frec->FileName[0], "..         \x10") == 0) {
         
        continue;
      }
    }

    if (frec->FileName[0] == 0x00) {
       
      goto dir_empty;
    }

    if (frec->FileName[0] == 0xE5) {
       
      continue;
    }

    if (frec->Attr == 0x08) {
       
      continue;
    }

    goto dir_not_empty;
  }

dir_not_empty:
  return (0);

dir_empty:
  return (1);
}


 

static BOOL read_last_entry (IOB *fcb, FILEREC *filerec) {
   
  FILEREC     *frec;
  U32          clus          = fcb->_lastEntClus;
  U32          idx           = (U32)fcb->fileID;
  U32          sect;

   
  sect = get_dir_sect (clus);

  if ((read_sector (sect + (idx >> 4))) == 0) return (0);;
  frec = (FILEREC *)ca.buf + (idx & 0x0F);

   
  memcpy (filerec, frec, 32);

   
  return (1);
}


 

static BOOL write_last_entry (IOB *fcb, FILEREC *filerec) {
   
  FILEREC     *frec;
  U32          clus          = fcb->_lastEntClus;
  U32          idx           = (U32)fcb->fileID;
  U32          sect;

   
  sect = get_dir_sect (clus);

  if ((read_sector (sect + (idx >> 4))) == 0) return (0);;
  frec = (FILEREC *)ca.buf + (idx & 0x0F);

   
  memcpy (frec, filerec, 32);

  if ((write_sector (sect + (idx >> 4))) == 0) return (0);;

   
  return (1);
}


 

static BOOL write_entries (const char *name, IOB *fcb, U8 type, FILEREC *copy_frec) {
  

 
  char         sfn[13];
  char         sen[13];
  FILEREC     *frec;
  U8           lfn_f         = 0;
  U8           dir_f         = (type == 1);
  U8           name_lfn_f    = check_lfn (name);
  U8           calc_chksum   = 0;
  U32          clus          = firstEntClus;
  U32          idx           = firstEntOffs;
  U32          sect;
  U32          sz            = strlen (name);
  U32          i, j;

   
  sect = get_dir_sect (clus);

  if (!name_lfn_f) {
     
    cvt_fatname (name, sen);
  }
  else {
     
    i = 0;
    while (get_nt_name  (name, sfn, i++) == 1) {
      if (check_name (sfn, fcb, 0) == 0) {
         
        cvt_fatname (sfn, sen);
        break;
      }
      if (i > (999999 - 1)) {
         
        return (0);
      }
    }
  }

  

 

   
  if (name_lfn_f) {
    calc_chksum = lfn_calc_chksum ((U8 *)sen);
  }

   
  for ( ; ; idx ++) {
     
    if (in_root_1x) {
      if (idx == 512) {
        goto fail;
      }
    }
    else {
       
      if (idx == mmc.EntsPerClus) {
        idx = 0;
        
 
        if (clus < mmc.FAT32_RootClus) {
          clus = mmc.FAT32_RootClus;
        }
        if ((alloc_new_clus (&clus, 1)) == 0) return (0);;
        if ((clear_clus (clus)) == 0) return (0);;
        sect = clus_to_sect (clus);
      }
    }

    if ((read_sector (sect + (idx >> 4))) == 0) return (0);;
    frec      = (FILEREC *)ca.buf + (idx & 0x0F);

    if (name_lfn_f) {
       
      if (lfn_f) {
         
        ((LFN_FILEREC *)frec)->Ordinal = 0;
      }
      else {
         
        lfn_f = 1;
        ((LFN_FILEREC *)frec)->Ordinal = 0x40;
      }

      if (sz) {
         
        ((LFN_FILEREC *)frec)->Ordinal    |= ((sz + 12) / 13);
        ((LFN_FILEREC *)frec)->Checksum    = calc_chksum;
        ((LFN_FILEREC *)frec)->FirstClusLO = 0;
        ((LFN_FILEREC *)frec)->Attr        = (0x01 | 0x02 | 0x04 | 0x08);

         
        i = ((((LFN_FILEREC *)frec)->Ordinal & 0x1F) - 1) * 13;

         
        lfn_copy_name ((U8 *)frec, (char *)&name[i]);

        if (sz > 12) {
          sz -= 13;
        }
        else {
          sz = 0;
        }

        if ((idx & 0x0F) == 0x0F) {
          
 
          if ((write_sector (sect + (idx >> 4))) == 0) return (0);;
        }
      }
      else {
         
        goto wr_short;
      }
    }
    else {
       

wr_short:
       
      for (j = 0; j < 11; j++) {
        frec->FileName[j]  = sen[j];
      }

      if (copy_frec == 0) {
         

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
           
          frec->Attr        = 0x10;
          fcb->_lastEntClus = clus;
          fcb->fileID       = idx;
           
          if (clus < mmc.FAT32_RootClus) {
            clus = mmc.FAT32_RootClus;
          }
          if ((alloc_new_clus (&clus, 0)) == 0) return (0);;
          fcb->_firstClus   = clus;

          set_u16 ((U8 *)&frec->FirstClusHI, clus >> 16);
          set_u16 ((U8 *)&frec->FirstClusLO, clus      );

          if ((write_sector (sect + (idx >> 4))) == 0) return (0);;

          if ((clear_clus (clus)) == 0) return (0);;
          goto success_dir;
        }
        else {
           
          frec->Attr        = 0x20;
          frec->FirstClusHI = 0;
          frec->FirstClusLO = 0;
          fcb->_firstClus   = 0;

          if ((write_sector (sect + (idx >> 4))) == 0) return (0);;
        }
      }
      else {
         
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

        if ((write_sector (sect + (idx >> 4))) == 0) return (0);;
      }


       
      goto success;
    }
  }

fail:
  return (0);

success:
  fcb->fileID       = idx;
  fcb->_lastEntClus = clus;

success_dir:
  return (1);
}


 

static BOOL delete_entries (IOB *fcb, U8 keep_data) {
   
  FILEREC     *frec;
  U8           ents          = numOfEntries;
  U32          clus          = firstEntClus;
  U32          idx           = firstEntOffs;
  U32          sect;

   
  sect = get_dir_sect (clus);

  for ( ; ents != 0; idx ++) {
     
    if (in_root_1x) {
      if (idx == 512) {
        goto fail;
      }
    }
    else {
       
      if (idx == mmc.EntsPerClus) {
        idx = 0;
        if (clus < mmc.FAT32_RootClus) {
          clus = mmc.FAT32_RootClus;
        }
        if ((set_next_clus (&clus)) == 0) return (0);;
        sect = clus_to_sect (clus);
      }
    }

    if ((read_sector (sect + (idx >> 4))) == 0) return (0);;
    frec              = (FILEREC *)ca.buf + (idx & 0x0F);
    frec->FileName[0] = 0xE5;

    -- ents;
    if (((idx & 0x0F) == 0x0F) || (ents == 0)) {
       
      if ((write_sector (sect + (idx >> 4))) == 0) return (0);;
    }
  }

  if (!keep_data) {
     
    if ((unlink_clus_chain (fcb->_firstClus)) == 0) return (0);;
  }

   
  return (1);

fail:
  return (0);
}


 


static BOOL rename_entries (const char *new_name, IOB *fcb, U8 type) {
   
  FILEREC      old_frec;
  U8           name_lfn_f    = check_lfn (new_name); 
  U8           longer_f;
  U8           ents          = numOfEntries;

   
  if ((read_last_entry (fcb, &old_frec)) == 0) return (0);;

   
  longer_f     = 0;
  if (name_lfn_f) {
    if (ents == 1) {
      longer_f = 1;
    }
    else if (((strlen(new_name) + 12) / 13) > ents) {
      longer_f = 1;
    }
  }

   
  if ((delete_entries (fcb, 1)) == 0) return (0);;

  if (longer_f) {
     

     
    fcb->_firstClus = firstEntClus;
    if (alloc_name (new_name, fcb) == 0) {
       
      goto fail;
    }
  }

   
  if (write_entries (new_name, fcb, type, &old_frec) == 0) {
     
    goto fail;
  }

   
  return(1);

fail:
  return (0);
}


 

static BOOL write_dot_entries (IOB *fcb) {
   
  FILEREC     *frec;
  U16          time, date;
  U32          idx           = 0;
  U32          clus          = fcb->_firstClus;
  U32          sect;

   
  time = get_time ();
  date = get_date ();

   
  memset (ca.buf, 0, 512);

   
  frec = (FILEREC *)ca.buf;
  memcpy (&frec->FileName[0], ".          ", 11);
  frec->Attr   = 0x10;
  set_u16 ((U8 *)&frec->CrtTime, time);
  set_u16 ((U8 *)&frec->CrtDate, date);
  set_u16 ((U8 *)&frec->LastAccDate, date);
  set_u16 ((U8 *)&frec->WriteTime, time);
  set_u16 ((U8 *)&frec->WriteDate, date);

   
  memcpy (frec + 1, frec, sizeof (FILEREC));

  set_u16 ((U8 *)&frec->FirstClusHI, (fcb->_firstClus >> 16));
  set_u16 ((U8 *)&frec->FirstClusLO, (fcb->_firstClus      ));

   
  frec++;
  frec->FileName[1] = '.';

   
  set_u16 ((U8 *)&frec->FirstClusHI, (startDirClus >> 16));
  set_u16 ((U8 *)&frec->FirstClusLO, (startDirClus      ));

   
  sect = clus_to_sect (clus);
  if ((write_sector (sect)) == 0) return (0);;

   
  memset (ca.buf, 0, 2*sizeof (FILEREC));
  for (idx = 1; idx < mmc.SecPerClus; idx++) {
    if ((write_sector (sect + idx)) == 0) return (0);;
  }

   
  fcb->fileID = 2;

   
  return (1);
}


 

static U8 lfn_calc_chksum (U8 *fn) {
   
  U32 i;
  U8  sum;

  sum = 0;
  for (i = 0; i < 11; i++) {
    sum = ((sum & 1) ? 0x80 : 0) + (sum >> 1) + fn[i];
  }
  return (sum);
}


 

static void lfn_copy_name (U8 *lfn, char *fn) {
   
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


 

static BOOL lfn_cmp_name (U8 *lfr, char *fn) {
   
  U32 i;

  for (i = 0; i < 13; i++) {
    if ((lfr[ChIndex[i]] ^ fn[i]) & ~0x20) {
       
      return (0);
    }
    if (fn[i] == 0) break;
  }
  return (1);
}


 

static BOOL sfn_cmp_name (U8 *sfn, char *fn) {
   
  U32 i;

  for (i = 0; i < 11; i++) {
    if ((sfn[i] ^ fn[i]) & ~0x20) {
       
      return (0);
    }
    if (fn[i] == 0) break;
  }
  return (1);
}


 

static void lfn_copy_info (S8 *fn, U8 *lfn) {
   
  U32 i;

  for (i = 0; i < 13; i++) {
    fn[i] = lfn[ChIndex[i]];
  }
}


 

static BOOL chk_param (const char *par, const char *sp) {
   

  while (*sp != 0) {
    if (*sp++ == '/') {
      if (fn_cmp (par, sp) == 1) {
         
        return (1);
      }
    }
  }
  return (0);
}


 

static U16 get_u16 (U8 *nr) {
   




  return ((nr[1] << 8) | nr[0]);

}


 

static U32 get_u32 (U8 *nr) {
   




  return ((nr[3] << 24) | (nr[2] << 16) | (nr[1] << 8) | nr[0]);

}


 

static void set_u16 (U8 *nr, U16 val) {
   





  nr[1] = val >> 8;
  nr[0] = val;

}


 

static void set_u32 (U8 *nr, U32 val) {
   

#line 3295 "FlashFS\\fs_fat.c"
  nr[3] = val >> 24;
  nr[2] = val >> 16;
  nr[1] = val >> 8;
  nr[0] = val;

}




 
