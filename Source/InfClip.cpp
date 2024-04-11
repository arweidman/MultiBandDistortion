/*
  ==============================================================================

    InfClip.cpp
    Created: 9 Apr 2024 9:41:35am
    Author:  Alek Weidman

  ==============================================================================
*/

#include "InfClip.h"

float InfClip::processSample(float x, const int c) {
    if (x > 0) {
        x = 1;
    }
    else {
        x = -1;
    }
    return x;
}
