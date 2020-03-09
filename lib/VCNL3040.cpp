#include "VCNL3040.h"
#include "arduino.h"
#include "Wire.h"

#define DEBUG 

VCNL3040::VCNL3040(uint8_t dev)
{
    Wire.begin();
}

uint16_t VCNL3040::readCommand(uint8_t _devAddr, uint8_t _cmdCode)
{

    Wire.beginTransmission(_devAddr);
    Wire.write(_cmdCode);
    Wire.endTransmission(false);

    Wire.requestFrom(_devAddr, 0x02); // request 2 bytes (each command contains 2 registers)

    if (Wire.available() != 0x02)
    {
        Serial.println("not correct byte count");
        return 0;
    }

    byte Lbyte = Wire.read(); 
    byte Hbyte = Wire.read();

// #if DEBUG
//   Serial.print("Low Byte: ");
//   Serial.println(Lbyte);
//   Serial.print("High Byte: ");
//   Serial.println(Hbyte);
// #endif

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


