#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <string>
#include <map>
#include "Kmeans.h"
#include "AbstractExtractor.h"
#ifndef HEARTCLASS_H
#define HEARTCLASS_H

using namespace std;

class HeartClass{
	
	public:
	map<string, vector<double> > qrsClassificationMap;	
	
	HeartClass(vector<double>* qrsOnsetFromWaves, vector<double>* qrsEndFromWaves, vector<double>* signalFromEcgBaseline);
};


#endif // HEARTCLASS_H