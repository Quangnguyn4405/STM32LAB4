/*
 * scheduler.h
 *
 *  Created on: Nov 17, 2025
 *      Author: Admin
 */

#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "main.h"

#define SCH_MAX_TASKS           10
#define NO_TASK_ID              0

typedef struct sTask {
    void (*pTask)(void);
    uint32_t Delay;
    uint32_t Period;
    uint8_t RunMe;
    uint32_t TaskID;
    struct sTask* pNext;
} sTask;

extern sTask* SCH_listHead;
extern uint32_t SCH_taskID_counter;

void SCH_Init(void);
void SCH_Update(void);
void SCH_Dispatch_Tasks(void);
uint32_t SCH_Add_Task(void (*pFunction)(), uint32_t DELAY, uint32_t PERIOD);
uint8_t SCH_Delete_Task(uint32_t taskID);

#endif
