#include "EXTI.h"
#include "NVIC.h"
#include "GPIO_Config.h"
#include "NRF24L01.h"


void Delay(u32 t);



void EXTI_Config(void)
{	
	/*����һ��EXTI_InitTypeDef ���͵Ľṹ�壬���ֽ�EXTI_InitStructure*/
	EXTI_InitTypeDef EXTI_InitStructure;

	/*��ʼ���ж���������*/
	NVIC_Config();	

	/* ����IO�ڵ��ж��� */
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource7);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource9);

	/*�ж���*/
	EXTI_InitStructure.EXTI_Line = EXTI_Line7|EXTI_Line9; 
	/*����ģʽ*/
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;

	/*�����ź�*/
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;//�����ش���

	/*ʹ���ж���*/
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;

	/*���ÿ⺯������ʼ��EXTI*/
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
