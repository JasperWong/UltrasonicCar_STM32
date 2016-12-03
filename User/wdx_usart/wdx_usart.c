#include "wdx_usart.h"
#include "sys.h"
#include "delay.h"

float kp=30.0;
uint8_t ReceiveArray[RNumber];
static uint8_t count=0;

//�ж����ȼ�����
void NVIC_USART_Configuration(void)
{
	NVIC_InitTypeDef    NVIC_InitStructure; 					   //�������������жϵĽṹ�����

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);                //�ж����ȼ�����  ��ռʽ���ȼ�������Ϊ2λ����Ӧ���ȼ�ռ2λ
	
	//����1�ж����ȼ�����
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;             	//ͨ������Ϊ����1�ж�  
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;	   		//��ռ���ȼ�1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;            	//ָ����Ӧ���ȼ���1
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	              	//���ж�
	NVIC_Init(&NVIC_InitStructure);							       				

/*
	//����2�ж����ȼ�����
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;             	//ͨ������Ϊ����2�ж�  
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	   		//��ռ���ȼ�1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;            	//ָ����Ӧ���ȼ���1
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	              	//���ж�
	NVIC_Init(&NVIC_InitStructure);							       				

	//����3�ж����ȼ�����
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;             	//ͨ������Ϊ����3�ж�  
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	   		//��ռ���ȼ�1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;            	//ָ����Ӧ���ȼ���1
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	              	//���ж�
	NVIC_Init(&NVIC_InitStructure);							       				

	//����4�ж����ȼ�����
	NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;             	//ͨ������Ϊ����4�ж�  
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	   		//��ռ���ȼ�1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;            	//ָ����Ӧ���ȼ���1
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	              	//���ж�
	NVIC_Init(&NVIC_InitStructure);							       				

	//����5�ж����ȼ�����
	NVIC_InitStructure.NVIC_IRQChannel = UART5_IRQn;             	//ͨ������Ϊ����5�ж�  
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	   		//��ռ���ȼ�1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;            	//ָ����Ӧ���ȼ���1
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	              	//���ж�
	NVIC_Init(&NVIC_InitStructure);
*/	
}

//����1��ʼ��
void USART1_Config(void)
{
	GPIO_InitTypeDef     GPIO_InitStructure;   
	USART_InitTypeDef    USART_InitStructure; 

	RCC_APB2PeriphClockCmd(usart1_RCC_IO, ENABLE);					//��GPIOAʱ�Ӻ�GPIOA����ʱ��
	RCC_APB2PeriphClockCmd(usart1_RCC_USART1, ENABLE);			//�򿪴��ڸ���ʱ��
	
	USART_DeInit(USART1);										//��λ����1

	//��USART1 Tx�����ͽţ���GPIO����Ϊ���츴��ģʽ
	GPIO_InitStructure.GPIO_Pin = usart1_TX_pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(usart1_TX_port, &GPIO_InitStructure);
														  
	//��USART Rx�����սţ���GPIO����Ϊ��������ģʽ
	GPIO_InitStructure.GPIO_Pin = usart1_RX_pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;		//��������
	GPIO_Init(usart1_RX_port, &GPIO_InitStructure);	

	//����USART1����
	USART_InitStructure.USART_BaudRate             = usart1_baudrate;				 					//���������ã�115200
	USART_InitStructure.USART_WordLength           = USART_WordLength_8b;			 				//����λ�����ã�8λ
	USART_InitStructure.USART_StopBits             = USART_StopBits_1;				 				//ֹͣλ���ã�1λ
	USART_InitStructure.USART_Parity               = USART_Parity_No;				 					//�Ƿ���żУ�飺��
	USART_InitStructure.USART_HardwareFlowControl  = USART_HardwareFlowControl_None; 	//Ӳ��������ģʽ���ã�û��ʹ��
	USART_InitStructure.USART_Mode                 = USART_Mode_Rx | USART_Mode_Tx;	 	//�����뷢�Ͷ�ʹ��
	USART_Init(USART1, &USART_InitStructure);																					//��ʼ��USART1

  
	NVIC_USART_Configuration();
	//�����жϺͽ����ж�
//	USART_ITConfig(USART1, USART_IT_TXE, ENABLE);											// ʹ��ָ����USART1�����ж�;
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);										// ʹ��ָ����USART1�����ж�;
  USART_ClearFlag(USART1, USART_FLAG_TC);														//�崮��1���ͱ�־
	
	USART_Cmd(USART1, ENABLE);																					//ʹ�� USART1

	//�����������1���ֽ��޷���ȷ���ͳ�ȥ������
  USART_ClearFlag(USART1, USART_FLAG_TC);                //�崮��1���ͱ�־
}

