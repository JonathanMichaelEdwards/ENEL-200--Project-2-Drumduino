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


int16_t offsetMagX = 0;
int16_t offsetMagY = 0;
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

    PORTB &= ~BIT(3) | BIT(4) | ~BIT(5);
    _delay_ms(100);  // wait for ports to register
    DDRB |= BIT(3) | BIT(5);
}


void blink(uint16_t delay)
{
    _delay_ms(delay);
    PORTB ^= BIT(5);
}


void loop() 
{
    accRun();
    
    Direction dirAcc = dirAccel();
    Gyro gyroAcc = gyroAccel();
    Magnitude magAcc = magAccel();

    if (!ready) {
        if (PINB & BIT(4)) ready = true;

        blink(100);
        offsetMagX = magAcc.accX;
        offsetMagY = magAcc.accY;   
  
        if (ready) {
            for (int i = 0; i < 5; i++) blink(400);
            PORTB &= ~BIT(5);
        }
    } else { 
        bool detectMagY = (-80 <= magAcc.accY-offsetMagY && magAcc.accY-offsetMagY <= 200);  // Y Magnitude offset (up and down playing motion region)

        if (dirAcc.accZ <= -15 && !playingDrum && detectMagY) {
            int note = 1;

            if (magAcc.accX-offsetMagX < -150) note = 3;
            else if (magAcc.accX-offsetMagX > 150) note = 1;
            else note = 2;

            startPlayback(note);
            playingDrum = true;
        } 

        if (dirAcc.accZ >= 2 && playingDrum) playingDrum = false;
    }
} 
