#pragma once
#include <vector>
#include <AbstractResult.h>
using namespace std;
class SigEDResult :
	public AbstractResult
{
public:
	void setVectorResult(vector<double> vd);
	vector<double> getVectorResult();
	SigEDResult* getResult();
	SigEDResult(void);
	~SigEDResult(void);
	 
private:
	vector<double> vectorResult;
};

