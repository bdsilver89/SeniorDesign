#include "OSMemMap.h"

#include <stdlib.h>
#include <cstdint>

#define NUM_INIT			1 
#define NUM_TASKS	4

struct RTOS_SHARED_MEM MemMap;

typedef void (*TASK_HANDLE)(struct RTOS_SHARED_MEM* RTOS_MEM,
                            uint32_t RTOSTime);

typedef struct task
{
    TASK_HANDLE            RTOSTask;
    struct RTOS_SHARED_MEM   *MEM;
} RTOS_TASK;

//List of all Initialization tasks to run BEFORE the OS cycle starts
RTOS_TASK Init_List[NUM_INIT] = {
    {&Motor_Init, 			&(MemMap)}
};


// List of all tasks to run in one OS cycle
RTOS_TASK Task_List[NUM_TASKS] = {
    {&TestTask_A, 					&(MemMap)},
    {&TestTask_B, 					&(MemMap)},
    {&Controller_Update,	&(MemMap)},
    {&Motor_Update, 			&(MemMap)}
};