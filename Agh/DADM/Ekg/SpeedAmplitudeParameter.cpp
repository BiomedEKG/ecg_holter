#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <string>
#include <map>
#include "SpeedAmplitudeParameter.h"

SpeedAmplitudeParameter::SpeedAmplitudeParameter(vector<double> qrsOnsetData, vector<double> qrsEndData, vector<double> signalData) : 
										AbstractExtractor(qrsOnsetData, qrsEndData, signalData){
											
}

// Testing on a different data
void SpeedAmplitudeParameter::SpeedAmplitudeExtractor(){
	
	vector<double> signalData;

	for(unsigned int i = 0; i < this->signalMap.size(); i++){

		double maxSpeed = 0;
		double maxSignal = 0;
		double miniSignal = 0;
		double speed = 0;
		double maxAmplitude = 0;
		signalData.clear();
		signalData = this->signalMap[i];
		
		for(unsigned int j = 0; j < signalData.size(); j++){

			if(j >= 2){
				speed = signalData.at(j) + signalData.at(j-2) - 2*signalData.at(j-1);
				if(speed > maxSpeed){
					maxSpeed = speed;
				}
			}
			if(signalData.at(j) > maxSignal){
				maxSignal = signalData.at(j);
			}
			if(signalData.at(j) < miniSignal){
				miniSignal = signalData.at(j);
			}
		}
		
		maxAmplitude = fabs(maxSignal - miniSignal);
		this->speedAmplitudeValues.push_back(10*(maxSpeed/maxAmplitude)*10);
	}
}

