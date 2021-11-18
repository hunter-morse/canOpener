/**
 * @file
 * */

#ifndef Stepper_Driver_h
#define Stepper_Driver_h

#include <Arduino.h>
#include <Stepper.h>

class StepperDriver
{
    public:
        StepperDriver(uint8_t new_id, uint8_t stepsPerRev, uint32_t pin1, uint32_t pin2, 
                    uint32_t pin3, uint32_t pin4, uint32_t enable, uint8_t new_speed);

        void move(int16_t steps);

        int32_t getPosition(void);

        void setPosition(int32_t new_pos);

        void setSpeed(uint16_t new_speed);

        uint16_t getSpeed(void);

        uint8_t getID(void);

    protected:
        int32_t curr_pos;

        uint8_t id;

        uint32_t pin_A;

        uint32_t pin_Abar;

        uint32_t pin_B;

        uint32_t pin_Bbar;

        uint32_t pin_enable;

        uint16_t speed;

        Stepper* p_Stepper; 

};

#endif