/**
    This is a library written for the VCNL3040
    
    I intend to sell a board with this particular sensor
    once it will be available for sell link will show up here:

    Written by Andris Jenerts @ SIG, March 2020

    VCNL3040 integrates a proximity sensor (PS), and a high
    power IRED into one small package. Besides selectable 12-bit 
    or 16-bit output, it has programmable interrupt features of
    individual high and low threshold levels. 

    This library handles the VCNL3040 register setup and is able to
    make proximity and interrup flag readings

   https://github.com/JenertsA/VCNL3040_Proximity_Sensor_Library

    Development environment specifics:
    Arduino IDE 1.8.10

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY

    Copyright (c) 2020 Andris Jenerts. All rights reserved.

    This work is licensed under the terms of the MIT license.  
    For a copy, see <https://opensource.org/licenses/MIT>.

*/



#include "VCNL3040.h"



VCNL3040::VCNL3040(){};

bool VCNL3040::begin(bool _resetToDefault)
{
    if(isConnected())
    {
        if(_resetToDefault)
        {
            writeToCommand(VCNL3040_DEV_ADDRESS,0x03,0x0003);
            writeToCommand(VCNL3040_DEV_ADDRESS,0x04,0x00);
            writeToCommand(VCNL3040_DEV_ADDRESS,0x05,0x00);
            writeToCommand(VCNL3040_DEV_ADDRESS,0x06,0x00);
            writeToCommand(VCNL3040_DEV_ADDRESS,0x07,0x00);
        }
        return true;
    }
    return false;
}

bool VCNL3040::isConnected()
{
    Wire.beginTransmission(VCNL3040_DEV_ADDRESS);
    if(Wire.endTransmission() == 0) //ack
    {
        if(readCommand(0x60, 0x0C) == 0x186)
        {
            return true;
        }
        return false;
    }
    return false;
}

void VCNL3040::startReading()
{
    _currentSetting = _currentSetting = readCommand(VCNL3040_DEV_ADDRESS, 0x03);  
    _currentSetting = _currentSetting & 0xFFFE;

    writeToCommand(VCNL3040_DEV_ADDRESS, 0x03, _currentSetting);
}

void VCNL3040::sleep()
{
    _currentSetting = _currentSetting = readCommand(VCNL3040_DEV_ADDRESS, 0x03);  
    _currentSetting = _currentSetting | 0x01;

    writeToCommand(VCNL3040_DEV_ADDRESS, 0x03, _currentSetting);
}

uint8_t VCNL3040::readINTFlag()
{
    _currentValue = readCommand(VCNL3040_DEV_ADDRESS, 0x0B);
    _highByte = _currentValue >> 8;

    return _highByte;
}

uint16_t VCNL3040::readPSData()
{
    _currentValue = readCommand(VCNL3040_DEV_ADDRESS, 0x08);

    return _currentValue;
}




void VCNL3040::setLedCurrent(uint8_t _ledCurrentSetting)
{
    _currentSetting = readCommand(VCNL3040_DEV_ADDRESS, 0x04);
    _currentSetting = _currentSetting & 0xF8FF;
    _currentSetting = _currentSetting | (_ledCurrentSetting << 8);

    writeToCommand(VCNL3040_DEV_ADDRESS, 0x04, _currentSetting);
}


void VCNL3040::setPSDuty(uint8_t _PSDutySetting)
{
    _currentSetting = readCommand(VCNL3040_DEV_ADDRESS, 0x03);
    _currentSetting = _currentSetting & 0xFF3F;
    _currentSetting = _currentSetting | (_PSDutySetting << 6);

    writeToCommand(VCNL3040_DEV_ADDRESS, 0x03, _currentSetting);
}

void VCNL3040::setPSIT(uint8_t _psITSetting)
{
    _currentSetting = readCommand(VCNL3040_DEV_ADDRESS, 0x03);
    _currentSetting = _currentSetting & 0xFFF1;
    _currentSetting = _currentSetting | (_psITSetting << 1);

    writeToCommand(VCNL3040_DEV_ADDRESS, 0x03, _currentSetting);
}

void VCNL3040::setPSResolution(bool _psResolutionSetting)
{
    _currentSetting = _currentSetting = readCommand(VCNL3040_DEV_ADDRESS, 0x03);
    _currentSetting = _currentSetting & 0xF7FF;
    _currentSetting = _currentSetting | (_psResolutionSetting<<11);
    
    writeToCommand(VCNL3040_DEV_ADDRESS, 0x03, _currentSetting);
}



void VCNL3040::setINTMode(uint8_t _psINTMode)
{
    _currentSetting = _currentSetting = readCommand(VCNL3040_DEV_ADDRESS, 0x03);
    _currentSetting = _currentSetting & 0xFCFF;
    _currentSetting = _currentSetting | (_psINTMode<<8);
    
    writeToCommand(VCNL3040_DEV_ADDRESS, 0x03, _currentSetting);
}

void VCNL3040::enableINTProxMode()
{
    _currentSetting = readCommand(VCNL3040_DEV_ADDRESS, 0x04);
    _currentSetting = _currentSetting & 0xBFFF;
    _currentSetting = _currentSetting | (0x01 << 14);

    writeToCommand(VCNL3040_DEV_ADDRESS, 0x04, _currentSetting);
}

void VCNL3040::enableINTNormalMode()
{
    _currentSetting = readCommand(VCNL3040_DEV_ADDRESS, 0x04);
    _currentSetting = _currentSetting & 0xBFFF;
    _currentSetting = _currentSetting | (0x00 << 14);

    writeToCommand(VCNL3040_DEV_ADDRESS, 0x04, _currentSetting);
}

void VCNL3040::setPSPers(uint8_t _psPersSetting)
{
    _currentSetting = _currentSetting = readCommand(VCNL3040_DEV_ADDRESS, 0x03);
    _currentSetting = _currentSetting & 0xFFCF;
    _currentSetting = _currentSetting | (_psPersSetting << 4);
    
    writeToCommand(VCNL3040_DEV_ADDRESS, 0x03, _currentSetting);
}

void VCNL3040::setPSTHDL(uint16_t _THDLValue)
{
    writeToCommand(VCNL3040_DEV_ADDRESS, 0x06, _THDLValue);
}

void VCNL3040::setPSTHDH(uint16_t _THDHValue)
{
    writeToCommand(VCNL3040_DEV_ADDRESS, 0x07, _THDHValue);
}



uint16_t VCNL3040::readCommand(int _devAddr, int _cmdCode)
{

    Wire.beginTransmission(_devAddr);
    Wire.write(_cmdCode);
    Wire.endTransmission(false);

    Wire.requestFrom(_devAddr, 0x02); // request 2 bytes (each command contains 2 registers)

    if (Wire.available() != 0x02)
    {
        //TO DO throw some kind of error
        return 0;
    }

    byte Lbyte = Wire.read(); 
    byte Hbyte = Wire.read();

    uint16_t value = (Hbyte << 8) | Lbyte; // compose two bytes in 16-bit variable with High Byte first
    return value; // return 16-bits 
}

void VCNL3040::writeToCommand(uint8_t _devAddr, uint8_t _cmdCode, uint16_t _value)
{
    Wire.beginTransmission(_devAddr);
    Wire.write(_cmdCode);

    Wire.write(uint8_t(_value & 0xff)); // LOW byte
    Wire.write(uint8_t(_value >> 8)); //HIGH byte
    Wire.endTransmission();
    //delay(5);
}


