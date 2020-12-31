# Code Readme

The program, skill10.c, uses the features of RTOS in order to schedule tasks based on priority. In this program, task 1 was prioritized first, task 2 second, and task 3 last. In the function of task 1, I reused code from skill07 (GPIO Skill) in order to count up or down in binary using LEDs. Then, in another function, task 2 was created to use a button to toggle between counting up or down. Last, in task 3, a separate function reused the code from skill 8, inorder to use the alphanumeric display to indicate the direction of the counting. This program uses global variables in order to communicate with all the fucntion tasks.

#### Sources
- [Link to Skill 7 - Use GPIOs to Drive LEDS](https://github.com/BU-EC444/Roque-Lesbeth/blob/master/skills/cluster-1/07/code/skill07.c)
- [Link to Skill 8 - Alphanumeric Display Code](https://github.com/BU-EC444/Roque-Lesbeth/blob/master/skills/cluster-1/08/code/skill08.c)
