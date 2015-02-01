#include "LeastMeanSquares.h"
#include "Butterworth.h"
#include <vector>

std::vector <double> LeastMeanSquares::calculateLeastMeanSquares (std::vector<double>* signal, int samplingFrequency, FILTERTYPE filterType){

	int numberOfSamples = signal->size();

	ButterworthFilter butterworthFilter;
	butterworthFilter.numberOfSamples = signal->size();

	referenceSignal.resize(numberOfSamples);

	filterType = HIGHPASS;   
	std::vector<std::vector<double>> butterworthCoefficients = butterworthFilter.setParameters(samplingFrequency, filterType);
	referenceSignal = butterworthFilter.zeroPhaseFiltering(butterworthCoefficients[0], butterworthCoefficients[1], signal);

	inputSignal = *signal;    

	outputSignal.resize(numberOfSamples);
	errorValue.resize(numberOfSamples);
	adaptiveCoefficients.resize(numberOfSamples);

	const double stepSize = 0.5;

for (int i=0; i<numberOfSamples-1; i++) {
	errorValue[i] = referenceSignal[i] - adaptiveCoefficients[i]*inputSignal[i];
	adaptiveCoefficients[i+1] = adaptiveCoefficients[i] + stepSize*errorValue[i]*inputSignal[i];
	}

for (int i=0; i<numberOfSamples; i++) {
    outputSignal[i] = adaptiveCoefficients[i]*inputSignal[i];
	}

	return outputSignal;

}