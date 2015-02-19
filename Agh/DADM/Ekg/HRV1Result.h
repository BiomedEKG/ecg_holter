#pragma once
#include "AbstractResult.h"
#include <vector>
#include <string>
#include <map>


class HRV1Result: public AbstractResult
{
public:
	HRV1Result* getResult();
	HRV1Result();
    ~HRV1Result();

	void setHRV1(std::map<std::string, double> timeParameters, std::map<std::string, double> freqParameters, std::vector<double> power, std::vector<double> frequency, std::string tabtime[8], std::string tabfreq[6]);
public:
	void getHRV1();
	std::map<std::string, double> prvtimeParameters;
	std::map<std::string, double> prvfreqParameters;
	std::vector<double> prvpower;
	std::vector<double> prvfrequency;
	std::string prvtimetab[8];
	std::string prvfreqtab[6];
	
	
};