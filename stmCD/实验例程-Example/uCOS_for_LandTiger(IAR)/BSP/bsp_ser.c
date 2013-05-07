/*
*********************************************************************************************************
*                                     MICRIUM BOARD SUPPORT SUPPORT
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
*                                      MICRIUM BOARD SUPPORT PACKAGE
*                                         SERIAL (UART) INTERFACE
*
* Filename      : bsp_ser.c
* Version       : V1.00
* Programmer(s) : FT
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                             INCLUDE FILES
*********************************************************************************************************
*/

#define   BSP_SER_MODULE
#include  <stdarg.h>
#include  <stdio.h>
#include  <bsp.h>


/*
*********************************************************************************************************
*                                            LOCAL DEFINES
*********************************************************************************************************
*/

#define  BSP_SER_REG_U0_BASE_ADDR                ((CPU_INT32U)0x4000C000)
#define  BSP_SER_REG_U1_BASE_ADDR                ((CPU_INT32U)0x40010000)

                                                                  /* ------------- UART0 Register Defines ----------- */
#define  BSP_SER_REG_U0_RBR              (*(CPU_REG32 *)(BSP_SER_REG_U0_BASE_ADDR + 0x0000))
#define  BSP_SER_REG_U0_THR              (*(CPU_REG32 *)(BSP_SER_REG_U0_BASE_ADDR + 0x0000))
#define  BSP_SER_REG_U0_DLL              (*(CPU_REG32 *)(BSP_SER_REG_U0_BASE_ADDR + 0x0000))
#define  BSP_SER_REG_U0_DLM              (*(CPU_REG32 *)(BSP_SER_REG_U0_BASE_ADDR + 0x0004))
#define  BSP_SER_REG_U0_IER              (*(CPU_REG32 *)(BSP_SER_REG_U0_BASE_ADDR + 0x0004))
#define  BSP_SER_REG_U0_IIR              (*(CPU_REG32 *)(BSP_SER_REG_U0_BASE_ADDR + 0x0008))
#define  BSP_SER_REG_U0_FCR              (*(CPU_REG32 *)(BSP_SER_REG_U0_BASE_ADDR + 0x0008))
#define  BSP_SER_REG_U0_LCR              (*(CPU_REG32 *)(BSP_SER_REG_U0_BASE_ADDR + 0x000C))
#define  BSP_SER_REG_U0_LSR              (*(CPU_REG32 *)(BSP_SER_REG_U0_BASE_ADDR + 0x0014))
#define  BSP_SER_REG_U0_FDR              (*(CPU_REG32 *)(BSP_SER_REG_U0_BASE_ADDR + 0x0028))

                                                                  /* ------------- UART1 Register Defines ----------- */
#define  BSP_SER_REG_U0_RBR              (*(CPU_REG32 *)(BSP_SER_REG_U0_BASE_ADDR + 0x0000))
#define  BSP_SER_REG_U1_THR              (*(CPU_REG32 *)(BSP_SER_REG_U0_BASE_ADDR + 0x0000))
#define  BSP_SER_REG_U1_DLL              (*(CPU_REG32 *)(BSP_SER_REG_U0_BASE_ADDR + 0x0000))
#define  BSP_SER_REG_U1_DLM              (*(CPU_REG32 *)(BSP_SER_REG_U0_BASE_ADDR + 0x0004))
#define  BSP_SER_REG_U1_IER              (*(CPU_REG32 *)(BSP_SER_REG_U0_BASE_ADDR + 0x0004))
#define  BSP_SER_REG_U1_IIR              (*(CPU_REG32 *)(BSP_SER_REG_U0_BASE_ADDR + 0x0008))
#define  BSP_SER_REG_U1_FCR              (*(CPU_REG32 *)(BSP_SER_REG_U0_BASE_ADDR + 0x0008))
#define  BSP_SER_REG_U1_LCR              (*(CPU_REG32 *)(BSP_SER_REG_U0_BASE_ADDR + 0x000C))
#define  BSP_SER_REG_U1_LSR              (*(CPU_REG32 *)(BSP_SER_REG_U0_BASE_ADDR + 0x0014))
#define  BSP_SER_REG_U1_FDR              (*(CPU_REG32 *)(BSP_SER_REG_U0_BASE_ADDR + 0x0028))


