#include "Hrv2Result.h"
#include <vector>
#include <map>
#include <string>


Hrv2Result::Hrv2Result(void)
{
}


Hrv2Result::~Hrv2Result(void)
{
}


Hrv2Result* Hrv2Result :: getResult() {
	//potrzeba pobra� czestotliwosc pr�bkowania i r_peaks (do poprawy)
	this->paramType = R_peaks;//(?)
	return this;
}
void Hrv2Result::setHrv2Result(map<string,double> params, map<string,vector<double>> h,map<string,vector<double>> p ) {
	this->paramsResult = params;
	this->histResult = h;
	this->poincareResult = p;
}
