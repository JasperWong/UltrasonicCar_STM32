#include "wdx_usart.h"
#include "sys.h"
#include "delay.h"

float kp=30.0;
uint8_t ReceiveArray[RNumber];
static uint8_t count=0;

//中断优先级配置
void NVIC_USART_Configuration(void)
{
	NVIC_InitTypeDef    NVIC_InitStructure; 					   //定义用于配置中断的结构体变量

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);                //中断优先级分组  抢占式优先级别设置为2位；响应优先级占2位
	
	//串口1中断优先级设置
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;             	//通道设置为串口1中断  
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;	   		//抢占优先级1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;            	//指定响应优先级别1
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	              	//打开中断
	NVIC_Init(&NVIC_InitStructure);							       				

/*
	//串口2中断优先级设置
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;             	//通道设置为串口2中断  
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	   		//抢占优先级1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;            	//指定响应优先级别1
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	              	//打开中断
	NVIC_Init(&NVIC_InitStructure);							       				

	//串口3中断优先级设置
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;             	//通道设置为串口3中断  
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	   		//抢占优先级1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;            	//指定响应优先级别1
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	              	//打开中断
	NVIC_Init(&NVIC_InitStructure);							       				

	//串口4中断优先级设置
	NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;             	//通道设置为串口4中断  
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	   		//抢占优先级1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;            	//指定响应优先级别1
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	              	//打开中断
	NVIC_Init(&NVIC_InitStructure);							       				

	//串口5中断优先级设置
	NVIC_InitStructure.NVIC_IRQChannel = UART5_IRQn;             	//通道设置为串口5中断  
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	   		//抢占优先级1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;            	//指定响应优先级别1
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	              	//打开中断
	NVIC_Init(&NVIC_InitStructure);
*/	
}

//串口1初始化
void USART1_Config(void)
{
	GPIO_InitTypeDef     GPIO_InitStructure;   
	USART_InitTypeDef    USART_InitStructure; 

	RCC_APB2PeriphClockCmd(usart1_RCC_IO, ENABLE);					//打开GPIOA时钟和GPIOA复用时钟
	RCC_APB2PeriphClockCmd(usart1_RCC_USART1, ENABLE);			//打开串口复用时钟
	
	USART_DeInit(USART1);										//复位串口1

	//将USART1 Tx（发送脚）的GPIO配置为推挽复用模式
	GPIO_InitStructure.GPIO_Pin = usart1_TX_pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(usart1_TX_port, &GPIO_InitStructure);
														  
	//将USART Rx（接收脚）的GPIO配置为浮空输入模式
	GPIO_InitStructure.GPIO_Pin = usart1_RX_pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;		//浮空输入
	GPIO_Init(usart1_RX_port, &GPIO_InitStructure);	

	//配置USART1参数
	USART_InitStructure.USART_BaudRate             = usart1_baudrate;				 					//波特率设置：115200
	USART_InitStructure.USART_WordLength           = USART_WordLength_8b;			 				//数据位数设置：8位
	USART_InitStructure.USART_StopBits             = USART_StopBits_1;				 				//停止位设置：1位
	USART_InitStructure.USART_Parity               = USART_Parity_No;				 					//是否奇偶校验：无
	USART_InitStructure.USART_HardwareFlowControl  = USART_HardwareFlowControl_None; 	//硬件流控制模式设置：没有使能
	USART_InitStructure.USART_Mode                 = USART_Mode_Rx | USART_Mode_Tx;	 	//接收与发送都使能
	USART_Init(USART1, &USART_InitStructure);																					//初始化USART1

  
	NVIC_USART_Configuration();
	//发送中断和接收中断
//	USART_ITConfig(USART1, USART_IT_TXE, ENABLE);											// 使能指定的USART1发送中断;
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);										// 使能指定的USART1接收中断;
  USART_ClearFlag(USART1, USART_FLAG_TC);														//清串口1发送标志
	
	USART_Cmd(USART1, ENABLE);																					//使能 USART1

	//如下语句解决第1个字节无法正确发送出去的问题
  USART_ClearFlag(USART1, USART_FLAG_TC);                //清串口1发送标志
}

