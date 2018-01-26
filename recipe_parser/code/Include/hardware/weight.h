#ifndef WEIGHT_H
#define WEIGHT_H

#include <cstdint>
// #include "hardware/i2c.h"

class weight
{
public:
    weight(uint8_t addr);

    int readSensor(void);
    
};

#endif