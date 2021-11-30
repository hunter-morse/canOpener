/**
 * @file TempSensor.h
 * @brief Header file for the TempSensor Class
 * 
 * @author Benjamin Bons
 * @date Nov 15, 2021
 **/

#ifndef tempSensor_h
#define tempSensor_h


#include <Arduino.h>
#include <Wire.h>


//Defines a Temperature sensor object, for reading temperatures off the MCP9808 Temperature sensor
/**
 * @brief Class that reads temperature over I2C from the MCP9808 temperature sensor
 * @details This class contains the functions to read the temperature from the different registers on the sensors.
 *          This class cannot use all the functions of the MCP9808, like temperature alerts and such, but it does have
 *          core funtionality
 * */
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
        const uint8_t temp = 0x05;

        //Manufacturer Value address
        const uint8_t manu = 0x06;

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