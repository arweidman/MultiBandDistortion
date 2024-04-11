/*
  ==============================================================================

    HardClip.cpp
    Created: 9 Apr 2024 9:41:20am
    Author:  Alek Weidman

  ==============================================================================
*/

#include "HardClip.h"

float HardClip::processSample(float x, const int c) {
        x = x * drive;
        if (x >= thresh) { // If we go above our threshold...
            x = thresh; // then put a hard stop to any values going above it
        }
        else if(x <= -thresh){ // If we go below our negative threshold...
            x = -thresh; // then put a hard stop to any values going below it
        }
        else {
            x = x; // If unaffected by the threshold, return value as is
        }
    return x;
}
