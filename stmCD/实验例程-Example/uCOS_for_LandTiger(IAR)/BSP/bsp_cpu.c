/*
*********************************************************************************************************
*                                               uC/CPU
*                                    CPU CONFIGURATION & PORT LAYER
*
*                          (c) Copyright 2004-2009; Micrium, Inc.; Weston, FL
*
*               All rights reserved.  Protected by international copyright laws.
*
*               uC/CPU is provided in source form for FREE evaluation, for educational
*               use or peaceful research.  If you plan on using uC/CPU in a commercial
*               product you need to contact Micrium to properly license its use in your
*               product.  We provide ALL the source code for your convenience and to
*               help you experience uC/CPU.  The fact that the source code is provided
*               does NOT mean that you can use it without paying a licensing fee.
*
*               Knowledge of the source code may NOT be used to develop a similar product.
*
*               Please help us continue to provide the Embedded community with the finest
*               software available.  Your honesty is greatly appreciated.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*
*                               CPU BOARD SUPPORT PACKAGE (BSP) FUNCTIONS
*
*                            NXP LPC1768 ON THE IAR LPC1768-SK KICKSTART KIT
*
* Filename      : cpu_bsp.c
* Version       : V1.23
* Programmer(s) : ITJ
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/

#define    CPU_BSP_MODULE
#include  <cpu_core.h>
#include  <bsp.h>


/*$PAGE*/
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


/*$PAGE*/
/*
*********************************************************************************************************
*                                          CPU_TS_TmrInit()
*
* Description : Initialize & start CPU timestamp timer.
*
* Argument(s) : none.
*
* Return(s)   : Number of left-shifts to scale & return timer as (32-bit) 'CPU_TS' data type
*                 (see Note #2a1), if necessary.
*
*               0 (see Note #2a2), otherwise.
*
* Caller(s)   : CPU_TS_Init().
*
*               This function is an INTERNAL CPU module function & MUST be implemented by application/
*               BSP function(s) [see Note #1] but MUST NOT be called by application function(s).
*
* Note(s)     : (1) CPU_TS_TmrInit() is an application/BSP function that MUST be defined by the developer
*                   if either of the following CPU features is enabled :
*
*                   (a) CPU timestamps
*                   (b) CPU interrupts disabled time measurements
*
*                   See 'cpu_cfg.h  CPU TIMESTAMP CONFIGURATION  Note #1'
*                     & 'cpu_cfg.h  CPU INTERRUPTS DISABLED TIME MEASUREMENT CONFIGURATION  Note #1a'.
*
*               (2) (a) Timer count values MUST be scaled & returned via (32-bit) 'CPU_TS' data type.
*
*                       (1) If timer has less bits, left-shift timer values until the most
*                           significant bit of the timer value is shifted into    the most
*                           significant bit of the return timestamp data type.
*                       (2) If timer has more bits, truncate   timer values' higher-order
*                           bits greater than  the return timestamp data type.
*
*                   (b) Timer SHOULD be an 'up'  counter whose values increase with each time count.
*
*                   (c) When applicable, timer period SHOULD be less than the typical measured time
*                       but MUST be less than the maximum measured time; otherwise, timer resolution
*                       inadequate to measure desired times.
*
*                   See also 'CPU_TS_TmrRd()  Note #2'.
*********************************************************************************************************
*/

#if (CPU_CFG_TS_TMR_EN == DEF_ENABLED)
CPU_INT16U  CPU_TS_TmrInit (void)
{
    CPU_INT16U  nbr_shifts;

    BSP_REG_DEMCR  |= DEF_BIT_24;
    BSP_REG_DWT_CR |= DEF_BIT_00;

    nbr_shifts = 0u;
    return (nbr_shifts);
}
#endif


