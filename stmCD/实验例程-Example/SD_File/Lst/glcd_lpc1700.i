#line 1 "GLCD_LPC1700.c"
 
 
 
 
 
 
 
 
 
 


#line 1 "d:\\Keil\\ARM\\INC\\NXP\\LPC17xx\\lpc17xx.h"




















 









 

typedef enum IRQn
{
 
  NonMaskableInt_IRQn           = -14,       
  MemoryManagement_IRQn         = -12,       
  BusFault_IRQn                 = -11,       
  UsageFault_IRQn               = -10,       
  SVCall_IRQn                   = -5,        
  DebugMonitor_IRQn             = -4,        
  PendSV_IRQn                   = -2,        
  SysTick_IRQn                  = -1,        

 
  WDT_IRQn                      = 0,         
  TIMER0_IRQn                   = 1,         
  TIMER1_IRQn                   = 2,         
  TIMER2_IRQn                   = 3,         
  TIMER3_IRQn                   = 4,         
  UART0_IRQn                    = 5,         
  UART1_IRQn                    = 6,         
  UART2_IRQn                    = 7,         
  UART3_IRQn                    = 8,         
  PWM1_IRQn                     = 9,         
  I2C0_IRQn                     = 10,        
  I2C1_IRQn                     = 11,        
  I2C2_IRQn                     = 12,        
  SPI_IRQn                      = 13,        
  SSP0_IRQn                     = 14,        
  SSP1_IRQn                     = 15,        
  PLL0_IRQn                     = 16,        
  RTC_IRQn                      = 17,        
  EINT0_IRQn                    = 18,        
  EINT1_IRQn                    = 19,        
  EINT2_IRQn                    = 20,        
  EINT3_IRQn                    = 21,        
  ADC_IRQn                      = 22,        
  BOD_IRQn                      = 23,        
  USB_IRQn                      = 24,        
  CAN_IRQn                      = 25,        
  DMA_IRQn                      = 26,        
  I2S_IRQn                      = 27,        
  ENET_IRQn                     = 28,        
  RIT_IRQn                      = 29,        
  MCPWM_IRQn                    = 30,        
  QEI_IRQn                      = 31,        
  PLL1_IRQn                     = 32,        
  USBActivity_IRQn              = 33,        
  CANActivity_IRQn              = 34,        
} IRQn_Type;






 

 





#line 1 "d:\\Keil\\ARM\\RV31\\INC\\core_cm3.h"
 




















 





































 

 
 
 
 
 
 
 
 








 











#line 1 "d:\\Keil\\ARM\\RV31\\INC\\stdint.h"
 
 





 









#line 25 "d:\\Keil\\ARM\\RV31\\INC\\stdint.h"







 

     

     
typedef   signed          char int8_t;
typedef   signed short     int int16_t;
typedef   signed           int int32_t;
typedef   signed       __int64 int64_t;

     
typedef unsigned          char uint8_t;
typedef unsigned short     int uint16_t;
typedef unsigned           int uint32_t;
typedef unsigned       __int64 uint64_t;

     

     
     
typedef   signed          char int_least8_t;
typedef   signed short     int int_least16_t;
typedef   signed           int int_least32_t;
typedef   signed       __int64 int_least64_t;

     
typedef unsigned          char uint_least8_t;
typedef unsigned short     int uint_least16_t;
typedef unsigned           int uint_least32_t;
typedef unsigned       __int64 uint_least64_t;

     

     
typedef   signed           int int_fast8_t;
typedef   signed           int int_fast16_t;
typedef   signed           int int_fast32_t;
typedef   signed       __int64 int_fast64_t;

     
typedef unsigned           int uint_fast8_t;
typedef unsigned           int uint_fast16_t;
typedef unsigned           int uint_fast32_t;
typedef unsigned       __int64 uint_fast64_t;

     
typedef   signed           int intptr_t;
typedef unsigned           int uintptr_t;

     
typedef   signed       __int64 intmax_t;
typedef unsigned       __int64 uintmax_t;




     

     





     





     





     

     





     





     





     

     





     





     





     

     


     


     


     

     


     


     


     

     



     



     


     
    
 



#line 196 "d:\\Keil\\ARM\\RV31\\INC\\stdint.h"

     







     










     











#line 260 "d:\\Keil\\ARM\\RV31\\INC\\stdint.h"



 


#line 91 "d:\\Keil\\ARM\\RV31\\INC\\core_cm3.h"

















 

#line 117 "d:\\Keil\\ARM\\RV31\\INC\\core_cm3.h"





 


 





 
typedef struct
{
  volatile uint32_t ISER[8];                       
       uint32_t RESERVED0[24];                                   
  volatile uint32_t ICER[8];                       
       uint32_t RSERVED1[24];                                    
  volatile uint32_t ISPR[8];                       
       uint32_t RESERVED2[24];                                   
  volatile uint32_t ICPR[8];                       
       uint32_t RESERVED3[24];                                   
  volatile uint32_t IABR[8];                       
       uint32_t RESERVED4[56];                                   
  volatile uint8_t  IP[240];                       
       uint32_t RESERVED5[644];                                  
  volatile  uint32_t STIR;                          
}  NVIC_Type;                                               
   





 
typedef struct
{
  volatile const  uint32_t CPUID;                         
  volatile uint32_t ICSR;                          
  volatile uint32_t VTOR;                          
  volatile uint32_t AIRCR;                         
  volatile uint32_t SCR;                           
  volatile uint32_t CCR;                           
  volatile uint8_t  SHP[12];                       
  volatile uint32_t SHCSR;                         
  volatile uint32_t CFSR;                          
  volatile uint32_t HFSR;                          
  volatile uint32_t DFSR;                          
  volatile uint32_t MMFAR;                         
  volatile uint32_t BFAR;                          
  volatile uint32_t AFSR;                          
  volatile const  uint32_t PFR[2];                        
  volatile const  uint32_t DFR;                           
  volatile const  uint32_t ADR;                           
  volatile const  uint32_t MMFR[4];                       
  volatile const  uint32_t ISAR[5];                       
} SCB_Type;                                                

 












 






























 






 





















 









 


















 
































                                     









 









 









 














   





 
typedef struct
{
  volatile uint32_t CTRL;                          
  volatile uint32_t LOAD;                          
  volatile uint32_t VAL;                           
  volatile const  uint32_t CALIB;                         
} SysTick_Type;

 












 



 



 








   





 
typedef struct
{
  volatile  union  
  {
    volatile  uint8_t    u8;                        
    volatile  uint16_t   u16;                       
    volatile  uint32_t   u32;                       
  }  PORT [32];                                
       uint32_t RESERVED0[864];                                 
  volatile uint32_t TER;                           
       uint32_t RESERVED1[15];                                  
  volatile uint32_t TPR;                           
       uint32_t RESERVED2[15];                                  
  volatile uint32_t TCR;                           
       uint32_t RESERVED3[29];                                  
  volatile uint32_t IWR;                           
  volatile uint32_t IRR;                           
  volatile uint32_t IMCR;                          
       uint32_t RESERVED4[43];                                  
  volatile uint32_t LAR;                           
  volatile uint32_t LSR;                           
       uint32_t RESERVED5[6];                                   
  volatile const  uint32_t PID4;                          
  volatile const  uint32_t PID5;                          
  volatile const  uint32_t PID6;                          
  volatile const  uint32_t PID7;                          
  volatile const  uint32_t PID0;                          
  volatile const  uint32_t PID1;                          
  volatile const  uint32_t PID2;                          
  volatile const  uint32_t PID3;                          
  volatile const  uint32_t CID0;                          
  volatile const  uint32_t CID1;                          
  volatile const  uint32_t CID2;                          
  volatile const  uint32_t CID3;                          
} ITM_Type;                                                

 



 
























 



 



 



 








   





 
typedef struct
{
       uint32_t RESERVED0;
  volatile const  uint32_t ICTR;                          



       uint32_t RESERVED1;

} InterruptType_Type;

 



 








   






 
typedef struct
{
  volatile const  uint32_t TYPE;                          
  volatile uint32_t CTRL;                          
  volatile uint32_t RNR;                           
  volatile uint32_t RBAR;                          
  volatile uint32_t RASR;                          
  volatile uint32_t RBAR_A1;                       
  volatile uint32_t RASR_A1;                       
  volatile uint32_t RBAR_A2;                       
  volatile uint32_t RASR_A2;                       
  volatile uint32_t RBAR_A3;                       
  volatile uint32_t RASR_A3;                       
} MPU_Type;                                                

 









 









 



 









 



























   






 
typedef struct
{
  volatile uint32_t DHCSR;                         
  volatile  uint32_t DCRSR;                         
  volatile uint32_t DCRDR;                         
  volatile uint32_t DEMCR;                         
} CoreDebug_Type;

 




































 






 






































   


 
#line 721 "d:\\Keil\\ARM\\RV31\\INC\\core_cm3.h"

#line 728 "d:\\Keil\\ARM\\RV31\\INC\\core_cm3.h"






   




 





#line 758 "d:\\Keil\\ARM\\RV31\\INC\\core_cm3.h"


 


 




#line 783 "d:\\Keil\\ARM\\RV31\\INC\\core_cm3.h"


 
 
 
 








 
extern uint32_t __get_PSP(void);








 
extern void __set_PSP(uint32_t topOfProcStack);








 
extern uint32_t __get_MSP(void);








 
extern void __set_MSP(uint32_t topOfMainStack);








 
extern uint32_t __REV16(uint16_t value);








 
extern int32_t __REVSH(int16_t value);


#line 933 "d:\\Keil\\ARM\\RV31\\INC\\core_cm3.h"





 








 
static __inline uint32_t  __get_BASEPRI(void)
{
  register uint32_t __regBasePri         __asm("basepri");
  return(__regBasePri);
}







 
static __inline void __set_BASEPRI(uint32_t basePri)
{
  register uint32_t __regBasePri         __asm("basepri");
  __regBasePri = (basePri & 0xff);
}







 
static __inline uint32_t __get_PRIMASK(void)
{
  register uint32_t __regPriMask         __asm("primask");
  return(__regPriMask);
}







 
static __inline void __set_PRIMASK(uint32_t priMask)
{
  register uint32_t __regPriMask         __asm("primask");
  __regPriMask = (priMask);
}







 
static __inline uint32_t __get_FAULTMASK(void)
{
  register uint32_t __regFaultMask       __asm("faultmask");
  return(__regFaultMask);
}







 
static __inline void __set_FAULTMASK(uint32_t faultMask)
{
  register uint32_t __regFaultMask       __asm("faultmask");
  __regFaultMask = (faultMask & 1);
}







 
static __inline uint32_t __get_CONTROL(void)
{
  register uint32_t __regControl         __asm("control");
  return(__regControl);
}







 
static __inline void __set_CONTROL(uint32_t control)
{
  register uint32_t __regControl         __asm("control");
  __regControl = control;
}





