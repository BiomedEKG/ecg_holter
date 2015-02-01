#include "SleepApnea.h"
#include <vector>


SigEDResult::SleepApnea(void)
{

}

SigEDResult::~SleepApnea(void)
{

}





SleepApnea* SleepApnea :: getResult() {

	this->paramType = Sleep_Apnea;
	return this;

}


void Sleep_Apnea::setVectorResult(vector<double> rez) {
	this->vectorResult = rez;
}


