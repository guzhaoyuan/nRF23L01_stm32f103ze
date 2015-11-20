/* 接收端程序

本程序是接收程序，本不用按键中断，但是为了调试方便，所以才加了按键。
程序版本号：V1030
*/



#include "stm32f10x.h"
#include "GPIO_Config.h"
#include "NVIC.h"
#include "EXTI.h"
#include "NRF24L01.h"




int main(void)
{
	u8 RxBuf[32];		  //接收缓冲区
	GPIO_Config();			//初始化所用的IO口
	EXTI_Config();		   //  中断程序配置
	init_NRF24L01();	   //2.4G模块初始化
	LED1_OFF;
	Delay(250);
	while(1)
	{
		SetRX_Mode();			//接收数据
		if(nRF24L01_RxPacket(RxBuf))
		{
			if(RxBuf[4]==0xcf)
			{
			LED1_ON;
			}
			else if(RxBuf[4]==0xfc)
			{
			LED1_OFF;	
			}
		}
	}
}
