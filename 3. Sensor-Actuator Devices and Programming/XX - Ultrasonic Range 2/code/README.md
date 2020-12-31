# Code Readme

In skill31.c, I use RMT (Remote Control)  and PWM to read in meaningful data from the Ultrasonic 2. Then this pulse is measured using the RMT Receiver. Once the duration of the return pulse is measured, the distance is converted from meters into cm. The Pin out use in the code is as follows: TX - pin 25 – trigger and RX - pin 26 – echo. A vtaskdelay() of 2s is used to sample the distance every 2 seconds.

#### Sources
- [Help from Supporting Website on HC-SR04 using RMT](https://esp32.com/viewtopic.php?t=5787)
- [Datasheet](https://cdn.sparkfun.com/assets/b/3/0/b/a/DGCH-RED_datasheet.pdf)
