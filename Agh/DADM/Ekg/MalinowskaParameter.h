#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <string>
#include <map>
#include "AbstractExtractor.h"
#ifndef MALINOWSKAPARAMETER_H
#define MALINOWSKAPARAMETER_H

using namespace std;

class MalinowskaParameter : public AbstractExtractor{
	
	public:
		vector<double> malinowskaValues;
		
		MalinowskaParameter(vector<double>* qrsOnsetData, vector<double>* qrsEndData, vector<double>* signalData);
		void MalinowskaExtractor();
};

#endif // MALINOWSKAPARAMETER_H
