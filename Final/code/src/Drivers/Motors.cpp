#include "Drivers/Motors.h"
#include "OS/OSMemMap.h"
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>

int32_t file_i2c;
int32_t length;
uint8_t	buffer[32] = {0};

void Motor_Init(struct RTOS_SHARED_MEM* RTOS_MEM,
											  uint32_t RTOSTime)
{
	struct Motors_MemMap* MotorMem_ptr = &((*RTOS_MEM).MotorDriverMem);
	uint8_t *filename = (uint8_t*)"/dev/i2c-1";
	/* if ((file_i2c = open(filename, O_RDWR)) < 0)
	{
		// Error handling
		std::cout << "ERROR: Failed to initialize motor I2C bus" << std::endl;	
		return;
	} */

	file_i2c = open(filename, O_RDWR);	
	
	(*MotorMem_ptr).i2caddr = 0x40;
	if (ioctl(file_i2c, I2C_SLAVE, (*MotorMem_ptr).i2caddr) < 0)
	{
		// Error handling
		std::cout << "ERROR: Failed to acquire Motor I2C bus and/or talk to slave" << std::endl;
		return;
	}

}


void Motor_Update(struct RTOS_SHARED_MEM* RTOS_MEM,
											  uint32_t RTOSTime)
{
	if (RTOSTime % 10 != 0)
		return;
		
	else
	{
		std::cout << "Motor update task starting" << std::endl;
		struct Motors_MemMap* MotorMem_ptr = &((*RTOS_MEM).MotorDriverMem);
		struct Controller_MemMap* ControllerMem_ptr = &((*RTOS_MEM).ControllerMem);
		
		// Motor speed represented by 0 = 1.5ms, 127=1.7ms, -128=1.3ms
		// float control_val = (float)((*ControllerMem_ptr).Motor0_Speed);
		// (*MotorMem_ptr).high_pulse = 1.3f + (control_val +128.0f) * (0.0015625f); 
		
		
		
		std::cout << "Motor 0 high pulse= " << (*MotorMem_ptr).high_pulse << std::endl;
			
		std::cout << "Motor update task ending\n"  << std::endl;
	}
}