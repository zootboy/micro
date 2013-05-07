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
*                                        MICRIUM BOARD SUPPORT PACKAGE
*                                         LPC17xx GENERAL PURPOSE I/O
*
* Filename      : bsp_gpio.c
* Version       : V1.00
* Programmer(s) : FT
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                             INCLUDE FILES
*********************************************************************************************************
*/

#define  BSP_GPIO_MODULE
#include <bsp.h>

/*
*********************************************************************************************************
*                                            LOCAL DEFINES
*********************************************************************************************************
*/

#define  BSP_GPIO_REG_PINSEL_BASE_ADDR                             (CPU_INT32U  )(0x4002C000)

#define  BSP_GPIO_REG_PINSEL0                                      (*(CPU_REG32 *)BSP_GPIO_REG_PINSEL_BASE_ADDR + 0x00)
#define  BSP_GPIO_REG_PINSEL1                                      (*(CPU_REG32 *)BSP_GPIO_REG_PINSEL_BASE_ADDR + 0x04)
#define  BSP_GPIO_REG_PINSEL2                                      (*(CPU_REG32 *)BSP_GPIO_REG_PINSEL_BASE_ADDR + 0x08)
#define  BSP_GPIO_REG_PINSEL3                                      (*(CPU_REG32 *)BSP_GPIO_REG_PINSEL_BASE_ADDR + 0x0C)
#define  BSP_GPIO_REG_PINSEL4                                      (*(CPU_REG32 *)BSP_GPIO_REG_PINSEL_BASE_ADDR + 0x10)
#define  BSP_GPIO_REG_PINSEL5                                      (*(CPU_REG32 *)BSP_GPIO_REG_PINSEL_BASE_ADDR + 0x14)
#define  BSP_GPIO_REG_PINSEL6                                      (*(CPU_REG32 *)BSP_GPIO_REG_PINSEL_BASE_ADDR + 0x18)
#define  BSP_GPIO_REG_PINSEL7                                      (*(CPU_REG32 *)BSP_GPIO_REG_PINSEL_BASE_ADDR + 0x1C)
#define  BSP_GPIO_REG_PINSEL8                                      (*(CPU_REG32 *)BSP_GPIO_REG_PINSEL_BASE_ADDR + 0x20)
#define  BSP_GPIO_REG_PINSEL9                                      (*(CPU_REG32 *)BSP_GPIO_REG_PINSEL_BASE_ADDR + 0x24)
#define  BSP_GPIO_REG_PINSEL10                                     (*(CPU_REG32 *)BSP_GPIO_REG_PINSEL_BASE_ADDR + 0x28)

#define  BSP_GPIO_REG_PINMODE_BASE_ADDR                            (CPU_INT32U  )(0x4002C040)

#define  BSP_GPIO_REG_PINMODE0                                     (*(CPU_REG32 *)BSP_GPIO_REG_PINMODE_BASE_ADDR + 0x00)
#define  BSP_GPIO_REG_PINMODE1                                     (*(CPU_REG32 *)BSP_GPIO_REG_PINMODE_BASE_ADDR + 0x04)
#define  BSP_GPIO_REG_PINMODE2                                     (*(CPU_REG32 *)BSP_GPIO_REG_PINMODE_BASE_ADDR + 0x08)
#define  BSP_GPIO_REG_PINMODE3                                     (*(CPU_REG32 *)BSP_GPIO_REG_PINMODE_BASE_ADDR + 0x0C)
#define  BSP_GPIO_REG_PINMODE4                                     (*(CPU_REG32 *)BSP_GPIO_REG_PINMODE_BASE_ADDR + 0x10)
#define  BSP_GPIO_REG_PINMODE5                                     (*(CPU_REG32 *)BSP_GPIO_REG_PINMODE_BASE_ADDR + 0x14)
#define  BSP_GPIO_REG_PINMODE6                                     (*(CPU_REG32 *)BSP_GPIO_REG_PINMODE_BASE_ADDR + 0x18)
#define  BSP_GPIO_REG_PINMODE7                                     (*(CPU_REG32 *)BSP_GPIO_REG_PINMODE_BASE_ADDR + 0x1C)
#define  BSP_GPIO_REG_PINMODE8                                     (*(CPU_REG32 *)BSP_GPIO_REG_PINMODE_BASE_ADDR + 0x20)
#define  BSP_GPIO_REG_PINMODE9                                     (*(CPU_REG32 *)BSP_GPIO_REG_PINMODE_BASE_ADDR + 0x24)

