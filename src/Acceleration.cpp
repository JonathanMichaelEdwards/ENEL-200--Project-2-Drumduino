// ****************************************************************************
// File:     Acceleration.c                                                   *
// Authors:  Jonathan Edwards                                                 *
// Date:     ...                                                              *
// Descr:    ...                                                              *
// ****************************************************************************


#include "Acceleration.h"
#include "MPU_9250.h"

#define SENSOR_ADDRESS 0x68

MPU9250 IMU(Wire, SENSOR_ADDRESS);  // Using MPU9250 sensor lib


Direction dirAccel()
{
    Direction dir = {0};

    dir.accX = IMU.getAccelX_mss();
    dir.accY = IMU.getAccelY_mss();
    dir.accZ = IMU.getAccelZ_mss();

    return dir;
}


Gyro gyroAccel()
{
    Gyro dir = {0};

    dir.accX = IMU.getGyroX_rads();
    dir.accY = IMU.getGyroY_rads();
    dir.accZ = IMU.getGyroZ_rads();

    return dir;
}


Magnitude magAccel()
{
    Magnitude dir = {0};

    dir.accX = IMU.getMagX_uT();
    dir.accY = IMU.getMagY_uT();
    dir.accZ = IMU.getMagZ_uT();

    return dir;
}


void runSensor()
{
    IMU.readSensor();  // read the sensor
} 


void accInit()
{
    IMU.begin();
}


void printData(Direction dirAcc, Gyro gyroAcc, Magnitude magAcc)
{
    // display the data
    Serial.print("AccelX: ");
    Serial.print(dirAcc.accX, 6);
    Serial.print("	");
    Serial.print("AccelY: ");  
    Serial.print(dirAcc.accY, 6);
    Serial.print("	");
    Serial.print("AccelZ: ");  
    Serial.println(dirAcc.accZ, 6);

    Serial.print("GyroX: ");
    Serial.print(gyroAcc.accX, 6);
    Serial.print("	");
    Serial.print("GyroY: ");  
    Serial.print(gyroAcc.accY, 6);
    Serial.print("	");
    Serial.print("GyroZ: ");  
    Serial.println(gyroAcc.accZ, 6);

    Serial.print("MagX: ");  
    Serial.print(magAcc.accX, 6);
    Serial.print("	");  
    Serial.print("MagY: ");
    Serial.print(magAcc.accY, 6);
    Serial.print("	");
    Serial.print("MagZ: ");  
    Serial.println(magAcc.accZ, 6);
    
    Serial.print("Temperature in C: ");
    Serial.println(IMU.getTemperature_C(), 6);
    Serial.println();

    delay(500);
}