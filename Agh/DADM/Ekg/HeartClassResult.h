#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <string>
#include <map>
#ifndef HEART_CLASS_RESULT_H
#define HEART_CLASS_RESULT_H

using namespace std;

class HeartClassResult{
	
	public:
		
		map<string, vector<double> > qrsParameters;
		map<string, vector<double> > qrsClassificationMap;
		vector<double> qrsClass;		
};

#endif // HEART_CLASS_RESULT_H
