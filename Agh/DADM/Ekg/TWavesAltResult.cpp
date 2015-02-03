#include "TWavesAltResult.h"


TWavesAltResult::TWavesAltResult(void) {}

TWavesAltResult::~TWavesAltResult(void) {}

TWavesAltResult* TWavesAltResult :: getResult() {
	this->paramType = twavesalt;
	return this;
}
void TWavesAltResult :: setTWavesAltResult(double ar_coeff) {
	this->paramsResult = ar_coeff;
		
}

