#pragma once

#include <vector>

class MovingAverage{
	public:
		std::vector <double> calculateMovingAverage (std::vector<double>* signal);
	private:
		static const int span = 5;
		double average;
		double averageWholeSignal;
};