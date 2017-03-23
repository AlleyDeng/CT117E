/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"

/** @addtogroup STM32F10x_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
	extern uint32_t timingDelay;
	timingDelay--;
}

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

void RTC_IRQHandler(void)
{
	extern uint8_t timeDisplayFlag;
	extern uint8_t adcDisplayFlag;

	adcDisplayFlag = 1;
	
	if (RTC_GetITStatus(RTC_IT_SEC) != RESET)
	{
		timeDisplayFlag = 1;
		
		if (RTC_GetCounter() == 3600*24-1) {
			RTC_SetCounter(0);
		}
		
		/* Clear Interrupt pending bit */
		RTC_ClearITPendingBit(RTC_FLAG_SEC);
	}
}


void USART2_IRQHandler(void)
{
	uint8_t temp;
	extern uint8_t RxFlag;
	extern uint8_t NbrOfDataToRead;
	extern uint8_t RxCounter;
	extern uint8_t RxBuffer[20];
	
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET) {
		/* Read one byte from the receive data register */
		temp = USART_ReceiveData(USART2);
		if(RxCounter == NbrOfDataToRead || temp == '\r') {
			/* Disable the USARTy Receive interrupt */
//			RxBuffer[RxCounter] = 0;
			RxFlag = 1;
			RxCounter = 0;
			USART_ITConfig(USART2, USART_IT_RXNE, DISABLE);
		}	else {
				RxBuffer[RxCounter++] = temp;
		}
	}	
}

void EXTI0_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line0) != RESET)
	{
		DelayMs(10);
		if (KEY0 == 0) {
			LCD_DisplayStringLine(Line7, " Button1 pressed... ");
		}
		/* Clear the  EXTI line 0 pending bit */
		EXTI_ClearITPendingBit(EXTI_Line0);
	}
}

void EXTI1_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line1) != RESET)
	{
		DelayMs(10);
		if (KEY2 == 0) {
			LCD_DisplayStringLine(Line7, " Button3 pressed... ");
		}
		/* Clear the  EXTI line 1 pending bit */
		EXTI_ClearITPendingBit(EXTI_Line1);
	}
}

void EXTI2_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line2) != RESET)
	{
		DelayMs(10);
		if (KEY3 == 0) {
			LCD_DisplayStringLine(Line7, " Button4 pressed... ");
		}
		/* Clear the  EXTI line 2 pending bit */
		EXTI_ClearITPendingBit(EXTI_Line2);
	}
}

void EXTI9_5_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line8) != RESET)
	{
		DelayMs(10);
		if (KEY1 == 0) {
			LCD_DisplayStringLine(Line7, " Button2 pressed... ");
		}
		/* Clear the  EXTI line 8 pending bit */
		EXTI_ClearITPendingBit(EXTI_Line8);
	}
}

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 


/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