#line 1445 "d:\\Keil\\ARM\\RV31\\INC\\core_cm3.h"







 
 

 











 
static __inline void NVIC_SetPriorityGrouping(uint32_t PriorityGroup)
{
  uint32_t reg_value;
  uint32_t PriorityGroupTmp = (PriorityGroup & 0x07);                          
  
  reg_value  =  ((SCB_Type *) ((0xE000E000) + 0x0D00))->AIRCR;                                                    
  reg_value &= ~((0xFFFFul << 16) | (7ul << 8));              
  reg_value  =  (reg_value                       |
                (0x5FA << 16) | 
                (PriorityGroupTmp << 8));                                      
  ((SCB_Type *) ((0xE000E000) + 0x0D00))->AIRCR =  reg_value;
}








 
static __inline uint32_t NVIC_GetPriorityGrouping(void)
{
  return ((((SCB_Type *) ((0xE000E000) + 0x0D00))->AIRCR & (7ul << 8)) >> 8);    
}








 
static __inline void NVIC_EnableIRQ(IRQn_Type IRQn)
{
  ((NVIC_Type *) ((0xE000E000) + 0x0100))->ISER[((uint32_t)(IRQn) >> 5)] = (1 << ((uint32_t)(IRQn) & 0x1F));  
}








 
static __inline void NVIC_DisableIRQ(IRQn_Type IRQn)
{
  ((NVIC_Type *) ((0xE000E000) + 0x0100))->ICER[((uint32_t)(IRQn) >> 5)] = (1 << ((uint32_t)(IRQn) & 0x1F));  
}









 
static __inline uint32_t NVIC_GetPendingIRQ(IRQn_Type IRQn)
{
  return((uint32_t) ((((NVIC_Type *) ((0xE000E000) + 0x0100))->ISPR[(uint32_t)(IRQn) >> 5] & (1 << ((uint32_t)(IRQn) & 0x1F)))?1:0));  
}








 
static __inline void NVIC_SetPendingIRQ(IRQn_Type IRQn)
{
  ((NVIC_Type *) ((0xE000E000) + 0x0100))->ISPR[((uint32_t)(IRQn) >> 5)] = (1 << ((uint32_t)(IRQn) & 0x1F));  
}








 
static __inline void NVIC_ClearPendingIRQ(IRQn_Type IRQn)
{
  ((NVIC_Type *) ((0xE000E000) + 0x0100))->ICPR[((uint32_t)(IRQn) >> 5)] = (1 << ((uint32_t)(IRQn) & 0x1F));  
}









 
static __inline uint32_t NVIC_GetActive(IRQn_Type IRQn)
{
  return((uint32_t)((((NVIC_Type *) ((0xE000E000) + 0x0100))->IABR[(uint32_t)(IRQn) >> 5] & (1 << ((uint32_t)(IRQn) & 0x1F)))?1:0));  
}












 
static __inline void NVIC_SetPriority(IRQn_Type IRQn, uint32_t priority)
{
  if(IRQn < 0) {
    ((SCB_Type *) ((0xE000E000) + 0x0D00))->SHP[((uint32_t)(IRQn) & 0xF)-4] = ((priority << (8 - 5)) & 0xff); }  
  else {
    ((NVIC_Type *) ((0xE000E000) + 0x0100))->IP[(uint32_t)(IRQn)] = ((priority << (8 - 5)) & 0xff);    }         
}















 
static __inline uint32_t NVIC_GetPriority(IRQn_Type IRQn)
{

  if(IRQn < 0) {
    return((uint32_t)(((SCB_Type *) ((0xE000E000) + 0x0D00))->SHP[((uint32_t)(IRQn) & 0xF)-4] >> (8 - 5)));  }  
  else {
    return((uint32_t)(((NVIC_Type *) ((0xE000E000) + 0x0100))->IP[(uint32_t)(IRQn)]           >> (8 - 5)));  }  
}
















 
static __inline uint32_t NVIC_EncodePriority (uint32_t PriorityGroup, uint32_t PreemptPriority, uint32_t SubPriority)
{
  uint32_t PriorityGroupTmp = (PriorityGroup & 0x07);           
  uint32_t PreemptPriorityBits;
  uint32_t SubPriorityBits;

  PreemptPriorityBits = ((7 - PriorityGroupTmp) > 5) ? 5 : 7 - PriorityGroupTmp;
  SubPriorityBits     = ((PriorityGroupTmp + 5) < 7) ? 0 : PriorityGroupTmp - 7 + 5;
 
  return (
           ((PreemptPriority & ((1 << (PreemptPriorityBits)) - 1)) << SubPriorityBits) |
           ((SubPriority     & ((1 << (SubPriorityBits    )) - 1)))
         );
}
















 
static __inline void NVIC_DecodePriority (uint32_t Priority, uint32_t PriorityGroup, uint32_t* pPreemptPriority, uint32_t* pSubPriority)
{
  uint32_t PriorityGroupTmp = (PriorityGroup & 0x07);           
  uint32_t PreemptPriorityBits;
  uint32_t SubPriorityBits;

  PreemptPriorityBits = ((7 - PriorityGroupTmp) > 5) ? 5 : 7 - PriorityGroupTmp;
  SubPriorityBits     = ((PriorityGroupTmp + 5) < 7) ? 0 : PriorityGroupTmp - 7 + 5;
  
  *pPreemptPriority = (Priority >> SubPriorityBits) & ((1 << (PreemptPriorityBits)) - 1);
  *pSubPriority     = (Priority                   ) & ((1 << (SubPriorityBits    )) - 1);
}



 












 
static __inline uint32_t SysTick_Config(uint32_t ticks)
{ 
  if (ticks > (0xFFFFFFul << 0))  return (1);             
                                                               
  ((SysTick_Type *) ((0xE000E000) + 0x0010))->LOAD  = (ticks & (0xFFFFFFul << 0)) - 1;       
  NVIC_SetPriority (SysTick_IRQn, (1<<5) - 1);   
  ((SysTick_Type *) ((0xE000E000) + 0x0010))->VAL   = 0;                                           
  ((SysTick_Type *) ((0xE000E000) + 0x0010))->CTRL  = (1ul << 2) | 
                   (1ul << 1)   | 
                   (1ul << 0);                     
  return (0);                                                   
}






 





 
static __inline void NVIC_SystemReset(void)
{
  ((SCB_Type *) ((0xE000E000) + 0x0D00))->AIRCR  = ((0x5FA << 16)      | 
                 (((SCB_Type *) ((0xE000E000) + 0x0D00))->AIRCR & (7ul << 8)) | 
                 (1ul << 2));                    
  __dsb(0);                                                                    
  while(1);                                                     
}

   



 






 
 

extern volatile int ITM_RxBuffer;                     












 
static __inline uint32_t ITM_SendChar (uint32_t ch)
{
  if ((((CoreDebug_Type *) (0xE000EDF0))->DEMCR & (1ul << 24))  &&       
      (((ITM_Type *) (0xE0000000))->TCR & (1ul << 0))                  &&       
      (((ITM_Type *) (0xE0000000))->TER & (1ul << 0)        )                    )      
  {
    while (((ITM_Type *) (0xE0000000))->PORT[0].u32 == 0);
    ((ITM_Type *) (0xE0000000))->PORT[0].u8 = (uint8_t) ch;
  }  
  return (ch);
}










 
static __inline int ITM_ReceiveChar (void) {
  int ch = -1;                                

  if (ITM_RxBuffer != 0x5AA55AA5) {
    ch = ITM_RxBuffer;
    ITM_RxBuffer = 0x5AA55AA5;        
  }
  
  return (ch); 
}









 
static __inline int ITM_CheckChar (void) {

  if (ITM_RxBuffer == 0x5AA55AA5) {
    return (0);                                  
  } else {
    return (1);                                  
  }
}

   






   



 
#line 97 "d:\\Keil\\ARM\\INC\\NXP\\LPC17xx\\lpc17xx.h"
#line 1 "d:\\Keil\\ARM\\INC\\NXP\\LPC17xx\\system_LPC17xx.h"




















 









extern uint32_t SystemFrequency;     










 
extern void SystemInit (void);





#line 98 "d:\\Keil\\ARM\\INC\\NXP\\LPC17xx\\lpc17xx.h"


 
 
 


#pragma anon_unions


 
typedef struct
{
  volatile uint32_t FLASHCFG;                
       uint32_t RESERVED0[31];
  volatile uint32_t PLL0CON;                 
  volatile uint32_t PLL0CFG;
  volatile const  uint32_t PLL0STAT;
  volatile  uint32_t PLL0FEED;
       uint32_t RESERVED1[4];
  volatile uint32_t PLL1CON;
  volatile uint32_t PLL1CFG;
  volatile const  uint32_t PLL1STAT;
  volatile  uint32_t PLL1FEED;
       uint32_t RESERVED2[4];
  volatile uint32_t PCON;
  volatile uint32_t PCONP;
       uint32_t RESERVED3[15];
  volatile uint32_t CCLKCFG;
  volatile uint32_t USBCLKCFG;
  volatile uint32_t CLKSRCSEL;
  volatile uint32_t	CANSLEEPCLR;
  volatile uint32_t	CANWAKEFLAGS;
       uint32_t RESERVED4[10];
  volatile uint32_t EXTINT;                  
       uint32_t RESERVED5;
  volatile uint32_t EXTMODE;
  volatile uint32_t EXTPOLAR;
       uint32_t RESERVED6[12];
  volatile uint32_t RSID;                    
       uint32_t RESERVED7[7];
  volatile uint32_t SCS;                     
  volatile uint32_t IRCTRIM;                 
  volatile uint32_t PCLKSEL0;
  volatile uint32_t PCLKSEL1;
       uint32_t RESERVED8[4];
  volatile uint32_t USBIntSt;                
  volatile uint32_t DMAREQSEL;
  volatile uint32_t CLKOUTCFG;               
 } LPC_SC_TypeDef;

 
typedef struct
{
  volatile uint32_t PINSEL0;
  volatile uint32_t PINSEL1;
  volatile uint32_t PINSEL2;
  volatile uint32_t PINSEL3;
  volatile uint32_t PINSEL4;
  volatile uint32_t PINSEL5;
  volatile uint32_t PINSEL6;
  volatile uint32_t PINSEL7;
  volatile uint32_t PINSEL8;
  volatile uint32_t PINSEL9;
  volatile uint32_t PINSEL10;
       uint32_t RESERVED0[5];
  volatile uint32_t PINMODE0;
  volatile uint32_t PINMODE1;
  volatile uint32_t PINMODE2;
  volatile uint32_t PINMODE3;
  volatile uint32_t PINMODE4;
  volatile uint32_t PINMODE5;
  volatile uint32_t PINMODE6;
  volatile uint32_t PINMODE7;
  volatile uint32_t PINMODE8;
  volatile uint32_t PINMODE9;
  volatile uint32_t PINMODE_OD0;
  volatile uint32_t PINMODE_OD1;
  volatile uint32_t PINMODE_OD2;
  volatile uint32_t PINMODE_OD3;
  volatile uint32_t PINMODE_OD4;
  volatile uint32_t I2CPADCFG;
} LPC_PINCON_TypeDef;

 
typedef struct
{
  union {
    volatile uint32_t FIODIR;
    struct {
      volatile uint16_t FIODIRL;
      volatile uint16_t FIODIRH;
    };
    struct {
      volatile uint8_t  FIODIR0;
      volatile uint8_t  FIODIR1;
      volatile uint8_t  FIODIR2;
      volatile uint8_t  FIODIR3;
    };
  };
  uint32_t RESERVED0[3];
  union {
    volatile uint32_t FIOMASK;
    struct {
      volatile uint16_t FIOMASKL;
      volatile uint16_t FIOMASKH;
    };
    struct {
      volatile uint8_t  FIOMASK0;
      volatile uint8_t  FIOMASK1;
      volatile uint8_t  FIOMASK2;
      volatile uint8_t  FIOMASK3;
    };
  };
  union {
    volatile uint32_t FIOPIN;
    struct {
      volatile uint16_t FIOPINL;
      volatile uint16_t FIOPINH;
    };
    struct {
      volatile uint8_t  FIOPIN0;
      volatile uint8_t  FIOPIN1;
      volatile uint8_t  FIOPIN2;
      volatile uint8_t  FIOPIN3;
    };
  };
  union {
    volatile uint32_t FIOSET;
    struct {
      volatile uint16_t FIOSETL;
      volatile uint16_t FIOSETH;
    };
    struct {
      volatile uint8_t  FIOSET0;
      volatile uint8_t  FIOSET1;
      volatile uint8_t  FIOSET2;
      volatile uint8_t  FIOSET3;
    };
  };
  union {
    volatile  uint32_t FIOCLR;
    struct {
      volatile  uint16_t FIOCLRL;
      volatile  uint16_t FIOCLRH;
    };
    struct {
      volatile  uint8_t  FIOCLR0;
      volatile  uint8_t  FIOCLR1;
      volatile  uint8_t  FIOCLR2;
      volatile  uint8_t  FIOCLR3;
    };
  };
} LPC_GPIO_TypeDef;

