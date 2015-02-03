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
		
		string qrsParameters[] = {"mV", "mV", "mv^2", "-", "-", "-", "-", "-"};
		vector<string> qrsParams;
		map<string, double> mapParameters;
		map<string, vector<double> > qrsClassificationMap;
		vector<double> qrsClass;

		HeartClassResult(void);
		~HeartClassResult(void);
		HeartClassResult* getResult();
};

#endif // HEART_CLASS_RESULT_H
