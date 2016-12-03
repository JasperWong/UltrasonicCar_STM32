#include "wdx_motor.h"
#include "delay.h"
#include "sys.h"

void Motor_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
 	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);  
 	RCC_APB2PeriphClockCmd(Motor_GPIO_CLOCK, ENABLE);  	
	//模式
	GPIO_InitStructure.GPIO_Pin = Motor_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(Motor_GPIO_PORT , &GPIO_InitStructure);	

	TIM_TimeBaseStructure.TIM_Period = 19999; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_Prescaler = 71; //设置用来作为TIMx时钟频率除数的预分频值  不分频
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; 			//选择定时器模式:TIM脉冲宽度调制模式2
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_Pulse = MOTOR_Value; 							//设置待装入捕获比较寄存器的脉冲值
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OC3Init(TIM2, &TIM_OCInitStructure);  				
	TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);  			//使能TIMx在CCR1上的预装载寄存器

	TIM_Cmd(TIM2, ENABLE);  									  //使能TIMx外设
}
