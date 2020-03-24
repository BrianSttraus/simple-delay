/*
  ==============================================================================

    DDL.h
    Created: 24 Mar 2020 10:31:34am
    Author:  Brian Roman 

  ==============================================================================
*/

#pragma once

class Ddl
{
public:
    Ddl();
    ~Ddl();
    
    void calculateVariables(float sampleRate);
    void setSize(int size);
    void resetDelay();
    
    float getSample(int index){return mDelayBuffer[index];};
    void setSample(float samp, int index){ mDelayBuffer[index] = samp;};
    
    float getCurrentFeedbackOutput();
    void setCurrentFeedbackInput(float f){mFeedbackIn = f;}
    void setUsesExternalFeedback(bool b){mUseExternalFeedback = b;}
    bool mUseExternalFeedback{false};
    
    float mFeedbackIn;
    float mDelayInSamples, mFeedback, mWetLevel;
    
private:
    
    float* mDelayBuffer;
    int mDelayBufferSize;
    
};
