#include "scheduler.h"
#include <stdlib.h>

sTask* SCH_listHead = NULL;
uint32_t SCH_taskID_counter = 1;
static uint8_t task_count = 0;


static void SCH_Insert_Task(sTask* newTask);


/**
 * Khởi tạo scheduler
 */
void SCH_Init(void) {
    // Xóa toàn bộ linked list
    while(SCH_listHead != NULL) {
        sTask* temp = SCH_listHead;
        SCH_listHead = SCH_listHead->pNext;
        free(temp);
    }

    SCH_taskID_counter = 1;
    task_count = 0;
}

/**
 * Update
 */
void SCH_Update(void) {

    if (SCH_listHead == NULL) return;
    if (SCH_listHead->Delay > 0) {
        SCH_listHead->Delay--;
    }

    while (SCH_listHead != NULL && SCH_listHead->Delay == 0) {
        SCH_listHead->RunMe = 1;
        if (SCH_listHead->Period > 0) {
            SCH_listHead->Delay = SCH_listHead->Period;
            sTask* current = SCH_listHead;
            SCH_listHead = SCH_listHead->pNext;
            SCH_Insert_Task(current);
        } else {
            break;
        }
    }
}

/**
 * Hàm helper
 */
static void SCH_Insert_Task(sTask* newTask) {
    if (SCH_listHead == NULL || newTask->Delay < SCH_listHead->Delay) {
        if (SCH_listHead != NULL) {
            SCH_listHead->Delay -= newTask->Delay;
        }
        newTask->pNext = SCH_listHead;
        SCH_listHead = newTask;
    } else {
        sTask* current = SCH_listHead;
        uint32_t cumulative_delay = current->Delay;

        while (current->pNext != NULL &&
               cumulative_delay + current->pNext->Delay <= newTask->Delay) {
            cumulative_delay += current->pNext->Delay;
            current = current->pNext;
        }
        newTask->Delay -= cumulative_delay;
        if (current->pNext != NULL) {
            current->pNext->Delay -= newTask->Delay;
        }
        newTask->pNext = current->pNext;
        current->pNext = newTask;
    }
}

/**
 * Thêm task mới (Optimized)
 */
uint32_t SCH_Add_Task(void (*pFunction)(), uint32_t DELAY, uint32_t PERIOD) {
    if (task_count >= SCH_MAX_TASKS) {
        return 0;  // Đã đầy
    }
    sTask* newTask = (sTask*)malloc(sizeof(sTask));
    if (newTask == NULL) return 0;

    newTask->pTask = pFunction;
    newTask->Delay = DELAY;
    newTask->Period = PERIOD;
    newTask->RunMe = 0;
    newTask->TaskID = SCH_taskID_counter++;
    newTask->pNext = NULL;
    SCH_Insert_Task(newTask);

    task_count++;
    return newTask->TaskID;
}

/**
 * Dispatcher
 */
void SCH_Dispatch_Tasks(void) {
    sTask* current = SCH_listHead;
    sTask* prev = NULL;

    while (current != NULL) {
        if (current->RunMe > 0) {
            (*current->pTask)();
            current->RunMe--;
            if (current->Period == 0) {
                sTask* toDelete = current;

                if (prev == NULL) {
                    SCH_listHead = current->pNext;
                    current = SCH_listHead;
                } else {
                    prev->pNext = current->pNext;
                    current = current->pNext;
                }

                free(toDelete);
                task_count--;
                continue;
            }
        }
        prev = current;
        current = current->pNext;
    }
}

/**
 * Xóa task
 */
uint8_t SCH_Delete_Task(uint32_t taskID) {
    sTask* current = SCH_listHead;
    sTask* prev = NULL;

    while (current != NULL) {
        if (current->TaskID == taskID) {
            if (prev == NULL) {
                SCH_listHead = current->pNext;
            } else {
                prev->pNext = current->pNext;
            }
            if (current->pNext != NULL) {
                current->pNext->Delay += current->Delay;
            }

            free(current);
            task_count--;
            return 0;
        }
        prev = current;
        current = current->pNext;
    }
    return 1;
}