typedef struct
{
  volatile const  uint32_t IntStatus;
  volatile const  uint32_t IO0IntStatR;
  volatile const  uint32_t IO0IntStatF;
  volatile  uint32_t IO0IntClr;
  volatile uint32_t IO0IntEnR;
  volatile uint32_t IO0IntEnF;
       uint32_t RESERVED0[3];
  volatile const  uint32_t IO2IntStatR;
  volatile const  uint32_t IO2IntStatF;
  volatile  uint32_t IO2IntClr;
  volatile uint32_t IO2IntEnR;
  volatile uint32_t IO2IntEnF;
} LPC_GPIOINT_TypeDef;

 
typedef struct
{
  volatile uint32_t IR;
  volatile uint32_t TCR;
  volatile uint32_t TC;
  volatile uint32_t PR;
  volatile uint32_t PC;
  volatile uint32_t MCR;
  volatile uint32_t MR0;
  volatile uint32_t MR1;
  volatile uint32_t MR2;
  volatile uint32_t MR3;
  volatile uint32_t CCR;
  volatile const  uint32_t CR0;
  volatile const  uint32_t CR1;
       uint32_t RESERVED0[2];
  volatile uint32_t EMR;
       uint32_t RESERVED1[12];
  volatile uint32_t CTCR;
} LPC_TIM_TypeDef;

 
typedef struct
{
  volatile uint32_t IR;
  volatile uint32_t TCR;
  volatile uint32_t TC;
  volatile uint32_t PR;
  volatile uint32_t PC;
  volatile uint32_t MCR;
  volatile uint32_t MR0;
  volatile uint32_t MR1;
  volatile uint32_t MR2;
  volatile uint32_t MR3;
  volatile uint32_t CCR;
  volatile const  uint32_t CR0;
  volatile const  uint32_t CR1;
  volatile const  uint32_t CR2;
  volatile const  uint32_t CR3;
       uint32_t RESERVED0;
  volatile uint32_t MR4;
  volatile uint32_t MR5;
  volatile uint32_t MR6;
  volatile uint32_t PCR;
  volatile uint32_t LER;
       uint32_t RESERVED1[7];
  volatile uint32_t CTCR;
} LPC_PWM_TypeDef;

 
typedef struct
{
  union {
  volatile const  uint8_t  RBR;
  volatile  uint8_t  THR;
  volatile uint8_t  DLL;
       uint32_t RESERVED0;
  };
  union {
  volatile uint8_t  DLM;
  volatile uint32_t IER;
  };
  union {
  volatile const  uint32_t IIR;
  volatile  uint8_t  FCR;
  };
  volatile uint8_t  LCR;
       uint8_t  RESERVED1[7];
  volatile const  uint8_t  LSR;
       uint8_t  RESERVED2[7];
  volatile uint8_t  SCR;
       uint8_t  RESERVED3[3];
  volatile uint32_t ACR;
  volatile uint8_t  ICR;
       uint8_t  RESERVED4[3];
  volatile uint8_t  FDR;
       uint8_t  RESERVED5[7];
  volatile uint8_t  TER;
       uint8_t  RESERVED6[39];
  volatile uint32_t FIFOLVL;
} LPC_UART_TypeDef;

typedef struct
{
  union {
  volatile const  uint8_t  RBR;
  volatile  uint8_t  THR;
  volatile uint8_t  DLL;
       uint32_t RESERVED0;
  };
  union {
  volatile uint8_t  DLM;
  volatile uint32_t IER;
  };
  union {
  volatile const  uint32_t IIR;
  volatile  uint8_t  FCR;
  };
  volatile uint8_t  LCR;
       uint8_t  RESERVED1[7];
  volatile const  uint8_t  LSR;
       uint8_t  RESERVED2[7];
  volatile uint8_t  SCR;
       uint8_t  RESERVED3[3];
  volatile uint32_t ACR;
  volatile uint8_t  ICR;
       uint8_t  RESERVED4[3];
  volatile uint8_t  FDR;
       uint8_t  RESERVED5[7];
  volatile uint8_t  TER;
       uint8_t  RESERVED6[39];
  volatile uint32_t FIFOLVL;
} LPC_UART0_TypeDef;

typedef struct
{
  union {
  volatile const  uint8_t  RBR;
  volatile  uint8_t  THR;
  volatile uint8_t  DLL;
       uint32_t RESERVED0;
  };
  union {
  volatile uint8_t  DLM;
  volatile uint32_t IER;
  };
  union {
  volatile const  uint32_t IIR;
  volatile  uint8_t  FCR;
  };
  volatile uint8_t  LCR;
       uint8_t  RESERVED1[3];
  volatile uint8_t  MCR;
       uint8_t  RESERVED2[3];
  volatile const  uint8_t  LSR;
       uint8_t  RESERVED3[3];
  volatile const  uint8_t  MSR;
       uint8_t  RESERVED4[3];
  volatile uint8_t  SCR;
       uint8_t  RESERVED5[3];
  volatile uint32_t ACR;
       uint32_t RESERVED6;
  volatile uint32_t FDR;
       uint32_t RESERVED7;
  volatile uint8_t  TER;
       uint8_t  RESERVED8[27];
  volatile uint8_t  RS485CTRL;
       uint8_t  RESERVED9[3];
  volatile uint8_t  ADRMATCH;
       uint8_t  RESERVED10[3];
  volatile uint8_t  RS485DLY;
       uint8_t  RESERVED11[3];
  volatile uint32_t FIFOLVL;
} LPC_UART1_TypeDef;

 
typedef struct
{
  volatile uint32_t SPCR;
  volatile const  uint32_t SPSR;
  volatile uint32_t SPDR;
  volatile uint32_t SPCCR;
       uint32_t RESERVED0[3];
  volatile uint32_t SPINT;
} LPC_SPI_TypeDef;

 
typedef struct
{
  volatile uint32_t CR0;
  volatile uint32_t CR1;
  volatile uint32_t DR;
  volatile const  uint32_t SR;
  volatile uint32_t CPSR;
  volatile uint32_t IMSC;
  volatile uint32_t RIS;
  volatile uint32_t MIS;
  volatile uint32_t ICR;
  volatile uint32_t DMACR;
} LPC_SSP_TypeDef;

 
typedef struct
{
  volatile uint32_t I2CONSET;
  volatile const  uint32_t I2STAT;
  volatile uint32_t I2DAT;
  volatile uint32_t I2ADR0;
  volatile uint32_t I2SCLH;
  volatile uint32_t I2SCLL;
  volatile  uint32_t I2CONCLR;
  volatile uint32_t MMCTRL;
  volatile uint32_t I2ADR1;
  volatile uint32_t I2ADR2;
  volatile uint32_t I2ADR3;
  volatile const  uint32_t I2DATA_BUFFER;
  volatile uint32_t I2MASK0;
  volatile uint32_t I2MASK1;
  volatile uint32_t I2MASK2;
  volatile uint32_t I2MASK3;
} LPC_I2C_TypeDef;

 
typedef struct
{
  volatile uint32_t I2SDAO;
  volatile uint32_t I2SDAI;
  volatile  uint32_t I2STXFIFO;
  volatile const  uint32_t I2SRXFIFO;
  volatile const  uint32_t I2SSTATE;
  volatile uint32_t I2SDMA1;
  volatile uint32_t I2SDMA2;
  volatile uint32_t I2SIRQ;
  volatile uint32_t I2STXRATE;
  volatile uint32_t I2SRXRATE;
  volatile uint32_t I2STXBITRATE;
  volatile uint32_t I2SRXBITRATE;
  volatile uint32_t I2STXMODE;
  volatile uint32_t I2SRXMODE;
} LPC_I2S_TypeDef;

 
typedef struct
{
  volatile uint32_t RICOMPVAL;
  volatile uint32_t RIMASK;
  volatile uint8_t  RICTRL;
       uint8_t  RESERVED0[3];
  volatile uint32_t RICOUNTER;
} LPC_RIT_TypeDef;

 
typedef struct
{
  volatile uint8_t  ILR;
       uint8_t  RESERVED0[7];
  volatile uint8_t  CCR;
       uint8_t  RESERVED1[3];
  volatile uint8_t  CIIR;
       uint8_t  RESERVED2[3];
  volatile uint8_t  AMR;
       uint8_t  RESERVED3[3];
  volatile const  uint32_t CTIME0;
  volatile const  uint32_t CTIME1;
  volatile const  uint32_t CTIME2;
  volatile uint8_t  SEC;
       uint8_t  RESERVED4[3];
  volatile uint8_t  MIN;
       uint8_t  RESERVED5[3];
  volatile uint8_t  HOUR;
       uint8_t  RESERVED6[3];
  volatile uint8_t  DOM;
       uint8_t  RESERVED7[3];
  volatile uint8_t  DOW;
       uint8_t  RESERVED8[3];
  volatile uint16_t DOY;
       uint16_t RESERVED9;
  volatile uint8_t  MONTH;
       uint8_t  RESERVED10[3];
  volatile uint16_t YEAR;
       uint16_t RESERVED11;
  volatile uint32_t CALIBRATION;
  volatile uint32_t GPREG0;
  volatile uint32_t GPREG1;
  volatile uint32_t GPREG2;
  volatile uint32_t GPREG3;
  volatile uint32_t GPREG4;
  volatile uint8_t  RTC_AUXEN;
       uint8_t  RESERVED12[3];
  volatile uint8_t  RTC_AUX;
       uint8_t  RESERVED13[3];
  volatile uint8_t  ALSEC;
       uint8_t  RESERVED14[3];
  volatile uint8_t  ALMIN;
       uint8_t  RESERVED15[3];
  volatile uint8_t  ALHOUR;
       uint8_t  RESERVED16[3];
  volatile uint8_t  ALDOM;
       uint8_t  RESERVED17[3];
  volatile uint8_t  ALDOW;
       uint8_t  RESERVED18[3];
  volatile uint16_t ALDOY;
       uint16_t RESERVED19;
  volatile uint8_t  ALMON;
       uint8_t  RESERVED20[3];
  volatile uint16_t ALYEAR;
       uint16_t RESERVED21;
} LPC_RTC_TypeDef;

 
typedef struct
{
  volatile uint8_t  WDMOD;
       uint8_t  RESERVED0[3];
  volatile uint32_t WDTC;
  volatile  uint8_t  WDFEED;
       uint8_t  RESERVED1[3];
  volatile const  uint32_t WDTV;
  volatile uint32_t WDCLKSEL;
} LPC_WDT_TypeDef;

 
typedef struct
{
  volatile uint32_t ADCR;
  volatile uint32_t ADGDR;
       uint32_t RESERVED0;
  volatile uint32_t ADINTEN;
  volatile const  uint32_t ADDR0;
  volatile const  uint32_t ADDR1;
  volatile const  uint32_t ADDR2;
  volatile const  uint32_t ADDR3;
  volatile const  uint32_t ADDR4;
  volatile const  uint32_t ADDR5;
  volatile const  uint32_t ADDR6;
  volatile const  uint32_t ADDR7;
  volatile const  uint32_t ADSTAT;
  volatile uint32_t ADTRM;
} LPC_ADC_TypeDef;

 
typedef struct
{
  volatile uint32_t DACR;
  volatile uint32_t DACCTRL;
  volatile uint16_t DACCNTVAL;
} LPC_DAC_TypeDef;

 
typedef struct
{
  volatile const  uint32_t MCCON;
  volatile  uint32_t MCCON_SET;
  volatile  uint32_t MCCON_CLR;
  volatile const  uint32_t MCCAPCON;
  volatile  uint32_t MCCAPCON_SET;
  volatile  uint32_t MCCAPCON_CLR;
  volatile uint32_t MCTIM0;
  volatile uint32_t MCTIM1;
  volatile uint32_t MCTIM2;
  volatile uint32_t MCPER0;
  volatile uint32_t MCPER1;
  volatile uint32_t MCPER2;
  volatile uint32_t MCPW0;
  volatile uint32_t MCPW1;
  volatile uint32_t MCPW2;
  volatile uint32_t MCDEADTIME;
  volatile uint32_t MCCCP;
  volatile uint32_t MCCR0;
  volatile uint32_t MCCR1;
  volatile uint32_t MCCR2;
  volatile const  uint32_t MCINTEN;
  volatile  uint32_t MCINTEN_SET;
  volatile  uint32_t MCINTEN_CLR;
  volatile const  uint32_t MCCNTCON;
  volatile  uint32_t MCCNTCON_SET;
  volatile  uint32_t MCCNTCON_CLR;
  volatile const  uint32_t MCINTFLAG;
  volatile  uint32_t MCINTFLAG_SET;
  volatile  uint32_t MCINTFLAG_CLR;
  volatile  uint32_t MCCAP_CLR;
} LPC_MCPWM_TypeDef;

 
typedef struct
{
  volatile  uint32_t QEICON;
  volatile const  uint32_t QEISTAT;
  volatile uint32_t QEICONF;
  volatile const  uint32_t QEIPOS;
  volatile uint32_t QEIMAXPOS;
  volatile uint32_t CMPOS0;
  volatile uint32_t CMPOS1;
  volatile uint32_t CMPOS2;
  volatile const  uint32_t INXCNT;
  volatile uint32_t INXCMP;
  volatile uint32_t QEILOAD;
  volatile const  uint32_t QEITIME;
  volatile const  uint32_t QEIVEL;
  volatile const  uint32_t QEICAP;
  volatile uint32_t VELCOMP;
  volatile uint32_t FILTER;
       uint32_t RESERVED0[998];
  volatile  uint32_t QEIIEC;
  volatile  uint32_t QEIIES;
  volatile const  uint32_t QEIINTSTAT;
  volatile const  uint32_t QEIIE;
  volatile  uint32_t QEICLR;
  volatile  uint32_t QEISET;
} LPC_QEI_TypeDef;

 
typedef struct
{
  volatile uint32_t mask[512];               
} LPC_CANAF_RAM_TypeDef;

