/*
  ==============================================================================

    This file was auto-generated by the Introjucer!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
FilterGuiDemoAudioProcessor::FilterGuiDemoAudioProcessor()
{
    /* The lambda is capturing a value copy of the this pointer to the audio processor. The processor will be destroyed after the parameter object so
     this is safe.*/
    auto cutoffParamCallback = [this] (float newCutoff){this->filter1->setCutoff(newCutoff);};
    filterCutoffParam = new CustomAudioParameter("FilterCutoff", CustomAudioParameter::ParameterTypes::Volt_Octave_Param, cutoffParamCallback);
    
    //Setting custom min and max values for filterCutoffParam as parameter is Volt_Octave_Param type. See CustomAudioParameter.h comments.
    filterCutoffParam->setCustomMinValue(defaultMinFilterFrequency);
    filterCutoffParam->setCustomMaxValue(defaultMaxFilterFrequency);
    
    auto gainParamCallback = [this] (float gain) {this->filter1->setGain(gain);};
    filterGainParam = new CustomAudioParameter("FilterGain", CustomAudioParameter::ParameterTypes::Regular_Float_Param, gainParamCallback);
    
    addParameter(filterCutoffParam);
    addParameter(filterGainParam);
}

FilterGuiDemoAudioProcessor::~FilterGuiDemoAudioProcessor()
{
}

//==============================================================================
const String FilterGuiDemoAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool FilterGuiDemoAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool FilterGuiDemoAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool FilterGuiDemoAudioProcessor::silenceInProducesSilenceOut() const
{
    return false;
}

double FilterGuiDemoAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int FilterGuiDemoAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int FilterGuiDemoAudioProcessor::getCurrentProgram()
{
    return 0;
}

void FilterGuiDemoAudioProcessor::setCurrentProgram (int index)
{
}

const String FilterGuiDemoAudioProcessor::getProgramName (int index)
{
    return String();
}

void FilterGuiDemoAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void FilterGuiDemoAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void FilterGuiDemoAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

template <typename FloatType>
void FilterGuiDemoAudioProcessor::process (AudioBuffer<FloatType>& buffer,
                                                MidiBuffer& midiMessages)
{
    float numSamples = buffer.getNumSamples();
    float currentSampleRate = getSampleRate();
    
    //Handles filter being added onto an already playing audio track where some hosts will not call prepare to play method.
    if (filter1->getSampleRate() != currentSampleRate)
    {
        filter1->initializeFilter(currentSampleRate, defaultMinFilterFrequency, defaultMaxFilterFrequency);
    }
    
    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // I've added this to avoid people getting screaming feedback
    // when they first compile the plugin, but obviously you don't need to
    // this code if your algorithm already fills all the output channels.
    for (int i = getTotalNumInputChannels(); i < getTotalNumOutputChannels(); ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // MAIN AUDIO PROCESSING BLOCK. PROCESS FILTER TWICE FOR STEREO CHANNELS
    for (int channel = 0; channel < getTotalNumInputChannels(); ++channel)
    {
        const FloatType* input = buffer.getReadPointer(channel);
        FloatType* output = buffer.getWritePointer (channel);
        
        for (int i = 0; i < numSamples; i++)
        {
            output[i] = filter1->processFilter(input[i], channel);
        }
    }
}

//==============================================================================
AudioFilter& FilterGuiDemoAudioProcessor::getAudioFilter()
{
    return *filter1;
}

//==============================================================================
bool FilterGuiDemoAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* FilterGuiDemoAudioProcessor::createEditor()
{
    return new FilterGuiDemoAudioProcessorEditor (*this);
}

//==============================================================================
void FilterGuiDemoAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void FilterGuiDemoAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new FilterGuiDemoAudioProcessor();
}
