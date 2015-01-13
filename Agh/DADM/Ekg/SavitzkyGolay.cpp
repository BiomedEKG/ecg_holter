#include "SavitzkyGolay.h"

//coefficients taken from MATLAB, for 4-order polynominal savitzkygolay filter
const double SavitzkyGolay::coefficientsArray[] = {01417, 0.0, -0.0043, 0.0, 0.0};
const unsigned int SavitzkyGolay::span = 25;
const unsigned int SavitzkyGolay::spanHalf = 12;
const unsigned int SavitzkyGolay::polynominalOrder = 4;

std::vector <double> SavitzkyGolay::calculateSavitzkyGolay (std::vector <double> *signal){

	//std::vector<double> coefficientsVector(coefficientsArray, coefficientsArray + sizeof(coefficientsArray) / sizeof(coefficientsArray[0]) );
	
	inputSignal = *signal;

	double sumSignal = 0.0;

	// count average of signal
	for (unsigned int n = 0; n < inputSignal.size(); n++){
	
		sumSignal += inputSignal[n]; 
	}
	
	averageWholeSignal = sumSignal / inputSignal.size();

	//add samples before first and after last sample because otherway it would be impossible to filter these samples
	for (unsigned int a = 0; a < spanHalf ; a++){
		
		inputSignal.push_back(averageWholeSignal);
		inputSignal.insert(inputSignal.begin(), averageWholeSignal);
	}

	createSpan();
	calculateFilterCoefficients();
	

	//filter signal
	for (unsigned long int j = spanHalf; j < (inputSignal.size() - spanHalf) ; j++ ){
		
		double sum = inputSignal[j];
		for(unsigned int i = 1 ; i <= spanHalf; i++){

			sum += inputSignal[j-i] * coefficientsFilter[spanHalf-i];
			sum += inputSignal[j+i] * coefficientsFilter[spanHalf+i];
		}
		outputSignal.push_back(sum);
	}

	return outputSignal;
}


void SavitzkyGolay::createSpan(){
	
	spanCount.push_back(0.0);

	for (int unsigned i = 0; i<spanHalf; i ++){
		
		spanCount.insert(spanCount.begin(), (-i));
		spanCount.push_back(i);
	}
}

void SavitzkyGolay::calculateFilterCoefficients(){
	
	//calculate coefficients of Savitzky-Golay filter

	//calculate 0 coefficient (middle)
	double zeroCoefficient = 0.0;

	for(int c = 0; c <= polynominalOrder ; c++){
			
		zeroCoefficient += pow(spanCount[spanHalf], c)*coefficientsArray[c];
	}
	coefficientsFilter.push_back(zeroCoefficient);

	//calculate others coefficients
	for (int b = 0; b <= spanHalf; b++){	

		double coefficientL = 0.0;
		double coefficientR = 0.0;

		for(int c = 0; c <= polynominalOrder ; c++){
			
			coefficientL += pow(spanCount[spanHalf -1 -b], c) * coefficientsArray[c];
			coefficientR += pow(spanCount[spanHalf +1 -b], c) * coefficientsArray[c];
		}
		
		coefficientsFilter.push_back(coefficientR);
		coefficientsFilter.insert(coefficientsFilter.begin(),coefficientL);
	}
}