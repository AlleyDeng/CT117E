#include "usart.h"
#include "led.h"
#include "string.h"

unsigned int TimingDelay = 0;

void DelayMs(unsigned int nTimeDelay)
{
	TimingDelay = nTimeDelay;
	while (TimingDelay != 0);
}

int main (void)
{
	LED_Init();
	USART_Config();
	LED_Control(LEDALL, 0);
	SysTick_Config(SystemCoreClock / 1000);	/* 1ms÷–∂œ“ª¥Œ */
	
	while (1) {
		USART_SendString("Hello\n");
		LED_Control(LED0 ,1);
		DelayMs(100);
		LED_Control(LED0, 0);		
		DelayMs(100);
	}
}

