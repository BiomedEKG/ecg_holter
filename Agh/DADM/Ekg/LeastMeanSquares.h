#pragma once

#include "FilterType.h"
#include <vector>

class LeastMeanSquares{
	public:
		std::vector <double> calculateLeastMeanSquares (std::vector<double>*, int samplingFrequency, FILTERTYPE filterType);
   private:
	    std::vector <double> referenceSignal;
	    std::vector<double> inputSignal;    
		std::vector<double> outputSignal;
		std::vector<double> errorValue;
		std::vector<double> adaptiveCoefficients;

};