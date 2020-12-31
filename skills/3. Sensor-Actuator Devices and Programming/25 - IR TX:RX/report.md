#  Skill 25 - IR TX/RX

Author: Lesbeth Roque

Date: 2020-11-10
-----

## Summary
In this skill we were required to build up two identical breadboards of an IR emitter and IR receiver. Building up from the traffic-light-ir-example provided in the example code, we were able to modify the code so that a button click on a (transmitter) fob will send the fob state of either off, red, green, or yellow to the receiving fob. Once the code is received by the receiving fob, it will set its state to the state received (of either off, red, green, or yellow) and light up the LED color associated with it. Moreover, this skill uses an H-bridge to modulate UART, IR receiver diodes, and IR LEDs to ensure the transfer of information.

## Sketches and Photos
<p align="left">
<img src="https://github.com/lsroque/EC444-Repository/blob/master/skills/3.%20Sensor-Actuator%20Devices%20and%20Programming/25%20-%20IR%20TX:RX/images/25_FOB_Setup.jpg" width="400">
</p>
<p>
    <em>FOB Set up. 220 ohm resistors used. In the other FOB (not shown) 330 ohm resistors were used.</em>
</p>

<p align="left">
<img src="https://github.com/lsroque/EC444-Repository/blob/master/skills/3.%20Sensor-Actuator%20Devices%20and%20Programming/25%20-%20IR%20TX:RX/images/25_Sytem_Setup.jpg" alt="System Setup" width="400">
</p>
<p>
    <em>Fob System. As shown, the IR LED's are bent at a 90 degree angle towards the other FOB and the IR receiver diodes 'curvy part' are set towards each other.</em>
</p>

## Modules, Tools, Source Used Including Attribution
- TX/RX
- GPIOs

## Supporting Artifacts
- [GitHub Repo for example code](https://github.com/BU-EC444/code-examples/tree/master/traffic-light-ir-example)
- [Video of Demo](https://youtu.be/q3uV300sDLU)


-----
