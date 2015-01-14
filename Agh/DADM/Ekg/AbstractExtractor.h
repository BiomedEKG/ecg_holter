#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <string>
#include <map>
#include "MyMap.h"
#ifndef ABSTRACTEXTRACTOR_H
#define ABSTRACTEXTRACTOR_H

using namespace std;

class AbstractExtractor{
	
	public:
		vector<double> qrsOnset;
		vector<double> qrsEnd;
		vector<double> signal;
		vector<double> numberOfSamples;
		MyMap extractedSamples;
		
		AbstractExtractor(vector<double> qrsOnsetFromWaves, vector<double> qrsEndFromWaves, vector<double> signalFromEcgBaseline);
		void SignalExtractor();
};

#endif // ABSTRACTEXTRACTOR_H
