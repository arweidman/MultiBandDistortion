/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "StandardIncludes.h"

//==============================================================================
MultiBandDistortionAudioProcessorEditor::MultiBandDistortionAudioProcessorEditor (MultiBandDistortionAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (1000, 675); // Sets the size of the the plugin window
    
    // First freq crossover slider
    firstCrossover.setBounds(250, 350, 100, 100);
//    firstCrossover.setRange(20, 20000.f, 1.f);
//    firstCrossover.setSkewFactorFromMidPoint(650.f);
//    firstCrossover.setValue(650.f);
    firstCrossover.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    firstCrossover.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 75, 25);
    firstCrossover.setTextValueSuffix(" Hz");
    addAndMakeVisible(firstCrossover);
    firstCrossover.addListener(this);
    
    // Second freq crossover slider
    secondCrossover.setBounds(650, 350, 100, 100);
//    secondCrossover.setRange(20, 20000.f, 1.f);
//    secondCrossover.setSkewFactorFromMidPoint(3500.f); // set so the middle of the knob will be 1000Hz, left will be 20 - 1000, and right will be 1000-20000
//    secondCrossover.setValue(3500.f);
    secondCrossover.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    secondCrossover.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 75, 25);
    secondCrossover.setTextValueSuffix(" Hz");
    addAndMakeVisible(secondCrossover);
    secondCrossover.addListener(this);
    
    // Dry Wet Slider for Band 1
    firstBandDryWet.setBounds(50, 475, 100, 100); // Combo Box 1 bounds: (150, 600, 100, 40)
//    firstBandDryWet.setRange(0.f, 100.f, 0.1f);
    firstBandDryWet.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    firstBandDryWet.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 75, 25);
    firstBandDryWet.setTextValueSuffix(" %");
    addAndMakeVisible(firstBandDryWet);
    firstBandDryWet.addListener(this);
    
    // Dry Wet Slider for Band 2
    secondBandDryWet.setBounds(350, 475, 100, 100); // Combo box 2 bounds: 450, 600, 100, 40
//    secondBandDryWet.setRange(0.f, 100.f, 0.1f);
    secondBandDryWet.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    secondBandDryWet.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 75, 25);
    secondBandDryWet.setTextValueSuffix(" %");
    addAndMakeVisible(secondBandDryWet);
    secondBandDryWet.addListener(this);
    
    // Dry Wet Slider for Band 3
    thirdBandDryWet.setBounds(650, 475, 100, 100); // Combo Box 3 bounds 750, 600, 100, 40
//    thirdBandDryWet.setRange(0.f, 100.f, 0.1f);
    thirdBandDryWet.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    thirdBandDryWet.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 75, 25);
    thirdBandDryWet.setTextValueSuffix(" %");
    addAndMakeVisible(thirdBandDryWet);
    thirdBandDryWet.addListener(this);
    
    // Distortion Parameter 1 for Band 1 // Need to set starting value for slider dist parameters at 0
    firstBandDistParameter1.setBounds(150, 475, 100, 100); // Need to update
//    firstBandDistParameter1.setRange(0.f, 100.f, 0.1f);
    firstBandDistParameter1.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    firstBandDistParameter1.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 75, 25);
    addAndMakeVisible(firstBandDistParameter1);
    firstBandDistParameter1.addListener(this);
    
    // Distortion Parameter 2 for Band 1 // Need to set starting value for slider dist parameters at 0
    firstBandDistParameter2.setBounds(250, 475, 100, 100); // Need to update
//    firstBandDistParameter2.setRange(0.f, 100.f, 0.1f);
    firstBandDistParameter2.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    firstBandDistParameter2.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 75, 25);
    addAndMakeVisible(firstBandDistParameter2);
    firstBandDistParameter2.addListener(this);
    
    // Distortion Parameter 1 for Band 2 // Need to set starting value for slider dist parameters at 0
    secondBandDistParameter1.setBounds(450, 475, 100, 100); // Need to update
