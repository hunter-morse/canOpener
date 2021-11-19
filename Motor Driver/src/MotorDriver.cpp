/**
 * @file
 * */

#include "MotorDriver.h"

MotorDriver::MotorDriver(uint8_t new_id, uint32_t pos, uint32_t neg, int8_t max_PWM, int8_t min_PWM, uint16_t delay)
{
    id = new_id;
    //FINISH THIS
}

void MotorDriver::move(float new_PWM)
{
    // Need to check direction, and if direction is opposite requested direction, apply braking for specified time
    if (new_PWM > PWM_max)
    {
        PWM = PWM_max;
    }
    else if (new_PWM < PWM_min)
    {
        PWM = PWM_min;
    }
    else
    {
        PWM = new_PWM;
    }
    int16_t motor_val = 0;
    if (PWM > 0)
    {
        motor_val = (int16_t) map(PWM, 0, 100, 0, 255);
        analogWrite(pinA, motor_val);
    }
}