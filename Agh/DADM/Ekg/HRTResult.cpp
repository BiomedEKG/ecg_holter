#include "HRTResult.h"

HRTResult::HRTResult(){}
HRTResult::~HRTResult(){}




HRTResult* HRTResult :: getResult(){
	HRTResult *res = new HRTResult;
	res->group = this->getGroup();
	res->MeanTachogram = this->getTachogram();
	res->TO_value = this->getTO();
	res->TS_value = this->getTS();
	res->TS_match = this->getTSMatch();
	res->param_Type = HRT;    //tutaj jakiœ enum czy co tam ma byæ =)

	return res;
}