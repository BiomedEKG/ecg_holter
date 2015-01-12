// SpeedAmplitudeParameter.cpp : Defines the max speed to amplitude ratio for further calculations.
//

#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <string>
#include <map>
#include "SpeedAmplitudeParameter.h"

using namespace std;

SpeedAmplitudeParameter::SpeedAmplitudeParameter(){

}


// Testing on a different data
vector<double> SpeedAmplitudeParameter::SpeedAmplitudeExtractor(){
	
	vector<double> speedAmplitude;
	vector<double> signalData;

	for(unsigned int i = 0; i < this->numberOfQrs; i++){

		signalData = SignalExtractor(i);
		double maxSpeed = 0;
		double maxSignal = 0;
		double miniSignal = 0;
		double speed = 0;
		double maxAmplitude = 0;

		for(unsigned int j = 0; j < signalData.size(); j++){

			if(j > 2){
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
		speedAmplitude.at(i) = 10*(maxSpeed/maxAmplitude);
	}

	return speedAmplitude;
}