#define  BSP_GPIO_REG_PORTx_FAST_BASE_ADDR                         ((CPU_INT32U)0x2009C000)
#define  BSP_GPIO_REG_PORT0_FAST_BASE_ADDR                         ((CPU_INT32U)(BSP_GPIO_REG_PORTx_FAST_BASE_ADDR + 0x00))
#define  BSP_GPIO_REG_PORT1_FAST_BASE_ADDR                         ((CPU_INT32U)(BSP_GPIO_REG_PORTx_FAST_BASE_ADDR + 0x20))
#define  BSP_GPIO_REG_PORT2_FAST_BASE_ADDR                         ((CPU_INT32U)(BSP_GPIO_REG_PORTx_FAST_BASE_ADDR + 0x40))
#define  BSP_GPIO_REG_PORT3_FAST_BASE_ADDR                         ((CPU_INT32U)(BSP_GPIO_REG_PORTx_FAST_BASE_ADDR + 0x60))
#define  BSP_GPIO_REG_PORT4_FAST_BASE_ADDR                         ((CPU_INT32U)(BSP_GPIO_REG_PORTx_FAST_BASE_ADDR + 0x80))

#define  BSP_GPIO_REG_PINMODE_ODx_BASE_ADDR                        ((CPU_INT32U)BSP_GPIO_REG_PINMODE_BASE_ADDR + 0x28)
#define  BSP_GPIO_REG_PINMODE_OD0_BASE_ADDR                        ((CPU_INT32U)(BSP_GPIO_REG_PINMODE_ODx_BASE_ADDR + 0x00))
#define  BSP_GPIO_REG_PINMODE_OD1_BASE_ADDR                        ((CPU_INT32U)(BSP_GPIO_REG_PINMODE_ODx_BASE_ADDR + 0x04))
#define  BSP_GPIO_REG_PINMODE_OD2_BASE_ADDR                        ((CPU_INT32U)(BSP_GPIO_REG_PINMODE_ODx_BASE_ADDR + 0x08))
#define  BSP_GPIO_REG_PINMODE_OD3_BASE_ADDR                        ((CPU_INT32U)(BSP_GPIO_REG_PINMODE_ODx_BASE_ADDR + 0x0C))
#define  BSP_GPIO_REG_PINMODE_OD4_BASE_ADDR                        ((CPU_INT32U)(BSP_GPIO_REG_PINMODE_ODx_BASE_ADDR + 0x10))

#define  BSP_GPIO_OPT_FNCT_ANY                                     (BSP_GPIO_OPT_FNCT_1 | \
                                                                    BSP_GPIO_OPT_FNCT_2 | \
                                                                    BSP_GPIO_OPT_FNCT_3 | \
                                                                    BSP_GPIO_OPT_FNCT_4)

#define  BSP_GPIO_OPT_MODE_ANY                                     (BSP_GPIO_OPT_MODE_PULLUP   | \
                                                                    BSP_GPIO_OPT_MODE_NONE     | \
                                                                    BSP_GPIO_OPT_MODE_PULLDOWN | \
                                                                    BSP_GPIO_OPT_MODE_REPEATER | \
                                                                    BSP_GPIO_OPT_MODE_OPEN_DRAIN)

#define  BSP_GPIO_OPT_MODE_INVALID                                  0xFF
#define  BSP_GPIO_OPT_FNCT_INVALID                                  0xFF


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

