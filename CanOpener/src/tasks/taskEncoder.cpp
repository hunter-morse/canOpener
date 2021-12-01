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

void taskEncoder(void* p_params)
{
    STM32Encoder encoder1(ENC1TIM, ENC1a, ENC1b);
    encoder1.zero();
    uint32_t last_pos_1 = 0;
    uint32_t curr_pos_1 = 0
    int64_t delta_1;

    for (;;)
    {
        curr_pos_1 = encoder1.getCount();
        delta_1 = curr_pos_1 - last_pos_1;
    }
}