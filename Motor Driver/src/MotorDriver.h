/**
 * @file
 * */

#ifndef MotorDriver_h
#define MotorDriver_h

#include <Arduino.h>
#include <math.h>

class MotorDriver
{
    public:
        //Note: delay is the time in ms for the motor to wait from switching directions to prevent negative loading on the motor driver
        MotorDriver(uint8_t new_id, uint32_t pos, uint32_t neg, int8_t max_PWM, int8_t min_PWM, uint16_t delay);

        void move(float new_PWM);

        void brake(void);


    protected:
        uint8_t id;
        float PWM;
        int8_t PWM_max;
        int8_t PWM_min;
};

#endif