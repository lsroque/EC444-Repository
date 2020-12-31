#  Skill 29 - Security in Connected Systems

Author: Lesbeth Roque

Date: 2020-11-10
-----

## Summary
Security issues can prove very harmful for any system we are creating. A person could take control of devices, falsify data, interrupt flow of data, etc.  The purpose of this assignment is to sketch an overall flow of information to drive a car with remote control, identify weaknesses in the system, identify 5 ways a bad guy could attack this system, and describe ways to mitigate these issues.

#### Questions
1. Sketch the overall flow of information to drive a car with remote control over the Internet
  <p align="left">
<img src="https://github.com/lsroque/EC444-Repository/blob/master/skills/5.%20Cyberphysical%20and%20Safety-Critical%20Systems/29%20-%20Security%20Issues/images/29_Flowchart.jpg" alt="Flowchart">
</p>
<p>
    <em>Flowchart to drive a car with remote control</em>
</p>

2. Identify weaknesses in your overall system (client, local network, internet, server, node.js, ESP32) with respect to security compromise. 
>
> Weaknesses in the system are based on the local network, internet, server, node.js and ESP32. In a person’s local network, it may be public or lack the protection necessary to maintain control/ transfer data during a security attack. Node.js itself poses a security risk and is open to attacks unless security measures are implemented. Last, the ESP32 connected over wifi can lead to more vulnerabilities. The ESP could be sent data that leads it to disconnect or crash from the system.
>
3. What ways can a bad guy attack your specific system? – list at least five and be very specific
> 
> - As explained by Professor Little, network intrusion can occur when a user is able to get access behind a firewall, especially when protections are lower. If the wifi connection occurs over a LAN (Local Area Network), it is likely that the speed is faster and more secure in comparison to WAN (Wide Area Network). Once accessed, the attacker can have control over the system.
> - Denial of Service can occur when bots launch an overwhelming traffic on a service/ system and make it unusable. This could lead to the flooding of unnecessary data to the ports and lead the user to lose their remote control over the car on a webpage. 
> - Spoilers are a deliberate attack on protocols. This can lead to sending bad requests to a server, thus not allowing the server to perform the tasks it needs.
> - Eavesdroppers and data interception could occur if a person gets in close proximity to and taps in to the network the car is connected to. This data interception can occur before the data is transferred to the sensor or before the data is transferred to the motor, not allowing the car to move and let the server know if the car has moved.
> - Endpoint attacks pick on the system and target the entry points into a network, such as targeting the sensor (accelerometer?), motor, or even the computer. Then, the bad guy is able to interpret the data held by the device picked at.
> 
4. Describe ways that you can overcome these attacks – in what ways can you mitigate these issues?
> - Placing the system to a more secure network, such as a VPN network, or adding protection to decrease the bad guy’s ability to get into the system’s network. (1st bullet point)
> - Adding content filtering to deal with overwhelming traffic and bad requests. (2nd & 3rd bullets) 
> - Building firewalls and identifying all users. (4th bullet)
> - Encrypt data so that the data ‘stolen’ cannot be understood easily by the attacker and maybe they'll move on to easier things to attack. :) (5th bullet)

## Sketches and Photos
- Flowchart shown in question 1

## Modules, Tools, Source Used Including Attribution

## Supporting Artifacts
- [Prevent DOS attacks](https://phoenixnap.com/blog/prevent-ddos-attacks)
- [Eavesdropping attacks](https://www.investopedia.com/terms/e/eavesdropping-attack.asp)
- [Prevent endpoint attacks](https://www.jolera.com/4-things-you-can-do-to-protect-your-organization-from-endpoint-attacks/)



-----
