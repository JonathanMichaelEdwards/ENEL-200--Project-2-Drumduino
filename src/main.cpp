// ****************************************************************************
// File:     main.c                                                           *
// Authors:  Jonathan Edwards, Josh Hogan & William Herewini                  *
// Date:     12/09/2019                                                       *
// Descr:    Code for the drum duino                                          *
// ****************************************************************************


#include <Arduino.h>
#include "Acceleration.h"
#include "uart.h"
#include "drum.h"

/*
 * Sets up everything.
 */
void setup()
{
    accInit();
    uartInit();
    setupPlayback();

    pinMode(LEDPIN, OUTPUT);
    digitalWrite(LEDPIN, HIGH);
}

/*
int16_t storeDirZ[15] = {0};
int16_t storeMagY[15] = {0};
int16_t storeMagZ[15] = {0};
int16_t minStoreMagZ[15] = {0};
int16_t maxDirZ = 0;
int16_t maxMagY = 0;
int16_t maxMagZ = 0;
int16_t minMagZ = 0;
int16_t prvMagX = 0;
int16_t gyroOffset = 0;
int index = 0;
bool checkSound = false;
bool gyroStable = false;
// */

/*
 *  Store a new acceleration value at the
 *  index of the array for every time this
 *  function is called.
 *  # note:
 *    - This functon only loops through once
 *      for everytime it is called (due to the
 *      break in the loop).
 */

/*
void storeAcc(int16_t dirZ, int16_t magY, int16_t magZ, int16_t dirX)
{
    while (index < 10) {
        checkSound = false;
        prvMagX = dirX;
        storeDirZ[index] = dirZ;
        storeMagY[index] = magY;
        storeMagZ[index] = magZ;

        if (maxDirZ < dirZ) maxDirZ = storeDirZ[index];
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
        // if (maxMagZ <= -70 && range) {
            if (maxDirZ  <= -100 && gyro < 0 && range) {
                // tone(12, 300, 30);
                tone(12, freq, 50);
                checkSound = false;
            // }
        }
    }
}//*/


boolean playingDrum = false;
int16_t totalgyro = 0;

void loop() 
{
    accRun();
    
    Direction dirAcc = dirAccel();
    Gyro gyroAcc = gyroAccel();
    Magnitude magAcc = magAccel();


    //storeAcc(dirAcc.accZ, magAcc.accY, magAcc.accZ, dirAcc.accX);

    // printData(dirAcc, gyroAcc, magAcc);
    
    // bool detectMagY = (5 <= magAcc.accY && magAcc.accY <= 45);  // Y Magnitude offset (up and down playing motion region)

    // if (dirAcc.accZ <= -15 && !playingDrum && detectMagY) {
    //     int note = 1;
    //     // if (dirAcc.accX > 10) {
    //     //     note = 2;
    //     // } else if (dirAcc.accX < -10) {
    //     //     note = 3;
    //     // }
    //     // printf("YESSSS %d\n", note);
    //     //tone(12, 100 * note, 50);
    //     startPlayback(note);
    //     playingDrum = true;
    // } 

    // if (dirAcc.accZ >= 2 && playingDrum) {
    //     playingDrum = false;
    // }

    digitalWrite(LEDPIN, HIGH);
    delay(1000);
    digitalWrite(LEDPIN, LOW);
    
    startPlayback(3);           //this is how you play a sound between 0-3 although i need to change them
    delay(250);
    startPlayback(3);
    delay(500);
    startPlayback(3);
    delay(250);
    startPlayback(1);

    


    /*
    while (!gyroStable && gyroAcc.accX != 0) {
        // if (gyroAcc.accX < 0) totalgyro = -1;
        // else totalgyro = 1;
        totalgyro = gyroAcc.accX;
        printf("%d\n", gyroAcc.accX);
        gyroStable = true;
    }

    // while (!gyroStable) {
    if (totalgyro > 0 && totalgyro < 400) {
        totalgyro -= 1;
    } else if (totalgyro < 0 && totalgyro > -400) {
        totalgyro += 1;
    }
    if (totalgyro <= -400) totalgyro += gyroAcc.accX;
    else if (totalgyro >= 400) totalgyro -= gyroAcc.accX;
    //     if (-100 <= totalgyro <= 100) gyroStable = false;
    // }

    // printf("%d\n", totalgyro);
    // totalgyro += gyroAcc.accX;

    // if (gyroAcc.accX > 0) totalgyro += gyroAcc.accX;
    // else if (gyroAcc.accX <= 0) totalgyro -= gyroAcc.accX;

    // totalgyro = gyroAcc.accX;

    // printf("%d %d\n", prvMagX, dirAcc.accX);
    // printf("%d\n", 65 <= magAcc.accX && magAcc.accX < 80);
    // playNote(true, 100, gyroAcc.accX);                       // Play center
    // playNote(prvMagX >= dirAcc.accX+20, 200, gyroAcc.accX);  // Play left
    // playNote(20 <= magAcc.accX && magAcc.accX < 50, 300, gyroAcc.accX);
       
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
            storeDirZ[j] = storeMagZ[j] = storeMagY[j] = 0; 
            // minStoreMagZ[j] = magAcc.accZ;
        }
        maxDirZ = maxMagY = index = 0; 
        maxMagZ = magAcc.accZ;
    } else index++;

    // find the max

    // if (dirAcc.accY < 0) dirAcc.accY *= -1;

    // printf("%d\n", magAcc.accX);
    // run(dirAcc.accY, gyroAcc.accZ);
    // intensity level is measured in Newtons (F = M * A)
    
    
    // if (dirAcc.accX > 15 || dirAcc.accX < -15 && magAcc.accZ >= -80) puts("Play Sound for X"); 
    // if ((maxDirY > 15) && maxMagZ <= -80) puts("nothing");
   
    // if (dirAcc.accZ > 15 || dirAcc.accZ < -15) puts("Play Z"); 
    // puts("N"); 
    // */
} 
