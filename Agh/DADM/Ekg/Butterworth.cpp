//#include "Butterworth.h"
//#include "FilterType.h"
//
//std::vector<std::vector<double>> ButterworthFilter::setParameters (int samplingFrequency, FILTERTYPE filterType) {
//
//	int order1;
//
//	if (filterType == HIGHPASS) {
//		order1 = 3;  
//	    }
//	else {
//		order1 = 5;  
//	}
//
//
//	std::vector<std::vector<double>> butterworthCoefficients(2, std::vector<double>(order1,0));  
//
//
//
//
//	switch (filterType){
//
//	case HIGHPASS:
//		switch (samplingFrequency){
//
//
//								   case 250:
//
//									       butterworthCoefficients[0][0] = 0.9823;
//										   butterworthCoefficients[0][1] = -1.9647;
//										   butterworthCoefficients[0][2] = 0.9823;
//
//										   butterworthCoefficients[1][0] = 1;
//										   butterworthCoefficients[1][1] = -1.9644;
//										   butterworthCoefficients[1][2] = 0.9650;
//
//									   break;
//
//								   case 360:
//
//									       butterworthCoefficients[0][0] =0.9877;
//										   butterworthCoefficients[0][1] = -1.9754;
//										   butterworthCoefficients[0][2] = 0.9877;
//
//										   butterworthCoefficients[1][0] = 1;
//										   butterworthCoefficients[1][1] = -1.9753;
//										   butterworthCoefficients[1][2] = 0.9756;
//
//								       break;
//
//								   default:
//									       butterworthCoefficients[0][0] =0.9877;
//										   butterworthCoefficients[0][1] = -1.9754;
//										   butterworthCoefficients[0][2] = 0.9877;
//
//										   butterworthCoefficients[1][0] = 1;
//										   butterworthCoefficients[1][1] = -1.9753;
//										   butterworthCoefficients[1][2] = 0.9756;
//
//									   break;
//		                          }
//		break;
//	case LOWPASS:
//		switch (samplingFrequency){
//								   case 250:
//									       //b
//										   butterworthCoefficients[0][0] = 0.4328;
//										   butterworthCoefficients[0][1] = 1.7313;
//										   butterworthCoefficients[0][2] = 2.5970;
//										   butterworthCoefficients[0][3] = 1.7313;
//										   butterworthCoefficients[0][4] = 0.4328;
//
//										   //a
//										   butterworthCoefficients[1][0] = 1;
//										   butterworthCoefficients[1][1] = 2.3695;
//										   butterworthCoefficients[1][2] = 2.3139;
//										   butterworthCoefficients[1][3] = 1.0546;
//										   butterworthCoefficients[1][4] = 0.1873;
//
//
//									   break;
//
//								   case 360:
//									       butterworthCoefficients[0][0] = 0.1309;
//										   butterworthCoefficients[0][1] = 0.5238;
//										   butterworthCoefficients[0][2] = 0.7857;
//										   butterworthCoefficients[0][3] = 0.5238;
//										   butterworthCoefficients[0][4] = 0.1309;
//
//
//										   butterworthCoefficients[1][0] = 1;
//										   butterworthCoefficients[1][1] = 0.4340;
//										   butterworthCoefficients[1][2] = 0.5456;
//										   butterworthCoefficients[1][3] = 0.0942;
//										   butterworthCoefficients[1][4] = 0.0213;
//
//
//								       break;
//
//								   default:
//									       butterworthCoefficients[0][0] = 0.1309;
//										   butterworthCoefficients[0][1] = 0.5238;
//										   butterworthCoefficients[0][2] = 0.7857;
//										   butterworthCoefficients[0][3] = 0.5238;
//										   butterworthCoefficients[0][4] = 0.1309;
//
//
//										   butterworthCoefficients[1][0] = 1;
//										   butterworthCoefficients[1][1] = 0.4340;
//										   butterworthCoefficients[1][2] = 0.5456;
//										   butterworthCoefficients[1][3] = 0.0942;
//										   butterworthCoefficients[1][4] = 0.0213;
//
//									   break;
//		                          }
//
//
//	
//
//		break;
//
//
//	}
//
//	return butterworthCoefficients;
//
//}