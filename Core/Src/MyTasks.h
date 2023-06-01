/*
 * MyTasks.h
 *
 *  Created on: May 30, 2023
 *      Author: eduardomunoz
 */
#include "cmsis_os.h"
#include "main.h"
#include "spsgrf.h"



#ifndef SRC_MYTASKS_H_
#define SRC_MYTASKS_H_




void TX_task(void *argument);

void RX_task(void *argument);

void print_task(void *argument);



#endif /* SRC_MYTASKS_H_ */
