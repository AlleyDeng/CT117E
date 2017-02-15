#include <stdio.h>
#include <string.h>
#include "stm32f10x.h"
#include "led.h"
#include "key.h"
#include "lcd.h"
#include "beep.h"
#include "usart.h"
#include "rtc.h"

uint32_t nTimingDelay = 0;
uint32_t RxCounter = 0;
//uint32_t packingTime[2][10] = {0};
uint8_t keyTemp = 0;
uint8_t string[20];
uint8_t RxBuffer[20];
uint8_t RxFlag = 0;
uint8_t timeDisplayFlag = 0;
int packingSpace = 10;

void TimeDisplay(uint32_t timeShow)
{
	uint8_t str[20];
	
	uint32_t HH = timeShow / 3600;
	uint32_t MM = (timeShow % 3600) / 60;
	uint32_t SS = (timeShow % 3600) % 60;
	
	sprintf (str, "  Time: %.2d:%.2d:%.2d   ", HH, MM, SS);
	LCD_DisplayStringLine(Line9, str);
}
void DelayMs(uint32_t nTime)	
{
	nTimingDelay = nTime;
	while (nTimingDelay != 0);
}

int main (void)
{
	SysTick_Config(SystemCoreClock/1000);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_SetPriority(SysTick_IRQn, 0);
	LED_Config();
	Key_Config();
	RTC_Config();
	Beep_Config();
	Usart_Config();
	STM3210B_LCD_Init();
	/* Configure the NVIC Preemption Priority Bits */
	
	LED_Control(LEDALL, 0);
	Usart_SendString("Input command:\n");
	
	LCD_SetBackColor(Blue);
	LCD_SetTextColor(White);
	LCD_Clear(Blue);
	
	sprintf(string, "%s%d%c", " packingSpace : ", packingSpace, ' ');
	LCD_DisplayStringLine(Line1, string);
	
	RTC_SetCounter(55+60*59+23*60*60);
	
	while (1) {
		if (packingSpace == 0) {		/* 没有停车位 */
			LED_Control(LEDALL, 0);
			LED_Control(LED0, 1);
		}	else {						/* 有停车位 */
			LED_Control(LEDALL, 0);
			LED_Control(LED1, 1);
		}
		if (timeDisplayFlag == 1) {
			TimeDisplay(RTC_GetCounter());	/* 显示时间 */
			timeDisplayFlag = 0;
		}
		//GPIO_SetBits(GPIOB, GPIO_Pin_4);
	}
}
