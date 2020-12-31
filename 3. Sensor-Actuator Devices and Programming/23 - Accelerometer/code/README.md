# Code Readme

For this skill there is a skill23.c file and a ADXL343.h header file. In the C file, there are multiple modules and functions that allow the user to interface with the I2C, read in the values from the accelerometer, and finally calculate the tilt data. For the I2C interface, the example on the I2C Brief was followed. For the writeRegister, readRegister, and read16 functions I followed the I2C procudures of the write one byte, read one byte, and read multiple bytes, respectively. This procedure is outlined in the code and shown in the data table provided in the report README. In these codes there was som difficulty in calling the data in the readRegister and read 16 functions. In order to call data I used '&data' to call the data of the register and read either the 1 or 2 byte register. Next, in the getAccel and calcRP functions, I am able to read the acceleration values and translate it into meaningful values that help us understand the tilt angles of the sensor. In order to establish that the tilt angles were correct, we noted that one of the axes should read around 9.8 m/s^2, signifying gravity. This value is shown in our Z axis.

#### Sources:
- [Accelerometer Data Sheet](https://cdn-learn.adafruit.com/assets/assets/000/070/556/original/adxl343.pdf?1549287964)
- [Tilt Sensing Formulas](https://wiki.dfrobot.com/How_to_Use_a_Three-Axis_Accelerometer_for_Tilt_Sensing)
- [I2C Brief](http://whizzer.bu.edu/briefs/design-patterns/dp-i2c)
