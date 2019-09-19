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


int16_t storeMagX[30] = {0};
int16_t maxMagX = 0;
int16_t minMagX = 0;
int16_t addLimit = 0;
int16_t offsetMagX = 0;
int16_t offsetMagY = 0;
uint8_t pullDownValue = 0;
bool playingDrum = false;
bool ready = false;
int index = 0;


/*
 * Sets up everything.
 */
void setup()
{   
    accInit();
    uartInit();
    setupPlayback();

    // // puts("Please callibrate the accelerometer by rotating it 360 degrees. Hit the button when done.");
    // while (1) {
    //     if (PINB & BIT(4)) {  // pull down resistor
    //         puts("Callibration Succesful, Getting ready to play, please wait...");
    //         break;
    //     }
    // }

    PORTB &= ~BIT(3) | BIT(4) | ~BIT(5);
    _delay_ms(100);  // wait for ports to register
    DDRB |= BIT(3) | BIT(5);
}


void blink(uint16_t delay)
{
    _delay_ms(delay);
    PORTB ^= BIT(5);
}


// /*
//  *  Store a new acceleration value at the
//  *  index of the array for every time this
//  *  function is called.
//  *  # note:
//  *    - This functon only loops through once
//  *      for everytime it is called (due to the
//  *      break in the loop).
//  */
// void storeAcc(int16_t dirX)
// {
//     if (index < 30) {
//         storeMagX[index] = dirX;

//         if (dirX >= 0) {
//             if (maxMagX <= dirX) maxMagX = storeMagX[index];
//         } else {
//             if (minMagX >= dirX) minMagX = storeMagX[index];
//         }
//     }
// }


void loop() 
{
    accRun();
    
    Direction dirAcc = dirAccel();
    Gyro gyroAcc = gyroAccel();
    Magnitude magAcc = magAccel();


    if (!ready) {
        if ((PINB & BIT(4)) == BIT(4)) ready = true;
        blink(100);
        offsetMagX = magAcc.accX;
        offsetMagY = magAcc.accY;   
  
        if (ready) {
            for (int i = 0; i < 5; i++) blink(400);
            PORTB &= ~BIT(5);
        }

        // addLimit = abs((minMagX + maxMagX) / 2);
    } else {


        //storeAcc(dirAcc.accZ, magAcc.accY, magAcc.accZ, dirAcc.accX);

        // printData(dirAcc, gyroAcc, magAcc);
        
        bool detectMagY = (-80 <= magAcc.accY-offsetMagY && magAcc.accY-offsetMagY <= 200);  // Y Magnitude offset (up and down playing motion region)

        if (dirAcc.accZ <= -15 && !playingDrum && detectMagY) {
            int note = 1;

            if (magAcc.accX-offsetMagX < -150) note = 3;
            else if (magAcc.accX-offsetMagX > 150) note = 1;
            else note = 2;

            startPlayback(note);
            playingDrum = true;
        } 

        if (dirAcc.accZ >= 2 && playingDrum) {
            playingDrum = false;
        }



    // testSound();

    // if (totalMag < 0) totalMag = magAcc.accX - offsetMag;// - addLimit;
    // else if (magAcc.accX > 0) totalMag = magAcc.accX - offsetMag;// + addLimit;
    // else totalMag = magAcc.accX - offsetMag;
    }
    

    // magAcc.accX = magAcc.accX - offsetMag;

    // totalMag = magAcc.accX - offsetMag;


    // printf("total    %d  %d %d\n", magAcc.accX, offsetMag, totalMag);
    // storeAcc(magAcc.accX);

    // for (int i = 0; i < 30; i++) printf("%d ", storeMagX[i]);
    // printf("max and min    %d %d\n", maxMagX, minMagX);

    // storeAcc(magAcc.accX);

    // for (int i = 0; i < 30; i++) printf("%d ", storeMagX[i]);

    // printf("max and min    %d %d\n", maxMagX, minMagX);
// accX = magAcc.accX - offsetMag;

    // totalMag = magAcc.accX - offsetMag;




    // storeAcc(magAcc.accX);

    // for (int i = 0; i < 30; i++) printf("%d ", storeMagX[i]);

    // printf("max and min    %d %d\n", maxMagX, minMagX);


    // if (index == 30) index = 0;
    // else index

    // if (index == 30) index = 0;
    // else index++;




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
