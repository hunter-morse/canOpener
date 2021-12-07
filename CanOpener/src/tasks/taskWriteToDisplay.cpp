/**
 * @file    taskWriteToDisplay.cpp
 *          Task to write the temperature of the can to a display
 *          Temperature data is recieved from the temperature share
 * 
 * @author Ben Bons
 * @date Nov 27, 2021
 * */

#include "STM32FreeRTOS.h"
#include <Arduino.h>
#include "PrintStream.h"
#include "shares.h"
#include "taskWriteToDisplay.h"

/**
 * @brief   Task: Write to Display
 * @details Period: 1000ms, Priority: 1
 *          Write can temperature data to display
 * @param   p_params: task parameters
 */ 

void taskWriteToDisplay(void* p_params)
{
    //Serial.begin(115200);

    // See here for why this was included (Essentially increases timing accuracy)
    //https://canvas.calpoly.edu/courses/57860/files/5478349?wrap=1
    TickType_t xLastWakeTime = xTaskGetTickCount();
    Serial << "Task Write to Display begun" << endl;
    for (;;)
    {
        Serial << "Can Temperature: " << currentTemp.get() << " C" << endl;

        //From the same Canvas site as above.
        vTaskDelayUntil (&xLastWakeTime, 1000);
    }
}