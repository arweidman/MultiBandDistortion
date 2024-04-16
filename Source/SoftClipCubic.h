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
  
};
