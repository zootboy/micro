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
*                                       BOARD SUPPORT PACKAGE (BSP)
*
*                                         NXP LPC1766 (Cortex-M3)
*                                                on the
*
*                                            IAR LPC1766-SK 
*                                             Kickstart Kit
*
* Filename      :bsp.c
* Version       :V1.00
* Programmer(s) :FT
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                             INCLUDE FILES
*********************************************************************************************************
*/

#define  BSP_MODULE
#include <bsp.h>


/*
*********************************************************************************************************
*                                             REGISTER & BIT DEFINES
*********************************************************************************************************
*/

                                                                /* SYSTEM CONTROL AND STATUS REGISTER & BIT DEFINES */
#define  BSP_REG_SCS                             (*(CPU_REG32 *)(0x400FC1A0))
#define  BSP_BIT_SCS_OSCRANGE                    DEF_BIT_04
#define  BSP_BIT_SCS_OSCEN                       DEF_BIT_05
#define  BSP_BIT_SCS_OSCSTAT                     DEF_BIT_06

                                                                /* ----- CLOCK DIVIDERS REGISTER & BIT DEFINES ----- */
#define  BSP_REG_CCLKCFG                         (*(CPU_REG32 *)(0x400FC104))
#define  BSP_REG_CLKSRCSEL                       (*(CPU_REG32 *)(0x400FC10C))
#define  BSP_REG_PCLKSEL0                        (*(CPU_REG32 *)(0x400FC1A8))
#define  BSP_REG_PCLKSEL1                        (*(CPU_REG32 *)(0x400FC1AC))


                                                                /* ---------- PLL REGISTER & BIT DEFINES ------------ */
#define  BSP_REG_PLL_BASE_ADDR                   (CPU_INT32U )0x400FC080

#define  BSP_REG_PLLCTRL(pll_id)                 (*(CPU_REG32 *)(BSP_REG_PLL_BASE_ADDR + (0x20 * pll_id) + 0x00))
#define  BSP_REG_PLLCFG(pll_id)                  (*(CPU_REG32 *)(BSP_REG_PLL_BASE_ADDR + (0x20 * pll_id) + 0x04))
#define  BSP_REG_PLLSTAT(pll_id)                 (*(CPU_REG32 *)(BSP_REG_PLL_BASE_ADDR + (0x20 * pll_id) + 0x08))
#define  BSP_REG_PLLFEED(pll_id)                 (*(CPU_REG32 *)(BSP_REG_PLL_BASE_ADDR + (0x20 * pll_id) + 0x0C))

#define  BSP_BIT_PLLCTRL_PLLE                    DEF_BIT_00     /* PLL enable                                           */
#define  BSP_BIT_PLLCTRL_PLLC                    DEF_BIT_01     /* PLL connect                                          */

#define  BSP_BIT_PLLSTAT_PLLE0_STAT              DEF_BIT_24     /* Read-back for the PLL enable bit                     */
#define  BSP_BIT_PLLSTAT_PLLC0_STAT              DEF_BIT_25     /* Read-back for the PLL connect bit                    */
#define  BSP_BIT_PLLSTAT_PLOCK0                  DEF_BIT_26     /* Refkect the PLL lock status                          */

#define  BSP_BIT_PLLSTAT_PLLE1_STAT              DEF_BIT_08     /* Read-back for the PLL enable bit                     */
#define  BSP_BIT_PLLSTAT_PLLC1_STAT              DEF_BIT_09     /* Read-back for the PLL connect bit                    */
#define  BSP_BIT_PLLSTAT_PLOCK1                  DEF_BIT_10     /* Refkect the PLL lock status                          */

#define  BSP_BIT_PLLFEED_VAL0                   (CPU_INT32U)(0x000000AA)
#define  BSP_BIT_PLLFEED_VAL1                   (CPU_INT32U)(0x00000055)

                                                                /* --- FLASH ACCELERATOR CFG REGISTER & BIT DEFINES --- */
#define  BSP_REG_FLASHCFG                        (*(CPU_REG32 *)(0x400FC000))      

