//AbstractExtractor.cpp - preparing the signal for further caluclations

#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <string>
#include <map>
#include "AbstractExtractor.h"

using namespace std;

AbstractExtractor::AbstractExtractor(vector<double> qrsOnsetFromWaves, vector<double> qrsEndFromWaves, vector<double> signalFromEcgBaseline){
	
	this -> qrsOnset= qrsOnsetFromWaves;
	this -> qrsEnd = qrsEndFromWaves;
	this -> signal = signalFromEcgBaseline;
	this -> numberOfQrs = qrsOnsetFromWaves.size();
}

vector<double> AbstractExtractor::SignalExtractor(unsigned int qrsNumber){
	
	double signalBegin = 0;
	double signalEnd = 0;
	vector<double> signalExtracted;
	signalBegin = signal.at(qrsOnset.at(qrsNumber));
	signalEnd = signal.at(qrsEnd.at(qrsNumber));

	for(signalBegin, int i = 0; signalBegin < signalEnd; signalBegin++, i++){
		signalExtracted.at(i) = signal.at(signalBegin);
	}
	return signalExtracted;
}