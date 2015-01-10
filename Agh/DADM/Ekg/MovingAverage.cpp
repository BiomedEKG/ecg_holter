#include "MovingAverage.h"
#include <vector>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_statistics.h>

unsigned int MovingAverage::span = 5;

std::vector <double> MovingAverage::calculateMovingAverage (std::vector<double>* signal){

	inputSignal = *signal;
	double sumSignal = 0.0;

	for (unsigned int n = 0; n < inputSignal.size(); n++){
	
		sumSignal += inputSignal[n]; 
	}
	
	averageWholeSignal = sumSignal / inputSignal.size();

	for (unsigned int a = 0; a < (span-1)/2 ; a++){
		
		inputSignal.push_back(averageWholeSignal);
		inputSignal.insert(inputSignal.begin(), averageWholeSignal);
	}

	for (unsigned long int j = (span-1)/2; j < (inputSignal.size - (span-1)) ; j++ ){
		double sum = inputSignal[j]; 
		double average;

		for(int i = 1 ; i <= (span-1)/2; i++){
			sum += inputSignal[j-i];
			sum += inputSignal[j+i];
		}

		average = sum/span;
		outputSignal.push_back(average);
	}

	return outputSignal;
}