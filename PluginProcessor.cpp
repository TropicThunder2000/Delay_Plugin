/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Delay_AdityaJeganathKAudioProcessor::Delay_AdityaJeganathKAudioProcessor()
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
    gainKnobParam = new juce::AudioParameterFloat(juce::ParameterID("1", 1), "Gain", -24.f, 5.f, 0.f);
    delayTimeParam = new juce::AudioParameterFloat(juce::ParameterID("2", 2), "Delay Time", 0.1f, 1.0f, 0.1f);
    lowPassParam = new juce::AudioParameterFloat(juce::ParameterID("3", 3), "Low Pass", 0.1f, 1.0f, 0.1f);

    addParameter(gainKnobParam);
    addParameter(delayTimeParam);
    addParameter(lowPassParam);
    maxDelayTime = 1.0f;
    currentGain = *gainKnobParam;
    currentDelaytime = *delayTimeParam;
    currentCutOff = *lowPassParam;
    if (currentGain != *gainKnobParam || currentDelaytime != *delayTimeParam /*|| currentCutOff != *lowPassParam*/) {
        currentGain = *gainKnobParam;
        currentDelaytime = *delayTimeParam;
        currentCutOff = *lowPassParam;
    }   
}

Delay_AdityaJeganathKAudioProcessor::~Delay_AdityaJeganathKAudioProcessor()
{
}

//==============================================================================
const juce::String Delay_AdityaJeganathKAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool Delay_AdityaJeganathKAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool Delay_AdityaJeganathKAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool Delay_AdityaJeganathKAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double Delay_AdityaJeganathKAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int Delay_AdityaJeganathKAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int Delay_AdityaJeganathKAudioProcessor::getCurrentProgram()
{
    return 0;
}

void Delay_AdityaJeganathKAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String Delay_AdityaJeganathKAudioProcessor::getProgramName (int index)
{
    return {};
}

void Delay_AdityaJeganathKAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void Delay_AdityaJeganathKAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    setSampleRate(sampleRate);
    delaySize = static_cast<int>(sampleRate * maxDelayTime);
    delayEffect.resize(2);
    for (uint32_t i = 0;i < delayEffect.size();i++)
    {
        delayEffect[i].setSampleRate(sampleRate);
        delayEffect[i].setMaxDelayTime(static_cast<uint32_t>(delayTimeParam->range.end));
    }
}

void Delay_AdityaJeganathKAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool Delay_AdityaJeganathKAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void Delay_AdityaJeganathKAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
    {
        buffer.clear(i, 0, buffer.getNumSamples());
    }

    for (uint32_t i = 0;i < delayEffect.size();i++)
    {
        delayEffect[i].setParameters(*delayTimeParam);
        delayEffect[i].setCutOff(*lowPassParam);
    }
    
    for (int i = 0;i < buffer.getNumChannels();i++)
    {
        for (int j = 0;j < buffer.getNumSamples();j++)
        {
            buffer.setSample(i, j, delayEffect[i].process(powf(10, *gainKnobParam / 20) * buffer.getSample(i, j)));
        }
    }
}

//==============================================================================
bool Delay_AdityaJeganathKAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* Delay_AdityaJeganathKAudioProcessor::createEditor()
{
    return new Delay_AdityaJeganathKAudioProcessorEditor (*this);
}

//==============================================================================
void Delay_AdityaJeganathKAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void Delay_AdityaJeganathKAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

void Delay_AdityaJeganathKAudioProcessor::setSampleRate(double sampleRate)
{
    fs = sampleRate;
}


void Delay::setMaxDelayTime(int maxDelay) {
    maxDelay = 1.0;
    buffer.resize(maxDelay * sampleRate);
    std::fill(buffer.begin(), buffer.end(), 0.0f);
}

void Delay::setSampleRate(int sampleRate)
{
    this->sampleRate = sampleRate;
}

void Delay::setParameters(float delayTime)
{
    if (this->delay != delayTime)
    {
        this->delay = delayTime;
    }
}

void Delay::setCutOff(float cutOff)
{
    this->cutOff = cutOff;
}

float Delay::process(float sample)
{
    buffer[writeIndex++] = sample;
    int delayInSamples = this->delay * sampleRate;
    readIndex = delayInSamples - writeIndex;
    readIndex = readIndex >= buffer.size() ? readIndex % buffer.size() : readIndex;
    readIndex = readIndex < 0 ? readIndex + delayInSamples : readIndex;
    float newSample = cutOff * buffer[readIndex] + (1-cutOff)* sample;
    writeIndex %= delayInSamples;
    return newSample;
}


//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Delay_AdityaJeganathKAudioProcessor();
}

