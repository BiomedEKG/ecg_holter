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
		vector<double> fastGrowthValues;
		FastGrowthParameter(vector<double> qrsOnsetData, vector<double> qrsEndData, vector<double> signalData);
		void FastGrowthExtractor();
};

#endif // FASTGROWTHPARAMETER_H

