#include "led.h"

/**
  *@brief  LED���ӵ�IO�ڳ�ʼ��
  *@param  None
  *@retval None
  */
void LED_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD, ENABLE);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = LED0 | LED1 | LED2 | LED3 | LED4 | LED5 | LED6 | LED7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	GPIO_ResetBits(GPIOD, GPIO_Pin_2);
}

/**
  *@brief  ����LED��������
  *@param  LED Ҫ������Ϩ���LEDλ��
  *@param  ledStatus ������Ϩ��LED,1:������0��Ϩ��
  *@retval Nones 
  */
void LED_Control(uint16_t LED, uint8_t ledStatus)
{
	if (ledStatus == 0) {
		GPIO_SetBits(GPIOC, LED);
		GPIO_SetBits(GPIOD, GPIO_Pin_2);
		GPIO_ResetBits(GPIOD, GPIO_Pin_2);
	}	else {
		GPIO_ResetBits(GPIOC, LED);
		GPIO_SetBits(GPIOD, GPIO_Pin_2);
		GPIO_ResetBits(GPIOD, GPIO_Pin_2);
	}
}


