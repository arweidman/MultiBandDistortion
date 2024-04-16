/*
  ==============================================================================

    InfClip.h
    Created: 9 Apr 2024 9:41:35am
    Author:  Alek Weidman

  ==============================================================================
*/

#pragma once
#include "DistortionProcessor.h"

class InfClip : public DistortionProcessor {
    
public:
    
    float processSample(float x, const int c) override;
  
};
