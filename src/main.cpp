// ****************************************************************************
// File:     main.c                                                           *
// Authors:  Jonathan Edwards, Josh Hogan & William Herewini                  *
// Date:     12/09/2019                                                       *
// Descr:    Code for the drum duino                                          *
// ****************************************************************************


#include <Arduino.h>
#include "Acceleration.h"
#include "uart.h"


/*
 * Sets up everything.
 */
void setup()
{
    accInit();
    uartInit();
    pinMode(12, 1);
}


int16_t store[15] = {0};
int16_t maxDirY = 0;
int index = 0;


/*
 *  Store a new acceleration value at the
 *  index of the array for every time this
 *  function is called.
 *  # note:
 *    - This functon only loops through once
 *      for everytime it is called (due to break)
 */
void storeValues(int index, int16_t acc)
{
    while (index < 15) {
        store[index] = acc;
        if (maxDirY < acc) maxDirY = store[index];
        break;
    }
}


void loop() 
{
    accRun();
    Direction dirAcc = dirAccel();
    Gyro gyroAcc = gyroAccel();
    Magnitude magAcc = magAccel();

    
    storeValues(index, dirAcc.accY);
       

    printf("y=%d z=%d\n", magAcc.accY, magAcc.accZ);
    // printf("=%d\n", magAcc.accX);

    if (index == 15) {
        if (maxDirY >= 15 && magAcc.accZ >= -90 && magAcc.accY <= -20) tone(12, 300, 10);
        for (int j  = 0; j < 15; j++) store[j] = 0; 
        maxDirY = index = 0;
    } else index++;
    

    
    // find the max

    // if (dirAcc.accY < 0) dirAcc.accY *= -1;

    // printf("%d %d %d\n", dirAcc.accY, magAcc.accZ, gyroAcc.accY);
    // run(dirAcc.accY, gyroAcc.accZ);
    // intensity level is measured in Newtons (F = M * A)
    // printData(dirAcc, gyroAcc, magAcc);
    
    // if (dirAcc.accX > 15 || dirAcc.accX < -15 && magAcc.accZ >= -80) puts("Play Sound for X"); 
    // if ((maxDirY > 15) && maxMagZ <= -80) puts("nothing");
   
    // if (dirAcc.accZ > 15 || dirAcc.accZ < -15) puts("Play Z"); 
    // puts("N"); 
} 