typedef  struct bsp_gpio_fast_reg {
    CPU_REG32  FIODIR;
    CPU_REG32  RESERVED0[3];
    CPU_REG32  FIOMASK;
    CPU_REG32  FIOPIN;
    CPU_REG32  FIOSET;
    CPU_REG32  FIOCLR;    
} BSP_GPIO_FAST_REG;


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
*
*********************************************************************************************************
*                                           BSP_GPIO_Cfg()
*
* Description : Configure I/O pins on a specific port.
*
* Argument(s) : gpio_port           The PIO controller port.
*                                       BSP_GPIO_PORT0_FAST
*                                       BSP_GPIO_PORT1_FAST 
*                                       BSP_GPIO_PORT2_FAST
*                                       BSP_GPIO_PORT3_FAST 
*                                       BSP_GPIO_PORT4_FAST
*
*               gpio_pin            Bit field with the pins to be configured
*
*               gpio_cfg_opt        PIO configuration options
*                                       BSP_GPIO_OPT_OUT_EN           Controlled pin is output
*                                       BSP_GPIO_OPT_IN_EN            Controlled pin is input
*                                       BSP_GPIO_OPT_RD_WR_EN         Controlled pin is affected by writes to
*                                                                     FIOSET, FIOCLR, FIOPIN registers.
*                                       BSP_GPIO_OPT_FNCT1            Controlled pin is configured with function 1
*                                       BSP_GPIO_OPT_FNCT2            Controlled pin is configured with function 2
*                                       BSP_GPIO_OPT_FNCT3            Controlled pin is configured with function 3
*                                       BSP_GPIO_OPT_FNCT4            Controlled pin is configured with function 4
*
*                                       BSP_GPIO_OPT_MODE_PULLUP      Controlled pin has a pull-up resitor enabled.
*                                       BSP_GPIO_OPT_MODE_NONE        Controlled pin has neither pull-up nor pull-down.
*                                       BSP_GPIO_OPT_MODE_PULLDOWN    Controlled pin has a pull-down resistor enabled.
*                                       BSP_GPIO_OPT_MODE_REPEATER    Controlled pin has repeater mode enabled.
*                                       BSP_GPIO_OPT_MODE_OPEN_DRAIN  Controlled pin is in open drain mode.
*
* Return(s)   : none.
*
*
* Caller(s)   : Application.
*
* Note(s)     : None.
*********************************************************************************************************
*/

