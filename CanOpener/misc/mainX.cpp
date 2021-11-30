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
    int DC1a    = PB4;
    int DC1b    = PB5;
    int DCEN1   = PA13;

    int DC2a    = PA10;
    int DC2b    = PA11;
    int DCEN2   = PA14;

    int DC3a    = PA5;
    int DC3b    = PB3;
    int DCEN3   = PC13;

    int DC4a    = PB10;
    int DC4b    = PB11;
    int DCEN4   = PC14;

    int STEP1a  = PB4;
    int STEP1b  = PB5;
    int STEP1c  = PB0;
    int STEP1d  = PB1;
    int STEPEN1 = PC15;

    pinMode(DC1a, OUTPUT);
    pinMode(DC1b, OUTPUT);
    pinMode(DCEN1, OUTPUT);

    pinMode(DC2a, OUTPUT);
    pinMode(DC2b, OUTPUT);
    pinMode(DCEN2, OUTPUT);
    
    pinMode(DC3a, OUTPUT);
    pinMode(DC3b, OUTPUT);
    pinMode(DCEN3, OUTPUT);

    pinMode(DC4a, OUTPUT);
    pinMode(DC4b, OUTPUT);
    pinMode(DCEN4, OUTPUT);

    pinMode(STEP1a, OUTPUT);
    pinMode(STEP1b, OUTPUT);
    pinMode(STEP1c, OUTPUT);
    pinMode(STEP1d, OUTPUT);
    pinMode(STEPEN1, OUTPUT);

    digitalWrite(DC1a, HIGH);
    digitalWrite(DC1b, LOW);
    digitalWrite(DCEN1, HIGH);

    digitalWrite(DC2a, HIGH);
    digitalWrite(DC2b, LOW);
    digitalWrite(DCEN2, HIGH);

    digitalWrite(DC3a, HIGH);
    digitalWrite(DC3b, LOW);
    digitalWrite(DCEN3, HIGH);

    digitalWrite(DC4a, HIGH);
    digitalWrite(DC4b, LOW);
    digitalWrite(DCEN4, HIGH);

    digitalWrite(STEP1a, HIGH);
    digitalWrite(STEP1b, LOW);
    digitalWrite(STEP1c, HIGH);
    digitalWrite(STEP1d, LOW);
    digitalWrite(STEPEN1, HIGH);


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

