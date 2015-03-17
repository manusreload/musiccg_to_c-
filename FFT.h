/*
 * Copyright 2007 Sun Microsystems, Inc.  All Rights Reserved.
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 *
 * This code is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 only, as
 * published by the Free Software Foundation.  Sun designates this
 * particular file as subject to the "Classpath" exception as provided
 * by Sun in the LICENSE file that accompanied this code.
 *
 * This code is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * version 2 for more details (a copy is included in the LICENSE file that
 * accompanied this code).
 *
 * You should have received a copy of the GNU General Public License version
 * 2 along with this work; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Please contact Sun Microsystems, Inc., 4150 Network Circle, Santa Clara,
 * CA 95054 USA or visit www.sun.com if you need additional information or
 * have any questions.
 * 
 * translated to C++ by antwalls
 */

#ifndef FFT_H
#define	FFT_H
#include <vector>
#include "auxiliar.h"

using namespace std;

class FFT 
{
private:
    vector<double>      w;
    int                 fftFrameSize;
    int                 sign;
    vector<int>         bitm_array;
    int                 fftFrameSize2;
public:
    FFT();
    // Sign = -1 is FFT, 1 is IFFT (inverse FFT)
    // Data = Interlaced double array to be transformed.
    // The order is: real (sin), complex (cos)
    // Framesize must be power of 2
    FFT(int fftFrameSize, int sign);
    static vector<double> computeTwiddleFactors(int fftFrameSize,int sign);
    static void calc(int fftFrameSize, vector<double> data, int sign,vector<double> w);
    static void calcF2E(int fftFrameSize, vector<double> data, int i,int nstep, vector<double> w) ;
    // Perform Factor-4 Decomposition with 3 * complex operators and 8 +/-
    // complex operators
    static void calcF4F(int fftFrameSize, vector<double> data, int i,int nstep, vector<double> w);
    // Perform Factor-4 Decomposition with 3 * complex operators and 8 +/-
    // complex operators
    static void calcF4I(int fftFrameSize, vector<double> data, int i,int nstep, vector<double> w);
    // Perform Factor-4 Decomposition with 3 * complex operators and 8 +/-
    // complex operators
    static void calcF4FE(int fftFrameSize, vector<double> data, int i,int nstep, vector<double> w) ;
    // Perform Factor-4 Decomposition with 3 * complex operators and 8 +/-
    // complex operators
    static void calcF4IE(int fftFrameSize, vector<double> data, int i, int nstep, vector<double> w) ;
    void bitreversal(vector<double> data) ;
    void transform();
    FFT(const FFT& orig);
    virtual ~FFT();

};

#endif	/* FFT_H */

