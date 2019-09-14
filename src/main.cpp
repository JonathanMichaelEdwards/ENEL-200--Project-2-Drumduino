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


int16_t storeDirY[15] = {0};
int16_t storeMagY[15] = {0};
int16_t storeMagZ[15] = {0};
int16_t minStoreMagZ[15] = {0};
int16_t maxDirY = 0;
int16_t maxMagY = 0;
int16_t maxMagZ = 0;
int16_t minMagZ = 0;
int index = 0;
bool checkSound = false;
bool up = true;


/*
 *  Store a new acceleration value at the
 *  index of the array for every time this
 *  function is called.
 *  # note:
 *    - This functon only loops through once
 *      for everytime it is called (due to the
 *      break in the loop).
 */
void storeAcc(int16_t dirY, int16_t magY, int16_t magZ)
{
    while (index < 10) {
        checkSound = false;
        storeDirY[index] = dirY;
        storeMagY[index] = magY;
        storeMagZ[index] = magZ;

        if (maxDirY < dirY) maxDirY = storeDirY[index];
        if (maxMagY > magY) maxMagY = storeMagY[index];
        if (maxMagZ < magZ) maxMagZ = storeMagZ[index];
        // if (!(minMagZ < magZ)) minMagZ = minStoreMagZ[index];
        break;
    }
    checkSound = true;  // limit found
}


void playNote(bool range, int freq, int16_t gyro)
{
    if (checkSound) {
        if (maxMagZ >= -100 && range) {
            if (maxDirY >= 15  && gyro < 0) {
                // tone(12, 300, 30);
                tone(12, freq, 50);
                checkSound = false;
            }
        }
    }
}


void loop() 
{
    accRun();
    
    Direction dirAcc = dirAccel();
    Gyro gyroAcc = gyroAccel();
    Magnitude magAcc = magAccel();


    storeAcc(dirAcc.accY, magAcc.accY, magAcc.accZ);

    // printf("%d\n", 65 <= magAcc.accX && magAcc.accX < 80);
    playNote(80 <= magAcc.accX && magAcc.accX <= 110, 100, gyroAcc.accX);
    playNote(50 <= magAcc.accX && magAcc.accX < 80, 200, gyroAcc.accX);
    playNote(20 <= magAcc.accX && magAcc.accX < 50, 300, gyroAcc.accX);
       
    // printf("y=%d z=%d\n", maxMagZ, magAcc.accZ);
    // printf("%d %d %d %d\n", magAcc.accX, magAcc.accY, gyroAcc.accX, gyroAcc.accY);

    // printf("dy=%d y=%d z=%d     mdy=%d   my=%d   z=%d  %d\n", dirAcc.accY, magAcc.accY, magAcc.accZ, maxDirY, maxMagY, maxMagZ, minMagZ);

    // Allow accelerometor to detect sound again
    // if (index == 9) checkSound = true;


   

    if (index == 10) {
        // printf("dy= %d y=%d z=%d\n", dirAcc.accY, magAcc.accY, magAcc.accZ);
        // puts("yes");
        // while (checkSound) {
        //     checkSound = false;
            // puts("play");
            // tone(12, 300, 10);
        // if (maxMagY >= -40 && maxMagY >= -90) {
        //     if (maxDirY >= 15 && maxMagZ <= -20) tone(12, 300, 10);
        // }
        // if (maxDirY >= 15 && maxMagY >= -90 && maxMagZ <= -20) tone(12, 300, 30);
            // pinMode(12, 0);
        // }
        //  && minMagZ < -40
        for (int j  = 0; j < 10; j++) {
            storeDirY[j] = storeMagZ[j] = storeMagY[j] = 0; 
            // minStoreMagZ[j] = magAcc.accZ;
        }
        maxDirY = maxMagY = index = 0; 
        maxMagZ = magAcc.accZ;
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