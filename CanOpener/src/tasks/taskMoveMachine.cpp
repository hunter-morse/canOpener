/**
 * @file    taskMoveMachine.cpp
 *          Task to control the two DC and one servo motor on the canopener
 *          Each state in the task is controlled by the limit switches in 
 *          taskLimitSwitches.cpp
 * @author  Hunter Morse
 * @date    Nov 30, 2021
 */

#include "taskMoveMachine.h"
#include <math.h>

/**
 * @brief   Task: Move Machine
 * @details Period: 10ms, Priority: 3/4
 *          Task dictates the movement of the machine through 8 distinct states. 
 *          State   0: Check if can detected in machine
 *                  1: Move head down until touching top of can
 *                  2: Back of slightly from the top of the can
 *                  3: Rotate base to find the tab
 *                  4: Open the can
 *                  5: Move head up for easy removal of the can
 *                  6: Move the opening motor back to position
 *                  7: Move the base back to position
 * @param   p_params: task parameters
 */                 

void taskMoveMachine(void *p_params){
    // Setup task vars
    uint8_t state = 0;          // State of task specifies which switches are checked
    
    // Instantiate motor drivers
    uint8_t pwm = 100;
    uint8_t stepsPerRev = 200;
    uint8_t stepSpeed = 0;

    MotorDriver dcMotorBase(0, DC1a, DC1b, DCEN1, pwm);     // base motor
    MotorDriver dcMotorHead(1, DC2a, DC2b, DCEN2, pwm);     // head motor
    StepperDriver stepMotor(0, stepsPerRev, STEP1a, STEP1b, STEP1c, STEP1d, STEP1EN, stepSpeed);    // stepper motor

    int16_t down_step = 4; //Amount of steps to move down each cycle
    int16_t up_step = -1*down_step; //Amount of steps to move up each cycle
    float motor_PWM = 15; //PWM for the base motor to rotate at.

    uint8_t canOpenCount = 0;
    uint8_t canOpenTicks = 50;

    uint8_t baseTicks = 0;

    // Included to increase timing accuracy (https://canvas.calpoly.edu/courses/57860/files/5478349?wrap=1)
    TickType_t xLastWakeTime = xTaskGetTickCount();
    //Serial.begin(115200);
    Serial << "Task Move Machine begun" << endl;
    for(;;){
        if (kill.get())
        {
            state = 0;
        }
        // Always check canDetect
        if(state == 0){ //No can in machine state
            if(canDetected.get()){
                // if can detected then move to next state
                Serial.println("taskMoveMachine-state0: Can detected");     // should be written to display
                vTaskDelay(2000);
                state = 1;
            }
            else
            {
                dcMotorBase.move(0);
            }
        } else if(state == 1){//Moving down to find the can state
            // always make sure the can is detected
            if(!canDetected.get()){
                // if no can detected then go back to state 0
                Serial.println("taskMoveMachine-state1: Can not detected");
                state = 0;
            } else if(canTopDetected.get()){
                // if can top detected stop moving the head, pring message, and change state
                Serial.println("taskMoveMachine-state1: Can top detected");
                state = 2;
                stepMotor.setPosition(0);
            } else {
                // if can top not detected then move the head down and remain in current state
                stepMotor.setSpeed(75);
                stepMotor.move(down_step);
                Serial.println("taskMoveMachine-state1: Moving Down");
                // do nothing, stay in state 1
            }
        } else if (state == 2){
            if(!canDetected.get()){
                // if no can detected then go back to state 0
                Serial.println("taskMoveMachine-state1: Can not detected");
                state = 0;
            }
            else
            {
                if(!canTopDetected.get())
                {
                    // Found the top of the can, move to state 3
                    state = 3;
                    Serial.println("taskMoveMachine-state2: Moved up enough");
                }
                else
                {
                    stepMotor.move(up_step); // Move a few steps until the can top is no longer detected
                    Serial.println("taskMoveMachine-state2: Moving up");
                }
            }
        
        } else if (state == 3){
            // state 3 finds the tab
            // always make sure the can is detected
            if(!canDetected.get()){
                // if no can detected then go back to state 0
                Serial.println("taskMoveMachine-state3: Can not detected");
                state = 0;
                dcMotorBase.move(0);
            } 
            // make sure can and top are detected
            else if (canDetected.get()){
                // check to see if tab has been found
                if (canTopDetected.get()){ //Changed from CanTabDetected b/c only one limit switch is planned to be used
                    // do not change state -- only change state if either the can/its top aren't detected
                    dcMotorBase.brake();        // stop rotating the base
                    Serial.println("taskMoveMachine-state3: Can tab found!");
                    state = 4;   //Skips state 4 - not seen as useful.   
                    vTaskDelay(4000);             
                } else {
                    // tell base to rotate and remain in state 3
                    dcMotorBase.move(motor_PWM);       // rotate the base at 30% speed (pwm)
                    Serial.println("taskMoveMachine-state3: Rotating base");
                    vTaskDelay(50);
                    dcMotorBase.move(0);
                    vTaskDelay(50);
                    baseTicks ++;
                }
            } 
            
            // the can is not detected
            else {
                Serial.println("taskMoveMachine-state2: Can no longer detected");
                state = 0;
            }
        } 

        /*
        else if (state ==10){
            // State 4 confirms the tab was found
            if (canTopDetected.get())
            {
                dcMotorBase.move(motor_PWM);       // rotate the base at 30% speed (pwm)
                Serial.println("taskMoveMachine-state4: Rotating along tab");
                vTaskDelay(50);
                dcMotorBase.move(0);
                vTaskDelay(50);
            }
            else
            {
                Serial.println("taskMoveMachine-state4: Can tab position confirmed");
                state = 5;
                stepMotor.setPosition(0);
            }

        }
        */ 
        else if (state == 4){
            // State 4 opens the can
            // always make sure the can is detected
            if(!canDetected.get()){
                // if no can detected then go back to state 0
                Serial.println("taskMoveMachine-state4: Can not detected");
                state = 0;
                dcMotorBase.move(0);
            } else {
                // move the head up slightly
                if (abs(stepMotor.getPosition()) < abs(100*up_step)){
                    // move head up 100 ticks
                    stepMotor.move(up_step);
                    Serial.println("taskMoveMachine-state4: Moving Up");
                } else if (abs(stepMotor.getPosition()) >= abs(100*up_step)){
                    // moved to desired position- time to open
                    if(canOpenCount < canOpenTicks){
                        // open can
                        Serial.println("taskMoveMachine-state4: Opening can");
                        dcMotorHead.move(motor_PWM);
                        vTaskDelay(50);
                        canOpenCount ++;
                    } else {
                        // stop opening can
                        state = 5;
                        Serial.print("taskMoveMachine-state4: new state ");
                        Serial.println(state);
                        Serial.println("taskMoveMachine-state4: Can open");
                        dcMotorHead.brake();
                        vTaskDelay(500);
                        Serial.println("taskMoveMachine-state4: dcMotorHead stopped");
                    }
                } else {
                    Serial.println("taskMoveMachine-state4: Error opening can");
                    state = 5;
                }
            }

        } else if (state == 5){
            // State 5 moves the head up so the can be removed
            if (abs(stepMotor.getPosition()) >= abs(400*up_step))
            {
                if(!canDetected.get())
                {
                    state = 6;
                    Serial.println("taskMoveMachine-state5: Can Removed");
                }
            }
            else
            {
                stepMotor.move(up_step);
                Serial.println("taskMoveMachine-state5: Moving Up");
            }
        } else if (state = 6){
            // State 6 moves the head motor back to position
            if(canOpenCount > 0 or canOpenCount > 150){
                // reset can open
                Serial.println("taskMoveMachine-state6: Resetting dcMotorHead");
                dcMotorHead.move(-motor_PWM);
                vTaskDelay(50);
                canOpenCount --;
            } else {
                // motor reset
                Serial.println("taskMoveMachine-state6: dcMotorHead reset");
                dcMotorHead.brake();
                state = 7;
            }
        } else if (state = 7){
            // State 7 moves the base back to position
            if(baseTicks > 0 or baseTicks > 150){
                // reset base
                Serial.println("taskMoveMachine-state7: dcMotorBase reset");
                dcMotorBase.move(-motor_PWM);
            } else {
                // stop moving the base
                dcMotorBase.brake();
                state = 0;
            }
        }
        vTaskDelayUntil(&xLastWakeTime, 10);
    }
}