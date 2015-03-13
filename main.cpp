/* 
 * File:   main.cpp
 * Author: antwalls
 *
 * Created on 13 de marzo de 2015, 10:06
 */

#include <cstdlib>
using namespace std;

/*
 * 
 */
int main(int argc, char** argv) 
{
        string filename = "cock_a_1.wav";
        // create a wave object
        Wave wave = new Wave("audio_work/"+filename);
        // get the fingerprint
        byte[] fingerprint=wave.getFingerprint();

        // dump the fingerprint
        FingerprintManager fingerprintManager=new FingerprintManager();
        fingerprintManager.saveFingerprintAsFile(fingerprint, "out/"+filename+".fingerprint");

        // load fingerprint from file
        byte[] loadedFp=fingerprintManager.getFingerprintFromFile("out/"+filename+".fingerprint");

        /*
        // fingerprint bytes checking
        for (int i=0; i<fingerprint.length; i++){
                System.out.println(fingerprint[i]+" vs "+loadedFp[i]);
        }
        */

}

