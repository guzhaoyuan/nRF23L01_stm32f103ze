#include "EXTI.h"
#include "NVIC.h"
#include "GPIO_Config.h"
#include "NRF24L01.h"
//#include "stm32f10x_conf.h"

void Delay(u32 t);



void EXTI_Config(void)
{	
	/*����һ��EXTI_InitTypeDef ���͵Ľṹ�壬���ֽ�EXTI_InitStructure*/
	EXTI_InitTypeDef EXTI_InitStructure;

	/*��ʼ���ж���������*/
	NVIC_Config();	

	/* ����IO�ڵ��ж��� */
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource0);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource13);

	/*�ж���*/
	EXTI_InitStructure.EXTI_Line = EXTI_Line0|EXTI_Line13; 
	/*����ģʽ*/
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;

	/*�����ź�*/
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;//�����ش���

	/*ʹ���ж���*/
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;

	/*���ÿ⺯������ʼ��EXTI*/
	EXTI_Init(&EXTI_InitStructure);

}

void EXTI15_10_IRQHandler(void)
{   
		if(EXTI_GetITStatus(EXTI_Line13) != RESET)
	{
		EXTI_ClearITPendingBit(EXTI_Line13);
		TxBuf[4]=0xcf;
		nRF24L01_TxPacket(TxBuf);
		LED1_ON;
		USART1_printf( USART1, "cf sent \r\n" );
		//LED1_OFF;
//		Delay(2250);
	//	SPI_RW_Reg(NRF_WRITE_REG+STATUS,0XFF);
		Delay(2250);	
			init_NRF24L01();
	}
		
}

void EXTI0_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line0) != RESET)
		{
			EXTI_ClearITPendingBit(EXTI_Line0);
			TxBuf[4]=0xfc;
			nRF24L01_TxPacket(TxBuf);
			LED1_OFF;
			USART1_printf( USART1, "\r\n fc sent \r\n" );
			Delay(2250);						 									 						
		}
}

void Delay(u32 t)
{	u32 i,j;
	for(i=0;i<t;i++)
	for(j=0;j<t;j++);
}