#define  BSP_SER_U0_PINS                 (DEF_BIT_02 | DEF_BIT_03)
#define  BSP_SER_U1_PINS                 (DEF_BIT_15 | DEF_BIT_16)


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

static  BSP_OS_SEM   BSP_SerTxWait;
static  BSP_OS_SEM   BSP_SerRxWait;
static  BSP_OS_SEM   BSP_SerLock;

static  CPU_INT08U   BSP_SerRxData;


/*
*********************************************************************************************************
*                                      LOCAL FUNCTION PROTOTYPES
*********************************************************************************************************
*/

static  void        BSP_SerISR_Handler     (void);

static  CPU_INT08U  BSP_SerRdByteUnlocked  (void);

static  void        BSP_SerWrByteUnlocked  (CPU_INT08U  c);


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
*                                          BSP_Ser_Init()
*
* Description : Initialize a serial port for communication.
*
* Argument(s) : baud_rate           The desire RS232 baud rate.
*
* Return(s)   : none.
*
* Caller(s)   : Application
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  BSP_SerInit (CPU_INT32U  baud_rate)
{    
    CPU_INT16U  div;                                            /* Baud rate divisor                                  */
    CPU_INT08U  divlo;
    CPU_INT08U  divhi;
    CPU_INT32U  pclk_freq;

  
    BSP_OS_SemCreate(&BSP_SerTxWait, 0, "Serial Tx Wait");
    BSP_OS_SemCreate(&BSP_SerRxWait, 0, "Serial Rx Wait");        
    BSP_OS_SemCreate(&BSP_SerLock  , 1, "Serial Lock");    

    BSP_SerRxData = 0; 
                                                                /* ------------ COMPUTE DIVISOR BAUD RATE ----------- */
                                                                /* Get the peripheral frequency                       */

    pclk_freq  = BSP_PM_PerClkFreqGet(BSP_PM_PER_NBR_UART0);
    
    
    div       = (CPU_INT16U)(((2 * pclk_freq / 16 / baud_rate) + 1) / 2);
    divlo     =  div & 0x00FF;                                  /* Split divisor into LOW and HIGH bytes              */
    divhi     = (div >> 8) & 0x00FF;
    
#if (BSP_CFG_SER_COMM_SEL == BSP_SER_COMM_UART_00)
    BSP_PM_PerClkEn(BSP_PM_PER_NBR_UART0);
                                                                /* ------------------- ENABLE UART0 I/Os ------------------ */
    BSP_GPIO_Cfg(BSP_GPIO_PORT0_FAST,
                 BSP_SER_U0_PINS,
                 BSP_GPIO_OPT_FNCT_2);
                                                                /* --------------------- SETUP UART0 ---------------------- */
    BSP_SER_REG_U0_LCR = DEF_BIT_07;                            /* Set divisor access bit                                   */
    BSP_SER_REG_U0_DLL = divlo;                                 /* Load divisor                                             */
    BSP_SER_REG_U0_DLM = divhi;
    BSP_SER_REG_U0_LCR = 0x03;                                  /* 8 Bits, 1 Stop, No Parity                                */
    BSP_SER_REG_U0_IER = 0x00;                                  /* Disable both Rx and Tx interrupts                        */
    BSP_SER_REG_U0_FDR = DEF_BIT_NONE;
    BSP_SER_REG_U0_FCR = DEF_BIT_00;                            /* Enable FIFO, flush Rx & Tx                               */
 
    BSP_IntVectSet((CPU_INT08U   )BSP_INT_SRC_NBR_UART0,
                   (CPU_FNCT_VOID)BSP_SerISR_Handler );

    BSP_IntEn(BSP_INT_SRC_NBR_UART0);
#endif

#if (BSP_CFG_SER_COMM_SEL == BSP_SER_COMM_UART_01)
    BSP_PM_PerClkEn(BSP_PM_PER_NBR_UART1);
                                                                /* ------------------- ENABLE UART0 I/Os ------------------ */
    BSP_GPIO_Cfg(BSP_GPIO_PORT0_FAST,
                 BSP_SER_U1_PINS,
                 BSP_GPIO_OPT_FNCT_2);
                                                                /* --------------------- SETUP UART1 ---------------------- */
    BSP_SER_REG_U1_LCR = DEF_BIT_07;                            /* Set divisor access bit                                   */
    BSP_SER_REG_U1_DLL = divlo;                                 /* Load divisor                                             */
    BSP_SER_REG_U1_DLM = divhi;
    BSP_SER_REG_U1_LCR = 0x03;                                  /* 8 Bits, 1 Stop, No Parity                                */
    BSP_SER_REG_U1_IER = 0x00;                                  /* Disable both Rx and Tx interrupts                        */
    BSP_SER_REG_U1_FDR = DEF_BIT_NONE;
    BSP_SER_REG_U1_FCR = DEF_BIT_00;                            /* Enable FIFO, flush Rx & Tx                               */
 
    BSP_IntVectSet((CPU_INT08U   )BSP_INT_SRC_NBR_UART1,
                   (CPU_FNCT_VOID)BSP_SerISR_Handler );

    BSP_IntEn(BSP_INT_SRC_NBR_UART1);
#endif           
}


