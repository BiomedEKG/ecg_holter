#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <string>
#include <map>
#ifndef ABSTRACTEXTRACTOR_H
#define ABSTRACTEXTRACTOR_H

using namespace std;

class AbstractExtractor{
	
	public:
		map<int, vector<double> > signalMap;
		
		AbstractExtractor(vector<double>* qrsOnsetFromWaves, vector<double>* qrsEndFromWaves, vector<double>* signalFromEcgBaseline);
};

#endif // ABSTRACTEXTRACTOR_H