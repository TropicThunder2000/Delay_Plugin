/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Delay_AdityaJeganathKAudioProcessorEditor::Delay_AdityaJeganathKAudioProcessorEditor (Delay_AdityaJeganathKAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    setSize(700,400);
    addAndMakeVisible(gainKnob);
    addAndMakeVisible(delayKnob);
    addAndMakeVisible(gainLabel);
    addAndMakeVisible(delayLabel);
    addAndMakeVisible(imageComponent);
    addAndMakeVisible(pluginTitle);
    addAndMakeVisible(lowPassKnob);
    addAndMakeVisible(lowPassLabel);

    // Gain Knob component GUI
    gainKnob.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    gainKnob.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    gainKnob.setColour(juce::Slider::thumbColourId, juce::Colour(82,121,111));
    gainKnob.setColour(juce::Slider::rotarySliderFillColourId, juce::Colour(132,169,140));
    gainKnob.setColour(juce::Slider::rotarySliderOutlineColourId, juce::Colour(34, 34, 34));
    gainKnob.setColour(juce::Slider::textBoxBackgroundColourId, juce::Colour(11,82,91));

    gainLabel.setText("Gain", juce::dontSendNotification);
    gainLabel.attachToComponent(&gainKnob, false);
    gainLabel.setColour(juce::Label::textColourId, juce::Colour(132,169,140));
    gainLabel.setJustificationType(juce::Justification::centredBottom);

    //Delay Knob Component GUI
    delayKnob.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    delayKnob.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    delayKnob.setColour(juce::Slider::thumbColourId, juce::Colour(82, 121, 111));
    delayKnob.setColour(juce::Slider::rotarySliderFillColourId, juce::Colour(132, 169, 140));
    delayKnob.setColour(juce::Slider::rotarySliderOutlineColourId, juce::Colour(34, 34, 34));
    delayKnob.setColour(juce::Slider::textBoxBackgroundColourId, juce::Colour(11,82,91));

    delayLabel.setText("Delay Time", juce::dontSendNotification);
    delayLabel.attachToComponent(&delayKnob, false);
    delayLabel.setColour(juce::Label::textColourId, juce::Colour(132, 169, 140));
    delayLabel.setJustificationType(juce::Justification::centredBottom);
    


    //Low Pass Component GUi
    lowPassKnob.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    lowPassKnob.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    lowPassKnob.setColour(juce::Slider::thumbColourId, juce::Colour(82, 121, 111));
    lowPassKnob.setColour(juce::Slider::rotarySliderFillColourId, juce::Colour(132, 169, 140));
    lowPassKnob.setColour(juce::Slider::rotarySliderOutlineColourId, juce::Colour(34, 34, 34));
    lowPassKnob.setColour(juce::Slider::textBoxBackgroundColourId, juce::Colour(11, 82, 91));

    lowPassLabel.setText("Dry/Wet", juce::dontSendNotification);
    lowPassLabel.attachToComponent(&lowPassKnob, false);
    lowPassLabel.setColour(juce::Label::textColourId, juce::Colour(132, 169, 140));
    lowPassLabel.setJustificationType(juce::Justification::centredBottom);

    pluginTitle.setText("Nelson manDELAY", juce::dontSendNotification);
    pluginTitle.setColour(juce::Label::textColourId, juce::Colour(132, 169, 140));

    juce::Font titleFont;
    titleFont.setHeight(30.0f);
    titleFont = titleFont.withStyle(juce::Font::italic);
    pluginTitle.setFont(titleFont);

    juce::File imageFile("C:/Mue/Sem2/DSP2/Projects/Delay_AdityaJeganathK/dragon-png-17372.png");
    juce::Image image = juce::ImageFileFormat::loadFrom(imageFile);
    
    imageComponent.setImage(image);

    auto parameterTree = audioProcessor.getParameters();

    gainKnobParam = (juce::AudioParameterFloat*)parameterTree.getUnchecked(0);
    delayTimeParam = (juce::AudioParameterFloat*)parameterTree.getUnchecked(1);
    lowPassParam = (juce::AudioParameterFloat*)parameterTree.getUnchecked(2);


    gainKnob.setRange(gainKnobParam->range.start, gainKnobParam->range.end, gainKnobParam->range.interval);
    delayKnob.setRange(delayTimeParam->range.start, delayTimeParam->range.end, delayTimeParam->range.interval);
    lowPassKnob.setRange(lowPassParam->range.start, lowPassParam->range.end, lowPassParam->range.interval);

    gainKnob.setValue(0, juce::dontSendNotification);
    delayKnob.setValue(0, juce::dontSendNotification);
    lowPassKnob.setValue(0, juce::dontSendNotification);

    gainKnob.onValueChange = [this]
        {
            *gainKnobParam = gainKnob.getValue();
        };

    delayKnob.onValueChange = [this]
        {
            *delayTimeParam = delayKnob.getValue();
        };
    lowPassKnob.onValueChange = [this]
        {
            *lowPassParam = lowPassKnob.getValue();
        };
}

Delay_AdityaJeganathKAudioProcessorEditor::~Delay_AdityaJeganathKAudioProcessorEditor()
{
}

//==============================================================================
void Delay_AdityaJeganathKAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colour(42,67,70));
}

void Delay_AdityaJeganathKAudioProcessorEditor::resized()
{
    auto x = getWidth() / 10;
    auto y = getHeight() / 10;

    gainKnob.setBounds(0, y, 3 * x, 4 * y);

    delayKnob.setBounds(7.1 * x, 3*y, 3 * x, 4 * y);

    pluginTitle.setBounds(3.5*x, y-80, 4 * x, 4 * y);

    imageComponent.setBounds(3.2*x, 1.1*y, 4*x, 8*y);

    lowPassKnob.setBounds(0, 5.5*y, 3 * x, 4 * y);

}
