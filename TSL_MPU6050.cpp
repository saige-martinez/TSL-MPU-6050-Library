/*
 * TSL_MPU6050.cpp
 * 
 * This is Technology Solutions Lab's library for the MPU-6050 3-axis 
 * Accelerometer and Gyroscope module.
 * 
 * In this current version, only the accelerometer is engaged. Gyroscopic 
 * capability will be included at a later date.
 * 
 * Written by Saige Martinez for CNM Ingenuity's Technology Solutions Lab.
 */
 
#include <Arduino.h>
#include <Wire.h>
#include "TSL_MPU6050.h"

float _sensitivity;

TSL_MPU6050::TSL_MPU6050(int select) {
  /*
   * Select triggers the accelerometer self test and configure the full scale
   * of the accelerometer according to the following table:
   *        AFS_SEL | Full Scale Range | LSB Sensitivity 
   *           0    |       +- 2 g     |   16384 LSB/g
   *           1    |       +- 4 g     |   8192 LSB/g
   *           2    |       +- 8 g     |   4096 LSB/g
   *           3    |       +- 16 g    |   2048 LSB/g
   */
   
  _select = select;
    
  switch (_select) {
    case 0:
      _select = 0x00;
      _sensitivity = 16384.0;
      break;
    case 1:
      _select = 0x08;
      _sensitivity = 8192.0;
      break;
    case 2:
      _select = 0x10;
      _sensitivity = 4096.0;
      break;
    case 3:
      _select = 0x18;
      _sensitivity = 2048.0;
      break;
  }

  Wire.begin();
  Wire.beginTransmission(0x68);
  Wire.write(0x1C);
  Wire.write(_select);
  Wire.endTransmission(true);
}

void TSL_MPU6050::begin() {
  /*
   * This function configures the power mode and clock source
   * of the accelerometer with the following settings:
   *        DEVICE_RESET | False
   *        SLEEP        | False
   *        CYCLE        | False
   *        TEMP_DIS     | False
   *        CLKSEL[2:0]  | Internal 8MHz Oscillator
   *
   * The clock source can be selected according to the following
   * table:
   *        CLKSEL | Clock Source
   *          0    | Internal 8MHz oscillator
   *          1    | PLL with X axis gyroscope reference
   *          2    | PLL with Y axis gyroscope reference
   *          3    | PLL with Z axis gyroscope reference
   *          4    | PLL with external 32.768kHz reference
   *          5    | PLL with external 19.2MHz reference
   *          6    | Reserved
   *          7    | Stops the clock and keeps the time
   *               | generator in reset
   */

  Wire.begin();
  Wire.beginTransmission(0x68);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
}

float TSL_MPU6050::getXAccel() {
  /*
   * This function requests the most recent 16-bit 2's compliment
   * accelerometer values along the x-axis.
   */

  int16_t xRaw;
  float xCal;

  // Request most recent accelerometer measurements.
  Wire.beginTransmission(0x68);
  Wire.write(0x3B); // Start at 0x3B ACCEL_XOUT[15:8]
  Wire.endTransmission(false);
  Wire.requestFrom(0x68, 2, true); // Read six registers.

  // Shift bits.
  xRaw = Wire.read() << 8 | Wire.read(); // 0x3B ACCEL_XOUT[15:8] & 0x3C ACCEL_XOUT[7:0]

  // Calibrate measurements to least significant bit sensitivity.
  xCal = xRaw / _sensitivity * (-1);

  return xCal;
}

float TSL_MPU6050::getYAccel() {
  /*
   * This function requests the most recent 16-bit 2's compliment
   * accelerometer values along the y-axis.
   */

  int16_t yRaw;
  float yCal;

  // Request most recent accelerometer measurements.
  Wire.beginTransmission(0x68);
  Wire.write(0x3D); // Start at 0x3D ACCEL_YOUT[15:8]
  Wire.endTransmission(false);
  Wire.requestFrom(0x68, 2, true); // Read six registers.

  // Shift bits.
  yRaw = Wire.read() << 8 | Wire.read(); // 0x3D ACCEL_YOUT[15:8] & 0x3E ACCEL_YOUT[7:0]

  // Calibrate measurements to least significant bit sensitivity.
  yCal = yRaw / _sensitivity * (-1);

  return yCal;
}

float TSL_MPU6050::getZAccel() {
  /*
   * This function requests the most recent 16-bit 2's compliment
   * accelerometer values along the z-axis.
   */

  int16_t zRaw;
  float zCal;

  // Request most recent accelerometer measurements.
  Wire.beginTransmission(0x68);
  Wire.write(0x3F); // Start at 0x3F ACCEL_ZOUT[15:8]
  Wire.endTransmission(false);
  Wire.requestFrom(0x68, 2, true); // Read six registers.

  // Shift bits.
  zRaw = Wire.read() << 8 | Wire.read(); // 0x3F ACCEL_ZOUT[15:8] & 0x40 ACCEL_ZOUT[7:0]

  // Calibrate measurements to least significant bit sensitivity.
  zCal = zRaw / _sensitivity * (-1);

  return zCal;
}
