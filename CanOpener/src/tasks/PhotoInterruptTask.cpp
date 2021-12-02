#include <Arduino.h>
#include <PrintStream.h>
#if (defined STM32L4xx || defined STM32F4xx)
    #include <STM32FreeRTOS.h>
#endif
#include "PhotoInterruptTask.h"
#include "../../CanOpener/src/pins.h"

//const uint8_t IR_INPUT_PIN = A1;
//const uint8_t IR_LED_PIN  = D7;

void photoInterruptTask(void* p_params){

    (void) p_params;

    pinMode(IN_REFL, INPUT);
    pinMode(OUT_REFL, OUTPUT);

    for (;;){

        int ambient = 0;
        int lit = 0;
        int value = 0;
  
        digitalWrite(OUT_REFL, LOW);
        delay(5);                            
        ambient = analogRead(IN_REFL);
  
        digitalWrite(OUT_REFL, HIGH);
        delay(5);
        lit = analogRead(IN_REFL);
  
        value = lit - ambient;
  
        Serial.println(value);
        vTaskDelay(2000);

    }

}