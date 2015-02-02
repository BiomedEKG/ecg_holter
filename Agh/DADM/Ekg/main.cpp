#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <string>
#include <map>
#include <fstream>
#include "HeartClass.h"
#include "ResultKeeper.h"

using namespace std;

int main(){
	
	ResultKeeper rpk;
	ResultKeeper *wskRpk;
	wskRpk = &rpk;
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

	
	
	
	return 0;	
}
