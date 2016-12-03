#include "wdx_ultrasonic.h"
#include "sys.h"
#include "delay.h"

uint16_t Ultra_Data[4] = {0.0, 0.0, 0.0, 0.0};

//超声波IO口配置
void ultrasonic_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	ultrasonic_GPIO_APBxClock_FUN(ultrasonic_GPIO_CLK, ENABLE);
	ultrasonic_GPIO_APBxClock_FUN(RCC_APB2Periph_AFIO, ENABLE);
	
	/*使能SWD 禁用JTAG(即PB3/PB4/PA15作为普通IO口)*/
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);
	
	//超声波——左
	GPIO_InitStructure.GPIO_Pin = ultrasonic1_Tri_PIN;		//Trig	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_Init(ultrasonic1_Tri_PORT, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = ultrasonic1_Echo_PIN;		//Echo
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_Init(ultrasonic1_Echo_PORT, &GPIO_InitStructure);

	//超声波——前
	GPIO_InitStructure.GPIO_Pin = ultrasonic2_Tri_PIN;		//Trig	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_Init(ultrasonic2_Tri_PORT, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = ultrasonic2_Echo_PIN;		//Echo
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_Init(ultrasonic2_Echo_PORT, &GPIO_InitStructure);
	
	//超声波——右
	GPIO_InitStructure.GPIO_Pin = ultrasonic3_Tri_PIN;		//Trig	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_Init(ultrasonic3_Tri_PORT, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = ultrasonic3_Echo_PIN;		//Echo
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_Init(ultrasonic3_Echo_PORT, &GPIO_InitStructure);
	
	//超声波Trig设置为低电平
	GPIO_ResetBits(ultrasonic1_Tri_PORT, ultrasonic1_Tri_PIN);
	GPIO_ResetBits(ultrasonic2_Tri_PORT, ultrasonic2_Tri_PIN);	 
	GPIO_ResetBits(ultrasonic3_Tri_PORT, ultrasonic3_Tri_PIN);
	
}


void ultrasonic_GetData(void)
{
	uint16_t wait_echo,echo_high;
	uint16_t H_count;
	
	/*
	//超声波（前）启动
	*/
	echo_high=0x0350 ;
	H_count=0;
	GPIO_SetBits(ultrasonic2_Tri_PORT,ultrasonic2_Tri_PIN );
	delay_us(20);
	GPIO_ResetBits(ultrasonic2_Tri_PORT,ultrasonic2_Tri_PIN );
	while(!GPIO_ReadInputDataBit(ultrasonic2_Echo_PORT,ultrasonic2_Echo_PIN))									//wait Hight Voltage
	{	
//		wait_echo--;
//		if(!wait_echo)
//			break;
	}
	while(GPIO_ReadInputDataBit(ultrasonic2_Echo_PORT,ultrasonic2_Echo_PIN) &&echo_high--)		//count high_voltage time
	{
		delay_us(10);
		H_count += 10;
	}
	Ultra_Data[2] = H_count/58;
	
	/*
	//超声波（右）启动
	*/
	echo_high=0x0350;
	H_count=0;
	GPIO_SetBits(ultrasonic1_Tri_PORT,ultrasonic1_Tri_PIN );
	delay_us(20);
	GPIO_ResetBits(ultrasonic1_Tri_PORT,ultrasonic1_Tri_PIN );
	while(!GPIO_ReadInputDataBit(ultrasonic1_Echo_PORT,ultrasonic1_Echo_PIN))									//wait Hight Voltage
	{	
//		wait_echo--;
//		if(!wait_echo)
//			break;
	}
	while(GPIO_ReadInputDataBit(ultrasonic1_Echo_PORT,ultrasonic1_Echo_PIN) &&echo_high--)		//count high_voltage time
	{
		delay_us(10);
		H_count += 10;
	}
	Ultra_Data[1] = H_count/58;	
	
	/*
	//超声波（左）启动
	*/
	echo_high=0x0350;
	H_count=0;
	GPIO_SetBits(ultrasonic3_Tri_PORT,ultrasonic3_Tri_PIN );
	delay_us(20);
	GPIO_ResetBits(ultrasonic3_Tri_PORT,ultrasonic3_Tri_PIN );
	while(!GPIO_ReadInputDataBit(ultrasonic3_Echo_PORT,ultrasonic3_Echo_PIN))									//wait Hight Voltage
	{	
//		wait_echo--;
//		if(!wait_echo)
//			break;
	}
	while(GPIO_ReadInputDataBit(ultrasonic3_Echo_PORT,ultrasonic3_Echo_PIN) && echo_high--)		//count high_voltage time
	{
		delay_us(10);
		H_count += 10;
	}
	Ultra_Data[3] = H_count/58;		

	delay_us(500);
}

