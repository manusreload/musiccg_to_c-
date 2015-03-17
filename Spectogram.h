/* 
 * File:   Spectogram.h
 * Author: antwalls
 *
 * Created on 16 de marzo de 2015, 17:55
 */

#ifndef SPECTOGRAM_H
#define	SPECTOGRAM_H

#include <vector>

using namespace std;
class Spectogram 
{
public:  
       
        static int SPECTROGRAM_DEFAULT_FFT_SAMPLE_SIZE = 1024;
        static int SPECTROGRAM_DEFAULT_OVERLAP_FACTOR = 0;	// 0 for no overlapping
	
private:
	Wave wave;
	vector<vector<double> > spectrogram;	// relative spectrogram
	vector<vector<double> > absoluteSpectrogram;	// absolute spectrogram
	int                     fftSampleSize;	// number of sample in fft, the value needed to be a number to power of 2
	int                     overlapFactor;	// 1/overlapFactor overlapping, e.g. 1/4=25% overlapping
	int                     numFrames;	// number of frames of the spectrogram
	int                     framesPerSecond;	// frame per second of the spectrogram
	int                     numFrequencyUnit;	// number of y-axis unit
	double                  unitFrequency;	// frequency per y-axis unit
public:
    Spectogram();
    /**
     * Constructor
     * 
     * @param wave
     */
    Spectrogram(Wave wave); 

    /**
     * Constructor
     * 
     * @param wave
     * @param fftSampleSize	number of sample in fft, the value needed to be a number to power of 2
     * @param overlapFactor	1/overlapFactor overlapping, e.g. 1/4=25% overlapping, 0 for no overlapping
     */
    Spectrogram(Wave wave, int fftSampleSize, int overlapFactor) ;

    /**
     * Build spectrogram
     */
    void buildSpectrogram();

    /**
     * Get spectrogram: spectrogram[time][frequency]=intensity
     * 
     * @return	logarithm normalized spectrogram
     */
    vector<vector<double> > getNormalizedSpectrogramData();
    /**
     * Get spectrogram: spectrogram[time][frequency]=intensity
     * 
     * @return	absolute spectrogram
     */
    vector<vector<double> > getAbsoluteSpectrogramData();
    /**
     * Get the frequency intensities
     * 
     * @param amplitudes
     *            amplitudes of the signal
     * @return intensities of each frequency unit: mag[frequency_unit]=intensity
     */
    vector<double> getFFTMagnitudes(vector<double> amplitudes) ;
    
    int getNumFrames();
    int getFramesPerSecond();
    int getNumFrequencyUnit();
    double getUnitFrequency();
    int getFftSampleSize() ;
    int getOverlapFactor() ;
    Spectogram(const Spectogram& orig);
    virtual ~Spectogram();

};

#endif	/* SPECTOGRAM_H */

