/* 
 * File:   IntensityProcessor.cpp
 * Author: antwalls
 * 
 * Created on 17 de marzo de 2015, 17:32
 */

#include <string.h>

#include "IntensityProcessor.h"

IntensityProcessor::IntensityProcessor() 
{
    
}
IntensityProcessor::IntensityProcessor(vector<vector<double> > intensities, int numPointsPerFrame)
{
        this.intensities=intensities;
        this.numPointsPerFrame=numPointsPerFrame;
}
void IntensityProcessor::execute()
{
        int numX=intensities.size();
        int numY=intensities[0].size();
        vector<vector<double> > processedIntensities = vector<vector<double>(numX);
        for (int i = 0; i < numX; i++) 
        {
            processedIntensities[i] = vector<double>(numY);
        }
        for (int i=0; i<numX; i++)
        {
                vector<double> tmpArray = vector<double>(numY);
                memcpy(tmpArray,intensities[i],numY);

                // pass value is the last some elements in sorted array	
                ArrayRankDouble arrayRankDouble=new ArrayRankDouble();
                double passValue=arrayRankDouble.getNthOrderedValue(tmpArray,numPointsPerFrame,false);

                // only passed elements will be assigned a value
                for (int j=0; j<numY; j++)
                {
                        if (intensities[i][j]>=passValue)
                        {
                                processedIntensities[i][j]=intensities[i][j];
                        }
                }
        }
        intensities=processedIntensities;
}

vector<vector<double> > IntensityProcessor::getIntensities()
{
        return intensities;
}

IntensityProcessor::IntensityProcessor(const IntensityProcessor& orig) {
}

IntensityProcessor::~IntensityProcessor() {
}

