#pragma once

#include "FilterType.h"
#include <vector>

class LeastMeanSquares{
	public:
		std::vector <double> calculateLeastMeanSquares (std::vector<double>*, int samplingFrequency, FILTERTYPE filterType);


};