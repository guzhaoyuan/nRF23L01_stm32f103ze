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
	
	GPIO_Config();			//��ʼ�����õ�IO��
	EXTI_Config();		   //  �жϳ�������
	USART1_Config();
	init_NRF24L01();	   //2.4Gģ���ʼ��
	USART1_printf( USART1, "\r\n init complete \r\n" );
	LED1_OFF;
	Delay(250);
	SetRX_Mode();	//��������
	while(1)
	{
		
		//while(!nRF24L01_RxPacket(RxBuf)){};
		
	}
}
