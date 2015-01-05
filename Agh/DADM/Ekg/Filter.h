#pragma once

#include <vector>   

class Filter{
	public:
		std::vector <double> calculateFilter (std::vector<double>);
	private:
		const double bandStop = 50;
		const double highPass = 0.5;
		const double lowPass = 100;

		double samplingFrequency;
		double cutoffFrequency;
};