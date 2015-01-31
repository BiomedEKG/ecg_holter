#include "AbstractModule.h"
#pragma once
#include "ReturnType.h"
#include <map>

class WavesResult: public AbstractResult {
public:

	WavesResult(){};
	~WavesResult(){};
	WavesResult * getResult() override;
	map <string, vector<int>> GetWavesResultData(void);
	void SetWavesResultData(map <string, vector<int>> ComputedData);

private:
	map <string, vector<int>> WavesResultData;


};
