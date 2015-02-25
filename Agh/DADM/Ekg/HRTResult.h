#ifndef HRT_RESULT_H
#define HRT_RESULT_H
#include <AbstractResult.h>
#include "TO.h"
#include "TS.h"
#include <vector>
#include <string>
#include <map>


class HRTResult : public AbstractResult, public TS, public TO{

private:
std::map<std::string, double> TableParameters;
double GroupRisk;							
std::vector<double> MeanTachogram;
//enum paramType param_Type;		to dziedziczymy po klasie AbstractResult

public:
virtual HRTResult* getResult();
HRTResult();
~HRTResult();

void setTableParameters(std::string key, double val){
	this->TableParameters[key] = val;
}

void setMeanTachogram(std::vector<double> a){
	this->MeanTachogram = a;
}



void setGroup(double a){
	this->GroupRisk = a;
}

double getTableParamteres(std::string key){
	return TableParameters[key];
}

double getGroupRisk(){
	return GroupRisk;
}


std::vector<double> getTachogram(){
	return MeanTachogram;
}


};
#endif HRT_RESULT_H