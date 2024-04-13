/*
  ==============================================================================

    SoftClipArcTan.h
    Created: 9 Apr 2024 9:40:55am
    Author:  Alek Weidman

  ==============================================================================
*/

#pragma once
#include "DistortionProcessor.h"

class SoftClipArcTan : public DistortionProcessor {
    
public:
    
    void setDistParam1(float inputAlpha) override { // Set the alpha value for the processSoftClipArcTan function
        alpha = (inputAlpha/10); // 1 - 100 in the plugin, Makes it 1 - 10 internally
    }
    
    float processSample(float x, const int c) override;
 
private:
    
    float alpha = 1.0f; // Between 1 and 10

    float wet = 0.f; // helps us get a balance between two parts, the unprocessed and proccessed signals (0 - 1)
    
    float dry = 1.f;
  
};
