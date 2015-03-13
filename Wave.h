/* 
 * File:   Wave.h
 * Author: antwalls
 *
 * Created on 13 de marzo de 2015, 11:45
 */

#ifndef WAVE_H
#define	WAVE_H

using namespace std;

class Wave 
{
private:
   static long serialVersionUID = 1L;
   WaveHeader waveHeader;
   unsigned char data[];	// little endian
   unsigned char fingerprint[];
public:
    Wave();
    Wave(string name);
    Wave(iostream inputStream);
    Wave(const Wave& orig);
    virtual ~Wave();

};

#endif	/* WAVE_H */

