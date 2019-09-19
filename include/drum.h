#ifndef DRUM_H
#define DRUM_H

#include "drum.h"

#define LEDPIN 13
#define SPEAKERPIN 11    // Fixed for pin 11


void stopPlayback(void);
void setupPlayback(void);
void startPlayback(int16_t drum);
void testSound(void);

ISR(TIMER1_COMPA_vect);


#endif // DRUM_H
