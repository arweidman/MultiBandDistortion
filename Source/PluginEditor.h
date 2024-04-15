/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class MultiBandDistortionAudioProcessorEditor  : public juce::AudioProcessorEditor,
                                                 public juce::ComboBox::Listener, // inherit the combo listener class
                                                 public juce::Slider::Listener // inherit the slider listener class
{
public:
    MultiBandDistortionAudioProcessorEditor (MultiBandDistortionAudioProcessor&);
    ~MultiBandDistortionAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    
    // THESE WILL GET CALLED FOR ALL SLIDERS/ComboBoxes! dont need a function for each individual instance
    void sliderValueChanged(juce::Slider * slider) override; // Function for when our slider value is changed
    void comboBoxChanged(juce::ComboBox * combBox) override; // Function for when our combo box is changed

private:
    
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    MultiBandDistortionAudioProcessor& audioProcessor;
    
    juce::Slider firstCrossover; // Our parameter thats sets our first crossover frequency (between bands 1 and 2)
    juce::Slider secondCrossover; // Our parameter that sets our seceond crossover frequency (between bands 2 and 3)
    
    // Dry/Wet parameter that sets the balance between our processed signal and distorted signal
    juce::Slider firstBandDryWet;
    juce::Slider secondBandDryWet;
    juce::Slider thirdBandDryWet;
    
    // Parameters to manipulate the distortion parameters unique to each distortion type, for each distortion band
    juce::Slider firstBandDistParameter1;
    juce::Slider firstBandDistParameter2;
    juce::Slider secondBandDistParameter1;
    juce::Slider secondBandDistParameter2;
    juce::Slider thirdBandDistParameter1;
    juce::Slider thirdBandDistParameter2;

    // Our parameter that sets the type of distortion we want to add to each respective frequency band
    juce::ComboBox firstBandSelectionType;
    juce::ComboBox secondBandSelectionType;
    juce::ComboBox thirdBandSelectionType;
    
    // Standard bypass button
    juce::ToggleButton bypassButton;
    juce::ToggleButton firstBandSoloButton;
    juce::ToggleButton secondBandSoloButton;
    juce::ToggleButton thirdBandSoloButton;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MultiBandDistortionAudioProcessorEditor)
};
