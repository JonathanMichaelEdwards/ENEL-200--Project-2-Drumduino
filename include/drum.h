#ifndef DRUM_H
#define DRUM_H
#include "drum_data.h"

void stopPlayback();
void setupPlayback();
void startPlayback(int drum);

ISR(TIMER1_COMPA_vect);
#endif
