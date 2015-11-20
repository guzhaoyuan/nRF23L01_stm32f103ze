#include "NVIC.h"

void NVIC_Config(void)
{	
	/*����һ��NVIC_InitTypeDef ���͵Ľṹ�壬���ֽ�NVIC_InitStructure*/ 
	NVIC_InitTypeDef NVIC_InitStructure;
	
	/* �����ж�ʹ�����0*/
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	/*����ѡ�е��ж�����*/
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
	/*������ռ���ȼ�*/
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	/*������Ӧ���ȼ�*/
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	/*ʹ���ж�����*/
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	/*���ÿ⺯������ʼ���ж�����*/
	NVIC_Init(&NVIC_InitStructure);
	
//	/* �����ж�ʹ�����0*/
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
//	/*����ѡ�е��ж�����*/
//	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
//	/*������ռ���ȼ�*/
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
//	/*������Ӧ���ȼ�*/
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
//	/*ʹ���ж�����*/
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//	/*���ÿ⺯������ʼ���ж�����*/
//	NVIC_Init(&NVIC_InitStructure);
						 
	
}


