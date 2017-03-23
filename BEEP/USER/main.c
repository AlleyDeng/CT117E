#include "stm32f10x.h"
#include "lcd.h"
#include "led.h"
#include "beep.h"

uint32_t TimingDelay = 0;
unsigned int n50Ms;
unsigned int num;

void DelayMs(uint32_t nTime)	
{
	TimingDelay = nTime;
	while (TimingDelay != 0);
}

int main (void)
{
	SysTick_Config(SystemCoreClock / 1000);
	LED_Init();
	Beep_Config();
	STM3210B_LCD_Init();
	LCD_Clear(White);
	LCD_DisplayStringLine(Line1, "        BEEP       ");	
	
	while (1) {
		//LED_Control(LEDALL, 1);
		GPIO_ResetBits(GPIOB, GPIO_Pin_4);
		LCD_DisplayStringLine(Line4, "       BEEP ON      ");	
		DelayMs(200);
//		GPIO_SetBits(GPIOB, GPIO_Pin_4);
//		LCD_DisplayStringLine(Line5, "       BEEP OFF     ");	
//		DelayMs(200);
	}		
}
