/*
 * MyTasks.c
 *
 *  Created on: May 30, 2023
 *      Author: eduardomunoz
 */

#include "MyTasks.h"
#include "main.h"
#include "semphr.h"
#include "message_buffer.h"
#include "spsgrf.h"

extern uint8_t DMorGM;
extern uint8_t newaddressflag;
extern uint8_t newaddresscount;
extern SpiritFlagStatus xTxDoneFlag;
extern IrqList xRxDoneFlag;
extern payload[PAYLOAD_SIZE];
extern TaskHandle_t TXmessage_Handler,RXmessage_Handler, printmessage_Handler;
extern People *head;

//this link always point to last Link
extern People *last;

extern People *this;

//might want to use a mutex in order to control what can print!!, i.e. not allow

MessageBufferHandle_t xpayLoad;
SemaphoreHandle_t xTXsem = NULL;
SemaphoreHandle_t xPrintNodes = NULL;
SemaphoreHandle_t xTXorRX = NULL;

People Node1;
Packets packetdata;
Packets gmpacket;

void TX_task(void *argument)
{
	packetdata.message[0] = 2;


	size_t xBytesSent;
	UART_escapes("[2J");
	uint8_t curraddress;
	xTXsem = xSemaphoreCreateBinary();
	xPrintNodes = xSemaphoreCreateMutex();
	xTXorRX = xSemaphoreCreateBinary();

    if( xTXsem != NULL && xPrintNodes != NULL)
    {
		for(;;)
		{
			if(DMorGM==2)
			{
				UART_print("DM to: 0x");
				UART_print(packetdata.address);
				DMorGM=0;

			}

			if(xSemaphoreTake( xTXsem, ( TickType_t ) 100 ) == pdTRUE )
			{

				do {

					/* Go to the ready state */
					if (g_xStatus.MC_STATE == MC_STATE_LOCK) {
						SpiritCmdStrobeReady();
					} else {
						SpiritCmdStrobeSabort();
					}

					/* Delay for state transition */
					for (volatile uint8_t i = 0; i != 0xFF; i++);

					/* Update the global status register variable */
					SpiritRefreshStatus();

				} while (g_xStatus.MC_STATE != MC_STATE_READY);

//				vTaskSuspend(RXmessage_Handler);
//				if(xSemaphoreTake( xTXorRXmutex, ( TickType_t ) 100 ) == pdTRUE )
//				{
				sscanf(packetdata.address, "%x", &curraddress);
			    SpiritPktCommonSetDestinationAddress(curraddress);

				xTxDoneFlag = READY;

				// Send the payload
				SPSGRF_StartTx(packetdata.message, strlen(packetdata.message));
				while(!xTxDoneFlag);
				UART_print("Message Sent\n\r");
				memset(&packetdata.message[1], '\0', PAYLOAD_SIZE-1);
				xRxDoneFlag = S_RESET;
//				SPSGRF_StartRx();

//				xSemaphoreGive(xTXorRXmutex);
//				}
//				vTaskResume(RXmessage_Handler);
			}

		}

    }
}

void RX_task(void *argument)
{
	xpayLoad = xMessageBufferCreate(PAYLOAD_SIZE);
//	if(xpayLoad!=NULL)
//	{
		size_t xBytesSent;
		volatile char payloadl[PAYLOAD_SIZE] = "";
//		UART_escapes("[H");
//		UART_escapes("[2J");
//		UART_escapes("[1B");
//		UART_escapes("[s");
		for(;;)
		{



				xRxDoneFlag = READY;
					SPSGRF_StartRx();

					while (xRxDoneFlag == READY);

					if(xRxDoneFlag == RX_DATA_READY)
					{
					SPSGRF_GetRxData(payloadl);


					xBytesSent = xMessageBufferSend( xpayLoad,
							( void * ) payloadl,
							strlen( payloadl), 100);

					if( xBytesSent != strlen( payloadl) )
					{
						/* The string could not be added to the message buffer because there was
		        not enough free space in the buffer. */
					}
					memset(payloadl, '\0', PAYLOAD_SIZE);
					}

		}

}

void print_task(void *argument)
{

	size_t xBytesReceived;
	char ucRxData[PAYLOAD_SIZE]={'\0'};
	size_t xReceivedBytes;
	const TickType_t xBlockTime = pdMS_TO_TICKS( 20 );

	for(;;)
	{
		if(newaddressflag == 255)
		{
			if(xSemaphoreTake(xPrintNodes, ( TickType_t ) 100 ))
			{
				uint8_t listnum = 1;
			    char str[5];


				People *ptr = head;
				while(ptr != NULL)
				{
				    itoa(listnum, str, 10);
					UART_print(str);
					UART_print(": ");
					UART_print(ptr->Name);
					UART_print(" at 0x");
					UART_print(ptr->address);
					UART_print("\n\r");
					ptr = ptr->next;
					++listnum;
				}
				listnum = 1;
				UART_print("Enter Desired Contact(1,2,or 3...):");
				while(newaddressflag==255);
				uint8_t wantedaddr = atoi(packetdata.address);

				ptr = head;

				do
				{
					ptr = ptr->next;
					++listnum;
				}while(listnum < wantedaddr);

				strcpy(packetdata.address, ptr->address);

				xSemaphoreGive(xPrintNodes);
				newaddressflag = 0;

			}
		}

		memset(ucRxData, '\0', PAYLOAD_SIZE);
		xReceivedBytes = xMessageBufferReceive( xpayLoad,
		                                            ( void * ) ucRxData,
		                                            sizeof( ucRxData ),
		                                            xBlockTime );

		    if( xReceivedBytes > 0 && (ucRxData[0]==2))
		    {
		    	if(ucRxData[0]==2) UART_print("DM from ");

		    	uint8_t sAddress = SpiritPktCommonGetReceivedSourceAddress();
		    	char sAddString[2];
		    	itoa(sAddress, sAddString, 16);
		    	UART_print("0x");
		    	UART_print(sAddString);
		    	UART_print(":");

		    	UART_print(&ucRxData[1]);
		    	UART_print("\n");
		    }
		    else if( xReceivedBytes > 0 &&ucRxData[0]==6)
		    {
		    	uint8_t sAddress = SpiritPktCommonGetReceivedSourceAddress();
		    	char sAddString[2];
		    	itoa(sAddress, sAddString, 16);
		    	UART_print("New Node: ");
		    	UART_print(&ucRxData[1]);
		    	ucRxData[strlen(&ucRxData[1])]='\0';
		    	People *tempnode = CreateNode(sAddString,&ucRxData[1]);
		    	insertLast(tempnode);

		    }

	}
}
