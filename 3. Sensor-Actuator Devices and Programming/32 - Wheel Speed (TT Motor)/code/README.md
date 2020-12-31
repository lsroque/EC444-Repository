# Code Readme

In skill32.c, I use the optical encoder with the PWM signals and TT motots to obtain wheel speed. In order to measure the ticks, or timing the gap between pulses, I used timers as my base code. Then I was able to identify the state of the encoder based on a rising edge count. Moreover, ADC was used to read in the data from the encoder to obtain distance. Wheel speed was measured by dividing distance by time.
