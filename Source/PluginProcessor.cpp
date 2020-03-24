/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
DdlmoduleAudioProcessor::DdlmoduleAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       ), parameters(*this, nullptr,"Parameter",
                                     {
                           std::make_unique<AudioParameterFloat>("delay",
                                                                 "Delay",
                                                                 0.0f,
                                                                 2000.0f,
                                                                 0.0f),
                           std::make_unique<AudioParameterFloat>("feedback",
                                                                 "Feedback",
                                                                 -100.0f,
                                                                 100.0f,
                                                                 0.0f),
                           std::make_unique<AudioParameterFloat>("wet",
                                                                 "Wet/Dry",
                                                                 0.0f,
                                                                 100.0f,
                                                                 50.0f),
                       })
#endif
{
    //get slider parameter values
    delaySliderValue = parameters.getRawParameterValue("delay");
    feedbackSliderValue = parameters.getRawParameterValue("feedback");
    wetSliderValue = parameters.getRawParameterValue("wet");
    mDelaySize = 0;
    mReadindex = 0;
    mWriteIndex = 0;
   
}

//float DdlmoduleAudioProcessor::getCurrentFeedbackOutput()
//{
//    auto delayBuffer = mDelayBuffer.getReadPointer(0);
//    return mFeedback * delayBuffer[mReadindex];
//}

DdlmoduleAudioProcessor::~DdlmoduleAudioProcessor()
{
}

//==============================================================================
const String DdlmoduleAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool DdlmoduleAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool DdlmoduleAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool DdlmoduleAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double DdlmoduleAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int DdlmoduleAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int DdlmoduleAudioProcessor::getCurrentProgram()
{
    return 0;
}

void DdlmoduleAudioProcessor::setCurrentProgram (int index)
{
}

const String DdlmoduleAudioProcessor::getProgramName (int index)
{
    return {};
}

void DdlmoduleAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================


void DdlmoduleAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    //intialize delay line size. 2 sec max
    mDelaySize = int(2*sampleRate);
    delayLine.setSize(mDelaySize);
    //clear delay line before audio stream
    delayLine.resetDelay();
    //set delay line variables before audio stream
    delayLine.mDelayInSamples = *delaySliderValue;
    delayLine.mFeedback = *feedbackSliderValue;
    delayLine.mWetLevel = *wetSliderValue;
    delayLine.calculateVariables(sampleRate);
    
    //set read index and wrap around circular buffer
    mReadindex = mWriteIndex - (int)delayLine.mDelayInSamples;
    if(mReadindex<0)
        mReadindex += mDelaySize;
    
}

void DdlmoduleAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool DdlmoduleAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
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

void DdlmoduleAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    //calculate variables and position of read head for each new audio buffer
    delayLine.mDelayInSamples = *delaySliderValue;
    delayLine.mFeedback = *feedbackSliderValue;
    delayLine.mWetLevel = *wetSliderValue;
    delayLine.calculateVariables((float)getSampleRate());
    
    mReadindex = mWriteIndex - (int)delayLine.mDelayInSamples;
    if(mReadindex<0)
        mReadindex += mDelaySize;

    auto bufferIn = buffer.getReadPointer(0);
    
    auto bufferOut = buffer.getArrayOfWritePointers();
    
    
    for (int sample=0; sample<buffer.getNumSamples(); ++sample) {
       
        float xn = bufferIn[sample];

        float yn = delayLine.getSample(mReadindex);
        //if delay < 1 sample, interpolate between x and x-1
        if(mReadindex == mWriteIndex && delayLine.mDelayInSamples < 1.0)
            yn = xn;
        
        int mReadIndex_1 = mReadindex - 1;
        if(mReadIndex_1 < 0)
            mReadIndex_1 = mDelaySize-1;
            
        float yn_1 = delayLine.getSample(mReadIndex_1);
        
        //linear interpolation
        float fracDelay = delayLine.mDelayInSamples - (int)delayLine.mDelayInSamples;
        float interp = yn*fracDelay + yn_1*(1.0-fracDelay);
        
        if (delayLine.mDelayInSamples==0)
            yn = xn;
        else
            yn = interp;
        
//        if(!mUseExternalFeedback)
        delayLine.setSample(xn + delayLine.mFeedback*yn, mWriteIndex);
//        else
//            delayBuffer[mWriteIndex] = xn + mFeedbackIn;

        float out =delayLine.mWetLevel*yn + (1.0-delayLine.mWetLevel)*xn;
        bufferOut[0][sample] = out;
        bufferOut[1][sample] = out;
        
        //wrap read and write head around delay buffer
        mWriteIndex++;
        if(mWriteIndex >= mDelaySize)
            mWriteIndex = 0;
        mReadindex++;
        if(mReadindex >= mDelaySize)
            mReadindex = 0;
    }
        
        
    
}

//==============================================================================
bool DdlmoduleAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* DdlmoduleAudioProcessor::createEditor()
{
    return new DdlmoduleAudioProcessorEditor (*this,parameters);
}

//==============================================================================
void DdlmoduleAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void DdlmoduleAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new DdlmoduleAudioProcessor();
}


