#  Skill 14 - Ultrasonic Range Sensor

Author: Lesbeth Roque

Date: 2020-10-08
-----

## Summary
In this skill, we were able to use an ultrasonic sensor to estimate the distance from the sensor to an object that reflects sound. Here, we were required to connect our 3.3V to the sensor and connect the sensot to an ADC pin. In this way, we can use read the data from the sensor and calculate range using the equation provided on the sensors data sheet. In this skill, I used the Analog output on the sensor and conected it to pin A2, a non-output pin. Once connected, the console displays the distance in meters and is sampled every 2s. The terminal output is show below.

## Sketches and Photos
<p align="left">
<img src="https://github.com/lsroque/EC444-Repository/blob/master/skills/3.%20Sensor-Actuator%20Devices%20and%20Programming/14%20-%20Ultrasonic%20Range%201/images/14_Breadboard.jpg" width="400">
</p>
<p>
    <em>Breadboard setup</em>
</p>

<p align="left">
<img src="https://github.com/lsroque/EC444-Repository/blob/master/skills/3.%20Sensor-Actuator%20Devices%20and%20Programming/14%20-%20Ultrasonic%20Range%201/images/14_Terminal.jpg" alt="Terminal" width="400">
</p>
<p>
    <em>Terminal Output</em>
</p>

## Modules, Tools, Source Used Including Attribution
- GPIO
- ADC

## Supporting Artifacts
- [Ultrasonic Distance Equation](https://www.maxbotix.com/documents/HRLV-MaxSonar-EZ_Datasheet.pdf)
- [Sketch provided by website](http://whizzer.bu.edu/skills/ultrasonic1)

-----
