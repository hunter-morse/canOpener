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
        MotorDriver(uint8_t new_id, uint32_t pos, uint32_t neg, uint32_t enable, uint8_t PWM_bound, 
                    uint16_t b_delay = 0);

        void move(float new_PWM);

        void brake(void);

        float getPWM(void);

        uint8_t getID(void);

        int8_t getDirection(void);


    protected:
        uint8_t id;
        float PWM;
        int8_t PWM_max;
        int8_t PWM_min;
        uint32_t pinA;
        uint32_t pinB;
        uint32_t pinEN;
        uint16_t brake_delay;
        int8_t direction;
};

#endif