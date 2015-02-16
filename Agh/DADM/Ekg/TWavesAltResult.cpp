#include "TWavesAltResult.h"


TWavesAltResult::TWavesAltResult(void) {}

TWavesAltResult::~TWavesAltResult(void) {}

TWavesAltResult* TWavesAltResult :: getResult() {
	this->paramType = twavesalt;
	return this;
}
void TWavesAltResult :: setTWavesAltResult(double ar_coeff, vector<double> start, vector<double> end) {
	this->paramsResult = ar_coeff;
	this->startResult = start;
	this->endResult = end;
}

