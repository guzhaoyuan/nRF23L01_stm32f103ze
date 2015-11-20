#include "EXTI.h"
#include "NVIC.h"
#include "GPIO_Config.h"
#include "NRF24L01.h"
//#include "stm32f10x_conf.h"

void Delay(u32 t);
u8 RxBuf[32];		  //���ջ�����


void EXTI_Config(void)
{	
	/*����һ��EXTI_InitTypeDef ���͵Ľṹ�壬���ֽ�EXTI_InitStructure*/
	EXTI_InitTypeDef EXTI_InitStructure;

	/*��ʼ���ж���������*/
	NVIC_Config();	

	/* ����IO�ڵ��ж��� */
	//GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource0);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource5);

	/*�ж���*/
	EXTI_InitStructure.EXTI_Line = EXTI_Line5; 
	/*����ģʽ*/
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;

	/*�����ź�*/
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;//�����ش���

	/*ʹ���ж���*/
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;

	/*���ÿ⺯������ʼ��EXTI*/
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
		SetRX_Mode();	//��������
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
