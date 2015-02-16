#include "WavesResult.h"
 

WavesResult::WavesResult(void)
{
}

WavesResult::~WavesResult(void)
{
}

WavesResult * WavesResult::getResult(){
	//this->paramType = BASELINE;
	WavesResult *wr = new WavesResult();
	wr->WavesResultData = this->WavesResultData;
	return wr;
}

map <string, vector<int>> WavesResult::GetWavesResultData(void){
	
	return WavesResultData;
}

void WavesResult::SetWavesResultData(map <string, vector<int>> ComputedData){
		WavesResultData = ComputedData;
	}