/*
*********************************************************************************************************
*                                              EXAMPLE CODE
*
*                          (c) Copyright 2003-2009; Micrium, Inc.; Weston, FL
*
*               All rights reserved.  Protected by international copyright laws.
*               Knowledge of the source code may NOT be used to develop a similar product.
*               Please help us continue to provide the Embedded community with the finest
*               software available.  Your honesty is greatly appreciated.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*
*                                           uC/Probe
*                                      Application Code
*
* Filename      : app_probe.c
* Version       : V1.00
* Programmer(s) : FT
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                             INCLUDE FILES
*********************************************************************************************************
*/
#define  APP_PROBE_MODULE
#include <app_probe.h>


/*
*********************************************************************************************************
*                                                 ENABLE
*********************************************************************************************************
*/

#if (APP_CFG_PROBE_COM_EN        == DEF_ENABLED) || \
    (APP_CFG_PROBE_OS_PLUGIN_EN  == DEF_ENABLED)

/*
*********************************************************************************************************
*                                       LOCAL GLOBAL VARIABLES
*********************************************************************************************************
*/

#if (APP_CFG_PROBE_OS_PLUGIN_EN == DEF_ENABLED)
static  CPU_INT32U   App_ProbeCnts;
#endif


/*
*********************************************************************************************************
*                                          FUNCTION PROTOTYPES
*********************************************************************************************************
*/


#if (APP_CFG_PROBE_OS_PLUGIN_EN == DEF_ENABLED)
static  void  App_ProbeCallback          (void);
#endif


/*
*********************************************************************************************************
*                                    LOCAL CONFIGURATION ERRORS
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                         App_ProbeInit()
*
* Description : Initialize all uC/Probe modules.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Note(s)     : none
*********************************************************************************************************
*/


void  App_ProbeInit (void)
{

#if (APP_CFG_PROBE_OS_PLUGIN_EN == DEF_ENABLED)

    OSProbe_Init();
    OSProbe_SetCallback(App_ProbeCallback);
    OSProbe_SetDelay(50);
#endif

#if (APP_CFG_PROBE_COM_EN == DEF_ENABLED)
    APP_TRACE_INFO(("Initializing uC/Probe ... \n\r"));    
    ProbeCom_Init();                                            /* Initialize the uC/Probe communications module            */

#if (PROBE_COM_CFG_RS232_EN == DEF_ENABLED)
    ProbeRS232_Init(115200);
    ProbeRS232_RxIntEn();
#endif

#if (PROBE_COM_CFG_TCPIP_EN == DEF_ENABLED)
    ProbeTCPIP_Init();
#endif    
#endif
    
#if (APP_CFG_PROBE_DEMO_INTRO_EN == DEF_ENABLED)
    ProbeDemoIntro_Init();
#endif    
}


/*
*********************************************************************************************************
*                                         AppProbeCallback()
*
* Description : This function is called by the uC/Probe uC/OS-II plug-in after updating task information.
*
* Argument(s) : none.
*
* Return(s)   : none.
*********************************************************************************************************
*/

#if (APP_CFG_PROBE_OS_PLUGIN_EN == DEF_ENABLED)
static  void  App_ProbeCallback (void)
{
    App_ProbeCnts++;    
}
#endif



#endif