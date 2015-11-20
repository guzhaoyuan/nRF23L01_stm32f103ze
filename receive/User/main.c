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
	
	GPIO_Config();			//初始化所用的IO口
	EXTI_Config();		   //  中断程序配置
	USART1_Config();
	init_NRF24L01();	   //2.4G模块初始化
	USART1_printf( USART1, "\r\n init complete \r\n" );
	LED1_OFF;
	Delay(250);
	SetRX_Mode();	//接收数据
	while(1)
	{
		
		//while(!nRF24L01_RxPacket(RxBuf)){};
		
	}
}
