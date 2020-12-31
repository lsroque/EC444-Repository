#  Skill 10 - RTOS - Hardware Interrupt

Author: Lesbeth Roque

Date: 2020-09-22
-----

## Summary
In this skill we were required to use a real time operating system (RTOS) using the ESP32's FreeRTOS instance. I was able to wire up LEDs, a button, and the alphanumeric display and connect it to the ESP32. Once connected, a program was created to use the LEDs to count up or down in binary, use the button to toggle direction in which the LEDs blink, and display the direction "UP" or "DOWN" on the alphanumeric display.

## Sketches and Photos
#### Set Up:
<p align="left">
<img src="https://github.com/lsroque/EC444-Repository/blob/master/skills/5.%20Cyberphysical%20and%20Safety-Critical%20Systems/10%20-%20RTOS/images/10_SetupUp.jpg" alt="Breadboard Setup" width="500">
</p>

<p align="left">
<img src="https://github.com/lsroque/EC444-Repository/blob/master/skills/5.%20Cyberphysical%20and%20Safety-Critical%20Systems/10%20-%20RTOS/images/10_SetupPins.jpg" alt="ESP Setup" width="400">
</p>
<p>
    <em>Pins used: <br/> LED Pins: A0, A1, SCK, 13 <br/> I2C Pins: 3V, GND, SCL, SDA</em>
</p>


<p align="left">
<img src="https://github.com/lsroque/EC444-Repository/blob/master/skills/5.%20Cyberphysical%20and%20Safety-Critical%20Systems/10%20-%20RTOS/images/10_SetupButton.png" alt="Setup2" width="400">
</p>
<p>
    <em>Wiring connection for button. Pins used: GND, A2</em>
</p>

#### Video:
<p align="left">
<img src="https://github.com/lsroque/EC444-Repository/blob/master/skills/5.%20Cyberphysical%20and%20Safety-Critical%20Systems/10%20-%20RTOS/images/10_SetupDown.jpg" alt="Video Thumbnail" width="400">
</p>
<p>
    <em>https://youtu.be/pYvsO7hiGlw</em>
</p>

## Modules, Tools, Source Used Including Attribution
- GPIOs
- RTOS

## Supporting Artifacts
- [Design Pattern source](http://whizzer.bu.edu/briefs/design-patterns/dp-tasks)


-----