void   BSP_GPIO_Cfg (CPU_INT08U   gpio_port,
                     CPU_INT32U   gpio_pins,     
                     CPU_INT16U   gpio_opt)
{
    BSP_GPIO_FAST_REG  *p_gpio_fast_reg;    
    CPU_REG32          *p_gpio_pinsel;
    CPU_REG32          *p_gpio_pinmode;  
    CPU_REG32          *p_gpio_pinmode_od;  
    
    CPU_INT32U          pinsel_opt;
    CPU_INT32U          pinmode_opt;
    CPU_INT32U          pin_nbr;
    
    
    switch (gpio_port) {
        case BSP_GPIO_PORT0_FAST:
             p_gpio_fast_reg   = (BSP_GPIO_FAST_REG *)(BSP_GPIO_REG_PORT0_FAST_BASE_ADDR); 
             p_gpio_pinsel     = (CPU_REG32         *)(BSP_GPIO_REG_PINSEL_BASE_ADDR  + 0x00);
             p_gpio_pinmode    = (CPU_REG32         *)(BSP_GPIO_REG_PINMODE_BASE_ADDR + 0x00);
             p_gpio_pinmode_od = (CPU_REG32         *)(BSP_GPIO_REG_PINMODE_OD0_BASE_ADDR);
             break;

        case BSP_GPIO_PORT1_FAST:
             p_gpio_fast_reg   = (BSP_GPIO_FAST_REG *)(BSP_GPIO_REG_PORT1_FAST_BASE_ADDR); 
             p_gpio_pinsel     = (CPU_REG32         *)(BSP_GPIO_REG_PINSEL_BASE_ADDR  + 0x08);
             p_gpio_pinmode    = (CPU_REG32         *)(BSP_GPIO_REG_PINMODE_BASE_ADDR + 0x08);
             p_gpio_pinmode_od = (CPU_REG32         *)(BSP_GPIO_REG_PINMODE_OD1_BASE_ADDR);
             break;

        case BSP_GPIO_PORT2_FAST:
             p_gpio_fast_reg   = (BSP_GPIO_FAST_REG *)(BSP_GPIO_REG_PORT2_FAST_BASE_ADDR); 
             p_gpio_pinsel     = (CPU_REG32         *)(BSP_GPIO_REG_PINSEL_BASE_ADDR  + 0x10);
             p_gpio_pinmode    = (CPU_REG32         *)(BSP_GPIO_REG_PINMODE_BASE_ADDR + 0x10);
             p_gpio_pinmode_od = (CPU_REG32         *)(BSP_GPIO_REG_PINMODE_OD2_BASE_ADDR);
             
             break;

        case BSP_GPIO_PORT3_FAST:
             p_gpio_fast_reg   = (BSP_GPIO_FAST_REG *)(BSP_GPIO_REG_PORT3_FAST_BASE_ADDR); 
             p_gpio_pinsel     = (CPU_REG32         *)(BSP_GPIO_REG_PINSEL_BASE_ADDR  + 0x18);
             p_gpio_pinmode    = (CPU_REG32         *)(BSP_GPIO_REG_PINMODE_BASE_ADDR + 0x18);
             p_gpio_pinmode_od = (CPU_REG32         *)(BSP_GPIO_REG_PINMODE_OD3_BASE_ADDR);
             
             break;

        case BSP_GPIO_PORT4_FAST:
             p_gpio_fast_reg   = (BSP_GPIO_FAST_REG *)(BSP_GPIO_REG_PORT4_FAST_BASE_ADDR); 
             p_gpio_pinsel     = (CPU_REG32         *)(BSP_GPIO_REG_PINSEL_BASE_ADDR  + 0x20);
             p_gpio_pinmode    = (CPU_REG32         *)(BSP_GPIO_REG_PINMODE_BASE_ADDR + 0x20);
             p_gpio_pinmode_od = (CPU_REG32         *)(BSP_GPIO_REG_PINMODE_OD4_BASE_ADDR);
             break;

        case BSP_GPIO_PORT0:
        case BSP_GPIO_PORT1:             
        default:
             return;
    }

                                                                /* ------------ I/O DIRECTION CONFIGURATION ----------- */
    if (DEF_BIT_IS_SET(gpio_opt, BSP_GPIO_OPT_OUT_EN)) {
        DEF_BIT_SET(p_gpio_fast_reg->FIODIR, gpio_pins);
    }
    
    if (DEF_BIT_IS_SET(gpio_opt, BSP_GPIO_OPT_IN_EN)) {
        DEF_BIT_CLR(p_gpio_fast_reg->FIODIR, gpio_pins);
    }            
        
    if (DEF_BIT_IS_SET(gpio_opt, BSP_GPIO_OPT_RD_WR_EN)) {
        DEF_BIT_CLR(p_gpio_fast_reg->FIOMASK, gpio_pins);
    }            
    
    if (DEF_BIT_IS_SET(gpio_opt, BSP_GPIO_OPT_RD_WR_DIS)) {
        DEF_BIT_SET(p_gpio_fast_reg->FIOMASK, gpio_pins);
    }            

                
                                                                /* ---- I/O MODE/PERIPHERAL FUNCTION CONFIGURATION ---- */
    pinsel_opt  = BSP_GPIO_OPT_FNCT_INVALID;                   
    pinmode_opt = BSP_GPIO_OPT_MODE_INVALID;
                                                                /* Set PINSELxx based on BSP_GPIO_OPT_FNCT_xxx          */
    if (DEF_BIT_IS_SET_ANY(gpio_opt, BSP_GPIO_OPT_FNCT_ANY)) {
        if (DEF_BIT_IS_SET(gpio_opt, BSP_GPIO_OPT_FNCT_1)) {
            pinsel_opt = 0x00;
        } else if (DEF_BIT_IS_SET(gpio_opt, BSP_GPIO_OPT_FNCT_2)) {
            pinsel_opt = 0x01;
        } else if (DEF_BIT_IS_SET(gpio_opt, BSP_GPIO_OPT_FNCT_3)) {
            pinsel_opt = 0x02;
        } else if (DEF_BIT_IS_SET(gpio_opt, BSP_GPIO_OPT_FNCT_4)) {
            pinsel_opt = 0x03;
        } else {
            return;
        }
    }

                                                                /* Set PMODExx based on BSP_GPIO_OPT_MDOE_xxx         */
    if (DEF_BIT_IS_SET_ANY(gpio_opt, BSP_GPIO_OPT_MODE_ANY)) {
        if (DEF_BIT_IS_SET(gpio_opt, BSP_GPIO_OPT_MODE_PULLUP)) {
            pinmode_opt = 0x00;
        } else if (DEF_BIT_IS_SET(gpio_opt, BSP_GPIO_OPT_MODE_REPEATER)) {
            pinmode_opt = 0x01;            
        } else if (DEF_BIT_IS_SET(gpio_opt, BSP_GPIO_OPT_MODE_NONE)) {
            pinmode_opt = 0x02;
        } else if (DEF_BIT_IS_SET(gpio_opt, BSP_GPIO_OPT_MODE_PULLDOWN)) {
            pinmode_opt = 0x03;
        }
    }
    
    if ((pinsel_opt != BSP_GPIO_OPT_FNCT_INVALID) ||
        (pinmode_opt  != BSP_GPIO_OPT_MODE_INVALID)) {
        for (pin_nbr = 0; pin_nbr < 32; pin_nbr++) {
            if (DEF_BIT_IS_SET(gpio_pins, DEF_BIT(pin_nbr))) {
                
                if (pinsel_opt != BSP_GPIO_OPT_FNCT_INVALID) {
                    if (pin_nbr < 16) {
                        DEF_BIT_CLR(*p_gpio_pinsel, DEF_BIT_FIELD(2, pin_nbr * 2));
                        DEF_BIT_SET(*p_gpio_pinsel, DEF_BIT_MASK(pinsel_opt, pin_nbr * 2));
                    } else {
                        DEF_BIT_CLR(*((CPU_REG32 *)((CPU_INT32U)p_gpio_pinsel + 0x04)), DEF_BIT_FIELD(2, (pin_nbr - 16) * 2));
                        DEF_BIT_SET(*((CPU_REG32 *)((CPU_INT32U)p_gpio_pinsel + 0x04)), DEF_BIT_MASK(pinsel_opt, (pin_nbr - 16) * 2));
                    }
                }
        
                if (DEF_BIT_IS_SET(gpio_pins, DEF_BIT(pin_nbr))) {
                    if (pinmode_opt != BSP_GPIO_OPT_MODE_INVALID) {
                        if (pin_nbr < 16) {                        
                            DEF_BIT_CLR(*p_gpio_pinmode, DEF_BIT_FIELD(2, pin_nbr * 2));
                            DEF_BIT_SET(*p_gpio_pinmode, DEF_BIT_MASK(pinmode_opt, pin_nbr * 2));
                        } else {
                            DEF_BIT_CLR(*((CPU_REG32 *)((CPU_INT32U)p_gpio_pinmode + 0x04)), DEF_BIT_FIELD(2, (pin_nbr - 16) * 2));
                            DEF_BIT_SET(*((CPU_REG32 *)((CPU_INT32U)p_gpio_pinmode + 0x04)), DEF_BIT_MASK(pinmode_opt, (pin_nbr - 16) * 2));
                        }
                    }
                }
            }
        }
    }

    if (DEF_BIT_IS_SET(gpio_opt, BSP_GPIO_OPT_MODE_OPEN_DRAIN)) {
        *p_gpio_pinmode_od = gpio_pins;
    }
}


