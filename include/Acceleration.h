// ****************************************************************************
// File:     Acceleration.h                                                   *
// Authors:  Jonathan Edwards                                                 *
// Date:     12/09/2019                                                       *
// Descr:    Accelerometer.h determines the usibility                         *
// ****************************************************************************


/*  Connecting the MPU 9250/Accelerometer
    ********** Pin Layout **********
    Accelerometer    -        Arduino       
    VCC              ->       5V
    GND              ->       GND
    SCL              ->       A5
    SDA              ->       A4

    # note:
        - Other pins are NOT CONNECTED
*/


#ifndef ACCELERATION_H
#define ACCELERATION_H

extern "C" void uartInit(void);

typedef struct DirAcc {
    int accX;
    int accY;
    int accZ;
} Direction;

typedef struct GyroAcc {
    int accX;
    int accY;
    int accZ;
} Gyro;

typedef struct MagAcc {
    int accX;
    int accY;
    int accZ;
} Magnitude;

// Setup accelerometer functions
void accInit(void);  // (put me in Setup)
void accRun(void);   // (put me in loop to update reader)

// Accelerometer Functions
Direction dirAccel(void);
Gyro gyroAccel(void);
Magnitude magAccel(void);
void printData(Direction, Gyro, Magnitude);


#endif  // ACCELERATION_H
