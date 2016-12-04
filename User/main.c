#include "stm32f10x.h"
#include "sys.h"
#include "delay.h"
#include "wdx_ultrasonic.h"
#include "wdx_motor.h"
#include "wdx_usart.h"
#include <stdlib.h>
#include <math.h>

#define E_Value		30				//expect value
#define	Time_ms		100

static uint8_t Flag_Side;				//0--右边 1--左边


void Straight_Mode(float *diff_Value);
void Avoid_Mode(void);
void Turn_Mode(void);

 
int main(void)
{	
	uint8_t Current_Status;
	float *diff_Value;				//distance-E_Value的差值
	
	delay_init(72);						//延时函数初始化，用SysTick定时器
	NVIC_Configuration();
	ultrasonic_Config();				//超声波初始化
	Motor_Config();	
	USART1_Config();
	while(1)
	{
			ultrasonic_GetData();
			switch(Current_Status)
			{
				case 0:
				{
					Straight_Mode(diff_Value);
					if(Flag_Side)			//左贴边模式->其他模式
					{
						if((Ultra_Data[2]<=30)&&((*diff_Value)>2)&&(Ultra_Data[1]<=90))
						{
								Current_Status=1;
						}
						else if(Ultra_Data[3]>=100)	
						{
								Current_Status=2;
						}
						else
						{
							Current_Status=0;
						}						
					}
					else							//右贴边模式->其他模式
					{
						if((Ultra_Data[2]<=30)&&((*diff_Value)>2))
						{
							if(Ultra_Data[3]<=100)
								Current_Status=1;
							else
								Current_Status=2;
						}
						else 
						{
							Current_Status=0;
						}								
					}
				}
				case 1:
				{
					Avoid_Mode();
					Current_Status=0;					
				}
				case 2:
				{
					Turn_Mode();
					Current_Status=0;
				}
				default:Current_Status=0;
			}
//		ultrasonic_GetData();
//		pwm=MOTOR_Value+pid_distance(Ultra_Data[1]);
//		printf("F:%d L%d R%d \r\n",Ultra_Data[2],Ultra_Data[3],Ultra_Data[1]);
//		delay_ms(2);
//		printf("kP%4.1f p%d \r\n",kp,pwm);
//		TIM_SetCompare3(TIM2,pwm);
	}
}

int pid_distance(uint16_t distance,float *diff_Value)
{
	int temp;

	*diff_Value=distance-E_Value;
	temp=kp*(*diff_Value);			//kp参数是串口头文件定义的，由蓝牙传送该参数的值
	
	if(temp <= -100)
		temp = -100;
	if(temp >= 100)
		temp = 100;
	
	return temp;
}

void Straight_Mode(float *diff_Value)
{
	int pwm=0;
	
	//Flag_Side为真，左贴边模式。反之右贴边模式
	if(Flag_Side)
	{
		pwm=MOTOR_Value-pid_distance(Ultra_Data[3],diff_Value);
		TIM_SetCompare3(TIM2,pwm);			
	}
	else
	{
		pwm=MOTOR_Value+pid_distance(Ultra_Data[1],diff_Value);
		TIM_SetCompare3(TIM2,pwm);			
	}
}

void Avoid_Mode(void)
{
	if(Flag_Side)
	{
		TIM_SetCompare3(TIM2,MOTOR_Value+150);
		delay_ms(2);
		TIM_SetCompare3(TIM2,MOTOR_Value);
		delay_ms(2);
		ultrasonic_GetData();
		while(Ultra_Data[1]>30)
		{
			ultrasonic_GetData();
		}
		TIM_SetCompare3(TIM2,MOTOR_Value-150);
		delay_ms(2);
		TIM_SetCompare3(TIM2,MOTOR_Value);
		delay_ms(2);		
		Flag_Side = !Flag_Side;
	}
	else
	{
		TIM_SetCompare3(TIM2,MOTOR_Value-150);
		delay_ms(2);
		TIM_SetCompare3(TIM2,MOTOR_Value);
		delay_ms(2);
		ultrasonic_GetData();
		while(Ultra_Data[1]>30)
		{
			ultrasonic_GetData();
		}
		TIM_SetCompare3(TIM2,MOTOR_Value+150);
		delay_ms(2);
		TIM_SetCompare3(TIM2,MOTOR_Value);
		delay_ms(2);		
		Flag_Side = !Flag_Side;
	}
}

void Turn_Mode(void)
{
	
}
/*********************************************END OF FILE**********************/
