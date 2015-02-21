#pragma once
#include "AbstractModule.h"     
#include "Result.h"   
#include<BaselineResult.h>
#include <ECGFiltrationMethod.h>
#include "FilterType.h"
#include "MovingAverage.h"
#include "Butterworth.h"
#include "Chebyshev.h"
#include "LeastMeanSquares.h"
#include "CubicSpline.h"
#include "SavitzkyGolay.h"




class ECGBaseline: public AbstractModule<BaselineResult> {

public:
	// BaselineResult* compute (ResultKeeper *rkp, BASELINEMETHOD baselineMethod);
	BaselineResult* compute (ResultKeeper *rkp) override;
	std::vector <double> output;
	static const unsigned int chosenChannels[];
	static const std::string namesChannels[];
	std::map <std::string, std::vector <double>> ecgSignals;
private:
	ECGFiltrationMethod baselineMethod;
	FILTERTYPE filterType;
	int samplingFrequency;
	std::vector<double> butterworthFilter (std::vector<double>* signal, int samplingFrequency);
	std::vector<double> chebyshevFilter (std::vector<double>* signal, int samplingFrequency);
	std::vector<double> movingAverage (std::vector<double>* signal);
	std::vector<double> leastMeanSquares (std::vector<double>* signal, int samplingFrequency);
	std::vector<double> cubicSpline (std::vector<double>* signal, int samplingFrequency);
	std::vector<double> savitzkyGolay (std::vector<double>* signal, int samplingFrequency);
	
};