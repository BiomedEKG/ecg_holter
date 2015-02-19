#include "HRV1Result.h"
#include "ReturnType.h"
#include <vector>

HRV1Result::HRV1Result(void)
{
}

HRV1Result::~HRV1Result(void)
{
}
//narazie, nie wiem w czym te wyniki umiescic. 
void HRV1Result::getHRV1()
{
	//return HRV1;
}

void HRV1Result::setHRV1(std::map<std::string, double> timeParameters, std::map<std::string, double> freqParameters, std::vector<double> power, std::vector<double> frequency, std::string tabtime[8], std::string tabfreq[6]) {
	this -> prvtimeParameters = timeParameters;
	this -> prvfreqParameters = freqParameters;
	this -> prvpower = power;
	this -> prvfrequency = frequency;
	for (size_t i = 0; i<8; i++){
		this->prvtimetab[i] = tabtime[i];
	}
	//this -> prvtimetab[8]= tabtime;
	for (size_t i = 0; i<6; i++){
		this->prvfreqtab[i] = tabfreq[i];
	}
	/*
	std::cout<<"HRV1Result power = " << std::endl;
	for (size_t i = 0; i < 25 ;i++){
		std::cout<<power.at(i)<<std::endl;
	}
	std::cout<<"size of power = " << std::endl;
	std::cout<<power.size()<<std::endl;
	//this -> prvfreqtab[6] = tabfreq;
	std::cout<<"frequency  = " << std::endl;
	for (size_t i = 0; i < 25 ;i++){
		std::cout<<frequency.at(i)<<std::endl;
	}
	std::cout<<"size of freq = " << std::endl;
	std::cout<<frequency.size()<<std::endl;
	//this -> prvfreqtab[6] = tabfreq;*/

}



HRV1Result* HRV1Result:: getResult() {
	HRV1Result* rp = new HRV1Result();
	rp->prvtimeParameters = this->prvtimeParameters;
	rp->prvfreqParameters = this->prvfreqParameters;
	rp->prvpower = this->prvpower;
	rp->prvfrequency = this->prvfrequency;
	//rp->R_Peaks = R_Peaks;
	//paramType = RPEAKS;
	return rp;
	}