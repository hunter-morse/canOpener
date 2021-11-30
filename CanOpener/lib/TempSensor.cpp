/**
 * @file
 * */

#include <Arduino.h>
#include "TempSensor.h"
#include <Wire.h>



TempSensor::TempSensor(uint8_t scl, uint8_t sda, uint8_t addr)
{
    scl_pin = scl;
    sda_pin = sda;
    address = addr;
    Wire.begin(sda_pin, scl_pin);
}

float TempSensor::getTempC()
{
    Wire.beginTransmission(address);
    Wire.write(0x05);
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
float TempSensor::getTempF()
{
    float temp = getTempC();
    return (float) 9/5*temp + 32;
}

uint16_t TempSensor::getManuCode()
{
    Wire.beginTransmission(address);
    Wire.write(0x06);
    Wire.endTransmission(false);
    Wire.requestFrom(address, (uint8_t) 2, (uint8_t) true);
    uint8_t msb = Wire.read();
    uint8_t lsb = Wire.read();
    return (uint16_t) msb*8 + lsb;
}