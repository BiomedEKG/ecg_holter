#pragma once
#include "AbstractResult.h"
#include <vector>


class RPeaksResult: public AbstractResult
{
public:
	RPeaksResult* getResult();
	RPeaksResult();
    ~RPeaksResult();
protected:
	std::vector <unsigned int> R_Peaks;
public:
	std::vector <unsigned int> getRPeaks();
	void setRPeaks(std::vector <unsigned int>);
	
};
