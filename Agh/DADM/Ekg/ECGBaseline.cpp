#include "ECGBaseline.h"
#include "math.h"
#include <vector>    

std::vector<double> ECGBaseline::compute (std::vector<double>* signal){
	switch (baselineMethod){

		case  BUTTERWORTH:
			butterworthFilter (signal);
			break;
		case  CHEBYSHEV:
			chebyshevFilter (signal);
			break;
		case  LMS:
			leastMeanSquares (signal);
			break;
		case  MOVINGAVERAGE:
			movingAverage (signal);
			break;
		case  CUBICSPLINE:
			cubicSpline (signal);
			break;
		case  SAVITZKYGOLAY:
			savitzkyGolay (signal);
			break;
		default:
			movingAverage (signal);
			break;
	} 
	return signal;   //// hmmm
}



std::vector<double> ECGBaseline::butterworthFilter (std::vector<double>* signal){


}


std::vector<double> ECGBaseline::chebyshevFilter (std::vector<double>* signal){


}

std::vector<double> ECGBaseline::leastMeanSquares (std::vector<double>* signal){


}


std::vector<double> ECGBaseline::movingAverage (std::vector<double>* signal){
	MovingAverage movingAverage;
	movingAverage.calculateMovingAverage(signal);

	
}

std::vector<double> ECGBaseline::cubicSpline (std::vector<double>* signal){
	
}


std::vector<double> ECGBaseline::savitzkyGolay (std::vector<double>* signal){


}