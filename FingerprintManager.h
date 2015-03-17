/* 
 * File:   FingerprintManager.h
 * Author: antwalls
 *
 * Created on 16 de marzo de 2015, 13:12
 */

#ifndef FINGERPRINTMANAGER_H
#define	FINGERPRINTMANAGER_H
typedef unsigned char    byte;
#define MAX_VAUE        INT_MAX;        

#include <vector>
#include <list>
#include <limits>
#include <fstream>
#include "Spectogram.h"
#include "auxiliar.h"
#include <FingerprintProperties.h>
using namespace std;

class FingerprintManager 
{
private:
        FingerprintProperties* fingerprintProperties    = FingerprintProperties.getInstance();
        int sampleSizePerFrame                          = fingerprintProperties.getSampleSizePerFrame();
        int overlapFactor                               = fingerprintProperties.getOverlapFactor();
        int numRobustPointsPerFrame                     = fingerprintProperties.getNumRobustPointsPerFrame();
        int numFilterBanks                              = fingerprintProperties.getNumFilterBanks();
public:
    FingerprintManager();
    byte* extractFingerprint(Wave wave);

    /**
     * Get bytes from fingerprint file
     * 
     * @param fingerprintFile	fingerprint filename
     * @return fingerprint in bytes
     */
    byte* getFingerprintFromFile(string fingerprintFile);
	
    /**
     * Get bytes from fingerprint inputstream
     * 
     * @param fingerprintFile	fingerprint inputstream
     * @return fingerprint in bytes
     */
     byte* getFingerprintFromInputStream(ifstream inputStream);
	
    /**
     * Save fingerprint to a file
     * 
     * @param fingerprint	fingerprint bytes
     * @param filename		fingerprint filename
     * @see	fingerprint file saved
     */
    void saveFingerprintAsFile(byte fingerprint[], string filename);

    // robustLists[x]=y1,y2,y3,...
    vector<list<int> > getRobustPointList(vector<vector<double > >spectrogramData);

    /**
     * Number of frames in a fingerprint
     * Each frame lengths 8 bytes
     * Usually there is more than one point in each frame, so it cannot simply divide the bytes length by 8
     * Last 8 byte of thisFingerprint is the last frame of this wave
     * First 2 byte of the last 8 byte is the x position of this wave, i.e. (number_of_frames-1) of this wave	 
     * 
     * @param fingerprint	fingerprint bytes
     * @return number of frames of the fingerprint
     */
    static int getNumFrames(vector<byte> fingerprint);
    
    FingerprintManager(const FingerprintManager& orig);
    virtual ~FingerprintManager();

};

#endif	/* FINGERPRINTMANAGER_H */

