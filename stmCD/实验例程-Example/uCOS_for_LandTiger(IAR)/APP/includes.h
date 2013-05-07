/*
*********************************************************************************************************
*                                              uC/OS-II
*                                        The Real-Time Kernel
*
*                          (c) Copyright 2004-2008; Micrium, Inc.; Weston, FL               
*
*               All rights reserved.  Protected by international copyright laws.
*
*               uC/OS-II is provided in source form for FREE evaluation, for educational
*               use or peaceful research.  If you plan on using uC/OS-II in a commercial    
*               product you need to contact Micrium to properly license its use in your     
*               product.  We provide ALL the source code for your convenience and to        
*               help you experience uC/OS-II.  The fact that the source code is provided
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
*                                           MASTER INCLUDES
*
*                                             NXP LPC1768
*                                                on the
*                                     IAR LPC1768-SK Kickstart Kit
*
* Filename      : includes.h
* Version       : V1.00
* Programmer(s) : FT
*********************************************************************************************************
*/

#ifndef  INCLUDES_MODULES_PRESENT
#define  INCLUDES_MODULES_PRESENT

/*
*********************************************************************************************************
*                                         STANDARD LIBRARIES
*********************************************************************************************************
*/

#include  <stdarg.h>
#include  <stdio.h>
#include  <stdlib.h>
#include  <math.h>


/*
*********************************************************************************************************
*                                              LIBRARIES
*********************************************************************************************************
*/

#include  <cpu.h>
#include  <lib_def.h>
#include  <lib_ascii.h>
#include  <lib_math.h>
#include  <lib_mem.h>
#include  <lib_str.h>


/*
*********************************************************************************************************
*                                              APP / BSP
*********************************************************************************************************
*/

#include  <app_cfg.h>
#include  <bsp.h>

#if (APP_CFG_PROBE_COM_EN        == DEF_ENABLED) || \
    (APP_CFG_PROBE_OS_PLUGIN_EN  == DEF_ENABLED)
#include  <app_probe.h>
#endif

#if (APP_CFG_LCD_EN == DEF_ENABLED)
#include   <glcd_ll.h>
#endif


/*
*********************************************************************************************************
*                                                 OS
*********************************************************************************************************
*/

#include  <ucos_ii.h>

/*
*********************************************************************************************************
*                                       IAR REGISTER DEFINITION 
*********************************************************************************************************
*/

#include  <iolpc1768.h>


/*
*********************************************************************************************************
*                                            INCLUDES END
*********************************************************************************************************
*/

#endif
