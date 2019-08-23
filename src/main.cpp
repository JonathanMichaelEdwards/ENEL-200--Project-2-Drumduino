// ****************************************************************************
// File:     main.c                                                           *
// Authors:  Jonathan Edwards, Josh Hogan & William Herewini                  *
// Date:     ...                                                              *
// Descr:    ...                                                              *
// ****************************************************************************


#include <Arduino.h>
#include "Acceleration.h"


void setup()
{
    Serial.begin(9600);
    accInit();
}


void loop() 
{
    runSensor();
    Direction dirAcc = dirAccel();
    Gyro gyroAcc = gyroAccel();
    Magnitude magAcc = magAccel();

    printData(dirAcc, gyroAcc, magAcc);
} 