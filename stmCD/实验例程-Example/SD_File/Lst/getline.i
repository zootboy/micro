#line 1 "Getline.c"








 

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






 
  

 
#line 12 "Getline.c"
#line 1 "d:\\Keil\\ARM\\RV31\\INC\\stdio.h"
 
 
 





 






 









#line 34 "d:\\Keil\\ARM\\RV31\\INC\\stdio.h"


  
  typedef unsigned int size_t;    








 
 

 
  typedef struct __va_list __va_list;





   




 




typedef struct __fpos_t_struct {
    unsigned __int64 __pos;
    



 
    struct {
        unsigned int __state1, __state2;
    } __mbstate;
} fpos_t;
   


 


   

 

typedef struct __FILE FILE;
   






 

extern FILE __stdin, __stdout, __stderr;
extern FILE *__aeabi_stdin, *__aeabi_stdout, *__aeabi_stderr;

#line 125 "d:\\Keil\\ARM\\RV31\\INC\\stdio.h"
    

    

    





     



   


 


   


 

   



 

   


 




   


 





    


 






extern __declspec(__nothrow) int remove(const char *  ) __attribute__((__nonnull__(1)));
   





 
extern __declspec(__nothrow) int rename(const char *  , const char *  ) __attribute__((__nonnull__(1,2)));
   








 
extern __declspec(__nothrow) FILE *tmpfile(void);
   




 
extern __declspec(__nothrow) char *tmpnam(char *  );
   











 

extern __declspec(__nothrow) int fclose(FILE *  ) __attribute__((__nonnull__(1)));
   







 
extern __declspec(__nothrow) int fflush(FILE *  );
   







 
extern __declspec(__nothrow) FILE *fopen(const char * __restrict  ,
                           const char * __restrict  ) __attribute__((__nonnull__(1,2)));
   








































 
extern __declspec(__nothrow) FILE *freopen(const char * __restrict  ,
                    const char * __restrict  ,
                    FILE * __restrict  ) __attribute__((__nonnull__(2,3)));
   








 
extern __declspec(__nothrow) void setbuf(FILE * __restrict  ,
                    char * __restrict  ) __attribute__((__nonnull__(1)));
   




 
extern __declspec(__nothrow) int setvbuf(FILE * __restrict  ,
                   char * __restrict  ,
                   int  , size_t  ) __attribute__((__nonnull__(1)));
   















 
#pragma __printf_args
extern __declspec(__nothrow) int fprintf(FILE * __restrict  ,
                    const char * __restrict  , ...) __attribute__((__nonnull__(1,2)));
   


















 
#pragma __printf_args
extern __declspec(__nothrow) int _fprintf(FILE * __restrict  ,
                     const char * __restrict  , ...) __attribute__((__nonnull__(1,2)));
   



 
#pragma __printf_args
extern __declspec(__nothrow) int printf(const char * __restrict  , ...) __attribute__((__nonnull__(1)));
   




 
#pragma __printf_args
extern __declspec(__nothrow) int _printf(const char * __restrict  , ...) __attribute__((__nonnull__(1)));
   



 
#pragma __printf_args
extern __declspec(__nothrow) int sprintf(char * __restrict  , const char * __restrict  , ...) __attribute__((__nonnull__(1,2)));
   






 
#pragma __printf_args
extern __declspec(__nothrow) int _sprintf(char * __restrict  , const char * __restrict  , ...) __attribute__((__nonnull__(1,2)));
   



 

#pragma __printf_args
extern __declspec(__nothrow) int snprintf(char * __restrict  , size_t  ,
                     const char * __restrict  , ...) __attribute__((__nonnull__(3)));
   















 

#pragma __printf_args
extern __declspec(__nothrow) int _snprintf(char * __restrict  , size_t  ,
                      const char * __restrict  , ...) __attribute__((__nonnull__(3)));
   



 
