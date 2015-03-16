/* 
 * File:   FingerprintProperties.cpp
 * Author: antwalls
 * 
 * Created on 16 de marzo de 2015, 12:40
 */

#include "FingerprintProperties.h"

//FingerprintProperties::FingerprintProperties() {
//}

FingerprintProperties::FingerprintProperties(const FingerprintProperties& orig) 
{
}

FingerprintProperties FingerprintProperties::getInstance()
{		
    if (instance == 0)
    {
            if(instance == 0) {
                 instance = new FingerprintProperties();
            }
    }
    return instance;
}
int FingerprintProperties::getNumRobustPointsPerFrame() 
{
        return numRobustPointsPerFrame;
}
int FingerprintProperties::getSampleSizePerFrame() 
{
        return sampleSizePerFrame;
}
int FingerprintProperties::getOverlapFactor() 
{
        return overlapFactor;
}
int FingerprintProperties::getNumFilterBanks() 
{
        return numFilterBanks;
}
int FingerprintProperties::getUpperBoundedFrequency() 
{
        return upperBoundedFrequency;
}
int FingerprintProperties::getLowerBoundedFrequency() 
{
        return lowerBoundedFrequency;
}
int FingerprintProperties::getFps() 
{
        return fps;
}
int FingerprintProperties::getRefMaxActivePairs() 
{
        return refMaxActivePairs;
}
int FingerprintProperties::getSampleMaxActivePairs() 
{
        return sampleMaxActivePairs;
}
int FingerprintProperties::getNumAnchorPointsPerInterval() 
{
        return numAnchorPointsPerInterval;
}
int FingerprintProperties::getAnchorPointsIntervalLength() 
{
        return anchorPointsIntervalLength;
}
int FingerprintProperties::getMaxTargetZoneDistance() 
{
        return maxTargetZoneDistance;
}
int FingerprintProperties::getNumFrequencyUnits() 
{
        return numFrequencyUnits;
}
int FingerprintProperties::getMaxPossiblePairHashcode()
{
        return maxTargetZoneDistance*numFrequencyUnits*numFrequencyUnits+numFrequencyUnits*numFrequencyUnits+numFrequencyUnits;
}
int FingerprintProperties::getSampleRate() 
{
        return sampleRate;
}
int FingerprintProperties::getNumFramesInOneSecond() 
{
        return numFramesInOneSecond;
}
FingerprintProperties::~FingerprintProperties()
{
}

