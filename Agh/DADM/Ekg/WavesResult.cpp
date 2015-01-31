#include "WavesResult.h"
#include "ReturnType.h"

WavesResult::WavesResult(void)
{
}


WavesResult::~WavesResult(void)
{
	delete ws;
}


WavesResult* WavesResult::getResult() {
	 WavesResult* res = new WavesResult();
	 return res;
}

map <string, vector<int>> WavesResult::getWavesMap(){
	return wavesMap;
}

void WavesResult::setWavesMap(map <string, vector<int>> *map) {
	wavesMap = *map;
}