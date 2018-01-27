#ifndef TASK_A_H
#define TASK_A_H

#include <cstdint>

struct TaskA_MemMap
{
    uint32_t var1 = 0;
};


void TestTask_A(struct RTOS_SHARED_MEM* RTOS_MEM,
                uint32_t RTOSTime);

#endif