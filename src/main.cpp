// ****************************************************************************
// File:     main.cpp                                                         *
// Authors:  Jonathan Edwards, Josh Hogan & William Herewini                  *
// Date:     25/09/2019                                                       *
// Descr:    Code for the drum duino                                          *
// ****************************************************************************

#include <Arduino.h>
#include "Acceleration.h"
#include "drum.h"

int16_t offsetMagX = 0;
int16_t offsetMagY = 0;
bool playingDrum = false;

void blink(uint16_t delayt)
{
    delay(delayt);
    digitalWrite(13, !digitalRead(13));
}
/*
 * Sets up everything.
 */
void setup()
{
    setupPlayback();
    testSound();
    accInit();

    //Serial.begin(9600);
    //Serial.println("Starting Drum");
    pinMode(13, OUTPUT);
    delay(50); // wait for ports to register

    for (int i = 0; i < 5; i++)
    {
        blink(100);
    }
    testSound();
    //Serial.println("Now loop");
}

/*
Runs over and over again
*/
void loop()
{
    accRun();

    Direction dirAcc = dirAccel();
    //Gyro gyroAcc = gyroAccel(); //we only use the accelerometer
    //Magnitude magAcc = magAccel();

    if (dirAcc.accZ <= -15 && !playingDrum)
    {
        int note = 1;

        if (dirAcc.accX > 7) //(magAcc.accX - offsetMagX < -150)
            note = 3;
        else if (dirAcc.accX < -7) //(magAcc.accX - offsetMagX > 150)
            note = 1;
        else
            note = 2;

        //Serial.println(note);
        startPlayback(note);
        playingDrum = true;
    }

    if (dirAcc.accZ >= 2 && playingDrum)
        playingDrum = false;
}
