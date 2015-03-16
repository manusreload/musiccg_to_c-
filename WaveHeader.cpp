/* 
 * File:   WaveHeader.cpp
 * Author: antwalls
 * 
 * Created on 13 de marzo de 2015, 10:07
 */

#include "WaveHeader.h"

string toUpperCase(const string& _cadena)
{
    std::locale loc;
    string cadena;
    for (int i = 0; i < cadena.length(); ++i) 
    {
        cadena[i] = toupper(_cadena[i],loc);
    }
    return cadena;
}

WaveHeader::WaveHeader() 
{
    // init a 8k 16bit mono wav		
		chunkSize=36;
		subChunk1Size=16;
		audioFormat=1;
		channels=1;
		sampleRate=8000;
		byteRate=16000;
		blockAlign=2;
		bitsPerSample=16;
		subChunk2Size=0;
		valid=true;
    
}

WaveHeader::WaveHeader(const WaveHeader& orig) 
{
}

WaveHeader::~WaveHeader() 
{
}

WaveHeader::WaveHeader(iostream inputStream) 
{
    valid = loadHeader(inputStream);
}
bool WaveHeader::loadHeader(iostream inputStream)
{
    unsigned char headerBuffer[] = char[HEADER_BYTE_LENGTH];
    try{
        
        int pointer                  = 0;

        inputStream.read(headerBuffer, HEADER_BYTE_LENGTH);
        unsigned char temp[];
        temp = 
        {
            headerBuffer[pointer++],
            headerBuffer[pointer++],
            headerBuffer[pointer++],
            headerBuffer[pointer++]
        };
        chunkId     = string(temp);
        chunkSize   = (long) (headerBuffer[pointer++] & 0xff)
                | (long) (headerBuffer[pointer++] & 0xff) << 8
                | (long) (headerBuffer[pointer++] & 0xff) << 16
                | (long) (headerBuffer[pointer++] & 0xff << 24);

        temp = {headerBuffer[pointer++],
            headerBuffer[pointer++], headerBuffer[pointer++],
            headerBuffer[pointer++]};
        format = string(temp);

        temp = {headerBuffer[pointer++],
            headerBuffer[pointer++],
            headerBuffer[pointer++],
            headerBuffer[pointer++]};

        subChunk1Id = string(temp);

        subChunk1Size = (long) (headerBuffer[pointer++] & 0xff)
                        | (long) (headerBuffer[pointer++] & 0xff) << 8
                        | (long) (headerBuffer[pointer++] & 0xff) << 16
                        | (long) (headerBuffer[pointer++] & 0xff) << 24;
        audioFormat = (int) ((headerBuffer[pointer++] & 0xff) | (headerBuffer[pointer++] & 0xff) << 8);
        channels = (int) ((headerBuffer[pointer++] & 0xff) | (headerBuffer[pointer++] & 0xff) << 8);
        sampleRate = (long) (headerBuffer[pointer++] & 0xff)
                        | (long) (headerBuffer[pointer++] & 0xff) << 8
                        | (long) (headerBuffer[pointer++] & 0xff) << 16
                        | (long) (headerBuffer[pointer++] & 0xff) << 24;
        byteRate = (long) (headerBuffer[pointer++] & 0xff)
                        | (long) (headerBuffer[pointer++] & 0xff) << 8
                        | (long) (headerBuffer[pointer++] & 0xff) << 16
                        | (long) (headerBuffer[pointer++] & 0xff) << 24;
        blockAlign = (int) ((headerBuffer[pointer++] & 0xff) | (headerBuffer[pointer++] & 0xff) << 8);
        bitsPerSample = (int) ((headerBuffer[pointer++] & 0xff) | (headerBuffer[pointer++] & 0xff) << 8);

        temp  = { headerBuffer[pointer++],
                        headerBuffer[pointer++], headerBuffer[pointer++],
                        headerBuffer[pointer++] };

        subChunk2Id =  string(temp);
        subChunk2Size = (long) (headerBuffer[pointer++] & 0xff)
                        | (long) (headerBuffer[pointer++] & 0xff) << 8
                        | (long) (headerBuffer[pointer++] & 0xff) << 16
                        | (long) (headerBuffer[pointer++] & 0xff) << 24;
    }catch(exception& e)
    {
        cout<<"Exceprion loading wave header"<<endl;
    }
    if (bitsPerSample!=8 && bitsPerSample!=16)
    {
			printf("WaveHeader: only supports bitsPerSample 8 or 16");			
			return false;
    }
    if( toUpperCase(chunkId) == RIFF_HEADER && 
        toUpperCase(format) == WAVE_HEADER && 
        audioFormat == 1 )
    {
        return true;
    }else
    {
        printf("WaveHeader: Unsupported header format");			
    }
    
    return false;
    
}

