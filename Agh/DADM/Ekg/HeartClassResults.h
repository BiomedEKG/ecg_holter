#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <string>
#include <map>
#ifndef HEART_CLASS_RESULTS_H
#define HEART_CLASS_RESULTS_H

using namespace std;

class HeartClassResults{
	
	public:
		
		map<string, vector<double> > qrsParameters;
		map<string, vector<double> > qrsClassificationMap;
		vector<double> qrsClass;
		
};

#endif // HEART_CLASS_RESULTS_H
