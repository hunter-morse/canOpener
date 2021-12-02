#include <Arduino.h>
#include <PrintStream.h>
#if (defined STM32L4xx || defined STM32F4xx)
    #include <STM32FreeRTOS.h>
#endif
#include "PhotoInterruptTask.h"

const uint8_t IR_INPUT_PIN = A1;
const uint8_t IR_LED_PIN  = D7;

void photoInterruptTask(void* p_params){

    (void) p_params;

    pinMode(IR_INPUT_PIN, INPUT);
    pinMode(IR_LED_PIN, OUTPUT);

    for (;;){

        int ambient = 0;
        int lit = 0;
        int value = 0;
  
        digitalWrite(IR_LED_PIN, LOW);
        delay(5);                            
        ambient = analogRead(IR_INPUT_PIN);
  
        digitalWrite(IR_LED_PIN, HIGH);
        delay(5);
        lit = analogRead(IR_INPUT_PIN);
  
        value = lit - ambient;
  
        Serial.println(value);
        vTaskDelay(2000);

    }

}