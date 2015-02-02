#include "SleepApneaResult.h"
#include <vector>


SleepApneaResult::SleepApneaResult(void)
{

}

SleepApneaResult::~SleepApneaResult(void)
{

}

SleepApneaResult* SleepApneaResult::getResult()
{
	SleepApneaResult* odp = new  SleepApneaResult();
	odp->Xlab="min";
	odp->Ylab="";
	odp->MapResult=MapResult;
	odp->paramType=SLEEP_APNEA;

	return odp;

}

void SleepApneaResult::setMapResult(map<string,vector<double>> rez)
{
	this->MapResult = rez;
}

/*
void SleepApneaResult::setVectorResult(vector<int> rez)
{
	this->vectorResult = rez;
}
/*
compute() {

SleepApneaResult* sleep = new SLeep....;
sleep->vector = vectkor z funckji;
return sleep->getResult();
}
*/