typedef struct                           
{
  volatile uint32_t AFMR;
  volatile uint32_t SFF_sa;
  volatile uint32_t SFF_GRP_sa;
  volatile uint32_t EFF_sa;
  volatile uint32_t EFF_GRP_sa;
  volatile uint32_t ENDofTable;
  volatile const  uint32_t LUTerrAd;
  volatile const  uint32_t LUTerr;
  volatile uint32_t FCANIE;
  volatile uint32_t FCANIC0;
  volatile uint32_t FCANIC1;
} LPC_CANAF_TypeDef;

typedef struct                           
{
  volatile const  uint32_t CANTxSR;
  volatile const  uint32_t CANRxSR;
  volatile const  uint32_t CANMSR;
} LPC_CANCR_TypeDef;

typedef struct                           
{
  volatile uint32_t MOD;
  volatile  uint32_t CMR;
  volatile uint32_t GSR;
  volatile const  uint32_t ICR;
  volatile uint32_t IER;
  volatile uint32_t BTR;
  volatile uint32_t EWL;
  volatile const  uint32_t SR;
  volatile uint32_t RFS;
  volatile uint32_t RID;
  volatile uint32_t RDA;
  volatile uint32_t RDB;
  volatile uint32_t TFI1;
  volatile uint32_t TID1;
  volatile uint32_t TDA1;
  volatile uint32_t TDB1;
  volatile uint32_t TFI2;
  volatile uint32_t TID2;
  volatile uint32_t TDA2;
  volatile uint32_t TDB2;
  volatile uint32_t TFI3;
  volatile uint32_t TID3;
  volatile uint32_t TDA3;
  volatile uint32_t TDB3;
} LPC_CAN_TypeDef;

 
typedef struct                           
{
  volatile const  uint32_t DMACIntStat;
  volatile const  uint32_t DMACIntTCStat;
  volatile  uint32_t DMACIntTCClear;
  volatile const  uint32_t DMACIntErrStat;
  volatile  uint32_t DMACIntErrClr;
  volatile const  uint32_t DMACRawIntTCStat;
  volatile const  uint32_t DMACRawIntErrStat;
  volatile const  uint32_t DMACEnbldChns;
  volatile uint32_t DMACSoftBReq;
  volatile uint32_t DMACSoftSReq;
  volatile uint32_t DMACSoftLBReq;
  volatile uint32_t DMACSoftLSReq;
  volatile uint32_t DMACConfig;
  volatile uint32_t DMACSync;
} LPC_GPDMA_TypeDef;

typedef struct                           
{
  volatile uint32_t DMACCSrcAddr;
  volatile uint32_t DMACCDestAddr;
  volatile uint32_t DMACCLLI;
  volatile uint32_t DMACCControl;
  volatile uint32_t DMACCConfig;
} LPC_GPDMACH_TypeDef;

 
typedef struct
{
  volatile const  uint32_t HcRevision;              
  volatile uint32_t HcControl;
  volatile uint32_t HcCommandStatus;
  volatile uint32_t HcInterruptStatus;
  volatile uint32_t HcInterruptEnable;
  volatile uint32_t HcInterruptDisable;
  volatile uint32_t HcHCCA;
  volatile const  uint32_t HcPeriodCurrentED;
  volatile uint32_t HcControlHeadED;
  volatile uint32_t HcControlCurrentED;
  volatile uint32_t HcBulkHeadED;
  volatile uint32_t HcBulkCurrentED;
  volatile const  uint32_t HcDoneHead;
  volatile uint32_t HcFmInterval;
  volatile const  uint32_t HcFmRemaining;
  volatile const  uint32_t HcFmNumber;
  volatile uint32_t HcPeriodicStart;
  volatile uint32_t HcLSTreshold;
  volatile uint32_t HcRhDescriptorA;
  volatile uint32_t HcRhDescriptorB;
  volatile uint32_t HcRhStatus;
  volatile uint32_t HcRhPortStatus1;
  volatile uint32_t HcRhPortStatus2;
       uint32_t RESERVED0[40];
  volatile const  uint32_t Module_ID;

  volatile const  uint32_t OTGIntSt;                
  volatile uint32_t OTGIntEn;
  volatile  uint32_t OTGIntSet;
  volatile  uint32_t OTGIntClr;
  volatile uint32_t OTGStCtrl;
  volatile uint32_t OTGTmr;
       uint32_t RESERVED1[58];

  volatile const  uint32_t USBDevIntSt;             
  volatile uint32_t USBDevIntEn;
  volatile  uint32_t USBDevIntClr;
  volatile  uint32_t USBDevIntSet;

  volatile  uint32_t USBCmdCode;              
  volatile const  uint32_t USBCmdData;

  volatile const  uint32_t USBRxData;               
  volatile  uint32_t USBTxData;
  volatile const  uint32_t USBRxPLen;
  volatile  uint32_t USBTxPLen;
  volatile uint32_t USBCtrl;
  volatile  uint32_t USBDevIntPri;

  volatile const  uint32_t USBEpIntSt;              
  volatile uint32_t USBEpIntEn;
  volatile  uint32_t USBEpIntClr;
  volatile  uint32_t USBEpIntSet;
  volatile  uint32_t USBEpIntPri;

  volatile uint32_t USBReEp;                 
  volatile  uint32_t USBEpInd;
  volatile uint32_t USBMaxPSize;

  volatile const  uint32_t USBDMARSt;               
  volatile  uint32_t USBDMARClr;
  volatile  uint32_t USBDMARSet;
       uint32_t RESERVED2[9];
  volatile uint32_t USBUDCAH;
  volatile const  uint32_t USBEpDMASt;
  volatile  uint32_t USBEpDMAEn;
  volatile  uint32_t USBEpDMADis;
  volatile const  uint32_t USBDMAIntSt;
  volatile uint32_t USBDMAIntEn;
       uint32_t RESERVED3[2];
  volatile const  uint32_t USBEoTIntSt;
  volatile  uint32_t USBEoTIntClr;
  volatile  uint32_t USBEoTIntSet;
  volatile const  uint32_t USBNDDRIntSt;
  volatile  uint32_t USBNDDRIntClr;
  volatile  uint32_t USBNDDRIntSet;
  volatile const  uint32_t USBSysErrIntSt;
  volatile  uint32_t USBSysErrIntClr;
  volatile  uint32_t USBSysErrIntSet;
       uint32_t RESERVED4[15];

  union {
  volatile const  uint32_t I2C_RX;                  
  volatile  uint32_t I2C_TX;
  };
  volatile const  uint32_t I2C_STS;
  volatile uint32_t I2C_CTL;
  volatile uint32_t I2C_CLKHI;
  volatile  uint32_t I2C_CLKLO;
       uint32_t RESERVED5[824];

  union {
  volatile uint32_t USBClkCtrl;              
  volatile uint32_t OTGClkCtrl;
  };
  union {
  volatile const  uint32_t USBClkSt;
  volatile const  uint32_t OTGClkSt;
  };
} LPC_USB_TypeDef;

 
typedef struct
{
  volatile uint32_t MAC1;                    
  volatile uint32_t MAC2;
  volatile uint32_t IPGT;
  volatile uint32_t IPGR;
  volatile uint32_t CLRT;
  volatile uint32_t MAXF;
  volatile uint32_t SUPP;
  volatile uint32_t TEST;
  volatile uint32_t MCFG;
  volatile uint32_t MCMD;
  volatile uint32_t MADR;
  volatile  uint32_t MWTD;
  volatile const  uint32_t MRDD;
  volatile const  uint32_t MIND;
       uint32_t RESERVED0[2];
  volatile uint32_t SA0;
  volatile uint32_t SA1;
  volatile uint32_t SA2;
       uint32_t RESERVED1[45];
  volatile uint32_t Command;                 
  volatile const  uint32_t Status;
  volatile uint32_t RxDescriptor;
  volatile uint32_t RxStatus;
  volatile uint32_t RxDescriptorNumber;
  volatile const  uint32_t RxProduceIndex;
  volatile uint32_t RxConsumeIndex;
  volatile uint32_t TxDescriptor;
  volatile uint32_t TxStatus;
  volatile uint32_t TxDescriptorNumber;
  volatile uint32_t TxProduceIndex;
  volatile const  uint32_t TxConsumeIndex;
       uint32_t RESERVED2[10];
  volatile const  uint32_t TSV0;
  volatile const  uint32_t TSV1;
  volatile const  uint32_t RSV;
       uint32_t RESERVED3[3];
  volatile uint32_t FlowControlCounter;
  volatile const  uint32_t FlowControlStatus;
       uint32_t RESERVED4[34];
  volatile uint32_t RxFilterCtrl;            
  volatile uint32_t RxFilterWoLStatus;
  volatile uint32_t RxFilterWoLClear;
       uint32_t RESERVED5;
  volatile uint32_t HashFilterL;
  volatile uint32_t HashFilterH;
       uint32_t RESERVED6[882];
  volatile const  uint32_t IntStatus;               
  volatile uint32_t IntEnable;
  volatile  uint32_t IntClear;
  volatile  uint32_t IntSet;
       uint32_t RESERVED7;
  volatile uint32_t PowerDown;
       uint32_t RESERVED8;
  volatile uint32_t Module_ID;
} LPC_EMAC_TypeDef;


#pragma no_anon_unions



 
 
 
 
#line 924 "d:\\Keil\\ARM\\INC\\NXP\\LPC17xx\\lpc17xx.h"

 
#line 945 "d:\\Keil\\ARM\\INC\\NXP\\LPC17xx\\lpc17xx.h"

 
#line 959 "d:\\Keil\\ARM\\INC\\NXP\\LPC17xx\\lpc17xx.h"

 
#line 972 "d:\\Keil\\ARM\\INC\\NXP\\LPC17xx\\lpc17xx.h"

 







 
 
 
#line 1031 "d:\\Keil\\ARM\\INC\\NXP\\LPC17xx\\lpc17xx.h"

#line 14 "GLCD_LPC1700.c"
#line 1 "GLCD.h"
 
 
 
 
 
 
 
 
 












 
                            
 
#line 41 "GLCD.h"


extern void GLCD_Init           (void);
extern void GLCD_WindowMax      (void);
extern void GLCD_PutPixel       (unsigned int x, unsigned int y);
extern void GLCD_SetTextColor   (unsigned short color);
extern void GLCD_SetBackColor   (unsigned short color);
extern void GLCD_Clear          (unsigned short color);
extern void GLCD_DrawChar       (unsigned int x, unsigned int y, unsigned short *c);
extern void GLCD_DisplayChar    (unsigned int ln, unsigned int col, unsigned char  c);
extern void GLCD_DisplayString  (unsigned int ln, unsigned int col, unsigned char *s);
extern void GLCD_ClearLn        (unsigned int ln);
extern void GLCD_Bargraph       (unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned int val);
extern void GLCD_Bitmap         (unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned char *bitmap);
extern void GLCD_Bmp            (unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned char *bmp);

#line 15 "GLCD_LPC1700.c"
#line 1 "Font_24x16.h"












 