/*
*********************************************************************************************************
*                                           BSP_GPIO_Set()
*
* Description : Set a pin(s) ona specific port
*
* Argument(s) : gpio_port           The PIO controller port.
*                                       BSP_PIO_PORT0       
*                                       BSP_PIO_PORT1    
*                                       BSP_GPIO_PORT0_FAST
*                                       BSP_GPIO_PORT1_FAST 
*                                       BSP_GPIO_PORT2_FAST
*                                       BSP_GPIO_PORT3_FAST
*                                       BSP_GPIO_PORT4_FAST 
*
*               gpio_pin            Port pin(s) to be set.
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : None.
*********************************************************************************************************
*/

void  BSP_GPIO_Set  (CPU_INT08U   gpio_port,
                     CPU_INT32U   gpio_pin)
{
    BSP_GPIO_FAST_REG  *p_gpio_fast_reg;    


    switch (gpio_port) {
        case BSP_GPIO_PORT0_FAST:
             p_gpio_fast_reg   = (BSP_GPIO_FAST_REG *)(BSP_GPIO_REG_PORT0_FAST_BASE_ADDR); 
             break;

        case BSP_GPIO_PORT1_FAST:
             p_gpio_fast_reg   = (BSP_GPIO_FAST_REG *)(BSP_GPIO_REG_PORT1_FAST_BASE_ADDR); 
             break;

        case BSP_GPIO_PORT2_FAST:
             p_gpio_fast_reg   = (BSP_GPIO_FAST_REG *)(BSP_GPIO_REG_PORT2_FAST_BASE_ADDR); 
             break;

        case BSP_GPIO_PORT3_FAST:
             p_gpio_fast_reg   = (BSP_GPIO_FAST_REG *)(BSP_GPIO_REG_PORT3_FAST_BASE_ADDR); 
             break;

        case BSP_GPIO_PORT4_FAST:
             p_gpio_fast_reg   = (BSP_GPIO_FAST_REG *)(BSP_GPIO_REG_PORT4_FAST_BASE_ADDR); 
             break;             

        case BSP_GPIO_PORT0:
        case BSP_GPIO_PORT1:             
        default:
             return;
    
    }

    p_gpio_fast_reg->FIOSET = gpio_pin;
}


