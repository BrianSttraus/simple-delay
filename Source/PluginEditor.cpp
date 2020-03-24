/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
DdlmoduleAudioProcessorEditor::DdlmoduleAudioProcessorEditor (DdlmoduleAudioProcessor& p, AudioProcessorValueTreeState& vts)
    : AudioProcessorEditor (&p), valueTreeState(vts), processor (p)
{
    
    addAndMakeVisible(delaySlider);
    delaySlider.setTextValueSuffix(" mSec");
    delaySlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    delaySlider.setRange(0, 2000,0.1);
    delaySlider.setValue(0);
    delaySlider.setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxBelow, false, 80, 40);
    delayAttachment.reset(new SliderAttachment(valueTreeState,"delay",delaySlider));
    
    addAndMakeVisible(delayLabel);
    delayLabel.setText("Delay", dontSendNotification);
    delayLabel.attachToComponent(&delaySlider, false);
    delayLabel.setJustificationType(Justification::centred);
    
    
    addAndMakeVisible(feedbackSlider);
    feedbackSlider.setTextValueSuffix(" %");
    feedbackSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    feedbackSlider.setRange(-100, 100,0.1);
    feedbackSlider.setValue(0);
    feedbackSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxBelow, false, 80, 40);
    feedbackAttachment.reset(new SliderAttachment(valueTreeState,"feedback",feedbackSlider));
    
    addAndMakeVisible(feedbackLabel);
    feedbackLabel.setText("Feedback", dontSendNotification);
    feedbackLabel.attachToComponent(&feedbackSlider, false);
    feedbackLabel.setJustificationType(Justification::centred);
    
    
    addAndMakeVisible(wetSlider);
    wetSlider.setTextValueSuffix(" %");
    wetSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    wetSlider.setRange(0, 100,0.1);
    wetSlider.setValue(50);
    wetSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxBelow, false, 80, 40);
    wetAttachment.reset(new SliderAttachment(valueTreeState,"wet",wetSlider));
    
    addAndMakeVisible(wetLabel);
    wetLabel.setText("Wet/Dry", dontSendNotification);
    wetLabel.attachToComponent(&wetSlider, false);
    wetLabel.setJustificationType(Justification::centred);
    
    
    setSize (400, 300);
}

DdlmoduleAudioProcessorEditor::~DdlmoduleAudioProcessorEditor()
{
}

//==============================================================================
void DdlmoduleAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setColour (Colours::white);
    
}

void DdlmoduleAudioProcessorEditor::resized()
{
    delaySlider.setBounds(20, 50, 80, getHeight()-80);
    feedbackSlider.setBounds(140, 50, 80, getHeight()-80);
    wetSlider.setBounds(260, 50, 80, getHeight()-80);
}
