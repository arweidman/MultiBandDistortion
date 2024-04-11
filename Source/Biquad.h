/*
  ==============================================================================

    Biquad.h
    Created: 9 Apr 2024 9:28:17am
    Author:  Alek Weidman

  ==============================================================================
*/

#pragma once

#include <cmath>

class Biquad
{
public:
    enum FilterType
    {
        LPF,
        HPF,
        BPF1,
        BPF2,
        NOTCH,
        LSHELF,
        HSHELF,
        PEAK,
        APF
    };

    Biquad() {};
    Biquad(FilterType filterType, float Q) : filterType(filterType), Q(Q) {};
    ~Biquad() {};

    // Functions for Biquad Filter
    void processBuffer(float * samples, const int numSamples, const int channel);
        
    float processSample(float x, int channel);

    void setFs(float Fs);
    float getFs();

    void setFreq(float freq);
    float getFreq();

    void setQ(float Q);
    float getQ();

    void setAmpdB(float ampdB);
    float getAmpdB();

    void setFilterType (FilterType filterTypeParam)
    {
        this->filterType = filterTypeParam;
    }

private:
    FilterType filterType = LPF;

    float Fs = 48000.0f; // Sampling Rate

    // Variables for User to Modify Filter
    float freq = 20.0f; // frequency in Hz
    float Q = 0.707f; // Q => [0.1 - 10]
    float ampdB = 0.0f; // Amplitude on dB scale

    // Intermediate Variables
    float w0 = (float) (2.0 * M_PI) * freq / Fs; // Normalize frequency
    float alpha = std::sin(w0) / (2.0f * Q); // Bandwidth/slope/resonance parameter
    float A = std::pow(10.0f, ampdB / 40.0f); // Linear amplitude

    // Variables for Biquad Implementation
    // 2 channels - L,R : Up to 2nd Order
    float x1[2] = { 0.0f }; // 1 sample of delay feedforward
    float x2[2] = { 0.0f }; // 2 samples of delay feedforward
    float y1[2] = { 0.0f }; // 1 sample of delay feedback
    float y2[2] = { 0.0f }; // 2 samples of delay feedback

    // Filter coefficients
    float b0 = 1.0f; // initialized to pass signal
    float b1 = 0.0f; // without filtering
    float b2 = 0.0f;
    float a0 = 1.0f;
    float a1 = 0.0f;
    float a2 = 0.0f;

    void updateCoefficients();
};
