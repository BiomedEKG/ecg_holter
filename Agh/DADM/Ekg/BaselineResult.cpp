#include <BaselineResult.h>
#include "ReturnType.h"


BaselineResult::BaselineResult(void)
{
}

BaselineResult::~BaselineResult(void)
{
}

std::vector <double> BaselineResult::getFilteredSignal()
{
	return filteredSignal;
}

void BaselineResult::setFilteredSignal(std::vector <double> signal)
{
	filteredSignal = signal;
}

BaselineResult* BaselineResult:: getResult() {
	BaselineResult* br  = new BaselineResult();
	paramType = BASELINE;
	br->filteredSignal = filteredSignal;
	size = filteredSignal.size();
	br->size = size;
	br->filteredSignalMap = filteredSignalMap;
	return br;
	}

//M
void BaselineResult::setSignalMap (std::map<std::string, std::vector<double>> mapS){

	filteredSignalMap = mapS;
}

//M
std::map <std::string, std::vector<double>> BaselineResult::getSignalMap(){

	return filteredSignalMap;
}
