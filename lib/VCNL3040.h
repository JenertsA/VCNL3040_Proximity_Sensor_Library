#ifndef VCNL3040.h

#define VCNL3040.h
#include "Arduino.h"


#define VCNL3040_addr 0x60

//// VCNL3040 PARAMETERS ////
enum VCNL3040
{
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


#endif