#include <ResultVCG.h>

ResultVCG::ResultVCG(void)
{
}

ResultVCG::~ResultVCG(void)
{
}

ResultVCG* ResultVCG:: getResult() {
 //paramType = ;
	ResultVCG *res = new ResultVCG();
	res->VCG = this->VCG;
	res->parameters = this->parameters;
 return res;
 }