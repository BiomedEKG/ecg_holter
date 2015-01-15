#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <string>
#include <map>
#include "FastGrowthParameter.h"

using namespace std;

FastGrowthParameter::FastGrowthParameter(vector<double> qrsOnsetData, vector<double> qrsEndData, vector<double> signalData) : 
										AbstractExtractor(qrsOnsetData, qrsEndData, signalData){

}

void FastGrowthParameter::FastGrowthExtractor(){

	vector<double> signalData;
	
	for(unsigned int i = 0; i < this->signalMap.size(); i++){

		signalData.clear();
		double maxSpeed = 0;
		double speed = 0;
		double samplesCount = 0;
		signalData = this->signalMap[i];
	
		for(unsigned int j = 2; j < signalData.size(); j++){

			speed = signalData.at(j) + signalData.at(j-2) - 2*signalData.at(j-1);
			if(speed > maxSpeed){
				maxSpeed = speed;
			}
		}

		maxSpeed = maxSpeed*0.4;

		for(unsigned int k = 0; k < signalData.size(); k++){

			if(signalData.at(k) > maxSpeed){
				samplesCount++;
			}
		}

		this->fastGrowthValues.push_back((samplesCount/signalData.size())*10);
	}
}

