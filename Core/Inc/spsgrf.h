/*
 * spsgrf.h
 *
 *  Created on: May 27, 2023
 *      Author: eduardomunoz
 */

#ifndef SRC_SPSGRF_H_
#define SRC_SPSGRF_H_


/**
******************************************************************************
* @file    spsgrf.h
* @author  Matthew Mielke
* @version V1.0.0
* @date    07-Jul-2021
* @brief   An abstraction of the SPIRIT1 library for the SPSGRF module.
******************************************************************************
*/

/* Includes ------------------------------------------------------------------*/
#include "SPIRIT_Config.h"


/* Exported constants --------------------------------------------------------*/
#define XTAL_FREQUENCY              50000000

/*  Radio configuration parameters  */
#define XTAL_OFFSET_PPM             0
//#define INFINITE_TIMEOUT            0.0
#define BASE_FREQUENCY              915.0e6
#define CHANNEL_SPACE               100e3
#define CHANNEL_NUMBER              0
#define MODULATION_SELECT           FSK
#define DATARATE                    38400
#define FREQ_DEVIATION              20e3
#define BANDWIDTH                   100E3

#define POWER_INDEX                 7
#define POWER_DBM                   11.6

#define RECEIVE_TIMEOUT            	2000.0 // change the value for required timeout period
#define RSSI_THRESHOLD              -120  // Default RSSI at reception, more than noise floor
//#define CSMA_RSSI_THRESHOLD         -90   // Higher RSSI to Transmit. If it's lower, the Channel will be seen as busy.

///*  Packet configuration parameters  */
#define PREAMBLE_LENGTH             PKT_PREAMBLE_LENGTH_04BYTES
#define SYNC_LENGTH                 PKT_SYNC_LENGTH_4BYTES
#define SYNC_WORD                   0x88888888
#define LENGTH_TYPE                 PKT_LENGTH_VAR
#define LENGTH_WIDTH                7
#define CRC_MODE                    PKT_CRC_MODE_8BITS
#define CONTROL_LENGTH              PKT_CONTROL_LENGTH_0BYTES
#define EN_ADDRESS                  S_ENABLE
#define EN_FEC                      S_DISABLE
#define EN_WHITENING                S_ENABLE

#define EN_FILT_MY_ADDRESS          S_ENABLE
#define EN_FILT_MULTICAST_ADDRESS   S_ENABLE
#define EN_FILT_BROADCAST_ADDRESS   S_ENABLE
#define MY_ADDRESS                  0xED
#define MULTICAST_ADDRESS           0xEE
#define BROADCAST_ADDRESS           0xFF

#define MAX_BUFFER_LEN              96
#define MAX_PAYLOAD_LEN             126 // (2^7 - 1) - 1 - 0 = 126 (LENGTH_WID=7, 1 address byte, & 0 control bytes)

#define EQUAL_STRINGS               0

/* Exported functions --------------------------------------------------------*/
void SPSGRF_Init(void);
void SPSGRF_StartTx(uint8_t *txBuff, uint8_t txLen);
void SPSGRF_StartRx(void);
uint8_t SPSGRF_GetRxData(uint8_t *rxBuff);

typedef struct mystackpackets
{
	volatile char message[100];
	char address[2];
}Packets;

typedef struct Node
{
	char address[4];
	char Name[100];
	struct People *next;

}People;

People *CreateNode(char *address, char *name);

uint8_t sizeList(void);

void insertLast(People *link);

People* FindInList (char *keyAddress);


/*** end of file ***/


#endif /* SRC_SPSGRF_H_ */
