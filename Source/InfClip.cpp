/*
  ==============================================================================

    InfClip.cpp
    Created: 9 Apr 2024 9:41:35am
    Author:  Alek Weidman

  ==============================================================================
*/

#include "InfClip.h"

float InfClip::processSample(float x, const int c) {
    
    float y = x;
    
    if (y > 0) {
        y = 1;
    }
    else {
        y = -1;
    }
    
    return (dry * x) - (wet * y);
    
}