/*
*********************************************************************************************************
*                                         BSP_Ser_ISR_Handler()
*
* Description : Serial ISR
*
* Argument(s) : none
*
* Return(s)   : none.
*
* Caller(s)   : This is an ISR.
*
* Note(s)     : none.
*********************************************************************************************************
*/

static  void  BSP_SerISR_Handler (void)
{
    CPU_INT08U  lsr;
    CPU_INT08U  iir;

#if (BSP_CFG_SER_COMM_SEL == BSP_SER_COMM_UART_00)
    iir = BSP_SER_REG_U0_IIR & 0x0F;
#endif

#if (BSP_CFG_SER_COMM_SEL == BSP_SER_COMM_UART_01)
    iir = BSP_SER_REG_U1_IIR & 0x0F;
#endif
    
    while (iir != 1) {
        switch (iir) {
            case  2:                                            /* Transmitted character?                                   */
                 BSP_OS_SemPost(&BSP_SerTxWait);    
                 break;

            case  4:                                            /* Received a character?                                    */
                BSP_OS_SemPost(&BSP_SerRxWait);     
                lsr           = BSP_SER_REG_U0_LSR;
                BSP_SerRxData = BSP_SER_REG_U0_RBR;
                (void)lsr;
                break;

            default:
                break;
        }
#if (BSP_CFG_SER_COMM_SEL == BSP_SER_COMM_UART_00)
        iir = BSP_SER_REG_U0_IIR & 0x0F;
#endif

#if (BSP_CFG_SER_COMM_SEL == BSP_SER_COMM_UART_01)
        iir = BSP_SER_REG_U1_IIR & 0x0F;
#endif        
    }
}


