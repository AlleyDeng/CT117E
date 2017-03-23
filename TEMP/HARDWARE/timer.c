#include "timer.h"

void TIMER_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	TIM_TimeBaseStructure.TIM_Period = 4999;
	TIM_TimeBaseStructure.TIM_Prescaler = 7199;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
	TIM_OCInitStructure.TIM_Pulse = Channel2Pulse;
	TIM_OC2Init(TIM2, &TIM_OCInitStructure);
	
	TIM_OCInitStructure.TIM_Pulse = Channel3Pulse;
	TIM_OC3Init(TIM2, &TIM_OCInitStructure);
	
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;				
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;			/* 上升沿捕获 */
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;	
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;				/* 输入不分频，分频即捕获到若干次中断一次 */
	TIM_ICInitStructure.TIM_ICFilter = 0;								/* 不滤波 */
	TIM_ICInit(TIM3, &TIM_ICInitStructure);
	
	TIM_Cmd(TIM2, ENABLE);
	TIM_ITConfig(TIM3, TIM_IT_CC2 | TIM_IT_Update, ENABLE);
	TIM_CtrlPWMOutputs(TIM2, ENABLE);	/* 使能TIM2 PWM输出模式 */
	
	/* 设置输入捕获 */
	
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;			/* 选择定时器的通道 */
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	/* 上升沿捕获 */
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;		/* 输入不分频,分频捕获到若干次中断一次 */
	TIM_ICInitStructure.TIM_ICFilter = 0;						/* 不滤波 */
	
	TIM_ICInit(TIM3, &TIM_ICInitStructure);
	
	/* TIM enable counter */
	TIM_Cmd(TIM3, ENABLE);
	
	/* Enable the CC2 Interrupt Request */
	TIM_ITConfig(TIM3, TIM_IT_CC2 | TIM_IT_Update, ENABLE);	/* 捕获中断与更新中断都打开 */
}	

	