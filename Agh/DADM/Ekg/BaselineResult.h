#pragma once
#include <AbstractResult.h>
#include <vector>


class BaselineResult: public AbstractResult
{
public:
	BaselineResult* getResult();
	BaselineResult();
    ~BaselineResult();

	std::vector <double> filteredSignal;
public:
	std::vector <double> getFilteredSignal();
	void setFilteredSignal(std::vector <double>);
	
};
