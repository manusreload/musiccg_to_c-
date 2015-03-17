/* 
 * File:   Resampler.h
 * Author: antwalls
 *
 * Created on 16 de marzo de 2015, 16:59
 */

#ifndef RESAMPLER_H
#define	RESAMPLER_H

typedef unsigned char    byte;

#include <vector>

using namespace std;

class Resampler {
public:
    Resampler();
    /**
     * Do resampling. Currently the amplitude is stored by short such that maximum bitsPerSample is 16 (bytePerSample is 2)
     * 
     * @param sourceData	The source data in bytes
     * @param bitsPerSample	How many bits represents one sample (currently supports max. bitsPerSample=16) 
     * @param sourceRate	Sample rate of the source data
     * @param targetRate	Sample rate of the target data
     * @return re-sampled data
     */
    vector<byte> reSample(vector<byte> sourceData, int bitsPerSample, int sourceRate, int targetRate);
    
    /**
     * Do interpolation on the samples according to the original and destinated sample rates
     * 
     * @param oldSampleRate	sample rate of the original samples
     * @param newSampleRate	sample rate of the interpolated samples
     * @param samples	original samples
     * @return interpolated samples
     */
     vector<short> interpolate(int oldSampleRate, int newSampleRate, vector<short> samples);

    Resampler(const Resampler& orig);
    virtual ~Resampler();
private:

};

#endif	/* RESAMPLER_H */

