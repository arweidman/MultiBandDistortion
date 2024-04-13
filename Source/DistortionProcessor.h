/*
  ==============================================================================

    DistortionProcessor.h
    Created: 9 Apr 2024 9:40:12am
    Author:  Alek Weidman

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "Biquad.h"

class DistortionProcessor : public Biquad {
    
public:
    
    virtual ~DistortionProcessor() {}; // Destructor
    
    void prepare(double sampleRate){
        Fs = sampleRate;
    }
    
    void setWet(float inputWet) { // set wet amount function
        wet = (inputWet/100); // takes a value from 1 to 100 and shrinks it down to a value between 0 - 1
        dry = 1 - wet;
    }
    
    void virtual setDistParam1(float inputDistParam1) {
        distParam1 = inputDistParam1;
    }
    
    void virtual setDistParam2(float inputDistParam2) {
        distParam2 = inputDistParam2;
    }
    
    void process(float * buffer, const int N, const int c);
    
    virtual float processSample(float x, const int c) {
        return x; // Just passes through "like a wire." The program will run this when empty is selected in the combo box
    }
    
private:
    
    double Fs = 48000.0;
    
    float wet = 0.f; // helps us get a balance between two parts, the unprocessed and proccessed signals (0 - 1)
    
    float dry = 1.f; 
    
    float distParam1 = 0.f;
    
    float distParam2 = 0.f;
};
