#include "OSMemMap.h"

#include "TestTask/task_a.h"
#include "TestTask/task_b.h"

#include <stdlib.h>



#define NUM_TASKS 2

typedef void (*TASK_HANDLE)(void *input_args, void *output_args);

typedef struct task
{
    TASK_HANDLE   RTOSTask;
    void         *RTOSTaskInputArg;
    void         *RTOSTaskOutputArg;
} RTOS_TASK;


// List of all tasks to run in one OS cycle
RTOS_TASK Task_List[NUM_TASKS] = {
    {&TestTask_A, NULL, &(Memory.var1)},
    {&TestTask_B, &(Memory.var1), NULL}
};