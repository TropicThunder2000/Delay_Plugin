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
class Delay_AdityaJeganathKAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    Delay_AdityaJeganathKAudioProcessorEditor (Delay_AdityaJeganathKAudioProcessor&);
    ~Delay_AdityaJeganathKAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    Delay_AdityaJeganathKAudioProcessor& audioProcessor;

    juce::AudioParameterFloat* gainKnobParam;
    juce::AudioParameterFloat* delayTimeParam;
    juce::AudioParameterFloat* lowPassParam;

    juce::Slider gainKnob;
    juce::Slider delayKnob;
    juce::Slider lowPassKnob;
    juce::Label lowPassLabel;
    juce::Label gainLabel;
    juce::Label delayLabel;
    juce::Label pluginTitle;
    juce::ImageComponent imageComponent;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Delay_AdityaJeganathKAudioProcessorEditor)
};
