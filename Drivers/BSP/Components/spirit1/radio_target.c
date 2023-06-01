/*
 * radio_target.c
 *
 *  Created on: May 27, 2023
 *      Author: eduardomunoz
 */
/**
******************************************************************************
* @file    radio_target.c
* @author  Matthew Mielke
* @version V1.0.0
* @date    07-Jul-2021
* @brief     Defines the implementation of the SPIRIT1 interface for the
*          target platform.
******************************************************************************
*/


/* Includes ------------------------------------------------------------------*/
#include "radio_target.h"
#include "MCU_Interface.h"


/* Private defines -----------------------------------------------------------*/
#define HEADER_WRITE_MASK     0x00 /*!< Write mask for header byte*/
#define HEADER_READ_MASK      0x01 /*!< Read mask for header byte*/
#define HEADER_ADDRESS_MASK   0x00 /*!< Address mask for header byte*/
#define HEADER_COMMAND_MASK   0x80 /*!< Command mask for header byte*/

#define BUILT_HEADER(add_comm, w_r) (add_comm | w_r)  /*!< macro to build the header byte*/
#define WRITE_HEADER    BUILT_HEADER(HEADER_ADDRESS_MASK, HEADER_WRITE_MASK) /*!< macro to build the write header byte*/
#define READ_HEADER     BUILT_HEADER(HEADER_ADDRESS_MASK, HEADER_READ_MASK)  /*!< macro to build the read header byte*/
#define COMMAND_HEADER  BUILT_HEADER(HEADER_COMMAND_MASK, HEADER_WRITE_MASK) /*!< macro to build the command header byte*/

#define LINEAR_FIFO_ADDRESS 0xFF  /*!< Linear FIFO address*/


/* External functions --------------------------------------------------------*/
/**
* @brief  The SPI peripheral should already be initialized. This function simply
*         confirms that it is.
* @param  None
* @retval None
*/
void RadioSpiInit(void)
{
  if (radioSpi->State == HAL_SPI_STATE_RESET)
  {
    Error_Handler();
  }
}


/**
* @brief  Write single or multiple registers.
* @param  cRegAddress: base register's address to be write
* @param  cNbBytes: number of registers and bytes to be write
* @param  pcBuffer: pointer to the buffer of values have to be written into registers
* @retval Device status
*/
StatusBytes RadioSpiWriteRegisters(uint8_t cRegAddress, uint8_t cNbBytes, uint8_t* pcBuffer)
{
  uint8_t tx_buff[2] = {WRITE_HEADER, cRegAddress};
  uint8_t rx_buff[2];
  StatusBytes status;

  SPI_ENTER_CRITICAL();

  RadioSpiCSLow(); // Puts the SPI chip select low to start the transaction
  HAL_SPI_TransmitReceive(radioSpi, tx_buff, rx_buff, 2, RADIO_SPI_TIMEOUT_MAX);
  HAL_SPI_Transmit(radioSpi, pcBuffer, cNbBytes, RADIO_SPI_TIMEOUT_MAX);
  RadioSpiCSHigh(); // Puts the SPI chip select high to end the transaction

  SPI_EXIT_CRITICAL();

  ((uint8_t *)&status)[1] = rx_buff[0];
  ((uint8_t *)&status)[0] = rx_buff[1];

  return status;

}

/**
* @brief  Read single or multiple registers.
* @param  cRegAddress: base register's address to be read
* @param  cNbBytes: number of registers and bytes to be read
* @param  pcBuffer: pointer to the buffer of registers' values read
* @retval Device status
*/
StatusBytes RadioSpiReadRegisters(uint8_t cRegAddress, uint8_t cNbBytes, uint8_t* pcBuffer)
{
  uint8_t tx_buff[2] = {READ_HEADER, cRegAddress};
  uint8_t rx_buff[2];
  StatusBytes status;

  SPI_ENTER_CRITICAL();

  RadioSpiCSLow();  // Puts the SPI chip select low to start the transaction
  HAL_SPI_TransmitReceive(radioSpi, tx_buff, rx_buff, 2, RADIO_SPI_TIMEOUT_MAX);
  HAL_SPI_Receive(radioSpi, pcBuffer, cNbBytes, RADIO_SPI_TIMEOUT_MAX);
  RadioSpiCSHigh(); // Puts the SPI chip select high to end the transaction

  SPI_EXIT_CRITICAL();

  ((uint8_t *)&status)[1] = rx_buff[0];
  ((uint8_t *)&status)[0] = rx_buff[1];

  return status;
}

