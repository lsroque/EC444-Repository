#  Skill 09 - Servos

Author: Lesbeth Roque

Date: 2020-09-20
-----

## Summary
In this skill, we were required to control the servo using an ESP32. In order to do so, we needed to wire up the ESP to the standard rotational Servo. Next, we needed to modify the provided code to run the servo through its full range of 180 degrees. I modified the minimum and maximum pulse width in my servo. In order to rotate 180 degrees, my minimum pulse width was 500us and maximum pulse width was 2300us. 

## Sketches and Photos
#### Set Up:
<p align="left">
<img src="https://github.com/BU-EC444/Roque-Lesbeth/blob/master/skills/cluster-1/09/images/09_ServoToEspPins.jpg" alt="Setup1" width="500">
</p>
<p>
    <em>GPIO Pins 3V, GND, and 18 used.</em>
</p>

<p align="left">
<img src="https://github.com/BU-EC444/Roque-Lesbeth/blob/master/skills/cluster-1/09/images/09_ServoToEspWires.jpg" alt="Setup2" width="500">
</p>
<p>
    <em>Wiring on ESP</em>
</p>


<p align="left">
<img src="https://github.com/BU-EC444/Roque-Lesbeth/blob/master/skills/cluster-1/09/images/09_ServotoEspConnection.jpg" alt="Setup2" width="500">
</p>
<p>
    <em>Wiring connection from Servo to ESP:<br/> Servo Brown Wire/Black Wire -> GND<br/> Servo Red Wire/ Orange Wire -> POWER (3V) <br/> Orange Servo Wire/ Yellow Wire -> SIGNAL(GPIO Pin 18)</em>
</p>

#### Video:
<p align="left">
<img src="https://github.com/BU-EC444/Roque-Lesbeth/blob/master/skills/cluster-1/09/images/09_VideoThumbnail.jpg" alt="Video Thumbnail" width="500">
</p>
<p>
    <em>https://youtu.be/L93I1Z6jpNg</em>
</p>

## Modules, Tools, Source Used Including Attribution
- GPIOs
- Servos/PWM (Pulse Width Modulation)

## Supporting Artifacts
- [Wiring help](https://randomnerdtutorials.com/esp32-servo-motor-web-server-arduino-ide/)
- [Servo Github Repo](https://github.com/espressif/esp-idf/tree/master/examples/peripherals/mcpwm/)


-----
