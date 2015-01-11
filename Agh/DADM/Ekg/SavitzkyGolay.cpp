#include "SavitzkyGolay.h"

//coefficients taken from MATLAB, for 4-order polynominal savitzkygolay filter
const double SavitzkyGolay::coefficientsArray[] = {01417, 0.0, -0.0043, 0.0, 0.0};
const unsigned int SavitzkyGolay::span = 25;
const unsigned int SavitzkyGolay::polynominalOrder = 4;

std::vector <double> SavitzkyGolay::calculateSavitzkyGolay (std::vector <double> *signal){

	//std::vector<double> coefficientsVector(coefficientsArray, coefficientsArray + sizeof(coefficientsArray) / sizeof(coefficientsArray[0]) );

	double sumSignal;

	// count average of signal
	for (unsigned int n = 0; n < inputSignal.size(); n++){
	
		sumSignal += inputSignal[n]; 
	}
	
	averageWholeSignal = sumSignal / inputSignal.size();

	//add samples before first and after last sample because otherway it would be impossible to filter these samples
	for (unsigned int a = 0; a < (span-1)/2 ; a++){
		
		inputSignal.push_back(averageWholeSignal);
		inputSignal.insert(inputSignal.begin(), averageWholeSignal);
	}

	spanCount = createSpan();
	/*
	//count coefficients of Savitzky-Golay filter
	double coefficient;
	
	for (int b = 0; b < span; b++){	

		double sumCoefficient;

		for(int c = 0; c < polynominalOrder+1 ; c++){
			
			sumCoefficient = pow();
		}
		coefficient = 
		coefficientsFilter.push_back(); 
	}
	return *signal;

}
*/

std::vector<int> SavitzkyGolay::createSpan(){
	
	std::vector<int> createSpanOutput;
	createSpanOutput.push_back(0);

	for (int unsigned i = 0; i<(span-1)/2; i ++){
		
		createSpanOutput.insert(createSpanOutput.begin(), (-i));
		createSpanOutput.push_back(i);
	}
	return createSpanOutput;
}