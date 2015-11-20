#ifndef __GPIO_Config_H
#define	__GPIO_Config_H

#include "stm32f10x.h"

#define   LED1_ON        GPIO_ResetBits(GPIOC, GPIO_Pin_0)
#define   LED1_OFF       GPIO_SetBits(GPIOC, GPIO_Pin_0)
#define   NRF_CE_1		 GPIO_SetBits(GPIOA, GPIO_Pin_4)
#define   NRF_CE_0		 GPIO_ResetBits(GPIOA, GPIO_Pin_4)
#define   NRF_CSN_1		 GPIO_SetBits(GPIOC, GPIO_Pin_4)
#define   NRF_CSN_0		 GPIO_ResetBits(GPIOC, GPIO_Pin_4)
#define   NRF_SCK_1		 GPIO_SetBits(GPIOA, GPIO_Pin_5)
#define   NRF_SCK_0		 GPIO_ResetBits(GPIOA, GPIO_Pin_5)
#define   NRF_MOSI_1	 GPIO_SetBits(GPIOA, GPIO_Pin_7)
#define   NRF_MOSI_0 	 GPIO_ResetBits(GPIOA, GPIO_Pin_7)

#define   NRF_MISO		 GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_6)
#define	  NRF_IRQ 		 GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_5)



void GPIO_Config(void);
#endif
