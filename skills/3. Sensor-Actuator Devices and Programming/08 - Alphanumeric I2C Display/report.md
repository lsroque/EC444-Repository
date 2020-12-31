#  Skill 08 - Alphanumeric Display

Author: Lesbeth Roque

Date: 2020-09-20
-----

## Summary
In this skill, we were required to wire up the alphanumeric display on our breadboard with an ESP32 and create a program that would allow a user to input up to 4 ASCII characters to display from the console on the the alphanumeric display. An I2C bus connected to the alphanumeric display was used to control all of segments on the display. The I2C required pull up resistors, thus, the pins SCL and SDA were connected from the ESP32 to the alphanumeric display. SCL and SDA pins have pull up resistors internally. 

## Sketches and Photos
#### Circuitry Setup

<p align="left">
<img src="https://github.com/BU-EC444/Roque-Lesbeth/blob/master/skills/cluster-1/08/images/08_CircuitrySetup.jpg" alt="Circuitry Setup" width="500">
</p>
<p>
    <em>GPIO Pins SCL and SDA used.</em>
</p>

<p align="left">
<img src="https://github.com/BU-EC444/Roque-Lesbeth/blob/master/skills/cluster-1/08/images/08_I2CDemo.jpg" alt="Setup2" width="500">
</p>
<p>
    <em>Program output. My initials and a star is shown.</em>
</p>

## Modules, Tools, Source Used Including Attribution
- GPIOs
- Huzzah Board Wiring
- UART


## Supporting Artifacts
Github repositories used:<br/>
- [I2C Display](https://github.com/BU-EC444/code-examples/tree/master/i2c-display)
- [Adafruit - ASCII Characters](https://github.com/adafruit/Adafruit_LED_Backpack/blob/master/Adafruit_LEDBackpack.cpp)


-----