/*
//����2��ʼ��
void USART2_Config(void)
{
	GPIO_InitTypeDef     GPIO_InitStructure;   
	USART_InitTypeDef    USART_InitStructure; 

	RCC_APB2PeriphClockCmd(usart2_RCC_IO, ENABLE);
	RCC_APB1PeriphClockCmd(usart2_RCC_USART2, ENABLE);
	
	USART_DeInit(USART2);										//��λ����2

	//��USART2 Tx�����ͽţ���GPIO����Ϊ���츴��ģʽ
	GPIO_InitStructure.GPIO_Pin = usart2_TX_pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(usart2_TX_port, &GPIO_InitStructure);
														  
	//��USART Rx�����սţ���GPIO����Ϊ��������ģʽ
	GPIO_InitStructure.GPIO_Pin = usart2_RX_pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;		//��������
	GPIO_Init(usart2_RX_port, &GPIO_InitStructure);	

	//����USART2����
	USART_InitStructure.USART_BaudRate             = usart2_baudrate;				 					//���������ã�115200
	USART_InitStructure.USART_WordLength           = USART_WordLength_8b;			 				//����λ�����ã�8λ
	USART_InitStructure.USART_StopBits             = USART_StopBits_1;				 				//ֹͣλ���ã�1λ
	USART_InitStructure.USART_Parity               = USART_Parity_No;				 					//�Ƿ���żУ�飺��
	USART_InitStructure.USART_HardwareFlowControl  = USART_HardwareFlowControl_None; 	//Ӳ��������ģʽ���ã�û��ʹ��
	USART_InitStructure.USART_Mode                 = USART_Mode_Rx | USART_Mode_Tx;	 	//�����뷢�Ͷ�ʹ��
	USART_Init(USART2, &USART_InitStructure);																					//��ʼ��USART2

	NVIC_Configuration();
  //�����жϺͽ����ж�
	//USART_ITConfig(USART2, USART_IT_TXE, ENABLE);										// ʹ��ָ����USART2�����ж�;
  USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);										// ʹ��ָ����USART2�����ж�;
  USART_ClearFlag(USART2, USART_FLAG_TC);														//�崮��2���ͱ�־
	
	USART_Cmd(USART2, ENABLE);																					//ʹ�� USART2
	
	//�����������1���ֽ��޷���ȷ���ͳ�ȥ������
  USART_ClearFlag(USART2, USART_FLAG_TC);                //�崮��2���ͱ�־
}
//����3��ʼ��
void USART3_Config(void)
{
	GPIO_InitTypeDef     GPIO_InitStructure;   
	USART_InitTypeDef    USART_InitStructure; 

	RCC_APB2PeriphClockCmd(usart3_RCC_IO, ENABLE);
	RCC_APB1PeriphClockCmd(usart3_RCC_USART3, ENABLE);
	
	USART_DeInit(USART3);										//��λ����3

	//��USART3 Tx�����ͽţ���GPIO����Ϊ���츴��ģʽ
	GPIO_InitStructure.GPIO_Pin = usart3_TX_pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(usart3_TX_port, &GPIO_InitStructure);
														  
	//��USART Rx�����սţ���GPIO����Ϊ��������ģʽ
	GPIO_InitStructure.GPIO_Pin = usart3_RX_pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;		//��������
	GPIO_Init(usart3_RX_port, &GPIO_InitStructure);	

	//����USART3����
	USART_InitStructure.USART_BaudRate             = usart3_baudrate;				 					//���������ã�115200
	USART_InitStructure.USART_WordLength           = USART_WordLength_8b;			 				//����λ�����ã�8λ
	USART_InitStructure.USART_StopBits             = USART_StopBits_1;				 				//ֹͣλ���ã�1λ
	USART_InitStructure.USART_Parity               = USART_Parity_No;				 					//�Ƿ���żУ�飺��
	USART_InitStructure.USART_HardwareFlowControl  = USART_HardwareFlowControl_None; 	//Ӳ��������ģʽ���ã�û��ʹ��
	USART_InitStructure.USART_Mode                 = USART_Mode_Rx | USART_Mode_Tx;	 	//�����뷢�Ͷ�ʹ��
	USART_Init(USART3, &USART_InitStructure);																					//��ʼ��USART3

	NVIC_Configuration();
  //�����жϺͽ����ж�
	//USART_ITConfig(USART3, USART_IT_TXE, ENABLE);										// ʹ��ָ����USART3�����ж�;
  USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);										// ʹ��ָ����USART3�����ж�;
  USART_ClearFlag(USART3, USART_FLAG_TC);														//�崮��3���ͱ�־
	
	USART_Cmd(USART3, ENABLE);																					//ʹ�� USART3
	
	//�����������1���ֽ��޷���ȷ���ͳ�ȥ������
  USART_ClearFlag(USART3, USART_FLAG_TC);                //�崮��3���ͱ�־
}
//����4��ʼ��
void UART4_Config(void)
{
	GPIO_InitTypeDef     GPIO_InitStructure;   
	USART_InitTypeDef    USART_InitStructure; 

	RCC_APB2PeriphClockCmd(uart4_RCC_IO, ENABLE);					
	RCC_APB1PeriphClockCmd(uart4_RCC_UART4, ENABLE);			
	
	USART_DeInit(UART4);										//��λ����4

	//��UART4 Tx�����ͽţ���GPIO����Ϊ���츴��ģʽ
	GPIO_InitStructure.GPIO_Pin = uart4_TX_pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(uart4_TX_port, &GPIO_InitStructure);
														  
	//��USART Rx�����սţ���GPIO����Ϊ��������ģʽ
	GPIO_InitStructure.GPIO_Pin = uart4_RX_pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;		//��������
	GPIO_Init(uart4_RX_port, &GPIO_InitStructure);	

	//����UART4����
	USART_InitStructure.USART_BaudRate             = uart4_baudrate;				 					//���������ã�115200
	USART_InitStructure.USART_WordLength           = USART_WordLength_8b;			 				//����λ�����ã�8λ
	USART_InitStructure.USART_StopBits             = USART_StopBits_1;				 				//ֹͣλ���ã�1λ
	USART_InitStructure.USART_Parity               = USART_Parity_No;				 					//�Ƿ���żУ�飺��
	USART_InitStructure.USART_HardwareFlowControl  = USART_HardwareFlowControl_None; 	//Ӳ��������ģʽ���ã�û��ʹ��
	USART_InitStructure.USART_Mode                 = USART_Mode_Rx | USART_Mode_Tx;	 	//�����뷢�Ͷ�ʹ��
	USART_Init(UART4, &USART_InitStructure);																					//��ʼ��UART4

	NVIC_Configuration();
  //�����жϺͽ����ж�
	//USART_ITConfig(UART4, USART_IT_TXE, ENABLE);										// ʹ��ָ����UART4�����ж�;
  USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);										// ʹ��ָ����UART4�����ж�;
  USART_ClearFlag(UART4, USART_FLAG_TC);														//�崮��4���ͱ�־
	
	USART_Cmd(UART4, ENABLE);																					//ʹ�� UART4
	
	//�����������1���ֽ��޷���ȷ���ͳ�ȥ������
  USART_ClearFlag(UART4, USART_FLAG_TC);                //�崮��4���ͱ�־
}

void UART5_Config(void)
{
	GPIO_InitTypeDef     GPIO_InitStructure;   
	USART_InitTypeDef    USART_InitStructure; 

	RCC_APB2PeriphClockCmd(uart5_RCC_IO, ENABLE);
	RCC_APB1PeriphClockCmd(uart5_RCC_UART5, ENABLE);
	
	USART_DeInit(UART5);										//��λ����5

	//��UART5 Tx�����ͽţ���GPIO����Ϊ���츴��ģʽ
	GPIO_InitStructure.GPIO_Pin = uart5_TX_pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(uart5_TX_port, &GPIO_InitStructure);
														  
	//��USART Rx�����սţ���GPIO����Ϊ��������ģʽ
	GPIO_InitStructure.GPIO_Pin = uart5_RX_pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;		//��������
	GPIO_Init(uart5_RX_port, &GPIO_InitStructure);	

	//����UART5����
	USART_InitStructure.USART_BaudRate             = uart5_baudrate;				 					//���������ã�115200
	USART_InitStructure.USART_WordLength           = USART_WordLength_8b;			 				//����λ�����ã�8λ
	USART_InitStructure.USART_StopBits             = USART_StopBits_1;				 				//ֹͣλ���ã�1λ
	USART_InitStructure.USART_Parity               = USART_Parity_No;				 					//�Ƿ���żУ�飺��
	USART_InitStructure.USART_HardwareFlowControl  = USART_HardwareFlowControl_None; 	//Ӳ��������ģʽ���ã�û��ʹ��
	USART_InitStructure.USART_Mode                 = USART_Mode_Rx | USART_Mode_Tx;	 	//�����뷢�Ͷ�ʹ��
	USART_Init(UART5, &USART_InitStructure);																					//��ʼ��UART5

	NVIC_Configuration();
  //�����жϺͽ����ж�
	//USART_ITConfig(UART5, USART_IT_TXE, ENABLE);										// ʹ��ָ����UART5�����ж�;
  USART_ITConfig(UART5, USART_IT_RXNE, ENABLE);										// ʹ��ָ����UART5�����ж�;
  USART_ClearFlag(UART5, USART_FLAG_TC);														//�崮��5���ͱ�־
	
	USART_Cmd(UART5, ENABLE);																					//ʹ�� UART5
	
	//�����������1���ֽ��޷���ȷ���ͳ�ȥ������
  USART_ClearFlag(UART5, USART_FLAG_TC);                //�崮��5���ͱ�־
}
*/


//����ȫ���жϷ�����
void USART1_IRQHandler(void)
{
	 if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
	 {
		 ReceiveArray[count] = USART_ReceiveData(USART1);   //��������
		 if(count == 0 && ReceiveArray[0] != 'p')						// 112���ַ�P��ASCIIֵ
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
	/* ����һ���ֽ����ݵ�USART1 */
	USART_SendData(pUSARTx,ch);
		
	/* �ȴ�������� */
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

//�ض���c�⺯��printf��USARTx
int fputc(int ch, FILE *f)
{
		/* ����һ���ֽ����ݵ�USART1 */
		USART_SendData(USART1, (uint8_t) ch);
		
		/* �ȴ�������� */
		while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);		
	
		return (ch);
}

//�ض���c�⺯��scanf��USARTx
int fgetc(FILE *f)
{
		/* �ȴ�����1�������� */
		while (USART_GetFlagStatus(usart_scanf, USART_FLAG_RXNE) == RESET);

		return (int)USART_ReceiveData(usart_scanf);
}
