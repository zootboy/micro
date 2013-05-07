/*
*********************************************************************************************************
*                                     MICIRUM BOARD SUPPORT PACKAGE
*
*                            (c) Copyright 2006-2009; Micrium, Inc.; Weston, FL
*
*                   All rights reserved.  Protected by international copyright laws.
*                   Knowledge of the source code may not be used to write a similar
*                   product.  This file may only be used in accordance with a license
*                   and should not be redistributed in any way.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*
*                                         BOARD SUPPORT PACKAGE
*                                          (SYSTEM CONTROLLER)
*
* Filename      : bsp_sys_ctrl.c
* Version       : V1.00
* Programmer(s) : FT
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                             INCLUDE FILES
*********************************************************************************************************
*/

#define  BSP_PM_MODULE
#include <bsp.h>

/*
*********************************************************************************************************
*                                            LOCAL DEFINES
*********************************************************************************************************
*/
                                                                /* --------- REGISTER BASE ADDRESS DEFINES ---------- */
#define  BSP_REG_PLL_BASE_ADDR                   (CPU_INT32U )0x400FC080
  
#define  BSP_REG_PLLCTRL                         (*(CPU_REG32 *)(BSP_REG_PLL_BASE_ADDR  + 0x00))
#define  BSP_REG_PLLCFG                          (*(CPU_REG32 *)(BSP_REG_PLL_BASE_ADDR  + 0x04))
#define  BSP_REG_PLLSTAT                         (*(CPU_REG32 *)(BSP_REG_PLL_BASE_ADDR  + 0x08))
#define  BSP_REG_PLLFEED                         (*(CPU_REG32 *)(BSP_REG_PLL_BASE_ADDR  + 0x0C))

                                                                /* --------- POWER CONTROL REGISTER DEFINES --------- */
#define  BSP_REG_PCON                            (*(CPU_REG32 *)(0x400FC0C0))
#define  BSP_REG_PCONP                           (*(CPU_REG32 *)(0x400FC0C4))

                                                                /* ------- CLOCK SOURCE SELECT REGISTER DEFINE ------ */
#define  BSP_REG_PCLKSRCSEL                      (*(CPU_REG32 *)(0x400FC10C))

                                                                /* --------- PLL STATUS REGISTER BIT DEFINES -------- */
#define  BSP_BIT_PLLSTAT_MSEL_MASK               DEF_BIT_FIELD(15,  0)
#define  BSP_BIT_PLLSTAT_PSEL_MASK               DEF_BIT_FIELD(8 , 16)
#define  BSP_BIT_PLLSTAT_PLLE                    DEF_BIT_24     /* Read-back for the PLL enable bit                     */
#define  BSP_BIT_PLLSTAT_PLLC                    DEF_BIT_25     /* Read-back for the PLL connect bit                    */
#define  BSP_BIT_PLLSTAT_PLOCK                   DEF_BIT_26     /* Refkect the PLL lock status                          */

                                                                /* -------- CLOCK DIVIDERS REGISTER DEFINITION ------ */
#define  BSP_REG_CCLKCFG                         (*(CPU_REG32 *)(0x400FC104))
#define  BSP_REG_USBCLKCFG                       (*(CPU_REG32 *)(0x400FC108))
#define  BSP_REG_IRCTRIM                         (*(CPU_REG32 *)(0x400FC1A4))
#define  BSP_REG_PCLKSEL0                        (*(CPU_REG32 *)(0x400FC1A8))
#define  BSP_REG_PCLKSEL1                        (*(CPU_REG32 *)(0x400FC1AC))

                                                                /* ---------- APB DIVIDER REGISTER BIT DEFINES ------ */
#define  BSP_BIT_APBDIV_MASK                     DEF_BIT_FIELD(2, 0)
#define  BSP_BIT_APBDIV_4                        DEF_BIT_NONE
#define  BSP_BIT_APBDIV_1                        DEF_BIT_MASK(1, 0)
#define  BSP_BIT_APBDIV_2                        DEF_BIT_MASK(2, 0)


/*
*********************************************************************************************************
*                                       EXTERN  GLOBAL VARIABLES
*********************************************************************************************************
*/


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
*********************************************************************************************************
**                                        GLOBAL FUNCTIONS
*********************************************************************************************************
*********************************************************************************************************
*/



/*
*********************************************************************************************************
*                                              BSP_SysCtrl_CPU_FreqGet ()
*
* Description : This function return the CPU clk frequency
*
* Argument(s) : none.
*
* Return(s)   : The CPU clk frequency
*
* Caller(s)   : Application.
*
* Note(s)     : None.                
*********************************************************************************************************
*/

