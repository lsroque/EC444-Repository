# Code Readme
In skill 13, we were required to show the thermistors temperatures in celcius. This equation was found on the adafruit's website on using a thermistor. Moreover, in order to get these temperature values within the required range, the attenuation factor was changed to 2.5 was used. Last, the GPIO34 (A2) pin was used due to the fact it is an analog input and a non-output-capable pin. This is ideal as it used ADC#1. In order to sample every 2s, a vTaskDelay of 2000ms was used.

#### Sources
- [Link to Adafruit Thermister Equation](https://learn.adafruit.com/thermistor/using-a-thermistor)

