#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <string>
#include <map>
#include "AbstractExtractor.h"

using namespace std;

AbstractExtractor::AbstractExtractor(vector<double> qrsOnsetFromWaves, vector<double> qrsEndFromWaves, vector<double> signalFromEcgBaseline){
    
    double signalBegin = 0;
	double signalEnd = 0; 
	vector<double> temp;
	
	// ile wektor�w
	for(unsigned int i = 0; i < qrsEndFromWaves.size(); i++){
		
		signalBegin = qrsOnsetFromWaves.at(i);
		signalEnd = qrsEndFromWaves.at(i);
		temp.clear();
		
		// jak d�ugie wektory
		for(unsigned int j = 0; signalBegin < signalEnd+1; signalBegin++){
			
			this->signalMap[i].push_back(signalFromEcgBaseline.at(signalBegin));
		}
	}
}














