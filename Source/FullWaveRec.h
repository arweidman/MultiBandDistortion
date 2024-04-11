/*
  ==============================================================================

    FullWaveRec.h
    Created: 9 Apr 2024 9:42:13am
    Author:  Alek Weidman

  ==============================================================================
*/

#pragma once
#include "DistortionProcessor.h"

class FullWaveRec : public DistortionProcessor {
    
public:
    
    float processSample(float x, const int c) override;
 
};
