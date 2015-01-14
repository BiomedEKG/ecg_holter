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
		SpeedAmplitudeParameter(vector<double> qrsOnsetData, vector<double> qrsEndData, vector<double> signalData);
		friend vector<double> SpeedAmplitudeExtractor(SpeedAmplitudeParameter &speedAmplitudeType);
};

#endif // SPEEDAMPLITUDEPARAMETER_H