#pragma __scanf_args
extern __declspec(__nothrow) int fscanf(FILE * __restrict  ,
                    const char * __restrict  , ...) __attribute__((__nonnull__(1,2)));
   






























 
#pragma __scanf_args
extern __declspec(__nothrow) int _fscanf(FILE * __restrict  ,
                     const char * __restrict  , ...) __attribute__((__nonnull__(1,2)));
   



 
#pragma __scanf_args
extern __declspec(__nothrow) int scanf(const char * __restrict  , ...) __attribute__((__nonnull__(1)));
   






 
#pragma __scanf_args
extern __declspec(__nothrow) int _scanf(const char * __restrict  , ...) __attribute__((__nonnull__(1)));
   



 
#pragma __scanf_args
extern __declspec(__nothrow) int sscanf(const char * __restrict  ,
                    const char * __restrict  , ...) __attribute__((__nonnull__(1,2)));
   








 
#pragma __scanf_args
extern __declspec(__nothrow) int _sscanf(const char * __restrict  ,
                     const char * __restrict  , ...) __attribute__((__nonnull__(1,2)));
   



 

 
extern __declspec(__nothrow) int vfscanf(FILE * __restrict  , const char * __restrict  , __va_list) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) int vscanf(const char * __restrict  , __va_list) __attribute__((__nonnull__(1)));
extern __declspec(__nothrow) int vsscanf(const char * __restrict  , const char * __restrict  , __va_list) __attribute__((__nonnull__(1,2)));

extern __declspec(__nothrow) int _vfscanf(FILE * __restrict  , const char * __restrict  , __va_list) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) int _vscanf(const char * __restrict  , __va_list) __attribute__((__nonnull__(1)));
extern __declspec(__nothrow) int _vsscanf(const char * __restrict  , const char * __restrict  , __va_list) __attribute__((__nonnull__(1,2)));

extern __declspec(__nothrow) int vprintf(const char * __restrict  , __va_list  ) __attribute__((__nonnull__(1)));
   





 
extern __declspec(__nothrow) int _vprintf(const char * __restrict  , __va_list  ) __attribute__((__nonnull__(1)));
   



 
extern __declspec(__nothrow) int vfprintf(FILE * __restrict  ,
                    const char * __restrict  , __va_list  ) __attribute__((__nonnull__(1,2)));
   






 
extern __declspec(__nothrow) int vsprintf(char * __restrict  ,
                     const char * __restrict  , __va_list  ) __attribute__((__nonnull__(1,2)));
   






 

extern __declspec(__nothrow) int vsnprintf(char * __restrict  , size_t  ,
                     const char * __restrict  , __va_list  ) __attribute__((__nonnull__(3)));
   







 

extern __declspec(__nothrow) int _vsprintf(char * __restrict  ,
                      const char * __restrict  , __va_list  ) __attribute__((__nonnull__(1,2)));
   



 
extern __declspec(__nothrow) int _vfprintf(FILE * __restrict  ,
                     const char * __restrict  , __va_list  ) __attribute__((__nonnull__(1,2)));
   



 
extern __declspec(__nothrow) int _vsnprintf(char * __restrict  , size_t  ,
                      const char * __restrict  , __va_list  ) __attribute__((__nonnull__(3)));
   



 
extern __declspec(__nothrow) int fgetc(FILE *  ) __attribute__((__nonnull__(1)));
   







 
extern __declspec(__nothrow) char *fgets(char * __restrict  , int  ,
                    FILE * __restrict  ) __attribute__((__nonnull__(1,3)));
   










 
extern __declspec(__nothrow) int fputc(int  , FILE *  ) __attribute__((__nonnull__(2)));
   







 
extern __declspec(__nothrow) int fputs(const char * __restrict  , FILE * __restrict  ) __attribute__((__nonnull__(1,2)));
   




 
extern __declspec(__nothrow) int getc(FILE *  ) __attribute__((__nonnull__(1)));
   







 




    extern __declspec(__nothrow) int (getchar)(void);

   





 
