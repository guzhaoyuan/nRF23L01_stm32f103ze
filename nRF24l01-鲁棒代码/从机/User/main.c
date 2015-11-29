/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   2.4g����ģ��/nrf24l01+/slave ����
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ�� iSO STM32 ������ 
  * ��̳    :http://www.chuxue123.com
  * �Ա�    :http://firestm32.taobao.com
  *
  ******************************************************************************
  */
  
#include "stm32f10x.h"
#include "bsp_usart1.h"
#include "bsp_spi_nrf.h"

u8 status;		 //�����жϽ���/����״̬
u8 txbuf[4];	 //���ͻ���
u8 rxbuf[4];	 //���ջ���
u8 i; 

 /**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{      
  /* ����1��ʼ�� */
  USART1_Config(); 

  /*SPI�ӿڳ�ʼ��*/   
  SPI_NRF_Init(); 

  printf("\r\n ����һ�� NRF24L01 ���ߴ���ʵ�� \r\n");
  printf("\r\n �������ߴ��� �ӻ��� �ķ�����Ϣ\r\n");
  printf("\r\n   ���ڼ��NRF��MCU�Ƿ��������ӡ�����\r\n");

  /*���NRFģ����MCU������*/
  status = NRF_Check();   		
  if(status == SUCCESS)	   
    printf("\r\n      NRF��MCU���ӳɹ�\r\n");  
  else	  
    printf("\r\n   ���ڼ��NRF��MCU�Ƿ��������ӡ�����\r\n");

  while(1)
  {  		 	
    printf("\r\n �ӻ��� �������ģʽ\r\n"); 
    NRF_RX_Mode();

    /*�ȴ���������*/
    status = NRF_Rx_Dat(rxbuf);

    /*�жϽ���״̬*/
    if(status == RX_DR)
    {
      for(i=0;i<4;i++)
      {	
        printf("\r\n �ӻ��� ���յ� ������ ���͵�����Ϊ��%d \r\n",rxbuf[i]); 
        /*�ѽ��յ�����+1���͸�����*/
        rxbuf[i]+=1;	  
        txbuf[i] = rxbuf[i]; 
      }
    }   
    printf("\r\n �ӻ��� ������Ӧ����ģʽ\r\n"); 
    NRF_TX_Mode();

//    /*�����ط���ֱ�����ͳɹ�*/	  
//    do
//    { 	  
//      status = NRF_Tx_Dat(txbuf);
//    }while(status == MAX_RT);
  } 
}
/*********************************************END OF FILE**********************/
