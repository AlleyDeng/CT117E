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
	static uint8_t ms = 0;
	extern uint8_t adcDisplayFlag;
	extern uint32_t timingDelay;
	timingDelay--;
	if (++ms == 200) {
		adcDisplayFlag = 1;
		ms = 0;
	}
}


/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles USARTy global interrupt request.
  * @param  None
  * @retval None
  */
void USART2_IRQHandler(void)
{
	extern uint8_t RxBuffer[20];
	extern uint8_t RxCounter;
	extern int8_t RxStatus;
	extern float k;
	
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET) {
		if(RxCounter == 5 || RxBuffer[RxCounter] == '\r' || RxBuffer[RxCounter] == '\n') {
			RxCounter = 0;
			RxStatus = 1;
	//		USART_SendData(USART2, 'a');
			/* Disable the USARTy Receive interrupt */
			USART_ITConfig(USART2, USART_IT_RXNE, DISABLE);
		}	else {
			/* Read one byte from the receive data regist er */
			RxBuffer[RxCounter++] = USART_ReceiveData(USART2);	
		}
		if (RxStatus == 1) {
			RxStatus = 0;
			if (RxBuffer[3] > '0' && RxBuffer[3] <= '9' && 
			  RxBuffer[0] == 'k' && RxBuffer[1] == '0' && 
			  RxBuffer[2] == '.') {
				k = (RxBuffer[3] - '0') / 10.0;
				USART_SendString("OK\n");
			}
		}
	}
}

/**
  * @brief  This function handles RTC global interrupt request.
  * @param  None
  * @retval None
  */
void RTC_IRQHandler(void)
{
	extern float k;
	extern uint8_t timeDisplayFlag;
	extern uint32_t sendValtageTime;
	if (RTC_GetITStatus(RTC_IT_SEC) != RESET) {
		/* Clear the RTC Second interrupt */
		RTC_ClearITPendingBit(RTC_IT_SEC);		
		if (RTC_GetCounter() == 24*3600 - 1) {
			RTC_SetCounter(0);
		}	
		timeDisplayFlag = 1;
		if (timeDisplayFlag == 1) {
			TimeDisplay(RTC_GetCounter());
			timeDisplayFlag = 0;
		}	  
    /* Wait until last write operation on RTC registers has finished */
		RTC_WaitForLastTask();   
	}
}

/**
  * @brief  This function handles External line 0 interrupt request.
  * @param  None
  * @retval None
  */
void EXTI0_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line0) != RESET) {
		DelayMs(10);
		if (KEY1 == 0) {
			if (ledWorkFlag == 1) {
				ledWorkFlag = 0;
			}	else if (ledWorkFlag == 0) {
				ledWorkFlag = 1;
			}
		//	sprintf (lcdString, " Button1 pressed...");
		//	LCD_DisplayStringLine(Line8, lcdString);		
			while (KEY1 != 1);
		}
		/* Clear the  EXTI line 0 pending bit */
		EXTI_ClearITPendingBit(EXTI_Line0);
  }
}

/**
  * @brief  This function handles External lines 9 to 5 interrupt request.
  * @param  None
  * @retval None
  */
void EXTI9_5_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line8) != RESET) {
		DelayMs(10);
		sprintf (lcdString, " Button2 pressed...");
		LCD_DisplayStringLine(Line8, lcdString);			
		while (KEY2 != 1);
		/* Clear the  EXTI line 8 pending bit */
		EXTI_ClearITPendingBit(EXTI_Line8);
  }
}

/**
  * @brief  This function handles External line 1 interrupt request.
  * @param  None
  * @retval None
  */
void EXTI1_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line1) != RESET) {
		DelayMs(10);
		if (KEY3 == 0) {
			sprintf (lcdString, " Button3 pressed...");
			LCD_DisplayStringLine(Line8, lcdString);
			while (KEY3 != 1);
		}
		/* Clear the  EXTI line 0 pending bit */
		EXTI_ClearITPendingBit(EXTI_Line1);
  }
}

/**
  * @brief  This function handles External line 2 interrupt request.
  * @param  None
  * @retval None
  */
void EXTI2_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line2) != RESET) {
		DelayMs(10);
		if (KEY4 == 0) {
			sprintf (lcdString, " Button4 pressed...");
			LCD_DisplayStringLine(Line8, lcdString);		
			while (KEY4 != 1);
		}
		/* Clear the  EXTI line 0 pending bit */
		EXTI_ClearITPendingBit(EXTI_Line2);
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
