#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <string>
#include <map>
#include "AbstractExtractor.h"
#ifndef FASTGROWTHPARAMETER_H
#define FASTGROWTHPARAMETER_H

using namespace std;

class FastGrowthParameter : public AbstractExtractor{
	
	public:
		FastGrowthParameter(vector<double> qrsOnsetData, vector<double> qrsEndData, vector<double> signalData);
		friend vector<double> FastGrowthExtractor(FastGrowthParameter &fgType);
};

#endif // FASTGROWTHPARAMETER_H