//    secondBandDistParameter1.setRange(0.f, 100.f, 0.1f);
    secondBandDistParameter1.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    secondBandDistParameter1.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 75, 25);
    addAndMakeVisible(secondBandDistParameter1);
    secondBandDistParameter1.addListener(this);
    
    // Distortion Parameter 2 for Band 2 // Need to set starting value for slider dist parameters at 0
    secondBandDistParameter2.setBounds(550, 475, 100, 100); // Need to update
//    secondBandDistParameter2.setRange(0.f, 100.f, 0.1f);
    secondBandDistParameter2.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    secondBandDistParameter2.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 75, 25);
    addAndMakeVisible(secondBandDistParameter2);
    secondBandDistParameter2.addListener(this);
    
    // Distortion Parameter 1 for Band 3 // Need to set starting value for slider dist parameters at 0
    thirdBandDistParameter1.setBounds(750, 475, 100, 100); // Need to update
//    thirdBandDistParameter1.setRange(0.f, 100.f, 0.1f);
    thirdBandDistParameter1.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    thirdBandDistParameter1.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 75, 25);
    addAndMakeVisible(thirdBandDistParameter1);
    thirdBandDistParameter1.addListener(this);
    
    // Distortion Parameter 2 for Band 3 // Need to set starting value for slider dist parameters at 0
    thirdBandDistParameter2.setBounds(850, 475, 100, 100); // Need to update
//    thirdBandDistParameter2.setRange(0.f, 100.f, 0.1f);
    thirdBandDistParameter2.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    thirdBandDistParameter2.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 75, 25);
    addAndMakeVisible(thirdBandDistParameter2);
    thirdBandDistParameter2.addListener(this);
    
    // Input and Output gain sliders
    inGain.setBounds(0, 100, 100, 200); // Need to update
//    inGain.setRange(-12.f, 12.f, 0.1f);
    inGain.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    inGain.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 75, 25);
    inGain.setTextValueSuffix(" dB");
    addAndMakeVisible(inGain);
    inGain.addListener(this);
    
    outGain.setBounds(900, 100, 100, 200); // Need to update
//    outGain.setRange(-12.f, 12.f, 0.1f);
    outGain.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    outGain.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 75, 25);
    outGain.setTextValueSuffix(" dB");
    addAndMakeVisible(outGain);
    outGain.addListener(this);

    // Look and Feel For Sliders
    getLookAndFeel().setColour(juce::Slider::thumbColourId, juce::Colours::darkcyan);
    getLookAndFeel().setColour(juce::Slider::rotarySliderOutlineColourId, juce::Colours::azure);
    getLookAndFeel().setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::darkseagreen);
    getLookAndFeel().setColour(juce::Slider::textBoxTextColourId, juce::Colours::beige);
    
    // Selection Combo Box for Band 1
    firstBandSelectionType.addListener(this);
    firstBandSelectionType.setBounds(150, 600, 200, 40); // first band distortion selection combo box
    firstBandSelectionType.addItem("Empty", 1);
    firstBandSelectionType.addItem("Full Wave Rectification", 2);
    firstBandSelectionType.addItem("Half Wave Rectification", 3);
    firstBandSelectionType.addItem("Hard Clip", 4);
    firstBandSelectionType.addItem("Infinite Clip", 5);
    firstBandSelectionType.addItem("Soft Clip (Arc Tangent)", 6);
    firstBandSelectionType.addItem("Soft Clip (Cubic)", 7);
    addAndMakeVisible(firstBandSelectionType);
    
    // Selection Combo Box for Band 2
    secondBandSelectionType.addListener(this);
    secondBandSelectionType.setBounds(450, 600, 200, 40);
    secondBandSelectionType.addItem("Empty", 1);
    secondBandSelectionType.addItem("Full Wave Rectification", 2);
    secondBandSelectionType.addItem("Half Wave Rectification", 3);
    secondBandSelectionType.addItem("Hard Clip", 4);
    secondBandSelectionType.addItem("Infinite Clip", 5);
    secondBandSelectionType.addItem("Soft Clip (Arc Tangent)", 6);
    secondBandSelectionType.addItem("Soft Clip (Cubic)", 7);
    addAndMakeVisible(secondBandSelectionType);
    
    // Selection Combo Box for Band 3
    thirdBandSelectionType.addListener(this);
    thirdBandSelectionType.setBounds(750, 600, 200, 40); // Third band distortion selection combo box
    thirdBandSelectionType.addItem("Empty", 1);
    thirdBandSelectionType.addItem("Full Wave Rectification", 2);
    thirdBandSelectionType.addItem("Half Wave Rectification", 3);
    thirdBandSelectionType.addItem("Hard Clip", 4);
    thirdBandSelectionType.addItem("Infinite Clip", 5);
    thirdBandSelectionType.addItem("Soft Clip (Arc Tangent)", 6);
    thirdBandSelectionType.addItem("Soft Clip (Cubic)", 7);
    addAndMakeVisible(thirdBandSelectionType);
    
    // Look and Feel For Combo Boxes
    getLookAndFeel().setColour(juce::ComboBox::backgroundColourId, juce::Colours::darkcyan);
    getLookAndFeel().setColour(juce::ComboBox::textColourId, juce::Colours::beige);
    getLookAndFeel().setColour(juce::ComboBox::focusedOutlineColourId, juce::Colours::darkcyan);
    
