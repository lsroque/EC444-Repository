# Code Readme

In skill14.c, we were able to use GPIO34 (or pin A2) as it supports ADC1 and is a non-output-capable pin. We changed the attenuation back to 0 in order to obtain the correct ditance values that are within the ultrasonic sensor range. Last, the equation for the distance was received from the sensor's data sheet. The skill required us to display the distance in meters and every 2s. Thus, I divided the given equation by 1000 to convert to meters and a vTaskDelay was set to 2000ms.

#### Sources
- [Ultrasonic Distance Equation](https://www.maxbotix.com/documents/HRLV-MaxSonar-EZ_Datasheet.pdf)
