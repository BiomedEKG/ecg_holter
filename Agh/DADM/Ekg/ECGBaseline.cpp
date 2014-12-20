#include "ECGBaseline.h"
#include "math.h"

vector<double> ECGBaseline::compute (vector<double> *signal){
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
		case  MOVINGAVERAGES:
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
	return signal;
}



vector<double> ECGBaseline::butterworthFilter (vector<double> *signal){


}


vector<double> ECGBaseline::chebyshevFilter (vector<double> *signal){


}

vector<double> ECGBaseline::leastMeanSquares (vector<double> *signal){


}


vector<double> ECGBaseline::movingAverage (std::vector<double> *signal){
	MovingAverage movingAverage;
}

vector<double> ECGBaseline::cubicSpline (vector<double> *signal){
	
}


vector<double> ECGBaseline::savitzkyGolay (vector<double> *signal){


}