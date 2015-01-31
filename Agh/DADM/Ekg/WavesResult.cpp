#include "WavesResult.h"
 

WavesResult * WavesResult::getResult(void){
	this->paramType = BASELINE;
return this;
}

map <string, vector<int>> WavesResult::GetWavesResultData(void){
	
	return WavesResultData;
}

void WavesResult::SetWavesResultData(map <string, vector<int>> ComputedData){
		WavesResultData = ComputedData;
	}