#include "TestTask/task_b.h"
#include <iostream>

void TestTask_B(struct RTOS_SHARED_MEM* RTOS_MEM,
                uint32_t RTOSTime)
{
    if (RTOSTime % 10 != 0)
        return;

    else
    {
        std::cout << "Task B starting" << std::endl;
        std::cout << "Task B ending\n" << std::endl;
    }
}