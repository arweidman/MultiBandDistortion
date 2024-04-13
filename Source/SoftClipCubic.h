/*
  ==============================================================================

    SoftClipCubic.h
    Created: 9 Apr 2024 9:40:45am
    Author:  Alek Weidman

  ==============================================================================
*/

#pragma once
#include "DistortionProcessor.h"

class SoftClipCubic : public DistortionProcessor {
    
public:
    
    float processSample(float x, const int c) override;

private:
    
    float wet = 0.f; // helps us get a balance between two parts, the unprocessed and proccessed signals (0 - 1)
    
    float dry = 1.f;
  
};
