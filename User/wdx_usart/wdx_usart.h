#ifndef __USART_H
#define __USART_H

#include "stm32f10x.h" 
#include "stdio.h"	 

#define		RNumber				6
extern float kp;



//printf & scanf
#define		usart_printf		USART1
#define		usart_scanf			USART1

//USART1
#define		usart1_RCC_IO			(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO)
#define		usart1_RCC_USART1	RCC_APB2Periph_USART1
#define		usart1_baudrate		115200
#define		usart1_TX_port		GPIOA
#define		usart1_TX_pin			GPIO_Pin_9
#define		usart1_RX_port		GPIOA
#define		usart1_RX_pin			GPIO_Pin_10
/*
//USART2
#define		usart2_RCC_IO			(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO)
#define		usart2_RCC_USART2	RCC_APB1Periph_USART2
#define		usart2_baudrate		115200
#define		usart2_TX_port		GPIOA
#define		usart2_TX_pin			GPIOA_Pin_2
#define		usart2_RX_port		GPIOA
#define		usart2_RX_pin			GPIOA_Pin_3
//USART3
#define		usart3_RCC_IO			(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO)
#define		usart3_RCC_USART3	RCC_APB1Periph_USART3
#define		usart3_baudrate		115200
#define		usart3_TX_port		GPIOB
#define		usart3_TX_pin			GPIOB_Pin_10
#define		usart3_RX_port		GPIOB
#define		usart3_RX_pin			GPIOB_Pin_11
//注意串口4、5的IO口还没有修改
//UART4
#define		uart4_RCC_IO			(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO)
#define		uart4_RCC_UART4		RCC_APB1Periph_UART4
#define		uart4_baudrate		115200
#define		uart4_TX_port			GPIOB
#define		uart4_TX_pin			GPIOB_Pin_10
#define		uart4_RX_port			GPIOB
#define		uart4_RX_pin			GPIOB_Pin_11
//UART5
#define		uart5_RCC_IO			(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO)
#define		uart5_RCC_UART5		RCC_APB1Periph_UART5
#define		uart5_baudrate		115200
#define		uart5_TX_port			GPIOB
#define		uart5_TX_pin			GPIOB_Pin_10
#define		uart5_RX_port			GPIOB
#define		uart5_RX_pin			GPIOB_Pin_11
*/

void USART1_Config(void);   //初始化 配置USART1
/*
void USART2_Config(void);   //初始化 配置USART2
void USART3_Config(void);   //初始化 配置USART3
void UART4_Config(void);    //初始化 配置UART4
void UART5_Config(void);    //初始化 配置UART5
*/

void Usart_SendByte( USART_TypeDef * pUSARTx, char ch );
void Usart_SendString( USART_TypeDef * pUSARTx, char *str);

#endif	
