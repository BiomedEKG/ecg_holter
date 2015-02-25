#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <string>
#include <map>
#include "AbstractResult.h"
#ifndef HEART_CLASS_RESULT_H
#define HEART_CLASS_RESULT_H

using namespace std;

class HeartClassResult : public AbstractResult{
	
	public:
		map<string, double> qrsParameters;
		map<string, vector<int>> qrsClassificationMap;
		vector<double> qrsClass;	
		string qrsUnits[8];
	public:
		HeartClassResult* getResult();
		map<string, double> getQrsParameters();
		map<string, vector<int>> getQrsClassMap();//Dla Etiopic Beat
		string* getQrsUnits();
		
};

#endif // HEART_CLASS_RESULT_H
