#include "LED.h"

/* ��ʼ��IO�� */
void LED_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	/* ���IO��ʱ��ʹ�� */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD, ENABLE);
	
	/* LED�˿ڳ�ʼ�� */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	/* �������˿ڳ�ʼ�� */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
}

/*
 *���ƴ򿪻�ر�LED
 *LED:LED��ţ�GPIO_Pin_8��GPIO_Pin_15
 *LED_Status:0,�ر�LED	1,��LED
*/
void LED_Control(uint16_t LED, uint8_t LED_Status)
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


