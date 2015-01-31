#include "AtrfibrResult.h"
#include "ReturnType.h"

AtrfibrResult::AtrfibrResult(void)
{
}


AtrfibrResult::~AtrfibrResult(void)
{
}

AtrfibrResult* AtrfibrResult::getResult(){
	this->paramType = ATRIAL;
	return this;
}
void AtrfibrResult::setIsArtDetected(bool in){
	isArtFibDetected = in;
}
void AtrfibrResult::setDetectedIndOfAF(vector<unsigned int>& vec){
	deteckedAF = vec;
}