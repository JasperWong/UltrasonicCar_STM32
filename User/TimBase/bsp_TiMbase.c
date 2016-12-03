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
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);


	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	 80K
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值  不分频
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; 			//选择定时器模式:TIM脉冲宽度调制模式2
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_Pulse = pwm; 							//设置待装入捕获比较寄存器的脉冲值
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; 	//输出极性:TIM输出比较极性高
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High; 	//输出极性:TIM输出比较极性高
	TIM_OCInitStructure.TIM_OCIdleState	= TIM_OCIdleState_Set;
	TIM_OCInitStructure.TIM_OCNIdleState	= TIM_OCIdleState_Reset;
	TIM_OC1Init(TIM1, &TIM_OCInitStructure);  				
	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);  			//使能TIMx在CCR1上的预装载寄存器

//	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; 			  //选择定时器模式:TIM脉冲宽度调制模式2
//	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
//	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable; //比较输出使能
//	TIM_OCInitStructure.TIM_Pulse = 0; 							  //设置待装入捕获比较寄存器的脉冲值
//	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; 	  //输出极性:TIM输出比较极性高
//	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High; 	//输出极性:TIM输出比较极性高
//	TIM_OCInitStructure.TIM_OCIdleState	= TIM_OCIdleState_Set;
//	TIM_OCInitStructure.TIM_OCNIdleState	= TIM_OCIdleState_Reset;
//	TIM_OC2Init(TIM1, &TIM_OCInitStructure); 
//	TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable);  			  //使能TIMx在CCR2上的预装载寄存器

//	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; 			//选择定时器模式:TIM脉冲宽度调制模式2
//	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
//	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable; //比较输出使能
//	TIM_OCInitStructure.TIM_Pulse = 0; 							//设置待装入捕获比较寄存器的脉冲值
//	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; 	//输出极性:TIM输出比较极性高
//	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High; 	//输出极性:TIM输出比较极性高
//	TIM_OCInitStructure.TIM_OCIdleState	= TIM_OCIdleState_Set;
//	TIM_OCInitStructure.TIM_OCNIdleState	= TIM_OCIdleState_Reset;
//	TIM_OC3Init(TIM1, &TIM_OCInitStructure);  				
//	TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable);  			//使能TIMx在CCR3上的预装载寄存器

//	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; 			  //选择定时器模式:TIM脉冲宽度调制模式2
//	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
//	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable; //比较输出使能
//	TIM_OCInitStructure.TIM_Pulse = 0; 							  //设置待装入捕获比较寄存器的脉冲值
//	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; 	  //输出极性:TIM输出比较极性高
//	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High; 	//输出极性:TIM输出比较极性高
//	TIM_OCInitStructure.TIM_OCIdleState	= TIM_OCIdleState_Set;
//	TIM_OCInitStructure.TIM_OCNIdleState	= TIM_OCIdleState_Reset;
//	TIM_OC4Init(TIM1, &TIM_OCInitStructure); 
//	TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable);  			  //使能TIMx在CCR4上的预装载寄存器
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
	TIM_ARRPreloadConfig(TIM1, ENABLE); 						  //使能TIMx在ARR上的预装载寄存器 
	TIM_Cmd(TIM1, ENABLE);  									  //使能TIMx外设
	TIM_CtrlPWMOutputs(TIM1, ENABLE);							  //pwm输出使能，一定要记得打开
}
