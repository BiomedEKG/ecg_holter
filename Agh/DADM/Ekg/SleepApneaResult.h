
#pragma once
#include <vector>
#include <AbstractResult.h>
#include <AbstractModule.h>
#include <ReturnType.h>


class SleepApneaResult :public AbstractResult
{
	public:

	void setVectorResult(vector<int> rez, string X, string Y);
	SleepApneaResult* getResult();
	SleepApneaResult(void);
	~SleepApneaResult(void);

private:
	vector<int> vectorResult;
	string Xlab;
	string Ylab;
};