/* 
 * File:   Spectogram.cpp
 * Author: antwalls
 * 
 * Created on 16 de marzo de 2015, 17:55
 */

#include "Spectogram.h"

Spectogram::Spectogram() 
{
}

int bitcount(int i)
{
    unsigned int cnt = 0, MASK;

    for (MASK = 0x1; MASK != 0; MASK <<= 1)
    {
        if ((MASK & i) == MASK)
        cnt++;
    }
    
    return cnt;
}


/**
 * Constructor
 * 
 * @param wave
 */
Spectogram::Spectrogram(Wave wave) 
{
        this.wave=wave;
        // default
        this.fftSampleSize=SPECTROGRAM_DEFAULT_FFT_SAMPLE_SIZE;
        this.overlapFactor=SPECTROGRAM_DEFAULT_OVERLAP_FACTOR;
        buildSpectrogram();
}

/**
 * Constructor
 * 
 * @param wave
 * @param fftSampleSize	number of sample in fft, the value needed to be a number to power of 2
 * @param overlapFactor	1/overlapFactor overlapping, e.g. 1/4=25% overlapping, 0 for no overlapping
 */
Spectogram::Spectrogram(Wave wave, int fftSampleSize, int overlapFactor) 
{
        this.wave=wave;

        if (bitcount(fftSampleSize)==1){
                this.fftSampleSize=fftSampleSize;
        }
        else{
                printf("The input number must be a power of 2");
                this.fftSampleSize=SPECTROGRAM_DEFAULT_FFT_SAMPLE_SIZE;
        }

        this.overlapFactor = overlapFactor;

        buildSpectrogram();
}

/**
 * Build spectrogram
 */
void Spectogram::buildSpectrogram()
{

        vector<short> amplitudes=wave.getSampleAmplitudes();
        int numSamples = amplitudes.size();

        int pointer=0;
        // overlapping
        if (overlapFactor>1){
                int numOverlappedSamples        = numSamples*overlapFactor;
                int backSamples                 = fftSampleSize*(overlapFactor-1)/overlapFactor;
                int fftSampleSize_1             = fftSampleSize-1;
                vector<short> overlapAmp        = vector<short>(numOverlappedSamples);
                pointer                         = 0;
                for (int i=0; i<amplitudes.size(); i++)
                {
                        overlapAmp[pointer++] = amplitudes[i];
                        if (pointer % fftSampleSize == fftSampleSize_1)
                        {
                                // overlap
                                i -= backSamples;
                        }
                }
                numSamples=numOverlappedSamples;
                amplitudes=overlapAmp;
        }
        // end overlapping

        numFrames=numSamples/fftSampleSize;
        framesPerSecond=(int)(numFrames/wave.length());	

        // set signals for fft
        WindowFunction window = WindowFunction();
        window.setWindowType("Hamming");
        vector<double> win = window.generate(fftSampleSize);

        vector<vector<double> >signals=new double[numFrames][];
        for(int f=0; f<numFrames; f++) 
        {
                signals[f] = new double[fftSampleSize];
                int startSample = f*fftSampleSize;
                for (int n = 0; n<fftSampleSize; n++)
                {
                        signals[f][n]=amplitudes[startSample+n]*win[n];							
                }
        }
        // end set signals for fft

        absoluteSpectrogram=new double[numFrames][];
        // for each frame in signals, do fft on it
        FastFourierTransform fft = FastFourierTransform();
        for (int i=0; i<numFrames; i++){			
                absoluteSpectrogram[i] = fft.getMagnitudes(signals[i]);
        }

        if (absoluteSpectrogram.size()>0){

                numFrequencyUnit=absoluteSpectrogram[0].length;
                unitFrequency=(double)wave.getWaveHeader().getSampleRate()/2/numFrequencyUnit;	// frequency could be caught within the half of nSamples according to Nyquist theory

                // normalization of absoultSpectrogram
                spectrogram=new double[numFrames][numFrequencyUnit];

                // set max and min amplitudes
                double maxAmp = DOUBLE_MIN_VALUE;
                double minAmp = DOUBLE_MAX_VALUE;	
                for (int i=0; i<numFrames; i++){
                        for (int j=0; j<numFrequencyUnit; j++){
                                if (absoluteSpectrogram[i][j]>maxAmp){
                                        maxAmp=absoluteSpectrogram[i][j];
                                }
                                else if(absoluteSpectrogram[i][j]<minAmp){
                                        minAmp=absoluteSpectrogram[i][j];
                                }
                        }
                }
                // end set max and min amplitudes

                // normalization
                // avoiding divided by zero 
                double minValidAmp = 0.00000000001F;
                if (minAmp==0){
                        minAmp=minValidAmp;
                }

                double diff = log10(maxAmp/minAmp);	// perceptual difference
                for (int i=0; i<numFrames; i++){
                        for (int j=0; j<numFrequencyUnit; j++){
                                if (absoluteSpectrogram[i][j]<minValidAmp){
                                        spectrogram[i][j]=0;
                                }
                                else{
                                        spectrogram[i][j]=(log10(absoluteSpectrogram[i][j]/minAmp))/diff;
                                }
                        }
                }
                // end normalization
        }
}

/**
 * Get spectrogram: spectrogram[time][frequency]=intensity
 * 
 * @return	logarithm normalized spectrogram
 */
vector<vector<double> > Spectogram::getNormalizedSpectrogramData(){
        return spectrogram;
}

/**
 * Get spectrogram: spectrogram[time][frequency]=intensity
 * 
 * @return	absolute spectrogram
 */
vector<vector<double> > Spectogram::getAbsoluteSpectrogramData()
{
        return absoluteSpectrogram;
}
int Spectogram::getNumFrames()
{
        return numFrames;
}
int Spectogram::getFramesPerSecond()
{
        return framesPerSecond;
}
int Spectogram:: getNumFrequencyUnit()
{
        return numFrequencyUnit;
}
double Spectogram::getUnitFrequency()
{
        return unitFrequency;
}
int Spectogram::getFftSampleSize() 
{
        return fftSampleSize;
}
int Spectogram::getOverlapFactor() 
{
        return overlapFactor;
}

Spectogram::Spectogram(const Spectogram& orig) {
}

Spectogram::~Spectogram() {
}

