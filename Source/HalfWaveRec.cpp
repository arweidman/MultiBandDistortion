/*
  ==============================================================================

    HalfWaveRec.cpp
    Created: 9 Apr 2024 9:42:56am
    Author:  Alek Weidman

  ==============================================================================
*/

#include "HalfWaveRec.h"

float HalfWaveRec::processSample(float x, const int c) {
    
    float y = x;
    
    if (y < 0.f) {
        y = 0.f;
    }
    else {
        y = y;
    }
    
    return (dry * x) - (wet * y);
    
}