CPU_INT32U  BSP_PM_CPU_FreqGet (void)
{
    CPU_INT32U  cpu_freq;
    CPU_INT08U  cpu_div;
    CPU_INT16U  pll_mul;
    CPU_INT08U  pll_div;
    CPU_INT32U  reg_val;


    reg_val = BSP_REG_PCLKSRCSEL & DEF_BIT_FIELD(2, 0);
 
    switch(reg_val) {
        case 0x00:
             cpu_freq = BSP_PM_OSC_INT_RC_FREQ_HZ;
             break;
    
        case 0x01:
             cpu_freq = BSP_PM_OSC_MAIN_OSC_FREQ_HZ;
             break;

        case 0x02:
             cpu_freq = BSP_PM_OSC_RTC_FREQ_HZ;
             break;
                  
        default:
             return (0);
    }
 
    pll_mul =   ((BSP_REG_PLLSTAT & BSP_BIT_PLLSTAT_MSEL_MASK)         + 1);
    pll_div = ((((BSP_REG_PLLSTAT & BSP_BIT_PLLSTAT_PSEL_MASK)) >> 16) + 1);

    if (DEF_BIT_IS_SET(BSP_REG_PLLSTAT, (BSP_BIT_PLLSTAT_PLLE | 
                                         BSP_BIT_PLLSTAT_PLLC |
                                         BSP_BIT_PLLSTAT_PLOCK ))) {
        cpu_freq = ((cpu_freq * 2 * pll_mul) / pll_div);
    }
        
    cpu_div = BSP_REG_CCLKCFG & DEF_BIT_FIELD(8, 0); 
    cpu_div++;
    
    if (cpu_div != 0) {
        cpu_freq /= cpu_div;
    }
    
    return (cpu_freq);
}


/*
*********************************************************************************************************
*                                             BSP_PM_PerClkDis()
*
* Description : Disable peripheral clock.
*
* Argument(s) : per_nbr    The peripheral identifier number (defined in 'bsp_pmc.h')
*
* Return(s)   : none.
*              
* Caller(s)   : Application.
*
* Note(s)     : None.                
*********************************************************************************************************
*/

void  BSP_PM_PerClkDis (CPU_INT08U  per_nbr)
{
    switch (per_nbr) {
        case BSP_PM_PER_NBR_RESERVED0:
        case BSP_PM_PER_NBR_RESERVED1:
        case BSP_PM_PER_NBR_RESERVED2:
        case BSP_PM_PER_NBR_RESERVED3:
        case BSP_PM_PER_NBR_RESERVED4:
             return ;
    
        default:
             break;
    }
    
    DEF_BIT_CLR(BSP_REG_PCONP, DEF_BIT(per_nbr));
}


/*
*********************************************************************************************************
*                                             BSP_PM_PerClkEn()
*
* Description : Enable a peripheral clock.
*
* Argument(s) : per_nbr    The peripheral identifier number (defined in 'bsp_pmc.h')
*
* Return(s)   : none.              
*
* Caller(s)   : Application.
*
* Note(s)     : None.                
*********************************************************************************************************
*/

void  BSP_PM_PerClkEn (CPU_INT08U  per_nbr)
{
    switch (per_nbr) {
        case BSP_PM_PER_NBR_RESERVED0:
        case BSP_PM_PER_NBR_RESERVED1:
        case BSP_PM_PER_NBR_RESERVED2:
        case BSP_PM_PER_NBR_RESERVED3:
        case BSP_PM_PER_NBR_RESERVED4:
             return;
    
        default:
             break;
    }
    
    DEF_BIT_SET(BSP_REG_PCONP, DEF_BIT(per_nbr));
}


/*
*********************************************************************************************************
*                                           BSP_PM_PerClkFreqGet()
*
* Description : Get the peripheral clock frequency
*
* Argument(s) : per_nbr    The peripheral identifier number (defined in 'bsp_pmc.h')
*
* Return(s)   : The peripheral clock frequency.
*
* Caller(s)   : Application.
*
* Note(s)     : none.               
*********************************************************************************************************
*/

CPU_INT32U  BSP_PM_PerClkFreqGet  (CPU_INT08U  per_nbr)
                                        
{
    CPU_INT32U  per_clk_freq;
    CPU_INT32U  per_clk_div;
    CPU_INT32U  reg_val;
    
                                                                /* ----------------- ARGUMENTS CHECKING ------------- */
    switch (per_nbr) {
        case BSP_PM_PER_NBR_PCLKSEL_RESERVED0:
        case BSP_PM_PER_NBR_PCLKSEL_RESERVED1:
        case BSP_PM_PER_NBR_PCLKSEL_RESERVED2:        
             return (DEF_FAIL);
    
        default:
             break;
    }
    
    if (per_nbr < BSP_PM_PER_NBR_RIT) {
        reg_val = (BSP_REG_PCLKSEL0 >> ((per_nbr      ) * 2u)) & DEF_BIT_FIELD(2, 0);
    } else {
        reg_val = (BSP_REG_PCLKSEL1 >> ((per_nbr - 16u) * 2u)) & DEF_BIT_FIELD(2, 0);
    }
    
    switch (reg_val) {
        case 0x01:            
             per_clk_div = 1u;
             break;
             
        case 0x02:
             per_clk_div = 2u;
             break;
             
        case 0x00:            
             per_clk_div = 4u;
             break;

        case 0x03:            
             if ((per_nbr == BSP_PM_PER_NBR_CAN1       ) ||
                 (per_nbr == BSP_PM_PER_NBR_CAN2       ) ||
                 (per_nbr == BSP_PM_PER_NBR_PCLKSEL_ACF)) {
                 per_clk_div = 6u;
             } else {
                 per_clk_div = 8u;
             }
             break;

        default:
             break;
    }
    
    per_clk_freq  = BSP_PM_CPU_FreqGet();
    per_clk_freq /= per_clk_div;
    
    return (per_clk_freq);
}


