// ****************************************************************************
// File:     Acceleration.c                                                   *
// Authors:  Jonathan Edwards                                                 *
// Date:     12/09/2019                                                       *
// Descr:    Accelerometer setup                                              *
// ****************************************************************************


#include "Acceleration.h"
#include "MPU_9250.h"
#include "uart.h"

#define SENSOR_ADDRESS 0x68


MPU9250 IMU(Wire, SENSOR_ADDRESS);  // Using MPU9250 sensor lib


/*
 * Getting I2C data from the accelerometer.
 * # note: sometimes X and Y directions are flipped due to board.
 */
Direction dirAccel()
{
    Direction dir = {0};

    dir.accX = (int16_t)IMU.getAccelY_mss();
    dir.accY = (int16_t)IMU.getAccelX_mss();
    dir.accZ = (int16_t)IMU.getAccelZ_mss();

    return dir;
}

Gyro gyroAccel()
{
    Gyro dir = {0};

    dir.accX = (int16_t)(IMU.getGyroY_rads()*100);
    dir.accY = (int16_t)(IMU.getGyroX_rads()*100);
    dir.accZ = (int16_t)(IMU.getGyroZ_rads()*100);

    return dir;
}

Magnitude magAccel()
{
    Magnitude dir = {0};

    dir.accX = (int16_t)IMU.getMagY_uT();
    dir.accY = (int16_t)IMU.getMagX_uT();
    dir.accZ = (int16_t)IMU.getMagZ_uT();

    return dir;
}


/*
 * Initializes I2C.
 */
void accInit()
{
    // start communication
    IMU.begin();

    // setting the accelerometer full scale range to +/-8G 
    // IMU.setAccelRange(MPU9250::ACCEL_RANGE_2G);
    // IMU.calibrateAccel();

    // // setting the gyroscope full scale range to +/-500 deg/s
    // IMU.setGyroRange(MPU9250::GYRO_RANGE_500DPS);
    // // IMU.calibrateGyro();

    // // setting DLPF bandwidth to 20 Hz
    // IMU.setDlpfBandwidth(MPU9250::DLPF_BANDWIDTH_184HZ);
    // // IMU.calibrateMag();

    IMU.setSrd(9);

    float ab = 0.01; // accel bias of 0.01 m/s/s
    float as = 0.97; // accel scale factor of 0.97
    IMU.setAccelCalX(ab,as);
    
    IMU.setAccelCalY(ab,as);

    IMU.setAccelCalZ(ab,as);
}


/*
 * I2C data is ready to transmit.
 */
void accRun()
{
    IMU.readSensor();  // read the sensor
} 


/*
 * Displaying data.
 */
void printData(Direction dirAcc, Gyro gyroAcc, Magnitude magAcc)
{
    // display the data
    // printf("AccelX: %d    AccelY: %d    AccelZ: %d    ", (int16_t)dirAcc.accX, (int16_t)dirAcc.accY, (int16_t)dirAcc.accZ);
    // printf("GyroX: %d    GyroY: %d    GyroZ: %d    ", (uint16_t)gyroAcc.accX, (uint16_t)gyroAcc.accY, (uint16_t)gyroAcc.accZ);
    printf("MagX: %d    MagY: %d    MagZ: %d    \n", (uint16_t)magAcc.accX, (uint16_t)magAcc.accY, (uint16_t)magAcc.accZ);
    // printf("Temp in celsius: %d\n", (uint16_t)(IMU.getTemperature_C()));
}