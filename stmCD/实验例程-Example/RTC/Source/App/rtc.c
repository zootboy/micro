/****************************************Copyright (c)****************************************************
**                                 http://www.PowerAVR.com
**								   http://www.PowerMCU.com
**--------------File Info---------------------------------------------------------------------------------
** File name:           rtc.c
** Last modified Date:  2010-05-12
** Last Version:        V1.00
** Descriptions:        
**
**--------------------------------------------------------------------------------------------------------
** Created by:          PowerAVR
** Created date:        2010-05-10
** Version:             V1.00
** Descriptions:        ±àÐ´Ê¾Àý´úÂë
**
**--------------------------------------------------------------------------------------------------------       
*********************************************************************************************************/
#include "lpc17xx.h"
#include "rtc.h"

volatile uint32_t alarm_on = 0;

/*****************************************************************************
** Function name:		RTC_IRQHandler
**
** Descriptions:		RTC interrupt handler, it executes based on the
**						the alarm setting
**
** parameters:			None
** Returned value:		None
** 
*****************************************************************************/
void RTC_IRQHandler (void) 
{  
  LPC_RTC->ILR |= ILR_RTCCIF;		/* clear interrupt flag */
  alarm_on = 1;
  return;
}

/*****************************************************************************
** Function name:		RTCInit
**
** Descriptions:		Initialize RTC timer
**
** parameters:			None
** Returned value:		None
** 
*****************************************************************************/
void RTCInit( void )
{
  alarm_on = 0;

  /* Enable CLOCK into RTC */
  LPC_SC->PCONP |= (1 << 9);

  /* If RTC is stopped, clear STOP bit. */
  if ( LPC_RTC->RTC_AUX & (0x1<<4) )
  {
	LPC_RTC->RTC_AUX |= (0x1<<4);	
  }
  
  /*--- Initialize registers ---*/    
  LPC_RTC->AMR = 0;
  LPC_RTC->CIIR = 0;
  LPC_RTC->CCR = 0;
  return;
}

/*****************************************************************************
** Function name:		RTCStart
**
** Descriptions:		Start RTC timer
**
** parameters:			None
** Returned value:		None
** 
*****************************************************************************/
void RTCStart( void ) 
{
  /*--- Start RTC counters ---*/
  LPC_RTC->CCR |= CCR_CLKEN;
  LPC_RTC->ILR = ILR_RTCCIF;
  return;
}

/*****************************************************************************
** Function name:		RTCStop
**
** Descriptions:		Stop RTC timer
**
** parameters:			None
** Returned value:		None
** 
*****************************************************************************/
void RTCStop( void )
{   
  /*--- Stop RTC counters ---*/
  LPC_RTC->CCR &= ~CCR_CLKEN;
  return;
} 

/*****************************************************************************
** Function name:		RTC_CTCReset
**
** Descriptions:		Reset RTC clock tick counter
**
** parameters:			None
** Returned value:		None
** 
*****************************************************************************/
void RTC_CTCReset( void )
{   
  /*--- Reset CTC ---*/
  LPC_RTC->CCR |= CCR_CTCRST;
  return;
}

/*****************************************************************************
** Function name:		RTCSetTime
**
** Descriptions:		Setup RTC timer value
**
** parameters:			None
** Returned value:		None
** 
*****************************************************************************/
void RTCSetTime( RTCTime Time ) 
{
  LPC_RTC->SEC = Time.RTC_Sec;
  LPC_RTC->MIN = Time.RTC_Min;
  LPC_RTC->HOUR = Time.RTC_Hour;
  LPC_RTC->DOM = Time.RTC_Mday;
  LPC_RTC->DOW = Time.RTC_Wday;
  LPC_RTC->DOY = Time.RTC_Yday;
  LPC_RTC->MONTH = Time.RTC_Mon;
  LPC_RTC->YEAR = Time.RTC_Year;    
  return;
}

/*****************************************************************************
** Function name:		RTCSetAlarm
**
** Descriptions:		Initialize RTC timer
**
** parameters:			None
** Returned value:		None
** 
*****************************************************************************/
void RTCSetAlarm( RTCTime Alarm ) 
{   
  LPC_RTC->ALSEC = Alarm.RTC_Sec;
  LPC_RTC->ALMIN = Alarm.RTC_Min;
  LPC_RTC->ALHOUR = Alarm.RTC_Hour;
  LPC_RTC->ALDOM = Alarm.RTC_Mday;
  LPC_RTC->ALDOW = Alarm.RTC_Wday;
  LPC_RTC->ALDOY = Alarm.RTC_Yday;
  LPC_RTC->ALMON = Alarm.RTC_Mon;
  LPC_RTC->ALYEAR = Alarm.RTC_Year;    
  return;
}

/*****************************************************************************
** Function name:		RTCGetTime
**
** Descriptions:		Get RTC timer value
**
** parameters:			None
** Returned value:		The data structure of the RTC time table
** 
*****************************************************************************/
RTCTime RTCGetTime( void ) 
{
  RTCTime LocalTime;
    
  LocalTime.RTC_Sec = LPC_RTC->SEC;
  LocalTime.RTC_Min = LPC_RTC->MIN;
  LocalTime.RTC_Hour = LPC_RTC->HOUR;
  LocalTime.RTC_Mday = LPC_RTC->DOM;
  LocalTime.RTC_Wday = LPC_RTC->DOW;
  LocalTime.RTC_Yday = LPC_RTC->DOY;
  LocalTime.RTC_Mon = LPC_RTC->MONTH;
  LocalTime.RTC_Year = LPC_RTC->YEAR;
  return ( LocalTime );    
}

/*****************************************************************************
** Function name:		RTCSetAlarmMask
**
** Descriptions:		Set RTC timer alarm mask
**
** parameters:			Alarm mask setting
** Returned value:		None
** 
*****************************************************************************/
void RTCSetAlarmMask( uint32_t AlarmMask ) 
{
  /*--- Set alarm mask ---*/    
  LPC_RTC->AMR = AlarmMask;
  return;
}

/*****************************************************************************
**                            End Of File
******************************************************************************/

