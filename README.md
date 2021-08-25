# TSL MPU6050 Library
## Overview
This is a library for the GY-521 MPU-6050 3-Axis Accelerometer Gyroscope Sensor Module. This is an open-source library developed at CNM Ingenuity's Technology Solutions Labs. The sensor module used in the development of this library can be purchased [here](https://www.amazon.com/HiLetgo-MPU-6050-Accelerometer-Gyroscope-Converter/dp/B078SS8NQV).

![Sensor Module](https://github.com/saige-martinez/TSL-MPU6050-Library/blob/main/Assets/sensor.jpg)
## Setup
![Schematic Diagram](https://github.com/saige-martinez/TSL-MPU6050-Library/blob/main/Assets/setup.jpg)
## Example
```
TSL_MPU6050 myMPU(3);

float myXAccel, myYAccel, myZAccel; 

void setup() {
  Serial.begin(9600);
  myMPU.begin();
}

void loop() {
  myXAccel = myMPU.getXAccel();
  myYAccel = myMPU.getYAccel();
  myZAccel = myMPU.getZAccel();

  Serial.printf("X-Axis: %0.1f\tY-Axis: %0.1f\tZ-Axis: %0.1f\n", myXAccel, myYAccel, myZAccel);
  delay(1);
}
```
