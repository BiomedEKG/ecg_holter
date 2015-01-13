#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <string>
#include <map>
#include "AbstractExtractor.h"

using namespace std;

class FastGrowthParameter : public AbstractExtractor{
	
	FastGrowthParameter(vector<double> qrsOnsetData, vector<double> qrsEndData, vector<double> signalData);
	vector<double> FastGrowthExtractor();
};
