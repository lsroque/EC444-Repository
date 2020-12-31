# Code Readme

In skill15.c, we were able to use GPIO34 (or pin A2) as it supports ADC1 and is a non-output-capable pin. The attenuation was set to 2.5 in order to stay within the desired range (20-150cm). The equation used in the code, is derived from the graphing of the data on the websites linked below. The skill required us to display the distance in meters and every 2s. Thus, I divided the given equation by 1000 to convert to meters and added a vTaskDelay of 2000ms.

#### Sources
- [IR Distance Equation](http://home.roboticlab.eu/en/examples/sensor/ir_distance)
- [More on IR Distance Equation](https://www.limulo.net/website/coding/physical-computing/sharp-linearization.html)
