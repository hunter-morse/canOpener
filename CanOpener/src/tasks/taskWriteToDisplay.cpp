/**
 * @file taskWriteToDisplay.cpp
 * @brief Header file for taskWriteToDisplay
 * 
 * @author Ben Bons
 * @date Nov 27, 2021
 * */

#include "STM32FreeRTOS.h"
#include <Arduino.h>
#include "PrintStream.h"
#include "shares.h"
#include "taskWriteToDisplay.h"

void taskWriteToDisplay(void* p_params)
{
    Serial.begin(115200);

    // See here for why this was included (Essentially increases timing accuracy)
    //https://canvas.calpoly.edu/courses/57860/files/5478349?wrap=1
    TickType_t xLastWakeTime = xTaskGetTickCount();

    for (;;)
    {
        Serial << "Can Temperature: " << currentTemp.get() << " C" << endl;

        //From the same Canvas site as above.
        vTaskDelayUntil (&xLastWakeTime, 1000);
    }
}