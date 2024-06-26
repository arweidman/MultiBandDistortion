/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Biquad.h"
#include "DistortionProcessor.h"

//==============================================================================
/**
*/
class MultiBandDistortionAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    MultiBandDistortionAudioProcessor();
    ~MultiBandDistortionAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    juce::AudioProcessorValueTreeState apvts; // Creating the instance of our value tree state class
       
    // Variables below are communicating between the front end and backend, where the components on the front end update these varibles, which are then sent to the backend (DSP algorithms). They need to be public so we can access them outside of our class.
    float filterFrequencyCrossover1 = 650.f;
    float filterFrequencyCrossover2 = 4000.f;
    
    float WetBand1 = 1.f;
    float smoothedWet1 = 0.f;
    float WetBand2 = 1.f;
    float smoothedWet2 = 0.f;
    float WetBand3 = 1.f;
    float smoothedWet3 = 0.f;
    
    float distParam1Band1 = 0.f;
    float smoothedDistP1B1 = 0.f;
    float distParam2Band1 = 0.f;
    float smoothedDistP2B1 = 0.f;
    float distParam1Band2 = 0.f;
    float smoothedDistP1B2[2] = {0.f};
    float distParam2Band2 = 0.f;
    float smoothedDistP2B2[2] = {0.f};
    float distParam1Band3 = 0.f;
    float smoothedDistP1B3[2] = {0.f};
    float distParam2Band3 = 0.f;
    float smoothedDistP2B3[2] = {0.f};
    
    float inputGain = 1.f;
    float smoothedInputGain[2] = {0.f};
    float outputGain = 1.f;
    float smoothedOutputGain[2] = {0.f};
    
    bool bypass = false;
    bool band1Solo = false;
    bool band2Solo = false;
    bool band3Solo = false;
    
    float alpha = 0.999f;
    const float respTime = 0.1f; // smoothing response time in seconds
    
    // This will take a band number (the low, mid, or high band) and apply a new effect selection to it
    void setDistType(int bandNum, int selection);

private:
    
    juce::AudioProcessorValueTreeState::ParameterLayout createParams();
    
    int ParameterVersionHint = 1;
    
    // how many slots there are to apply distortion (3 bands, 3 distortion slots)
    static const int NUM_DISTORTION = 3;
    
    // a pointer than can redirect to different things
    DistortionProcessor * effect[NUM_DISTORTION];
    
    // This will be the first selection band (Low frequencies)
    Biquad lowBandLowPass;
    Biquad lowBandLowPassDup; // Dup means duplicate
    
    // This will be the second selection band (Mid frequencies)
    Biquad midBandLowPass;
    Biquad midBandLowPassDup;
    Biquad midBandHighPass;
    Biquad midBandHighPassDup;
    
    // This will be the third selection band (High frequencies)
    Biquad highBandHighPass;
    Biquad highBandHighPassDup;
    
    double Fs = 48000;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MultiBandDistortionAudioProcessor)
};
