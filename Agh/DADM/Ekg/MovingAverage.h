#pragma once

class MovingAverage{
	public:
		std::vector <double> calculateMovingAverage (std::vector<double>* signal);
	private:
		const int span = 5;
		double average;
		double averageWholeSignal;
};