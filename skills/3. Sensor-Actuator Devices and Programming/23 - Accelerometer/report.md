#  Skill 23 - Accelerometer

Author: Lesbeth Roque

Date: 2020-10-23
-----

## Summary
In skill 23, we were provided with the base code to start and were able to work modularly. I first figured out how to use the I2C interface, then read acceleration, and last convert to tilt angles. In order to use the I2C interface, I based it off of the example code provided on the I2C Brief and used the accelerometer data sheet to figure out the proper procedure to take for reading a register and writing to register(s). Next, I was able to read in the accelerometer data and have it tilt in different directions to show that it was reading data correctly. Last, the recorded acceleration was converted to tilt angles, as this would be extremely beneficial to understand roll and pitch in measuring vibrations.

** Unfortunately, my team kit did not have the digital accelerometer (ADXL343). Therefore, I was able to write up the code and have my teammate run it on her sensor to make sure it worked. Attached is the zoom call of her showing it works :).

## Sketches and Photos
<p align="left">
<img src="https://github.com/lsroque/EC444-Repository/blob/master/skills/3.%20Sensor-Actuator%20Devices%20and%20Programming/23%20-%20Accelerometer/images/23_Terminal_Output.jpg" width="400">
</p>
<p>
    <em>Terminal Output</em>
</p>

<p align="left">
<img src="https://github.com/lsroque/EC444-Repository/blob/master/skills/3.%20Sensor-Actuator%20Devices%20and%20Programming/23%20-%20Accelerometer/images/23_Data_Table.jpg" alt="Terminal" width="600">
</p>
<p>
    <em>I2C table procudure</em>
</p>

<p align="left">
<img src="https://github.com/lsroque/EC444-Repository/blob/master/skills/3.%20Sensor-Actuator%20Devices%20and%20Programming/23%20-%20Accelerometer/images/23_roll_pitch.png" alt="Terminal" width="400">
</p>
<p>
    <em>Roll and Pitch graphic</em>
</p>

## Modules, Tools, Source Used Including Attribution
- Accelerometer
- Registers


## Supporting Artifacts
- [Accelerometer Data Sheet](https://cdn-learn.adafruit.com/assets/assets/000/070/556/original/adxl343.pdf?1549287964)
- [Tilt Sensing Formulas](https://wiki.dfrobot.com/How_to_Use_a_Three-Axis_Accelerometer_for_Tilt_Sensing)
- [I2C Brief](http://whizzer.bu.edu/briefs/design-patterns/dp-i2c)


-----
