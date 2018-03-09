#include "Drivers/Weight.h"
#include "OS/OSMemMap.h"
#include <iostream>
#include <unistd.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>

// #define ENABLE_DEBUG_CONSOLE

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

	(*WeightMem_ptr).i2caddr    = 0x48;	// Need to connect the ADDR pin to GND
	(*WeightMem_ptr).ADC_scale  = 975.0/2560.0;	// datasheet gain / amp gain
	(*WeightMem_ptr).ADC_offset = 0;	// Need to update in calibrate routine

	wiringPiSetupSys();
	sensor = wiringPiI2CSetup((*WeightMem_ptr).i2caddr);
	if (sensor < 0)
	{
		*err = 1;
		return;
	}
	
	/* Setup the ADC for:
	 *     Continous reading of samples
	 *     +- 2.048V FS
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
                      ADS1015_REG_CONFIG_PGA_2_048V	  |	// +-2.048V, Gain = 2
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
	#endif


	#ifdef ENABLE_DEBUG_CONSOLE
		std::cout << "Weight init task ending\n"  << std::endl;
	#endif
}

	

void Weight_Update(struct RTOS_SHARED_MEM* RTOS_MEM,
											  uint32_t RTOSTime)
{
	/*
	if (RTOSTime % 10 != 0)
		return;
		
	else
	{*/
		#ifdef ENABLE_DEBUG_CONSOLE
			//std::cout << "Weight update task starting" << std::endl;
		#endif

		//task update code
		struct Weight_MemMap* WeightMem_ptr = &((*RTOS_MEM).WeightDriverMem);
		
		uint16_t config_val = wiringPiI2CReadReg16(sensor, ADS1015_REG_POINTER_CONFIG);
		config_val = ((((config_val & 0x00FF) << 8)   | ((config_val & 0xFF00) >> 8)));
		config_val |= ADS1015_REG_CONFIG_OS_SINGLE;
		wiringPiI2CWriteReg16(sensor, ADS1015_REG_POINTER_CONFIG, (((config_val & 0x00FF) << 8) | ((config_val & 0xFF00) >> 8)));
		
		// TODO: Test without this
		usleep(1000);
		
		int16_t raw = wiringPiI2CReadReg16(sensor, ADS1015_REG_POINTER_CONVERT);
		raw = ((((raw & 0x00FF) << 8)  | ((raw & 0xFF00) >> 8)));
		(*WeightMem_ptr).raw_ADC = raw >> 4;
		(*WeightMem_ptr).voltage_ADC = 2.048 * double((*WeightMem_ptr).raw_ADC)/2048.0;

		// TODO: Add a scale and offset calibration routine
		(*WeightMem_ptr).weight = 1000 * (((*WeightMem_ptr).ADC_scale) * ((*WeightMem_ptr).voltage_ADC) + (*WeightMem_ptr).ADC_offset);
		#ifdef ENABLE_DEBUG_CONSOLE		
			std::cout << "\tADC raw value: " << std::dec << (*WeightMem_ptr).raw_ADC;
			std::cout << ", " << std::hex    << (*WeightMem_ptr).raw_ADC << std::endl;
			std::cout << "\tADC voltage: "   << (*WeightMem_ptr).voltage_ADC << std::endl;
			std::cout << "\tADC weight: "    << (*WeightMem_ptr).weight << " grams" << std::endl;
		#endif
		
		#ifdef ENABLE_DEBUG_CONSOLE
			//std::cout << "Weight update task ending" << std::endl;
		#endif
	// }
}
