/* 
 * File:   Wave.cpp
 * Author: antwalls
 * 
 * Created on 13 de marzo de 2015, 11:45
 */

#include "Wave.h"
/**
	 * Constructor
	 * 
	 */
Wave::Wave() 
{
    waveHeader  = new WaveHeader();
    data        = byte[0];
    data_size   = 0;
}
/**
 * Constructor
 * 
 * @param filename
 *            Wave file
 */
Wave::Wave(string filename)
{
    ifstream inputStream(filename);
    initWaveWithInputStream(inputStream);
    inputStream.close();
}
/**
 * Constructor
 * 
 * @param inputStream
 *            Wave file input stream
 */
Wave::Wave(ifstream inputStream)
{
    initWaveWithInputStream(inputStream);
}

/**
 * Constructor
 * 
 * @param WaveHeader
 *            waveHeader
 * @param byte[]
 *            data
 */
Wave::Wave(WaveHeader waveHeader, byte data[]) 
{
        waveHeader = waveHeader;
        data = data;
}

void Wave::initWaveWithInputStream(ifstream inputStream) 
{
    // reads the first 44 bytes for header
    waveHeader = new WaveHeader(inputStream);

    if (waveHeader.isValid()) 
    {
            // load file
        
            // first, we set the cursor at the end of the file, in order to know sike in bytes.
            // file must be open in std::binary std::ate
        try{
                inputStream.seekg(0,ifstream::end);
                data_size = inputStream.tellg();
                data = byte[data_size];
                inputStream.read(data,data_size);
            }catch(exception& e)
            {
                cout<<"Exception opening file"<<endl;
            }
           
            // end load data
    } else {
            printf("Invalid Wave Header");
    }
}

/**
 * Trim the wave data
 * 
 * @param leftTrimNumberOfSample
 *            Number of sample trimmed from beginning
 * @param rightTrimNumberOfSample
 *            Number of sample trimmed from ending
 */
void Wave::trim(int leftTrimNumberOfSample, int rightTrimNumberOfSample) {

        long chunkSize = waveHeader.getChunkSize();
        long subChunk2Size = waveHeader.getSubChunk2Size();

        long totalTrimmed = leftTrimNumberOfSample + rightTrimNumberOfSample;

        if (totalTrimmed > subChunk2Size) {
                leftTrimNumberOfSample = (int) subChunk2Size;
        }
        // update wav info
        chunkSize -= totalTrimmed;
        subChunk2Size -= totalTrimmed;
        if (chunkSize>=0 && subChunk2Size>=0){
                waveHeader.setChunkSize(chunkSize);
                waveHeader.setSubChunk2Size(subChunk2Size);

                byte trimmedData[] = byte[(int) subChunk2Size];
                //this is way faster than doing it in a for loop
                memcpy(trimmedData,data,subChunk2Size);
                data = trimmedData;
        }
        else{
                printf("Trim error: Negative length");
        }
}

/**
* Trim the wave data from beginning
* 
* @param numberOfSample
*            numberOfSample trimmed from beginning
*/
void Wave::leftTrim(int numberOfSample) 
{
    trim(numberOfSample, 0);
}

/**
 * Trim the wave data from ending
 * 
 * @param numberOfSample
 *            numberOfSample trimmed from ending
 */
void Wave::rightTrim(int numberOfSample) 
{
    trim(0, numberOfSample);
}

/**
 * Trim the wave data
 * 
 * @param leftTrimSecond
 *            Seconds trimmed from beginning
 * @param rightTrimSecond
 *            Seconds trimmed from ending
 */
void Wave::trim(double leftTrimSecond, double rightTrimSecond) {

        int sampleRate = waveHeader.getSampleRate();
        int bitsPerSample = waveHeader.getBitsPerSample();
        int channels = waveHeader.getChannels();

        int leftTrimNumberOfSample = (int) (sampleRate * bitsPerSample / 8
                        * channels * leftTrimSecond);
        int rightTrimNumberOfSample = (int) (sampleRate * bitsPerSample / 8
                        * channels * rightTrimSecond);

        trim(leftTrimNumberOfSample, rightTrimNumberOfSample);
}

