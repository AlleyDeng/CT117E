#include "stm32f10x.h"
#include "lcd.h"
#include "led.h"

u32 TimingDelay = 0;

void Delay_Ms(u32 nTime);

//Main Body
int main(void)
{

	STM3210B_LCD_Init();
	LED_Init();
	LED_Control(LEDALL, 0);
	LCD_Clear(Blue);
	LCD_SetBackColor(Blue);
	LCD_SetTextColor(White);
	
	SysTick_Config(SystemCoreClock/1000);

//	LCD_DrawLine(120,0,320,Horizontal);
//	LCD_DrawLine(0,160,240,Vertical);
//	Delay_Ms(1000);
//	LCD_Clear(Blue);

//	LCD_DrawRect(70,210,100,100);
//	Delay_Ms(1000);
//	LCD_Clear(Blue);

//	LCD_DrawCircle(120,160,50);
//	Delay_Ms(1000);

//	LCD_Clear(Blue);
//	LCD_DisplayStringLine(Line4 ,"    Hello,world.   ");
//	Delay_Ms(1000);	
	
	while(1) {
		LCD_DisplayStringLine(Line1, "DENGCHAO");
		LED_Control(LEDALL, 0);
		LED_Control(LED0, 1);
		Delay_Ms(100);
		LED_Control(LED0, 0);
		Delay_Ms(100);
	}
}

//
void Delay_Ms(u32 nTime)
{
	TimingDelay = nTime;
	while(TimingDelay != 0);	
}
