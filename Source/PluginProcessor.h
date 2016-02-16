/*
  ==============================================================================

    This file was auto-generated by the Introjucer!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#ifndef PLUGINPROCESSOR_H_INCLUDED
#define PLUGINPROCESSOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "VAOnePoleFilter.h"
#include "CustomAudioParameter.h"


//==============================================================================
/**
*/
class FilterGuiDemoAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    FilterGuiDemoAudioProcessor();
    ~FilterGuiDemoAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

    void processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages) override
    {
        jassert (! isUsingDoublePrecision());
        process (buffer, midiMessages);
    }
    
    void processBlock (AudioBuffer<double>& buffer, MidiBuffer& midiMessages) override
    {
        jassert (isUsingDoublePrecision());
        process (buffer, midiMessages);
    }

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool silenceInProducesSilenceOut() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    //Returns the processors AudioFilter instance for GUI code etc.
    AudioFilter& getAudioFilter();

private:
    //==============================================================================
    template <typename FloatType>
    void process (AudioBuffer<FloatType>& buffer, MidiBuffer& midiMessages);
    
    std::unique_ptr<AudioFilter> filter1;
    
    CustomAudioParameter* filterCutoffParam;
    CustomAudioParameter* filterGainParam;
    
    //Default setup values for filter etc.
    const float defaultSampleRate = 44100.00;
    const float defaultMinFilterFrequency = 6.00;
    const float defaultMaxFilterFrequency = 20000.00;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FilterGuiDemoAudioProcessor)
};


#endif  // PLUGINPROCESSOR_H_INCLUDED
