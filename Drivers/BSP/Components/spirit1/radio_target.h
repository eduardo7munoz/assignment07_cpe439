/*
 * radio_target.h
 *
 *  Created on: May 27, 2023
 *      Author: eduardomunoz
 */


/**
******************************************************************************
* @file    radio_target.h
* @author  Matthew Mielke
* @version V1.0.0
* @date    07-Jul-2021
* @brief     Defines several macros allowing the user to easily modify the
*          digital interface to the SPIRIT1 transceiver.
******************************************************************************
*/


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __RADIO_SPI_H
#define __RADIO_SPI_H

/* Includes ------------------------------------------------------------------*/
#include "spi.h"


/* Exported constants --------------------------------------------------------*/
SPI_HandleTypeDef *radioSpi = &hspi1;

#define RADIO_GPIO_IRQ        SPIRIT1_GPIO3_EXTI_IRQn
#define SPI_ENTER_CRITICAL()  HAL_NVIC_DisableIRQ(RADIO_GPIO_IRQ);
#define SPI_EXIT_CRITICAL()   HAL_NVIC_EnableIRQ(RADIO_GPIO_IRQ);

#define RadioSpiCSLow()       HAL_GPIO_WritePin(SPIRIT1_SPI_CSn_GPIO_Port, SPIRIT1_SPI_CSn_Pin, GPIO_PIN_RESET)
#define RadioSpiCSHigh()      HAL_GPIO_WritePin(SPIRIT1_SPI_CSn_GPIO_Port, SPIRIT1_SPI_CSn_Pin, GPIO_PIN_SET)

#define RADIO_SPI_TIMEOUT_MAX ((uint32_t)1000)

#define RADIO_SDN_PORT        SPIRIT1_SDN_GPIO_Port
#define RADIO_SDN_PIN         SPIRIT1_SDN_Pin

#endif /*__RADIO_SPI_H */


