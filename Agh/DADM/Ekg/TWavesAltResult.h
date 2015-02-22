#pragma once
#include "AbstractResult.h"
#include <vector>

using namespace std;

class TWavesAltResult :  public AbstractResult
{
public:
	TWavesAltResult(void);
	void setTWavesAltResult(double ar_coeff, vector<unsigned int> start, vector<unsigned int> end);
	TWavesAltResult* getResult();
	~TWavesAltResult(void);

	public:  
		double paramsResult;
		vector<unsigned int> startResult; 
		vector<unsigned int> endResult;
};