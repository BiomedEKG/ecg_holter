#include "ECGBaseline.h"
#include "BaselineResult.h"
#include "math.h"
#include <vector> 
#include "ResultKeeper.h"

BaselineResult* ECGBaseline::compute (ResultKeeper *rkp) {



//	samplingFrequency = rkp->samplingFrequency;   // nie ma tego w result keeperze
	//Input in = rkp->getSignalHandler();
	//in.Open(rkp->pathToFile);
	//int numbOfChannels = in.GetNumberOfChannels();
	//char** channelsNames = in.GetChannelsNames();
	//
	//for(int i = 0; i < 12; i++) {
	//	std::cout << channelsNames[i] << std::endl; 
	//	in.SelectChannel(channelsNames[11]);
	//}
	//std::vector <double> signal = in.vdGetChannelData(); 
static const unsigned int  chosenChannels[] = {0,1,6,7,8,9,10,11}; //kana³y, które maj¹ byæ wybrane (zak³adam numeracjê od 0)
const std::string namesChannels[] = {"e1","e2","v1","v2","v3","v4","v5","v6"};

	for (unsigned int i = 0; i<8; i++){
	
		std::vector<double> signal = rkp->getSingleChannel(rkp->pathToFile, i); 

		enum ECGFiltrationMethod bM = BUTTERWORTH_FILTER;

		switch (bM){

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

		//M
		string key = namesChannels[i];
		ecgSignals[key] = output;
	}
	BaselineResult b = BaselineResult(); 
	b.setSignalMap(ecgSignals);
	b.setFilteredSignal(ecgSignals["e2"]);
 	return b.getResult();
	//return b.getResult();
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