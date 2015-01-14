#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <string>
#include <map>
#include "MalinowskaParameter.h"

MalinowskaParameter::MalinowskaParameter(vector<double> qrsOnsetData, vector<double> qrsEndData, vector<double> signalData) : 
										AbstractExtractor(qrsOnsetData, qrsEndData, signalData){

}

// Testing on a different data
vector<double> MalinowskaExtractor(MalinowskaParameter &malinowskaType){

	vector<double> signalData;
	vector<double> malinowska;

	malinowskaType.SignalExtractor();
	MyMap tempMap = malinowskaType.extractedSamples;

	for(unsigned int i = 0; i < malinowskaType.qrsOnset.size(); i++){

		double area = 0;
		double sum = 0;
		signalData = tempMap.FindInMap(i);
		
		for(unsigned int j = 0; j < signalData.size(); j++){

			if(j > 1){
				area = area + fabs(signalData.at(j) - signalData.at(j-1));
			}

			sum = sum + fabs(signalData.at(j));
		}

		malinowska.at(i) = 10*sum/area*10;
	}
	
	return malinowska;
}

