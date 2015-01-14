
#include"Waves.h"

map <string, vector<int>> Waves::Compute(vector<double>* resultFromECKBaseline, vector<double>* resultFromRPeaks){

	vector<int> FooVector1;
	vector<int> FooVector2;


	for(int i=0;i<7;i++){
		FooVector1.push_back(i);
	}
	WavesData["QRS_ONSET"] = FooVector1;

	for(int i=0;i<7;i++){
		FooVector1.push_back(i);
	}
	WavesData["QRS_END"] = FooVector2;



	return WavesData;
	}
