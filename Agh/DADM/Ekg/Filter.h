#pragma once

#include <vector>   


class Filter{
	public:
		std::vector <double> filterSignal (std::vector<double>, std::vector<double>, std::vector<double>* );
		std::vector <double> zeroPhaseFiltering (std::vector<double>, std::vector<double>, std::vector<double>* );
		int numberOfSamples;
	private:
	static const int filterOrder = 6;	

};