/*
*********************************************************************************************************
*                                     MICIRUM BOARD SUPPORT PACKAGE
*
*                          (c) Copyright 2003-2008; Micrium, Inc.; Weston, FL
*
*               All rights reserved.  Protected by international copyright laws.
*               Knowledge of the source code may NOT be used to develop a similar product.
*               Please help us continue to provide the Embedded community with the finest
*               software available.  Your honesty is greatly appreciated.
*********************************************************************************************************
*/


/*
*********************************************************************************************************
**
*                                       MICIUM BOARD SUPPORT PACKAGE
*                                                OS LAYER
*
* Filename      : bsp_os.c
* Version       : V1.00
* Programmer(s) : FT
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                             INCLUDE FILES
*********************************************************************************************************
*/

#define  BSP_OS_MODULE
#include <bsp.h>

/*
*********************************************************************************************************
*                                            LOCAL DEFINES
*********************************************************************************************************
*/

#define  BSP_REG_DEMCR             (*(CPU_REG32 *)0xE000EDFC)
#define  BSP_REG_DWT_CR            (*(CPU_REG32 *)0xE0001000)
#define  BSP_REG_DWT_CYCCNT        (*(CPU_REG32 *)0xE0001004)


/*
*********************************************************************************************************
*                                           LOCAL CONSTANTS
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                          LOCAL DATA TYPES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                            LOCAL TABLES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                       LOCAL GLOBAL VARIABLES
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                      LOCAL FUNCTION PROTOTYPES
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                     LOCAL CONFIGURATION ERRORS
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*********************************************************************************************************
**                                          GLOBAL FUNCTIONS
*********************************************************************************************************
*********************************************************************************************************
*/



/*
*********************************************************************************************************
*********************************************************************************************************
**                                     BSP OS LOCKS FUNCTIONS
*********************************************************************************************************
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                      BSP_OS_SemCreate()
*
* Description : Creates a sempahore.
*
* Argument(s) : p_sem        Pointer to a BSP_OS_SEM structure
*  
*               sem_val      Initial value of the semaphore.  
*
*               p_name       Pointer to an ASCII string with the semaphore name.
*
* Return(s)   : DEF_OK    if the sempahore was created correctly
*               DEF_FAIL  otherwise
*     
* Caller(s)   : Application.
*
* Note(s)     : none.
*
*********************************************************************************************************
*/

CPU_BOOLEAN  BSP_OS_SemCreate (BSP_OS_SEM       *p_sem,
                               BSP_OS_SEM_VAL    sem_val,
                               CPU_CHAR         *p_name)
{
    OS_EVENT    *p_event;
#if (OS_EVENT_NAME_EN > 0)
    CPU_INT08U   os_err;
#endif

    p_event = OSSemCreate(sem_val);

    if (p_event == (OS_EVENT *)0) {
         return (DEF_FAIL);
    }
    
    *p_sem = (BSP_OS_SEM)(p_event);

#if (OS_EVENT_NAME_EN > 0)
    OSEventNameSet((OS_EVENT * )p_event, 
                   (INT8U     *)p_name, 
                   (INT8U     *)&os_err);
    
    if (os_err != OS_ERR_NONE) {
         return (DEF_FAIL);
    }
#endif
    
    return (DEF_OK);    
}


/*
*********************************************************************************************************
*                                     BSP_OS_SemWait()
*
* Description : Wait on a semaphore to become available
*
* Argument(s) : sem          sempahore handler
*  
*               dly_ms       delay in miliseconds to wait on the semaphore
*
*               p_err        Pointer to the error code.
*                                BSP_ERR_NONE            No errors
*                                BSP_ERR_OS_SEM_TIMEOUT  The semaphore was not acquire in the specified timeout
*                                BSP_ERR_OS_SEM_INT      Internal semaphore error.     
*                            
*
* Return(s)   : none.
*               
*     
* Caller(s)   : Application.
*
* Note(s)     : none.
*
*********************************************************************************************************
*/

CPU_BOOLEAN  BSP_OS_SemWait (BSP_OS_SEM  *p_sem,
                             CPU_INT32U   dly_ms)
                    