/*
*********************************************************************************************************
*                                           BSP_GPIO_Clr()
*
* Description : Clear a pin(s) ona specific port
*
* Argument(s) : gpio_port           The PIO controller port.
*                                       BSP_GPIO_PORT0_FAST
*                                       BSP_GPIO_PORT1_FAST 
*                                       BSP_GPIO_PORT2_FAST
*                                       BSP_GPIO_PORT3_FAST
*                                       BSP_GPIO_PORT4_FAST 
*
*               gpio_pin            Port pin(s) to be cleared.
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  BSP_GPIO_Clr (CPU_INT08U  gpio_port,
                    CPU_INT32U  gpio_pin)
{    
    BSP_GPIO_FAST_REG  *p_gpio_fast_reg;    


    switch (gpio_port) {
        case BSP_GPIO_PORT0_FAST:
             p_gpio_fast_reg   = (BSP_GPIO_FAST_REG *)(BSP_GPIO_REG_PORT0_FAST_BASE_ADDR); 
             break;

        case BSP_GPIO_PORT1_FAST:
             p_gpio_fast_reg   = (BSP_GPIO_FAST_REG *)(BSP_GPIO_REG_PORT1_FAST_BASE_ADDR); 
             break;

        case BSP_GPIO_PORT2_FAST:
             p_gpio_fast_reg   = (BSP_GPIO_FAST_REG *)(BSP_GPIO_REG_PORT2_FAST_BASE_ADDR); 
             break;

        case BSP_GPIO_PORT3_FAST:
             p_gpio_fast_reg   = (BSP_GPIO_FAST_REG *)(BSP_GPIO_REG_PORT3_FAST_BASE_ADDR); 
             break;

        case BSP_GPIO_PORT4_FAST:
             p_gpio_fast_reg   = (BSP_GPIO_FAST_REG *)(BSP_GPIO_REG_PORT4_FAST_BASE_ADDR); 
             break;

        case BSP_GPIO_PORT0:
        case BSP_GPIO_PORT1:             
        default:
             return;
    }

    p_gpio_fast_reg->FIOCLR = gpio_pin;
}


/*
*********************************************************************************************************
*                                           BSP_GPIO_StatusGet()
*
* Description : Return current status status of the pin(s).
*
* Argument(s) : gpio_port           The PIO controller port.
*                                       BSP_GPIO_PORT0_FAST
*                                       BSP_GPIO_PORT1_FAST 
*                                       BSP_GPIO_PORT2_FAST
*                                       BSP_GPIO_PORT3_FAST
*                                       BSP_GPIO_PORT4_FAST 
*
*               gpio_pin            Port pin(s) to be read.
*
* Return(s)   : The status of the pin(s)
*                               
* Caller(s)   : Application.
*
* Note(s)     : None.
*********************************************************************************************************
*/
CPU_INT32U  BSP_GPIO_StatusGet  (CPU_INT08U   gpio_port)

