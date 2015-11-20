#include "EXTI.h"
#include "NVIC.h"
#include "GPIO_Config.h"
#include "NRF24L01.h"
//#include "stm32f10x_conf.h"

void Delay(u32 t);
u8 RxBuf[32];		  //接收缓冲区


void EXTI_Config(void)
{	
	/*定义一个EXTI_InitTypeDef 类型的结构体，名字叫EXTI_InitStructure*/
	EXTI_InitTypeDef EXTI_InitStructure;

	/*初始化中断向量函数*/
	NVIC_Config();	

	/* 连接IO口到中断线 */
	//GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource0);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource5);

	/*中断线*/
	EXTI_InitStructure.EXTI_Line = EXTI_Line5; 
	/*触发模式*/
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;

	/*触发信号*/
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;//上升沿触发

	/*使能中断线*/
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;

	/*调用库函数，初始化EXTI*/
	EXTI_Init(&EXTI_InitStructure);

}

void EXTI9_5_IRQHandler(void)
{   
		if(EXTI_GetITStatus(EXTI_Line5) != RESET)
	{
		EXTI_ClearITPendingBit(EXTI_Line5);
		LED1_ON;
//		Delay(2250);
	//	SPI_RW_Reg(NRF_WRITE_REG+STATUS,0XFF);
		//USART1_printf( USART1, "\r\n receive somthing \r\n" );
		if(nRF24L01_RxPacket(RxBuf))
		{
			if(RxBuf[4]==0xcf)
			{
			USART1_printf( USART1, "cf\r\n" );
			LED1_ON;
			}
			else if(RxBuf[4]==0xfc)
			{
			USART1_printf( USART1, "fc\r\n" );
			LED1_OFF;	
			}
		}
		SetRX_Mode();	//接收数据
		Delay(2250);				
		LED1_OFF;
	}
		
}

//void EXTI0_IRQHandler(void)
//{
//	if(EXTI_GetITStatus(EXTI_Line0) != RESET)
//		{
//			EXTI_ClearITPendingBit(EXTI_Line0);
//			LED1_OFF;
//			Delay(2250);						 									 						
//		}
//}

void Delay(u32 t)
{	u32 i,j;
	for(i=0;i<t;i++)
	for(j=0;j<t;j++);
}
