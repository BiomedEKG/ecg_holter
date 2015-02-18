#include "SigEDResult.h"
#include <vector>
using namespace std;
SigEDResult::SigEDResult(void)
{
	
}


SigEDResult::~SigEDResult(void)
{
	
}


SigEDResult* SigEDResult :: getResult() {
	
	SigEDResult* result = new SigEDResult();
	result->vectorResult = this->vectorResult;
	return result;
}

void SigEDResult::setVectorResult(vector<double> vd) {
	this->vectorResult = vd;
}

vector<double> SigEDResult::getVectorResult() {
	return vectorResult;
}