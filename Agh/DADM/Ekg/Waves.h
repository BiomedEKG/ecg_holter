#include <map>
#include<vector>
#include<string>
#include "WavesResult.h"
#include "Result.h" 

using namespace std;

class Waves: public AbstractModule<WavesResult>{
private:

	map <string, vector<int>> WavesData;
public:
	virtual WavesResult* compute(ResultKeeper *rkp)const override;
	
	/*
	OLD ARGUMENTS:
	vector<double>* resultFromECKBaseline, vector<double>* resultFromRPeaks
	*/
	/*
	OLD OUTPUT:
	map <string, vector<int>>
	*/

};