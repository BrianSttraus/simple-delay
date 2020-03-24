/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class DdlmoduleAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    DdlmoduleAudioProcessorEditor (DdlmoduleAudioProcessor&, AudioProcessorValueTreeState&);
    ~DdlmoduleAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    typedef AudioProcessorValueTreeState::SliderAttachment SliderAttachment;
    
    AudioProcessorValueTreeState& valueTreeState;
    Label delayLabel, feedbackLabel, wetLabel;
    Slider delaySlider, feedbackSlider, wetSlider;
    
    std::unique_ptr<SliderAttachment> delayAttachment, feedbackAttachment, wetAttachment;
    
    DdlmoduleAudioProcessor& processor;

    

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DdlmoduleAudioProcessorEditor)
};
