/**
 * @file
 * @brief
 * @details
 * 
 * @author Benjamin Bons
 * @date Nov 15, 2021
 **/

#ifndef tempSensor_h
#define tempSensor_h


#include <Arduino.h>
#include <Wire.h>


//Defines a Temperature sensor object, for reading temperatures off the MCP9808 Temperature sensor
class TempSensor
{
    protected:
        // SCL pin
        uint8_t scl_pin;

        //SDA Pin
        uint8_t sda_pin;

        //I2C address
        uint8_t address;

        //Temp Value address
        const uint8_t temp = 0x06;

        //Manufacturer Value address
        const uint8_t manu = 0x07;

    public:
        
        //Constructor
        TempSensor(uint8_t scl, uint8_t sda, uint8_t add);

        //Get the temp in C
        float getTempC();

        //Get the temp in F
        float getTempF();

        //Get the manufacturer code for I2C debugging - should return 0x54 or 84
        uint16_t getManuCode();
};

#endif