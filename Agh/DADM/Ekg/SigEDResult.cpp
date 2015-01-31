#include "SigEDResult.h"
#include <vector>

SigEDResult::SigEDResult(void)
{
	
}


SigEDResult::~SigEDResult(void)
{
}


SigEDResult* SigEDResult :: getResult() {
	this->paramType = SIG_EDRe;
	return this;
}

void SigEDResult::setVectorResult(vector<double> vd) {
	this->vectorResult = vd;
}