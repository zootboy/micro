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
#include "LPC17xx.h"
#include "uart.h"

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

int main(void)
{
	SystemInit();

	UART3_Init();

    while (1) 
	{  
		UART3_SendString("路虎（LandTiger）RS485测试程序\n");	 /* 将数据发送到串口显示         */
		UART3_SendByte('\n');
        Delay(3000);
    }
}