const uint16_t Font_24x16[] = {
   
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
   
  0x0000, 0x0180, 0x0180, 0x0180, 0x0180, 0x0180, 0x0180, 0x0180,
  0x0180, 0x0180, 0x0180, 0x0180, 0x0180, 0x0180, 0x0000, 0x0000,
  0x0180, 0x0180, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
   
  0x0000, 0x0000, 0x00CC, 0x00CC, 0x00CC, 0x00CC, 0x00CC, 0x00CC,
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
   
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0C60, 0x0C60,
  0x0C60, 0x0630, 0x0630, 0x1FFE, 0x1FFE, 0x0630, 0x0738, 0x0318,
  0x1FFE, 0x1FFE, 0x0318, 0x0318, 0x018C, 0x018C, 0x018C, 0x0000,
   
  0x0000, 0x0080, 0x03E0, 0x0FF8, 0x0E9C, 0x1C8C, 0x188C, 0x008C,
  0x0098, 0x01F8, 0x07E0, 0x0E80, 0x1C80, 0x188C, 0x188C, 0x189C,
  0x0CB8, 0x0FF0, 0x03E0, 0x0080, 0x0080, 0x0000, 0x0000, 0x0000,
   
  0x0000, 0x0000, 0x0000, 0x180E, 0x0C1B, 0x0C11, 0x0611, 0x0611,
  0x0311, 0x0311, 0x019B, 0x018E, 0x38C0, 0x6CC0, 0x4460, 0x4460,
  0x4430, 0x4430, 0x4418, 0x6C18, 0x380C, 0x0000, 0x0000, 0x0000,
   
  0x0000, 0x01E0, 0x03F0, 0x0738, 0x0618, 0x0618, 0x0330, 0x01F0,
  0x00F0, 0x00F8, 0x319C, 0x330E, 0x1E06, 0x1C06, 0x1C06, 0x3F06,
  0x73FC, 0x21F0, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
   
  0x0000, 0x0000, 0x000C, 0x000C, 0x000C, 0x000C, 0x000C, 0x000C,
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
   
  0x0000, 0x0200, 0x0300, 0x0180, 0x00C0, 0x00C0, 0x0060, 0x0060,
  0x0030, 0x0030, 0x0030, 0x0030, 0x0030, 0x0030, 0x0030, 0x0030,
  0x0060, 0x0060, 0x00C0, 0x00C0, 0x0180, 0x0300, 0x0200, 0x0000,
   
  0x0000, 0x0020, 0x0060, 0x00C0, 0x0180, 0x0180, 0x0300, 0x0300,
  0x0600, 0x0600, 0x0600, 0x0600, 0x0600, 0x0600, 0x0600, 0x0600,
  0x0300, 0x0300, 0x0180, 0x0180, 0x00C0, 0x0060, 0x0020, 0x0000,
   
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x00C0, 0x00C0,
  0x06D8, 0x07F8, 0x01E0, 0x0330, 0x0738, 0x0000, 0x0000, 0x0000,
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
   
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0180, 0x0180,
  0x0180, 0x0180, 0x0180, 0x3FFC, 0x3FFC, 0x0180, 0x0180, 0x0180,
  0x0180, 0x0180, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
   
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
  0x0000, 0x0180, 0x0180, 0x0100, 0x0100, 0x0080, 0x0000, 0x0000,
   
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
  0x0000, 0x0000, 0x0000, 0x0000, 0x07E0, 0x07E0, 0x0000, 0x0000,
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
   
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
  0x0000, 0x00C0, 0x00C0, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
   
  0x0000, 0x0C00, 0x0C00, 0x0600, 0x0600, 0x0600, 0x0300, 0x0300,
  0x0300, 0x0380, 0x0180, 0x0180, 0x0180, 0x00C0, 0x00C0, 0x00C0,
  0x0060, 0x0060, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
   
  0x0000, 0x03E0, 0x07F0, 0x0E38, 0x0C18, 0x180C, 0x180C, 0x180C,
  0x180C, 0x180C, 0x180C, 0x180C, 0x180C, 0x180C, 0x0C18, 0x0E38,
  0x07F0, 0x03E0, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
   
  0x0000, 0x0100, 0x0180, 0x01C0, 0x01F0, 0x0198, 0x0188, 0x0180,
  0x0180, 0x0180, 0x0180, 0x0180, 0x0180, 0x0180, 0x0180, 0x0180,
  0x0180, 0x0180, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
   
  0x0000, 0x03E0, 0x0FF8, 0x0C18, 0x180C, 0x180C, 0x1800, 0x1800,
  0x0C00, 0x0600, 0x0300, 0x0180, 0x00C0, 0x0060, 0x0030, 0x0018,
  0x1FFC, 0x1FFC, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
   
  0x0000, 0x01E0, 0x07F8, 0x0E18, 0x0C0C, 0x0C0C, 0x0C00, 0x0600,
  0x03C0, 0x07C0, 0x0C00, 0x1800, 0x1800, 0x180C, 0x180C, 0x0C18,
  0x07F8, 0x03E0, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
   
  0x0000, 0x0C00, 0x0E00, 0x0F00, 0x0F00, 0x0D80, 0x0CC0, 0x0C60,
  0x0C60, 0x0C30, 0x0C18, 0x0C0C, 0x3FFC, 0x3FFC, 0x0C00, 0x0C00,
  0x0C00, 0x0C00, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
   
  0x0000, 0x0FF8, 0x0FF8, 0x0018, 0x0018, 0x000C, 0x03EC, 0x07FC,
  0x0E1C, 0x1C00, 0x1800, 0x1800, 0x1800, 0x180C, 0x0C1C, 0x0E18,
  0x07F8, 0x03E0, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
   
  0x0000, 0x07C0, 0x0FF0, 0x1C38, 0x1818, 0x0018, 0x000C, 0x03CC,
  0x0FEC, 0x0E3C, 0x1C1C, 0x180C, 0x180C, 0x180C, 0x1C18, 0x0E38,
  0x07F0, 0x03E0, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
   
  0x0000, 0x1FFC, 0x1FFC, 0x0C00, 0x0600, 0x0600, 0x0300, 0x0380,
  0x0180, 0x01C0, 0x00C0, 0x00E0, 0x0060, 0x0060, 0x0070, 0x0030,
  0x0030, 0x0030, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
   
  0x0000, 0x03E0, 0x07F0, 0x0E38, 0x0C18, 0x0C18, 0x0C18, 0x0638,
  0x07F0, 0x07F0, 0x0C18, 0x180C, 0x180C, 0x180C, 0x180C, 0x0C38,
  0x0FF8, 0x03E0, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
   
  0x0000, 0x03E0, 0x07F0, 0x0E38, 0x0C1C, 0x180C, 0x180C, 0x180C,
  0x1C1C, 0x1E38, 0x1BF8, 0x19E0, 0x1800, 0x0C00, 0x0C00, 0x0E1C,
  0x07F8, 0x01F0, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
   
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0180, 0x0180,
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
  0x0180, 0x0180, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
   
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0180, 0x0180,
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
  0x0180, 0x0180, 0x0100, 0x0100, 0x0080, 0x0000, 0x0000, 0x0000,
   
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
  0x1000, 0x1C00, 0x0F80, 0x03E0, 0x00F8, 0x0018, 0x00F8, 0x03E0,
  0x0F80, 0x1C00, 0x1000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
   
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
  0x1FF8, 0x0000, 0x0000, 0x0000, 0x1FF8, 0x0000, 0x0000, 0x0000,
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
   
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
  0x0008, 0x0038, 0x01F0, 0x07C0, 0x1F00, 0x1800, 0x1F00, 0x07C0,
  0x01F0, 0x0038, 0x0008, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
   
  0x0000, 0x03E0, 0x0FF8, 0x0C18, 0x180C, 0x180C, 0x1800, 0x0C00,
  0x0600, 0x0300, 0x0180, 0x00C0, 0x00C0, 0x00C0, 0x0000, 0x0000,
  0x00C0, 0x00C0, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
   
  0x0000, 0x0000, 0x07E0, 0x1818, 0x2004, 0x29C2, 0x4A22, 0x4411,
  0x4409, 0x4409, 0x4409, 0x2209, 0x1311, 0x0CE2, 0x4002, 0x2004,
  0x1818, 0x07E0, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
   
  0x0000, 0x0380, 0x0380, 0x06C0, 0x06C0, 0x06C0, 0x0C60, 0x0C60,
  0x1830, 0x1830, 0x1830, 0x3FF8, 0x3FF8, 0x701C, 0x600C, 0x600C,
  0xC006, 0xC006, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
   
  0x0000, 0x03FC, 0x0FFC, 0x0C0C, 0x180C, 0x180C, 0x180C, 0x0C0C,
  0x07FC, 0x0FFC, 0x180C, 0x300C, 0x300C, 0x300C, 0x300C, 0x180C,
  0x1FFC, 0x07FC, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
   
  0x0000, 0x07C0, 0x1FF0, 0x3838, 0x301C, 0x700C, 0x6006, 0x0006,
  0x0006, 0x0006, 0x0006, 0x0006, 0x0006, 0x6006, 0x700C, 0x301C,
  0x1FF0, 0x07E0, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
   
  0x0000, 0x03FE, 0x0FFE, 0x0E06, 0x1806, 0x1806, 0x3006, 0x3006,
  0x3006, 0x3006, 0x3006, 0x3006, 0x3006, 0x1806, 0x1806, 0x0E06,
  0x0FFE, 0x03FE, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
   
  0x0000, 0x3FFC, 0x3FFC, 0x000C, 0x000C, 0x000C, 0x000C, 0x000C,
  0x1FFC, 0x1FFC, 0x000C, 0x000C, 0x000C, 0x000C, 0x000C, 0x000C,
  0x3FFC, 0x3FFC, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
   
  0x0000, 0x3FF8, 0x3FF8, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018,
  0x1FF8, 0x1FF8, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018,
  0x0018, 0x0018, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
   
  0x0000, 0x0FE0, 0x3FF8, 0x783C, 0x600E, 0xE006, 0xC007, 0x0003,
  0x0003, 0xFE03, 0xFE03, 0xC003, 0xC007, 0xC006, 0xC00E, 0xF03C,
  0x3FF8, 0x0FE0, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
   
  0x0000, 0x300C, 0x300C, 0x300C, 0x300C, 0x300C, 0x300C, 0x300C,
  0x3FFC, 0x3FFC, 0x300C, 0x300C, 0x300C, 0x300C, 0x300C, 0x300C,
  0x300C, 0x300C, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
   
  0x0000, 0x0180, 0x0180, 0x0180, 0x0180, 0x0180, 0x0180, 0x0180,
  0x0180, 0x0180, 0x0180, 0x0180, 0x0180, 0x0180, 0x0180, 0x0180,
  0x0180, 0x0180, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
   
  0x0000, 0x0600, 0x0600, 0x0600, 0x0600, 0x0600, 0x0600, 0x0600,
  0x0600, 0x0600, 0x0600, 0x0600, 0x0600, 0x0618, 0x0618, 0x0738,
  0x03F0, 0x01E0, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
   
  0x0000, 0x3006, 0x1806, 0x0C06, 0x0606, 0x0306, 0x0186, 0x00C6,
  0x0066, 0x0076, 0x00DE, 0x018E, 0x0306, 0x0606, 0x0C06, 0x1806,
  0x3006, 0x6006, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
   
  0x0000, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018,
  0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018,
  0x1FF8, 0x1FF8, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
   
  0x0000, 0xE00E, 0xF01E, 0xF01E, 0xF01E, 0xD836, 0xD836, 0xD836,
  0xD836, 0xCC66, 0xCC66, 0xCC66, 0xC6C6, 0xC6C6, 0xC6C6, 0xC6C6,
  0xC386, 0xC386, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
   
  0x0000, 0x300C, 0x301C, 0x303C, 0x303C, 0x306C, 0x306C, 0x30CC,
  0x30CC, 0x318C, 0x330C, 0x330C, 0x360C, 0x360C, 0x3C0C, 0x3C0C,
  0x380C, 0x300C, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
   
  0x0000, 0x07E0, 0x1FF8, 0x381C, 0x700E, 0x6006, 0xC003, 0xC003,
  0xC003, 0xC003, 0xC003, 0xC003, 0xC003, 0x6006, 0x700E, 0x381C,
  0x1FF8, 0x07E0, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
   
  0x0000, 0x0FFC, 0x1FFC, 0x380C, 0x300C, 0x300C, 0x300C, 0x300C,
  0x180C, 0x1FFC, 0x07FC, 0x000C, 0x000C, 0x000C, 0x000C, 0x000C,
  0x000C, 0x000C, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
   
  0x0000, 0x07E0, 0x1FF8, 0x381C, 0x700E, 0x6006, 0xE003, 0xC003,
  0xC003, 0xC003, 0xC003, 0xC003, 0xE007, 0x6306, 0x3F0E, 0x3C1C,
  0x3FF8, 0xF7E0, 0xC000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
   
  0x0000, 0x0FFE, 0x1FFE, 0x3806, 0x3006, 0x3006, 0x3006, 0x3806,
  0x1FFE, 0x07FE, 0x0306, 0x0606, 0x0C06, 0x1806, 0x1806, 0x3006,
  0x3006, 0x6006, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
   
  0x0000, 0x03E0, 0x0FF8, 0x0C1C, 0x180C, 0x180C, 0x000C, 0x001C,
  0x03F8, 0x0FE0, 0x1E00, 0x3800, 0x3006, 0x3006, 0x300E, 0x1C1C,
  0x0FF8, 0x07E0, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
   
  0x0000, 0x7FFE, 0x7FFE, 0x0180, 0x0180, 0x0180, 0x0180, 0x0180,
  0x0180, 0x0180, 0x0180, 0x0180, 0x0180, 0x0180, 0x0180, 0x0180,
  0x0180, 0x0180, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
   
  0x0000, 0x300C, 0x300C, 0x300C, 0x300C, 0x300C, 0x300C, 0x300C,
  0x300C, 0x300C, 0x300C, 0x300C, 0x300C, 0x300C, 0x300C, 0x1818,
  0x1FF8, 0x07E0, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
   
  0x0000, 0x6003, 0x3006, 0x3006, 0x3006, 0x180C, 0x180C, 0x180C,
  0x0C18, 0x0C18, 0x0E38, 0x0630, 0x0630, 0x0770, 0x0360, 0x0360,
  0x01C0, 0x01C0, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
   
  0x0000, 0x6003, 0x61C3, 0x61C3, 0x61C3, 0x3366, 0x3366, 0x3366,
  0x3366, 0x3366, 0x3366, 0x1B6C, 0x1B6C, 0x1B6C, 0x1A2C, 0x1E3C,
  0x0E38, 0x0E38, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
   
  0x0000, 0xE00F, 0x700C, 0x3018, 0x1830, 0x0C70, 0x0E60, 0x07C0,
  0x0380, 0x0380, 0x03C0, 0x06E0, 0x0C70, 0x1C30, 0x1818, 0x300C,
  0x600E, 0xE007, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
   
  0x0000, 0xC003, 0x6006, 0x300C, 0x381C, 0x1838, 0x0C30, 0x0660,
  0x07E0, 0x03C0, 0x0180, 0x0180, 0x0180, 0x0180, 0x0180, 0x0180,
  0x0180, 0x0180, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
   
  0x0000, 0x7FFC, 0x7FFC, 0x6000, 0x3000, 0x1800, 0x0C00, 0x0600,
  0x0300, 0x0180, 0x00C0, 0x0060, 0x0030, 0x0018, 0x000C, 0x0006,
  0x7FFE, 0x7FFE, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
   
  0x0000, 0x03E0, 0x03E0, 0x0060, 0x0060, 0x0060, 0x0060, 0x0060,
  0x0060, 0x0060, 0x0060, 0x0060, 0x0060, 0x0060, 0x0060, 0x0060,
  0x0060, 0x0060, 0x0060, 0x0060, 0x0060, 0x03E0, 0x03E0, 0x0000,
   
  0x0000, 0x0030, 0x0030, 0x0060, 0x0060, 0x0060, 0x00C0, 0x00C0,
  0x00C0, 0x01C0, 0x0180, 0x0180, 0x0180, 0x0300, 0x0300, 0x0300,
  0x0600, 0x0600, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
   
  0x0000, 0x03E0, 0x03E0, 0x0300, 0x0300, 0x0300, 0x0300, 0x0300,
  0x0300, 0x0300, 0x0300, 0x0300, 0x0300, 0x0300, 0x0300, 0x0300,
  0x0300, 0x0300, 0x0300, 0x0300, 0x0300, 0x03E0, 0x03E0, 0x0000,
   
  0x0000, 0x0000, 0x01C0, 0x01C0, 0x0360, 0x0360, 0x0360, 0x0630,
  0x0630, 0x0C18, 0x0C18, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
   
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
  0x0000, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
   
  0x0000, 0x000C, 0x000C, 0x000C, 0x000C, 0x000C, 0x000C, 0x0000,
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
   
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x03F0, 0x07F8,
  0x0C1C, 0x0C0C, 0x0F00, 0x0FF0, 0x0CF8, 0x0C0C, 0x0C0C, 0x0F1C,
  0x0FF8, 0x18F0, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
   
  0x0000, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x03D8, 0x0FF8,
  0x0C38, 0x1818, 0x1818, 0x1818, 0x1818, 0x1818, 0x1818, 0x0C38,
  0x0FF8, 0x03D8, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
   
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x03C0, 0x07F0,
  0x0E30, 0x0C18, 0x0018, 0x0018, 0x0018, 0x0018, 0x0C18, 0x0E30,
  0x07F0, 0x03C0, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
   
  0x0000, 0x1800, 0x1800, 0x1800, 0x1800, 0x1800, 0x1BC0, 0x1FF0,
  0x1C30, 0x1818, 0x1818, 0x1818, 0x1818, 0x1818, 0x1818, 0x1C30,
  0x1FF0, 0x1BC0, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
   
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x03C0, 0x0FF0,
  0x0C30, 0x1818, 0x1FF8, 0x1FF8, 0x0018, 0x0018, 0x1838, 0x1C30,
  0x0FF0, 0x07C0, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
   
  0x0000, 0x0F80, 0x0FC0, 0x00C0, 0x00C0, 0x00C0, 0x07F0, 0x07F0,
  0x00C0, 0x00C0, 0x00C0, 0x00C0, 0x00C0, 0x00C0, 0x00C0, 0x00C0,
  0x00C0, 0x00C0, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
   
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0DE0, 0x0FF8,
  0x0E18, 0x0C0C, 0x0C0C, 0x0C0C, 0x0C0C, 0x0C0C, 0x0C0C, 0x0E18,
  0x0FF8, 0x0DE0, 0x0C00, 0x0C0C, 0x061C, 0x07F8, 0x01F0, 0x0000,
   
  0x0000, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x07D8, 0x0FF8,
  0x1C38, 0x1818, 0x1818, 0x1818, 0x1818, 0x1818, 0x1818, 0x1818,
  0x1818, 0x1818, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
   
  0x0000, 0x00C0, 0x00C0, 0x0000, 0x0000, 0x0000, 0x00C0, 0x00C0,
  0x00C0, 0x00C0, 0x00C0, 0x00C0, 0x00C0, 0x00C0, 0x00C0, 0x00C0,
  0x00C0, 0x00C0, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
   
  0x0000, 0x00C0, 0x00C0, 0x0000, 0x0000, 0x0000, 0x00C0, 0x00C0,
  0x00C0, 0x00C0, 0x00C0, 0x00C0, 0x00C0, 0x00C0, 0x00C0, 0x00C0,
  0x00C0, 0x00C0, 0x00C0, 0x00C0, 0x00C0, 0x00F8, 0x0078, 0x0000,
   
  0x0000, 0x000C, 0x000C, 0x000C, 0x000C, 0x000C, 0x0C0C, 0x060C,
  0x030C, 0x018C, 0x00CC, 0x006C, 0x00FC, 0x019C, 0x038C, 0x030C,
  0x060C, 0x0C0C, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
   
  0x0000, 0x00C0, 0x00C0, 0x00C0, 0x00C0, 0x00C0, 0x00C0, 0x00C0,
  0x00C0, 0x00C0, 0x00C0, 0x00C0, 0x00C0, 0x00C0, 0x00C0, 0x00C0,
  0x00C0, 0x00C0, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
   
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x3C7C, 0x7EFF,
  0xE3C7, 0xC183, 0xC183, 0xC183, 0xC183, 0xC183, 0xC183, 0xC183,
  0xC183, 0xC183, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
   
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0798, 0x0FF8,
  0x1C38, 0x1818, 0x1818, 0x1818, 0x1818, 0x1818, 0x1818, 0x1818,
  0x1818, 0x1818, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
   
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x03C0, 0x0FF0,
  0x0C30, 0x1818, 0x1818, 0x1818, 0x1818, 0x1818, 0x1818, 0x0C30,
  0x0FF0, 0x03C0, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
   
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x03D8, 0x0FF8,
  0x0C38, 0x1818, 0x1818, 0x1818, 0x1818, 0x1818, 0x1818, 0x0C38,
  0x0FF8, 0x03D8, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0000,
   
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x1BC0, 0x1FF0,
  0x1C30, 0x1818, 0x1818, 0x1818, 0x1818, 0x1818, 0x1818, 0x1C30,
  0x1FF0, 0x1BC0, 0x1800, 0x1800, 0x1800, 0x1800, 0x1800, 0x0000,
   
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x07B0, 0x03F0,
  0x0070, 0x0030, 0x0030, 0x0030, 0x0030, 0x0030, 0x0030, 0x0030,
  0x0030, 0x0030, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
   
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x03E0, 0x03F0,
  0x0E38, 0x0C18, 0x0038, 0x03F0, 0x07C0, 0x0C00, 0x0C18, 0x0E38,
  0x07F0, 0x03E0, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
   
  0x0000, 0x0000, 0x0080, 0x00C0, 0x00C0, 0x00C0, 0x07F0, 0x07F0,
  0x00C0, 0x00C0, 0x00C0, 0x00C0, 0x00C0, 0x00C0, 0x00C0, 0x00C0,
  0x07C0, 0x0780, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
   
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x1818, 0x1818,
  0x1818, 0x1818, 0x1818, 0x1818, 0x1818, 0x1818, 0x1818, 0x1C38,
  0x1FF0, 0x19E0, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
   
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x180C, 0x0C18,
  0x0C18, 0x0C18, 0x0630, 0x0630, 0x0630, 0x0360, 0x0360, 0x0360,
  0x01C0, 0x01C0, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
   
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x41C1, 0x41C1,
  0x61C3, 0x6363, 0x6363, 0x6363, 0x3636, 0x3636, 0x3636, 0x1C1C,
  0x1C1C, 0x1C1C, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
   
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x381C, 0x1C38,
  0x0C30, 0x0660, 0x03C0, 0x03C0, 0x03C0, 0x03C0, 0x0660, 0x0C30,
  0x1C38, 0x381C, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
   
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x3018, 0x1830,
  0x1830, 0x1870, 0x0C60, 0x0C60, 0x0CE0, 0x06C0, 0x06C0, 0x0380,
  0x0380, 0x0380, 0x0180, 0x0180, 0x01C0, 0x00F0, 0x0070, 0x0000,
   
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x1FFC, 0x1FFC,
  0x0C00, 0x0600, 0x0300, 0x0180, 0x00C0, 0x0060, 0x0030, 0x0018,
  0x1FFC, 0x1FFC, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
   
  0x0000, 0x0300, 0x0180, 0x00C0, 0x00C0, 0x00C0, 0x00C0, 0x00C0,
  0x00C0, 0x0060, 0x0060, 0x0030, 0x0060, 0x0040, 0x00C0, 0x00C0,
  0x00C0, 0x00C0, 0x00C0, 0x00C0, 0x0180, 0x0300, 0x0000, 0x0000,
   
  0x0000, 0x0180, 0x0180, 0x0180, 0x0180, 0x0180, 0x0180, 0x0180,
  0x0180, 0x0180, 0x0180, 0x0180, 0x0180, 0x0180, 0x0180, 0x0180,
  0x0180, 0x0180, 0x0180, 0x0180, 0x0180, 0x0180, 0x0180, 0x0000,
   
  0x0000, 0x0060, 0x00C0, 0x01C0, 0x0180, 0x0180, 0x0180, 0x0180,
  0x0180, 0x0300, 0x0300, 0x0600, 0x0300, 0x0100, 0x0180, 0x0180,
  0x0180, 0x0180, 0x0180, 0x0180, 0x00C0, 0x0060, 0x0000, 0x0000,
   
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
  0x10F0, 0x1FF8, 0x0F08, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
   
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,

   
   
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x03C0, 0x0C30, 0x1008,
  0x2004, 0x2004, 0x4002, 0x4002, 0x4002, 0x4002, 0x4002, 0x2004,
  0x2004, 0x1008, 0x0C30, 0x03C0, 0x0000, 0x0000, 0x0000, 0x0000,
   
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x03C0, 0x0FF0, 0x1FF8,
  0x3FFC, 0x3FFC, 0x7FFE, 0x7FFE, 0x7FFE, 0x7FFE, 0x7FFE, 0x3FFC,
  0x3FFC, 0x1FF8, 0x0FF0, 0x03C0, 0x0000, 0x0000, 0x0000, 0x0000,
   
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x07E0,
  0x0FF0, 0x1818, 0x1818, 0x1818, 0x1818, 0x1818, 0x1818, 0x0FF0,
  0x07E0, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
   
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x07E0,
  0x0FF0, 0x1FF8, 0x1FF8, 0x1FF8, 0x1FF8, 0x1FF8, 0x1FF8, 0x0FF0,
  0x07E0, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
   
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
  0x0000, 0x0000, 0x0000, 0x0000, 0x0180, 0x03C0, 0x0660, 0x0C30,
  0x1818, 0x1818, 0x1FF8, 0x1FF8, 0x0000, 0x0000, 0x0000, 0x0000,
   
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
  0x0000, 0x0000, 0x0000, 0x0000, 0x0180, 0x03C0, 0x07E0, 0x0FF0,
  0x1FF8, 0x1FF8, 0x1FF8, 0x1FF8, 0x0000, 0x0000, 0x0000, 0x0000,
   
  0x0000, 0x0000, 0x0000, 0x0000, 0x1FF8, 0x1FF8, 0x1818, 0x1818,
  0x0C30, 0x0660, 0x03C0, 0x0180, 0x0000, 0x0000, 0x0000, 0x0000,
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
   
  0x0000, 0x0000, 0x0000, 0x0000, 0x1FF8, 0x1FF8, 0x1FF8, 0x1FF8,
  0x0FF0, 0x07E0, 0x03C0, 0x0180, 0x0000, 0x0000, 0x0000, 0x0000,
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
   
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x01E0,
  0x01F0, 0x0198, 0x018C, 0x0186, 0x0186, 0x018C, 0x0198, 0x01F0,
  0x01E0, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
   
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x01E0,
  0x01F0, 0x01F8, 0x01FC, 0x01FE, 0x01FE, 0x01FC, 0x01F8, 0x01F0,
  0x01E0, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
   
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0780,
  0x0F80, 0x1980, 0x3180, 0x6180, 0x6180, 0x3180, 0x1980, 0x0F80,
  0x0780, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
   
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0780,
  0x0F80, 0x1F80, 0x3F80, 0x7F80, 0x7F80, 0x3F80, 0x1F80, 0x0F80,
  0x0780, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
   
  0x0000, 0x01C0, 0x0220, 0x0220, 0x0140, 0x0630, 0x0808, 0x0808,
  0x0808, 0x0808, 0x0808, 0x0808, 0x0808, 0x0220, 0x0220, 0x0220,
  0x0220, 0x0220, 0x0220, 0x0220, 0x0220, 0x0220, 0x0220, 0x0000,
   
  0x0000, 0x01C0, 0x03E0, 0x03E0, 0x01C0, 0x07F0, 0x0DD8, 0x0DD8,
  0x0DD8, 0x0DD8, 0x0DD8, 0x0DD8, 0x0DD8, 0x0360, 0x0360, 0x0360,
  0x0360, 0x0360, 0x0360, 0x0360, 0x0360, 0x0360, 0x0360, 0x0000,
   
  0x0000, 0x01C0, 0x0220, 0x0220, 0x0140, 0x0630, 0x0808, 0x0808,
  0x0808, 0x1004, 0x2002, 0x2002, 0x0140, 0x0220, 0x0220, 0x0410,
  0x0808, 0x0808, 0x1004, 0x1004, 0x2004, 0x4004, 0x0000, 0x0000,
   
  0x0000, 0x01C0, 0x03E0, 0x03E0, 0x01C0, 0x07F0, 0x0DD8, 0x0DD8,
  0x0DD8, 0x19CC, 0x31C6, 0x61C2, 0x01C0, 0x0360, 0x0360, 0x0670,
  0x0C38, 0x0C18, 0x180C, 0x180C, 0x300C, 0x600C, 0x0000, 0x0000,
};

