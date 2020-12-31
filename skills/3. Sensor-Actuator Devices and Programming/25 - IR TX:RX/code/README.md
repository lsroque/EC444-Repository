# Code Readme

In this skill, I modified the program called ir-car-beacon.c given in the EC444's example code github. I renamed the program to Skill25.c, and built this code on both FOBs. In the code, a button click on one FOB is able to send code containing the state of off, red, green, or yellow to the receiving fob. In order to do so, I used a button task that would be able to transmit data to the other FOB once clicked. I also used switch statements to cycle through the states (i.e: off -> red -> green -> yellow -> off etc.). Once the data was trasmitted to the receiving fob, the new state is shown on the receiver FOB. 

Due to the fact I built the code on both FOBs, any FOB can act as a trasmitter or receiver as shown in the video in the README.

Also
- GPIOs (for the LED connection on the ESP)
- [GitHub Repo for EC444 example code](https://github.com/BU-EC444/code-examples/tree/master/traffic-light-ir-example)
