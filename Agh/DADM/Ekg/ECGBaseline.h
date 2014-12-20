#pragma once

#include "MovingAverage.h"
#include "Butterworth.h"
#include "Chebyshev.h"
#include "LeastMeanSquares.h"
#include "CubicSpline.h"
#include "SavitzkyGolay.h"


class ECGBaseline {

public:
	vector<double> compute (vector<double> signal);
	
private:
	BASELINEMETHOD baselineMethod;
	vector<double> butterworthFilter (vector<double>* signal);
	vector<double> chebyshevFilter (vector<double>* signal);
	vector<double> movingAverage (vector<double>* signal);
	vector<double> leastMeanSquares (vector<double>* signal);
	vector<double> cubicSpline (vector<double>* signal);
	vector<double> savitzkyGolay (vector<double>* signal);
};