#pragma once
#include <vector>
#include <math.h> 


class SavitzkyGolay{
	
public:
		static const double coefficientsArray[];
		static const unsigned int span;
		static const unsigned int spanHalf;
		static const unsigned int polynominalOrder;

		std::vector<double> calculateSavitzkyGolay (std::vector <double>*);
		void createSpan();
		void calculateFilterCoefficients();

private:
		std::vector<double> inputSignal;
		std::vector<double> outputSignal;

		double averageWholeSignal;
		std::vector<int> spanCount;
		std::vector<double> coefficientsFilter;
};