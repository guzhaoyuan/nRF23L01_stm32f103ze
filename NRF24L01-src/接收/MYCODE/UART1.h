#ifndef __UART1_H
#define __UART1_H

#include "stm32f10x.h"
#include <stdio.h>

void USART1_Config(void);	
int fputc(int ch, FILE *f);
void USART1_Putc(u8 c);
void USART1_Puts(char * str);
void USART1_IRQHandler(void);
void USART1_printf(USART_TypeDef* USARTx, uint8_t *Data,...);
#endif
