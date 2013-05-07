This example project uses CMSIS and demonstrates 
the use of Systick in interrupt driven mode

LandTiger GPIO Example
/*********************** Design by PowerAVR *********************/
Design: www.PowerMCU.com
		www.PowerAVR.com
Board:  LandTiger Evaluation Board
Device: LPC1768
/*********************** Design by PowerAVR *********************/

Example functionality:                                                   
 - Clock Settings:
   - XTAL    =           12.00 MHz
   - SYSCLK  =          100.00 MHz

-- CMSIS ---------------------------------------------
SystemInit       called from startup_LPC17xx.s
SystemCoreClock  is 100000000Hz
SysTick          runs in interrupt mode

JP8 jumper 
			Open:   LED disabled    
			Short:	LED active (default)
/****************************************************************/
路虎开发板 GPIO实验

这个例程是将路虎开发板上的八个LED轮流点亮100毫秒，
采用SYStick 定时器中断方式做延时  系统时钟设置在100MHZ
使用时，短路JP8跳线使能LED。
