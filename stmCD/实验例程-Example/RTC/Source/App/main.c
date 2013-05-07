/****************************************Copyright (c)****************************************************
**                                 http://www.PowerAVR.com
**								   http://www.PowerMCU.com
**--------------File Info---------------------------------------------------------------------------------
** File name:           main.c
** Last modified Date:  2010-05-12
** Last Version:        V1.00
** Descriptions:        The main() function example template
**
**--------------------------------------------------------------------------------------------------------
** Created by:          PowerAVR
** Created date:        2010-05-10
** Version:             V1.00
** Descriptions:        编写示例代码
**
**--------------------------------------------------------------------------------------------------------       
*********************************************************************************************************/
#include "lpc17xx.h"
#include "rtc.h"
#include "uart.h"

extern volatile uint32_t alarm_on;
RTCTime local_time, alarm_time, current_time;


/*********************************************************************************************************
** Function name:       Delay
** Descriptions:        软件延时
** input parameters:    ulTime
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
void Delay (uint32_t Time)
{
    uint32_t i;
    
    i = 0;
    while (Time--) {
        for (i = 0; i < 5000; i++);
    }
}

/*****************************************************************************
**   Main Function  main()
******************************************************************************/
int main (void)
{
  SystemInit();		    		
  
  UART0_Init();
  /* Initialize RTC module */
  RTCInit();

  local_time.RTC_Sec = 0;
  local_time.RTC_Min = 0;
  local_time.RTC_Hour = 0;
  local_time.RTC_Mday = 8;
  local_time.RTC_Wday = 3;
  local_time.RTC_Yday = 12;		/* current date 05/12/2010 */
  local_time.RTC_Mon = 5;
  local_time.RTC_Year = 2010;
  RTCSetTime( local_time );		/* Set local time */

  alarm_time.RTC_Sec = 0;
  alarm_time.RTC_Min = 0;
  alarm_time.RTC_Hour = 0;
  alarm_time.RTC_Mday = 1;
  alarm_time.RTC_Wday = 0;
  alarm_time.RTC_Yday = 1;		/* alarm date 01/01/2011 */
  alarm_time.RTC_Mon = 1;
  alarm_time.RTC_Year = 2011;
  RTCSetAlarm( alarm_time );		/* set alarm time */

  NVIC_EnableIRQ(RTC_IRQn);

  /* mask off alarm mask, turn on IMYEAR in the counter increment interrupt
  register */
  RTCSetAlarmMask(AMRSEC|AMRMIN|AMRHOUR|AMRDOM|AMRDOW|AMRDOY|AMRMON|AMRYEAR);
  LPC_RTC->CIIR = IMMIN | IMYEAR;
  /* 2007/01/01/00:00:00 is the alarm on */
    
  RTCStart();

  while (1) 
  {					/* Loop forever */
	current_time = RTCGetTime();
	if ( alarm_on != 0 )
	{
	  alarm_on = 0;
	  /* Get current time when alarm is on */
	  current_time = RTCGetTime();	
	}
	UART0_SendString("现在的时间是：");
	UART0_SendChar(current_time.RTC_Year);
	UART0_SendByte('/');
	UART0_SendChar(current_time.RTC_Mon);
	UART0_SendByte('/');
	UART0_SendChar(current_time.RTC_Yday);
	UART0_SendByte('/');
	UART0_SendChar(current_time.RTC_Hour);
	UART0_SendByte(':');
	UART0_SendChar(current_time.RTC_Min);
	UART0_SendByte(':');
	UART0_SendChar(current_time.RTC_Sec);
	UART0_SendByte('\n');
	Delay(3000);
  }

}

/******************************************************************************
**                            End Of File
******************************************************************************/
