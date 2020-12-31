#  Skill 32 - Wheel Speed

Author: Lesbeth Roque

Date: 2020-12-01
-----

## Summary
The goal of this skill it to measure the wheel speed of the purple car. To determine speed, the optical encode is used to count the ticks that pass the sensor in a period of time. Wheel speed can be calculated using RPM X 60 (s/m) X wheel circumference (m). Ticks are sensed using the LED/phototransmitter to detect the presense of light in order to get a pulse that is high or low.

## Sketches and Photos
<p align="left">
<img src="https://github.com/BU-EC444/Roque-Lesbeth/blob/master/skills/cluster-5/32/images/32_Wiring2.jpg" width=600>
</p>
<p>
    <em>Wiring. Black is the emitter connected to ground, Orange is the anode (connected to 330 ohm resistor and 5V), Green is the collector (connected to 10k ohm resistor, GPIO 34 (A2), and 5V), and Yellow is the cathode connected to ground</em>
</p>

<p align="left">
<img src="https://github.com/BU-EC444/Roque-Lesbeth/blob/master/skills/cluster-5/32/images/32_Wiring1.jpg" width=600>
</p>
<p>
    <em>Wiring Side View</em>
</p>

<p align="left">
<img src="https://github.com/BU-EC444/Roque-Lesbeth/blob/master/skills/cluster-5/32/images/32_Wheel_Paper.jpg" width=600>
</p>
<p>
    <em>Optical Encoder and Black and White Paper shown on wheel </em>
</p>


<p align="left">
<img src="https://github.com/BU-EC444/Roque-Lesbeth/blob/master/skills/cluster-5/32/images/32_Terminal_Output.jpg" width=600>
</p>
<p>
    <em>Terminal Output</em>
</p>


## Modules, Tools, Source Used Including Attribution
- Optical Encoder
- Timers

## Supporting Artifacts
- [Wiring](https://learn.sparkfun.com/tutorials/qrd1114-optical-detector-hookup-guide#example-circuit)

-----
