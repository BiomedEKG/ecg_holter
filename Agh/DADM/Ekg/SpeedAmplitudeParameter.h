#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <string>
#include <map>
#include "AbstractExtractor.h"
#ifndef SPEEDAMPLITUDEPARAMETER_H
#define SPEEDAMPLITUDEPARAMETER_H

using namespace std;

class SpeedAmplitudeParameter : public AbstractExtractor{
	
	public:
		vector<double> speedAmplitudeValues;
		SpeedAmplitudeParameter(vector<double> qrsOnsetData, vector<double> qrsEndData, vector<double> signalData);
		void SpeedAmplitudeExtractor();
};

#endif // SPEEDAMPLITUDEPARAMETER_H
