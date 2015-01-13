#pragma once

#include "Methods.h"
#include "FilterType.h"
#include "MovingAverage.h"
#include "Butterworth.h"
#include "Chebyshev.h"
#include "LeastMeanSquares.h"
#include "CubicSpline.h"
#include "SavitzkyGolay.h"



class ECGBaseline {

public:
	std::vector<double> compute (std::vector<double>* signal, BASELINEMETHOD baselineMethod, int samplingFrequency);
	std::vector <double> output;
	
private:
	BASELINEMETHOD baselineMethod;
	FILTERTYPE filterType;
	int samplingFrequency;
	std::vector<double> butterworthFilter (std::vector<double>* signal, int samplingFrequency);
	std::vector<double> chebyshevFilter (std::vector<double>* signal, int samplingFrequency);
	std::vector<double> movingAverage (std::vector<double>* signal);
	std::vector<double> leastMeanSquares (std::vector<double>* signal, int samplingFrequency);
	std::vector<double> cubicSpline (std::vector<double>* signal, int samplingFrequency);
	std::vector<double> savitzkyGolay (std::vector<double>* signal);
};