/*
*********************************************************************************************************
*                                                BSP_Ser_Printf()
*
* Description : Formatted outout to the serial port.
*               This funcion reads a string from a serial port. This call blocks until a
*               character appears at the port and the last character is a Carriage
*               Return (0x0D).
*
* Argument(s) : Format string follwing the C format convention.
*
* Return(s)   : none.
*
* Caller(s)   : Application
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  BSP_SerPrintf (CPU_CHAR *format, ...)
{
    CPU_CHAR  buffer[128u + 1u];
    va_list   vArgs;


    va_start(vArgs, format);
    vsprintf((char *)buffer, (char const *)format, vArgs);
    va_end(vArgs);

    BSP_SerWrStr((CPU_CHAR*) buffer);
}


/*
*********************************************************************************************************
*                                                Ser_WrByte()
*
* Description : Writes a single byte to a serial port.
*
* Argument(s) : tx_byte     The character to output.
*
* Return(s)   : none.
*
* Caller(s)   : Application
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  BSP_SerWrByte (CPU_INT08U  c)
{        
    BSP_OS_SemWait(&BSP_SerLock, 0);
    
    BSP_SerWrByteUnlocked(c);

    BSP_OS_SemPost(&BSP_SerLock);    
}


/*
*********************************************************************************************************
*                                             BSP_Ser_WrByteUnlocked()
*
* Description : Writes a single byte to a serial port.
*
* Argument(s) : tx_byte     The character to output.
*
* Return(s)   : none.
*
* Caller(s)   : BSP_Ser_WrStr()
*
* Note(s)     : (1) This function blocks until room is available in the UART for the byte to be sent.
*********************************************************************************************************
*/

static  void  BSP_SerWrByteUnlocked (CPU_INT08U c)
{                
#if (BSP_CFG_SER_COMM_SEL == BSP_SER_COMM_UART_00)
    BSP_SER_REG_U0_THR = c;
    DEF_BIT_SET(BSP_SER_REG_U0_IER, DEF_BIT_01);

    BSP_OS_SemWait(&BSP_SerTxWait, 0);    
    DEF_BIT_CLR(BSP_SER_REG_U0_IER, DEF_BIT_01);
#endif
    
#if (BSP_CFG_SER_COMM_SEL == BSP_SER_COMM_UART_01)
    BSP_SER_REG_U1_THR = c;
    DEF_BIT_SET(BSP_SER_REG_U1_IER, DEF_BIT_01);

    BSP_OS_SemWait(&BSP_SerTxWait, 0);
    DEF_BIT_CLR(BSP_SER_REG_U1_IER, DEF_BIT_01);
#endif

}


/*
*********************************************************************************************************
*                                                BSP_Ser_WrStr()
*
* Description : Transmits a string.
*
* Argument(s) : tx_str      The string that will be transmitted.
*
* Return(s)   : none.
*
* Caller(s)   : Application
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  BSP_SerWrStr (CPU_CHAR *p_str)
{
    BSP_OS_SemWait(&BSP_SerLock, 0);

    while ((*p_str) != 0) {
        BSP_SerWrByteUnlocked(*p_str);

        if (*p_str == ASCII_CHAR_LINE_FEED) {
            BSP_SerWrByteUnlocked(ASCII_CHAR_CARRIAGE_RETURN);            
        }
        p_str++;
    }

    BSP_OS_SemPost(&BSP_SerLock);
}


/*
*********************************************************************************************************
*                                                BSP_Ser_RdByte()
*
* Description : Read a single byte.
*
* Argument(s) : none.
*
* Return(s)   : The received byte
*
* Caller(s)   : BSP_Ser_RdStr()
*
* Note(s)     : none.
*********************************************************************************************************
*/

CPU_INT08U  BSP_SerRdByte (void)
{
    CPU_INT08U   rx_byte;
    
    
    BSP_OS_SemWait(&BSP_SerLock, 0);
    
    rx_byte = BSP_SerRdByteUnlocked();
    
    BSP_OS_SemPost(&BSP_SerLock);
    
    return (rx_byte);    
}

/*
*********************************************************************************************************
*                                          BSP_Ser_RdByteUnlocked()
*
* Description : Read a single byte.
*
* Argument(s) : none.
*
* Return(s)   : The received byte
*
* Caller(s)   : BSP_Ser_RdStr()
*               BSP_Ser_RdByte()
*
* Note(s)     : none.
*********************************************************************************************************
*/

