#include "stm32f10x.h"
#include "sys.h"
#include "delay.h"
#include "wdx_ultrasonic.h"
#include "wdx_motor.h"
#include "wdx_usart.h"
#include <stdlib.h>

#define E_Value		25				//expect value
#define	Time_ms		100

int pid_distance(uint16_t distance)
{
	int temp;
	
	temp=kp*(distance-E_Value);
	if(temp <= -110)
		temp = -110;
	if(temp >= 300)
		temp = 300;
	return temp;
}


int main(void)
{	
	int pwm=0;
	int KP=0; 
	delay_init(72);						//延时函数初始化，用SysTick定时器
	NVIC_Configuration();
	ultrasonic_Config();				//超声波初始化
	Motor_Config();	
	USART1_Config();
	while(1)
	{
//		ultrasonic_GetData();
//		pwm=1200+pid_distance(Ultra_Data[1]);
//		printf("F:%d L%d R%d \r\n",Ultra_Data[2],Ultra_Data[3],Ultra_Data[1]);
//		delay_ms(2);
//		printf("kP%4.1f p%d \r\n",kp,pwm);
//		TIM_SetCompare3(TIM2,pwm);
	}
}

/*********************************************END OF FILE**********************/
