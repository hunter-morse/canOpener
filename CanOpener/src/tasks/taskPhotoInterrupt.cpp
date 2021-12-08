/**
 * @file    taskPhotoInterrupt.cpp
 *          Task to check the status of the photo interrupt sensor
 *          Lit vs ambient IR light data is compared to determine
 *          if a reflective object is present in front of the sensor. 
 *          Results are put to the canDetected share.
 * @author  Kyle Van Housen
 * 
 * @date    Nov xx, 2021
 */

#include <Arduino.h>
#include <PrintStream.h>
#if (defined STM32L4xx || defined STM32F4xx)
    #include <STM32FreeRTOS.h>
#endif
#include "taskPhotoInterrupt.h"
#include "../pins.h"
#include "../shares.h"

/**
 * @brief   Task: Check Photo Interrupt
 * @details Period: 500ms, Priority: 4/4
 *          Check whether or not a reflective object (can) is present
 *          on the platform
 * @param   p_param: task parameters
 */ 

void taskPhotoInterrupt(void* p_params){

    (void) p_params;

    pinMode(IN_REFL, INPUT);
    pinMode(OUT_REFL, OUTPUT);

    Serial.println("Task Photo Begun");

    for (;;){

        uint32_t ambient = 0;
        uint32_t lit = 0;
        int32_t value = 0;
  
        digitalWrite(OUT_REFL, LOW);
        vTaskDelay(5);                            
        ambient = analogRead(IN_REFL);
  
        digitalWrite(OUT_REFL, HIGH);
        vTaskDelay(5);
        lit = analogRead(IN_REFL);
  
        value = lit - ambient;

        canDetected.put(value < -50);
  
        //Serial << "Value: " << value  << endl;
        //Serial << "Ambient: " << ambient << endl << endl;
        //Serial << canDetected.get() << endl;
        vTaskDelay(500);

    }

}