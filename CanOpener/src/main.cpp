/**
 * @file    main.cpp
 *          Main file for the ME 507 CanOpener robot
 *          Developed on a Nucleo L476RG Development Board using FreeRTOS
 * @authors Hunter Morse, Ben Bons, Kyle Van Housen
 * @date    Fall 2021
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
#include "tasks/taskPhotoInterrupt.h"
/// Share that holds the current temperature
Share<float> currentTemp("Current Temperature");
/// Share that tells whether a can is in the machine
Share<bool> canDetected("Can Detected");
/// Share that tells if the can top limit switch is depressed
Share<bool> canTopDetected("Can Top Detected");
/// Share that tells if the can tab has been detected
Share<bool> canTabDetected("Can Tab Detected");
/// Share that holds the current encoder 1 value
Share<int64_t> enc1("Encoder 1");
/// Share that holds the current encoder 2 value
Share<int64_t> enc2("Encoder 2");
/// Share that tells if the kill switch is depressed
Share<bool> kill("Kill Switch");
/// @cond
void setup(){
    Serial.begin(115200);
    delay(5000);
    Serial << "Begun" << endl;
    xTaskCreate(taskCheckLimitSwitches, 
                "Limit Switches",
                2048,
                NULL,
                4,
                NULL);
    
    xTaskCreate(taskMoveMachine,
                "Move Machine",
                8192,
                NULL,
                3,
                NULL);
    
    xTaskCreate(taskPhotoInterrupt,
                "Photo Interrupt",
                1024,
                NULL,
                4,
                NULL);
    /*xTaskCreate(taskTemp,
                "Temperatures",
                1024,
                NULL,
                2,
                NULL);*/
    /*xTaskCreate(taskWriteToDisplay,
                "Display",
                2048,
                NULL,
                1,
                NULL);
    xTaskCreate(taskEncoder,
                "Display",
                2048,
                NULL,
                1,
                NULL);*/
    
    vTaskStartScheduler();
}

void loop(){
    //Will not be used bc of FreeRTOS
}
/// @endcond