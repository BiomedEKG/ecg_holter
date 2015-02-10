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
	return br;
	}