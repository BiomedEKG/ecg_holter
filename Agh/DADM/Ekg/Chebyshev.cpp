//#include "Chebyshev.h"
//#include "FilterType.h"
//
//std::vector<std::vector<double>> ChebyshevFilter::setParameters (int samplingFrequency, FILTERTYPE filterType) {
//
//	int order1;
//
//	if (filterType == HIGHPASS) {
//		order1 = 3;  
//	    }
//	else {
//		order1 = 4;  
//	}
//
//
//	std::vector<std::vector<double>> chebyshevCoefficients(2, std::vector<double>(order1,0)); 
//
//
//
//
//	switch (filterType){
//
//	case HIGHPASS:
//		switch (samplingFrequency){
//								   case 250:
//									       //b
//										   chebyshevCoefficients[0][0] = 0.8857;
//										   chebyshevCoefficients[0][1] = -1.7714;
//										   chebyshevCoefficients[0][2] = 0.8857;
//
//										   //a
//										   chebyshevCoefficients[1][0] = 1;
//										   chebyshevCoefficients[1][1] = -1.9874;
//										   chebyshevCoefficients[1][2] = 0.9876;
//									
//
//									   break;
//
//								   case 360:
//									       chebyshevCoefficients[0][0] = 0.8873;
//										   chebyshevCoefficients[0][1] = -1.7747;
//										   chebyshevCoefficients[0][2] = 0.8873;
//
//										   chebyshevCoefficients[1][0] = 1;
//										   chebyshevCoefficients[1][1] = -1.9912;
//										   chebyshevCoefficients[1][2] = 0.9913;
//
//								       break;
//
//								   default:
//									       chebyshevCoefficients[0][0] = 0.8873;
//										   chebyshevCoefficients[0][1] = -1.7747;
//										   chebyshevCoefficients[0][2] = 0.8873;
//
//										   chebyshevCoefficients[1][0] = 1;
//										   chebyshevCoefficients[1][1] = -1.9912;
//										   chebyshevCoefficients[1][2] = 0.9913;
//
//
//									   break;
//		                          }
//		break;
//	case LOWPASS:
//		switch (samplingFrequency){
//								   case 250:
//									       //b
//										   chebyshevCoefficients[0][0] = 0.4759;
//										   chebyshevCoefficients[0][1] = 1.4278;
//										   chebyshevCoefficients[0][2] = 1.4278;
//										   chebyshevCoefficients[0][3] = 0.4759;
//
//
//										   //a
//										   chebyshevCoefficients[1][0] = 1;
//										   chebyshevCoefficients[1][1] = 1.6168;
//										   chebyshevCoefficients[1][2] = 1.0366;
//										   chebyshevCoefficients[1][3] = 0.1540;
//
//
//
//									   break;
//
//								   case 360:
//									       chebyshevCoefficients[0][0] = 0.1744;
//										   chebyshevCoefficients[0][1] = 0.5232;
//										   chebyshevCoefficients[0][2] = 0.5232;
//										   chebyshevCoefficients[0][3] = 0.1744;
//
//
//
//										   chebyshevCoefficients[1][0] = 1;
//										   chebyshevCoefficients[1][1] = 0.0159;
//										   chebyshevCoefficients[1][2] = 0.5365;
//										   chebyshevCoefficients[1][3] = -0.1572;
//
//
//
//								       break;
//
//								   default:
//									       chebyshevCoefficients[0][0] = 0.1744;
//										   chebyshevCoefficients[0][1] = 0.5232;
//										   chebyshevCoefficients[0][2] = 0.5232;
//										   chebyshevCoefficients[0][3] = 0.1744;
//
//
//
//										   chebyshevCoefficients[1][0] = 1;
//										   chebyshevCoefficients[1][1] = 0.0159;
//										   chebyshevCoefficients[1][2] = 0.5365;
//										   chebyshevCoefficients[1][3] = -0.1572;
//
//									   break;
//		                          }
//	
//
//		break;
//
//
//	}
//
//	return chebyshevCoefficients;
//
//}