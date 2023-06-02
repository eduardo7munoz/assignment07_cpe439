/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    usart.c
  * @brief   This file provides code for the configuration
  *          of the USART instances.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "usart.h"
#include"FreeRTOS.h"
#include "semphr.h"
#include "spsgrf.h"
#include "MyTasks.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */
#define PAYLOAD_SIZE 100
UART_HandleTypeDef huart2;
uint16_t count = 1;
extern uint8_t DMorGM;
extern char payload[PAYLOAD_SIZE];
extern uint8_t sendflag;
extern xTXsem;
extern TaskHandle_t TXmessage_Handler,RXmessage_Handler, printmessage_Handler;
extern Packets packetdata;
extern Packets gmpacket;
uint8_t newaddressflag;
uint8_t newaddresscount;

/* USART2 init function */

void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
	  huart2.Instance = USART2;
	  huart2.Init.BaudRate = 115200;
	  huart2.Init.WordLength = UART_WORDLENGTH_8B;
	  huart2.Init.StopBits = UART_STOPBITS_1;
	  huart2.Init.Parity = UART_PARITY_NONE;
	  huart2.Init.Mode = UART_MODE_TX_RX;
	  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
	  huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
	  huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
	  __enable_irq();

  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};
  if(uartHandle->Instance==USART2)
  {
  /* USER CODE BEGIN USART2_MspInit 0 */

  /* USER CODE END USART2_MspInit 0 */

  /** Initializes the peripherals clock
  */
    PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART2;
    PeriphClkInit.Usart2ClockSelection = RCC_USART2CLKSOURCE_PCLK1;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
    {
      Error_Handler();
    }

    /* USART2 clock enable */
    __HAL_RCC_USART2_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**USART2 GPIO Configuration
    PA2     ------> USART2_TX
    PA3     ------> USART2_RX
    */
    GPIO_InitStruct.Pin = USART_TX_Pin|USART_RX_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
    __HAL_UART_ENABLE_IT(&huart2,UART_IT_RXNE);
    /* USART2 interrupt Init */
    HAL_NVIC_SetPriority(USART2_IRQn, 5, 0);
    HAL_NVIC_EnableIRQ(USART2_IRQn);
  /* USER CODE BEGIN USART2_MspInit 1 */

  /* USER CODE END USART2_MspInit 1 */
  }
}

void HAL_UART_MspDeInit(UART_HandleTypeDef* uartHandle)
{

  if(uartHandle->Instance==USART2)
  {
  /* USER CODE BEGIN USART2_MspDeInit 0 */

  /* USER CODE END USART2_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART2_CLK_DISABLE();

    /**USART2 GPIO Configuration
    PA2     ------> USART2_TX
    PA3     ------> USART2_RX
    */
    HAL_GPIO_DeInit(GPIOA, USART_TX_Pin|USART_RX_Pin);

    /* USART2 interrupt Deinit */
    HAL_NVIC_DisableIRQ(USART2_IRQn);
  /* USER CODE BEGIN USART2_MspDeInit 1 */

  /* USER CODE END USART2_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */

void UART_print(char *outputstring)
{
	for(uint16_t currchar = 0; currchar<strlen(outputstring);currchar++)
	{
		while(!(USART2->ISR & USART_ISR_TXE)); //Transmit data register empty, using negation since value of 0 means data has not been transferred

		USART2->TDR = outputstring[currchar];
	}

}

void USART2_IRQHandler()
{
	BaseType_t xHigherPriorityTaskWoken = pdFALSE;


	uint8_t RX = USART2->RDR;
	char tempstr[6]={'\0'};
	switch(RX)
	{

			break;
		case 'J':
			UART_escapes("[2J"); //clear everything
			break;


		case 'D':
			packetdata.message[0] = 2;
			DMorGM =1;
			UART_escapes("[s");
		case '$':
			newaddressflag = 1;
			UART_print("Enter Address");
			break;
		case 'G':
				packetdata.message[0] = 6;
				packetdata.address[0] = 'F';//hardcoding broadcast address
				packetdata.address[1] = 'F';
			break;
		default:


			if(newaddressflag)
			{

				packetdata.address[newaddresscount] = RX;
				++newaddresscount;
				USART2->TDR=RX;
				if(newaddresscount == 2)
				{

					DMorGM=2;
					newaddressflag = 0;
					newaddresscount = 0;
				}

			}
			else
			{
				packetdata.message[count] = RX;
				++count;
				while(!(USART2->ISR & USART_ISR_TXE));
				USART2->TDR=RX;

				if(RX == '\r') {
					count = 1;
					xSemaphoreGiveFromISR( xTXsem, &xHigherPriorityTaskWoken );



				}
			}
				break;
	}
}

void UART_escapes(char *escstring)
{
	while(!(USART2->ISR & USART_ISR_TXE));//do not advance until receiving transmit flag
	USART2->TDR = (0x1B);  // ESC
	UART_print(escstring);

}

void print_DM()
{
	UART_escapes("[31m");
}

void print_GM()
{
	UART_escapes("[32m");
}


/* USER CODE END 1 */
