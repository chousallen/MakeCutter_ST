/*
 * tasklist.c
 *
 *  Created on: May 4, 2024
 *      Author: jacki
 */

#include "tasklist.h"

void TaskList_Init(TaskQueue* queue){
    queue->headInd = 0;
    queue->tailInd = 0;
    queue->qsize = 0;
}
bool TaskList_Enqueue(TaskQueue* queue, bool isTrim, bool isCrimp, uint16_t length, uint8_t quantity){
    if (queue->qsize >= MAXTASK){
        return false;
    }
    Task temp;
    temp.trim = isTrim;
    temp.crimp = isCrimp;
    temp.length = length;
    temp.qty = quantity;
    queue->Queue[queue->tailInd] =temp;
    queue->qsize++;
    if (queue->tailInd == MAXTASK - 1){
        queue->tailInd = 0;
    }
    else {
        queue->tailInd++;
    }
    return true;
}

Task TaskList_Dequeue(TaskQueue* queue){
    Task temp = queue->Queue[queue->headInd];
    if (queue->headInd == MAXTASK - 1){
        queue->headInd = 0;
    }
    else {
        queue->headInd++;
    }
    queue->qsize--;
    return temp;
}

bool TaskList_isEmpty(TaskQueue* queue){
    if (queue->qsize <= 0) return true;
    else return false;
}

const Task* TaskList_Peek(TaskQueue* queue){
    return &(queue->Queue[queue->headInd]);
}

