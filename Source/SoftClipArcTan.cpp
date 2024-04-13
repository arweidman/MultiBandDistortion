/*
  ==============================================================================

    SoftClipArcTan.cpp
    Created: 9 Apr 2024 9:40:55am
    Author:  Alek Weidman

  ==============================================================================
*/

#include "SoftClipArcTan.h"

float SoftClipArcTan::processSample(float x, const int c) {
    
    float y = atan(x * alpha) * 2/M_PI;
    
    return (dry * x) - (wet * y);
    
}
