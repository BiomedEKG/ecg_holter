#include "atrialFibrFrequency.h"

atrialFibrFrequencyOut atrialFibrFrequency (vector<double> atrialFibrSignal, double frequency){
//double atrialFibrFrequency (vector<double> atrialFibrSignal, double frequency){
    bool atrialFibrilation;
    double atrialFreq, meanSig;
    vector<double> spectralPower;
    unsigned int signalLength=atrialFibrSignal.size();
    unsigned int inIterator=0;
    unsigned int outIterator=0;

    if((signalLength/frequency)>360000){
        signalLength=360000*frequency;
    }

    //in, out & plan for DFT
    fftw_complex *in;
    fftw_complex *out;
    fftw_plan p;
    //initialization of in, out & plan
    in=(fftw_complex*) fftw_malloc(sizeof(fftw_complex)*signalLength);
    out=(fftw_complex*) fftw_malloc(sizeof(fftw_complex)*signalLength);
    p=fftw_plan_dft_1d(signalLength, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
    //counting mean
    meanSig=0;
    for(inIterator=0;inIterator<signalLength;inIterator++){
            meanSig+=atrialFibrSignal[inIterator];
    }
    meanSig=meanSig/inIterator;
    //input for DFT, with mean subtracted
    for(inIterator=0;inIterator<signalLength;inIterator++){
        in[inIterator][0]=atrialFibrSignal[inIterator]-meanSig;     //Re
        in[inIterator][1]=0;                                        //Im
    };
    //executing DFT
    fftw_execute(p);
    //calculation of spectral power
    for(outIterator=0;outIterator<signalLength;outIterator++){
        spectralPower.push_back((out[outIterator][0]*out[outIterator][0])+(out[outIterator][1]*out[outIterator][1]));
    }
    //Finding dominant frequency
    for(outIterator=0;outIterator<signalLength;outIterator++){
        atrialFreq=1;
        if(spectralPower[outIterator]>spectralPower[atrialFreq]){
            atrialFreq=outIterator;
        }
    }
    atrialFreq=atrialFreq/frequency;
    //Compassion with frequency threshold
    if(atrialFreq<=80 || atrialFreq>=50){
        atrialFibrilation=0;
    }else{
        atrialFibrilation=1;
    }
    //plan deallocation
    fftw_destroy_plan(p);
    fftw_free(in);
    fftw_free(out);

    atrialFibrFrequencyOut ferqOut;
        ferqOut.atrialFreq=atrialFreq;
        ferqOut.atrialFibrilation=atrialFibrilation;

    return ferqOut;
    //return atrialFreq;
}
