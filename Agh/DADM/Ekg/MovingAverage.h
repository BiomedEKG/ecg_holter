#pragma once

#include <vector>

class MovingAverage{
	public:
		static unsigned int span;

		std::vector <double> calculateMovingAverage (std::vector<double>* signal);

	private:
		std::vector<double> inputSignal;
		std::vector <double> outputSignal;

		double average;
		double averageWholeSignal;
		double averageSignal (std::vector<double>* signal);
};