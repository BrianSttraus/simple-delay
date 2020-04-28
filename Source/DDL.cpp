/*
  ==============================================================================

    DDL.cpp
    Created: 24 Mar 2020 10:31:34am
    Author:  Brian Roman 

  ==============================================================================
*/

#include "DDL.h"
#include <cstring>

Ddl::Ddl()
{
    mDelayInSamples = 0;
    mFeedback = 0;
    mWetLevel = 0;
    mDelayBufferSize = 0;
    mReadindex = 0;
    mWriteIndex = 0;
    mDelayTimeSmoothed = 0;
    mDelayBuffer = nullptr;
}

Ddl::~Ddl()
{
   if(mDelayBuffer)
       delete [] mDelayBuffer;
}

void Ddl::setSize(int srate)
{
    mDelayBufferSize = 2*srate;
    
    if(mDelayBuffer)
        delete [] mDelayBuffer;
    
    mDelayBuffer = new float[mDelayBufferSize];
}

void Ddl::resetDelay()
{
    if(mDelayBuffer)
        std::memset(mDelayBuffer, 0,mDelayBufferSize*sizeof(float));
}

void Ddl::calculateVariables(float feedback, float wet, float delaytime, float sampleRate)
{
    sRate = sampleRate;
    mFeedback = feedback/100.0;
    mWetLevel = wet/100.0;
    mDelayInSamples = delaytime * sRate / 1000.0;
    
    //set read index and wrap around circular buffer
       mReadindex = mWriteIndex - (int)mDelayInSamples;
       if(mReadindex<0)
           mReadindex += getDelayBufferSize();
    
    mDelayTimeSmoothed = delaytime;
}

void Ddl::delayLineProcessor(float* sample, float delayTime)
{
    mDelayInSamples = delayTime * sRate / 1000.0f;
    float xn = *sample;

    float yn = mDelayBuffer[mReadindex];
    //if delay < 1 sample, interpolate between x and x-1
    if(mReadindex == mWriteIndex && mDelayInSamples < 1.0)
        yn = xn;
    
    int mReadIndex_1 = mReadindex - 1;
    if(mReadIndex_1 < 0)
        mReadIndex_1 = mDelayBufferSize-1;
        
    float yn_1 = mDelayBuffer[mReadIndex_1];
    
    //linear interpolation
    float fracDelay = mDelayInSamples - (int)mDelayInSamples;
    float interp = yn*fracDelay + yn_1*(1.0-fracDelay);
    
    if (mDelayInSamples==0)
        yn = xn;
    else
        yn = interp;
    
//        if(!mUseExternalFeedback)
    mDelayBuffer[mWriteIndex] = xn + mFeedback*yn;
//        else
//            delayBuffer[mWriteIndex] = xn + mFeedbackIn;

    *sample = mWetLevel*yn + (1.0-mWetLevel)*xn;
    
    
    //wrap read and write head around delay buffer
    mWriteIndex++;
    if(mWriteIndex >= mDelayBufferSize)
        mWriteIndex = 0;
    mReadindex++;
    if(mReadindex >= mDelayBufferSize)
        mReadindex = 0;
}