/*
//串口2初始化
void USART2_Config(void)
{
	GPIO_InitTypeDef     GPIO_InitStructure;   
	USART_InitTypeDef    USART_InitStructure; 

	RCC_APB2PeriphClockCmd(usart2_RCC_IO, ENABLE);
	RCC_APB1PeriphClockCmd(usart2_RCC_USART2, ENABLE);
	
	USART_DeInit(USART2);										//复位串口2

	//将USART2 Tx（发送脚）的GPIO配置为推挽复用模式
	GPIO_InitStructure.GPIO_Pin = usart2_TX_pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(usart2_TX_port, &GPIO_InitStructure);
														  
	//将USART Rx（接收脚）的GPIO配置为浮空输入模式
	GPIO_InitStructure.GPIO_Pin = usart2_RX_pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;		//浮空输入
	GPIO_Init(usart2_RX_port, &GPIO_InitStructure);	

	//配置USART2参数
	USART_InitStructure.USART_BaudRate             = usart2_baudrate;				 					//波特率设置：115200
	USART_InitStructure.USART_WordLength           = USART_WordLength_8b;			 				//数据位数设置：8位
	USART_InitStructure.USART_StopBits             = USART_StopBits_1;				 				//停止位设置：1位
	USART_InitStructure.USART_Parity               = USART_Parity_No;				 					//是否奇偶校验：无
	USART_InitStructure.USART_HardwareFlowControl  = USART_HardwareFlowControl_None; 	//硬件流控制模式设置：没有使能
	USART_InitStructure.USART_Mode                 = USART_Mode_Rx | USART_Mode_Tx;	 	//接收与发送都使能
	USART_Init(USART2, &USART_InitStructure);																					//初始化USART2

	NVIC_Configuration();
  //发送中断和接收中断
	//USART_ITConfig(USART2, USART_IT_TXE, ENABLE);										// 使能指定的USART2发送中断;
  USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);										// 使能指定的USART2接收中断;
  USART_ClearFlag(USART2, USART_FLAG_TC);														//清串口2发送标志
	
	USART_Cmd(USART2, ENABLE);																					//使能 USART2
	
	//如下语句解决第1个字节无法正确发送出去的问题
  USART_ClearFlag(USART2, USART_FLAG_TC);                //清串口2发送标志
}
//串口3初始化
void USART3_Config(void)
{
	GPIO_InitTypeDef     GPIO_InitStructure;   
	USART_InitTypeDef    USART_InitStructure; 

	RCC_APB2PeriphClockCmd(usart3_RCC_IO, ENABLE);
	RCC_APB1PeriphClockCmd(usart3_RCC_USART3, ENABLE);
	
	USART_DeInit(USART3);										//复位串口3

	//将USART3 Tx（发送脚）的GPIO配置为推挽复用模式
	GPIO_InitStructure.GPIO_Pin = usart3_TX_pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(usart3_TX_port, &GPIO_InitStructure);
														  
	//将USART Rx（接收脚）的GPIO配置为浮空输入模式
	GPIO_InitStructure.GPIO_Pin = usart3_RX_pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;		//浮空输入
	GPIO_Init(usart3_RX_port, &GPIO_InitStructure);	

	//配置USART3参数
	USART_InitStructure.USART_BaudRate             = usart3_baudrate;				 					//波特率设置：115200
	USART_InitStructure.USART_WordLength           = USART_WordLength_8b;			 				//数据位数设置：8位
	USART_InitStructure.USART_StopBits             = USART_StopBits_1;				 				//停止位设置：1位
	USART_InitStructure.USART_Parity               = USART_Parity_No;				 					//是否奇偶校验：无
	USART_InitStructure.USART_HardwareFlowControl  = USART_HardwareFlowControl_None; 	//硬件流控制模式设置：没有使能
	USART_InitStructure.USART_Mode                 = USART_Mode_Rx | USART_Mode_Tx;	 	//接收与发送都使能
	USART_Init(USART3, &USART_InitStructure);																					//初始化USART3

	NVIC_Configuration();
  //发送中断和接收中断
	//USART_ITConfig(USART3, USART_IT_TXE, ENABLE);										// 使能指定的USART3发送中断;
  USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);										// 使能指定的USART3接收中断;
  USART_ClearFlag(USART3, USART_FLAG_TC);														//清串口3发送标志
	
	USART_Cmd(USART3, ENABLE);																					//使能 USART3
	
	//如下语句解决第1个字节无法正确发送出去的问题
  USART_ClearFlag(USART3, USART_FLAG_TC);                //清串口3发送标志
}
//串口4初始化
void UART4_Config(void)
{
	GPIO_InitTypeDef     GPIO_InitStructure;   
	USART_InitTypeDef    USART_InitStructure; 

	RCC_APB2PeriphClockCmd(uart4_RCC_IO, ENABLE);					
	RCC_APB1PeriphClockCmd(uart4_RCC_UART4, ENABLE);			
	
	USART_DeInit(UART4);										//复位串口4

	//将UART4 Tx（发送脚）的GPIO配置为推挽复用模式
	GPIO_InitStructure.GPIO_Pin = uart4_TX_pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(uart4_TX_port, &GPIO_InitStructure);
														  
	//将USART Rx（接收脚）的GPIO配置为浮空输入模式
	GPIO_InitStructure.GPIO_Pin = uart4_RX_pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;		//浮空输入
	GPIO_Init(uart4_RX_port, &GPIO_InitStructure);	

	//配置UART4参数
	USART_InitStructure.USART_BaudRate             = uart4_baudrate;				 					//波特率设置：115200
	USART_InitStructure.USART_WordLength           = USART_WordLength_8b;			 				//数据位数设置：8位
	USART_InitStructure.USART_StopBits             = USART_StopBits_1;				 				//停止位设置：1位
	USART_InitStructure.USART_Parity               = USART_Parity_No;				 					//是否奇偶校验：无
	USART_InitStructure.USART_HardwareFlowControl  = USART_HardwareFlowControl_None; 	//硬件流控制模式设置：没有使能
	USART_InitStructure.USART_Mode                 = USART_Mode_Rx | USART_Mode_Tx;	 	//接收与发送都使能
	USART_Init(UART4, &USART_InitStructure);																					//初始化UART4

	NVIC_Configuration();
  //发送中断和接收中断
	//USART_ITConfig(UART4, USART_IT_TXE, ENABLE);										// 使能指定的UART4发送中断;
  USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);										// 使能指定的UART4接收中断;
  USART_ClearFlag(UART4, USART_FLAG_TC);														//清串口4发送标志
	
	USART_Cmd(UART4, ENABLE);																					//使能 UART4
	
	//如下语句解决第1个字节无法正确发送出去的问题
  USART_ClearFlag(UART4, USART_FLAG_TC);                //清串口4发送标志
}

void UART5_Config(void)
{
	GPIO_InitTypeDef     GPIO_InitStructure;   
	USART_InitTypeDef    USART_InitStructure; 

	RCC_APB2PeriphClockCmd(uart5_RCC_IO, ENABLE);
	RCC_APB1PeriphClockCmd(uart5_RCC_UART5, ENABLE);
	
	USART_DeInit(UART5);										//复位串口5

	//将UART5 Tx（发送脚）的GPIO配置为推挽复用模式
	GPIO_InitStructure.GPIO_Pin = uart5_TX_pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(uart5_TX_port, &GPIO_InitStructure);
														  
	//将USART Rx（接收脚）的GPIO配置为浮空输入模式
	GPIO_InitStructure.GPIO_Pin = uart5_RX_pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;		//浮空输入
	GPIO_Init(uart5_RX_port, &GPIO_InitStructure);	

	//配置UART5参数
	USART_InitStructure.USART_BaudRate             = uart5_baudrate;				 					//波特率设置：115200
	USART_InitStructure.USART_WordLength           = USART_WordLength_8b;			 				//数据位数设置：8位
	USART_InitStructure.USART_StopBits             = USART_StopBits_1;				 				//停止位设置：1位
	USART_InitStructure.USART_Parity               = USART_Parity_No;				 					//是否奇偶校验：无
	USART_InitStructure.USART_HardwareFlowControl  = USART_HardwareFlowControl_None; 	//硬件流控制模式设置：没有使能
	USART_InitStructure.USART_Mode                 = USART_Mode_Rx | USART_Mode_Tx;	 	//接收与发送都使能
	USART_Init(UART5, &USART_InitStructure);																					//初始化UART5

	NVIC_Configuration();
  //发送中断和接收中断
	//USART_ITConfig(UART5, USART_IT_TXE, ENABLE);										// 使能指定的UART5发送中断;
  USART_ITConfig(UART5, USART_IT_RXNE, ENABLE);										// 使能指定的UART5接收中断;
  USART_ClearFlag(UART5, USART_FLAG_TC);														//清串口5发送标志
	
	USART_Cmd(UART5, ENABLE);																					//使能 UART5
	
	//如下语句解决第1个字节无法正确发送出去的问题
  USART_ClearFlag(UART5, USART_FLAG_TC);                //清串口5发送标志
}
*/


