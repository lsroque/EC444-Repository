#  Skill 28 - Leader Elections

Author: Nnenna Eze and Lesbeth Roque

Date: 2020-11-09
-----

## Summary
The code for this skill is based on the Bully Algorithm, in which a leader is elected based on minimum ID, and a new election is started if the leader is disconnected, or if a device with a lower ID joins the server. This skill, unlike skill 25, used UDP to communicate between ESPs. LEDs were also incorporated into the code to show which state an ESP was in. For instance, in my specific code, a red LED represents the fact that an election is happening, and a green LED signifies that a specific ESP is the current leader. 

## Sketches and Photos
<img src="https://github.com/lsroque/EC444-Repository/blob/master/skills/5.%20Cyberphysical%20and%20Safety-Critical%20Systems/28%20-%20State%20Models/images/skill28img.jpg" width="400" >

<img src="https://github.com/lsroque/EC444-Repository/blob/master/skills/5.%20Cyberphysical%20and%20Safety-Critical%20Systems/28%20-%20State%20Models/images/skill28img2.jpg" width="400" >

## Modules, Tools, Source Used Including Attribution
- UDP
- LEDs
- Server/Client
- ESP Wifi Connection
- [Skill 28 demo](https://youtu.be/ImSPWiK8cZY)

## Supporting Artifacts and References
- [UDP Server/Client Implementation](https://www.geeksforgeeks.org/udp-server-client-implementation-c/)
- [Election Buill Algorithm](https://www.geeksforgeeks.org/election-algorithm-and-distributed-processing/#:~:text=The%20Bully%20Algorithm%20%E2%80%93,assumed%20that%20coordinator%20has%20failed.)

-----
