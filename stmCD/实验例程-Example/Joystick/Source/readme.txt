
LandTiger Joystick Example
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
/****************************************************************/
路虎开发板 Joystick 五向导航键实验

这个例程是测试路虎开发板上的Joystick 五向导航键
将Joystick 五向导航键按下后的状态显示在板上的LD7....LD11上按下
Joystick 五向导航键相应的LED灯亮。
系统时钟设置在100MHZ
使用时，短路JP8跳线使能LED。
