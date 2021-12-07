/**
 * @file taskTemp.cpp
 * @brief Task for recording temperature from the MCP9808 temperature sensor.
 * @details This task will record the current temperature of the can every 0.5 seconds. 
 *          The task is build to work with the FreeRTOS system.
 * 
 * @author Ben Bons
 * @date Nov 27, 2021
 * */

#include <Arduino.h>
#include <Wire.h>
#include "STM32FreeRTOS.h"
#include "PrintStream.h"
#include "taskshare.h"
#include "../lib/sensorLib/TempSensor.h"
#include "shares.h"
#include "taskTemp.h"

// Share<float> currentTemp("Current Temperature");


/**
 * @brief Task that periodically reads the temperature of the can and puts it into a variable to be read elsewhere
 * @details This task will read a temperature off of the MCP9808 sensor. The task puts this temperature into a Share<float> object
 *          that can be read by the printout task later on. It uses vTaskDelayUntil for high accuracy with the timing, so that this
 *          occurs every 0.5 seconds
 * 
 * @param p_params An unused parameter where other parameters could be passed in, but they aren't as that is outside the scope of this course
 * */
void taskTemp(void* p_params)
{
    uint8_t scl_pin = PB8;
    uint8_t sda_pin = PB9;

    uint8_t addr = 0b0011000;

    // See here for why this was included (Essentially increases timing accuracy)
    //https://canvas.calpoly.edu/courses/57860/files/5478349?wrap=1
    TickType_t xLastWakeTime = xTaskGetTickCount();
    Serial << "Task Temp begun" << endl;
    TempSensor sensor(scl_pin, sda_pin, addr);
    for (;;)
    {
        currentTemp.put(sensor.getManuCode());
        Serial << "Temperature: " << currentTemp.get() << endl;
        //From the same Canvas site as above.
        vTaskDelayUntil (&xLastWakeTime, 500);
    }
}