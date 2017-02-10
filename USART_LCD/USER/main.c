#include "stm32f10x.h"
#include "lcd.h"
#include "led.h"
#include "usart.h"

uint8_t USART_RXBUF[20];
uint8_t RXCUNT;
uint8_t RXOVER = 0;

unsigned int TimingDelay = 0;
unsigned char str[20] = "                    ";

void DelayMs(unsigned int nTimeDelay)
{
	TimingDelay = nTimeDelay;
	while (TimingDelay != 0);
}

int main (void)
{
	unsigned int i;
	LED_Init();
	USART_Config();
	SysTick_Config(SystemCoreClock/1000);
	STM3210B_LCD_Init();
	LCD_Clear(White);
	while (1) {
		if (RXOVER == 1) {
			LCD_ClearLine(Line7);
			LCD_DisplayStringLine(Line7, USART_RXBUF);
			for (i = 0 ; i < 20; i++) {
				USART_RXBUF[i] = 0;
			}
			RXOVER = 0;
			USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
		}
	}
}
