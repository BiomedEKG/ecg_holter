#include "TWavesAltResult.h"


TWavesAltResult::TWavesAltResult(void) {}

TWavesAltResult::~TWavesAltResult(void) {}

TWavesAltResult* TWavesAltResult :: getResult() {
//	this->paramType = T_WAVES_ALT;
	//return this;
	TWavesAltResult *twa = new TWavesAltResult();
	twa->paramsResult = this->paramsResult;
	twa->startResult = this->startResult;
	twa->endResult = this->endResult;
	return twa;
}
void TWavesAltResult :: setTWavesAltResult(double ar_coeff, vector<unsigned int> start, vector<unsigned int> end) {
	this->paramsResult = ar_coeff;
	this->startResult = start;
	this->endResult = end;
}