#define  BSP_REG_FLASHCFG_CLK_1                  DEF_BIT_MASK(1, 12)
#define  BSP_REG_FLASHCFG_CLK_2                  DEF_BIT_MASK(2, 12)
#define  BSP_REG_FLASHCFG_CLK_3                  DEF_BIT_MASK(3, 12)
#define  BSP_REG_FLASHCFG_CLK_4                  DEF_BIT_MASK(4, 12)
#define  BSP_REG_FLASHCFG_CLK_5                  DEF_BIT_MASK(5, 12)
#define  BSP_REG_FLASHCFG_CLK_6                  DEF_BIT_MASK(6, 12)


/*
*********************************************************************************************************
*                                             GPIO DEFINES
*********************************************************************************************************
*/
                                                              /* ----------------- GPIO PIN DEFINITION ------------- */
//#define  BSP_GPIO0_BUT1                          DEF_BIT_23    /* P0.23 Push Button 1                                 */
//#define  BSP_GPIO0_JOY_CENTER                    DEF_BIT_05    /* P0.5  Joystick Center  switch contact               */
//#define  BSP_GPIO0_LED2                          DEF_BIT_04    /* P0.4  LED1                                          */

//#define  BSP_GPIO1_LED1                          DEF_BIT_25    /* P1.25 LED1                                          */

//#define  BSP_GPIO2_JOY_UP                        DEF_BIT_00    /* P2.0  Joystick Up      switch contact               */
//#define  BSP_GPIO2_JOY_DOWN                      DEF_BIT_01    /* P2.1  Joystick Down    switch contact               */
//#define  BSP_GPIO2_JOY_LEFT                      DEF_BIT_07    /* P2.7  Joystick Left    switch contact               */
//#define  BSP_GPIO2_JOY_RIGHT                     DEF_BIT_08    /* P2.8  Joystick Right   switch contact               */

//#define  BSP_GPIO2_BUT2                          DEF_BIT_13    /* P2.13 Push Button 2                                 */
#define  BSP_GPIO2_BUT1                          DEF_BIT_11    /* P2.11 Push Button 1                                 */
#define  BSP_GPIO1_JOY_CENTER                    DEF_BIT_25    /* P1.25  Joystick Center  switch contact               */
#define  BSP_GPIO2_LED2                          DEF_BIT_01    /* P2.01  LED2                                          */

#define  BSP_GPIO2_LED1                          DEF_BIT_00    /* P2.00 LED1                                          */

#define  BSP_GPIO1_JOY_UP                        DEF_BIT_29    /* P1.29  Joystick Up      switch contact               */
#define  BSP_GPIO1_JOY_DOWN                      DEF_BIT_26    /* P1.26  Joystick Down    switch contact               */
#define  BSP_GPIO1_JOY_LEFT                      DEF_BIT_27    /* P1.27  Joystick Left    switch contact               */
#define  BSP_GPIO1_JOY_RIGHT                     DEF_BIT_28    /* P1.28  Joystick Right   switch contact               */

#define  BSP_GPIO2_BUT2                          DEF_BIT_22    /* P2.22 Push Button 2                                 */

/*
*********************************************************************************************************
*                                             BSP CONSTANS VALUES
*********************************************************************************************************
*/
                                                               /* Maximum register timeout                            */
#define  BSP_VAL_MAX_TO                         (CPU_INT16U)(0xFFFF)


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

typedef  struct bsp_tmr_reg {
    CPU_REG32  IR;
    CPU_REG32  TCR;
    CPU_REG32  TC;
    CPU_REG32  PR;
    CPU_REG32  PC;
    CPU_REG32  MCR;
    CPU_REG32  MR[4];
    CPU_REG32  CCR;
    CPU_REG32  CR[4];
    CPU_REG32  EMR;
} BSP_TMR_REG, *BSP_TMR_REG_PTR;

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
*                                               MACRO'S
*********************************************************************************************************
*/

#define  BSP_PLL_FEED_SEQ(pll_nbr)              {    CPU_CRITICAL_ENTER();                             \
                                                                                                       \
                                                     BSP_REG_PLLFEED(pll_nbr) = BSP_BIT_PLLFEED_VAL0;  \
                                                     BSP_REG_PLLFEED(pll_nbr) = BSP_BIT_PLLFEED_VAL1;  \
                                                                                                       \
                                                     CPU_CRITICAL_EXIT();                              \
                                                }


