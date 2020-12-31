#  Skill 28 - Leader Elections

Author: Nnenna Eze and Lesbeth Roque

Date: 2020-11-09
-----

## Summary
The code for this skill is based on the Bully Algorithm, in which a leader is elected based on minimum ID, and a new election is started if the leader is disconnected, or if a device with a lower ID joins the server. This skill, unlike skill 25, used UDP to communicate between ESPs. LEDs were also incorporated into the code to show which state an ESP was in. For instance, in my specific code, a red LED represents the fact that an election is happening, and a green LED signifies that a specific ESP is the current leader. 

## Sketches and Photos
<img src="https://user-images.githubusercontent.com/44929220/99131481-40cd5580-25e1-11eb-8ea7-ed97be879877.jpg" width="400" >

<img src="https://user-images.githubusercontent.com/44929220/99131485-42971900-25e1-11eb-8d85-6f9ade76081b.jpg" width="400" >

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
