#include "HRV1Result.h"
#include <vector>
#include <map>

HRV1Result::HRV1Result(void){
}
HRV1Result::~HRV1Result(void){
}

HRV1Result* HRV1Result :: getResult() {
	this -> paramType = R_peaks;
	//potrzeba pobra� wektor pik�w R i cz�stotliwo�� pr�bkowania
	return this;
}
void HRV1Result::setHRV1Result(map<string, double> timeParameters, map<string, double> freqParameters, vector<double> power, vector<double> frequency) {
	this -> prvtimeParameters = timeParameters;
	this -> prvfreqParameters = freqParameters;
	this -> prvpower = power;
	this -> prvfrequency = frequency;
}