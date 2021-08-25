/*
 * TSL_MPU6050.ino
 * 
 * This is an example for the TSL_MPU6050 library.
 * 
 * This example interfaces with a MPU-6050 3-axis Accelerometer and Gyroscope
 * module using I2C to communicate.
 * 
 * Written by Saige Martinez for CNM Ingenuity's Technology Solutions Lab.
 */

#include "TSL_MPU6050.h"

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