/*
*********************************************************************************************************
*                                      LOCAL FUNCTION PROTOTYPES
*********************************************************************************************************
*/

static  CPU_BOOLEAN  BSP_CPU_Init  (void); 

static  void         BSP_Joy_Init  (void);

static  void         BSP_LED_Init  (void);

static  void         BSP_PB_Init   (void);


/*
*********************************************************************************************************
*                                     LOCAL CONFIGURATION ERRORS
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*********************************************************************************************************
**                                         GLOBAL FUNCTIONS
*********************************************************************************************************
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                             BSP_Init()
*
* Description : Initialize the Board Support Package (BSP).
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : (1) This function SHOULD be called before any other BSP function is called.
*********************************************************************************************************
*/

void  BSP_Init (void)
{
    BSP_CPU_Init();                                             /* Initialize the CPU's clocks                        */
           
    BSP_LED_Init();                                             /* Initialize LEDs I/O                                */
     
    BSP_PB_Init();                                              /* Initialize PB I/O                                  */
                
    BSP_Joy_Init();                                             /* Initialize PB I/O                                  */

    BSP_IntInit();                                              /* Initialize the Interrupt controller                */
}


/*
*********************************************************************************************************
*                                            BSP_CPU_ClkFreq()
*
* Description : Get the CPU clock frequency.
*
* Argument(s) : none.
*
* Return(s)   : The CPU clock frequency, in Hz.
*
* Caller(S)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/

CPU_INT32U  BSP_CPU_ClkFreq (void)
{
    CPU_INT32U  cpu_freq;

    
    cpu_freq = (BSP_PM_CPU_FreqGet());

    return (cpu_freq);
}


/*
*********************************************************************************************************
*                                             BSP_CPU_Init()
*
* Description : Initialize the CPU clks, memory map, etc.
*               (1) Initialize the main oscillator.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : BSP_Init()
*
* Note(s)     : (1) The PLL0 Frequency is determined by:
*
*                       Fcco = (2 x M x Fin) / N
*
*                       where M   = PLL0 Multipler
*                             N   = PLL0 Pre-dividier
*                            Fin  = PLL0 Input Frequency (Main oscillator).
*                                     
*               (2) PLL0 settings must meet the following:
*                       Fin is in the range of 32Khz to 50 Mhz.
*                       Fcco is in the range of 275 Mhz to 550 Mhz
*
*               (3) The LPC17xx CPU frequency is determined by:
*
*                       CPU_freq = Fcc0 / CPU_Div                            
*
*               (4) The USB clock frequency is determined by:
*
*                       USB_Clk = M x Fosc x P, or USB_clk = Fcco / (2 x P)
*
*                       Fcco    =  Fosc x 2 x M x 2 x P
*
*                       where Fcco = PLL1 output frequency.
*                             M    = PLL1 multiplier.
*                             P    = PLL1 pre-divider.
*                             Fosc = Oscialltor  frequency.
* 
*               (5) The PLL1 inputs and settings must meet the following criteria:
*                   Fosc    is in the range of 10 Mhz to 25 Mhz.
*                   USBClk  is 48 Mhz
*                   Fcco    is in the range of 156 Mhz to 320 Mhz
*
*               (6) In this example the LPC1768 operates:
*
*                       PLL0_Fcco = 2 x 25 x 12 / 2
*                       PLL0_Fcco = 300mhz
*
*                       CPU_freq  =  300 Mhz  / 3 
*                                 =  100 Mhz
*
*                       PLL1_Fcc0 = 12 x 4 x 2 x 2
*                       USB_Clk   = 48 Mhz
*********************************************************************************************************
*/

