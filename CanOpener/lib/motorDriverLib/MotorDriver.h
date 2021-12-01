/**
 * @file MotorDriver.h
 * @brief Header file which contains the MotorDriver Class
 * 
 * @author Ben Bons
 * @date Nov 29, 2021
 * */

#ifndef MotorDriver_h
#define MotorDriver_h

#include <Arduino.h>
#include <math.h>


/**
 * @brief A class which controls a servo motor
 * @details This class allows for PWM control of a servo motor. The motor must be a simple 2-wire servo motor.
 *          The class includes protections against quick reversal of the motor with a (blocking) brake delay.
 *          The class will also allow for a maximum PWM to be used.
 * */
class MotorDriver
{
    public:
        //Note: delay is the time in ms for the motor to wait from switching directions to prevent negative loading on the motor driver
        MotorDriver(uint8_t new_id, uint8_t pos, uint8_t neg, uint8_t enable, uint8_t PWM_bound, 
                    uint16_t b_delay = 0);

        void move(float new_PWM);

        void brake(void);

        float getPWM(void);

        uint8_t getID(void);

        int8_t getDirection(void);


    protected:
        uint8_t id;
        float   PWM;
        int8_t  PWM_max;
        int8_t  PWM_min;
        uint8_t pinA;
        uint8_t pinB;
        uint8_t pinEN;
        uint16_t brake_delay;
        int8_t  direction;
};

#endif