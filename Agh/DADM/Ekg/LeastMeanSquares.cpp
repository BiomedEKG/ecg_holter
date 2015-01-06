#include "LeastMeanSquares.h"
#include "Butterworth.h"
#include <vector>

std::vector <double> LeastMeanSquares::calculateLeastMeanSquares (std::vector<double>* signal, int samplingFrequency, FILTERTYPE filterType){

ButterworthFilter butterworthFilter;
int numberOfSamples = butterworthFilter.numberOfSamples = signal->size();
std::vector<std::vector<double>> butterworthCoefficients = butterworthFilter.setParameters(samplingFrequency, filterType);
std::vector <double> referenceSignal = butterworthFilter.zeroPhaseFiltering(butterworthCoefficients[0], butterworthCoefficients[1], signal);

//x inputSignal 
//y outputSignal
//d referenceSignal
//e errorValue
//w adaptiveCoefficients

std::vector<double> inputSignal = *signal;
std::vector<double> outputSignal(numberOfSamples);
std::vector<double> errorValue(numberOfSamples);
std::vector<double> adaptiveCoefficients(numberOfSamples);

const double stepSize = 0.5;

adaptiveCoefficients.assign (numberOfSamples,0.0);


for (int i=0; i<numberOfSamples; i++) {
	errorValue[i] = referenceSignal[i] - adaptiveCoefficients[i]*inputSignal[i];
	adaptiveCoefficients[i+1] = adaptiveCoefficients[i] + stepSize*errorValue[i]*inputSignal[i];
	}

for (int i=0; i<numberOfSamples; i++) {
    outputSignal[i] = adaptiveCoefficients[i]*inputSignal[i];
	}

	return outputSignal;

}