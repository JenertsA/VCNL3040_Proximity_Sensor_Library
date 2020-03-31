VCNL3040 Proximity Sensor Library
===========================================================

The VCNL3040 Proximity sensor from Vishay integrates sensing element with high power IR LED in a single small package. This sensor is ideal for detecting if something is in front of sensor. It is made to work up to 30 cm range and adjustable LED current, Duty cycle and integration Time can get useful for application specific integration.

Programmable interrupt feature can help reduce the workload on MCU and decrease power consumption. It is possible to setup low and high thresholds for interrupt. In addition, Proximity detection logic output mode allows to detect closing objects and when it moves away.

Here you will find link to the tindie shop once boards will be up there:
**[VCN3040 breakout board](https://www.tindie.com/products/jenertsa/vcnl3040-breakout/)** on Tindie
![](https://cdn.tindiemedia.com/images/resize/uLIJQ6O9tM3doxCwJIUIHGCP2oI=/p/fit-in/1032x688/filters:fill(fff)/i/928471/products/2020-03-29T20%3A11%3A18.100Z-top_bottom.png)

You can find
-------------------

* **/examples** - :ghost: TO DO
* **/src** - Source files for the library (.cpp, .h).
* **keywords.txt** - Keywords from this library that will be highlighted in the Arduino IDE. 
* **library.properties** - General library properties for the Arduino package manager.

How it works?
------------------

start by including this and Wire libraries. Make a VCNL3040 object

    #include <VCNL3040.h>
    #include <Wire.h>
    
    VCNL3040 sens;
    
library doesn't call `Wire.begin()` you should do it yourself in `void setup()`.

### Basic functions

`sens.begin()` - must be called to initialize sensor, <br>
`sens.begin(true)` - can be used to rest all settings to default.<br>

`sens.startReading()` - sensor is woken from sleep mode, once this function is called sensor starts performing measurements <br>

`sens.sleep()`- sensor is powered down in sleep mode.

`sens.readPSData()` - returns `unsigned int` value of last measurment value.<br>

`sens.readINTFlag()` - returns interrupt status

INT flag value | meaning 
-----|------
0x00 | interrupt not triggered  
0x01 | PS drops below PS_THDL (low interupt treshold)  
0x02 | PS rises above PS_THDH (high interupt treshold) 
0x03 | PS entering protection mode (what is that!?)


### Configuring sensor
There are many things you can configure on VCNL3040.<br> 
Vishay has made [app note](http://www.vishay.com/docs/84940/designingvcnl3040.pdf), about how to implement sensor in specific application.<br>

**Bolded** setting are default ones.
<br>

**Resolution**

There are low and high resoluiton modes for VCNL3040<br>
use function `sens.setPSResolution(value)` for choosing one

value | HEX | resolution
------|-----|-----------
**LOW** | 0x00 | 12-bit
HIGH | 0x01 | 16-bit

<br>

**LED current**

Use function `sens.setLedCurrent(value)` as an value you can use on of the specified values from list below <br>

value | HEX | LED current 
---------------|-----|------------
**LED_CURRENT_50mA** | 0x00 | 50mA
LED_CURRENT_75mA | 0x01 | 75mA
LED_CURRENT_120mA | 0x02 | 120mA
LED_CURRENT_140mA | 0x03 | 140mA
LED_CURRENT_160mA | 0x04 | 160mA
LED_CURRENT_180mA | 0x05 | 180mA
LED_CURRENT_200mA | 0x06 | 200mA

<br>

**PS duty**

set prefered PS duty using `sens.setPSDuty(value)` <br>

value | HEX | PS Duty | measurement time
------|-----|---------|-----------------
**PS_DUTY_40** | 0x00 | 1/40 | 4.85 ms
PS_DUTY_80 | 0x01 | 1/80 | *unknown*
PS_DUTY_160 | 0x02 | 1/160 | *unknown*
PS_DUTY_320 | 0x03 | 1/320 | 40 ms 

<br>

**Integration time**

set PS_IT using `sens.setPSIT(value)` <br>
value | HEX | PS_IT
------|-----|------
**PS_IT_1T0** | 0x00 | 1T
PS_IT_1T5 | 0x01 | 1.5T
PS_IT_2T0 | 0x02 | 2T
PS_IT_2T5 | 0x03 | 2.5T
PS_IT_3T0 | 0x04 | 3T
PS_IT_3T5 | 0x05 | 3.5T
PS_IT_4T0 | 0x06 | 4T
PS_IT_8T0 | 0x07 | 8T

<br>

**Interrupt settings**

By default setting interrupt is disabled you can enable it by using function<br>
`sens.setINTMode(value)` - enable interrupt in one of the modes - table below<br>
To effectively adopt PS INT function Vishay recommends `trigger by closing` mode
value | HEX | trigger mode
------|-----|-----
**PS_INT_DISABLED** | 0x00 | disabled
PS_INT_CLOSING | 0x01 | by closing
PS_INT_AWAY | 0x02 | by away
PS_INT_CLOSING_AWAY | 0x03 | by closing and away

there are two interrput modes. You can switch between them using funtions:
`sens.enableINTNormalMode()` - normal mode is when interrup is triggered. <br> 
It stays that way until you read out interrup flag using function `sens.readINTFlag()`

`sens.enableINTProxMode()` - proximity interrupt mode

`sens.setPSPers(value)` - you can choose how many consecutive measurments in tirggering range have to be made to assert interrupt

value | HEX | count
------|-----|------------------
**PS_PERS_1** | 0x00 | 1
PS_PERS_2 | 0x01 | 2
PS_PERS_3 | 0x03 | 3
PS_PERS_4 | 0x04 | 4

<br>

**interrupt thresholds**

There are upper and lower threshold. You can set nedeed value (up to 16-bit) for both of them using functions

`sens.setPSTHDL()` - for setting lower threshold <br>
`sens.setPSTHDH()` - for setting upper threshold

<br>

TODO LIST
------------------
- [ ] Example code
- [ ] Features from PS_CONF3 register
- [ ] Add boards to Tindie

License Information
-------------------

This code is _**open source**_! 

Please review the LICENSE.md file for license information.

Please use, reuse, and modify these files as you see fit. Please maintain attribution to my name - Andris Jenerts and release anything derivative under the same license.

Distributed as-is; no warranty is given.

