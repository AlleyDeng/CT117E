#include "key.h"

/*
 *按键接口初始化函数
**/
void Key_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE);
	
	/* B1、B2按键引脚配置 */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	/* B3、B4按键引脚配置 */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}

/*
 *按键扫描函数
**/
uint8_t Key_Scan(void)
{
	uint8_t Key_value = 0xFF;
	
	if (KEY1 == 0) {
		Key_value = '1';
	}
	if (KEY2 == 0) {
		Key_value = '2';
	}
	if (KEY3 == 0) {
		Key_value = '3';
	}
	if (KEY4 == 0) {
		Key_value = '4';
	}
	
	return Key_value;
}








