#ifndef _KEY_H_
#define _KEY_H_

#include "stm32f10x.h"

#define KEY0	GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0)
#define KEY1	GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_8)
#define KEY2	GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1)
#define KEY3	GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_2)

void KEY_Config(void);









#endif
