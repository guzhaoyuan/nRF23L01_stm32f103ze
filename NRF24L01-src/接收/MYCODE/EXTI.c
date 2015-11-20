#include "EXTI.h"
#include "NVIC.h"
#include "GPIO_Config.h"
#include "NRF24L01.h"


void Delay(u32 t);



void EXTI_Config(void)
{	
	/*定义一个EXTI_InitTypeDef 类型的结构体，名字叫EXTI_InitStructure*/
	EXTI_InitTypeDef EXTI_InitStructure;

	/*初始化中断向量函数*/
	NVIC_Config();	

	/* 连接IO口到中断线 */
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource7);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource9);

	/*中断线*/
	EXTI_InitStructure.EXTI_Line = EXTI_Line7|EXTI_Line9; 
	/*触发模式*/
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;

	/*触发信号*/
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;//上升沿触发

	/*使能中断线*/
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;

	/*调用库函数，初始化EXTI*/
	EXTI_Init(&EXTI_InitStructure);

}

void EXTI9_5_IRQHandler(void)
{   
		if(EXTI_GetITStatus(EXTI_Line7) != RESET)
	{
		EXTI_ClearITPendingBit(EXTI_Line7);
		LED1_ON;
		Delay(2250);							 									 						
	}
		if(EXTI_GetITStatus(EXTI_Line9) != RESET)
	{
		EXTI_ClearITPendingBit(EXTI_Line9);
		LED1_OFF;
		Delay(2250);						 									 						
	}
		
}
void Delay(u32 t)
{	u32 i,j;
	for(i=0;i<t;i++)
	for(j=0;j<t;j++);
}
