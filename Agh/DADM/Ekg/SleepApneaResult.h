
#pragma once
#include <vector>
#include <AbstractModule.h>


class SleepApnea :

public AbstractResult
{
public:
void setVectorResult(vector<double> rez);
SleepApnea* getResult();
	SleepApnea(void);
	~SleepApnea(void);

private:
	vector<double> vectorResult;
};