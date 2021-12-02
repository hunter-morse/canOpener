#include <Arduino.h>
#include <PrintStream.h>
#if (defined STM32L4xx || defined STM32F4xx)
    #include <STM32FreeRTOS.h>
#endif
#include "PhotoInterruptTask.h"

void setup() {
  // put your setup code here, to run once:
Serial.begin(115200); 
delay (2000);
Serial.println("HEllo:");

xTaskCreate(photoInterruptTask,"PhotoInterrupt", 2048,NULL,1,NULL);
#if (defined STM32L4xx || defined STM32F4xx)
        vTaskStartScheduler ();
#endif
}

void loop() {

}