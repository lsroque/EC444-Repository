#  Skill 33 - PID

Author: Lesbeth Roque

Date: 2020-12-01
-----

## Summary
In this skill, we are required to use a range sensor and implement a proportional control algorithm. Then, we are to wire up 3 LEDs (yellow, green, and blue). Based on the PID algorithm, error values will be obtained. If the error is less than 0, the yellow LED turns on, if the error is exactly 0, the green LED turns on, and when the error is greater than 0, the blue LED is turned on. The setpoint distance is set to 50cm using the ultrasonic 2 sensor.

## Sketches and Photos
<p align="left">
<img src="https://github.com/lsroque/EC444-Repository/blob/master/skills/5.%20Cyberphysical%20and%20Safety-Critical%20Systems/33%20-%20PID/images/33_Wiring.jpg" width=600>
</p>
<p>
    <em>Wiring with 330 ohm resistors. LED GPIO 13, 5, and 12 are used for blue, green, and yellow respectively.</em>
</p>

<p align="left">
<img src="https://github.com/lsroque/EC444-Repository/blob/master/skills/5.%20Cyberphysical%20and%20Safety-Critical%20Systems/33%20-%20PID/images/33_PID_Terminal.png" width=600>
</p>
<p>
    <em>Terminal Output</em>
</p>


## Modules, Tools, Source Used Including Attribution
- [Link to Skill Demo](https://youtu.be/h1d93HMWbDY)
- GPIO
- Ultrasonic 2

## Supporting Artifacts
- [PID Design Pattern](http://whizzer.bu.edu/briefs/design-patterns/dp-pid)
-----
