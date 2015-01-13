#include "LeastMeanSquares.h"
#include "Butterworth.h"
#include <vector>

std::vector <double> LeastMeanSquares::calculateLeastMeanSquares (std::vector<double>* signal, int samplingFrequency, FILTERTYPE filterType){

ButterworthFilter butterworthFilter;
int numberOfSamples = signal->size();
butterworthFilter.numberOfSamples = numberOfSamples;
std::vector<std::vector<double>> butterworthCoefficients = butterworthFilter.setParameters(samplingFrequency, filterType);
std::vector <double> referenceSignal = butterworthFilter.zeroPhaseFiltering(butterworthCoefficients[0], butterworthCoefficients[1], signal);

//x inputSignal 
//y outputSignal
//d referenceSignal
//e errorValue
//w adaptiveCoefficients

/* od MZS: nie chcia³am Ci robiæ konfliktu i poprawiaæ, ale mo¿e lepiej by by³o te zmienne poni¿ej 
	zadeklarowaæ jako prywatne w nag³ówku, a w pliku .cpp w tej metodzie tylko ich u¿ywaæ albo do nich coœ przypisaæ
*/

std::vector<double> inputSignal = *signal;    
std::vector<double> outputSignal;
std::vector<double> errorValue;
std::vector<double> adaptiveCoefficients;
outputSignal.resize(numberOfSamples);
errorValue.resize(numberOfSamples);
adaptiveCoefficients.resize(numberOfSamples);

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