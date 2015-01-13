#include "ECGBaseline.h"
#include "math.h"
#include <vector>    

std::vector<double> ECGBaseline::compute (std::vector<double>* signal){

	std::vector <double> output; // t¹ definicjê przenios³abym do nag³ówka ECGBaseline.h, wtedy wszystkie metody 
	//z klasy ECGBaseline  mog³yby z tego pola (output) korzystaæ i nie trzebaby by³o w ka¿dej metodzie z osobna jej tworzyæ
	// - mam na myœli metody butterworthFilter, chebyshevFilter itp.

	switch (baselineMethod){

		case  BUTTERWORTH:
			output = butterworthFilter (signal, samplingFrequency, filterType);
			break;
		case  CHEBYSHEV:
			output = chebyshevFilter (signal, samplingFrequency, filterType);
			break;
		case  LMS:
			output = leastMeanSquares (signal, samplingFrequency, filterType);
			break;
		case  MOVINGAVERAGE:
			output = movingAverage (signal);
			break;
		case  CUBICSPLINE:
			output = cubicSpline (signal, samplingFrequency);
			break;
		case  SAVITZKYGOLAY:
			output = savitzkyGolay (signal);
			break;
		default:
			output = movingAverage (signal);
			break;
	} 
	return output;   
}



std::vector<double> ECGBaseline::butterworthFilter (std::vector<double>* signal, int samplingFrequency, FILTERTYPE filterType){
	ButterworthFilter butterworthFilter;
	butterworthFilter.numberOfSamples = signal->size();
	std::vector<std::vector<double>> butterworthCoefficients = butterworthFilter.setParameters(samplingFrequency, filterType);
	std::vector <double> output = butterworthFilter.zeroPhaseFiltering(butterworthCoefficients[0], butterworthCoefficients[1], signal);
	return output;
}


std::vector<double> ECGBaseline::chebyshevFilter (std::vector<double>* signal, int samplingFrequency, FILTERTYPE filterType){
	ChebyshevFilter chebyshevFilter;
	chebyshevFilter.numberOfSamples = signal->size();
	std::vector<std::vector<double>> chebyshevCoefficients = chebyshevFilter.setParameters(samplingFrequency, filterType);
	std::vector <double> output = chebyshevFilter.zeroPhaseFiltering(chebyshevCoefficients[0], chebyshevCoefficients[1], signal);
	return output;
}

std::vector<double> ECGBaseline::leastMeanSquares (std::vector<double>* signal, int samplingFrequency, FILTERTYPE filterType){
	LeastMeanSquares leastMeanSquares;
	std::vector <double> output = leastMeanSquares.calculateLeastMeanSquares(signal, samplingFrequency, filterType);
	return output;
}


std::vector<double> ECGBaseline::movingAverage (std::vector<double>* signal){
	MovingAverage movingAverage;
	std::vector <double> output = movingAverage.calculateMovingAverage(signal);
	return output;
	
}

std::vector<double> ECGBaseline::cubicSpline (std::vector<double>* signal, int samplingFrequency){
	CubicSpline cubicSpline;
	std::vector <double> output = cubicSpline.calculateCubicSpline(signal, samplingFrequency);
	return output;
}


std::vector<double> ECGBaseline::savitzkyGolay (std::vector<double>* signal){
	SavitzkyGolay savitzkyGolay;
	std::vector<double> output = savitzkyGolay.calculateSavitzkyGolay(signal);
	return output;
}