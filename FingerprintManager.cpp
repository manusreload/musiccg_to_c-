/* 
 * File:   FingerprintManager.cpp
 * Author: antwalls
 * 
 * Created on 16 de marzo de 2015, 13:12
 */

#include "FingerprintManager.h"


FingerprintManager::FingerprintManager() {
}

byte* FingerprintManager::extractFingerprint(Wave wave)
{

    int**   coordinates;	// coordinates[x][0..3]=y0..y3
    byte* fingerprint=new byte[0];

    // resample to target rate
    Resampler resampler =       new Resampler();
    int sourceRate      =       wave.getWaveHeader().getSampleRate();
    int targetRate      =       fingerprintProperties.getSampleRate();

    byte resampledWaveData[] = resampler.reSample(wave.getBytes(), wave.getWaveHeader().getBitsPerSample(), sourceRate, targetRate);

    // update the wave header
    WaveHeader resampledWaveHeader = wave.getWaveHeader();
    resampledWaveHeader.setSampleRate(targetRate);

    // make resampled wave
    Wave resampledWave = Wave(resampledWaveHeader, resampledWaveData);
    // end resample to target rate

    // get spectrogram's data
    Spectogram spectrogram = resampledWave.getSpectrogram(sampleSizePerFrame, overlapFactor);
    vector<vector<double> > spectorgramData = spectrogram.getNormalizedSpectrogramData();

    vector<list<int> > pointsLists = getRobustPointList(spectorgramData);
    int numFrames = pointsLists.size();

    // prepare fingerprint bytes
    coordinates = new int[numFrames][numRobustPointsPerFrame];

    for (int x = 0; x < numFrames; x++) {
        if (pointsLists[x].size() == numRobustPointsPerFrame) 
        {
            list<int>::iterator pointsListsIterator = pointsLists[x].begin();
            for (int y = 0; y < numRobustPointsPerFrame; y++) 
            {
                coordinates[x][y] = (*pointsListsIterator);
                pointsListsIterator++;
            }
        } else 
        {
            // use -1 to fill the empty byte
            for (int y = 0; y < numRobustPointsPerFrame; y++) 
            {
                coordinates[x][y] = -1;
            }
        }
    }
    // end make fingerprint

    // for each valid coordinate, append with its intensity
    list<byte> byteList = list<byte>();
    for (int i = 0; i < numFrames; i++) 
    {
        for (int j = 0; j < numRobustPointsPerFrame; j++) 
        {
            if (coordinates[i][j] != -1) 
            {
                // first 2 bytes is x
                int x = i;
                byteList.push_back((byte) (x >> 8));
                byteList.push_back(((byte) x));

                // next 2 bytes is y
                int y = coordinates[i][j];
                byteList.push_back((byte) (y >> 8));
                byteList.push_back((byte) y);

                // next 4 bytes is intensity
                int intensity = (int) (spectorgramData[x][y] * INT_MAX_VALUE); // spectorgramData is ranged from 0~1
                byteList.push_back((byte) (intensity >> 24));
                byteList.push_back((byte) (intensity >> 16));
                byteList.push_back((byte) (intensity >> 8));
                byteList.push_back((byte) intensity);
            }
        }
    }
    // end for each valid coordinate, append with its intensity

    fingerprint                           = new byte[byteList.size()];
    list<byte>::iterator byteListIterator = byteList.begin();
    int                         pointer   = 0;
    while (byteListIterator != byteList.end()) 
    {
        fingerprint[pointer++] = *(++byteListIterator);
    }

    return fingerprint;
}
/**
 * Get bytes from fingerprint file
 * 
 * @param fingerprintFile	fingerprint filename
 * @return fingerprint in bytes
 */
byte* getFingerprintFromFile(string fingerprintFile) 
{
    byte* fingerprint = 0;
    try {
        ifstream fis = ifstream(fingerprintFile);
        fingerprint = getFingerprintFromInputStream(fis);
        fis.close();
    } catch (exception& e) 
    {
        cout<<"Exception getFingerprontFromFile"<<endl;
    } 
    return fingerprint;
}