{    
    BSP_GPIO_FAST_REG  *p_gpio_fast_reg;     
    CPU_INT32U          port_status;


    switch (gpio_port) {
        case BSP_GPIO_PORT0_FAST:
             p_gpio_fast_reg   = (BSP_GPIO_FAST_REG *)(BSP_GPIO_REG_PORT0_FAST_BASE_ADDR);
             break;

        case BSP_GPIO_PORT1_FAST:
             p_gpio_fast_reg   = (BSP_GPIO_FAST_REG *)(BSP_GPIO_REG_PORT1_FAST_BASE_ADDR);
             break;

        case BSP_GPIO_PORT2_FAST:
             p_gpio_fast_reg   = (BSP_GPIO_FAST_REG *)(BSP_GPIO_REG_PORT2_FAST_BASE_ADDR);
             break;

        case BSP_GPIO_PORT3_FAST:
             p_gpio_fast_reg   = (BSP_GPIO_FAST_REG *)(BSP_GPIO_REG_PORT3_FAST_BASE_ADDR);
             break;

        case BSP_GPIO_PORT4_FAST:
             p_gpio_fast_reg   = (BSP_GPIO_FAST_REG *)(BSP_GPIO_REG_PORT4_FAST_BASE_ADDR);
             break;

        case BSP_GPIO_PORT0:
        case BSP_GPIO_PORT1:
        default:
             return (DEF_BIT_NONE);
    }
        
    port_status = p_gpio_fast_reg->FIOPIN;

    return (port_status);
}


/*
*********************************************************************************************************
*                                           BSP_GPIO_Toggle()
*
* Description : Toggle an I/O pin(s)
*
* Argument(s) : gpio_port           The PIO controller port.
*                                       BSP_GPIO_PORT0_FAST
*                                       BSP_GPIO_PORT1_FAST 
*                                       BSP_GPIO_PORT2_FAST
*                                       BSP_GPIO_PORT3_FAST
*                                       BSP_GPIO_PORT4_FAST 
*
*               gpio_pin            Port pin(s) to be toggled
*
* Return(s)   : none.
*                               
* Caller(s)   : Application.
*
* Note(s)     : None.
*********************************************************************************************************
*/

void  BSP_GPIO_Toggle (CPU_INT08U   gpio_port,
                       CPU_INT32U   gpio_pin)
{    
    BSP_GPIO_FAST_REG  *p_gpio_fast_reg;         
    CPU_INT32U          pin_set;
    CPU_INT32U          pin_clr;
    

    switch (gpio_port) {             
        case BSP_GPIO_PORT0_FAST:
             p_gpio_fast_reg   = (BSP_GPIO_FAST_REG *)(BSP_GPIO_REG_PORT0_FAST_BASE_ADDR); 
             break;

        case BSP_GPIO_PORT1_FAST:
             p_gpio_fast_reg   = (BSP_GPIO_FAST_REG *)(BSP_GPIO_REG_PORT1_FAST_BASE_ADDR); 
             break;

        case BSP_GPIO_PORT2_FAST:
             p_gpio_fast_reg   = (BSP_GPIO_FAST_REG *)(BSP_GPIO_REG_PORT2_FAST_BASE_ADDR); 
             break;

        case BSP_GPIO_PORT3_FAST:
             p_gpio_fast_reg   = (BSP_GPIO_FAST_REG *)(BSP_GPIO_REG_PORT3_FAST_BASE_ADDR); 
             break;

        case BSP_GPIO_PORT4_FAST:
             p_gpio_fast_reg   = (BSP_GPIO_FAST_REG *)(BSP_GPIO_REG_PORT4_FAST_BASE_ADDR); 
             break;

        case BSP_GPIO_PORT0:
        case BSP_GPIO_PORT1:             
        default:
             return;
    }
    
    pin_clr                 =  (p_gpio_fast_reg->FIOPIN) & gpio_pin;    
    pin_set                 = ~(p_gpio_fast_reg->FIOPIN) & gpio_pin;
    p_gpio_fast_reg->FIOCLR = pin_clr;
    p_gpio_fast_reg->FIOSET = pin_set;
}