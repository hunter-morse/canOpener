#include <Arduino.h>
#include <PrintStream.h>
#if (defined STM32L4xx || defined STM32F4xx)
    #include <STM32FreeRTOS.h>
#endif
#include "taskPhotoInterrupt.h"
#include "../pins.h"
#include "../shares.h"

//const uint8_t IR_INPUT_PIN = A1;
//const uint8_t IR_LED_PIN  = D7;

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