static  CPU_BOOLEAN  BSP_CPU_Init (void)
{
    CPU_INT16U    reg_to;
    CPU_INT32U    reg_val;
    CPU_SR_ALLOC();
        
                                                                /* ----------- MAIN OSCILLATOR INITIALIZATION --------- */
    DEF_BIT_SET(BSP_REG_SCS, BSP_BIT_SCS_OSCRANGE);             /* Set the main oscillator range                        */
    
    
    reg_to = BSP_VAL_MAX_TO;
    
    DEF_BIT_SET(BSP_REG_SCS, BSP_BIT_SCS_OSCEN);                /* Enable the Main Oscillator                           */
    
                                                                /* Wait until the main oscillator is enabled.           */    
    while (DEF_BIT_IS_CLR(BSP_REG_SCS, BSP_BIT_SCS_OSCSTAT) &&
          (reg_to > 0)) {
        reg_to--;
    }
    
    if (reg_to == 0) {                                          /* Configuration fail                                   */
        return (DEF_FAIL);
    }
    
    BSP_REG_FLASHCFG = BSP_REG_FLASHCFG_CLK_5;                  /* Set 5 cycles to acces the Flash memory               */            
        
                                                                /* ------------------ PLL0 CONFIGURATION -------------- */

    reg_val  = ((25u - 1u) <<  0) & DEF_BIT_FIELD(15,  0)       /* PLL0 values M = 25 & N = 2 (see note #6)             */ 
             | (( 2u - 1u) << 16) & DEF_BIT_FIELD( 8, 16);    
                                                                /* 1. Disconnect PLL0 with one feed sequence if PLL ... */
                                                                /* ... already connected.                               */
    if (DEF_BIT_IS_SET(BSP_REG_PLLSTAT(0), BSP_BIT_PLLSTAT_PLLC0_STAT)) {        
        DEF_BIT_CLR(BSP_REG_PLLCTRL(0), BSP_BIT_PLLCTRL_PLLC);   
        BSP_PLL_FEED_SEQ(0);        
    }
    
    DEF_BIT_CLR(BSP_REG_PLLCTRL(0), BSP_BIT_PLLCTRL_PLLE);      /* 2. Disable PLL0 with one feed sequence               */
    BSP_PLL_FEED_SEQ(0);        
    
    BSP_REG_CCLKCFG   = (1u - 1u);                              /* 3. Change the CPU clock divider setting to speed ... */
                                                                /* ... operation without PLL0                           */

    BSP_REG_CLKSRCSEL = 0x01;                                   /* 4. Select the main osc. as the PLL0 clock source     */
    
    BSP_REG_PLLCFG(0) = reg_val;                                /* 5. Write to the PLLCFG and make it effective with... */
    BSP_PLL_FEED_SEQ(0);                                        /* ... one one feed sequence                            */
    
    DEF_BIT_SET(BSP_REG_PLLCTRL(0), BSP_BIT_PLLCTRL_PLLE);      /* 6. Enable PLL0 with one feed sequence                */
    BSP_PLL_FEED_SEQ(0);                                        

    BSP_REG_CCLKCFG   = (3u - 1u);                              /* 7. Change the CPU clock divider setting for ...      */
                                                                /* ... operation with PLL0                              */

    reg_to = BSP_VAL_MAX_TO;                                    /* 8. Wait for PLL0 to achieve lock by monitoring ...   */
                                                                /* ... the PLOCK0 bit in the PLL0STAT                   */
    while (DEF_BIT_IS_CLR(BSP_REG_PLLSTAT(0), BSP_BIT_PLLSTAT_PLOCK0) &&
          (reg_to > 0)) {
        reg_to--;
    }
           
    if (reg_to == 0) {
        return (DEF_FAIL);        
    }

    DEF_BIT_SET(BSP_REG_PLLCTRL(0), BSP_BIT_PLLCTRL_PLLC);      /* 9. Connect PLL0 with one feed sequence               */
    BSP_PLL_FEED_SEQ(0);                                            
                                                                /* ------------------ PLL1 CONFIGURATION -------------- */
    reg_val  = ((4u - 1u) <<  0) & DEF_BIT_FIELD(4, 0)          /* PLL1 values M = 4; P = 2 coded as '01' (see note #6) */ 
             | ((0x01   ) <<  5) & DEF_BIT_FIELD(2, 5);    

    DEF_BIT_CLR(BSP_REG_PLLCTRL(1), BSP_BIT_PLLCTRL_PLLC);      /* 1. Disconnect PLL1 with one feed sequence            */
    BSP_PLL_FEED_SEQ(1);        

    DEF_BIT_CLR(BSP_REG_PLLCTRL(1), BSP_BIT_PLLCTRL_PLLE);      /* 2. Disable PLL1 with one feed sequence               */
    BSP_PLL_FEED_SEQ(1);        

    BSP_REG_PLLCFG(1) = reg_val;                                /* 3. Write to the PLLCFG and make it effective with... */
    BSP_PLL_FEED_SEQ(1);                                        /* ... one one feed sequence                            */
    
    DEF_BIT_SET(BSP_REG_PLLCTRL(1), BSP_BIT_PLLCTRL_PLLE);      /* 4. Enable PLL1 with one feed sequence                */
    BSP_PLL_FEED_SEQ(1);                                        

    reg_to = BSP_VAL_MAX_TO;                                    /* 5. Wait for PLL1 to achieve lock by monitoring ...   */
                                                                /* ... the PLOCK1 bit in the PLL1STAT                   */
    while (DEF_BIT_IS_CLR(BSP_REG_PLLSTAT(1), BSP_BIT_PLLSTAT_PLOCK1) &&
          (reg_to > 0)) {
        reg_to--;
    }

    if (reg_to == 0) {
        return (DEF_FAIL);        
    }    

    
    DEF_BIT_SET(BSP_REG_PLLCTRL(1), BSP_BIT_PLLCTRL_PLLC);      /* 6. Connect PLL1 with one feed sequence               */
    BSP_PLL_FEED_SEQ(1);                                        
           
    BSP_REG_PCLKSEL0 = DEF_BIT_NONE;                            /* All peripheral clock runrs at CPU_Clk / 4 = 25 Mhz   */
    BSP_REG_PCLKSEL1 = DEF_BIT_NONE;
            
    return (DEF_OK);
}