/*$PAGE*/
/*
*********************************************************************************************************
*                                           CPU_TS_TmrRd()
*
* Description : Get current CPU timestamp timer count value.
*
* Argument(s) : none.
*
* Return(s)   : (32-bit) Timestamp timer count (see Notes #2a & #2b).
*
* Caller(s)   : CPU_TS_Init(),
*               CPU_TS_UpdateHandler(),
*               CPU_IntDisMeasStart(),
*               CPU_IntDisMeasStop().
*
*               This function is an INTERNAL CPU module function & MUST be implemented by application/
*               BSP function(s) [see Note #1] but SHOULD NOT be called by application function(s).
*
* Note(s)     : (1) CPU_TS_TmrRd() is an application/BSP function that MUST be defined by the developer
*                   if either of the following CPU features is enabled :
*
*                   (a) CPU timestamps
*                   (b) CPU interrupts disabled time measurements
*
*                   See 'cpu_cfg.h  CPU TIMESTAMP CONFIGURATION  Note #1'
*                     & 'cpu_cfg.h  CPU INTERRUPTS DISABLED TIME MEASUREMENT CONFIGURATION  Note #1a'.
*
*               (2) (a) Timer count values MUST be returned via (32-bit) 'CPU_TS' data type.
*
*                       (1) If timer has less bits, left-shift timer values until the most
*                           significant bit of the timer value is shifted into    the most
*                           significant bit of the return timestamp data type.
*                       (2) If timer has more bits, truncate   timer values' higher-order
*                           bits greater than  the return timestamp data type.
*
*                   (b) Timer SHOULD be an 'up'  counter whose values increase with each time count.
*
*                       (1) If timer is a 'down' counter whose values decrease with each time count,
*                           then the returned timer value MUST be ones-complemented.
*
*                   (c) (1) When applicable, the amount of time measured by CPU timestamps is
*                           calculated by either of the following equations :
*
*                           (A) Time measured  =  Number timer counts  *  Timer period
*
*                                   where
*
*                                       Number timer counts     Number of timer counts measured
*                                       Timer period            Timer's period in some units of
*                                                                   (fractional) seconds
*                                       Time measured           Amount of time measured, in same
*                                                                   units of (fractional) seconds
*                                                                   as the Timer period
*
*                                                  Number timer counts
*                           (B) Time measured  =  ---------------------
*                                                    Timer frequency
*
*                                   where
*
*                                       Number timer counts     Number of timer counts measured
*                                       Timer frequency         Timer's frequency in some units
*                                                                   of counts per second
*                                       Time measured           Amount of time measured, in seconds
*
*                       (2) Timer period SHOULD be less than the typical measured time but MUST be less
*                           than the maximum measured time; otherwise, timer resolution inadequate to
*                           measure desired times.
*********************************************************************************************************
*/

#if (CPU_CFG_TS_TMR_EN == DEF_ENABLED)
CPU_TS  CPU_TS_TmrRd (void)
{
    CPU_TS  time_meas_cnts;


    time_meas_cnts = (CPU_TS)BSP_REG_DWT_CYCCNT;

    return (time_meas_cnts);
}
#endif


/*$PAGE*/
/*
*********************************************************************************************************
*                                          CPU_TS_to_uSec()
*
* Description : Convert a CPU timestamp from timer counts to microseconds.
*
* Argument(s) : ts_lo_cnts      CPU timestamp lower half (in timestamp timer counts [see Note #2aA]).
*
*               ts_hi_cnts      CPU timestamp upper half (in timestamp timer counts [see Note #2aA]).
*
*               p_ts_lo_usec    Pointer to variable that will receive the converted CPU timestamp's
*                                   lower half [in microseconds (see Note #2aD)], if available.
*
*               p_ts_hi_usec    Pointer to variable that will receive the converted CPU timestamp's
*                                   upper half [in microseconds (see Note #2aD)], if available.
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
*               This function is an (optional) CPU module application interface (API) function which
*               MAY be implemented by application/BSP function(s) [see Note #1] & MAY be called by
*               application function(s).
*
* Note(s)     : (1) CPU_TS_to_uSec() is an application/BSP function that MAY be optionally defined by
*                   the developer when either of the following CPU features is enabled :
*
*                   (a) CPU timestamps
*                   (b) CPU interrupts disabled time measurements
*
*                   See 'cpu_cfg.h  CPU TIMESTAMP CONFIGURATION  Note #1'
*                     & 'cpu_cfg.h  CPU INTERRUPTS DISABLED TIME MEASUREMENT CONFIGURATION  Note #1a'.
*
*               (2) (a) The amount of time measured by CPU timestamps is calculated by either of
*                       the following equations :
*
*                                                                        10^6 microseconds
*                       (1) Time measured  =   Number timer counts   *  -------------------  *  Timer period
*                                                                            1 second
*
*                                              Number timer counts       10^6 microseconds
*                       (2) Time measured  =  ---------------------  *  -------------------
*                                                Timer frequency             1 second
*
*                               where
*
*                                   (A) Number timer counts     Number of timer counts measured
*                                   (B) Timer frequency         Timer's frequency in some units
*                                                                   of counts per second
*                                   (C) Timer period            Timer's period in some units of
*                                                                   (fractional)  seconds
*                                   (D) Time measured           Amount of time measured,
*                                                                   in microseconds
*
*                   (b) Timer period SHOULD be less than the typical measured time but MUST be less
*                       than the maximum measured time; otherwise, timer resolution inadequate to
*                       measure desired times.
*
*                   (c) Specific implementations may convert any number of CPU timestamps bits, up
*                       to 64, into microseconds.
*********************************************************************************************************
*/

#if (CPU_CFG_TS_TMR_EN == DEF_ENABLED)
void  CPU_TS_to_uSec(CPU_TS       ts_lo_cnts,
                     CPU_TS       ts_hi_cnts,
                     CPU_INT32U  *p_ts_lo_usec,
                     CPU_INT32U  *p_ts_hi_usec)
{

}
#endif

