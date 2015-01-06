#pragma once

#include <vector>

class CubicSpline{
	public:
		std::vector <double> calculateCubicSpline (std::vector<double>* );
	private:
		static const int stepSize = 0.5;

};