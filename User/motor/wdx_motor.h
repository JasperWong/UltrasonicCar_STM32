#ifndef __MOTOR_H
#define __MOTOR_H

#include "stm32f10x.h"

//»úÐµÖÐÖµ  1580
#define		MOTOR_Value		1580

#define Motor_GPIO_CLOCK				RCC_APB2Periph_GPIOA
#define Motor_GPIO_PORT					GPIOA	
#define Motor_GPIO_PIN					GPIO_Pin_2	

void Motor_Config(void);

#endif /*__MOTOR_H*/
