/** @file encoder_test.cpp
 *    This file contains code to test a class for using encoders on STM32's in
 *    the Arduino environment.
 * 
 *    References:
 *    @c https://www.edwinfairchild.com/2019/04/interface-rotary-encoder-right-way.html
 *
 *  @author JR Ridgely
 *  @date   2020-Nov-15 Original file, based on stuff from the Interwebs
 */

#include <Arduino.h>
#include <PrintStream.h>
#include <STM32FreeRTOS.h>

// #include "encoder3.h"
#include "encoder_counter.h"


/** @brief   Task which tests the reading of encoders using the @c STM32Encoder
 *           class.
 *  @param   p_params A pointer, which is ignored, to no parameters
 */
void task_read_encoders (void* p_params)
{
    // Pointers to timer/counters used; could be in a task function
    Serial << "Initializing timers...";
    STM32Encoder timer_X (TIM2, PA0, PA1);
    // STM32Encoder timer_Y (TIM8, PC6, PC7);
    Serial << "done." << endl;

    for (;;)
    {
        delay (100);

        Serial << "Timer X: " << (int16_t)(timer_X.getCount ()) 
        << "      \r";
         //   << ", Timer Y: " << (int16_t)(timer_Y.getCount ())
    }
}


/** @brief   The usual Arduino setup function which runs once as we start up.
 */
void setup (void) 
{
    Serial.begin (115200);
    delay (1000);
    
    // Set pins to communicate with motor
    int DC2a    = PA10;
    int DC2b    = PA11;
    int DCEN2   = PA14;
    
    pinMode(DC2a, OUTPUT);
    pinMode(DC2b, OUTPUT);
    pinMode(DCEN2, OUTPUT);

    digitalWrite(DC2a, HIGH);
    digitalWrite(DC2b, LOW);
    digitalWrite(DCEN2, HIGH);

    Serial << "\033[2JTimer/Counter Test in Encoder Mode" << endl;

    // Create the task that tests the encoder interface class
    xTaskCreate (task_read_encoders,     // Task function
                 "Encoders",             // Name in diagnostic printouts
                 1000,                   // Stack size in bytes
                 NULL,                   // Parameters for task function
                 5,                      // Task priority
                 NULL);                  // Handle to task struct

    // STM32duino requires that the FreeRTOS scheduler be manually started
    vTaskStartScheduler ();

    
}


/** @brief   The Arduino loop function, which is unused in this program.
 */
void loop (void)
{
}

