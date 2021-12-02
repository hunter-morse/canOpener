/**
 * @file pins.h
 * @brief Definition of all pins used
 */ 

#ifndef PINS_H
#define PINS_H

// DC Motor 1
#define DC1a    PA8 //TIM1
#define DC1b    PA9
#define DCEN1   PA13

// DC Motor 2
#define DC2a    PA10 //TIM1
#define DC2b    PA11
#define DCEN2   PA14

// DC Motor 3
#define DC3a    PA5 //TIM2
#define DC3b    PB3
#define DCEN3   PC13

// DC Motor 4
#define DC4a    PB10 //TIM2
#define DC4b    PB11
#define DCEN4   PC14

// Stepper Motor 1
#define STEP1a  PB4 //TIM3
#define STEP1b  PB5
#define STEP1c  PB0
#define STEP1d  PB1
#define STEP1EN PC15

// Limit Switches
#define INLIM1  PC4
#define INLIM2  PC5
#define INLIM3  PC12

// Encoders
#define ENC1a   PB6 //TIM4
#define ENC1b   PB7
#define ENC1TIM TIM4
#define ENC2a   PA0 //TIM5
#define ENC2b   PA1
#define ENC2TIM TIM5

// Reflective Sensor
#define OUT_REFL PC10
#define IN_REFL PA4

#endif