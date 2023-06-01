/*
 * MyTasks.c
 *
 *  Created on: May 30, 2023
 *      Author: eduardomunoz
 */

#include "MyTasks.h"
#include "main.h"


//might want to use a mutex in order to control what can print!!, i.e. not allow


void TX_task(void *argument)
{

	UART_escapes("[2J");

	for(;;)
	{
		//		UART_escapes("[H");
		//		UART_print("this is a test for tx");
		//		print_GM();
	}
}

void RX_task(void *argument)
{
	char payload[20] = "";
	UART_escapes("[H");
	UART_escapes("[2J");
	UART_escapes("[1B");
	UART_escapes("[s");
	for(;;)
	{

//		UART_escapes("8");
//		UART_print("this is a test for rx");


	}

}

void print_task(void *argument)
{
	for(;;)
	{

	}
}
