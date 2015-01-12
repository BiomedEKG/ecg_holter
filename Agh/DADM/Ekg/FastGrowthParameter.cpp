// FastGrowthParameter.cpp : Defines the percentage of samples which speed exceed 40% of a max speed

#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <string>
#include <map>
#include "FastGrowthParameter.h"

using namespace std;

FastGrowthParameter::FastGrowthParameter(){

}

// Testing on a different data

vector<double> FastGrowthParameter::FastGrowthExtractor(){

	vector<double> signalData;
	vector<double> fastGrowth;

	for(unsigned int i = 0; i < this->numberOfQrs; i++){

		signalData = SignalExtractor(i);
		double maxSpeed = 0;
		double samplesCount = 0;

		for(unsigned int j = 0; j < signalData.size(); j++){

			speed = signalData.at(j) + signalData.at(j-2) - 2*signalData.at(j-1);
			if(speed > maxSpeed){
				maxSpeed = speed;
			}
		}

		maxSpeed = maxSpeed*0.4;

		for(unsigned int j = 0; j < signalData.size(); j++){

			if(signalData.at(j) > maxSpeed){
				samplesCount++;
			}

		}

		fastGrowth.at(i) = samplesCount/signalData.size();
	}

	return fastGrowth;
}
