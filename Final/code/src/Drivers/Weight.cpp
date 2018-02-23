#include "Drivers/Weight.h"
#include "OS/OSMemMap.h"
#include <iostream>
#include <unistd.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>

#define ENABLE_DEBUG_CONSOLE

#ifdef ENABLE_DEBUG_CONSOLE
	#include <bitset>
#endif

/* NOTE:
 * WiringPiI2C has a fun bug for writing to 16 bit registers
 * that flips the endianness
 * This is a known problem and requires each read and write to be
 * modified. See this post for more info:
 * https://www.raspberrypi.org/forums/viewtopic.php?f=33&t=122923
 */



int32_t sensor;


void Weight_Init(struct RTOS_SHARED_MEM* RTOS_MEM, uint8_t* err)
{
	#ifdef ENABLE_DEBUG_CONSOLE
		std::cout << "Weight init task starting" << std::endl;
	#endif
	struct Weight_MemMap* WeightMem_ptr = &((*RTOS_MEM).WeightDriverMem);

	(*WeightMem_ptr).i2caddr = 0x48;	// Need to connect the ADDR pin to GND
	wiringPiSetupSys();
	sensor = wiringPiI2CSetup((*WeightMem_ptr).i2caddr);
	if (sensor < 0)
	{
		*err = 1;
		return;
	}
	
	/* Setup the ADC for:
	 *     Continous reading of samples
	 *     +- 4.096V FS
	 *     1600 sps
	 *     Traditional comparator mode
	 *     Active low comparator
	 *     Latching and asserting comparator
	 */
	uint16_t config = ADS1015_REG_CONFIG_CQUE_NONE    | // Disable the comparator (default val)
                      ADS1015_REG_CONFIG_CLAT_NONLAT  | // Non-latching (default val)
                      ADS1015_REG_CONFIG_CPOL_ACTVLOW | // Alert/Rdy active low   (default val)
                      ADS1015_REG_CONFIG_CMODE_TRAD   | // Traditional comparator (default val)
                      ADS1015_REG_CONFIG_DR_1600SPS   | // 1600 samples per second (default)
                      ADS1015_REG_CONFIG_MODE_SINGLE  | // Single-shot mode (default)
                      ADS1015_REG_CONFIG_PGA_4_096V	  |	// +-4.096V, Gain = 1
                      ADS1015_REG_CONFIG_MUX_SINGLE_0;	// MUX0 Single-Ended
						
	wiringPiI2CWriteReg16(sensor, ADS1015_REG_POINTER_CONFIG, (((config & 0x00FF) << 8) | ((config & 0xFF00) >> 8)));
	
	
	// Verfiy registers
	#ifdef ENABLE_DEBUG_CONSOLE
		int16_t convert_val  = wiringPiI2CReadReg16(sensor, ADS1015_REG_POINTER_CONVERT); 
		uint16_t config_val   = wiringPiI2CReadReg16(sensor, ADS1015_REG_POINTER_CONFIG);
		int16_t lothresh_val = wiringPiI2CReadReg16(sensor, ADS1015_REG_POINTER_LOWTHRESH);
		int16_t hithresh_val = wiringPiI2CReadReg16(sensor, ADS1015_REG_POINTER_HITHRESH);
		
		convert_val  = ((((convert_val & 0x00FF) << 8)  | ((convert_val & 0xFF00) >> 8)));
		config_val   = ((((config_val & 0x00FF) << 8)   | ((config_val & 0xFF00) >> 8)));
		lothresh_val = ((((lothresh_val & 0x00FF) << 8) | ((lothresh_val & 0xFF00) >> 8)));
		hithresh_val = ((((hithresh_val & 0x00FF) << 8) | ((hithresh_val & 0xFF00) >> 8)));

		
		std::cout << "\tConvert:  " << std::hex << convert_val  << std::endl;
		std::cout << "\tConfig:   " << std::hex << config_val   << std::endl;
		std::cout << "\tLothresh: " << std::hex << lothresh_val << std::endl;
		std::cout << "\tHithresh: " << std::hex << hithresh_val << std::endl;
		
		/*
		std::cout << "\tConvert:  " << std::bitset<16>(convert_val)  << std::endl;
		std::cout << "\tConfig:   " << std::bitset<16>(config_val)   << std::endl;
		std::cout << "\tLothresh: " << std::bitset<16>(lothresh_val) << std::endl;
		std::cout << "\tHithresh: " << std::bitset<16>(hithresh_val) << std::endl;		
		*/
	#endif


	#ifdef ENABLE_DEBUG_CONSOLE
		std::cout << "Weight init task ending\n"  << std::endl;
	#endif
}
	

void Weight_Update(struct RTOS_SHARED_MEM* RTOS_MEM,
											  uint32_t RTOSTime)
{
	
	if (RTOSTime % 10 != 0)
		return;
		
	else
	{
	
		#ifdef ENABLE_DEBUG_CONSOLE
			//std::cout << "Weight update task starting" << std::endl;
		#endif


		//task update code
		struct Weight_MemMap* WeightMem_ptr = &((*RTOS_MEM).WeightDriverMem);
		
		uint16_t config_val = wiringPiI2CReadReg16(sensor, ADS1015_REG_POINTER_CONFIG);
		config_val = ((((config_val & 0x00FF) << 8)   | ((config_val & 0xFF00) >> 8)));
		config_val |= ADS1015_REG_CONFIG_OS_SINGLE;
		wiringPiI2CWriteReg16(sensor, ADS1015_REG_POINTER_CONFIG, (((config_val & 0x00FF) << 8) | ((config_val & 0xFF00) >> 8)));
		
		usleep(1000);
	
		
		int16_t raw = wiringPiI2CReadReg16(sensor, ADS1015_REG_POINTER_CONVERT);
		raw = ((((raw & 0x00FF) << 8)  | ((raw & 0xFF00) >> 8)));
		raw = raw >> 4;

		#ifdef ENABLE_DEBUG_CONSOLE		
			std::cout << "\tADC raw value: " << std::dec << raw << ", " << std::hex << raw << std::endl;
			std::cout << "\tADC voltage: " << 4.096 * double(raw)/2048.0 << std::endl;
		#endif
		

		#ifdef ENABLE_DEBUG_CONSOLE
			//std::cout << "Weight update task ending" << std::endl;
		#endif
	}
}
