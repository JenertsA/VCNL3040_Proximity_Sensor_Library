#ifndef VCNL3040_h

#define VCNL3040_h
#include "Arduino.h"


//// VCNL3040 PARAMETERS ////
enum VCNL3040_PARAM
{

    DEV_ADDRESS = 0x60,

    //LED current settings
    LED_CURRENT_50mA = 0x00,
    LED_CURRENT_75mA = 0x01,
    LED_CURRENT_120mA = 0x02,
    LED_CURRENT_140mA = 0x03,
    LED_CURRENT_160mA = 0x04,
    LED_CURRENT_180mA = 0x05,
    LED_CURRENT_200mA = 0x07,

    //Duty cycle for sensors LED
    PS_DUTY_40 = 0x00,
    PS_DUTY_80 = 0x01,
    PS_DUTY_160 = 0x02,
    PS_DUTY_320 = 0x03,

    //Measurement integration time 1T0 - IT = 1 -  125us (application note page 5 )
    PS_IT_1T0 = 0x00,
    PS_IT_1T5 = 0x01,
    PS_IT_2T0 = 0x02,
    PS_IT_2T5 = 0x03,
    PS_IT_3T0 = 0x04,
    PS_IT_3T5 = 0x05,
    PS_IT_4T0 = 0x06,
    PS_IT_8T0 = 0x07,

    //Iterupt setup
    PS_IT_DISABLED = 0x00, 
    PS_IT_CLOSING = 0x01,
    PS_IT_AWAY = 0x02,
    PS_IT_CLOSING_AWAY = 0x03
};



class VCNL3040
{
    public:


    /**
         *@param sensNum set which sensor is it
        **/
    VCNL3040(uint8_t sensNum); //uint8_t addr = VCNL3040_PARAM::DEV_ADDRESS


    /**
         * FUNCTION FOR READING 16 bits (two 8-bit registers)
         * @param devAddr Device slave address
         * @param cmdCode Command code from which to request data
         * @return return 16-bits with DataByteHigh first and then DataByteLow
        **/
    uint16_t readCommand(uint8_t devAddr, uint8_t cmdCode);

    /**
         * FUNCTION FOR WRITING 16 bits (two 8-bit registers)
         * @param devAddr Device slave address
         * @param cmdCode Command code to which write data
         * @param value 16-bit value to write in command
        **/
    void writeToCommand(uint8_t DevAddr, uint8_t cmdCode, uint16_t value);

    private:

};


#endif