#line 16 "GLCD_LPC1700.c"

 












 

#line 39 "GLCD_LPC1700.c"

 


 


 






 

 

 

 

 

 

 

 

 
 

 
static volatile unsigned short TextColor = 0x0000, BackColor = 0xFFFF;


 





 

static void delay (int cnt) {

  cnt <<= 18;
  while (cnt--);
}

__asm void wait()
{
    nop
    BX lr
}

void wait_delay(int count)
{
  while(count--);
}





 

static __inline unsigned char lcd_send (unsigned short byte) {

  ((LPC_GPIO_TypeDef *) ((0x2009C000UL) + 0x00040) )->FIODIR |= 0x000000ff;  
  ((1) ? (((LPC_GPIO_TypeDef *) ((0x2009C000UL) + 0x00000) )->FIOSET = (1 << 21)) : (((LPC_GPIO_TypeDef *) ((0x2009C000UL) + 0x00000) )->FIOCLR = (1 << 21)));		   				
  ((0) ? (((LPC_GPIO_TypeDef *) ((0x2009C000UL) + 0x00000) )->FIOSET = (1 << 19)) : (((LPC_GPIO_TypeDef *) ((0x2009C000UL) + 0x00000) )->FIOCLR = (1 << 19)));	                        
  ((LPC_GPIO_TypeDef *) ((0x2009C000UL) + 0x00040) )->FIOPIN =  byte;        
  ((1) ? (((LPC_GPIO_TypeDef *) ((0x2009C000UL) + 0x00000) )->FIOSET = (1 << 20)) : (((LPC_GPIO_TypeDef *) ((0x2009C000UL) + 0x00000) )->FIOCLR = (1 << 20)));                         
  ((0) ? (((LPC_GPIO_TypeDef *) ((0x2009C000UL) + 0x00000) )->FIOSET = (1 << 20)) : (((LPC_GPIO_TypeDef *) ((0x2009C000UL) + 0x00000) )->FIOCLR = (1 << 20)));							
  ((LPC_GPIO_TypeDef *) ((0x2009C000UL) + 0x00040) )->FIOPIN =  byte >> 8;   
  return(1);
}






 

