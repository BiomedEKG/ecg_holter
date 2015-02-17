#include "ECGBaseline.h"
#include "BaselineResult.h"
#include "math.h"
#include <vector>    

BaselineResult* ECGBaseline::compute (ResultKeeper *rkp, BASELINEMETHOD baselineMethod){

	samplingFrequency = rkp->samplingFrequency;   // wlasciwe nazwy pól :P
	std::vector <double> signal = rkp->signal;                          //

	switch (baselineMethod){

		case  BUTTERWORTH:
			output = butterworthFilter (&signal, samplingFrequency);
			break;
		case  CHEBYSHEV:
			output = chebyshevFilter (&signal, samplingFrequency);
			break;
		case  LMS:
			output = leastMeanSquares (&signal, samplingFrequency);
			break;
		case  MOVINGAVERAGE:
			output = movingAverage (&signal);
			break;
		case  CUBICSPLINE:
			output = cubicSpline (&signal, samplingFrequency);
			break;
		case  SAVITZKYGOLAY:
			output = savitzkyGolay (&signal, samplingFrequency);
			break;
		default:
			output = movingAverage (&signal);
			break;
	} 
	rkp->signal = output;  // yyyy
	return new BaselineResult();   
}



std::vector<double> ECGBaseline::butterworthFilter (std::vector<double>* signal, int samplingFrequency){
	ButterworthFilter butterworthFilter;
	butterworthFilter.numberOfSamples = signal->size();
	filterType = HIGHPASS;   
	std::vector<std::vector<double>> butterworthCoefficients = butterworthFilter.setParameters(samplingFrequency, filterType);
	std::vector <double> output = butterworthFilter.zeroPhaseFiltering(butterworthCoefficients[0], butterworthCoefficients[1], signal);
	filterType =LOWPASS;   
	butterworthCoefficients = butterworthFilter.setParameters(samplingFrequency, filterType);
	output = butterworthFilter.zeroPhaseFiltering(butterworthCoefficients[0], butterworthCoefficients[1], &output);  
	return output;
}


std::vector<double> ECGBaseline::chebyshevFilter (std::vector<double>* signal, int samplingFrequency){
	ChebyshevFilter chebyshevFilter;
	chebyshevFilter.numberOfSamples = signal->size();
	filterType = HIGHPASS; 
	std::vector<std::vector<double>> chebyshevCoefficients = chebyshevFilter.setParameters(samplingFrequency, filterType);
	std::vector <double> output = chebyshevFilter.zeroPhaseFiltering(chebyshevCoefficients[0], chebyshevCoefficients[1], signal);
	filterType = LOWPASS;
	chebyshevCoefficients = chebyshevFilter.setParameters(samplingFrequency, filterType);
	output = chebyshevFilter.zeroPhaseFiltering(chebyshevCoefficients[0], chebyshevCoefficients[1], &output);
	return output;
}

std::vector<double> ECGBaseline::leastMeanSquares (std::vector<double>* signal, int samplingFrequency){
	LeastMeanSquares leastMeanSquares;
	filterType = HIGHPASS;
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