/**
 * Get bytes from fingerprint inputstream
 * 
 * @param fingerprintFile	fingerprint inputstream
 * @return fingerprint in bytes
 */
byte* getFingerprintFromInputStream(ifstream inputStream)
{		
        byte* fingerprint       = 0;
        int fingerprint_size    = 0;
        try 
        {
            inputStream.seekg(0,ifstream::end);
            fingerprint_size    = inputStream.tellg();
            fingerprint         = byte[fingerprint_size];
            inputStream.read(fingerprint,fingerprint_size);
        } catch (exception& e) 
        {
            cout<<"Exception reading fingerprint file"<<endl;
        }
        return fingerprint;
}

/**
 * Save fingerprint to a file
 * 
 * @param fingerprint	fingerprint bytes
 * @param filename		fingerprint filename
 * @see	fingerprint file saved
 */
void FingerprintManager::saveFingerprintAsFile(byte fingerprint[], string filename){

        ofstream fileOutputStream;
        try {
                fileOutputStream = ofstream(filename);
                fileOutputStream.write(fingerprint);
                fileOutputStream.close();
        } catch (exception& e1) 
        {
            cout<<"File not found"<<endl;
        } 
}

// robustLists[x]=y1,y2,y3,...
vector<list<int> > FingerprintManager::getRobustPointList(vector<vector<double > >spectrogramData){

        int numX = spectrogramData.size();
        int numY = spectrogramData[0].size();

        vector<vector<double> > allBanksIntensities    = vector<vector<double> > (numX);
        for (int i = 0; i < numX; i++) 
        {
            allBanksIntensities[i] = vector<double>(numY);  
        }
        int bandwidthPerBank            = numY/numFilterBanks;

        for (int b=0; b<numFilterBanks; b++)
        {

            double** bankIntensities = new double[numX][bandwidthPerBank];

            for (int i=0; i<numX; i++)
            {
                    for (int j=0; j<bandwidthPerBank; j++)
                    {
                            bankIntensities[i][j] = spectrogramData[i][j + b * bandwidthPerBank];
                    }
            }
            // get the most robust point in each filter bank
            TopManyPointsProcessorChain processorChain          = TopManyPointsProcessorChain(bankIntensities,1);
            vector<vector<double> > processedIntensities        = processorChain.getIntensities();

            for (int i=0; i<numX; i++){
                    for (int j=0; j<bandwidthPerBank; j++){
                            allBanksIntensities[i][j+b*bandwidthPerBank]=processedIntensities[i][j];
                    }
            }
        }

        list<vector<int> > robustPointList=list<vector<int> >();

        // find robust points
        for (int i=0; i< allBanksIntensities.size(); i++)
        {
                for (int j=0; j<allBanksIntensities[i].size(); j++)
                {	
                        if (allBanksIntensities[i][j]>0)
                        {
                                vector<int> point=vector<int>(2);
                                point[0] = i;
                                point[1] = j;
                                //System.out.println(i+","+frequency);
                                robustPointList.push_back(point);
                        }
                }
        }
        // end find robust points

        vector<list<int> > robustLists=vector<list<int> >[spectrogramData.size()];
        for (int i=0; i<robustLists.size(); i++)
        {
            robustLists[i]=list<int>();
        }

        // robustLists[x]=y1,y2,y3,...
        vector<list<int> > robustPointListIterator = robustPointList.iterator();
        while (robustPointListIterator != robustPointList.end())
        {
                vector<int> coor = *(++robustPointListIterator);
                robustLists[coor[0]].add(coor[1]);
               
        }

        // return the list per frame
        return robustLists;
}

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
int FingerprintManager::getNumFrames(vector<byte> fingerprint){

        if (fingerprint.size()<8){
                return 0;
        }
        // get the last x-coordinate (length-8&length-7)bytes from fingerprint
        int numFrames=((int)(fingerprint[fingerprint.size() - 8] & 0xff ) << 8 | (int)(fingerprint[fingerprint.size() - 7]&0xff )) + 1 ;
        return numFrames;
}
FingerprintManager::FingerprintManager(const FingerprintManager& orig) {
}

FingerprintManager::~FingerprintManager() {
}