//    // Bypass Button
//    bypassButton.setBounds(10, 10, 100, 20);
//    bypassButton.setButtonText("Bypass");
//    bypassButton.setToggleState(false, juce::dontSendNotification);
//    addAndMakeVisible(bypassButton);
////    bypassButton.addListener(this);
//    
//    // First Band Solo Button
//    firstBandSoloButton.setBounds(70, 610, 100, 20);
//    firstBandSoloButton.setButtonText("Solo");
//    firstBandSoloButton.setToggleState(false, juce::dontSendNotification);
//    addAndMakeVisible(firstBandSoloButton);
////    bypassButton.addListener(this);
//    
//    // Second Band Solo Button
//    secondBandSoloButton.setBounds(370, 610, 100, 20);
//    secondBandSoloButton.setButtonText("Solo");
//    secondBandSoloButton.setToggleState(false, juce::dontSendNotification);
//    addAndMakeVisible(secondBandSoloButton);
////    bypassButton.addListener(this);
//    
//    // third Band Solo Button
//    thirdBandSoloButton.setBounds(670, 610, 100, 20);
//    thirdBandSoloButton.setButtonText("Solo");
//    thirdBandSoloButton.setToggleState(false, juce::dontSendNotification);
//    addAndMakeVisible(thirdBandSoloButton);
////    bypassButton.addListener(this);

    // Slider attachments
    sliderAttachments.emplace_back(new SliderAttachment(audioProcessor.apvts,g_InGain,inGain));
    sliderAttachments.emplace_back(new SliderAttachment(audioProcessor.apvts,g_OutGain,outGain));
    
    sliderAttachments.emplace_back(new SliderAttachment(audioProcessor.apvts,g_Crossover1,firstCrossover));
    sliderAttachments.emplace_back(new SliderAttachment(audioProcessor.apvts,g_Crossover2,secondCrossover));
    
    sliderAttachments.emplace_back(new SliderAttachment(audioProcessor.apvts,g_Wet1,firstBandDryWet));
    sliderAttachments.emplace_back(new SliderAttachment(audioProcessor.apvts,g_Wet2,secondBandDryWet));
    sliderAttachments.emplace_back(new SliderAttachment(audioProcessor.apvts,g_Wet3,thirdBandDryWet));
    
    sliderAttachments.emplace_back(new SliderAttachment(audioProcessor.apvts,g_Param1B1,firstBandDistParameter1));
    sliderAttachments.emplace_back(new SliderAttachment(audioProcessor.apvts,g_Param2B1,firstBandDistParameter2));
    sliderAttachments.emplace_back(new SliderAttachment(audioProcessor.apvts,g_Param1B2,secondBandDistParameter1));
    sliderAttachments.emplace_back(new SliderAttachment(audioProcessor.apvts,g_Param2B2,secondBandDistParameter2));
    sliderAttachments.emplace_back(new SliderAttachment(audioProcessor.apvts,g_Param1B3,thirdBandDistParameter1));
    sliderAttachments.emplace_back(new SliderAttachment(audioProcessor.apvts,g_Param2B3,thirdBandDistParameter2));
    
    // Need attachments for combo box
    
    
    // Bypass/solo buttons attachments
