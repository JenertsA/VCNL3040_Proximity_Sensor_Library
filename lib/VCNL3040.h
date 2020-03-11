#ifndef VCNL3040_H

#define VCNL3040_H
#include <Arduino.h>
#include <Wire.h>


//// VCNL3040 PARAMETERS ////
enum VCNL3040_PARAM
{

    DEV_ADDRESS = 0x60,

    ///LED current settings
    LED_CURRENT_50mA = 0x00,
    LED_CURRENT_75mA = 0x01,
    LED_CURRENT_120mA = 0x02,
    LED_CURRENT_140mA = 0x03,
    LED_CURRENT_160mA = 0x04,
    LED_CURRENT_180mA = 0x05,
    LED_CURRENT_200mA = 0x07,

    ///Duty cycle for sensors LED
    PS_DUTY_40 = 0x00,
    PS_DUTY_80 = 0x01,
    PS_DUTY_160 = 0x02,
    PS_DUTY_320 = 0x03,

    ///Measurement integration time 1T0 - IT = 1 -  125us (application note page 5 )
    PS_IT_1T0 = 0x00,
    PS_IT_1T5 = 0x01,
    PS_IT_2T0 = 0x02,
    PS_IT_2T5 = 0x03,
    PS_IT_3T0 = 0x04,
    PS_IT_3T5 = 0x05,
    PS_IT_4T0 = 0x06,
    PS_IT_8T0 = 0x07,

    ///Interupt persistance setting - how many consecutive measruements
    ///have to be made in interupt range to trigger interupt (datasheet page 11)
    PS_PERS_1 = 0x00,
    PS_PERS_2 = 0x01,
    PS_PERS_3 = 0x02,
    PS_PERS_4 = 0x03,

    ///Iterupt modes
    PS_INT_DISABLED = 0x00, 
    PS_INT_CLOSING = 0x01,
    PS_INT_AWAY = 0x02,
    PS_INT_CLOSING_AWAY = 0x03,
   
};



class VCNL3040
{
    public:

    VCNL3040();

    /**
     * check if sensor is connected with option to reset all settings
     * @return true if sensor is conected
     */
    bool begin(bool resetToDefault = false);

    /**
     * check if sensor is conected
     * @return true if sensor is connected
     */
    bool isConnected();

    /// start reading data
    void startReading();

    /// set sensor to sleep mode
    void sleep();

    /**
     * return state of INT_Flag register (0x0B high byte)
     * @return 0x01 -> PS drops below PS_THDL 
     *         0x02 -> PS rises above PS_THDH
     *         0x40 -> PS entering protection mode (what is that!?)
     */
    uint8_t readINTFlag();

    /**
     * read proximity data
     * @return 12 or 16 bit ps sensors value
     */
    uint16_t readPSData();


    /**
     * set sensors led current 
     * @param ledCurrentSetting PS_MS (0x05 High byte) 2:0 bits 
     */
    void setLedCurrent(uint8_t ledCurrentSetting); 

    /**
     * Set duty cycle
     * @param psDutySetting PS_CONF1 (0x03 Low byte) 7:6 bits 
     */
    void setPSDuty(uint8_t psDutySetting);

    /**
     * Set integration time
     * @param psITSetting PS_CONF1 (0x03 Low byte) 3:1 bits 
     */
    void setPSIT(uint8_t psITSetting);

    /**
     * select output resolution
     * @param psResolutionSetting  PS_CONF2 (0x03 High byte) 3rd bit 
     *                             12-bit -> LOW 
     *                             16-bit -> HIGH
     */
    void setPSResolution(bool psResolutionSetting);


    /**
     * Select interupt mode
     * enable interupt and select mode - closing, away or both
     * @param psINTMode PS_CONF2 (0x03 High byte) byte 1:0 bits 
     */
    void setINTMode(uint8_t psINTMode);

    ///enable proximity mode for trigger
    void enableINTProxMode();

    ///enable normal mode for trigger
    void enableINTNormalMode();

    /**
     * Set interupt persistence setting
     * how many consecutive measurements triggers flag
     * @param psPersSetting PS_CONF1 (0x03 Low byte) 5:4 bits 
     */
    void setPSPers(uint8_t psPersSetting);

    /**
     * set interupt LOW threshold 
     * @param THDLValue 16 or 12 bit value for thershold 
     */
    void setPSTHDL(uint16_t THDLValue);

    /**
     * set interupt HIGH threshold 
     * @param THDHValue 16 or 12 bit value for thershold 
     */
    void setPSTHDH(uint16_t THDHValue);



    /**
     * Read 16 bits (two 8-bit registers)
     * @param devAddr Device slave address
     * @param cmdCode Command code from which to request data
     * @return return 16-bits with DataByteHigh first and then DataByteLow
     */
    uint16_t readCommand(int devAddr, int cmdCode);

    /**
     * Write 16 bits (two 8-bit registers)
     * @param devAddr Device slave address
     * @param cmdCode Command code to which write data
     * @param value 16-bit value to write in command
     */
    void writeToCommand(uint8_t DevAddr, uint8_t cmdCode, uint16_t value);


    /**
     * TO DO 
     * PS_CANC_L and PS_CANC_H
     * PS_CONF_3 
     * 
     */

    private:
    uint16_t _currentSetting; 
    uint16_t _currentValue;
    uint8_t _lowByte;
    uint8_t _highByte;
};


#endif