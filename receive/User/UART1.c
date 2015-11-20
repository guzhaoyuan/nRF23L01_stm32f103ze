/**
  ******************************************************************************
  * 文件名    USART.c 
  * 作者      miwu
  * 库版本    V3.5.0
  * 日期      2012-9-3
  * 实验平台
  ******************************************************************************
  * 功能描述:串口初始化
  *
  ****************************************************************************** 
*/  

#include "UART1.h"
#include <stdarg.h>
/**
  *函数名     USART_Config
  *描述		  串口初始化函数
  *输入		  无
  *输出		  无
  */
void USART1_Config(void)
{	
	
	GPIO_InitTypeDef GPIO_InitStructure;

    USART_InitTypeDef USART_InitStructure;
	
	/*使能复用时钟，使能串口1时钟*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA,ENABLE);
	
	/*A9 做TX*/ 
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /*A10 做RX */ 
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	/*配置USART1的工作模式*/
	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
										
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
										
	USART_InitStructure.USART_Parity = USART_Parity_No;
									
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;							
	
    USART_Init(USART1, &USART_InitStructure);//初始化外设 USARTx寄存器
    
    USART_Cmd(USART1, ENABLE);

	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
}

/*
 * 函数名：fputc
 * 描述  ：重定向c库函数printf到USART
 * 输入  ：无
 * 输出  ：无
 * 调用  ：由printf调用
 */
int fputc(int ch, FILE *f)
{
/* 将Printf内容发往串口 */
  USART_SendData(USART1, (unsigned char) ch);
  while (!(USART1->SR & USART_FLAG_TXE));
 
  return (ch);
}
/*
 * 函数名：USART1_Putc
 * 描述  ：将USART1_Putc（）内容打印到串口
 * 输入  ：无
 * 输出  ：无
 * 调用  ：无
 */
void USART1_Putc(unsigned char c)
{
    USART_SendData(USART1, c);
    while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET );
}
/*
 * 函数名：USART1_Puts
 * 描述  ：将USART1_Puts（）内容打印到串口
 * 输入  ：无
 * 输出  ：无
 * 调用  ：无
 */
void USART1_Puts(char * str)
{
    while(*str)
    {
        USART_SendData(USART1, *str++);
        /* Loop until the end of transmission */
        while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
    }
}

void USART1_IRQHandler(void)
{
	 u16 usarnum;
     
  if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
  {
     /* Disable USART1 RXNE Interrupt */
     USART_ITConfig(USART1, USART_IT_RXNE, DISABLE);
     usarnum=USART_ReceiveData(USART1);
     USART_SendData(USART1, usarnum);
     while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET); 
     USART_ITConfig( USART1,USART_IT_RXNE, ENABLE);
  }
}
/*
 * 函数名：itoa
 * 描述  ：将整形数据转换成字符串
 * 输入  ：-radix =10 表示10进制，其他结果为0
 *         -value 要转换的整形数
 *         -buf 转换后的字符串
 *         -radix = 10
 * 输出  ：无
 * 返回  ：无
 * 调用  ：被USART1_printf()调用
 */
static char *itoa(int value, char *string, int radix)
{
    int     i, d;
    int     flag = 0;
    char    *ptr = string;

    /* This implementation only works for decimal numbers. */
    if (radix != 10)
    {
        *ptr = 0;
        return string;
    }

    if (!value)
    {
        *ptr++ = 0x30;
        *ptr = 0;
        return string;
    }

    /* if this is a negative value insert the minus sign. */
    if (value < 0)
    {
        *ptr++ = '-';

        /* Make the value positive. */
        value *= -1;
    }

    for (i = 10000; i > 0; i /= 10)
    {
        d = value / i;

        if (d || flag)
        {
            *ptr++ = (char)(d + 0x30);
            value -= (d * i);
            flag = 1;
        }
    }

    /* Null terminate the string. */
    *ptr = 0;

    return string;

} /* NCL_Itoa */

/*
 * 函数名：USART1_printf
 * 描述  ：格式化输出，类似于C库中的printf，但这里没有用到C库
 * 输入  ：-USARTx 串口通道，这里只用到了串口1，即USART1
 *		     -Data   要发送到串口的内容的指针
 *			   -...    其他参数
 * 输出  ：无
 * 返回  ：无 
 * 调用  ：外部调用
 *         典型应用USART1_printf( USART1, "\r\n this is a demo \r\n" );
 *            		 USART1_printf( USART1, "\r\n %d \r\n", i );
 *            		 USART1_printf( USART1, "\r\n %s \r\n", j );
 */
void USART1_printf(USART_TypeDef* USARTx, uint8_t *Data,...)
{
	const char *s;
  int d;   
  char buf[16];

  va_list ap;
  va_start(ap, Data);

	while ( *Data != 0)     // 判断是否到达字符串结束符
	{				                          
		if ( *Data == 0x5c )  //'\'
		{									  
			switch ( *++Data )
			{
				case 'r':							          //回车符
					USART_SendData(USARTx, 0x0d);
					Data ++;
					break;

				case 'n':							          //换行符
					USART_SendData(USARTx, 0x0a);	
					Data ++;
					break;
				
				default:
					Data ++;
				    break;
			}			 
		}
		else if ( *Data == '%')
		{									  //
			switch ( *++Data )
			{				
				case 's':										  //字符串
					s = va_arg(ap, const char *);
          for ( ; *s; s++) 
					{
						USART_SendData(USARTx,*s);
						while( USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET );
          }
					Data++;
          break;

        case 'd':										//十进制
          d = va_arg(ap, int);
          itoa(d, buf, 10);
          for (s = buf; *s; s++) 
					{
						USART_SendData(USARTx,*s);
						while( USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET );
          }
					Data++;
          break;
				 default:
						Data++;
				    break;
			}		 
		} /* end of else if */
		else USART_SendData(USARTx, *Data++);
		while( USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET );
	}
}
