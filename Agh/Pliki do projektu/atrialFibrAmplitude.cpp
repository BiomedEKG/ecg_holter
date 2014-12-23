#include "atrialFibrAmplitude.h"

double atrialFibrAmplitude (vector<double> atrialFibrSignal){
    double atrialAmplitude=0;
    vector<double> maxAmplitudes;
    vector<double>::iterator itSignal;
	for (int i=0; i<4; i++){
		maxAmplitudes.push_back(0);
	}
    //findings 4 max Amplitudes in atrial fibrillation-signal
    for(itSignal=(atrialFibrSignal.begin()+1);(itSignal+1)!=atrialFibrSignal.end();itSignal++){
		//checking if founded maximum is higher then any of current maxAmplitudes
        if((*itSignal>*(itSignal-1))&&(*itSignal>*(itSignal+1))){
            if(*itSignal>maxAmplitudes[0]){
                maxAmplitudes.at(3)=maxAmplitudes[2];
                maxAmplitudes.at(2)=maxAmplitudes[1];
                maxAmplitudes.at(1)=maxAmplitudes[0];
                maxAmplitudes.at(0)=*itSignal;
            }else if(*itSignal>maxAmplitudes[1]){
                maxAmplitudes.at(3)=maxAmplitudes[2];
                maxAmplitudes.at(2)=maxAmplitudes[1];
                maxAmplitudes.at(1)=*itSignal;
            }else if(*itSignal>maxAmplitudes[2]){
                maxAmplitudes.at(3)=maxAmplitudes[2];
                maxAmplitudes.at(2)=*itSignal;
            }else if(*itSignal>maxAmplitudes[3]){
                maxAmplitudes.pop_back();
                maxAmplitudes.push_back(*itSignal);
            }
        }
    }
    //mean from 4 max Amplitudes
    atrialAmplitude=(maxAmplitudes[0]+maxAmplitudes[1]+maxAmplitudes[2]+maxAmplitudes[3])/4;
return atrialAmplitude;
}
