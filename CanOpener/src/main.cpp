/**
 * @file main.cpp
 * 
 */
#include <Arduino.h>
#include <STM32FreeRTOS.h>
#include <PrintStream.h>
#include "shares.h"
#include "tasks/taskLimitSwitch.h"
#include "tasks/taskMoveMachine.h"
#include "tasks/taskTemp.h"
#include "tasks/taskWriteToDisplay.h"
#include "tasks/taskEncoder.h"

Share<float> currentTemp("Current Temperature");
Share<bool> canDetected("Can Detected");
Share<bool> canTopDetected("Can Top");
Share<bool> canTabDetected("Can Tab");
Share<int32_t> enc1("Encoder 1");

void setup(){
    xTaskCreate(taskCheckLimitSwitches, 
                "Limit Switches",
                2048,
                NULL,
                4,
                NULL);
    xTaskCreate(taskMoveMachine,
                "Move Machine",
                2048,
                NULL,
                3,
                NULL);
    xTaskCreate(taskTemp,
                "Temperatures",
                1024,
                NULL,
                2,
                NULL);
    xTaskCreate(taskWriteToDisplay,
                "Display",
                2048,
                NULL,
                1,
                NULL);
    vTaskStartScheduler();
}

void loop(){
    //Will not be used bc of FreeRTOS
}
