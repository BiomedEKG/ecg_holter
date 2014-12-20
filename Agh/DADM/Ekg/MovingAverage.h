#pragma once

class MovingAverage{
	public:
		vector <double> calculateMovingAverage (vector<double>);
	private:
		const int span = 5;
		double average;
		double averageWholeSignal;
};