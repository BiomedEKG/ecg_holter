#include "ECGBaseline.h"
#include "BaselineResult.h"
#include "math.h"
#include <vector> 
#include "ResultKeeper.h"

#include "ECGFiltrationMethod.h"

BaselineResult* ECGBaseline::compute (ResultKeeper *rkp)
{
	Input *inputHandler = rkp->getInput();
	int samplingFrequency = inputHandler->GetFs();
	std::vector <double> signal = inputHandler->vdGetChannelData(); 

	switch (rkp->getECGBaselineMethod())
	{
	case  BUTTERWORTH_FILTER:
		output = butterworthFilter (&signal, samplingFrequency);
		break;
	case  CZEBYSZEW_FILTER:
		output = chebyshevFilter (&signal, samplingFrequency);
		break;
	case  LMS:
		output = leastMeanSquares (&signal, samplingFrequency);
		break;
	case  MOVING_AVERAGE:
		output = movingAverage (&signal);
		break;
	case  CUBIC_SPLINE:
		output = cubicSpline (&signal, samplingFrequency);
		break;
	case  SAVITZKY_GOLAY_FILTER:
		output = savitzkyGolay (&signal, samplingFrequency);
		break;
	default:
		output = movingAverage (&signal);
		break;
	} 
	BaselineResult b = BaselineResult(); 

	//M
	/*	string key = namesChannels[i];
		signals[key] = output;*/

	b.setSignalMap(signals1);
	b.setFilteredSignal(signals1["e2"]);
 	return b.getResult();
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


std::vector<double> ECGBaseline::savitzkyGolay (std::vector<double>* signal, int samplingFrequency){
	SavitzkyGolay savitzkyGolay;
	std::vector<double> output = savitzkyGolay.calculateSavitzkyGolay(signal);
	return output;
}


