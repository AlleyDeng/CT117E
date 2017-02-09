#include "timer.h"
#include "led.h"

/**
  * @brief：通用定时器TIM3配置函数 
  * @param: None
  * @retval: None 
  */
void TIM_Config(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	/* TIM3 clock enable */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	
	/* NVIC configuration */
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);
	
	/* TIM3 base configuration*/
	TIM_TimeBaseStructure.TIM_Period = 499;			/* 延时50ms */			
	TIM_TimeBaseStructure.TIM_Prescaler = 7199;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;	
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	/* 通用定时器TIM3中断配置 */
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);	/* 使能TIM3中断，允许中断更新 */
	/* TIM3 enable counter */
	TIM_Cmd(TIM3, ENABLE);
}

void TIM3_IRQHandler(void)
{
	extern unsigned int n50Ms;
	extern unsigned int num;
	if (TIM_GetFlagStatus(TIM3, TIM_FLAG_Update) == SET) {
		TIM_ClearFlag(TIM3, TIM_FLAG_Update);	/* 清除标志位 */
		n50Ms++;
		if (n50Ms == 20) {
			n50Ms = 0;
			num++;
		}
	}
}	
