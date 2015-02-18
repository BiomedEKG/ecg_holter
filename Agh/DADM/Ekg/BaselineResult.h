#pragma once
#include <AbstractResult.h>
#include <vector>
#include <map>

class BaselineResult: public AbstractResult
{
public:
	BaselineResult* getResult();
	BaselineResult();
    ~BaselineResult();

	std::vector <double> filteredSignal;
	void setSignalMap (std::map<std::string, std::vector<double>>);
	std::map <std::string, std::vector<double>> getSignalMap();

	//M
	std::map <std::string, std::vector<double>> filteredSignalMap;
public:
	std::vector <double> getFilteredSignal();
	void setFilteredSignal(std::vector <double>);
	unsigned int size;
	
};
