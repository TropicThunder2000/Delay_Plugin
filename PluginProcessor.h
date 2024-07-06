/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/**
*/



class Delay {
public:
    Delay() = default;
    ~Delay() = default;
    Delay(const Delay& delay) = default;
    void setMaxDelayTime(int maxDelay);
    void setSampleRate(int sampleRate);
    void setParameters(float delayTime);
    float process(float sample);
    int32_t readIndex = 0;
    int32_t writeIndex = 0;
    void setCutOff(float cutOff);

private:
    std::vector<float> buffer;
    float sampleRate;
    float delay;
    float cutOff;
    
};

class Delay_AdityaJeganathKAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    Delay_AdityaJeganathKAudioProcessor();
    ~Delay_AdityaJeganathKAudioProcessor() override;

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
    void setSampleRate(double sampleRate);
    
private:

    //==============================================================================
    juce::AudioParameterFloat* gainKnobParam;
    juce::AudioParameterFloat* delayTimeParam;
    float currentCutOff;
    juce::AudioParameterFloat* lowPassParam;

    float currentGain, currentDelaytime;
    float maxDelayTime;
    double fs;
    int delaySize;
    std::vector<Delay> delayEffect;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Delay_AdityaJeganathKAudioProcessor)
};
