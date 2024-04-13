/*
  ==============================================================================

    SoftClipCubic.cpp
    Created: 9 Apr 2024 9:40:45am
    Author:  Alek Weidman

  ==============================================================================
*/

#include "SoftClipCubic.h"

float SoftClipCubic::processSample(float x, const int c) {
    
    float y = x - (1/3 * pow(x,3));
    
    return (dry * x) - (wet * y);
    
}
