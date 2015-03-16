/* 
 * File:   FingerprintProperties.h
 * Author: antwalls
 *
 * Created on 16 de marzo de 2015, 12:40
 */

#ifndef FINGERPRINTPROPERTIES_H
#define	FINGERPRINTPROPERTIES_H
using namespace std;

class FingerprintProperties 
{
protected:
        static FingerprintProperties* instance   =       0;
private:
    
        int numRobustPointsPerFrame     =       4;	// number of points in each frame, i.e. top 4 intensities in fingerprint
	int sampleSizePerFrame          =       2048;	// number of audio samples in a frame, it is suggested to be the FFT Size
	int overlapFactor               =       4;	// 8 means each move 1/8 nSample length. 1 means no overlap, better 1,2,4,8 ...	32
	int numFilterBanks              =       4;
	
	int upperBoundedFrequency       =       1500;	// low pass
	int lowerBoundedFrequency       =       400;	// high pass
	int fps                         =       5;	// in order to have 5fps with 2048 sampleSizePerFrame, wave's sample rate need to be 10240 (sampleSizePerFrame*fps)
	int sampleRate                  =       sampleSizePerFrame*fps;	// the audio's sample rate needed to resample to this in order to fit the sampleSizePerFrame and fps
	int numFramesInOneSecond        =       overlapFactor*fps;	// since the overlap factor affects the actual number of fps, so this value is used to evaluate how many frames in one second eventually  
	
	int refMaxActivePairs           =       1;	// max. active pairs per anchor point for reference songs
	int sampleMaxActivePairs        =       10;	// max. active pairs per anchor point for sample clip
	int numAnchorPointsPerInterval  =       10;
	int anchorPointsIntervalLength  =       4;	// in frames (5fps,4 overlap per second)
	int maxTargetZoneDistance       =       4;	// in frame (5fps,4 overlap per second)
	
	int numFrequencyUnits           =       (upperBoundedFrequency-lowerBoundedFrequency+1)/fps+1;
public:
        static FingerprintProperties getInstance();
        int getNumRobustPointsPerFrame();
	int getSampleSizePerFrame();
	int getOverlapFactor();
	int getNumFilterBanks();
	int getUpperBoundedFrequency();
	int getLowerBoundedFrequency();
	int getFps();
	int getRefMaxActivePairs();
	int getSampleMaxActivePairs();
	int getNumAnchorPointsPerInterval();
	int getAnchorPointsIntervalLength();
	int getMaxTargetZoneDistance();
	int getNumFrequencyUnits() ;
	int getMaxPossiblePairHashcode();
	int getSampleRate() ;
	int getNumFramesInOneSecond();
//        FingerprintProperties();
        FingerprintProperties(const FingerprintProperties& orig);
        virtual ~FingerprintProperties();

};

#endif	/* FINGERPRINTPROPERTIES_H */

