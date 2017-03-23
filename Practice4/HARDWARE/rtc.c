#include "rtc.h"

void RTC_Config(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);
	PWR_BackupAccessCmd(ENABLE);
	BKP_DeInit();
	RCC_LSICmd(ENABLE);
	while (RCC_GetFlagStatus(RCC_FLAG_LSIRDY) == RESET);
	RCC_RTCCLKConfig(RCC_RTCCLKSource_LSI);
	RCC_RTCCLKCmd(ENABLE);
	RTC_WaitForSynchro();
	RTC_WaitForLastTask();
	RTC_ITConfig(RTC_IT_SEC, ENABLE);
	RTC_WaitForLastTask(); 
	RTC_SetPrescaler(40000);
	RTC_WaitForLastTask();

	NVIC_InitStructure.NVIC_IRQChannel = RTC_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&NVIC_InitStructure);
}

void RTC_DisplayTime(void)
{
	uint8_t str[20];
	uint32_t nTime = RTC_GetCounter();
	uint32_t hour = nTime / 3600;
	uint32_t min = nTime % 3600 / 60;
	uint32_t sec = nTime % 3600 % 60;
	
	sprintf(str, "   Time: %.2d:%.2d:%.2d    ", hour, min, sec);
	LCD_DisplayStringLine(Line8, str);
}
