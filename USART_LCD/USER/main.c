#include "stm32f10x.h"
#include "lcd.h"
#include "led.h"
#include "usart.h"

unsigned int TimingDelay = 0;
unsigned char str[20] = "                    ";

void DelayMs(unsigned int nTimeDelay)
{
	TimingDelay = nTimeDelay;
	while (TimingDelay != 0);
}

int main (void)
{
	LED_Init();
	USART_Config();
	SysTick_Config(SystemCoreClock/1000);
	STM3210B_LCD_Init();
	LCD_Clear(White);
	while (1) {

	}
}
