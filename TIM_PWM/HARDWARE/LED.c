#include "LED.h"

/* 初始化IO口 */
void LED_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	/* 相关IO口时钟使能 */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD, ENABLE);
	
	/* LED端口初始化 */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	/* 锁存器端口初始化 */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
}

/*
 *控制打开或关闭LED
 *LED:LED编号，GPIO_Pin_8到GPIO_Pin_15
 *LED_Status:0,关闭LED	1,打开LED
*/
void LED_Control(uint16_t LED, uint8_t LED_Status)
{
	if (LED_Status == 1) {
		GPIO_ResetBits(GPIOC, LED);
		GPIO_SetBits(GPIOD, GPIO_Pin_2);
		GPIO_ResetBits(GPIOD, GPIO_Pin_2);	/* 状态锁存 */
	}	else {
		GPIO_SetBits(GPIOC, LED);
		GPIO_SetBits(GPIOD, GPIO_Pin_2);
		GPIO_ResetBits(GPIOD, GPIO_Pin_2);	/* 状态锁存 */
	}
}


