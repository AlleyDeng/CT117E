#include "key.h"
#include "led.h"
#include "lcd.h"

uint32_t TimingDelay = 0;

void Delay_ms(uint32_t nTime)
{
	TimingDelay = nTime;
	while (TimingDelay != 0);
}

int main (void)
{
	uint8_t key_temp = 0;
	
	LED_Init();
	Key_Init();
	
	SysTick_Config(SystemCoreClock / 1000);	/* 1ms中断一次 */
	
	/* LCD初始化 */
	STM3210B_LCD_Init();
	LCD_Clear(White);
	LCD_SetTextColor(Black);
	LCD_SetBackColor(White);
	
	LCD_DisplayStringLine(Line1, "   KEY TEST DEMO    ");
	LCD_DisplayStringLine(Line3, " Press the button...");
	
	while (1) {
		key_temp = Key_Scan();
		switch(key_temp)
		{
			case '1' :
				LCD_DisplayStringLine(Line7, "  Button1 pressed..."); 
				break;
			case '2' :
				LCD_DisplayStringLine(Line7, "  Button2 pressed...");
				break;
			case '3' :
				LCD_DisplayStringLine(Line7, "  Button3 pressed...");
				break;
			case '4' :
				LCD_DisplayStringLine(Line7, "  Button4 pressed...");
				break;
			default: ;
			
		}
		key_temp = 0;	/* 清除按键 */
	}
}
