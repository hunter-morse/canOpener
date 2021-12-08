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
        /// The id of the MotorDriver object
        uint8_t id;
        /// The current PWM value
        float   PWM;
        /// The maximum PWM allowed
        int8_t  PWM_max;
        /// The minimum PWM allowed
        int8_t  PWM_min;
        /// The positive pin connected to the motor
        uint8_t pinA;
        /// The negative pin connected to the motor
        uint8_t pinB;
        /// The enable pin
        uint8_t pinEN;
        /// The time that the motor will brake when switching directions
        uint16_t brake_delay;
        /// The current direction of the motor: 1 = forward, 0 = stopped, -1 = reverse
        int8_t  direction;
};

#endif