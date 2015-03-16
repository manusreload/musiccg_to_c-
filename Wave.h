/* 
 * File:   Wave.h
 * Author: antwalls
 *
 * Created on 13 de marzo de 2015, 11:45
 */

#ifndef WAVE_H
#define	WAVE_H

#include "WaveHeader.h"


using namespace std;

class Wave 
{
private:
   static long          serialVersionUID = 1L;
   WaveHeader           waveHeader;
   unsigned char        data[];	// little endian
   unsigned char        fingerprint[];
   int                  data_size;
public:
    Wave();
    Wave(string name);
    Wave(iostream inputStream);
    Wave(WaveHeader waveHeader, unsigned char data[]);
    void                        initWaveWithInputStream(ifstream inputStream);
    void                        trim(int leftTrimNumberOfSample, int rightTrimNumberOfSample);
    void                        leftTrim(int numberOfSample);
    void                        rightTrim(int numberOfSample);
    void                        trim(double leftTrimSecond, double rightTrimSecond);
    void                        leftTrim(double second);
    void                        rightTrim(double second);
    WaveHeader                  getWaveHeader();
    Spectrogram                 getSpectrogram();
    Spectrogram                 getSpectrogram(int fftSampleSize, int overlapFactor);
    unsigned char*              getBytes();
    int                         size();
    float                       length();
    string                      timestamp();
    short*                      getSampleAmplitudes(); 
    string                      toString();
    double*                     getNormalizedAmplitudes();
    unsigned char*              getFingerprint();
    FingerprintSimilarity       getFingerprintSimilarity(Wave wave);
    
    
    
    
    Wave(const Wave& orig);
    virtual ~Wave();

};

#endif	/* WAVE_H */