/*
*********************************************************************************************************
*                                             BSP_Joy_GetPos()
*
* Description : Get the position of the Joystick on the board.
*
* Argument(s) : none.
*
* Return(s)   : The current position of the Joystick.
*
*                           BSP_JOY_NONE     If the Joystick is not being pressed.
*                           BSP_JOY_UP       If the Joystick is toggled up.
*                           BSP_JOY_DOWN     If the Joystick is toggled down.
*                           BSP_JOY_RIGHT    If the Joystick is toggled right.
*                           BSP_JOY_LEFT     If the Joystick is toggled left.
*                           BSP_JOY_CENTER   If the Joystick is being pressed. 
*
* Caller(s)  : Application.
*
* Note(s)    : none.
*********************************************************************************************************
*/

CPU_INT08U  BSP_Joy_GetPos (void) 
{
    CPU_INT32U  port_status;    
    
    
    port_status = BSP_GPIO_StatusGet(BSP_GPIO_PORT1_FAST);
        
    if (DEF_BIT_IS_CLR(port_status, BSP_GPIO1_JOY_UP)) {
        return (BSP_JOY_UP);
    }
    
    if (DEF_BIT_IS_CLR(port_status, BSP_GPIO1_JOY_DOWN)) {
        return (BSP_JOY_DOWN);
    }

    if (DEF_BIT_IS_CLR(port_status, BSP_GPIO1_JOY_LEFT)) {
        return (BSP_JOY_LEFT);
    }
    
    if (DEF_BIT_IS_CLR(port_status, BSP_GPIO1_JOY_RIGHT)) {
        return (BSP_JOY_RIGHT);
    }

    port_status = BSP_GPIO_StatusGet(BSP_GPIO_PORT1_FAST);

    if (DEF_BIT_IS_CLR(port_status, BSP_GPIO1_JOY_CENTER)) {
        return (BSP_JOY_CENTER);
    }
    
    return (BSP_JOY_NONE);
}


