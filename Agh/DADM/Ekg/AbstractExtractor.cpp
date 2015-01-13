#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <string>
#include <map>
#include "AbstractExtractor.h"

using namespace std;

AbstractExtractor::AbstractExtractor(vector<double> qrsOnsetFromWaves, vector<double> qrsEndFromWaves, vector<double> signalFromEcgBaseline){
	
	for(unsigned int i = 0; i < qrsOnsetFromWaves.size(); i++){
		
        this->qrsOnset.push_back(qrsOnsetFromWaves.at(i));
        this->qrsEnd.push_back(qrsEndFromWaves.at(i));
        this->signal.push_back(signalFromEcgBaseline.at(i));
    }
}

MyMap AbstractExtractor::SignalExtractor(){
	
	double signalBegin = 0;
	double signalEnd = 0;
	MyMap qrsMap; 
	vector<double> temp;
	
	// ile wektorów
	for(unsigned int i = 0; i < qrsEnd.size(); i++){
		
		signalBegin = this->signal.at(qrsOnset.at(i));
		signalEnd = this->signal.at(qrsEnd.at(i));
		temp.clear();
		
		// jak d³ugie wektory
		for(unsigned int j = 0; signalBegin < signalEnd+1; signalBegin++){
			
			temp.at(j) = this->signal.at(signalBegin);
		}
		
		qrsMap.InsertToMap(i, temp);
	}
	
	return qrsMap;
}