static __inline unsigned short lcd_read (void) {
  unsigned short id;
  ((LPC_GPIO_TypeDef *) ((0x2009C000UL) + 0x00040) )->FIODIR &= 0xffffff00;                
  ((0) ? (((LPC_GPIO_TypeDef *) ((0x2009C000UL) + 0x00000) )->FIOSET = (1 << 21)) : (((LPC_GPIO_TypeDef *) ((0x2009C000UL) + 0x00000) )->FIOCLR = (1 << 21)));		   				              
  ((0) ? (((LPC_GPIO_TypeDef *) ((0x2009C000UL) + 0x00000) )->FIOSET = (1 << 19)) : (((LPC_GPIO_TypeDef *) ((0x2009C000UL) + 0x00000) )->FIOCLR = (1 << 19)));	                                      
  wait_delay(50);							      
  id = ((LPC_GPIO_TypeDef *) ((0x2009C000UL) + 0x00040) )->FIOPIN & 0x00ff;                
  ((1) ? (((LPC_GPIO_TypeDef *) ((0x2009C000UL) + 0x00000) )->FIOSET = (1 << 19)) : (((LPC_GPIO_TypeDef *) ((0x2009C000UL) + 0x00000) )->FIOCLR = (1 << 19)));	                                      
  wait_delay(50);							      
  id = (id << 8) | (((LPC_GPIO_TypeDef *) ((0x2009C000UL) + 0x00040) )->FIOPIN & 0x00ff);  
  ((1) ? (((LPC_GPIO_TypeDef *) ((0x2009C000UL) + 0x00000) )->FIOSET = (1 << 21)) : (((LPC_GPIO_TypeDef *) ((0x2009C000UL) + 0x00000) )->FIOCLR = (1 << 21)));						
  return(id); 
}





 

static __inline void wr_cmd (unsigned char c) {

  ((0) ? (((LPC_GPIO_TypeDef *) ((0x2009C000UL) + 0x00000) )->FIOSET = (1 << 23)) : (((LPC_GPIO_TypeDef *) ((0x2009C000UL) + 0x00000) )->FIOCLR = (1 << 23)));
  ((1) ? (((LPC_GPIO_TypeDef *) ((0x2009C000UL) + 0x00000) )->FIOSET = (1 << 25)) : (((LPC_GPIO_TypeDef *) ((0x2009C000UL) + 0x00000) )->FIOCLR = (1 << 25)));
  lcd_send(c);
  ((0) ? (((LPC_GPIO_TypeDef *) ((0x2009C000UL) + 0x00000) )->FIOSET = (1 << 24)) : (((LPC_GPIO_TypeDef *) ((0x2009C000UL) + 0x00000) )->FIOCLR = (1 << 24)));
  wait();
  ((1) ? (((LPC_GPIO_TypeDef *) ((0x2009C000UL) + 0x00000) )->FIOSET = (1 << 24)) : (((LPC_GPIO_TypeDef *) ((0x2009C000UL) + 0x00000) )->FIOCLR = (1 << 24)));
}






 

static __inline void wr_dat (unsigned short c) {

  ((1) ? (((LPC_GPIO_TypeDef *) ((0x2009C000UL) + 0x00000) )->FIOSET = (1 << 23)) : (((LPC_GPIO_TypeDef *) ((0x2009C000UL) + 0x00000) )->FIOCLR = (1 << 23)));
  ((1) ? (((LPC_GPIO_TypeDef *) ((0x2009C000UL) + 0x00000) )->FIOSET = (1 << 25)) : (((LPC_GPIO_TypeDef *) ((0x2009C000UL) + 0x00000) )->FIOCLR = (1 << 25)));
  lcd_send(c);
  ((0) ? (((LPC_GPIO_TypeDef *) ((0x2009C000UL) + 0x00000) )->FIOSET = (1 << 24)) : (((LPC_GPIO_TypeDef *) ((0x2009C000UL) + 0x00000) )->FIOCLR = (1 << 24)));
  wait();
  ((1) ? (((LPC_GPIO_TypeDef *) ((0x2009C000UL) + 0x00000) )->FIOSET = (1 << 24)) : (((LPC_GPIO_TypeDef *) ((0x2009C000UL) + 0x00000) )->FIOCLR = (1 << 24)));
}





 

static __inline unsigned short rd_dat (void) {
  unsigned short val = 0;

  ((1) ? (((LPC_GPIO_TypeDef *) ((0x2009C000UL) + 0x00000) )->FIOSET = (1 << 23)) : (((LPC_GPIO_TypeDef *) ((0x2009C000UL) + 0x00000) )->FIOCLR = (1 << 23)));
  ((1) ? (((LPC_GPIO_TypeDef *) ((0x2009C000UL) + 0x00000) )->FIOSET = (1 << 24)) : (((LPC_GPIO_TypeDef *) ((0x2009C000UL) + 0x00000) )->FIOCLR = (1 << 24)));
  ((0) ? (((LPC_GPIO_TypeDef *) ((0x2009C000UL) + 0x00000) )->FIOSET = (1 << 25)) : (((LPC_GPIO_TypeDef *) ((0x2009C000UL) + 0x00000) )->FIOCLR = (1 << 25)));
  val = lcd_read();
  ((1) ? (((LPC_GPIO_TypeDef *) ((0x2009C000UL) + 0x00000) )->FIOSET = (1 << 25)) : (((LPC_GPIO_TypeDef *) ((0x2009C000UL) + 0x00000) )->FIOCLR = (1 << 25)));
  return val;
}





 

static __inline void wr_dat_start (void) {

  ((1) ? (((LPC_GPIO_TypeDef *) ((0x2009C000UL) + 0x00000) )->FIOSET = (1 << 23)) : (((LPC_GPIO_TypeDef *) ((0x2009C000UL) + 0x00000) )->FIOCLR = (1 << 23)));
}






 

static __inline void wr_dat_stop (void) {

  ((1) ? (((LPC_GPIO_TypeDef *) ((0x2009C000UL) + 0x00000) )->FIOSET = (1 << 22)) : (((LPC_GPIO_TypeDef *) ((0x2009C000UL) + 0x00000) )->FIOCLR = (1 << 22)));
}






 

static __inline void wr_dat_only (unsigned short c) {

  lcd_send(c);
  ((0) ? (((LPC_GPIO_TypeDef *) ((0x2009C000UL) + 0x00000) )->FIOSET = (1 << 24)) : (((LPC_GPIO_TypeDef *) ((0x2009C000UL) + 0x00000) )->FIOCLR = (1 << 24)));
  wait();
  ((1) ? (((LPC_GPIO_TypeDef *) ((0x2009C000UL) + 0x00000) )->FIOSET = (1 << 24)) : (((LPC_GPIO_TypeDef *) ((0x2009C000UL) + 0x00000) )->FIOCLR = (1 << 24)));
}






 

