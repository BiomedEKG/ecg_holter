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
	odp->NrEp=NrEp;
	odp->Tstart=Tstart;
	odp->Tend=Tend;

	odp->paramType=SLEEP_APNEA;

	return odp;

}

void SleepApneaResult::setResult(vector<string> Nrepi,vector<double> ts,vector<double> te)
{
	this->NrEp=Nrepi;
	this->Tstart=ts;
	this->Tend=te;
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