//    buttonAttachments.emplace_back(new ButtonAttachment(audioProcessor.apvts,MultiBandDistortionAudioProcessor::Bypass,bypassButton));
//    buttonAttachments.emplace_back(new ButtonAttachment(audioProcessor.apvts,MultiBandDistortionAudioProcessor::SoloBand1,firstBandSoloButton));
//    buttonAttachments.emplace_back(new ButtonAttachment(audioProcessor.apvts,MultiBandDistortionAudioProcessor::SoloBand2,secondBandSoloButton));
//    buttonAttachments.emplace_back(new ButtonAttachment(audioProcessor.apvts,MultiBandDistortionAudioProcessor::SoloBand3,thirdBandSoloButton));
    
    
}

MultiBandDistortionAudioProcessorEditor::~MultiBandDistortionAudioProcessorEditor()
{
}

//==============================================================================
void MultiBandDistortionAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
    g.fillAll (juce::Colours::cadetblue); // this is how I will change the background color of my plugin

    g.setColour (juce::Colours::beige);
    g.setFont (15.0f);
    
    // Adding Image
    cartoonCar = juce::ImageCache::getFromMemory(BinaryData::Hot_Rod_PNG_png, BinaryData::Hot_Rod_PNG_pngSize);
    g.drawImageAt(cartoonCar, 365, 100);
    
    // "Band select" titles below combo box
    g.drawText ("Band 1 Select", 200, 635, 100, 40,
                juce::Justification::centred, false);
    g.drawText ("Band 2 Select", 500, 635, 100, 40,
                juce::Justification::centred, false);
    g.drawText ("Band 3 Select", 800, 635, 100, 40,
                juce::Justification::centred, false);
    
    // Parameter titles below each parameter
//    g.drawText ("Frequency", 250, 325, 100, 40,
//                juce::Justification::centred, false);
//    g.drawText ("Frequency", 650, 325, 100, 40,
//                juce::Justification::centred, false);
    g.drawText ("Crossover 1", 250, 440, 100, 40,
                juce::Justification::centred, false);
    g.drawText ("Crossover 2", 650, 440, 100, 40,
                juce::Justification::centred, false);
    
    g.drawText ("Dry/Wet", 50, 567, 100, 40,
                juce::Justification::centred, false);
    g.drawText ("Dry/Wet", 350, 567, 100, 40,
                juce::Justification::centred, false);
    g.drawText ("Dry/Wet", 650, 567, 100, 40,
                juce::Justification::centred, false);
    
    g.drawText ("Dist Param 1", 150, 567, 100, 40,
                juce::Justification::centred, false);
    g.drawText ("Dist Param 1", 450, 567, 100, 40,
                juce::Justification::centred, false);
    g.drawText ("Dist Param 1", 750, 567, 100, 40,
                juce::Justification::centred, false);
    
    g.drawText ("Dist Param 2", 250, 567, 100, 40,
                juce::Justification::centred, false);
    g.drawText ("Dist Param 2", 550, 567, 100, 40,
                juce::Justification::centred, false);
    g.drawText ("Dist Param 2", 850, 567, 100, 40,
                juce::Justification::centred, false);
    
    g.drawText ("Input Gain", 0, 295, 100, 40,
                juce::Justification::centred, false);
    g.drawText ("Output Gain", 900, 295, 100, 40,
                juce::Justification::centred, false);
    
    // Plug-in Title
    g.drawText ("Chop Shop", 435, 100, 100, 40,
                juce::Justification::centred, true);
    g.drawText ("A Hot Rod Multiband Distortion Tool", 350, 325, 300, 40,
                juce::Justification::centred, true);
    
}


void MultiBandDistortionAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}

// This is the part where our front end will interface with our backend!
void MultiBandDistortionAudioProcessorEditor::sliderValueChanged(juce::Slider * slider) {
    if (slider == &firstCrossover) { // If the first crossover slider has been adjusted...
        audioProcessor.filterFrequencyCrossover1 = firstCrossover.getValue(); // update the value of the variable we want associated with it...
    }
    if (slider == &secondCrossover) {
        audioProcessor.filterFrequencyCrossover2 = secondCrossover.getValue();
    }
    if (slider == &firstBandDryWet) {
        audioProcessor.WetBand1 = firstBandDryWet.getValue();
    }
    if (slider == &secondBandDryWet) {
        audioProcessor.WetBand2 = secondBandDryWet.getValue();
    }
    if (slider == &thirdBandDryWet) {
        audioProcessor.WetBand3 = thirdBandDryWet.getValue();
    }
    if (slider == &firstBandDistParameter1) {
        audioProcessor.distParam1Band1 = firstBandDistParameter1.getValue();
    }
    if (slider == &firstBandDistParameter2) {
        audioProcessor.distParam2Band1 = firstBandDistParameter2.getValue();
    }
    if (slider == &secondBandDistParameter1) {
        audioProcessor.distParam1Band2 = secondBandDistParameter1.getValue();
    }
    if (slider == &secondBandDistParameter2) {
        audioProcessor.distParam2Band2 = secondBandDistParameter2.getValue();
    }
    if (slider == &thirdBandDistParameter1) {
        audioProcessor.distParam1Band3 = thirdBandDistParameter1.getValue();
    }
    if (slider == &thirdBandDistParameter2) {
        audioProcessor.distParam2Band3 = thirdBandDistParameter2.getValue();
    }
    if (slider == &inGain) {
        audioProcessor.inputGain = inGain.getValue();
    }
    if (slider == &outGain) {
        audioProcessor.outputGain = outGain.getValue();
    }
}

