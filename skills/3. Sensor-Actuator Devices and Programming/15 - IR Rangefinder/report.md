#  Skill 15 - Long Range IR Range Sensor

Author: Lesbeth Roque

Date: 2020-10-08
-----

## Summary
In this skill we were required to use a long range IR sensor to measure the distance at the receiver. In order to do so, I used a Vcc of 4.5-5.5V (USB Pin to sensor), and placed the other wires of the IR connected to ADC Pin 34 and GND. In order to calculate this range, I used an IR distance equation taken from the sources below. Once connected, the console displays the distance in meters and is sampled every 2s. The terminal output is show below.

## Sketches and Photos
<p align="left">
<img src="https://github.com/lsroque/EC444-Repository/blob/master/skills/3.%20Sensor-Actuator%20Devices%20and%20Programming/15%20-%20IR%20Rangefinder/images/15_Breadboard.jpg" width="400">
</p>
<p>
    <em>Breadboard setup, GPIO34 works as the ADC Pin</em>
</p>

<p align="left">
<img src="https://github.com/lsroque/EC444-Repository/blob/master/skills/3.%20Sensor-Actuator%20Devices%20and%20Programming/15%20-%20IR%20Rangefinder/images/15_Terminal.jpg" alt="Terminal" width="400">
</p>
<p>
    <em>Terminal output</em>
</p>

## Modules, Tools, Source Used Including Attribution
- GPIOs
- ADC

## Supporting Artifacts
- [IR Distance Equation](http://home.roboticlab.eu/en/examples/sensor/ir_distance)
- [More on IR Distance Equation](https://www.limulo.net/website/coding/physical-computing/sharp-linearization.html)

-----
