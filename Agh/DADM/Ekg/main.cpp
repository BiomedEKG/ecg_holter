#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <string>
#include <map>
#include <fstream>
#include "HeartClass.h"
#include "ResultKeeper.h"
//#include "HeartClassResult.h"

using namespace std;

int main(){
	
	ResultKeeper rpk;
	ResultKeeper *wskRpk;
	wskRpk = &rpk;

// Sprawdzenie czy poprawnie zapisuje cechy rpk  
/*
	for(unsigned int i = 0; i < rpk.qrsOnset.size(); i++){

		//cout << rpk.qrsOnset.at(i) << endl;
		//cout << rpk.qrsEnd.at(i) << endl;
		cout << rpk.signal.at(i) << endl;
	}
*/




	HeartClass heartClass(wskRpk);
	
	vector<double>* tempSignal;
	
	for(unsigned int i = 0; i < heartClass.signalMap.size(); i++){
		
		tempSignal = &heartClass.signalMap[i];
		heartClass.Amplitudes(tempSignal);	
	}
	
	heartClass.MeanAmplitude();
	
	heartClass.FrameLocator();
	
	heartClass.SamplesBetween();
	
	heartClass.Conditioning();
	
	//HeartClass heartClass(wskRpk);
	//HeartClassResult* k = heartClass.compute(wskRpk);	
	
	system("PAUSE");
	return 0;	
}