//串口全局中断服务函数
void USART1_IRQHandler(void)
{
	 if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
	 {
		 ReceiveArray[count] = USART_ReceiveData(USART1);   //接收数据
		 if(count == 0 && ReceiveArray[0] != 'p')						// 112是字符P的ASCII值
		 {
				USART_ClearITPendingBit(USART1,USART_IT_RXNE);
				return;
		 }
		 count++;		
		 if(ReceiveArray[count] == '\n')
		 {
//			 printf("%s",ReceiveArray);
//			 delay_ms(2000);
			 kp = (ReceiveArray[1]-'0')*100.0 + (ReceiveArray[2]-'0')*10.0 + (ReceiveArray[3]-'0') + (ReceiveArray[4]-'0')/10.0;
			 count = 0;
		 }
	 }
	 USART_ClearITPendingBit(USART1,USART_IT_RXNE);
}	

void Usart_SendByte( USART_TypeDef * pUSARTx, char ch )
{
	/* 发送一个字节数据到USART1 */
	USART_SendData(pUSARTx,ch);
		
	/* 等待发送完毕 */
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);	
}


void Usart_SendString( USART_TypeDef * pUSARTx, char *str)
{
	unsigned int k=0;
    do 
    {
        Usart_SendByte( pUSARTx, *(str + k) );
        k++;
    } while(*(str + k)!='\0');
}

//重定向c库函数printf到USARTx
int fputc(int ch, FILE *f)
{
		/* 发送一个字节数据到USART1 */
		USART_SendData(USART1, (uint8_t) ch);
		
		/* 等待发送完毕 */
		while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);		
	
		return (ch);
}

//重定向c库函数scanf到USARTx
int fgetc(FILE *f)
{
		/* 等待串口1输入数据 */
		while (USART_GetFlagStatus(usart_scanf, USART_FLAG_RXNE) == RESET);

		return (int)USART_ReceiveData(usart_scanf);
}
