#ifndef MOTOR_H
#define MOTOR_H

#include <cstdint>
// #include "hardware/i2c.h"

#define DEVICE_ADDR 0x40

class PWMMotor
{
private:
	void write8(uint8_t addr, uint8_t d);
	
public:
    PWMMotor(void);

    void begin (void);

    void reset (void);

    // Included in Adafruit API, not sure if we need a function for this
    void setPWMFreq(float freq);

    void setPWM(uint8_t num, uint16_t on, uint16_t off);

    void setPin(uint16_t num, uint16_t val, bool invert);
    
};

#endif