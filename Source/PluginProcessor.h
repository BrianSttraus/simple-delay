/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "DDL.h"

//==============================================================================
/**
*/
class DdlmoduleAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    DdlmoduleAudioProcessor();
    ~DdlmoduleAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
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
    
    float getCurrentFeedbackOutput();
    void setCurrentFeedbackInput(float f){mFeedbackIn = f;}
    void setUsesExternalFeedback(bool b){mUseExternalFeedback = b;}

    bool mUseExternalFeedback{false};
    float mFeedbackIn;
    
private:
    
    AudioProcessorValueTreeState parameters;
//    float mDelayInSamples, mFeedback, mWetLevel;
//    AudioBuffer<float> mDelayBuffer;
    
//    int mDelayBufferSize;
    
    Ddl delayLine;
    int mDelaySize;
    int mReadindex, mWriteIndex;
    std::atomic<float>* delaySliderValue;
    std::atomic<float>* feedbackSliderValue;
    std::atomic<float>* wetSliderValue;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DdlmoduleAudioProcessor)
};
