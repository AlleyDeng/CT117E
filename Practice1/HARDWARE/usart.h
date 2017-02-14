#ifndef _USART_H_
#define _USART_H_

#include <stdio.h>
#include "stm32f10x.h"

void Usart_Config(void);
void Usart_SendString(uint8_t* string);



#endif
