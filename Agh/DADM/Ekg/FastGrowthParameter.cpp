#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <string>
#include <map>
#include "FastGrowthParameter.h"

FastGrowthParameter::FastGrowthParameter(vector<double> qrsOnsetData, vector<double> qrsEndData, vector<double> signalData) : 
										AbstractExtractor(qrsOnsetData, qrsEndData, signalData){

}

vector<double> FastGrowthParameter::FastGrowthExtractor(){

	vector<double> signalData;
	vector<double> fastGrowth;

	MyMap tempMap = SignalExtractor();
	
	for(unsigned int i = 0; i < this->qrsOnset.size(); i++){

		double maxSpeed = 0;
		double speed = 0;
		double samplesCount = 0;
		signalData = tempMap.FindInMap(i);
	
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