{
    CPU_INT08U   os_err;
    CPU_INT32U   dly_ticks;
    CPU_BOOLEAN  err;
    
    
    dly_ticks  = ((dly_ms * DEF_TIME_NBR_mS_PER_SEC) / OS_TICKS_PER_SEC);
    
    OSSemPend((OS_EVENT   *)*p_sem,
              (CPU_INT32U  ) dly_ticks,
              (CPU_INT08U *)&os_err);

    switch (os_err) {
        case OS_ERR_NONE:
             err = DEF_OK;
             break;
             
        case OS_ERR_TIMEOUT:
        case OS_ERR_PEND_ABORT:
        case OS_ERR_EVENT_TYPE:
        case OS_ERR_PEND_ISR:
        case OS_ERR_PEVENT_NULL:
        case OS_ERR_PEND_LOCKED:
              err = DEF_FAIL;
              break;

        default:
              err = DEF_FAIL;
              break;
    }
    
    return (err);

}

/*
*********************************************************************************************************
*                                      BSP_OS_SemCreate()
*
* Description : Post a semaphore
*
* Argument(s) : sem          Semaphore handler
*  
*               dly_ms       delay in miliseconds to wait on the semaphore
*
* Return(s)   : error code return     DEF_FALSE     if the semaphore was created.
*                                     DEF_TRUE      if the sempahore could be created.
*     
* Caller(s)   : Application.
*
* Note(s)     : none.
*
*********************************************************************************************************
*/

CPU_BOOLEAN  BSP_OS_SemPost (BSP_OS_SEM  *p_sem)
                      
{
    CPU_INT08U   os_err;
    CPU_BOOLEAN  err;
        
    
    os_err = OSSemPost((OS_EVENT *)*p_sem);

    switch (os_err) {
        case OS_ERR_NONE:
             err = DEF_OK;
             break;
             
        case OS_ERR_SEM_OVF:
        case OS_ERR_EVENT_TYPE:
        case OS_ERR_PEVENT_NULL:
              err = DEF_FAIL;
              break;
    }
    
    return (err);
}



/*
*********************************************************************************************************
*********************************************************************************************************
**                                     uC/OS-II TIMER FUNCTIONS
*********************************************************************************************************
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                      BSP_OS_TmrTickInit()
*
* Description : Initialize uC/OS-II's tick source;
*
* Argument(s) : The tick rate in Hz
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/

void   BSP_OS_TmrTickInit (CPU_INT32U  tick_rate)
{
    CPU_INT32U  cnts;
    CPU_INT32U  cpu_freq;

    
    cpu_freq = BSP_PM_CPU_FreqGet();
    cnts     = (cpu_freq / tick_rate);

    OS_CPU_SysTickInit(cnts);
}


/*
*********************************************************************************************************
*********************************************************************************************************
*                             uC/Probe PLUG-IN FOR uC/OS-II FUNCTIONS
*********************************************************************************************************
*********************************************************************************************************
*/

/*
******************************************************************************************************************************
******************************************************************************************************************************
*                                  uC/Probe Plug-In for uC/OS-II Functions
******************************************************************************************************************************
******************************************************************************************************************************
*/

/*
*********************************************************************************************************
*                                   OSProbe_TmrInit()
*
* Description : This function is called to by uC/Probe Plug-In for uC/OS-II to initialize the
*               free running timer that is used to make time measurements.
*
* Argument(s) : none
*
* Return(s)   : none
*
* Caller(s)   : OSProbe_Init()
*
* Note(s)     : none.
*********************************************************************************************************
*/

#if (APP_CFG_PROBE_OS_PLUGIN_EN == DEF_ENABLED) && \
    (OS_PROBE_HOOKS_EN          == 1)
void  OSProbe_TmrInit (void)
{
    BSP_REG_DEMCR  |= DEF_BIT_24;
    BSP_REG_DWT_CR |= DEF_BIT_00;   
}
#endif


/*
*********************************************************************************************************
*                                        OSProbe_TmrRd()
*
* Description : This function is called to read the current counts of a 32 bit free running timer.
*
* Argument(s) : none
*
* Return(s)   : The 16 or 32 bit count of the timer assuming the timer is an UP counter.
*
* Caller(s)   : OSProbe_TimeGetCycles()
*
* Note(s)     : None.
*********************************************************************************************************
*/

#if (APP_CFG_PROBE_OS_PLUGIN_EN == DEF_ENABLED) && \
    (OS_PROBE_HOOKS_EN          == 1)
CPU_INT32U  OSProbe_TmrRd (void)
{
    return  ((CPU_INT32U)BSP_REG_DWT_CYCCNT);

}
#endif

