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
    mDelayBuffer = nullptr;
}

Ddl::~Ddl()
{
   if(mDelayBuffer)
       delete [] mDelayBuffer;
}

void Ddl::setSize(int size)
{
    mDelayBufferSize = size;
    
    if(mDelayBuffer)
        delete [] mDelayBuffer;
    
    mDelayBuffer = new float[mDelayBufferSize];
}

void Ddl::resetDelay()
{
    if(mDelayBuffer)
        std::memset(mDelayBuffer, 0,mDelayBufferSize*sizeof(float));
}

void Ddl::calculateVariables(float sampleRate)
{
    
    mFeedback /= 100.0;
    mWetLevel /= 100.0;
    mDelayInSamples *= (sampleRate/1000.0);
    
}
