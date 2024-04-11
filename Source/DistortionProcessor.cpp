/*
  ==============================================================================

    DistortionProcessor.cpp
    Created: 9 Apr 2024 9:40:12am
    Author:  Alek Weidman

  ==============================================================================
*/

#include "DistortionProcessor.h"

void DistortionProcessor::process(float * buffer, const int N, const int c) {
    for (int n = 0 ; n < N ; n++) {
        float x = buffer[n];
        float y = processSample(x, c);
        buffer[n] = (dry * x) + (wet * y); // Wet/Dry parameters applied here
    }
}
