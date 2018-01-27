#include "OSMemMap.h"

#include <stdlib.h>
#include <cstdint>

#define NUM_INIT	2 
#define NUM_TASKS	2

struct RTOS_SHARED_MEM MemMap;

typedef void (*UPDATE_TASK_HANDLE)(struct RTOS_SHARED_MEM* RTOS_MEM,
                            uint32_t RTOSTime);

typedef struct task
{
    UPDATE_TASK_HANDLE            RTOSTask;
    struct RTOS_SHARED_MEM   *MEM;
} RTOS_TASK;


typedef void (*INIT_TASK_HANDLE)(struct RTOS_SHARED_MEM* RTOS_MEM, uint8_t* err);

typedef struct init
{
    INIT_TASK_HANDLE            RTOSInitTask;
    struct RTOS_SHARED_MEM   *MEM;
} RTOS_INIT_TASK;



//List of all Initialization tasks to run BEFORE the OS cycle starts
RTOS_INIT_TASK Init_List[NUM_INIT] = {
    {&Controller_Init, 		&(MemMap)},
    {&Motor_Init, 			&(MemMap)}
};


// List of all tasks to run in one OS cycle
RTOS_TASK Task_List[NUM_TASKS] = {
//    {&TestTask_A, 					&(MemMap)},
//    {&TestTask_B, 					&(MemMap)},
    {&Controller_Update,	&(MemMap)},
    {&Motor_Update, 			&(MemMap)}
};
