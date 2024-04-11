/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "FullWaveRec.h"
#include "HalfWaveRec.h"
#include "HardClip.h"
#include "InfClip.h"
#include "SoftClipArcTan.h"
#include "SoftClipCubic.h"

//==============================================================================
MultiBandDistortionAudioProcessor::MultiBandDistortionAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
}

MultiBandDistortionAudioProcessor::~MultiBandDistortionAudioProcessor()
{
    for(int i = 0 ; i < NUM_DISTORTION ; i++) { // This deletes the effects when our plugin closes - "Release Memory"
        delete effect[i];
    }
}

//==============================================================================
const juce::String MultiBandDistortionAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool MultiBandDistortionAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool MultiBandDistortionAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool MultiBandDistortionAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double MultiBandDistortionAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int MultiBandDistortionAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int MultiBandDistortionAudioProcessor::getCurrentProgram()
{
    return 0;
}

void MultiBandDistortionAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String MultiBandDistortionAudioProcessor::getProgramName (int index)
{
    return {};
}

void MultiBandDistortionAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void MultiBandDistortionAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    for (int i = 0 ; i < NUM_DISTORTION ; i++) {
        effect[i] = new DistortionProcessor;
        effect[i]->prepare(sampleRate);
    }
}

void MultiBandDistortionAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool MultiBandDistortionAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void MultiBandDistortionAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    int N = buffer.getNumSamples(); // Gets the number of samples in the buffer
    
    
    
       
    
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);
        
//        for (int i = 0 ; i < NUM_DISTORTION ; i++) {
//            effect[i] = new DistortionProcessor;
//            effect[i]->process(channelData, N, channel); // ChannelData is our pointer to the buffer
//        }
        
        // MAIN PROCESSING DONE HERE
        for (int n = 0 ; n < N ; n++) {
            
            // First Band Filtering (Low Pass)
            lowBandLowPass.setFreq(filterFrequencyCrossover1); // function that sets our freq. will be equal to that of the first crossover value
            lowBandLowPass.setQ(0.0f); // function that sets our q value
            lowBandLowPass.setAmpdB(10.f); // function that sets our amplitude
            lowBandLowPass.setFilterType(Biquad::FilterType::LPF); // function that sets our filter type
            
            lowBandLowPassDup.setFreq(filterFrequencyCrossover1); // duplicate function that will be combined with our first
            lowBandLowPassDup.setQ(0.0f);
            lowBandLowPassDup.setAmpdB(10.f);
            lowBandLowPassDup.setFilterType(Biquad::FilterType::LPF);
            
            // Second Band Effects Processing
            float a = lowBandLowPass.processSample(channelData[n], channel); // Process the filter on the sample
            float b = lowBandLowPassDup.processSample(channelData[n], channel); // Process the filter on the sample
            
            float band1Filter = a + b; // combine the two
            
            effect[0]->setDistParam1(distParam1Band1); // Setting the distortion 1 parameter if applicable
            effect[0]->setDistParam2(distParam2Band1); // Setting the distrotion 2 parameter if applicable
            effect[0]->processSample(band1Filter, channel); // Processes the buffer with the effect parameters, at the sample
            
            
            // Second Band Filtering (Band Pass)
            // The 1st frequency crossover value is set to the highpass cutoff
            // The 2nd frequency crossover value is set to the Lowpass cutoff
            // When combined together, they make the band pass
            midBandHighPass.setQ(filterFrequencyCrossover1);
            midBandHighPass.setQ(0.0f);
            midBandHighPass.setAmpdB(10.f);
            midBandHighPass.setFilterType(Biquad::FilterType::HPF);
            
            midBandHighPassDup.setQ(filterFrequencyCrossover1);
            midBandHighPassDup.setQ(0.0f);
            midBandHighPassDup.setAmpdB(10.f);
            midBandHighPassDup.setFilterType(Biquad::FilterType::HPF);
            
            midBandLowPass.setQ(filterFrequencyCrossover2);
            midBandLowPass.setQ(0.0f);
            midBandLowPass.setAmpdB(10.f);
            midBandLowPass.setFilterType(Biquad::FilterType::LPF);
            
            midBandLowPassDup.setQ(filterFrequencyCrossover2);
            midBandLowPassDup.setQ(0.0f);
            midBandLowPassDup.setAmpdB(10.f);
            midBandLowPassDup.setFilterType(Biquad::FilterType::LPF);
            
            float c = midBandHighPass.processSample(channelData[n], channel); // Process the filter on the sample
            float d = midBandHighPassDup.processSample(channelData[n], channel); // Process the filter on the sample
            float e = midBandLowPass.processSample(channelData[n], channel); // Process the filter on the sample
            float f = midBandLowPassDup.processSample(channelData[n], channel); // Process the filter on the sample
            
            float band2Filter = c + d + e + f;
            
            effect[1]->setDistParam1(distParam1Band2);
            effect[1]->setDistParam2(distParam2Band2);
            effect[1]->processSample(band2Filter, channel);
            
            // Third Band Filtering (High Pass)
            highBandHighPass.setFreq(filterFrequencyCrossover2); // function that sets our freq. will be equal to that of the second crossover value
            highBandHighPass.setQ(0.0f);
            highBandHighPass.setAmpdB(10.f);
            highBandHighPass.setFilterType(Biquad::FilterType::HPF);
            
            highBandHighPassDup.setFreq(filterFrequencyCrossover2); // function that sets our freq. will be equal to that of the second crossover value
            highBandHighPassDup.setQ(0.0f);
            highBandHighPassDup.setAmpdB(10.f);
            highBandHighPassDup.setFilterType(Biquad::FilterType::HPF);
            
            float g = highBandHighPass.processSample(channelData[n], channel);
            float h = highBandHighPassDup.processSample(channelData[n], channel);
            
            float band3Filter = g + h;
            
            effect[2]->setDistParam1(distParam1Band3);
            effect[2]->setDistParam2(distParam2Band3);
            effect[2]->processSample(band3Filter, channel);
            
            channelData[n] = band1Filter + band2Filter + band3Filter;
            
            // My original idea was to make a copy of each buffer, apply processing to each individually then combine them back together. This ended up being quite a pain and I was unable to get it to work,
        }
    }
}

//==============================================================================
bool MultiBandDistortionAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* MultiBandDistortionAudioProcessor::createEditor()
{
    return new MultiBandDistortionAudioProcessorEditor (*this);
}

//==============================================================================
void MultiBandDistortionAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void MultiBandDistortionAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

void MultiBandDistortionAudioProcessor::setDistType(int bandNum, int selection) {
    
    // band num corresponds to the band that the distortion will be applied to (band 1 (low frequencies), band 2 (mid frequencies), band 3 (high frequencies))
    // selection corresponds to the user selected distortion type
    
    delete effect[bandNum]; // Deletes the current instance of whatever distortion is currently on the selected band
    
    if (selection == 1) {
        effect[bandNum] = new DistortionProcessor; // and creates a new instance based on the selection
    }
    
    if (selection == 2) {
        effect[bandNum] = new FullWaveRec;
    }
    
    if (selection == 3) {
        effect[bandNum] = new HalfWaveRec;
    }
    
    if (selection == 4) {
        effect[bandNum] = new HardClip;
    }
    
    if (selection == 5) {
        effect[bandNum] = new InfClip;
    }
    
    if (selection == 6) {
        effect[bandNum] = new SoftClipArcTan;
    }
    
    if (selection == 7) {
        effect[bandNum] = new SoftClipArcTan;
    }
    
    effect[bandNum]->prepare(Fs);
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new MultiBandDistortionAudioProcessor();
}
