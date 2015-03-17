/* 
 * File:   Resampler.cpp
 * Author: antwalls
 * 
 * Created on 16 de marzo de 2015, 16:59
 */

#include "Resampler.h"

Resampler::Resampler() {
}

vector<byte> Resampler::reSample(vector<byte> sourceData, int bitsPerSample, int sourceRate, int targetRate) 
{

    // make the bytes to amplitudes first
    int bytePerSample = bitsPerSample / 8;
    int numSamples = sourceData.size() / bytePerSample;
    short* amplitudes = new short[numSamples]; // 16 bit, use a short to store

    int pointer = 0;
    for (int i = 0; i < numSamples; i++) 
    {
        short amplitude = 0;
        for (int byteNumber = 0; byteNumber < bytePerSample; byteNumber++) 
        {
            // little endian
            amplitude |= (short) ((sourceData[pointer++] & 0xFF) << (byteNumber * 8));
        }
        amplitudes[i] = amplitude;
    }
    // end make the amplitudes

    // do interpolation
    vector<short> targetSample          = interpolate(sourceRate, targetRate, amplitudes);
    int targetLength                    = targetSample.size();
    // end do interpolation

    // TODO: Remove the high frequency signals with a digital filter, leaving a signal containing only half-sample-rated frequency information, but still sampled at a rate of target sample rate. Usually FIR is used

    // end resample the amplitudes

    // convert the amplitude to bytes
    vector<bytes> bytes;
    if (bytePerSample == 1) 
    {
        bytes = new byte[targetLength];
        for (int i = 0; i < targetLength; i++) 
        {
            bytes[i] = (byte) targetSample[i];
        }
    } else 
    {
        // suppose bytePerSample==2
        bytes = new byte[targetLength * 2];
        for (int i = 0; i < targetSample.size(); i++) 
        {
            // little endian			
            bytes[i * 2]        = (byte) (targetSample[i] & 0xff);
            bytes[i * 2 + 1]    = (byte) ((targetSample[i] >> 8) & 0xff);
        }
    }
    // end convert the amplitude to bytes

    return bytes;
}

vector<short> interpolate(int oldSampleRate, int newSampleRate, vector<short> samples)
{
    if (oldSampleRate == newSampleRate) 
    {
        return samples;
    }

    int newLength                       = (int) round(((float) samples.size() / oldSampleRate * newSampleRate));
    float lengthMultiplier              = (float) newLength / samples.size();
    vector<short> interpolatedSamples   = vector<short>(newLength);
    // interpolate the value by the linear equation y=mx+c        
    for (int i = 0; i < newLength; i++) 
    {
        // get the nearest positions for the interpolated point
        float currentPosition           = i / lengthMultiplier;
        int nearestLeftPosition         = (int) currentPosition;
        int nearestRightPosition        = nearestLeftPosition + 1;
        if (nearestRightPosition >= samples.size()) 
        {
            nearestRightPosition = samples.size() - 1;
        }
        float slope             = samples[nearestRightPosition] - samples[nearestLeftPosition]; // delta x is 1
        float positionFromLeft  = currentPosition - nearestLeftPosition;
        interpolatedSamples[i]  = (short) (slope * positionFromLeft + samples[nearestLeftPosition]); // y=mx+c
}

return interpolatedSamples;
}

Resampler::Resampler(const Resampler& orig) {
}

Resampler::~Resampler() {
}

