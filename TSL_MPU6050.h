/*
 * TSL_MPU6050.h
 * 
 * This is Technology Solutions Lab's library for the MPU-6050 3-axis 
 * Accelerometer and Gyroscope module.
 * 
 * In this current version, only the accelerometer is engaged. Gyroscopic 
 * capability will be included at a later date.
 * 
 * Written by Saige Martinez for CNM Ingenuity's Technology Solutions Lab.
 */

#ifndef TSL_MPU6050_h
#define TSL_MPU6050_h

#include <Arduino.h>
#include <Wire.h>

class TSL_MPU6050 {
  public:
    TSL_MPU6050(int select);
    void begin();
    float getXAccel();
    float getYAccel();
    float getZAccel();
    
  private:
    int _select;
    float _sensitivity;
};

#endif
