/* 
 * File:   WindowFunction.cpp
 * Author: antwalls
 * 
 * Created on 17 de marzo de 2015, 11:36
 */

#include "WindowFunction.h"

WindowFunction::WindowFunction() 
{
}
void WindowFunction::setWindowType(int wt) 
{
    windowType = wt;
}

void WindowFunction::setWindowType(string w) 
{
        if (toUpperCase(w) == "RECTANGULAR" )
                windowType = RECTANGULAR;
        if (toUpperCase(w) == "BARTLETT")
                windowType = BARTLETT;
        if (toUpperCase(w) == "HANNING")
                windowType = HANNING;
        if (toUpperCase(w) == "HAMMING")
                windowType = HAMMING;
        if (toUpperCase(w) == "BLACKMAN")
                windowType = BLACKMAN;
}

int WindowFunction::getWindowType() 
{
        return windowType;
}

/**
 * Generate a window
 * 
 * @param nSamples	size of the window
 * @return	window in array
 */
vector<double> WindowFunction::generate(int nSamples) 
{
        // generate nSamples window function values
        // for index values 0 .. nSamples - 1
        int m   = nSamples / 2;
        double r;
        double pi = PI;
        vector<double> w = vector<double>[nSamples];
        switch (windowType) 
        {
            case BARTLETT: // Bartlett (triangular) window
                    for (int n = 0; n < nSamples; n++)
                            w[n] = 1.0f - abs(n - m) / m;
                    break;
            case HANNING: // Hanning window
                    r = pi / (m + 1);
                    for (int n = -m; n < m; n++)
                            w[m + n] = 0.5f + 0.5f * cos(n * r);
                    break;
            case HAMMING: // Hamming window
                    r = pi / m;
                    for (int n = -m; n < m; n++)
                            w[m + n] = 0.54f + 0.46f * cos(n * r);
                    break;
            case BLACKMAN: // Blackman window
                    r = pi / m;
                    for (int n = -m; n < m; n++)
                            w[m + n] = 0.42f + 0.5f * cos(n * r) + 0.08f
                                            * cos(2 * n * r);
                    break;
            default: // Rectangular window function
                    for (int n = 0; n < nSamples; n++)
                            w[n] = 1.0f;
        }
        return w;
}
    
WindowFunction::WindowFunction(const WindowFunction& orig) {
}

WindowFunction::~WindowFunction() {
}

