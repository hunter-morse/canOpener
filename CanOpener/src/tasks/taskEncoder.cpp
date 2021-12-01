/**
 * @file
 * */

#include <Arduino.h>
#include <STM32FreeRTOS.h>
#include <PrintStream.h>
#include "../../lib/sensorLib/encoder_counter.h"
#include "../shares.h"
#include "../pins.h"
#include "taskEncoder.h"

const uint32_t tim4period = 65535;
const uint32_t tim5period = UINT32_MAX;

/**
 * @brief 
 * */
void taskEncoder(void* p_params)
{
    STM32Encoder encoder1(ENC1TIM, ENC1a, ENC1b);
    encoder1.zero();
    int64_t last_pos_1 = 0;
    uint32_t curr_pos_1 = 0;
    int64_t delta_1;

    STM32Encoder encoder2(ENC2TIM, ENC2a, ENC2b);
    encoder2.zero();
    int64_t last_pos_2 = 0;
    uint32_t curr_pos_2 = 0;
    int64_t delta_2;

    TickType_t xLastWakeTime = xTaskGetTickCount();

    for (;;)
    {
        curr_pos_1 = encoder1.getCount();
        delta_1 = -1 * last_pos_1 + curr_pos_1;
        delta_1 = fixDelta(delta_1, tim4period);
        last_pos_1 += delta_1;
        enc1.put(last_pos_1);

        curr_pos_2 = encoder2.getCount();
        delta_2 = -1 * last_pos_2 + curr_pos_2;
        delta_2 = fixDelta(delta_2, tim5period);
        last_pos_2 += delta_2;
        enc2.put(last_pos_2);

        vTaskDelayUntil (&xLastWakeTime, 10);
    }
}

int64_t fixDelta(int64_t delta, uint32_t period)
{
    
    if (delta > period/2 || -1*delta > period/2)
    {
        if (delta > 0)
        {
            return delta - period - 1;
        }
        else
        {
            return delta + period + 1;
        }
    }
    else
    {
        return delta;
    }
}