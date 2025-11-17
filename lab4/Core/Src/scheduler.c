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

    // Xóa tất cả task trong mảng
    for (i = 0; i < SCH_MAX_TASKS; i++) {
        SCH_tasks_G[i].pTask = 0;
        SCH_tasks_G[i].Delay = 0;
        SCH_tasks_G[i].Period = 0;
        SCH_tasks_G[i].RunMe = 0;
        SCH_tasks_G[i].TaskID = 0;
    }

    // Reset task ID counter
    SCH_taskID_counter = 1;
}

/**
 * Cập nhật scheduler - được gọi từ Timer ISR mỗi 10ms
 */
void SCH_Update(void) {
    uint8_t Index;

    // Duyệt qua tất cả task
    for (Index = 0; Index < SCH_MAX_TASKS; Index++) {
        // Kiểm tra task có tồn tại không
        if (SCH_tasks_G[Index].pTask) {
            if (SCH_tasks_G[Index].Delay == 0) {
                // Task sẵn sàng chạy
                SCH_tasks_G[Index].RunMe += 1;

                if (SCH_tasks_G[Index].Period) {
                    // Task định kỳ - reset delay
                    SCH_tasks_G[Index].Delay = SCH_tasks_G[Index].Period;
                }
            } else {
                // Chưa đến lúc chạy - giảm delay
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

    // Duyệt qua tất cả task
    for (Index = 0; Index < SCH_MAX_TASKS; Index++) {
        if (SCH_tasks_G[Index].RunMe > 0) {
            // Thực thi task
            (*SCH_tasks_G[Index].pTask)();

            // Giảm cờ RunMe
            SCH_tasks_G[Index].RunMe -= 1;

            // Nếu là one-shot task (Period = 0), xóa khỏi mảng
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

    // Tìm vị trí trống trong mảng
    while ((SCH_tasks_G[Index].pTask != 0) && (Index < SCH_MAX_TASKS)) {
        Index++;
    }

    // Kiểm tra mảng đã đầy chưa
    if (Index == SCH_MAX_TASKS) {
        return 0;  // Mảng đầy
    }

    // Thêm task vào vị trí trống
    SCH_tasks_G[Index].pTask = pFunction;
    SCH_tasks_G[Index].Delay = DELAY;
    SCH_tasks_G[Index].Period = PERIOD;
    SCH_tasks_G[Index].RunMe = 0;
    SCH_tasks_G[Index].TaskID = SCH_taskID_counter++;

    // Trả về TaskID
    return SCH_tasks_G[Index].TaskID;
}

/**
 * Xóa task khỏi scheduler
 */
uint8_t SCH_Delete_Task(uint32_t taskID) {
    uint8_t Index;

    // Tìm task với TaskID tương ứng
    for (Index = 0; Index < SCH_MAX_TASKS; Index++) {
        if (SCH_tasks_G[Index].TaskID == taskID) {
            // Tìm thấy task - xóa nó
            SCH_tasks_G[Index].pTask = 0;
            SCH_tasks_G[Index].Delay = 0;
            SCH_tasks_G[Index].Period = 0;
            SCH_tasks_G[Index].RunMe = 0;
            SCH_tasks_G[Index].TaskID = 0;

            return 0; // Thành công
        }
    }

    return 1; // Không tìm thấy task
}