extern __declspec(__nothrow) char *gets(char *  ) __attribute__((__nonnull__(1)));
   









 
extern __declspec(__nothrow) int putc(int  , FILE *  ) __attribute__((__nonnull__(2)));
   





 




    extern __declspec(__nothrow) int (putchar)(int  );

   



 
extern __declspec(__nothrow) int puts(const char *  ) __attribute__((__nonnull__(1)));
   





 
extern __declspec(__nothrow) int ungetc(int  , FILE *  ) __attribute__((__nonnull__(2)));
   






















 

extern __declspec(__nothrow) size_t fread(void * __restrict  ,
                    size_t  , size_t  , FILE * __restrict  ) __attribute__((__nonnull__(1,4)));
   











 

extern __declspec(__nothrow) size_t __fread_bytes_avail(void * __restrict  ,
                    size_t  , FILE * __restrict  ) __attribute__((__nonnull__(1,3)));
   











 

extern __declspec(__nothrow) size_t fwrite(const void * __restrict  ,
                    size_t  , size_t  , FILE * __restrict  ) __attribute__((__nonnull__(1,4)));
   







 

extern __declspec(__nothrow) int fgetpos(FILE * __restrict  , fpos_t * __restrict  ) __attribute__((__nonnull__(1,2)));
   








 
extern __declspec(__nothrow) int fseek(FILE *  , long int  , int  ) __attribute__((__nonnull__(1)));
   














 
extern __declspec(__nothrow) int fsetpos(FILE * __restrict  , const fpos_t * __restrict  ) __attribute__((__nonnull__(1,2)));
   










 
extern __declspec(__nothrow) long int ftell(FILE *  ) __attribute__((__nonnull__(1)));
   











 
extern __declspec(__nothrow) void rewind(FILE *  ) __attribute__((__nonnull__(1)));
   





 

extern __declspec(__nothrow) void clearerr(FILE *  ) __attribute__((__nonnull__(1)));
   




 

extern __declspec(__nothrow) int feof(FILE *  ) __attribute__((__nonnull__(1)));
   


 
extern __declspec(__nothrow) int ferror(FILE *  ) __attribute__((__nonnull__(1)));
   


 
extern __declspec(__nothrow) void perror(const char *  );
   









 

extern __declspec(__nothrow) int _fisatty(FILE *   ) __attribute__((__nonnull__(1)));
    
 

extern __declspec(__nothrow) void __use_no_semihosting_swi(void);
extern __declspec(__nothrow) void __use_no_semihosting(void);
    





 











#line 944 "d:\\Keil\\ARM\\RV31\\INC\\stdio.h"



 
#line 13 "Getline.c"
#line 1 "SD_File.h"








 

#line 18 "SD_File.h"

 
typedef struct scmd {
  char val[8];
  void (*func)(char *par);
} SCMD;

 
extern BOOL getline (char *, U32);
extern void init_serial (void);
extern int  getkey (void);



 
#line 14 "Getline.c"



 
BOOL getline (char *lp, U32 n) {
  U32 cnt = 0;
  char c;

  do {
    c = getkey ();
    switch (c) {
      case 0x11:                           
      case 0x13:
        break;;
      case 0x08:
      case 0x7F:
        if (cnt == 0) {
          break;
        }
        cnt--;                              
        lp--;                               
        putc(0x08, (& __stdout));                     
        putc(' ', (& __stdout));
        putc(0x08, (& __stdout));
        fflush ((& __stdout));
        break;
      case 0x1B:
        *lp = 0;                            
        return (0);
      case 0x0D:                              
        *lp = c;
        lp++;                               
        cnt++;                              
        c = 0x0A;
      default:
        putc(*lp = c, (& __stdout));                  
        fflush ((& __stdout));
        lp++;                               
        cnt++;                              
        break;
    }
  } while (cnt < n - 2  &&  c != 0x0A);       
  *lp = 0;                                  
  return (1);
}



 
