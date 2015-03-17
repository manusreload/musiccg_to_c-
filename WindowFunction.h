/* 
 * File:   WindowFunction.h
 * Author: antwalls
 *
 * Created on 17 de marzo de 2015, 11:35
 */

#ifndef WINDOWFUNCTION_H
#define	WINDOWFUNCTION_H

#include <vector>
#include "auxiliar.h"
using namespace std;

class WindowFunction 
{
public:
    
    static  int RECTANGULAR = 0;
    static  int BARTLETT = 1;
    static  int HANNING = 2;
    static  int HAMMING = 3;
    static  int BLACKMAN = 4;
    
    int windowType = 0; // defaults to rectangular window
    
    WindowFunction();
    
    void setWindowType(int wt) ;
    void setWindowType(string w) ;
    int getWindowType() ;
    /**
    * Generate a window
    * 
    * @param nSamples	size of the window
    * @return	window in array
    */
    vector<double> generate(int nSamples);

    
    WindowFunction(const WindowFunction& orig);
    virtual ~WindowFunction();
private:

};

#endif	/* WINDOWFUNCTION_H */

