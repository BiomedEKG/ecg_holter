#include "ECGBaseline.h"
#include "math.h"
#include <vector>    

std::vector<double> ECGBaseline::compute (std::vector<double>* signal){

	std::vector <double> output;

	switch (baselineMethod){

		case  BUTTERWORTH:
			output = butterworthFilter (signal, samplingFrequency, filterType);
			break;
		case  CHEBYSHEV:
			output = chebyshevFilter (signal, samplingFrequency, filterType);
			break;
		case  LMS:
			leastMeanSquares (signal);
			break;
		case  MOVINGAVERAGE:
			output = movingAverage (signal);
			break;
		case  CUBICSPLINE:
			cubicSpline (signal);
			break;
		case  SAVITZKYGOLAY:
			savitzkyGolay (signal);
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

std::vector<double> ECGBaseline::leastMeanSquares (std::vector<double>* signal){

	return *signal;
}


std::vector<double> ECGBaseline::movingAverage (std::vector<double>* signal){
	MovingAverage movingAverage;
	std::vector <double> output = movingAverage.calculateMovingAverage(signal);
	return output;
	
}

std::vector<double> ECGBaseline::cubicSpline (std::vector<double>* signal){
	
	return *signal;
}


std::vector<double> ECGBaseline::savitzkyGolay (std::vector<double>* signal){

	return *signal;
}