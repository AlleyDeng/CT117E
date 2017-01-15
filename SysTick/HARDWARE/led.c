#include "led.h"

void LED_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	/* ʱ�ӳ�ʼ�� */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD, ENABLE);
	
	/* LED�˿ڳ�ʼ�� */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	/* �������˿ڳ�ʼ�� */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_Init(GPIOF, &GPIO_InitStructure);
}


void LED_Control(uint16_t LED, char LED_Status)
{
	if (LED_Status == 1) {
		GPIO_ResetBits(GPIOC, LED);
		GPIO_SetBits(GPIOD, GPIO_Pin_2);
		GPIO_ResetBits(GPIOD, GPIO_Pin_2);	/* ״̬���� */
	}	else {
		GPIO_SetBits(GPIOC, LED);
		GPIO_SetBits(GPIOD, GPIO_Pin_2);
		GPIO_ResetBits(GPIOD, GPIO_Pin_2);	/* ״̬���� */
	}
}
	





