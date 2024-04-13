/*
  ==============================================================================

    HardClip.h
    Created: 9 Apr 2024 9:41:20am
    Author:  Alek Weidman

  ==============================================================================
*/

#pragma once
#include "DistortionProcessor.h"

class HardClip : public DistortionProcessor {
    
public:
    
    void setDistParam1(float inputDrive) override { // set drive function
        drive = (inputDrive/10); // 1-100 in the plugin, Makes it 1 - 10 internally
    }
    
    void setDistParam2(float inputThresh) override { // set threshold function
        thresh = (inputThresh/100); // 1-100 in the plugin, Makes it 1 - 10 internally
    }
    
    float processSample(float x, const int c) override;
 
private:
    
    float drive = 1.0f; // drive: will be set between...
    
    float thresh = 1.0f; // between 0 and 1
    
    float wet = 0.f; // helps us get a balance between two parts, the unprocessed and proccessed signals (0 - 1)
    
    float dry = 1.f;
  
};
