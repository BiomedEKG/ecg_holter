#include "HRTResult.h"

HRTResult::HRTResult(){}
HRTResult::~HRTResult(){}


HRTResult* HRTResult :: getResult(){
	HRTResult *res = new HRTResult;
	res->GroupRisk = this->getGroupRisk();				
	res->MeanTachogram = this->getTachogram();
	res->setTOvalue(this->getTOvalue());
	res->setTS_value(this->getTS_value());
	res->setY(this->getY());
	res->setX(this->getX());
					//tutaj jakiœ enum czy co tam ma byæ =)

	return res;
}