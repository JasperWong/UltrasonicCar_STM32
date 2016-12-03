#ifndef __WDX_TIMCAP_H
#define __WDX_TIMCAP_H

#include "stm32f10x.h"

extern uint16_t Ultra_Data[4];

/*****************************GPIO*************************************************/	
#define  			ultrasonic_GPIO_APBxClock_FUN			RCC_APB2PeriphClockCmd 
#define				ultrasonic_GPIO_CLK								(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB)

//超声波——左-- Tri-PA1 Echo-PA0
#define 			ultrasonic1_Tri_PORT							GPIOB
#define				ultrasonic1_Tri_PIN								GPIO_Pin_3
#define 			ultrasonic1_Echo_PORT							GPIOA
#define				ultrasonic1_Echo_PIN							GPIO_Pin_15
//超声波——前-- Tri-PA7 Echo-PA6
#define 			ultrasonic2_Tri_PORT							GPIOA
#define				ultrasonic2_Tri_PIN								GPIO_Pin_7
#define 			ultrasonic2_Echo_PORT							GPIOA
#define				ultrasonic2_Echo_PIN							GPIO_Pin_6
//超声波——右-- Tri-PB7 Echo-PB6
#define 			ultrasonic3_Tri_PORT							GPIOB
#define				ultrasonic3_Tri_PIN								GPIO_Pin_7
#define 			ultrasonic3_Echo_PORT							GPIOB
#define				ultrasonic3_Echo_PIN							GPIO_Pin_6

void ultrasonic_Config(void);
void ultrasonic_GetData(void);
																		
#endif /*__WDX_TIMCAP_H*/
