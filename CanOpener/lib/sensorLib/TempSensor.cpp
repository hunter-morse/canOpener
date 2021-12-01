/**
 * @file TempSensor.cpp
 * @brief Contains the functionality of the TempSensor class
 * 
 * @author Ben Bons
 * @date Nov 30, 2021
 * */

#include <Arduino.h>
#include <Wire.h>
#include "TempSensor.h"



/**
 * @brief Constructor for the TempSensor class
 * @details This constructor takes in the address, scl, and sda pins for connecting to the MCP9808 sensor. The address is set
 *          with the address pins, and off of the base address of the MCP 9808. This base address is 0x18, but can be changed
 *          from 0x18 to 0x1F depending on the address pins. Look at the datasheet for more info - https://cdn-shop.adafruit.com/datasheets/MCP9808.pdf
 * 
 * @param scl The SCL pin for I2C communication
 * @param sda The SDA pin for I2C communication
 * @param addr The address of the MCP9808 sensor
 * */
TempSensor::TempSensor(uint8_t scl, uint8_t sda, uint8_t addr)
{
    scl_pin = scl;
    sda_pin = sda;
    address = addr;
    Wire.begin(sda_pin, scl_pin);
}

/**
 * @brief Gets the temperature in Celsius from the sensor
 * @details The algorithm for getting the temperature in C is found in the datasheet. Reading
 *          from the I2C bus would not have been possible without the people here:
 *          https://forum.arduino.cc/t/how-to-read-a-register-value-using-the-wire-library/206123
 * 
 * @return The temperature in Celsius
 * */
float TempSensor::getTempC()
{
    Wire.beginTransmission(address);
    Wire.write(temp);
    Wire.endTransmission(false);

    Wire.requestFrom(address, (uint8_t) 2, (uint8_t) true);
    
    uint8_t msb = Wire.read();
    //Serial.println(msb);
    msb = msb & 0x1F;
    //Serial.println(msb);
    uint8_t lsb = Wire.read();
    //Serial.println(lsb);

    float temp = 0;
    if (msb >= 0x10)
    {
        msb = msb & 0x0F;
        temp = (float) (256 - ((float) msb*16 + (float) lsb/16));
        //Serial.print("IF ");
        //Serial.println(temp);
    }
    else
    {
        temp = (float)msb*16 + (float)lsb/16;
        //Serial.println((float) lsb/16);
    }
    return temp;
}

/**
 * @brief Returns the temperature in Fahrenheit
 * @details This function just calls TempSensor::getTempC() and then converts to Fahrenheit
 * 
 * @return The temperature in Fahrenheit
 * */
float TempSensor::getTempF()
{
    float temp = getTempC();
    return (float) 9/5*temp + 32;
}

/**
 * @brief Returns the manufacturer code from the MCP9808
 * @details This function is used to ensure proper connection to the MCP9808 sensor. This function, if the 
 *          sensor is connected correctly, should return 0x54
 * 
 * @return The manufacturer ID - should be 0x54
 * */
uint16_t TempSensor::getManuCode()
{
    Wire.beginTransmission(address);
    Wire.write(manu);
    Wire.endTransmission(false);
    Wire.requestFrom(address, (uint8_t) 2, (uint8_t) true);
    uint8_t msb = Wire.read();
    uint8_t lsb = Wire.read();
    return (uint16_t) msb*8 + lsb;
}