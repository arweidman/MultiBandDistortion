/*
  ==============================================================================

    HalfWaveRec.cpp
    Created: 9 Apr 2024 9:42:56am
    Author:  Alek Weidman

  ==============================================================================
*/

#include "HalfWaveRec.h"

float HalfWaveRec::processSample(float x, const int c) {
    if (x < 0.f) {
        x = 0.f;
    }
    return x;
}