/**
 * Trim the wave data from beginning
 * 
 * @param second
 *            Seconds trimmed from beginning
 */
void Wave::leftTrim(double second) {
        trim(second, 0);
}

/**
 * Trim the wave data from ending
 * 
 * @param second
 *            Seconds trimmed from ending
 */
void Wave::rightTrim(double second) 
{
        trim(0, second);
}

/**
 * Get the wave header
 * 
 * @return waveHeader
 */
WaveHeader Wave::getWaveHeader() 
{
        return waveHeader;
}

/**
 * Get the wave spectrogram
 * 
 * @return spectrogram
 */
Spectrogram Wave::getSpectrogram()
{
        return new Spectrogram(this);
}
/**
 * Get the wave spectrogram
 * 
 * @param fftSampleSize	number of sample in fft, the value needed to be a number to power of 2
 * @param overlapFactor	1/overlapFactor overlapping, e.g. 1/4=25% overlapping, 0 for no overlapping
 * 
 * @return spectrogram
 */
Spectrogram Wave::getSpectrogram(int fftSampleSize, int overlapFactor) {
        return Spectrogram(this,fftSampleSize,overlapFactor);
}

/**
 * Get the wave data in bytes
 * 
 * @return wave data
 */
byte* Wave::getBytes() 
{
        return data;
}

/**
 * Data byte size of the wave excluding header size
 * 
 * @return byte size of the wave
 */
int Wave::size() 
{
        return data_size;
}

/**
 * Length of the wave in second
 * 
 * @return length in second
 */
float Wave::length() 
{
        float second = (float) waveHeader.getSubChunk2Size() / waveHeader.getByteRate();
        return second;
}
/**
 * Timestamp of the wave length
 * 
 * @return timestamp
 */
string Wave::timestamp() 
{
        float totalSeconds      = this.length();
        float second            = totalSeconds % 60;
        int minute              = (int) totalSeconds / 60 % 60;
        int hour                = (int) (totalSeconds / 3600);

        string sb = string();
        if (hour > 0) 
        {
                sb.append(hour + ":");
        }
        if (minute > 0) 
        {
                sb.append(minute + ":");
        }
        sb.append(second);

        return sb;
}

/**
 * Get the amplitudes of the wave samples (depends on the header)
 * 
 * @return amplitudes array (signed 16-bit)
 */
short* Wave::getSampleAmplitudes()
{
        int bytePerSample       = waveHeader.getBitsPerSample() / 8;
        int numSamples          = data_size / bytePerSample;
        short amplitudes[]      = short[numSamples];

        int pointer = 0;
        for (int i = 0; i < numSamples; i++) {
                short amplitude = 0;
                for (int byteNumber = 0; byteNumber < bytePerSample; byteNumber++) {
                        // little endian
                        amplitude |= (short) ((data[pointer++] & 0xFF) << (byteNumber * 8));
                }
                amplitudes[i] = amplitude;
        }

        return amplitudes;
}

string Wave::toString()
{
        string sb = string(waveHeader.toString());
        sb.append("\n");
        sb.append("length: " + timestamp());
        return sb;
}

double* Wave::getNormalizedAmplitudes() 
{
        NormalizedSampleAmplitudes amplitudes = NormalizedSampleAmplitudes(this);
        return amplitudes.getNormalizedAmplitudes();
}

byte* Wave::getFingerprint()
{		
        if (fingerprint == NULL)
        {
                FingerprintManager fingerprintManager = FingerprintManager();
                fingerprint = fingerprintManager.extractFingerprint(this);
        }
        return fingerprint;
}

FingerprintSimilarity Wave::getFingerprintSimilarity(Wave wave)
{		
        FingerprintSimilarityComputer fingerprintSimilarityComputer = FingerprintSimilarityComputer(this.getFingerprint(),wave.getFingerprint());
        return fingerprintSimilarityComputer.getFingerprintsSimilarity();
}

Wave::Wave(const Wave& orig) {
}

Wave::~Wave() {
}

