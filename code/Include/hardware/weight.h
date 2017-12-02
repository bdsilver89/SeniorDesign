#ifndef WEIGHT_H
#define WEIGHT_H

#include "hardware/i2c.h"

class weight : public I2CDevice
{
public:
    weight();

    int readSensor(void);

    
};

#endif