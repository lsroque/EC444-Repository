# Code Readme

This program, skill09.c, builds off of the servo code provided in the github repo: https://github.com/espressif/esp-idf/tree/master/examples/peripherals/mcpwm/. <br/>

Segments of the already provided code were modified to make the servo run through its full range: from -90 to +90 or 180 degrees. In order to make the servo run 180 degrees, I modified the servo's minimum pulsewidth and maximum pulsewidth. In my program, the minimum pulsewidth was changed to 500 and the maximum pulsewidth changed to 2300.