void MultiBandDistortionAudioProcessorEditor::comboBoxChanged(juce::ComboBox * comboBox) {
    if (comboBox == &firstBandSelectionType) { // if the first combo box is changed
        audioProcessor.setDistType(0, firstBandSelectionType.getSelectedId()); // update/change the distortion selection
        
        // Based on the selection, certain paramters will become available for use, or unavaiable for use, I could probably make this into a function
        // The bool statements are set to false if the selected type does not utilize a parameter control
        
        if (firstBandSelectionType.getSelectedId() == 1) { // Empty
            firstBandDryWet.setEnabled(false);
            firstBandDistParameter1.setEnabled(false);
            firstBandDistParameter2.setEnabled(false);
        }
        if (firstBandSelectionType.getSelectedId() == 2) { // Full Wave
            firstBandDryWet.setEnabled(true);
            firstBandDistParameter1.setEnabled(false);
            firstBandDistParameter2.setEnabled(false);
        }
        if (firstBandSelectionType.getSelectedId() == 3) { // Half Wave
            firstBandDryWet.setEnabled(true);
            firstBandDistParameter1.setEnabled(false);
            firstBandDistParameter2.setEnabled(false);
        }
        if (firstBandSelectionType.getSelectedId() == 4) { // Hard Clip
            firstBandDryWet.setEnabled(true);
            firstBandDistParameter1.setEnabled(true);
            firstBandDistParameter2.setEnabled(true);
        }
        if (firstBandSelectionType.getSelectedId() == 5) { // Infinite Clip
            firstBandDryWet.setEnabled(true);
            firstBandDistParameter1.setEnabled(false);
            firstBandDistParameter2.setEnabled(false);
        }
        if (firstBandSelectionType.getSelectedId() == 6) { // Soft Clip (Arc Tangent)
            firstBandDryWet.setEnabled(true);
            firstBandDistParameter1.setEnabled(true);
            firstBandDistParameter2.setEnabled(false);
        }
        if (firstBandSelectionType.getSelectedId() == 7) { // Soft Clip (Cubic)
            firstBandDryWet.setEnabled(true);
            firstBandDistParameter1.setEnabled(false);
            firstBandDistParameter2.setEnabled(false);
        }
    }
    
    if (comboBox == &secondBandSelectionType) {
        audioProcessor.setDistType(1, secondBandSelectionType.getSelectedId());
        
        if (secondBandSelectionType.getSelectedId() == 1) { // Empty
            secondBandDryWet.setEnabled(false);
            secondBandDistParameter1.setEnabled(false);
            secondBandDistParameter2.setEnabled(false);
        }
        if (secondBandSelectionType.getSelectedId() == 2) { // Full Wave
            secondBandDryWet.setEnabled(true);
            secondBandDistParameter1.setEnabled(false);
            secondBandDistParameter2.setEnabled(false);
        }
        if (secondBandSelectionType.getSelectedId() == 3) { // Half Wave
            secondBandDryWet.setEnabled(true);
            secondBandDistParameter1.setEnabled(false);
            secondBandDistParameter2.setEnabled(false);
        }
        if (secondBandSelectionType.getSelectedId() == 4) { // Hard Clip
            secondBandDryWet.setEnabled(true);
            secondBandDistParameter1.setEnabled(true);
            secondBandDistParameter2.setEnabled(true);
        }
        if (secondBandSelectionType.getSelectedId() == 5) { // Infinite Clip
            secondBandDryWet.setEnabled(true);
            secondBandDistParameter1.setEnabled(false);
            secondBandDistParameter2.setEnabled(false);
        }
        if (secondBandSelectionType.getSelectedId() == 6) { // Soft Clip (Arc Tangent)
            secondBandDryWet.setEnabled(true);
            secondBandDistParameter1.setEnabled(true);
            secondBandDistParameter2.setEnabled(false);
        }
        if (secondBandSelectionType.getSelectedId() == 7) { // Soft Clip (Cubic)
            secondBandDryWet.setEnabled(true);
            secondBandDistParameter1.setEnabled(false);
            secondBandDistParameter2.setEnabled(false);
        }
    }
    
    if (comboBox == &thirdBandSelectionType) {
        audioProcessor.setDistType(2, thirdBandSelectionType.getSelectedId());
        if (thirdBandSelectionType.getSelectedId() == 1) { // Empty
            thirdBandDryWet.setEnabled(false);
            thirdBandDistParameter1.setEnabled(false);
            thirdBandDistParameter2.setEnabled(false);
        }
        if (thirdBandSelectionType.getSelectedId() == 2) { // Full Wave
            thirdBandDryWet.setEnabled(true);
            thirdBandDistParameter1.setEnabled(false);
            thirdBandDistParameter2.setEnabled(false);
        }
        if (thirdBandSelectionType.getSelectedId() == 3) { // Half Wave
            thirdBandDryWet.setEnabled(true);
            thirdBandDistParameter1.setEnabled(false);
            thirdBandDistParameter2.setEnabled(false);
        }
        if (thirdBandSelectionType.getSelectedId() == 4) { // Hard Clip
            thirdBandDryWet.setEnabled(true);
            thirdBandDistParameter1.setEnabled(true);
            thirdBandDistParameter2.setEnabled(true);
        }
        if (thirdBandSelectionType.getSelectedId() == 5) { // Infinite Clip
            thirdBandDryWet.setEnabled(true);
            thirdBandDistParameter1.setEnabled(false);
            thirdBandDistParameter2.setEnabled(false);
        }
        if (thirdBandSelectionType.getSelectedId() == 6) { // Soft Clip (Arc Tangent)
            thirdBandDryWet.setEnabled(true);
            thirdBandDistParameter1.setEnabled(true);
            thirdBandDistParameter2.setEnabled(false);
        }
        if (thirdBandSelectionType.getSelectedId() == 7) { // Soft Clip (Cubic)
            thirdBandDryWet.setEnabled(true);
            thirdBandDistParameter1.setEnabled(false);
            thirdBandDistParameter2.setEnabled(false);
        }
    }
        
}
