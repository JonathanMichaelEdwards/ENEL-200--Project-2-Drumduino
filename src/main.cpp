// ****************************************************************************
// File:     main.c                                                           *
// Authors:  Jonathan Edwards, Josh Hogan & William Herewini                  *
// Date:     12/09/2019                                                       *
// Descr:    Code for the drum duino                                          *
// ****************************************************************************

#include <Arduino.h>
#include "Acceleration.h"
//#include "uart.h" doesn't work for my board no idea why mate
#include "drum.h"

int16_t offsetMagX = 0;
int16_t offsetMagY = 0;
bool playingDrum = false;
int index = 0;

void blink(uint16_t delayt)
{
    delay(delayt);
    //PORTB ^= BIT(5);
    digitalWrite(13, !digitalRead(13));
}
/*
 * Sets up everything.
 */
void setup()
{
    accInit();
    //uartInit();
    setupPlayback();
    testSound();
    //Serial.begin(9600);
    //Serial.println("josh is coool");

    //DDRB |= BIT(3) | BIT(5); not sure what this does will just use pinMode
    //PORTB &= ~BIT(3) | BIT(4) | ~BIT(5); ?turns all bits as high?

    pinMode(8, INPUT_PULLUP);
    pinMode(13, OUTPUT);
    
    delay(50); // wait for ports to register

    /*while (digitalRead(8) == HIGH)
    //{
        Magnitude magAcc = magAccel();

        blink(100);
        offsetMagX = magAcc.accX;
        offsetMagY = magAcc.accY;
    } //*/
    for (int i = 0; i < 5; i++)
    {
        blink(400);
    }
    //PORTB &= ~BIT(5);
    //Serial.println("Now loop");
}

void loop()
{
    accRun();

    Direction dirAcc = dirAccel();
    //Gyro gyroAcc = gyroAccel();
    Magnitude magAcc = magAccel();

    bool detectMagY = true; //(-80 <= magAcc.accY - offsetMagY && magAcc.accY - offsetMagY <= 200); // Y Magnitude offset (up and down playing motion region)

    if ((dirAcc.accZ <= -15 || dirAcc.accZ - abs(dirAcc.accX) <= -20) && !playingDrum && detectMagY)
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
