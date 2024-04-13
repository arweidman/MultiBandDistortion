/*
  ==============================================================================

    HardClip.cpp
    Created: 9 Apr 2024 9:41:20am
    Author:  Alek Weidman

  ==============================================================================
*/

#include "HardClip.h"

float HardClip::processSample(float x, const int c) {
    
        float y = x * drive;
    
        if (y >= thresh) { // If we go above our threshold...
            y = thresh; // then put a hard stop to any values going above it
        }
        else if(y <= -thresh){ // If we go below our negative threshold...
            y = -thresh; // then put a hard stop to any values going below it
        }
        else {
            y = y; // If unaffected by the threshold, return value as is
        }
    
    return (dry * x) - (wet * y);
    
}
