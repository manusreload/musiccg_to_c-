/* 
 * File:   WaveHeader.h
 * Author: antwalls
 *
 * Created on 13 de marzo de 2015, 10:07
 */

#ifndef WAVEHEADER_H
#define	WAVEHEADER_H
using namespace std;
#include <string>
#include <iostream>

class WaveHeader 
{
public:
        static string RIFF_HEADER = "RIFF";
	static string WAVE_HEADER = "WAVE";
	static string FMT_HEADER = "fmt ";
	static string DATA_HEADER = "data";
	static int HEADER_BYTE_LENGTH = 44;	// 44 bytes for header
   
private:
    
	bool valid;
	string chunkId;	// 4 bytes
	long chunkSize; // unsigned 4 bytes, little endian
	string format;	// 4 bytes
	string subChunk1Id;	// 4 bytes
	long subChunk1Size; // unsigned 4 bytes, little endian
	int audioFormat; // unsigned 2 bytes, little endian
	int channels; // unsigned 2 bytes, little endian
	long sampleRate; // unsigned 4 bytes, little endian
	long byteRate; // unsigned 4 bytes, little endian
	int blockAlign; // unsigned 2 bytes, little endian
	int bitsPerSample; // unsigned 2 bytes, little endian
	string subChunk2Id;	// 4 bytes
	long subChunk2Size; // unsigned 4 bytes, little endian
public:
    WaveHeader();
    WaveHeader(iostream inputStream);
    WaveHeader(const WaveHeader& orig);
    bool        loadHeader(iostream inputStream);
    bool        isValid() ;
    string      getChunkId(); 
    long        getChunkSize();
    string      getFormat(); 
    string      getSubChunk1Id(); 
    long        getSubChunk1Size(); 
    int         getAudioFormat(); 
    int         getChannels(); 
    int         getSampleRate(); 
    int         getByteRate(); 
    int         getBlockAlign();
    int         getBitsPerSample(); 
    string      getSubChunk2Id(); 
    long        getSubChunk2Size(); 
    void        setSampleRate(int sampleRate);
    void        setChunkId(string chunkId);
    void        setChunkSize(long chunkSize); 
    void        setFormat(string format) ;
    void        setSubChunk1Id(string subChunk1Id) ;
    void        setSubChunk1Size(long subChunk1Size) ;
    void        setAudioFormat(int audioFormat) ;
    void        setChannels(int channels) ;
    void        setByteRate(long byteRate);
    void        setBlockAlign(int blockAlign) ;
    void        setBitsPerSample(int bitsPerSample) ;
    void        setSubChunk2Id(string subChunk2Id) ;
    void        setSubChunk2Size(long subChunk2Size) ;
    string      toString() ;
    
    
    virtual ~WaveHeader();


};

#endif	/* WAVEHEADER_H */

