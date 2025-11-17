/*
 * scheduler.c
 *
 *  Created on: Nov 17, 2025
 *      Author: Admin
 */


#include "scheduler.h"

// Mảng task và biến global
sTask SCH_tasks_G[SCH_MAX_TASKS];
uint32_t SCH_taskID_counter = 1;

/**
 * Khởi tạo scheduler
 */
void SCH_Init(void) {
    uint8_t i;

    for (i = 0; i < SCH_MAX_TASKS; i++) {
        SCH_tasks_G[i].pTask = 0;
        SCH_tasks_G[i].Delay = 0;
        SCH_tasks_G[i].Period = 0;
        SCH_tasks_G[i].RunMe = 0;
        SCH_tasks_G[i].TaskID = 0;
    }

    SCH_taskID_counter = 1;
}

/**
 * Cập nhật scheduler - được gọi từ Timer ISR mỗi 10ms
 */
void SCH_Update(void) {
    uint8_t Index;

    for (Index = 0; Index < SCH_MAX_TASKS; Index++) {
        if (SCH_tasks_G[Index].pTask) {
            if (SCH_tasks_G[Index].Delay == 0) {
                SCH_tasks_G[Index].RunMe += 1;

                if (SCH_tasks_G[Index].Period) {
                    SCH_tasks_G[Index].Delay = SCH_tasks_G[Index].Period;
                }
            } else {
                SCH_tasks_G[Index].Delay -= 1;
            }
        }
    }
}

/**
 * Dispatcher - thực thi các task đã sẵn sàng
 */
void SCH_Dispatch_Tasks(void) {
    uint8_t Index;

    for (Index = 0; Index < SCH_MAX_TASKS; Index++) {
        if (SCH_tasks_G[Index].RunMe > 0) {

            (*SCH_tasks_G[Index].pTask)();

            SCH_tasks_G[Index].RunMe -= 1;

            if (SCH_tasks_G[Index].Period == 0) {
                SCH_Delete_Task(SCH_tasks_G[Index].TaskID);
            }
        }
    }
}

/**
 * Thêm task vào scheduler
 */
uint32_t SCH_Add_Task(void (*pFunction)(), uint32_t DELAY, uint32_t PERIOD) {
    uint8_t Index = 0;

    while ((SCH_tasks_G[Index].pTask != 0) && (Index < SCH_MAX_TASKS)) {
        Index++;
    }

    if (Index == SCH_MAX_TASKS) {
        return 0;
    }

    SCH_tasks_G[Index].pTask = pFunction;
    SCH_tasks_G[Index].Delay = DELAY;
    SCH_tasks_G[Index].Period = PERIOD;
    SCH_tasks_G[Index].RunMe = 0;
    SCH_tasks_G[Index].TaskID = SCH_taskID_counter++;

    return SCH_tasks_G[Index].TaskID;
}

/**
 * Xóa task khỏi scheduler
 */
uint8_t SCH_Delete_Task(uint32_t taskID) {
    uint8_t Index;

    for (Index = 0; Index < SCH_MAX_TASKS; Index++) {
        if (SCH_tasks_G[Index].TaskID == taskID) {
            SCH_tasks_G[Index].pTask = 0;
            SCH_tasks_G[Index].Delay = 0;
            SCH_tasks_G[Index].Period = 0;
            SCH_tasks_G[Index].RunMe = 0;
            SCH_tasks_G[Index].TaskID = 0;

            return 0;
        }
    }

    return 1;
}
