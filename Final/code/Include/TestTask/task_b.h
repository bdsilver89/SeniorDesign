#ifndef TASK_B_H
#define TASK_B_H

#include <cstdint>

struct TaskB_MemMap
{
    uint32_t var1 = 0;
};

void TestTask_B(struct RTOS_SHARED_MEM* RTOS_MEM,
                uint32_t RTOSTime);

#endif