/*
*********************************************************************************************************
*                                             BSP_Joy_GetStatus()
*
* Description : Get the status of the Joystick at a given position.
*
* Argument(s) :   joy_pos.   Position of the Joystick.
*
*                             BSP_JOY_UP       If the Joystick is toggled up.
*                             BSP_JOY_DOWN     If the Joystick is toggled down.
*                             BSP_JOY_RIGHT    If the Joystick is toggled right.
*                             BSP_JOY_LEFT     If the Joystick is toggled left.
*                             BSP_JOY_CENTER   If the Joystick is being pressed. 
*
* Return(s)   :  The current Joystick status at a given position.
*
*                             DEF_ON           If the Joystick is     in the position specifies by joy_position
*                             DEF_OFF          If the Joystick is not in the position specifies by joy_position
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/

CPU_INT08U  BSP_Joy_GetStatus (CPU_INT08U  joy_pos) 
{
    CPU_INT08U joy_status;

    
    joy_status = BSP_Joy_GetPos();    

    if (joy_status == joy_pos) {
        return (DEF_ON);
    }
    
    return (DEF_OFF);
}


/*
*********************************************************************************************************
*                                         BSP_Joy_Init()
*
* Description : Initializes the Joystick's I/O.
*
* Argument(s) : none
*
* Return(s)   : none.
*
* Caller(s)   : BSP_Init().
*
* Note(s)     : none.
*********************************************************************************************************
*/

static  void  BSP_Joy_Init      (void)
{
    BSP_GPIO_Cfg(BSP_GPIO_PORT1_FAST,
                (BSP_GPIO1_JOY_RIGHT |
                 BSP_GPIO1_JOY_DOWN  |
                 BSP_GPIO1_JOY_LEFT  |   
                 BSP_GPIO1_JOY_RIGHT),
                (BSP_GPIO_OPT_IN_EN | BSP_GPIO_OPT_FNCT_1));       

    BSP_GPIO_Cfg(BSP_GPIO_PORT1_FAST,
                 BSP_GPIO1_JOY_CENTER,
                (BSP_GPIO_OPT_IN_EN | BSP_GPIO_OPT_FNCT_1));           
}


/*
*********************************************************************************************************
*                                         BSP_LED_Init()
*
* Description : Initializes the board's LEDs.
*
* Argument(s) : none
*
* Return(s)   : none.
*
* Caller(s)   : BSP_Init().
*
* Note(s)     : none.
*********************************************************************************************************
*/

static  void  BSP_LED_Init (void)
{
    BSP_GPIO_Cfg(BSP_GPIO_PORT2_FAST,
                 BSP_GPIO2_LED2,
                (BSP_GPIO_OPT_OUT_EN | BSP_GPIO_OPT_FNCT_1));   

    BSP_GPIO_Cfg(BSP_GPIO_PORT2_FAST,
                 BSP_GPIO2_LED1,
                (BSP_GPIO_OPT_OUT_EN | BSP_GPIO_OPT_FNCT_1)); 
    
    BSP_LED_Off(0);
}

