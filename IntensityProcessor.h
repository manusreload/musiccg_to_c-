/* 
 * File:   IntensityProcessor.h
 * Author: antwalls
 *
 * Created on 17 de marzo de 2015, 17:32
 */

#ifndef INTENSITYPROCESSOR_H
#define	INTENSITYPROCESSOR_H
#include <vector> 
using namespace std;

class IntensityProcessor 
{
private:
    vector<vector<double> >* intensities;
    int numPointsPerFrame;
    
public:
    IntensityProcessor();
    IntensityProcessor(vector<vector<double> > intensities, int numPointsPerFrame);
    void execute();
    vector<vector<double> > getIntensities();
    IntensityProcessor(const IntensityProcessor& orig);
    virtual ~IntensityProcessor();

};

#endif	/* INTENSITYPROCESSOR_H */