/**
* @brief  Send a command
* @param  cCommandCode: command code to be sent
* @retval Device status
*/
StatusBytes RadioSpiCommandStrobes(uint8_t cCommandCode)
{
  uint8_t tx_buff[2] = {COMMAND_HEADER, cCommandCode};
  uint8_t rx_buff[2];
  StatusBytes status;

  SPI_ENTER_CRITICAL();

  RadioSpiCSLow();  // Puts the SPI chip select low to start the transaction
  HAL_SPI_TransmitReceive(radioSpi, tx_buff, rx_buff, 2, RADIO_SPI_TIMEOUT_MAX);
  RadioSpiCSHigh(); // Puts the SPI chip select high to end the transaction

  SPI_EXIT_CRITICAL();

  ((uint8_t *)&status)[1] = rx_buff[0];
  ((uint8_t *)&status)[0] = rx_buff[1];

  return status;
}


/**
* @brief  Write data into TX FIFO.
* @param  cNbBytes: number of bytes to be written into TX FIFO
* @param  pcBuffer: pointer to data to write
* @retval Device status
*/
StatusBytes RadioSpiWriteFifo(uint8_t cNbBytes, uint8_t* pcBuffer)
{
  uint8_t tx_buff[2] = {WRITE_HEADER, LINEAR_FIFO_ADDRESS};
  uint8_t rx_buff[2];
  StatusBytes status;

  SPI_ENTER_CRITICAL();

  RadioSpiCSLow();  // Puts the SPI chip select low to start the transaction
  HAL_SPI_TransmitReceive(radioSpi, tx_buff, rx_buff, 2, RADIO_SPI_TIMEOUT_MAX);
  HAL_SPI_Transmit(radioSpi, pcBuffer, cNbBytes, RADIO_SPI_TIMEOUT_MAX);
  RadioSpiCSHigh(); // Puts the SPI chip select high to end the transaction

  SPI_EXIT_CRITICAL();

  ((uint8_t *)&status)[1] = rx_buff[0];
  ((uint8_t *)&status)[0] = rx_buff[1];

  return status;
}


/**
* @brief  Read data from RX FIFO.
* @param  cNbBytes: number of bytes to read from RX FIFO
* @param  pcBuffer: pointer to data read from RX FIFO
* @retval Device status
*/
StatusBytes RadioSpiReadFifo(uint8_t cNbBytes, uint8_t* pcBuffer)
{
  uint8_t tx_buff[2] = {READ_HEADER, LINEAR_FIFO_ADDRESS};
  uint8_t rx_buff[2];
  StatusBytes status;

  SPI_ENTER_CRITICAL();

  RadioSpiCSLow();  // Puts the SPI chip select low to start the transaction
  HAL_SPI_TransmitReceive(radioSpi, tx_buff, rx_buff, 2, RADIO_SPI_TIMEOUT_MAX);
  HAL_SPI_Receive(radioSpi, pcBuffer, cNbBytes, RADIO_SPI_TIMEOUT_MAX);
  RadioSpiCSHigh();  // Puts the SPI chip select high to end the transaction

  SPI_EXIT_CRITICAL();

  ((uint8_t *)&status)[1] = rx_buff[0];
  ((uint8_t *)&status)[0] = rx_buff[1];

  return status;
}


/**
* @brief  Puts at logic 1 the SDN pin.
* @param  None.
* @retval None.
*/
void RadioEnterShutdown(void)
{
  /* Puts high the GPIO connected to shutdown pin */
  HAL_GPIO_WritePin(RADIO_SDN_PORT, RADIO_SDN_PIN, GPIO_PIN_SET);
}


/**
* @brief  Put at logic 0 the SDN pin.
* @param  None.
* @retval None.
*/
void RadioExitShutdown(void)
{
  /* Puts low the GPIO connected to shutdown pin */
  HAL_GPIO_WritePin(RADIO_SDN_PORT, RADIO_SDN_PIN, GPIO_PIN_RESET);

  /* Delay to allow the circuit POR, about 700 us */
  //for(volatile uint32_t i=0;i<0x1E00;i++);
  HAL_Delay(1); // 1ms (Note: Table 20 of SPIRIT1 datasheet specifies ~650 us)
}


/**
* @brief  check the logic(0 or 1) at the SDN pin.
* @param  None.
* @retval FlagStatus.
*/
SpiritFlagStatus RadioCheckShutdown(void)
{
  return HAL_GPIO_ReadPin(RADIO_SDN_PORT, RADIO_SDN_PIN);
}

