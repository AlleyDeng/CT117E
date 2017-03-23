#include "rtc.h"

void RTC_Config(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	
    /* Enable PWR and BKP clocks */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);
    /* Allow access to BKP Domain */
    PWR_BackupAccessCmd(ENABLE);
    /* Reset Backup Domain */
    BKP_DeInit();
    /* Enable the LSI OSC */
    RCC_LSICmd(ENABLE);
    /* Wait till LSI is ready */
    while (RCC_GetFlagStatus(RCC_FLAG_LSIRDY) == RESET);
    /* Select the RTC Clock Source */
    RCC_RTCCLKConfig(RCC_RTCCLKSource_LSI);
    /* Enable RTC Clock */
    RCC_RTCCLKCmd(ENABLE);
    /* Wait for RTC registers synchronization */
    RTC_WaitForSynchro();
    /* Wait until last write operation on RTC registers has finished */
    RTC_WaitForLastTask();
    /* Enable the RTC Second */
    RTC_ITConfig(RTC_IT_SEC, ENABLE);
    /* Wait until last write operation on RTC registers has finished */
    RTC_WaitForLastTask();
    /* Set RTC prescaler: set RTC period to 1sec */
    RTC_SetPrescaler(40000);
    /* Wait until last write operation on RTC registers has finished */
    RTC_WaitForLastTask();

	NVIC_InitStructure.NVIC_IRQChannel = RTC_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

void DisplayTime(void)
{
	uint8_t str[20];
	uint8_t tempTime = RTC_GetCounter();
	uint8_t hour = tempTime / 3600;
	uint8_t min = tempTime % 3600 / 60;
	uint8_t sec = tempTime % 3600 % 60;
	
	sprintf((char *)str, "      T:%.2d:%.2d:%.2d     ", hour, min, sec);
	LCD_DisplayStringLine(Line6, str);
	LED_Control(LEDALL, 0);
}

