// ****************************************************************************
// File:     Acceleration.c                                                   *
// Authors:  Jonathan Edwards                                                 *
// Date:     ...                                                              *
// Descr:    ...                                                              *
// ****************************************************************************


/*  Connecting the MPU 9250/Accelerometer
    ********** Pin Layout **********
    Accelerometer    -        Arduino       
    VCC              ->       5V
    GND              ->       GND
    SCL              ->       SCL (top left corner)
    SDA              ->       SDA (top left corner + 1)

    # note:
        - Other pins are NOT CONNECTED
*/


#ifndef ACCELERATION_H
#define ACCELERATION_H


typedef struct DirAcc {
    float accX;
    float accY;
    float accZ;
} Direction;

typedef struct GyroAcc {
    float accX;
    float accY;
    float accZ;
} Gyro;

typedef struct MagAcc {
    float accX;
    float accY;
    float accZ;
} Magnitude;


Direction dirAccel(void);
Gyro gyroAccel(void);
Magnitude magAccel(void);
void printData(Direction, Gyro, Magnitude);

void accInit(void);
void runSensor(void);


#endif  // ACCELERATION_H
