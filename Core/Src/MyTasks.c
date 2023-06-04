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
#include "usart.h"

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
	volatile uint8_t curraddress;
	xTXsem = xSemaphoreCreateBinary();
	xPrintNodes = xSemaphoreCreateMutex();
	xTXorRX = xSemaphoreCreateBinary();

    if( xTXsem != NULL && xPrintNodes != NULL)
    {
		for(;;)
		{
			if(DMorGM==2 || DMorGM==3)
			{
				if(xSemaphoreTake(xPrintNodes, ( TickType_t ) 100 ))
				{
					print_message_id();
					DMorGM=0;
		    		xSemaphoreGive(xPrintNodes);
				}


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
				UART_print("\n\r");
				memset(&packetdata.message[1], '\0', PAYLOAD_SIZE-1);
				xRxDoneFlag = S_RESET;
				if(packetdata.message[0]==6)packetdata.message[0] =2;
				print_message_id();
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

		size_t xBytesSent;
		volatile char payloadl[PAYLOAD_SIZE] = "";
		for(;;)
		{



				xRxDoneFlag = READY;
					SPSGRF_StartRx();

					while (xRxDoneFlag == READY);

					if(xRxDoneFlag == RX_DATA_READY)
					{
					SPSGRF_GetRxData(payloadl);

					if(payloadl[0]==6)
					{
						if(xSemaphoreTake(xPrintNodes, ( TickType_t ) 100 ))
						{


							uint8_t sAddress = SpiritPktCommonGetReceivedSourceAddress();
							char sAddString[2];
							itoa(sAddress, sAddString, 16);
							People *ptr = FindInList(sAddString);
							if(ptr == NULL)
							{
								UART_print("\r");
								UART_escapes("[2K"); //clear line
								UART_print("New Node: ");
								UART_print(&payloadl[1]);
								UART_print("\n\r");
								payloadl[strlen(&payloadl[1])]='\0';
								People *tempnode = CreateNode(sAddString,&payloadl[1]);
								insertLast(tempnode);
							}
							xSemaphoreGive(xPrintNodes);

						}


					}
					else{

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

}

void print_task(void *argument)
{

	char ucRxData[PAYLOAD_SIZE]={'\0'};
	size_t xReceivedBytes;
	const TickType_t xBlockTime = pdMS_TO_TICKS( 20 );

	for(;;)
	{
		if(newaddressflag == 255)
		{
			memset(&packetdata.message[1], '\0', PAYLOAD_SIZE-1);

				print_linkedList();




		}
		else
		{
		memset(ucRxData, '\0', PAYLOAD_SIZE);
		xReceivedBytes = xMessageBufferReceive( xpayLoad,
		                                            ( void * ) ucRxData,
		                                            sizeof( ucRxData ),
		                                            xBlockTime );

		    if( xReceivedBytes > 0 && (ucRxData[0]==2))
		    {

		    	uint8_t currmesslen = strlen(&packetdata.message[1]);
		    	if(currmesslen>1)
		    	{
	    			UART_print("\r");
		    		UART_escapes("[2K"); //clear line
		    	}
		    	if(xSemaphoreTake(xPrintNodes, ( TickType_t ) 100 ))
		    	{
		    		uint8_t sAddress = SpiritPktCommonGetReceivedSourceAddress();
		    		char sAddString[2];
		    		itoa(sAddress, sAddString, 16);

		    		People *ptr = FindInList(sAddString); //used to only print contacts
		    		if(ptr != NULL) //if Null means message is not from a contact
		    		{
		    			UART_print("\r");
			    		UART_escapes("[2K"); //clear line
		    			if(ucRxData[0]==2 && SpiritPktCommonGetReceivedDestAddress() == MY_ADDRESS) {

		    				UART_print("DM from ");
		    			}
		    			else if(ucRxData[0]==2) {
		    				UART_print("GM from ");
		    			}


		    			UART_print("0x");
		    			UART_print(sAddString);
		    			UART_print("  ");
		    			UART_print(ptr->Name);
		    			UART_print(": ");

		    			UART_print(&ucRxData[1]);
		    			UART_print("\n");
		    		}
		    		if(currmesslen>1)
		    		{
		    			print_message_id();
		    			UART_print(&packetdata.message[1]);
		    		}
		    		else
		    		{
		    			print_message_id();
		    		}
		    		xSemaphoreGive(xPrintNodes);
		    	}
		    }
		}

	}
}


