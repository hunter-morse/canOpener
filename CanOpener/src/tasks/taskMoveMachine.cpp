#include "taskMoveMachine.h"

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

    // Included to increase timing accuracy (https://canvas.calpoly.edu/courses/57860/files/5478349?wrap=1)
    TickType_t xLastWakeTime = xTaskGetTickCount();
    //Serial.begin(115200);
    Serial << "Task Move Machine begun" << endl;
    for(;;){
        // Always check canDetect
        if(state == 0){ //No can in machine state
            if(canDetected.get()){
                // if can detected then move to next state
                Serial.println("taskLimitSwitch-state0: Can detected");     // should be written to display
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
                Serial.println("taskLimitSwitch-state1: Can not detected");
                state = 0;
            } else if(canTopDetected.get()){
                // if can top detected stop moving the head, pring message, and change state
                Serial.println("taskLimitSwitch-state1: Can top detected");
                state = 2;
                stepMotor.setPosition(0);
            } else {
                // if can top not detected then move the head down and remain in current state
                stepMotor.setSpeed(75);
                stepMotor.move(down_step);
                Serial.println("taskLimitSwitch-state1: Moving Down");
                // do nothing, stay in state 1
            }
        } else if (state == 2){
            if(!canDetected.get()){
                // if no can detected then go back to state 0
                Serial.println("taskLimitSwitch-state1: Can not detected");
                state = 0;
            }
            else
            {
                if(!canTopDetected.get())
                {
                    state = 3;
                    Serial.println("taskLimitSwitch-state2: Moved up enough");
                }
                else
                {
                    stepMotor.move(up_step); // Move a few steps until the can top is no longer detected
                    Serial.println("taskLimitSwitch-state2: Moving up");
                }
            }
        
        }else if (state == 3){
            // always make sure the can is detected
            if(!canDetected.get()){
                // if no can detected then go back to state 0
                Serial.println("taskLimitSwitch-state3: Can not detected");
                state = 0;
                dcMotorBase.move(0);
            } 
            // make sure can and top are detected
            else if (canDetected.get()){
                // check to see if tab has been found
                if (canTopDetected.get()){ //Changed from CanTabDetected b/c only one limit switch is planned to be used
                    // do not change state -- only change state if either the can/its top aren't detected
                    dcMotorBase.brake();        // stop rotating the base
                    Serial.println("taskLimitSwitch-state3: Can tab found!");                   
                } else {
                    // tell base to rotate and remain in state 3
                    dcMotorBase.move(motor_PWM);       // rotate the base at 30% speed (pwm)
                    Serial.println("taskLimitSwitch-state3: Rotating base");
                    vTaskDelay(50);
                    dcMotorBase.move(0);
                    vTaskDelay(50);
                }
            } 
            
            // the can is no detected
            else {
                Serial.println("taskLimitSwitch-state2: Can no longer detected");
                state = 0;
            }
        }
        vTaskDelayUntil(&xLastWakeTime, 10);
    }
}