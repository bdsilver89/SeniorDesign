#include "TestTask/task_a.h"
#include <iostream>
#include <cstdint>
#include <stdlib.h>

uint32_t x = 0;

void TestTask_A(void *input_args, void *output_args)
{
   std::cout << "Task A starting" << std::endl;
   *((uint32_t*)output_args) = x;
   x++;
   std::cout << "Task A ending" << std::endl;
}