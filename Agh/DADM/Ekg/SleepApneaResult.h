
#pragma once
#include <vector>
#include <map>
#include <AbstractResult.h>
#include <AbstractModule.h>
#include <ReturnType.h>


class SleepApneaResult :public AbstractResult
{
	public:

	// void setVectorResult(vector<int> rez);
	void setResult(vector<string> Nrepi,vector<double> ts,vector<double> te);
	SleepApneaResult* getResult();
	SleepApneaResult(void);
	~SleepApneaResult(void);

// private: jesli chcemy miec tu private to trzeba napisac getery
	// vector<int> vectorResult;
	vector<string> NrEp;
	vector<double> Tstart;
	vector<double> Tend;
};