/*
*********************************************************************************************************
*                                                 BSP_LED_Off()
*
* Description : Turn OFF any or all the LEDs on the board.
*
* Argument(s) : led_id   The ID of the LED to control:
*
*                       0    turn OFF all LEDs on the board
*                       1    turn OFF USB_UP_LED1
*                       2    turn OFF USB_UP_LED2
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  BSP_LED_Off (CPU_INT08U  led) 
{
    switch (led)  {
        case 0:
             BSP_GPIO_Set(BSP_GPIO_PORT2_FAST,
                          BSP_GPIO2_LED1);

             BSP_GPIO_Set(BSP_GPIO_PORT2_FAST,
                          BSP_GPIO2_LED2);             
             break;

        case 1:         
             BSP_GPIO_Set(BSP_GPIO_PORT2_FAST,
                          BSP_GPIO2_LED1);
             break;

        case 2:         
             BSP_GPIO_Set(BSP_GPIO_PORT2_FAST,
                          BSP_GPIO2_LED2);
             break;
             
        default:
            break;
    }
}


/*
*********************************************************************************************************
*                                                 BSP_LED_On()
*
* Description : Turn ON any or all the LEDs on the board.
*
* Argument(s) : led_id   The ID of the LED to control:
*
*                       0    turn ON all LEDs on the board.
*                       1    turn ON USB_UP_LED1.
*                       2    turn ON USB_UP_LED2.
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  BSP_LED_On (CPU_INT08U  led) 
{
    switch (led)  {
        case 0:
             BSP_GPIO_Clr(BSP_GPIO_PORT2_FAST,
                          BSP_GPIO2_LED1);

             BSP_GPIO_Clr(BSP_GPIO_PORT2_FAST,
                          BSP_GPIO2_LED2);             
             break;

        case 1:         
             BSP_GPIO_Clr(BSP_GPIO_PORT2_FAST,
                          BSP_GPIO2_LED1);
             break;

        case 2:         
             BSP_GPIO_Clr(BSP_GPIO_PORT2_FAST,
                          BSP_GPIO2_LED2);
             break;
             
        default:
            break;
    }
}


/*
*********************************************************************************************************
*                                                 BSP_LED_Toggle()
*
* Description : Toggles any or all the LEDs on the board.
*
* Argument(s) : led_id   The ID of the LED to control:
*
*                       0    toggle all LEDs on the board
*                       1    toggle USB_UP_LED1
*                       2    toggle USB_UP_LED2
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  BSP_LED_Toggle (CPU_INT08U  led) 
{
    switch (led)  {
        case 0:
             BSP_GPIO_Toggle(BSP_GPIO_PORT2_FAST,
                             BSP_GPIO2_LED1);

             BSP_GPIO_Toggle(BSP_GPIO_PORT2_FAST,
                             BSP_GPIO2_LED2);             
             break;

        case 1:         
             BSP_GPIO_Toggle(BSP_GPIO_PORT2_FAST,
                             BSP_GPIO2_LED1);
             break;

        case 2:         
             BSP_GPIO_Toggle(BSP_GPIO_PORT2_FAST,
                             BSP_GPIO2_LED2);
             break;
             
        default:
            break;
    }
}


/*
*********************************************************************************************************
*                                           BSP_PB_GetStatus()
*
* Description : Get the status of a push button on the board.
*
* Argument(s) : pb_id   The ID of the push button to probe
*
*                       1    probe the push button B1
*                       2    probe the push button B2
*
* Return(s)   : DEF_OFF  if the push button is not pressed
*               DEF_ONN    if the push button is     pressed
*
* Caller(s)   : Application
*
* Note(s)     : none.
*********************************************************************************************************
*/


CPU_BOOLEAN  BSP_PB_GetStatus (CPU_INT08U  pb_id)
{
    CPU_INT32U   port_status;
    CPU_BOOLEAN  pb_status;
    
   
    pb_status   = DEF_OFF; 
    
    switch (pb_id) {
        case 1:
             port_status = BSP_GPIO_StatusGet(BSP_GPIO_PORT0_FAST);
             if (DEF_BIT_IS_CLR(port_status, BSP_GPIO2_BUT1)) {
                 pb_status = DEF_ON;    
             }
             break;
            
        case 2:
             port_status = BSP_GPIO_StatusGet(BSP_GPIO_PORT2_FAST);
             if (DEF_BIT_IS_CLR(port_status, BSP_GPIO2_BUT2)) {
                 pb_status = DEF_ON;    
             }
             break;
             
        default:
             break;
    }
    
    return (pb_status);
}


/*
*********************************************************************************************************
*                                                 BSP_PB_Init()
*
* Description : Initialize the I/Os for the LEDs
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : BSP_Init()
*
* Note(s)     : none.
*********************************************************************************************************
*/

static  void  BSP_PB_Init (void) 
{
    BSP_GPIO_Cfg(BSP_GPIO_PORT0_FAST,
                 BSP_GPIO2_BUT1,
                (BSP_GPIO_OPT_IN_EN | BSP_GPIO_OPT_FNCT_1));   

    BSP_GPIO_Cfg(BSP_GPIO_PORT2_FAST,
                 BSP_GPIO2_BUT2,
                (BSP_GPIO_OPT_IN_EN | BSP_GPIO_OPT_FNCT_1));       
}