#include "AtrfibrResult.h"

AtrfibrResult::AtrfibrResult(void)
{
}


AtrfibrResult::~AtrfibrResult(void)
{
}

AtrfibrResult* AtrfibrResult::getResult(){
	//this->paramType = ATRIAL;
	AtrfibrResult *atrialFibrResult = new AtrfibrResult();
	atrialFibrResult->deteckedAF = this->deteckedAF;
	atrialFibrResult->isArtFibDetected = this->isArtFibDetected;
	return atrialFibrResult;
}
void AtrfibrResult::setIsArtDetected(bool in){
	isArtFibDetected = in;
}
void AtrfibrResult::setDetectedIndOfAF(std::vector<unsigned int>& vec){
	deteckedAF = vec;
}