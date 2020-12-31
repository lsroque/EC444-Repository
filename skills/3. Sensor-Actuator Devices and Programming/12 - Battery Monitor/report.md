#  Skill 12 - Battery Voltage Monitor

Author: Lesbeth Roque

Date: 2020-10-08
-----

## Summary
In this skill, we were required to measure the voltage of the ESP board at the ADC pin and then diplay it on the alphanumeric display. In order to measure this voltage, we were required to make a volatge divider that we well not exceed the input voltage on the ADC. In this skill I used three 1M ohm resistors to set um my voltage divider. Below is the math I used to chose resisitors and their placement on the breadboad. Attenuation factors were changed to 2.5 to get values within the required range.

## Sketches and Photos
<p align="left">
<img src="https://github.com/BU-EC444/Roque-Lesbeth/blob/master/skills/cluster-2/12/images/12_BatteryConnection.png" width="400">
</p>
<p>
    <em>Breadboard setup and battery connection</em>
</p>


<p align="left">
<img src="https://github.com/BU-EC444/Roque-Lesbeth/blob/master/skills/cluster-2/12/images/12_Wiring.png" alt="Wiring" width="400">
</p>
<p>
    <em>Wiring </em>
</p>

<p align="left">
<img src="https://github.com/BU-EC444/Roque-Lesbeth/blob/master/skills/cluster-2/12/images/12_Math.jpg" alt="Math" width="400">
</p>
<p>
    <em>Voltage divider equation, 1M ohm resistors used.</em>
</p>

<p align="left">
<img src="https://github.com/BU-EC444/Roque-Lesbeth/blob/master/skills/cluster-2/12/images/12_Terminal.png" alt="Terminal" width="400">
</p>
<p>
    <em>Terminal Output</em>
</p>


## Modules, Tools, Source Used Including Attribution
- Voltage dividers
- ADC

## Supporting Artifacts
- [Link to Adafruit Github Repo](https://github.com/adafruit/Adafruit_LED_Backpack/blob/master/Adafruit_LEDBackpack.cpp)
- [Link to ADC1 Sample Code](https://github.com/espressif/esp-idf/tree/39f090a4f1dee4e325f8109d880bf3627034d839/examples/peripherals/adc)


-----
