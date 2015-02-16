#pragma once
#include "AbstractResult.h"
#include <string>
#include <map>
#include <vector>
using namespace std;
class WavesResult: public AbstractResult {
public:

	WavesResult();
	~WavesResult();
	WavesResult * getResult();
	map <string, vector<int>> GetWavesResultData(void);
	void SetWavesResultData(map <string, vector<int>> ComputedData);

private:
	map <string, vector<int>> WavesResultData;


};
