#pragma once
#include "AbstractModule.h"     
#include "Result.h"   
#include "BaselineResult.h"
#include "RPeaksResult.h"
//#include "Methods.h"           
#include "ResultKeeper.h"
#include <vector>

class RPeaks: public AbstractModule<RPeaksResult> {

public:
	//RPeaksResult* compute(ResultKeeper *rkp, RPEAKSMETHOD RPeaksMethod) override; 
	RPeaksResult* compute(ResultKeeper *rkp) override;
	std::vector <unsigned int> output;
	
private:
	//RPEAKSMETHOD RPeaksMethod;
	
	int samplingFrequency;
	std::vector<unsigned int> computePT(std::vector<double> signal, unsigned int sampling_frequency);
	std::vector<unsigned int> computeHilbert(std::vector<double> signal, unsigned int sampling_frequency); 
};