static __inline void wr_reg (unsigned char reg, unsigned short val) {

  ((0) ? (((LPC_GPIO_TypeDef *) ((0x2009C000UL) + 0x00000) )->FIOSET = (1 << 22)) : (((LPC_GPIO_TypeDef *) ((0x2009C000UL) + 0x00000) )->FIOCLR = (1 << 22)));
  wr_cmd(reg);
  wr_dat(val);
  ((1) ? (((LPC_GPIO_TypeDef *) ((0x2009C000UL) + 0x00000) )->FIOSET = (1 << 22)) : (((LPC_GPIO_TypeDef *) ((0x2009C000UL) + 0x00000) )->FIOCLR = (1 << 22)));
}






 

static unsigned short rd_reg (unsigned short reg) {
  unsigned short val = 0;

  ((0) ? (((LPC_GPIO_TypeDef *) ((0x2009C000UL) + 0x00000) )->FIOSET = (1 << 22)) : (((LPC_GPIO_TypeDef *) ((0x2009C000UL) + 0x00000) )->FIOCLR = (1 << 22)));
  wr_cmd(reg);
  val = rd_dat(); 
  ((1) ? (((LPC_GPIO_TypeDef *) ((0x2009C000UL) + 0x00000) )->FIOSET = (1 << 22)) : (((LPC_GPIO_TypeDef *) ((0x2009C000UL) + 0x00000) )->FIOCLR = (1 << 22)));
  return (val);
}


 





 

void GLCD_Init (void) { 
  static unsigned short driverCode;

   
  ((LPC_GPIO_TypeDef *) ((0x2009C000UL) + 0x00000) )->FIODIR   |= 0x03f80000;
  ((LPC_GPIO_TypeDef *) ((0x2009C000UL) + 0x00000) )->FIOSET    = 0x03f80000;	

  delay(5);                              

  driverCode = rd_reg(0x00);

  if(driverCode == 0x4531)				
  {
  	wr_reg(0x00,0x0001);
  	wr_reg(0x10,0x0628);
  	wr_reg(0x12,0x0006);
  	wr_reg(0x13,0x0A32);
  	wr_reg(0x11,0x0040);
  	wr_reg(0x15,0x0050);
  	wr_reg(0x12,0x0016);
  	delay(15);
  	wr_reg(0x10,0x5660);
  	delay(15);
  	wr_reg(0x13,0x2A4E);
  	wr_reg(0x01,0x0100);
  	wr_reg(0x02,0x0300);
	
  	wr_reg(0x03,0x1030);
	
  	wr_reg(0x08,0x0202);
  	wr_reg(0x0A,0x0000);
  	wr_reg(0x30,0x0000);
  	wr_reg(0x31,0x0402);
  	wr_reg(0x32,0x0106);
  	wr_reg(0x33,0x0700);
  	wr_reg(0x34,0x0104);
  	wr_reg(0x35,0x0301);
  	wr_reg(0x36,0x0707);
  	wr_reg(0x37,0x0305);
  	wr_reg(0x38,0x0208);
  	wr_reg(0x39,0x0F0B);
  	delay(15);
  	wr_reg(0x41,0x0002);
  	wr_reg(0x60,0x2700);
  	wr_reg(0x61,0x0001);
  	wr_reg(0x90,0x0119);
  	wr_reg(0x92,0x010A);
  	wr_reg(0x93,0x0004);
  	wr_reg(0xA0,0x0100);
  	delay(15);
  	wr_reg(0xA0,0x0000);
  	delay(20);
  }
  else if(driverCode == 0x9320)		 
  {
     
	wr_reg(0xE5, 0x8000);                  
	wr_reg(0x00, 0x0001);                  
	wr_reg(0x01, 0x0100);                  
	wr_reg(0x02, 0x0700);                  
	wr_reg(0x03, 0x1030);                  
	wr_reg(0x04, 0x0000);                  
	wr_reg(0x08, 0x0202);                  
	wr_reg(0x09, 0x0000);                  
	wr_reg(0x0A, 0x0000);                  
	wr_reg(0x0C, 0x0000);                  
	wr_reg(0x0D, 0x0000);                  
	wr_reg(0x0F, 0x0000);                  
	
	 
	wr_reg(0x10, 0x0000);                  
	wr_reg(0x11, 0x0000);                  
	wr_reg(0x12, 0x0000);                  
	wr_reg(0x13, 0x0000);                  
	delay(20);                             
    wr_reg(0x10, 0x17B0);                  
	wr_reg(0x11, 0x0137);                  
	delay(5);                              
	wr_reg(0x12, 0x0139);                  
	delay(5);                              
	wr_reg(0x13, 0x1D00);                  
	wr_reg(0x29, 0x0013);                  
	delay(5);                              
	wr_reg(0x20, 0x0000);                  
	wr_reg(0x21, 0x0000);                  
	
	 
	wr_reg(0x30, 0x0006);
	wr_reg(0x31, 0x0101);
	wr_reg(0x32, 0x0003);
	wr_reg(0x35, 0x0106);
	wr_reg(0x36, 0x0B02);
	wr_reg(0x37, 0x0302);
	wr_reg(0x38, 0x0707);
	wr_reg(0x39, 0x0007);
	wr_reg(0x3C, 0x0600);
	wr_reg(0x3D, 0x020B);
	  
	 
	wr_reg(0x50, 0x0000);                  
	wr_reg(0x51, (240-1));              
	wr_reg(0x52, 0x0000);                  
	wr_reg(0x53, (320-1));               
	wr_reg(0x60, 0x2700);                  
	wr_reg(0x61, 0x0001);                  
	wr_reg(0x6A, 0x0000);                  
	
	 
	wr_reg(0x80, 0x0000);
	wr_reg(0x81, 0x0000);
	wr_reg(0x82, 0x0000);
	wr_reg(0x83, 0x0000);
	wr_reg(0x84, 0x0000);
	wr_reg(0x85, 0x0000);
	
	 
	wr_reg(0x90, 0x0010);
	wr_reg(0x92, 0x0000);
	wr_reg(0x93, 0x0003);
	wr_reg(0x95, 0x0110);
	wr_reg(0x97, 0x0000);
	wr_reg(0x98, 0x0000);
  }
  

 
  wr_reg(0x03, 0x1038);

  wr_reg(0x07, 0x0173);                   
}






 

void GLCD_WindowMax (void) {

  wr_reg(0x50, 0);                       
  wr_reg(0x51, 240-1);                
  wr_reg(0x52, 0);                       
  wr_reg(0x53, 320-1);                 
}







 

void GLCD_PutPixel (unsigned int x, unsigned int y) {

  wr_reg(0x20, y);
  wr_reg(0x21, 320-1-x);
  ((0) ? (((LPC_GPIO_TypeDef *) ((0x2009C000UL) + 0x00000) )->FIOSET = (1 << 22)) : (((LPC_GPIO_TypeDef *) ((0x2009C000UL) + 0x00000) )->FIOCLR = (1 << 22)));
  wr_cmd(0x22);
  wr_dat(TextColor);
  ((1) ? (((LPC_GPIO_TypeDef *) ((0x2009C000UL) + 0x00000) )->FIOSET = (1 << 22)) : (((LPC_GPIO_TypeDef *) ((0x2009C000UL) + 0x00000) )->FIOCLR = (1 << 22)));
}






 

void GLCD_SetTextColor (unsigned short color) {

  TextColor = color;
}






 

void GLCD_SetBackColor (unsigned short color) {

  BackColor = color;
}






 

void GLCD_Clear (unsigned short color) {
  unsigned int   i;

  GLCD_WindowMax();

  wr_reg(0x20, 0);
  wr_reg(0x21, 0);
  ((0) ? (((LPC_GPIO_TypeDef *) ((0x2009C000UL) + 0x00000) )->FIOSET = (1 << 22)) : (((LPC_GPIO_TypeDef *) ((0x2009C000UL) + 0x00000) )->FIOCLR = (1 << 22)));
  wr_cmd(0x22);
  wr_dat_start();
  for(i = 0; i < (320*240); i++)
    wr_dat_only(color);
  wr_dat_stop();
}








 

void GLCD_DrawChar (unsigned int x, unsigned int y, unsigned short *c) {
  int idx = 0, i, j;

  x = 320-x-16;
  wr_reg(0x50, y);                       
  wr_reg(0x51, y+24-1);              
  wr_reg(0x52, x);                       
  wr_reg(0x53, x+16-1);              

  wr_reg(0x20, y);
  wr_reg(0x21, x);
  ((0) ? (((LPC_GPIO_TypeDef *) ((0x2009C000UL) + 0x00000) )->FIOSET = (1 << 22)) : (((LPC_GPIO_TypeDef *) ((0x2009C000UL) + 0x00000) )->FIOCLR = (1 << 22)));
  wr_cmd(0x22);
  wr_dat_start();
  for (j = 0; j < 24; j++) {
    for (i = 16-1; i >= 0; i--) {
      if((c[idx] & (1 << i)) == 0x00) {
        wr_dat_only(BackColor);
      } else {
        wr_dat_only(TextColor);
      }
    }
    c++;
  }
  wr_dat_stop();
}








 

void GLCD_DisplayChar (unsigned int ln, unsigned int col, unsigned char c) {

  c -= 32;
  GLCD_DrawChar(col * 16, ln * 24, (unsigned short *)&Font_24x16[c * 24]);
}








 

void GLCD_DisplayString (unsigned int ln, unsigned int col, unsigned char *s) {

  GLCD_WindowMax();
  while (*s) {
    GLCD_DisplayChar(ln, col++, *s++);
  }
}






 

void GLCD_ClearLn (unsigned int ln) {

  GLCD_WindowMax();
  GLCD_DisplayString(ln, 0, "                    ");
}








 

void GLCD_Bargraph (unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned int val) {
  int i,j;

  x = 320-x-w;
  wr_reg(0x50, y);                       
  wr_reg(0x51, y+24-1);              
  wr_reg(0x52, x);                       
  wr_reg(0x53, x+w-1);                   

  val = (val * w) >> 10;                 
  wr_reg(0x20, y);
  wr_reg(0x21, x);
  ((0) ? (((LPC_GPIO_TypeDef *) ((0x2009C000UL) + 0x00000) )->FIOSET = (1 << 22)) : (((LPC_GPIO_TypeDef *) ((0x2009C000UL) + 0x00000) )->FIOCLR = (1 << 22)));
  wr_cmd(0x22);
  wr_dat_start();
  for (i = 0; i < h; i++) {
    for (j = w-1; j >= 0; j--) {
      if(j >= val) {
        wr_dat_only(BackColor);
      } else {
        wr_dat_only(TextColor);
      }
    }
  }
  wr_dat_stop();
}












 

void GLCD_Bitmap (unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned char *bitmap) {
  unsigned int    i, j;
  unsigned short *bitmap_ptr = (unsigned short *)bitmap;

  x = 320-x-w;
  wr_reg(0x50, y);                       
  wr_reg(0x51, y+h-1);                   
  wr_reg(0x52, x);                       
  wr_reg(0x53, x+w-1);                   

  wr_reg(0x20, y);
  wr_reg(0x21, x);
  ((0) ? (((LPC_GPIO_TypeDef *) ((0x2009C000UL) + 0x00000) )->FIOSET = (1 << 22)) : (((LPC_GPIO_TypeDef *) ((0x2009C000UL) + 0x00000) )->FIOCLR = (1 << 22)));
  wr_cmd(0x22);
  wr_dat_start();
  for (j = 0; j < h; j++) {
    bitmap_ptr += w-1;
    for (i = 0; i < w; i++) {
      wr_dat_only(*bitmap_ptr--);
    }
    bitmap_ptr += w+1;
  }
  wr_dat_stop();
}












 

void GLCD_Bmp (unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned char *bmp) {
  unsigned int    i, j;
  unsigned short *bitmap_ptr = (unsigned short *)bmp;

  x = 320-x-w;
  wr_reg(0x50, y);                       
  wr_reg(0x51, y+h-1);                   
  wr_reg(0x52, x);                       
  wr_reg(0x53, x+w-1);                   

  wr_reg(0x20, y);
  wr_reg(0x21, x);
  ((0) ? (((LPC_GPIO_TypeDef *) ((0x2009C000UL) + 0x00000) )->FIOSET = (1 << 22)) : (((LPC_GPIO_TypeDef *) ((0x2009C000UL) + 0x00000) )->FIOCLR = (1 << 22)));
  wr_cmd(0x22);
  wr_dat_start();
  bitmap_ptr += (h*w)-1;
  for (j = 0; j < h; j++) {
    for (i = 0; i < w; i++) {
      wr_dat_only(*bitmap_ptr--);
    }
  }
  wr_dat_stop();
}

 