static  CPU_INT08U  BSP_SerRdByteUnlocked (void)
{
    CPU_INT08U    rx_byte;


#if (BSP_CFG_SER_COMM_SEL == BSP_SER_COMM_UART_00)          
    rx_byte = 0;
    
    DEF_BIT_SET(BSP_SER_REG_U0_IER, DEF_BIT_00);
    
    BSP_OS_SemWait(&BSP_SerRxWait, 0);
    
    rx_byte = BSP_SerRxData;    

    DEF_BIT_CLR(BSP_SER_REG_U0_IER, DEF_BIT_00);
#endif

#if (BSP_CFG_SER_COMM_SEL == BSP_SER_COMM_UART_01)
    rx_byte = 0;
    
    DEF_BIT_SET(BSP_SER_REG_U1_IER, DEF_BIT_00);
    
    BSP_OS_SemWait(&BSP_SerRxWait, 0);
    
    rx_byte = BSP_SerRxData;    

    DEF_BIT_CLR(BSP_SER_REG_U1_IER, DEF_BIT_00);
#endif
   
    return (rx_byte);    
}


/*
*********************************************************************************************************
*                                              BSP_SerRdStr()
*
* Description : This function reads a string from a UART.
*
* Argument(s) : p_str      A pointer to a buffer at which the string can be stored.
*
*               len         The size of the string that will be read.
*
* Return(s)   : none.
*
* Caller(s)   : Application
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  BSP_SerRdStr (CPU_CHAR   *p_str,
                    CPU_INT16U  len)
{
    CPU_CHAR     rx_data;
    CPU_CHAR     rx_buf_ix;
    CPU_BOOLEAN  err;


    rx_buf_ix = 0;
    p_str[0]  = 0;

    err = BSP_OS_SemWait(&BSP_SerLock, 0);                      /* Obtain access to the serial interface              */
    
    if (err != DEF_OK ) {
        return;
    }

    while (DEF_TRUE)
    {        
        rx_data = BSP_SerRdByteUnlocked();
        
        if ((rx_data == ASCII_CHAR_CARRIAGE_RETURN) ||          /* Is it '\r' or '\n' character  ?                    */
            (rx_data == ASCII_CHAR_LINE_FEED      )) {
                          
            BSP_SerWrByteUnlocked((CPU_INT08U)ASCII_CHAR_LINE_FEED);
            BSP_SerWrByteUnlocked((CPU_INT08U)ASCII_CHAR_CARRIAGE_RETURN);

            p_str[rx_buf_ix] = 0;                              /* set the null character at the end of the string     */
            break;                                             /* exit the loop                                       */
        }

        if (rx_data == ASCII_CHAR_BACKSPACE) {                 /* Is backspace character                              */
            if (rx_buf_ix > 0) {
                BSP_SerWrByteUnlocked((CPU_INT08U)ASCII_CHAR_BACKSPACE);
                BSP_SerWrByteUnlocked((CPU_INT08U)ASCII_CHAR_SPACE);
                BSP_SerWrByteUnlocked((CPU_INT08U)ASCII_CHAR_BACKSPACE);
                
                rx_buf_ix--;                                   /* Decrement the index                                 */
                p_str[rx_buf_ix] = 0;
            }
        }

        if (ASCII_IsPrint(rx_data)) {                           /* Is it a printable character ... ?                  */
            BSP_SerWrByteUnlocked((CPU_INT08U)rx_data);         /* Echo-back                                          */
            p_str[rx_buf_ix] = rx_data;                         /* Save the received character in the buffer          */
            rx_buf_ix++;                                        /* Increment the buffer index                         */
            if (rx_buf_ix >= len) {
               rx_buf_ix = len;
            }
        }
    }
    
    BSP_OS_SemPost(&BSP_SerLock);                               /* Release access to the serial interface            */
}
