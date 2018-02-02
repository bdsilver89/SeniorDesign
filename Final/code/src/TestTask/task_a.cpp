#include "TestTask/task_a.h"
#include "OS/OSMemMap.h"
#include <iostream>


void TestTask_A(struct RTOS_SHARED_MEM* RTOS_MEM,
                uint32_t RTOSTime)
{
    if (RTOSTime % 10 != 0)
        return;
    
    else
    {
        std::cout << "Task A starting" << std::endl;
        struct TaskA_MemMap* tempMemA = &((*RTOS_MEM).A_Mem);
        (*tempMemA).var1 = 12;
        // std::cout << ((*RTOS_MEM).A_Mem).var1 << std::endl;
        std::cout << "Task A ending\n" << std::endl;
    }
}