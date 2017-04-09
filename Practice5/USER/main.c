#include <stdio.h>
#include <string.h>
#include "stm32f10x.h"
#include "lcd.h"
#include "led.h"
#include "beep.h"
#include "key.h"
#include "usart.h"
#include "rtc.h"
#include "adc.h"
#include "timer.h"
#include "i2c.h"
#include "eeprom.h"

uint8_t NbrOfDataToRead = 20;
uint8_t RxCounter;
uint8_t RxFlag;
uint8_t RxBuffer[20] = {0};
uint32_t timingDelay;
uint8_t timeDisplayFlag = 0;
uint8_t adcDisplayFlag = 0;
char lcdString[20] = {0};

void DelayMs(uint32_t nTime)
{
    timingDelay = nTime;
    while (timingDelay != 0);
}

int main (void)
{
	uint8_t i; 
	
    SysTick_Config(SystemCoreClock/1000);
    NVIC_SetPriority(SysTick_IRQn, 0);
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

//	BEEP_Config();
	ADC_Config();
    LED_Config();
    KEY_Config();
	RTC_Config();
	TIMER_Config();
    USART_Config();
    STM3210B_LCD_Init();
    LCD_Clear(Blue);
    LCD_SetTextColor(White);
    LCD_SetBackColor(Blue);

    //USART_SendData(USART2, 'a');
    LCD_DisplayStringLine(Line1, "      Practice5     ");
    LED_Control(LEDALL, 0);

    printf("Are you OK?\n");

    GPIO_ResetBits(GPIOB, GPIO_Pin_4);
    DelayMs(100);
    GPIO_SetBits(GPIOB, GPIO_Pin_4);
    DelayMs(100);
	
    while (1) {	
		if (adcDisplayFlag == 1) {
			sprintf(lcdString, "      V:%.2f      ", Read_ADC());
			LCD_DisplayStringLine(Line3, (u8 *)lcdString);
			adcDisplayFlag = 0;
		}

		if (timeDisplayFlag == 1) {
			DisplayTime();
			LED_Control(LEDALL, 0);
		}
		if (RxFlag == 1) {
//			USART_SendData(USART2, RxBuffer[0]);
			printf("%s\n", RxBuffer);
            if (strstr((char *)RxBuffer, "LED1ON") != 0) {
                LED_Control(LEDALL, 0);
                LED_Control(LED1, 1);
            }
            if (strstr((char *)RxBuffer, "LED2ON") != 0) {
                LED_Control(LEDALL, 0);
                LED_Control(LED2, 1);
            }
            RxFlag = 0;
						
			for (i = 0; i < 20; i++) {
				RxBuffer[i] = ' ';
			}
            USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
        }
    }
}

