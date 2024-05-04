/*
 * tasklist.h
 *
 *  Created on: May 4, 2024
 *      Author: jacki
 */

#ifndef INC_TASKLIST_H_
#define INC_TASKLIST_H_

#include <stdbool.h>
#include <stdint.h>
#define MAXTASK 32

typedef struct Task{
	bool trim;
	bool crimp;
	uint16_t length;	
	uint8_t qty;
}Task;

typedef struct TaskQueue{
	Task Queue[MAXTASK];
	uint8_t headInd; 
	uint8_t tailInd;
	uint8_t qsize;
}TaskQueue;

bool TaskList_Enqueue(TaskQueue* queue, bool isTrim, bool isCrimp, uint16_t lenght, uint8_t quantity);
Task TaskList_Dequeue(TaskQueue* queue);
const Task* TaskList_Peek(TaskQueue* queue);
bool TaskList_isEmpty(TaskQueue* queue);

#endif /* INC_TASKLIST_H_ */
