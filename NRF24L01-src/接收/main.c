/* ���ն˳���

�������ǽ��ճ��򣬱����ð����жϣ�����Ϊ�˵��Է��㣬���Բż��˰�����
����汾�ţ�V1030
*/



#include "stm32f10x.h"
#include "GPIO_Config.h"
#include "NVIC.h"
#include "EXTI.h"
#include "NRF24L01.h"




int main(void)
{
	u8 RxBuf[32];		  //���ջ�����
	GPIO_Config();			//��ʼ�����õ�IO��
	EXTI_Config();		   //  �жϳ�������
	init_NRF24L01();	   //2.4Gģ���ʼ��
	LED1_OFF;
	Delay(250);
	while(1)
	{
		SetRX_Mode();			//��������
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
