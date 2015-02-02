#pragma once
#include <vector>
#include <map>
#include <string>
#include <AbstractModule.h>

class HRV1Result :
public AbstractResult{

public:
	void setHRV1Result(map<string, double> timeParameters, map<string, double> freqParameters, vector<double> power, vector<double> frequency);
	HRV1Result* getResult();
	HRV1Result(void);
	~HRV1Result(void);

private:
	map<string, double> prvtimeParameters;
	map<string, double> prvfreqParameters;
	vector<double> prvpower;
	vector<double> prvfrequency;
};