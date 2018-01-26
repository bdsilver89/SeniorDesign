#include "TestTask/task_b.h"
#include <iostream>
#include <cstdint>

void TestTask_B(void *input_args, void *output_args)
{
   std::cout << "Task B starting" << std::endl;
   std::cout << "Value: " << *((uint32_t*)input_args) << std::endl;
   std::cout << "Task B ending" << std::endl;
}