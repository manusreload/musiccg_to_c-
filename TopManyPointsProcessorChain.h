/* 
 * File:   TopManyPointsProcessorChain.h
 * Author: antwalls
 *
 * Created on 17 de marzo de 2015, 17:12
 */

#ifndef TOPMANYPOINTSPROCESSORCHAIN_H
#define	TOPMANYPOINTSPROCESSORCHAIN_H

#include <list> 
#include <vector>

using namespace std;

class TopManyPointsProcessorChain 
{
private:
    list<IntensityProcessor>    processorList = list<IntensityProcessor>();
    vector<vector<double> >     intensities;
public:
    TopManyPointsProcessorChain();
    TopManyPointsProcessorChain(vector<vector<double> > intensities, int numPoints)
    {
        this.intensities=intensities;
        IntensityProcessor robustProcessor = IntensityProcessor(intensities,numPoints);
        processorList.push_back(robustProcessor);
        process();
    }
    vector<vector<double> > getIntensities()
    {
        return intensities;
    }
private:
    void process()
    {
        list<IntensityProcessor>::iterator iterator=processorList.iterator();
        while(iterator != processorList.end())
        {
                IntensityProcessor processor = *(++iterator);
                processor.execute();
                intensities = processor.getIntensities();
        }
    }

    TopManyPointsProcessorChain(const TopManyPointsProcessorChain& orig);
    virtual ~TopManyPointsProcessorChain();

};

#endif	/* TOPMANYPOINTSPROCESSORCHAIN_H */

