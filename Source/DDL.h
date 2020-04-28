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
    
    void calculateVariables(float feedback, float wet, float delaytime, float sampleRate);
    void setSize(int srate);
    void resetDelay();
    
    int getDelayBufferSize(){return mDelayBufferSize;};
    
    //float& operator[](int index) const {return mDelayBuffer[index];};
    void delayLineProcessor(float* sample, float delayTime);
    void setSample(float samp, int index){ mDelayBuffer[index] = samp;};
    
    void setCurrentFeedbackInput(float f){mFeedbackIn = f;}
    void setUsesExternalFeedback(bool b){mUseExternalFeedback = b;}
    
    bool mUseExternalFeedback{false};
    float mFeedbackIn;
    
    
    
private:
    float mDelayInSamples, mFeedback, mWetLevel;
    int mReadindex, mWriteIndex;
    float* mDelayBuffer;
    int mDelayBufferSize;
    float mDelayTimeSmoothed;
    float sRate;
    
};
