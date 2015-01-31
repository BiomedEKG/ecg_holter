#pragma once
#include <vector>
#include <AbstractModule.h>
class SigEDResult :
	public AbstractResult
{
public:
	void setVectorResult(vector<double> vd);
	SigEDResult* getResult();
	SigEDResult(void);
	~SigEDResult(void);

private:
	vector<double> vectorResult;
};

