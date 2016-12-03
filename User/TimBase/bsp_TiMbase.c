#include "bsp_TiMbase.h"
void TIM1_Init(u16 arr,u16 psc,u16 pwm)		 //Advanced TIM
{  
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
//	TIM_BDTRInitTypeDef TIM_BDTRInitStructure;

 	RCC_APB2PeriphClockCmd( RCC_APB2Periph_TIM1, ENABLE);  
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);   
														  	                                     
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8; //TIM_CH1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);


	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	 80K
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  ����Ƶ
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; 			//ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_Pulse = pwm; 							//���ô�װ�벶��ȽϼĴ���������ֵ
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; 	//�������:TIM����Ƚϼ��Ը�
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High; 	//�������:TIM����Ƚϼ��Ը�
	TIM_OCInitStructure.TIM_OCIdleState	= TIM_OCIdleState_Set;
	TIM_OCInitStructure.TIM_OCNIdleState	= TIM_OCIdleState_Reset;
	TIM_OC1Init(TIM1, &TIM_OCInitStructure);  				
	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);  			//ʹ��TIMx��CCR1�ϵ�Ԥװ�ؼĴ���

//	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; 			  //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
//	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
//	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable; //�Ƚ����ʹ��
//	TIM_OCInitStructure.TIM_Pulse = 0; 							  //���ô�װ�벶��ȽϼĴ���������ֵ
//	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; 	  //�������:TIM����Ƚϼ��Ը�
//	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High; 	//�������:TIM����Ƚϼ��Ը�
//	TIM_OCInitStructure.TIM_OCIdleState	= TIM_OCIdleState_Set;
//	TIM_OCInitStructure.TIM_OCNIdleState	= TIM_OCIdleState_Reset;
//	TIM_OC2Init(TIM1, &TIM_OCInitStructure); 
//	TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable);  			  //ʹ��TIMx��CCR2�ϵ�Ԥװ�ؼĴ���

//	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; 			//ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
//	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
//	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable; //�Ƚ����ʹ��
//	TIM_OCInitStructure.TIM_Pulse = 0; 							//���ô�װ�벶��ȽϼĴ���������ֵ
//	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; 	//�������:TIM����Ƚϼ��Ը�
//	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High; 	//�������:TIM����Ƚϼ��Ը�
//	TIM_OCInitStructure.TIM_OCIdleState	= TIM_OCIdleState_Set;
//	TIM_OCInitStructure.TIM_OCNIdleState	= TIM_OCIdleState_Reset;
//	TIM_OC3Init(TIM1, &TIM_OCInitStructure);  				
//	TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable);  			//ʹ��TIMx��CCR3�ϵ�Ԥװ�ؼĴ���

//	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; 			  //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
//	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
//	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable; //�Ƚ����ʹ��
//	TIM_OCInitStructure.TIM_Pulse = 0; 							  //���ô�װ�벶��ȽϼĴ���������ֵ
//	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; 	  //�������:TIM����Ƚϼ��Ը�
//	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High; 	//�������:TIM����Ƚϼ��Ը�
//	TIM_OCInitStructure.TIM_OCIdleState	= TIM_OCIdleState_Set;
//	TIM_OCInitStructure.TIM_OCNIdleState	= TIM_OCIdleState_Reset;
//	TIM_OC4Init(TIM1, &TIM_OCInitStructure); 
//	TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable);  			  //ʹ��TIMx��CCR4�ϵ�Ԥװ�ؼĴ���
//	
//	TIM_BDTRInitStructure.TIM_OSSRState = TIM_OSSRState_Enable;
//	TIM_BDTRInitStructure.TIM_OSSIState = TIM_OSSIState_Enable;
//	TIM_BDTRConfig(TIM1, &TIM_BDTRInitStructure);
// /* 	assert_param(IS_TIM_OSSR_STATE(TIM_BDTRInitStruct->TIM_OSSRState));
//  	assert_param(IS_TIM_OSSI_STATE(TIM_BDTRInitStruct->TIM_OSSIState));
//  	assert_param(IS_TIM_LOCK_LEVEL(TIM_BDTRInitStruct->TIM_LOCKLevel));
//  	assert_param(IS_TIM_BREAK_STATE(TIM_BDTRInitStruct->TIM_Break));
//	assert_param(IS_TIM_BREAK_POLARITY(TIM_BDTRInitStruct->TIM_BreakPolarity));
//	assert_param(IS_TIM_AUTOMATIC_OUTPUT_STATE(TIM_BDTRInitStruct->TIM_AutomaticOutput));
//  */
	TIM_ARRPreloadConfig(TIM1, ENABLE); 						  //ʹ��TIMx��ARR�ϵ�Ԥװ�ؼĴ��� 
	TIM_Cmd(TIM1, ENABLE);  									  //ʹ��TIMx����
	TIM_CtrlPWMOutputs(TIM1, ENABLE);							  //pwm���ʹ�ܣ�һ��Ҫ�ǵô�
}
