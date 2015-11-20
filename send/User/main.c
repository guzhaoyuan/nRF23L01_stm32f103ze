/*发送端程序

PC9和PC7为两个按键，分别控制接收端LED的开与关。	 PS：也同时控制发送端哦！
按键为中断模式。
程序版本号：V1030
*/
#include "stm32f10x.h"
#include "GPIO_Config.h"
#include "NVIC.h"
#include "EXTI.h"
#include "NRF24L01.h"

u8 TxBuf[32]=
{
0x01,0x02,0x03,0x4,0x05,0x06,0x07,0x08,
0x09,0x10,0x11,0x12,0x13,0x14,0x15,0x16,
0x17,0x18,0x19,0x20,0x21,0x22,0x23,0x24,
0x25,0x26,0x27,0x28,0x29,0x30,0x31,0x32,
};

int main(void)
{
	GPIO_Config();		 //IO口初始化
	EXTI_Config();		 //中断配置
	USART1_Config();
	init_NRF24L01();	  //2.4G模块初始化
	USART1_printf( USART1, "\r\n init complete \r\n" );
	
	nRF24L01_TxPacket(TxBuf);
	Delay(250);
	while(1)
	{
//		LED1_ON;
//		nRF24L01_TxPacket(TxBuf);
//		LED1_OFF;
//		Delay(2250);
		
	}
}
