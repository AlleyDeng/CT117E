#include "rtc.h"

void RTC_Config(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;

	/* Configure one bit for preemption priority */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

	/* Enable the RTC Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = RTC_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
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
	/* To output second signal on Tamper pin, the tamper functionality
       must be disabled (by default this functionality is disabled) */
	//BKP_TamperPinCmd(DISABLE);
	/* Enable the RTC Second Output on Tamper Pin */
	//BKP_RTCOutputConfig(BKP_RTCOutputSource_Second);
}

void TimeDisplay(uint32_t timeVar)
{
	uint8_t text[20];
	
	uint32_t THH = timeVar / 3600;
	uint32_t TMM = (timeVar % 3600) / 60;
	uint32_t TSS = (timeVar % 3600) % 60;

	sprintf(text, "   Time: %0.2d:%0.2d:%0.2d", THH, TMM, TSS);
	LCD_DisplayStringLine(Line7, text);
}
