#include "HRV1Result.h"
#include <vector>
#include <map>

HRV1Result::HRV1Result(void){
}
HRV1Result::~HRV1Result(void){
}

HRV1Result* HRV1Result :: getResult() {
	this -> paramType = R_peaks;
	//potrzeba pobraæ wektor pików R i czêstotliwoœæ próbkowania
	return this;
}
void HRV1Result::setHRV1Result(map<string, double> timeParameters, map<string, double> freqParameters, vector<double> power, vector<double> frequency, string tabtime[8], string tabfreq[6]) {
	this -> prvtimeParameters = timeParameters;
	this -> prvfreqParameters = freqParameters;
	this -> prvpower = power;
	this -> prvfrequency = frequency;
	this -> prvtimetab[8] = tabtime;
	this -> prvfreqtab[6] = tabfreq;
}