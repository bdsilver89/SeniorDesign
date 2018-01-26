#include "TestTask/task_a.h"
#include "TestTask/task_b.h"

#define NUM_TASKS 2

void (*task_ptr[])(void) = {
    TestTask_A,
    TestTask_B
};