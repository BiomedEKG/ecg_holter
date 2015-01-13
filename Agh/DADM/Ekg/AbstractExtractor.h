#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <string>
#include <map>
#include "MyMap.h"

using namespace std;

class AbstractExtractor{
	
	public:
		vector<double> qrsOnset;
		vector<double> qrsEnd;
		vector<double> signal;
		vector<double> numberOfSamples;
		
		AbstractExtractor(vector<double> qrsOnsetFromWaves, vector<double> qrsEndFromWaves, vector<double> signalFromEcgBaseline);
		MyMap SignalExtractor();
};