bool WaveHeader::isValid() 
{
            return valid;
}
string WaveHeader::getChunkId() 
{
            return chunkId;
}
long WaveHeader::getChunkSize() 
{
            return chunkSize;
}
string WaveHeader::getFormat() 
{
        return format;
}
string WaveHeader::getSubChunk1Id() 
{
        return subChunk1Id;
}

long WaveHeader::getSubChunk1Size() 
{
        return subChunk1Size;
}
int WaveHeader::getAudioFormat() {
        return audioFormat;
}

int WaveHeader::getChannels() {
        return channels;
}

int WaveHeader::getSampleRate() {
        return (int) sampleRate;
}

int WaveHeader::getByteRate() {
        return (int) byteRate;
}
int WaveHeader::getBlockAlign() {
        return blockAlign;
}
int WaveHeader::getBitsPerSample() {
        return bitsPerSample;
}
string WaveHeader::getSubChunk2Id() {
        return subChunk2Id;
}

long WaveHeader::getSubChunk2Size() {
        return subChunk2Size;
}
void WaveHeader::setSampleRate(int sampleRate){
        int newSubChunk2Size = (int)(this.subChunk2Size * sampleRate / this.sampleRate);
        // if num bytes for each sample is even, the size of newSubChunk2Size also needed to be in even number
        if ((bitsPerSample/8)%2==0){			
                if (newSubChunk2Size%2!=0){
                        newSubChunk2Size++;
                }
        }

        this.sampleRate = sampleRate;
        this.byteRate = sampleRate*bitsPerSample/8;
        this.chunkSize = newSubChunk2Size+36;
        this.subChunk2Size = newSubChunk2Size;
}

void WaveHeader::setChunkId(string chunkId) {
        this.chunkId = chunkId;
}

void WaveHeader::setChunkSize(long chunkSize) {
        this.chunkSize = chunkSize;
}

void WaveHeader::setFormat(string format) {
        this.format = format;
}

void WaveHeader::setSubChunk1Id(string subChunk1Id) {
        this.subChunk1Id = subChunk1Id;
}
void WaveHeader::setSubChunk1Size(long subChunk1Size) {
        this.subChunk1Size = subChunk1Size;
}
void WaveHeader::setAudioFormat(int audioFormat) {
        this.audioFormat = audioFormat;
}
void WaveHeader::setChannels(int channels) {
        this.channels = channels;
}
void WaveHeader::setByteRate(long byteRate) 
{
        this.byteRate = byteRate;
}
void WaveHeader::setBlockAlign(int blockAlign) {
        this.blockAlign = blockAlign;
}
void WaveHeader::setBitsPerSample(int bitsPerSample) {
        this.bitsPerSample = bitsPerSample;
}
void WaveHeader::setSubChunk2Id(string subChunk2Id) {
        this.subChunk2Id = subChunk2Id;
}
void WaveHeader::setSubChunk2Size(long subChunk2Size) {
        this.subChunk2Size = subChunk2Size;
}
string WaveHeader::toString() {

        string sb = string();
        sb.append("chunkId: " + chunkId);
        sb.append("\n");
        sb.append("chunkSize: " + chunkSize);
        sb.append("\n");
        sb.append("format: " + format);
        sb.append("\n");
        sb.append("subChunk1Id: " + subChunk1Id);
        sb.append("\n");
        sb.append("subChunk1Size: " + subChunk1Size);
        sb.append("\n");
        sb.append("audioFormat: " + audioFormat);
        sb.append("\n");
        sb.append("channels: " + channels);
        sb.append("\n");
        sb.append("sampleRate: " + sampleRate);
        sb.append("\n");
        sb.append("byteRate: " + byteRate);
        sb.append("\n");
        sb.append("blockAlign: " + blockAlign);
        sb.append("\n");
        sb.append("bitsPerSample: " + bitsPerSample);
        sb.append("\n");
        sb.append("subChunk2Id: " + subChunk2Id);
        sb.append("\n");
        sb.append("subChunk2Size: " + subChunk2Size);		
        return sb;
}